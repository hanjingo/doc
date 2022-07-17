# 第二十三章 高级SCTP套接字编程

[TOC]



## 23.1 概述



## 23.2 自动关闭的一到多式服务器程序

自动关闭允许SCTP端点指定某个关联可以保持空闲的最大秒钟数。关联在任何方向上都没有用户数据在传输时就认为它是空闲的。如果关联的控件事件超过它的最大允许事件，该关联就由SCTP实现自动关闭。

```c++
if (argc == 2)
    stream_increment = atoi(argv[1]);
	sock_fd = Socket(AF_INET, SOCK_SEQPACKET, IPPROTO_SCTP);
close_time = 120;
Setsockopt(sock_fd, IPPROTO_SCTP, SCTP_AUTOCLOSE,
           &close_time, sizeof(close_time));
bzero(&servaddr, sizeof(servaddr));
servaddr.sin_family = AF_INET;
servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
servaddr.sin_port = htons(SERV_PORT);
```

*sctp/sctpserv04.c*



## 23.3 部分递送

当应用进程要求SCTP传输过大的消息时，SCTP可能采取部分递送措施。

```c++
#include "unp.h"
static uint8_t *sctp_pdapi_readbuf = NULL;
static int sctp_pdapi_rdbuf_sz = 0;
uint8_t *
pdapi_recvmsg(int sock_fd,
              int *rdlen,
              SA *from,
              int *from_len, struct sctp_sndrcvinfo *sri, int *msg_flags)
{
    int rdsz, left, at_in_buf;
    int frmlen = 0;
    if (sctp_pdapi_readbuf == NULL) {
        sctp_pdapi_readbuf = (uint8_t *)Malloc(SCTP_PDAPI_INCR_SZ);
        sctp_pdapi_rdbuf_sz = SCTP_PDAPI_INCR_SZ;
    }
    at_in_buf = 
        Sctp_recvmsg(sock_fd, sctp_pdapi_readbuf, sctp_pdapi_rdbuf_sz, from,
                     from_len, sri, msg_flags);
    if (at_in_buf < 1) {
        *rdlen = at_in_buf;
        return(NULL);
    }
    while ((*msg_flags & MSG_EOR) == 0) {
        left = sctp_pdapi_rdbuf_sz - at_in_buf;
        if (left < SCTP_PDAPI_NEED_MORE_THRESHOLD) {
            sctp_pdapi_readbuf = 
                realloc(sctp_pdapi_readbuf,
                        sctp_pdapi_rdbuf_sz + SCTP_PDAPI_INCR_SZ);
            if (sctp_pdapi_readbuf == NULL) {
                err_quit("sctp_pdapi ran out of memory");
            }
            sctp_pdapi_rdbuf_sz += SCTP_PDAPI_INCR_SZ;
            left = sctp_pdapi_rdbuf_sz - at_in_buf;
        }
        rdsz = Sctp_recvmsg(sock_fd, &sctp_pdapi_readbuf[at_in_buf],
                            left, NULL, &frmlen, NULL, msg_flags);
        at_in_buf += rdsz;
    }
    *rdlen = at_in_buf;
    return(sctp_pdapi_readbuf);
}
```

*sctp/sctp_pdapircv.c*

```c++
for (;;) {
    len = sizeof(struct sockaddr_in);
    bzero(&sri, sizeof(sri));
    readbuf = pdapi_recvmsg(sock_fd, &rd_sz,
                            (SA *)&cliaddr, &len, &sri, &msg_flags);
    if (readbuf == NULL)
        continue;
}
```

*sctp/sctpserv05.c*



## 23.4 通知

