# 摘要
Paxos算法运行在允许宕机故障的异步系统中，它利用大多数 (Majority) 机制保证了2F+1的容错能力，即2F+1个节点的系统最多允许F个节点同时出现故障，从而实现分布式锁功能;

# 详情
## 知识点
1. 角色分类(每个节点都同时具有3种角色)::
* 提议者(proposer):提出提案
* 决策者(acceptor):参与决策
* 学习者(learner):小弟，接收提案

2. 动作分类:
* Accept:接受
* Promise:允诺
* Choose:批准

## 前提 
1. 每个提案都有一个唯一id,大的优先级高;
2. id结构:序列号+服务id;

## 流程
paxos算法通过分为3阶段:
* 阶段一:proposer向acceptor发出一个id=n的提案准备(prepare)请求，acceptor收到请求后，如果acceptor收到过比n更大的id,回复这个id更大的提案给proposer；S否则采取承诺动作（Promise）:不再接收id<=n的请求;
* 阶段二:如果proposer没有收到比n更大的提案回复，向acceptor发出提案接受请求(Accept)动作;
* 阶段三:proposer向所有小弟(learner)发送决议结果；

## paxos算法的进化版:multi_paxos:
由于paxos效率较低且当有多个proposer时容易产生冲突和活锁(livelock)；所以在一般的工程项目里，
一开始会选举一个leader proposer,只有leader proposer可以提问,防止多个proposer锁死问题;
同时省略prepare阶段,只有一个proposer时无法锁死,由prepare保存一个全局最大提案id;