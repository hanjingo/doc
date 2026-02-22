# Chapter2 Basic Structures: Sets, Functions, Sequences, Sums, and Matrices

[TOC]

**Definition**: A `set` is an unordered collection of distinct objects, called `elements or members` of the set. A set is said to `contain` its elements. We write $a \in A$ to denote that $a$ is an element of the set A. The notation $a \notin A$ denotes that $a$ is not an element of the set A.

There are several ways to describe a set:

1. One way is to list all the members of a set, when this is possible. We use a notation where all members of the set are listed between braces. This way of describing a set is known as the **roster method**.
2. Another way to describe a set to use **set builder** notation. We characterize all those elements in the set by stating the property or properties they must have to be members. The general form of this notation is $\{x | x \text{ has property } P\}$ and is read "the set of all $x$ such that $x$ has property $P$".

If $a$ and $b$ are real numbers with $a \le b$, we denote these intervals by:
$$
[a, b] = \{x | a \leq x \leq b\} \\
[a, b) = \{x | a \leq x < b\} \\
(a, b] = \{x | a < x \leq b\} \\
(a, b) = \{x | a < x < b\}.
$$
, Note that $[a, b]$ is called the **closed interval** from $a$ to $b$ and $(a, b)$ is called the **open interval** from $a$ to $b$.

**Definition**: Two sets are `equal` if and only if they have the same elements. Therefore, if $A$ and $B$ are sets, then $A$ and $B$ are equal if and only if $\forall x (x \in A \leftrightarrow x \in B)$. We write $A = B$ if $A$ and $B$ are equal sets.

**THE EMPTY SET** There is a special set that has no elements. This set is called the **empty set**, or **null set**, and is denoted by $\emptyset$. The empty set can also be denoted by $\{\}$(that is, we represent the empty set with a pair of braces that encloses all the elements in this set).

A set with one element is called a **singleton set**.

**Definition**: The set $A$ is a `subset` of $B$, and $B$ is a `superset` of $A$, if and only if every element of $A$ is also an element of $B$. We use the notation $A \subseteq B$ to indicate that $A$ is a subset of the set $B$. If, instead, we want to stress that $B$ is a superset of $A$, we use the equivalent notation $B \supe A$. (So, $A \subseteq B$ and $B \supe A$ are equivalent statements.)

We have these useful rules for determining whether one set is a subset of another:

- **Showing that A is a Subset of B** To show that $A \subseteq B$, show that if $x$ belongs to $A$ then $x$ also belongs to $B$.
- **Showing that A is Not a Subset of B** To show that $A \subsetneq B$, find a single $x \in A$ such that $x \notin B$.

**THEOREM**: For every set $S, (i) \phi \subseteq S$ and $S \subseteq S$.

**Definition**: Let $S$ be a set. If there are exactly $n$ distinct elements in $S$ where $n$ is a nonnegative integer, we say that $S$ is a `finite set` and that $n$ is the `cardinality` of $S$. The cardinality of $S$ is denoted by $|S|$.

**Definition**: A set is said to be `infinite` if it is not finite.

**Definition**: Given a set $S$, the `power set` of $S$ is the set of all subsets of the set $S$. The power set of $S$ is denoted by $P(S)$.

**Definition**: The `ordered n-tuple`$(a_1, a_2, ..., a_n)$ is the ordered collection that has $a_1$ as its first element, $a_2$ as its second element, ..., and $a_n$ as its $n$th element.

**Definition**: Let $A$ and $B$ be sets. The `Cartesian product` of $A$ and $B$, denoted by $A \times B$, is the set of all ordered pairs $(a, b)$, where $a \in A$ and $b \in B$. Hence: $A \times B = \{(a, b) | a \in A \wedge b \in B\}$.

**Definition**: The `Cartesian product` of the sets $A_1, A_2, ..., A_n$ denoted by $A_1 \times A_2 \times ... \times A_n$, is the set of ordered $n$-tuples $(a_1, a_2, ..., a_n)$, where $a_i$ belongs to $A_i$ for $i = 1, 2, ..., n$. In other words, $A_1 \times A_2 \times ... A_n = \{(a_1, a_2, ..., a_n)|a_i \in A_i\ for\ i = 1, 2, ..., n\}$.

