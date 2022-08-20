# 第19章 伪终端

[TOC]



## 19.1 引言



## 19.2 概述

![19_1](res/19_1.png)

*使用伪终端的相关进程的典型结构*

![19_2](res/19_2.png)

*Solaris中的伪终端结构*

![19_3](res/19_3.png)

*rlogind服务器的进程组织结构*

![19_4](res/19_4.png)

*script程序*

![19_5](res/19_5.png)

*用伪终端驱动一个协同进程*



## 19.3 打开伪终端设备

![19_6](res/19_6.png)

*使用伪终端运行一个缓慢输出的程序*

```c++
#include <stdlib.h>
#include <fcntl.h>
int posix_openpt(int oflag);
```

- `oflag` 位屏蔽字

- `返回值`

  成功：下一个可用的PTY主设备的文件描述符

  失败：-1

*打开下一个可用的伪终端主设备*

```c++
#include <stdlib.h>
int grantpt(int filedes);
```

- `filedes` 终端

- `返回值`

  成功：0

  失败：-1

*设置伪终端从设备权限*

```c++
#include <stdlib.h>
int unlockpt(int filedes);
```

- `filedes` 终端

- `返回值`

  成功：0

  失败：-1

*允许对伪终端从设备的访问*

```c++
#include <stdlib.h>
char *ptsname(int filedes);
```

- `filedes` 终端

- `返回值`

  成功：指向PTY从设备名的指针

  失败：NULL

*找到从伪终端设备的路径名*

| 函数         | 说明                | XSI  | FreeBSD 5.2.1 | Linux 2.4.22 | Mac OS X 10.3 | Solaris 9 |
| ------------ | ------------------- | ---- | ------------- | ------------ | ------------- | --------- |
| grantpt      | 更改从PTY设备的权限 | *    | *             | *            |               | *         |
| posix_openpt | 打开一主PTY设备     | *    | *             |              |               |           |
| ptsname      | 返回从PTY设备的名字 | *    | *             | *            |               | *         |
| unlockpt     | 允许从PTY设备被打开 | *    | *             | *            |               | *         |

*XSI伪终端函数*

```c++
#include "apue.h"
int ptym_open(char *pts_name, int pts_namesz);
```

- `pts_name` PTY主设备名

- `pts_namesz` PTY主设备名长度

- `返回值`

  成功：PTY主设备的文件描述符

  失败：-1

*打开下一个可用的PTY主设备*

```c++
#include "apue.h"
int ptys_open(char *pts_name);
```

- `pts_name` PTY主设备名

- `返回值`

  成功：PTY从设备的文件描述符

  失败：-1

*打开对应的从设备*

### 19.3.1 基于STREAMS的伪终端

```c++
#include "apue.h"
#include <errno.h>
#include <fcntl.h>
#include <stropts.h>

int 
ptym_open(char *pts_name, int pts_namesz)
{
    char *ptr;
    int fdm;
    
    strncpy(pts_name, "/dev/ptmx", pts_namesz);
    pts_name[pts_namesz - 1] = '\0';
    if ((fdm = open(pts_name, O_RDWR)) < 0)
        return (-1);
    if (grantpt(fdm) < 0) {
        close(fdm);
        return (-2);
    }
    if (unlockpt(fdm) < 0) {
        close(fdm);
        return(-3);
    }
    if ((ptr = ptsname(fdm)) == NULL) {
        close(fdm);
        return(-4);
    }
    strncpy(pts_name, ptr, pts_namesz);
    pts_name[pts_namesz - 1] = '\0';
    return(fdm);
}

ptys_open(char *pts_name)
{
    int fds, setup;
    if ((fds = open(pts_name, O_RDWR)) < 0)
        return(-5);
    if ((setup = ioctl(fds, I_FIND, "ldterm")) < 0) {
        close(fds);
        return(-6);
    }
    if (setup == 0) {
        if (ioctl(fds, I_PUSH, "ldterm") < 0) {
            close(fds);
            return(-7);
        }
        if (ioctl(fds, I_PUSH, "ldterm") < 0) {
            close(fds);
            return(-8);
        }
        if (ioctl(fds, I_PUSH, "ttcompat") < 0) {
            close(fds);
            return(-9);
        }
    }
    return(fds);
}
```

*基于STREAMS的伪终端打开函数*

### 19.3.2 基于BSD的伪终端

