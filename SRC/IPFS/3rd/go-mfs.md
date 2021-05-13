# 摘要:
文件/目录的创建，链接和发布

# 详情:
[go-mfs](https:|github.com/ipfs/go-mfs)

## 定义类型
|名称|类型|注释|
|:---|:---|:---|
|PubFunc|func(context.Context, cid.Cid) error|发布函数|

## 定义全局函数
|函数|注释|
|:---|:---|
|func NewDirectory(ctx context.Context, name string, node ipld.Node, parent parent, dserv ipld.DAGService) (*Directory, error)|新建目录(上下文，目录名，节点，父类, dagservice)（目录，err）|
|func NewFile(name string, node ipld.Node, parent Parent, dserv ipld.DAGService)(*File, error)|新建文件(文件名， 节点， 父类， DAGService)（文件, err）|
|func Mv(r *Root, src, dst string) error|将src移动到dst，如果dst下已存在src文件，取消已有文件的链接，如果已存在src目录，就放到src目录的子目录,即 /dst/src/src|
|func PutNode(r *Root, path string, nd ipld.Node) error|放置节点|
|func Mkdir(r *Root, pth string, opts MkdirOpts) error|创建目录(root目录节点, 路径, 创建选项)|
|func Lookup(r *Root, path string) (FSNode, error)|遍历目录/文件，返回节点|
|func DirLookup(d *Directory, pth string) (FSNode, error)|遍历目录，返回节点|
|func FlushPath(ctx context.Context, rt *Root, pth string) (ipld.Node, error)|刷入目录/文件|
|func NewRepublisher(ctx context.Context, pf PubFunc, tshort, tlong time.Duration) *Republisher|new一个发布器|

## 定义接口
### FSNode 节点
|接口|注释|
|:---|:---|
|GetNode()(ipld.Node, error)|拿节点|
|Flush() error|刷入磁盘|
|Type() NodeType|类型|

### parent 父类
|接口|注释|
|:---|:---|
|updateChildEntry(c child) error|更新子类|

### DAGService
|接口|注释|
|:---|:---|
|NodeGetter|
|NodeAdder|
|Remove(context.Context, cid.Cid) error|
|RemoveMany(context.Context, []cid.Cid) error|

### FileDescriptor 文件描述器
|接口|注释|
|:---|:---|
|io.Reader|读入器|
|CtxReadFull(context.Context, []byte) (int, error)|全部读|
|io.Writer|写入器|
|io.WriterAt|全写入|
|io.Closer|读写关闭器|
|io.Seeker|索引器|
|Truncate(int64) error|截断|
|Size() (int64, error)|尺寸|
|Flush() error|刷入|

## 定义类
### child 子类
|名字|类型|注释|
|:---|:---|:---|
|Name|string|子类名|
|Node|ipld.Node|子类节点|

### Directory 目录
|名字|类型|注释|
|:---|:---|:---|
|inode|
|entriesCache|map[string]FSNode|缓存
|lock|sync.Mutex|原子锁|
|ctx|context.Context|上下文|
|unixfsDir|uio.Directory|
|modTime|time.Time|修改时间|
|GetCidBuilder() cid.Builder|func|获得自描述地址构建器|
|SetCidBuilder(b cid.Builder)|func|设置自描述地址构建器|
|Child(name string) (FSNode, error)|func|返回缓存的子(目录/文件)节点|
|Uncache(name string)|func|取消对name的缓存|
|ListNames(ctx context.Context)([]string, error)|func|返回名称列表|
|List(ctx context.Context) ([]NodeListing, error)|func|返回节点列表|
|ForEachEntry(ctx context.Context, f func(NodeListing) error) error|func|遍历缓存|
|Mkdir(name string) (*Directory, error)|func|创建目录（不存在就创建，已存在就返回,name是文件就返回nil）|
|Unlink(name string) error|func|取消链接|
|Flush() error|func|刷入|
|AddChild(name string, nd ipld.Node) error|func|添加子节点|
|Path() string|func|路径|
|GetNode() (ipld.Node, error)|func|以复制的方式拿一个节点|

### NodeListing 节点列表条目
|名字|类型|注释|
|:---|:---|:---|
|Name|string|名字|
|Type|int|类型|
|Size|int64|大小|
|Hash|string|hash|

### File 文件
|名字|类型|注释|
|:---|:---|:---|
|inode|-|继承自节点
|desclock|sync.RWMutex|读写锁
|node|ipld.Node|根节点
|nodeLock|sync.RWMutex|节点读写锁
|RawLeaves|bool|?|
|Open(flags Flags) (_ FileDescriptor, _retErr error)|func|打开文件,返回文件描述 flags:读写标记|
|func (fi *File) Size() (int64, error)|func|返回文件尺寸(单位:)|
|func (fi *File) GetNode() (ipld.Node, error)|func|拿文件节点|
|func (fi *File) Flush() error|func|刷入数据|
|func (fi *File) Sync() error|func|同步（此处没做处理）|
|func (fi *File) Type() NodeType|func|返回|

### MkdirOpts 创建目录选项
|名字|类型|注释|
|:---|:---|:---|
|Mkparents|bool|是否创建父目录|
|Flush|bool|是否刷入|
|CidBuilder|cid.Builder|cid构建器|

### Flags 标记
|名字|类型|注释|
|:---|:---|:---|
|Read|bool|读|
|Write|bool|写|
|Sync|bool|同步|

### Republisher 发布器
|名字|类型|注释|
|:---|:---|:---|
|TimeoutLong|time.Duration|长超时|
|TimeoutShort|time.Duration|短超时|
|RetryTimeout|time.Duration|重试超时|
|pubfunc|PubFunc|发布函数|
|update|chan cid.Cid|待更新的cid管道,容量1|
|immediatePublish|chan chan struct{}|需要立即发布的管道，无容量|
|ctx|context.Context|上下文|
|cancel|func()|取消函数|