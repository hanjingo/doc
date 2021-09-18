# skynet Http模块



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



## 参考

- [http协议的服务](https://blog.csdn.net/qq769651718/article/details/79435329)
- [云风-给 skynet 增加 http 服务器模块](https://blog.codingnow.com/2014/07/skynet_http.html)
- [skynet框架应用 (十八) http协议的服务](https://blog.csdn.net/qq769651718/article/details/79435329?spm=1001.2014.3001.5501)

