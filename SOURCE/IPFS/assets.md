# 摘要
1. 记录说明文档，加载文件；

# 详情
* [assets.go](https://github.com/hanjingo/go-ipfs/blob/master/assets/assets.go)
* [bindata.go](https://github.com/hanjingo/go-ipfs/blob/master/assets/bindata.go)
* [bindata_dep.go](https://github.com/hanjingo/go-ipfs/blob/master/assets/bindata_dep.go)
* [bindata_version_hash.go](https://github.com/hanjingo/go-ipfs/blob/master/assets/bindata_version_hash.go)

## 定义全局函数
|定义|注释|
|:---|:---|
|SeedInitDocs(nd *core.IpfsNode) (cid.Cid, error)|初始化文档|

## 定义全局变量
|定义|注释|
|:---|:---|
|BindataVersionHash = "c1aa0601ac3eac2c50b296cf618a6747eeba8579"|版本二进制数据hash|

## 定义结构体
#### asset 资产
|名称|类型|注释|
|:---|:---|:---|
|bytes|[]byte|二进制数据|
|info|os.FileInfo|文件信息|
  
#### bindataFileInfo 二进制文件信息
|名称|类型|注释|
|:---|:---|:---|
|name|string|文件名|
|size|int64|大小|
|mode|of.FileMode|文件格式|
|modTime|time.Time|修改时间|
