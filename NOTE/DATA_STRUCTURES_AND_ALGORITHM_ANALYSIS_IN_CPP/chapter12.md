# 第12章 高级数据结构及其实现

[TOC]



## 12.1 自顶向下伸展树

![12_1](res/12_1.png)

*自顶向下伸展旋转：单旋转，一字形旋转和之字形旋转*

![12_2](res/12_2.png)

*简化的自顶向下的之字形旋转*

![12_3](res/12_3.png)

*自顶向下伸展的最后整型*

![12_4](res/12_4.png)

*自顶向下伸展的各步（访问上面树中的19）*

例，伸展树，类接口，构造函数和析构函数：

```c++
template <typename Comparable>
class SplayTree
{
public:
    SplayTree() {
        nullNode = new BinaryNode;
        nullNode->left = nullNode->right = nullNode;
        root = nullNode;
    }
    ~SplayTree() {
        makeEmpty();
        delete nullNode;
    }
    SplayTree(const SplayTree& rhs);
    const SplayTree& operator=(const SplayTree& rhs);

private:
    struct BinaryNode {};

    BinaryNode *root;
    BinaryNode *nullNode;

    void rotateWithLeftChild(BinaryNode * & k2);
    void rotateWithRightChild(BinaryNode * & k1);
    void splay(const Comparable& x, BinaryNode * & t) {
        BinaryNode *leftTreeMax, *rightTreeMin;
        static BinaryNode header;

        header.left = header.right = nullNode;
        leftTreeMax = rightTreeMin = &header;

        nullNode->element = x;

        for (; ;)
            if (x < t->left->element) {
                if (x < t->left->element) 
                    rotateWithLeftChild(t);
                if (t->left == nullNode)
                    break;
                // Link Right
                rightTreeMin->left = t;
                rightTreeMin = t;
                t = t->left;
            }
            else if (t->element < x) {
                if (t->right->element < x)
                    rotateWithRightChild(t);
                if (t->right == nullNode)
                    break;
                // Link Left
                leftTreeMax->right = t;
                leftTreeMax = t;
                t = t->right;
            }
            else
                break;

        leftTreeMax->right = t->left;
        rightTreeMin->left = t->right;
        t->left = header.right;
        t->right = header.left;
    };

    void insert(const Comparable& x) {
        static BinaryNode *newNode = NULL;
        if (newNode == NULL)
            newNode = new BinaryNode;
        newNode->element = x;

        if (root == nullNode) {
            newNode->left = newNode->right = nullNode;
            root = newNode;
        } else {
            splay(x, root);
            if (x < root->element) {
                newNode->left = root->left;
                newNode->right = root;
                root->left = nullNode;
                root = newNode;
            } else {
                if (root->element < x) {
                    newNode->right = root->right;
                    newNode->left = root;
                    root->right = nullNode;
                    root = newNode;
                } 
                else
                    return; 
            }
            newNode = NULL;
        }
    }
};
```



## 12.2 红黑树

红黑树是具有下列性质的二叉查找树：

1. 每一个结点或者红色，或者黑色；
2. 根是黑色的；
3. 如果一个结点是红色的，那么它的子结点必须是黑色的；
4. 从一个结点到一个NULL指针的每一条路径都必须包含相同数目的黑色结点。

![12_9](res/12_9.png)

*红黑树的例子（插入序列为：10, 85, 15, 70, 20, 60, 30, 50, 65, 80, 90, 40, 5, 55）*

例，自顶向下的删除过程和makeEmpty：

```c++
void remove(const Comparable& x)
{
    BinaryNode *newTree;
    splay(x, root);
    if (root->element != x)
        return;
    if (root->left == nullNode)
        newTree = root->right;
    else
    {
        newTree = root->left;
        splay(x, newTree);
        newTree->right = root->right;
    }
    delete root;
    root = newTree;
}

void makeEmpty()
{
    while(!isEmpty())
    {
        findMax();
        remove(root->element);
    }
}
```

### 12.2.1 自底向上插入

![12_10](res/12_10.png)

*如果S是黑色的，则单旋转和之字形旋转有效*

### 12.2.2 自顶向下红黑树

![12_11](res/12_11.png)

*颜色翻转：只有当X的父节点是红色的时候才继续旋转*

![12_12](res/12_12.png)

*将45插入到上图（红黑树的例子）中的树上*

### 12.2.3 自顶向下删除

![12_17](res/12_17.png)

*当X是一个左儿子并有两个黑色的儿子时的三种情形*



## 确定性跳跃表

TODO