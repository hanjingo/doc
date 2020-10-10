# 摘要

ipfs的p2p go语言实现

# 详情 
## 定义类型
|名称|类型|注释|
|:---|:---|:---|
|DisconnectReason|int|断线理由|  
|Option|func(opts *Options) error|设置选项函数|  
|AddrAction|int|地址动作|
|SubscriptionOpt|func(interface{}) error|订阅选项函数|
|EmitterOpt|func(interface{}) error|触发器选项函数|
|CancelFunc|func()|取消函数|
|wildcardSubscription|interface{}|订阅通配符|
|RawJSON|string|滚动的json|
|Direction|int|表示哪类节点需要连接|
|Connectedness|int|连接状态|
|StreamHandler|func(Stream)|流处理器|
|ConnHandler|func(Conn)|连接处理器|
|ID|string|id,节点id|
|PSK|[]byte|利用私钥启用私有网络|
|HandlerFunc|func(protocol string, rwc io.ReadWriteCloser) error|协议或流回调函数|
|Option|func(opts *Options) error|选项路由函数|
|QueryEventType|int|查询事件类型|
|Multiaddr|multiaddr.Multiaddr|多地址|
|PeerID|peer.ID|节点id|
|ProtocolID|protocol.ID|协议id|
|PeerAddrInfo|peer.AddrInfo|节点地址信息|
|Host|host.Host|主机|
|Network|network.Network|网络|
|Conn|network.Conn|连接|
|Stream|network.Stream|流|

## 定义错误
|名称|值|注释|
|:---|:---|:---|
|ErrExpectedEOF|errors.New("read data when expecting EOF")|读空错误|
|ErrReset|errors.New("stream reset")|流重置|
|ErrNoRemoteAddrs|errors.New("no remote addresses")|不存在远程地址错误|
|ErrNoConn|errorrs.New("no usable connection to peer")|没有可用的连接错误|
|ErrEmptyPeerID|errors.New("empty peer ID")|空节点id错误|
|ErrNoPublicKey|errors.New("public key is not embedded in peer ID")|节点的公钥无效|
|ErrNotFound|-|errors.New("item not found")|错误未发现|
|ErrNotInPrivateNetwork|error|NewError("private network was not configured but is enforced by the environment")|不在私有网络|
|ErrEmptyDomain|errors.New("envelope domain must not be empty")|空域|
|ErrEmptyPayloadType|errors.New("payloadType must not be empty")|负载类型不为空|
|ErrInvalidSignature|errors.New("invalid signature or incorrect domain")|不可用签名|
|ErrPayloadTypeNotRegistered|errors.New("payload type is not registered")|负载类型没有注册|
|ErrNotFound|errors.New("routing: not found")|路由未发现|
|ErrNotSupported|errors.New("routing: operation or key not supported")|不支持此路由操作|
  
