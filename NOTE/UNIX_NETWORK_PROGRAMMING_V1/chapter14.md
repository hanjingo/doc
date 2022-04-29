# 第14章 高级I/O函数

[TOC]



## 14.1 概述



## 14.2 套接字超时

设置套接字I/O操作超时的方法：

- 调用alarm，在指定超时期满时产生SIGALRM信号。
- 在select中阻塞等待I/O，以此代替直接阻塞在read或write调用上。
- 使用较新的SO_RCVTIMEO和SO_SNDTIMEO套接字选项。

### 14.2.1 使用SIGALRM为connect设置超时

```c++
// 带超时的connect
#include "unp.h"
static void connect_alarm(int);
int connect_timeo(int sockfd, const SA *saptr, socklen_t salen, int nsec)
{
    Sigfunc *sigfunc;
    int n;
    sigfunc = Signal(SIGALRM, connect_alarm);
    if (alarm(nsec) != 0) // 设置报警时钟
        err_msg("connect_timeo: alarm was already set");
    if ((n = connect(sockfd, saptr, salen)) < 0) { // 调用connect
        close(sockfd);
        if (errno == EINTR)
            errno = ETIMEDOUT;
    }
    alarm(0); // 关闭本进程的报警时钟
    Signal(SIGALRM, sigfunc); // 恢复原来的信号处理函数不
    return (n);
}
static void connect_alarm(int signo)
{
    return;
}
```

### 14.2.2 使用SIGALRM为recvfrom设置超时

```c++
#include "unp.h"
static void sig_alrm(int);
void
dg_cli(FILE *fp, int sockfd, const SA *pservaddr, socklen_t servlen)
{
    int n;
    char sendline[MAXLINE], recvline[MAXLINE + 1];
    Signal(SIGALRM, sig_alrm); // 设置信号处理函数
    while (Fgets(sendline, MAXLINE, fp) != NULL) {
        Sendto(sockfd, sendline, strlen(sendline), 0, pservaddr, servlen);
        alarm(5); // 设置5秒超时
        if ((n = recvfrom(sockfd, recvline, MAXLINE, 0, NULL, NULL)) < 0) {
            if (errno == EINTR)
                fprintf(stderr, "socket timeout\n");
            else
                err_sys("recvfrom error");
        } else {
            alarm(0);
            recvline[n] = 0;
            Fputs(recvline, stdout);
        }
    }
}
static void
sig_alrm(int signo)
{
    return;
}
```

*使用alarm超时recvfrom的dg_cli函数*

### 14.2.3 使用select为recvfrom设置超时

```c++
#include "unp.h"
int
readable_timeo(int fd, int sec)
{
    fd_set rset;
    struct timeval tv;
    FD_ZERO(&rset);
    FD_SET(FD, &rset);
    tv.tv_sec = sec;
    tv.tv_usec = 0;
    return (select(fd+1, &rset, NULL, NULL, &tv)); // 出错：-1，超时：0
}
```

*readable_timeo函数：等待一个描述符变为可读*

```c++
#include "unp.h"
void
dg_cli(FILE *fp, int sockfd, const SA *pservaddr, socklen_t servlen)
{
    int n;
    char sendline[MAXLINE], recvline[MAXLINE + 1];
    while (Fgets(sendline, MAXLINE, fp) != NULL) {
        Sendto(sockfd, sendline, strlen(sendline), 0, pservaddr, servlen);
        if (Readable_timeo(sockfd, 5) == 0) {
            fprintf(stderr, "socket timeout\n");
        } else {
            n = Recvfrom(sockfd, recvline, MAXLINE, 0, NULL, NULL);
            recvline[n] = 0;
            Fputs(recvline, stdout);
        }
    }
}
```

*调用redable_timeo设置超时的dg_cli函数*

### 14.2.4 使用SO_RCVTIMEO套接字选项为recvfrom设置超时

```c++
#include "unp.h"
void 
dg_cli(FILE *fp, int sockfd, const SA *pservaddr, socklen_t servlen)
{
    int n;
    char sendline[MAXLINE], recvline[MAXLINE + 1];
    struct timeval tv;
    tv.tv_sec = 5;
    tv.tv_usec = 0;
    Setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));
    while (Fgets(sendline, MAXLINE, fp) != NULL) {
        Sendto(sockfd, sendline, strlen(sendline), 0, pservaddr, servlen);
        n = recvfrom(sockfd, recvline, MAXLINE, 0, NULL, NULL);
        if (n < 0) {
            if (errno == EWOULDBLOCK) { // I/O操作超时
                fprintf(stderr, "socket timeout\n");
                continue;
            } else
                err_sys("recvfrom error");
        }
        recvline[n] = 0;
        Fputs(recvline, stdout);
    }
}
```

*使用SO_RCVTIMEO套接字选项设置超时的dg_cli函数*



## 14.3 recv和send函数

```c++
#include <sys/socket.h>
ssize_t recv(int sockfd, void *buff, size_t nbytes, int flags);
ssize_t send(int sockfd, const void *buff, size_t nbytes, int flags);
```

