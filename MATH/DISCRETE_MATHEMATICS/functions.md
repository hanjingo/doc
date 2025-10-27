# Functions (Discrete Mathematics)

[TOC]

## Introduction

This note summarizes the core concepts about functions used in discrete mathematics. It organizes standard definitions, common properties, examples, proof techniques, and useful identities (such as floor/ceiling rules). The content follows and condenses material from Kenneth H. Rosen, Discrete Mathematics and Its Applications (8th ed.).

## Definition and notation

Let $A$ and $B$ be nonempty sets. A function (or mapping) $f$ from $A$ to $B$, written $f: A \to B$, assigns to each element of $A$ exactly one element of $B$. For $a\in A$ we write $f(a)=b$ and say $b$ is the image of $a$ and $a$ is a preimage of $b$.

- Domain: $A$.
- Codomain: $B$.
- Range (image): $f(A)=\{f(a)\mid a\in A\}$, a subset of $B$.

Functions between sets of numbers often support algebraic operations: if $f_1,f_2:A\to\mathbb{R}$ then define
$$
(f_1+f_2)(x)=f_1(x)+f_2(x),\qquad (f_1f_2)(x)=f_1(x)f_2(x).
$$

## Types of functions

- Injective (one-to-one): $f(a)=f(b)$ implies $a=b$ for all $a,b\in A$.
- Surjective (onto): for every $b\in B$ there exists $a\in A$ with $f(a)=b$.
- Bijective: both injective and surjective. Bijective functions have inverses.
- Partial function: a mapping defined on a subset of $A$ (the domain of definition). If the domain of definition equals $A$, the function is total.

## Inverse and composition

If $f:A\to B$ is bijective, the inverse function $f^{-1}:B\to A$ satisfies $f^{-1}(f(a))=a$ for all $a\in A$ and $f(f^{-1}(b))=b$ for all $b\in B$.

Let $g:A\to B$ and $f:B\to C$. The composition $f\circ g:A\to C$ is defined by $(f\circ g)(x)=f(g(x))$ for all $x\in A$. Composition is associative: $h\circ(f\circ g)=(h\circ f)\circ g$ when types match.

## Common properties and proof techniques

- To prove injectivity: assume $f(x)=f(y)$ and deduce $x=y$.
- To disprove injectivity: provide distinct $x,y$ with $f(x)=f(y)$.
- To prove surjectivity: take an arbitrary $b\in B$ and construct $a\in A$ with $f(a)=b$.
- To disprove surjectivity: find $b\in B$ with no preimage.
- To prove bijectivity: prove both injectivity and surjectivity (or construct an explicit inverse).

Examples:

- $f:\mathbb{Z}\to\mathbb{Z}$ defined by $f(n)=n+1$ is bijective (inverse $f^{-1}(n)=n-1$).
- $g:\mathbb{N}\to\mathbb{N}$ by $g(n)=2n$ is injective but not surjective when codomain is all naturals (odd numbers are not in the range).

## Special functions: monotonicity

For real-valued functions on an ordered domain:
- Increasing: $x<y\Rightarrow f(x)\le f(y)$.
- Strictly increasing: $x<y\Rightarrow f(x)<f(y)$.
- Decreasing and strictly decreasing are defined similarly.

Monotonicity often implies injectivity on the domain (a strictly monotone function is injective).

## Graph of a function

The graph of $f:A\to B$ is the set $\{(a,f(a))\mid a\in A\}\subseteq A\times B$. Graphs are useful to visualize and reason about functions.

## Floor and ceiling functions

The floor function $\lfloor x\rfloor$ assigns to real $x$ the greatest integer $\le x$. The ceiling function $\lceil x\rceil$ assigns the least integer $\ge x$.

Useful identities (for integer $n$ and real $x$):

- $\lfloor x\rfloor=n$ iff $n\le x<n+1$.
- $\lceil x\rceil=n$ iff $n-1<x\le n$.
- $\lfloor -x\rfloor=-\lceil x\rceil$, \quad $\lceil -x\rceil=-\lfloor x\rfloor$.
- $\lfloor x+n\rfloor=\lfloor x\rfloor+n$, \quad $\lceil x+n\rceil=\lceil x\rceil+n$.

Also: $x-1<\lfloor x\rfloor\le x\le\lceil x\rceil<x+1$.

## Equality of functions

Two functions $f,g:A\to B$ are equal if for every $x\in A$ we have $f(x)=g(x)$. Equality requires identical domain and codomain in formal contexts.

## Additional remarks

- Many proofs about functions use elementwise reasoning (pick arbitrary element of domain) and quantifier manipulation.
- In discrete mathematics, functions are often used to define sequences, recurrence relations, combinatorial constructions, and encodings between sets.

## Further reading and references

[1] Kenneth H. Rosen. Discrete Mathematics and Its Applications. 8th Edition.

