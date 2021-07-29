[TOC]

# POSIX接口

POSIX(Portable Operating System Interface， 可移植操作系统接口)是一个由IEEE(电气和电子工程师学会)制订的标准族。

## 头文件

#### 必需

| 头文件            | 说明                 |
| ----------------- | -------------------- |
| `<aio.h>`         | 异步I/O              |
| `<cpio.h>`        | cpio归档值           |
| `<dirent.h>`      | 目录项               |
| `<dlfcn.h>`       | 动态链接             |
| `<fcntl.h>`       | 文件控制             |
| `<fnmatch.h>`     | 文件名匹配类型       |
| `<glob.h>`        | 路径名模式匹配与生成 |
| `<grp.h>`         | 组代码               |
| `<iconv.h>`       | 代码集变换实用程序   |
| `<langinfo.h>`    | 语言信息常量         |
| `<monetary.h>`    | 货币类型与函数       |
| `<netdb.h>`       | 网络数据库操作       |
| `<nl_types.h>`    | 消息类               |
| `<poll.h>`        | 投票函数             |
| `<pthread.h>`     | 线程                 |
| `<pwd.h>`         | 口令文件             |
| `<regex.h>`       | 正则表达式           |
| `<sched.h>`       | 执行调度             |
| `<semaphore.h>`   | 信号量               |
| `<strings.h>`     | 字符串操作           |
| `<tar.h>`         | tar归档值            |
| `<termios.h>`     | 终端I/O              |
| `<unistd.h>`      | 符号常量             |
| `<wordexp.h>`     | 字扩充类型           |
| `<arpa/inet.h>`   | 因特网定义           |
| `<net/if.h>`      | 套接字本地接口       |
| `<netinet/in.h>`  | 因特网地址族         |
| `<netinet/tcp.h>` | 传输控制协议定义     |
| `<sys/mman.h>`    | 存储管理声明         |
| `<sys/select.h>`  | select函数           |
| `<sys/socket.h>`  | 套接字接口           |
| `<sys/stat.h>`    | 文件状态             |
| `<sys/statvfs.h>` | 文件系统信息         |
| `<sys/times.h>`   | 进程时间             |
| `<sys/types.h>`   | 基本系统数据类型     |
| `<sys/un.h>`      | UNIX域套接字定义     |
| `<sys/utsname.h>` | 系统名               |
| `<sys/wait.h>`    | 进程控制             |

#### 可选

| 头文件       | 说明          |
| ------------ | ------------- |
| `<mqueue.h>` | 消息队列      |
| `<spawn.h>`  | 实时spawn接口 |

#### XSI可选

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

#### 可选项

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

## `arpa/inet.h`

### inet_aton 

`int inet_aton(const char *strptr, struct in_addr *addrptr)`

  - strptr: 需要转换的c字符串
  - addrptr: 用来存储网络字节序二进制值的指针

将c字符串转换成一个32位的网络字节序二进制值

---

### inet_ntoa

`char *inet_ntoa(struct in_addr inaddr)` 

  - inaddr:

将32位的网络字节序二进制IPv4地址转换成相应的点分十进制字符串。

  **返回值所指向的字符串驻留在静态内存中，该函数不可重入！！！**

---



## `dlfcn.h`



---



## `netdb.h`

### getnameinfo

`int getnameinfo(const struct sockaddr *sockaddr, socklen_t addrlen, char *host, size_t hostlen, char *service, size_t servlen, int flags )`

- sockaddr
- addrlen
- host
- hostlen
- service
- servicelen
- flags

- return
  - 成功 0
  - 其他 非0

返回描述套接字主机的字符串和服务字符串

---



## `netinet/in.h`

### IPv4套接字地址结构

```c
struct in_addr {
    in_addr_t s_addr; // 至少32位无符号整数类型
};
struct sockaddr_in {
    uint8_t         sin_len; 		// 长度字段
    sa_family_t     sin_family; // 地址族; 任何无符号整数类型
    in_port_t       sin_port; 	// TCP或UDP端口
    struct in_addr  sin_addr;
    char 						sin_zero[8];
};
```

---

### IPv6套接字地址结构

```c
struct in6_addr {
    uint8_t s6_addr[16];
};
#defie SIN6_LEN
struct sockaddr_in6 {
    uint8_t         sin6_len;
    sa_family_t     sin6_family;
    in_port_t       sin6_port;
    uint32_t        sin6_flowinfo;
    struct in6_addr sin6_addr;
    uint32_t        sin6_scope_id;
}
```

---

### 通用套接字地址结构

```c
struct sockaddr_storage { // 存储套接字地址结构
    uint8_t     ss_len;
    sa_family_t ss_family;
};
```

---

### htons

`uint16_t htons(uint16_t host16bitvalue)` 

- `host16bitvalue`

主机字节序转网络字节序(16位)

---

### htonl

`uint32_t htonl(uint32_t host32bitvalue)` 

- `host32bitvalue`

主机字节序转网络字节序(32位)

---

### ntohs

`uint16_t ntohs(uint16_t net16bitvalue)` 

- `net16bitvalue`

网络字节序转主机字节序(16位)

---

### nthol

`uint32_t ntohl(uint32_t net32bitvalue)` 

- `net32bitvalue`

网络字节序转主机字节序(32位)

---



## `string.h`

### memset

`void *memset(void *dest, int c, size_t len)`

- dest: 被设置的字符串
- c: 要设置的值
- len: 要设置的字节数

设置字符串为指定值

---

### memcpy

`void *memcpy(void *dest, const void *src, size_t nbytes)`

- dest: 目标字符串
- src: 源字符串
- nbytes: 要复制的字节数

复制字符串

**注意：当dest和src重叠时，memcpy操作结果无法预料**

---

### memcmp

`int memcmp(const void *ptr1, const void *ptr2, size_t nbytes)`

- ptr1: 字符串1
- ptr2: 字符串2
- nbytes: 要比较的字符串长度

比较字符串

---



## `strings.h`

### bzero

`void bzero(void *dest, size_t nbytes)` 

- dest: 被设置的字符串
- nbytes: 要设置的字节数

 设置字符串的值为0

---

### bcopy

`void bcopy(const void *src, void *dest, size_t nbytes)` 

- src: 源字符串
- dest: 目标字符串
- nbytes: 要复制的数量

复制字符串

---

### bcmp

`int bcmp(const void *ptr1, const void *ptr2, size_t nbytes)` 

- ptr1: 字符串1

- ptr2: 字符串2

- nbytes: 要比较的字符长度

比较字符串

---



## `sys/socket.h`

### 通用套接字地址结构

  ```c
struct sockaddr {
    uint8_t     sa_len;
    sa_family_t sa_family;
    char        sa_data[14];
};
  ```

---

### 组播结构体

  ```c
struct ip_mreq {
	struct  in_addr imr_multiaddr; // 组播的ip地址
	struct  in_addr imr_interface; // 指定加入组播使用哪张网卡的IP地址
};
  ```

---

### setsockopt

`int setsockopt(int, int, int, const void *, socklen_t)`

设置套接字选项

---



## 其它

### memcpy



## 参考

- <<UNIX环境高级编程>> 第三版`_POSIX_`
