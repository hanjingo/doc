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
| `<pthread.h>`                       | 线程                 |
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
| `<sys/times.h>`                     | 进程时间             |
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

### getgrgid/getgrnam

`struct group *getgrgid(gid_t gid)`
`struct group *getgrnam(const char *name)`

- `gid` 组ID

- `name` 组名

- `返回值`

  成功：group指针

  失败：NULL

*根据组名/数值组ID查看组信息*

### setgrent

`void setgrent(void)`

*打开组文件文件中的条目*

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



## shadow

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

---



## sys/resource.h

### getrlimit

`int getrlimit(int resource, struct rlimit *rlptr)`

- `resource` 资源

- `rlptr` 限制值

- `返回值`

  成功：0

  失败：非0

*设置进程的资源限制*

### setrlimit

`int setrlimit(int resource, const struct rlimit *rlptr)`

- `resource` 资源

- `rlptr` 限制值

- `返回值`

  成功：0

  失败：非0

*更新进程的资源限制*

---



## sys/select.h

### select

`int select(int maxfdp1, fd_set *readset, fd_set *writeset, fd_set *exceptset, const struct timeval *timeout)`

允许进程指示内核等待多个事件中的任何一个发生，并只在有一个或多个时间发生或经历一段指定的时间后才唤醒它。具体见：[I/O#select](NET/io.md)

[返回顶部](#POSIX接口)

---



## stdio

### clearerr

`void clearerr(FILE *fp)`

- `fp` 流

*清空错误标记*

### fclose

`int fclose(FILE *fp)`

- `fp` 流

- `返回值`

  成功：0

  失败：EOF

*关闭流*

### ferror/feof

`int ferror(FILE *fp)`
`int feof(FILE *fp)`

- `fp` 流

- `返回值`

  条件为真：非0

  条件为假：0

*判断错误类型/文件结束*

### fflush

`int fflush(FILE *fp)`

- `fp` 文件流

- `返回值`

  成功：0

  失败：EOF

*强制刷出一个流*

### fgetpos/fsetpos

`int fgetpos(FILE *restrict fp, fpos_t *restrict pos)`
`int fsetpos(FILE *fp, const fpos_t *pos)`

- `fp` 流

- `pos` 当前位置

- `返回值`

  成功：0

  失败：非0

*获取/设置流的当前位置*

### fileno

`int fileno(FILE *fp)`

- `fp` 流
- `返回值` 与流相关联的文件描述符

*获得流的描述符*

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

### fread

`size_t fread(void *restrict ptr, size_t size, size_t nobj, FILE *restrict fp)`

- `ptr` 缓冲区
- `size` 缓冲区长度
- `nobj` 要读/写的数据长度
- `fp` 流
- `返回值`对象数

*读二进制数据*

### fseek/fseeko

`int fseek(FILE *fp, long offset, int whence)`

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

### ftell/ftello

`long ftell(FILE *fp)`

`off_t ftello(FILE *fp);`

- `fp` 流

- `返回值`

  成功：当前文件位置

  失败：(off_t)-1

*定位标准I/O流*

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

### getc/getchar/fgetc

`int getc(FILE *fp)`
`int fgetc(FILE *fp)`
`int getchar(void)`

- `fp` 流

- `返回值`

  成功：下一个字符

  到达文件尾或出错：EOF

*一次读一个字符*

### gets/fgets

`char *fgets(char *restrict buf, int n, FILE *restrict fp)`
`char *gets(char *buf)`

- `buf` 缓冲区

- `n` 缓冲区长度

- `fp` 流

- `返回值`

  成功：buf

  到达文件尾或出错：NULL

*从流中读一行字符串*

### mkstemp

`int mkstemp(char *template)`

- `template` 字符串模板

- `返回值`

  成功：文件描述符

  失败：-1

*创建临时文件*

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

### putc/putchar/fputc

`int putc(int c, FILE *fp)`
`int fputc(int c, FILE *fp)`
`int putchar(int c)`

- `c` 字符

- `fp` 流

- `返回值`

  成功：c

  失败：EOF

*写单个字符到流中*

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

### malloc

`void *malloc(size_t size)`

- `size` 长度（字节数）

- `返回值`

  成功：非空指针

  失败：NULL

*分配指定字节数的存储区，此存储区中的初始值不确定。*

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

### getpid/getppid

`pid_t getpid(void)`

`pid_t getppid(void)`

- `返回值` 进程ID

*返回进程的ID/父进程ID*

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

### setgroups

`int setgroups(int ngroups, const gid_t grouplist[])`

- `ngroups` ID数组容量

- `grouplist` ID数组

- `返回值`

  成功：0

  失败：-1

*设置附加组ID表*

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