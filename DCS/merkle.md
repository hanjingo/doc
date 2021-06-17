# Merkle树



## 概述

Merkle Tree，通常也被称作Hash Tree 哈希树，顾名思义，就是存储hash值的一棵树。Merkle树的叶子是数据块(例如，文件或者文件的集合)的hash值。非叶节点是其对应子节点串联字符串的hash。

2个节点成一对，可以根据任2个同级节点hash合并得到上级节点，最终回溯到root节点；任何底层数据的变动都会传递到其父节点，一直到树根。



## Merkle树结构

### 创建Merkle树

![merkle_create.png](res/merkle_create.png)

- Merkle树是一种树，大多数是二叉树，也可以多叉树，无论是几叉树，它都具有树结构的所有特点
- Merkle树的叶子节点的value是数据集合的单元数据或者单元数据HASH
- 非叶子节点的value是根据它下面所有的叶子节点值，然后按照Hash算法计算而得出的

### 检索数据块

![merkle_check.png](res/merkle_check.png)

复杂度：$\log (N)$

### 更新，插入和删除

todo

### 节点校验

例[<sup>[7]</sup>](#7)，对于一颗merkle tree：

![merkle_tree_check1.png](res/merkle_tree_check1.png)

如果要验证`slice2`的正确性，只需要拿到`hash1`,`h12`,`h02`这3个hash加上`root` hash，就可以验证了

![merkle_tree_check2.png](res/merkle_tree_check2.png)




## 源码分析

ipfs团队基于Merkle树构建了一种新的数据结构:Merkle DAG; 其与Merkle tree略有不同：

1. Merkle DAG不需要进行树的平衡操作，DAG可以存在单身节点
2. 非叶子节点允许包含数据，有时候小数据直接存在非叶子结点上

源码如下：

```C++

```


## 应用

### 零知识证明





## 参考
<div id="1"></div>
[1] [Merkle Tree 专利文档（英文）](res/US4309569.pdf)

<div id="2"></div>
[2] [`Merkle Tree（默克尔树）算法解析`](https://blog.csdn.net/wo541075754/article/details/54632929)

<div id="3"></div>
[3] [`区块链技术架构分析（3）-默克尔树（merkle tree）`](https://zhuanlan.zhihu.com/p/39271872)

<div id="4"></div>
[4] [百度百科-梅克尔树](https://baike.baidu.com/item/%E6%A2%85%E5%85%8B%E5%B0%94%E6%A0%91)

<div id="5"></div>
[5] [零知识证明-一种新型的Merkle树（Shrubs）](https://learnblockchain.cn/2019/10/15/Shrubs)

<div id="6"></div>
[6] [Merkle Tree and Zero Knowledge Proof](https://www.codenong.com/cs110403770/)

<div id="7"></div>
[7] [以太坊MPT原理，你最值得看的一篇](https://blog.csdn.net/ITleaks/article/details/79992072)
