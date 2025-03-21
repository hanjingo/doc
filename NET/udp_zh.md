# UDP协议

[TOC]



## 数据报

### IPv4

![udp_ipv4_pack](res/udp_ipv4_pack.png)

IPv6类似。



## 头部

### IPv4

![udp_head_ipv4](res/udp_head_ipv4.png)

- `Source Port Number(源端口号)`

- `Destination Port Number(目的端口号)`

- `Length(长度)`

  理论上数据报的最大长度为65535字节（8个字节给UDP头部）；

  UDP编程接口允许应用程序指定每次一个网络的读操作完成时返回的最大字节数，如果接受的数据报操作这个指定大小会发生API`截断（truncate）`数据报行为。

- `Checksum(校验和)`

  ![udp_checksum](res/udp_checksum.png)

  **注意：当一个UDP/IPV4数据报穿过一个NAT时，不仅IP层头部的校验和要被修改，而且UDP伪头部的校验和也必须被正确地修改，因为IP层的地址和`/`或UDP层的端口号可能会改变。**

- `Payload Data(负载数据)`

### IPv6

![udp_head_ipv6](res/udp_head_ipv6.png)

- `Source IPv6 Address(源IPv6地址)`
- `Destination IPv6 Address(目的IPv6地址)`
- `Length(长度)`
- `Reserved(保留)`
- `Next Header(下一个UDP头)`

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

![udp_lite](res/udp_lite.png)

- `源端口号`

- `目的端口号`

- `校验和覆盖范围`

  这个字段给出被校验和覆盖的字节数（从UDP-Lite头部的第1个字节开始）。最小值是0，表示整个数据报都被覆盖。值`1~7`是无效的，因为头部总是要被覆盖的。UDP-Lite使用一个与UDP（17）不同的IPv4协议号（136）。IPv6在下一个头部字段中使用相同的值。

- `校验和`



## IP分片

### 最大数据报长度

**理论上**，一个IPv4数据报的最大长度是65535字节，这由IPv4头部的16位`总长度字段`决定。对于IPv6，在没有使用超长数据报的情况下，16位`负载长度`字段可允许65527字节的有效UDP负载。然而在现实中会受到一些限制。

UDP协议的实现提供了一个API套接字函数`setsocketopt()`来设置UDP数据报最大大小。

UDP编程接口允许应用程序指定每次一个网络的读操作完成时返回的最大字节数，如果接受的数据报操作这个指定大小会发生API`截断（truncate）`数据报行为。

### 重组超时

一个数据报的任何一个分片首先到达时，IP层就得启动一个计时器。如果不这样做的话，不能到达的分片可能会最终导致接收方用尽缓存，留下一种攻击机会。

### 示例

![udp_ip_split](res/udp_ip_split.png)

*一个带有2992字节UDP负载的UDP数据报被分片成三个UDP/IPv4分组（没有选项）。包含源和目的端口号的UDP头部只出现在第一个分片里（对防火墙和NAT来说，这是一个复杂因素）。分片由IPv4头部中的标识（Identification），分片偏移（Fragment Offset）和更多分片（More Fragments，MF）字段控制。*



## 安全

### IP分片相关攻击

1. `DoS攻击` 使用UDP的Dos攻击瞬间产生大量的流量，因为UDP不能管理它的流量发送率，从而对其它应用产生负面影响。
2. `放大(magnification)攻击` 攻击者发送小部分流量，从而致使其他系统产生更多的流量。
3. `IP分片攻击` 利用IPv4重组程序的漏洞，发送不带任何数据的分片，导致系统崩溃。
4. `泪滴（teardrop）攻击` 使用可使某些系统崩溃或严重受影响的`重叠分片偏移(Fragment Offset)`字段来精心构造一系列分片。



## 参考

[1] [美] Kevin R. Fall, [美] W. Richard Stevens.Tcp/ip详解.3ED

