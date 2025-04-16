# Functions

[TOC]



## Definition

**Definition**: Let $A$ and $B$ be nonempty sets. A `function f` from $A$ to $B$ is an assignment of exactly one element of $B$ to each element of $A$. We write $f(a) = b$ if $b$ is the unique element of $B$ assigned by the function $f$ to the element $a$ of $A$. If $f$ is a function from $A$ to $B$, we write $f: A \rightarrow B$.

**Definition**: If $f$ is a function from $A$ to $B$, we say that $A$ is the `domain` of $f$ and $B$ is the `codomain` of $f$. If $f(a) = b$, we say that $b$ is the `image` of $a$ and $a$ is a preimage of $b$. The `range`, or `image`, of $f$ is the set of all images of elements of $A$. Also, if $f$ is a function from $A$ to $B$, we say that $f$ maps $A$ to $B$.

**Definition**: Let $f_1$ and $f_2$ be functions from $A$ to $R$. Then $f_1 + f_2$ and $f_1 f_2$ are also functions from $A$ to $R$ defined for all $x \in A$ by:
$$
(f_1 + f_2)(x) = f_1(x) + f_2(x), \\
(f_1 f_2)(x) = f_1(x) f_2(x).
$$
**Definition**: Let $f$ be a function from $A$ to $B$ and let $S$ be a subset of $A$. The `image` of $S$ under the function $f$ is the subset of $B$ that consists of the images of the elements of $S$. We denote the image of $S$ by $f(S)$, so:
$$
f(S) = \{t | \exists s \in S (t = f(s))\}.
$$
, We also use the shorthand $\{f(s) | s \in S\}$ to denote this set.

**Definition**: A function $f$ is said to be `one-to-one`, if and only if $f(a) = f(b)$ implies that $a = b$ for all $a$ and $b$ in the domain of $f$. A function is said to be `injective` if it is one-to-one.

**Definition**: A function $f$ whose domain and codomain are subsets of the set of real numbers is called `increasing` if $f(x) \leq f(y)$, and `strictly increasing` if $f(x) < f(y)$, whenever $x < y$ and $x$ and $y$ are in the domain of $f$. Similarly, $f$ is called `decreasing` if $f(x) \geq f(y)$, and `strictly decreasing` if $f(x) > f(y)$, whenever $x < y$ and $x$ and $y$ are in the domain of $f$. (The word `strictly` in this definition indicates a strict inequality.)

**Definition**: A function $f$ from $A$ to $B$ is called `onto`, or a `surjection`, if and only if for every element $b \in B$ there is an element $a \in A$ with $f(a) = b$. A function $f$ is called `surjective` if it is onto.

**Definition**: The function $f$ is a `one-to-one correspondence`, or a `bijection`, if it is both one-to-one and onto. We also say that such a function is `bijective`.

**Definition**: Let $f$ be a one-to-one correspondence from the set $A$ to the set $B$. The `inverse function` of $f$ is the function that assigns to an element $b$ belonging to $B$ the unique element $a$ in $A$ such that $f(a) = b$. The inverse function of $f$ is denoted by $f^{-1}$. Hence, $f^{-1}(b) = a$ when $f(a) = b$.

**Definition**: Let $g$ be a function from the set $A$ to the set $B$ and let $f$ be a function from the set $B$ to the set $C$. The `composition` of the functions $f$ and $g$, denoted for all $a \in A$ by $f \cdot g$, is the function from $A$ to $C$ defined by $(f \cdot g)(a) = f(g(a))$.

**Definition**: Let $f$ be a function from the set $A$ to the set $B$. The `graph` of the function $f$ is the set of ordered pairs $\{(a,b) | a \in A \text{ and } f(a) = b\}$.

**Definition**: The `floor` function assigns to the real number $x$ the largest integer that is less than or equal to $x$. The value of the floor function at $x$ is denoted by $\lfloor x \rfloor$. The `ceiling function` assigns to the real number $x$ the smallest integer that is greater than or equal to $x$. The value of the ceiling function at $x$ is denoted by $\lceil x \rceil$.

**Definition**: A `partial function f` from a set $A$ to a set $B$ is an assignment to each element $a$ in a subset of $A$, called the `domain of definition` of $f$, of a unique element $b$ in $B$. The sets $A$ and $B$ are called the `domain and codomain` of $f$, respectively. We say that $f$ is `undefined` for elements in $A$ that are not in the domain of the definition of $f$. When the domain of definition of $f$ equals $A$, we say that $f$ is a total function.



## Claim

Two functions are **equal** when they have the same domain, have the same codomain, and map each element of their common domain to the same element in their common codomain.

Suppose that $f: A \rightarrow B$.

> **To show that $f$ is injective** Show that if $f(x) = f(y)$ for arbitrary $x, y \in A, then\ x = y$ .
>
> **To show that $f$ is not injective** Find particular elements $x, y \in A$ such that $x \neq y$ and $f(x) = f(y)$.
>
> **To show that $f$ is surjective** Consider an arbitrary element $y \in B$ and find an element $x \in A$ such that $f(x) = y$.
>
> **To show that $f$ is not surjective** Find a particular $y \in B$ such that $f(x) \neq y$ for all $x \in A$.

A one-to-one correspondence is called **invertible** because we can define an inverse of this function. A function is **not invertible** if it is not a one-to-one correspondence, because the inverse of such a function does not exist.

| Useful Properties of the Floor and Ceiling Functions. ($n$ is an integer, $x$ is a real number) |
| ------------------------------------------------------------ |
| $\lfloor x \rfloor = n \text{ if and only if } n \leq x < n + 1$<br>$\lceil x \rceil = n \text{ if and only if } n - 1 < x \leq n$<br>$\lfloor x \rfloor = n \text{ if and only if } n - 1 < n \leq x$<br>$\lceil x \rceil = n \text{ if and only if } x \leq n < x + 1$ |
| $x - 1 < \lceil x \rceil \leq x \leq \lceil x \rceil < x + 1$ |
| $\lfloor -x \rfloor = -\lceil x \rceil$<br>$\lceil -x \rceil = -\lfloor x \rfloor$ |
| $\lfloor x + n \rfloor = \lfloor x \rfloor + n$<br>$\lceil x + n \rceil = \lceil x \rceil + n$ |



## References

[1] Kenneth H. Rosen . Discrete Mathematics and Its Applications . 8Edition
