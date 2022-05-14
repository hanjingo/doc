# 第三十章 客户/服务器程序设计范式

[TOC]



## 30.1 概述

![30_1](res/30_1.png)

*本章所讨论各个范式服务器的测时结果比较*

![30_1A](res/30_1A.png)

*过多子进程或线程对服务器CPU时间的影响*

![30_2](res/30_2.png)

*15个子进程或线程中每一个所服务的客户数的分布*



## 30.2 TCP客户程序设计范式



## 30.3 TCP测试用客户程序

```c++
#include "unp.h"
#define MAXN 16384
int 
main(int argc, char **argv)
{
    int i, j, fd, nchildren, nloops, nbytes;
    pid_t pid;
    ssize_t n;
    char request[MAXLINE], reply[MAXN];
    if (argc != 6)
        err_quit("usage: client <hostname or IPaddr> <port> <#children> "
                 "<#loops/child> <#bytes/request>");
    nchildren = atoi(argv[3]);
    nloops = atoi(argv[4]);
    nbytes = atoi(argv[5]);
    snprintf(request, sizeof(request), "%d\n", nbytes);
    for (i = 0; i < nchildren; i++) {
        if ((pid = Fork()) == 0) {
            for (j = 0; j < nloops; j++) {
                fd = Tcp_connect(argv[1], argv[2]);
                Write(fd, request, strlen(request));
                if ((n = Readn(fd, reply, nbytes)) != nbytes)
                    err_quit("server returned %d bytes", n);
                Close(fd);
            }
            printf("child %d done\n", i);
            exit(0);
        }
        /* parent loops around to fork() again */
    }
    while (wait(NULL) > 0)
        ;
    if (errno != ECHILD)
        err_sys("wait error");
    exit(0);
}
```

*用于测试各个范式服务器的TCP客户程序*



## 30.4 TCP迭代服务器程序



## 30.5 TCP并发服务器程序，每个客户一个子进程

```c++
#include "unp.h"
int 
main(int argc, char **argv)
{
    int listenfd, connnfd;
    pid_t childpid;
    void sig_chld(int), sig_int(int), web_child(int);
    socklen_t clilen, addrlen;
    struct sockaddr *cliaddr;
    if (argc == 2)
        listenfd = Tcp_listen(NULL, argv[1], &addrlen);
    else if (argc == 3)
        listenfd = Tcp_listen(argv[1], argv[2], &addrlen);
    else
        err_quit("usage: serv01 [<host>] <port#>");
    cliaddr = Malloc(addrlen);
    Signal(SIGCHLD, sig_chld);
    Signal(SIGINT, sig_int);
    for (;;) {
        clilen = addrlen;
        if ((connfd = accept(listenfd, cliaddr, &clilen)) < 0) {
            if (errno == EINTR)
                continue;
            else
                err_sys("accept error");
        }
        if ((childpid = Fork()) == 0) {
            Close(listenfd);
        	web_child(connfd);
            exit(0);
        }
        Close(connfd);
    }
}
void 
sig_int(int signo)
{
    void pr_cpu_time(void);
    pr_cpu_time();
    exit(0);
}
```

*server/serv01.c*

```c++
#include "unp.h"
#include <sys/resource.h>
#ifndef HAVE_GETRUSAGE_PROTO
int getrusage(int, struct rusage *);
#endif
void 
pr_cpu_time(void)
{
    double user, sys;
    struct rusage myusage, childusage;
    if (getrusage(RUSAGE_SELF, &myusage) < 0)
        err_sys("getrusage error");
    if (getrusage(RUSAGE_CHILDREN, &childusage) < 0)
        err_sys("getrusage error");
    user = (double)myusage.ru_utime.tv_sec + 
        myusage.ru_utime.tv_usec / 1000000.0;
    user += (double)childusage.ru_utime.tv_sec +
        childusage.ru_utime.tv_usec / 1000000.0;
    sys = (double)myusage.ru_stime.tv_sec + 
        myusage.ru_stime.tv_usec / 1000000.0;
    sys += (double)childusage.ru_stime.tv_sec + 
        childusage.ru_stime.tv_usec / 1000000.0;
    printf("\nuser time = %g, sys time = %g\n", user, sys);
}
```

*server/pr_cpu_time.c*

