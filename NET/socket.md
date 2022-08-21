# 套接字编程

[TOC]



## 套接字地址

### 通用Unix套接字地址

```c++
#include <netinet/in.h>
struct sockaddr_storage {
    uint8_t     ss_len;
    sa_family_t ss_family;
};
```

### Unix IPv4套接字地址

```c++
#include <netinet/in.h>
struct in_addr {
    in_addr_t s_addr;           // 至少32位无符号整数类型
};
struct sockaddr_in {
    uint8_t         sin_len;    // 长度字段
    sa_family_t     sin_family; // 地址族; 任何无符号整数类型
    in_port_t       sin_port;   // TCP或UDP端口; 至少16位的无符号整数类型 
    struct in_addr  sin_addr;
    char		   sin_zero[8];
};
```

### Unix IPv6套接字地址

```c++
#include <netinet/in.h>
struct in6_addr {
    uint8_t s6_addr[16];
};
#defie SIN6_LEN
struct sockaddr_in6 {
    uint8_t          sin6_len;
    sa_family_t      sin6_family;
    in_port_t      	 sin6_port;
    uint32_t         sin6_flowinfo;
    struct in6_addr  sin6_addr;
    uint32_t         sin6_scope_id;
}
```

### 地址转换

#### 地址传递

1. 从进程到内核传递套接字地址结构的函数
   - `bind`
   - `connect`
   - `sendto`
2. 从内核到进程传递套接字地址结构的函数
   - `accept`
   - `recvfrom`
   - `getsockname`
   - `getpeername`

#### 格式转换

![sockaddr_trans](res/sockaddr_trans.png)

#### 名字与地址转换

TODO

#### IPv4与IPv6互操作

TODO

### 不同套接字地址的比较

![sockaddr_compare](res/sockaddr_compare.png)



## 套接字函数

![sock_usage](res/sock_usage.png)

### socket

```c++
#include <sys/socket.h>
int socket(int family, int type, int protocol)
```

- `family` 协议族

  | family   | 说明       |
  | -------- | ---------- |
  | AF_INET  | IPv4协议   |
  | AF_INET6 | IPv6协议   |
  | AF_LOCAL | Unix域协议 |
  | AF_ROUTE | 路由套接字 |
  | AF_KEY   | 密钥套接字 |

- `type` 套接字类型

  | type           | 说明           |
  | -------------- | -------------- |
  | SOCK_STREAM    | 字节流套接字   |
  | SOCK_DGRAM     | 数据报套接字   |
  | SOCK_SEQPACKET | 有序分组套接字 |
  | SOCK_RAW       | 原始套接字     |

- `protocol` 协议类型

  | protocol     | 说明         |
  | ------------ | ------------ |
  | IPPROTO_TCP  | TCP传输协议  |
  | IPPROTO_UDP  | UDP传输协议  |
  | IPPROTO_SCTP | SCTP传输协议 |

 - `返回值`

   成功：套接字描述符（非负）

   失败：-1

*创建套接字，返回套接字描述符*

|                | AF_INET    | AF_INET6   | AF_LOCAL | AF_ROUTE | AF_KEY |
| -------------- | ---------- | ---------- | -------- | -------- | ------ |
| SOCK_STREAM    | `TCP/SCTP` | `TCP/SCTP` | 是       |          |        |
| SOCK_DGRAM     | UDP        | UDP        | 是       |          |        |
| SOCK_SEQPACKET | SCTP       | SCTP       | 是       |          |        |
| SOCK_RAW       | IPv4       | IPv6       |          | 是       | 是     |

*套接字`family`与`type`可能的组合*

### connect

```c++
#include <sys/socket.h>
int connect(int sockfd, const struct sockaddr *servaddr, socklen_t addrlen)
```

- `sockfd` 套接字描述符

- `servaddr` 指向套接字的地址

- `addrlen` 套接字地址长度

- `返回值`

  成功：0

  失败：-1

*建立与TCP服务器的连接*

#### 非阻塞式connect

TODO

### bind

```c++
#include <sys/socket.h>
int bind(int sockfd, const struct sockaddr *myaddr, socklen_t addrlen)
```