Given a predicate $P$, and a domain $D$, we define the **truth set** of $P$ to be the set of elements $x$ in $D$ for which $P(x)$ is true. The truth set of $P(x)$ is denoted by $\{x \in D | P(x)\}$.



## Set Operations

**Definition**: Let $A$ and $B$ be sets. The `union` of the sets $A$ and $B$, denoted by $A \cup B$, is the set that contains those elements that are either in $A$ or in $B$, or in both.

**Definition**: Let $A$ and $B$ be sets. The `intersection` of the sets $A$ and $B$, denoted by $A \cap B$, is the set containing those elements in both $A$ and $B$.

**Definition**: Two sets are called `disjoint` if their intersection is the empty set.

**Definition**: Let $A$ and $B$ sets. The `difference` of $A$ and $B$, denoted by $A - B$, is the set containing those elements that are in $A$ but not in $B$. The difference of $A$ and $B$ is also called the `complement of` $B$ `with respect to` $A$.

**Definition**: let $U$ be the universal set. The `complement` of the set $A$, denoted by $\overline{A}$, is the complement of $A$ with respect to $U$. Therefore, the complement of the set $A$ is $U - A$.

| Set Identities                                               |                     |
| ------------------------------------------------------------ | ------------------- |
| Identity                                                     | Name                |
| $A \cap U = A$<br>$A \cup \phi = A$                          | Identity laws       |
| $A \cup U = U$<br>$A \cap \phi = \phi$                       | Domination laws     |
| $A \cup A = A$<br>$A \cap A = A$                             | Idempotent laws     |
| $\overline{(\overline{A})} = A$                              | Complementation law |
| $A \cup B = B \cup A$<br>$A \cap B = B \cap A$               | Commutative laws    |
| $A \cup (B \cup C) = (A \cup B) \cup C$<br>$A \cap (B \cap C) = (A \cap B) \cap C$ | Associative laws    |
| $A \cup (B \cap C) = (A \cup B) \cap (A \cup C)$<br>$A \cap (B \cup C) = (A \cap B) \cup (A \cap C)$ | Distributive laws   |
| $\overline{A \cap B} = \overline{A} \cup \overline{B}$<br>$\overline{A \cup B} = \overline{A} \cap \overline{B}$ | De Morgan's laws    |
| $A \cup (A \cap B) = A$<br>$A \cap (A \cup B) = A$           | Absorption laws     |
| $A \cup \overline{A} = U$<br>$A \cap \overline{A} = \phi$    | Complement laws     |

**Definition**: The `union` of a collection of sets is the set that contains those elements that are members of at least one set in the collection.

> We use the notation $A_1 \cup A_2 \cup ... \cup A_n = \underset{i=1}{\overset{n}{\bigcup}} A_i$ to denote the union of the sets $A_1, A_2, ..., A_n$.

**Definition**: The `intersection` of a collection of sets is the set that cotains those elements that are members of all the sets in the collection.

> We use the notation $A_1 \cap A_2 \cap ... \cap A_n = \overset{n}{\underset{i=1}{\bigcap}} A_i$ to denote the intersection of the sets $A_1, A_2, ..., A_n$.



## Functions

**Definition**: Let $A$ and $B$ be nonempty sets. A `function f` from $A$ to $B$ is an assignment of exactly one element of $B$ to each element of $A$. We write $f(a) = b$ if $b$ is the unique element of $B$ assigned by the function $f$ to the element $a$ of $A$. If $f$ is a function from $A$ to $B$, we write $f: A \rightarrow B$.

**Definition**: If $f$ is a function from $A$ to $B$, we say that $A$ is the `domain` of $f$ and $B$ is the `codomain` of $f$. If $f(a) = b$, we say that $b$ is the `image` of $a$ and $a$ is a preimage of $b$. The `range`, or `image`, of $f$ is the set of all images of elements of $A$. Also, if $f$ is a function from $A$ to $B$, we say that $f$ maps $A$ to $B$.

Two functions are **equal** when they have the same domain, have the same codomain, and map each element of their common domain to the same element in their common codomain.

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

Suppose that $f: A \rightarrow B$.