```c++
#include "unp.h"
#define MAXN 16384
void 
web_child(int sockfd)
{
    int ntowrite;
    ssize_t nread;
    char line[MAXLINE], result[MAXN];
    for (;;) {
        if ((nread = Readline(sockfd, line, MAXLINE)) == 0)
            return;
        /* line from client specifies #bytes to write back */
        ntowrite = atol(line);
        if ((ntowrite <= 0) || (ntowrite > MAXN))
            err_quit("client request for %d bytes", ntowrite);
        Writen(sockfd, result, ntowrite);
    }
}
```

*server/web_child.c*



## 30.6 TCP预先派生子进程服务器程序，accept无上锁保护

![30_8](res/30_8.png)

*服务器预先派生子进程*

```c++
#include "unp.h"
static int nchildren;
static pid_t *pids;
int 
main(int argc, char **argv)
{
    int listenfd, i;
    socklen_t addrlen;
    void sig_int(int);
    pid_t child_make(int, int, int);
    if (argc == 3) // 指派子进程个数
        listenfd = Tcp_listen(NULL, argv[1], &addrlen);
    else if (argc == 4)
        listenfd = Tcp_listen(argv[1], atgv[2], &addrlen);
    else
        err_quit("usage: serv02 [ <host> ] <port#> <#children>");
    nchildren = atoi(argv[argc - 1]);
    pids = Calloc(nchildren, sizeof(pid_t));
    for (i = 0; i < nchildren; i++)
        pids[i] = child_make(i, listenfd, addrlen); // 创建子进程
    Signal(SIGINT, sig_int);
    for (;;)
        pause();
}
void 
sig_int(int signo)
{
    int i;
    void pr_cpu_time(void);
    /* terminate all children */
    for (i = 0; i < nchildren; i++)
        kill(pids[i], SIGTERM);
    while (wait(NULL) > 0)
        ;
    if (errno != ECHILD)
        err_sys("wait error");
    pr_cput_time();
    exit(0);
}
```

*server/serv02.c*

```c++
#include "unp.h"
pid_t 
child_make(int i, int listenfd, int addrlen)
{
    pid_t pid;
    void child_main(int, int, int);
    if ((pid = Fork()) > 0) // 派生子进程
        return (pid);
    child_main(i, listenfd, addrlen);
}
void 
child_main(int i, int listenfd, int addrlen)
{
    int connfd;
    void web_child(int);
    socklen_t clilen;
    struct sockaddr *cliaddr;
    cliaddr = Malloc(addrlen);
    printf("child %1d starting\n", (long)getpid());
    for (;;) {
        clilen = addrlen;
        connfd = Accept(listenfd, cliaddr, &clilen);
        web_child(connfd); // 处理客户请求
        Close(connfd);
    }
}
```

*server/child02.c*

### 30.6.1 4.4BSD上的实现

![30_13](res/30_13.png)

*proc, file和socket这三个结构之间的关系*

### 30.6.2 子进程过多的影响

### 30.6.3 连接在子进程中的分布

```c++
#include "unp.h"
#include <sys/mman.h>
/*
 * Allocate an array of "nchildren" longs in shared memory that can
 * be used as a counter by each child of how many clients it services.
 * See pp. 467-470 of "Advanced Programming in the Unix Environment."
 */
long * 
meter(int nchildren)
{
    int fd;
    log *ptr;
#ifdef MAP_ANON
    ptr = Mmap(0, nchildren * sizeof(long), PROT_READ | PROT_WRITE,
               MAP-ANON | MAP_SHARED, -1, 0);
#else
    fd = Open("/dev/zero", O_RDWR, 0);
    ptr = Mmap(0, nchildren * sizeof(long), PROT_READ | PROT_WRITE,
               MAP_SHARED, fd, 0);
    Close(fd);
#endif
    return (ptr);
}
```

*在共享内存中分配一个数组的meter函数*

### 30.6.4 select冲突



## 30.7 TCP预先派生子进程服务器程序，accept使用文件上锁保护

