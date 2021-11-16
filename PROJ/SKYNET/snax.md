[TOC]

# skynet的snax框架

`snax`是对 skynet API 的部分封装（主要是请求/回调这一块）而产生的一个框架。



## 使用

使用snax之前需要引入`require "snax"`

### snax服务编写规范

要使用snax服务必须实现以下接口：

- `init(...)`
- `exit(...)`

例，创建一个snax服务：

1. 创建配置文件`examples/config.snax`，内容如下：

   ```txt
   thread = 8
   logger = nil
   harbor = 0
   start = "main_snax"
   bootstrap = "snlua bootstrap"	-- The service for bootstrap
   luaservice = "./service/?.lua;./test/?.lua;./examples/?.lua"
   lualoader = "lualib/loader.lua"
   cpath = "./cservice/?.so"
   snax = "./examples/?.lua"
   ```

 2. 创建入口文件`examples/main_snax.lua`，内容如下：

    ```lua
    local skynet = require "skynet"
    local snax = require "skynet.snax"
    
    skynet.start(function ()
        local s = snax.newservice("snhello", "hello")
        if not s then
            print("create snax server fail")
            return
        end
        snax.kill(s, "world")
    end)
    ```

3. 实现snax服务文件`examples/snhello.lua`，内容如下：

   ```lua
   local skynet = require "skynet"
   local snax = require "skynet.snax"
   
   function init(...) -- 初始化函数
       print("snax start with arg:", ...)
   end
   
   function exit(...) -- 退出函数
       print("snax exit with arg:", ...)
   end
   ```

### 创建snax请求

- `obj.post.CMD(...)` 用来发送无响应请求
- `obj.req.CMD(...)` 用来发送有响应请求

例，snax请求：

1. 创建配置文件`examples/config.snax`，内容如下：

   ```txt
   -- 同上
   ```

 2. 创建入口文件`examples/main_snax.lua`，内容如下：

    ```lua
    ... -- 同上
    skynet.start(function ()
        ... -- 同上
        s.post.hello("hello") -- 无响应请求
        print("post hello")
    
        local r = s.req.work("coding") -- 有响应请求
        print("req work with result:", r)
    end)
    ```

3. 实现snax服务文件`examples/snhello.lua`，内容如下：

   ```lua
   ... -- 同上
   function accept.hello(...) -- 响应obj.post.hello
       print("how are you")
   end
   
   function response.work(arg) -- 响应obj.req.work
       return "do "..arg
   end
   ```



## 热更新

`snax.hotfix`可以用于热更新（被热更的对象只能是全局变量）

例，热更新`response.work(arg)`函数：

1. 创建配置文件`examples/config.snax`，内容如下：

   ```txt
   -- 同上
   ```

 2. 创建入口文件`examples/main_snax.lua`，内容如下：

    ```lua
    ... -- 同上
    skynet.start(function ()
        ... -- 同上
        -- 热更新
        snax.hotfix(s, [[ 
            function response.work(arg) -- 响应obj.req.work
                return "finish "..arg
            end
        ]])
        local r = s.req.work("watch movie")
        print("req work with hotfix result:", r)
    end)
    ```

3. 实现snax服务文件`examples/snhello.lua`，内容如下：

   ```lua
   -- 同上
   ```



## 参考

- [云风-skynet 的 snax 框架及热更新方案](https://blog.codingnow.com/2014/04/skynet_snax.html)
- [skynet框架应用 (十二) snax框架](https://blog.csdn.net/qq769651718/article/details/79435352)

