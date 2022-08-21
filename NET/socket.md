# 套接字

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

### 地址传递

1. 从进程到内核传递套接字地址结构的函数
   - `bind`
   - `connect`
   - `sendto`
2. 从内核到进程传递套接字地址结构的函数
   - `accept`
   - `recvfrom`
   - `getsockname`
   - `getpeername`

### 地址转换

![sockaddr_trans](res/sockaddr_trans.png)

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

### 套接字常见错误

| 错误                      | 说明                                                         |
| ------------------------- | ------------------------------------------------------------ |
| EADDRINUSE                | Address already in use，地址已使用                           |
| ECONNREFUSED              | 这是一种**硬错误（hard error）**。若对客户的SYN的响应是RST（表示复位），则表明该服务器主机在我们指定的端口上没有进程在等待与之连接。客户一接收到RST就马上返回ECONNREFUSED错误。RST是TCP在发生错误时发送的一种TCP分节。产生RST的三个条件：<br>  1.目的地为某端口的SYN到达，然而该端口上没有正在监听的服务器<br>  2.TCP想取消一个已有连接<br>  3.TCP接收到一个根本不存在的连接上的分节 |
| ETIMEDOUT                 | TCP客户没有收到SYN分节的响应。                               |
| `distination unreachable` | 这是一种**软错误（soft error）**。客户主机内核保存该消息，并按第一种情况中所述的时间间隔继续发送SYN。若在某个规定的时间（4.4BSD规定75s）后仍未收到响应，则把保存的消息（即ICMP错误）作为EHOSTUNREACH或ENETUNREACH错误返回给进程。以下两种情形也是有可能的：<br>  1.按照本地系统的转发表，根本没有到达远程系统的路径。<br>  2.connect调用根本不等待就返回。 |



## 参考

TODO