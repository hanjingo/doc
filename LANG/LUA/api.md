# LUA API

[TOC]

## Lua库

### 基础库

#### assert

`assert(v[, message])`

- `v` 需要断言的语句
- `message` 输出yu ju

断言语句

#### collectgrabage

`collectgarbage([opt [, arg]])`

- `opt` 选项
  - `collect` 做一次完整的垃圾收集循环（默认）；
  - `stop` 停止垃圾收集器的运行，在调用重启前，收集器只会因显式的调用运行；
  - `restart` 重启垃圾收集器的自动运行；
  - `count` 以K字节数为单位返回Lua使用的总内存数；
  - `step` 单步运行垃圾收集器，步长由arg定义；结束一个循环返回true；
  - `setpause` 将arg设置为收集器的间歇率，返回间歇率的前一个值；
  - `setstepmul` 将arg设置为收集器的步进倍率，返回步进倍率的前一个值；
  - `isrunning` 返回收集器是否在工作。
- `arg` 参数

启动垃圾收集

#### ipairs

`ipairs (t)`

- `t` table

返回key，value

#### pairs

`pairs (t)`

- `t` table

迭代table，如果 `t` 有元方法 `__pairs`， 以 `t` 为参数调用它

#### tonumber

`tonumber (e [, base])`

- `e` 字符串
- `base` 要转换的进制

把参数转换为一个数字

#### tostring

`tostring (v)`

- `v` 值

转为字符串（`如果实现有"__tostring"，调用"__string"`）

#### type

`type(v)`

- `v` 值

将参数的类型编码为一个字符串返回

#### select

`select (index, ...)`

- `index` 起始位置（可负，负数表示从后向前索引，正数表示从前向后索引；当`index=#`时，select返回参数的个数）

返回可变长参数的区间`[index, #...]`中的参数

### 协程库

TODO

### 包管理库

TODO

### 字符串控制

#### string.format

`string.format(formatstring, ...)`

- `formatstring` 字符串格式

格式化字符串，以下为转义码：

| 转义码   | 说明                                                       |
| -------- | ---------------------------------------------------------- |
| `%c`     | 接受一个数字, 并将其转化为ASCII码表中对应的字符            |
| `%d, %i` | 接受一个数字并将其转化为有符号的整数格式                   |
| `%o`     | 接受一个数字并将其转化为八进制数格式                       |
| `%u`     | 接受一个数字并将其转化为无符号整数格式                     |
| `%x`     | 接受一个数字并将其转化为十六进制数格式, 使用小写字母       |
| `%X`     | 接受一个数字并将其转化为十六进制数格式, 使用大写字母       |
| `%e`     | 接受一个数字并将其转化为科学记数法格式, 使用小写字母e      |
| `%E`     | 接受一个数字并将其转化为科学记数法格式, 使用大写字母E      |
| `%f`     | 接受一个数字并将其转化为浮点数格式                         |
| `%g(%G)` | 接受一个数字并将其转化为%e(%E, 对应%G)及%f中较短的一种格式 |
| `%q`     | 接受一个字符串并将其转化为可安全被Lua编译器读入的格式      |
| `%s`     | 接受一个字符串并按照给定的参数格式化该字符串               |

%后面还可以添加如下参数（按顺序读入）：

1. 符号

   一个+号表示其后的数字转义符将让正数显示正号. 默认情况下只有负数显示符号.

2. 占位符

    一个0, 在后面指定了字串宽度时占位用. 不填时的默认占位符是空格.

3. 对齐标识

   在指定了字串宽度时, 默认为右对齐, 增加-号可以改为左对齐.

4. 宽度数值

5. 小数位数/字符裁切

   在宽度数值后增加的小数部分n, 若后接f(浮点数转义符, 如%6.3f)则设定该浮点数的小数只保留n位, 若后接s(字符串转义符, 如%5.3s)则设定该字符串只显示前n位.

#### string.sub

`string.sub (s, i [, j])`

- `s` 字符串
- `i` 开始位置（可负）
- `j` 结束位置（可负）

返回s的子字符串`s[i, j]`

#### string.len

`string.len (s)`

- `s` 字符串

返回字符串长度（'\0'也算一位）

### 基础UTF-8支持

TODO

### 表控制

#### table.unpack

`table.unpack (list [, i [, j]])`

- `list` lua table
- `i` 起始位置（默认 1）
- `j` 结束位置（默认 #list）

返回列表中的元素，等价于`return list[i], ..., list[j]`

#### table.pack

`table.pack (···)`

返回用所有参数以键 1,2, 等填充的新表， 并将 "`n`" 这个域设为参数的总数。

### 数学函数

TODO

### 输入输出

TODO

### 操作系统库

TODO

### 调试库

TODO

---

## C库

#### luaL_openlibs

`LUALIB_API void luaL_openlibs (lua_State *L)`

打开指定状态机中的所有 Lua 标准库（要使用标准库，需先调用它）

#### luaL_requiref

