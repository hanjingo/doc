# 摘要
功能:1.检测、设置指定账户的权限；2.限制指定账户或全局的资源使用；3.设置区块生产者
类似超级管理员;

# 详情
## 定义action
|接口|参数|注释|
|:---|:---|:---|
|newaccount|name 创建者<br>name 账号名<br>ignore<authority> owner权限<br>ignore<authority> active权限|新建账号,强制资源限制;1.12个字符长，不能包含`"."`;2.新账号创建时需要一点点token;|
|updateauth|ignore<name> 账号<br>ignore<name> 权限<br>ignore<name> 父账号<br>ignore<authority> 权限|更新权限|
|deleteauth|ignore<name> 账号<br>ignore<name> 权限|删除权限|
|linkauth|ignore<name> 账号<br>ignore<name> 合约部署者 <br>ignore<name> 需要赋权的action<br>ignore<name> 权限|赋予权限，给action签名;对以下系统action:updateauth, deleteauth, linkauth, unlinkauth, canceldelay无效;用来做权限验证很方便,如果不赋予权限，默认eosio.any|
|unlinkauth|ignore<name> 账号<br>ignore<name> 合约部署者<br>ignore<name> 合约|取消赋权|
|canceldelay|ignore<permission_level> 权限<br>ignore<checksum256> 传输id|取消一个延时传输|
|**setcode**|name 合约部署者<br>uint8_t vm类型<br>uint8_t vm版本<br>`const std::vector<char>&` 合约|设置合约|
|**setabi**|name 账号<br>`const std::vector<char>&` abi|设置abi|
|onerror|`ignore<uint128_t>` 发送者<br>`ignore<std::vector<char>>` 报错的传输|错误回调|
|setpriv|name 账号<br>uint8_t 是否开启特权|设置特权，0不开，>0开启|
|setalimits|name 账号<br>int64_t 内存字节大小<br>int64_t 网络<br>int64_t cpu|设置资源限制|
|setprods|`const std::vector<eosio::producer_authority>& ` 权限集合|设置节点|
|setparams|`const eosio::blockchain_parameters&` 参数|设置系统参数|
|reqauth|name 验证者|权限验证，reqauth2不能用了|
|activate|`const eosio::checksum256&` 协议|激活协议|
|reqactivated|`const eosio::checksum256&` 协议|判断协议是否激活|