> **To show that $f$ is injective** Show that if $f(x) = f(y)$ for arbitrary $x, y \in A, then\ x = y$ .
>
> **To show that $f$ is not injective** Find particular elements $x, y \in A$ such that $x \neq y$ and $f(x) = f(y)$.
>
> **To show that $f$ is surjective** Consider an arbitrary element $y \in B$ and find an element $x \in A$ such that $f(x) = y$.
>
> **To show that $f$ is not surjective** Find a particular $y \in B$ such that $f(x) \neq y$ for all $x \in A$.

**Definition**: Let $f$ be a one-to-one correspondence from the set $A$ to the set $B$. The `inverse function` of $f$ is the function that assigns to an element $b$ belonging to $B$ the unique element $a$ in $A$ such that $f(a) = b$. The inverse function of $f$ is denoted by $f^{-1}$. Hence, $f^{-1}(b) = a$ when $f(a) = b$.

A one-to-one correspondence is called **invertible** because we can define an inverse of this function. A function is **not invertible** if it is not a one-to-one correspondence, because the inverse of such a function does not exist.

**Definition**: Let $g$ be a function from the set $A$ to the set $B$ and let $f$ be a function from the set $B$ to the set $C$. The `composition` of the functions $f$ and $g$, denoted for all $a \in A$ by $f \cdot g$, is the function from $A$ to $C$ defined by $(f \cdot g)(a) = f(g(a))$.

**Definition**: Let $f$ be a function from the set $A$ to the set $B$. The `graph` of the function $f$ is the set of ordered pairs $\{(a,b) | a \in A \text{ and } f(a) = b\}$.

**Definition**: The `floor` function assigns to the real number $x$ the largest integer that is less than or equal to $x$. The value of the floor function at $x$ is denoted by $\lfloor x \rfloor$. The `ceiling function` assigns to the real number $x$ the smallest integer that is greater than or equal to $x$. The value of the ceiling function at $x$ is denoted by $\lceil x \rceil$.

| Useful Properties of the Floor and Ceiling Functions. ($n$ is an integer, $x$ is a real number) |
| ------------------------------------------------------------ |
| $\lfloor x \rfloor = n \text{ if and only if } n \leq x < n + 1$<br>$\lceil x \rceil = n \text{ if and only if } n - 1 < x \leq n$<br>$\lfloor x \rfloor = n \text{ if and only if } n - 1 < n \leq x$<br>$\lceil x \rceil = n \text{ if and only if } x \leq n < x + 1$ |
| $x - 1 < \lceil x \rceil \leq x \leq \lceil x \rceil < x + 1$ |
| $\lfloor -x \rfloor = -\lceil x \rceil$<br>$\lceil -x \rceil = -\lfloor x \rfloor$ |
| $\lfloor x + n \rfloor = \lfloor x \rfloor + n$<br>$\lceil x + n \rceil = \lceil x \rceil + n$ |

**Definition**: A `partial function f` from a set $A$ to a set $B$ is an assignment to each element $a$ in a subset of $A$, called the `domain of definition` of $f$, of a unique element $b$ in $B$. The sets $A$ and $B$ are called the `domain and codomain` of $f$, respectively. We say that $f$ is `undefined` for elements in $A$ that are not in the domain of the definition of $f$. When the domain of definition of $f$ equals $A$, we say that $f$ is a total function.



## Sequences and Summations

**Definition**: A `sequence` is a function from a subset of the set of integers (usually either the set $\{0, 1, 2, ...\}$ or the set $\{1, 2, 3, ...\}$) to a set $S$. We use the notation $a_n$ to denote the image of the integer $n$. We call $a_n$ a term of the sequence.

**Definition**: A `geometric progression` is a sequence of the form $a, ar, ar^2, ..., ar^n, ...$ where the `initial term a` and the `common ratio r` are real numbers.

**Definition**: An `arithmetic progression` is a sequence of the form $a, a + d, a + 2d, ..., a + nd, ...$ where the `initial term a` and the `common difference d` are real numbers.

**Definition**: A `recurrence relation` for the sequence $\{a_n\}$ is an equation that expresses $a_n$ in terms of one or more of the previous terms of the sequence, namely, $a_0, a_1, ..., a_{n - 1}$, for all integers $n$ with $n \geq n_0$, where $n_0$ is a nonnegative integer. A sequence is called a `solution` of a recurrence relation if it's terms satisfy the recurrence relation.

