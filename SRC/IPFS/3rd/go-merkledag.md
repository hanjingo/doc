# 摘要
merkeldag，用来存文件路径；做路径遍历操作；
  
# 详情
[go-merkledag](https://github.com/ipfs/go-merkledag)
## 定义类型
|名称|类型|注释|
|:-----|:-----|:------|
|Order|int|序列类别|
|Func|func(current State) error|遍历节点回调函数|
|GetLinks|func(context.Context, cid.Cid) ([]*ipld.Link, error)|获得cid的所有链接|
|WaltOption|func(*walkOptions)|设置遍历选项|
|ErrFunc|func(err error) error|错误回调函数|
|dfsFunc|func(state State, t *traversal) error|定义|
|ChangeType|int|数据操作类型|
## 定义全局变量
|名称|类型|注释|
|:-----|:-----|:------|
|v0CidPrefix|cid.Prefix|cid.Prefix{Codec: cid.DagProtobuf, MhLength: -1, MhType: mh.SHA2_256, Version: 0,}|
|v1CidPrefix|cid.Prefix	|cid.Prefix{Codec: cid.DagProtobuf, MhLength: -1, MhType: mh.SHA2_256, Version: 1,}|
|DFSPre|Order|0, 前序遍历|
|DFSPost|Order|1, 后序遍历|
|BFS|Order|2, 宽度优先遍历|
|Add|ChangeType|0.添加|
|Remove|ChangeType|1.删除|
|Mod|ChangeType|2.修改|

## 定义全局函数
|函数|注释|
|:-----|:-----|
|V0CidPrefix() cid.Prefix|返回全局变量v0CidPrefix|
|V1CidPrefix() cid.Prefix|返回全局变量v1CidPrefix|
|PrefixForCidVersion(version int) (cid.Prefix, error)|返回cid前缀|
|NodeWithData(d []byte) *ProtoNode|根据byte数组新建节点|
|NewDAGService(bs bserv.BlockService) *dagService|新建一个DAG服务|
|GetLinksDirect(serv ipld.NodeGetter) GetLinks|-|
|FetchGraph(ctx context.Context, root cid.Cid, serv ipld.DAGService) error|拿到结点的子节点|
|FetchGraphWithDepthLimit(ctx context.Context, root cid.Cid, depthLim int, serv ipld.DAGService) error|按照指定深度拿节点的子节点，深度为0返回root节点，深度为-1无限制|
|GetLinksWithDAG(ng ipld.NodeGetter) GetLinks|返回一个获得所有链接的函数|
|SkipRoot() WalkOption|设置跳过root节点|
|Concurrent() WalkOption|设置默认协程数量|
|Concurrency(worker int) WalkOption|设置指定协程数量|
|IgnoreErrors() WalkOption|设置忽略错误|
|IgnoreMissing() WalkOption|设置跳过ipld.ErrNotFound|
|OnMissing(callback func(c cid.Cid)) WalkOption|设置ipld.ErrNotFound错误回调|
|OnError(handler func(c cid.Cid, err error) error) WalkOption|设置错误回调|
|Walk(ctx context.Context, getLinks GetLinks, c cid.Cid, visit func(cid.Cid) bool, options ...WalkOption) error|深度优先遍历|
|WalkDepth(ctx context.Context, getLinks GetLinks, c cid.Cid, visit func(cid.Cid, int) bool, options ...WalkOption) error|深度遍历|
|NewRawNode(data []byte) *RawNode|使用sha-256算法创建一个只包含数据的节点|
|DecodeRawBlock(block blocks.Block) (ipld.Node, error)|解析只包含数据的节点|
|NewRawNodeWPrefix(data []byte, builder cid.Builder) (*RawNode, error)|通过cid构建器创建一个只包含数据的节点|
|NewReadOnlyDagService(ng ipld.NodeGetter) ipld.DAGService|新建一个只读DagService|
|NewSession(ctx context.Context, g ipld.NodeGetter) ipld.NodeGetter|创建session|
|Traverse(root ipld.Node, o Options) error|遍历节点|
|ApplyChange(ctx context.Context, ds ipld.DAGService, nd *dag.ProtoNode, cs []*Change) (*dag.ProtoNode, error)|应用操作|
|Diff(ctx context.Context, ds ipld.DAGService, a, b ipld.Node) ([]*Change, error)|比对变更|
|MergeDiffs(a, b []*Change) ([]*Change, []Conflict)|合并变更|
|DiffEnumerate(ctx context.Context, dserv ipld.NodeGetter, from, to cid.Cid) error|枚举比对变更|
|NewMemoryDagService() ipld.DAGService|新建内存DagService|
|NewDagEditor(root *dag.ProtoNode, source ipld.DAGService) *Editor|新建Dag编辑器|
|FetchGraph(ctx context.Context, root cid.Cid, serv ipld.DAGService) error|按深度获得节点，无限制|
  
## 定义接口
|接口|注释|
|:-----|:-----|
|Session(context.Context) ipld.NodeGetter|-|
  
## 定义类
#### ProtoNode 节点类
|名字|类型|注释|
|:-----|:-----|:-----|
|links|[]*ipld.Link|
|data|[]byte|
|encoded|[]byte|
|cached|cid.Cid|
|builder|cid.Builder|
|CidBuilder() cid.Builder|func|返回cid构建器|
|SetCidBuilder(builder cid.Builder)|func|设置cid构建器|
|AddNodeLink(name string, that ipld.Node) error|func|给节点添加链接|
|AddRawLink(name string, l *ipld.Link) error|func|给节点添加一个链接复制|
|RemoveNodeLink(name string) error|func|删除一个节点的链接|
|GetNodeLink(name string) (*ipld.Link, error)|func|根据链接返回节点|
|GetLinkedProtoNode(ctx context.Context, ds ipld.DAGService, name string) (*ProtoNode, error)|func|根据链接返回ProtoNode|
|GetLinkedNode(ctx context.Context, ds ipld.DAGService, name string) (ipld.Node, error)|func|根据链接返回IPLD节点|
|Copy() ipld.Node|func|复制节点|
|RawData() []byte|func|返回protobuf编码的节点|
|Data() []byte|func|返回节点数据|
|SetData(d []byte)|func|设置节点数据|
|UpdateNodeLink(name string, that *ProtoNode) (*ProtoNode, error)|func|更新节点的链接|
|Size() (uint64, error)|func|返回节点总大小，包括链接的大小|
|Stat() (*ipld.NodeStat, error)|func|返回节点的数据统计|
|Loggable() map[string]interface{}|func|ipfs/go-log.Loggable的实现|
|UnmarshalJSON(b []byte) error|func|从json解析ProtoNode|
|MarshalJSON() ([]byte, error)|func|ProtoNode转json|
|Cid() cid.Cid|func|返回节点的Cid|
|String() string|func|返回节点的Cid的string|
|Multihash() mh.Multihash|func|返回节点hash|
|Links() []*ipld.Link|func|返回节点的link集合|
|SetLinks(links []*ipld.Link)|func|设置节点的link集合|
|Resolve(path []string) (interface{}, []string, error)|func|解析link的别名|
|ResolveLink(path []string) (*ipld.Link, []string, error)|func|解析并返回链接|
|Tree(p string, depth int) []string|func|返回链接的名字集合|
|Marshal() ([]byte, error)|func|格式化protoNode|
|GetPBNode() *pb.PBNode|func|返回pb类型的节点|
|EncodeProtobuf(force bool) ([]byte, error)|func|序列化为protobuf|
|DecodeProtobuf(encoded []byte) (*ProtoNode, error)|func|反序列化为protobuf|
|DecodeProtobufBlock(b blocks.Block) (ipld.Node, error)|func|解析protobuf块|

#### LinkSlice link集合
|名字|类型|注释|
|:-----|:-----|:-----|
|Len() int|func|返回link集合长度|
|Swap(a, b int)|func|交换2个link|
|Less(a, b int) bool|func|a的名字是否比b的名字短|
  
#### ErrorService 实现自ipld.DAGService
|名字|类型|注释|
|:-----|:-----|:-----|
|Err|error|错误|
|Add(ctx context.Context, nd ipld.Node) error|func|返回错误|
|AddMany(ctx context.Context, nds []ipld.Node) error|func|返回错误|
|Get(ctx context.Context, c cid.Cid) (ipld.Node, error)|func|返回错误|
|GetMany(ctx context.Context, cids []cid.Cid) <-chan *ipld.NodeOption|func|返回错误|
|Remove(ctx context.Context, c cid.Cid) error|func|返回错误|
|RemoveMany(ctx context.Context, cids []cid.Cid) error|func|返回错误|
  
#### dagService IPFS Merkle DAG service
|名字|类型|注释|
|:-----|:-----|:-----|
|Blocks|bserv.BlockService|块集合|
|Add(ctx context.Context, nd ipld.Node) error|func|添加块节点|
|AddMany(ctx context.Context, nds []ipld.Node) error|func|一次性添加多个块节点|
|Get(ctx context.Context, c cid.Cid) (ipld.Node, error)|func|根据cid获得块节点|
|GetLinks(ctx context.Context, c cid.Cid) ([]*ipld.Link, error)|func|根据cid获得链接集合|
|Remove(ctx context.Context, c cid.Cid) error|func|删除cid指向的块节点|
|RemoveMany(ctx context.Context, cids []cid.Cid) error|func|删除多个cid志向的快捷键|
|GetMany(ctx context.Context, keys []cid.Cid) <-chan *ipld.NodeOption|func|返回多个cid的节点块|
  
#### sesGetter
|名字|类型|注释|
|:-----|:-----|:-----|
|bs|*bserv.Session|session|
|Get(ctx context.Context, c cid.Cid) (ipld.Node, error)|func|从DAG拿一个块节点|
|GetMany(ctx context.Context, keys []cid.Cid) <-chan *ipld.NodeOption|func|返回多个cid指向的节点|
|Session(ctx context.Context) ipld.NodeGetter|func|返回sesGetter|
  
#### walkOptions 路径遍历选项
|名字|类型|注释|
|:-----|:-----|:-----|
|SkipRoot|bool|是否跳过root节点|
|Concurrency|int|协程数量|
|ErrorHandler|func(c cid.Cid, err error) error|错误回调|
|addHandler(handler func(c cid.Cid, err error) error)|func|添加错误回调|
  
#### ProgressTracker 路径追踪器
|名字|类型|注释|
|:-----|:-----|:-----|
|Total|int|深度|
|lk|sync.Mutex|互斥锁|
|DeriveContext(ctx context.Context) context.Context|func|产生上下文|
|Increment()|func|自增|
|Value()|int|返回Total|
  
#### RawNode 只包含数据的节点
|名字|类型|注释|
|:-----|:-----|:-----|
|-|blocks.Block|继承自blocks.Block|
|Links() []*ipld.Link|func|返回空|
|ResolveLink(path []string) (*ipld.Link, []string, error)|func|返回空|
|Resolve(path []string) (interface{}, []string, error)|func|返回空|
|Tree(p string, depth int) []string|func|返回空|
|Copy() ipld.Node|func|复制一个节点|
|Size() (uint64, error)|func|返回节点数据大小|
|Stat() (*ipld.NodeStat, error)|func|返回节点统计信息|
|MarshalJSON() ([]byte, error)|func|序列化节点|
  
#### ComboService 混合服务
|名字|类型|注释|
|:-----|:-----|:-----|
|Read|ipld.NodeGetter|读|
|Write|ipld.DAGService|写|
|Add(ctx context.Context, nd ipld.Node) error|func|添加节点|
|AddMany(ctx context.Context, nds []ipld.Node) error|func|添加多个节点|
|Get(ctx context.Context, c cid.Cid) (ipld.Node, error)|func|获得节点|
|GetMany(ctx context.Context, cids []cid.Cid) <-chan *ipld.NodeOption|func|获得多个节点|
|Remove(ctx context.Context, c cid.Cid) error|func|删除节点|
|RemoveMany(ctx context.Context, cids []cid.Cid) error|func|删除多个节点|
  
#### Options 选项
|名字|类型|注释|
|:-----|:-----|:-----|
|DAG|ipld.NodeGetter|搜索路径|
|Order|Order|遍历方式|
|Func|Func|每步回调函数|
|ErrFunc|ErrFunc|错误回调函数|
|SkipDuplicates|bool是否跳过重复节点|
  
#### State 节点状态
|名字|类型|注释|
|:-----|:-----|:-----|
|Node|ipld.Node|当前节点|
|Depth|int|深度|
  
#### traversal 遍历
|名字|类型|注释|
|:-----|:-----|:-----|
|opts|Options|选项|
|seen|map[string]struct{}|存放遍历节点的内容|
|shouldSkip(n ipld.Node) (bool, error)|func|跳过|
|callFunc(next State) error|func|回调遍历，设置节点状态|
|getNode(link *ipld.Link) (ipld.Node, error)|func|返回链接对应的节点|
  
#### queue 节点信息队列
|名字|类型|注释|
|:-----|:-----|:-----|
|s|[]State|信息队列|
|enq(n State)|func|入队|
|deq() State|func|出队|
|len() int|func|返回队列长度|
  
#### Change 操作
|名字|类型|注释|
|:-----|:-----|:-----|
|Type|ChangeType|操作类型|
|Path|string|路径|
|Before|cid.Cid|前一个节点|
|After|cid.Cid|后一个节点|
|String() string|func|本次操作的string描述|
  
#### Conflict 冲突
|名字|类型|注释|
|:-----|:-----|:-----|
|A|*Change|a操作|
|B|*Change|b操作|
  
#### diffpair 比对pair
|名字|类型|注释|
|:-----|:-----|:-----|
|bef|cid.Cid|bef:前一个版本|
|aft|cid.Cid|aft:后一个版本|
  
#### Editor 编辑器
|名字|类型|注释|
|:-----|:-----|:-----|
|root|*dag.ProtoNode|root节点|
|tmp|ipld.DAGService|临时路径|
|src|ipld.DAGService|源路径|
|GetNode() *dag.ProtoNode|func|获得root节点的复制|
|GetDagService() ipld.DAGService|func|获得编辑器的临时DagService|
|InsertNodeAtPath(ctx context.Context, pth string, toinsert ipld.Node, create func() *dag.ProtoNode) error|func|根据路径插入节点|
|RmLink(ctx context.Context, pth string) error|func|删除链接|
|Finalize(ctx context.Context, ds ipld.DAGService) (*dag.ProtoNode, error)|func|固定路径和数据|