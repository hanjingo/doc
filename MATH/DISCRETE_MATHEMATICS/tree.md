# Tree

[TOC]



## Definition

**Definition** A `tree` is a connected undirected graph with no simple circuits.

**Definition** A `rooted tree` is a tree in which one vertex has been designated as the root and every edge is directed away from the root.

**Definition** A rooted tree is called an `m-ary tree` if every internal vertex has no more than `m` children. The tree is called a `full m-ary tree` if every internal vertex has exactly `m` children. An `m`-ary tree with `m = 2` is called a `binary tree`.

**Definition** The `value of a vertex in a game tree` is defined recursively as:

- the value of a leaf is the payoff to the first player player when the game terminates in the position represented by this leaf.
- the value of an internal vertex at an even level is the maximum of the values of its children, and the value of an internal vertex at an odd level is the minimum of the values of its children.

**Definition** Let $T$ be an ordered rooted tree with root $r$. If $T$ consists only of $r$, then $r$ is the `preorder traversal` of $T$. Otherwise, suppose that $T_1, T_2, ..., T_n$ are the subtrees at $r$ from left to right in $T$. The `preorder traversal` begins by visiting $r$. It continues by traversing $T_1$ in preorder, then $T_2$ in preorder, and so on, until $T_n$ is traversed in preorder.

![preorder_traversal](res/preorder_traversal.png)

**Definition** Let $T$ be an ordered rooted tree with root $r$. If $T$ consists only of $r$, then $r$ is the `inorder traversal` of $T$. Otherwise, suppose that $T_1, T_2, ..., T_n$ are the subtrees at $r$ from left to right. The `inorder traversal` begins by traversing $T_1$ in inorder, then visiting $r$. It continues by traversing $T_2$ in inorder, then $T_3$ in inorder, ..., and finally $T_n$ in inorder.

![inorder_traversal](res/inorder_traversal.png)

**Definition** Let $T$ be an ordered rooted tree with root $r$. If $T$ consists only of $r$, then $r$ is the `postorder traversal` of $T$. Otherwise, suppose that $T_1, T_2, ..., T_n$ are the subtrees at $r$ from left to right. The `postorder traversal` begins by traversing $T_1$ in postorder, then $T_2$ in postorder, ..., then $T_n$ in postorder, and ends by visiting $r$.

![postorder_traversal](res/postorder_traversal.png)

**Definition** Let $G$ be a simple graph. A `spanning tree` of $G$ is a subgraph of $G$ that is a tree containing every vertex of $G$​.

**Definition** A `minimum spanning tree` in a connected weighted graph is a spanning tree that has the smallest possible sum of weights of its edges.



## Theorem

**THEOREM** An undirected graph is a tree if and only if there is a unique simple path between any two of its vertices.

**THEOREM** A tree with $n$ vertices has $n - 1$ edges.

**THEOREM** A full $m$-ary tree with $i$ internal vertices contains $n = mi + 1$ vertices.

**THEOREM**: A full $m$-ary tree with:

- $n$ vertices has $i = (n - 1)/m$ internal vertices and $l = [(m - 1)n + 1]/m$ leaves.
- $i$ internal vertices has $n = mi + 1$ vertices and $l = (m - 1)i + 1$ leaves.
- $l$ leaves has $n = (ml - 1)/(m - 1)$ vertices and $i = (l - 1)/(m - 1)$ internal vertices.

**THEOREM** There are at most $m^k$ leaves in an $m$-ary tree of height $h$.

**THEOREM** A sorting algorithm based on binary comparisons requires at least $\lceil \log_2 n! \rceil$ comparisons.

**THEOREM** The average number of comparisons used by a sorting algorithm to sort $n$ elements based on binary comparisons is $\Omega(n \log n)$.

**THEOREM** The value of a vertex of a game tree tells us the payoff to the first player if both players follow the minmax strategy and play starts from the position represented by this vertex.

**THEOREM** A simple graph is connected if and only if it has a spanning tree.



## Corollary

**COROLLARY** The number of comparisons used by a sorting algorithm to sort $n$ elements based on binary comparisons is $\Omega(n \log n)$.

