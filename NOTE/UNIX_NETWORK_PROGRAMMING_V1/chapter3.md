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
}
```

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

### 新的通用套接字地址结构
```c
// 头文件:<netinet/in.h>
// 存储套接字地址结构
struct sockaddr_storage {
    uint8_t     ss_len;
    sa_family_t ss_family;
};
```

### 套接字地址结构的比较
![不同套接字地址结构的比较]()

## 值-结果参数
### 字节排序函数
![从进程到内核传递套接字地址结构]()

![从内核到进程传递套接字地址结构]()

## 字节排序函数
![16位整数的小端字节序和大端字节序]()

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