```c++
#include "unp.h"
static struct flock lock_it, unlock_it; // 文件锁
static int lock_fd = -1;
/* fcntl() will fail if my_lock_init() not called */
void 
my_lock_init(char *pathname)
{
    char lock_file[1024];
    /* must copy caller's string, in case it's a constant */
    strncpy(lock_file, pathname, sizeof(lock_file)); // 路径名
    lock_fd = Mkstemp(lock_file); // 创建唯一路径名
    Unlink(lock_file); // 解除路径名的链接
    lock_it.l_type = F_WRLCK; // 文件加锁
    lock_it.l_whence = SEEK_SET;
    lock_it.l_start = 0;
    lock_it.l_len = 0;
    unlock_it.l_type = F_UNLCK; // 文件解锁
    unlock_it.l_whence = SEEK_SET;
    unlock_it.l_start = 0;
    unlock_it.l_len = 0;
}
void 
my_lock_wait()
{
    int rc;
    while ((rc = fcntl(locak_fd, F_SETLKW, &lock_it)) < 0) {
        if (errno == EINTR)
            continue;
        else
            err_sys("fcntl error for my_lock_wait");
    }
}
void 
my_lock_release()
{
    if (fcntl(lock_fd, F_SETLKW, &unlock_it) < 0)
        err_sys("fcntl error for my_lock_release");
}
```

*server/lock_fcntl.c*

### 30.7.1 子进程过多的影响

### 30.7.2 连接在子进程中的分布



## 30.8 TCP预先派生子进程服务器程序，accept使用线程上锁保护

```c++
#include "unpthread.h"
#include <sys/mman.h>
static pthread_mutex_t *mptr;
void 
my_lock_init(char *pathname)
{
    int fd;
    pthread_mutexattr_t mattr;
    fd = Open("/dev/zero", O_RDWR, 0); // 打开 /dev/zero
    mptr = Mmap(0, sizeof(pthread_mutex_t), PROT_READ | PROT_WRITE,
                MAP_SHARED, fd, 0);
    Close(fd);
    Pthread_mutexattr_init(&mattr); // 加锁
    Pthread_mutexattr_setpshared(&mattr, PTHREAD_PROCESS_SHARED);
    Pthread_mutex_init(mptr, &mattr); // 解锁
}
```

*server/lock_pthread.c*



## 30.9 TCP预先派生子进程服务器程序，传递描述符

```c++
typedef struct {
    pid_t child_pid;
    int   child_pipefd;
    int   child_status;
    long  child_count;
} Child;
Child *cptr;
```

*Child结构*

![30_22](res/30_22.png)

*父子进程各自关闭一端后的字节流管道*

![30_23](res/30_23.png)

*所有子进程都派生之后的各个字节流管道*

```c++
#include "unp.h"
#include "child.h"
pid_t 
child_make(int i, int listenfd, int addrlen)
{
    int sockfd[2];
    pid_t pid;
    void child_main(int, int, int);
    Socketpair(AF_LOCAL, SOCK_STREAM, 0, sockfd);
    if ((pid = Fork()) > 0) {
        Close(sockfd[1]);
        cptr[i].child_pid = pid;
        cptr[i].child_pipefd = sockfd[0];
        cptr[i].child_status = 0;
        return(pid);
    }
    Dup2(sockfd[1], STDERR_FILENO);
    Close(sockfd[0]);
    Close(sockfd[1]);
    Close(listenfd);
    child_main(i, listenfd, addrlen);
}
void 
child_main(int i, int listenfd, int addrlen)
{
    char c;
    int connfd;
    ssize_t n;
    void web_child(int);
    printf("child %1d starting\n", (long)getpid());
    for (;;) {
        if ((n = Read_fd(STDERR_FILENO, &c, 1, &connfd)) == 0) // 阻塞
            err_quit("read_fd returned 0");
        if (connfd < 0)
            err_quit("no descriptor from read_fd");
        web_child(connfd);
        Close(connfd);
        Write(STDERR_FILENO, "", 1); // 写1个字节，告知父进程：本子进程可用
    }
}
```

*server/child05.c*