## 定义全局变量 
#### 地址动作
|名称|类型|注释|
|:---|:---|:---|
|Unknown|AddrAction|0|
|Added|AddrAction|1|
|Maintained|AddrAction|2|
|Removed|AddrAction|3|  
#### 待连接节点类型
|名称|类型|注释|
|:---|:---|:---|
|DirUnknown|Direction|0, 未知节点|
|DirInbound|Direction|1，远程节点连接|
|DirOutbound|Direction|2，本地节点连接|  
### 连接状态
|名称|类型|注释|
|:---|:---|:---|
|NotConnected|Connectedness|0，连接未连接|
|Connected|Connectedness|1，连接已打开，且活动着|
|CanConnect|Connectedness|2，可以连接，意味着最近连接过，已经被安全地关闭|
|CannotConnect|Connectedness|3，无法连接，意味着最近尝试连接过，但是失败了|
#### 可连接性
|名称|类型|注释|
|:---|:---|:---|
|ReachabilityUnknown|Reachability|0，无法确定是否可连接|
|ReachabilityPublic|Reachability|1，可被公开连接|
|ReachabilityPrivate|Reachability|2，可以被私有连接|
#### 节点时长设置
|名称|类型|注释|
|:---|:---|:---|
|AddressTTL|time.Duration|1小时, 地址有效期|
|TempAddrTTL|time.Duration|2分钟, 临时地址有效期|
|ProviderAddrTTL|time.Duration|10分钟, 提供者地址有效期|
|RecentlyConnectedAddrTTL|time.Duration|10分钟, 最近连接地址有效期|
|OwnObservedAddrTTL|time.Duration|10分钟, 节点监视地址有效期|
|PermanentAddrTTL|time.Duration|math.MaxInt64, 长期地址时长|
|ConnectedAddrTTL|time.Duration|math.MaxInt64-1, 连接地址时长|
### psk路径
|名称|类型|注释|
|:---|:---|:---|
|pathPSKv1|[]byte|"/key/swarm/psk/1.0.0/"|psk地址|
|pathBin|string|"/bin/"|
|pathBase16|string|"/base16/"|
|pathBase64|string|"/base64/"|
### 查询事件类型
|名称|类型|注释|
|:---|:---|:---|
|SendingQuery|QueryEventType|0, 发送查询到节点|
|PeerResponse|QueryEventType|1, 节点响应|
|FinalPeer|QueryEventType|2, 发现一个"closest"节点|
|QueryError|QueryEventType|3, 查询出错|
|Provider|QueryEventType|4, 发现一个提供者|
|Value|QueryEventType|5, 发现一个值|
|AddingPeer|QueryEventType|6, 添加一个节点到查询|
|DialingPeer|QueryEventType|7, 向节点拨号|
#### 其他
|名称|类型|注释|
|:---|:---|:---|
|DecayFn|func(value DecayingValue, delta int) (after int)|以减法value的腐败值|
|BumpFn|func(value DecayingValue, delta int) (after int)|以加法计算value的腐败值|
|ConnManager|NullConnMgr|连接管理器| 
|EOFTimeout|time.Second|60秒,流处理超时时长|
|NoopHandler|func(s MuxedStream){s.Reset()}|重置流|
|DialPeerTimeout|time.Duration|60秒, 拨号超时|
|MessageSizeMax|1 << 22|4MB, 最大消息尺寸|
|**AdvancedEnableInlining**|bool|true, 让键少于42字节,除非必要千万不要改,默认为true(极重要)|
|**maxInlineKeyLength**|int|42, 最大键长度|
|PeerRecordEnvelopeDomain|string|"libp2p-peer-record"|
|PeerRecordEnvelopePayloadType|[]byte|[]byte{0x03, 0x01}, 节点记录负载类型|
|EnvKey|string|"LIBP2P_FORCE_PNET", 环境变量|
|ForcePrivateNetwork|bool|false, 如果设置了"LIBP2P_FORCE_PNET"环境变量,就启用私有网络|
|TestingID|ID|"/p2p/_testing", 测试id|
|QueryEventBufferSize|int|16, 查询事件缓存尺寸|
|ID|string|"/plaintext/2.0.0"|
|DialTimeout|60秒, 拨号超时|
|AcceptTimeout|60秒, 接收超时|
  