**Definition**: The `Fibonacci sequence`, $f_0, f_1, f_2, ...$, is defined by the initial conditions $f_0 = 0, f_1 = 1$, and the recurrence relation $f_n = f_{n - 1} + f_{n - 2}$ for $n = 2, 3, 4, ...$.

**Summation notation**, We begin by describing the notation used to express the sum of the terms: $a_m, a_{m + 1}, ..., a_n$ from the sequence $\{a_n\}$. We use the notation:
$$
\sum_{j=m}^{n}a_j, \sum_{j=m}^{n}a_j, or \sum_{m \leq j \leq n}a_j
$$
, (read as the sum from $j = m$ to $j = n$ of $a_j$) to represent:
$$
a_m + a_{m + 1} + ... + a_n
$$
, Here, the variable $j$ is called the **index of summation**, and the choice of the letter $j$ as the variable is arbitrary; that is, we could have used any other letter, such as $i$ or $k$. Or, in notation, here, the index of summation runs through all integers starting with its **lower limit** $m$ and ending with its **upper limit** $n$. A large uppercase Greek letter sigma, $\sum$, is used to denote summation.

**THEOREM** If $a$ and $r$ are real numbers and $r \neq 0$, then:
$$
\sum_{j = 0}^{n} ar^j = 
\begin{cases}
\frac{ar^{n + 1} - a}{r - 1} &if\ r \neq 1 \\
(n + 1)a &if\ r = 1
\end{cases}
$$


## Cardinality of Sets

**Definition**: The sets $A$ and $B$ have the same `cardinality` if and only if there is a one-to-one correspondence from $A$ to $B$. When $A$ and $B$ have the same cardinality, we write $|A| = |B|$.

**Definition**: If there is a one-to-one function from $A$ to $B$, the cardinality of $A$ is less than or the same as the cardinality of $B$ and we write $|A| \leq |B|$. Moreover, when $|A| \leq |B|$ and $A$ and $B$ have different cardinality, we way that the cardinality of $A$ is less than the cardinality of $B$ and we write $|A| < |B|$.

**THEOREM**: If $A$ and $B$ are countable sets, then $A \cup B$ is also countable.

**THEOREM**: If $A$ and $B$ are sets with $|A| \leq |B|$ and $|B| \leq |A|$, then $|A| = |B|$. In other words, if there are one-to-one functions $f$ from $A$ to $|B|$ and $g$ from $B$ to $A$, then there is a one-to-one correspondence between $A$ and $B$.

**Definition**: We say that a function is **computable** if there is a computer program in some programming language that finds the values of this function. If a function is not computable we say it is **uncomputable**.



## Matrix

**Definition**: A `matrix` is a rectangular array of numbers. A matrix with `m rows` and `n` columns is called an $m \times n$ matrix. The plural of matrix is `matrices`. A matrix with the same number of rows as columns is called `square`. Two matrices are `equal` if they have the same number of rows and the same number of columns and the corresponding entries in every position are equal.

**Definition** Let $m$ and $n$ be positive integers and let
$$
A = 
\begin{bmatrix}
a_{11} & a_{12} & \dots & a_{1n} \\
a_{21} & a_{22} & \dots & a_{2n} \\
\vdots & \vdots &       & \vdots \\
a_{m1} & a_{m2} & \dots & a_{mn}
\end{bmatrix}
$$
, The $i$th row of **A** is the $1 \times n$ matrix $[a_{i1}, a_{i2}, ..., a_{in}]$. The $j$th column of $A$ is the $m \times 1$ matrix:
$$
\begin{bmatrix}
a_{1j} \\
a_{2j} \\
\vdots \\
a_{mj}
\end{bmatrix}
$$
, The $(i, j)$th `element` or `entry` of $A$ is the element $a_{ij}$, that is, the number in the $i$th row and $j$th column of $A$. A convenient shorthand notation for expressing the matrix $A$ is to write $A = [a_{ij}]$, which indicates that $A$ is the matrix with its $(i,j)$th element equal to $a_{ij}$.

