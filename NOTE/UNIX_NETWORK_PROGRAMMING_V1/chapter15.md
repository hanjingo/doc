# 第十五章 Unix域协议

[TOC]



## 15.1 概述

使用Unix域套接字的理由：

1. 在源自Berkeley的实现中，Unix域套接字往往比通信两端位于同一个主机的TCP套接字快出一倍。
2. Unix域套接字可用于在同一个主机上的不同进程之间传递描述符。
3. Unix域套接字较新的实现把客户的凭证提供给服务器，从而能够提供额外的安全检查措施。



## 15.2 Unix域套接字地址结构

```c++
struct sockaddr_un {
    sa_family_t sun_family;
    char        sun_path[104];
};
```

*<sys/un.h>中定义的Unix域套接字地址结构*

```c++
#include "unp.h"
int 
main(int argc, char **argv)
{
    int sockfd;
    socklen_t len;
    struct sockaddr_un addr1, addr2;
    if (argc != 2)
        err_quit("usage: unixbind <pathname>");
    sockfd = Socket(AF_LOCAL, SOCK_STREAM, 0);
    unlink(argv[1]); // 解除链接
    bzero(&addr1, sizeof(addr1));
    addr1.sun_family = AF_LOCAL;
    strncpy(addr1.sun_path, argv[1], sizeof(addr1.sun_path) - 1);
    Bind(sockfd, (SA *)&addr1, SUN_LEN(&addr1));
    len = sizeof(addr2);
    Getsockname(sockfd, (SA *)&addr2, &len);
    printf("bound name = %s, returned len = %d\n", addr2.sun_path, len);
    exit(0);
}
```

*unixdomain/unixbind.c*



## 15.3 socketpair函数

```c++
#include <sys/socket.h>
int socketpair(int family, int type, int protocol, int sockfd[2]);
```

- `family`协议族（必须为AF_LOCAL）
- `type`类型（为SOCK_STREAM或SOCK_DGRAM中的一个）
- `protocol`协议（必须为0）
- `sockfd`用于返回新创建的套接字描述符
- 返回值
  - 成功：非0
  - 失败：-1

*创建两个随后连接起来的套接字*



## 15.4 套接字函数



## 15.5 Unix域字节流客户/服务器程序

```c++
#include "unp.h"
int 
main(int argc, char **argv)
{
    int listenfd, connfd;
    pid_t childpid;
    socklen_t clilen;
    struct sockaddr_un cliaddr, servaddr;
    void sig_chld(int);
    listenfd = Socket(AF_LOCAL, SOCK_STREAM, 0);
    unlink(UNIXSTR_PATH);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sun_family = AF_LOCAL;
    strcpy(servaddr.sun_path, UNIXSTR_PATH);
    Bind(listenfd, (SA *)&servaddr, sizeof(servaddr));
    Listen(listenfd, LISTENQ);
    Signal(SIGCHLD, sig_child);
    for (;;) {
        clilen = sizeof(cliladdr);
        if ((connfd = accept(listenfd, (SA *)&cliaddr, &clilen)) < 0) {
            if (errno == EINTR)
                continue;
            else
                err_sys("accept error");
        }
        if ((childpid = Fork()) == 0) {
            Close(listenfd);
            str_echo(connfd);
            exit(0);
        }
        Close(connfd);
    }
}
```

*unixdomain/unixstrserv01.c*

```c++
#include "unp.h"
int 
main(int argc, char **argv)
{
    int sockfd;
    struct sockaddr_un servaddr;
    sockfd = Socket(AF_LOCAL, SOCK-STREAM, 0);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sun_family = AF_LOCAL;
    strcpy(servaddr.sun_path, UNIXSTR_PATH);
    Connect(sockfd, (SA *)&servaddr, sizeof(servaddr));
    str_cli(stdin, sockfd);
    exit(0);
}
```

*unixdomain/unixstrcli01.c*



## 15.6 Unix域数据报客户/服务器程序

```c++
#include "unp.h"
int 
main(int argc, char **argv)
{
    int sockfd;
    struct sockaddr_un srvaddr, cliaddr;
    sockfd = Socket(AF_LOCAL, SOCK_DGRAM, 0);
    unlink(UNIXDG_PATH);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sun_family = AF_LOCAL;
    strcpy(servaddr.sun_path, UNIXDG_PATH);
    Bind(sockfd, (SA *)&servaddr, sizeof(servaddr));
    dg_echo(sockfd, (SA *)&cliaddr, sizeof(cliaddr));
}
```

*unixdomain/unixdgserv01.c*

