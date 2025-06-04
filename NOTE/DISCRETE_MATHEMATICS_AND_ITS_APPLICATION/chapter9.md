# CHAPTER 9 Relations

[TOC]



## Relations and Their Properties

**Definition** Let $A$ and $B$ be sets. A `binary relation from` $A$ to $B$ is a subset of $A \times B$.

**Definition** A `relation on a set` A is a relation from $A$ to $A$.

**Definition** A relation $R$ on a set $A$ is called `reflexive` if $(a, a) \in R$ for every element $a \in A$.

**Definition** A relation $R$ on a set $A$ is called `symmetric` if $(b, a) \in R$ whenever $(a, b) \in R$, for all $a, b \in A$. A relation $R$ on a set $A$ such that for all $a, b \in A$, if $(a, b) \in R$ and $(b, a) \in R$, then $a = b$ is called `antisymmetric`.

**Definition** A relation $R$ on a set $A$ is called `transitive` if whenever $(a, b) \in R$ and $(b, c) \in R$, then $(a, c) \in R$, for all $a, b, c \in A$.

**Definition** Let $R$ be a relation from a set $A$ to a set $B$ and $S$ a relation from $B$ to a set $C$. The `composite` of $R$ and $S$ is the relation consisting of ordered pairs $(a, c)$, where $a \in A, c \in C$, and for which there exists an element $b \in B$ such that $(a, b) \in R$ and $(b, c) \in S$. We denote the composite of $R$ and $S$ by $S \circ R$.

**Definition** Let $R$ be a relation on the set $A$. The powers $R^n, n = 1, 2, 3, ...$, are defined recursively by $R^1 = R$ and $R^{n + 1} = R^n \circ R$.

**THEOREM** The relation $R$ on a set $A$ is transitive if and only if $R^n \subseteq R$ for $n = 1, 2, 3, ...$



## $n$-ary Relations and Their Applications

**Definition** Let $A_1, A_2, ..., A_n$ be sets. An `n-ary` relation on these sets is a subset of $A_1 \times A_2 \times \cdots \times A_n$. The sets $A_1, A_2, ..., A_n$ are called the `domains` of the relation, and $n$ is called its `degree`.

A domain of an $n$-ary relation is called a **primary key** when the value of the $n$-tuple from this domain determines the $n$-tuple.

**Definition** Let $R$ be an $n$-ary relation and $C$ a condition that elements in $R$ may satisfy. Then the `selection operator` $s_C$ maps the $n$-ary relation $R$ to the $n$-ary relation of all $n$-tuples from $R$ that satisfy the condition $C$.

**Defintion** The `projection` $P_{i_1 i_2, ..., i_m}$ where $i_1 < i_2 < \cdots < i_m$, maps the $n$-tuple $(a_1, a_2, ..., a_n)$ to the $m$-tuple $(a_{i_1}, a_{i_2}, ..., a_{i_m})$, where $m \leq n$.

**Definition** Let $R$ be a relation of degree $m$ and $S$ a relation of degree $n$. The `join` $J_p (R, S)$, where $p \leq m$ and $p \leq n$, is a relation of degree $m + n - p$ that consists of all $(m + n - p)$-tuples $(a_1, a_2, ..., a_{m-p}, c_1, c_2, ..., c_p, b_1, b_2, ..., b_{n - p})$, where the $m$-tuple $(a_1, a_2, ..., a_{m-p}, c_1, c_2, ..., c_p)$ belongs to $R$ and the $n$-tuple $(c_1, c_2, ..., c_p, b_1, b_2, ..., b_{n - p})$ belongs to $S$.

**Definition** The `count` of an itemset $I$, denoted by $\sigma(I)$, in a set of transactions $T=\{t_1, t_2, ..., t_k\}$, where $k$ is a positive integer, is the number of transactions that contain this itemset. That is, $\sigma(I) = |\{t_i \in T | I \subseteq t_i \}|$. The `support` of an itemset $I$ is the probability that $I$ is included in a randomly selected transaction from $T$. That is $support(I) = \frac{\sigma(I)}{|T|}$.

**Definition** If $I$ and $J$ are subsets of a set $T$ of transactions, then $support(I \rightarrow J) = \frac{\sigma(I \cup J)}{|T|}$ and $confidence(I \rightarrow J) = \frac{\sigma(I \cup J)}{\sigma(I)}$.



## Representing Relations

A relation between finite sets can be represented using a zero-one matrix. Suppose that $R$ is a relation from $A = \{a_1, a_2, ..., a_m\}$ to $B = \{b_1, b_2, ..., b_n\}$. (Here the elements of the sets $A$ and $B$ have been listed in a particular, but arbitrary, order. Furthermore, when $A = B$ we use the same ordering for $A$ and $B$.) The relation $R$ can be represented by the matrix $M_R = [m_{ij}]$, where
$$
m_{ij} = 
\begin{cases}
1 &if(a_i, b_j) \in R, \\
0 &if(a_i, b_j) \notin R. 
\end{cases}
$$
, In other words, the zero-one matrix representing $R$ has a 1 as its $(i, j)$ entry when $a_i$ is related to $b_j$, and a 0 in this position if $a_i$ is not related to $b_j$. (Such a representation depends on the orderings used for A and B.)

**Definition** A `directed graph`, or `digraph`, consists of a sset $V$ of `vertices` (or `nodes`) together with a set $E$ of ordered pairs of elements of $V$ called `edges` (or `arcs`). The vertex `a` is called the `initial vertex` of the edge $(a, b)$, and the vertex $b$ is called the `terminal vertex` of this edge.



## Closures of Relations

