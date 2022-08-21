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

| 头文件                              | 说明                 |
| ----------------------------------- | -------------------- |
| `<aio.h>`                           | 异步I/O              |
| `<cpio.h>`                          | cpio归档值           |
| [`<dirent.h>`](#dirent.h)           | 目录项               |
| [`<dlfcn.h>`](#dlfcn.h)             | 动态链接             |
| [`<fcntl.h>`](#fcntl.h)             | 文件控制             |
| `<fnmatch.h>`                       | 文件名匹配类型       |
| `<glob.h>`                          | 路径名模式匹配与生成 |
| [`<grp.h>`](#grp.h)                 | 组代码               |
| `<iconv.h>`                         | 代码集变换实用程序   |
| `<langinfo.h>`                      | 语言信息常量         |
| `<monetary.h>`                      | 货币类型与函数       |
| [`<netdb.h>`](#netdb.h)             | 网络数据库操作       |
| `<nl_types.h>`                      | 消息类               |
| `<poll.h>`                          | 投票函数             |
| [`<pthread.h>`](#pthread.h)         | 线程                 |
| `<pwd.h>`                           | 口令文件             |
| `<regex.h>`                         | 正则表达式           |
| `<sched.h>`                         | 执行调度             |
| `<semaphore.h>`                     | 信号量               |
| [`<strings.h>`](#strings.h)         | 字符串操作           |
| `<tar.h>`                           | tar归档值            |
| `<termios.h>`                       | 终端I/O              |
| [`<unistd.h>`](#unistd.h)           | 符号常量             |
| `<wordexp.h>`                       | 字扩充类型           |
| [`<arpa/inet.h>`](#arpa/inet.h)     | 因特网定义           |
| `<net/if.h>`                        | 套接字本地接口       |
| [`<netinet/in.h>`](#netinet/in.h)   | 因特网地址族         |
| `<netinet/tcp.h>`                   | 传输控制协议定义     |
| `<sys/mman.h>`                      | 存储管理声明         |
| [`<sys/select.h>`](#sys/select.h)   | select函数           |
| [`<sys/socket.h>`](#sys/socket.h)   | 套接字接口           |
| [`<sys/stat.h>`](#sys/stat.h)       | 文件状态             |
| `<sys/statvfs.h>`                   | 文件系统信息         |
| [`<sys/times.h>`](#sys/times.h)     | 进程时间             |
| `<sys/types.h>`                     | 基本系统数据类型     |
| `<sys/un.h>`                        | UNIX域套接字定义     |
| [`<sys/utsname.h>`](#sys/utsname.h) | 系统名               |
| `<sys/wait.h>`                      | 进程控制             |

### 可选

| 头文件       | 说明          |
| ------------ | ------------- |
| `<mqueue.h>` | 消息队列      |
| `<spawn.h>`  | 实时spawn接口 |

### XSI可选

| 头文件                    | 说明             |
| ------------------------- | ---------------- |
| `<fmtmsg.h>`              | 消息显示结构     |
| `<ftw.h>`                 | 文件树漫游       |
| `<libgen.h>`              | 路径名管理函数   |
| `<ndbm.h>`                | 数据库操作       |
| `<search.h>`              | 搜索表           |
| [`<syslog.h>`](#syslog.h) | 系统出错日志记录 |
| `<utmpx.h>`               | 用户账户数据库   |
| `<sys/ipc.h>`             | IPC              |
| `<sys/msg.h>`             | XSI消息队列      |
| `<sys/resource.h>`        | 资源操作         |
| `<sys/sem.h>`             | XSI信号量        |
| `<sys/shm.h>`             | XSI共享存储      |
| `<sys/time.h>`            | 时间类型         |
| `<sys/uio.h>`             | 矢量I/O操作      |

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

### htonl

`uint32_t htonl(uint32_t hostint32)`

- `hsotint32` 主机字节序
- `返回值` 以网络字节序表示的32位整型数

*主机字节序转网络字节序*

### htons

`uint16_t htons(uint16_t hostint16)`

- `hostint16` 主机字节序
- `返回值` 以网络字节序表示的16位整型数

*主机字节序转网络字节序*

### inet_aton 

`int inet_aton(const char *strptr, struct in_addr *addrptr)`

- `strptr` 需要转换的c字符串
- `addrptr` 用来存储网络字节序二进制值的指针

*将c字符串转换成一个32位的网络字节序二进制值*

### inet_ntoa

`char *inet_ntoa(struct in_addr inaddr)`

- `inaddr`32位网络字节序二进制IPV4地址

*将32位的网络字节序二进制IPv4地址转换成相应的点分十进制字符串*

### inet_ntop

`const char *inet_ntop(int domain, const void *restrict addr, char *restrict str, socklen_t size)` 

- `domain` 域（仅支持`AF_INET`和`AF_INET6`）

- `addr` 网络字节序地址

- `str` 文本字符串地址

- `size` 文本字符串长度；

- `返回值`

  成功：地址字符串指针

  失败：NULL

*将网络字节序的二进制地址转换为文本字符串地址*

### inet_pton

`int inet_pton(int domain, const char *restrict str, void *restrict addr)`

- `domain` 地址族（仅支持`AF_INET`和`AF_INET6`）`

- `str` 文本字符串地址

- `addr` 网络字节序地址

- `返回值`

  成功：1

  格式无效：0

  出错：-1

*将文本字符串地址转换为网络字节序的二进制地址*

### ntohl

`uint32_t ntohl(uint32_t netint32)`

- `netint32` 网络字节序
- `返回值` 以主机字节序表示的32位整型数

*网络字节序转主机字节序*

### ntohs

`uint16_t ntohs(uint16_t netint16)`

- `netint16` 网络字节序
- `返回值` 以主机字节序表示的16位整型数

*网络字节序转主机字节序*

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

### fdopendir

`DIR *fdopendir(int fd)`

- `pathname` 路径名

- `fd` 文件描述符

- `返回值`

  成功：目录指针；

  失败：NULL；

*把文件描述符转换成目录。*

### opendir

`DIR *opendir(const char *pathname)`

- `pathname` 路径名

- `fd` 文件描述符

- `返回值`

  成功：目录指针；

  失败：NULL；

*把文件转换成目录。*

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

### getopt

`int getopt(int argc, const *const argv[], const char *options)`

- `argc` 参数数量

- `argv` 参数数组

- `options` 命令支持的选项字符

- `返回值`

  成功：下一个选项字符

  全部选项处理完毕：-1

*按照一致的方式来处理命令行选项*

### open

`int open(const char* path, int oflag, ...)`

打开文件/目录；具体见：[I/O#open](io.md)

### openat

`int openat(int fd, const char* path, int oflag, ...)`

打开文件/目录；具体见：[I/O#openat](io.md)

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



## grp.h

### endgrent

`void endgrent(void)`

`关闭组文件文件中的条目`

### getgrent

`struct group *getgrent(void)`

- `返回值`

  成功：group指针

  失败/到达文件结尾：NULL

*搜索组文件中的条目*

### getgrnam

`struct group *getgrnam(const char *name)`

- `name` 组名

- `返回值`

  成功：group指针

  失败：NULL

*根据组名查看组信息*

### getgrgid

`struct group *getgrgid(gid_t gid)`

- `gid` 组ID

- `返回值`

  成功：group指针

  失败：NULL

*根据数值组ID查看组信息*

### setgrent

`void setgrent(void)`

*打开组文件文件中的条目*

[返回顶部](#POSIX接口)

---



## netdb.h

### endhostent

`void endhostent(void)`

`关闭主机数据文件信息`

### endservent

`void endservent(void)`

*关闭服务数据库*

### endnetent

`void endnetent(void)`

*关闭网络名字和网络号文件信息*

### endprotoent

`void endprotoent(void)`

*关闭`/etc/protocols`文件*

### freeaddrinfo

`void freeaddrinfo(struct addrinfo *ai)`

- `ai` 地址

*释放地址结构*

### gai_strerror

`const char *gai_strerror(int error)`

- `error` 错误码
- `返回值` 指向描述错误的支付穿指针

*将错误码转换成错误消息*

### getaddrinfo

`int getaddrinfo(const char *restrict host, const char *restrict service, const struct addrinfo *restrict hint, struct addrinfo **restrict res)`

- `host` 主机名

- `service` 服务名

- `hint` 地址过滤模板

- `res` 地址链表

- `ai`

- `返回值`

  成功：0

  失败：非0错误码

*将主机名和服务名映射到一个地址*

### gethostent

`struct hostent *gethostent(void)`

- `返回值`

  成功：指针

  失败：NULL

*返回主机数据文件信息*

### getnameinfo

`int getnameinfo(const struct sockaddr *restrict addr, socklen_t alen, char *restrict host, socklen_t hostlen, char *restrict service, socklen_t servlen, unsigned int flags)`

- `addr` 套接字地址

- `alen` 套接字地址长度

- `host` 返回的主机名

- `hostlen` host字符串长度

- `service` 返回的服务名

- `servlen` service字符串长度

- `flags` 标志

  | 标志           | 描述                                           |
  | -------------- | ---------------------------------------------- |
  | NI_DGRAM       | 服务基于数据报而非基于流                       |
  | NI_NAMEREQD    | 如果找不到主机名字，将其作为一个错误对待       |
  | NI_NOFQDN      | 对于本地主机，仅返回完全限定域名的节点名字部分 |
  | NI_NUMERICHOST | 以数字形式而非名字返回主机地址                 |
  | NI_NUMERICSERV | 以数字形式而非名字返回服务地址（即端口号）     |

- `返回值`

  成功：0

  失败：非0值

*将地址转换成主机名或服务名*

### getnetbyaddr

TODO

### getnetbyname

TODO

### getprotobyname

`struct protoent *getprotobyname(const char *name)`

- `name` 协议名字

- `返回值`

  成功：protoent指针

  失败：NULL

*根据协议名字返回协议信息*

### getprotobynumber

`struct protoent *getprotobynumber(int proto)`

- `proto` 协议号

- `返回值`

  成功：protoent指针

  失败：NULL

*根据协议号返回协议信息*

### getprotoent

`struct protoent *getprotoent(void)`

- `返回值`

  成功：protoent指针

  失败：NULL

*打开协议文件`/etc/protocols`*

### getservbyname

`struct servent *getservbyname(const char *name, const char *proto)`

- `name` 协议名字

- `proto` 协议号

- `返回值`

  成功：服务的信息指针

  失败：NULL

*服务名来获取服务的信息*

### getservbyport

`struct servent *getservbyport(int port, const char *proto)`

- `proto` 协议号

- `port` 端口号

- `返回值`

  成功：服务的信息指针

  失败：NULL

*通过服务的端口来获取服务的信息*

### getservent

`struct servent *getservent(void)`

- `返回值`

  成功：服务的信息指针

  失败：NULL

*从服务数据库中读取下一个条目*

### setservent

`void setservent(int stayopen)`

- `stayopen` 是否保持打开

  1：持续打开

  0：自动关闭

*打开与服务数据库的连接*

### sethostent

`void sethostent(int stayopen)`

- `stayopen` 输入参数

  非0：使用TCP/IP

  0：使用UDP

*设置主机数据文件信息*

### setnetent

TODO

### setprotoent

`void setprotoent(int stayopen)`

- `stayopen` 是否保持打开

  1：保持打开

  0：自动关闭

*设置打开`/etc/protocols`*后是否自动关闭

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



## poll.h

### poll

`int poll(struct pollfd fdarray[], nfds_t nfds, int timeout)`

- `fdarray` 描述符信息数组

- `nfds` 数组长度

- `timeout` 超时时间

  - `-1` 永远等待；
  - `0` 不等待；
  - `> 0` 等待timeout毫秒；

- `返回值`

  超时：0

  出错：-1

  成功：准备就绪的描述符数

*多路转接*

[返回顶部](#POSIX接口)

---



## pthread.h

### pthread_atfork

`int pthread_atfork(void (*prepare)(void), void (*parernt)(void), void (*child)(void))`

- `prepare` 获取父进程定义的所有锁（在创建子进程前调用）

- `parent` 对prepare获得的所有锁进行解锁（在创建子进程后，fork返回之前的父进程调用）

- `child` 释放prepare获得的所有锁（在fork返回之前调用，fork返回之前的子进程调用）

- `返回值`

  成功：0

  失败：错误码

*清除锁状态*

### pthread_attr_getdetachstate/pthread_attr_setdetachstate

`int pthread_attr_getdetachstate(const pthread_attr_t *restrict attr, int *detachstate)`
`int pthread_attr_setdetachstate(pthread_attr_t *attr, int detachstate)`

- `attr` 属性

- `detachstate` 分离状态

- `返回值`

  成功：0

  失败：错误码

*获取/设置线程分离状态*

### pthread_attr_getstack/pthread_attr_setstack

`int pthread_attr_getstack(const pthread_attr_t *restrict attr, void **restrict stackaddr, size_t *restrict stacksize)`

`int pthread_attr_setstack(const pthread_attr_t *attr, void *stackaddr, size_t *stacksize)`

- `attr` 属性

- `stackaddr` 栈地址指针

- `stacksize` 栈默认大小

- `返回值`

  成功：0

  失败：错误码

*获取/设置线程属性stackaddr（栈地址）和stacksize（栈默认大小）*

### pthread_attr_getstacksize/pthread_attr_setstackszie

`int pthread_attr_getstacksize(const pthread_attr_t *restrict attr, size_t *restrict stacksize)`
`int pthread_attr_setstackszie(pthread_attr_t *attr, size_t stacksize)`

- `attr` 属性

- `stacksize` 值

- `返回值`

  成功：0

  失败：错误码

*获取/设置线程属性stacksize（栈默认大小）*

### pthread_attr_getguardsize/pthread_attr_setguardsize

`int pthread_attr_getguardsize(const pthread_attr_t *restrict attr, size_t *restrict guardsize)`
`int pthread_attr_setguardsize(pthread_attr_t *attr, size_t guardsize)`

- `attr` 属性

- `guardsize` 栈指针警戒线

- `返回值`

  成功：0

  失败：错误码

*获取/设置线程属性guardsize（栈指针警戒线，栈溢出时可以通过信号接受到出错信息）*

### pthread_attr_init/pthread_attr_destroy

`int pthread_attr_init(pthread_attr_t *attr)`
`int pthread_attr_destroy(pthread_attr_t *attr)`

- `attr` 线程属性

  | 名称        | 描述                                 |
  | ----------- | ------------------------------------ |
  | detachstate | 线程的分离状态属性                   |
  | guardsize   | 线程栈末尾的警戒缓冲区大小（字节数） |
  | stackaddr   | 线程栈的最低地址                     |
  | stacksize   | 线程栈的最小长度（字节数）           |

- `返回值`

  成功：0

  失败：错误码

*初始化/反初始化线程*

### pthread_barrier_destroy

`int pthread_barrier_destroy(pthread_barrier_t *barrier)`

- `barrier` 屏障

- `返回值`

  成功：0

  失败：错误码

*反初始化屏障*

### pthread_barrier_init

`int pthread_barrier_init(pthread_barrier_t *restrict barrier, const pthread_barrierattr_t *restrict attr, unsigned int count)`

- `barrier` 屏障

- `attr` 屏障对象属性

- `count` 线程数目

- `返回值`

  成功：0

  失败：错误码

*初始化屏障*

### pthread_barrier_wait

`int pthread_barrier_wait(pthread_barrier_t *barrier)`

- `barrier` 屏障

- `返回值`

  成功：0或`PTHREAD_BARRIER_SERIAL_THREAD`

  失败：错误码

*等待唤醒*

### pthread_barrierattr_destroy

`int pthread_barrierattr_destroy(pthread_barrierattr_t *attr)`

- `attr` 屏障属性

- `返回值`

  成功：0

  失败：错误码

*反初始化 屏障属性*

### pthread_barrierattr_getpshared

`int pthread_barrierattr_getpshared(const pthread_barrierattr_t *restrict attr, int *restrict pshared)`

- attr` 屏障属性

- `pshared` 进程共享属性

- `返回值`

  成功：0

  失败：错误码

*获取屏障属性*

### pthread_barrierattr_setpshared

`int pthread_barrierattr_setpshared(pthread_barrierattr_t *attr, int pshared)`

- `attr` 屏障属性

- `pshared` 进程共享属性

- `返回值`

  成功：0

  失败：错误码

*设置屏障属性*

### pthread_barrierattr_init

`int pthread_barrierattr_init(pthread_barrierattr_t *attr)`

- `attr` 屏障属性

- `返回值`

  成功：0

  失败：错误码

*初始化屏障属性*

### pthread_cancel

`int pthread_cancel(pthread_t tid)`

- `tid` 线程ID

- 返回值

  成功：0

  失败：错误码

*发送终止信号，请求取消同一进程中的其它线程*

### pthread_cond_broadcast

`int pthread_cond_broadcast(pthread_cond_t *cond)`

- `cond` 条件变量

- `返回值`

  成功：0

  失败：错误码

*唤醒所有等待条件的线程*

### pthread_cond_destroy

`int pthread_cond_destroy(pthread_cond_t *cond)`

- `cond` 条件变量

- `返回值`

  成功：0

  失败：错误码

*初始化条件变量*

### pthread_cond_init

`int pthread_cond_init(pthread_cond_t *restrict cond, const pthread_condattr_t *restrict attr)`

- `cond` 条件变量

- `attr` 条件变量属性

- `返回值`

  成功：0

  失败：错误码

*初始化条件变量*

### pthread_cond_signal

`int pthread_cond_signal(pthread_cond_t *cond)`

- `cond` 条件变量

- `返回值`

  成功：0

  失败：错误码

*唤醒一个等待条件的线程*

### pthread_cond_timewait

`int pthread_cond_timewait(pthread_cond_t *restrict cond, pthread_mutex_t *restrict mutex, const struct timespec *restrict tsptr)`

- `cond` 条件变量

- `mutex` 互斥量

- `tsptr` 超时时间

- `返回值`

  成功：0

  失败：错误码

*超时等待条件成立（等待唤醒）*

### pthread_cond_wait

`int pthread_cond_wait(pthread_cond_t *restrict cond, pthread_mutex_t *restrict mutex)`

- `cond` 条件变量

- `mutex` 互斥量

- `返回值`

  成功：0

  失败：错误码

*等待条件成立（等待唤醒）*

### pthread_condattr_destroy

`int pthread_condattr_destroy(pthread_condattr_t *attr)`

- `attr` 条件变量属性

- `返回值`

  成功：0

  失败：错误码

*回收条件变量属性*

### pthread_condattr_getclock

`int pthread_condattr_getclock(const pthread_condattr_t *restrict attr, clockid_t *restrict clock_id)`

- `attr` 条件变量属性

- `clock_id` 时钟id

- `返回值`

  成功：0

  失败：错误编号

*获取条件变量时钟*

### pthread_condattr_getpshared

`int pthread_condattr_getpshared(const pthread_condattr_t *restrict attr, int *restrict pshared)`

- `attr` 线程条件属性

- `pshared` 进程共享属性值

- `返回值`

  成功：0

  失败：错误码

*获取进程共享属性*

### pthread_condattr_init

`int pthread_condattr_init(pthread_condattr_t *attr)`

- attr` 条件变量属性

- `返回值`

  成功：0

  失败：错误码

*初始化条件变量属性*

### pthread_cleanup_pop

`void pthread_cleanup_pop(int execute)`

- `execute` （非0）执行参数

*删除上次执行的线程退出时需要执行的操作*

### pthread_cleanup_push

`void pthread_cleanup_push(void(*rtn)(void *), void *arg)`

- `rtn` 要执行的函数
- `arg` 要执行的函数参数

*指定线程退出时需要执行的操作*

### pthread_condattr_setclock

`int pthread_condattr_setclock(pthread_condattr_t *attr, clockid_t clock_id)`

- `attr` 条件变量属性

- `clock_id` 时钟id

- `返回值`

  成功：0

  失败：错误编号

*设置条件变量时钟*

### pthread_condattr_setpshared

`int pthread_condattr_setpshared(pthread_condattr_t *attr, int pshared)`

- `attr` 线程条件属性

- `pshared` 进程共享属性值

- `返回值`

  成功：0

  失败：错误码

*设置进程共享属性*

### pthread_create

`int pthread_create(pthread_t *restrict tidp, const pthread_attr_t *restrict attr, void *(*start_rtn)(void *), void *restrict arg)`

- `tidp` 指向线程标识符的指针

- `attr` 线程属性

- `start_rtn` 线程函数起始地址

- `arg` 线程函数参数

- 返回值

  成功：0

  失败：错误码

*创建一条线程（注意：线程创建时并不能保证哪个线程会先运行）*

### pthread_detach

`int pthread_detach(pthread_t tid)`

- `tid` 线程ID

- 返回值

  成功：0

  失败：错误码

*分离线程*

### pthread_equal

`int pthread_equal(pthread_t tid1, pthread_t tid2)`

- `tid1` 线程1

- `tid2` 线程2

- 返回值

  非0：相等

  0：不相等

*对两个线程ID进行比较*

### pthread_exit

`void pthread_exit(void *rval_ptr)`

- `rval_ptr` 一个无类型指针，与传给启动例程的单个参数类似；

*退出线程*

### pthread_getconcurrency

`int pthread_getconcurrency(void)`

- `返回值`

  成功：0

  失败：错误码

*获取线程并发度（影响性能）*

### pthread_getspecific

`void *pthread_getspecific(pthread_key_t key)`

- `key` 键

- `返回值`

  成功：线程私有数据

  失败：NULL

*返回与键关联的线程私有数据*

### pthread_join

`int pthread_join(pthread_t thread, void **rval_ptr)`

- `thread` 线程标识符

- `rval_ptr` 指向线程返回值

- 返回值

  成功：0

  失败：错误码

*以**阻塞**的方式等待线程结束*

### pthread_key_create

`int pthread_key_create(pthread_key_t *keyp, void (*destructor)(void *))`

- `keyp` 键

- `destructor` 析构函数

- `返回值`

  成功：0

  失败：错误码

*创建与线程数据关联的键（用于获取对线程私有数据的访问权）*

### pthread_key_delete

`int pthread_key_delete(pthread_key_t *key)`

- `key` 键

- `返回值`

  成功：0

  失败：错误码

*取消键与线程数据的关联*

### pthread_mutex_destroy

`int pthread_mutex_destroy(pthread_mutex_t *mutex)`

- `mutex` 互斥量

- `返回值`

  成功：0

  失败：错误码

*销毁互斥锁*

### pthread_mutex_init

`int pthread_mutex_init(pthread_mutex_t *restrict mutex, const pthread_mutexattr_t *restrict attr)`

- `mutex` 互斥量

- `attr` 互斥量属性

- `返回值`

  成功：0

  失败：错误码

*创建互斥锁*

### pthread_mutex_lock

`int pthread_mutex_lock(pthread_mutex_t *mutex)`

- `mutex` 互斥量

- `返回值`

  成功：0

  失败：错误码

*对互斥量进行加锁*

### pthread_mutex_timedlock

`int pthread_mutex_timedlock(pthread_mutex_t *restrict mutex, const struct timespec *restrict tsptr)`

- `mutex` 互斥量

- `tsptr` 超时时间

- `返回值`

  成功：0

  失败：错误码

*绑定线程阻塞时间（在达到超时时间时不会对互斥量进行加锁，而是返回错误码`ETIMEDOUT`）*

### pthread_mutex_trylock

`int pthread_mutex_trylock(pthread_mutex_t *mutex)`

- `mutex` 互斥量

- `返回值`

  成功：0

  失败：错误码

*尝试对互斥量进行加锁*

### pthread_mutex_unlock

`int pthread_mutex_unlock(pthread_mutex_t *mutex)`

- `mutex` 互斥量

- `返回值`

  成功：0

  失败：错误码

*对互斥量进行解锁*

### pthread_mutexattr_destroy

`int pthread_mutexattr_destroy(pthread_mutexattr_t *attr)`

- `attr` 属性

- `返回值`

  成功：0

  失败：错误码

*回收互斥量属性*

### pthread_mutexattr_getpshared

`int pthread_mutexattr_getpshared(const pthread_mutexattr_t *restrict attr, int *restrict pshared)`

- `attr` 互斥量属性

- `pshared` 进程共享属性值

- `返回值`

  成功：0

  失败：错误码

*获取进程共享属性*

### pthread_mutexattr_gettype

`int pthread_mutexattr_gettype(const pthread_mutexattr_t *restrict attr, int *restrict type)`

- attr` 互斥量属性

- `type` 互斥量类型

- `返回值`

  成功：0

  失败：错误码

*获取互斥量类型*

### pthread_mutexattr_init

`int pthread_mutexattr_init(pthread_mutexattr_t *attr)`

- `attr` 属性

- `返回值`

  成功：0

  失败：错误码

*初始化互斥量属性*

### pthread_mutexattr_setpshared

`int pthread_mutexattr_setpshared(pthread_mutexattr_t *attr, int pshared)`

- `attr` 互斥量属性

- `pshared` 进程共享属性值

- `返回值`

  成功：0

  失败：错误码

*设置进程共享属性*

### pthread_mutexattr_settype

`int pthread_mutexattr_settype(pthread_mutexattr_t *attr, int type)`

- attr` 互斥量属性

- `type` 互斥量类型

- `返回值`

  成功：0

  失败：错误码

*设置互斥量类型*

### pthread_once

`int pthread_once(pthread_once_t *initflag, void (*initfn)(void))`

- `initflag` 标志（全局变量或静态变量）

- `initfn` 只执行一次的函数

- `返回值`

  成功：0

  失败：错误码

*让函数只执行一次*

### pthread_rwlock_destroy

`int pthread_rwlock_destroy(pthread_rwlock_t *rwlock)`

- `rwlock` 读写锁

- `返回值`

  成功：0

  失败：错误码

*销毁读写锁*

### pthread_rwlock_init

`int pthread_rwlock_init(pthread_rwlock_t *restrict rwlock, const pthread_rwlockattr_t *restrict attr)`

- `rwlock` 读写锁

- `attr` 读写锁属性

- `返回值`

  成功：0

  失败：错误码

*创建读写锁*

### pthread_rwlock_rdlock

`int pthread_rwlock_rdlock(pthread_rwlock_t *rwlock)`

- `rwlock` 读写锁

- `返回值`

  成功：0

  失败：错误码

*加读锁*

### pthread_rwlock_timedrdlock

`int pthread_rwlock_timedrdlock(pthread_rwlock_t *restrict rwlock, const struct timespec *restrict tsptr)`

- `rwlock` 读写锁

- `tsptr` 超时时间

- `返回值`

  成功：0

  失败：错误码

*以超时模式加读锁*

### pthread_rwlock_timedwrlock

`int pthread_rwlock_timedwrlock(pthread_rwlock_t *restrict rwlock, const struct timespec *restrict tsptr)`

- `rwlock` 读写锁

- `tsptr` 超时时间

- `返回值`

  成功：0

  失败：错误码

*以超时模式加写锁*

### pthread_rwlock_tryrdlock

`int pthread_rwlock_tryrdlock(pthread_rwlock_t *rwlock)`

- `rwlock` 读写锁

- `返回值`

  成功：0

  失败：错误码

*尝试加读锁*

### pthread_rwlock_trywrlock

`int pthread_rwlock_trywrlock(pthread_rwlock_t *rwlock)`

- `rwlock` 读写锁

- `返回值`

  成功：0

  失败：错误码

*尝试加写锁*

### pthread_rwlock_wrlock

`int pthread_rwlock_wrlock(pthread_rwlock_t *rwlock)`

- `rwlock` 读写锁

- `返回值`

  成功：0

  失败：错误码

*加写锁*

### pthread_rwlock_unlock

`int pthread_rwlock_unlock(pthread_rwlock_t *rwlock)`

- rwlock` 读写锁

- `返回值`

  成功：0

  失败：错误码

*解读写锁*

### pthread_rwlockattr_destroy

`int pthread_rwlockattr_destroy(pthread_rwlockattr_t *attr)`

- `attr` 读写锁属性

- `返回值`

  成功：0

  失败：错误码

*回收读写锁属性*

### pthread_rwlockattr_getpshared

`int pthread_rwlockattr_getpshared(const pthread_rwlockattr_t *restrict attr, int *rstrict pshared)`

- `attr`读写锁属性

- `pshared` 进程共享属性值

- `返回值`

  成功：0

  失败：错误码

*获取读写锁进程共享属性*

### pthread_rwlockattr_init

`int pthread_rwlockattr_init(pthread_rwlockattr_t *attr)`

- `attr` 读写锁属性

- `返回值`

  成功：0

  失败：错误码

*初始化读写锁属性*

### pthread_rwlockattr_setpshared

`int pthread_rwlockattr_setpshared(pthread_rwlockattr_t *attr, int pshared)`

- `attr`读写锁属性

- `pshared` 进程共享属性值

- `返回值`

  成功：0

  失败：错误码

*设置读写锁进程共享属性*

### pthread_self

`pthread_t pthread_self(void)`

- `返回值` 调用线程的线程ID

*获得自身的线程ID*

### pthread_setcancelstate

`int pthread_setcancelstate(int state, int *oldstate)`

- `state` 可取消状态

- `oldstate` 旧状态

- `返回值`

  成功：0

  失败：错误码

*设置可取消状态（线程启动时默认为PTHREAD_CANCEL_ENABLE）*

### pthread_setcanceltype

`int pthread_setcanceltype(int type, int *oldtype)`

- `type` 新取消类型

- `oldtype` 旧取消类型

- `返回值`

  成功：0

  失败：错误码

*修改取消类型*

### pthread_setconcurrency

`int pthread_setconcurrency(int level)`

- `level` 并发度

- `返回值`

  成功：0

  失败：错误码

*设置线程并发度（影响性能）*

### pthread_setspecific

`int pthread_setspecific(pthread_key_t key, const void *value)`

- `key` 键

- `value` 值

- `返回值`

  成功：0

  失败：错误码

*设置键与关联的线程私有数据*

### pthread_spin_destroy

`int pthread_spin_destroy(pthread_spinlock_t *lock)`

- `lock` 自旋锁

- `返回值`

  成功：0

  失败：错误码

*反初始化自旋锁*

### pthread_spin_init

`int pthread_spin_init(pthread_spinlock_t *lock, int pshared)`

- `lock` 自旋锁

- `pshared` 进程共享属性

- `返回值`

  成功：0

  失败：错误码

*初始化自旋锁*

### pthread_spin_lock

`int pthread_spin_lock(pthread_spinlock_t *lock)`

- `lock` 自旋锁

- `返回值`

  成功：0

  失败：错误码

*对自旋锁进行加锁*

### pthread_spin_trylock

`int pthread_spin_trylock(pthread_spinlock_t *lock)`

- `lock` 自旋锁

- `返回值`

  成功：0

  失败：错误码

*尝试对自旋锁进行加锁*

### pthread_spin_unlock

`int pthread_spin_unlock(pthread_spinlock_t *lock)`

- `lock` 自旋锁

- `返回值`

  成功：0

  失败：错误码

*对自旋锁进行解锁*

### pthread_testcancel

`void pthread_testcancel(void)`

*添加自定义取消点*

[返回顶部](#POSIX接口)

---



## pwd.h

### endpwent

`void endpwent(void)`

- `返回值`

  成功：passwd指针

  失败或到达文件结尾：NULL

*关闭口令文件内容*

### getpwent

`struct passwd *getpwent(void)`

- `返回值`

  成功：passwd指针

  失败或到达文件结尾：NULL

*获得口令文件内容*

### getpwuid/getpwnam

`struct passwd *getpwuid(uid_t uid)`
`struct passwd *getpwnam(const char *name)`

- `uid` 用户ID

- `name` 用户登陆名

- `返回值`

  成功：passwd指针

  失败：NULL

*获取口令文件项*

### setpwent

`void setpwent(void)`

- `返回值`

  成功：passwd指针

  失败或到达文件结尾：NULL

*设置口令文件内容*

[返回顶部](#POSIX接口)

---



## semaphore.h

### sem_close

`int sem_close(sem_t *sem)`

- `sem` 信号量

- `返回值`

  成功：0

  失败：-1

*释放信号量的资源*

### sem_destroy

`int sem_destroy(sem_t *sem)`

- `sem` 信号量

- `返回值`

  成功：0

  失败：-1

*丢弃未命名信号量*

### sem_getvalue

`int sem_getvalue(sem_t *restrict sem, int *restrict valp)`

- `sem` 信号量

- `valp` 信号量值指针

- `返回值`

  成功：0

  失败：-1

*检索信号量值*

### sem_init

`int sem_init(sem_t *sem, int pshared, unsigned int value)`

- `sem` 信号量

- `pshared` 是否在多个进程中使用信号量（是：非0）

- `value` 信号量的初始值

- `返回值`

  成功：0

  失败：-1

*创建一个未命名的信号量并初始化*

### sem_open

`sem_t *sem_open(const char *name, int oflag, ...)`

- `name` 信号量名字

- `oflag` 标志

  | oflag值 | 说明                                                         |
  | ------- | ------------------------------------------------------------ |
  | O_CREAT | 如果信号量不存在，创建一个新的；如果已存在，直接使用而不做初始化。<br>当使用此标志时，需要提供两个额外的参数：<br>- mode：权限位（与文件权限位规则相同）；<br>- value：信号量的初始值（取值范围：[0, SEM_VALUE_MAX]）。 |
  | O_EXCL  | 如果信号量已存在，将导致`sem_open`失败。                     |

- `...` 变参，取决于oflag的值

*创建一个新的命名信号量或使用一个现有信号量*

### sem_post

`int sem_post(sem_t *sem)`

- `sem` 信号量

- `返回值`

  成功：0

  失败：-1

*对信号量进行 +1 操作（如果进程在sem_wait时被阻塞，将唤醒进程，并先执行 +1 ，后执行 -1 操作）*

### sem_timedwait

`int sem_timedwait(sem_t *restrict sem, const struct timespec *restrict tsptr)`

- `sem` 信号量

- `tsptr` 绝对时间

- `返回值`

  成功：0

  失败：-1

*以超时方式对信号量进行 -1 操作*

### sem_trywait

`int sem_trywait(sem_t *sem)`

- `sem` 信号量

- `返回值` 

  成功：0

  失败：-1

*对信号量进行 -1 操作（非阻塞）*

### sem_unlink

`int sem_unlink(const char *name)`

- `name` 信号量名字

- `返回值`

  成功：0

  失败：-1

*销毁一个命名信号量*

### sem_wait

`int sem_wait(sem_t *sem)`

- `sem` 信号量

- `返回值` 

  成功：0

  失败：-1

*对信号量进行 -1 操作（阻塞）*

[返回顶部](#POSIX接口)

---



## setjmp.h

### longjmp

`void longjmp(jmp_buf env, int val)`

- `env` 保存恢复栈状态的所有信息
- `val` 从setjmp处返回的值

*进行非局部跳转（全局的goto）*

### setjmp

`int setjmp(jmp_buf env)`

- `env` 保存恢复栈状态的所有信息

- `返回值`

  直接调用：0

  从longjmp返回：非0

**设置非局部跳转信息（全局的goto）**

[返回顶部](#POSIX接口)

---



## shadow.h

### endspent

`void endspent(void)`

*关闭口令文件*

### getspnam/getspent

`struct spwd *getspnam(const char *name)`
`struct spwd *getspent(void)`

- `name` 口令文件

- `返回值`

  成功：spwd指针

  出错：NULL

*访问口令文件*

### setspent

`void setspent(void)`

*打开口令文件*

[返回顶部](#POSIX接口)

---



## signal.h

### kill

`int kill(pid_t pid, int signo)`

- `pid` 进程ID

- `signo` 信号

- 返回值

  成功：0

  失败：-1

*将信号发送给进程或进程组*；具体见[unix环境高级编程#第十章#函数kill和raise](../NOTE/ADVANCED_PROGRAMMING_IN_THE_UNIX_ENVIRONMENT/chapter10.md)。

### pthread_kill

`int pthread_kill(pthread_t thread, int signo)`

- `thread` 线程

- `signo` 信号

- `返回值`

  成功：0

  失败：错误码

*把信号发送到线程*

### pthread_sigmask

`int pthread_sigmask(int how, const sigset_t *restrict set, sigset_t *restrict oset)`

- `how` 动作

  SIG_BLOCK：把信号添加到线程信号屏蔽字中

  SIG_SETMASK：用信号集替换线程的信号屏蔽字

  SIG_UNBLOCK：从线程信号屏蔽字中移除信号集

- `set` 新信号集

- `oset` 旧信号集

- `返回值`

  成功：0

  失败：错误码

*阻止信号发送*

### raise

`int raise(int signo)`

- `signo` 信号

- 返回值

  成功：0

  失败：-1

*允许进程向自身发送信号*

### sigaction

`int sigaction(int signo, const struct sigaction *restrict act, struct sigaction *restrict oact)`

- `signo` 要检查/修改的信号编号

- `act` 非空，则修改其动作

- `oact` 非空，则返回该信号的上一个动作

- 返回值

  成功：0

  失败：-1

*检查/修改指定信号相关联的处理动作。*

### sigaddset

`int sigaddset(sigset_t *set, int signo)`

- `set` 信号集

- `signo` 信号

- `返回值`

  成功：0

  失败：-1

*添加信号*

### sigdelset

`int sigdelset(sigset_t *set, int signo)`

- `set` 信号集

- `signo` 信号

- `返回值`

  成功：0

  失败：-1

*删除信号*

### sigemptyset

`int sigemptyset(sigset_t *set)`

- `set` 信号集

- `返回值`

  成功：0

  失败：-1

*初始化信号集，清除其中所有信号*

### sigfillset

`int sigfillset(sigset_t *set)`

- `set` 信号集

- `返回值`

  成功：0

  失败：-1

*初始化由set指向的信号集，使其包括所有信号*

### sigismember

`int sigismember(const sigset_t *set, int signo)`

- `set` 信号集

- `signo` 信号

- `返回值`

  真：0

  假：-1

*判断信号是否是信号集中的成员*

### signal

`void(*signal(int signo, void(*func)(int)))(int)`

- `signo` 信号量

- `func` 信号处理动作，默认SIG_IGN

- 返回值

  成功：返回以前的信号处理配置

  出错：返回SIG_ERR

*信号处理程序*

### sigpending

`int sigpending(sigset_t *set)`

- `set` 返回的信号集

- 返回值

  成功：0

  失败：-1

*返回当前进程的阻塞且不可递送的信号集合*

### sigprocmask

`int sigprocmask(int how, const sigset_t *restrict set, sigset_t *restrict oset)`

- `how` 操作

- `set` 如果非空，则指示需要修改修改的当前信号屏蔽字

- `oset` 如果非空，用来返回进程的当前信号屏蔽字

- 返回值：

  成功：0

  失败：-1

*检测/更改进程的信号屏蔽字*

### sigwait

`int sigwait(const sigset_t *restrict set, int *restrict signop)`

- `set` 信号集

- `signop` 返回发送信号的数量

- `返回值`

  成功：0

  失败：错误码

*等待一个或多个信号发生*

[返回顶部](#POSIX接口)

---



## stdio.h

### clearerr

`void clearerr(FILE *fp)`

- `fp` 流

*清空错误标记*

### ctermid

`char *ctermid(char *ptr)`

- `ptr` 控制终端名

- `返回值`

  成功：返回指向控制终端名的指针

  失败：返回指向空字符串的指针

*设置控制终端名*

### fclose

`int fclose(FILE *fp)`

- `fp` 流

- `返回值`

  成功：0

  失败：EOF

*关闭流*

### feof

`int feof(FILE *fp)`

- `fp` 流

- `返回值`

  条件为真：非0

  条件为假：0

*判断文件结束*

### ferror

`int ferror(FILE *fp)`

- `fp` 流

- `返回值`

  条件为真：非0

  条件为假：0

*判断错误类型*

### fflush

`int fflush(FILE *fp)`

- `fp` 文件流

- `返回值`

  成功：0

  失败：EOF

*强制刷出一个流*

### fgetc

`int fgetc(FILE *fp)`

- `fp` 流

- `返回值`

  成功：下一个字符

  到达文件尾或出错：EOF

*一次读一个字符*

### fgetpos

`int fgetpos(FILE *restrict fp, fpos_t *restrict pos)`

- `fp` 流

- `pos` 当前位置

- `返回值`

  成功：0

  失败：非0

*获取流的当前位置*

### fgets

`char *fgets(char *restrict buf, int n, FILE *restrict fp)`

- `buf` 缓冲区

- `n` 缓冲区长度

- `fp` 流

- `返回值`

  成功：buf

  到达文件尾或出错：NULL

*从流中读一行字符串*

### fileno

`int fileno(FILE *fp)`

- `fp` 流
- `返回值` 与流相关联的文件描述符

*获得流的描述符*

### flockfile

`void flockfile(FILE *fp)`

- `fp` 文件描述符

*对文件对象加锁（线程安全）*

### fopen/freopen/fdopen

`FILE *fopen(const char *restrict pathname, const char *restrict type)`
`FILE *freopen(const char *restrict pathname, const char *restrict type, FILE *restrict fp)`
`FILE *fdopen(int fd, const char *type)`

- `pathname` 路径

- `type` 打开模式

- `fd` 文件描述符

- `返回值`

  成功：文件指针

  失败：NULL

*fopen：打开一个标准I/O流*

*freopen：重新打开一个标准I/O流*

*fdopen：使一个标准的I/O流与已有的文件描述符结合*

### fputc

`int fputc(int c, FILE *fp)`

- `c` 字符

- `fp` 文件流

- `返回值`

  成功：c

  失败：EOF

*写单个字符到文件流中*

### fread

`size_t fread(void *restrict ptr, size_t size, size_t nobj, FILE *restrict fp)`

- `ptr` 缓冲区
- `size` 缓冲区长度
- `nobj` 要读/写的数据长度
- `fp` 流
- `返回值`对象数

*读二进制数据*

### fseek

`int fseek(FILE *fp, long offset, int whence)`

- `fp` 流

- `offset` 偏移量

- `whence` 位置

  - `SEEK_SET` 将文件的偏移量设置为距文件开始处offset个字节
  - `SEEK_CUR` 将文件偏移量设置为其当前值加offset，offset可正可负
  - `SEEK_END` 将文件的偏移量设置为文件长度加offset，offset可正可负

- `返回值`

  成功：0

  失败：非0

*定位标准I/O流*

### fseeko

`int fseeko(FILE *fp, off_t offset, int whence)`

- `fp` 流

- `offset` 偏移量

- `whence` 位置

  - `SEEK_SET` 将文件的偏移量设置为距文件开始处offset个字节
  - `SEEK_CUR` 将文件偏移量设置为其当前值加offset，offset可正可负
  - `SEEK_END` 将文件的偏移量设置为文件长度加offset，offset可正可负

- `返回值`

  成功：0

  失败：非0

*定位标准I/O流*

### fsetpos

`int fsetpos(FILE *fp, const fpos_t *pos)`

- `fp` 流

- `pos` 当前位置

- `返回值`

  成功：0

  失败：非0

*设置流的当前位置*

### ftell/ftello

`long ftell(FILE *fp)`

`off_t ftello(FILE *fp);`

- `fp` 流

- `返回值`

  成功：当前文件位置

  失败：(off_t)-1

*定位标准I/O流*

### ftrylockfile

`int ftrylockfile(FILE *fp)`

- `fp` 文件描述符

- `返回值`

  成功：0

  失败：非0

*尝试对文件对象加锁（线程安全）*

### funlockfile

`void funlockfile(FILE *fp)`

- `fp` 文件描述符

*解锁文件对象（线程安全）*

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

### fwrite

`size_t fwrite(const void *restrict ptr, size_t size, size_t nobj, FILE *restrict fp)`

- `ptr` 缓冲区
- `size` 缓冲区长度
- `nobj` 要读/写的数据长度
- `fp` 流
- `返回值`对象数

*写二进制数据*

### getc

`int getc(FILE *fp)`

- `fp` 流

- `返回值`

  成功：下一个字符

  到达文件尾或出错：EOF

*一次读一个字符*

### getc_unlocked

`int getc_unlocked(FILE *fp)`

- `fp` 文件描述符

- `返回值`

  成功：下一个字符

  已到达文件尾或出错：EOF

*读一个字符（不加锁，不建议使用）*

### getchar

`int getchar(void)`

- `返回值`

  成功：下一个字符

  到达文件尾或出错：EOF

*一次读一个字符*

### getchar_unlocked

`int getchar_unlocked(void)`

- `返回值`

  成功：下一个字符

  已到达文件尾或出错：EOF

*读一个字符（不加锁，不建议使用）*

### gets

`char *gets(char *buf)`

- `buf` 缓冲区

- `返回值`

  成功：buf

  到达文件尾或出错：NULL


*从流中读一行字符串*

### isatty

`int isatty(int filedes)`

- `filedes` 终端

- `返回值`

  是终端设备：1

  不是终端设备：0

*判断是否为终端设备*

### mkstemp

`int mkstemp(char *template)`

- `template` 字符串模板

- `返回值`

  成功：文件描述符

  失败：-1

*创建临时文件*

### pclose

`int pclose(FILE *fp)`

- `fp` 文件描述符

- `返回值`

  成功：cmdstring的终止状态

  失败：-1

*关闭标准I/O流*

### popen

`FILE *popen(const char *cmdstring, const char *type)`

- cmdstring` 命令行

- `type` 创建模式

- `返回值` 

  成功：标准I/O文件指针

  失败：NULL

*创建管道*

### printf/vprintf/fprintf/vprintf

`int printf(const char *restrict format, ...)`
`int vprintf(const char *restrict format, va_list arg)`
`int fprintf(FILE *restrict fp, const char *restrict format, ...)`
`int vfprintf(FILE *restrict fp, const char *restrict format, va_list arg)`

- `format` 格式化字符串

- `fp` 流

- `返回值`

  成功：字符数

  失败：负数

*格式化输出字符到流*

### putc

`int putc(int c, FILE *fp)`

- `c` 字符

- `fp` 流

- `返回值`

  成功：c

  失败：EOF

*写单个字符到流中*

### putc_unlocked

`int putc_unlocked(int c, FILE *fp)`

- `c` 字符

- `fp` 文件描述符

- `返回值`

  成功：c

  失败：EOF

*写单个字符到流中（不加锁，不建议使用）*

### putchar

`int putchar(int c)`

- `c` 字符

- `fp` 流

- `返回值`

  成功：c

  失败：EOF

*写单个字符到流中*

### putchar_unlocked

`int putchar_unlocked(int c)`

- `c` 字符

- `fp` 流

- `返回值`

  成功：c

  失败：EOF

*写一个字符到流（不加锁，不建议使用）*

### puts/fputs

`int fputs(const char *restrict str, FILE *restrict fp)`
`int puts(const char *str)`

- `str` 字符串

- `fp` 流

- `返回值`

  成功：非负值

  失败：EOF

*将一行字符串（null结尾）写入到流*

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

### rewind

`void rewind(FILE *fp)`

- `fp` 流

*将流设置到文件的起始位置*

### scanf/fscanf/sscanf/vscanf/vfscanf/vsscanf

`int scanf(const char *restrict format, ...)`
`int vscanf(const char *restrict format, va_list arg)`
`int fscanf(FILE *restrict fp, const char *restrict format, ...)`
`int vfscanf(FIEL *restrict fp, const char *restrict format, va_list arg)`
`int sscanf(const char *restrict buf, const char *restrict format, ...)`
`int vsscanf(const char *restrict buf, const char *restrict format, va_list arg)`

- `format` 格式化字符串

- `fp` 流

- `buf` 缓冲区

- `返回值`

  成功：输入的项数

  出错或再任意变换前已到达文件结尾：EOF

*格式化输入*

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

### sprintf/vsprintf/snprintf/vsnprintf

`int sprintf(char *restrict buf, const char *restrict format, ...)`
`int vsprintf(char *restrict buf, const char *restrict format, va_list arg)`
`int snprintf(char *restrict buf, size_t n, const char *restrict format, ...)`
`int vsnprintf(char *restrict buf, size_t n, const char *restruct format, va_list arg)`

- `buf` 缓冲区

- `format` 格式化字符串

- `n` 缓冲区长度

- `返回值`

  成功：存入数组的字符数

  失败：负数

*格式化输出字符串到缓冲区*

### tmpfile

`FILE *tmpfile(void)`

- `返回值`

  成功：文件指针

  失败：NULL

*创建临时文件*

### tmpnam

`char *tmpnam(char *ptr)`

- `ptr` 文件路径
- `返回值` 创建的临时文件路径

*创建一个与现有文件名不同的临时文件路径（此函数最多调用`TMP_MAX`次）*

### ungetc

`int ungetc(int c, FILE *fp)`

- `c` 字符

- `fp` 流

- `返回值`

  成功：c

  失败：EOF

*将从流中读取的字符再退回流中*

[返回顶部](#POSIX接口)

---



## stdlib.h

### atexit

`int atexit(void (*func)(void))`

- `func` 终止处理回调函数
- `返回值`
  - 成功：0
  - 失败：非0

*注册`终止处理程序（exit handler）`，最多32个且不做去重。*

### calloc

`void *calloc(size_t mobj, size_t size)`

- `mobj` 对象个数
- `size` 长度（字节数）
- `返回值`
  - 成功：非空指针
  - 失败：NULL

*为指定数量指定长度的对象分配存储空间，该空间中的每bit都初始化为0。*

### exit

`void exit(int status)`

- `status` 终止状态

*执行完清理操作：对于所有打开流调用fclose函数，冲刷输出缓冲中的所有数据；然后返回内核。*

### free

`void free(void *ptr)`

- `ptr` 分配区指针

*释放存储空间。*

### getenv

`char *getenv(const char *name)`

- `name` 键
- `返回值`
  - 成功：与name关联的指针
  - 失败：NULL

*获取环境变量值。*

### grantpt

`int grantpt(int filedes)`

- `filedes` 终端

- `返回值`

  成功：0

  失败：-1

*设置伪终端从设备权限*

### malloc

`void *malloc(size_t size)`

- `size` 长度（字节数）

- `返回值`

  成功：非空指针

  失败：NULL

*分配指定字节数的存储区，此存储区中的初始值不确定。*

### posix_openpt

`int posix_openpt(int oflag)`

- `oflag` 位屏蔽字

- `返回值`

  成功：下一个可用的PTY主设备的文件描述符

  失败：-1

*打开下一个可用的伪终端主设备*

### ptsname

`char *ptsname(int filedes)`

- `filedes` 终端

- `返回值`

  成功：指向PTY从设备名的指针

  失败：NULL

*找到从伪终端设备的路径名*

### putenv

`int putenv(char *str)`

- `str` 格式为`name=value的`键值对
- `返回值`
  - 成功：0
  - 失败：非0

*取形式为`name=value`的字符串，将其放到环境表中；如果name已经存在，则先删除其原来的定义。*

### realloc

`void *realloc(void *ptr, size_t newsize)`

- `ptr` 旧的分配区指针
- `newsize` 长度（字节数）
- `返回值`
  - 成功：非空指针
  - 失败：NULL

*增加或减少以前分配区的长度；当增加长度时，可能需将以前分配区的内容移到另一个足够大的区域，以便在尾端提供增加的存储区，而新增区域内的初始值则不确定。*

### setenv

`int setenv(const char *name, const char *value, int rewrite)`

- `name` 键
- `value` 值
- `rewrite` 是否重写该值（0：保留现有定义，非0：删除现有定义）
- `返回值`
  - 成功：0
  - 失败：-1

*将name设置为value；如果name已经存在：1.如果rewrite非0，则首先删除其现有的定义；2.如果rewrite为0，则不删除其现有定义。

### unlockpt

`int unlockpt(int filedes)`

- filedes` 终端

- `返回值`

  成功：0

  失败：-1

*允许对伪终端从设备的访问*

### unsetenv

`int unsetenv(const char *name)`

- `name` 键
- `返回值`
  - 成功：0
  - 失败：-1

*删除指定key的环境变量。*

### _exit

`void _exit(int status)`

- `status` 终止状态

*立即返回内核，不做清理。*

### _Exit

`void _Exit(int status)`

- `status` 终止状态

*立即返回内核，不做清理。*

[返回顶部](#POSIX接口)

---



## string.h

### memset

`void *memset(void *dest, int c, size_t len)`

- `dest` 被设置的字符串
- `c` 要设置的值
- `len` 要设置的字节数

设置字符串为指定值

### memcpy

`void *memcpy(void *dest, const void *src, size_t nbytes)`

- `dest` 目标字符串
- `src` 源字符串
- `nbytes` 要复制的字节数

复制字符串

### memcmp

`int memcmp(const void *ptr1, const void *ptr2, size_t nbytes)`

- `ptr1` 字符串1
- `ptr2` 字符串2
- `nbytes` 要比较的字符串长度

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

- `dest` 被设置的字符串
- `nbytes` 要设置的字节数

 *设置字符串的值为0*

### bcopy

`void bcopy(const void *src, void *dest, size_t nbytes)` 

- `src` 源字符串
- `dest` 目标字符串
- `nbytes` 要复制的数量

*复制字符串*

### bcmp

`int bcmp(const void *ptr1, const void *ptr2, size_t nbytes)` 

- `ptr1` 字符串1
- `ptr2` 字符串2
- `nbytes` 要比较的字符长度

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



## stropts.h

### isastream

`int isastream(int filedes)`

- `filedes` 描述符

- `返回值`

  STREAMS设备：1

  失败：0

*判断一个描述符是否引用一个流*

### putmsg

`int putmsg(int fields, const struct strbuf *ctlptr, const struct strbuf *dataptr, int flag)`

- `filedes` 描述符

- `ctlptr` 控制指针

- `dataptr` 数据流

- `flag` 标志

- `返回值`

  成功：0

  失败：-1

*将STREAMS消息写入到流中*

### putpmsg

`int putpmsg(int fields, const struct strbuf *ctlptr, const struct strbuf *dataptr, int band, int flag)`

- `filedes` 描述符

- `ctlptr` 控制指针

- `dataptr` 数据流

- `band` 优先级波段

- `flag` 标志

- `返回值`

  成功：0

  失败：-1

*将STREAMS消息写入到流中*

[返回顶部](#POSIX接口)

---



## sys/ipc.h

### ftok

`key_t ftok(const char *path, int id)`

- `path` 现有文件的路径
- `id` 项目ID
- `返回值`
  - 成功：返回键
  - 失败：返回(key_t) - 1

*将路径名和项目ID变换为一个键。*

[返回顶部](#POSIX接口)

---



## sys/mman.h

### mmap

`void *mmap(void *addr, size_t len, int prot, int flag, int fields, off_t off)`

- `addr` 映射存储区的起始地址

- `len` 映射的字节数

- `prot` 对映射存储区的保护要求

- `flag` 映射存储区的属性

  - `MAP_FIXED` 返回值必须等于addr（不利于可移植性，不推荐使用此标志）；
  - `MAP_SHARED` 指定存储操作修改映射文件；
  - `MAP_PRIVATE` 对映射区的存储操作导致创建该映射文件的一个私有副本；

- `fields` 被映射文件的描述符

- `off` 要映射字节在文件中的起始偏移量

- `返回值`

  成功：映射区的起始地址

  失败：MAP_FAILED

*告诉内核将一个文件映射到指定存储区域*

### mprotect

`int mprotect(void *addr, size_t len, int prot)`

- `addr` 映射存储区的起始地址

- `len` 映射的字节数

- `prot` 对映射存储区的保护要求

- `返回值`

  成功：0

  失败：-1

*更改一个现存映射存储区的权限*

### msync

`int msync(void *addr, size_t len, int flags)`

- `addr` 映射存储区的起始地址
- `len` 映射的字节数
- `flags` 控制冲洗存储区

*存储映射区*

### munmap

`int munmap(caddr_t addr, size_t len)`

- `addr` 映射存储区的起始地址

- `len` 映射的字节数

- `返回值`

  成功：0

  失败：-1

*解除存储映射*

[返回顶部](#POSIX接口)

---



## sys/msg.h

### msgctl

`int msgctl(int msqid, int cmd, struct msqid_ds *buf)`

- `msqid` 消息队列id

- `cmd` 指定对msqid指定的队列要执行的命令

- `buf` 缓冲区

- `返回值`

  成功：0

  失败：-1

*对队列执行操作*

### msgget

`int msgget(key_t key, int flag)`

- `key` 键
- `flag` 标志
- `返回值`
  - 成功：消息队列ID（非负）
  - 失败：-1

*打开/创建一个队列*

### msgrcv

`ssize_t msgrcv(int msqid, void *ptr, size_t bytes, long type, int flag)`

- `msqid` 消息队列ID

- `ptr` 数据指针

- `bytes` 数据大小

- `type` 消息类型

- `flag` 标志

- `返回值`

  - 成功：消息数据长度
  - 失败：-1

*从队列中取用消息*

### msgsnd

`int msgsnd(int msqid, const void *ptr, size_t nbytes, int flag)`

- `msqid` 消息队列ID

- `ptr` 指向数据的指针

- `nbytes` 数据大小

- `flag` 标志

  | flag值     | 说明   |
  | ---------- | ------ |
  | IPC_NOWAIT | 非阻塞 |

- `返回值`

  - 成功：0
  - 失败：-1

*将数据放到消息队列中*



[返回顶部](#POSIX接口)

---



## sys/resource.h

### getpriority

`int getpriority(int which, id_t who)`

- `which` 类别
  - `PRIO_PROCESS` 进程
  - `PRIO_PGRP` 进程组
  - `PRIO_USER` 用户ID
- `who` 进程/进程组/用户ID
- `返回值`
  - 成功：返回[-NZERO, NZERO-1]之间的值
  - 失败：-1

*返回指定对象的nice值（调度优先级）*

### getrlimit

`int getrlimit(int resource, struct rlimit *rlptr)`

- `resource` 资源

- `rlptr` 限制值

- `返回值`

  成功：0

  失败：非0

*设置进程的资源限制*

### setpriority

`int setpriority(int which, id_t who, int value)`

- `which` 类别
  - `PRIO_PROCESS` 进程
  - `PRIO_PGRP` 进程组
  - `PRIO_USER` 用户ID
- `who` 进程/进程组/用户ID
- `value` 值
- `返回值`
  - 成功：0
  - 失败：-1

*设置指定对象的nice值（调度优先级）*

### setrlimit

`int setrlimit(int resource, const struct rlimit *rlptr)`

- `resource` 资源

- `rlptr` 限制值

- `返回值`

  成功：0

  失败：非0

*更新进程的资源限制*

[返回顶部](#POSIX接口)

---



## sys/select.h

### pselect

`int pselect(int maxfdp1, fd_set *restrict readfds, fd_set *restrict writefds, fd_set *restrict exceptfds, const struct timespec *restrict tsptr, cosnt sigset_t *restrict sigmask)`

- `maxfdp1 ` 最大描述符数 + 1

- `readfds` 可读描述符

- `writefds` 可写描述符

- `exceptfds` 异常描述符

- `tvptr` 超时时间

- `sptr` 超时时间（更精确的时间，参考`tvptr`）

- `sigmask` 信号屏蔽字

- `返回值`

  超时：0

  出错：-1

  成功：准备就绪的描述符数

*多路转接（允许禁止某些信号）*

### select

`int select(int maxfdp1, fd_set *restrict readfds, fd_set *restrict writefds, fd_set *restrict exceptfds, struct timeval *restrict tvptr)`

- `maxfdp1 ` 最大描述符数 + 1

- `readfds` 可读描述符

- `writefds` 可写描述符

- `exceptfds` 异常描述符

- `tvptr` 超时时间

- sptr` 超时时间（更精确的时间，参考`tvptr`）

- `sigmask` 信号屏蔽字

- `返回值`

  超时：0

  出错：-1

  成功：准备就绪的描述符数

*多路转接*

### FD_CLR

`void FD_CLR(int fd, fd_set *fdset)`

- `fd` 文件描述符
- `fdset` 文件描述符集

*将fdset变量的所有位设置为0*

### FD_ISSET

`int FD_ISSET(int fd, fd_set *fdset)`

- `fd` 文件描述符
- `fdset` 文件描述符集
- `返回值` fd在描述符集里：非0；否则：0

*文件描述符是否在文件描述符集里*

### FD_SET

`void FD_SET(int fd, fd_set *fdset)`

- `fd` 文件描述符
- `fdset` 文件描述符集

*设置fdset变量的指定位*

### FD_ZERO

`void FD_ZERO(fd_set *fdset)`

- `fdset` 文件描述符集

*清除fdset的所有位*

[返回顶部](#POSIX接口)

---



## sys/sem.h

### semctl

`int semctl(int semid, int semnum, int cmd, ...)`

- `semid` 信号量ID

- `semnum` 指定该信号量集合中的一个成员

- `cmd` 命令

- `...` （变参）多个命令特定参数的union，是否使用取决于cmd的值

- `返回值`

  成功：0

  失败：-1

*对信号量操作*

### semget

`int semget(key_t key, int nsems, int flag)`

- `key` 键
- `nsems` 集合中的信号量数（如果是创建新集合，必须指定nsems；如果是引用现有集合，指定nsems为0）
- `flag` 标志
- `返回值`
  - 成功：信号量ID
  - 失败：-1

*获得一个信号量ID*

### semop

`int semop(int semid, struct sembuf semoparray[], size_t nops)`

- semid` 信号量ID

- `semoparray` 信号量操作数组

- `nops` 信号量操作数组中元素数量

- `返回值`

  成功：0

  失败：-1

*自动执行信号量集合上的操作数组*

[返回顶部](#POSIX接口)

---



## sys/shm.h

### shmat

`void *shmat(int shmid, const void *addr, int flag)`

- `shmid`  共享存储段ID
- `addr` 地址空间
- `flag` 标志
  - SHM_RND 配合addr使用；
  - SHM_RDONLY 以只读方式连接此段（默认读写方式）。

*将共享存储段连接到它的地址空间中*

### shmctl

`int shmctl(int shmid, int cmd, struct shmid_ds *buf)`

- `shmid` 共享存储段ID

- `cmd` 命令行

- `buf` 缓冲区

- `返回值`

  成功：0

  失败：-1

*对共享存储段执行多种操作*

### shmdt

`int shmdt(const void *addr)`

- `addr` 地址空间

- `返回值`

  成功：0

  失败：-1

*分离地址空间上的共享存储段*

### shmget

`int shmget(key_t key, size_t size, int flag)`

- `key` 键

- `size` 共享存储段长度（单位：字节）

- `flag` 标志

- `返回值`

  成功：共享存储ID

  失败：-1

*获得一个共享存储标识符*

[返回顶部](#POSIX接口)

---



## sys/socket.h

### accept

`int accept(int sockfd, struct sockaddr *restrict addr, socklen_t *restrict len)`

- `sockfd` 套接字

- `addr` 地址

- `len` 地址长度

- `返回值`

  成功：文件描述符

  失败：-1

*获得连接请求并建立连接（阻塞）*；具体见[unix网络编程-卷一#第四章#accept函数](../NOTE/UNIX_NETWORK_PROGRAMMING_V1/chapter4.md)。

### bind

`int bind(int sockfd, const struct sockaddr *addr, socklen_t len)`

- `sockfd` 套接字描述符

- `addr` 地址

- `len` 地址长度

- `返回值`

  成功：0

  失败：-1

*将地址绑定到一个套接字*；具体见[unix网络编程-卷一#第四章#bind函数](../NOTE/UNIX_NETWORK_PROGRAMMING_V1/chapter4.md)。

### connect

`int connect(int sockfd, const struct sockaddr *addr, socklen_t len)`

- `sockfd` 套接字

- `addr` 地址

- `len` 地址长度

- `返回值`

  成功：0

  失败：-1

*建立连接*；具体见[unix网络编程-卷一#第四章#connect函数](../NOTE/UNIX_NETWORK_PROGRAMMING_V1/chapter4.md)

### getpeername

`int getpeername(int sockfd, struct sockaddr *restrict addr, socklen_t *restrict alenp)`

- `sockfd` 套接字

- `addr` 对方地址

- `alenp` 对方地址长度

- `返回值`

  成功：0

  失败：-1

*查找与套接字连接的对方地址*；；具体见：[unix网络编程-卷一#第四章#getpeername函数](../NOTE/UNIX_NETWORK_PROGRAMMING_V1/chapter4.md)

### getsockname

`int getsockname(int sockfd, struct sockaddr *restrict addr, socklen_t *restrict alenp)`

- `sockfd` 套接字

- `addr` 地址

- `alenp` 地址长度

- `返回值`

  成功：0

  失败：-1

*查找绑定到套接字的地址*；具体见：[unix网络编程-卷一#第四章#getsockname函数](../NOTE/UNIX_NETWORK_PROGRAMMING_V1/chapter4.md)

### getsockopt

`int getsockopt(int sockfd, int level, int option void *restrict val, socklen_t *restrict lenp)`

- `sockfd` 套接字描述符

- `level` 选项应用的协议号

- `option` 选项

- `val` 参数

- `lenp` 复制缓冲区大小（根据选项值的实际尺寸更新）

- `返回值`

  成功：0

  失败：-1

*返回套接字选项值*

### listen

`int listen(int sockfd, int backlog)`

- `sockfd` 套接字

- `backlog` 数量

- `返回值`

  成功：0

  失败：-1

*监听套接字*；具体见[unix网络编程-卷一#第四章#listen函数](NOTE/UNIX_NETWORK_PROGRAMMING_V1/chapter4.md)。

### recv

`ssize_t recv(int sockfd, void *buf, size_t nbytes, int flags)`

- `sockfd` 套接字

- `buf` 接收缓冲区

- `nbytes` 接收数据长度

- `flags` 标志

  | 标志        | 描述                                       |
  | ----------- | ------------------------------------------ |
  | MSG_OOB     | 如果协议支持，接收带外数据                 |
  | MSG_PEEK    | 返回报文内容而不真正取走报文               |
  | MSG_TRUNC   | 即使报文被截断，要求返回的是报文的实际长度 |
  | MSG_WAITALL | 等待直到所有的数据可用（仅SOCK_STREAM）    |

- `返回值`

  成功：消息长度（字节）

  无可用消息或对方已经按序结束：0

  失败：-1

*接收数据*

### recvfrom

`ssize_t recvfrom(int sockfd, void *restrict buf, size_t len, int flags, struct sockaddr *restrict addr, socklen_t *restrict addrlen)`

- `sockfd` 套接字

- `buf` 缓冲区

- `len` 接收数据长度

- `flags` 标志

- `addr` 地址

- `addrlen` 地址长度

- `返回值`

  成功：消息长度（字节）

  无可用消息或对方已经按序结束：0

  失败：-1

*接收数据（用于无连接套接字）*

### recvmsg

`ssize_t recvmsg(int sockfd, struct msghdr *msg, int flags)`

- `sockfd` 套接字

- `msg` 消息

- `flags` 标志

  | 标志         | 描述                  |
  | ------------ | --------------------- |
  | MSG_CTRUNC   | 控制数据被截断        |
  | MSG_DONTWAIT | recvmsg处于非阻塞模式 |
  | MSG_EOR      | 接收到记录结束符      |
  | MSG_OOB      | 接收到带外数据        |
  | MSG_TRUNC    | 一般数据被截断        |

- `返回值`

  成功：消息长度（字节）

  无可用消息或对方已经按序结束：0

  失败：-1

*接收数据并放入多个缓冲区*

### send

`ssize_t send(int sockfd, const void *buf, size_t nbytes, int flags)`

- `sockfd` 套接字

- `buf` 缓冲区

- `nbytes` 数据长度

- `flags` 标志

  | 标志          | 描述                                   |
  | ------------- | -------------------------------------- |
  | MSG_DONTROUTE | 勿将数据路由出本地网络                 |
  | MSG_DONTWAIT  | 允许非阻塞操作（等价于使用O_NONBLOCK） |
  | MSG_EOR       | 如果协议支持，此为记录结束             |
  | MSG_OOB       | 如果协议支持，发送带外数据             |

- `返回值`

  成功：发送的字节数

  失败：-1

*发送数据*

### sendmsg

`ssize_t sendmsg(int sockfd, const struct msghdr *msg, int flags)`

- `sockfd` 套接字

- `msg` 数据

- `flags` 标志

- `返回值`

  成功：发送的字节数

  失败：-1

*发送数据（使用多重缓冲区）*

### sendto

`ssize_t sendto(int sockfd, const void *buf, size_t nbytes, int flags, const struct sockaddr *destaddr, socklen_t destlen)`

- `sockfd` 套接字

- `buf` 缓冲区

- `nbytes` 字节数

- `flags` 标志

- `destaddr` 目标地址

- `destlen` 目标地址长度

- `返回值`

  成功：发送的字节数

  失败：-1

*发送数据（在无连接的套接字上指定地址）*

### setsockopt

`int setsockopt(int sockfd, int level, int option, const void *val, socklen_t len)`

- `sockfd` 套接字

- `level` 选项应用的协议

- `option` 选项

- `val` 指向option对应的数据结构或整数

- `len` val指向的对象大小

- `返回值`

  成功：0

  失败：-1

*设置套接字选项*

### shutdown

`int shutdown(int sockfd, int how)`

- `sockfd` 套接字

- `how` 动作

  | how值     | 说明     |
  | --------- | -------- |
  | SHUT_RD   | 关闭读   |
  | SHUT_WR   | 关闭写   |
  | SHUT_RDWR | 关闭读写 |

- `返回值`

  成功：0

  失败：-1

*关闭一个套接字的I/O*

### socket

`int socket(int domain, int type, int protocol)`

- `domain` 域

  | 域        | 描述           |
  | --------- | -------------- |
  | AF_INET   | IPv4因特网域。 |
  | AF_INET6  | IPv6因特网域。 |
  | AF_UNIX   | UNIX域。       |
  | AF_UPSPEC | 未指定。       |

- `type` 套接字类型

  | 类型           | 描述                                             |
  | -------------- | ------------------------------------------------ |
  | SOCK_DGRAM     | 固定长度的，无连接的，不可靠的报文传递。         |
  | SOCK_RAW       | IP协议的数据报接口。                             |
  | SOCK_SEQPACKET | 固定长度的，有序的，可靠的，面向连接的报文传递。 |
  | SOCK_STREAM    | 有序的，可靠的，双向的，面向连接的字节流。       |

- `protocol` 协议

  | 协议         | 描述                                     |
  | ------------ | ---------------------------------------- |
  | IPPROTO_IP   | IPv4网际协议                             |
  | IPPROTO_IPV6 | IPv6网际协议                             |
  | IPPROTO_ICMP | 因特网控制报文协议                       |
  | IPPROTO_RAW  | 原始IP数据包协议                         |
  | IPPROTO_TCP  | 传输控制协议                             |
  | IPPROTO_UDP  | 用户数据报协议（User Datagram Protocol） |

- `返回值`

  成功：文件描述符

  失败：-1

*创建一个套接字*

### sockatmark

`int sockatmark(int sockfd)`

- `sockfd` 套接字

- `返回值`

  在标记处：1

  没有在标记处：0

  出错：-1

*设置是否接收到紧急标记*

### socketpair

`int socketpair(int domain, int type, int protocol, int sockfd[2])`

- `domain` 域

- `type` 套接字类型

- `protocol` 协议

- `sockfd` 套接字描述符

- `返回值`

  成功：0

  失败：-1

*创建一对无命名的，相互连接的UNIX域套接字*

### CMSG_DATA

`unsigned char *CMSG_DATA(struct cmsghdr *cp)`

- `cp` cmsghdr指针
- `返回值` 指向与`cmsghdr`结构相关联的数据

*返回指向与cmsghdr结构相关联的数据指针*

### CMSG_FIRSTHDR

`struct cmsghdr *CMSG_FIRSTHDR(struct msghdr *mp)`

- `mp` msghdr指针

- `返回值`

  成功：指向与`msghdr`结构相关联的第一个`cmsghdr`结构

  失败：NULL

*返回与`msghdr`结构相关联的第一个`cmsghdr`结构*

### CMSG_NXTHDR

`struct cmsghdr *CMSG_NXTHDR(struct msghdr *mp, struct cmsghdr *cp)`

- `mp` msghdr指针

- `cp` cmsghdr指针

- `返回值`

  成功：指向与`msghdr`结构相关联的下一个`cmsghdr`结构，该`msghdr`结构给出了当前的`cmsghdr`结构

  当前`cmsghdr`结构是最后一个：NULL

*返回与`msghdr`结构相关联的下一个`cmsghdr`结构*

### CMSG_LEN

`unsigned int CMSG_LEN(unsigned int bytes)`

- `nbytes` 数据长度
- `返回值` 存储数据对象所需长度

*返回存储nbytes长的数据对象所需的字节数*

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

### mkdir

`int mkdir(const char *pathname, mode_t mode)`

- `pathname` 路径

- `mode` 文件访问权限

- `返回值`

  成功：0

  失败：-1

*创建一个新的空目录*

### mkdirat

`int mkdirat(int fd, const char *pathname, mode_t mode)`

- `pathname` 路径

- `mode` 文件访问权限

- `fd` 文件描述符

- `返回值`

  成功：0

  失败：-1

*创建一个新的空目录，并返回文件描述符*

### mkfifo

`int mkfifo(const char *path, mode_t mode)`

- `path` 绝对/相对路径

- `mode` 操作模式

- `返回值`

  成功：0

  失败：-1

*创建FIFO*

### mkfifoat

`int mkfifoat(int fd, const char *path, mode_t mode)`

- `path` 绝对/相对路径

- `mode` 操作模式

- `fd` 文件套接字

- `返回值`

  成功：0

  失败：-1

*创建FIFO*

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

[返回顶部](#POSIX接口)

---



## sys/time.h

### gettimeofday

`int gettimeofday(struct timeval *restrict tp, void *restrict tzp)`

- `tp` 时间信息

- `tzp` 时区（唯一合法值是NULL）

- `返回值` 总是0

*返回（更高分辨率级别，ms）的当前时间和日期*

### utimes

`int utimes(const char *pathname, const struct timeval times[2])`

- `pathname` 路径名

- `times` 时间值

- `返回值`

  成功：0

  失败：-1

*修改路径的时间*

[返回顶部](#POSIX接口)

---



## sys/times.h

### times

`clock_t times(struct tms *buf)`

- buf` 时间

- `返回值`

  成功：流逝的墙上时钟时间（以时钟滴答数为单位）

  失败：-1

*获得墙上时钟时间*

[返回顶部](#POSIX接口)

---



## sys/uio.h

### readv

`ssize_t readv(int filedes, const struct iovec *iov, int iovcnt)`

- `filedes` 描述符

- `iov` iovec数组（最大长度为`IOV_MAX`）

- `iovcnt` iovec数组长度

- `返回值`

  成功：已读/写的字节数

  失败：-1

*散布读（读多个非连续缓冲区）*

### writev

`ssize_t writev(int filedes, const struct iovec *iov, int iovcnt)`

- `filedes` 描述符

- `iov` iovec数组（最大长度为`IOV_MAX`）

- `iovcnt` iovec数组长度

- `返回值`

  成功：已读/写的字节数

  失败：-1

*聚集写（写多个非连续缓冲区）*

[返回顶部](#POSIX接口)

---



## sys/utsname.h

### uname

`int uname(struct utsname *name)`

- `name` 操作系统信息

- `返回值`

  成功：非0值

  失败：-1

*返回与当前主机和操作系统有关的信息*

[返回顶部](#POSIX接口)

---



## sys/wait.h

### wait

`pid_t wait(int *statloc)`

- `statloc`

  - 空指针：不关心终止状态
  - 非空指针：存放子进程的终止状态

- `返回值`

  成功：进程ID

  失败：0或-1

*查找终结的子进程（阻塞）*

### wait3/wait4

`pid_t wait3(int *statloc, int options, struct rusage *rusage)`

`pid_t wait4(pid_t pid, int *statloc, int options, struct rusage *rusage)`

- `statloc`
  - 空指针：不关心终止状态
  - 非空指针：存放子进程的终止状态
- `options`  选项
- `rusage` 资源概况信息
- `pid` 进程ID
- `返回值`
  - 成功：进程ID
  - 失败：-1

*通过内核返回由终止进程及其所有子进程使用的资源概况*

### waitid

`int waitid(idtype_t idtype, id_t id, siginfo_t *infop, int options)`

- `idtype` ID类型

  | 常量   | 说明                                                         |
  | ------ | ------------------------------------------------------------ |
  | P_PID  | 等待一特定进程：`id`包含要等待子进程的进程ID                 |
  | P_PGID | 等待一特定进程组中的任一子进程：`id`包含要等待子进程的进程组ID |
  | P_ALL  | 等待任一子进程：忽略`id`                                     |

- `id` 进程ID

- `infop` 指向造成子进程状态改变有关信号的信息

- `options` 选项

  | 常量       | 说明                                                         |
  | ---------- | ------------------------------------------------------------ |
  | WCONTINUED | 等待一进程，它以前曾被停止，此后又已继续，但其状态尚未报告   |
  | WEXITED    | 等待已退出的进程                                             |
  | WNOHANG    | 如无可用的子进程退出状态，立即返回而非阻塞                   |
  | WNOWAIT    | 不破坏子进程退出状态。该子进程退出状态可由后续的`wait`, `waitid`或`waitpid`调用取得 |
  | WSTOPPED   | 等待一进程，它已经停止，但其状态尚未报告                     |

- `返回值`

  - 成功：0
  - 失败：-1

*获得进程终止状态*

### waitpid

`pid_t waitpid(pid_t pid, int *statloc, int options)`

- `pid` 指定子进程ID

  - `-1` 等待任一子进程；
  - `>0` 等待进程ID与pid相等的子进程；
  - `0` 等待组ID等于调用进程组ID的任一子进程；
  - `<-1` 等待组ID等于pid绝对值的任一子进程。

- `statloc`

  - 空指针：不关心终止状态
  - 非空指针：存放子进程的终止状态

- `options` 选项参数

  | 常量       | 说明                                                         |
  | ---------- | ------------------------------------------------------------ |
  | WCONTINUED | 若实现支持作业控制，那么由`pid`指定的任一子进程在停止后已经继续，但其状态尚未报告，则返回其状态（POSIX.1的XSI扩展） |
  | WNOHANG    | 若由`pid`指定的子进程并不是立即可用的，则`waitpid`不阻塞，此时其返回值为0 |
  | WUNTRACED  | 若某实现支持作业控制，而由`pid`指定的任一子进程已处于停止状态，并且其状态自停止以来还未报告过，则返回其状态，WIFSTOPPED宏确定返回值是否对应于一个停止的子进程 |

- `返回值`

  成功：进程ID

  失败：0或-1

*查找终结的子进程（阻塞/非阻塞）*

[返回顶部](#POSIX接口)

---



## syslog.h

### closelog

`void closelog(void)`

- `返回值` 前日志记录优先级屏蔽值

*关闭日志*

### openlog

`void openlog(const char *ident, int option, int facility)`

- `ident` 认证信息，一般为程序名

- `option` 选项

- `facility` 设施

- `返回值` 前日志记录优先级屏蔽值

*打开日志（可选）*

### setlogmask

`int setlogmask(int maskpri)`

- `maskpri` 屏蔽字

- `返回值` 前日志记录优先级屏蔽值

*设置进程的记录优先级屏蔽字*

### syslog

`void syslog(int priority, const char *format, ...)`

- `priority` 优先级，由`facility`和`level`组合而成；
- `format` 格式化字符串
- `返回值` 前日志记录优先级屏蔽值

*写日志*

[返回顶部](#POSIX接口)

---



## termios.h

### cfgetispeed

`speed_t cfgetispeed(const struct termios *termptr)`

- `termptr` 终端
- `返回值` 波特率

*获取波特率*

### cfgetospeed

`speed_t cfgetospeed(const struct termios *termptr)`

- `termptr` 终端
- `返回值` 波特率

*获取波特率*

### cfsetispeed

`int cfsetispeed(struct termios *termptr, speed_t speed)`

- `termptr` 终端

- `speed` 波特率

- `返回值`

  成功：0

  失败：-1

*设置波特率*

### cfsetospeed

`int cfsetospeed(struct termios *termptr, speed_t speed)`

- `termptr` 终端

- `speed` 波特率

- `返回值`

  成功：0

  失败：-1

*设置波特率*

### tcdrain

`int tcdrain(int filedes)`

- `filedes` 终端设备

- `返回值`

  成功：0

  失败：-1

*等待所有输出都被发送*

### tcflow

`int tcflow(int filedes, int action)`

- `filedes` 终端设备

- `action` 控制动作

  - TCOOFF 输出被挂起；
  - TCOON 重新启动以前被挂起的输出；
  - TCIOFF 系统发送一个STOP字符（这将使终端设备暂停发送数据）；
  - TCION 系统发送一个START字符（这将使终端恢复发送数据）。

- `返回值`

  成功：0

  失败：-1

*对输入和输出流的控制命令进行控制*

### tcflush

`int tcflush(int filedes, int queue)`

- `filedes` 终端设备

- `queue` 控制动作

  - TCIFLUSH 刷清输入队列
  - TCOFLUSH 刷清输出队列
  - TCIOFLUSH 刷清输入，输出队列

- `返回值`

  成功：0

  失败：-1

*刷清（抛弃）输入/输出缓冲区*

### tcgetattr

`int tcgetattr(int filedes, struct termios *termptr)`

- `filedes` 终端设备

- `termptr` 返回的终端属性指针

- `返回值`

  成功：0

  失败：-1

*获得终端属性*

### tcsendbreak

`int tcsendbreak(int filedes, int duration)`

- `filedes` 终端设备

- `duration` 时长（值为0时，此种发送延续0.25至0.5之间）

- `返回值`

  成功：0

  失败：-1

*在一个指定的时间区间内发送连续的0位流*

### tcsetattr

`int tcsetattr(int filedes, int opt, const struct termios *termptr)`

- `filedes` 终端设备

- `termptr` 返回的终端属性指针

- `opt` 选项

  TCSANOW：更改立即发生；

  TCSADRAIN：发送了所有输出后更改才发生（若更改输出参数则应使用此选项）；

  TCSAFLUSH：发送了所有输出后更改才发生（更进一步，在更改发生时未读的所有输入数据都被删除（刷清））；

- `返回值`

  成功：0

  失败：-1

*设置终端属性*

[返回顶部](#POSIX接口)

---



## time.h

### asctime

`char *asctime(const struct tm *tmptr)`

- `tmptr` 本地时间
- `返回值` 指向以null结尾的字符串的指针

*将本地时间转换成字符串*

### ctime

`char *ctime(const time_t *ctlptr)`

- `ctlptr` 日历时间
- `返回值` 指向以null结尾的字符串的指针

*将日历时间转换成字符串*

### gmtime

`struct tm *gmtime(const time_t *calptr)`

- calptr` 日历时间
- `返回值` 指向tm结构的指针

*将日历时间转换为国际标准时间*

### localtime

`struct tm *localtime(const time_t *calptr)`

- alptr` 日历时间
- `返回值` 指向tm结构的指针

*将日历时间转换为本地时间*

### mktime

`time_t mktime(struct tm *tmptr)`

- `tmptr` 本地时间

- `返回值`

  成功：日历时间

  失败：-1

*将本地时间转换成日历时间*

### strftime

`size_t strftime(char *restrict buf, size_t maxsize, const char *restrict format, const struct tm *restrict tmptr)`

- `buf` 字符串数组

- `maxsize` 数组容量

- `format` 字符串格式

- `tmptr` 要格式化的时间值

- `返回值`

  成功：返回存入数组的字符数

  失败：0

*格式化时间*

### time

`time_t time(time_t *calptr)`

- `calptr` 

- `返回值`

  成功：时间值

  失败：-1

*返回当前时间和日期*

[返回顶部](#POSIX接口)

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

### alarm

`unsigned int alarm(unsigned int seconds)`

- `seconds` 时长（秒）
- 返回值：0或以前设置的闹钟时间的余留秒数

*设置一个定时器，当定时器超时时，产生SIGALRM信号*

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

- `fd` 文件描述符
- 返回值
  - 成功：0
  - 失败：-1

关闭文件

；具体见：[I/O#close](io.md)

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

### execl/execv/execle/execve/execlp/execvp/fexecve

`int execl(const char *pathname, const char *arg0, ...)`
`int execv(const char *pathname, char *const argv[])`
`int execle(const char *pathname, const char *arg0, ...)`
`int execve(const char *pathname, char *const argv[], char *const envp[])`
`int execlp(const char *filename, const char *arg0, ...)`
`int execvp(const char *filename, char *const argv[])`
`int fexecve(int fd, char *const argv[], char *const envp[])`

- `pathname` 路径名
  - 如果包含`/`，则将其视为路径名；
  - 否则按PATH环境变量，在它所指定的各目录中搜寻可执行文件。
- `argx` 各种参数
- `返回值`
  - 成功：不返回
  - 失败：-1

*执行程序*

### fdatasync

`int fdatasync(int fd)`

`fdatasync`类似于`fsync`，但它只影响文件的数据部分。而除数据外，fsync还会同步更新文件的属性。具体见：[I/O#fdatasync](io.md)

### fork

`pid_t fork(void)`

- `子进程返回值` 0

- `父进程返回值`

  成功：子进程ID

  失败：-1

*创建子进程*

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

### getgroups

`int getgroups(int gidsetsize, gid_t grouplist[])`

- `gidsetsize` 数组容量

- `grouplist` 数组

- `返回值`

  成功：附加组ID

  失败：-1

*将附加组ID添加到grouplist数组中*

### gethostname

`int gethostname(char *name, int namelen)`

- `name` 返回的主机名字符串

- `namelen` 主机名字符串长度

- `返回值`

  成功：0

  失败：-1

*返回主机名*

### getgid/getegid

`gid_t getgid(void)`
`gid_t getegid(void)`

- `返回值` 组ID

*返回进程的实际组ID/有效组ID*

### getlogin

`char *getlogin(void)`

- `返回值`

  成功：指向登录名字字符串的指针

  失败：NULL

*获得登录名*

### getopt

`int getopt(int argc, char *const argv[], const char *options)`

- `argc` 参数数组长度

- `argv` 参数数组

- `options` 包含该命令支持的选项字符的字符串

- `返回值`

  所有选项被处理完：-1

  所有选项未被处理完：下一个选项字符

*获得命令行参数*

### getpgid

`pid_t getpgid(pid_t pid)`

- `pid` 当前进程ID，为0时等价于`getpgrp()`

- `返回值`

  成功：进程组ID

  失败：-1

*返回调用进程的进程组ID*

### getpgrp

`pid_t getpgrp(void)`

- `返回值` 调用进程的进程组ID

*返回调用进程的进程组ID*

### getpid

`pid_t getpid(void)`

- `返回值` 进程ID

*返回进程的ID*

### getppid

`pid_t getppid(void)`

- `返回值` 进程ID

*返回父进程ID*

### getsid

`pid_t getsid(pid_t pid)`

- `pid` 进程ID

- `返回值`

  成功：会话首进程的进程组ID

  失败：-1

*返回会话首进程的进程组ID（如果pid不属于调用者所在的会话，那么调用进程不能得到该会话首进程的进程组ID*

### getuid/geteuid

`uid_t getuid(void)`

`uid_t geteuid(void)`

- `返回值` 用户ID

*返回实际用户ID/有效用户ID*

### initgroups

`int initgroups(const char *username, gid_t basegid)`

- `usrname` 用户名

- `basegid` 组ID

- `返回值`

  成功：0

  失败：-1

*设置组文件中用户名的映射关系*

### isatty

`int isatty(int filedes)`

- `filedes` 终端

- `返回值`

  是终端设备：1

  不是终端设备：0

*判断是否为终端设备*

### link

`int link(const char *existingpath, const char *newpath)`

- `existingpath` 现有文件路径

- `newpath` 链接文件路径（需要保证此路径不存在）

- `返回值`

  成功：0

  失败：-1

*创建一个指向现有文件的链接*

### linkat

`int linkat(int efd, const char *existingpath, int nfd, const char *newpath, int flag)`

- `existingpath` 现有文件路径

- `newpath` 链接文件路径（需要保证此路径不存在）

- `efd` 现有文件的文件描述符

- `nfd` 链接文件的文件描述符

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

### mice

`int mice(int incr)`

- `incr` 增量

- `返回值`

  成功：新的nice值

  失败：-1

*设置当前进程的nice值（调度优先级）*

### pathconf

`long pathconf(const char *pathname, int name)`

- `name` 限制名
- `pathname` 文件路径

*获得运行时限制*

### pause

`int pause(void)`

- 返回值：-1，errno设置为EINTR

*使进程挂起直至捕捉到一个信号（阻塞）*

### pipe

`int pipe(int fd[2])`

- `fd` 用于返回两个文件描述符，fd[0]为读而打开，fd[1]为写而打开；fd[1]输出的是fd[0]的输入；
- `返回值`
  - 成功：0
  - 失败：-1

*创建管道*

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

### setegid

`int setegid(gid_t gid)`

- `gid` 有效组ID

- `返回值`

  成功：0

  失败：-1

*更改有效组ID*

### seteuid

`int seteuid(uid_t uid)`

- `uid` 有效用户ID

- `返回值`

  成功：0

  失败：-1

*更改有效用户ID*

### setgid

`int setgid(gid_t gid)`

- `gid` 组ID

- `返回值`

  成功：0

  失败：-1

*设置实际组ID和有效组ID*

### setpgid

`int setpgid(pid_t pid, pid_t pgid)`

- `pid` 当前进程ID

- `pgid` 进程组ID

- `返回值`

  成功：0

  失败：-1

*创建/加入一个进程组*

### setgroups

`int setgroups(int ngroups, const gid_t grouplist[])`

- `ngroups` ID数组容量

- `grouplist` ID数组

- `返回值`

  成功：0

  失败：-1

*设置附加组ID表*

### setregid

`int setregid(gid_t rgid, gid_t egid)`

- `rgid` 实际组ID和有效组ID
- `egid` 实际组ID和有效组ID
- `返回值`
  - 成功：0
  - 失败：-1

*交换实际用户ID和有效用户ID*

### setsid

`pid_t setsid(void)`

- `返回值`

  成功：进程组ID

  失败：-1

*建立一个新会话（如果调用此函数的进程已经是一个进程组的组长，则此函数返回错误）*

### setreuid

`int setreuid(uid_t ruid, uid_t euid)`

- `ruid` 实际用户ID和有效用户ID
- `euid` 实际用户ID和有效用户ID
- `返回值`
  - 成功：0
  - 失败：-1

*交换实际用户ID和有效用户ID*

### setuid

`int setuid(uid_t uid)`

- `uid` 用户ID

- `返回值`

  成功：0

  失败：-1

*设置实际用户ID和有效用户ID*

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

### system

`int system(const char *cmdstring)`

- `cmdstring` 命令
- `返回值`
  - `fork`失败或者`waitpid`返回除`EINTR`之外的出错：返回-1，并设置errno以指示错误类型；
  - `exec`失败：如同`shell`执行了`exit(127)`一样；
  - `fork`，`exec`和`waitpid`都执行成功：返回shell的终止状态。

*执行命令*

### tcgetpgrp

`pid_t tcgetpgrp(int fd)`

- `fd`文件描述符

- `返回值`

  成功：返回前台进程组ID

  失败：-1

*返回前台进程组ID（与fd上打开的终端相关联）*

### tcgetsid

`pid_t tcgetsid(int fd)`

- `fd`文件描述符

- `返回值`

  成功：会话首进程的进程组ID

  失败：-1

*返回会话首进程的进程组ID*

### tcsetpgrp

`int tcsetpgrp(int fd, pid_t pgrpid)`

- `fd`文件描述符

- `pgrpid`前台进程组ID

- `返回值`

  成功：0

  失败：-1

*设置前台进程组ID*

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