## 定义全局函数
|函数|注释|
|:---|:---|
|DecayFn func(value DecayingValue) (after int, rm bool)|过期函数|
|BumpFn func(value DecayingValue, delta int) (after int)|碰撞函数|
|SupportsDecay(mgr ConnManager) (Decayer, bool)|连接管理器转decayer|
|DecayNone() DecayFn|返回过期值的真实值|
|DecayFixed(minuend int) DecayFn|是否匹配minued|
|DecayLinear(coef float64) DecayFn|是否匹配coef|
|DecayExpireWhenInactive(after time.Duration) DecayFn|判断是否超过指定过期时间|
|BumpSumUnbounded() BumpFn|计算参数value的值与参数delta数量值之和(不指定范围)|
|BumpSumBounded(min, max int) BumpFn|计算参数value的值与delta数量值之和(指定范围)|
|BumpOverwrite() BumpFn|无意义|
|MultistreamSemverMatche(base protocol.ID) (func(string) bool, error)|根据协议id返回一个版本比较函数|
|FlullClose(s network.Stream) error|读完再关闭流|
|AwaitEOF(s network.Stream) error|等待读完|
|InfoFromHost(h Host) *peer.AddrInfo|返回主机的id和地址信息|
|NewBandwidthCounter() *BandwidthCounter|new一个带宽统计器|
|RegisterViews(namespace string, views ...*view.View) error|?|
|LookupViews(name string) ([]*view.View, error)|?|
|AllViews() []*view.View|?|
|WithNoDial(ctx context.Context, reason string) context.Context|?|
|GetNoDial(ctx context.Context) (nodial bool, reason string)|开启新stream|
|GetDialPeerTimeout(ctx context.Context) time.Duration|获得节点拨号时长|
|WithDialPeerTimeout(ctx context.Context, timeout time.Duration) context.Context|返回一个携带超时信息的上下文|
|AddrInfoFromP2pAddrs(maddrs ...go-multiaddr.Multiaddr) ([]AddrInfo, error)|从p2p地址获得地址信息|
|SplitAddr(m ma.Multiaddr) (transport ma.Multiaddr, id ID)|拆分节点|
|AddrInfoFromP2pAddr(m ma.Multiaddr) (*AddrInfo, error)|从p2p节点地址返回一个节点信息|
|AddrInfoToP2pAddrs(pi *AddrInfo) ([]ma.Multiaddr, error)|从节点信息转回p2p节点地址|
|IDFromString(s string) (ID, error)|将string转化为id|
|IDFromBytes(b []byte) (ID, error)|将二进制数组转化为id|
|IDB58Decode(s string) (ID, error)|将58位的string转化为id|
|IDB58Encode(id ID) string|将id转为58位的string|
|IDHexDecode(s string) (ID, error)|16进制数据转id|
|IDHexEncode(id ID) string|id转16进制string|
|Decode(s string) (ID, error)|从str转id，id可能为multi_hash或sha256|
|Encode(id ID) string|id编码为58位string|
|FromCid(c cid.Cid) (ID, error)|将CID转id|
|ToCid(id ID) cid.Cid|将id转化为版本为v1的cid|
|IDFromPublicKey(pk ic.Pubkey) (ID, error)|公钥转id|
|IDFromPrivateKey(sk ic.PrivKey) (ID, error)|私钥转id，先提取公钥再转换|
|NewPeerRecord() *PeerRecord|新建节点记录|
|PeerRecordFromAddrInfo(info AddrInfo) *PeerRecord|从地址信息创建一个节点记录|
|PeerRecordFromProtobuf(msg *pb.PeerRecord) (*PeerRecord, error)|从protobuf转为节点记录|
|DecodeV1PSK(in io.Reader) (PSK, error)|解密PSK|
|ConvertFromStrings(ids []string) (res []ID)|从string集合转换为id集合|
|ConverToStrings(ids []ID) (res []string)|将id集合转换为string集合|
|Seal(rec Record, privateKey crypto.PrivKey) (*Envelope, error)|?|
|ConsumeEnvelope(data []byte, domain string) (envelope *Envelope, rec Record, err error)|?|
|UnmarshalEnvelope(data []byte) (*Envelope, error)|
|Expired|func(opts *Options) error|设置选项过期|
|Offline|func(opts *Options) error|设置选项掉线|
|RegisterForQueryEvents(ctx context.Context) (context.Context, <-chan *QueryEvent>)|注册并返回一个事件管道|
|PublishQueryEvent(ctx context.Context, ev *QueryEvent)|发布一个查询事件到事件管道|
|SubscribesToQueryEvents(ctx context.Context) bool|订阅查询事件|
|KeyForPublicKey(id peer.ID) string{return "/pk/" + string(id)}|将节点id转为string并返回|
|GetPublicKey(r ValueStore, ctx context.Context, p peer.ID) (ci.PubKey, error)|从节点id提取公钥，如果失败，就用r来提取私钥，并转为公钥|

### 定义事件
|事件|参数1|参数2|参数3|参数4|
|:---|:---|:----|:----|:---|
|EvtLocalAddressesUpdated 地址更新事件|Diffs bool 是否与上一个地址不同|Current []UpdatedAddress 当前更新地址集合|Removed []UpdatedAddress 删除的更新地址集合|SignedPeerRecord *record.Envelope 已经签名的节点记录|
|GenericDHTEvent DHT事件|Type string 类型|Raw RawJSON json类型|
|EvtPeerIdentificationCompleted 节点验证完成事件|Peer peer.ID 节点id|
|EvtPeerIdentifiecationFailed 节点验证失败事件|Peer peer.ID 节点id|Reason error 原因|
|EvtPeerConnectednessChanged 节点连接变更事件|Peer peer.ID 节点id|Connectedness network.Connectedness|
|EvtPeerProtocolsUpdated 节点协议变更事件|Peer peer.ID 节点id|Added []protocol.ID 新增的协议id集合|Removed []protocol.ID 删除的协议id集合|
|EvtLocalProtocolsUpdated 本地协议变更事件|Added []protocol.ID 新增的协议id集合|Removed []protocol.ID 删除的协议id集合|
|EvtLocalReachabilityChanged 本地节点可访问性变更事件|Reachability network.Reachability 可访问性|
  
## 定义接口
### Decayer 标记注册器
|接口|注释|
|:---|:---|
|io.Closer|关闭器|
|RegistersDecayingTag(name string, interval time.Duration, decayFn DecayFn, bumpFn BumpFn) (DecayingTag, error)|注册标记|  

### DecayingTag 腐败标记
|接口|注释|
|:---|:---|
|Name() string|返回标记名字|
|Interval() time.Duration|时长|
|Bump(peer peer.ID, delta int) error|设置delta到标记值|
|Remove(peer peer.ID) error|移除节点的标记|
|Close() error|关闭标记|  

