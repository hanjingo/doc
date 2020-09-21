# 摘要
生产者调度

# 详情
[producer_schedule.hpp]()

## 定义类
#### producer_key 生产者key
|类别|名称|注释|
|:---|:---|:---|
|name|producer_name|?|
|func|friend constexpr bool operator < ( const producer_key& a, const producer_key& b ){ return a.producer_name < b.producer_name; }|比较名字|

#### producer_schedule 生产者调度器
|类别|名称|注释|
|:---|:---|:---|
|uint32_t|version|版本|
|std::vector< producer_key >|producers|生产者集合|

#### key_weight 密钥权重
|类别|名称|注释|
|:---|:---|:---|
|public_key|key|公钥|
|uint16_t|weight|权重|

#### block_signing_authority_v0 块签名验证版本0
|类别|名称|注释|
|:---|:---|:---|
|uint32_t|threshold|起点|
|std::vector< key_weight >|keys|密钥集合|
|func|bool is_valid() const|验证是否有效|

#### producer_authority
|类别|名称|注释|
|:---|:---|:---|
|name|producer_name|?|
|block_signing_authority|authority|?|
|friend constexpr bool operator < ( const producer_authority& a, const producer_authority& b ){ return a.producer_name < b.producer_name; }|

