# raft算法



## 摘要

raft(Reliable Replicated Redundant And Fault-Tolerant, 可靠，可复制，可冗余，可容错算法)

一种相对paxos更简单的算法;具体流程:raft会先选举出leader，leader完全负责replicated log的管
理。leader负责接受所有客户端更新请求，然后复制到follower节点，并在“安全”的时候执行这些
请求。如果leader故障，followes会重新选举出新的leader;




## 知识点
1. 节点的三个状态(同一时间只能由一个状态):
* leader(领导)
* fllower(跟随者)
* condidate(领导候选人)
**最大容错节点数量:(n-1)/2**



## 领导竞选

系统一启动，所有节点都是follower状态;如果一段时间没有收到leader的心跳,发起选举;  
1. 增加节点本地的current term, 切换到candidate状态
2. 投自己一票
3. 并行给其他节点发送RequestVote RPCs
4. 等待其他节点的回复:
	- 1. 收到投票（含自己的一票）结果,赢得选举，成为leader
	- 2. 被告知别人已当选，自行切换到follower
	- 3. 一段时间内没有收到投票结果,保持candidate状态，重新发出选举

注意点: 
1. 每个节点只能投一票
2. 选举人为奇数，防止票数相等
3. leader只能追加记录，无法覆盖删除记录

log replication:



## 链接

- [维基百科-raft](https://zh.wikipedia.org/wiki/Raft)

