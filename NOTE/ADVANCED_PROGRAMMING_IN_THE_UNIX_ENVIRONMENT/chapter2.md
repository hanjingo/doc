# 第二章 UNIX标准化及实现

[TOC]



## 2.1 引言



## 2.2 UNIX标准化

### 2.2.1 ISO C

![t2_1](res/t2_1.png)

*ISO C标准定义的头文件*

### 2.2.2 IEEE POSIX

![t2_2](res/t2_2.png)

*POSIX标准定义的必需的头文件*

![t2_3](res/t2_3.png)

*POSIX标准定义的XSI扩展头文件*

![t2_4](res/t2_4.png)

*POSIX标准定义的可选头文件*

![t2_5](res/t2_5.png)

*POSIX.1可选接口组和代码*

### 2.2.3 Single UNIX Specification

### 2.2.4 FIPS



## 2.3 UNIX系统实现

### 2.3.1 SVR4

SVR4（UNIX System V Release）

### 2.3.2 4.4BSD

BSD（Berkeley Software Distribution）

### 2.3.3 FreeBSD

### 2.3.4 Linux

### 2.3.5 Mac OS X

### 2.3.6 Solaris

### 2.3.7 其它UNIX系统



## 2.4 标准和实现的关系



## 2.5 限制

### 2.5.1 ISO C限制

![t2_6](res/t2_6.png)

*<limits.h>中定义的整型值大小*

![t2_7](res/t2_7.png)

*在各种平台上的ISO限制*

### 2.5.2 POSIX限制

![t2_8](res/t2_8.png)

*<limits.h>中的POSIX.1不变最小值*

### 2.5.3 XSI限制

XSI定义了处理实现限制的下面的常量：

- 不变最小值；

  ![t2_9](res/t2_9.png)

  *<limits.h>中的XSI不变最小值*

- 数值限制：`LONG_BIT`和`WORD_BIT`；

- 运行时不变值：`ATEXIT_MAX`, `IOV_MAX`以及`PAGE_SIZE`。

### 2.5.4 sysconf,pathconf和fpathconf函数

```c++
#include <unistd.h>
long sysconf(int name);
long pathconf(const char *pathname, int name);
long fpathconf(int filedes, int name);
```

- `name` 限制名

  ![t2_10](res/t2_10.png)

  *sysconf的限制及name参数*

  ![t2_11](res/t2_11.png)

  *pathconf和fpathconf的限制及name参数*

- `pathname` 文件路径

- `filedes` 文件描述符

- `返回值`

  成功：运行时限制

  失败：-1

*获得运行时限制*

例：

```c++
TODO
```

*构建C程序以打印所有得到支持的系统配置限制*

例：

```c++
#include "apue.h"
#include <errno.h>
#include <limits.h>

static void pr_sysconf(char *, int);
static void pr_pathconf(char *, char *, int);

int 
main(int argc, char *argv[])
{
    if (argc != 2)
        err_quit("usage: a.out <dirname>");
#ifdef ARG_MAX
    printf("ARG_MAX defined to be %d\n", ARG_MAX + 0);
#else
    printf("no symbol for ARG_MAX\n");
#endif
#ifdef _SC_ARG_MAX
    pr_sysconf("ARG_MAX = ", _SC_ARG_MAX);
#else
    printf("no symbol for _SC_ARG_MAX");
#endif
    
#ifdef MAX_CANON
    printf("MAX_CANON defined to be %d\n", MAX_CANON+0);
#else
    printf("no symbol for MAX_CANON\n");
#endif
#ifdef _PC_MAX_CANON
    pr_pathconf("MAX_CANON = ", argv[1], _PC_MAX_CANON);
#else
    printf("no symbol for _PC_MAX_CANON\n");
#endif
    exit(0);
}

static void 
pr_sysconf(char *mesg, int name)
{
    long val;
    fputs(mesg, stdout);
    errno = 0;
    if ((val = sysconf(name)) < 0) {
        if (errno != 0) {
            if (errno == EINVAL)
                fputs("(not supported)\n", stdout);
            else
                err_sys("sysconf error");
        } else {
            fputs(" %1d\n", val);
        }
    }
}

static void 
pr_pathconf(char *mesg, char *path, int name)
{
    long val;
    fputs(mesg, stdout);
    errno = 0;
    if ((val = pathconf(path, name)) < 0) {
        if (errno != 0) {
            if (errno == EINVAL)
                fputs("(not supported)\n", stdout);
            else
                err_sys("pathconf error, path = %s", path);
        } else {
            fputs("(no limit)\n", stdout);
        }
    } else {
        printf("%1d\n", val);
    }
}
```

*打印所有可能的sysconf和pathconf值*

![t2_12](res/t2_12.png)

*配置限制的实例*

### 2.5.5 不确定的运行时限制

例：

```c++
#include "apue.h"
#include <errno.h>
#include <limits.h>

#ifdef PATH_MAX
static int pathmax = PATH_MAX;
#else
static int pathmax = 0;
#endif

#define SUSV3 200112L

static long posix_version = 0;

#define PATH_MAX_GUESS 1024

char *
path_alloc(int *sizep)
{
    char *ptr;
    int size;
    
    if (posix_version == 0)
        posix_version = sysconf(_SC_VERSION);
    if (pathmax == 0)
        errno = 0;
    if ((pathmax = pathconf("/", _PC_PATH_MAX)) < 0) {
        if (errno == 0)
            pathmax = PATH_MAX_GUESS;
        else
            err_sys("pathconf error for _PC_PATH_MAX");
    } else {
        pathmax++;
    }
}

if (posix_version < SUSV3)
    size = pathmax + 1;
else
    size = pathmax;

if ((ptr = malloc(size)) == NULL)
    err_sys("malloc error for pathname");
if (sizep != NULL)
    *sizep = size;

return(ptr);
```

*为路径名动态地分配空间*

例：

```c++
#include "apue.h"
#include <errno.h>
#include <limits.h>

#ifdef OPEN_MAX
static long openmax = OPEN_MAX;
#else
static long openmax = 0;
#endif

#define OPEN_MAX_GUESS 256

long 
open_max(void)
{
    if (openmax == 0) {
        errno = 0;
        if ((openmax = sysconf(_SC_OPEN_MAX)) < 0) {
            if (errno == 0)
                openmax = OPEN_MAX_GUESS;
            else
                err_sys("sysconf error for _SC_OPEN_MAX");
        }
    }
    return(openmax);
}
```

*确定文件描述符数*



## 2.6 选项

![t2_13](res/t2_13.png)

*sysconf的选项及name参数*

![t2_14](res/t2_14.png)

*pathconf和fpathconf的选项及name参数*

![t2_15](res/t2_15.png)

*配置选项的实例*



## 2.7 功能测试宏



## 2.8 基本系统数据类型

![t2_16](res/t2_16.png)

*某些常用的基本系统数据类型*



## 2.9 标准之间的冲突



## 2.10 小结

