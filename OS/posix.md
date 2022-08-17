# POSIX接口

[TOC]



POSIX(Portable Operating System Interface， 可移植操作系统接口)是一个由IEEE(电气和电子工程师学会)制订的标准族。

## 头文件与可选项

### 操作系统类型判断

```c++
__linux__       Defined on Linux
__sun           Defined on Solaris
__FreeBSD__     Defined on FreeBSD
__NetBSD__      Defined on NetBSD
__OpenBSD__     Defined on OpenBSD
__APPLE__       Defined on Mac OS X
__hpux          Defined on HP-UX
__osf__         Defined on Tru64 UNIX (formerly DEC OSF1)
__sgi           Defined on Irix
_AIX            Defined on AIX
_WIN32          Defined on Windows
```

### 必需

| 头文件                            | 说明                 |
| --------------------------------- | -------------------- |
| `<aio.h>`                         | 异步I/O              |
| `<cpio.h>`                        | cpio归档值           |
| `<dirent.h>`                      | 目录项               |
| [`<dlfcn.h>`](#dlfcn.h)           | 动态链接             |
| [`<fcntl.h>`](#fcntl.h)           | 文件控制             |
| `<fnmatch.h>`                     | 文件名匹配类型       |
| `<glob.h>`                        | 路径名模式匹配与生成 |
| `<grp.h>`                         | 组代码               |
| `<iconv.h>`                       | 代码集变换实用程序   |
| `<langinfo.h>`                    | 语言信息常量         |
| `<monetary.h>`                    | 货币类型与函数       |
| [`<netdb.h>`](#netdb.h)           | 网络数据库操作       |
| `<nl_types.h>`                    | 消息类               |
| `<poll.h>`                        | 投票函数             |
| `<pthread.h>`                     | 线程                 |
| `<pwd.h>`                         | 口令文件             |
| `<regex.h>`                       | 正则表达式           |
| `<sched.h>`                       | 执行调度             |
| `<semaphore.h>`                   | 信号量               |
| [`<strings.h>`](#strings.h)       | 字符串操作           |
| `<tar.h>`                         | tar归档值            |
| `<termios.h>`                     | 终端I/O              |
| [`<unistd.h>`](#unistd.h)         | 符号常量             |
| `<wordexp.h>`                     | 字扩充类型           |
| [`<arpa/inet.h>`](#arpa/inet.h)   | 因特网定义           |
| `<net/if.h>`                      | 套接字本地接口       |
| [`<netinet/in.h>`](#netinet/in.h) | 因特网地址族         |
| `<netinet/tcp.h>`                 | 传输控制协议定义     |
| `<sys/mman.h>`                    | 存储管理声明         |
| [`<sys/select.h>`](#sys/select.h) | select函数           |
| [`<sys/socket.h>`](#sys/socket.h) | 套接字接口           |
| [`<sys/stat.h>`](#sys/stat.h)     | 文件状态             |
| `<sys/statvfs.h>`                 | 文件系统信息         |
| `<sys/times.h>`                   | 进程时间             |
| `<sys/types.h>`                   | 基本系统数据类型     |
| `<sys/un.h>`                      | UNIX域套接字定义     |
| `<sys/utsname.h>`                 | 系统名               |
| `<sys/wait.h>`                    | 进程控制             |

### 可选

| 头文件       | 说明          |
| ------------ | ------------- |
| `<mqueue.h>` | 消息队列      |
| `<spawn.h>`  | 实时spawn接口 |

### XSI可选

| 头文件             | 说明             |
| ------------------ | ---------------- |
| `<fmtmsg.h>`       | 消息显示结构     |
| `<ftw.h>`          | 文件树漫游       |
| `<libgen.h>`       | 路径名管理函数   |
| `<ndbm.h>`         | 数据库操作       |
| `<search.h>`       | 搜索表           |
| `<syslog.h>`       | 系统出错日志记录 |
| `<utmpx.h>`        | 用户账户数据库   |
| `<sys/ipc.h>`      | IPC              |
| `<sys/msg.h>`      | XSI消息队列      |
| `<sys/resource.h>` | 资源操作         |
| `<sys/sem.h>`      | XSI信号量        |
| `<sys/shm.h>`      | XSI共享存储      |
| `<sys/time.h>`     | 时间类型         |
| `<sys/uio.h>`      | 矢量I/O操作      |

### 可选项

| 选项码 | 符号常量                            | 说明                             |
| ------ | ----------------------------------- | -------------------------------- |
| ADV    | `_POSIX_ADVISORY_INFO`              | 建议性信息（实时）               |
| CPT    | `_POSIX_CPUTIME`                    | 进程CPU时间时钟（实时）          |
| FSC    | `_POSIX_FSYNC`                      | 文件同步                         |
| IP6    | `_POSIX_IPV6`                       | IPv6接口                         |
| ML     | `_POSIX_MEMLOCK`                    | 进程存储区加锁（实时）           |
| MLR    | `_POSIX_MEMLOCK_RANGE`              | 存储区域加锁（实时）             |
| MON    | `_POSIX_MONOTONIC_CLOCK`            | 单调时钟（实时）                 |
| MSG    | `_POSIX_MESSAGE_PASSING`            | 消息传送（实时）                 |
| MX     | `__STDC_IEC_559__`                  | IEC60559浮点选项                 |
| PIO    | `_POSIX_PRIORITIZED_IO`             | 优先输入和输出                   |
| PS     | `_POSIX_PRIORITIZED_SCHEDULING`     | 进程调度（实时）                 |
| RPI    | `_POSIX_THREAD_ROBUST_PRIO_INHERIT` | 健壮的互斥量优先权继承（实时）   |
| RPP    | `_POSIX_THREAD_ROBUST_PRIO_PROTECT` | 健壮的互斥量优先权保护（实时）   |
| RS     | `_POSIX_RAW_SOCKETS`                | 原始套接字                       |
| SHM    | `_POSIX_SHARED_MEMORY_OBJECTS`      | 共享存储对象（实时）             |
| SIO    | `_POSIX_SYNCHRONIZED_IO`            | 同步输入和输出（实时）           |
| SPN    | `_POSIX_SPAWN`                      | 产生（实时）                     |
| SS     | `_POSIX_SPORADIC_SERVER`            | 进程阵发性服务器（实时）         |
| TCT    | `_POSIX_THREAD_CPUTIME`             | 线程CPU时间时钟（实时）          |
| TPI    | `_POSIX_THREAD_PRIO_INHERIT`        | 非健壮的互斥量优先权继承（实时） |
| TPP    | `_POSIX_THREAD_PRIO_PROTECT`        | 非健壮的互斥量优先权保护（实时） |
| TPS    | `_POSIX_THREAD_PRIORITY_SCHEDULING` | 线程执行调度（实时）             |
| TSA    | `_POSIX_THREAD_ATTR_STACKADDR`      | 线程栈地址属性                   |
| TSH    | `_POSIX_THREAD_PROCESS_SHARED`      | 线程进程共享同步                 |
| TSP    | `_POSIX_THREAD_SPORADIC_SERVER`     | 线程阵发性服务器（实时）         |
| TSS    | `_POSIX_THREAD_ATTR_STACKSIZE`      | 线程栈长度属性                   |
| TYM    | `_POSIX_TYPED_MEMORY_OBJECTS`       | 类型存储对象（实时）             |
| XSI    | `_POSIX_UNIX`                       | X/Open扩充接口                   |

---



## arpa/inet.h

### inet_aton 

`int inet_aton(const char *strptr, struct in_addr *addrptr)`

将c字符串转换成一个32位的网络字节序二进制值

### inet_ntoa

`char *inet_ntoa(struct in_addr inaddr)` 

将32位的网络字节序二进制IPv4地址转换成相应的点分十进制字符串。**注意：返回值所指向的字符串驻留在静态内存中，该函数不可重入！！！**

### inet_pton

`int inet_pton(int family, const char *strptr, void *addrptr)`

将字符串格式转换到二进制格式

### net_ntop

`const char *inet_ntop(int family, const void *addrptr, char *strptr, size_t len)` 

将二进制格式转换到字符串格式

[返回顶部](#POSIX接口)

---



## dirent.h

### closedir

`int closedir(DIR *dp)`

- `dp` 目录指针

- `返回值`

  成功：0；

  失败：-1；

*关闭目录流*

### opendir/fdopendir

`DIR *opendir(const char *pathname)`
`DIR *fdopendir(int fd)`

- `pathname` 路径名

- `fd` 文件描述符

- `返回值`

  成功：目录指针；

  失败：NULL；

*把文件/文件描述符转换成目录。*

### readdir

`struct dirent *readdir(DIR *dp)`

- `dp` 目录指针
- `返回值`
  - 成功：目录指针；
  - 在目录尾或失败：NULL；

*读目录流并返回第一个目录项。*

### rewinddir

`void rewinddir(DIR *dp)`

- dp` 目录指针
- `返回值`
  - 成功：o；
  - 失败：-1；

*设置目录流读取位置为原来开头的读取位置*

### seekdir

`void seekdir(DIR *dp, long loc)`

- `dp` 目录指针
- `loc` 偏移量

*设置目录流目前的读取位置*

### telldir

`long telldir(DIR *dp)`

- dp` 目录指针
- `返回值` 偏移量

*返回目录流目前的读取位置*

---



## dlfcn.h

### dlopen

`void *dlopen(const char *filename, int flags)`

加载动态共享库文件；如果`filename`为NULL，则返回的句柄用于主程序。如果`filename`指定的对象依赖于其它共享对象，动态链接器也会自动加载这些对象。具体见：[动态链接库#dlopen](dll.md)

### dlsym

`void *dlsym(void *handle, const char *symbol)`

解析动态链接库符号，返回符号对应的地址；具体见：[动态链接库#dlsym](dll.md)

### dlclose

`int dlclose(void *handle)`

关闭指定句柄的动态链接库；具体见：[动态链接库#dlclose](dll.md)

[返回顶部](#POSIX接口)

---



## fcntl.h

### fcntl

`int fcntl(int fd, int cmd, ...)`

- `fd` 文件描述符
- `cmd` 命令
  - `F_DUPFD` 复制文件描述符，新文件描述符作为函数值返回。
  - `F_DUPFD_CLOEXEC` 复制文件描述符，设置与新描述符关联的FD_CLOEXEC文件描述符标志的值，返回新文件描述符。
  - `F_GETFD` 对应于fd的文件描述符标志作为函数值返回。
  - `F_SETFD` 对于fd设置文件描述符标志。
  - `F_GETFL` 对应于fd的文件状态标志作为函数值返回。
  - `F_SETFL` 将文件状态标志设置为第3个参数的值（取为整型值），此参数可以为：O_APPEND,O_NONBLOCK,O_SYNC,O_DSYNC,O_RSYNC,O_FSYNC,O_ASYNC。
  - `F_GETOWN` 获取当前接受SIGIO和SIGURG信号的进程ID或进程组ID。
  - `F_SETOWN` 设置接收SIGIO和SIGURG信号的进程ID或进程组ID。
- 返回值
  - 成功：取决于cmd的值
  - 失败：-1

fcntl有5种功能，具体功能取决于cmd的值：

1. 复制一个已有的描述符
2. 获取/设置文件描述符标志
3. 获取/设置文件状态标志
4. 获取/设置异步I/O所有权
5. 获取/设置记录锁

具体见：[I/O#fcntl](io.md)

### open/openat

`int open(const char* path, int oflag, ...)`

`int openat(int fd, const char* path, int oflag, ...)`

打开文件/目录；具体见：[I/O#open/openat](io.md)

### close

`int close(int fd)`

- `fd` 文件描述符
- 返回值
  - 成功：0
  - 失败：-1

*关闭文件。*

### create

`int create(const char* path, mode_t mode)`

创建一个新文件；具体见：[I/O#create](io.md)

[返回顶部](#POSIX接口)

---



## netdb.h

### getnameinfo

`int getnameinfo(const struct sockaddr *sockaddr, socklen_t addrlen, char *host, size_t hostlen, char *service, size_t servlen, int flags )`

返回描述套接字主机的字符串和服务字符串

[返回顶部](#POSIX接口)

---



## netinet/in.h

### htons

`uint16_t htons(uint16_t host16bitvalue)` 

主机字节序转网络字节序(16位)

### htonl

`uint32_t htonl(uint32_t host32bitvalue)` 

主机字节序转网络字节序(32位)

### ntohs

`uint16_t ntohs(uint16_t net16bitvalue)` 

网络字节序转主机字节序(16位)

### nthol

`uint32_t ntohl(uint32_t net32bitvalue)` 

网络字节序转主机字节序(32位)

[返回顶部](#POSIX接口)

---



## sys/select.h

### select

`int select(int maxfdp1, fd_set *readset, fd_set *writeset, fd_set *exceptset, const struct timeval *timeout)`

允许进程指示内核等待多个事件中的任何一个发生，并只在有一个或多个时间发生或经历一段指定的时间后才唤醒它。具体见：[I/O#select](NET/io.md)

[返回顶部](#POSIX接口)

---



## stdio

### fflush

`int fflush(FILE *fp)`

- `fp` 文件流

- `返回值`

  成功：0

  失败：EOF

*强制刷出一个流*

### fopen/freopen/fdopen

`FILE *fopen(const char *restrict pathname, const char *restrict type)`
`FILE *freopen(const char *restrict pathname, const char *restrict type, FILE *restrict fp)`
`FILE *fdopen(int fd, const char *type)`

- `pathname` 路径

- `type` 打开模式

  | type         | 说明                                     | open(2)标志                     |
  | ------------ | ---------------------------------------- | ------------------------------- |
  | r或rb        | 为读而打开。                             | O_RDONLY                        |
  | w或wb        | 把文件截断至0长，或为写而创建。          | O_WRONLY \| O_CREAT \| O_TRUNC  |
  | a或ab        | 追加：为在文件尾写而打开，或为写而创建。 | O_WRONLY \| O_CREAT \| O_APPEND |
  | r+或r+b或rb+ | 为读和写而打开。                         | O_RDWR                          |
  | w+或w+b或wb+ | 把文件截断至0长，或为读和写而打开。      | O_RDWR \| O_CREAT \| O_TRUNC    |
  | a+或a+b或ab+ | 为在文件尾读和写而打开或创建。           | O_RDWR \| O_CREAT \| O_APPEND   |

- `fd` 文件描述符

- `返回值`

  成功：文件指针

  失败：NULL

*fopen：打开一个标准I/O流*

*freopen：重新打开一个标准I/O流*

*fdopen：使一个标准的I/O流与已有的文件描述符结合*

### fwide

`int fwide(FILE *fp, int mode)`

- `fp` 文件流

- `mode` 模式

  - `< 0` 试图使指定的流是字节定向的；
  - `= 0` 将不试图设置流的定向，但返回标识该流定向的值；
  - `> 0` 试图使指定的流是宽定向的。

- `返回值`

  流是宽定向的：`> 0`

  流是未定向的：`0`

  流是字节定向的：`< 0`

*设置流的定向*

### rename/renameat

`int rename(const char *oldname, const char *newname)`
`int renameat(int oldfd, const char *oldname, int newfd, const char *newname)`

- `oldname` 旧名字

- `newname` 新名字

- `oldfd` 旧文件描述符

- `newfd` 新文件描述符

- `返回值` 

  成功：0

  失败：-1

*对文件/目录进行重命名*

### remove

`int remove(const char *pathname)`

- `pathname` 路径

- `返回值` 

  成功：0

  失败：-1

*解除对一个文件或目录的链接（对于文件，等同于unlink；对于目录，等同于rmdir）。*

### setbuf/setvbuf

`void setbuf(FILE *restrict fp, char *restrict buf)`
`int setvbuf(FILE *restrict fp, char *restrict buf, int mode, size_t size)`

- `fp` 文件流

- `buf` 缓冲区（长度为BUFSIZ）

- `mode` 缓冲类型

  - `_IOFBF` 全缓冲
  - `_IOLBF` 行缓冲
  - `_IONBF` 不带缓冲

- `size` 缓冲区长度

- `返回值`

  成功：0

  失败：非0

*设置缓冲区属性*

---



## string.h

### memset

`void *memset(void *dest, int c, size_t len)`

设置字符串为指定值

### memcpy

`void *memcpy(void *dest, const void *src, size_t nbytes)`

复制字符串

### memcmp

`int memcmp(const void *ptr1, const void *ptr2, size_t nbytes)`

比较字符串

### perror

`void perror(const char *msg)`

- `msg` 返回的错误信息

*根据当前错误码输出错误信息*

### strerror

`char *strerror(int errnum)`

- `errnum` 错误码
- `返回值` 指向消息字符串的指针

*将错误码映射为错误信息字符串*

[返回顶部](#POSIX接口)

---



## strings.h

### bzero

`void bzero(void *dest, size_t nbytes)` 

 设置字符串的值为0

### bcopy

`void bcopy(const void *src, void *dest, size_t nbytes)` 

复制字符串

### bcmp

`int bcmp(const void *ptr1, const void *ptr2, size_t nbytes)` 

比较字符串

### memset

`void *memset(void *dest, int c, size_t len)`

设置字符串为指定值

### memcpy

`void *memcpy(void *dest, const void *src, size_t nbytes)`

复制字符串；**注意：当dest和src重叠时，memcpy操作结果无法预料**

### memcmp

`int memcmp(const void *ptr1, const void *ptr2, size_t nbytes)` 

比较字符串

[返回顶部](#POSIX接口)

---



## sys/socket.h

### connect

`int connect(int sockfd, const struct sockaddr *servaddr, socklen_t addrlen)`

建立与TCP服务器的连接；具体见[unix网络编程-卷一#第四章#connect函数](NOTE/UNIX_NETWORK_PROGRAMMING_V1/chapter4.md)

### bind

`int bind(int sockfd, const struct sockaddr *myaddr, socklen_t addrlen)`

把一个本地协议地址赋予一个套接字；具体见[unix网络编程-卷一#第四章#bind函数](NOTE/UNIX_NETWORK_PROGRAMMING_V1/chapter4.md)。

### listen

`int listen(int sockfd, int backlog)` 

把一个未连接的套接字转化为一个被动套接字，指示内核应接受指向该套接字的连接请求，同时设定排队的套接字队列的最大长度。**注意：此函数仅由TCP服务器调用**；具体见[unix网络编程-卷一#第四章#listen函数](NOTE/UNIX_NETWORK_PROGRAMMING_V1/chapter4.md)。

### accept

`int accept(int sockfd, struct sockaddr *cliaddr, socklen_t *addrlen)`

从已完成连接队列头返回下一个已完成连接，如果已完成连接队列为空，那么进程被投入睡眠；具体见[unix网络编程-卷一#第四章#accept函数](NOTE/UNIX_NETWORK_PROGRAMMING_V1/chapter4.md)。

[返回顶部](#POSIX接口)

---



## sys/stat.h

### chmod/fchmod/fchmodat

`int chmod(const char *pathname, mode_t mode)`

`int fchmod(int fd, mode_t mode)`

`int fchmodat(int fd, const char *pathname, mode_t mode, int flag)`

- `fd`文件描述符
- `pathname` 路径
- `mode` 访问权限
- `flag` 用于改变fchmodat的行为

*chmod：更改指定路径上文件的访问权限*

*fchmod：更改已打开文件的访问权限*

*fchmodat：以指定行为来更改绝对/相对路径的文件的访问权限*

### fstat

`int fstat(int fd, struct stat *buf)`

- `fd` 文件描述符
- `buf` 用于返回文件信息
- `返回值`

  - 成功：0
  - 失败：-1

*获取文件描述符指向的文件的信息*

### fstatat

`int fstatat(int fd, const char *restrict pathname, struct stat *restrict buf, int flag)`

- `fd` 文件描述符

- `pathname` 文件路径

- `buf` 用于返回文件信息

- `flag` 标志

- `返回值`

  - 成功：0
  - 失败：-1

*获取目录的文件统计信息*

### lstat

`int lstat(const char *restrict pathname, struct stat *restrict buf)`

- `pathname` 文件路径
- `buf` 用于返回文件信息
- `返回值`

  - 成功：0
  - 失败：-1

*获取符号链接的有关信息*

### mkdir/mkdirat

`int mkdir(const char *pathname, mode_t mode)`
`int mkdirat(int fd, const char *pathname, mode_t mode)`

- `pathname` 路径

- `mode` 文件访问权限

- `fd` 文件描述符

- `返回值`

  成功：0

  失败：-1

*创建一个新的空目录*

### stat

`int stat(const char *restrict pathname, struct stat *restrict buf)`

- `pathname` 文件路径
- `buf` 用于返回文件信息
- `返回值`

  - 成功：0
  - 失败：-1

*获取指定路径上文件的信息*

### umask

`mode_t umask(mode_t cmask)`

- `cmask` 访问权限位（见上面“9个访问权限位，取自<sys/stat.h>”）
- `返回值` 由之前的文件模式所创建的屏蔽字

*为进程设置文件模式创建屏蔽字*

### utimestat/futimens

`int utimensat(int fd, const char *path, const struct timespec times[2], int flag)`

`int futimens(int fd, const struct timespec times[2])`

- `fd` 文件套接字

- `times` 时间值

  - [0]：访问时间
  - [1]：修改时间

- `path` 文件路径

- `flag` 标记

- `返回值`

  成功：0

  失败：-1

*修改文件的时间（精度：ns）*

---



## sys/time.h

### utimes

`int utimes(const char *pathname, const struct timeval times[2])`

- `pathname` 路径名

- `times` 时间值

- `返回值`

  成功：0

  失败：-1

*修改路径的时间*

---



## unistd.h

### access/faccessat

`int access(const char *pathname, int mode)`

`int faccessat(int fd, const char *pathname, int mode, int flag)`

- `fd` 文件描述符

- `pathname` 绝对/相对路径

- `mode` 模式

- `flags` 标志

- `返回值`

  - 成功：0
  - 失败：-1

*进行访问权限测试*。具体见：[I/O#access/faccessat](io.md)

### chdir/fchdir

`int chdir(const char *pathname)`

`int fchdir(int fd)`

- `pathname` 路径名
- `fd` 文件描述符
- `返回值`
  - 成功：0；
  - 失败：-1；

*更改当前工作目录。

### chown/fchown/fchownat/lchown

`int chown(const char *pathname, uid_t owner, gid_t group)`

`int fchown(int fd, uid_t owner, git_t group)`

`int fchownat(int fd, const char *pathname, uid_t owner, gid_t group, int flag)`

`int lchown(const char *pathname, uid_t owner, gid_t group)`

- `pathname` 路径
- `fd` 文件描述符
- `owner` 用户ID
- `group` 组ID
- `flag` 标志

*更改文件/链接的用户ID和组ID*

### close

`int close(int fd)`

关闭文件；具体见：[I/O#close](io.md)

### dup/dup2

`int dup(int fd)`
`int dup2(int fd, int fd2)`

- `fd` 待复制的文件描述符
- `fd2` 用来指定返回的文件描述符的值
  - 如果`fd2`已经打开，先关闭它
  - 如果`fd`等于`fd2`，则`dup2`返回`fd2`而不关闭它
  - 其它情况，`fd2`的`FD_CLOEXEC`文件描述符标志被清除，`fd2`在进程调用exec时是打开状态
- 返回值
  
  成功：新的文件描述符
  
  失败：-1

复制一个现有的文件描述符；具体见：[I/O#dup/dup2](io.md)

### fdatasync

`int fdatasync(int fd)`

`fdatasync`类似于`fsync`，但它只影响文件的数据部分。而除数据外，fsync还会同步更新文件的属性。具体见：[I/O#fdatasync](io.md)

### fpathconf

`long fpathconf(int filedes, int name)`

- `name` 限制名

- `filedes` 文件描述符

- `返回值`

  成功：运行时限制

  失败：-1

*获得运行时限制*

### getcwd

`char *getcwd(char *buf, size_t size)`

- `buf` 缓冲区
- `size` 缓冲区长度（字节，路径名+null）
- `返回值`
  - 成功：buf
  - 失败：NULL

*返回当前目录的完整绝对路径。*

### link/linkat

`int link(const char *existingpath, const char *newpath)`
`int linkat(int efd, const char *existingpath, int nfd, const char *newpath, int flag)`

- `existingpath` 现有文件路径

- `newpath` 链接文件路径（需要保证此路径不存在）

- `efd` 现有文件的文件描述符

- `nfd` 链接文件的文件描述符

- `newpath` 链接文件路径

- `flag` 标志，标识创建链接的链接or文件的链接

- `返回值`

  成功：0

  失败：-1

*创建一个指向现有文件的链接*

### lseek

`off_t lseek(int fd, off_t offset, int whence)`

- `fd` 文件描述符
- `offset` 偏移量
- `whence` 位置
  - `SEEK_SET` 将文件的偏移量设置为距文件开始处offset个字节
  - `SEEK_CUR` 将文件偏移量设置为其当前值加offset，offset可正可负
  - `SEEK_END` 将文件的偏移量设置为文件长度加offset，offset可正可负
- 返回值
  - 成功：新的文件偏移量
  - 失败：-1

为一个打开的文件设置偏移量；具体见：[I/O#lseek](io.md)

### pathconf

`long pathconf(const char *pathname, int name)`

- `name` 限制名
- `pathname` 文件路径

*获得运行时限制*

### pread

`ssize_t pread(int fd, void *buf, size_t nbytes, off_t offset)`

*以原子方式读文件*

### pwrite

`ssize_t pwrite(int fd, const void* buf, size_t nbytes, off_t offset)`

*以原子方式写文件*

### read/readlink/readlinkat

`ssize_t read(int fd, void *buf, size_t nbytes)`

`ssize_t readlink(const char *restrict pathname, char *restrict buf, size_t bufsize)`

- `fd` 文件描述符
- `buf` 缓冲区
- `nbytes` 要求读的长度
- `bufsize` 缓冲区长度
- 返回值
  - 成功：读到的字节数
  - 已到文件尾：0
  - 失败：-1

*从文件中读数据；*具体见：[I/O#read](io.md)

### rmdir

`int rmdir(const char *pathname)`

- `pathname` 路径
- `返回值`
  - 如果没有其它进程打开此目录，释放由此目录占用的空间；
  - 如果有1个或多个进程打开此目录，在函数返回前删除最后一个连接及`.`和`..`项；

*将目录的链接计数设置为0。*

### symlink/symlinkat

`int symlink(const char *actualpath, const char *sympath)`
`int symlinkat(const char *actualpath, int fd, const char *sympath)`

- `actualpath` 真实地址

- `sympath` 符号链接

- `fd` 文件描述符

- `返回值`

  成功：0

  失败：-1

*创建一个符号链接*

### sync/fsync/fdatasync

`void sync(void)`

`int fsync(int fd)`

`int fdatasync(int fd)`

- `fd` 文件描述符
- 返回值
  - 成功：0
  - 失败：-1

`sync`只是将所有修改过的块缓冲区排入写队列，然后就返回，**它并不等实际写磁盘操作结束。**具体见：[I/O#sync](io.md)

`fsync`只对由文件描述符fd指定的一个文件起作用，并且等待写磁盘操作结束才返回。具体见：[I/O#fsync](io.md)

`fdatasync`类似于`fsync`，但它只影响文件的数据部分。而除数据外，fsync还会同步更新文件的属性。具体见：[I/O#fdatasync](io.md)

### sysconf

`long sysconf(int name)`

- `name` 限制名

- `返回值`

  成功：运行时限制

  失败：-1

*获得运行时限制*

### truncate/ftruncate

`int truncate(const char *pathname, off_t length)`

`int ftruncate(int fd, off_t length)`

- `fd` 文件描述符
- `pathname` 路径
- `length` 截断后的长度

*根据文件路径/描述符来截断文件；如果截断前文件长度>length，则length以外的数据将无法访问；如果截断前文件长度<length，文件尾端到length之间的数据读作0。*

### unlink/unlinkat

`int unlink(const char *pathname)`
`int unlinkat(int fd, const char *pathname, int flag)`

- `pathname` 路径

- `fd` 文件描述符

- `flag` 标志

- `返回值`

  成功：0

  出错：-1

*删除目录项（只有当链接计数达到0时，该文件的内容才可被删除！！！）*

### write

`ssize_t write(int fd, const void* buf, size_t nbytes)`

- `fd` 文件描述符
- `buf` 缓冲区
- `nbytes` 要写入的字节数
- 返回值
  - 成功：已写的字节数==要写入的字节数
  - 失败：-1或已写的字节数<要写入的字节数

写数据到文件；具体见：[I/O#write](io.md)

[返回顶部](#POSIX接口)

---



## 其它

### memcpy

TODO

[返回顶部](#POSIX接口)

---



## 参考

- <<UNIX环境高级编程>> 第三版