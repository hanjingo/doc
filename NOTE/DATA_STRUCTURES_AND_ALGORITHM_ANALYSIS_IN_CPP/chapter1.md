# Chapter 1 Programming: A General Overview

[TOC]



## Mathematics Review

### Exponents

$X^A X^B = X^{A+B}$

$\frac{X^A}{X^B} = X^{A-B}$

$(X^A)^B = X^{AB}$

$X^N + X^N = 2X^N \neq X^{2N}$

$2^N + 2^N = x^{N+1}$

### Logarithms

**Definition 1.1** $X^A = B$ if and only if $log_x{B} = A$.

**Theorem 1.1** $log_A{B} = \frac{log_c{B}}{log_c{A}}; A, B, C > 0, A \neq 1$.

**Theorem 1.2** $logAB = logA + logB; A, B > 0$。

Some other useful formulas, which can all be derived in a similar manner, follow:

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

**Theorem 1.4** The recursive number-printing algorithm is correct for $n \geq 0$.

