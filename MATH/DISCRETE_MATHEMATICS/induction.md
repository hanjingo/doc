# Induction

[TOC]



**PRINCIPLE OF MATHEMATICAL INDUCTION** To prove that $P(n)$ is true for all positive integers $n$, where $P(n)$ is a propositional function, we complete two steps:

> **BASIS STEP**: We verify that $P(1)$ is true.
>
> **INDUCTIVE STEP**: We show that the conditional statement $P(k) \rightarrow P(k + 1)$ is true for all positive integers $k$.

**Template for Proofs by Mathematical Induction**:

1. Express the statement that is to be proved in the form "for all $n \geq b, P(n)$" for a fixed integer $b$. For statements of the form "$P(n)$ for all positive integers $n$", let $b = 1$, and for statements of the form "$P(n)$ for all nonnegative integers $n$", let $b = 0$. For some statements of the form $P(n)$, such as inequalities, you may need to determine the appropriate value of $b$ by checking the truth values of $P(n)$ for small values of $n$.
2. Write out the words "Basic Step". Then show that $P(b)$ is true, taking care that the correct value of $b$ is used. This completes the first part of the proof.
3. Write out the words "Inductive Step" and state, and clearly identify, the inductive hypothesis, in the form "Assume that $P(k)$ is true for an arbitrary fixed integer $k \geq b$".
4. State what needs to be proved under the assumption that the inductive hypothesis is true. That is, write out what $P(k + 1)$ says.
5. Prove the statement $P(k + 1)$ making use of the assumption $P(k)$. (Generally, this is the most difficult part of a mathematical induction proof. Decide on the most promising proof strategy and look ahead to see how to use the induction hypothesis to build your proof of the inductive step. Also, be sure that your proof is valid for all integers $k$ with $k \geq b$, taking care that the proof works for small values of $k$, including $k = b$.)
6. Clearly identify the conclusion of the inductive step, such as by saying "This completes the inductive step".
7. After completing the basis step and the inductive step, state teh conclusion, namely, "By mathematical induction, $P(n)$ is true for all integers $n$ with $n \geq b$".



## Strong Induction and Well-Ordering

**STRONG INDUCTION** To prove that $P(n)$ is true for all positive integers $n$, where $P(n)$ is a propositional function, we complete two steps:

> **BASIS STEP**: We verify that the proposition $P(1)$ is true.
>
> **INDUCTIVE STEP**: We show that the conditional statement $[P(1) \wedge P(2) \wedge \cdots \wedge P(k)] \rightarrow P(k + 1)$ is true for all positive integers $k$.

**THEOREM** A simple polygon with $n$ sides, where $n$ is an integer with $n \geq 3$, can be triangulated into $n - 2$ triangles.

**LEMMA** Every simple polygon with at least four sides has an interior diagonal.



## Recursive Definitions and Structural Induction

**THEOREM** LAME'S THEOREM: Let $a$ and $b$ be positive integers with $a \geq b$. Then the number of divisions used by the Euclidean algorithm to find $gcd(a, b)$ is less than or equal to five times the number of decimal digits in $b$.

**Definition** The set $\sum^{*}$ of `strings` over the alphabet $\sum$ is defined recursively by:

> **BASIS STEP**: $\lambda \in \sum^{*}$ (where $\lambda$ is the empty string containing no symbols).
>
> **RECURSIVE STEP**: If $w \in \sum^{*}$ and $x \in \sum$, then $wx \in \sum^{*}$.

**Definition** Two strings can be combined via the operation of `concatenation`. Let $\sum$ be a set of symbols and $\sum^{*}$ the set of strings formed from symbols in $\sum$. We can define the concatenation of two strings, denoted by $\cdot$, recursively as follow:

> **BASIS STEP**: If $w \in \sum^{*}$, then $w \cdot \lambda = w$, where $\lambda$ is the empty string.
>
> **RECURSIVE STEP**: If $w_1 \in \sum^{*}$ and $w_2 \in \sum^{*}$ and $x \in \sum$, then $w_1 \cdot (w_2 x) = (w_1 \cdot w_2)x$.

**Definition** The set of `rooted trees`, where a rooted tree consists of a set of vertices containing a distinguished vertex called the `root`, and edges connecting these vertices, can be defined recursively by these steps:

> **BASIS STEP**: A single vertex $r$ is a rooted tree.
>
> **RECURSIVE STEP**: Suppose that $T_1, T_2, \cdots, T_n$ are disjoint rooted trees with roots $r_1, r_2, \cdots, r_n$, respectively. Then the graph formed by starting with a root $r$, which is not in any of the rooted trees $T_1, T_2, \cdots, T_n$, and adding an edge from $r$ to each of the vertices $r_1, r_2, \cdots, r_n$, is also a rooted tree.

**Definition** The set of `extended binary trees` can be defined recursively by these steps:

> **BASIS STEP**: The empty set is an extended binary tree.
>
> **RECURSIVE STEP**: If $T_1$ and $T_2$ are disjoint extended binary trees, there is an extended binary tree, denoted by $T_1 \cdot T_2$, consisting of a root $r$ together with edges connecting the root to each of the roots of the left subtree $T_1$ and the right subtree $T_2$ when these trees are nonempty.

**Definition** The set of full binary trees can be defined recursively by these steps:

> **BASIS STEP**: There is a full binary tree consisting only of a single vertex $r$.
>
> **RECURSIVE STEP**: If $T_1$ and $T_2$ are disjoint full binary trees, there is a full binary tree, denoted by $T_1 \cdot T_2$, consisting of a root $r$ together with edges connecting the root to each of the roots of the left subtree $T_1$ and the right subtree $T_2$.

**Definition** We define the height $h(T)$ of a full binary tree $T$ recursively.

> **BASIS STEP**: The height of the full binary tree $T$ consisting of only a root $r$ is $h(T) = 0$.
>
> **RECURSIVE STEP**: If $T_1$ and $T_2$ are full binary trees, then the full binary tree $T = T_1 \cdot T_2$ has hight $h(T) = 1 + max(h(T_1), h(T_2))$.

**THEOREM** If $T$ is a full binary tree $T$, then $n(T) \leq 2^{h(T) + 1} - 1$.



## Recursive Algorithms

**Definition** An algorithm is called `recursive` is it solves a problem by reducing it to an instance of the same problem with smaller input.

**THEOREM** The number of comparisons needed to merge sort a list with $n$ elements is $O(n \log n)$.



## Program Correctness

**Definition** A program, or program segment, $S$ is said to be `partially correct with respect to` the initial assertion $p$ and the final assertion $q$ if whenever $p$ is true for the input values of $S$ and $S$ terminates, then $q$ is true for the output values of $S$. The notation $p \{S\} q$ indicates that the program, or program segment, $S$ is partially correct with respect to the initial assertion $p$ and the final assertion $q$.
