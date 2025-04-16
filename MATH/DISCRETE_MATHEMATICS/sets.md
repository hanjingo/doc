# Sets

[TOC]



## Definition

**Definition**: A `set` is an unordered collection of distinct objects, called `elements or members` of the set. A set is said to `contain` its elements. We write $a \in A$ to denote that $a$ is an element of the set A. The notation $a \notin A$ denotes that $a$ is not an element of the set A.

**Definition**: Two sets are `equal` if and only if they have the same elements. Therefore, if $A$ and $B$ are sets, then $A$ and $B$ are equal if and only if $\forall x (x \in A \leftrightarrow x \in B)$. We write $A = B$ if $A$ and $B$ are equal sets.

**Definition**: The set $A$ is a `subset` of $B$, and $B$ is a `superset` of $A$, if and only if every element of $A$ is also an element of $B$. We use the notation $A \subseteq B$ to indicate that $A$ is a subset of the set $B$. If, instead, we want to stress that $B$ is a superset of $A$, we use the equivalent notation $B \supe A$. (So, $A \subseteq B$ and $B \supe A$ are equivalent statements.)

**THE EMPTY SET** There is a special set that has no elements. This set is called the **empty set**, or **null set**, and is denoted by $\phi$. The empty set can also be denoted by $\{\}$(that is, we represent the empty set with a pair of braces that encloses all the elements in this set).

**Definition**: Let $S$ be a set. If there are exactly $n$ distinct elements in $S$ where $n$ is a nonnegative integer, we say that $S$ is a `finite set` and that $n$ is the `cardinality` of $S$. The cardinality of $S$ is denoted by $|S|$.

**Definition**: A set is said to be `infinite` if it is not finite.

**Definition**: Given a set $S$, the `power set` of $S$ is the set of all subsets of the set $S$. The power set of $S$ is denoted by $P(S)$.

**Definition**: The `ordered n-tuple`$(a_1, a_2, ..., a_n)$ is the ordered collection that has $a_1$ as its first element, $a_2$ as its second element, ..., and $a_n$ as its $n$th element.

**Definition**: Let $A$ and $B$ be sets. The `Cartesian product` of $A$ and $B$, denoted by $A \times B$, is the set of all ordered pairs $(a, b)$, where $a \in A$ and $b \in B$. Hence: $A \times B = \{(a, b) | a \in A \wedge b \in B\}$.

**Definition**: The `Cartesian product` of the sets $A_1, A_2, ..., A_n$ denoted by $A_1 \times A_2 \times ... \times A_n$, is the set of ordered $n$-tuples $(a_1, a_2, ..., a_n)$, where $a_i$ belongs to $A_i$ for $i = 1, 2, ..., n$. In other words, $A_1 \times A_2 \times ... A_n = \{(a_1, a_2, ..., a_n)|a_i \in A_i\ for\ i = 1, 2, ..., n\}$.

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

**Definition**: The sets $A$ and $B$ have the same `cardinality` if and only if there is a one-to-one correspondence from $A$ to $B$. When $A$ and $B$ have the same cardinality, we write $|A| = |B|$.

**Definition**: If there is a one-to-one function from $A$ to $B$, the cardinality of $A$ is less than or the same as the cardinality of $B$ and we write $|A| \leq |B|$. Moreover, when $|A| \leq |B|$ and $A$ and $B$ have different cardinality, we way that the cardinality of $A$ is less than the cardinality of $B$ and we write $|A| < |B|$.

**Definition**: We say that a function is **computable** if there is a computer program in some programming language that finds the values of this function. If a function is not computable we say it is **uncomputable**.



## Theorem

**THEOREM**: For every set $S, (i) \phi \subseteq S$ and $S \subseteq S$.

**THEOREM**: If $A$ and $B$ are countable sets, then $A \cup B$ is also countable.

**THEOREM**: If $A$ and $B$ are sets with $|A| \leq |B|$ and $|B| \leq |A|$, then $|A| = |B|$. In other words, if there are one-to-one functions $f$ from $A$ to $|B|$ and $g$ from $B$ to $A$, then there is a one-to-one correspondence between $A$ and $B$.



## References

[1] Kenneth H. Rosen . Discrete Mathematics and Its Applications . 8Edition
