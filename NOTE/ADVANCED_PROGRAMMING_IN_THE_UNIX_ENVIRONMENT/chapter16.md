# 第十六章 网络IPC：套接字

[TOC]



## 16.1 引言



## 16.2 套接字描述符

```c++
#include <sys/socket.h>
int socket(int domain, int type, int protocol);
```

- `domain` 域

  | 域        | 描述           |
  | --------- | -------------- |
  | AF_INET   | IPv4因特网域。 |
  | AF_INET6  | IPv6因特网域。 |
  | AF_UNIX   | UNIX域。       |
  | AF_UPSPEC | 未指定。       |

- `type` 套接字类型

  | 类型           | 描述                                             |
  | -------------- | ------------------------------------------------ |
  | SOCK_DGRAM     | 固定长度的，无连接的，不可靠的报文传递。         |
  | SOCK_RAW       | IP协议的数据报接口。                             |
  | SOCK_SEQPACKET | 固定长度的，有序的，可靠的，面向连接的报文传递。 |
  | SOCK_STREAM    | 有序的，可靠的，双向的，面向连接的字节流。       |

- `protocol` 协议

  | 协议         | 描述                                     |
  | ------------ | ---------------------------------------- |
  | IPPROTO_IP   | IPv4网际协议                             |
  | IPPROTO_IPV6 | IPv6网际协议                             |
  | IPPROTO_ICMP | 因特网控制报文协议                       |
  | IPPROTO_RAW  | 原始IP数据包协议                         |
  | IPPROTO_TCP  | 传输控制协议                             |
  | IPPROTO_UDP  | 用户数据报协议（User Datagram Protocol） |

- `返回值`

  - 成功：文件描述符
  - 失败：-1

*创建一个套接字*

![16_4](res/16_4.png)

*文件描述符函数使用套接字时的行为*

```c++
#include <sys/socket.h>
int shutdown(int sockfd, int how);
```

- `sockfd` 套接字

- `how` 动作

  | how值     | 说明     |
  | --------- | -------- |
  | SHUT_RD   | 关闭读   |
  | SHUT_WR   | 关闭写   |
  | SHUT_RDWR | 关闭读写 |

- `返回值`

  - 成功：0
  - 失败：-1

*关闭一个套接字的I/O*



## 16.3 寻址

### 16.3.1 字节序

![16_5](res/16_5.png)

大端（big-endian）：最大字节地址出现在最低有效字节（Least Significant Byte, LSB）上。

小端（little-endian）：最小字节地址出现在最高有效字节（Most Significant Byte, MSB）上。

![16_6](res/16_6.png)

*测试平台的字节序*

```c++
#include <arpa/inet.h>
uint32_t htonl(uint32_t hostint32); // 主机字节序转网络字节序
uint16_t htons(uint16_t hostint16); // 主机字节序转网络字节序
uint32_t ntohl(uint32_t netint32);  // 网络字节序转主机字节序
uint16_t ntohs(uint16_t netint16);  // 网络字节序转主机字节序
```

*字节序转换函数*

### 16.3.2 地址格式

```c++
#include <arpa/inet.h>
const char *inet_ntop(int domain, const void *restrict addr, 
                      char *restrict str, socklen_t size);
```

- `domain` 域（仅支持`AF_INET`和`AF_INET6`）

- `addr` 网络字节序地址

- `str` 文本字符串地址

- `size` 文本字符串长度；

- `返回值`

  成功：地址字符串指针

  失败：NULL

*将网络字节序的二进制地址转换为文本字符串地址*

```c++
#include <arpa/inet.h>
int inet_pton(int domain, const char *restrict str, void *restrict addr);
```

- `domain 域（仅支持`AF_INET`和`AF_INET6`）`

- `str` 文本字符串地址

- `addr` 网络字节序地址

- `返回值`

  成功：1

  格式无效：0

  出错：-1

*将文本字符串地址转换为网络字节序的二进制地址*

### 16.3.3 地址查询

```c++
#include <netdb.h>
struct hostent *gethostent(void);
void sethostent(int stayopen);
void endhostent(void)
```

- `stayopen` 

- `返回值`

  成功：指针

  失败：NULL

*返回/设置/关闭 主机数据文件信息*

```c++
#include <netdb.h>
struct netent *getnetbyaddr(uint32_t net, int type);
struct netent *getnetbyname(const char *name);
struct netent *getnetent(void);
void setnetent(int stayopen);
void endnetent(void);
```

- `net`

- `type` 地址类型（地址族常量）

- `name` 

- `返回值`

  成功：netent指针

  失败：NULL

*获得/设置/关闭 网络名字和网络号文件信息*

```c++
#include <netdb.h>
struct protoent *getprotobyname(const char *name);
struct protoent *getprotobynumber(int proto);
struct protoent *getprotoent(void);
void setprotoent(int stayopen);
void endprotoent(void);
```

- `name` 协议名字

- `proto` 协议号

- `返回值`

  成功：protoent指针

  失败：NULL

*映射协议名字和协议号*

```c++
#include <netdb.h>
struct servent *getservbyname(const char *name, const char *proto);
struct servent *getservbyport(int port, const char *proto);
struct servent *getservent(void);
void setservent(int stayopen);
void endservent(void);
```

- `name` 协议名字

- `proto` 协议号

- `port` 端口号

- `返回值`

  成功：指针

  失败：NULL

*映射端口到服务名*

```c++
#include <sys/socket.h>
#include <netdb.h>
int getaddrinfo(const char *restrict host,
                const char *restrict service,
                const struct addrinfo *restrict hint,
                struct addrinfo **restrict res);
```



