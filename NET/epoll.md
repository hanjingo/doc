[TOC]

# epoll

epoll是linux内核的可扩展`I/O`事件通知机制，于linux 2.5.44首次登场，旨在取代`poll`和`select`



## 定义



## 接口

### epoll_create

头文件：`sys/epoll.h`

```c++
int epoll_create(int size);
```

创建epoll对象，流程如下：

1. 在内核cache里建立了一个红黑树用于存储`epoll_ctl`传来的`socket`；
2. 在内核cache建立一个`rdllist`双向链表（就序列表），用于存储准备就绪的事件。

- size 无意义，兼容以前的代码

### poll_ctl

头文件：`sys/epoll.h`

```c
int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);
```

向epfd对应的内核`epoll`实例添加，修改或删除对fd上事件event的监听。

- `epfd` epoll句柄

- `op` 操作

  - `EPOLL_CTL_ADD` 添加事件
  - `EPOLL_CTL_MOD` 修改监听的事件
  - `EPOLL_CTL_DEL` 删除监听的事件

- `fd` 套接字

- `event` 事件

  | 事件         | 说明                                          |
  | ------------ | --------------------------------------------- |
  | EPOLLIN      | 描述符处于可读状态                            |
  | EPOLLOUT     | 描述符处于可写状态                            |
  | EPOLLET      | 将`epoll event`通知模式设置成`edge triggered` |
  | EPOLLONESHOT | 第一次进行通知，之后不在监测                  |
  | EPOLLHUP     | 本段描述符产生一个挂断事件，默认监测事件      |
  | EPOLLRDHUP   | 对端描述符产生一个挂断事件                    |
  | EPOLLPRI     | 由带外数据触发                                |
  | EPOLLERR     | 描述符产生错误时触发，默认监测事件            |

### epoll_wait

头文件：`sys/epoll.h`

```c++
int epoll_wait(int epfd, struct epoll_event *events, int maxevents, int timeout);
```

检测有没有数据，有数据就返回，没有数据就`sleep`，等到`timeout`时间到后返回，示意图如下：

![epoll_wait](res/epoll_wait.png)

- `epfd` epoll句柄
- `events` 用来记录被触发的events，其大小应该和maxevents一致
- `maxevents` 返回的events的最大个数
- `timeout` 超时时间（ms）
  - `0`  立即返回
  - `-1` 一直阻塞到已注册的事件变为就绪
  - `>0` 阻塞直到时间结束或已注册的时间变为就绪



## 触发模式

- LT（`Level Triggered`，水平触发）

  默认模式，**只要有数据都会触发**，缓冲区剩余未读尽的数据会导致epoll_wait返回。

- ET（`Edge Triggered`，边缘触发）

  高速模式，**只有数据到来才触发**，**不管缓存区中是否还有数据**，缓冲区剩余未读尽的数据不会导致epoll_wait返回；Nginx用的ET。
  
  在以下情况推荐使用：
  
  - `read`或`write`系统调用返回`EAGAIN`
  - 非阻塞的文件描述符



## 用例

### 服务端

