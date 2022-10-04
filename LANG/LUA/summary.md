# Lua总结


<!-- vim-markdown-toc GFM -->

* [源码组织结构](#源码组织结构)
* [环境变量](#环境变量)
    - [_ENV](#env)
    - [_G](#g)
* [`:`与`.`的区别](#与的区别)
* [参考](#参考)

<!-- vim-markdown-toc -->



## 源码组织结构

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

每个被编译的Lua代码块都会绑定一个单独的环境叫做`_ENV`，`_ENV`默认指向`_G`；

（个人理解）`_ENV`在闭包被调用用时提供环境信息，它位于闭包的第1个upvalue位置。

### _G

Lua保有一个被称为**全局环境**的特殊环境，叫做`_G`，用来存储一些全局变量；

~~修改`_G`会影响Lua的其他服务（不建议使用全局环境，会污染命名空间）。~~



## `:`与`.`的区别

`:`定义的函数会自动传入一个名为`self`的隐式变量（类似于c++的this），标识当前对象的指针；`.`没有这个功能。



## 参考

[1] [Environments Tutorial](http://lua-users.org/cgi-bin/wiki.pl?action=search&string=EnvironmentsTutorial&body=1)

[2] [Lua 5.3 参考手册](https://www.runoob.com/manual/lua53doc/manual.html#4)

[3] [lua 5.2 的 _ENV](https://blog.codingnow.com/2011/12/lua_52_env.html)

[4] [Lua细节归纳](https://www.zhyingkun.com/markdown/luadetail/)

