# Redis源码分析-链表

[TOC]



## API

| 函数               | 作用                                                         | 时间复杂度                                      |
| ------------------ | ------------------------------------------------------------ | ----------------------------------------------- |
| listSetDupMethod   | 将给定的函数设置为链表的节点值复制函数                       | 复制函数可以通过链表的dup属性获得，$O(1)$       |
| listGetDupMethod   | 返回链表当前正在使用的节点值复制函数                         | $O(1)$                                          |
| listSetFreeMethod  | 将给定的函数设置为链表的节点值释放函数                       | 释放函数可以通过链表的free属性直接获得，$O(1)$  |
| listGetFree        | 返回链表当前正在使用的节点值释放函数                         | 对比函数可以通过链表的match属性直接获得，$O(1)$ |
| listGetMatchMethod | 返回链表当前正在使用的节点值对比函数                         | $O(1)$                                          |
| listLength         | 返回链表长度（包含了多少节点）                               | 链表长度可以通过链表的len属性直接获得，$O(1)$   |
| listFirst          | 返回链表的表头节点                                           | 表头节点可以通过链表的head属性直接获得，$O(1)$  |
| listLast           | 返回链表的表尾节点                                           | 表尾节点可以通过链表的tail属性直接获得，$O(1)$  |
| listPrevNode       | 返回给定节点的前置节点                                       | 前置节点可以通过节点的prev属性直接获得，$O(1)$  |
| listNextNode       | 返回给定节点的后置节点                                       | 后置节点可以通过节点的next属性直接获得，$O(1)$  |
| listNodeValue      | 返回给定节点目前正在保存的值                                 | 节点值可以通过节点的value属性直接获得，$O(1)$   |
| listCreate         | 创建一个不包含任何节点的新链表                               | $O(1)$                                          |
| listAddNodeHead    | 将一个包含给定值的新节点添加到给定链表的表头                 | $O(1)$                                          |
| listAddNodeTail    | 将一个包含给定值的新节点添加到给定链表的表尾                 | $O(1)$                                          |
| listInsertNode     | 将一个包含给定值的新节点添加到给定节点的之前或之后           | $O(1)$                                          |
| listSearchKey      | 查找并返回链表中包含给定值的节点                             | $O(N)$，N为链表长度                             |
| listIndex          | 返回链表在给定索引上的节点                                   | $O(N)$，N为链表长度                             |
| listDelNode        | 从链表中删除给定节点                                         | $O(N)$，N为链表长度                             |
| listRotate         | 将链表的表尾节点弹出，然后被弹出的节点插入到链表的表头，称为新的表头节点 | $O(1)$                                          |
| listDup            | 复制一个给定链表的副本                                       | $O(N)$，N为链表长度                             |
| listRelease        | 释放给定链表，以及链表中的所有节点                           | $O(N)$，N为链表长度                             |



## 定义

### 节点

```c
typedef struct listNode { // 链表节点
    struct listNode *prev; // 前置节点
    struct listNode *next; // 后置节点
    void *value;           // 节点的值
} listNode;
```

### 迭代器

```c
typedef struct listIter { // 链表迭代器
    listNode *next; // 指向下一个
    int direction;  // 方向
} listIter;

// 迭代器的方向
#define AL_START_HEAD 0 // 头
#define AL_START_TAIL 1 // 尾
```

### 链表

```c
typedef struct list { // 链表
    listNode *head;                     // 节点头
    listNode *tail;                     // 节点尾部
    void *(*dup)(void *ptr);            // 节点复制函数
    void (*free)(void *ptr);            // 节点释放函数
    int (*match)(void *ptr, void *key); // 节点值对比函数
    unsigned long len;                  // 节点数量
} list;
```



## 参考

### 文献

[1] 黄健宏.Redis设计与实现

