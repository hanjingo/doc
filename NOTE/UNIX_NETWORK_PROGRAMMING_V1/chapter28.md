# 第二十八章 原始套接字

[TOC]



## 28.1 概述

原始套接字提供普通的TCP和UDP套接字所不提供的以下能力：

- 进程可以读与写ICMPv4，IGMPv4和ICMPv6等分组。
- 进程可以读写内核不处理其协议字段的IPv4数据报。
- 进程还可以使用IP_HDRINCL套接字选项自行构造IPv4首部。



## 28.2 原始套接字创建

创建原始套接字步骤：

1. 把第二个参数指定为SOCK_RAW并调用socket函数，以创建一个原始套接字；第三个参数（协议）通常不为0。

   例：

   ```c++
   int sockfd;
   sockfd = socket(AF_INET, SOCK_RAW, protocol);
   ```

2. 可以在原始套接字上开启IP_HDRINCL套接字选项。

   例：

   ```c++
   const int on = 1;
   if (setsockopt(sockfd, IPPROTO_IP, IP_HDRINCL, &on, sizeof(on)) < 0)
       // 出错处理
   ```

3. 可以在原始套接字上调用bind函数，用于设置从这个原始套接字发送的所有数据报的源IP地址（只在IP_HDRINCL套接字选项未开启的前提下）。

4. 可以在这个原始套接字上调用connect函数，用于设置外地地址。



## 28.3 原始套接字输出

原始套接字的输出遵循以下规则：

- 普通输出通过调用sendto或sendmsg并指定目的IP地址完成。如果套接字已经连接，那么也可以调用write，writev或send。

- 如果IP_HDRINCL套接字选项未开启，那么由进程让内核发送的数据的起始地址指的是IP首部之后的第一个字节，因为内核将构造IP首部并把它置于来自进程的数据之前。内核把所构造IPv4首部的协议字段设置成来自socket调用的第三个参数。

- 如果IP_HDRINCL套接字选项已开启，那么由进程让内核发送的数据的起始地址指的是IP首部的第一个字节。进程调用输出函数写出的数据量必须包括IP首部的大小。整个IP首部由进程构造。

  注意事项：

  1. IPv4标识字段可置为0，从而告知内核设置该值；
  2. IPv4首部校验和字段总是由内核计算并存储；
  3. IPv4选项字段是可选的。

- 内核会对超出外出接口MTU的原始分组执行分片。

### 28.3.1 IPv6的差异

IPv6原始套接字与IPv4相比存在如下差异：

- 通过IPv6原始套接字发送和接受的协议首部中的所有字段均采用网络字节序；
- IPv6不存在与IPv4的IP_HDRINCL套接字选项类似的东西。通过IPv6原始套接字无法读入或写出完整的IPv6分组（包括IPv6首部和任何扩展首部）。IPv6首部的几乎所有字段以及所有扩展首部都可以通过套接字选项或辅助数据由应用进程指定或获取。如果应用进程需要读入或写出完整的IPv6数据报，那就必须使用数据链路访问。
- IPv6原始套接字的校验和处理存在差异。

### 28.3.2 IPV6_CHECKSUM套接字选项

对于其他IPv6原始套接字（不是以IPPROTO_ICMPV6为第三个参数调用socket创建的那些原始套接字），进程可以使用一个套接字选项告知内核是否计算并存储外出分组中的校验和，且验证接收分组中的校验和。该选项默认关闭，可以通过以下代码开启：

```c++
int offset = 2;
if (setsockopt(sockfd, IPPROTO_IPV6, IPV6_CHECKSUM, 
               &offset, sizeof(offset)) < 0)
    // 出错处理
```



## 28.4 原始套接字输入

内核把接收到的IP数据报传递到原始套接字规则：

- 接收到的UDP分组和TCP分组和TCP分组绝不传递到任何原始套接字。
- 大多数ICMP分组在内核处理完其中的ICMP消息后传递到原始套接字。
- 所有IGMP分组在内核完成处理其中的IGMP消息后传递到原始套接字。
- 内核不认识其协议字段的所有IP数据报传递到原始套接字。
- 如果某个数据报以片段形式到达，那么在它的所有片段均到达且重组出该数据报之前，不传递任何片段分组到原始套接字。

内核对每个原始套接字均执行以下3个测试，只有这3个测试结果为真，内核才把接收到的数据报地送到这个套接字：

- 如果创建这个原始套接字时制定了非0的协议参数（socket的第三个参数），那么接收到的数据报的协议字段必须匹配该值，否则该数据报不递送到这个套接字。
- 如果这个原始套接字已由bind调用绑定了某个本地IP地址，那么接收到的数据报的目的IP地址必须匹配这个绑定地址，否则该数据报不递送到这个套接字。
- 如果这个原始套接字已由connect调用指定了某个外地IP地址，那么接收到的数据报的源IP地址必须匹配这个已连接地址，否则该数据报不递送到这个套接字。

```c++
#include <netinet/icmp6.h>
void ICMP6_FILTER_SETPASSALL(struct icmp6_filter *filt); // 指定所有消息类型都传递到应用进程
void ICMP6_FILTER_SETBLOCKALL(struct icmp6_filter *filt); // 指定不传递任何消息类型
void ICMP6_FILTER_SETPASS(int msgtype struct icmp6_filter *filt); // 放行某个指定消息类型到应用进程的传递
void ICMP6_FILTER_SETBLOCK(int msgtype, struct icmp6_filter *filt); // 阻止某个指定消息类型的传递
int ICMP6_FILTER_WILLPASS(int msgtype, const struct icmp6_filter *filt); // 判断消息类型是否被过滤器放行
int ICMP6_FILTER_WILLBLOCK(int msgtype, const struct icmp6_filter *filt);// 判断消息类型是否被过滤器阻止
```



## 28.5 ping程序

![28_1](res/28_1.png)

*ICMPv4和ICMPv6回射请求和回射应答消息的格式*

![28_3](res/28_3.png)

*我们的ping程序中各个函数的概貌*

