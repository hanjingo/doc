# 第二十九章 数据链路访问

[TOC]



## 29.1 概论

数据链路层访问功能：

- 能够监视由数据链路层接收的分组，使得诸如tcpdump之类的程序能够在普通计算机系统上运行，而无需使用专门的硬件设备来监视分组。
- 能够作为普通应用进程而不是内核的一部分运行某些程序。



## 29.2 BPF: BSD分组过滤器

![29_1](res/29_1.png)

*使用BPF截获分组*

BPF使用以下技术来降低开销：

- BPF过滤在内核中进行，以次把从BPF到应用进程的数据复制量减少到最小。
- 由BPF传递到应用进程的只是每个分组的一段定长部分，这个长度称为`捕获长度（capture length）`或`快照长度（snapshot length, snaplen）`。
- BPF为每个应用进程分别缓冲数据，只有当缓冲区已满或读超时（read timeout）期满时缓冲区中的数据才复制到应用进程。



## 29.3 DLPI:数据链路提供者接口

SVR4通过数据链路提供者接口（Datal;ink Provider Interface, DLPI）提供数据链路访问。

![29_2](res/29_2.png)

*使用DLPI，pfmod和bufmod捕获分组*



## 29.4 Linux: SOCK_PACKET和PF_PACKET

Linux的数据链路访问方法相比BPF和DLPI存在如下差别：

- Linux方法不提供内核缓冲，而且只有较新的方法才能提供内核过滤。
- Linux较旧的方法不提供针对设备的过滤。



## 29.5 libpcap: 分组捕获函数库

libpcap是访问操作系统所提供的分组捕获机制的分组捕获函数库，它是与实现无关的。



## 29.6 libnet:分组构造与输出函数库

libnet函数库提供构造任意协议的分组并将其输出到网络中的接口。它以实现无关的方式提供原始套接字访问方式和数据链路访问方式。



## 29.7 检查UDP的校验和字段

![29_3](res/29_3.png)

*检查某个名字服务器是否开启UDP校验和的应用程序*

![29_4](res/29_4.png)

*udpcksum程序中的函数汇总*

![29_17](res/29_17.png)

*从分组捕获函数库读入分组的相关函数调用*

```c++
#include "unp.h"
#include <pcap.h>
#include <netinet/in_system.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/ip_var.h>
#include <netinet/udp.h>
#include <netinet/udp_var.h>
#include <net/if.h>
#include <netinet/if_ether.h>
#define TTL_OUT 64
/* declare global variables */
extern struct sockaddr *dest, *local;
extern socklen_t destlen, locallen;
extern int datalink;
extern char *device;
extern pcap_t *pd;
extern int rawfd;
extern int snaplen;
extern int verbose;
extern int zerosum;
/* function prototypes */
void  cleanup(int);
char *next_pcap(int *);
void  open_output(void);
void  open_pcap(void);
void  send_
void
void
struct udpiphdr *
```

*udpcksum/udpcksum.h*

```c++
#include "udpcksum.h"
/* DefinE global variables */
struct sockaddr *dest, *local;
struct sockaddr_in locallookup;
socklen_t destlen, locallen;
int datalink;
char *device;
pcap_t *pd;
int rawfd;
int snaplen = 200;
int verbose;
int zerosum;
static void usage(const char *);
int 
main(int argc, char *argv[])
{
    int c, lopt = 0;
    char *ptr, localname[1024], *localport;
    struct addrinfo *aip;
    opterr = 0;
    while ((c = getopt(argc, argv, "oi:l:v")) != -1) {
        switch (c) {
            case '0': // 不设置UDP校验和就发送UDP查询
                zerosum = 1;
                break;
            case 'i': // 指定接收服务器的应答接口
                device = optarg;
                break;
            case '1': // 指定源IP和端口
                if ((ptr = strrchr(optarg, '.')) == NULL)
                    usage("invalid - 1 option");
                *ptr++ = 0;
                localport = ptr;
                strncpy(localname, optarg, sizeof(localname));
                lopt = 1;
                break;
            case 'v':
                verbose = 1;
                break;
            case '?':
                usage("unrecognized option");
        }
    }
    if (optind != argc-2)
        usage("missing <host> and/or <serv>");
    /* convert destination anme and service */
    aip = Host_serv(argv[optind], argv[optind+1], AF_INET, SOCK_DGRAM);
    dest = aip->ai_addr;
    destlen = aip->ai_addrlen;
    /*
     * Need local IP address for source IP address for UDP datagrams.
     * Can't specify 0 and let IP choose, as we need to know it for 
     * the pseudoheader to calculate the UDP checksum.
     * If -1 option supplied, then use those values; otherwise,
     * connect a UDP socket to the destination to determine the right
     * source address.
     */
    if (lopt) {
        /* convert local name and service */
        aip = Host_serv(localname, localport, AF_INET, SOCK_DGRAM);
        local = api->ai_addr;
        locallen = aip->ai_addrlen;
    } else {
        int s;
        s = Socket(AF_INET, SOCK_DGRAM, 0);
        Connect(s, dest, destlen);
        /* kernel chooses correct local address for dest */
        locallen = sizeof(locallookup);
        local = (struct sockaddr *)&locallookup;
        Getsockname(s, local, &locallen);
        if (locallookup.sin_addr.s_addr == htonl(INADDR_ANY))
            err_quit("Can't determine local address - use -l\n");
        close(s);
    }
    open_output(); // 创建原始套接字并开启IP_HDRINCL
    open_pcap(); // 打开分组捕获设备
    setuid(getuid()); // 重设用户ID
    Signal(SIGTERM, cleanup);
    Signal(SIGINT, cleanup);
    Signal(SIGHUP, cleanup);
    test_udp();
    cleanup(0);
}
```