```c++
#include "unp.h"
#include "child.h"
static int nchildren;
int 
main(int argc, char **argv)
{
    int listenfd, i, navail, maxfd, nsel, connfd, rc;
    void sig_int(int);
    pid_t child_make(int, int, int);
    ssize_t n;
    fd_set rset, masterset;
    socklen_t addrlen, clilen;
    struct sockaddr *cliaddr;
    if (argc == 3)
        listenfd = Tcp_listen(NULL, argv[1], &addrlen);
    else if (argc == 4)
        listenfd = Tcp_listen(argv[1], argv[2], &addrlen);
    else
        err_quit("usage: serv05 [<host>] <port#> <#children>");
    FD_ZERO(&masterset);
    FD_SET(listenfd, &masterset);
    maxfd = listenfd;
    cliaddr = Malloc(addrlen);
    nchildren = atoi(argv[argc - 1]);
    navail = nchildren;
    cptr = Calloc(nchildren, sizeof(Child));
    /* prefork all the children */
    for (i = 0; i < nchildren; i++) {
        child_make(i, listenfd, addrlen);
        FD_SET(cptr[i].child_pipefd, &masterset);
        maxfd = max(maxfd, cptr[i].child_pipefd);
    }
    Signal(SIGINT, sig_int);
    for (;;) {
        rset = masterset;
        if (navail <= 0) // 当前无可用子进程
            FD_CLR(listenfd, &rset);
        nsel = Select(maxfd + 1, &rset, NULL, NULL, NULL);
        /* check for new connections */
        if (FD_ISSET(listenfd, &rset)) { // accept新连接
            clilen = addrlen;
            connfd = Accept(listenfd, cliaddr, &clilen);
            for (i = 0; i < nchildren; i++)
                if (cptr[i].child_status == 0)
                    break;
            if (i == nchildren)
                err_quit("no available children");
            cptr[i].child_status = 1;
            cptr[i].child_count++;
            navail--;
            n = Write_fd(cptr[i].child_pipefd, "", 1, connfd);
            Close(connfd);
            if (--nsel == 0)
                continue;
        }
        /* find any newly-available children */
        for (i = 0; i < nchildren; i++) { // 处理新近可用的子进程
            if (FD_ISSET(cptr[i].child_pipefd, &rset)) {
                if ((n = Read(cptr[i].child_pipefd, &rc, 1)) == 0)
                    err_quit("child %d terminated unexpectedly", i);
                cptr[i].child_status = 0;
                navail++;
                if (--nsel == 0)
                    break;
            }
        }
    }
}
```

*server/serv05.c*



## 30.10 TCP并发服务器程序，每个客户一个线程

```c++
#include "unpthread.h"
int 
main(int argc, char **argv)
{
    int listenfd, connfd;
    void sig_int(int);
    void *doit(void *);
    pthread_t tid;
    socklen_t clilen, addrlen;
    struct sockaddr *cliaddr;
    if (argc == 2)
        listenfd = Tcp_listen(NULL, argv[1], &addrlen);
    else if (argc == 3)
        listenfd = Tcp_listen(argv[1], argv[2], &addrlen);
    else
        err_quit("usage: serv06 [<host>] <port#>");
    cliaddr = Malloc(addrlen);
    Signal(SIGINT, sig_int);
    for (;;) {
        clilen = addrlen;
        connfd = Accept(listenfd, cliaddr, &clilen);
        Pthread_create(&tid, NULL, &doit, (void *)connfd);
    }
}
void * 
doit(void *arg)
{
    void web_child(int);
    Pthread_detach(pthread_self());
    web_child((int)arg);
    Close((int)arg);
    return(NULL);
}
```

*server/serv06.c*



## 30.11 TCP预先创建线程服务器程序，每个线程各自accept

```c++
typedef struct {
    pthread_t thread_tid;
    long      thread_count;
} Thread;
Thread *tptr;
int listenfd, nthreads;
socklen_t addrlen;
pthread_mutex_t mlock;
```

*server/pthread07.h*

```c++
#include "unpthread.h"
#include "pthread07.h"
pthread_mutex_t mlock = PTHREAD_MUTEX_INITIALIZER;
int 
main(int argc, char **argv)
{
    int i;
    void sig_int(int), thread_make(int);
    if (argc == 3)
        listenfd = Tcp_listen(NULL, argv[1], &addrlen);
    else if (argc == 4)
        listenfd = Tcp_listen(argv[1], argv[2], &addrlen);
    else
        err_quit("usage: serv07 [<host>] <port#> <#threads>");
    nthreads = atoi(argv[argc - 1]);
    tptr = Calloc(nthreads, sizeof(Thread));
    for (i = 0; i < nthreads; i++)
        thread_make(i);
    Signal(SIGINT, sig_int);
    for (;;)
        pause();
}
```

*server/serv07.c*

