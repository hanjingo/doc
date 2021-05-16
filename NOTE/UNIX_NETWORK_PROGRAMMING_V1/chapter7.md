# 第七章 套接字选项



## 概述



## getsockopt和setsockopt函数

头文件`sys/socket.h`

`int getsockopt(int sockfd, int level, int optname, void *optval, socklen_t *optlen)`

- sockfd：套接字
- level：级别，指定系统中解释选项的代码或为通用套接字代码，或为某个特定于协议的代码
- optname
- optval：
- optlen
- return

获得套接字选项

`int setsockopt(int sockfd, int level, int optname, const void *optval, socklen_t optlen)`

- sockfd
- level
- optname
- optval
- optlen

设置套接字选项

传输层的套接字选项汇总