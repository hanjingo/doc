[TOC]

# epoll

epoll是linux内核的可扩展`I/O`事件通知机制，于linux 2.5.44首次登场，旨在取代`poll`和`select`



## 定义



## 接口

### epoll_create

```c++
int epoll_create(int size);
```

创建epoll对象，流程如下：

1. 在内核cache里建立了一个红黑树用于存储`epoll_ctl`传来的`socket`；
2. 在内核cache建立一个`rdllist`双向链表（就序列表），用于存储准备就绪的事件。

- size 无意义，兼容以前的代码

### poll_ctl

```sh
int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);
```

向epfd对应的内核`epoll`实例添加，修改或删除对fd上事件event的监听。

- `epfd` epoll的文件描述符

- `op` 操作

  - `EPOLL_CTL_ADD` 添加事件
  - `EPOLL_CTL_MOD` 修改监听的事件
  - `EPOLL_CTL_DEL` 删除监听的事件

- `fd` 套接字

- `event` 事件

  | 事件         | 说明 |
  | ------------ | ---- |
  | EPOLLIN      |      |
  | EPOLLOUT     |      |
  | EPOLLONESHOT |      |
  | EPOLLHUP     |      |
  | EPOLLRDHUP   |      |
  | EPOLLPRI     |      |
  | EPOLLERR     |      |

### epoll_wait

```c++
int epoll_wait(int epfd, struct epoll_event *events, int maxevents, int timeout);
```

检测有没有数据，有数据就返回，没有数据就`sleep`，等到`timeout`时间到后返回，示意图如下：

![epoll_wait](res/epoll_wait.png)

- `epfd`
- `events`
- `maxevents`
- `timeout`
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



## 参考

- [维基百科-epoll](https://zh.wikipedia.org/wiki/Epoll)

