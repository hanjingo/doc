# 摘要

一个自描述地址项目

# 详情
[go-cid](https://github.com/ipfs/go-cid)
## 定义全局变量
|名称|类型|注释|
|:-----|:------|:-----|
|Raw|"raw"|0x55, 滚动|
|DagProtobuf|"protobuf"|0x70, dag协议|
|DagCBOR|"cbor"|0x71|
|Libp2pKey|"libp2p-key"|0x72|
|GitRaw|"git-raw"|0x78|
|EthBlock|"eth-block"|0x90, 以太坊块|
|EthBlockList|"eth-block-list"|0x9, 以太坊块列表|
|EthTxTrie|"eth-tx-trie"|0x92|
|EthTx|"eth-tx"|0x93|
|EthTxReceiptTrie|"eth-tx-receipt-trie"|0x94|
|EthTxReceipt|"eth-tx-receipt"|0x95|
|EthStateTrie|"eth-state-trie"|0x96|
|EthAccountSnapshot|"eth-account-snapshot"|0x97|
|EthStorageTrie|"eth-storage-trie"|0x98|
|BitcoinBlock|"bitcoin-block"|0xb0|
|BitcoinTx|"bitcoin-tx"|0xb1|
|ZcashBlock|"zcash-block"|0xc0|
|ZcashTx|"zcash-tx"|0xc1|
|DecredBlock|"decred-block"|0xe0|
|DecredTx|"decred-tx"|0xe1|
|DashBlock|"dash-block"|0xf0|
|DashTx|"dash-tx"|0xf1|
|FilCommitmentUnsealed|"fil-commitment-unsealed"|0xf101|
|FilCommitmentSealed|"fil-commitment-sealed"|0xf102|
  
## 定义全局函数
|函数|注释|
|:-----|:-----|
|Fuzz(data []byte) int|测试cid的相关转换函数是否有效|
|NewCidV0(mhash mh.Multihash) Cid|新建一个cid包裹的multihash(推荐优先使用NewCidV1)|
|NewCidV1(codecType uint64, mhash mh.Multihash) Cid|新建一个cid包裹的multihash|
|Parse(v interface{}) (Cid, error)|将对象解析成cid|
|Decode(v string) (Cid, error)|str解码成Cid|
|ExtractEncoding(v string) (mbase.Encoding, error)|提取编码器|
|Cast(data []byte) (Cid, error)|byte数组转cid (数据格式:版本 编码器类型 multihash)|
|PrefixFromBytes(buf []byte) (Prefix, error)|二进制数组转前缀|
|CidFromBytes(data []byte) (int, Cid, error)|二进制数组转cid|
|NewPrefixV0(mhType uint64) Prefix|new一个v0版本的前缀|
|NewPrefixV1(codecType uint64, mhType uint64) Prefix|new一个v1版本的前缀|
  
## 定义接口
#### Builder 构造器
|接口|注释|
|:-----|:-----|
|Sum(data []byte)(Cid, error)|?|
|GetCodec() uint64|?|
|WithCodec(uint64) Builder|?|
  
## 定义类
#### V0Builder v0版本构建器
|名字|类型|注释|
|:-----|:-----|:------|
|Sum(data []byte)(Cid, error)|?|
|GetCodec() uint64|？|
|WithCodec(c uint64) Builder|？|
  
#### V1Builder v1版本构建器
|名字|类型|注释|
|:-----|:-----|:------|
|Codec|uint64|？|
|MhType|uint64|？|
|MhLength|int|？|
|Sum(data []byte) (Cid, error)|func|?|
|GetCodec() uint64|func|?|
|WithCodec(c uint64) Builder|func|?|
  
#### Prefix 前缀
|名字|类型|注释|
|:-----|:-----|:------|
|Version|uint64|版本|
|Codec|uint64|编解码器|
|MhType|uint64|multihash版本|
|MhLength|int|multihash长|
|Sum(data []byte) (Cid, error)|func|与二进制数组求和并返回一个cid|
|Bytes() []byte|func|返回前缀的二进制数组|
|GetCodec() uint64|func|?|
|WithCodec(c uint64) Builder|func|?|
  
#### Cid 自描述地址
|名字|类型|注释|
|:-----|:-----|:------|
|str|string|地址内容|
|Defined() bool|func|是否已被定义|
|UnmarshalBinary(data []byte) error|func|解析二进制数组|
|UnmarshalText(text []byte) error|func|解析文本|
|Version() uint64|func|返回cid版本 0或1|
|Type() uint64|func|返回cid类型|
|String() string|func|返回 版本0：b58str 版本1:b32str|
|StringOfBase(base mbase.Encoding) (string, error)|func|返回str的进制|
|Encode(base mbase.Encoder) string|func|cid编码成str|
|Hash() mh.Multihash|func|返回cid的hash|
|Bytes() []byte|func|返回cid的二进制数据|
|ByteLen() int|func|返回cid的二进制数据长度|
|WriteBytes(w io.Writer) (int, error)|func|写入二进制数据|
|MarshalBinary() ([]byte, error)|func|格式化二进制|
|MarshalText() ([]byte, error)|func|格式化文本|
|Equals(o Cid) bool|func|判断2个cid是否相等|
|UnmarshalJSON(b []byte) error|func|反格式化json转为cid|
|MarshalJSON() ([]byte, error)|func|格式化json|
|KeyString() string|func|返回string类型的cid内容|
|Loggable() map[string]interface{}|func|导出map["cid"]cid 这种格式|
|Prefix() Prefix|func|返回前缀|