```c++
#include "unp.h"
#include <netinet/in_system.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#define BUFSIZE 1500
/* globals */
char sendbuf[BUFSIZE];
int datalen;
char *host;
int nset;
pid_t pid;
int sockfd;
int verbose;
/* function prototypes */
void init_v6(void);
void proc_v4(char *, ssize_t, struct msghdr *, struct timeval *);
void proc_v6(char *, ssize_t, struct msghdr *, struct timeval *);
void send_v4(void);
void send_v6(void);
void readloop(void);
void sig_alrm(int);
void tv_sub(struct timeval *, struct timeval *);
struct proto { // 用于处理IPv4与IPv6之间的差异
    void (*fproc)(char *, ssize_t, struct msghdr *, struct timeval *);
    void (*fsend)(void);
    void (*finit)(void);
    struct sockaddr *sasend;
    struct sockaddr *sarecv;
    socklen_t salen;
    int icmpproto;
} *pr;
#ifdef IPV6
#include <netinet/ip6.h>
#include <netinet/icmp6.h>
#endif
```

*ping/ping.h*

```c++
#include "ping.h"
struct proto proto_v4 = 
	{proc_v4, send_v4, NULL, NULL, NULL, 0, IPPROTO_ICMP};
#ifdef IPV6
struct protoproto_v6 = 
	{proc_v6, send_v6, init_v6, NULL, NULL, 0, IPPROTO_ICMPV6};
#endif
int datalen = 56; // 随同回射请求发送的可选数据量
int 
main(int argc, char **argv)
{
    int c;
    struct addrinfo *ai;
    char *h;
    opterr = 0;
 	while ((c = getopt(argc, argv, "v")) != -1) {
        switch(c) {
            case 'v':
                verbose++;
                break;
            case '?':
                err_quit("unrecognized option: %c", c);
        }
    }   
    if (optind != argc - 1)
        err_quit("usage: ping [ -v ] <hostname>");
    host = argv[optind];
    pid = getpid() & 0xffff;
    Signal(SIGALRM, sig_alrm);
    ai = Host_serv(host, NULL, 0, 0); // 处理主机名参数
    h = Sock_ntop_host(ai->ai_addr, ai->ai_addrlen);
    printf("PING %s (%s): %d data bytes\n",
           ai->ai_canonname ? ai->ai_canonname : h, h, datalen);
    /* initialize according to protocol */
    if (ai->ai_family == AF_INET) {
        pr = &proto_v4;
#ifdef IPV6
    } else if (ai->ai_family == AF_INET6) {
        pr = &proto_v6;
        if (IN6_IS_ADDR_V4MAPPED(&(((struct sockaddr_in6 *)
                                 ai->ai_addr)->sin6_addr)))
            err_quit("cannot ping IPv4-mapped IPv6 address");
#endif
    } else
        err_quit("unknown address family %d", ai->ai_family);
    pr->sasend = ai->ai_addr;
    pr->sarecv = Calloc(1, ai->ai_addrlen);
    pr->aslen  = ai->ai_addrlen;
    readloop();
    exit(0);
}
```

*ping/main.c*

```c++
#include "ping.h"
void 
readloop(void)
{
    int size;
    char recvbuf[BUFSIZE];
    char controlbuf[BUFSIZE];
    struct msghdr msg;
    struct iovec iov;
    ssize_t n;
    struct timeval tval;
    sockfd = Socket(pr->sasend->sa_family, SOCK_RAW, pr->icmpproto);
    setuid(getuid());
    if (pr->finit)
        (*pr->finit)(); // 执行特定协议的初始化
    size = 60 * 1024;
    setsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, &size, sizeof(size)); // 设置接收缓冲区大小
    sig_alrm(SIGALRM); // 发送第一个分组
    iov.iov_base = recvbuf;
    iov.iov_len = sizeof(recvbuf);
    msg.msg_name = pr->sarecv;
    msg.msg_iov = &iov;
    msg.msg_iovlen = 1;
    msg.msg_contrl = controlbuf;
    for (;;) {
        msg.msg_namelen = pr->salen;
        msg.msg_controllen = sizeof(controlbuf);
        n = recvmsg(sockfd, &msg, 0);
        if (n < 0) {
            if (errno == EINTR)
                continue;
            else
                err_sys("recvmsg error");
        }
        Gettimeofday(&tval, NULL); // 记录分组收取时刻
        (*ptr->fproc)(recvbuf, n, &msg, &tval);
    }
}
```

*ping/readloop.c*

```c++
#include "unp.h"
void 
tv_sub(struct timeval *out, struct timeval *in)
{
    if ((out->tv_usec -= in->tv_usec) < 0) {
        --out->tv_sec;
        out->tv_usec += 1000000;
    }
    out->tv_sec -= in->tv_sec;
}
```

*lib/tv_sub.c*

```c++
#include "ping.h"
void 
proc_v4(char *ptr, ssize_t len, struct msghdr *msg, struct timeval *tvrecv)
{
    int             hlen1, icmplen;
    double          rtt;
    struct ip      *ip;
    struct icmp    *icmp;
    struct timeval *tvsend;
    ip = (struct ip *)ptr;
    hlen1 = ip->ip_hl << 2;
    if (ip->ip_p != IPPROTO_ICMP)
        return;
    icmp = (struct icmp *)(ptr + hlen1);
    if ((icmplen = len - hlen1) < 8)
        return;
    if (icmp->icmp_type == ICMP_ECHOREPLY) {
        if (icmp->icmp_id != pid)
            return;
        if (icmplen < 16)
            return;
        tvsend = (struct timeval *)icmp->icmp_data;
        tv_sub(tvrecv, tvsend);
        rtt = tvrecv->tv_sec * 1000.0 + tvrecv->tv_usec / 1000.0;
        printf("%d bytes from %s: seq=%u, ttl=%d, rtt=%.3f ms\n",
               icmplen, Sock_ntop_host(pr->sarecv, pr->salen),
               icmp->ivmp_seq, ip->ip_ttl, rtt);
    } else if(verbose) {
        printf("%d bytes from %s: type = %d, code = %d\n",
               icmplen, Sock_ntop_host(pr->sarecv, pr->salen),
               icmp->icmp_type, icmp->icmp_code);
    }
}
```