```c++
#include "unp.h"
void 
print_notification(char *notify_buf)
{
    union sctp_notification *snp;
    struct sctp_assoc_change *sac;
    struct sctp_paddr_change *spc;
    struct sctp_remote_error *sre;
    struct scpt_send_failed *ssf;
    struct sctp_shutdown_event *sse;
    struct sctp_adaption_event *ae;
    struct sctp_pdapi_event *pdapi;
    const char *str;
    snp = (union sctp_notification *)notify_buf;
    switch(snp->sn_header.sn_type) {
        case SCTP_ASSOC_CHANGE:
            sac = &snp->sn_assoc_change;
            switch(sac->sac_state) {
                case SCTP_COM_UP:
                    str = "COMMUNICATION UP";
                    break;
                case SCTP_COMM_LOST:
                    str = "COMMUNICATION LOST";
                    break;
                case SCTP_RESTART:
                    str = "RESTART";
                    break;
                case SCTP_SHUTDOWN_COMP:
                    str = "SHUTDOWN COMPLETE";
                    break;
                case SCTP_CANT_STR_ASSOC:
                    str = "CAN'T START ASSOC";
                    break;
                default:
                    str = "UNKNOWN";
                    break;
            }
            printf("SCTP_ASSOC_CHANGE:%s, assoc=0x%x\n", str, 
                   (uint32_t)sac->sac_assoc_id);
            break;
        case SCTP_PEER_ADDR_CHANGE:
            spc = &snp->sn_paddr_change;
            switch(spc->spc_state) {
                case SCTP_ADDR_AVAILABLE:
                    str = "ADDRESS AVAILABLE";
                    break;
                case SCTP_ADDR_UNREACHABLE:
                    str = "ADDRESS UNREACHABLE";
                    break;
                case SCTP_ADDR_REMOVED:
                    str = "ADDRESS REMOVED";
                    break;
                case SCTP_ADDR_ADDED:
                    str = "ADDRESS ADDED";
                    break;
                case SCTP_ADDR_MADE_PRIM:
                    str = "ADDRESS MAKE PRIMARY";
                    break;
                default:
                    str = "UNKNOWN";
                    break;
            }
            printf("SCTP_PEER_ADDR_CHANGE: %s, addr=%s, assoc=0x%x\n", str, 
                  Sock_ntop((SA *)&spc->spc_aaddr, sizeof(spc->spc_aaddr)),
                  (uint32_t)spc->spc_assoc_id);
            break;
        case SCTP_REMOTE_ERROR:
            sre = &snp->sn_remote_error;
            printf("SCTP_REMOTE_ERROR: assoc=0x%x error=%d\n",
                   (uint32_t)sre->sre_assoc_id, sre->sre_error);
            break;
        case SCTP_SEND_FAILED:
            ssf = &snp->sn_send_failed;
            printf("SCTP_SEND_FAILED: assoc=0x%x error=%d\n",
                   (uint32_t)ssf->ssf_assoc_id, ssf->ssf_error);
            break;
        case SCTP_ADAPTION_INDICATION:
            ae = &snp->sn_adaption_event;
            printf("SCTP_ADAPTION_INDICATION: 0x%x\n",
                   (u_int)ae->sai_adaption_ind);
            break;
        case SCTP_PARTIAL_DELIVERY_EVENT:
            pdapi = &snp->sn_pdapi_event;
            if (pdapi->pdapi_indication == SCTP_PARTIAL_DELIVERY_ABORTED)
                printf("SCTP_PARTIAL_DELIEVERY_ABORTED\n");
            else
                printf("Unknown SCTP_PARTIAL_DELIVERY_EVENT 0x%x\n",
                       pdapi->pdapi_indication);
            break;
        case SCTP_SHUTDOWN_EVENT:
            sse = &snp->sn_shutdown_event;
            printf("SCTP_SHUTDOWN_EVENT: assoc=0x%x\n",
                   (uint32_t)sse->sse_assoc_id);
            break;
        default:
            printf("Unknown notification event type=0x%x\n",
                   snp->sn_header.sn_type);
    }
}
```

*sctp/sctp_displayevents.c*

```c++
bzero(&evnts, sizeof(evnts));
evnts.sctp_data_io_event = 1;
evnts.sctp_association_event = 1;
evnts.sctp_address_event = 1;
evnts.sctp_send_failure_event = 1;
evnts.sctp_peer_error_event = 1;
evnts.sctp_shutdown_event = 1;
evnts.sctp_partial_delivery_event = 1;
evnts.sctp_adaption_layer_event = 1;
Setsockopt(sock_fd, IPPROTO_SCTP, SCTP_EVENTS, &evnts, sizeof(evnts));
Listen(sock_fd, LISTENQ);
for (;;) {
    len = sizeof(struct sockaddr_in);
    rd_sz = Sctp_recvmsg(sock_fd, readbuf, sizeof(readbuf),
                         (SA *)&cliaddr, &len, &sri, &msg_flags);
    if (msg_flags & MSG_NOTIFICATION) {
        print_notification(readbuf);
        continue;
    }
}
```

*sctp/sctpserv06.c*



## 23.5 无序的数据

