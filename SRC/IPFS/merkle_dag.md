# merkle_dag



merkle data（有向无环图），是ipfs在Merkle tree的基础上开发的一个数据结构；支持：内容寻址，防篡改，防重复等功能。



## 参考

- [IPFS - 内容寻址的版本化点对点文件系统(草稿3) 翻译](https://www.jianshu.com/p/24f989ec2aab)
- [IPFS协议层深入分析10---MerkleDAG](https://www.jianshu.com/p/26f2d5282552)



## 源码

- [go-merkledag](https://github.com/hanjingo/go-merkledag/tree/he)



## 结构定义

### 数据对象定义

```go
// ipfs对象
type IpfsObject struct {
	Links []ObjectLink  // 对象引用
	Data  string				// 数据
}

// ipfs对象引用
type ObjectLink struct {
	Name, Hash string // 对象名， hash
	Size       uint64			// 对象大喜
}
```

### 路径追踪器

```go
type ProgressTracker struct { // 进程追踪器，标识有多少个协程
	Total int 				// 协程数量
	lk    sync.Mutex // 互斥锁
}
```



## 内容寻址



## 防篡改



## 去重







## 遍历

### 遍历方式

- 串行遍历
- 并行遍历

