# skynet登录服务器

登录服务器是用户接入游戏系统接触到的第一个服务；登录服务器主要用来做以下功能：

- 权限验证
- 登录操作
- 服务地址路由
- ...



## 登录协议

```sequence
Title:snax loginserver登录协议
Note right of 服务端: >>> 产生随机数challenge(8byte)
服务端->客户端: base64(challenge)

Note left of 客户端: 产生随机数clientkey(8byte) <<<
客户端->服务端: base64(clientkey)

Note right of 服务端: >>> 产生随机数serverkey(8byte)
服务端->客户端: base64(DH-Exchange(serverkey))

Note left of 客户端: 使用clientkey与serverkey，通过dhsecret算法得到安全密钥secret <<<
Note right of 服务端: >>> 使用clientkey与serverkey，通过dhsecret算法得到安全密钥secret

Note left of 客户端: 使用密钥secret通过hmac64加密challenge得到chmac <<<
客户端->服务端: base64(chmac)
Note right of 服务端: >>> 使用密钥secret通过hmac64加密challenge得到shmac
Note right of 服务端: >>> 比对shmac和chamc：如果相等，密钥交换成功；不相等，断开连接

Note left of 客户端: 组合base64 user @ base64 server:base64 passwd <<<
Note left of 客户端: 使用secret通过DES加密，得到etoken <<<
客户端->服务端: base64(etoken)

Note right of 服务端: >>> 使用secret通过DES解密etoken得到token
Note right of 服务端: >>> 使用token调用auth_handler得到server和uid(用户自定义事件)
Note right of 服务端: >>> 使用uid和secret调用login_handler得到subid
服务端->客户端: base64(subid)

Note left of 客户端: 用subid去登陆 <<<
Note left of 客户端: 断开与login服务的连接 <<<

Note over 服务端,客户端: 通信使用的是行协议
```

- `DHexchange` 密钥交换算法，主要用来协商一个服务器与客户端的密钥；

- `hmac64` 以一个密钥secret和一个消息challenge为输入，生成一个消息摘要hmac作为输出；

- `base64` 基于64个可打印字符来表示二进制数据的编码算法；

- `DES` 密钥加密的块算法(Data Encryption Standard)；

- `hashkey` 云风自实现的hash算法（只能哈希小于8字节的数据，返回8字节数据的hash）



## 登录流程

```sequence
Title:snax loginserver 登录流程
客户端->服务端: 连接服务
客户端->服务端: handshake:base64 HSHHmac
服务端->客户端: "200 ok"
客户端->服务端: request session
服务端->客户端: response ok session
```

- `400 Bad Request`：握手失败
- `401 Unauthorized`：自定义的auth_handler不认可token
- `403 Forbidden`：自定义的login_handler调用失败
- `406 Not Acceptable`：不允许多点登录
- `200 OK`：成功，返回一个subid，用作唯一标识



## 编码规范

要使用login server需要实现以下方法：

- `function server.auth_handler(token)`

  - `token` 凭证

  验证客户端发送过来的token：

  1. 验证失败，通过error抛出异常；
  2. 验证通过，返回用户希望进入的登陆点以及用户名。

- `function server.login_handler(server, uid, secret)`

  - `server` 登陆点
  - `uid` 用户名
  - `secret` 登录协议中，通过dhsecret算法得到安全密钥secret

  登陆后的处理逻辑。

- `server.command_handler(command, ...)`

  - `command` 指令类型

  用来处理一些skynet内部控制指令。



## 参考

- [云风-LoginServer](https://github.com/cloudwu/skynet/wiki/LoginServer)
- [skynet框架应用 (十四) 登录服务](https://blog.csdn.net/qq769651718/article/details/79435251)
