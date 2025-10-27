# Generalized Permutations and Combinations

[TOC]

## Introduction

This note summarizes the counting rules and standard formulas used in permutations and combinations, including generalized cases with repetition and indistinguishable objects. The content condenses material from Kenneth H. Rosen's Discrete Mathematics and Its Applications (8th ed.) and highlights key identities and short remarks about proofs.

## Basic counting rules

- Product rule: If a procedure consists of two tasks where the first can be done in $n_1$ ways and for each such way the second can be done in $n_2$ ways, then the whole procedure can be done in $n_1n_2$ ways. This extends to any fixed number of sequential tasks.
- Sum rule: If a task can be done either in one of $n_1$ ways or in one of $n_2$ ways and the two sets of ways are disjoint, then there are $n_1+n_2$ ways to do the task.
- Subtraction (inclusion–exclusion for two sets): If some ways are counted by both of two choices, subtract the overlap: $|A\cup B|=|A|+|B|-|A\cap B|$.
- Division rule: If each outcome of interest corresponds to exactly $d$ outcomes of a larger procedure that can be executed in $n$ ways, then the number of distinct outcomes of interest is $n/d$.

Combinatorial proofs: A combinatorial (counting) proof shows that two expressions are equal by interpreting both as counts of the same set (double counting) or by giving an explicit bijection between the two sets counted.

## Pigeonhole principle

- Basic pigeonhole principle: If $k+1$ or more objects are placed into $k$ boxes, some box contains at least two objects.
- Generalized version: If $N$ objects are placed into $k$ boxes, some box contains at least $\lceil N/k\rceil$ objects.

Remark: These principles give simple existence results and are often used in combinatorial proofs.

## Permutations and combinations (distinct objects)

- $r$-permutations (ordered selections without repetition) of $n$ distinct objects:
	$$P(n,r)=n(n-1)(n-2)\\cdots(n-r+1)=\\frac{n!}{(n-r)!}.$$ 
- $r$-combinations (unordered selections without repetition) of $n$ distinct objects:
	$$\\binom{n}{r}=\\frac{n!}{r!(n-r)!}.$$ 

Symmetry: $\\binom{n}{r}=\\binom{n}{n-r}$.

Binomial theorem: For variables $x,y$ and nonnegative integer $n$,
$$ (x+y)^n=\\sum_{j=0}^n\\binom{n}{j}x^{n-j}y^j. $$

Pascal's identity: $\\binom{n+1}{k}=\\binom{n}{k-1}+\\binom{n}{k}$. This is often proved combinatorially by classifying $k$-subsets of an $(n+1)$-set by whether they contain a distinguished element.

Vandermonde's identity: For nonnegative integers $m,n,r$,
$$ \\binom{m+n}{r}=\\sum_{k=0}^r\\binom{m}{r-k}\\binom{n}{k}, $$
which counts $r$-subsets of an $(m+n)$-set by how many elements come from the first $m$.

Hockey-stick identity: For $0\\le r\\le n$,
$$ \\binom{n+1}{r+1}=\\sum_{j=r}^n\\binom{j}{r}. $$

Useful binomial sums (special cases):
- $\\sum_{k=0}^n\\binom{n}{k}=2^n$.
- $\\sum_{k=0}^n(-1)^k\\binom{n}{k}=0$ for $n\\ge1$.
- $\\sum_{k=0}^n2^k\\binom{n}{k}=3^n$.
- $\\binom{2n}{n}=\\sum_{k=0}^n\\binom{n}{k}^2$ (central binomial via Vandermonde with $m=n$ and $r=n$).

## Repetition and indistinguishability

- Ordered selections with repetition allowed (sequence of length $r$ from $n$ types): $n^r$.
- Unordered selections with repetition allowed (multicombinations, stars and bars): the number of $r$-combinations from $n$ types with repetition is
	$$\\binom{n+r-1}{r}=\\binom{n+r-1}{n-1}. $$ 
	This follows from the stars-and-bars argument or a bijection to weak compositions.
- Permutations of multiset (indistinguishable objects): If an $n$-element multiset has multiplicities $n_1,n_2,\\dots,n_k$ with $\\sum_i n_i=n$, then the number of distinct permutations is
	$$\\frac{n!}{n_1!\\,n_2!\\cdots n_k!},$$
	often called the multinomial coefficient in the context of expanding $(x_1+\\cdots+x_k)^n$.

## Short examples

- Example (multicombination): Number of ways to choose 3 donuts from 5 types (repetition allowed) is $\\binom{5+3-1}{3}=\\binom{7}{3}=35$.
- Example (permutations with repetition): Distinct arrangements of the letters of "MISSISSIPPI" use the multiset formula with multiplicities for M,I,S,P.

## Corollaries and remarks

- Any function from a set of size $k+1$ to a set of size $k$ cannot be injective (pigeonhole principle).
- Many combinatorial identities admit both algebraic and combinatorial proofs; providing a combinatorial proof often clarifies why the identity is true.

## References

[1] Kenneth H. Rosen. Discrete Mathematics and Its Applications. 8th Edition.
