[TOC]

# skynet问题

### lua模块引用时找不到文件

**问题**

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

**原因**

1. lua没有找到文件，`require "xxx"`这里报错

**解决**

修改调用语句：

```lua
package.path = "./examples/?.lua;" .. package.path -- 指定目录
local hot = require "hot"
```



### 热更新时print函数无法打印

**问题**

测试热更新机制时，print函数失效

**原因**

热更新时skynet屏蔽了print函数，导致print无法打印

**解决**

将`print(xxx)`函数修改为`_G.print(xxx)`



### 调用snax.exit()报错

**问题**

```lua
local skynet = require "skynet"
local snax = require "skynet.snax"

skynet.start(function ()
    local s = snax.newservice("snhello", "hello")
    if not s then
        print("create snax server fail")
        return
    end
    snax.exit()
end)
```

当执行到snax.exit退出时，报错如下：

```sh
[:00000008] init service failed: ./lualib/snax/interface.lua:82: ./examples/main_snax.lua:4: attempt to index a nil value (local 'skynet')
stack traceback:
        ...
```

**原因**

`snax.exit`退出的是自己的服务，不是`snhello`服务

**解决**

将`snax.exit()`修改为`snax.kill(s)`

