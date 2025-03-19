English | [中文版](binary_tree_zh.md)

# Binary Tree

[TOC]



A binary tree is a tree in which no node can have more than two children. A property of a binary tree that is sometimes important is that the depth of an average binary tree is considerably smaller than $N$.



## Generic binary tree

![binary_tree_struct](res/binary_tree_struct.png)

*Generic binary tree*

```c++
struct BinaryNode
{
  Object     element;
  BinaryNode *left;
  BinaryNode *right;
};
```



## Expression Tree

### Implement

An `expression tree`. The leaves of an expression tree are `operands`, such as constants or variable names, and the other nodes contain `operators`.

![expression_tree](res/expression_tree.png)

Expression tree for $(a+b*c)+((d*e+f)*g)$

### Example

Constructing an Expression Tree:

1. suppose the input is: `a b + c d e + * *`

2. The first two symbols are operands, so we create one-node trees and push pointers to them onto a stack

   ![expression_tree_examp1_1](res/expression_tree_examp1_1.png)

3. A `+` is read, so two pointers to trees are popped, a new tree is formed, and a pointer to it is pushed onto the stack

   ![expression_tree_examp1_2](res/expression_tree_examp1_2.png)

4. c, d, and e are read, and for each a one-node tree is created and a pointer to the corresponding tree is pushed onto the stack

   ![expression_tree_examp1_3](res/expression_tree_examp1_3.png)

5. a `+` is read, so two trees are merged

   ![expression_tree_examp1_4](res/expression_tree_examp1_4.png)

6. A `*` is read, so we pop two tree pointers and form a new tree with a `*` as root

   ![expression_tree_examp1_5](res/expression_tree_examp1_5.png)

7. The last symbol is read, two trees are merged, and a pointer to the final tree is left on the stack

   ![expression_tree_examp1_6](res/expression_tree_examp1_6.png)



## The Search Tree ADT - Binary Search Trees

The average depth of a binary search tree turns out to be $O(log N)$, we generally do not need to worry about running out of stack space.

```c++
// binary search tree
template <typename Comparable>
class BinarySearchTree
{
public:
    BinarySearchTree();
    BinarySearchTree(const BinarySearchTree& rhs);
    ~BinarySearchTree() {
        makeEmpty();
    };

private:
    struct BinaryNode
    {
        Comparable element;
        BinaryNode* left;
        BinaryNode* right;

        BinaryNode(const Comparable& theElement, BinaryNode* lt, BinaryNode* rt)
            : element(theElement), left(lt), right(rt) {}
    };

    BinaryNode* root;
};
```

### insert

```c++
void insert(const Comparable& x, BinaryNode* & t) const {
        if (t == NULL)
            t = new BinarySearchTree(x, NULL, NULL);
        else if (x < t->element)
            insert(x, t->left);
        else if (t->element < x)
            insert(x, t->right);
        else
            ...
};
```

### delete

```c++
void remove(const Comparable& x, BinaryNode* & t) const {
        if (t == NULL)
            return;
        if (x < t->element)
            remove(x, t->left);
        else if(t->element < x)
            remove(x, t->right);
        else if(t->left != NULL && t->right != NULL)
        {
            t->element = findMin(t->right)->element;
            remove(t->element, t->right);
        }
        else
        {
            BinaryNode* oldNode = t;
            t = (t->left != NULL) ? t->left : t->right;
            delete oldNode;
        }
};
```

### search

```c++
    BinaryNode* findMin(BinaryNode* t) const {
        if (t == NULL)
            return NULL;
        if (t->left == NULL)
            return t;
        return findMin(t->left);
    };

    BinaryNode* findMax(Binarynode* t) const {
        if (t != NULL)
            while(t->right != NULL)
                t = t->right;
        return t;
    };
```

### Average-Case Analysis

The sum of the depths of all nodes in a tree is known as the `internal path length`.

**Result** The average depth over all nodes in a tree is $O(logN)$ on the assumption that all insertion sequences are equally likely.

**Proof** Let $D(N)$ be the internal path length for some tree $T$ of $N$ nodes. $D(1) = 0$. An N-node tree consists of an $i$-node left subtree and an $(N - i - 1)$-node right subtree, plus a root at depth zero for $0 \leq i < N$. $D(i)$ is the internal path length of the left subtree with respect to tis root. In the main tree, all these nodes are one level deeper. The same holds for the right subtree. Thus, we get the recurrence: 
$$
D(N) = D(i) + D(N-i-1) + N - 1
$$
, If all subtree sizes are equally likely, which is true for binary search trees (since the subtree size depends only on the relative rank of the first element inerted into the tree), but not binary trees, then the average value of both $D(i)$ and $D(N - i - 1)$ is $(1/N) \sum_{j=0}^{N-1} D(j)$. This yields:
$$
D(N) \frac{2}{N} \left[ \sum_{j=0}^{N-1} D(j)\right] + N - 1
$$
, obtaining an average value of $D(N) = O(NlogN)$. Thus, the expected depth of any node is $O(logN)$.



## AVL Trees

An AVL (Adelson-Velskii and Landis) tree is a binary search tree with a `balance condition`, it requires:

1. the depth of the tree is $O(logN)$.
2. the left and right subtrees have the same height.

