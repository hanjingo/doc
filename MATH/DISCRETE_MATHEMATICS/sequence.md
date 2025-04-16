# Sequences And Summations

[TOC]



## Definition

**Definition**: A `sequence` is a function from a subset of the set of integers (usually either the set $\{0, 1, 2, ...\}$ or the set $\{1, 2, 3, ...\}$) to a set $S$. We use the notation $a_n$ to denote the image of the integer $n$. We call $a_n$ a term of the sequence.

**Definition**: A `geometric progression` is a sequence of the form $a, ar, ar^2, ..., ar^n, ...$ where the `initial term a` and the `common ratio r` are real numbers.

**Definition**: An `arithmetic progression` is a sequence of the form $a, a + d, a + 2d, ..., a + nd, ...$ where the `initial term a` and the `common difference d` are real numbers.

**Definition**: A `recurrence relation` for the sequence $\{a_n\}$ is an equation that expresses $a_n$ in terms of one or more of the previous terms of the sequence, namely, $a_0, a_1, ..., a_{n - 1}$, for all integers $n$ with $n \geq n_0$, where $n_0$ is a nonnegative integer. A sequence is called a `solution` of a recurrence relation if it's terms satisfy the recurrence relation.

**Definition**: The `Fibonacci sequence`, $f_0, f_1, f_2, ...$, is defined by the initial conditions $f_0 = 0, f_1 = 1$, and the recurrence relation $f_n = f_{n - 1} + f_{n - 2}$ for $n = 2, 3, 4, ...$.



## Theorem

**THEOREM** If $a$ and $r$ are real numbers and $r \neq 0$, then:
$$
\sum_{j = 0}^{n} ar^j = 
\begin{cases}
\frac{ar^{n + 1} - a}{r - 1} &if\ r \neq 1 \\
(n + 1)a &if\ r = 1
\end{cases}
$$





## Claim

**Summation notation**, We begin by describing the notation used to express the sum of the terms: $a_m, a_{m + 1}, ..., a_n$ from the sequence $\{a_n\}$. We use the notation:
$$
\sum_{j=m}^{n}a_j, \sum_{j=m}^{n}a_j, or \sum_{m \leq j \leq n}a_j
$$
, (read as the sum from $j = m$ to $j = n$ of $a_j$) to represent:
$$
a_m + a_{m + 1} + ... + a_n
$$
, Here, the variable $j$ is called the **index of summation**, and the choice of the letter $j$ as the variable is arbitrary; that is, we could have used any other letter, such as $i$ or $k$. Or, in notation, here, the index of summation runs through all integers starting with its **lower limit** $m$ and ending with its **upper limit** $n$. A large uppercase Greek letter sigma, $\sum$, is used to denote summation.



## References

[1] Kenneth H. Rosen . Discrete Mathematics and Its Applications . 8Edition
