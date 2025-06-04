# Chapter 6 Counting

[TOC]



## The Basics of Counting

**THE PRODUCT RULE** Suppose that a procedure can be broken down into a sequence of two tasks. If there are $n_1$ ways to do the first and for each of these ways of doing the first task, there are $n_2$ ways to do the second task, then there are $n_1 n_2$ ways to do the procedure.

**THE SUM RULE** If a task can be done either in one of $n_1$ ways or in one of $n_2$ ways, where none of the set of $n_1$ ways is the same as any of the set of $n_2$ ways, then there are $n_1 + n_2$ ways to do the task.

**THE SUBTRACTION RULE** If a task can be done in either $n_1$ ways or $n_2$ ways, then the number of ways to do the task is $n_1 + n_2$ minus the number of ways to do the task that are common to the two different ways.

**THE DIVISION RULE** There are $n/d$ ways to do a task if it can be done using a procedure that can be carried out in $n$ ways, and for every way $w$, exactly $d$ of the $n$ ways correspond to way $w$.

**THEOREM** THE PIGEONHOLE PRINCIPLE: If $k$ is a positive integer and $k + 1$ or more objects are placed into $k$ boxes, then there is at least one box containing two or more of the objects.

**COROLLARY** A function $f$ from a set with $k + 1$ or more elements to a set with $k$ elements is not one-to-one.

**THEOREM** THE GENERALIZED PIGEONHOLE PRINCIPLE If $N$ objects are placed into $k$ boxes, then there is at least one box containing at least $\lceil N/k \rceil$ objects.

**THEOREM** Every sequence of $n^2 + 1$ distinct real numbers contain a subsequence of length $n + 1$ that is either strictly increasing or strictly decreasing.



## Permutations and Combinations

**THEOREM** If $n$ is a positive integer and $r$ is an integer with $1 \leq r \leq n$, then there are $P(n, r) = n(n - 1)(n - 2) \cdots (n - r + 1)$  `r`-permutations of a set with $n$ distinct elements.

**COROLLARY** If $n$ and $r$ are integers with $0 \leq r \leq n$, then $P(, r) = \frac{n!}{(n - r)!}$.

**THEOREM** The number of $r$-combinations of a set with $n$ elements, where $n$ is a nonnegative integer and $r$ is an integer with $0 \leq r \leq n$, equals $C(n, r) = \frac{n!}{r!(n - r)!}$.

**COROLLARY** Let $n$ and $r$ be nonnegative integers with $r \leq n$. Then $C(n, r) = C(n, n - r)$.

**Definition** A `combinatorial proof` of an identity is a proof that uses counting arguments to prove that both sides of the identity count the same objects but in different ways or a proof that is based on showing that there is a bijection between the sets of objects counted by the two sides of the identity. There are two types of proofs are called `double-counting proofs` and `bijective proofs`, respectively.



## Binomial Coefficients and Identities

The number of $r$-combinations from a set with $n$ elements is often denoted by ${n \choose r}$. This number is also called a **binomial coefficient** because these numbers occur as coefficients in the expansion of powers of binomial expressions such as $(a + b)^{n}$.

**THEOREM** THE BINOMIAL THEOREM: Let $x$ and $y$ be variables, and let $n$ be a nonnegative integer. Then $(x + y)^n = \sum_{j = 0}^{n} {n \choose j}x^{n - j} y^{j} = {n \choose 0}x^n + {n \choose 1}x^{n - 1}y + \cdots + {n \choose n - 1}xy^{n - 1} + {n \choose n}y^n$.

**COROLLARY** Let $n$ be a nonnegative integer. Then $\sum_{k = 0}^{n} {n \choose k} = 2^n$.

**COROLLARY** Let $n$ be a positive integer. Then $\sum_{k = 0}^{n}(-1)^k {n \choose k} = 0$.

**COROLLARY** Let $n$ be a nonnegative integer. Then $\sum_{k = 0}^{n}2^{k} {n \choose k} = 3^n$.

**THEOREM** PASCAL'S IDENTITY: Let $n$ and $k$ be positive integers with $n \geq k$. Then ${n + 1 \choose k} = {n \choose k - 1} + {n \choose k}$.

**THEOREM** VANDERMONDE'S IDENTITY: Let $m$, $n$, and $r$ be nonnegative integers with $r$ not exceeding either $m$ or $n$. Then ${m + n \choose r} = \sum_{k = 0}^{r} {m \choose r - k} {n \choose k}$.

