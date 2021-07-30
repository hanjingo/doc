[TOC]

# TCP协议



## 状态转移

![tcp_stat](res/tcp_stat.png)

### TIME_WAIT状态

TIME_WAIT状态有2个存在的理由:

- 可靠地实现TCP全双工连接的终止；
- 允许老的重复分节在网络中消逝；

#### TIME_WAIT过多怎么处理

