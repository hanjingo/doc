# `netinet/in.h`

- [IPv4套接字地址结构](#IPv4套接字地址结构)
- [IPv6套接字地址结构](#IPv6套接字地址结构)
- [通用套接字地址结构](#通用套接字地址结构)
- [htons](#htons)
- [htonl](#htonl) 
- [ntohs](#ntohs)
- [nthol](#nthol)



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

