# 摘要
1. 块的删除和过滤

# 详情
* [remove.go](https://github.com/hanjingo/go-ipfs/blob/master/blocks/blockstoreutil/remove.go)

## 知识点
omitempty:表示这条信息如果没有提供，在序列化成 json 的时候就不要包含其默认值

## 定义全局函数
|定义|注释|
|:---|:---|
|RmBlocks(ctx context.Context, blocks bs.GCBlockstore, pins pin.Pinner, cids []cid.Cid, opts RmBlocksOpts) (<-chan interface{}, error)|删除块; ctx: 上下文, blocks: 块集合; pins: 固定器; cids: cid入参; opts: 选项|
|FilterPinned(ctx context.Context, pins pin.Pinner, out chan<- interface{}, cids []cid.Cid) []cid.Cid|过滤已固定的cid; ctx: 上下文, pinds: 固定器, out: 已删除块的管道, cids: cid集合, 返回: 过滤后的cid|
|ProcRmOutput(next func() (interface{}, error), sout io.Writer, serr io.Writer) error|便利函数是否返回错误; next: 遍历函数, sout: 用来返回删除的buffer, serr:用来返回未删除的buffer|

## 定义结构体
#### RemoveBlock 已经被删除的块
|名称|类型|注释|
|:---|:---|:---|
|Hash|string `json:",omitempty"`|hash|
|Error|string `json:",omitempty"`|错误|
  
#### RmBlocksOpts 删除块选项
|名称|类型|注释|
|:---|:---|:---|
|Prefix|string|前缀|
|Quiet|bool|是否静默|
|Force|bool|是否强制删除|
