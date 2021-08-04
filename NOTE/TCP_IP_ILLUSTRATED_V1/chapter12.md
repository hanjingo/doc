[TOC]

# 第十二章 TCP 传输控制协议



## ARQ和重传

ARQ(Automatic Repeat Request，自动重复请求)

ACK(acknowledgment， 确认)

### 分组窗口和滑动窗口

滑动窗口协议（sliding window protocol）示意：

![12-1](res/12-1.png)

### 变量窗口：流量控制和拥塞控制

流量控制（flow control）：在接收方跟不上时会强迫发送方慢下来，一共有2种方法：

- 基于速率（rate-based）流量控制

  给发送方指定某个速率，同时确保数据永远不能超过这个速率发送，适用于流应用程序。

- 基于窗口（windows-based）流量控制

  使用滑动窗口，窗口大小不是固定的，而是允许随时间而变动的；发送方使用**窗口通告(window advertisement)或窗口更新(window update)**调整窗口大小。

### 设置重传超时

RTT(round-trip-time estimation， 往返时间估计)



## TCP的引入

### TCP服务模型

TCP提供了一种*面向连接的(connection-oriented)，可靠的*字节流服务。

### 

## TCP头部和封装

TCP在IP数据报中的封装：

![12-2](res/12-2.png)

TCP头部结构：

![12-3](res/12-3.png)

- `源端口` (16bit)

  与IP头部中的源地址组合成一个端点(endpoint)，用于唯一标识发送方。

- `目的端口` (16bit)

  与IP头部中的目的地址组合成一个端点(endpoint)，用于唯一标识接收方。

- `序列号` (32bit)

  Sequence Number，标识TCP发送端到TCP接收端的数据流的一个字节，该字节代表着包含该序列号的报文段的数据中的第一个字节。

- `确认号` (32bit)

  Acknowledgment Number，发送方期待接收的下一个序列号。

- `头部长度` (4bit)

  定义了头部的长度，长度单位为字（32bit）；TCP头部被限制为60字节，不带选项的TCP头部大小为20字节。

- `保留字段`(4bit)

- `CWR`(1bit) 缩小拥塞窗口

  发送方用来降低它的发送速率

- `ECE`(1bit) ECN回显

  发送方收到了一个更早的拥塞通告

- `URG`(1bit) 紧急

  让`紧急指针`生效，很少使用

- `ACK`(1bit) 确认

  让`确认号字段`生效，建立连接后启用

- `PSH`(1bit) 推送

- `RST`(1bit) 重置连接 

- `SYN`(1bit) 初始化同步序号

- `FIN`(1bit) 发送数据结束

- `窗口大小`(16bit)

  用来通告窗口大小（单位：字节数，最大65535字节），实现流量控制

- `TCP校验和`(16bit)

  强制性的，由发送方进行计算和保存，由接收方验证。

- `紧急指针`(16bit)

  Urgent Pointer，只有当`URG`字段被设置时生效；

- `选项`(变长)