- sockfd` 套接字

- `myaddr` 指向特定于协议的地址结构的指针

- `addrlen` 该地址结构的长度

- `返回值`

  成功：0

  失败：-1

*绑定地址（把一个本地协议地址赋予一个套接字）*

### listen

```c++
#include <sys/socket.h>
int listen(int sockfd, int backlog);
```

- `sockfd` 套接字

- `backlog` 待处理的套接字队列的最大长度

- `返回值`

  成功：0

  失败：-1

*监听套接字（把一个未连接的套接字转化为一个被动套接字，指示内核应接受指向该套接字的连接请求，同时设定排队的套接字队列的最大长度）*

### accept

```c++
#include <sys/socket.h>
int accept(int sockfd, struct sockaddr *cliaddr, socklen_t *addrlen);
```

- `sockfd` 监听套接字

- `cliaddr` 返回已连接的协议地址

- `addrlen` 返回已连接的协议地址长度

- `返回值`

  成功：一个全新的描述符

  失败：错误码

*接受连接（从已完成连接队列头返回下一个已完成连接，如果已完成连接队列为空，那么进程被投入睡眠）*

#### 非阻塞式accept

TODO

### close

```c++
#include <unistd.h>
int close(int sockfd);
```

- `sockfd` 套接字文件描述符

- `返回值`

  成功：0

  出错：-1

*将套接字标记为关闭，使它无法再被read或write调用*

### getsockname

```c++
#include <sys/socket.h>
int getsockname(int sockfd, struct sockaddr *localaddr, socklen_t *addrlen);
```

- `sockfd` 套接字文件描述符

- `localaddr` 本地协议地址

- `addrlen` 本地协议地址长度

- `返回值`

  成功：0

  失败：-1

*返回与套接字关联的本地协议地址*

### getpeername

```c++
#include <sys/socket.h>
int getpeername(int sockfd, struct sockaddr *peeraddr, socklen_t *addrlen);
```

- `sockfd` 套接字文件描述符

- `localaddr` 外地协议地址

- `addrlen` 外地协议地址长度

- `返回值`

  成功：0

  失败：-1

*返回与套接字关联的外地协议地址（getpeername）*

### shutdown

```c++
#include <sys/socket.h>
int shutdown(int sockfd, int howto);
```

- `sockfd`套接字文件描述符

- `howto`动作

  | 动作      | 说明                                                         |
  | --------- | ------------------------------------------------------------ |
  | SHUT_RD   | 关闭连接的读，丢弃接收缓冲区的数据。                         |
  | SHUT_WR   | 关闭连接的写，丢弃发送缓冲区的数据。                         |
  | SHUT_RDWR | 关闭连接的读和写，类似于调用1次`SHUT_RD`，又调用1次`SHUT_WR`。 |

- `返回值`

  成功：0

  失败：-1

*关闭连接*

### ioctl

TODO



## 套接字选项

### getsockopt

```c++
#include <sys/socket.h>
int getsockopt(int sockfd, int level, int optname, void *optval, socklen_t *optlen);
```

- `sockfd`：套接字

- `level`：级别，指定系统中解释选项的代码或为通用套接字代码，或为某个特定于协议的代码

- `optname`：opt名字

- `optval`：指向一个变量

- `optlen`：指定optval的大小

- 返回值

  成功：0

  出错：-1

*获得套接字选项*

### setsockopt

```c++
#include <sys/socket.h>
int setsockopt(int sockfd, int level, int optname, const void *optval, socklen_t optlen);
```

- `sockfd`：套接字
- `level`：级别，指定系统中解释选项的代码或为通用套接字代码，或为某个特定于协议的代码
- `optname`：opt名字
- `optval`：指向一个opt变量
- `optlen`：指定optval的大小
- 返回值
  - 成功：0
  - 出错：-1

*设置套接字选项*

### IP选项

TODO

### 套接字选项汇总

| level（级别）              | optname（选项名）                                            | 数据类型                                                     | 说明                                                         |
| -------------------------- | ------------------------------------------------------------ | :----------------------------------------------------------- | ------------------------------------------------------------ |
| SOL_SOCKET                 | SO_BROADCAST<br>SO_DEBUG<br>SO_DONTROUTE<br>SO_ERROR<br>SO_KEEPALIVE<br>SO_LINGER<br>SO_OOBINLINE<br>SO_RCVBUF<br>SO_SNDBUF<br>SO_RCVLOWAT<br>SO_SNDLOWAT<br>SO_RCVTIMEO<br>SO_SNDTIMEO<br>SO_REUSEADDR<br>SO_REUSEPORT<br>SO_TYPE<br>SO_USELOOPBACK | int<br>int<br>int<br>int<br>int<br>linger<br>int<br>int<br>int<br>int<br>int<br>timeval<br>timeval<br>int<br>int<br>int<br>int | - 允许发送广播数据报<br>- 开启调试跟踪<br>- 绕过外出路由表查询<br>- 获取待处理错误并清除<br>- 周期性测试连接是否仍存活<br>- 若有数据待发送则延迟关闭<br>- 让接收到的带外数据继续在线留存<br>- 接收缓冲区大小<br>- 发送缓冲区大小<br>- 接收缓冲区低水位标记<br>- 发送缓冲区低水位标记<br>- 接收超时<br>- 发送超时<br>- 允许重用本地地址<br>- 允许重用本地端口<br>- 取得套接字类型<br>- 路由套接字取得所发送数据的副本 |
| IPPROTO_IP                 | IP_HDRINCL<br>IP_OPTIONS<br>IP_RECVDSTANDDR<br>IP_RECVIF<br>IP_TOS<br>IP_TTL<br><br>IP_MULTICAST_IF<br>IP_MULTICAST_TTL<br>IP_MULTICAST_LOOP<br>IP_ADD_MEMBERSHIP<br>IP_DROP_MEMBERSHIP<br>IP_BLOCK_SOURCE<br>IP_UNBLOCK_SOURCE<br>IP_ADD_SOURCE_MEMBERSHIP<br>IP_DROP_SOURCE_MEMBERSHIP | int<br>(见正文)<br>int<br>int<br>int<br>int<br><br>in_addr{}<br>u_char<br>u_char<br>ip_mreq{}<br>ip_mreq{}<br>ip_mreq_source{}<br>ip_mreq_source{}<br>ip_mreq_source{}<br>ip_mreq_source{} | - 随数据包含的IP首部<br>- IP首部选项<br>- 返回目的IP地址<br>- 返回接收接口索引<br>- 服务类型和优先权<br>- 存活时间<br><br>- 指定外出接口<br>- 指定外出TTL<br>- 指定是否环回<br>- 加入多播组<br>- 离开多播组<br>- 阻塞多播组<br>- 开通多播组<br>- 加入源特定多播组<br>- 离开源特定多播组 |
| IPPROTO_ICMPV6             | ICMP6_FILTER                                                 | ivmp6_filter{}                                               | - 指定待传递的ICMPv6消息类型                                 |
| IPPROTO_IPV6               | IPV6_CHECKSUM<br>IPV6_DONTFRAG<br>IPV6_NEXTHOP<br>IPV6_PATHMTU<br>IPV6_RECVDSTOPTS<br>IPV6_RECVHOPLIMIT<br>IPV6_RECVHOPOPTS<br>IPV6_RECVPATHMTU<br>IPV6_RECVPKTINFO<br>IPV6_RECVRTHDR<br>IPV6_RECVTCLASS<br>IPV6_UNICAST_HOPS<br>IPV6_USE_MIN_MTU<br>IPV6_V60NLY<br>IPV6_XXX<br><br>IPV6_MULTICAST_IP<br>IPV6_MULTICAST_HOPS<br>IPV6_MULTICAST_LOOP<br>IPV6_JOIN_GROUP<br>IPV6_LEAVE_GROUP | int<br>int<br>sockaddr_in6{}<br>ip6_mtuinfo{}<br>int<br>int<br>int<br>int<br>int<br>int<br>int<br>int<br>int<br>int<br>(见正文)<br><br>u_int<br>int<br>u_int<br>ipv6_mreq{}<br>ipv6_mreq{} | - 用于原始套接字的校验和字段偏移<br>- 丢弃大的分组而非将其分片<br>- 指定下一跳地址<br>- 获取当前路径MTU<br>接收目的地址选项<br>- 接收单播跳限<br>- 接收步跳选项<br>- 接收路径MTU<br>- 接收分组信息<br>- 接收源路径<br>- 接收流通类型<br>- 默认单播跳限<br>- 使用最小MTU<br>- 禁止v4兼容<br>- 粘附性辅助数据<br><br>- 指定外出接口<br>- 指定外出跳限<br>- 指定是否环回<br>- 加入多播组<br>- 离开多播组 |
| IPPROTO_IP<br>IPPROTO_IPV6 | MCAST_JOIN_GROUP<br>MCAST_LEAVE_GROUP<br>MCAST_BLOCK_SOURCE<br>MCAST_UNBLOCK_SOURCE<br>MCAST_JOIN_SOURCE_GROUP<br>MCAST_LEAVE_SOURCE_GROUP | group_req{}<br>group_source_req{}<br>group_source_req{}<br>group_source_req{}<br>group_source_req{}<br>group_source_req{} | - 加入多播组<br>- 离开多播组<br>- 阻塞多播源<br>- 开通多播源<br>- 加入源特定多播组<br>- 离开源特定多播组 |

传输层的套接字选项汇总：

| level（级别） | optname（选项名）                                            | 数据类型   | 说明                                                         |
| ------------- | ------------------------------------------------------------ | ---------- | ------------------------------------------------------------ |
| IPPROTO_TCP   | TCP_MAXSEG<br>TCP_NODELAY                                    | int<br>int | - TCP最大分节大小<br>- 禁止Nagle算法                         |
| IPPROTO_SCTP  | SCTP_ADAPTION_LAYER<br>SCTP_ASSOCINFO<br>SCTP_AUTOCLOSE<br>SCTP_DEFAULT_SEND_PARAM<br>SCTP_DISABLE_FRAGMENTS<br>SCTP_EVENTS<br>SCTP_GET_PEER_ADDR_INFO<br>SCTP_I_WANT_MAPPED_V4_ADDR<br>SCTP_INITMSG<br>SCTP_MAXBURST<br>SCTP_MAXSEG<br>SCTP_NODELAY<br>SCTP_PEER_ADDR_PARAMS<br>SCTP_PRIMARY_ADDR<br>SCTP_RTOINFO<br>SCTP_SET_PEER_PRIMARY_ADDR<br>SCTP_STATUS |            | - 适配层指示<br>- 检查并设置关联信息<br>- 自动关闭操作<br>- 默认发送参数<br>- SCTP分片<br>- 感兴趣事件的通知<br>- 获取对端地址状态<br>- 映射的v4地址<br>- 默认的INIT参数<br>- 最大猝发大小<br>- 最大分片大小<br>- 禁止Nagle算法<br>- 对端地址参数<br>- 主目的地址<br>- RTO信息<br>- 对端的主目的地址<br>- 获取关联状态 |



## UDP套接字编程

TODO

### 广播

TODO

### 多播

TODO



## TCP套接字编程

TODO

### 带外数据

TODO



## SCTP套接字编程

TODO



## 原始套接字编程

TODO



## 数据链路层访问

TODO



## 异常处理

### 错误汇总

| 错误                      | 说明                                                         |
| ------------------------- | ------------------------------------------------------------ |
| EADDRINUSE                | Address already in use，地址已使用                           |
| ECONNREFUSED              | 这是一种**硬错误（hard error）**。若对客户的SYN的响应是RST（表示复位），则表明该服务器主机在我们指定的端口上没有进程在等待与之连接。客户一接收到RST就马上返回ECONNREFUSED错误。RST是TCP在发生错误时发送的一种TCP分节。产生RST的三个条件：<br>  1.目的地为某端口的SYN到达，然而该端口上没有正在监听的服务器<br>  2.TCP想取消一个已有连接<br>  3.TCP接收到一个根本不存在的连接上的分节 |
| ETIMEDOUT                 | TCP客户没有收到SYN分节的响应。                               |
| `distination unreachable` | 这是一种**软错误（soft error）**。客户主机内核保存该消息，并按第一种情况中所述的时间间隔继续发送SYN。若在某个规定的时间（4.4BSD规定75s）后仍未收到响应，则把保存的消息（即ICMP错误）作为EHOSTUNREACH或ENETUNREACH错误返回给进程。以下两种情形也是有可能的：<br>  1.按照本地系统的转发表，根本没有到达远程系统的路径。<br>  2.connect调用根本不等待就返回。 |

### 超时处理

TODO



## 总结

TODO



## 参考

[1] (美)W.Richard Stevens, (美)Bill Fenner, (美)Andrew M Rudoff . Unix网络编程 卷一:套接字联网api . 3th Edition