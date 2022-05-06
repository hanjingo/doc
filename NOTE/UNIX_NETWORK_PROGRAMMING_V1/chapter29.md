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
TODO
```

*udpcksum/udpcksum.h*

```c++
TODO
```

*udpcksum/main.c*

```c++
TODO
```

*udpcksum/pcap.c*

```c++
TODO
```

*udpcksum/senddnsquery-raw.c*

```c++
TODO
```

*udpcksum/udpwrite.c*

```c++
TODO
```

*udpcksum/udpread.c*

```c++
TODO
```

*udpcksum/cleanup.c*

### 29.7.1 例子

### 29.7.2 libnet输出函数

```c++
TODO
```

*udpcksum/senddnsquery-libnet.c*



## 29.8 小结



