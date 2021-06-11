# ipfs block

## 块定义

定义了块的接口和基本类：

```go
// 定义块接口
type Block interface {
	RawData() []byte
	Cid() cid.Cid
	String() string
	Loggable() map[string]interface{}
}

// 定义了基本块
type BasicBlock struct {
	cid cid.Cid
	data []byte
}
```

## Node定义

```go

```
