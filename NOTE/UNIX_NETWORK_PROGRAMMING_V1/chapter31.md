# 第三十一章 流

[TOC]



## 31.1 概述



## 31.2 概貌

![31_1](res/31_1.png)

*一个进程和一个驱动程序之间的某个流*

![31_2](res/31_2.png)

*压入一个处理模块的某个流*

![31_3](res/31_3.png)

*TCP/IP基于流的某种可能的实现*

![31_4](res/31_4.png)

*流中每个部件至少有一对队列*

![31_5](res/31_5.png)

*一个队列中的流消息基于优先级的排序*

![31_6](res/31_6.png)

*由write和putmsg产生的流消息类型*



## 31.3 getmsg和putmsg函数

```c++
#include <stropts.h>
int getmsg(int fd, struct strbuf *ctlptr, struct strbuf *dataptr, int *flagsp);
int putmsg(int fd, const struct strbuf *ctlptr, const struct strbuf *dataptr, int flags);

struct strbuf {
    int   maxlen;
    int   len;
    char *buf;
};
```

- `fd`文件描述符

- `ctlptr`控制信息

- `dataptr`数据

- `flagsp`标志

  | flagsp   | 说明         |
  | -------- | ------------ |
  | 0        | 普通消息     |
  | RS_HIPRI | 高优先级消息 |

接收/发送控制信息和数据。



## 31.4 getpmsg和putpmsg函数

```c++
#include <stropts.h>
int getpmsg(int fd, struct strbuf *ctlptr, struct strbuf *dataptr, int *bandp, int *flagsp);
int putpmsg(int fd, const struct strbuf *ctlptr, const struct strbuf *dataptr, int band, int flags);
```

- `fd`文件描述符
- `ctlptr`控制信息
- `dataptr`数据
- `bandp`优先级带
- `flagsp`标志

接收/发送带优先级的控制信息和数据。



## 31.5 ioctl函数

```c++
#include <stropts.h>
int ioctl(int fd, int request, ...);
```



## 31.6 TPI：传输提供者接口

```c++
TODO
```

*streams/tpi_daytime.h*

```c++
TODO
```

*streams/tpi_daytime.c*

```c++
TODO
```

*streams/tpi_bind.c*

```c++
TODO
```

*streams/tpi_connect.c*

```c++
TODO
```

*streams/tpi_read.c*

```c++
TODO
```

*stream/tpi_close.c*



## 31.7 小结