*ping/proc_v4.c*

```c++
void 
init_v6()
{
#ifdef IPV6
    int on = 1;
    if (verbose == 0) {
        /* install a filter that only passes ICMP6_ECHO_REPLY unless verbose */
        struct icmp6_filter myfilt;
        ICMP6_FILTER_SETBLOCKALL(&myfilt);
        ICMP6_FILTER_SETPASS(ICMP6_ECHO_REPLY, &myfilt);
        setsockopt(sockfd, IPPROTO_IPV6, ICMP6_FILTER, &myfilt, 
                   sizeof(myfilt)); // 获取ICMPv6首部的指针
        /* ignore error return; the filter is an optimization */
    }
    /* ignore error returned below; we just won't receive the hop limit */
#ifdef IPV6_RECVHOPLIMIT
    /* RFC 3542 */
    setsockopt(sockfd, IPPROTO_IPV6, IPV6_RECVHOPLIMIT, &on, sizeof(on));
#else
    /* RFC 2292 */
    setsockopt(sockfd, IPPROTO_IPV6, IPV6_HOPLIMIT, &on, sizeof(on));
#endif
#endif
}
```

*ping/init_v6.c*

```c++
#include "ping.h"
void 
proc_v6(char *ptr, ssize_t len, struct msghdr *msg, struct timeval* tvrecv)
{
#ifdef IPV6
    double rtt;
    struct icmp6_hdr *icmp6;
    struct timeval *tvsend;
    struct cmsghdr *cmsg;
    int hlim;
    icmp6 = (struct icmp6_hdr *)ptr;
    if (len < 8)
        return;
    if (icmp6->icmp6_type == ICMP6_ECHO_REPLY) {
        if (icmp6->icmp6_id != pid)
            return;
        if (len < 16)
            return;
        tvsend = (struct timeval *)(icmp6 + 1);
        tv_sub(tvrecv, tvsend);
        rtt = tvrecv->tv_sec * 1000.0 + tvrecv->tv_usec / 1000.0;
        hlim = -1;
        for (cmsg = CMSG_FIRSTHDR(msg); cmsg != NULL;
             cmsg = CMSG_NXTHDR(msg, cmsg)) {
            if (cmsg->cmsg_level == IPV6_HOPLIMIT) {
                hlim = *(u_int32_t *)CMSG_DATA(cmsg);
                break;
            }
        }
        printf("%d bytes from %s: seq=%u, hlim=",
               len, Sock_ntop_host(pr->sarecv, pr->salen), icmp6->icmp6_seq);
        if (hlim == -1)
            printf("???");
        else
            printf("%d", hlim);
        printf(", rtt=%.3f ms\n", rtt);
    } else if(verbose) {
        printf("%d bytes from %s: type = %d, code = %d\n",
               len, Sock_ntop_host(pr->sarecv, pr->salen),
               icmp6->icmp6_type, icmp6->icmp6_code);
    }
#endif
}
```

*ping/proc_v6.c*

```c++
#include "ping.h"
void 
sig_alrm(int signo)
{
    (*pr->fsend)();
    alarm(1);
    return;
}
```

*ping/sig_alrm.c*

```c++
#include "ping.h"
void 
send_v4(void)
{
    int len;
    struct icmp *icmp;
    icmp = (struct icmp *)sendbuf; // 构造ICMPv4消息
    icmp->icmp_type = ICMP_ECHO;
    icmp->icmp_code = 0;
    icmp->icmp_id = pid; // 设置标识符字段
    icmp->icmp_seq = nsent++;
    memset(icmp->icmp_data, 0xa5, datalen);
    Gettimeofday((struct timeval *)icmp->icmp_data, NULL);
    len = 8 + datalen;
    icmp->icmp_cksum = 0;
    icmp->icmp_cksum = in_cksum((u_short *)icmp, len); // 计算校验和
    Sendto(sockfd, sendbuf, len, 0, pr->sasend, pr->salen); // 发送数据报
}
```

*ping/send_v4.c*

```c++
uint16_t 
in_cksum(uint16_t *addr, int len)
{
    int nleft = len;
    uint32_t sum = 0;
    uint16_t *w = addr;
    int16_t answer = 0;
    /*
     * Our algorithm is simple, using a 32 bit accumulator (sum), we add
     * sequential 16 bit words to it, and at the end, fold back all the 
     * carry bits from the top 16 bits into the lower 16 bits.
     */
    while (nleft > 1) {
        sum += *w++;
        nleft -= 2;
    }
    /* mop up an odd byte, if necessary */
    if (nleft == 1) {
        *(unsigned char *)(&answer) = *(unsigned char *)w;
        sum += answer;
    }
    /* add back carry outs from top 16 bits to low 16 bits */
    sum = (sum >> 16) + (sum & 0xffff);
    sum += (sum >> 16);
    answer = ~sum;
    return (answer);
}
```

*libfree/in_cksum.c*

```c++
#include "ping.h"
void 
send_v6()
{
#ifdef IPV^
    int len;
    struct icmp6_hdr *icmp6;
    icmp6 = (struct icmp6_hdr *)sendbuf;
    icmp6->icmp6_type = ICMP6_ECHO_REQUEST;
    icmp6->icmp6_code = 0;
    icmp6->icmp6_id = pid;
    icmp6->icmp6_seq = nsent++;
    memset((icmp6 + 1), 0xa5, datalen);
    Gettimeofday((struct timeval *)(icmp6 + 1), NULL);
    len = 8 + datalen;
    Sendto(sockfd, sendbuf, len, 0, pr->sasend, pr->salen);
    /* kernel calculates and stores checksum for us */
#endif
}
```

*ping/send_v6.c*

![28_9](res/28_9.png)

*处理ICMPv4应答涉及的首部，指针和长度*



## 28.6 traceroute程序

![28_21](res/28_21.png)

*处理ICMPv4错误涉及的首部，指针和长度*

![28_22](res/28_22.png)

*处理ICMPv6错误涉及的首部，指针和长度*

