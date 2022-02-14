# Eos源码分析-datastream

[TOC]



## 摘要

eos的二进制流工具类,负责数据缓存，打/解包;



## 详情

* [datastream.hpp](https://github.com/hanjingo/eosio.cdt/blob/master/libraries/eosiolib/core/eosio/datastream.hpp)

### 重载运算符
```
<< 输入
>> 输出
```
### 定义类
|类型|名称|注释|
|:---|:---|:---|
|func|`datastream(T start, size_t s) : _start(start), _pos(start), _end(start+x){}`|?|
|func|`inline void skip(size_t s){_pos += s;}`|?|
|func|`inline bool read(char* d, size_t s)`|?|
|func|`inline bool write(const char* d, size_t s)`|?|
|func|`inline bool put(char c)`|?|
|func|`inline bool get(unsigned char& c){return get(*(char*)&c);}`|?|
|func|`inline bool get(char& c)`|?|
|func|`T pos() const {return _pos;} inline bool valid()const{ return _pos <= _end && _pos >= _start; }`|?|
|func|`inline bool seekp(size_t p){_pos = start+p; return _pos <= _end;}`|?|

TODO
