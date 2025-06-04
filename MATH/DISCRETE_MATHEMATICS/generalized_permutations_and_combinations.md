# Generalized Permutations and Combinations

[TOC]



## Definition

**THE PRODUCT RULE** Suppose that a procedure can be broken down into a sequence of two tasks. If there are $n_1$ ways to do the first and for each of these ways of doing the first task, there are $n_2$ ways to do the second task, then there are $n_1 n_2$ ways to do the procedure.

**THE SUM RULE** If a task can be done either in one of $n_1$ ways or in one of $n_2$ ways, where none of the set of $n_1$ ways is the same as any of the set of $n_2$ ways, then there are $n_1 + n_2$ ways to do the task.

**THE SUBTRACTION RULE** If a task can be done in either $n_1$ ways or $n_2$ ways, then the number of ways to do the task is $n_1 + n_2$ minus the number of ways to do the task that are common to the two different ways.

**THE DIVISION RULE** There are $n/d$ ways to do a task if it can be done using a procedure that can be carried out in $n$ ways, and for every way $w$, exactly $d$ of the $n$ ways correspond to way $w$.

**Definition** A `combinatorial proof` of an identity is a proof that uses counting arguments to prove that both sides of the identity count the same objects but in different ways or a proof that is based on showing that there is a bijection between the sets of objects counted by the two sides of the identity. There are two types of proofs are called `double-counting proofs` and `bijective proofs`, respectively.



## THEOREM

**THEOREM** THE PIGEONHOLE PRINCIPLE: If $k$ is a positive integer and $k + 1$ or more objects are placed into $k$ boxes, then there is at least one box containing two or more of the objects.

**THEOREM** THE GENERALIZED PIGEONHOLE PRINCIPLE If $N$ objects are placed into $k$ boxes, then there is at least one box containing at least $\lceil N/k \rceil$ objects.

**THEOREM** Every sequence of $n^2 + 1$ distinct real numbers contain a subsequence of length $n + 1$ that is either strictly increasing or strictly decreasing.

**THEOREM** If $n$ is a positive integer and $r$ is an integer with $1 \leq r \leq n$, then there are $P(n, r) = n(n - 1)(n - 2) \cdots (n - r + 1)$  `r`-permutations of a set with $n$ distinct elements.

**THEOREM** The number of $r$-combinations of a set with $n$ elements, where $n$ is a nonnegative integer and $r$ is an integer with $0 \leq r \leq n$, equals $C(n, r) = \frac{n!}{r!(n - r)!}$.

**THEOREM** THE BINOMIAL THEOREM: Let $x$ and $y$ be variables, and let $n$ be a nonnegative integer. Then $(x + y)^n = \sum_{j = 0}^{n} {n \choose j}x^{n - j} y^{j} = {n \choose 0}x^n + {n \choose 1}x^{n - 1}y + \cdots + {n \choose n - 1}xy^{n - 1} + {n \choose n}y^n$.

**THEOREM** PASCAL'S IDENTITY: Let $n$ and $k$ be positive integers with $n \geq k$. Then ${n + 1 \choose k} = {n \choose k - 1} + {n \choose k}$.

**THEOREM** VANDERMONDE'S IDENTITY: Let $m$, $n$, and $r$ be nonnegative integers with $r$ not exceeding either $m$ or $n$. Then ${m + n \choose r} = \sum_{k = 0}^{r} {m \choose r - k} {n \choose k}$.

**THEOREM** Let $n$ and $r$ be nonnegative integers with $r \leq n$. Then ${n + 1 \choose r + 1} = \sum_{j = r}^{n} {j \choose r}$.

**THEOREM** The number of $r$-permutations of a set of $n$ objects with repetition allowed is $n^r$.

**THEOREM** There are $C(n + r - 1, r) = C(n + r - 1, n - 1)$ `r`-combinations from a set with $n$ elements when repetition of elements is allowed.

**THEOREM** The number of different permutations of $n$ objects, where there are $n_1$ indistinguishable objects of type 1, $n_2$ indistinguishable objects of type 2, ..., and $n_k$ indistinguishable objects of type $k$, is $\frac{n!}{n_1! n_2! \cdots n_k!}$.



## COROLLARY

**COROLLARY** A function $f$ from a set with $k + 1$ or more elements to a set with $k$ elements is not one-to-one.

**COROLLARY** If $n$ and $r$ are integers with $0 \leq r \leq n$, then $P(, r) = \frac{n!}{(n - r)!}$.

**COROLLARY** Let $n$ and $r$ be nonnegative integers with $r \leq n$. Then $C(n, r) = C(n, n - r)$.

**COROLLARY** Let $n$ be a nonnegative integer. Then $\sum_{k = 0}^{n} {n \choose k} = 2^n$.

**COROLLARY** Let $n$ be a positive integer. Then $\sum_{k = 0}^{n}(-1)^k {n \choose k} = 0$.

**COROLLARY** Let $n$ be a nonnegative integer. Then $\sum_{k = 0}^{n}2^{k} {n \choose k} = 3^n$.

**COROLLARY** If $n$ is a nonnegative integer, then ${2n \choose n} = \sum_{k = 0}^{n} {n \choose k}^2$.