```c++
#include "unp.h"
#include <netinet/in_systm.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <netinet/udp.h>
#define BUFSIZE 1500
struct rec {
    u_short rec_seq;
    u_short rec_ttl;
    struct timeval rec_tv;
};
/* globals */
char recvbuf[BUFSIZE];
char sendbuf[BUFSIZE];
int datalen;
char *host;
u_short sport, dport;
int nsent;
pid_t pid;
int probe, nprobes;
int sendfd, recvfd;
int ttl, max_ttl;
int verbose;
/* function prototypes */
const char *icmpcode_v4(int);
const char *icmpcode_v6(int);
int recv_v4(int, struct timeval *);
int recv_v6(int, struct timeval *);
void sig_alrm(int);
void traceloop(void);
void tv_sub(struct timeval *, struct timeval *);
struct proto {
    const char *(*icmpcode)(int);
    int (*recv)(int, struct timeval *);
    struct sockaddr *sasend;
    struct sockaddr *sarecv;
    struct sockaddr *salast;
    struct sockaddr *sabind;
    socklen_t salen;
    int icmpproto;
    int ttllevel;
    int ttloptname;
} *pr;
#ifdef IPV6 // 包含IPv6头文件
#include <netinet/ip6.h>
#include <netinet/icmp6.h>
#endif
```

*traceroute/trace.h*

```c++
#include "trace.h"
struct protoproto_v4 = {icmpcode_v4, recv_v4, NULL, NULL, NULL, NULL, 0, 
                        IPPROTO_ICMP, IPPROTO_IP, IP_TTL
                       };
#ifdef IPV6
struct protoproto_v6 = {icmpcode_v6, recv_v6, NULL, NULL, NULL, NULL, 0, 
                        IPPROTO_ICMPV6, IPPROTO_IPV6, IPV6_UNICAST_HOPS
                       };
#endif
int datalen = sizeof(struct rec);
int max_ttl = 30;
int nprobes = 3;
u_short dport = 32768 + 666;
int 
main(int argc, char **argv)
{
    int c;
    struct addrinfo *ai;
    char *h;
    opterr = 0;
    while ((c = getopt(argc, argv, "m:v")) != -1) {
        switch(c) {
            case 'm':
                if ((max_ttl = atoi(optarg)) <= 1)
                    err_quit("invalid -m value");
                break;
            case 'v':
                verbose++;
                break;
            case '?':
                err_quit("unrecognized option: %c", c);
        }
    }
    if (optid != argc - 1)
        err_quit("usage: traceroute [ -m <maxttl> -v ] <hsotname>");
    host = argv[optind];
    pid = getpid();
    Signal(SIGALRM, sig_alrm);
    ai = Host_serv(host, NULL, 0, 0); // 处理目的主机名/ip地址
    h = Sock_ntop_host(ai->ai_addr, ai->ai_addrlen);
    printf("traceroute to %s (%s): %d hops max, %d data bytes\n",
           ai->ai_canonname ? ai->ai_canonname : h, h, max_ttl, datalen);
    /* initialize according to protocol */
    if (ai->ai_family == AF_INET) {
        pr = &proto_v4;
#ifdef IPV6
    } else if(ai->ai_family == AF_INET6) {
        pr = &proto_v6;
        if (IN6_IS_ADDR_V4MAPPED
            (&(((struct sockaddr_in6 *)ai->ai_addr)->sin6_addr)))
            err_quit("cannot traceroute IPv4-mapped IPv6 address");
#endif
    } else
        errquit("unknown address family %d", ai->ai_family);
    pr->sasend = ai->ai_addr;
    pr->sarecv = Calloc(1, ai->ai_addrlen);
    pr->salast = Calloc(1, ai->ai_addrlen);
    pr->sabind = Calloc(1, ai->ai_addrlen);
    pr->salen = ai->ai_addrlen;
    traceloop();
    exit(0);
}
```

*traceroute/main.c*

```c++
#include "trace.h"
void 
traceloop(void)
{
    int seq, code, done;
    double rtt;
    struct rec *rec;
    struct timeval tvrecv;
    recvfd = Socket(pr->sasend->sa_family, SOCK_RAW, pr->icmpproto);
    setuid(getuid()); // 设置有效用户ID未实际用户ID
#ifdef IPV6
    if (pr->sasend->sa_family == AF_INET6 && verbose == 0) {
        struct icmp6_filter myfilt; // ICMPv6接收过滤器
        ICMP6_FILTER_SETBLOCKALL(&myfilt);
        ICMP6_FILTER_SETPASS(ICMP6_TIME_EXCEEDED, &myfilt);
        ICMP6_FILTER_SETPASS(ICMP6_DST_UNREACH, &myfilt);
        setsockopt(recvfd, IPPROTO_IPV6, ICMP6_FILTER,
                   &myfilt, sizeof(myfilt));
    }
#endif
    sendfd = Socket(pr->sasend->sa_family, SOCK_DGRAM, 0);
    pr->sabind->sa_family = pr->sasend->sa_family;
    sport = (getpid() & 0xffff) | 0x8000;
    sock_set_port(pr->sabind, pr->salen, htons(sport)); // 绑定端口
    Bind(sendfd, pr->sabind, pr->salen);
    sig_alrm(SIGALRM); // 建立信号处理函数
    seq = 0;
    done = 0;
    for (ttl = 1; ttl <= max_ttl && done == 0; ttl++) { // 设置TTL或跳限并发3个探测分组
        Setsockopt(sendfd, pr->ttllevel, pr->ttloptname, &ttl, sizeof(int));
        bzero(pr->salast, pr->salen);
        printf("%2d ", ttl);
        fflush(stdout);
        for (probe = 0; probe < nprobes; probe++) {
            rec = (struct rec*)sendbuf;
            rec->rec_seq = ++seq;
            rec->rec_ttl = ttl;
            Gettimeofday(&rec->rec_tv, NULL);
            sock_set_port(pr->sasend, pr->salen, htons(dport + seq)); // 设置目的端口
            Sendto(sendfd, sendbuf, datalen, 0, pr->sasend, pr->salen); // 发送UDP数据报
            if ((code = (*pr->recv)(seq, &tvrecv)) == -3) // 读入ICMP消息
                printf(" *");
            else {
                char str[NI_MAXHOST];
                if (sock_cmp_addr(pr->sarecv, pr->salast, pr->salen) != 0) {
                    if (getnameinfo(pr->sarecv, pr->salen, str, sizeof(str),
                                    NULL, 0, 0) == 0)
                        printf(" %s (%s)", str,
                               Sock_ntop_host(pr->sarecv, pr->salen));
                    else
                        printf(" %s", Sock_ntop_host(pr->sarecv, pr->salen));
                    memcpy(pr->salast, pr->sarecv, pr->salen);
                }
                tv_sub(&tvrecv, &rec->rec_tv);
                rtt = tvrecv.tv_sec * 1000.0 + tvrecv.tv_usec / 1000.0;
                printf(" %.3f ms", rtt);
                if (code == -1)
                    done++;
                else if (code >= 0)
                    printf(" (ICMP %s)", (*pr->icmpcode)(code));
            }
            fflush(stdout);
        }
        printf("\n");
    }
}
```

