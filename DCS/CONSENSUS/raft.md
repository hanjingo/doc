[TOC]

# Raft

`raft(Reliable Replicated Redundant And Fault-Tolerant, 可靠，可复制，可冗余，可容错算法)`；一种相对paxos更简单的算法。

具体流程：

1. raft会先选举出`leader`，`leader`完全负责`replicated log`的管理。
2. `leader`负责接受所有客户端更新请求，然后复制到`follower`节点，并在“安全”的时候执行这些
   请求。
3. 如果`leader`故障，`followes`会重新选举出新的`leader`。



## 节点的三个状态

* **Leader(领导)**
* **Follower(跟随者)**
* **Candidate(领导候选人)**
`最大容错节点数量 = (n-1)/2`

注意：同一时间只能有一个状态



## 领导选举

`Leader Election`，系统一启动，所有节点都是`follower`状态或者如果一段时间没有收到leader的心跳，由`Candidate`发起选举，流程如下：

1. 增加节点本地的`current term`, 切换到`candidate`状态
2. 投自己一票
3. 并行给其他节点发送`RequestVote RPCs`来拉票
4. 等待其他节点的回复:
	- 1. 收到投票（含自己的一票）结果，赢得选举，成为leader
	- 2. 被告知别人已当选，自行切换到`follower`
	- 3. 一段时间内没有收到投票结果,保持`candidate`状态，重新发出选举

**注意点: **

1. 每个节点只能投一票
2. 选举人为奇数，防止票数相等
3. `leader`只能追加记录，无法覆盖删除记录



## 记录复写

`Log Replication`，整个集群有`state machine`（复写状态机），可执行外来指令，记录复写的责任在领袖身上，流程如下：

1. `leader`接受指令，写入自己的记录中，将指令转发给`follower`；如果`follower`没有反应，重发。
2. 当`leader`收到过半`follower`写入确认的消息，就会把指令视为`committed`（已存储）。
3. 当`follower`发现指令状态变为`committed`时，运行该指令。
4. 当`leader`挂点时，集群的记录可能处于不一致的状态；新的`leader`会和每个`follower`比对记录，删除`follower`的不一致记录，复制`leader`记录给它。



## 安全性

`Safety`，Raft保证以下的安全性：

- 选举安全性

  `Election Safety`，每个任期最多只有一个`leader`

- 领袖附加性

  `Leader Append-Only`，`leader`不会修改或删除已有指令，只会追加新指令

- 记录符合性

  `Log Matching`，如果两个记录中的任期和序号一致，则序号较小的指令也一样

- 领袖完整性

  `Leader Completeness`，如果指令存储成功，后续的任期该指令不会变

- 状态安全性

  `State Machine Safety`，所有状态机运行的是同一条指令，`相同的初始状态+相同的输入=相同的结束状态`



## 链接

- [维基百科-raft](https://zh.wikipedia.org/wiki/Raft)
- [一文搞懂Raft算法](raft.md)

