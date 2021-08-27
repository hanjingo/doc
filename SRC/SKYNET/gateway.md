# skynet网关

网关服务提供了客户端连接的管理，数据包分割与转发等功能。skynet提供了网关服务，具体看`gateserver.lua`



## msgserver

msgserver指逻辑服务器，只要实现指定的接口，就可以满足不同的功能；

### 编码规范

要使用msgserver需要实现以下接口：

- `register_handler(name)`

  - `name` 当前登陆点的名字

  监听成功回调

- `login_handler(uid, secret)`

  - `uid`
  - `secret`

  登录回调

- `logout_handler(uid, subid)`

  - `uid`
  - `subid`

  注销回调

- `kick_handler(uid, subid)`

  - `uid`
  - `subid`

  关闭连接回调

- `disconnect_handler(username)`

  - `username`

  断开连接回调

- `request_handler(username, msg, sz)`

  - `username`
  - `msg`
  - `sz`

  客户端请求回调



## 原理

gate其实就是一个msgserver，gate服务通过函数`gateserver.start(handler)`启动，用户需要自己实现回调器接口，其接口定义如下：

- `handler.connect(fd, ipaddr)`

  - `fd` socket句柄
  - `ipaddr` 客户端地址

  当一个新客户端被accept后，connect被回调；

  **注意：当connect被调用后，一定要记得调用`gateserver.openclient(fd)`给套接字放行。**

- `handler.disconnect(fd)`

  - `fd` socket句柄

  当连接被断开，disconnect被回调；

- `handler.open(source, conf)`

  - `source` 请求来源地址
  - `conf` 开启gate服务的参数表

  当监听的端口被打开时，open被调用

- `handler.message(fd, msg, sz)`

  - `fd` socket句柄
  - `msg` C指针（用完之后记得用skynet_free释放）
  - `sz` 包长度

  当一个完整的消息包被切分好后，message被调用；

- `handler.error(fd, msg)`

  - `fd` socket句柄
  - `msg` 错误消息

  当一个连接异常（通常意味着断开），error被调用

- `handler.warning(fd, size)`

  - `fd` socket句柄
  - `size` 待发送的数据大小（单位：字节）

  当fd上**待发送**的数据累积超过1M字节后，warning被调用

- `handler.command(cmd, source, ...)`

  - `cmd` 内部消息指令(字符串，open和close系统保留)
  - `source` 消息来源

  当收到skynet内部消息时，如果有注册command方法，command被调用



## 示例

TODO



## 参考

- [GateServer](https://github.com/cloudwu/skynet/wiki/GateServer)
- [skynet框架应用 (十四) 登录服务](https://blog.csdn.net/qq769651718/article/details/79435251)

