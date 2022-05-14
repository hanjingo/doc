# 第十九章 密钥管理套接字

[TOC]



## 19.1 概述

密钥管理套接字支持以下类型的操作：

- 通过写出到密钥管理套接字，进程可以往内核以及打开着密钥管理套接字的所有其他进程发送消息。
- 通过从密钥管理套接字读入，进程可以自内核（或其他进程）接收消息。
- 进程可以往内核发送一个倾泻（dumping）请求消息，内核作为应答倾泻出当前的SADB。



## 19.2 读和写

```c++
struct sadb_msg {
    u_int8_t  sadb_msg_version;
    u_int8_t  sadb_msg_type;
    u_int8_t  sadb_msg_errno;
    u_int8_t  sadb_msg_satype;
    u_int16_t sadb_msg_len;
    u_int16_t sadb_msg_reserved;
    u_int32_t sadb_msg_seq;
    u_int32_t sadb_msg_pid;
};
```

![19_2](res/19_2.png)

*通过密钥管理套接字交换的消息类型*

![19_3](res/19_3.png)

![19_3B](res/19_3B.png)

*PF_KEY扩展类型*



## 19.3 倾泻安全关联数据库

![19_4](res/19_4.png)

*SA类型*

```c++
void 
sadb_dump(int type)
{
    int s;
    char buf[4096];
    struct sadb_msg msg;
    int goteof;
    s = Socket(PF_KEY, SOCK_RAW, PF_KEY_V2); // 打开PF_KEY套接字
    /* 构造SADB_DUMP请求 */
    bzero(&msg, sizeof(msg));
    msg.sadb_msg_version = PF_KEY_V2;
    msg.sadb_msg_type = SADB_DUMP;
    msg.sadb_msg_satype = type;
    msg.sadb_msg_len = sizeof(msg) / 8;
    msg.sadb_msg_pid = getpid();
    printf("Sending dump message:\n");
    print_sadb_msg(&msg, sizeof(msg));
    Write(s, &msg, sizeof(msg)); // 写SADB_DUP消息
    printf("\nMessages returned:\n");
    /* Read and print SADB_DUMP replies until done */
    goteof = 0;
    while (goteof == 0) {
        int msglen;
        struct sadb_msg *msgp;
        msglen = Read(s, &buf, sizeof(buf));
        msgp = (struct sadb_msg *)&buf;
        print_sadb_msg(msgp, msglen);
        if (msgp->sadb_msg_seq == 0)
            goteof = 1;
    }
    close(s);
}
int 
main(int argc, char **argv)
{
    int satype = SADB_SATYPE_UNSPEC;
    int c;
    opterr = 0;
    while ((c = getopt(argc, argv, "t:")) != -1) {
        switch(c) {
            case 't':
                if ((satype = getsatypebyname(optarg)) == -1)
                    err_quit("invalid -t option %s", optarg);
                break;
            default:
                err_quit("unrecognized option: %c", c);
        }
    }
    sadb_dump(satype);
}
```

*通过密钥管理套接字发出SADB_DUMP命令的程序*



## 19.4 创建静态安全关联

SADB_ADD消息的扩展：

- SA（必须）
- 地址（必须）
- 密钥（必须）
- 生命期（可选）
- 身份（可选）
- 敏感性（可选）

```c++
struct sadb_sa {
    u_int16_t sadb_sa_len;     // 
    u_int16_t sadb_sa_exttype; // 
    u_int32_t sadb_sa_spi;     // 
    u_int8_t  sadb_sa_replay;  // 
    u_int8_t  sadb_sa_state;   // 
    u_int8_t  sadb_sa_auth;    // 
    u_int8_t  sadb_sa_encrypt; // 
    u_int32_t sadb_sa_flags;   // 
};
```

*SA扩展*

![19_7](res/19_7.png)

*SA的可能状态*

![19_8](res/19_8.png)

*认证和加密算法*

```c++
struct sadb_address {
    u_int16_t sadb_address_len;
    u_int16_t sadb_address_exttype;
    u_int8_t  sadb_address_proto;
    u_int8_t  sadb_address_prefixlen;
    u_int16_t sadb_address_reserved;
};
```

*地址扩展*

```c++
struct sadb_key {
    u_int16_t sadb_key_len;
    u_int16_t sadb_key_exttype;
    u_int16_t sadb_key_bits;
    u_int16_t sadb_key_reserved;
};
```

*密钥扩展*

```c++
struct sadb_lifetime {
    u_int16_t sadb_lifetime_len;
    u_int16_t sadb_lifetime_exttype;
    u_int32_t sadb_lifetime_allocations;
    u_int64_t sadb_lifetime_bytes;
    u_int64_t sadb_lifetime_addtime;
    u_int64_t sadb_lifetime_usetime;
};
```

*生命期扩展*

```c++
TODO
```

*key/add.c*



## 19.5 动态维护安全关联

```c++
struct sadb_supported {
    u_int16_t sadb_supported_len;
    u_int16_t sadb_supported_exttype;
    u_int32_t sadb_supported_reserved;
};
struct sadb_alg {
    u_int8_t sadb_alg_id;
    u_int8_t sadb_alg_ivlen;
    u_int16_t sadb_alg_minbits;
}
```

*受支持算法扩展*

![19_14](res/19_14.png)

*内核为SADB_REGISTER请求返回的应答*

```c++
void 
sadb_register(int type)
{
    int s;
    char buf[4096];
    struct sadb_msg msg;
    int goteof;
    int mypid;
    s = Socket(PF_KEY, SOCK_RAW, PF_KEY_V2);
    mypid = getpid(); // 保存PID
    /* Build and write SADB_REGISTER request */
    bzero(&msg, sizeof(msg));
    msg.sadb_msg_version = PF_KEY-V2;
    msg.sadb_msg_type = SADB_REGISTER;
    msg.sadb_msg_satype = type;
    msg.sadb_msg_len = sizeof(msg) / 8;
    msg.sadb_msg_pid = mypid;
    printf("Sending register message:\n");
    print_sadb_msg(&msg, sizeof(msg));
    Write(s, &msg, sizeof(msg)); // 写消息
    printf("\nReply returned:\n");
    /* Read and print SADB_REGISTER reply, discarding any others */
    for (;;) { // d
        int msglen;
        struct sadb_msg *msgp;
        msglen = Read(s, &buf, sizeof(buf));
        msgp = (struct sadb_msg *)&buf;
        if (msgp->sadb_msg_pid == mypid && 
            msgp->sadb_msg_type == SADB_REGISTER) {
            print_sadb_msg(msgp, msglen);
            break;
        }
    }
    close(s);
}
```

*key/register.c*



## 19.6 小结

