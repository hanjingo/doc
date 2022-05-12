# 第二十四章 带外数据

[TOC]



## 24.1 概述



## 24.2 TCP带外数据

![24_1](res/24_1.png)

*含有待发送数据的套接字发送缓冲区*

![24_2](res/24_2.png)

*应用进程写入1字节带外数据后的套接字发送缓冲区*

### 24.2.1 使用SIGURG的简单例子

```c++
TODO
```

*oob/tcpsend01.c*

```c++
TODO
```

*oob/tcprecv01.c*

### 24.2.2 使用select的简单例子

```c++
TODO
```

*oob/tcprecv02.c*

```c++
TODO
```

*oob/tcprecv03.c*



## 24.3 sockatmark函数

```c++
#include <sys/socket.h>
int sockatmark(int sockfd);
```

- `sockfd`套接字描述符
- `返回值`
  - 1：处于带外标记
  - 0：不处于带外标记
  - -1：失败

*确定套接字是否处于带外标记*

```c++
TODO
```

*lib/sockatmark.c*

### 24.3.1 例子

```c++
TODO
```

*oob/tcpsend04.c*

```c++
TODO
```

*oob/tcprecv04.c*

### 24.3.2 例子

```c++
TODO
```

*oob/tcpsend05.c*

```c++
TODO
```

*oob/tcprecv05.c*

### 24.3.3 例子

```c++
TODO
```

*oob/tcpsend06.c*



## 24.4 TCP带外数据小结



## 24.5 客户/服务器心搏函数

![24_13](res/21_13.png)

*使用带外数据的客户/服务器心搏机制*

```c++
TODO
```

*oob/heartbeatcli.c*

```c++
TODO
```

*oob/heartbeatserv.c*



## 24.6 小结

