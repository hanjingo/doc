# go-libp2p



## 建立host

`New(ctx context.Context, opts ...Option) (host.Host, error)`

建立host主机，可以自定义构建选项或默认选项

### Option

`type Option func(cfg *Config) error`

- 默认选项
  - 如果未提供传输和侦听地址，则节点将侦听多重地址`/ip4/0.0.0.0/tcp/0`和`/ip6/::/tcp/0`
  - 如果未提供传输选项，则节点使用 TCP 和 websocket 传输协议
  - 如果未提供多路复用器配置，则默认情况下将节点配置为使用`yamux/1.0.0`和`mplux/6.7.0`流连接多路复用器
  - 如果未提供安全传输，则主机使用 go-libp2p 的`secio`加密传输来加密所有流量
  - 如果未提供对等身份，则会生成随机 RSA 2048 密钥对并从中生成新身份
  - 如果未提供 peertore，则使用空的 peerstore 初始化主机
- 自定义选项





