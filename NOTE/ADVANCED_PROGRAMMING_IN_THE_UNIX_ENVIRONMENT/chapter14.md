# 第十四章 高级I/O

[TOC]



## 14.1 引言



## 14.2 非阻塞I/O

对于一个给定的描述符有两种方法对其指定非阻塞I/O：

1. 如果调用open获得描述符，则可指定`O_NONBLOCK`标志。
2. 对于已经打开的一个描述符，则可调用`fcntl`，由该函数打开`O_NONBLOCK`文件状态标志。

例：

```c++
TODO
```

*长的非阻塞write*



## 14.3 记录锁

`记录锁（record locking）`当一个进程正在读或修改文件的某个部分时，它可以阻止其它进程修改同一文件区。

![14_1](res/14_1.png)

*各种UNIX系统支持的记录锁*

```c++
struct flock {
    short l_type;
    off_t l_start;
    short l_whence;
    off_t l_len;
    pid_t l_pid;
};
```

- `l_type` 锁类型
  - `F_RDLCK` 共享读锁
  - `F_WRLCK` 独占性写锁
  - `F_UNLCK` 解锁一个区域
- `l_start` 相对偏移量
- `l_whence` 相对偏移量起点
- `l_len` 字节长度
- `l_pid` 进程ID

```c++
#include <fcntl.h>
int fcntl(int filedes, int cmd, ... /* struct flock *flockptr */ );
```

- `filedes` 
- `cmd` 参数
  - `F_GETLK`
  - `F_SETLK`
  - `F_SETLKW`
- `返回值`

**