# UDP协议

[TOC]

## 数据报封装

### IPv4

![udp_ipv4_pack](res/udp_ipv4_pack.png)

### IPv6

TODO



## 头部

### IPv4

![udp_head_ipv4](res/udp_head_ipv4.png)

- `长度` 理论上数据报的最大长度为65535字节（8个字节给UDP头部）；

### IPv6

![udp_head_ipv6](res/udp_head_ipv6.png)



## 校验和

![udp_checksum](res/udp_checksum.png)

**注意：当一个UDP/IPV4数据报穿过一个NAT时，不仅IP层头部的校验和要被修改，而且UDP伪头部的校验和也必须被正确地修改，因为IP层的地址和`/`或UDP层的端口号可能会改变。**



## 参考

[1] [美] Kevin R. Fall, [美] W. Richard Stevens.Tcp/ip详解.3ED