*traceroute/traceloop.c*

```c++
#include "trace.h"
extern int gotalarm;
/*
 * Return: -3 on timeout
 *         -2 on ICMP time exceeded in transit (caller keeps going)
 *         -1 on ICMP port unreachable (caller is done)
 *        >=0 return value is some other ICMP unreachable code
 */
int 
recv_v4(int seq, struct timeval *tv)
{
    int hlen1, hlen2, icmplen, ret;
    socklen_t len;
    ssize_t n;
    struct ip *ip, *hip;
    struct icmp *icmp;
    struct udphdr *udp;
    gotalarm = 0;
    alarm(3); // 设置一个3秒的报警时钟
    for (;;) {
        if (gotalarm)
            return(-3);
        len = pr->salen;
        n = recvfrom(recvfd, recvbuf, sizeof(recvbuf), 0, pr->sarecv, &len);
        if (n < 0) {
            if (errno == EINTR)
                continue;
            else
                err_sys("recvfrom error");
        }
        ip = (struct ip *)recvbuf;
        hlen1 = ip->ip_h1 << 2;
        icmp = (struct icmp *)(recvbuf + hlen1); // 获取ICMP首部指针
        if ((icmplen = n - hlen1) < 8)
            continue;
        if (icmp->icmp_type == ICMP_TIMXCEED &&
            icmp->icmp_code == ICMP_TIMXCEED_INTRANS) { // ICMP传输中超时错误
            if (icmplen < 8 + sizeof(struct ip))
                continue;
            hip = (struct ip *)(recvbuf + hlen1 + 8);
            hlen2 = hip->ip_hl << 2;
            if (icmplen < 8 + hlen2 + 4)
                continue;
            udp = (struct udphdr *)(recvbuf + hlen1 + 8 + hlen2);
            if (hip->ip_p == IPPROTO_UDP &&
                udp->uh_sport == htons(sport) &&
                udp->uh_dport = htons(dport + seq)) {
                ret = -2;
                break;
            }
        } else if (icmp->icmp_type == ICMP_UNREACH) { // ICMP端口不可达
            if (icmplen < 8 + sizeof(struct ip))
                continue;
            hip = (struct ip *)(recvbuf + hlen1 + 8);
            hlen2 = hip->ip_h1 << 2;
            if (icmplen < 8 + hlen2 + 4)
                continue;
            udp = (struct udphdr *)(recvbuf + hlen1 + 8 + hlen2);
            if (hip->ip_p == IPPROTO_UDP &&
                udp->uh_sport == htons(sport) &&
                udp->uh_dport == htons(dport + seq)) {
                if (icmp->icmp_code == ICMP_UNREACH_PORT)
                    ret = -1;
                else
                    ret = icmp->icmp_code;
                break
            }
        }
        if (verbose) {
            printf(" (from %s: type = %d, code = %d)\n",
                   Sock_ntop_host(pr->sarecv, pr->salen),
                   icmp->icmp_type, icmp->icmp_code);
        }
        /* Some other ICMP error, recvfrom() again */
    }
    alarm(0);
    Gettimeofday(tv, NULL);
    return(ret);
}
```

*traceroute/recv_v4.c*

```c++
#include "trace.h"
int gotalarm;
void 
sig_alrm(int signo)
{
    gotalarm = 1;
    return;
}
```

*traceroute/sig_alrm.c*

```c++
#include "trace.h"
extern int gotalarm;
/*
 * Return: -3 on timeout
 *         -2 on ICMP time exceeded in transit (caller keeps going)
 *         -1 on ICMP port unreachable (caller is done)
 *        >=0 return value is some other ICMP unreachable code
 */
int 
recv_v6(int seq, struct timeval *tv)
{
#ifdef IPV6
    int hlen2, icmp5len, ret;
    ssize_t n;
    socklen_t len;
    struct ip6_hdr *hip6;
    struct icmp6_hdr *icmp6;
    struct udphdr *udp;
    gotalarm = 0;
    alarm(3);
    for (;;) {
        if (gotalarm)
            return(-3);
        len = pr->salen;
        n = recvfrom(recvfd, recvbuf, sizeof(recvbuf), 0, pr->sarecv, &len);
        if (n < 0) {
            if (errno == EINTR)
                continue;
            else
                err_sys("recvfrom error");
        }
        icmp6 = (struct icmp6_hdr *)recvbuf;
        if ((icmp6len = n) < 8)
            continue;
        if (icmp6->icmp6_type == ICMP6_TIME_EXCEEDED &&
            icmp6->icmp6_code == ICMP6_TIME_EXCEED_TRANSIT) {
            if (icmp6len < 8 + sizeof(struct ip6_hdr) + 4)
                continue;
            hip6 = (struct ip6_hdr *)(recvbuf + 8);
            hlen2 = sizeof(struct ip6_hdr);
            udp = (struct udphdr *)(recvbuf = 8 + hlen2);
            if (hip6->ip_nxt == IPPROTO_UDP &&
                udp->uh_sport == htons(sport) &&
                udp->uh_dport == htons(dport + seq))
                ret = -2;
            	break;
        } else if (icmp6->icmp6_type == ICMP6_DST_UNREACH) {
            if (icmp6len < 8 + sizeof(struct ip6_hdr) + 4)
                continue;
            hip6 = (struct ip6_hdr *)(recvbuf + 8);
            hlen2 = sizeof(struct ip6_hdr);
            udp = (struct udphdr *)(recvbuf + 8 + hlen2);
            if (hip6->ip6_nxt == IPPROTO_UDP &&
                udp->uh_sport == htons(sport) &&
                udp->uh_dport == htons(dport + seq)) {
                if (icmp6->icmp6_code == ICMP6_DST_UNREACH_NOPORT)
                    ret = -1;
                else
                    ret = icmp6->icmp6_code;
                break;
            }
        } else if (verbose) {
            printf(" (from %s: type = %d, code = %d)\n",
                   Sock_ntop_host(pr->sarecv, pr->salen),
                   icmp6->icmp6_type, icmp6->icmp6_code);
        }
        /* Some other ICMP error, recvfrom() again */
    }
    alarm(0);
    Gettimeofday(tv, NULL);
    return(ret);
#endif
}
```