```c++
#include "apue.h"
#include <errno.h>
#include <fcntl.h>
#include <grp.h>

#ifndef _HAS_OPENPT
int
posix_openpt(int oflag)
{
    int fdm;
    char *ptr1, *ptr2;
    char ptm_name[16];
    
    strcpy(ptm_name, "/dev/ptyXY");
    for (ptr1 = "pqrstuvwxyzPQRST"; *ptr1 != 0; ptr1++) {
        ptm_name[8] = *ptr1;
        for (ptr2 = "0123456789abcdef"; *ptr2 != 0; ptr2++) {
            ptm_name[9] = *ptr2;
            if ((fdm = open(ptm_name, oflag)) < 0) {
                if (errno == ENOENT)
                    return (-1);
                else
                    continue;
            }
            return(fdm);
        }
    }
    errno = EAGAIN;
    return(-1);
}
#endif
#ifndef _HAS_PTSNAME
char *
ptsname(int fdm)
{
    static char pts_name[16];
    char *ptm_name;
    ptm_name = ttyname(fdm);
    if (ptm_name = NULL)
        return(NULL);
    strncpy(pts_name, ptm_name, sizeof(pts_name));
    pts_name[sizeof(pts_name) - 1] = '\0';
    if (strncmp(pts_name, "/dev/pty/", 9) == 0)
        pts_name[9] = 's';
    else
        pts_name[5] = 't';
    return(pts_name);
}
#endif
#ifndef _HAS_GRANTPT
int 
grantpt(int fdm)
{
    struct group *grptr;
    int gid;
    char *pts_name;
    pts_name = ptsname(fdm);
    if ((grptr = getgrnam("tty")) != NULL)
        gid = grptr->gr_gid;
    else
        gid = -1;
    if (chown(pts_name, getuid(), gid) < 0)
        return(-1);
    return(chmod(pts_name, S_IRUSR | S_IWUSR | S_IWGRP));
}
#endif
#ifndef _HAS_UNLOCKPT
int 
unlockpt(int fdm)
{
    return(0);
}
#endif

int 
ptym_open(char *pts_name, int pts_namesz)
{
    char *ptr;
    int fdm;
    strncpy(pts_name, "/dev/ptyXX", pts_namesz);
    pts_name[pts_namesz - 1] = '\0';
    if ((fdm = posix_openpt(O_RDWR)) < 0)
        return (-1);
    if (grantpt(fdm) < 0) {
        close(fdm);
        return(-2);
    }
    if (unlockpt(fdm) < 0) {
        close(fdm);
        return(-3);
    }
    if ((ptr = ptsname(fdm)) == NULL) {
        close(fdm);
        return(-4);
    }
    strncpy(pts_name, ptr, pts_namesz);
    pts_name[pts_namesz - 1] = '\0';
    return(fdm);
}
int 
pty_open(char *pts_name)
{
    int fds;
    if ((fds = open(pts_name, O_RDWR)) < 0)
        return (-5);
    return(fds);
}
```

*BSD和Linux的伪终端打开函数*

### 19.3.3 基于LInux的伪终端

```c++
#include "apue.h"
#include <fcntl.h>

#ifndef _HAS_OPENPT
int 
posix_openpt(int oflag)
{
    int fdm;
    fdm = open("/dev/ptmx", oflag);
    return(fdm);
}
#endif

#ifndef _HAS_PTSNAME
char *
ptsname(int fdm)
{
    int sminor;
    static char pts_name[16];
    if (ioctl(fdm, TIOCGPTN, &sminor) < 0)
        return(NULL);
    snprintf(pts_name, sizeof(pts_name), "/dev/pts/%d", sminor);
    return(pts_name);
}
#endif

#ifndef _HAS_GRANTPT
int 
grantpt(int fdm)
{
    char *pts_name;
    pts_name = ptsname(fdm);
    return(chmod(pts_name, S_IRUSR | S_IWUSR | S_IWGRP));
}
#endif

#ifndef _HAS_UNLOCKPT
int 
unlockpt(int fdm)
{
    int lock = 0;
    return(ioctl(fdm, TIOCSPTLCK, &lock));
}
#endif

int 
ptym_open(char *pts_name, int pts_namesz)
{
    char *ptr;
    int fdm;
    strncpy(pts_name, "/dev/ptmx", pts_namesz);
    pts_name[pts_namesz - 1] = '\0';
    fdm = posix_openpt(O_RDWR);
    if (fdm < 0)
        return (-1);
    if (grantpt(fdm) < 0) {
        close(fdm);
        return(-2);
    }
    if (unlockpt(fdm) < 0) {
        close(fdm);
        return(-3);
    }
    if ((ptr = ptsname(fdm)) == NULL) {
        close(fdm);
        return(-4);
    }
    strncpy(pts_name, ptr, pts_namesz);
    pts_name[pts_namesz - 1] = '\0';
    return(fdm);
}

int 
ptys_open(char *pts_name)
{
    int fds;
    if ((fds = open(pts_name, O_RDWR)) < 0)
        return(-5);
    return(fds);
}
```

