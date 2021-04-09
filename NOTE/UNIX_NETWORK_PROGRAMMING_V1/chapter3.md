# 第三章 套接字编程简介


## 套接字地址结构

### IPV4套接字地址结构
```c
// 头文件:<netinet/in.h>
struct in_addr {
    in_addr_t s_addr;           // 至少32位无符号整数类型
};
struct sockaddr_in {
    uint8_t         sin_len;    // 长度字段
    sa_family_t     sin_family; // 地址族; 任何无符号整数类型
    in_port_t       sin_port;   // TCP或UDP端口; 至少16位的无符号整数类型

    struct in_addr  sin_addr;

    char sin_zero[8];
};
```

POSIX规范要求的数据类型

| 数据类型                                                     | 说明                                                         | 头文件                                                       |
| ------------------------------------------------------------ | ------------------------------------------------------------ | ------------------------------------------------------------ |
| int8_t<br>uint8_t<br>int16_t<br>uint16_t<br>int32_t<br>uint32_t | 带符号的8位整数<br>无符号的8位整数<br>带符号的16位整数<br>无符号的16位整数<br>带符号的32位整数<br>无符号的32位整数 | <sys/types.h><br><sys/types.h><br><sys/types.h><br><sys/types.h><br><sys/types.h><br><sys/types.h> |
| sa_family_t<br>sockle_t                                      | 套接字地址结构的地址族<br>套接字地址结构的长度，一般为uint32_t | <sys/socket.h><br><sys/socket.h>                             |
| in_addr_t<br>in_port_t                                       | IPv4地址，一般为uint32_t<br>TCP或UDP端口，一般为uint16_t     | <netinet/in.h><br><netinet/in.h>                             |

### 通用套接字地址结构

```c
// 头文件:<sys/socket.h>
struct sockaddr {
    uint8_t     sa_len;
    sa_family_t sa_family;
    char        sa_data[14];
};
```

### IPV6套接字地址结构
```c
// 头文件:<netinet/in.h>
struct in6_addr {
    uint8_t s6_addr[16];
};
#defie SIN6_LEN
struct sockaddr_in6 {
    uint8_t         sin6_len;
    sa_family_t     sin6_family;
    in_port_t       sin6_port;

    uint32_t        sin6_flowinfo; // 流标; 低序20位是流标(flow label),高序12位保留
    struct in6_addr sin6_addr;

    uint32_t        sin6_scope_id;
}
```

- 如果系统支持套接字地址结构中的长度字段，那么SIN6_LEN常值必须定义
- IPv6的地址族是AF_INET6，而IPv4的地址族是AF_INET
- 结构中字段的先后顺序做过编排，使得如果sockaddr_in6结构本身是64位对齐的，那么128位的sin6_addr字段也是64位对齐的。在一些64位处理器上，如果64位数据存储在某个64位边界位置，那么对它的访问将得到优化处理。
- Sin6_flowinfo字段分成2个字段:
  - 低序20位是流标(flow label)
  - 高序12位保留
- 对于具备范围的地址(scoped address), sin6_scope_id字段标识其范围(scope)，最常见的是链路局部地址(link-local address)的接口索引(interface index)

### 新的通用套接字地址结构

```c
// 头文件:<netinet/in.h>
struct sockaddr_storage { // 存储套接字地址结构
    uint8_t     ss_len;
    sa_family_t ss_family;
};
```

### 套接字地址结构的比较
![3-6](RES/3-6.png)



## 值-结果参数

### 字节排序函数

从进程到内核传递套接字地址结构的函数:

- bind
- connect
- sendto

![3-7](RES/3-7.png)

从内核到进程传递套接字地址结构的函数:

- accept
- recvfrom
- getsockname
- getpeername

![3-8](RES/3-8.png)



## 字节排序函数

![3-9](RES/3-9.png)

### 确定主机字节序的程序
```c
#include "unp.h"
int
main (int argc, char **argv)
{
    union {
        short   s;
        char    c[sizeof(short)]  ;
    } un;
    un.s = 0x0102;
    printf("%s: ", CPU_VENDOR_OS);
    if (sizeof(short) == 2) {
        if (un.c[0] == 1 && un.c[1] == 2)
            printf("big-endian\n");
        else if (un.c[0] == 2 && un.c[1] == 1)
            printf("little-endian\n");
        else
            printf("unknown\n");
    } else
        printf("sizeof(short) = %d\n", sizeof(short));
    exit(0);
}
```

### 主机字节序与网络字节序的转换
```c++
#include <netinet/in.h>
/*主机字节序转网络字节序*/
uint16_t htons(uint16_t host16bitvalue);
uint32_t htonl(uint32_t host32bitvalue);

/*网络字节序转主机字节序*/
uint16_t ntohs(uint16_t net16bitvalue);
uint32_t ntohl(uint32_t net32bitvalue);
```



## 字节操纵函数

头文件 `strings.h`