### ConnectionGater 网关
|接口|注释|
|:---|:---|
|InterceptPeerDial(p peer.ID) (allow bool)|中断向节点拨号|
|InterceptAddrDial(peer.ID, ma.Multiaddr) (allow bool)|中断向地址的拨号|
|InterceptAccept(network.ConnMultiaddrs) (allow bool)|中断建立连接|
|InterceptSecured(network.Directionn, peer.ID, network.ConnMultiaddrs) (allow bool)|中断握手验证|
|InterceptUpgraded(network.Conn) (allow bool, reason control.DisconnectReason)|中断升级协议|   

### ConnManager 连接管理器
|接口|注释|
|:---|:---|
|TagPeer(peer.ID, string, int)|给节点打标记，用来标识节点|  
|UntagPeer(p peer.ID, tag string)|取消节点的标记|
|UpsertTag(p peer.ID, tag string, upsert func(int)int)|更新节点标记|
|GetTagInfo(p peer.ID) *TagInfo|获得tag信息|
|TrimOpenConns(ctx context.Context)|终止已打开的连接|
|Notice() network.Notifiee|返回一个通知函数|
|Protect(id peer.ID, tag string)|给节点打标记，并赋予保护|
|Unprotect(id peer.ID, tag string) (protected bool)|打标记并取消保护|
|IsProtected(id peer.ID, tag string) (protected bool)|判断节点是否被保护|
|Close() error|关闭连接管理器|   

### Advertiser 推荐器
|接口|注释|
|:---|:---|  
|Advertise(ctx context.Context, ns string, opts ...Option) (time.Duration, error)|推荐|  

### Discoverer 发现器
|接口|注释|
|:---|:---|  
|FindPeers(ctx context.Context, ns string, opts ...Option) (<-chan peer.AddrInfo, error)|查找节点|  

### Discovery 发现接口,包括推荐器和发现器
|接口|注释|
|:---|:---|
|Advertiser|推荐器|
|Discoverer|发现器|  

### Emitter 触发器
|接口|注释|
|:---|:---|
|io.Closer|关闭接口|
|Emit(evt interfae{}) error|触发事件到eventbus,调用错误的事件会导致panic|  

### Subscription 订阅器
|接口|注释|
|:---|:---|
|io.Closer|关闭接口|
|Out() <-chan interface{}|返回一个用来消费事件的管道|  

### Bus 总线
|接口|注释|
|:---|:---|
|Subscribe(eventType interface{}, opts ...SubscriptionOpt) (Subscription, error)|订阅事件|
|Emitter(eventType interface{}, opts ...EmitterOpt) (Emitter, error)|根据事件创建一个触发器|
|GetAllEventTypes() []reflect.Type|返回所有的事件类型|  

### Host 主机
|接口|注释|
|:---|:---|
|ID() peer.ID|返回本地节点id|
|Peerstore() peerstore.Peerstore|返回节点存储的信息(地址,key...)|
|Addrs() []ma.Multiaddr|返回主机坚挺的地址集合|
|NetWork() network.Network|返回主机的网络接口|
|Mux() protocol.Switch|返回入流的多路复用器|
|Connect(ctx context.Context, pi peer.AddrInfo) error|连接地址|
|SetStreamHandler(pid protocol.ID, handler network.StreamHandler)|设置流处理器|
|SetStreamHandlerMatch(protocol.ID, func(string) bool, network.StreamHandler)|设置流处理器匹配|
|RemoveStreamHandler(pid protocol.ID)|设置流处理器|
|NewStream(ctx context.Context, p peer.ID, pids ...protocol.ID) (network.Stream, error)|新建流|
|Close() error|关闭网络和服务|
|ConnManager() connmgr.ConnManager|返回端点的连接管理器|
|EventBus() event.Bus|返回端点的事件总线|  

### IntrospectableHost
|接口|注释|
|:---|:---|
|Introspector() introspection.Introspector|?|
|IntrospectionEndpoint() introspection.Endpoint|?|

### Reporter 报告器
|接口|注释|
|:---|:---|
|LogSentMessage(int64)|统计发消息大小|
|LogRecvMessage(int64)|统计收消息大小|
|LogSentMessageStream(int64, protocol.ID, peer.ID)|统计发消息流|
|LogRecvMessageStream(int64, protocol.ID, peer.ID)|统计收消息流|
|GetBandwidthForPeer(peer.ID) Stats|获得节点的带宽|
|GetBandwidthForProtocol(protocol.ID) Stats|获得协议的带宽|
|GetBandwidthTotals() Stats|获得总带宽|
|GetBandwidthByPeer() map[peer.ID]Stats|获得所有节点对应的带宽|
|GetBandwidthByProtocol() map[protocol.ID]Stats|获得所有协议对应的带宽|

