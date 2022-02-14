# Eos源码分析-contract

[TOC]



## 摘要

获得合约的名字，部署者等;



## 详情

* [contract.hpp](https://github.com/hanjingo/eosio.cdt/blob/master/libraries/eosiolib/contracts/eosio/contract.hpp)

### 知识点

- `deprecated` 主要用于标记过时的函数、接口、类等;

### 定义类
#### contract
|类别|名称|注释|
|:---|:---|:---|
|name|`_self`|合约部署者名字|
|name|`_first_receiver`|合约部署者|
|`datastream<const char*>`|`_ds`|数据流处理器|
|func|`contract( name self, name first_receiver, datastream<const char*> ds ):_self(self),_first_receiver(first_receiver), _ds(ds){}`|new一个合约|
|func|`inline name get_self()const{ return _self; }`|返回合约名字|
|func|`inline name get_code()const { return _first_receiver; }`|返回合约部署者|
|func|`inline get_first_receiver()const{ return _first_receiver; }`|返回合约部署者|
|func|`inline datastream<const char*>&get_datastream() { return _ds; }`|返回数据流处理器|
|func|`inline const datastream<const char*>& get_datastream()const { return _ds; }`|返回数据流处理器|

