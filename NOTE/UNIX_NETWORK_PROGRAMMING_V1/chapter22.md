# 第22章 高级UDP套接字编程

- [概述](#概述)



## 概述



## 接收标志_目的IP地址和接口索引

```c++
#include "unp.h"
#include <sys/param.h>

struct unp_in_pktinfo {
  struct in_addr ipi_addr;
  int		 				 ipi_ifindex;
};

ssize_t
recvfrom_flags(int fd, void *ptr, size_t nbytes, int *flagsp,
               SA *sa, socklen_t *salenptr, struct unp_in_pktinfo *pktp)
{
  struct msghdr msg;
  struct iovec iov[1];
  ssize_t n;
#ifdef HAVE_MSGHDR_MSG_CONTROL
  struct cmsghdr *cmptr;
  union {
    struct cms ghdr cm;
    char control[CMSG_SPACE(sizeof(struct in_addr)) + 
                 CMSG_SPACE(sizeof(struct unp_in_pktinfo))];
  } control_un;
  msg.msg_control = control_un.control;
  msg.msg_controllen = sizeof(control_un.control);
  msg.msg_flags = 0;
#else
  bzero(&msg, sizeof(msg));
#endif
  msg.msg_name = sa;
  msg.msg_namelen = *salenptr;
  iov[0].iov_base = ptr;
  iov[0].iov_len = nbytes;
  msg.msg_iov = iov;
  msg.msg_iovlen = 1;
  if( (n) )
}
```