*Linux的伪终端open函数*



## 19.4 pty_fork函数

```c++
#include "apue.h"
#include <termios.h>
#include <sys/ioctl.h>
pid_t pty_fork(int *ptrfdm, char *slave_name, int slave_namesz,
               const struct termios *slave_termios,
               const struct winsize *slave_winsize);
```

- `ptrfdm` PTY主设备文件描述符
- `slave_name` 存放从设备名字符数组
- `slave_namesz` 从设备名字符数组长度
- `slave_termios` 初始化从设备的终端行规程
- `slave_winsize` 初始化从设备的窗口大小
- `返回值` 子进程中返回0，父进程中返回子进程的进程ID，出错返回-1

*用fork调用打开主设备和从设备，创建作为会话首进程的子进程并使其具有控制终端*

例：

```c++
#include "apue.h"
#include <termios.h>
#ifndef TIOCGWINSZ
#include <sys/ioctl.h>
#endif

pid_t 
ptt_fork(int *ptrfdm, char *slave_name, int slave_namesz, 
         const struct termios *slave_termios,
         const struct winsize *slave_winsize)
{
    int fdm, fds;
    pid_t pid;
    char pts_name[20];
    if ((fdm = ptym_open(pts_name, sizeof(pts_name))) < 0)
        err_sys("can't open master pty: %s, error %d", pts_name, fdm);
    if (slave_name != NULL) {
        strncpy(slave_name, pts_name, slave_namesz);
        slave_name[slave_namesz - 1] = '\0';
    }
    if ((pid = fork()) < 0) {
        return (-1);
    } else if (pid == 0) {
        if (setsid() < 0)
            err_sys("setsid error");
        if ((fds = ptys_open(pts_name)) < 0)
            err_sys("can't open slave pty");
        close(fdm);
#if defined(TIOCSCTTY)
        if (ioctl(fds, TIOCSCTTY, (char *)0) < 0)
            err_sys("TIOCSCTTY error");
#endif
        if (slave_termios != NULL) {
            if (tcsetattr(fds, TCSANOW, slave_termios) < 0)
                err_sys("tcsetattr error on slave pty");
        }
        if (slave_winsize != NULL) {
            if (ioctl(fds, TIOCSWINSZ, slave_winsize) < 0)
                err_sys("TIOCSWINSZ error on slave pty");
        }
        if (dup2(fds, STDIN_FILENO) != STDIN_FILENO)
            err_sys("dup2 error to stdin");
        if (dup2(fds, STDOUT_FILENO) != STDOUT_FILENO)
            err_sys("dup2 error to stdout");
        if (dup2(fds, STERR_FILENO) != STDERR_FILENO)
            err_sys("dup2 error to stderr");
        if (fds != STDIN_FILENO && fds != STDOUT_FILENO &&
            fds != STDERR_FILENO)
            close(fds);
        return(0);
    } else {
        *ptrfdm = fdm;
        return(pid);
    }
}
```

*pty_fork函数*



## 19.5 pty程序

例：