```c++
struct AvlNode
{
    Comparable element;
    AvlNode*   left;
    AvlNode*   right;
    int        height;

    AvlNode(const Comparable& theElement, AvlNode* lt, AvlNode* rt, int h = 0)
        : element(theElement), left(lt), right(rt), height(h){};

    int height(AvlNode* t) const 
    {
        return t == NULL ? -1 : t->height;
    }

    void insert(const Comparable& x, AvlNode* &t)
    {
        if (t == NULL)
            t = new AvlNode(x, NULL, NULL);
        else if(x < t->element)
        {
            insert(x, t->left);
            if (height(t->left) - height(t->right) == 2)
                if (x < t->left->element)
                    rotateWithLeftChild(t);
                else
                    doubleWithLeftChild(t);
        }
        else if(t->element < x)
        {
            insert(x, t->right);
            if (height(t->right) - height(t->left) == 2)
                if (t->right->element < x)
                    rotateWithRightChild(t);
                else
                    doubleWithRightChild(t);
        }
        else
            // TODO
        t->height = max(height(t->left), height(t->right)) + 1;
    }

    void rotateWithLeftChild(AvlNode* & k2)
    {
        AvlNode *k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = max(height(k2->left), height(k2->right)) + 1;
        k1->height = max(height(k1->left), k2->height) + 1;
        k2 = k1;
    }

    void doubleWithLeftChild(AvlNode * & k3)
    {
        rotateWithRightChild(k3->left);
        rotateWithLeftChild(k3);
    }
};
```

### Single Rotation

![avl_single_rotation](res/avl_single_rotation.png)

*Single rotation to fix*

### Double Rotation

![avl_double_rotation](res/avl_double_rotation.png)

*Left-right double rotation to fix*

Example:

1. Insert 15

   ![avl_example1](res/avl_example1.png)
   
2. Insert 14

   ![avl_example2](res/avl_example2.png)

3. Insert 13

   ![avl_example3](res/avl_example3.png)

4. Insert 12

   ![avl_example4](res/avl_example4.png)

5. Insert 11，10，8

   ![avl_example5](res/avl_example5.png)

6. Insert 9

   ![avl_example6](res/avl_example6.png)



## Splay Trees

**Splay tree** that guarantees that any $M$ consecutive tree operations starting from an empty tree take at most $O(Mlog\ N)$ time.

Generally, when a sequence of $M$ operations has total worst-case running time of $O(Mf(N))$, we say that the **amortized** running time is $O(f(N))$.



## B-Trees

A B-tree of order $M$ is an $M$-ary tree with the following properties:

1. The data items are stored at leaves.
2. The nonleaf nodes store up to $M - 1$ keys to guide the searching; key $i$ represents the smallest key in subtree $i + 1$.
3. The root is either a leaf or has between two and $M$ children.
4. All nonleaf nodes (except the root) have between $\lceil M / 2 \rceil$ and $M$ children.
5. All leaves are at the same depth and have between $\lceil L / 2 \rceil$ and $L$ data items, for some $L$ (the determination of $L$ is described shortly).

reference to [Balance Tree](balance_tree.md)



## Red Black Tree

reference to [Red Black Tree](rb_tree.md)



## Sets and Maps in the Standard Library

### set

The `set` is an ordered container that does not allow duplicates.

The unique operations required by the `set` are the abilities to insert, remove, and perform a basic search (efficiently).

The STL defines insert/erase function:

```c++
pair<iterator, bool> insert(const Object& x);
pair<iterator, bool> insert(iterator hint, const Object& x);

int erase(const Object& x);
iterator erase(iterator itr);
iterator erase(iterator start, iterator end);
```

For example:

```c++
set<int> s;
for (int i = 0; i < 1000000; i++)
  s.insert(s.end(), i);
```

### Maps

A `map` is used to store a collection of ordered entries that consists of keys and their values. Keys must be unique, but several keys can map to the same values. Thus values need not be unique.

Consequently, the underlying implementation is a balanced binary search tree. Typically, an AVL tree is not used; instead, top-down red-black trees are often used:

```c++
map<string, double> salaries;
salaries["Pat"] = 75000.00;

map<string, double>::const_iterator itr;
itr = salaries.find("Chris");
if (itr == salaries.end())
	cout << "end" << endl;
else
  cout << itr->second << endl;
```

The hard part is efficiently advancing to the next node. There are several possible solutions, some of which are lsited here:

1. When the iterator is constructed, have each iterator store as its data an array containing the `set` items. This doesn't work: It makes it impossible to efficiently implement any of the routines that return an iterator after modifying the `set`, such as some of the versions of `erase` and `insert`.
2. Have the iterator maintain a stack storing nodes on the path to the current node. With this information, one can deduce the next node in the iteration, which is either the node in the current node's right subtree that contains the minimum item or the nearest ancestor that contains the current node in its left subtree. This makes the iterator somewhat large and makes the iterator code clumsy.
3. Have each node in the search tree store its parent in addition to the children. The iterator is not as large, but there is now extra memory required in each node, and the code to iterate is still clumsy.
4. Have each node maintain extra links: one to the next smaller, and one to the next larger node. This takes space, but the iteration is very simple to do, and it is easy to maintain these links.
5. Maintain the extra links only for nodes that have `nullptr` left or right links by using extra Boolean variables to allow the routines to tell if a left link is being used as a standard binary search tree left link or a link to the next smaller node, and similarly for the right link.



## Reference

[1] Mark Allen Weiss.Data Structures and Algorithm Analysis in C++.4ED
