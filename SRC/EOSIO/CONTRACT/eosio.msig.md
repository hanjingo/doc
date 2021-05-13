# 摘要
用于多签，用户管理

# 详情
## 定义action
|接口|参数|注释|
|:---|:---|:---|
|propose|`ignore<name>` 提名人<br>`ignore<name>` 被提名名字<br>`ignore<std::vector<permission_level>>` 权限等级<br>`ignore<transaction>` 传输块|提名|
|approve|name proposer<br>name proposal_name<br>permission_level level<br>`const eosio::bnary_extension<eosio::checksum256>&` proposal_hash|批准|
|unapprove|name proposer<br>name proposal_name<br>permission_level level|不批准|
|cancel|name proposer<br>name proposal_name<br>nmae canceler|取消|
|exec|name proposer<br>name proposal_name<br>name executer|执行提名|
|invalidate|name account|让账号失效|

## 定义表
#### proposal
|类型|名称|注释|
|:---|:---|:---|
|name|proposal_name|?|
|std::vector<char>|packed_transaction|?|

#### old_approvals_info 
|类型|名称|注释|
|:---|:---|:---|
|name|proposal_name|?|
|std::vector<permission_level>|requested_approvals|?|
|std::vector<permission_level>|provided_approvals|?|

#### approval 
|类型|名称|注释|
|:---|:---|:---|
|permission_level|level|
|time_point|time|

#### approvals_info
|类型|名称|注释|
|:---|:---|:---|
|uint8_t|version=1|?|
|name|proposal_name|?|
|std::vector<approval>|requested_approvals|?|
|std::vector<approval>|provided_approvals|?|

#### invalidation 
|类型|名称|注释|
|:---|:---|:---|
|name|account|?|
|time_point|last_invalidation_time|?|
