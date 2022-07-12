# UDP协议

[TOC]



## 数据报

### IPv4

![udp_ipv4_pack](res/udp_ipv4_pack.png)

### IPv6

TODO



## 头部

### IPv4

![udp_head_ipv4](res/udp_head_ipv4.png)

- `源端口号`

- `目的端口号`

- `长度`

  理论上数据报的最大长度为65535字节（8个字节给UDP头部）；

  UDP编程接口允许应用程序指定每次一个网络的读操作完成时返回的最大字节数，如果接受的数据报操作这个指定大小会发生API`截断（truncate）`数据报行为。

- `校验和`

  ![udp_checksum](res/udp_checksum.png)

  **注意：当一个UDP/IPV4数据报穿过一个NAT时，不仅IP层头部的校验和要被修改，而且UDP伪头部的校验和也必须被正确地修改，因为IP层的地址和`/`或UDP层的端口号可能会改变。**

- `负载数据`

### IPv6

![udp_head_ipv6](res/udp_head_ipv6.png)

- `源IPv6地址`
- `目的IPv6地址`
- `长度`

**注意：**

1. 在IPv6里，最小MTU大小是1280字节（与IPv4要求的需要所有主机支持的最小大小576字节不同）；
2. IPv6支持超长数据报（>65535字节的分组）。



## Teredo

![udp_teredo](res/udp_teredo.png)

*Teredo，一种IPv6过渡机制，在UDP/IPv4数据报的负载区中封装IPv6数据报和可选的追踪符，以使IPv6流量能经过只支持IPv4的基础设施。服务器帮助客户机获得一个IPv6地址并决定它们的映射地址和端口号。如果需要，中继器在Teredo，6to4及原生IPv6客户机间转发流量*

### IPv4封装

![udp_teredo_ipv4](res/udp_teredo_ipv4.png)

- `追踪符`

  Teredo追踪符被携带在封装于UDP/IPv4数据报里的IPv6负载之后。每个追踪符都有一个类型值，名称和对应的诠释。某些情况下，长度值是一个常数：

  | 类型 | 长度    | 名称               | 用途                | 备注                                                 |
  | ---- | ------- | ------------------ | ------------------- | ---------------------------------------------------- |
  | 0x00 | 保留    | 未分配             | 未分配              | 未分配                                               |
  | 0x01 | 0x04    | 随机数（Nonce）    | SNS，UP，PP，SP，HP | 32位的随机数，用于防治重放攻击                       |
  | 0x02 | 保留    | 未分配             | 未分配              | 未分配                                               |
  | 0x03 | [8, 26] | 替换地址           | HP                  | 位于同一个NAT后面的Teredo客户机使用的额外的地址/端口 |
  | 0x04 | 0x04    | ND（邻居发现）选项 | SLR                 | 允许NAT使用直接气泡（带NS消息）来进行更新            |
  | 0x05 | 0x02    | 随机端口           | PP                  | 发送方的预测映射端口                                 |


### IPv6封装

![udp_teredo_ipv6](res/udp_teredo_ipv6.png)



## UDP-Lite

TODO



## IP分片

### 重组超时

一个数据报的任何一个分片首先到达时，IP层就得启动一个计时器。如果不这样做的话，不能到达的分片可能会最终导致接收方用尽缓存，留下一种攻击机会。

### 示例

![udp_ip_split](res/udp_ip_split.png)

*一个带有2992字节UDP负载的UDP数据报被分片成三个UDP/IPv4分组（没有选项）。包含源和目的端口号的UDP头部只出现在第一个分片里（对防火墙和NAT来说，这是一个复杂因素）。分片由IPv4头部中的标识（Identification），分片偏移（Fragment Offset）和更多分片（More Fragments，MF）字段控制*



## 参考

[1] [美] Kevin R. Fall, [美] W. Richard Stevens.Tcp/ip详解.3ED

