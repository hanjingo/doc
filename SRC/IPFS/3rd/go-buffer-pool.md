# 摘要

# 详情 
## 定义类型
|名称|类型|注释|
|:--|:--|:--|

## 定义全局变量 
|名称|类型|注释|
|:--|:--|:--|
|GlobalPool|*BufferPool|全局缓冲池|
|MaxLength|math.MaxInt32|能加到缓冲池的最大容量；40亿左右|

## 定义全局函数
|函数|注释|
|:--|:--|
|NewBuffer(buf []byte) *Buffer|根据二进制数组新建缓冲区|
|NewBufferString(buf string) *Buffer|根据string新建缓冲区|

## 定义接口
### 接口名
|接口|注释|
|:--|:--|

## 定义类
### Buffer 缓冲区
|名字|类型|注释|
|:--|:--|:--|
|Pool|*BufferPol|缓冲池|
|buf|[]byte|数据区|
|rOff|int|?|
|bootstrap|[64]byte|
|grow(n int) int|func|扩容:2*数据长度+n; 返回扩容/缩小之后的容量|
|getPool() *BufferPool|func|返回缓冲区的缓冲池；如果不存在则返回全局缓冲池GlobalPool|
|returnBuf()|func|返回缓冲池的数据区|

### bufp
|名字|类型|注释|
|:--|:--|:--|
|buf|[]byte|-|

### BufferPool 缓冲池
|名字|类型|注释|
|:--|:--|:--|
|pools|[32]sync.Pool|备用池；包括32个Pool类|
|ptrs|sync.Pool|当前池|