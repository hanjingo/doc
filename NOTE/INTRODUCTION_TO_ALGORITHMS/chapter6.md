[中文版](chapter6_zh.md) | English

# 6 Heapsort

[TOC]



## Heaps

The **(binary) heap** data structure is an array object that we can view as a nearly complete binary tree.

![6_1](res/6_1.png)

There are two kinds of binary heaps:

- **max-heap**: the **max-heap property** is that for every node $i$ other than the root, $A[PARENT(i)] \geq A[i]$.
- **min-heap**: the **min-heap property** is that for every node $i$ other than the root, $A[PARENT(i)] \leq A[i]$.

The basic operations on heaps run in time at most proportional to the height of the tree and thus take $O(lg\ n)$ time.



## Maintaining the heap property

![6_2](res/6_2.png)
$$
MAX-HEAPIFY(A, i) \\
\begin{align}
& l = LEFT(i) \\
& r = RIGHT(i) \\
& if\ l \leqslant A.heap - size\ and\ A[l] > A[i] \\
& \qquad largest = l \\
& else\ largest = i \\
& if\ r \leqslant A.heap - size\ and\ A[r] > A[largest] \\
& \qquad largest = r \\
& if\ larget \neq i \\
& \qquad exchange\ A[i]\ with\ A[largest] \\
& \qquad MAX-HEAPIFY(A, largest)
\end{align}
$$
The running time of $MAX-HEAPIFY$ by the recurrence $T(n) \leq T(2n / 3) + \theta(1)$. The solution to this recurrence, is $T(n) = O(lg\ n)$. Alternatively, we can characterize the running time of $MAX-HEAPIFY$ on a node of height $h$ as $O(h)$.



## Building a heap

![6_3](res/6_3.png)
$$
BUILD-MAX-HEAP(A) \\
\begin{align}
& A.heap - size = A.length \\
& for i = \lfloor A.length / 2 \rfloor downto 1 \\
& \qquad MAX-HEAPIFY(A, i)
\end{align}
$$
The total cost of BUILD-MAX-HEAP:

$\sum^{\lfloor lg n \rfloor}_{h = 0} \lceil \frac{n}{2^{h + 1}} \rceil O(h) = O(n \sum_{h = 0}^{\lfloor lgn \rfloor} \frac{h}{2^h}) = O(n \sum_{h = 0}^{\infty} \frac{h}{2^h}) = O(n)$。



## The heapsort algorithm

![6_4](res/6_4.png)
$$
HEAPSORT(A) \\
\begin{align}
& BUILD-MAX-HEAP(A) \\
& for\ i = A.length\ downto\ 2 \\
& \qquad exchange\ A[1]\ with\ A[i] \\
& \qquad A.heap - size = A.heap - size - 1 \\
& \qquad MAX-HEAPIFY(A, 1) \\
\end{align}
$$



## Priority queues

A **priority queue** is a data structure for maintaining a set $S$ of elements, each with an associated value called a **key**. A **max-priority queue** supports the following operations:

- $INSERT(S, x)$ inserts the element $x$ into the set $S$, which is equivalent to the operation $S = S \cup \{x\}$.
- $MAXIMUM(S)$ returns the element of $S$ with the largest key.
- $EXTRACT-MAX(S)$ removes and returns the element of $S$ with the largest key.
- $INCREASE-KEY(S, x, k)$ increases the value of element $x$'s key to the new value $k$, which is assumed to be at least as large as $x$'s current key value.

![6_5](res/6_5.png)
$$
HEAP-INCREASE-KEY(A, i, key) \\
\begin{align}
& if\ key < A[i] \\
& \qquad error "new key is smaller than current key" \\
& A[i] = key \\
& while\ i > 1\ and\ A[PARENT(i)] < A[i] \\
& \qquad exchange A[i] with A[PARENT(i)] \\
& \qquad i = PARENT(i)
\end{align}
$$
