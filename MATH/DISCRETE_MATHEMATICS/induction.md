# Induction

[TOC]

## Introduction

This note collects the main forms of mathematical induction used in discrete mathematics, including ordinary (weak) induction, strong induction, and structural induction for recursively defined objects. It also summarizes related results (well-ordering principle, Lamé's theorem), recursive definitions, a few observations about recursive algorithms, and a short note on program correctness.

## Principle of mathematical induction

To prove a property $P(n)$ for all integers $n\ge b$ (typically $b=0$ or $1$), use two steps:

- Basis step: prove $P(b)$.
- Inductive step: assume $P(k)$ holds for an arbitrary $k\ge b$ (inductive hypothesis) and then prove $P(k+1)$.

Conclusion: by mathematical induction, $P(n)$ holds for every integer $n\ge b$.

Template (practical): state clearly the base value $b$, the inductive hypothesis, and how $P(k)$ implies $P(k+1)$. For many inequalities and combinatorial identities this is the standard method.

## Strong induction and the well-ordering principle

Strong induction assumes the truth of $P(1),P(2),\dots,P(k)$ and uses this to prove $P(k+1)$. It is logically equivalent to ordinary induction but often more convenient when $P(k+1)$ depends on several smaller values.

Well-ordering principle: every nonempty set of positive integers has a least element. The well-ordering principle, ordinary induction, and strong induction are equivalent (each can be proved from the others).

Example application: any simple polygon with $n\ge3$ sides can be triangulated into $n-2$ triangles; proofs often use induction on $n$. The Erdős–Szekeres monotone subsequence theorem (every sequence of $n^2+1$ distinct reals contains a monotone subsequence of length $n+1$) is another classic combinatorial application.

## Lamé's theorem (Euclidean algorithm)

Lamé's theorem: if $a\ge b>0$ are integers, the number of division steps performed by the Euclidean algorithm to compute $\gcd(a,b)$ is at most five times the number of decimal digits of $b$. The proof uses properties of Fibonacci numbers and an induction argument on the size of the operands.

## Structural induction and recursive definitions

Structural induction is the natural induction principle for objects defined recursively (strings, trees, expressions, etc.). The proof pattern is:

1. Show the property holds for each base constructor (base case).
2. For each recursive constructor, assume the property for the constituent parts and prove it for the constructed object.

Example recursive definitions:

- Strings: the set $\Sigma^*$ is defined by $\lambda\in\Sigma^*$ (empty string) and if $w\in\Sigma^*$ and $x\in\Sigma$ then $wx\in\Sigma^*$.
- Concatenation: defined by $w\cdot\lambda=w$ and $w_1\cdot(w_2x)=(w_1\cdot w_2)x$.
- Rooted trees: a single vertex is a rooted tree; if $T_1,\dots,T_n$ are disjoint rooted trees with roots $r_i$, adding a new root joined to each $r_i$ yields a rooted tree.
- Full binary trees: base case a single root; inductive step joins two full binary trees as left and right subtrees.

Height of a full binary tree $T$ is defined recursively by $h(T)=0$ for the single-vertex tree and $h(T)=1+\max(h(T_1),h(T_2))$ when $T$ is formed from $T_1$ and $T_2$. By induction one shows that a full binary tree of height $h$ has at most $2^{h+1}-1$ nodes.

## Recursive algorithms

An algorithm is recursive if it solves a problem by calling itself on smaller inputs. Common analysis techniques combine recurrence relations (e.g., $T(n)=2T(n/2)+\Theta(n)$ for merge sort) with tools like the Master theorem to obtain asymptotic bounds. For example, merge sort performs $\Theta(n\log n)$ comparisons in the worst case.

## Program correctness (brief)

Partial correctness: a program $S$ is partially correct with respect to precondition $p$ and postcondition $q$ (written $p\{S\}q$) if whenever $p$ holds before $S$ executes and $S$ terminates, then $q$ holds after execution.

Total correctness adds termination: $S$ is totally correct with respect to $p$ and $q$ if it is partially correct and it always terminates when started in a state satisfying $p$.

Hoare triples, loop invariants, and well-founded measures are standard tools for proving partial and total correctness; induction often appears when proving loop invariants or when reasoning about recursive procedures.

## References

[1] Kenneth H. Rosen. Discrete Mathematics and Its Applications. 8th Edition.