```c++
#include "unp.h"
int 
main(itn argc, char **argv)
{
    int sockfd;
    struct sockaddr_un cliaddr, servaddr;
    sockfd = Socket(AF_LOCAL, SOCK_DGRAM, 0);
    bzero(&cliaddr, sizeof(cliaddr));
    cliaddr.sun_family = AF_LOCAL;
    strcpy(cliaddr.sun_path, tmpnam(NULL));
    Bind(sockfd, (SA *)&cliaddr, sizeof(cliaddr));
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sun_family = AF_LOCAL;
    strcpy(servaddr.sun_path, UNIXDG_PATH);
    dg_cli(stdin, sockfd, (SA *)&servaddr, sizeof(servaddr));
    exit(0);
}
```

*unixdomain/unixdgcli01.c*



## 15.7 描述符传递

![15_7](res/15_7.png)

*使用socketpair创建流管道后的mycat进程*

![15_8](res/15_8.png)

*启动执行openfile程序后的mycat进程*

```c++
#include "unp.h"
int my_open(const char *, int);
int 
main(int argc, char **argv)
{
    int fd, n;
    char buff[BUFFSIZE];
    if (argc != 2)
        err_quit("usage: mycat <pathname>");
    if ((fd = my_open(argv[1], O_RDONLY)) < 0)
        err_sys("cannot open %s", argv[1]);
    while ((n = Read(fd, buff, BUFFSIZE)) > 0)
        Write(STDOUT_FILENO, buff, n);
    exit(0);
}
```

*unixdomain/mycat.c*

```c++
#include "unp.h"
int 
my_open(const char *pathname, int mode)
{
	int fd, sockfd[2], status;
	pid_t childpid;
	char c, argsockfd[10], argmode[10];
	Socketpair(AF-LOCAL, SOCK_STREAM, 0, sockfd);
	if ((childpid = Fork()) == 0) {
		Close(sockfd[0]);
		snprintf(argsockfd, sizeof(argsockfd), "%d", sockfd[1]);
		snprintf(argmode, sizeof(argmode), "%d", mode);
		execl("./openfile", "openfile", argsockfd, pathanme, argmode,
		 	  (char *)NULL);
		err_sys("execl error");
	}
	/* parent process - wait for the child to terminate */
	Close(sockfd[1]);
	Waitpid(childpid, &status, 0);
	if (WIFEXITED(status) == 0)
		err_quit("child did not terminate");
    if ((status = WEXITSTATUS(status)) == 0) // 终止状态 -> 退出状态
        Read_fd(sockfd[0], &c, 1, &fd); // 读取1个字节
    else {
        errno = status;
        fd = -1;
    }
    Close(sockfd[0]);
    return (fd);
}
```

*unixdomain/myopen.c*

```c++
#include "unp.h"
ssize_t 
read_fd(int fd, void *ptr, size_t nbytes, int *recvfd)
{
    struct msghdr msg;
    struct iovec iov[1];
    ssize_t n;
#ifdef HAVE_MSGHDR_MSG_CONTROL
    union {
        struct cmsghdr cm;
        char control[CMSG_SPACE(sizeof(int))];
    } control_un;
    struct cmsghdr *cmptr;
    msg.msg_control = control_un.control;
    msg.msg_controllen = sizeof(control_un.control);
#else
    int newfd;
    msg.msg_accrights = (caddr_t)&newfd;
    msg.msg_accrightslen = sizeof(int);
#endif
    msg.msg_name = NULL;
    msg.msg_namelen = 0;
    iov[0].iov_base = ptr;
    iov[0].iov_len = nbytes;
    msg.msg_iov = iov;
    msg.msg_iovlen = 1;
    if ((n = recvmsg(fd, &msg, 0)) <= 0)
        return(n);
#ifdef HAVE_MSGHDR_MSG_CONTROL
	if ((cmptr = CMSG_FIRSTHDR(&msg)) != NULL &&
        cmptr->cmsg_len == CMSG_LEN(sizeof(int))) {
        if (cmptr->cmsg_level != SOL_SOCKET)
            err_quit("control level != SOL_SOCKET");
        if (cmptr->cmsg_type != SCM_RIGHTS)
            err_quit("control type != SCM_RIGHTS");
        *recvfd = *((int *)CMSG_DATA(cmptr));
    } else
        *recvfd = -1;
#else
    if (msg.msg_accrightslen == sizeof(int))
        *recvfd = newfd;
    else
        *recvfd = -1;
#endif
    return(n);
}
```

*lib/read_fd.c*

```c++
#include "unp.h"
int 
main(int argc, char **argv)
{
    int fd;
    if (argc != 4)
        err_quit("openfile <sockfd#> <filename> <mode>");
    if ((fd = open(argv[2], atoi(argv[3]))) < 0)
        exit((errno > 0) ? errno : 255);
    if (write_fd(atoi(argv[1]), "", 1, fd) < 0)
        exit((errno > 0) ? errno : 255);
    exit(0);
}
```

