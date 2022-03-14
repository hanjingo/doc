# TCP协议

[TOC]

## 术语

- ARQ(Automatic Repeat Request，自动重复请求)

- ACK(acknowledgment， 确认)

- RTT(round-trip-time estimation， 往返时间估计)



## 头部

![tcp_head](res/tcp_head.png)

- `源端口` 与IP头部中的源地址组合成一个端点(endpoint)，用于唯一标识发送方。

- `目的端口` 与IP头部中的目的地址组合成一个端点(endpoint)，用于唯一标识接收方。

- `序列号` Sequence Number，标识TCP发送端到TCP接收端的数据流的一个字节，该字节代表着包含该序列号的报文段的数据中的第一个字节。

- `确认号` Acknowledgment Number，发送方期待接收的下一个序列号。

- `头部长度` 定义了头部的长度，长度单位为字（32bit）；TCP头部被限制为60字节，不带选项的TCP头部大小为20字节。

- `保留字段`

- `CWR` 缩小拥塞窗口，发送方用来降低它的发送速率

- `ECE` ECN回显，发送方收到了一个更早的拥塞通告

- `URG` 紧急，让`紧急指针`生效，很少使用

- `ACK` 确认，让`确认号字段`生效，建立连接后启用

- `PSH` 推送

- `RST` 重置连接 

- `SYN` 初始化同步序号

- `FIN` 发送数据结束

- `窗口大小` 用来通告窗口大小（单位：字节数，最大65535字节），实现流量控制

- `TCP校验和` 强制性的，由发送方进行计算和保存，由接收方验证。

- `紧急指针` Urgent Pointer，只有当`URG`字段被设置时生效；

- `选项`(变长)

  | 种类 | 长度 | 名称           | 描述与目的                       |
  | ---- | ---- | -------------- | -------------------------------- |
  | 0    | 1    | EOL            | 选项列表结束                     |
  | 1    | 1    | NOP            | 无操作（用于填充）               |
  | 2    | 4    | MSS            | 最大段大小                       |
  | 3    | 3    | WSOPT          | 窗口缩放因子（窗口左移量）       |
  | 4    | 2    | SACK-Permitted | 发送者支持SACK选项               |
  | 5    | 可变 | SACK           | SACK阻塞（接收到乱序数据）       |
  | 8    | 10   | TSOPT          | 时间戳选项                       |
  | 28   | 4    | UTO            | 用户超时（一段空闲时间后的终止） |
  | 29   | 可变 | TCP-AO         | 认证选项（使用多种算法）         |
  | 253  | 可变 | Experimental   | 保留供实验所用                   |
  | 254  | 可变 | Experimental   | 保留供实验所用                   |




## 滑动窗口

![tcp_sliding_window](res/tcp_sliding_window.png)

*发送方窗口，显示了哪些分组将要被发送（或已经发送），哪些尚未发送，以及哪些已经发送并确认。在这个例子里，窗口大小被确定为三个分组*



## 连接的建立与终止

![tcp_start_end](res/tcp_start_end.png)

*一个普通TCP连接的建立与终止。通常，由客户端负责发起一个三次握手过程。在该过程中，客户端与服务器利用SYN报文段交换彼此的初始序列号（包括客户端的初始序列号和服务器的初始序列号）。在通信双方都发送了一个FIN数据包并收到来自对方的相应的确认数据包后，该连接终止*

### 半关闭

![tcp_half_close](res/tcp_half_close.png)

*在TCP半关闭操作中，连接的一个方向被关闭，而另一个方向仍在传输数据直到它被关闭为止；（很少有应用程序使用这一特性）*

### 同时打开与关闭

![tcp_open_closea](res/tcp_open_closea.png)

*在同时打开中交换的报文段。与正常的连接建立过程相比，需要增加一个报文段。数据报的SYN位将置位直到接收到一个ACK数据包为止*

![tcp_open_closeb](res/tcp_open_closeb.png)

*在同时关闭中交换的报文段。与正常关闭相似，指示报文段的顺序是交叉的*



## 状态转移

![tcp_stat](res/tcp_stat.png)



### TIME_WAIT

TIME_WAIT状态有2个存在的理由:

- 可靠地实现TCP全双工连接的终止；
- 允许老的重复分节在网络中消逝；

TIME_WAIT过多怎么处理？

### 时间等待错误

`时间等待错误（TIME-WAIT Assassination, TWA）` 如果在`TIME_WAIT`状态下接收到来自于这条连接的一些报文段，或是更加特殊的重置报文段，它将会被破坏；

![tcp_time_wait_err](res/tcp_time_wait_err.png)



## 参考

[1] [美] Kevin R. Fall, [美] W. Richard Stevens.Tcp/ip详解.3ED

