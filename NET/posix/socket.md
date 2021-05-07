# 套接字

## `netinet/in.h`

- IPv4套接字地址结构

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

- IPv6套接字地址结构
	
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
	
- 通用套接字地址结构
	
	```c
struct sockaddr_storage { // 存储套接字地址结构
	    uint8_t     ss_len;
	    sa_family_t ss_family;
	};
	```
	
- `uint16_t htons(uint16_t host16bitvalue)` 主机字节序转网络字节序(16位)
	
	- host16bitvalue

- `uint32_t htonl(uint32_t host32bitvalue)` 主机字节序转网络字节序(32位)

  - host32bitvalue

- `uint16_t ntohs(uint16_t net16bitvalue)` 网络字节序转主机字节序(16位)

  - net16bitvalue

- `uint32_t ntohl(uint32_t net32bitvalue)` 网络字节序转主机字节序(32位)

  - net32bitvalue



## `sys/socket.h`

- 通用套接字地址结构

  ```c
  struct sockaddr {
      uint8_t     sa_len;
      sa_family_t sa_family;
      char        sa_data[14];
  };
  ```

- 组播结构体

  ```c
  struct ip_mreq {
  	struct  in_addr imr_multiaddr; // 组播的ip地址
  	struct  in_addr imr_interface; // 指定加入组播使用哪张网卡的IP地址
  };
  ```

- `int setsockopt(int, int, int, const void *, socklen_t)` 设置套接字选项

  - 

  

### `arpa/inet.h`

- `int inet_aton(const char *strptr, struct in_addr *addrptr)` 将c字符串转换成一个32位的网络字节序二进制值

  - strptr: 需要转换的c字符串
  - addrptr: 用来存储网络字节序二进制值的指针

- `char *inet_ntoa(struct in_addr inaddr)` 将32位的网络字节序二进制IPv4地址转换成相应的点分十进制字符串。

  - inaddr:

  **返回值所指向的字符串驻留在静态内存中，改函数不可重入！！！**