*traceroute/recv_v6.c*

```c++
#include "trace.h"
const char * 
icmpcode_v6(int code)
{
#ifdef IPV6
    static char errbuf[100];
    switch (code) {
        case ICMP6_DST_UNREACH_NOROUTE:
            return("no route to host");
        case ICMP6_DST_UNREACH_ADMIN:
            return("administratively prohibited");
        case ICMP6_DST_UNREACH_NOTNEIGHBOR:
            return("not a neighbor");
        case ICMP6_DST_UNREACH_ADDR:
            return("address unreachable");
        case ICMP6_DST_UNREACH_NOPORT:
            return("port unreachable");
        default:
            sprintf(errbuf, "[unknown code %d]", code);
            return errbuf;
    }
#endif
}
```

*traceroute/icmpcode_v6.c*



## 28.7 一个ICMP消息守护程序

![28_26](res/28_26.png)

*icmpd守护进程：初始创建的套接字*

![28_27](res/28_27.png)

*应用进程创建自身的UDP套接字和到icmp的Unix域连接*

![28_28](res/28_28.png)

*应用进程跨Unix域连接把UDP套接字传递给icmpd*

![28_30](res/28_30.png)

*从ICMPv4和ICMPv6错误映射到icmpd_errno*

```c++
#ifndef __unpicmp_h
#define __unpicmp_h
#include "unp.h"
#define ICMPD_PATH
struct icmpd_err {
    int                     icmpd_errno; // ICMP错误
    char                    icmpd_type;
    char                    icmpd_code;
    socklen_t               icmpd_len;
    struct sockaddr_storage icmpd_dest;  // 对方套接字地址
};
#endif
```

*icmpd/unpicmpd.h*

### 28.7.1 使用icmpd的UDP回射客户程序

```c++
#include "unpicmpd.h"
void 
dg_cli(FILE *fp, int sockfd, const SA *pservaddr, socklen_t servlen)
{
    int icmpfd, maxfdp1;
    char sendline[MAXLINE], recvline[MAXLINE + 1];
    fd_set rset;
    ssize_t n;
    struct timeval tv;
    struct icmpd_err icmpd_err;
    struct sockaddr_un sun;
    Sock_bind_wild(sockfd, pservaddr->sa_family); // 绑定ip和临时端口到UDP套接字
    icmpfd = Socket(AF_LOCAL, SOCK_STREAM, 0);
    sun.sun_family = AF_LOCAL;
    strcpy(sun.sun_path, ICMPD_PATH);
    Connect(icmpfd, (SA *)&sun, sizeof(sun));
    Write_fd(icmpfd, "1", 1, sockfd); // 发送UDP套接字到icmpd
    n = Read(icmpfd, recvline, 1); // 等待icmpd的应答
    if (n != 1 || recvline[0] != '1')
        err_quit("error creating icmp socket, n = %d, char = %c", 
                 n, recvline[0]);
    FD_ZERO(&rset);
    maxfdp1 = max(sockfd, icmpfd) + 1;
    while (Fgets(sendline, MAXLINE, fp) != NULL) {
        Sendto(sockfd, sendline, strlen(sendline), 0, pservaddr, servlen);
        tv.tv_sec = 5; // 超时5秒
        tv.tv_usec = 0;
        FD_SET(sockfd, &rset);
        FD_SET(icmpfd, &rset);
        if ((n = Select(maxfdp1, &rset, NULL, NULL, &tv)) == 0) {
            fprintf(stderr, "socket timeout\n");
            continue;
        }
        if (FD_ISSET(sockfd, &rset)) { // 服务器返回数据报
            n = Recvfrom(sockfd, recvline, MAXLINE, 0, NULL, NULL);
            recvline[n] = 0;
            Fputs(recvline, stdout);
        }
        if (FD_ISSET(icmpfd, &rset)) { // 处理ICMP错误
            if ((n = Read(icmpfd, &icmpd_err, sizeof(icmpd_err))) == 0)
                err_quit("ICMP daemon terminated");
            else if (n != sizeof(icmpd_err))
                err_quit("n = %d, expected %d", n, sizeof(icmpd_err));
            printf("ICMP error: dest = %s, %s, type = %d, code = %d\n",
                   Sock_ntop(&icmpd_err.icmpd_dest, icmpd_err.icmpd_len),
                   strerror(icmpd_err.icmpd_errno),
                   icmpd_err.icmpd_type, icmpd_err.icmpd_code);
        }
    }
}
```

*icmpd/dgcli01.c*

### 28.7.2 UDP回射客户程序运行例子

### 28.7.3 icmpd守护进程

```c++
#include "unpicmpd.h"
struct client {
    int connfd;
    int family;
    int lport;
    /* network byte ordered */
} client[FD_SETSIZE];
/* globals */
int fd4, fd6, listenfd, maxi, maxfd, nready;
fd_set rset, allset;
struct sockaddr_un cliaddr;
/* function prototypes */
int readable_conn(int);
int readable_listen(void);
int readable_v4(void);
int readable_v6(void);
```