```c
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <sys/resource.h>

#define MAXEPOLL 10000
#define MAXLINE  1024
#define PORT 		 6000
#define MAXBACK  1000

int setnonblocking(int fd)
{
  if(fcntl(fd, F_SETFL, fcntl(fd, F_GETFD, 0)|O_NONBLOCK) == -1)
  {
    printf("Set blocking error:%d\n", errno);
    return -1;
  }
  return 0;
}

int main(int argc, char** argv)
{
  int listen_fd;
  int conn_fd;
  int epoll_fd;
  int nread;
  int cur_fds;
  int wait_fds;
  int i;
  struct sockaddr_in servaddr;
  struct sockaddr_in cliaddr;
  struct epoll_event ev; 						// 注意这里
  struct epoll_event evs[MAXEPOLL]; // 注意注意
  struct rlimit rlt; 								// 设置连接数
  char buf[MAXLINE];
  socklen_t len = sizeof(struct sockaddr_in);
  
  // 设置每个进程允许打开的最大文件数
  rlt.rlim_max = rlt.rlim_cur = MAXEPOLL;
  if(setrlimit(RLIMIT_NOFILE, &rlt) == -1)
  {
    printf("Setrlimit Error : %d\n", errno);
    exit(EXIT_FAILURE);
  }
  
  // 建立套接字
  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(PORT);
  if((listen_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
  {
    printf("Socket Error...\n", errno);
    exit(EXIT_FAILURE);
  }
  
  // 设置非阻塞模式
  if(setnonblocking(listen_fd) == -1)
  {
    printf("Setnonblocking Error:%d\n", errno);
    exit(EXIT_FAILURE);
  }
  
  // 绑定
  if(bind(listen_fd, (struct sockaddr*)&servaddr, sizeof(struct sockaddr)) == -1)
  {
    printf("Bind Error : %d\n", errno);
    exit(EXIT_FAILURE);
  }
  
  // 监听
  if(listen(listen_fd, MAXBACK) == -1)
  {
    printf("Listen Error : %d\n", errno);
    exit(EXIT_FAILURE);
  }
  
  // epoll操作（重点！！！）
  epoll_fd = epoll_create(MAXEPOLL);
  ev.events = EPOLLIN | EPOLLET;
  ev.data.fd = listen_fd; // 加入listen_fd
  if(epoll_ctl(epoll_fd, EPOLL_CTL_ADD, listen_fd, &ev) < 0)
  {
    printf("Epoll Error : %d\n", errno);
    exit(EXIT_FAILURE);
  }
  cur_fds = 1;
  
  // 监听epoll事件
  while(1)
  {
    if((wait_fds = epoll_wait(epoll_fd, evs, cur_fds, -1)) == -1)
    {
      printf("Epoll Wait Error : %d\n", errno);
      exit(EXIT_FAILURE);
    }
    for(i = 0; i < wait_fds; i++)
    {
      if(evs[i].data.fd == listen_fd && cur_fds < MAXEPOLL)
      {
        if((conn_fd = accept(listen_fd, (struct sockaddr *)&cliaddr, &len)) == -1)
        {
          printf("Accept Error : %d\n", errno);
          exit(EXIT_FAILURE);
        }
        printf("Server get from client!\n");
        
        ev.events = EPOLLIN | EPOLLET; // 边缘触发，高速模式
        ev.data.fd = conn_fd; 				 // 放入连接描述符
        if(epoll_ctl(epoll_fd, EPOLL_CTL_ADD, conn_fd, &ev) < 0) // 添加事件
        {
          printf("Epoll Error : %d\n", errno);
          exit(EXIT_FAILURE);
        }
        ++cur_fds; // 文件描述符数+1
        continue;
      }
      // 读数据
      nread = read(evs[i].data.fd, buf, sizeof(buf));
      if(nread <= 0)
      {
        close(evs[i].data.fd);
        epoll_ctl(epoll_fd, EPOLL_CTL_DEL, evs[i].data.fd, &ev); // 读取失败，删除事件
        --cur_fds;
        continue;
      }
      // 写数据
      write(evs[i].data.fd, buf, nread);
    }
  }
  close(listen_fd); // 关闭监听
  return 0;
}
```

### 客户端

```c
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/select.h>

#define MAXLINE 	1024
#define SERV_PORT 6000

void send_and_recv(int connfd)
{
  FILE* fp = stdin;
  int lens;
  char send[MAXLINE];
  char recv[MAXLINE];
  fd_set rset;
  FD_ZERO(&rset);
  int maxfd = (fileno(fp) > connfd ? fileno(fp) : connfd + 1);
  int n;
  
  while(1)
  {
    FD_SET(fileno(fp), &rset);
    FD_SET(connfd, &rset);
    if(select(maxfd, &rset, NULL, NULL, NULL) == -1)
    {
      printf("Client Select Error..\n");
      exit(EXIT_FAILURE);
    }
    
    // 连接端口有信息
    if(FD_ISSET(connfd, &rset))
    {
      printf("client get from server...\n");
      memset(recv, 0, sizeof(recv));
      n = read(connfd, recv, MAXLINE);
      if(n == 0)
      {
        printf("Recv ok...\n");
        break;
      }
      else if(n == -1)
      {
        printf("Recv error...\n");
        break;
      }
      else
      {
        lens = strlen(recv);
        recv[lens] = '\0';
        write(STDOUT_FILENO, recv, MAXLINE);
        printf("\n");
      }
    }
    
    if(FD_ISSET(fileno(fp), &rset))
    {
      memset(send, 0, sizeof(send));
      if(fgets(send, MAXLINE, fp) == NULL)
      {
        printf("End...\n");
        exit(EXIT_FAILURE);
      }
      else
      {
        lens = strlen(send);
        send[lens-1] = '\0'; // 不要回车字符
        if(strcmp(send, "q") == 0)
        {
          printf("Bye..\n");
          return;
        }
        printf("Client send : %s\n", send);
        write(connfd, send, strlen(send));
      }
    }
  }
}

int main(int argc, char** argv)
{
  char buf[MAXLINE];
  int connfd;
  struct sockaddr_in servaddr;
  
  if(argc != 2)
  {
    printf("Input server ip!\n");
    exit(EXIT_FAILURE);
  }
  
  // 建立套接字
  if((connfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
  {
    printf("Socket Error...\n", errno);
    exit(EXIT_FAILURE);
  }
  
  // 套接字信息
  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(SERV_PORT);
  inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
  
  // 链接server
  if(connect(connfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)
  {
    printf("Connect error..\n");
    exit(EXIT_FAILURE);
  }
  
  send_and_recv(connfd);
  close(connfd);
  printf("Exit\n");
  return 0;
}
```



## 参考

- [维基百科-epoll](https://zh.wikipedia.org/wiki/Epoll)
- [作为C++程序员，应该彻底搞懂epoll高效运行的原理](https://zhuanlan.zhihu.com/p/159135478)
- <<Linux 高性能服务器编程>>