*udpcksum/main.c*

```c++
#include "udpcksum.h"
#define CMD "udp and src host %s and src port %d"
void 
open_pcap(void)
{
    uint32_t localnet, netmask;
    char cmd[MAXLINE], errbuf[PCAP_ERRBUF_SIZE],
         str1[INET_ADDRSTRLEN], str2[INET_ADDRSTRLEN];
    struct bpf_program fcode;
    if (device == NULL) {
        if ((device = pcap_lookupdev(errbuf)) == NULL) // 选择分组捕获设备
            err_quit("pcap_lookup: %s", errbuf);
    }
    printf("device = %s\n", device);
    /* hardcode: promisc=0, to_ms=500 */
    if ((pd = pcap_open_live(device, snaplen, 0, 500, errbuf)) == NULL) // 打开设备
        err_quit("pcap_open_live: %s", errbuf);
    if (pcap_lookupnet(device, &localnet, &netmask, errbuf) < 0) // 返回分组捕获设备的IP和子网掩码
        err_quit("pcap_lookupnet: %s", errbuf);
    if (verbose)
        printf("localnet = %s, netmask = %s\n",
               Inet_ntop(AF_INET, &localnet, str1, sizeof(str1)),
               Inet_ntop(AF_INET, &netmask, str2, sizeof(str2)));
    snprintf(cmd, sizeof(cmd), CMD,
             Sock_ntop_host(dest, destlen),
             ntohs(sock_get_port(dest, destlen)));
    if (verbose)
        printf("cmd = %s\n", cmd);
    if (pcap_compile(pd, &fcode, cmd, 0, netmask) < 0) // 编译分组过滤器
        err_quit("pcap_compile: %s", pcap_geterr(pd));
    if (pcap_setfilter(pd, &fcode) < 0) // 装载过滤器程序
        err_quit("pcap_setfilter: %s", pcap_geterr(pd));
    if ((datalink = pcap_datalink(pd)) < 0) // 确定数据链路类型
        err_quit("pcap_datalink: %s", pcap_geterr(pd));
    if (verbose)
        printf("datalink = %d\n", datalink);
}
char * 
next_pcap(int *len)
{
    char *ptr;
    struct pcap_pkthdr hdr;
    /* keep looping until packet ready */
    while ((ptr = (char *)pcap_next(pd, &hdr)) == NULL); // 返回下一个分组或超时返回NULL
    *len = hdr.caplen;
    return(ptr);
}
```

*udpcksum/pcap.c*

```c++
#include "udpcksum.h"
#include <setjmp.h>
static sigjmp_buf jmpbuf;
static int canjump;
void 
sig_alrm(int signo)
{
    if (canjump == 0)
        return;
    siglongjmp(jmpbuf, 1);
}
void 
test_udp(void)
{
    volatile int nsent = 0, timeout = 3;
    struct udpiphdr *ui;
    Signal(SIGALRM, sig_alrm);
    if (sigsetjmp(jmpbuf, 1)) {
        if (nsent >= 3) // 3次请求无响应
            err_quit("no response");
        printf("timeout\n");
        timeout *= 2;
    }
    canjump = 1;
    send_dns_query(); // 发送DNS查询
    nsent++;
    alarm(timeout);
    ui = udp_read(); // 读入应答
    canjump = 0;
    alarm(0);
    if (ui->ui_sum == 0)
        printf("UDP cheksums off\n");
    else
        printf("UDP checksums on\n");
    if (verbose)
        printf("received UDP checksum = %x\n", ntohs(ui->ui_sum));
}
```