*icmpd/icmpd.h*

```c++
#include "icmpd.h"
int 
main(int argc, char **argv)
{
    int i, sockfd;
    struct sockaddr_un sun;
    if (argc != 1) 
        err_quit("usage: icmpd");
    maxi = -1;
    for (i = 0; i < FD_SETSIZE; i++)
        client[i].connfd = -1;
    FD_ZERO(&allset);
    fd4 = Socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    FD_SET(fd4, &allset);
    maxfd = fd4;
#ifdef IPV6
    fd6 = Socket(AF_INET6, SOCK_RAW, IPPROTO_ICMPV6);
    FD_SET(fd6, &allset);
    maxfd = max(maxfd, fd6);
#endif
    listenfd = Socket(AF_UNIX, SOCK_STREAM, 0);
    sun.sun_family = AF_LOCAL;
    strcpy(sun.sun_path, ICMPD_PATH);
    unlink(ICMPD_PATH);
    Bind(listenfd, (SA *)&sun, sizeof(sun));
    Listen(listenfd, LISTENQ);
    FD_SET(listenfd, &allset);
    maxfd = max(maxfd, listenfd);
    for (;;) {
        rset = allset;
        nready = Select(maxfd+1, &rset, NULL, NULL, NULL);
        if (FD_ISSET(listenfd, &rset))
            if (readable_listen() <= 0)
                continue;
        if (FD_ISSET(fd4, &rset))
            if (readable_v4() <= 0)
                continue;
#ifdef IPV6
        if (FD_ISSET(fd6, &rset))
            if (readable_v6() <= 0)
                continue;
#endif
        for (i = 0; i <= maxi; i++) { // 检查已连接Unix域套接字
            if ((sockfd = client[i].connfd) < 0)
                continue;
            if (FD_ISSET(sockfd, &rset))
                if (readable_conn(i) <= 0)
                    break;
        }
    }
    exit(0);
}
```

*icmpd/icmpd.c*

```c++
#include "icmpd.h"
int 
readable_listen(void)
{
    int i, connfd;
    socklen_t clilen;
    clilen = sizeof(cliaddr);
    connfd = Accept(listenfd, (SA *)&cliaddr, &clilen);
    /* find first available client[] structure */
    for (i = 0; i < FD_SETSIZE; i++)
        if (client[i].connfd < 0) {
            client[i].connfd = connfd;
            break;
        }
    if (i == FD_SETSIZE) {
        close(connfd);
        return(--nready);
    }
    printf("new connection, i = %d, connfd = %d\n", i, connfd);
    FD_SET(connfd, &allset);
    if (connfd > maxfd)
        maxfd = connfd;
    if (i > maxi)
        maxi = i;
    return(--nready);
}
```

*icmpd/readable_listen.c*

```c++
#include "icmpd.h"
int 
readable_conn(int i)
{
    int unixfd, recvfd;
    char c;
    ssize_t n;
    socklen_t len;
    struct sockaddr_storage ss;
    unixfd = client[i].connfd;
    recvfd = -1;
    if ((n = Read_fd(unixfd, &c, 1, &recvfd)) == 0) {
        err_msg("client %d terminated, recvfd = %d", i, recvfd);
        goto clientdone;
    }
    /* data from client; should be descriptor */
    if (recvfd < 0) {
        err_msg("read_fd did not return descriptor");
        goto clienterr;
    }
    len = sizeof(ss);
    if (getsockname(recvfd, (SA *)&ss, &len) < 0) { // 获取客户捆绑在UDP套接字上的端口号
        err_ret("getsockname error");
        goto clienterr;
    }
    client[i].family = ss.ss_family;
    if ((client[i].lport = sock_get_port((SA *)&ss, len)) == 0) {
        client[i].lport = sock_bind_wild(recvfd, client[i].family);
        if (client[i].lport <= 0) {
            err_ret("error binding ephemeral port");
            goto clientterr;
        }
    }
    Write(unixfd, "1", 1); // 发送"1"到客户
    Close(recvfd); // 关闭UDP套接字
    return(--nready);
clienterr:  // 客户端错误
    Write(unixfd, "0", 1);
clientdone: // 客户端终止
    Close(unixfd);
    if (recvfd >= 0)
        Close(recvfd);
    FD_CLR(unixfd, &allset);
    client[i].connfd = -1;
    return(--nready);
}
```

*icmpd/readable_conn.c*

