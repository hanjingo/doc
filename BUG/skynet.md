[TOC]

# skynet问题

### lua模块引用时找不到文件

新写了一个lua模块，其调用语句如下：

```lua
local xxx = require "xxx"
```

用skynet调用时报以下错误：

```lua
 lua loader error : ./lualib/skynet/require.lua:31: module 'xxx' not found:
        no field package.preload['xxx']
        no file './lualib/xxx.lua'
        no file './lualib/xxx/init.lua'
        no file './luaclib/xxx.so'
stack traceback:
        [C]: in upvalue 'require'
        ./lualib/skynet/require.lua:31: in function 'skynet.require.require'
        ./examples/hotpatch.lua:4: in local 'main'
        ./lualib/loader.lua:50: in main chunk
```

原因：

1. lua没有找到文件，`require "xxx"`这里报错

解决办法：

修改调用语句：

```lua
package.path = "./examples/?.lua;" .. package.path -- 指定目录
local hot = require "hot"
```