```c++
#include "unpthread.h"
#include "pthread07.h"
void 
thread_make(int i)
{
    void *thread_main(void *);
    Pthread_create(&tptr[i].thread_tid, NULL, &thread_main, (void *)i); // 创建线程
    return;
}
void * 
thread_main(void *arg)
{
    int connfd;
    void web_child(int);
    socklen_t clilen;
    struct sockaddr *cliaddr;
    cliaddr = Malloc(addrlen);
    printf("thread %d starting\n", (int)arg);
    for (;;) {
        clilen = addrlen;
        Pthread_mutex_lock(&mlock); // 加锁
        connfd = Accept(listenfd, cliaddr, &clilen);
        Pthread_mutex_unlock(&mlock); // 解锁
        tptr[(int)arg].thread_count++;
        web_child(connfd);
        Close(connfd);
    }
}
```

*server/pthread07.c*



## 30.12 TCP预先创建线程服务器程序，主线程统一accept

```c++
typedef struct {
    pthread_t thread_tid;
    long      thread_count;
} Thread;
Thread *tptr;
#define MAXNCLI 32
int clifd[MAXNCLI], iget, iput; // 客户端数组，取下标，放下标
pthread_mutex_t clifd_mutex;
pthread_cond_t  clifd_cond;
```

*server/pthread08.h*

```c++
#include "unpthread.h"
#include "pthread08.h"
static int nthreads;
pthread_mutex_t clifd_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t clifd_cond = PTHREAD_COND_INITIALIZER;
int 
main(int argc, char **argv)
{
    int i, listenfd, connfd;
    void sig_int(int), thread_make(int);
    socklen_t addrlen, clilen;
    struct sockaddr *cliaddr;
    if (argc == 3)
        listenfd = Tcp_listen(NULL, argv[1], &addrlen);
    else if (argc == 4)
        listenfd = Tcp_listen(argv[1], argv[2], &addrlen);
    else
        err_quit("usage: serv08 [ <hsot> ] <port#> <#threads>");
    cliaddr = Malloc(addrlen);
    nthreads = atoi(argv[argc - 1]);
    tptr = Calloc(nthreads, sizeof(Thread));
    iget = iput = 0;
    /* create all the threads */
    for (i = 0; i < nthreads; i++)
        thread_make(i); // 创建线程
    Signal(SIGINT, sig_int);
    for (;;) { // 等待客户连接
        clilen = addrlen;
        connfd = Accept(listenfd, cliaddr, &clilen);
        Pthread_mutex_lock(&clifd_mutex);
        clifd[iput] = connfd;
        if (++iput == MAXNCLI)
            iput = 0;
        if (iput == iget)
            err_quit("iput = iget = %d", iput);
        Pthread_cond_signal(&clifd_cond);
        Pthread_mutex_unlock(&clifd_mutex);
    }
}
```

*server/serv08.c*

```c++
#include "unpthread.h"
#include "pthread08.h"
void 
thread_make(int i)
{
    void *thread_main(void *);
    Pthread_create(&tptr[i].thread_tid, NULL, &thread_main, (void *)i);
    return;
}
void * 
thread_main(void *arg)
{
    int connfd;
    void web_child(int);
    printf("thread %d starting\n", (int)arg);
    for (;;) {
        Pthread_mutex_lock(&clifd_mutex); // 加锁
        while (iget == iput)
            Pthread_cond_wait(&clifd_cond, &clifd_mutex);
        connfd = clifd[iget];
        if (++iget == MAXNCLI)
            iget = 0;
        Pthread_mutex_unlock(&clifd_mutex); // j
        tptr[(int)arg].thread_count++;
        web_child(connfd);
        Close(connfd);
    }
}
```

*server/pthread08.c*



## 30.13 小结

- 当系统负载较轻时，没来一个客户请求现场派生一个子进程为之服务的传统并发服务器程序模型就足够了。
- 相比传统的每个客户fork一次的设计范式，预先创建一个子进程池或一个线程池的设计范式能够把进程控制CPU时间降低10倍或以上。
- 某些实现允许多个子进程或线程阻塞在同一个accept调用中，另一些实现却要求包绕accept调用安置某种类型的锁加以保护。文件上锁或Pthread互斥锁上锁都可以使用。
- 让所有子进程或线程自行调用accept通常比让父进程或主线程独自调用accept并把描述符传递给子进程或线程来的简单而快速。
- 让所有子进程或线程阻塞在同一个accept调用中币让它们阻塞在同一个select调用中更可取。
- 使用线程通常远快于使用进程。