`LUALIB_API void luaL_requiref (lua_State *L, const char *modname, lua_CFunction openf, int glb)`

- `L` 栈
- `modname` 模块名
- `openf` 自定义模块打开函数
- `glb` 是否要将模块设置到全局变量里并在栈上留下模块的副本（1：是）

require的简化版实现，如果modname不在package.loaded中，调用openf打开模块

#### luaL_newlib

`#define luaL_newlib(L,l) (luaL_checkversion(L), luaL_newlibtable(L,l), luaL_setfuncs(L,l,0))`

创建一张新的表，并把数组l中的函数注册进去

#### luaL_newlibtable

`#define luaL_newlibtable(L,l) lua_createtable(L, 0, sizeof(l)/sizeof((l)[0]) - 1)`

创建一张新表，并预分配足够保存下数组l内容的空间（但不填充）

#### lua_getfield

`LUA_API int lua_getfield (lua_State *L, int idx, const char *k)`

- `L` 栈
- `idx` 索引
- `K` 索引值的一个元素

把索引idx所在值的元素k压入栈

#### lua_setfield

`LUA_API void lua_setfield (lua_State *L, int idx, const char *k)`

- `L` 栈
- `idx` 索引
- `K` 索引值的一个元素

把栈顶元素v弹出栈，并且把v赋值给索引index所在值的元素k

#### lua_tolstring

`LUA_API const char *lua_tolstring (lua_State *L, int idx, size_t *len)`

- `L` 栈
- `idx` 索引
- `len` 返回的字符串长度
- 返回值
  - Lua值为字符串：返回C字符串
  - Lua值为数字：返回C字符串，并且把堆栈中的那个值的实际类型转换为一个字符串
  - 其他：返回NULL

把索引idx处的Lua值转换成一个C字符串，并将C字符串长度通过len返回

#### luaL_checklstring

`LUALIB_API const char *luaL_checklstring (lua_State *L, int arg, size_t *len)`

- `L` 栈
- `arg` 参数索引
- `len` 返回的字符串长度

检查第arg个参数是否是一个字符串，并通过len返回字符串长度

#### luaL_checktype

`LUALIB_API void luaL_checktype (lua_State *L, int arg, int t)`

- `L` 栈
- `arg` 参数索引
- `t` 参数类型

检查第arg个参数是否t类型

#### luaL_traceback

`LUALIB_API void luaL_traceback (lua_State *L, lua_State *L1, const char *msg, int level)`

- `L` 栈
- `L1` 栈
- `msg` 附加信息
- `level` 栈回溯开始层级

将栈L1的回溯信息压入栈，并将msg附加到回溯信息之前

#### lua_pushstring

`LUA_API const char *lua_pushstring (lua_State *L, const char *s)`

- `L` 栈
- `s` 以"\0"结尾的字符串的指针

将s指向的字符串压栈

#### lua_pushlstring

`LUA_API const char *lua_pushlstring (lua_State *L, const char *s, size_t len)`

- `L` 栈
- `s` 字符串内容
- `len` 字符串长度

将s指向的字符串复制一份后压栈

#### lua_getallocf

`LUA_API lua_Alloc lua_getallocf (lua_State *L, void **ud)`

- `L` 栈
- `ud` 内存分配函数的参数
- 返回值
  - 成功：内存分配函数
  - 失败：NULL

返回给定状态机的内存分配器函数

#### lua_newstate

`LUA_API lua_State *lua_newstate (lua_Alloc f, void *ud)`

- `f` 内存分配函数
- `ud` 内存分配函数参数
- 返回值
  - 成功：lua运行栈
  - 失败：NULL

创建一个运行在新的独立状态机中的线程

#### lua_gc

`LUA_API int lua_gc (lua_State *L, int what, int data)`

- `L` Lua运行栈
- `what` 任务
  - `LUA_GCSTOP` 停止垃圾收集器
  - `LUA_GCRESTART` 重启垃圾收集器
  - `LUA_GCCOLLECT` 发起一次完整的垃圾收集循环
  - `LUA_GCCOUNT` 返回Lua使用的内存总量（以K字节为单位）
  - `LUA_GCCOUNTB` 返回mod(当前内存使用量/1024)
  - `LUA_GCSTEP` 发起一步增量垃圾收集
  - `LUA_GCSETPAUSE` 设置垃圾收集器间歇率，并返回旧的值
  - `LUA_GCSETSTEPMUL` 设置垃圾收集器步进倍率，并返回旧的值
  - `LUA_GCISRUNNING` 返回收集器是否在运行（即没有停止
- `data` 参数

根据`what`命令来控制垃圾回收器

#### lua_pushboolean

`LUA_API void lua_pushboolean (lua_State *L, int b)`

- `L` 栈
- `b` 布尔值

把布尔值压栈

####lua_pushlightuserdata

`LUA_API void lua_pushlightuserdata (lua_State *L, void *p)`

- `L` 栈
- `p` 轻量用户数据

