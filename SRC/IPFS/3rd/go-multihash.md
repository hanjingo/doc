# 摘要

# 详情
## 定义全局变量
#### 错误表
|错误|注释|
|:-----|:-----|
|ErrUnknownCode|errors.New("unknown multihash code")|
|ErrTooShort|errors.New("multihash too short. must be >= 2 bytes")|
|ErrTooLong|errors.New("multihash too long. must be < 129 bytes")|
|ErrLenNotSupported|errors.New("multihash does not yet support digests longer than 127 bytes")|
|ErrInvalidMultihash|errors.New("input isn't valid multihash")|
|ErrVarintBufferShort|errors.New("uvarint: buffer too small")|
|ErrVarintTooLong|errors.New("uvarint: varint too big (max 64bit)")|
  
#### 算法类型
|算法|值|
|:-----|:----|
|IDENTITY|0x00, 长度:-1|
|ID|IDENTITY|
|SHA1|0x11, 长度:20|
|SHA2_256  |0x12, 长度:32|
|SHA2_512  |0x13, 长度:64|
|SHA3_224  |0x17, 长度:28|
|SHA3_256  |0x16, 长度:32|
|SHA3_384  |0x15, 长度:48|
|SHA3_512  |0x14, 长度:64|
|SHA3      |SHA3_512|
|KECCAK_224|0x1A|
|KECCAK_256|0x1B|
|KECCAK_384|0x1C|
|KECCAK_512|0x1D|
|SHAKE_128|0x18|
|SHAKE_256|0x19|
|BLAKE2B_MIN|0xb201|
|BLAKE2B_MAX|0xb240|
|BLAKE2S_MIN|0xb241|
|BLAKE2S_MAX|0xb260|
|MD5|0xd5, 长度:16|
|DBL_SHA2_256|0x56|
|MURMUR3_128|0x22|
|MURMUR3|MURMUR3_128|
|SHA2_256_TRUNC254_PADDED |0x1012|
|X11|0x1100|
|POSEIDON_BLS12_381_A1_FC1|0xb401|
  
## 定义全局函数
|函数|注释|
|:-----|:-----|
|NewReader(r io.Reader) Reader|新建mh阅读器|
|NewWriter(w io.Writer) Writer|新建mh写入器|
  
## 定义接口
#### Reader multihash读取器
|接口|注释|
|:-----|:-----|
|io.Reader|读取器|
|ReadMultihash() (Multihash, error)|读mh|
  
#### Writer multihash写入器
|接口|注释|
|:-----|:-----|
|io.Writer|写入器|
|WriteMultihash(Multihash) error|写入mh|
  
## 定义类
#### DecodedMultihash 
|名字|类型|注释|
|:-----|:-----|:------|
|Code|uint64|hash算法编号|
|Name|string|hash算法名字|
|Length|int|摘要长度|
|Digest|[]byte|摘要内容|
  
#### Multihash []byte
|名字|类型|注释|
|:-----|:-----|:------|
|Multihash|[]byte|hash算法编号+hash摘要长度+摘要|
  