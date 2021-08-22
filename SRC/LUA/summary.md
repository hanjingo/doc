# lua源码分析-总结



## 源码组织

- 虚拟机核心相关文件列表

  | 文件名     | 作用                             | 对外接口前缀 |
  | ---------- | -------------------------------- | ------------ |
  | lapi.c     | C语言接口                        | `lua_`       |
  | lcode.c    | 源码生成器                       | `luaK_`      |
  | ldebug.c   | 调试库                           | `luaG_`      |
  | ldo.c      | 函数调用及栈管理                 | `luaD_`      |
  | ldump.c    | 序列化预编译的Lua字节码          |              |
  | lfunc.c    | 提供操作函数原型及闭包的辅助函数 | `luaF_`      |
  | lgc.c      | GC                               | `luaC_`      |
  | llex.c     | 词法分析                         | `luaX_`      |
  | lmem.c     | 内存管理                         | `luaM_`      |
  | lobject.c  | 对象管理                         | `luaO_`      |
  | lopcodes.c | 字节码操作                       | `luaP_`      |
  | lparser.c  | 分析器                           | `luaY_`      |
  | lstate.c   | 全局状态机                       | `luaE_`      |
  | lstring.c  | 字符串操作                       | `luaS_`      |
  | ltable.c   | 表操作                           | `luaH_`      |
  | lundump.c  | 加载预编译字节码                 | `luaU_`      |
  | ltm.c      | tag方法                          | `luaT_`      |
  | lzio.c     | 缓存流接口                       | `luaZ_`      |

- 内嵌库相关文件列表

  | 文件名     | 作用                         |
  | ---------- | ---------------------------- |
  | lauxlib.c  | 库编写时需要用到的辅助函数库 |
  | lbaselib.c | 基础库                       |
  | ldblib.c   | 调试库                       |
  | liolib.c   | IO库                         |
  | lmathlib.c | 数学库                       |
  | loslib.c   | OS库                         |
  | ltablib.c  | 表操作库                     |
  | lstrlib.c  | 字符串操作库                 |
  | loadlib.c  | 动态扩展库加载器             |
  | limit.c    | 负责内嵌库的初始化           |

- 解析器，字节码编译器相关文件列表

  | 文件名 | 作用         |
  | ------ | ------------ |
  | lua.c  | 解释器       |
  | luac.c | 字节码编译器 |



## 环境变量

### _ENV

每个被编译的Lua代码块都会有一个外部的局部变量叫`_ENV`，被`_ENV`用于值的表被称为**环境**。

### _G

Lua保有一个被称为**全局环境**的特殊`_ENV`，叫做`_G`。



## lua优化技巧

1. 在Lua中，应该尽量少地使用字符串连接操作符，因为每一次都会生成一个新的字符串。
2. 创建表时可以采用“预分配技术”，防止表散列操作长度小的表时造成的性能不佳。
3. 尽量不要将一个表混用数组和散列桶，即一个表最好只存放一类数据。



## 参考

- [Lua 5.3 参考手册](https://www.runoob.com/manual/lua53doc/manual.html#4)
