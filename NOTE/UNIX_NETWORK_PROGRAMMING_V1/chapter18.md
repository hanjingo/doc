# 第十八章 路由套接字

[TOC]



## 18.1 概述



## 18.2 数据链路套接字地址结构

```c++
struct sockaddr_dl {
    uint8_t     sdl_len;
    sa_family_t sdl_family;
    uint16_t    sdl_index;
    uint8_t     sdl_type;
    uint8_t     sdl_nlen;
    uint8_t     sdl_alen;
    uint8_t     sdl_slen;
    char        sdl_data[12];
};
```

*数据链路套接字地址结构*



## 18.3 读和写

| 消息类型       | 去往内核？ | 来自内核？ | 说明                           | 结构类型          |
| -------------- | ---------- | ---------- | ------------------------------ | ----------------- |
| RTM_ADD        | Y          | Y          | 增加路径                       | rt_msghdr         |
| RTM_CHANGE     | Y          | Y          | 改动网关，测度或标志           | rt_msghdr         |
| RTM_DELADDR    |            | Y          | 地址正被删离接口               | ifa_msghdr        |
| RTM_DELETE     | Y          | Y          | 删除路径                       | rt_msghdr         |
| RTM_DELMADDR   |            | Y          | 多播地址正被删离接口           | ifma_msghdr       |
| RTM_GET        | Y          | Y          | 报告测度及其它路径信息         | rt_msghdr         |
| RTM_IFANNOUNCE |            | Y          | 接口正被增至或删离系统         | if_announcemsghdr |
| RTM_IFINFO     |            | Y          | 接口正在开工，停工等           | if_msghdr         |
| RTM_LOCK       | Y          | Y          | 锁住给定的测度                 | rt_msghdr         |
| RTM_LOSING     |            | Y          | 内核怀疑路径即将失效           | rt_msghdr         |
| RTM_MISS       |            | Y          | 地址查找失败                   | rt_msghdr         |
| RTM_NEWADDR    |            | Y          | 地址正被增至接口               | ifa_msghdr        |
| RTM_NEWMADDR   |            | Y          | 多播地址正被增至接口           | ifma_msghdr       |
| RTM_REDIRECT   |            | Y          | 内核被告知使用另外的路径       | rt_msghdr         |
| RTM_RESOLVE    |            | Y          | 请求把目的地址解析成链路层地址 | rt_msghdr         |

*通过路由套接字交换的消息类型*

```c++
struct rt_msghdr {
    u_short rtm_msglen;
    u_char  rtm_version;
    u_char  rtm_type;
    u_short rtm_index;
    int     rtm_flags;
    int     rtm_addrs;
    pid_t   rtm_pid;
    int     rtm_seq;
    int     rtm_errno;
    int     rtm_use;
    u_long  rtm_inits;
    struct rt_metrics rtm_rmx;
};
struct if_msghdr {
    u_short ifm_msglen;
    u_char  ifm_version;
    u_char  ifm_type;
    int     ifm_addrs;
    int     ifm_flags;
    u_short ifm_index;
    struct if_data ifm_data;
};
struct ifa_msghdr {
    u_short ifam_msglen;
    u_char  ifam_version;
    u_char  ifam_type;
    int     ifam_addrs;
    int     ifam_flags;
    u_short ifam_index;
    int     ifam_metric;
};
struct ifma_msghdr {
    u_short ifmam_msglen;
    u_char  ifmam_version;
    u_char  ifmam_type;
    int     ifmam_addrs;
    int     ifmam_fags;
    u_short ifmam_index;
};
struct if_announcemsghdr {
    u_short ifan_msglen;
    u_char  ifan_version;
    u_char  ifan_type;
    u_short ifan_index;
    char    ifan_name[IFNAMSIZ];
    u_short ifan_what;
};
```

*路由消息返回的三种结构*

![18_4](res/18_4.png)

*在路由消息中用于指称套接字地址结构的常值*

![18_5](res/18_5.png)

*RTM_GET命令通过路由套接字与内核交换的数据*

```c++
#include "unproute.h"
#define BUFLEN (sizeof(struct rt_msghdr) + 512)
// sizeof(struct sockaddr_in6) * 8 = 192
#define SEQ 9999
int 
main(int argc, char **argv)
{
    int sockfd;
    char *buf;
    pid_t pid;
    ssize_t n;
    struct rt_msghdr *rtm;
    struct sockaddr *sa, *rti_info[RTAX_MAX];
    struct sockaddr_in *sin;
    if (argc != 2)
        err_quit("usage: getrt <IPaddress>");
    sockfd = Socket(AF_ROUTE, SOCK_RAW, 0);
    buf = Calloc(1, BUFLEN);
    rtm = (struct rt_msghdr *)buf;
    rtm->rtm_msglen = sizeof(struct rt_msghdr) + sizeof(struct sockaddr_in);
    rtm->rtm_version = RTM_VERSION;
    rtm->rtm_type = RTM_GET;
    rtm->rtm_addrs = RTA_DST;
    rtm->rtm_pid = pid = getpid();
    
}
```

