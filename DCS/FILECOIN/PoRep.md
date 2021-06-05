# PoRep

PoRep (复制证明, Proof of Replication)，一种新型的存储证明；可以有效地避免：[女巫攻击(Sybil Attacks)]，[外包攻击(Outsourcing Attacks)], [生成攻击(Generation Attacks)]。



## 参考

- [Filecoin白皮书分析](https://www.jianshu.com/p/745d5d9be2d3)
- [Filecoin源码分析(2)--Filecoin的共识和出块原理解析](https://juejin.cn/post/6864831562882646024)



## 定义

复制证明：使得一个有效证明者P说服验证者V，数据D的一个独立物理副本R已经被存储在P上，且R专属于P。

PoRep协议的特征是多项式时间算法的元组：

$(Setup, Prove, Verify)$

- $PoRep.Setup(1^{\lambda}, D) \rightarrow R, S_p, S_v$，其中$S_p$和$S_v$是P和V的方案特定的设置变量，$\lambda$是一个安全参数。$PoRep.Setup$被用来生成副本$R$，并且给$P$和$V$必要的信息来运行$PoRep.Prove$和$PoRep.Verify$。一些方案可能需要证明人或者与第三方的相互作用来运算$PoRep.Setup$。
- $PoRep.Prove(S_p, R, c) \rightarrow \pi^c$，其中c是验证者$V$发出的一个随机挑战，并且$\pi^c$是证明者产生的对于数据$D$的特定副本$R$的访问权的证明。$PoRep.Prove$由$P$运行来为$V$生成$\pi^c$。
- $PoRep.Verify(Sv, c, \pi^c) \rightarrow \{0, 1\}$，用来检测证明是否正确。$PoRep.Verify$由$V$运行并且说服$V$：$P$是否存储了$R$。



## 步骤

```sequence
Title: 复制证明流程
Note left of 证明者: Setup
证明者->验证者: Prov
Note right of 验证者: Verify
```

### Seal操作

选用Seal操作(slow sequential computation)，的理由如下：

1. 使用伪随机排列PRP(pseudo-random permutation)算法生成原始数据D的一个唯一乱序副本R，每次存储商存储的都是一份唯一的R而不是原始数据D，解决了*女巫攻击*的问题；
2. Seal操作专门设计成非常耗时的顺序计算(sequential operation)，这个过程要比verify过程中的challenge-response通信要耗时很多，通常在10x~100x倍率(可以调整时间难度系数$\tau$)，使得Seal操作必须放在$PoRep.Setup()$中，而无法放在$PoRep.Prove()$操作中，如果存储商没有实际存储数据R而在$PoRep.Prove()$中使用$Seal$操作生成R，就会因为证明生成时间太长而很容易被验证为超时失败，这同时解决了*外包攻击*和*生成攻击*。

### Setup

通过密封操作生成一个副本，一个副本的树根和证明$\pi_{seal}$

- 输入
   - 证明者密钥对$(pk_p, sk_p)$
   - 证明者seal密钥$pk_{SEAL}$
   - 数据$D$

- 输出
  - 副本$R$
  - R的Merkle树根$rt$
  - 证明$\pi_{SEAL}$
  

流程：

1. 计算 $h_D := CRH(D)$
2. 计算 $R := Seal^{\tau}(D, sk_p)$
3. 计算 $rt := MerkleCRH(R)$
4. 设定 $\vec{x} := (pk_p, h_D, rt)$
5. 设定 $\vec{w} := (sk_p, D)$
6. 计算 $\pi_{SEAL} := SCIP.Prove(pk_{SEAL}, \vec{x}, \vec{w})$
7. 输出 $R, rt, \pi_{SEAL}$

### Prove

证明者受到来自验证者的随机挑战c，要求在以$rt$为树根的副本文件R的Merkle树中确认特定的叶子$R$； 证明者生成关于$R$的Merkle路径通往$rt$。

- 输入
  - 证明者存储证明密钥$pk_{POS}$
  - 副本$R$
  - 随机挑战$c$
- 输出
  - 证明$\pi_{POS}$
  

流程：

1. 计算 $rt := MerkleCRH(R)$
2. 计算路径 $path := 从rt到叶子R_c的Merkle路径$
3. 设定 $\vec{x} := (rt, c)$
4. 设定 $\vec{w} := (path, R_c)$
5. 计算 $\pi_{POS} := SCIP.Prove(pk_{POS}, \vec{x}, \vec{w})$
6. 输出 $\pi_{POS}$

### Verify

- 输入

  - 证明者公钥，$pk_p$
  - 验证者$SEAL$和$POS$密钥$vk_{SEAL}$, $vk_{POS}$
  - 数据D的哈希，$h_D$
  - 副本R的Merkle树根，$rt$
  - 随机挑战，$c$
  - 证明的元组，$(\pi_{SEAL}, \pi_{POS})$

- 输出

  比特b，在证明有效时为true

流程：

1. 设定 $\vec{x_1} := (pk_p, h_D, rt)$
2. 计算 $b_1 := SCIP.Verify(vk_{SEAL}, \vec{x_1}, \pi_{SEAL})$
3. 设定 $\vec{x_2} := (rt, c)$
4. 计算 $b_2 := SCIP.Verify(vk_{POS}, \vec{x_2}, \pi_{POS})$
5. 输出 $b_1 \bigwedge b_2$

注释：

- $CRH$：防碰撞的哈希
- $\vec{x}$：等待证明的NP声明
- $\vec{w}$：证人
