# `sys/socket.h`

- [通用套接字地址结构](#通用套接字地址结构)
- [组播结构体](#组播结构体)
- [setsockopt](#setsockopt)



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

