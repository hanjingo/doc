# Paxos

<!-- vim-markdown-toc GFM -->

* [角色分类](#角色分类)
* [动作分类](#动作分类)
* [前提](#前提)
* [流程](#流程)
* [Paxos算法的进化版Multi-Paxos](#paxos算法的进化版multi-paxos)
* [参考](#参考)

<!-- vim-markdown-toc -->



Paxos算法运行在允许宕机故障的异步系统中，它利用大多数 (Majority) 机制保证了`2F+1`的容错能力，即`2F+1`个节点的系统最多允许`F`个节点同时出现故障，从而实现分布式锁功能;



## 角色分类

- **Proposer**

  提议者，接入和协调；收到客户端请求后，发起二阶段提交，进行共识协商。

- **Acceptor**

  接受者，投票协商和存储数据；对提议的值进行投票，并接受达成共识的值，存储保存。

- **Learner**

  学习者（小弟），存储数据；不参与共识协商，只接受达成共识的值，存储保存。

**注意：一个节点允许身兼数职（可以同时为多种角色）**



## 动作分类

- **Accept**

  接受

- **Promise**

  允诺

- **Choose**

  批准



## 前提 

1. 每个提案都有一个唯一id，大的优先级高；
2. id结构：`序列号+服务id`；



## 流程

Paxos算法的流程如下:
1. `Proposer`向`Acceptor`发出一个`id=n`的提案准备请求。
2. `Acceptor`收到请求后，如果`Acceptor`收到过比n更大的id，回复这个id更大的提案给`Proposer`；否则采取承诺动作（`Promise`）不再接收`id<=n`的请求。
3. 如果`Proposer`没有收到比n更大的提案回复，向`Acceptor`发出提案接受请求(`Accept`)动作;
4. `Proposer`向所有`Learner`发送决议结果；

```sequence

```



## Paxos算法的进化版Multi-Paxos

由于paxos效率较低且当有多个`Proposer`时，容易产生冲突和活锁(`livelock`)；

所以在一般的工程项目里，
一开始会选举一个`Leader Proposer`，只有`Leader Proposer`可以提问，防止多个`Proposer`锁死问题;

同时省略`Prepare`阶段，只有一个`Proposer`时无法锁死，由`Prepare`保存一个全局最大提案`id`；



## 参考

- [维基百科-Paxos算法](https://zh.wikipedia.org/wiki/Paxos%E7%AE%97%E6%B3%95)
- [Paxos算法详解（一）](https://blog.csdn.net/lin819747263/article/details/106313936)