*unixdomain/openfile.c*

```c++
#include "unp.h"
ssize_t 
write_fd(int fd, void *ptr, size_t bytes, int sendfd)
{
    struct msghdr msg;
    struct iovec iov[1];
#ifdef HAVE_MSGHDR_MSG_CONTROL
    union {
        struct cmsghdr cm;
        char           control[CMSG_SPACE(sizeof(int))];
    } control_un;
    struct cmsghdr *cmptr;
    msg.msg_control = control_un.contrl;
    msg.msg_controllen = sizeof(control_un.control);
    cmptr = CMSG_FIRSTHDR(&msg);
    cmptr->cmsg_len = CMSG_LEN(sizeof(int));
    cmptr->cmsg_level = SOL_SOCKET;
    cmptr->cmsg_type = SCM_RIGHTS;
    *((int *)CMSG_DATA(cmptr)) == sendfd;
#else
    msg.msg_accrights = (caddr_t) &sendfd;
    msg.msg_accrightslen = sizeof(int);
#endif
    msg.msg_name = NULL;
    msg.msg_namelen = 0;
    iov[0].iov_base = ptr;
    iov[0].iov_len = bytes;
    msg.msg_iov = iov;
    msg.msg_iovlen = 1;
    return(sendmsg(fd, &msg, 0));
}
```

*lib/write_fd.c*



## 15.8 接收发送者的凭证

```c++
struct cmsgcred {
    pid_t cmcred_pid;
    uid_t cmcred_uid;
    uid_t cmcred_euid;
    gid_t cmcred_gid;
    short cmcred_ngroups;             // >= 1
    gid_t cmcred_groups[CMGROUP_MAX]; // CMGROUP_MAX一般为16
};
```

*FreeBSD在头文件<sys/socket.h>中定义的cmsgcred结构传递凭证*

```c++
#include "unp.h"
#define CONTROL_LEN (sizeof(struct cmsghdr) + sizeof(struct cmsgcred))
ssize_t 
read_cred(int fd, void *ptr, size_t nbytes, struct cmsgcred *cmsgcredptr)
{
    struct msghdr msg;
    struct iovec iov[1];
    char control[CONTROL_LEN];
    int n;
    msg.msg_name = NULL;
    msg.msg_namelen = 0;
    iov[0].iov_base = ptr;
    iov[0].iov_len = nbytes;
    msg.msg_iov = iov;
    msg.msg_iovlen = 1;
    msg.msg_control = control;
    msg.msg_controllen = sizeof(control);
    msg.msg_flags = 0;
    if ((n = recvmsg(fd, &msg, 0)) < 0)
        return(n);
    cmsgcredptr->cmcred_ngroups = 0;
    if (cmscredptr && msg.msg_controllen > 0) {
        struct cmsghdr *cmptr = (struct cmsghdr *)control;
        if (cmptr->cmsg_len < CONTROL_LEN)
            err_quit("control length = %d", cmptr->cmsg_len);
        if (cmptr->cmsg_level != SOL_SOCKET)
            err_quit("control level != SOL_SOCKET");
        if (cmptr->cmsg_type != SCM_CREDS)
            err_quit("control type != SCM_CREDS");
        memcpy(cmsgcredptr, CMSG_DATA(cmptr), sizeof(struct cmsgcred));
    }
    return(n);
}
```

*unixdomain/readcred.c*

```c++
#include "unp.h"
ssize_t read_cred(int, void*, size_t, struct cmsgcred *);
void 
str_echo(int sockfd)
{
    ssize_t n;
    int i;
    char buf[MAXLINE];
    struct cmsgcred cred;
again:
    while((n = read_cred(sockfd, buf, MAXLINE, &cred)) > 0) {
        if (cred.cmcred_ngroups == 0) {
            printf("(no credentials returned)\n");
        } else {
            printf("PID of sender = %d\n", cred.cmcred_pid);
            printf("real user ID = %d\n", cred.cmcred_uid);
            printf("real group ID = %d\n", cred.cmcred_gid);
            printf("effective user ID = %d\n", cred.cmcred_euid);
            printf("%d groups:", cred.cmcred_ngroups - 1);
            for (i = 1; i < cred.cmcred_ngroups; i++)
                printf(" %d", cred.cmcred_groups[i]);
            printf("\n");
        }
        Writen(sockfd, buf, n);
    }
    if (n < 0 && errno == EINTR)
        goto again;
    else if (n < 0)
        err_sys("str_echo: read error");
}
```

*unixdomain/strecho.c*



## 15.9 小结



