# 第五章 关联式容器

## 树的导览

### 二叉搜索树

节点插入:

![](res/5-5.png)

节点删除:

![](res/5-6.png)

### 平衡二叉搜索树(balanced binary search tree)

### AVL tree(Adelson-Velskii-Landis tree)

### 单旋转(Single Rotation)

### 双旋转(Double Rotation)

---

## RB-tree (红黑树)

RB-tree必须满足以下规则：

1. 每个节点不是红色就是黑色
2. 根节点为黑色
3. 如果节点为红，其子节点必须为黑
4. 任一节点至NULL（树尾端）的任何路径，所含的黑节点数必须相同

### 插入节点

### 一个由上而下的程序

### RB-tree的节点设计

### RB-tree的迭代器

### RB-tree的构造与内存管理

RB-tree的构造方式有2种:

1. 以现有的RB-tree复制一个新的RB-tree
2. 产生一棵空空如也的树

### RB-tree的元素操作

- insert_equal
- insert_unique
- find

---

## set



---