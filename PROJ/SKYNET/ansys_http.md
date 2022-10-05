# skynet源码分析-Http模块

<!-- vim-markdown-toc GFM -->

* [服务端](#服务端)
    - [API](#api)
* [示例](#示例)
    - [1 http服务器](#1-http服务器)
* [参考](#参考)

<!-- vim-markdown-toc -->



## 服务端

### API

- `function socket.start(id, func)`

  - `id` 套接字描述符
  - `func` 连接回调
  - `返回值`
    - 套接字文件描述符

- `function socket.listen(host, port, backlog)`

  - `host` IP地址
  - `port` 端口
  - `backlog`
  - `返回值`
    - 套接字文件描述符

  监听socket

- `function httpd.read_request(...)`

  - `sockethelper.readfunc(fd, pre)`
  - `request body size` HTTP Body的大小

  - `返回值`
    - `code` 返回值
    - `url` 请求的URL地址
    - `method` POST/GET...
    - `header` HTTP请求头
    - `body` HTTP Body

  读http请求

- `function httpd.write_response(...)`

  - `sockethelper.writefunc(id)`
  - `返回值`
    - `错误码`
    - `错误`

  写http返回

- `function url.parse(u)`

  - `u` URL
  - `返回值`
    - `path` URL地址
    - `query` 参数

  解析请求的URL

- `function url.parse_query(q)`

  - `q` 请求参数
  - `返回值`
    - 返回参数字典；k：参数名，v：参数值

  解析请求的参数



## 示例

### 1 http服务器

```lua
local skynet = require "skynet"
local socket = require "skynet.socket"
local httpd = require "http.httpd"
local sockethelper = require "http.sockethelper"
local urllib = require "http.url"

local function response(id, ...)
    local ok, err = httpd.write_response(sockethelper.writefunc(id), ...)
    if not ok then
        skynet.error(string.format("fd = %d, %s", id, err))
    end
end

local function handle(id)
    socket.start(id)
    -- 设置request body的最大尺寸(8K)
    local code, url, method, header, body = httpd.read_request(sockethelper.readfunc(id), 8192)
    if code then
        if code ~= 200 then
            response(id, code)
        else
            if header.host then
                skynet.error("header host", header.host)
            end

            local path, query = urllib.parse(url)
            skynet.error(string.format("path:%s", path))
            local color, text = "red", "hello"
            if query then
                local q = urllib.parse_query(query) -- 获取请求的参数
                for k, v in pairs(q) do
                    skynet.error(string.format("query: %s= %s", k, v))
                    if (k == "color") then
                        color = v
                    elseif (k == "text") then
                        text = v
                    end

                    local resphtml = "<body bgcolor=\""..color.."\">"..text.."</body>\n" -- 返回网页
                    response(id, code, resphtml)
                end
            else
                if url == sockethelper.socket_error then
                    skynet.error("socket closed")
                else
                    skynet.error(url)
                end
            end
            socket.close(id)
        end
    end
end

local function accept(fd)
    skynet.fork(handle, fd)
end

-- http://127.0.0.1:8001/?color=blue&text=abc
skynet.start(function()
    -- 监听一个端口
    local id = socket.listen("0.0.0.0", 8001)
    socket.start(id, accept)
end)
```



## 参考

- [http协议的服务](https://blog.csdn.net/qq769651718/article/details/79435329)
- [云风-给 skynet 增加 http 服务器模块](https://blog.codingnow.com/2014/07/skynet_http.html)
- [skynet框架应用 (十八) http协议的服务](https://blog.csdn.net/qq769651718/article/details/79435329?spm=1001.2014.3001.5501)

