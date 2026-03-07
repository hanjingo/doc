# Complexity Analysis

[TOC]



## Term

- `Analyzing` an algorithm has come to mean predicting the resources that the algorithm requires.



## Asymptotic Notation

**$\theta$-notation**

For a given function $g(n)$ we denote by $\theta(g(n))$ the set of functions:
$$
\theta(g(n)) = \{f(n):\text{there exist positive constants} c_1, c_2 \text{ and } n_0 \text{ such that}\}\\ 
0 \leq c_1 g(n) \leq f(n) \leq c_2 g(n) \text{ for all } n \geq n_0 \}
$$
For all $n \geq n_0$, the function $f(n)$ is equal to $g(n)$ to within a constant factor. We say that $g(n)$ is an `asymptotically tight bound` for $f(n)$.

**$O$-notation**

The $\theta$-notation asymptotically bounds a function from above and below. When we have only an **asymptotic upper bound**, we use $O$-notation. For a given function $g(n)$, we denote by $O(g(n))$ (pronounced "big-oh of g of n" or sometimes just "oh of g of n") the set of functions:
$$
O(g(n)) = \{f(n)：\text{there exist positive constants}\ c \text{ and } n_0 \text{ such that}\\
0 \leq f(n) \leq cg(n) \text{ for all } n \geq n_0\}
$$
, we use $O$-notation to give an upper bound on a function, to within a constant factor.

**$\Omega$-notation**

Just as $O$-notation provides an asymptotic upper bound on a function, $\Omega$-notation provides an **asymptotic lower bound**. For a given function $g(n)$, we denote by $\Omega(g(n))$ (pronounced "big-omega of g of n" or sometimes just "omega of g of n") the set of functions:
$$
\Omega(g(n)) = \{f(n): \text{there exist positive constants } c \text{ and } n_0 \text{ such\ that}\\
0 \leq cg(n) \leq f(n) \text{ for all } n \geq n_0\}
$$
**$o$-notation**

We use $o$-notation to denote an upper bound that is not asymptotically tight. We formally define $o(g(n))$ ("little-oh of g of n") as the set:
$$
o(g(n)) = \{f(n): \text{for any positive constant } c > 0，\text{ there exists a constant}\\
n_0 > 0 \text{ such that } 0 \leq f(n) < cg(n) \text{ for all } n \geq n_0\}
$$
Intuitively, in $o$-notation, the function $f(n)$ becomes insignificant relative to $g(n)$ as $n$ approaches infinity; that is: $\lim_{n \to \infty} \frac{f(n)}{g(n)} = 0$.

**$\omega$-notation**

$\omega$-notation is to $\Omega$-notation as $o$-notation is to $O$-notation. We use $\omega$-notation to denote a lower bound that is not asymptotically tight. One way to define it is by: $f(n) \in \omega(g(n))$ if and only if $g(n) \in o(f(n))$.

, formally, however, we define $\omega(g(n))$ ("little-omega of g of n") as the set:
$$
\omega(g(n)) = \{f(n): \text{for any positive constant } c > 0, \text{there exists a constant}\\
n_0 > 0 \text{ such that } 0 \leq cg(n) \text{ for all } n \geq n_0\}
$$
, the relation $f(n) = \omega(g(n))$ implies that: $\lim_{n \to \infty} \frac{f(n)}{g(n)} = \infty$, if the limit exists. That is, $f(n)$ becomes arbitrarily large relative to $g(n)$ as $n$ approaches infinity.



## Time Complexity

The Time Complexity is not equal to the actual time required to execute a particular code, but the number of times a statement executes.



## Space Complexity

The term Space Complexity is misused for Auxiliary Space at many places. Following are the correct definitions of Auxiliary Space and Space Complexity.



## Reference

[1] Thomas H.Cormen; Charles E.Leiserson; Ronald L. Rivest; Clifford Stein . Introduction to Algorithms . 3ED

[2] Mark Allen Weiss . Data Structures and Algorithm Analysis in C++ . 4ED

[3] Yudong Jin . Hello Algorithms