### MuxedStream 多路流
|接口|注释|
|:---|:---|
|io.Reader|读接口|
|io.Writer|写接口|
|io.Closer|关闭接口|
|Reset() error|重置|
|SetDeadline(time.Time) error|设置过期时间|
|SetReadDeadline(time.Time) error|设置读过期时间|
|SetWriteDeadline(time.Time) error|设置写过期时间|

### MuxedConn 多路连接
|接口|注释|
|:---|:---|
|io.Closer|关闭接口|
|IsClosed() bool|连接是否已关闭|
|OpenStream() (MuxedStream, error)|打开流|
|AcceptStream() (MuxedStream, error)|接收流|  

### Multiplexer 多路调制器
|接口|注释|
|:---|:---|
|NewConn(c net.Conn, isServer bool) (MuxedConn, error)|新建连接|  

### Conn 连接
|接口|注释|
|:---|:---|
|io.Closer|关闭器|
|ConnSecurity|连接鉴别器|
|ConnMultiaddrs|连接的地址|
|ID() string|连接的id|
|NewStream() (Stream, error)|新建流|
|GetStreams() []Stream|获得连接的所有流|
|Stat() Stat|返回连接的状态|

### ConnSecurity 连接的可靠性信息
|接口|注释|
|:---|:---|
|LocalPeer() peer.ID|本机节点|
|LocalPrivateKey() ic.PrivKey|返回本机私钥|
|RemotePeer() peer.ID|返回远程节点|
|RemotePublicKey() ic.PubKey|返回远程节点公钥|

### ConnMultiaddrs 连接的多地址
|接口|注释|
|:---|:---|
|LocalMultiaddr() ma.Multiaddr|返回本机的多节点地址|
|RemoteMultiaddr() ma.Multiaddr|返回远程的多节点地址|  

### Network 连接
|接口|注释|
|:---|:---|
|Dialer|拨号器|
|io.Closer|关闭器|
|SetStreamHandler(StreamHandler)|设置流回调器|
|SetConnHandler(ConnHandler)|设置连接回调器|
|NewStream(context.Context, peer.ID) (Stream, error)|新建流|
|Listen(...ma.Multiaddr) error|监听地址|
|ListenAddresses() []ma.Multiaddr|返回监听地址|
|InterfaceListenAddresses() ([]ma.Multiaddr, error)|-|
|Process() goprocess.Process|返回网络的进程|  

### Dialer 拨号器
|接口|注释|
|:---|:---|
|Peerstore() peerstore.Peerstore|节点存储|
|LocalPeer() peer.ID|返回关联网络的本地节点|
|DialPeer(context.Context, peer.ID) (Conn, error)|向节点拨号并建立连接|
|ClosePeer(peer.ID) error|关闭节点连接|
|Connectedness(peer.ID) Connectedness|-|
|Peers() []peer.ID|返回已连接的节点id集合|
|Conns() []Conn|返回连接集合|
|ConnsToPeer(p peer.ID) []Conn|根据节点id的连接集合|
|Notify(Notifiee)|通知|
|StopNotify(Notifiee)|停止通知|  

### Notifiee 通知
|接口|注释|
|:---|:---|
|Listen(Network, ma.Multiaddr)|监听|
|ListenClose(Network, ma.Multiaddr)|关闭监听|
|Connected(Network, Conn)|连接打开通知|
|Disconnected(Network, Conn)|连接关闭通知|
|OpenedStream(Network, Stream)|流打开通知|
|ClosedStream(Network, Stream)|流关闭通知|

### Stream 流
|接口|注释|
|:---|:---|
|mux.MuxedStream|多路流|
|ID() string|返回流id|
|Protocol() protocol.ID|返回流协议id|
|SetProtocol(id protocol.ID)|设置流协议id|
|Stat() Stat|返回流状态|
|Conn() Conn|返回流连接|

### Peerstore 节点存储
|接口|注释|
|:---|:---|
|io.Closer|关闭器|
|AddrBook|地址簿|
|KeyBook|key薄|
|PeerMetadata|节点数据|
|Metrics|-|
|ProtoBook|协议薄|
|PeerInfo(peer.ID) peer.AddrInfo|根据节点id返回节点地址信息|
|Peers() peer.IDSlice|返回所有节点|

### PeerMetadata 节点元数据
|接口|注释|
|:---|:---|
|Get(p peer.ID, key string) (interface{}, error)|拿元数据|
|Put(p peer.ID, key string, val interface{}) error|放元数据|

