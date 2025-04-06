[中文版](big_o_notation_zh.md) | English

# Big O Notation

[TOC]



## Definition

**Definition 2.1** $T(N) = O(f(N))$ if there are positive constants $c$ and $n_0$ such that $T(N) \leqslant cf(N)$ when $N \geqslant n_0$.

**Definition 2.2** $T(N)= \Omega (g(N))$ if there are positive `constants` $c$ and $n_{0}$ such that $T(N) \geqslant cg(N)$ when $N \geqslant n_0$.

**Definition 2.3** $T(N) = \Theta (h(N))$ if and only if $T(N) = O(h(N))$ and $T(N) = \Omega(h(N)) $.

**Definition 2.4** $T(N) = o(p(N))$ if, for all positive constants $c$, there exists an $n_{0}$ such that $T(N) < cp(N)$ when $N > n_0$. Less formally, $T(N) = o(p(N))$ if $T(N) = O(p(N))$ and $T(N) \neq \Theta(p(N))$.

**Rule 1** If $T_1(N) = O(f(N))$ and $T_2(N) = O(g(N))$, then

(a) $T_1(N) + T_2(N) = O(f(N) + g(N))$ (intuitively and less formally it is $O(max(f(N), g(N))$),

(b) $T_1(N) * T_2(N) = O(f(N) * g(N))$

**Rule 2** If $T(N)$ is a polynomial of degree $k$, then $T(N) = \Theta(N^k)$.

**Rule 3** $log^k N = O(N)$ for any constant $k$. This tells us that logarithms grow very slowly.

Typical growth rates:

| Function   | Name        |
| ---------- | ----------- |
| $c$        | Constant    |
| $log\ N$   | Logarithmic |
| $log^2\ N$ | Log-squared |
| $N$        | Linear      |
| $N logN$   |             |
| $N^2$      | Quadratic   |
| $N^3$      | Cubic       |
| $2^N$      | Exponential |



## Mathematics Theory

### Exponents

**Definition** $X^A = B$ if and only if $log_x{B} = A$.

**Theorem** $log_A{B} = \frac{log_c{B}}{log_c{A}}; A, B, C > 0, A \neq 1$.

**Theorem** $logAB = logA + logB; A, B > 0$.

**Theorem**

$logA/B = logA - logB$

$log(A^B) = B log A$

$log X < X$ for all $X > 0$

$log 1 = 0, log 2 = 1, log{1024} = 10, log {1048476} = 20$

### Series

The easiest formulas to remember are

$\sum_{i = 0}^{N} 2^i = 2^{N+1} - 1$

and the companion, 

$\sum_{i=0}^{N} A^i = \frac{A^{N+1} - 1}{A - 1}$

In the later formula, if $0 < A < 1$, then $\sum_{i = 0}^{N} \leqslant \frac{1}{1 - A}$ and as $N$ tends to $\infty$, the sum approaches $1/(1-A)$.

$\sum_{N}^{i=1} = \frac{N(N+1)}{2} \approx \frac{N^2}{2}$

$\sum_{i = 1}^{N} i^2 = \frac{N(N+1)(2N+1)}{6} \approx \frac{N^3}{3}$

$\sum_{i=1}^{N} i^k \approx \frac{N^{k+1}}{k+1};k \neq -1$

Euler's constant: $H_N = \sum_{i=1}^{N} \frac{1}{i} \approx log_e{N}$

$\sum_{i=1}^{N} \frac{1}{i} \approx log_e$

$\sum_{i=1}^{N} f(N) = Nf(N)$

$\sum_{i=n_0}^{N} f(i) = \sum_{i = 1}^{N} f(i) - \sum_{i = 1}^{n_0 - 1}f(i)$

### Modular Arithmetic

We say that $A$ us congruent to $B$ modulo $N$, written $A \equiv B (mod\ N)$, if $N$ divides $A - B$. Intuitively, this means that the remainder is the same when either $A$ or $B$ is divided by $N$. Thus, $81 \equiv 61 \equiv 1 (mod\ 10)$. As with equality, if $A \equiv B (mod\ N)$, then $A + C \equiv B + C(mod\ N)$ and $AD \equiv BD(mod\ N)$.

### The P Word

1. Proof by Induction

   A proof by induction has two standard parts. The first step is proving a `base case`, that is, establishing that a theorem is true for some small (usually degenerate) value(s); this step is almost always trivial. Next, an `inductive hypothesis` is assumed.

   **Theorem 1.3** If $N \geq 1$, then $\sum_{i = 1}^{N} i^{2} = \frac{N(N+1)(2N+1)}{6}$.

2. Proof by Counterexample

   The statement $F_k \leqslant K^2$ is false. The easiest way to prove this is to compute $F_{11} = 144 > 11^2$.

3. Proof by Contradiction

   Proof by contradiction proceeds by assuming that the theorem is false and showing that this assumption implies that some known property is false, and hence the original assumption was erroneous.



## Terminology

- `time complexity`



## Reference

[1] Thomas H.Cormen, Charles E.Leiserson, Ronald L. Rivest, Clifford Stein. Introduction to Algorithms . 3ED
