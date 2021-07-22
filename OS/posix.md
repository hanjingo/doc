[TOC]

# POSIX接口

## `arpa/inet.h`

### inet_aton c字符串转网络字节序

`int inet_aton(const char *strptr, struct in_addr *addrptr)`

  - strptr: 需要转换的c字符串
  - addrptr: 用来存储网络字节序二进制值的指针

将c字符串转换成一个32位的网络字节序二进制值

---

### inet_ntoa 网络字节序转点分十进制字符串

`char *inet_ntoa(struct in_addr inaddr)` 

  - inaddr:

将32位的网络字节序二进制IPv4地址转换成相应的点分十进制字符串。

  **返回值所指向的字符串驻留在静态内存中，该函数不可重入！！！**

---



## `netdb.h`

### getnameinfo 返回描述套接字主机的字符串和服务字符串

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