### AddrBook 地址簿
|接口|注释|
|:---|:---|
|AddAddr(p peer.ID, addr ma.Multiaddr, ttl time.Duration)|添加地址|
|AddAddrs(p peer.ID, addrs []ma.Multiaddr, ttl time.Duration)|添加地址集合|
|SetAddr(p peer.ID, addr ma.Multiaddr, ttl time.Duration)|设置节点地址|
|SetAddrs(p peer.ID, addrs []ma.Multiaddr, ttl time.Duration)|设置地址集合|
|UpdateAddrs(p peer.ID, oldTTL time.Duration, newTTL time.Duration)|更新地址集合|
|Addrs(p peer.ID) []ma.Multiaddr|返回地址集合|
|AddrStream(context.Context, peer.ID) <-chan ma.Multiaddr|添加流|
|ClearAddrs(p peer.ID)|清空节点地址集合|
|PeersWithAddrs() peer.IDSlice|-|  

### CertifiedAddrBook 加密地址本
|接口|注释|
|:---|:---|
|ConsumePeerRecord(s *record.Envelope, ttl time.Duration) (accepted bool, err error)|?|
|GetPeerRecord(p peer.ID) *record.Envelope|?|

### KeyBook 钥匙本
|接口|注释|
|:---|:---|
|PubKey(peer.ID) ic.PubKey|根据节点id返回公钥|
|AddPubKey(peer.ID, ic.PubKey)|添加公钥|
|PrivKey(peer.ID) ic.PrivKey|根据节点id返回私钥|
|AddPrivKey(peer.ID, ic.PrivKey) error|添加私钥|
|PeersWithKeys() peer.IDSlice|?|

### Metrics 度量器
|接口|注释|
|:---|:---|
|RecordLatency(peer.ID, time.Duration)|?|
|LatencyEWMA(peer.ID) time.Duration|?|

### ProtoBook 协议本
|接口|注释|
|:---|:---|
|GetProtocols(peer.ID) ([]string, error)|根据节点id拿协议|
|AddProtocols(peer.ID, ...string) error|添加协议|
|SetProtocols(peer.ID, ...string) error|设置协议|
|RemoveProtocols(peer.ID, ...string) error|删除协议|
|SupportsProtocols(peer.ID, ...string) ([]string, error)|返回节点支持的协议|
|FirstSupportedProtocol(peer.ID, ...string) (string, error)|第一个支持的协议|

### Router 路由器
|接口|注释|
|:---|:---|
|AddHandler(protocol string, handler HandlerFunc)|给协议添加回调函数|
|AddHandlerWithFunc(protocol string, match func(string) bool, handler HandlerFunc)|设置匹配的回调函数|
|RemoveHandler(protocol string)|移除协议的回调函数|
|Protocols() []string|返回路由器节点集合|

### Negotiator 协调器
|接口|注释|
|:---|:---|
|NegotiateLazy(rwc io.ReadWriteCloser) (io.ReadWriteCloser, string, HandleFunc, error)|消极协商（阻塞）|
|Negotiate(rwc io.ReadWriteCloser) (string, HandleFunc, error)|协商|
|Handle(rwc io.ReadWriteCloser) error|读/写关闭回调|

### Switch 交换机
|接口|注释|
|:---|:---|
|Router|路由器|
|Negotiator|协调器|

### Record 记录
|接口|注释|
|:---|:---|
|Domain() string|域|
|Codec() []byte|?|
|MarshalRecord() ([]byte, error)|序列化record为二进制数组|
|UnmarshalRecord([]byte) error|反序列二进制数组为record|

### ContentRouting 内容路由
|接口|注释|
|:---|:---|
|Provide(context.Context, cid.Cid, bool) error|将cid验证并加入路由系统，如果失败，保存在本地|
|FindProvidersAsync(context.Context, cid.Cid, int) <-chan peer.AddrInfo|-|

### PeerRouting 节点路由
|接口|注释|
|:---|:---|
|FindPeer(context.Context, peer.ID) (peer.AddrInfo, error)|根据ID搜索节点|

### ValueStore 值存储
|接口|注释|
|:---|:---|
|PutValue(context.Context, string, []byte, ...Option) error|根据key放值|
|GetValue(context.Context, string, ...Option) ([]byte, error)|根据key拿值|
|SearchValue(context.Context, string, ...Option) (<-chan []byte, error)|根据key查询值|

### Routing 路由
|接口|注释|
|:---|:---|
|ContentRouting|内容路由|
|PeerRouting|节点路由|
|ValueStore|值存储|
|Bootstrap(context.Context) error|-|

### PubKeyFetcher 公钥抓取器
|接口|注释|
|:---|:---|
|GetPublicKey(context.Context, peer.ID) (ci.PubKey, error)|根据节点id拿公钥|

### SecureConn 可靠的连接
|接口|注释|
|:---|:---|
|net.Conn|连接|
|ConnSecurity|连接可靠性信息|