*udpcksum/udpcksum.c*

```c++






void
send_dns_query(void)
{
    size_t nbytes;
    char *buf, *ptr;
    buf = Malloc(sizeof(struct udpiphdr) + 100);
    ptr = buf + sizeof(struct udpiphdr); // 构造DNS查询
    *((uint16_t *)ptr) = htons(1234);
    ptr += 2;
    *((uint16_t *)ptr) = htons(0x0100);
    ptr += 2;
    *((uint16_t *)ptr) = htons(1);
    ptr += 2;
    *((uint16_t *)ptr) = 0;
    ptr += 2;
    *((uint16_t *)ptr) = 0;
    ptr += 2;
    *((uint16_t *)ptr) = 0;
    ptr += 2;
    memcpy(ptr, "\001a\014root-servers\003net\000", 20);
    ptr += 20;
    *((uint16_t *)ptr) = htons(1);
    ptr += 2;
    *((uint16_t *)ptr) = htons(1);
    ptr += 2;
    nytes = (ptr - buf) - sizeof(struct udpiphdr);
    udp_write(buf, nbytes);
    if (verbose)
        printf("send: %d bytes of data\n", nbytes);
}
```

*udpcksum/senddnsquery-raw.c*

```c++

int rawfd; // 声明原始套接字描述符
void 
open_output(void)
{
    int on = 1;
    /*
     * Need a raw socket to write our own IP datagrams to.
     * Process must have superuser privileges to create this socket.
     * Also must set IP_HDRINCL so we can write our own IP heaers.
     */
    rawfd = Socket(dest->fa_family, SOCK_RAW, 0);
    Setsockopt(rawfd, IPPROTO_IP, IP_HDRINCL, &on, sizeof(on)); // 允许向套接字写完整IP数据报
}




void 
udp_write(char *buf, int userlen)
{
    struct udpiphdr *ui;
    struct ip *ip;
    /* fill in and checksum UDP header */
    ip = (struct ip *)buf;
    ui = (struct udpiphdr *)buf;
    bzero(ui, sizeof(*ui));
    /* add 8 to userlen for pseudoheader length */
    ui->ui_len = htons((uint16_t)(sizeof(struct udphdr) + userlen));
    /* then add 28 for IP datagram length */
    userlen += sizeof(struct udpiphdr); // 更新长度
    ui->ui_pr = IPPROTO_UDP;
    ui->ui_src.s_addr = ((struct sockaddr_in *)local)->sin_addr.s_addr;
    ui->ui_dst.s_addr = ((struct sockaddr_in *)dest)->sin_addr.s_addr;
    ui->ui_sport = ((struct sockaddr_in *)local)->sin_port;
    ui->ui_dport = ((struct sockaddr_in *)dest)->sin_port;
    ui->ui_ulen = ui->ui_len;
    if (zerosum == 0) {
#if 1
        if ((ui->ui_sum = in_cksum((u_int16_t *)ui, userlen)) == 0) // 计算校验和
            ui->ui_sum = 0xffff;
#else
        ui->ui_sum = ui->ui_len;
#endif
    }
    /* fill in rest of IP header; */
    /* ip_output() calcuates & stores IP header checksum */
    ip->ip_v = IPVERSION;
    ip->ip_hl = sizeof(struct ip) >> 2;
    ip->ip_tos = 0;
#if defined(linux) || defined(__OpenBSD__)
    ip->ip_len = htons(userlen);
#else
    ip->ip_len = userlen;
#endif
    ip->ip_id = 0;
    ip->ip_off = 0;
    ip->ip_ttl = TTL_OUT;
    Sendto(rawfd, buf, userlen, 0, dest, destlen);
}
```

*udpcksum/udpwrite.c*

