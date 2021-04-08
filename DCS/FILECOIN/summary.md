# filecoin总结
摘要:

- [参考](#参考)
- [简述](#简述)
- [要点](#要点)
- [付款方式](#付款方式)
- [惩罚](#惩罚)
  - [共识惩罚](#共识惩罚)
  - [存储惩罚](#存储惩罚)
- [证明](#证明)
  - [存储证明(Proof-of-Storage, PoS)](#存储证明(Proof-of-Storage, PoS))
  - [复制证明(Proof-of-Replication, PoRep)](#复制证明(Proof-of-Replication, PoRep))
  - [时空证明(PoST)](#时空证明(PoST))
  - [数据持有证明(Provable-Data-Possession, PDP)](#数据持有证明(Provable-Data-Possession, PDP))
  - [可检索证明(Proof-of-Retrievability, PoRet)](#可检索证明(Proof-of-Retrievability, PoRet))
  - [工作量证明(Proof-of-Work, PoW)](#工作量证明(Proof-of-Work, PoW))
  - [空间证明(Proof-of-Space, PoSpace)](#空间证明(Proof-of-Space, PoSpace))
- [架构](#架构)
  - [存储流程](#存储流程)
  - [消息流程](#消息流程)



## 参考

- [filecoin技术架构分析之一：filecoin概念](https://blog.csdn.net/qq_21393091/article/details/88072946)
- [filecoin技术架构分析之二：filecoin通用语言理解](https://blog.csdn.net/qq_21393091/article/details/88073022)
- [filecoin技术架构分析之三：filecoin开发网络使用](https://blog.csdn.net/qq_21393091/article/details/88073071)
- [filecoin技术架构分析之四：filecoin源码顶层架构分析](https://blog.csdn.net/qq_21393091/article/details/88073352)
- [filecoin技术架构分析之五：filecoin源码分析之协议层心跳协议](https://blog.csdn.net/qq_21393091/article/details/88139537)
- [FILECOIN挖矿原理](https://blog.csdn.net/vskovsko/article/details/111468620)
- [读懂区块链之零知识证明（zk-SNARK）](https://www.jianshu.com/p/7b772e5cdaef?utm_source=oschina-app)
- [filecoin工作原理](https://blog.csdn.net/kk3909/article/details/104814067)
- [Filecoin 系列01-Filecoin 工作原理](http://www.r9it.com/20190226/how-filecoin-work.html)



## 简述

filecoin采用存储证明，存储能力越强，挖到区块的概率越大；

filecoin市场存在着4个角色：
- 存储矿工：用来存储数据
- 检索矿工：用来提供检索，本身不一定有数据
- 存储客户端：要存数据的用户
- 检索客户端：要获取数据的用户



## 要点

1. Sectors: 扇区，矿工提供存储空间的最小单元，也就是说在我们创建矿工的时候抵押存储空间大小必须是 Sector 的整数倍。
2. Pieces: 数据单元，是 Filecoin 网络中最小存储单位，每个 Pieces 大小为 512KB， Filecoin 会把大文件拆分成很多个 Pieces, 交给不同的矿工存储。
3. AllocationTable: 数据分配追踪表，它记录了每个 Pieces 和 Sector 的对应关系，如某个 Pieces 存储在了哪个 Sector. 当某个 Sector 被存满(Fill)了之后，系统将会把该 Sector 封存(Sealing the Sector)，然后生成存储证明，这是一个缓慢的操作
4. Pledge: 抵押，矿工必须需要向 Filecoin 网络抵押 FIL 代币才能才能开始接受存储市场的订单。
5. Orders: 订单，系统中有两种订单，一种是竞价订单(bid order), 由客户发起，另一种是要价订单(ask order), 由矿工发起。
6. Orderbook: 订单簿，也就是订单列表，包括 bid order 和 ask order，系统根据订单列表进行自动撮合匹配交易



## 付款方式

1. 存储付款；并不是存储了数据就马上收款，而是分次小额支付，每完成一次挑战，就发一部分奖金
2. 检索付款；立即收款



## 惩罚

### 共识惩罚
在相同的高度提交两个以及以上的区块，以提高自己的 Weight（出块权重）

惩罚力度：当前矿工的所有 pledge collateral （抵押币）全部扣除，storage power(存储算力) 清零，并且均不可恢复， 即使作弊者重新抵押，该矿工也无法再产生新的区块

### 存储惩罚
1. 未能按时提交 PoSt（时空证明）

对于那些逾期提交 PoST 的矿工，只需加纳一定数量的罚金，具体数量通过调用 ComputeLateFee(minerPower, numLate) 函数计算得出，当前矿工的存储算力并不会受到影响

2. 提交非法的 PoST（作弊）
对于通过 generation attack （生成攻击）生成 PoST 的矿工，处罚就是致命性的， 除了扣除所有的抵押代币，存储算力清零之外，处于这种状态的矿工，即使被选取为出块矿工，它产生的任何区块都将无效。



## 证明

### 存储证明(Proof-of-Storage, PoS)

利用存储空间进行性的证明。

### 复制证明(Proof-of-Replication, PoRep)

新的PoS,证明数据的一个单独的拷贝已经在一个特定的扇区内创建成功,主要用来防以下的攻击:

- 女巫攻击(Sybil Attack)
- 外部数据源攻击(Outsourcing Attack)
- 生成攻击(Generation Attack)

### 时空证明(PoST)
证明一定数量的已封装的扇区，在一定的时间范围内存在于指定的存储空间中;它要求存储矿工每隔一段时间来发送一次存储证明到区块链网络

### 数据持有证明(Provable-Data-Possession, PDP)

用户发送数据给旷工进行存储，矿工证明数据已经被自己存储，用户可以重复检查矿工是否还在存储自己的数据

### 可检索证明(Proof-of-Retrievability, PoRet)

和PDP过程比较类似，证明矿工存储的数据是可以用来查询的

### 工作量证明(Proof-of-Work, PoW)

证明者向检验者证明自己消耗了一定的资源；

### 空间证明(Proof-of-Space, PoSpace)

证明者向检验者证明自己消耗了一定的存储;



## 架构
### 存储流程
```sequence
participant Client
participant Market
participant Miner


Client->Market:提交出价单(包含存储时长，副本份数)
Market->Market:检查出价单是否合法
Miner->Market:提交竞价单
Market->Market:检查竞价单是否合法
Market->Market:撮合订单
Market->Miner:接单成功，锁定存储空间
Market->Client:订单成交
Client->Miner:发送文件给矿机
Miner->Client:提供复制证明(PoRep)
Miner->Market:定期发送Post(时空证明)...

```

### 消息流程
```sequence
participant Network
participant Commands
participant Protocols
participant Internal Api
participant Core

Network->Protocols:storege protocol
Network->Protocols:mining protocol
Network->Protocols:retrieval protocol
Network->Protocols:heart protocol
Commands->Protocols:cmd
Protocols->Internal Api:Core Api
Protocols->Internal Api:Porcelain
Protocols->Internal Api:Plumbing
Internal Api->Core:Message Pool
Internal Api->Core:Chain Store
Internal Api->Core:Processor
Internal Api->Core:Block Service
Internal Api->Core:Wallet
```

Network:

- libp2p

Commands:

- HTTP REST / API

Protocols:

- 挖矿协议(mining protocol)
- 存储协议(storege protocol)
- 检索协议(retrival protocol)
- 心跳协议(heartbeat protocol)