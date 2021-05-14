# 第六章 I/O复用：select和pool函数

- [概述](#概述)
- [`I/O模型`](#`I/O模型`)
- [同步`I/O`和异步`I/O`对比](#同步`I/O`和异步`I/O`对比)
- [select函数](#select函数)



## 概述

I/O复用典型使用在下列网络应用场合：

- 当客户处理多个描述符（通常是胡教师输入和网络套接字）时，必须使用I/O复用
- 一个客户同时处理多个套接字是可能的，不过比较少见
- 如果一个服务器即要处理TCP，又要处理UDP，一般就要使用I/O复用
- 如果一个服务器要处理多个服务或者多个协议，一般就要使用I/O复用



## `I/O模型`

Unix下可用的5种I/O模型：

- 阻塞式I/O

    ![6-1](res/6-1.png)

- 非阻塞式I/O

    ![6-2](res/6-2.png)

- I/O复用（select和poll）

    ![6-3](res/6-3.png)

- 信号驱动式I/O（SIGIO）

    ![6-4](res/6-4.png)

- 异步I/O（POSIX的aio_系列函数）

    ![6-5](res/6-5.png)

前4种模型的主要区别在于第一阶段，因为他们的第二阶段是一样的：在数据从内核复制到调用者的缓冲区期间，进程阻塞于recvfrom调用。相反，异步`I/O`模型在这两个阶段都要处理，从而不同于其他4种模型。

### 同步`I/O`和异步`I/O`对比

- 同步`I/O`操作（synchronous I/O opetation）导致请求进程阻塞，直到`I/O`操作完成。
- 异步`I/O`操作（asynchronous I/O opetation）不导致请求进程阻塞。

![6-6](res/6-6.png)



## select函数

头文件`sys/select.h`

`int select(int maxfdp1, fd_set *readset, fd_set *writeset, fd_set *exceptset, const struct timeval *timeout)`

- maxfdp1：指定待测试的描述符个数
- readset：让内核测试读描述符
- writeset：让内核测试写描述符
- exceptset：让内核测试异常描述符
- timeout：超时时间（精确度10ms左右）
    - 永远等待下去：值为空
    - 等待一段固定时间：值非空
    - 根本不等待：值为0
- return
    - 有就绪描述符：返回描述符数量
    - 超时：0
    - 出错：-1

允许进程指示内核等待多个事件中的任何一个发生，并只在有一个或多个时间发生或经历一段指定的时间后才唤醒它。

目前支持的异常条件只有两个：

- 某个套接字的带外数据的到达
- 某个已置为分组模式的伪终端存在可从其主端读取的控制状态信息

设置fd的常用函数：

```c
void FD_ZERO(fd_set *fdset);
void FD_SET(int fd, fd_set *fdset);
void FD_CLR(int fd, fd_set *fdset);
int	   FD_ISSET(int fd, fd_set *fdset);
```

### 描述符就绪条件

套接字准备好读的条件（满足其一即可）：

- 该套接字接收缓冲区中的数据字节数大于等于套接字接收缓冲区低水位标记的当前大小。
- 该连接的读半部关闭（也就是接收了FIN的TCP连接）。对这样的套接字的读操作将不阻塞并返回0（也就是返回EOF）。