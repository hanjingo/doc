[中文版](chapter9_zh.md) | English

# 9 Medians and Order Statistics

[TOC]



We formally specify the **selection problem** as follows:

- **Input**: A set $A$ of $n$ (distinct) numbers and an integer $i$, with $1 \leq i \leq n$.
- **Output**: The element $x \in A$ that is larger than exactly $i - 1$ other elements of $A$.

## Minimum and maximum

$$
\begin{align}
& MINIMUM(A) \\
& for\ i\ =\ 2\ to\ A.length \\
& \qquad if\ min > A[i] \\
& \qquad \qquad min = A[i] \\
& return\ min
\end{align}
$$



## Selection in expected linear time

$$
\begin{align}
& RANDOMIZED-SELECT(A, p, r, i) \\
& if\ p == r \\
& \qquad return\ A[p] \\
& q = RANDOMIZED-PARTITION(A, p, r) \\
& k = q - p + 1 \\
& if\ i == k \\
& \qquad return\ A[q] \\
& else\ if\ i < k \\
& \qquad return\ RANDOMIZED-SELECT(A, p, q - 1, i) \\
& else\ return\ RANDOMIZED-SELECT(A, q + 1, r, i - k)
\end{align}
$$



## Selection in worst-case linear time

![9_1](res/9_1.png)

As in a comparison sort, $SELECT$ and $RANDOMIZED-SELECT$ determine information about the relative order of elements only by comparing elements. Recall from Chapter 8 that sorting requires $\Omega(n\ lg\ n)$ time in the comparison model, even on average.
