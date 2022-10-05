# 网络问题


<!-- vim-markdown-toc GFM -->

- [大小端问题](#大小端问题)
- [Nagle算法的坑](#nagle算法的坑)
- [Tcp timewait问题](#tcp-timewait问题)
- [linux端口访问不了](#linux端口访问不了)
- [SIGPIPE问题](#sigpipe问题)

<!-- vim-markdown-toc -->

### 大小端问题

**问题**

这是个历史遗留问题，一般手机，pc用的小端 比如 `(uint32)3019 = [203 11 0 0]`；服务器一般用的大端 比如 `(uint32)3019 = [0 0 11 203]`，java默认使用大端类型；如果通讯双方的大小端不一致，会导致解码时数据错乱；

**解决**

- 方法1

  前后端传数据时，在数据头里面做个标记是大端还是小端，收到消息后做一下转换;
- 方法2(推荐)

  前后端统一使用大端，收到数据后不管大小端都转成大端;



### Nagle算法的坑

TODO



### Tcp timewait问题

**问题**

为了防止出现“主动断开连接方发送的最后一个ACK包异常，导致被动关闭防会重发FIN请求，影响该四元组上的下一个连接的正确性”的情况，TCP通过主动关闭方等待 `2*MSL`来避免这个问题；但是，引来了另一个问题，如果主动发起方频繁建立/断开连接，会导致系统之存在大量的timewait连接，从而导致没法建立新的连接；

**解决**

- 方法一

  设置以下两个内核参数：

  - `net.ipv4.tcp_tw_recycle`

    - `1` 启动time wait连接的快速回收；
  - `net.ipv4.tcp_tw_reuse`

    - `1` 让time wait四元组可以快速用于新连接；



### linux端口访问不了

**问题**

telnet访问linux端口时不通

**原因**

1. 防火墙开了；
2. linux端口是默认关闭的，需要手动开启；

**解决**

1. (关闭防火墙) 或 (开启防火墙并开放端口)：

```sh
# 关闭防火墙
sudo ufw disable
```

或

```sh
# 开启防火墙，开放端口
sudo ufw allow xx # xx为端口号
sudo ufw reload
```

2. 设置iptable，手动开启端口：

```sh
# 安装iptables软件
sudo apt-get install iptables

# 开放端口
iptables -I INPUT -p tcp --dport xx -j ACCEPT # xx为端口号

# 临时生效
iptables-save

# 永久生效
sudo apt-get install iptables-persistent
sudo netfilter-persistent save
sudo netfilter-persistent reload
```



### SIGPIPE问题

**问题**

进程写套接字时自动终止。

**原因**

1. 当服务器close一个连接时，若client端接着发数据。根据TCP协议的规定，会收到一个RST响应。当进程向某个已收到RST的套接字执行写操作时，内核向该进程发送一个SIGPIPE信号。该信号的默认行为是终止进程，因此进程必须捕获它以免不情愿地被终止。不论该进程是捕获了该信号并从其信号处理函数返回，还是简单地忽略该信号，写操作都将返回EPIPE错误。

**解决**

1. 捕获SIGPIPE信号

   ```c++
   TODO
   ```

2. 忽略SIGPIPE信号

   ```c++
   signal(SIGPIPE, SIG_IGN);
   ```