**Definition**: Let $A = [a_{ij}]$ and $B = [b_{ij}]$ be $m \times n$ matrices. The `sum of A` and `B`, denoted by $A + B$, is the $m \times n$ matrix that has $a_{ij} + b_{ij}$ as its $(i,j)$th element. In other words, $A + B = [a_{ij} + b_{ij}]$.

**Definition**: Let $A$ be an $m \times k$ matrix and $B$ be a $k \times n$ matrix. The `product` of $A$ and $B$, denoted by $AB$, is the $m \times n$ matrix with its $(i, j)$th entry equal to the sum of the products of the corresponding elements from the $i$th row of $A$ and the $j$th column of $B$. In other words, if $AB = [c_{ij}]$, then $c_{ij} = a_{i1}b_{1j} + a_{i2}b_{2j} + ... + a_{ik}b_{kj}$.

**Definition**: The `identity matrix of order n` is the $n \times n$ matrix $I_n = [\delta_{ij}]$, (the `Kronecker delta`) where $\delta_{ij} = 1$ if $i = j$ and $\delta_{ij} = 0$ if $i \neq j$. Hence:
$$
I_n = 
\begin{bmatrix}
1 & 0 & \dots & 0 \\
0 & 1 & \dots & 0 \\
\vdots & \vdots & & \vdots \\
0 & 0 & \dots & 1
\end{bmatrix}
$$
**Definition**: Let $A = [a_{ij}]$ be an $m \times n$ matrix. The `transpose` of $A$, denoted by $A^t$, is the $n \times m$ matrix obtained by interchanging the rows and columns of $A$. In other words, if $A^t = [b_{ij}]$, then $b_{ij} = a_{ji}$ for $i = 1, 2, ..., n$ and $j = 1, 2, ..., m$.

**Definition**: A square matrix $A$ is called `symmetric` if $A = A^t$. Thus, $A = [a_{ij}]$ is symmetric if $a_{ij} = a_{ji}$ for all $i$ and $j$ with $1 \leq i \leq n$ and $1 \leq j \leq n$.

A matrix all of whose entries are either 0 or 1 is called a **zero-one matrix**.

**Definition**: Let $A = [a_{ij}]$ and $B = [b_{ij}]$ be $m \times n$ zero-one matrices. Then the `join` of $A$ and $B$ is the zero-one matrix with $(i,j)$th entry $a_{ij} \vee b_{ij}$. The join of $A$ and $B$ is denoted by $A \vee B$. The `meet` of $A$ and $B$ is the zero-one matrix with $(i,j)$th entry $a_{ij} \wedge b_{ij}$. The meet of $A$ and $B$ is denoted by $A \wedge B$.

**Definition**: Let $A = [a_{ij}]$ be an $m \times k$ zero-one matrix and $B = [b_{ij}]$ be a $k \times n$ zero-one matrix. Then the `Boolean product` of $A$ and $B$, denoted by $A \odot B$, is the $m \times n$ matrix with $(i,j)$th entry $c_{ij}$ where: $c_{ij} = (a_{i1} \wedge b_{1j}) \vee (a_{i2} \wedge b_{2j}) \vee ... \vee (a_{ik} \wedge b_{kj})$.

**Definition**: Let $A$ be a square zero-one matrix and let $r$ be a positive integer. The $r$th `Boolean power` of $A$ is the Boolean product of $r$ factors of $A$. The $r$th Boolean product of $A$ is denoted by $A^{[r]}$. Hence:
$$
A^{[r]} = \underbrace{A \odot A \odot A \odot ... \odot A.}_{r\ times}
$$
, (This is well defined because the Boolean product of matrices is associative.) We also define $A^{[0]}$ to be $I_n$.



## TERMS