- `flags`标志

  | flags         | 说明               | recv | send |
  | ------------- | ------------------ | ---- | ---- |
  | MSG_DONTROUTE | 绕过路由表查找     |      | Y    |
  | MSG_DONTWAIT  | 仅本操作非阻塞     | Y    | Y    |
  | MSG_OOB       | 发送或接收带外数据 | Y    | Y    |
  | MSG_PEEK      | 窥看外来消息       | Y    |      |
  | MSG_WAITALL   | 等待所有数据       | Y    |      |

  详细说明：

  - `MSG_DONTROUTE`告知内核目的主机在某个直接连接的本地网络上，因而无需执行路由表查找。

  - `MSG_DONTWAIT`在无需打开相应套接字的非阻塞标志的前提下，把单个I/O操作临时指定为非阻塞，接着执行I/O操作，然后关闭非阻塞标志。

  - `MSG_OOB`对于send，本标志指明即将发送带外数据；对于recv，本标志指明即将读入的是带外数据而不是普通数据。

  - `MSG_PEEK`适用于recv和recvfrom，它允许我们查看已可读取的数据，而且系统不在recv或recvfrom返回后丢弃这些数据。

  - `MSG_WAITALL`告知内核不要再尚未读入请求数目的字节之前让一个读操作返回。如果系统支持本标志，我们就可以省掉readn函数，替之以宏：

    ```c++
    #define readn(fd, ptr, n) recv(fd, ptr, n, MSG_WAITALL)
    ```

    即使指定了MSG_WAITALL，如果发生下列情况之一：

    1. 捕获一个信号；
    2. 连接被终止；
    3. 套接字发生一个错误，相应的读函数仍有可能返回比所请求字节数要少的数据。



## 14.4 readv和writev函数

```c++
#include <sys/uio.h>
ssize_t readv(int filedes, const struct iovec *iov, int iovcnt);
ssize_t writev(int filedes, const struct iovec *iov, int iovcnt);
```

- `filedes` 

- `iov`指向iovec结构数组的指针

  POSIX要求在头文件`<sys/uio.h>`中定义`IOV_MAX`常值来标识结构数组的容量，至少要为16；但是其实际值取决于具体实现：4.3BSD和Linux最多允许1024个，HP-UX最多允许2100个。

  iovec的定义如下：

  ```c++
  struct iovec {
      void *iov_base;
      size_t iov_len;
  }
  ```

- `iovcnt` iovec结构数组的元素数量

- `返回值`

  - 成功：读入/写出的字节数；
  - 失败：-1。

*读入/写出一个或多个缓冲区，这些操作分别称为`分散读（scatter read）`和`集中写（gather write）`，因为来自读操作的输入数据被分散到多个应用缓冲区中，而来自多个应用缓冲区的输出数据则被集中提供给单个写操作。*



## 14.5 recvmsg和sendmsg函数

```c++
#include <sys/socket.h>
ssize_t recvmsg(int sockfd, struct msghdr *msg, int flags);
ssize_t sendmsg(int sockfd, struct msghdr *msg, int flags);
```

- `sockfd`套接字

- `msg`

  ```c++
  struct msghdr {
      void         *msg_name;       // 接收者/发送者的协议地址
      socklen_t     msg_namelen;    // 协议地址长度
      struct iovec *msg_iov;        // 输入/输出缓冲区数组
      int           msg_iovlen;     // 缓冲区数组长度
      void         *msg_control;    // 辅助数据的位置（可选）
      socklen_t     msg_controllen; // 辅助数据的大小（可选）
      int           msg_flags;      // 消息标志
  };
  ```

- `flags`标志

  | 标志                                                         | 由内核检查send, sendto或sendmsg函数的flags参数 | 由内核检查recv, recvfrom或recvmsg函数的flags参数 | 由内核通过recvmsg函数的msg_flags结构参数成员返回 |
  | ------------------------------------------------------------ | ---------------------------------------------- | ------------------------------------------------ | ------------------------------------------------ |
  | MSG_DONTROUTE<br>MSG_DONTWAIT<br>MSG_PEEK<br>MSG_WAITALL     | Y<br>Y                                         | <br>Y<br>Y<br>Y                                  |                                                  |
  | MSG_EOR<br>MSG_OOB                                           | Y<br>Y                                         | <br>Y                                            | Y<br>Y                                           |
  | MSG_BCAST<br>MSG_MCAST<br>MSG_TRUNC<br>MSG_CTRUNC<br>MSG_NOTIFICATION |                                                |                                                  | Y<br>Y<br>Y<br>Y<br>Y                            |

  详细说明：

  - `MSG_BCAST` 返回条件是本数据报作为链路层广播收取或者其目的IP地址是一个广播地址。与IP_RECVD_STADDR套接字选项相比，本标志是用于判定一个UDP数据报是否发往某个广播地址的更好方法。
  - `MSG_MCAST`本标志随BSD
  - `MG_TRUNC`
  - `MSG_CTRUNC`
  - `MSG_EOR`
  - `MSG_OOB`
  - `MSG_NOTIFICATION`