# LRU算法

[TOC]



`LRU(Least Recently Used)算法`就是一种缓存淘汰策略，这种算法认为最近使用的数据是热门数据，下一次很大概率会再次被使用；而最近很少被使用的数据，很大概率下一次不在用到；当缓存容量满的时候，优先淘汰最近很少使用的数据。

## 实现

### 双向链表

维护一个双向链表用于存放缓存数据，将最近使用的数据放在链表开头。

#### 插入

在每次插入数据前，如果key存在，更新value值并将其移到链表开头。

如果key不存在，则判断链表容量：

- 如果链表已满，删除最后一个元素，并将新节点插入链表开头
- 如果链表未满，将数据添加到链表的开头

#### 查询

查询一个数据时，遍历整个链表，如果能查询到对应的数据，则将其移动到链表头部；如果查询不到则返回null；



## GO的LRU Cache

```go
TODO
```



## 参考

TODO
