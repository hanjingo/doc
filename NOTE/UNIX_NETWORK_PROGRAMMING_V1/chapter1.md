# 第一章 简介和TCP/IP
## 一个简单的时间获取客户程序
```c
#include "unp.h"

int
main(int argc, char **argv)
{
    int sockfd, n;
    char recvline[MAXLINE + 1];
    struct sockaddr_in6 servaddr;

    if (argc != 2) 
        err_quit("usage: a.out <IPaddress>");
    if ( (sockfd = socket(AF_INET6, SOCK_STREAM, 0)) < 0 )          // 创建套接字,返回套接字描述符
        err_sys("socket error");

    bzero(&servaddr, sizeof(servaddr));                             // 将servaddr清零
    servaddr.sin6_family = AF_INET6;                                // 设置地址族
    servaddr.sin6_port = htons(13);                                 // 设置端口，htons转换成二进制形式
    if (inet_pton(AF_INET6, argv[1], &servaddr.sin6_addr) <= 0)     // 设置ip
        err_quit("inet_pton error for %s", argv[1]);
    if (connect(sockfd, (SA *) &servaddr, sizeof(servaddr)) < 0>)   // 建立连接
        err_sys("connect error");

    while ( (n = read(sockfd, recvline, MAXLINE)) > 0 ) {           // 读一段MAXLINE大小的数据
        recvline[n] = 0;
        if (fputs(recvline, stdout) == EOF)
            err_sys("fputs error");
    }
    if (n < 0>)
        err_sys("read error");
    exit(0);
}
```

## 一个简单的时间获取服务器程序
```c
#include "unp.h"
#include <time.h>

int 
main(int argc, char **argv)
{
    int listenfd, connfd;
    struct sockaddr_in servaddr;
    char buf[MAXLINE];
    time_t ticks;

    listenfd = Socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(13);
    
    Bind(listenfd, (SA *) &servaddr, sizeof(servaddr));
    
    Listen(listenfd, LISTENQ);                          // 监听套接字
    
    for ( ; ; ) {
        connfd = Accept(listenfd, (SA *) NULL, NULL);   // 接受并创建套接字（阻塞），返回套接字描述符

        ticks = time(NULL);
        snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
        Write(connfd, buff, strlen(buff));

        Close(connfd);                                  // 关闭套接字
    }
}
```

## OSI模型
- 应用层
> - 应用层
> - 表示层
> - 会话层
- TCP/UDP
> - 传输层
- IPv4/Ipv6
> - 网络层
- 设备驱动程序和硬件
> - 数据链路层
> - 物理层