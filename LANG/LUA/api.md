[TOC]

# LUA API



## core

### load

`load(chunk [, chunkname [, mode [, env]]])`

- `chunk` 函数或字符串
- `chunkname` 代码块名字
- `mode` 加载模式
  - `"t"` 文本样式
  - `"b"` 二进制样式
  - `"bt"` 二进制和文本模式
- `env` 代码块需要的参数

加载一个数据块，从字符串或者函数中加载一个代码块作为方法并返回；



### lua_rawgetp

`lua_rawgetp(lua_State *L, int index, const void *p);`

- `L` lua虚拟机
- `index` table的位置
- `p` 
- 返回值

### lua_gettop

TODO



## debug

###getinfo

`debug.getinfo`

TODO

### getlocal

`debug.getlocal`

TODO

### setlocal

TODO

### setupvalue

TODO





