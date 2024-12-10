[中文版](chapter13_zh.md) | English

# Red-Black Trees

[TOC]



**Red-black trees** are one of many search-tree schemes that are "balanced" in order to guarantee that basic dynamic-set operations take $O(lg\ n)$ time in the worst case.

## Properties of red-black trees

A red-black tree is a binary tree that satisfies the following **red-black properties**:

1. Every node is either red or black.
2. The root is black.
3. Every leaf (NIL) is black.
4. If a node is red, then both its children are black.
5. For each node, all simple paths from the node to descendant leaves contain the same number of black nodes.

**Lemma 13.1** A red-black tree with $n$ internal nodes has height at most $2lg(n + 1)$.

![13_1](res/13_1.png)



## Rotations

![13_2](res/13_2.png)
$$
\begin{align}
& LEFT-ROTATE(T, x) \\
& y = x.right \\
& x.right = y.left \\
& if\ y.left \neq T.nil \\
& \qquad y.left.p = x \\
& y.p = x.p \\
& if\ x.p == T.nil \\
& \qquad T.root = y \\
& elseif\ x == x.p.left \\
& \qquad x.p.left = y \\
& else\ x.p.right = y \\
& y.left = x \\
& x.p = y
\end{align}
$$
![13_3](res/13_3.png)



## Insertion

$$
\begin{align}
& RB-INSERT(T, z) \\
& y = T.nil \\
& x = T.root \\
& while\ x \neq T.nil \\
& \qquad y = x \\
& \qquad if\ z.key < z.key \\
& \qquad \qquad x = x.left \\
& \qquad else\ x = x.right \\
& z.p = y \\
& if\ y == T.nil \\
& \qquad T.root = z \\
& elseif\ z.key < y.key \\
& \qquad y.left = z \\
& else\ y.right = z \\
& z.left = T.nil \\
& z.right = T.nil \\
& z.color = RED \\
& RB-INSERT-FIXUP(T, z)
\end{align}
$$

$$
\begin{align}
& RB-INSERT-FIXUP(T, z) \\
& while\ z.p.color == RED \\
& \qquad if\ z.p == z.p.p.left \\
& \qquad \qquad y = z.p.p.right \\
& \qquad \qquad if\ y.color == RED \\
& \qquad \qquad \qquad z.p.color = BLACK \\
& \qquad \qquad \qquad z.color = BLACK \\
& \qquad \qquad \qquad z.p.p.color = RED \\
& \qquad \qquad \qquad z = z.p.p \\
& \qquad \qquad else\ if\ z == z.p.right \\
& \qquad \qquad \qquad z = z.p \\
& \qquad \qquad \qquad LEFT-ROTATE(T, z) \\
& \qquad \qquad z.p.color = BLACK \\
& \qquad \qquad z.p.p.color = RED \\
& \qquad \qquad RIGHT-ROTATE(T, z.p.p) \\
& \qquad else(same\ as\ then\ clause\ with\ "right"\ and\ "left"\ exchanged) \\
& T.root.color = BLACK
\end{align}
$$

![13_4](res/13_4.png)



## Deletion

$$
\begin{align}
& RB-TRANSPLANT(T, u, v) \\
& if\ u.p == T.nil \\
& \qquad T.root = v \\
& elseif\ u == u.p.left \\
& \qquad u.p.left = v \\
& else\ u.p.right = v \\
& v.p = u.p
\end{align}
$$

$$
\begin{align}
& RB-DELETE-FIXUP(T, x) \\
& while\ x \neq T.root\ and\ x.color == BLACK \\
& \qquad if\ x == x.p.left \\
& \qquad \qquad w = x.p.right \\
& \qquad \qquad if\ w.color == RED \\
& \qquad \qquad \qquad w.color = BLACK \\
& \qquad \qquad \qquad x.p.color = RED \\
& \qquad \qquad \qquad LEFT-ROTATE(T, x.p) \\
& \qquad \qquad \qquad w = x.p.right \\
& \qquad \qquad if\ w.left.color == BLACK\ and\ w.right.color == BLACK \\
& \qquad \qquad \qquad w.color = RED \\
& \qquad \qquad \qquad x = x.p \\
& \qquad \qquad else\ if\ w.right.color == BLACK \\
& \qquad \qquad \qquad w.left.color = BLACK \\
& \qquad \qquad \qquad w.color = RED \\
& \qquad \qquad \qquad RIGHT-ROTATE(T, w) \\
& \qquad \qquad \qquad w = x.p.right \\
& \qquad \qquad w.color = x.p.color \\
& \qquad \qquad x.p.color = BLACK \\
& \qquad \qquad w.right.color = BLACK \\
& \qquad \qquad LEFT-ROTATE(T, x.p) \\
& \qquad \qquad x = T.root \\
& \qquad else(same\ as\ then\ clause\ with\ "right"\ and\ "left"\ exchanged) \\
\end{align}
$$

$$
\begin{align}
& RB-DELETE(T, z) \\
& y = z \\
& y - original - color = y.color \\
& if\ z.left == T.nil \\
& \qquad x = z.right \\
& \qquad RB-TRANSPLANT(T, z, z.right) \\
& elseif\ z.right == T.nil \\
& \qquad x = z.left \\
& \qquad RB-TRANSPLANT(T, z, z.left) \\
& else\ y = TREE-MINIMUM(z.right) \\
& \qquad y - original - color = y.color \\
& \qquad x = y.right \\
& \qquad if\ y.p == z \\
& \qquad \qquad x.p = y \\
& \qquad else\ RB-TRANSPLANT(T, y, y.right) \\
& \qquad \qquad y.right = z.right \\
& \qquad \qquad y.right.p = y \\
& \qquad RB-TRANSPLANT(T, z, y) \\
& \qquad y.left = z.left \\
& \qquad y.left.p = y \\
& \qquad y.color = z.color \\
& if\ y - original - color == BLACK \\
& \qquad RB-DELETE-FIXUP(T, x) 
\end{align}
$$

![13_7](res/13_7.png)