- **set**: an unordered collection of distinct objects.
- **axiom**: a basic assumption of a theory.
- **paradox**: a logical inconsistency.
- **element, member of a set**: an object in a set.
- **roster method**: a method that describes a set by listing its elements.
- **set builder notation**: the notation that describes a set by stating a property an element must have to be a member.
- **multiset**: an unordered collection of objects where objects can occur multiple times.
- **$\emptyset$(empty set, null set)**: the set with no members.
- **universal set**: the set containing all objects under consideration.
- **Venn diagram**: a graphical representation of a set or sets.
- **$S = T$ (set equality)**: $S$ and $T$ have the same elements.
- **$S \subseteq T$ (S is a subset of T)**: every element of $S$ is also an element of T.
- **$S \subset T$ (S is a proper subset of T)**: $S$ is a subset of $T$ and $S \neq T$.
- **finite set**: a set with $n$ elements, where $n$ is a nonnegative integer.
- **infinite set**: a set that is not finite.
- **|S| (the cardinality of S)**: the number of elements in $S$.
- **P(S) (the power set of S)**: the set of all subsets of $S$.
- **$A \cup B$ (the union of A and B)**: the set containing those elements that are in at least one of A and B.
- **$A \cap B$ (the intersection of A and B)**: the set containing those elements that are in both $A$ and $B$.
- **$A - B$ (the difference of A and B)**: the set containing those elements that are in $A$ but not in $B$.
- **$\overline{A}$ (the complement of A)**: the set of elements in the universal set that are not in $A$.
- **$A \oplus B$ (the symmetric difference of A and B)**: the set containing those elements in exactly one of $A$ and $B$.
- **membership table**: a table displaying the membership of elements in sets.
- **function from $A$ to $B$**: an assignment of exactly one element of $B$ to each element of $A$.
- **domain of $f$**: the set $A$, where $f$ is a function from $A$ to $B$.
- **codomain of $f$**: the set $B$, where $f$ is a function from $A$ to $B$.
- **$b$ is the image of $a$ under f**: $b = f(a)$.
- **$a$ is a preimage of $b$ under $f$**: $f(a) = b$.
- **range of $f$**: the set of images of $f$.
- **onto function, surjection**: a function from $A$ to $B$ such that every element of $B$ is the image of some element in $A$.
- **one-to-one function, injection**: a function such that the images of images of elements in its domain are distinct.
- **one-to-one correspondence, bijection**: a function that is both one-to-one and onto.
- **inverse of $f$**: the function that reverses the correspondence given by $f$ (when $f$ is a bijection).
- **$f \circ g$ (composition of $f$ and $g$)**: the function that assigns $f(g(x))$ to $x$.
- **$\lfloor x \rfloor$ (floor function)**: the largest integer not exceeding $x$.
- **$\lceil x \rceil$ (ceiling function)**: the smallest integer greater than or equal to $x$.
- **partial function**: an assignment to each element in a subset of the domain a unique element in the codomain.
- **sequence**: a function with domain that is a subset of the set of integers.
- **geometric progression**: a sequence of the form $a, ar, ar^2, ...$, where $a$ and $r$ are real numbers.
- **arithmetic progression**: a sequence of the form $a, a + d, a + 2d, ...$, where $a$ and $d$ are real numbers.
- **string**: a finite sequence.
- **empty string**: a string of length zero.
- **recurrence relation**: an equation that expresses the $n$th term $a_n$ of a sequence in terms of one or more of the previous terms of the sequence for all integers $n$ greater than a particular integer.
- **$\sum_{i = 1}^{n}a_i$**: the sum $a_1 + a_2 + ... + a_n$.
- $\prod_{i=1}^{n}a_i$: the product $a_1 a_2 ... a_n$.
- **cardinality**: two sets $A$ and $B$ have the same cardinality if there is a  one-to-one correspondence from A to B.
- **countable set**: a set that either is finite or can be placed in one-to-one correspondence with the set of positive integers.
- **uncountable set**: a set that is not countable.
- **(aleph null)**: the cardinality of a countable set.
- **$c$**: the cardinality of the set of real numbers.
- **Cantor diagonalization argument**: a proof technique used to show that the set of real numbers is uncountable.
- **computable function**: a function for which there is a computer program in some programming language that finds its values.
- **uncomputable function**: a function for which no computer program in a programming language exists that finds its values.
- **continuum hypothesis**: the statement that no set $A$ exists such that $$\aleph_0 < |A| < c$$.
- **matrix**: a rectangular array of numbers.
- **$I_n$ (identity matrix of order $n$)** the $n \times n$ matrix that has entries equal to 1 on its diagonal and 0s elsewhere.
- **$A^t (\text{transpose of } A)$**: the matrix obtained from $A$ by interchanging the rows and columns.
- **symmetric matrix**: a matrix is symmetric if it equals its transpose.
- **zero-one matrix**: a matrix with each entry equal to either 0 or 1.