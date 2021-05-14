# netdb.h

- [getnameinfo](#getnameinfo)



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

