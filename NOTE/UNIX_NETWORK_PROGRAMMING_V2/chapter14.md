# 第14章 System V 共享内存区



## 14.1 概述

对于每个共享内存区，内核维护如下的信息结构，它定义在<sys/shm.h>头文件中：

```c++
TODO
```



## 14.2 shmget函数

```c++
#include <sys/shm.h>
int shmget(key_t key, size_t size, int oflag);
```

- `key` 键

- `size` 内存区大小（字节）。

- `oflag` 读写权限值组合。

- `返回值`

  成功：共享内存区对象

  失败：-1

创建一个新的共享内存区或访问一个已存在的共享内存区。

  

## 14.3 shmat函数

```c++
#include <sys/shm.h>
void *shmat(int shmid, const void *shmaddr, int flag);
```

- `shmid` 共享内存区在调用进程内的起始地址

- `shmaddr` 地址

  1. 如果shmaddr是一个空指针，那么系统替调用者选择地址（推荐，可移植性强）。
  2. 如果shmaddr是一个非空指针，那么返回地址取决于调用者是否给flag参数指定了SHM_RND值：
     - 如果没有指定SHM_RND，那么相应的共享内存区附接到由shmaddr参数指定的地址；
     - 如果制定了SHM_RND，那么相应的共享内存区附接到由shmaddr参数指定的地址向下舍入一个SHMLBA常值。LBA代表“低端边界地址（lower boundary address）”。

- `flag` 标志

- `返回值`

  成功：映射区的起始地址

  失败：-1

将共享内存区附接到调用进程的地址空间。



## 14.4 shmdt函数

```c++
#include <sys/shm.h>
int shmdt(const void *shmaddr);
```

- `shmaddr` 共享内存区

- `返回值`

  成功：0

  失败：-1

主动断接共享内存区（注意：当一个进程终止时，它当前附接着的所有共享内存区都自动断接掉）。



## 14.5 shmctl函数

```c++
#include <sys/shm.h>
int shmctl(int shmid, int cmd, struct shmid_ds *buff);
```

- `shmid` 共享内存区

- `cmd` 操作命令

  | 命令     | 说明                                                         |
  | -------- | ------------------------------------------------------------ |
  | IPC_RMID | 从系统中删除由shmid标识的共享内存区并拆除它。                |
  | IPC_SET  | 给所指定的共享内存区设置其shmid_ds结构的以下三个成员：<br>  - shm_perm.uid<br>  - shm_perm.git<br>  - shm_perm.mode<br> 它们的值来自buff参数指向的结构中的相应成员。shm_ctime的值也用当前时间替换。 |
  | IPC_STAT | （通过buff参数）向调用者返回所指定共享内存区当前的shmid_ds结构。 |

- `buff` 用于返回共享内存区当前的shmid_ds结构

- `返回值`

  成功：0

  失败：-1

对一个共享内存区的多种操作。



## 14.6 简单的程序

### 14.6.1 shmget程序

```c++
TODO
```

*创建一个指定大小的System V共享内存区*

### 14.6.2 shmrmid程序

```c++
TODO
```

*删除一个System V共享内存区*

### 14.6.3 shmwrite程序

```c++
TODO
```

*打开一个共享内存区，填入一个数据模式*

### 14.6.4 shmread程序

```c++
TODO
```

*打开一个共享内存区，验证其数据模式*

### 14.6.5 例子



### 14.7 共享内存区限制

| 名字   | 说明                           | DUnix 4.0B | Solaris 2.6 |
| ------ | ------------------------------ | ---------- | ----------- |
| shmmax | 一个共享内存区的最大字节数     | 4194304    | 1048576     |
| shmmnb | 一个共享内存区的最小字节数     | 1          | 1           |
| shmmni | 系统范围最大共享内存区标识符数 | 128        | 100         |
| shmseg | 每个进程附接的最大共享内存区数 | 32         | 6           |

*System V共享内存区的典型系统限制*

```c++
TODO
```

*去顶共享内存区的系统限制*



## 14.8 小结

System V共享内存区在概念上与Posix共享内存区类似。最常用的函数调用有以下几个：

- shmget：获取一个标识符。
- shmat：把一个共享内存区附接到调用进程的地址空间。
- 以一个IPC_STAT命令调用shmctl：获取一个已存在共享内存区的大小。
- 以一个IPC_RMID命令调用shmctl：删除一个共享内存区对象。