**COROLLARY** If $n$ is a nonnegative integer, then ${2n \choose n} = \sum_{k = 0}^{n} {n \choose k}^2$.

**THEOREM** Let $n$ and $r$ be nonnegative integers with $r \leq n$. Then ${n + 1 \choose r + 1} = \sum_{j = r}^{n} {j \choose r}$.



## Generalized Permutations and Combinations

**THEOREM** The number of $r$-permutations of a set of $n$ objects with repetition allowed is $n^r$.

**THEOREM** There are $C(n + r - 1, r) = C(n + r - 1, n - 1)$ `r`-combinations from a set with $n$ elements when repetition of elements is allowed.

**THEOREM** The number of different permutations of $n$ objects, where there are $n_1$ indistinguishable objects of type 1, $n_2$ indistinguishable objects of type 2, ..., and $n_k$ indistinguishable objects of type $k$, is $\frac{n!}{n_1! n_2! \cdots n_k!}$.



## Key Terms and Results

### TERMS

- **Combinatorics**: the study of arrangements of objects.
- **Enumeration**: the counting of arrangements of objects.
- **Tree diagram**: a diagram made up of a root, branches leaving the root, and other branches leaving some of the endpoints of branches.
- **Permutation**: an ordered arrangement of the elements of a set.
- **$r$-permutation**: an ordered arrangement of $r$ elements of a set.
- **P(n, r)**: the number of $r$-Permutation of a set with $n$ elements.
- **$r$-combination**: an unordered selection of $r$ elements of a set.
- **C(n, r)**: the number of $r$-combinations of a set with $n$ elements.
- **Binomial coefficient $n \choose r$**: also the number of $r$-combinations of a set with $n$ elements.
- **Combinatorial proof**: a proof that uses counting arguments rather than algebraic manipulation to prove a result.
- **Pascal's triangle**: a representation of the binomial coefficients, where the $i$th row of the triangle contains ${i \choose j}$ for $j = 0, 1, 2, \cdots, i$.
- **$S(n, j)$**: the Stirling number of the second kind denoting the number of ways to distribute $n$ distinguishable objects into $j$ indistinguishable boxes so that no box is empty.

### RESULTS

- **Product rule for counting**: The number of ways to do a procedure that consists of two tasks is the product of the number of ways to do the first task and the number of ways to do the second task after the first task has been done.

- **Product rule for sets**: The number of elements in the Cartesian product of finite sets is the product of the number of elements in each set.

- **Sum rule for counting**: The number of ways to do a task in one of two ways is the sum of the number of ways to do these tasks if they cannot be done simultaneously.

- **Sum rule for sets**: The number of elements in the union of pairwise disjoint finite sets is the sum of the numbers of elements in these sets.

- **Subtraction rule for counting** or **Inclusion-exclusion for sets**: If a task can be done in either $n_1$ ways or $n_2$ ways, then the number of ways to do the task is $n_1 + n_2$ minus the number of elements in their intersection.

- **Division rule for counting**: There are $n/d$ ways to do a task if it can be done using a procedure that can be carried out in $n$ ways, and for every way $w$, exactly $d$ of the $n$ ways correspond to way $w$.

- **Division rule for sets**: Suppose that a finite set $A$ is the union of $n$ disjoint subsets each with $d$ elements. Then $n = |A|/d$.

- **The pigeohole principle**: When more than $k$ objects are placed in $k$ boxes, there must be a box containing more than one object.

- **The generalized pigeonhole principle**: When $N$ objects are placed in $k$ boxes, there must be a box containing at least $\lceil N / k \rceil$ objects.
  $$
  P(n, r) = \frac{n!}{(n - r)!} \\
  C(n, r) = {n \choose r} = \frac{n!}{r!(n - r)!}
  $$

- **Pascal's identity**: ${n + 1 \choose k} = {n \choose k - 1} + {n \choose k}$.

- **The binomial theorem**: $(x + y)^n = \sum_{k = 0}^{n} {n \choose k} x^{n - k} y^k$

  There are $n^r$ $r$-permutations of a set with $n$ elements when repetition is allowed.

  There are $C(n + r - 1, r)$ $r$-combinations of a set with $n$ elements when repetition is allowed.

  There are $n!/(n_1! n_2! \cdots n_k!)$ permutations of $n$ objects of $k$ types where there are $n_i$ indistinguishable objects of type $i$ for $i = 1, 2, 3, \cdots k$.

  the algorithm for generating the permutations of the set $\{1, 2, \cdots, n\}$.