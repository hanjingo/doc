[TOC]

# skynet热更新

skynet实现热更新的两种方式：

- clearcache
- inject



## 前提

### 控制台

控制台是skynet提供的一个控制工具，需要启动debug_console服务`skynet.newservice("debug_console", ip, port)`，指定一个地址；skynet启动后，用nc命令就可以进入控制台；

### 代码缓存

skynet修改了Lua的官方实现（可选），让多个Lua VM共享相同的函数原型；

#### 原理

改写了lua的辅助API（`luaL_loadfilex`），代码缓存采用只增加不删除的策略；一旦加载过一份脚本，那么到进程结束前，它占据的内存永远不会释放（也不会被加载多次）；所有直接或节点调用这个api都受其影响。

skynet提供了以下接口用来处理缓存：

- 清理缓存

  ```lua
  local cache = require "skynet.codecache"
  cache.clear()
  ```

  清理代码缓存并创建一个新的缓存

- 修改缓存工作模式

  ```lua
  cache.mode(mode)
  ```

  - `mode` 当mode为空时，返回当前的mode，默认为"ON"

  修改缓存的工作模式

  mode说明：

  | mode  | 说明                                                         |
  | ----- | ------------------------------------------------------------ |
  | ON    | 当前服务cache一切加载lua代码文件的行为                       |
  | OFF   | 当前服务关闭任何重复利用lua代码文件的行为，即使在别的服务中曾经加载过同名文件 |
  | EXIST | 当前服务在加载曾经在其他服务或自己的服务加载过同名文件时，复用之前的拷贝。但对新加载的文件则不进行cache。注：通常可以让skynet本身被cache |

参考源码：

- `service/debug_console.lua`
- `service/debug_console.lua`

#### 优点

- 当在同一个skynet进程中开启了大量lua VM时，可以节省不少内存，并且提高了VM启动速度。



## clearcache

**clearcache用于新服务的热更新，对已有服务不能热更新；**

### 使用

1. 在控制台输入`clearcache`

### 原理

每个snlua服务会启动一个单独的lua VM，对于同一份lua文件，N个服务就要加载N次到内存。

skynet对此做了优化，每个lua文件只加载一次到内存，保存`lua文件--内存映射表`，下一个服务加载的时候copy一份内存即可，提高了VM的启动速度。

参考源码：

- `3rd/lua/lauxlib.c`



## inject

**注入更新，将新代码注入到已有的服务里，让服务执行新的代码，可以热更已开启的服务。**

### 使用

1. 在控制台输入`inject address xxx.lua`

### 原理

参考源码：

- `lualib/skynet/inject.lua`



## 参考

- [skynet热更新](https://github.com/hanjingo/doc/blob/master/SRC/SKYNET/hotpatch.md)
- [云风-DebugConsole](https://github.com/cloudwu/skynet/wiki/DebugConsole)
- [skynet源码分析之热更新](https://www.cnblogs.com/RainRill/p/8940673.html)
- [CodeCache](https://github.com/cloudwu/skynet/wiki/CodeCache)

