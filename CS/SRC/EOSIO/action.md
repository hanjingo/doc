# 摘要
负责action的收发，鉴权



# 详情

* [action.hpp](https://github.com/hanjingo/eosio.cdt/blob/master/libraries/eosiolib/contracts/eosio/action.hpp)

## 知识点
1. std:tie: 1.用于解构std::tuple中的元素，2.用来将多个变量构造成std::tuple;
2. std::tuple: 元组,使用它可以把多个不同类型的变量组合成一个对象;

## action数据拆包
默认包缓冲区尺寸:512byte,如果超过就malloc;具体的拆包代码在datastream.hpp里;

## 定义导出c函数
|定义|注释|
|:---|:---|
|uint32_t read_action_data( void* msg, uint32_t len )|读action数据,具体看eos的wasm_interface.cpp|
|uint32_t action_data_size()|获得action数据尺寸,具体看eos的wasm_interface.cpp|
|void require_recepient( uint64_t name )|设置需要被通知的账号|
|void require_auth( uint64_t name )|验证权限|
|void require_auth2( uint64_t name, uint64_t permission )|验证权限v2|
|bool is_account( uint64_T name )|是否是一个账号|
|void send_inline( char* serialized_action, size_t size )|?|
|void send_context_free_inline( char* serialized_action, size_t size )|?|
|uint64_t publication_time()|?|
|uint64_t current_receiver()|?|

## 定义类
#### permission_level 权限等级
|类型|名称|注释|
|:---|:---|:---|
|func|permission_level( name a, name p ) : actor(a), permission(p){}|构造函数|
|func|permission_level(){}|构造函数|
|name|actor|权限拥有者|
|name|permission|权限名|
|-|==|判断是否相等|
|-|<|判断是否小于|

#### action_wrapper action封装类
|类型|名称|注释|
|:---|:---|:---|
|static constexpr eosio::name|action_name = eosio::name(Name)|action名字|
|eosio::name|code_name|调用的函数名字|
|std::vector< eosio::premission_level >|permissions|权限|
|func|template<typename... Args> action to_action(Args&&... args)const|转action|
|func|template<typename... Args> void send(Args&&... args)const|发送|
|func|template<typename... Args> void send_context_free(Args&&... args)const|?|
