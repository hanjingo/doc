# 摘要
eos货币机制
提供发币,转账等功能

# 详情
[eosio.token.hpp](https://github.com/EOSIO/eosio.contracts/blob/master/contracts/eosio.token/include/eosio.token/eosio.token.hpp)
[eosio.token.cpp](https://github.com/EOSIO/eosio.contracts/blob/master/contracts/eosio.token/src/eosio.token.cpp)

## 定义action
|接口|参数|说明|
|:-----|:------|:----|
|create|- `const name&` 发币人<br>- `const asset&` 最大供应量|发币|
|issue|- `const name&` 收款人<br>- `const asset&` 数量<br>- `const string&` 留言|分配创建的币|
|retire|- `const asset&` 废掉的币<br>- `const string&` 留言|废掉一部分币|
|transfer|- `const name&` 转账人<br>- `const name&` 收款人<br>- `const asset&` 币数量<br>- `const string&` 留言|转账|
|open|- `const name&` owner<br>- `const symbol&` symbol<br>- `const name&` ram_payer|?|
|close|- `const name&` owner<br>- `const symbol&` symbol|?|

## 定义函数
|接口|参数|说明|
|:-----|:------|:----|
|get_supply|- `const name&` 合约部署者<br>- `const symbol_code&` 币类型|获得货币的供应量|
|get_balance|- `const name&` 合约部署者<br>- `const name&` 要查询的人<br>- `const symbol_code&` 币类型|获得币的数额|

## 定义表
#### account 余额表(accounts)
|类型|名字|注释|
|:-----|:------|:----|
|asset|`balance`|余额|
|func|`uint64_t primary_key()const { return balance.symbol.code().raw(); }`|主键|

#### currency_stats 货币表(stat)
|类型|名字|注释|
|:-----|:------|:----|
|asset|supply|货币供应量|
|asset|max_supply|货币最大供应量|
|name|issuer|发币人|
|func|`uint64_t primary_key()const { return supply.symbol.code().raw(); }`|主键， 币类型|
