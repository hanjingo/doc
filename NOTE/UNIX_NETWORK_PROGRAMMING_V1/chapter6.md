# 第六章 I/O复用：select和pool函数

- [概述](#概述)
- [`I/O模型`](#`I/O模型`)
- [同步`I/O`和异步`I/O`对比](#同步`I/O`和异步`I/O`对比)
- [select函数](#select函数)
- [`str_cli函数（修订版）`](#`str_cli函数（修订版）`)
- [shutdown函数](#shutdown函数)
- [`str_cli函数（再修订版）`](#`str_cli函数（再修订版）`)



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

- 接收缓冲区中的数据字节数大于等于套接字接收缓冲区低水位标记的当前大小
- 连接的读半部关闭（也就是接收了FIN的TCP连接）。对这样的套接字的读操作将不阻塞并返回0（也就是返回EOF）
- 是一个监听套接字且已完成的连接数不为0
- 其上有一个套接字错误待处理

套接字准备好写的条件（满足其一即可）：

- 发送缓冲区中的可用空间字节数大于等于发送缓冲区低水位标记的当前大小，并且或者该套接字已连接，或者该套接字不需要连接（如UDP套接字）
- 该连接的写半部关闭
- 使用非阻塞connect的套接字已建立连接，或者connect已经以失败告终
- 其上有一个套接字错误待处理

如果一个套接字春在带外数据或者仍处于带外标记，那么它有异常条件待处理。

**注意：当某个套接字上发生错误时，它将由select标记为即可读又可写。**

任何UDP套接字只要其发送低水位标记小于等于发送缓冲区大小（默认应该总是这种关系）就总是可写的，这是因为UDP套接字不需要连接。

select返回某个套接字就绪的条件：

| 条件                                                       | 可读？      | 可写？ | 异常？ |
| ---------------------------------------------------------- | ----------- | ------ | ------ |
| 有数据可读<br>关闭连接的读一半<br>给监听套接口准备好新连接 | Y<br>Y<br>Y |        |        |
| 有可用于写的空间<br>关闭连接的写一半                       |             | Y<br>Y |        |
| 待处理错误                                                 | Y           | Y      |        |
| TCP带外数据                                                |             |        | Y      |

### select的最大描述符数

select的最大描述符数定义在`<sys/types.h>`或`<sys/select.h>`中:

```c
#ifndef FD_SETSIZE
#define FD_SETSIZE 256
#endif
```



## str_cli函数（修订版）

![6-8](res/6-8.png)

客户的套接字上的三个条件处理如下：

1. 如果对端TCP发送数据，那么该套接字变为可读，并且read返回一个大于0的值（即读入数据的字节数）。
2. 如果对端TCP发送一个FIN（对端进程终止），那么该套接字变为可读，并且read返回0（EOF）。
3. 如果对端TCP发送一个RST（对端主机崩溃并重新启动），那么该套接字变为可读，并且read返回-1，而errno中含有确切的错误码。

使用select的str_cli函数的实现:

```c
#include "unp.h"
void
str_cli(FILE *fp, int sockfd)
{
    int 		maxfdp1;
    fd_set 	rset;
    char	  sendline[MAXLINE], recvline[MAXLINE];
    
    FD_ZERO(&rset);
    for ( ; ; ) {
        FD_SET(fileno(fp), &rset);
        FD_SET(sockfd, &rset);
        maxfdp1 = max(fileno(fp), sockfd) + 1;
        Select(maxfdp1, &rset, NULL, NULL, NULL);
        if (FD_ISSET(sockfd, &rset)) { /* socket is readable */
            if (Readline(sockfd, recvline, MAXLINE) == 0)
                err_quit("str_cli: server terminated prematurely");
            Fputs(recvline, stdout);
        }
        if (FD_ISSET(fileno(fp), &rset)) {	/* input is readable */
            if (Fgets(sendline, MAXLINE, fp) == NULL)
                return;
            Writen(sockfd, sendline, strlen(sendline));
        }
    }
}
```



## shutdown函数

头文件`sys/socket.h`

`int shutdown(int sockfd, int howto)`

- sockfd
- howto
    - SHUT_RD：关闭连接的读，丢弃接收缓冲区的数据
    - SHUT_WR：关闭连接的写，丢弃发送缓冲区的数据
    - SHUT_RDWR：关闭连接的读和写，类似于调用1次SHUT_RD，又调用1次SHUT——WR

使用close函数来终止网络连接时有两个限制：

1. close把描述符的引用计数减1，仅在该计数变为0时才关闭套接字
2. close会同时终止读和写两个方向的数据传送

可以使用shutdown来避免上述限制，调用shutdown关闭一半TCP连接：

![6-12](res/6-12.png)



## `str_cli函数（再修订版）`

```c
#include "unp.h"
void
str_cli(FILE *fp, int sockfd)
{
    int maxfdp1, stdineof;
    fd_set rset;
    char buf[MAXLINE];
    int n;
    stdineof = 0;
    FD_ZERO(&rset);
    for ( ; ; ) {
        if (stdineof == 0)
            FD_SET(fileno(fp), &rset);
        FD_SET(sockfd, &rset);
        maxfdp1 = max(fileno(fp), sockfd) + 1;
        Select(maxfdp1, &rset, NULL, NULL, NULL);
        if (FD_ISSET(sockfd, &rset)) {	/* socket is readable */
            if ( (n = Read(sockfd, buf, MAXLINE)) == 0 ) {
                if (stdineof == 1)
                    return;
                else
                    err_quit("str_cli: server terminated prematurely");
            }
            Write(fileno(stdout), buf, n);
        }
        if (FD_ISSET(fileno(fp), &rset)) {	/* input is readable */
            if ( (n = Read(fileno(fp), buf, MAXLINE)) == 0 ) {
                stdineof = 1;
                Shutdown(sockfd, SHUT_WR);	/* send FIN */
                FD_CLR(fileno(fp), &rset);
                continue;
            }
            Writen(sockfd, buf, n);
        }
    }
}
```

