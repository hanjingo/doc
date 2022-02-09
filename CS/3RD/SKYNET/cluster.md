[TOC]

# skynet集群



## harbor ID

skynet使用32bit的id（harbor id）来作为skynet上节点的唯一标识，其结构如下：

| 机器标识 | 服务节点id |
| -------- | ---------- |
| 8bit     | 24bit      |

- 每个skynet进程与其它进程通讯的部件称为harbor
- 同一进程的“机器标识”是一致的，通过比较“机器标识”就可以判断是本机节点还是远程节点
- 机器标识一般的取值范围为`[1, 255]`(取0表示单进程)
- 由于机器标识为8bit，所以集群中最多只可能有255个harbor

### 消息投递

节点消息投递有以下2种方式：

1. 根据harbor id直接投递
2. 把消息转发给harbor服务



## `master/slave`模式

`master/slave`模式下节点的harbor之间通过master来建立网络，master既可以是一个单独的进程也可以依附于某个进程（默认）。

master其实就是一个简单的内存key-value数据库；key表示节点的名字/ID，value存储节点harbor的地址信息。

一个5节点网络示意图：

![cluster_sample1](res\cluster_sample1.png)

- master连接所有slave节点
- slave节点的新增/减少/服务变更都是先通知master，再由master转发

### API

```
local harbor = require "skynet.harbor"
```

- `harbor.link(id)` 监控一个slave是否已断开（阻塞）；如果harbor id对应的slave正常，这个api将阻塞；当slave断开时，立即返回。
- `harbor.linkmaster()` 监控与master的连接是否正常。（这个api用于异常时的安全退出，当slave和master断开后，没有手段可以恢复）。
- `harbor.connect(id)` 监控一个slave是否已连接（阻塞）；如果harbor id对应的slave没有连接，这个api将阻塞直至它连上来。
- `harbor.queryname(name)` 查询全局名字或本地名字对应的服务地址（阻塞）；
- `harbor.globalname(name, handle)` 注册一个全局名字；如果handle为空，则注册自己。

**注意：`harbor.link(id)`和`barbor.linkmaster()`有一定开销，慎用！**

参考源码：

- `lualib/skynet/harbor.lua`
- `service/cslave.lua`

### 开启集群

1. 当选项`harbor`不为0时，意味着采用`master/slave`模式进行组网；此时必须配置选项：`address`，`master`等选项，启动slave服务；slave会根据`master`选项地址去连接master节点。
2. 当选项`standalone`不为NULL时，意味着启用master服务；master会监听`standalone`地址。

### 组网

```sequence
Title:master/slave组网示意图
slave3->master: “[H] slave_id slave_addr”
Note right of master: 确认本次握手是否有效
master->slave1: "[C] slave_id slave_addr"
master->slave2: "[C] slave_id slave_addr"
master-->slave3: "[W] 现有的slave数量"
Note right of master: 将slave3加入到slave组
slave1->slave3: 连接
slave3-->slave1: 接受连接
slave2->slave3: 连接
slave3-->slave2: 接受连接
```

参考源码：

- `service/cslave.lua`
- `service/cmaster.lua`

### harbor服务

组网完成后，slave之间主要通过`harbor服务`来进行消息通讯；其流程如下：

```sequence
Title:进程间harbor服务示意图
slave1的A服务-->slave1的harbor服务:进程内通讯
slave1的harbor服务-->slave2的harbor服务:跨进程通讯
slave2的harbor服务-->slave2的B服务:进程内通讯
```

harbor服务的功能包括以下：

- 主动/被动连接其他slave
- 注册新的服务名称
- 接管新到的套接字文件描述符
- ...

参考源码：

- `service/cslave.lua`
- `service-src/service_harbor.c`

### 缺点

1. 过于强调CAP理论中的CA(一致性，可用性)，对于P(分区容错性)的考虑较少，做出来的系统不够健壮（例如，master一旦挂了，整个服务gg）。
2. 弹性不够，如果一个slave意外退出，这个harbor id就被废弃；如果这时一个新的进程以相同的harbor id接入，无法保证新旧地址不重复；需要自己解决harbor id复用问题。
3. `master/slave`机制建立在：节点之间是可靠连接，节点之间不会断开。的前提上，这个前提很多时候不一定成立。

### 操作示例

1. 设置master的配置文件和slave的配置文件，参考`examples/config`，`examples/config_log`这两个文件

2. 启动两个lua进程

   ```sh
   # 启动master
   ./skynet examples/config
   
   # 启动slave
   ./skynet examples/config_log
   ```



## cluster模式

cluster模式兼容`master/slave`模式，cluster模式其实就是用更上层的api来实现一个节点信息查询系统；通过查询注册的节点以及对应的服务信息来远程调用，从而实现消息路由。

### API

- `cluster.call(node, address, ...)` 向一个节点上的一个服务提起一个请求，等待回应。
- `cluster.send(node, address, ...)` 向一个节点上的一个服务推送一条消息。
- `cluster.open(port)` 让当前节点监听一个端口。
- `cluster.reload([config])` 重新加载当前节点的网络配置，通过config表来取代文件配置。
- `cluster.proxy(node, address)` 为远程节点上的服务创建一个本地代理服务。
- `cluster.snax(node, name, address)` 向远程节点上的snax服务创建一个本地代理。
- `cluster.wait` 
- `cluster.register(name, address)` 在当前节点上为一个服务起一个字符串名字，之后可以用这个名字取代地址。
- `cluster.query(node, name)` 在远程节点上查询一个名字对应的地址。

### 开启

#### 方法一 配置文件

1. 编写cluster配置文件，配置集群内所有节点的名字和对应的监听端口；
2. 将此配置文件部署到所有节点

参考示例：`examples/clustername.lua`

#### 方法二 lua table

1. 使用`cluster.reload`来更新配置，lua table的配置优先级高于配置文件

参考示例：`examples/clustername.lua`

### 示例

方法一：

1. 编写配置文件，参考：`examples/config.c1`，`examples/config.c2`这2个文件

2. 启动一个节点，并注册服务信息

   ```sh
   ./skynet examples/config.c1
   ```

3. 启动另一个节点

   ```sh
   ./skynet examples/config.c2
   ```



## 参考

- [skynet API](https://github.com/cloudwu/skynet/wiki/APIList)
- [Skynet集群及RPC](https://blog.codingnow.com/2012/08/skynet_harbor_rpc.html)
- [skynet 的集群方案](https://blog.codingnow.com/2014/06/skynet_cluster.html)
- [skynet wiki #Cluster](https://github.com/cloudwu/skynet/wiki/Cluster)
- [skynet源码分析之master/salve集群模式](https://www.cnblogs.com/RainRill/p/8868401.html)
- [skynet cluster 模块的设计与编码协议](https://blog.codingnow.com/2017/03/skynet_cluster.html)
- [重新设计并实现了 skynet 的 harbor 模块](https://blog.codingnow.com/2014/06/skynet_harbor_redesign.html)

