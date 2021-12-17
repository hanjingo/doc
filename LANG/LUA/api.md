# LUA API

[TOC]

## Lua库

[返回顶部](#LUA API)

### 基础库

#### assert

`assert(v[, message])`

- `v` 需要断言的语句
- `message` 输出语句

断言语句，遇到不满足的语句时，抛出错误

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

遍历表（表的key只能为整数，遇到nil时**终止遍历**）

#### load

`load(chunk [, chunkname [, mode [, env]]])`

- `chunk` 代码块
- `chunkname` 代码块名字，默认chunk
- `mode` 代码格式(b：二进制， t：文本，bt：二进制/文本)
- `env` 代码块需要的参数

加载一个数据块，并以函数形式返回加载的代码块；

**注意：lua不会对二进制代码块做健壮性检查，恶意构造一个二进制块可能会把解释器弄崩溃。**

#### pairs

`pairs (t)`

- `t` table

遍历表（如果 `t` 有元方法 `__pairs`， 以 `t` 为参数调用它；对key的类型没有要求，遇到nil时**直接跳过**）

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

[返回顶部](#LUA API)

### 字符串控制

#### 匹配模式

lua匹配模式使用字符串来描述；

字符含义如下：

| 字符类                    | 含义                                                         |
| ------------------------- | ------------------------------------------------------------ |
| `.`                       | 任何字符                                                     |
| `%a`                      | 任何字母                                                     |
| `%c`                      | 任何控制字符                                                 |
| `%d`                      | 任何数字                                                     |
| `%g`                      | 任何除空白符外的可打印字符                                   |
| `%l`                      | 所有小写字母                                                 |
| `%p`                      | 所有标点符号                                                 |
| `%s`                      | 所有空白字符                                                 |
| `%u`                      | 所有大写字母                                                 |
| `%w`                      | 所有字母及数字                                               |
| `x`                       | 表示字符 *x* 自身（这里 *x* 不能是 *魔法字符* `^$()%.[]*+-?` 中的一员） |
| `%x`                      | 表示所有16进制数字符号                                       |
| `%任意非字母或数字的字符` | 转义表示字符x（x为）                                         |
| `[set]`                   | 表示括号中所有字符的联合，用`-`连接；例：`[0-7]`表示8进制数据； |
| `[^set]`                  | 表示set的补集                                                |

字符条目格式如下：

| 条目格式         | 含义                                                         |
| ---------------- | ------------------------------------------------------------ |
| `单个字符`       | 匹配任意单个字符。                                           |
| `单个字符*`      | 匹配0或多个该类的字符；这个条目总是匹配尽可能长的串。        |
| `单个字符+`      | 匹配1或更多个该类的字符；这个条目总是匹配尽可能长的串。      |
| `单个字符-`      | 匹配0或更多个该类的字符；和`*`不同，这个条目总是匹配尽可能短的串。 |
| `单个字符?`      | 匹配0或1个该类的字符；只要有可能，它会匹配一个。             |
| `%数字`          | 匹配一个等于数字(0~9)的子串                                  |
| `%b字符一字符二` | 匹配以字符一开始字符二结束并且字符一与字符二保持*平衡（读到字符一就+1，读到字符二就-1，最终结束处的字符二是第一个计数到0的字符二）*的字符串； |
| `%f[set]`        | 边境模式；匹配一个位于set内某个字符之前的一个空串，且这个位置的前一个字符不属于set； |

#### string.dump

`string.dump(function [, strip])`

- `function` 函数
- `strip` 是否不携带调试信息
  - `true` 不携带调试信息
  - `false` 携带调试信息

将函数序列化为二进制数据

例:

```lua
 print(string.dump(function() print("hello") end))
uaS 

xV           (w@=stdin            @ A@  $@ &     printhello                               _ENV
>                                                                                                                    
```

#### string.find

`string.find(s, pattern, [, init [, plain]])`

- `s` 待查找的字符串
- `pattern` 匹配值
- `init` 查找的起始位置（默认1，可以为负）
- `plain` 是否关闭模式[匹配机制](#匹配模式)
  - `true` 关闭模式匹配机制，仅查找子串，将pattern看作普通字符串
  - `false` 打开匹配机制，将pattern看作“魔法字符串”
- 返回值  起始位置，终点位置

从字符串中查找子字符串位置；例：

```lua
> print(string.find("123ab456ab789", "ab"))
4       5
> print(string.find("123Ab456Ab789", "%u", 1, false))
4       4
```

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

#### string.gsub

`string.gsub (s, pattern, repl [, n])`

- `s` 待替换的字符串
- `pattern` 匹配值
- `repl` 替换后的值，可以为字符串/表/函数：
  - `字符串`  字符串（%：转义符）；
  - `表` 每次匹配时都会用第一个不货物作为键去查表；
  - `函数` 每次匹配时都会调用这个函数，所有捕获到的字串依次作为参数传入；
- `n` 匹配次数

使用`repl`替换`s`中的匹配字符串`pattern`，返回被替换后的字符串和替换的数量。

例：

```sh
> print(string.gsub("hello world", "(%w+)", "%1 %1"))
hello hello world world 2
> print(string.gsub("hello world", "%w+", "%0 %0", 1))
hello hello world       1
> print(string.gsub("hello world from Lua", "(%w+)%s*(%w+)", "%2 %1"))
world hello Lua from    2
> print(string.gsub("home = $HOME, user = $USER", "%$(%w+)", os.getenv))
home = /home/he, user = he      2
> print(string.gsub("4+5 = $return 4+5$", "%$(.-)%$", function (s)
           r>> eturn load(s)()
    >>      end))
4+5 = 9 1
```

#### string.len

`string.len (s)`

- `s` 字符串

返回字符串长度（'\0'也算一位）

#### string.rep

`string.rep (s, n [, sep])`

- `s` 原始字符串
- `n` 串联次数
- `sep` 分隔符

将原始字符串s以分隔符复制并串联n次，效果等同于使用n次`..`；例：

```lua
> print(string.rep("hello", 4, "_"))
hello_hello_hello_hello
```

#### string.sub

`string.sub (s, i [, j])`

- `s` 字符串
- `i` 开始位置（可负）
- `j` 结束位置（可负）

返回s的子字符串`s[i, j]`

#### string.byte

`string.byte (s [, i [, j]])`

- `s` 字符串
- `i` 索引开始位置（默认1）
- `j` 索引结束位置（默认1）

将某一段字符转化为二进制格式；例：

```lua
local s = "abcdefg"
print(string.byte(s))
print(string.byte(s, 2))
print(string.byte(s, 2, 3))
```

```sh
he@ya:~$ lua t.lua
97
98
98	99
```

#### string.char

`string.char (···)`

将number转为char；例：

```sh
> print(string.char(98))
b
```

### 基础UTF-8支持

TODO

[返回顶部](#LUA API)

### 表控制

#### table.insert

`table.insert (t, [pos,] value)`

在t的pos位置插入元素，并后移t[pos:]一位；pos默认为#t+1；

#### table.unpack

`table.unpack (list [, i [, j]])`

- `list` lua table
- `i` 起始位置（默认 1）
- `j` 结束位置（默认 #list）

返回列表中的元素，等价于`return list[i], ..., list[j]`

#### table.pack

`table.pack (···)`

返回以键 1,2... 等填充的新表， 并将 "`n`" 这个域设为参数的总数。

#### table.remove

`table.remove (list [, pos])`

移除list中pos位置上的元素，并返回这个被移除的量；当pos位于1到#list之间时，它向前移动元素list[pos+1], list[pos+2], ..., list[#list]并删除元素list[#list]；

pos 默认为 #list， 因此调用 table.remove(l) 将移除表 l 的最后一个元素；

例：

```lua
Lua 5.3.3  Copyright (C) 1994-2016 Lua.org, PUC-Rio
> a = {"a", "b", "c", "d"}
> print(table.remove(a, 2))
b
> for i = 1, #a do print(a[i]) end
a
c
d
> print(table.remove(a, #a))
d
> for i = 1, #a do print(a[i]) end
a
c
> print(table.remove(a))
c
>  for i = 1, #a do print(a[i]) end
a
```

### 数学函数

#### math.ceil

`math.ceil (x)`

- `x` number类型值

返回不小于x的最小整数值

#### math.floor

`math.floor (x)`

- `x` number类型值

返回不大于x的最大整形值

### 输入输出

TODO

### 操作系统库

#### clock

TODO

#### date

`os.date ([format [, time]])`

- `format` 格式化字符串

  - `以!开头` 按格林尼治时间进行格式化

  - `*t` 返一个带year(4位)，month(1-12)， day (1--31)， hour (0-23)， min (0-59)，sec (0-61)，wday (星期几， 星期天为1)， yday (年内天数)和isdst (是否为日光节约时间true/false)的带键名的表

  - `带格式符的字符串`

    | 格式符 | 含义               | 具体示例                     |
    | :----- | :----------------- | :--------------------------- |
    | %a     | 一星期中天数的简写 | (Fri)                        |
    | %A     | 一星期中天数的全称 | (Wednesday)                  |
    | %b     | 月份的简写         | (Sep)                        |
    | %B     | 月份的全称         | (May)                        |
    | %c     | 日期和时间         | (09/16/98 23:48:10)          |
    | %d     | 一个月中的第几天   | (28)[0 - 31]                 |
    | %H     | 24小时制中的小时数 | (18)[00 - 23]                |
    | %I     | 12小时制中的小时数 | (10)[01 - 12]                |
    | %j     | 一年中的第几天     | (209)[01 - 366]              |
    | %M     | 分钟数             | (48)[00 - 59]                |
    | %m     | 月份数             | (09)[01 - 12]                |
    | %P     | 上午或下午         | (pm)[am - pm]                |
    | %S     | 一分钟之内秒数     | (10)[00 - 59]                |
    | %w     | 一星期中的第几天   | (3)[0 - 6 = 星期天 - 星期六] |
    | %W     | 一年中的第几个星期 | (2)0 - 52                    |
    | %x     | 日期               | (09/16/98)                   |
    | %X     | 时间               | (23:48:10)                   |
    | %y     | 两位数的年份       | (16)[00 - 99]                |
    | %Y     | 完整的年份         | (2016)                       |
    | %%     | 字符串'%'          | (%)                          |

- `time` 时间（如果不填，则取当前时间）

将时间格式化。

例：

```sh
> print(os.date("%Y-%m-%d %H:%M:%S"))
2021-10-18 14:57:55
```

### 调试库

TODO

---

## C库

[返回顶部](#LUA API)

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