```c++






struct udpiphdr * 
udp_read(void)
{
    int len;
    char *ptr;
    struct ether_header *eptr;
    for (;;) {
        ptr = next_pcap(&len); // 从分组捕获设备获取下一个分组
        switch(datalink) {
            case DLT_NULL:
                return(udp_check(ptr+4, len-4));
            case DLT_EN10MB:
                eptr = (struct ether_header *)ptr;
                if (ntohs(eptr->ether_type) != ETHERTYPE_IP)
                    err_quit("Ethernet type %x not IP", ntohs(eptr->ether_type));
                return(udp_check(ptr+14, len-14));
            case DLT_SLIP:
                return(udp_check(ptr+24, len-24));
            case DLT_ppp:
                return(udp_check(ptr+24, len-24));
            default:
                err_quit("unsupported datalink (%d)", datalink);
        }
    }
}






struct udpiphdr * 
udp_check(char *ptr, int len)
{
    int hlen;
    struct ip *ip;
    struct udpiphdr *ui;
    if (len < sizeof(struct ip) + sizeof(struct udphdr))
        err_quit("len = %d", len);
    /* minimal verification of IP header */
    ip = (struct ip *)ptr;
    if (ip->ip_v != IPVERSION)
        err_quit("ip_v = %d", ip->ip_v);
    hlen = ip->ip_hl << 2;
    if (hlen < sizeof(struct ip))
        err_quit("ip_hl = %d", ip->ip_hl);
    if (len < hlen + sizeof(struct udphdr))
        err_quit("len = %d, hlen = %d", len, hlen);
    if ((ip->ip_sum = in_cksum((uint16_t *)ip, hlen)) != 0)
        err_quit("ip checksum error");
    if (ip->ip_p == IPPROTO_UDP) {
        ui = (struct udpiphdr *)ip;
        return(ui);
    } else
        err_quit("not a UDP packet");
}
```

*udpcksum/udpread.c*

```c++

void 
cleanup(int signo)
{
    struct pcap_stat stat;
    putc('\n', stdout);
    if (verbose) {
        if (pcap_stats(pd, &stat) < 0)
            err_quit("pcap_stats: %s\n", pcap_geterr(pd));
        printf("%d packets received by filter\n", stat.ps_recv);
        printf("%d packets dropped by kernel\n", stat.ps_drop);
    }
    exit(0);
}
```

*udpcksum/cleanup.c*

### 29.7.1 例子

### 29.7.2 libnet输出函数

```c++






static libnet_t *l; // 声明libnet描述符
void 
open_output(void)
{
    char errbuf[LIBNET_ERRBUF_SIZE];
    /* Initialize libnet with an IPv4 raw socket */
    l = libnet_init(LIBNET_RAW4, NULL, errbuf); // 初始化libnet
    if (l == NULL) {
        err_quit("Can't initialize libnet: %s", errbuf);
    }
}
void 
send_dns_query(void)
{
    char qbuf[24], *ptr;
    u_int16_t one;
    int packet_size = LIBNET_UDP_H + LIBNET_DNSV4_H = 24;
    static libnet_ptag_t ip_tag, udp_tag, dns_tag;
    /* build query portion of DNS packet */
    ptr = qbuf;
    memcpy(ptr, "\001a\014root-servers\003net\000", 20);
    ptr += 20;
    one = htons(1);
    memcpy(ptr, &one, 2);
    ptr ++ 2;
    memcpy(ptr, &one, 2);
    /* buidl DNS packet */
    dns_tag = libnet_build_dnsv4(1234,
                                 0x0100,
                                 1, 0,
                                 0,
                                 0,
                                 qbuf,
                                 24, 1, dns_tag);
    /* build UDP header */
    udp_tag = libnet_build_udp(((struct sockaddr_in *)local)->
                               sin_port,
                               ((struct sockaddr_in *)dest)->
                               sin_port,
                               packet_size, 0, 
                               NULL, 0, 
                               1, udp_tag);
    /* Since we specified the checksum as 0, libnet will automatically */
    /* calculate the UDP checksum. Turn it off if the user doesn't want it. */
    if (zerosum)
        if (libnet_toggle_checksum(1, udp_tag, LIBNET_OFF) < 0)
            err_quit("turning off checksums: %s\n", libnet_geterror(1));
    /* build IP header */
    ip_tag = libnet_build_ipv4(packet_size + LIBNET_IPV4_H,
                               0, 0, 0,
                               TTL_OUT, IPPROTO_UDP, 
                               0,
                               ((struct sockaddr_in *)local)->sin_addr.s_addr,
                               ((struct sockaddr_in *)dest)->sin_addr.s_addr,
                               NULL, 0, 1, ip_tag);
    if (libnet_write(1) < 0) {
        err_quit("libnet_write: %s\n", libnet_geterror(1));
    }
    if (verbose)
        printf("sent: %d bytes of data\n", packet_size);
}
```

*udpcksum/senddnsquery-libnet.c*



## 29.8 小结



