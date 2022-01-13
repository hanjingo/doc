# 详情
[history_api_plugin.hpp](https://github.com/hanjingo/eos/blob/master/plugins/history_api_plugin/include/eosio/history_api_plugin/history_api_plugin.hpp) 
[history_api_plugin.cpp](https://github.com/hanjingo/eos/blob/master/plugins/history_api_plugin/history_api_plugin.cpp)  

## 定义全局函数
CALL(api_name, api_handle, api_namespace, call_name) 
在插件启动时注册了以下几个api：  

* get_actions
* get_transaction
* get_key_accounts
* get_controlled_accounts
内容很简单，不再赘述;
