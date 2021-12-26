# Redis源码分析-客户端

[TOC]



## 客户端属性

```c
TODO
```

- `fd` 客户端的套接字描述符
  - `>-1` 普通客户端，命令来自于网络
  - `-1` 伪客户端（fake client），命令来自于AOF文件或LUA脚本，而不是网络
  
- `name` 客户端名字

- `flags` 客户端角色标记，可以是单个标记也可以是多个标记的二进制或；

  | 角色                       | 说明                                                         |
  | -------------------------- | ------------------------------------------------------------ |
  | `REDIS_SLAVE`              | 从服务器                                                     |
  | `REDIS_MASTER`             | 客户端代表的是一个主服务器                                   |
  | `REDIS_MONITOR`            | 从监视器                                                     |
  | `REDIS_MULTI`              | 正在执行事务                                                 |
  | `REDIS_BLOCKED`            | 客户端等待一个阻塞的操作                                     |
  | `REDIS_DIRTY_CAS`          | WATCH命令监视的键已经被修改                                  |
  | `REDIS_CLOSE_AFTER_REPLY`  | 客户端输出缓冲区大小超出服务器允许范围                       |
  | `REDIS_UNBLOCKED`          | 不再阻塞                                                     |
  | `REDIS_LUA_CLIENT`         | 用于处理Lua脚本里面包含的Redis命令的伪客户端                 |
  | `REDIS_ASKING`             | 向集群节点（运行在集群模式下的服务器）发送了ASKING命令       |
  | `REDIS_CLOSE_ASAP`         | 输出缓冲区超过了服务器允许范围，下一次serverCron执行时关闭这个客户端 |
  | `REDIS_UNIX_SOCKET`        | 客户端已连接上via Unix域名套接字                             |
  | `REDIS_DIRTY_EXEC`         | 排队时执行失败                                               |
  | `REDIS_MASTER_FORCE_REPLY` | 强制master回复队列                                           |
  | `REDIS_FORCE_AOF`          | 强制将当前命令写入到AOF文件                                  |
  | `REDIS_FORCE_REPL`         | 强制将当前执行的命令复制给所有从服务器                       |
  | `REDIS_PRE_PSYNC`          | 版本低于Redis2.8的从服务器                                   |
  | `REDIS_READONLY`           | 集群的客户端在只读状态                                       |
  | `REDIS_PUBSUB`             | 客户端在发布订阅模式中                                       |

- `argv` 要执行的命令(argv[0])及参数

- `argc` argv的长度

- `cmd` 当前要执行的命令

- `lastcmd` 最后一条要执行的命令

- `buf` 长度较小的回复缓冲区（16k）

- `bufpos` buf目前已使用的字节数量

- `reply` 可变大小缓冲区

- `authenticated` 身份验证标示
  - 0 未通过身份验证
  - 1 已经通过了身份验证
  
- `ctime` 创建时间

- `lastinteraction` 与服务端最后一次通信的时间

- `obuf_soft_limit_reached_time` 输出缓冲区大小超过软限制的时间



## 客户端的创建与关闭

客户端被关闭的原因：

- 客户端进程退出或被杀死
- 客户端向服务器发送了带有不符合协议格式的命令请求
- 客户端成为了CLIENT KILL命令的目标
- 客户端的空转时间超过`timeout`选项设置的值（这些情况例外：1.正在被BLPOP命令阻塞；2.正在执行SUBSCRIBE, PSUBSCRIBE等订阅命令）
- 客户端发送的命令请求的大小超过了输入缓冲区的限制大小（默认1GB）
- 发送给客户端的命令回复的大小超过了输出缓冲区的限制大小

服务器使用两种模式来限制客户端输出缓冲区的大小：

- 硬性限制（hard limit）：如果输出缓冲区的大小超过了硬性限制所设置的大小，服务器立即关闭客户端。
- 软性限制（soft limit）：如果输出缓冲区的大小超过了软性限制所设置的大小，但还没超过硬性限制，那么服务器将使用客户端状态结构的`obuf_soft_limit_reached_time`属性记录下客户端到达软性限制的起始时间；之后服务器会继续监视客户端，如果输出缓冲区的大小一直超出软性限制，并且持续时间超过服务器设定的时长，那么服务器将关闭客户端。

使用`client-output-buffer-limit`选项可以为普通客户端，从服务器客户端，执行发布与订阅功能的客户端分别设置不同的软性限制和硬性限制，该选项的格式为：

`client-output-buffer-limit <class> <hard limit> <soft limit> <soft seconds>`

- `class` 类别
  - `norm` 普通客户端
  - `slave` 从服务器
  - `pubsub` 发布订阅功能的客户端
- `hard limit` 硬限制
- `soft limit` 软限制
- `soft seconds` 软限制时长(s)



## 参考

### 文献

[1] 黄健宏.Redis设计与实现

### 外链

- [redis源码分析（3）——请求处理](https://blog.csdn.net/chosen0ne/article/details/43053915?utm_source=blogkpcl14)