```c++
#include "apue.h"
#include <termios.h>
#ifndef TIOCGWINSZ
#include <sys/ioctl.h>
#endif

#ifdef LINUX
#define OPTSTR "+d:einv"
#else
#define OPTSTR "d:einv"
#endif

static void set_noecho(int);
void do_driver(char *);
void loop(int, int);

int 
main(int argc, char *argv[])
{
    int fdm, c, ignoreeof, interactive, noecho, verbose;
    pid_t pid;
    char *driver;
    char slave_name[20];
    struct termios orig_termios;
    struct winszie size;
    
    interactive = isatty(STDIN_FILENO);
    ignoreeof = 0;
    noecho = 0;
    verbose = 0;
    driver = NULL;
    
    opterr = 0;
    while ((c = getopt(argc, argv, OPTSTR)) != EOF) {
        switch (c) {
            case 'd':
                driver = optarg;
                break;
            case 'e':
                noecho = 1;
                break;
            case 'i':
                ignoreeof = 1;
                break;
            case 'n':
                interactive = 0;
                break;
            case 'v':
                verbose = 1;
                break;
            case '?':
                err_quit("unrecoginzed option: -%c", optopt);
        }
    }
    if (optind >= argc)
        err_quit("usage: pty [ -d driver -einv ] program [arg ...]");
    if (interactive) {
        if (tcgetattr(STDIN_FILENO, &orig_termios) < 0)
            err_sys("tcgetattr error on stdin");
        if (ioctl(STDIN_FILENO, TIOCGWINSZ, (char *)&size) < 0)
            err_sys("TIOCGWINSZ error");
        pid = pty_fork(&fdm, slave_name, sizeof(slave_name),
                       &orig_termios, &size);
    } else {
        pid = pty_fork(&fdm, slave_name, sizeof(slave_name),
                       NULL, NULL);
    }
    if (pid < 0) {
        err_sys("fork error");
    } else if (pid == 0) {
        if (noecho)
            set_noecho(STDIN_FILENO);
        if (execvp(argv[optind], &argv[optind]) < 0)
            err_sys("can't execute: %s", argv[optind]);
    }
    if (verbose) {
        fprintf(stderr, "slave name = %s\n", slave_name);
        if (driver != NULL)
            fprintf(stderr, "driver = %s\n", driver);
    }
    if (interactive && driver == NULL) {
        if (tty_raw(STDIN_FILENO) < 0)
            err_sys("tty_raw error");
        if (atexit(tty_atexit) < 0)
            err_sys("atexit error");
    }
    if (driver)
        do_driver(driver);
    loop(fdm, ignoreeof);
    exit(0);
}

static void 
set_noecho(int fd)
{
    struct termios stermios;
    if (tcgetattr(fd, &stermios) < 0)
        err_sys("tcgetattr error");
    stermios.c_lflag &= ~(ECHO | ECHOE | ECHOK | ECHONL);
    stermios.c_oflag &= ~(ONLCR);
    if (tcsetattr(fd, TCSANOW, &stermios) < 0)
        err_sys("tcsetattr error");
}
```

*pty程序的main函数*

例：

```c++
#include "apue.h"

#define BUFFSIZE 512

static void sig_term(int);
static volatile sig_atomic_t sigcaught;

void 
loop(int ptym, int ignoreeof)
{
    pid_t child;
    int nread;
    char buf[BUFFSIZE];
    if ((child = fork()) < 0) {
        err_sys("fork error");
    } else if (child == 0) {
        for (;;) {
            if ((nread = read(STDIN_FILENO, buf, BUFFSIZE)) < 0)
                err_sys("read error from stdin");
            else if (nread == 0)
                break;
            if (writen(ptym, buf, nread) != nread)
                err_sys("writen error to master pty");
        }
        if (ignoreeof == 0)
            kill(getpid(), SIGTERM);
        exit(0);
    }
    if (signal_intr(SIGTERM, sig_term) == SIG_ERR)
        err_sys("signal_intr error for SIGTERM");
    for (;;) {
        if ((nread = read(ptym, buf, BUFFSIZE)) <= 0)
            break;
        if (writen(STDOUT_FILENO, buf, nread) != nread)
            err_sys("writen error to stdout");
    }
    if (sigcaught == 0)
        kill(child, SIGTERM);
}

static void 
sig_term(int signo) 
{
    sigcaught = 1;
}
```

*loop函数*



## 19.6 使用pty程序

![19_7](res/19_7.png)

*pty cat的进程组和会话*

![19_8](res/19_8.png)

*script shell脚本*

![19_9](res/19_9.png)

*运行一协同进程，以伪终端作为其输入和输出*

```c++
#include "apue.h"
void 
do_driver(char *driver)
{
    pid_t child;
    int pipe[2];
    int (s_pipe(piep) < 0)
        err_sys("can't create stream pipe");
    if ((child = fork()) < 0) {
        err_sys("fork error");
    } else if (child == 0) {
        close(pipe[1]);
        
        if (dup2(pipe[0], STDIN_FILENO) != STDIN_FILENO)
            err_sys("dup2 error to stdin");
        if (dp2(pipe[0], STDOUT_FILENO) != STDOUT_FILENO)
            err_sys("dup2 error to stdout");
        if (pipe[0] != STDIN_FILENO && pipe[0] != STDOUT_FILENO)
            close(pipe[0]);
        
        execlp(driver, driver, (char *)0);
        err_sys("execlp error for: %s", driver);
    }
    close(pipe[0]);
    if (dup2(pipe[1], STDIN_FILENO) != STDIN_FILENO)
        err_sys("dup2 error to stdin");
    if (dup2(pipe[1], STDOUT_FILENO) != STDOUT_FILENO)
        err_sys("dup2 error to stdout");
    if (pipe[1] != STDIN_FILENO && pipe[1] != STDOUT_FILENO)
        close(pipe[1]);
}
```

*pty程序的do_driver函数*



## 19.7 高级特性



## 19.8 小结

