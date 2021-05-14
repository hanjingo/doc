# `arpa/inet.h`

- [inet_aton](#inet_aton)
- [inet_ntoa](#inet_ntoa)



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

