# kad-dht

[TOC]



## 参考

- [`github.com/libp2p/go-libp2p-kad-dht`](https://github.com/libp2p/go-libp2p-kad-dht)
- [`github.com/libp2p/go-libp2p-kbucket`](https://github.com/libp2p/go-libp2p-kbucket)



## 定义

### DHT节点模式

一共定义了4种关于DHT的节点模式:

- ModeAuto：根据网络条件自动在客户端和服务器之间切换。
- ModeClient：DHT客户端，无法响应请求，只能发请求。
- ModeServer：DHT服务器，能发送和响应请求。
- ModeAutoServer：类似于ModeAuto，但是当请求不可达的时候，更像一台DHT服务器。

### DHT消息

通过protobuf定义了以下几种消息（它扩展了kad算法的4种消息）：

- PUT_VALUE
- GET_VALUE
- ADD_PROVIDER
- GET_PROVIDERS
- FIND_NODE
- PING

### DHT节点信息

通过protobuf定义了节点信息如下：

```protobuf
message Peer {
		bytes id = 1 [(gogoproto.customtype) = "byteString", (gogoproto.nullable) = false];
		repeated bytes addrs = 2;
		ConnectionType connection = 3;
	}
```

- id：节点id
- addrs：节点的ip+端口
- connection：连接方式
  - NOT_CONNECTED：未连接
  - CONNECTED：以连接
  - CAN_CONNECT：可连接
  - CANNOT_CONNECT：不可连接

### 路由表结构

todo

### K桶中节点的定义

```go
type PeerInfo struct {
	Id 														peer.ID 	// 节点id
	LastUsefulAt 									time.Time // 
	LastSuccessfulOutboundQueryAt time.Time // 最后一次查询成功的消息
	AddedAt 											time.Time	// 节点添加时间
	dhtId 												ID				// 距离
	replaceable 									bool 			// 是否可替换
}
```





## 初始化节点

### 节点ID生成

```go
// github.com/libp2p/go-libp2p-kbucket/table_refresh.go
func (rt *RoutingTable) GenRandPeerID(targetCpl uint) (peer.ID, error)
```

todo

### IpfsDHT

```go
type IpfsDHT struct {
	host      			host.Host 									 // 主机名
	self      			peer.ID											 // 自己的本地节点id
	selfKey   			kb.ID												 // 公钥
	peerstore 			peerstore.Peerstore 				 // 节点管理表
	datastore 			ds.Datastore 								 // 本地数据仓库接口
	routingTable 		*kb.RoutingTable 						 // 路由表
	ProviderManager *providers.ProviderManager 	 // 证明机管理器
	rtRefreshManager *rtrefresh.RtRefreshManager // 路由表刷新管理器
	birth 					time.Time										 // 节点的启动时间
	Validator 			record.Validator						 // 数据验证器
	ctx  						context.Context
	proc 						goprocess.Process
	strmap 					map[peer.ID]*messageSender	 // 消息发送器
	smlk   					sync.Mutex
	plk sync.Mutex
	stripedPutLocks [256]sync.Mutex
	protocols     []protocol.ID
	protocolsStrs []string
	serverProtocols []protocol.ID
	auto   ModeOpt
	mode   mode
	modeLk sync.Mutex
	bucketSize int
	alpha      int 
	beta       int 
	queryPeerFilter        QueryFilterFunc
	routingTablePeerFilter RouteTableFilterFunc
	rtPeerDiversityFilter  peerdiversity.PeerIPGroupFilter
	autoRefresh bool
	bootstrapPeers []peer.AddrInfo
	maxRecordAge time.Duration
	enableProviders, enableValues bool
	disableFixLowPeers bool
	fixLowPeersChan    chan struct{}
	addPeerToRTChan   chan addPeerRTReq
	refreshFinishedCh chan struct{}
	rtFreezeTimeout time.Duration
	testAddressUpdateProcessing bool
}
```

### ProviderManager

证明机器管理器



## 加入DHT网络

```go
func New(ctx context.Context, h host.Host, options ...Option) (*IpfsDHT, error) {
	var cfg config
  // 创建DHT节点(makeDHT)
	dht, err := makeDHT(ctx, h, cfg)
	if err != nil {
		return nil, fmt.Errorf("failed to create DHT, err=%s", err)
	}
	...
  // 根据传入的cfg.mode来设置DHT节点是客户端还是服务器
	dht.auto = cfg.mode
	switch cfg.mode {
	case ModeAuto, ModeClient:
		dht.mode = modeClient
	case ModeAutoServer, ModeServer:
		dht.mode = modeServer
	default:
		return nil, fmt.Errorf("invalid dht mode %d", cfg.mode)
	}
	if dht.mode == modeServer {
		if err := dht.moveToServerMode(); err != nil {
			return nil, err
		}
	}

	// 新建订阅通知器
	sn, err := newSubscriberNotifiee(dht)
	if err != nil {
		return nil, err
	}
	dht.proc.Go(sn.subscribe)
  ...
	// 发现host列表中的引导节点
	dht.plk.Lock()
	for _, p := range dht.host.Network().Peers() {
		dht.peerFound(dht.ctx, p, false)
	}
	dht.plk.Unlock()

	dht.proc.Go(dht.populatePeers)

	return dht, nil
}
```

如何判定找到的节点是有效？需要同时满足以下条件：

1. 是否支持协议dht协议
2. 是否是未知的节点（已知的节点无法再次添加）
3. 是否可连通

## 添加节点

```go
func (rt *RoutingTable) addPeer(p peer.ID, queryPeer bool, isReplaceable bool) (bool, error) {
	bucketID := rt.bucketIdForPeer(p)
	bucket := rt.buckets[bucketID]

	now := time.Now()
	var lastUsefulAt time.Time
	if queryPeer {
		lastUsefulAt = now
	}

	// 节点已存在表中；跳过
	if peer := bucket.getPeer(p); peer != nil {
		if peer.LastUsefulAt.IsZero() && queryPeer {
			peer.LastUsefulAt = lastUsefulAt
		}
		return false, nil
	}
	// 节点的延迟过大；跳过
	if rt.metrics.LatencyEWMA(p) > rt.maxLatency {
		return false, ErrPeerRejectedHighLatency
	}
	if rt.df != nil {
		if !rt.df.TryAdd(p) {
			return false, errors.New("peer rejected by the diversity filter")
		}
	}
	// 如果k桶的数量没有超过上限，直接添加
	if bucket.len() < rt.bucketsize {
		bucket.pushFront(&PeerInfo{
			Id:                            p,
			LastUsefulAt:                  lastUsefulAt,
			LastSuccessfulOutboundQueryAt: now,
			AddedAt:                       now,
			dhtId:                         ConvertPeerID(p),
			replaceable:                   isReplaceable,
		})
		rt.PeerAdded(p)
		return true, nil
	}
	// 如果k桶的数量接近上限，把一个k桶分裂成2个桶，放进K桶的前面
	if bucketID == len(rt.buckets)-1 {
		rt.nextBucket()
		bucketID = rt.bucketIdForPeer(p)
		bucket = rt.buckets[bucketID]
		if bucket.len() < rt.bucketsize {
			bucket.pushFront(&PeerInfo{
				Id:                            p,
				LastUsefulAt:                  lastUsefulAt,
				LastSuccessfulOutboundQueryAt: now,
				AddedAt:                       now,
				dhtId:                         ConvertPeerID(p),
				replaceable:                   isReplaceable,
			})
			rt.PeerAdded(p)
			return true, nil
		}
	}
  // 如果k桶数量达到上限，且桶子已满；找到一个可替换的节点，替换它；
  // 替换规则：如果p1可替换(replaceable=true)，就替换，否则不替换；
	replaceablePeer := bucket.min(func(p1 *PeerInfo, p2 *PeerInfo) bool {
		return p1.replaceable
	})

	if replaceablePeer != nil && replaceablePeer.replaceable {
    // 删除可替换节点，添加新节点
		if rt.removePeer(replaceablePeer.Id) {
			bucket.pushFront(&PeerInfo{
				Id:                            p,
				LastUsefulAt:                  lastUsefulAt,
				LastSuccessfulOutboundQueryAt: now,
				AddedAt:                       now,
				dhtId:                         ConvertPeerID(p),
				replaceable:                   isReplaceable,
			})
			rt.PeerAdded(p)
			return true, nil
		}
	}
	if rt.df != nil {
		rt.df.Remove(p)
	}
	return false, ErrPeerRejectedNoCapacity
}
```



## 更新节点

节点的更新由路由表刷新管理器来处理，实现如下

```go
func (r *RtRefreshManager) doRefresh(forceRefresh bool) error {
	var merr error
	if err := r.queryForSelf(); err != nil {
		merr = multierror.Append(merr, err)
	}
  // 读取路由表的cplRefreshedAt(最后一次刷新时间记录表)，来作为更新对象
	refreshCpls := r.rt.GetTrackedCplsForRefresh() // 最大15个

	rfnc := func(cpl uint) (err error) {
		if forceRefresh {
			err = r.refreshCpl(cpl) // 强制刷新，产生一个DHT查询
		} else {
			err = r.refreshCplIfEligible(cpl, refreshCpls[cpl]) // 非强制刷新
		}
		return
	}

	for c := range refreshCpls {
		cpl := uint(c)
		if err := rfnc(cpl); err != nil {
			merr = multierror.Append(merr, err)
		} else {
			if r.rt.NPeersForCpl(cpl) == 0 {
				lastCpl := min(2*(c+1), len(refreshCpls)-1)
				for i := c + 1; i < lastCpl+1; i++ {
					if err := rfnc(uint(i)); err != nil {
						merr = multierror.Append(merr, err)
					}
				}
				return merr
			}
		}
	}

	select {
	case r.refreshDoneCh <- struct{}{}:
	case <-r.ctx.Done():
		return r.ctx.Err()
	}

	return merr
}
```



## 定位资源





## 保存资源



## 离开网络



## 查询加速

