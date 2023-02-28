# 第十章 POSIX Socket API:本地通信



## 10.1 Echo Local Activity布局



## 10.2 Echo Local Activity



## 10.3 实现原生本地Socket Server

### 10.3.1 创建本地Socket: socket

### 10.3.2 将本地socket与Name绑定：bind

本地socket协议地址由`sockaddr_un`结构来指定，其结构定义如下：

```c++
struct sockaddr_un {
    sa_family_t sun_family;
    char sun_path[UNIX_PATH_MAX];
};
```

local socket协议地址只由一个名字构成。它没有IP地址或者端口号，可以在两个不同的命名空间中创建本地socket名：

- Abstract namespace：在本地socket通信协议模块中维护，socket名以NULL字符为前缀以绑定socket名。
- Filesystem namespace：通过文件系统以一个特殊socket文件的形式维护，socket名直接传递给sockaddr_un结构，将socket名与socket绑定。

### 10.3.3 接受本地Socket: accept

### 10.3.4 原生本地Socket Server



## 10.4 将本地Echo Activity添加到Manifest中



## 10.5 运行本地Sockets示例



## 10.6 异步I/O

socket通过select函数提供异步I/O。如要使用select函数，需要先包含头文件：

```c++
#include <sys/select.h>
```

select函数定义如下：

```c++
int select(int nfds, fd_set* readfds, fd_set* writefds, fd_set* exceptfds, struct timeval* timeout);
```

- `nfds`：为最高编号的描述加1，select函数将监控nfds指定数量的描述符。
- `readfds`：设置将被监控可读性的描述符列表集。
- `writefs`：设置将被监控可写性的描述符列表集。
- `exceptfds`：设置将被监控任何类型错误的描述符列表集。
- `timeout`：指定为了完成选择而阻塞当前进程的最大时间间隔。如果不需要，将其值设置为NULL。

如果选择成功，select函数返回就绪的描述符数，否则返回-1，同时将errno设置为相应的错误。

select函数的描述符列表通过`fd_set`结构提供。

```c++
struct fd_set readfds;
```

为了处理manipulate描述符列表，需要提供下面的宏集合：

- `FD_ZERO`宏：保存指向`fd_set`结构的指针并清除它。
- `FD_SET`宏：保存指向`fd_set`结构的指针并将描述符添加到集合中。
- `FD_CLR`宏：保存指向`fd_set`结构的指针并从集合中删除描述符。
- `FD_ISSET`宏：可以在选择完成后用来检查描述符是否为选择函数返回的集合的一部分。



## 10.7 小结

