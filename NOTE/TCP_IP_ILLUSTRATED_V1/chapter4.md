# 第四章 地址解析协议(ARP)

[返回目录](README.md)



## 引言

`ARP（Address Resolution Protocol）`可以用来将IP地址映射为MAC地址。



## ARP缓存

每个主机上都有一个ARP高速缓存，存放了最近Internet地址到硬件地址之间的映射记录;可以使用以下命令查看缓存:

```sh
arp -a
```



## ARP帧格式

帧结构

| DST  | SRC  | 长度或类型 | 硬件类型 | 协议类型 | 硬件大小 | 协议大小 | Op   | 发送端硬件地址 | 发送端协议地址 | 目的端硬件地址 | 目的端协议地址 | 填充 | FCS  |
| ---- | ---- | ---------- | -------- | -------- | -------- | -------- | ---- | -------------- | -------------- | -------------- | -------------- | ---- | ---- |
| 6    | 6    | 2          | 2        | 2        | 1        | 1        | 2    | 6              | 4              | 6              | 4              | 18   | 4    |

- MAC（以太网）头部:
  - DST: 目的端地址，主机号全为1表示广播地址。
  - SRC: 发送端地址
  - 长度或类型: 标识后面数据的类型。ARP的该字段为0x0806。

- 固定大小:

  - 硬件类型: 硬件地址的类型。

    - 1表示以太网地址；
  - 协议类型: 要映射的协议地址类型。
    - 0x0800表示ip地址
  - 硬件大小: 硬件地址长度(字节)。ARP的该字段为6；
  - 协议大小: 协议地址长度(字节)。ARP的该字段为4；
  - Op: 操作字段。
    - 1: ARP请求
    - 2: ARP应答
    - 3: RARP请求
    - 4: RARP应答


- 可变大小：
  - 发送端硬件地址
  - 发送端协议地址
  - 目的端硬件地址
  - 目的端协议地址
- 填充（不按比例）
- FCS



## ARP代理

如果ARP请求是从一个网络的主机发往另一个网络上的主机，那么连接这两个网络的路由器就可以回答该请求，这个过程称作委托ARP或ARP代理(Proxy ARP)；



## 免费ARP

gratuitous ARP(免费ARP): 在系统引导期时发送ARP查询自己的IP地址。

免费的ARP有2个作用:

1. 一个主机可以通过它来确定另一个主机是否设置了相同的ip地址。
2. 如果发送免费ARP的主机正好改变了硬件地址，那么这个分组就可以使其它主机高速缓存中旧的硬件地址进行相应的更新。



## ARP命令

arp 

- -a: 显示ARP高速缓存中的所有内容
- -d: 删除ARP高速缓存中的某一项内容
- -s: 增加高速缓存中的内容



## 使用ARP设置一台嵌入式设备的IPv4地址

嵌入式设备设置网络配置的方式：

1. 使用DHCP自动分配地址和其它信息
2. 使用ARP设置IPv4地址（使用 `arp -s` 命令）



## 与ARP相关的攻击

1. 假扮ARP代理主机