### SecureTransport 可靠的传输
|接口|注释|
|:---|:---|
|SecureInbound(ctx context.Context, insecure net.Conn) (SecureConn, error)|验证一个输入连接|
|SecureOutbound(ctx context.Context, insecure net.Conn, p peer.ID) (SecureConn, error)|验证一个输出连接|

### CapableConn 可伸缩连接
|接口|注释|
|:---|:---|
|mux.MuxedConn|多路连接|
|network.ConnSecurity|连接验证|
|network.ConnMultiaddrs|连接地址|
|Transport() Transport|返回连接所属的传输方式|

### Transport 传输
|接口|注释|
|:---|:---|
|Dial(ctx context.Context, raddr ma.Multiaddr, p peer.ID) (CapableConn, error)|拨号|
|CanDial(addr ma.Multiaddr) bool|判断地址能否拨号|
|Listen(laddr ma.Multiaddr) (Listener, error)|监听地址|
|Protocols() []int|返回协议|
|Proxy() bool|代理|

### Listener 监听器
|接口|注释|
|:---|:---|
|Accept() (CapableConn, error)|接收监听|
|Close() error|关闭监听|
|Addr() net.Addr|返回监听地址|
|Multiaddr() ma.Multiaddr|返回多地址|

### TransportNetwork 传输网络
|接口|注释|
|:---|:---|
|network.Network|网络|
|AddTransport(t Transport) error|添加传输|
  
## 定义类
### DecayingValue 过期标签
|名字|类型|注释|
|:---|:---|:---|
|Tag|DecayingTag|衰退标记|
|Peer|peer.ID|节点id|
|Added|time.Time|添加时间|
|LastVisit|time.Time|最后一次访问时间|
|Value|int|当前标记值|  

### TagInfo 标签信息
|名字|类型|注释|
|:---|:---|:---|
|FirstSeen|time.Time|标记时间|
|Value|int|标记值|
|Tags|map[string]int|标记集合|
|Conns|map[string]time.Time|连接集合|  

### Options 选项集合
|名字|类型|注释|
|:---|:---|:---| 
|Tt1|time.Duation|时长|
|Limit|int|限制|
|Other|map[interface{}]interface{}|其它选项集合|
|Apply(options ...Option) error|func|应用选项|
|TTL(ttl time.Duration) Option|func|-|
|Limmit(limit int) Option|func|设置限制|  

### UpdatedAddress 更新地址集合
|名字|类型|注释|
|:---|:---|:---| 
|Address|go-multiaddr.Multiaddr|多地址|
|Action|AddrAction|地址动作|  

### BandwidthCounter 带宽统计器
|名字|类型|注释|
|:---|:---|:---|
|totalIn|flow.Meter|总收包消息数量|
|totalOut|flow.Meter|总发包消息数量|
|protocolIn|flow.MeterRegister|收包协议的消息数量|
|protocolOut|flow.MeterRegister|发包协议的消息数量|
|peerIn|flow.MeterRegister|收包节点|
|peerOut|flow.MeterRegister|发包节点|
|LogSentMessage(size int64)|func|发消息数量统计|
|LogRecvMessage(size int64)|func|收消息数量统计|
|LogSentMessageStream(size int64, proto protocol.ID, p peer.ID)|func|发消息数量统计，所属协议统计|
|LogRecvMessageStream(size int64, proto protocol.ID, p peer.ID)|func|收消息数量统计，所属协议统计|
|LogGetBandwidthForPeer(p peer.ID) (out Stats)|func|返回节点的带宽信息|
|GetBandwidthForProtocol(proto protocol.ID) (out Stats)|func|返回协议带宽|
|GetBandwidthTotals() (out Stats)|func|获得带宽总计|
|GetBandwidthByPeer() map[peer.ID]Stats|func|获得所有节点的带宽信息|
|GetBandwidthByProtocol() map[protocol.ID]Stats|func|获得所有协议的带宽信息|
|Reset()|func|重置信息|
|TrimIdle(since time.Time)|func|减去since以前的统计信息|

### Stats 带宽状态
|名字|类型|注释|
|:---|:---|:--|
|TotalIn|int64|收包消息数量|
|TotalOut|int64|发包消息数量|
|RateIn|float64|收包速率|
|RateOut|float64|发包速率|  

### Stat 
|名字|类型|注释|
|:---|:---|:--|
|Direction|Direction|标识是入或出的连接|
|Opened|time.Time|连接打开时间|
|Extra|map[interface{}]interface{}|保存的连接信息|  

### NotifyBundle 通知绑定 
|名字|类型|注释|
|:---|:---|:--|
|Listen(n Network, a ma.Multiaddr)|func|监听|
|ListenClose(n Network, a ma.Multiaddr)|func|关闭监听|
|Connected(n Network, c Conn)|func|已连接|
|Disconnected(n Network, c Conn)|func|关闭连接|
|OpenedStream(n Network, s Stream)|func|打开流|
|ClosedStream(n Network, s Stream)|func|关闭流|  

