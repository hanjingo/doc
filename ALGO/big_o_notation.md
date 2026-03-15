English | [中文版](big_o_notation_zh.md)

# Big O Notation

[TOC]



## Terminology

- `time complexity` time complexity



## Definition

If there exist any positive constants c and $N_0$ such that when $N \geq N_0$, $T(N) \leq cF(N)$, then we can denote the complexity of T(N) as $O(F(N))^3$.

**Definition 2.1** If there exist positive constants $c$ and $n_0$ such that when $N \geqslant n_0$, $T(N) \leqslant cf(N)$, then we denote $T(N) = O(f(N))$.

**Definition 2.2** If there exist positive constants $c$ and $n_0$ such that when $N \geqslant n_0$, $T(N) \geqslant cg(N)$, then we denote $T(N)= \Omega (g(N))$.

**Definition 2.3** $T(N) = \Theta (h(N))$ if and only if $T(N) = O(h(N))$ and $T(N) = \Omega(h(N)) $.

**Definition 2.4** If for all constants $c$ there exists $n_0$ such that when $N > n_0$, $T(N) < cp(N)$, then we denote $T(N) = o(p(N))$. The informal definition is: if $T(N) = O(p(N))$ and $T(N) \neq \Theta(p(N))$, then $T(N) = o(p(N))$.

**Rule 1** If $T_1(N) = O(f(N))$ and $T_2(N) = O(g(N))$, then

(a) $T_1(N) + T_2(N) = O(f(N) + g(N))$ (informally expressed as $max(O(f(N)), O(g(N)))$)

(b) $T_1(N)T_2(N) = O(f(N)g(N))$

**Rule 2** If $T(N)$ is a polynomial of degree $k$, then $T(N) = \Theta(N^k)$.

**Rule 3** For any constant $k$, $log^kN = O(N)$. This tells us that logarithmic growth is very slow.

Common function orders:

| Symbol      | Name     |
| ----------- | -------- |
| $O(1)$      | Constant |
| $O(log n)$  | Logarithmic |
| $O(n)$      | Linear   |
| $O(nlog n)$ | Linearithmic |
| $O(n^2)$    | Quadratic |
| $O(n^3)$    | Cubic    |
| $O(c^n)$    | Exponential |
| $O(n!)$     | Factorial |



## Running Time Calculation

### General Rules

**Rule 1: For Loop** The running time of a for loop is at most the running time of the statements inside the for loop (including test) multiplied by the number of iterations.

**Rule 2: Nested Loops** Analyze these loops from the inside out. The total running time of a statement inside a group of nested loops is the running time of that statement multiplied by the product of the sizes of all loops in that group.

**Rule 3: Sequential Statements** Sum the running times of each statement.

**Rule 4: If/Else Statements** For a program segment:

```c++
if (condition)
  S1
else
  S2
```

The running time of an if/else statement never exceeds the test plus the sum of the running times of the longer of $S_1$ and $S_2$.

### Solution to the Maximum Subsequence Sum Problem

### Logarithms in Running Time

The most common pattern for logarithms is: if an algorithm reduces the problem size to a fraction in constant time $O(1)$ (usually 1/2), then the algorithm is $O(log\ N)$; on the other hand, if constant time only reduces the problem by a constant amount (such as reducing by 1), then that algorithm is $O(N)$.

1. Binary Search

   `Binary search` Given an integer $X$ and integers $A_0, A_1, ..., A_{N-1}$, which are pre-sorted and in memory, find the index $i$ such that $A_i = X$. If $X$ is not in the data, return $i = -1$.

   The running time is $O(log\ N)$.

2. Euclidean Algorithm

   **Theorem 2.1** If $M > N$, then $M \mod N < M/2$.

3. Exponentiation



## Mathematical Foundations

### Exponents

$X^A X^B = X^{A+B}$

$\frac{X^A}{X^B} = X^{A-B}$

$(X^A)^B = X^{AB}$

$X^N + X^N = 2X^N \neq X^{2N}$

$2^N + 2^N = 2^{N+1}$

### Logarithms

**Definition 1.1** $X^A = B$ if and only if $log_x{B} = A$.

**Theorem 1.1** $log_A{B} = \frac{log_c{B}}{log_c{A}}; A, B, C > 0, A \neq 1.$

**Theorem 1.2** $log AB = log A + log B; A, B > 0$.

Some other theorems:

$log A/B = log A - log B$

$log(A^B) = B log A$

$log X < X$ for all $X > 0$

$log 1 = 0, log 2 = 1, log 1024 = 10, log 1048576 = 20$

### Series

$\sum_{i = 0}^{N} 2^i = 2^{N+1} - 1$

$\sum_{i=0}^{N} A^i = \frac{A^{N+1} - 1}{A - 1}$, if $0 < A < 1$ then: $\sum_{i = 0}^{N} \leqslant \frac{1}{1 - A}$, as $N$ approaches $\infty$, the sum approaches $1/(1-A)$.

$\sum_{i=1}^{N} i = \frac{N(N+1)}{2} \approx \frac{N^2}{2}$

$\sum_{i = 1}^{N} i^2 = \frac{N(N+1)(2N+1)}{6} \approx \frac{N^3}{3}$

$\sum_{i=1}^{N} i^k \approx \frac{N^{k+1}}{k+1};k \neq -1$

`Euler's constant:` $H_N = \sum_{i=1}^{N} \frac{1}{i} \approx log_e{N}$

$\sum_{i=1}^{N} \frac{1}{i} \approx log_e N$

$\sum_{i=1}^{N} f(N) = Nf(N)$

$\sum_{i=n_0}^{N} f(i) = \sum_{i = 1}^{N} f(i) - \sum_{i = 1}^{n_0 - 1}f(i)$

### Modular Arithmetic

If $N$ divides $A-B$, then we say $A$ is congruent to $B$ (congruent), denoted as $A \equiv B (mod\ N)$. This means that regardless of whether $A$ or $B$ is divided by $N$, the remainder obtained is the same. Therefore, $81 \equiv 61 \equiv 1 (mod\ 10)$. Like equality, if $A \equiv B (mod\ N)$, then $A + C \equiv B + C(mod\ N)$ and $AD \equiv BD(mod\ N)$.

### Proof Methods

1. Proof by Mathematical Induction

   The first step is to prove the `base case`, which is to verify the correctness of the theorem for some small value; then we proceed with the `inductive hypothesis`.

2. Proof by Counterexample

   The formula $F_k \leqslant K^2$ does not hold. The easiest way to prove it is to calculate $F_{11} = 144 > 11^2$.

3. Proof by Contradiction

   Proof by contradiction is done by assuming the theorem does not hold, then proving that this assumption leads to some known property not holding, thus proving the original assumption is false.



## References

- [Wikipedia - Big O notation](https://en.wikipedia.org/wiki/Big_O_notation)
- [Big O Notation](https://blog.csdn.net/weixin_44560088/article/details/108052225)
- Introduction to Algorithms. Thomas H Cormen, Charles E Leiserson, Ronald L Rivest, Clifford Stein. Third Edition. 2013
- [US] Mark Allen Weiss. Data Structures and Algorithm Analysis in C++. 3rd Edition
