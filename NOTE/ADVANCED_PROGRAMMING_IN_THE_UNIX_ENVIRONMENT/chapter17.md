# 第十七章 高级进程间通信

[TOC]



## 17.1 引言



## 17.2 UNIX域套接字

```c++
#include <sys/socket.h>
int socketpair(int domain, int type, int protocol, int sockfd[2]);
```

- `domain` 域
- `type`
- `protocol`
- `sockfd`
- `返回值`
  - 成功：0
  - 失败：-1

*创建一对无命名的，相互连接的UNIX域套接字*

![17_1](res/17_1.png)

*套接字对*

例：

```c++
TODO
```

*创建一个全双工管道*

例：

```c++
TODO
```

*使用UNIX域套接字轮询XSI消息队列*

```c++
TODO
```

*给XSI消息队列发送消息*

例：

```c++
TODO
```

*将地址绑定到UNIX域套接字*