### AddrInfo 地址信息 
|名字|类型|注释|
|:---|:---|:--|
|ID|ID|-|
|Addrs|[]go-multiaddr.Multiaddr|地址|
|Loggable() map[string]interface{}|func|打印|
|MarshalJSON() ([]byte, error)|地址信息转json|
|UnmarshalJSON(b []byte) error|json转回地址信息|  

### ID 节点id 
|名字|类型|注释|
|:---|:---|:--|
|Pretty() string|func|编码为58位的string|
|Loggable() map[string]interface{}|func|打日志|
|String() string|func|返回节点的string|
|ShortString() string|func|返回短string|
|MatchesPrivateKey(sk ic.PrivKey) bool|func|私钥配对|
|MatchesPublicKey(pk ic.PubKey) bool|func|公钥配对|
|ExtractPublicKey() (ic.PubKey, error)|func|从id（multi_hash）中提取公钥|
|Validate() error|func|检查节点id是否为空|
|Marshal() ([]byte, error)|func|id强转字节数组|
|MarshalBinary() ([]byte, error)|func|id序列化位字节数组|
|MarshalTo(data []byte) (n int, err error)|序列化|
|Unmarshal(data []byte) (err error)|反序列化|
|UnmarshalBinary(data []byte) error|反序列化|
|Size() int|尺寸|
|MarshalJSON() ([]byte, error)|序列化为json|
|UnmarshalJSON(data []byte) (error)|反序列化json|
|MarshalText() ([]byte, error)|序列化文本|
|UnmarshalText(data []byte) error|反序列化文本|

### PeerRecord 节点记录 
|名字|类型|注释|
|:---|:---|:--|
|PeerID|ID|节点id|
|Addrs|[]go-multiaddr.Multiaddr|地址集合|
|Seq|uint64|?|
|Domain() string|func|?|
|Codec() []byte|func|?|
|UnmarshalRecord(bytes []byte) error|func|?|
|MarshalRecord() ([]byte, error)|func|?|
|Equal(other *PeerRecord) bool|func|?|
|ToProtobuf() (*pb.PeerRecord, error)|func|?|

### Envelope  
|名字|类型|注释|
|:---|:---|:--|
|PublicKey|crypto.PubKey|-|
|PayloadType|[]byte|-|
|RawPayload|[]byte|-|
|signature|[]byte|-|
|cached|Record|-|
|unmarshalError|error|-|
|unmarshalOnce|sync.Once|-|
|Marshal() ([]byte, error)|func|序列化成protobuf|
|Equal(other *Envelope) bool|func|-|
|Record() (Record, error)|func|-|
|TypeReord(domain string) error|func|-|
|validate(domain string) error|func|-|  

### Options 选项  
|名字|类型|注释|
|:---|:---|:--|
|Expired|bool|是否过期|
|Offline|bool|是否掉线|
|Other|map[interface{}]interface{}|其它选项|
|Apply(options ...Option) error|func|采取选项|
|ToOption()|func|复制一个选项|

### QueryEvent 查询事件  
|名字|类型|注释|
|:---|:---|:--|
|ID|peer.ID|事件id|
|Type|QueryEventType|事件类型|
|Responses|[]*peer.AddrInfo|响应集合|
|Extra|string|-|
|MarshalJSON() ([]byte, error)|func|将事件转为json|
|UnmarshalJSON(b []byte) error|func|将json解析为事件|

### Transport   
|名字|类型|注释|
|:---|:---|:--|
|id|peer.ID|id|
|key|ci.PrivKey|私钥|
|LocalPeer() peer.ID|func|返回本地id|
|LocalPrivateKey() ci.PrivKey|func|返回本地私钥|
|SecureInbound(ctx context.Context, insecure net.Conn) (sec.SecureConn, error)|func|通过握手让输入可靠|
|SecureOutbound(ctx context.Context, insecure net.Conn, p peer.ID) (sec.SecureConn, error)|通过握手让输出可靠|

### Conn   
|名字|类型|注释|
|:---|:---|:--|
|-|net.Conn|继承自网络连接|
|local|peer.ID|本机节点id|
|remote|peer.ID|远程节点id|
|localPrivKey|ci.PrivKey|本机私钥|
|remotePubKey|ci.PubKey|远程公钥|
|LocalPeer() peer.ID|func|返回本机节点id|
|RemotePeer() peer.ID|func|返回远程节点id|
|RemotePublicKey() ci.PubKey|func|返回远程节点公钥|
|LocalPrivateKey() ci.PrivKey|func|返回本地节点私钥|
  