SCTP指定MSG_UNORDERED标志发送的消息没有顺序限制，一到达对端就能被递送。无序的数据可以在任何SCTP流中发送，不用赋予流序列号。

```c++
out_sz = strlen(sendline);
Sctp_sendmsg(sock_fd, sendline, out_sz,
             to, tolen, 0, MSG_UNORDERED, sri.sinfo_stream, 0, 0);
```

*sctp/sctp_strcli_un.c*



## 23.6 捆绑地址子集

SCTP提供新的sctp_bindx函数调用允许应用进程捆绑多个地址（**注意：所有这些地址必须使用相同的端口**）。

```c++
#include "unp.h"
int 
sctp_bind_arg_list(int sock_fd, char **argv, int argc)
{
    struct addrinfo *addr;
    char *bindbuf, *p, portbuf[10];
    int addrcnt = 0;
    itn i;
    bindbuf = (char *)Calloc(argc, sizeof(struct sockaddr_storage));
    p = bindbuf;
    sprintf(portbuf, "%d", SERV_PORT);
    for (i = 0; i < argc; i++) {
        addr = Host_serv(argv[i], portbuf, AF_UNSPEC, SOCK_SEQPACKET);
        memcpy(p, addr->ai_addr, addr->ai_addrlen);
        freeaddrinfo(addr);
        addrcnt++;
        p += addr->ai_addrlen;
    }
    Sctp_bindx(sock_fd, (SA *)bindbuf, addrcnt, SCTP_BINDX_ADD_ADDR);
    free(bindbuf);
    return 0;
}
```

*sctp/sctp_bindargs.c*

```c++
if (argc < 2)
    err_quit("Error, use %s [list of addresses to bind]\n", argv[0]);
sock_fd = Socket(AF_INET6, SOCK_SEQPACKET, IPPROTO_SCTP);
if (sctp_bind_arg_list(sock_fd, argv + 1, argc - 1))
    err_sys("Can't bind the address set");
bzero(&evnts, sizeof(evnts));
evnts.sctp_data_io_event = 1;
```

*sctp/sctpserv07.c*



## 23.7 确定对端和本端地址信息

```c++
bzero(&evnts, sizeof(evnts));
evnts.sctp_data_io_event = 1;
evnts.sctp_association_event = 1;
Setsockopt(sock_fd, IPPROTO_SCTP, SCTP_EVENTS, &evnts, sizeof(evnts));
sctpstr_cli(stdin, sock_fd, (SA *)&servaddr, sizeof(servaddr));
```

*sctp/sctpclient04*

```c++
do {
    len = sizeof(peeraddr);
    rd_sz = Sctp_recvmsg(sock_fd, recvline, sizeof(recvl;ine),
                         (SA *)&peeraddr, &len, &sri, &msg_flags);
    if (msg_flags * MSG_NOTIFICATION)
        check_notification(sock_fd, recvline, rd_sz);
} while (msg_flags & MSG_NOTIFICATION);
printf("From str:%d seq:%d (assoc:0x%x):",
       sri.sinfo_stream, sri.sinfo_ssn, (u_int)sri.sinfo_assoc_id);
printf("%.*s", rd_sz, recvline);
```

*sctp/sctp_strcli1.c*

```c++
#include "unp.h"
void 
check_notification(int sock_fd, char *recvline, int rd_len)
{
    union sctp_notification *snp;
    struct sctp_assoc_change *sac;
    struct sockaddr_storage *sal, *sar;
    int num_rem, num_loc;
    snp = (union sctp_notification *)recvline;
    if (snp->sn_header.sn_type == SCTP_ASSOC_CHANGE) {
        sac = &snp->sn_assoc_change;
        if ((sac->sac_state == SCTP_COMM_UP) || 
            (sac->sac_state == SCTP_RESTART)) {
            num_rem = sctp_getpaddrs(sock_fd, sac->sac_assoc_id, &sar);
            printf("Thread are %d remote addresses and they are:\n", num_rem);
            sctp_print_addresses(sar, num_rem);
            sctp_freepaddrs(sar);
            num_lock = sctp_getladdrs(sock_fd, sac->sac_assoc_id, &sal);
            printf("There are %d local addresses and they are:\n", num_loc);
            sctp_print_addresses(sal, num_loc);
            sctp_freeladdrs(sal);
        }
    }
}
```

*sctp/sctp_check_notify.c*