```c++
#include "icmpd.h"
#include <netinet/in_systm.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <netinet/udp.h>
int 
readable_v4(void)
{
    int i, hlen1, hlken2, icmplen, sport;
    char buf[MAXLINE];
    char srcstr[INET_ADDRSTRLEN], dststr[INET_ADDRSTRLEN];
    ssize_t n;
    socklen_t len;
    struct ip *ip, *hip;
    struct icmp *icmp;
    struct udphdr *udp;
    struct sockaddr_in from, dest;
    struct icmpd_err icmpd_err;
    len = sizeof(from);
    n = Recvfrom(fd4, buf, MAXLINE, 0, (SA *)&from, &len);
    printf("%d bytes ICMPv4 from %s:", n, Sock_ntop_host((SA *)&from, len));
    ip = (struct ip *)buf;
    hlen1 = ip->ip_hl <, 2;
    icmp = (struct icmp *)(buf + hlen1);
    if ((icmplen = n - hlen1) < 8)
        err_quit("icmplen (%d) < 8", icmplen);
    printf(" type = %d, code = %\n", icmp->icmp_type, icmp->icmp_code);
    if (icmp->icmp_type == ICMP_UNREACH ||
        icmp->icmp_type == ICMP_TIMXCEED ||
        icmp->icmp_type == ICMP_SOURCEQUENCH) { // 检查需通知应用进程的消息类型
        if (icmplen < 8 + 20 + 8)
            err_quit("icmplen (%d) < 8 + 20 + 8", icmplen);
        hip = (struct ip *)(buf + hlen1 + 8);
        hlen2 = hip->ip_h1 << 2;
        printf("\tsrcip = %s, dstip = %s, proto = %d\n",
               Inet_ntop(AF_INET, &hip->ip_src, srcstr, sizeof(srcstr)),
               Inet_ntop(AF_INET, &hip->ip_dst, dststr, sizeof(dststr)),
               hip->ip_p);
        if (hip->ip_p == IPPROTO_UDP) {
            udp = (struct udphdr *)(buf + hlen1 = 8 + hlen2);
            sport = udp->uh_sport;
            /* find client's Unix domain socket, send headers */
            for (i = 0; i <= maxi; i++) {
                if (client[i].connfd >= 0 &&
                    client[i].family == AF_INET &&
                    client[i].lport == sport) {
                    bzero(&dest, sizeof(dest));
                    dest.sin_family = AF_INET;
#ifdef HAVE_SOCKADDR_SA_LEN
      			   dest.sin_len = sizeof(dest);              
#endif
                    memcpy(&dest.sin_addr, &hip->ip_dst,
                           sizeof(struct in_addr));
                    dest.sin_port = udp->uh_dport;
                    icmpd_err.icmpd_type =- icmp->icmp_type;
                    icmpd_err.icmpd_code = icmp->icmp_code;
                    icmpd_err.icmpd_len = sizeof(struct sockaddr_in);
                    memcpy(&icmpd_err.icmpd_dest, &dest, sizeof(dest));
                    /* convert type & code to reasonable errno value */
                    icmpd_err.icmpd_errno = EHOSTUNREACH;
                    if (icmp->icmp_type == ICMP_UNREACH) {
                        if (icmp->icmp_code == ICMP_UNREACH_PORT)
                            icmp_err.icmpd_errno = ECONNREFUSED;
                        else if (icmp->icmp_code == ICMP_UNREACH_NEEDFRAG)
                            icmpd_err.icmpd_errno = EMSGSIZE;
                    }
                    Write(client[i].connfd, &icmpd_err, sizeof(icmpd_err));
                }
            }
        }
    }
    return(--nready);
}
```

*icmpd/readable_v4.c*

```c++
#include "icmpd.h"
#include <netinet/in_systm.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <netinet/udp.h>
#ifdef IPV6
#include <netinet/ip6.h>
#include <netinet/icmp6.h>
#endif
int 
readable_v6(void)
{
#ifdef IPV6
    int i, hlen2, icmp6len, sport;
    char buf[MAXLINE];
    char srcstr[INET_ADDRSTRLEN], dststr[INET_ADDRSTRLEN];
    ssize_t n;
    socklen_t len;
    struct ip6_hdr *ip6, *hip6;
    struct icmp6_hdr *icmp6;
    struct udphdr *udp;
    struct sockaddr_in6 from, dest;
    struct icmpd_err icmpd_err;
    len = sizeof(from);
    n = Recvfrom(fd6, buf, MAXLINE, 0, (SA *)&from, &len);
    printf("%d bytes ICMPv6 from %s:", n, Sock_ntop_host((SA *)&from, len));
    icmp6 = (struct icmp6_hdr *)buf;
    if ((icmp6len = n) < 8)
        err_quit("icmp6len (%d) < 8", icmp6len);
    printf(" type = %d, code = %d\n", icmp6->icmp6_type, icmp6->icmp6_code);
    if (icmp6->icmp6_type == ICMP6_DST_UNREACH ||
        icmp6->icmp6_type == ICMP6_PACKET_TOO_BIG ||
        icmp6->icmp6_type == ICMP6_TIME_EXCEEDED) { // 检查需通知应用进程的消息类型
        if (icmp6len < 8 + 8)
            err_quit("icmp6len (%d) < 8 + 8", icmp6len);
        hip6 = (struct ip6_hdr *)(buf + 8);
        hlen2 = sizeof(struct ip6_hdr);
        printf("\tsrcip = %s, dstip = %s, next hdr = %d\n",
               Inet_ntop(AF_INET6, &hip6->ip6_src, srcstr, sizeof(srcstr)),
               Inet_ntop(AF_INET6, &hip6->ip6_dst, dststr, sizeof(dststr)),
               hip6->ip6_nxt);
        if (hip6->ip6_nxt == IPPROTO_UDP) {
            udp = (struct udphdr *)(buf + 8 + hlen2);
            sport = udp->uh_sport;
            /* find client's Unix domain socket, send headers */
            for (i = 0; i <= maxi; i++) {
                if (client[i].connfd >= 0 &&
                    client[i].family == AF_INET &&
                    client[i].lport == sport) {
                    bzero(&dest, sizeof(dest));
                    dest.sin6_family = AF_INET6;
#ifdef HAVE_SOCKADDR_SA_LEN
      			   dest.sin6_len = sizeof(dest);              
#endif
                    memcpy(&dest.sin6_addr, &hip6->ip6_dst,
                           sizeof(struct in_addr));
                    dest.sin6_port = udp->uh_dport;
                    icmpd_err.icmpd_type =- icmp6->icmp6_type;
                    icmpd_err.icmpd_code = icmp6->icmp6_code;
                    icmpd_err.icmpd_len = sizeof(struct sockaddr_in6);
                    memcpy(&icmpd_err.icmpd_dest, &dest, sizeof(dest));
                    /* convert type & code to reasonable errno value */
                    icmpd_err.icmpd_errno = EHOSTUNREACH;
                    if (icmp6->icmp_type == ICMP6_DST_UNREACH &&
                        icmp6->icmp_code == ICMP6_DST_UNREACH_NOPORT)
                        icmp_err.icmpd_errno = ECONNREFUSED;
                    if (icmp6->icmp6_type == ICMP6_PACKET_TOO_BIG)
                        icmpd_err.icmpd_errno = EMSGSIZE;
                    Write(client[i].connfd, &icmpd_err, sizeof(icmpd_err));
                }
            }
        }
    }
    return(--nready);
#endif
}
```

*icmpd/readable_v6.c*



## 28.8 小结

原始套接字提供以下3个能力：

- 进程可以读写ICMPv4，IGMPv4和ICMPv6等分组。
- 进程可以读写内核不处理其协议字段的IP数据报。
- 进程可以自行构造IPv4首部，通常用于诊断目的。