把一个轻量用户数据压栈

#### lua_pop

`#define lua_pop(L,n)  lua_settop(L, -(n)-1)`

从栈中弹出n个元素

#### lua_call

`#define lua_call(L,n,r)  lua_callk(L, (n), (r), 0, NULL)`

调用一个函数

#### lua_callk

`LUA_API void lua_callk (lua_State *L, int nargs, int nresults, lua_KContext ctx, lua_KFunction k)`

- `L` 栈
- `nargs` 传入的参数个数
- `nresults` 返回值的个数
- `ctx` 延续函数上下文
- `k` 延续函数

调用一个函数（如果被调用函数发生错误将会从延续函数k处继续运行）

#### lua_pcall

`#define lua_pcall(L,n,r,f) lua_pcallk(L, (n), (r), (f), 0, NULL)`

以保护模式调用一个函数(函数出错时，会调用错误处理函数)

#### lua_pcallk

LUA_API int lua_pcallk (lua_State *L, int nargs, int nresults, int errfunc, lua_KContext ctx, lua_KFunction k)`

- `L` 栈
- `nargs` 传入的参数的个数
- `nresults` 返回值的个数
- `errfunc` 错误处理函数在栈中的索引 
- `ctx` 延续函数上下文
- `k` 延续函数

以保护模式调用一个函数(函数出错时，会调用错误处理函数，同时会调用延续函数继续运行)

#### lua_pushcclosure

`LUA_API void lua_pushcclosure (lua_State *L, lua_CFunction fn, int n)`

- `L` 栈
- `fn` C函数
- `n` 需要关联的值的数量(<=MAXUPVAL)

根据C函数创建闭包并关联值，然后把闭包压入到栈上

#### lua_pushcfunction

`#define lua_pushcfunction(L,f) lua_pushcclosure(L, (f), 0)`

根据C函数创建闭包，并把闭包压入到栈上

#### lua_gettop

`LUA_API int lua_gettop (lua_State *L)`

返回栈顶元素的索引（因为索引是从1开始，所以这个值=栈元素数量）；如果返回0，表示栈空

#### lua_settop

`LUA_API void lua_settop (lua_State *L, int idx)`

把索引idx的位置设置为栈顶（如果新栈顶比原来的大，超出部分填充nil，如果idx为0，清空栈）

#### lua_load

`LUA_API int lua_load (lua_State *L, lua_Reader reader, void *data, const char *chunkname, const char *mode)`

- `L` 栈
- `reader` 用户自定义reader函数
- `data` reader函数的参数
- `chunkname` 代码块的名字
- `mode` 文件类型(str/bin)

加载一段lua代码，把此段代码作为lua函数压入栈

#### luaL_loadfilex

`LUALIB_API int luaL_loadfilex (lua_State *L, const char *filename, const char *mode)`

- `L` 栈
- `filename` 文件名
- `mode` 文件格式(str/bin)

从一个文件加载lua代码(如果filename为NULL，从标准输入加载；如果文件的第一行以#开头，忽略这一行)

#### lua_loadfile

`#define luaL_loadfile(L,f) luaL_loadfilex(L,f,NULL)`

加载lua文件

#### lua_touserdata

`LUA_API void *lua_touserdata (lua_State *L, int idx)`

返回idx处的用户数据(如果索引idx处的值是一个完全用户数据，返回其地址；如果是一个轻量用户数据，返回它表示的指针) 

#### lua_rawgeti

`LUA_API int lua_rawgeti (lua_State *L, int idx, lua_Integer n)`

- `L` 栈
- `idx` 一级索引
- `n` 二级索引

找到索引idx处的值t，并把t中索引为n的值压栈

#### lua_close

`LUA_API void lua_close (lua_State *L)`

消息lua状态机中的所有对象，释放状态机中的所有动态内存

#### lua_pushnil

`LUA_API void lua_pushnil (lua_State *L)`

将空值压栈

#### lua_rawseti

`LUA_API void lua_rawseti (lua_State *L, int idx, lua_Integer n)`

- `L` lua状态机
- `idx` 一级索引
- `n` 二级索引

将栈顶的值弹出，并赋值给索引idx处表t的值t[n]

#### lua_createtable

`LUA_API void lua_createtable (lua_State *L, int narray, int nrec)`

- `L` lua状态机
- `narray`  表作为序列时的元素个数(建议值)
- `nrec` 表可能拥有的序列之外的元素个数(建议值)

创建一张新的空表压栈

#### lua_getmetatable

`LUA_API int lua_getmetatable (lua_State *L, int objindex)`

如果索引objindex处的值有元表，将元表压入栈

#### lua_setmetatable

`LUA_API int lua_setmetatable (lua_State *L, int objindex)`

把一张表弹出栈，并将其设为给定索引objidex处的值的元表

---



## 参考

- [ Lua 5.3 参考手册](https://www.runoob.com/manual/lua53doc/manual.html#lua_pcall)