**Definition** If $R$ is a relation on a set $A$, then the **closure** of $R$ with repsect to $P$, if it exists, is the relation $S$ on $A$ with property $P$ that contains $R$ and is a subset of every subset of $A \times A$ containing $R$ with property $P$.

**Definition** A `path` from $a$ to $b$ in the directed graph $G$ is a sequence of edges $(x_0, x_1), (x_1, x_2), (x_2, x_3), ..., (x_{n - 1}, x_n)$ in $G$, where $n$ is a nonnegative integer, and $x_0 = a$ and $x_n = b$, that is, a sequence of edges where the terminal vertex of an edge is the same as the initial vertex in the next edge in the path. This path is denoted by $x_0, x_1, ..., x_{n - 1}, x_n$ and has `length n`. We view the empty set of edges as a path of length zero from $a$ to $a$. A path of length $n \geq 1$ that begins and ends at the same vertex is called a `circuit` or `cycle`.

**THEOREM** Let $R$ be a relation on a set $A$. There is a path of length $n$, where $n$ is a positive integer, from $a$ to $b$ if and only if $(a, b) \in R^n$.

**Definition** Let $R$ be a relation on a set $A$. The `connectivity relation` $R^{*}$ consists of the pairs $(a, b)$ such that there is a path of length at least one from $a$ to $b$ in $R$.

**THEOREM** The transitive closure of a relation $R$ equals the connectivity relation $R^{*}$.

**LEMMA** Let $A$ be a set with $n$ elements, and let $R$ be a relation on $A$. If there is a path of length at least one in $R$ from $a$ to $b$, then there is such a path with length not exceeding $n$. Moreover, when $a \neq b$, if there is a path of length at least one in $R$ from $a$ to $b$, then there is such a path with length not exceeding $n - 1$.

**THEOREM** Let $M_R$ be the zero-one matrix of the relation $R$ on a set with $n$ elements. Then the zero-one matrix of the transitive closure $R^{*}$ is $M_{R^{*}} = M_r \vee M_R^{[2]} \vee M_R^{[3]} \vee \cdots \vee M_R^{[n]}$.

**LEMMA** Let $W_k = [w_{ij}^{[k]}]$ be the zero-one matrix that has a 1 in its $(i, j)$th position if and only if there is a path from $v_i$ to $v_j$ with interior vertices from the set $\{v_1, v_2, ..., v_k\}$. Then $w_{ij}^{[k]} = w_{ij}^{k - 1} \vee (w_{ik}^{[k - 1]} \wedge w_{kj}^{[k - 1]})$, whenever $i, j$, and $k$ are positive integers not exceeding $n$.



## Equivalence Relations

**Definition** A relation on set $A$ is called an `equivalence relation` if it is reflexive, symmetric, and transitive.

**Definition** Two elements $a$ and $b$ that are related by an equivalence relation are called `equivalent`. The notation $a \sim b$ is often used to denote that $a$ and $b$ are equivalent elements with respect to a particular equivalence relation.

**Definition** Let $R$ be an equivalence relation on a set $A$. The set of all elements that are related to an element $a$ of $A$ is called the `equivalence class` of $a$. The equivalence class of $a$ with respect to $R$ is denoted by $[a]_R$. When only one relation is under consideration, we can delete the subscript $R$ and write $[a]$ for this equivalence class.

**THEOREM** Let $R$ be an equivalence relation on a set $A$. These statements for elements $a$ and $b$ of $A$ are equivalent:
$$
aRb \\
[a] = [b] \\
[a] \cap [b] \neq \emptyset
$$
**THEOREM** Let $R$ be an equivalence relation on a set $S$. Then the equivalence classes of $R$ form a partition of $S$. Conversely, given a partition $\{A_i | i \in I\}$ of the set $S$, there is an equivalence relation $R$ that has the sets $A_i, i \in I$, as its equivalence classes.



## Partial Orderings

**Definition** A relation $R$ on a set $S$ is called a `partial ordering` or `partial order` if it is reflexive, antisymmetric, and transitive. A set $S$ together with a partial ordering $R$ is called a `partially ordered set`, or `poset`, and is denoted by $(S, R)$. Members of $S$ are called `elements` of the poset.

**Definition** The elements $a$ and $b$ of a poset $(S, \preccurlyeq)$ are called `comparable` if either $a \preccurlyeq b$ or $b \preccurlyeq a$. When $a$ and $b$ are elements of $S$ such that neither $a \preccurlyeq b$ nor $b \preccurlyeq a$, $a$ and $b$ are called `incomparable`.

**Definition** If $(S, \preccurlyeq)$ is a poset and every two elements of $S$ are comparable, $S$ is called a `totally ordered` or `linearly ordered set`, and $\preccurlyeq$ is called a `total order` or a `linear order`. A totally ordered set is also called a `chain`.

**Definition** $(S, \preccurlyeq)$ is a `well-ordered set` if it is a poset such that $\preccurlyeq$ is a total ordering and every nonempty subset of $S$ has a least element.

**THEOREM** THE PRINCIPLE OF WELL-ORDERED INDUCTION: Suppose that $S$ is a well-ordered set. Then $P(x)$ is true for all $x \in S$, if For every $y \in S$, if $P(x)$ is true for all $x \in S$ with $x \prec y$, then $P(y)$ is true.

**LEMMA** Every finite nonempty poset $(S, \preccurlyeq)$ has at least one minimal element.



## Key Terms and Results

### TERMS

- **Binary relation from A to B**: a subset of $A \times B$.
- **Relation on A**: a binary relation from A to itself (that is, a subset of $A \times A$).



