# 摘要
eos货币机制  
提供发币,转账等功能
# 详情
[eosio.token.hpp](https://github.com/EOSIO/eosio.contracts/blob/master/contracts/eosio.token/include/eosio.token/eosio.token.hpp)  
[eosio.token.cpp](https://github.com/EOSIO/eosio.contracts/blob/master/contracts/eosio.token/src/eosio.token.cpp)
## 定义action
|接口|参数|说明|
|:-----|:------|:----|
|create|const name& issuer 发币人, const asset& maximum_supply 最大供应量|发币|
|issue|const name& to 收款人, const asset& quantity 数量, const string&memo 留言|分配创建的币|
|retire|const asset& quantity 废掉的币, const string& memo 留言|废掉一部分币|
|transfer|const name& from 转账人, const name& to 收款人, const asset& quantity 币数量, const string& memo 留言|转账|
|open|const name& owner, const symbol& symbol, const name& ram_payer|?|
|close|const name& owner, const symbol& symbol|?|
  
## 定义函数
|接口|参数|说明|
|:-----|:------|:----|
|get_supply|const name& token_contract_account 合约部署者, const symbol_code& sym_code 币类型|获得货币的供应量|
|get_balance|const name& token_contract_account 合约部署者, const name& owner 要查询的人, const symbol_code& sym_code 币类型|获得币的数额|
  
## 定义表
#### account 余额表
|类型|名字|注释|
|:-----|:------|:----|
|asset|balance|余额|
|func|uint64_t primary_key()const { return balance.symbol.code().raw(); }|主键|
  
#### currency_stats 货币表
|类型|名字|注释|
|:-----|:------|:----|
|asset|supply|货币供应量|
|asset|max_supply|货币最大供应量|
|name|issuer|发币人|
|func|uint64_t primary_key()const { return supply.symbol.code().raw(); }|主键， 币类型|