```c++
#include "unp.h"
void 
sctp_print_addresses(struct sockaddr_storage *addrs, int num)
{
    struct sockaddr_storage *ss;
    int i, salen;
    ss = addrs;
    for (i = 0; i < num; i++) {
        printf("%s\n", Sock_ntop((SA *)ss, salen));
#ifdef HAVE_SOCKADDR_SA_LEN
        salen = ss->ss_len;
#else
        switch(ss->ss_family) {
            case AF_INET:
                salen = sizeof(struct sockaddr_in);
                break;
#ifdef IPV6
            case AF_INET6:
                salen = sizeof(struct sockaddr_in6);
                break;
#endif
            default:
                err_quit("sctp_print_addresses: unknown AF");
                break;
        }
#endif
        ss == (struct sockaddr_storage *)((char *)ss + salen);
    }
}
```

*sctp/sctp_print_addrs.c*



## 23.8 给定IP地址找出关联ID

```c++
#include "unp.h"
sctp_assoc_t 
sctp_address_to_associd(int sock_fd, struct sockaddr *sa, socklen_t salen)
{
    struct sctp_paddrparams sp;
    int siz;
    siz = sizeof(struct sctp_paddrparams);
    bzero(&sp, siz);
    memcpy(&sp.spp_address, sa, salen);
    sctp_opt_info(sock_fd, 0, SCTP_PEER_ADDR_PARAMS, &sp, &siz);
    return (sp.spp_assoc_id);
}
```

*sctp/sctp_addr_to_associd.c*



## 23.9 心搏和地址不可达

SCTP的心搏机制默认开启。

```c++
#include "unp.h"
int 
heartbeat_action(int sock_fd, struct sockaddr *sa, socklen_t salen,
                 u_int value)
{
    struct sctp_paddrparams sp;
    int siz;
    bzero(&sp, sizeof(sp));
    sp.spp_hbinterval = value;
    memcpy((caddr_t)&sp.spp_address, sa, salen);
    Setsockopt(sock_fd, IPPROTO_SCTP,
               SCTP_PEER_ADDR_PARAMS, &sp, sizeof(sp));
    return (0);
}
```

*sctp/sctp_modify_hb.c*



## 23.10 关联剥离

一到多式接口相比一到一式接口存在以下优势：

- 只需维护单个描述符。
- 允许编写简单的迭代服务器程序。
- 允许应用进程在四路握手的第三个和第四个分组发送数据，只需使用sendmsg或sctp_sendmsg隐式建立关联就行。
- 无需跟踪传输状态。也就是说应用进程只需在套接字描述符上执行一个接收调用就可以接收消息，之前不必执行传统的connect或accept调用。

```c++
for (;;) {
    len = sizeof(struct sockaddr_in);
    rd_sz = Sctp_recvmsg(sock_fd, readbuf, sizeof(readbuf),
                         (SA *)&cliaddr, &len, &sri, &msg_flags);
    Sctp_sendmsg(sock_fd, readbuf, rd_sz,
                 (SA *)&cliaddr, len,
                 sri.sinfo_ppid,
                 sri.sinfo_flags, sri.sinfo_stream, 0, 0);
    assoc = sctp_address_to_associd(sock_fd, (SA *)&cliaddr, len);
    if ((int)assoc == 0) {
        err_ret("can't get association id");
        continue;
    }
    connfd = sctp_peeloff(sock_fd, assoc);
    if (connfd == -1) {
        err_ret("sctp_peeloff fails");
        continue;
    }
    if ((childpid = fork()) == 0) {
        Close(sock_fd);
        str_echo(connfd);
        exit(0);
    } else {
        Close(connfd);
    }
}
```

*sctp/sctpserv_fork.c*



## 23.11 定时控制

![23_16](res/23_16.png)

*SCTP中控制定时的字段*



## 23.12 何时改用SCTP代替TCP

SCTP的优点：

- SCTP直接支持多宿。
- 可以消除头端阻塞。
- 保持应用层消息边界。
- 提供无序消息服务。
- 有些SCTP实现提供部分可靠服务。
- SCTP以一到一式接口提供了从TCP到SCTP的简易已知手段。
- SCTP提供TCP的许多特性。
- SCTP提供许多供应用进程配置和调整传输服务，以便基于关联匹配其需求的挂钩。

SCTP不提供以下TCP特性：

- 半关闭状态。
- 紧急数据。



## 23.13 小结

