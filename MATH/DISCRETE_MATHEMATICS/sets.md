# Sets

[TOC]

## Introduction

This note summarizes the basic notions and commonly used operations on sets in discrete mathematics. It is concise and practical: definitions, common identities, cardinality, Cartesian products, and brief remarks on countability and computability.

## Basic definitions

- Set: An unordered collection of distinct objects called elements or members. We write a \in A to mean "a is an element of A" and a \notin A to mean "a is not an element of A." 

- Equality: Two sets A and B are equal (A = B) iff they contain exactly the same elements, i.e. \forall x (x \in A \leftrightarrow x \in B).

- Empty set: The unique set with no elements, denoted by \varnothing (or {}).

- Subset / superset: A is a subset of B (A \subseteq B) iff every element of A is also in B. Equivalently, B is a superset of A (B \supseteq A). If A \subseteq B and A \neq B we write A \subsetneq B.

- Power set: The power set P(S) is the set of all subsets of S.

- Ordered n-tuple: (a_1, a_2, ..., a_n) is an ordered collection where order matters.

- Cartesian product: For sets A and B, the Cartesian product A \times B = \{(a,b) \mid a \in A, b \in B\}. More generally, \prod_{i=1}^n A_i = A_1 \times \cdots \times A_n is the set of n-tuples with component i taken from A_i.

## Set operations

- Union: A \cup B = \{x \mid x \in A \text{ or } x \in B\}.
- Intersection: A \cap B = \{x \mid x \in A \text{ and } x \in B\}.
- Difference (relative complement): A \setminus B = \{x \mid x \in A \text{ and } x \notin B\}.
- Complement: Given a universal set U, the complement of A is \overline{A} = U \setminus A.
- Disjoint: A and B are disjoint if A \cap B = \varnothing.

## Common identities

Below are frequently used set identities (standard names shown):

- Identity laws: A \cap U = A, \quad A \cup \varnothing = A.
- Domination laws: A \cup U = U, \quad A \cap \varnothing = \varnothing.
- Idempotent laws: A \cup A = A, \quad A \cap A = A.
- Complementation: \overline{\overline{A}} = A.
- Commutative laws: A \cup B = B \cup A, \quad A \cap B = B \cap A.
- Associative laws: A \cup (B \cup C) = (A \cup B) \cup C, and similarly for intersection.
- Distributive laws: A \cup (B \cap C) = (A \cup B) \cap (A \cup C), and dual for intersection.
- De Morgan's laws: \overline{A \cap B} = \overline{A} \cup \overline{B}, \quad \overline{A \cup B} = \overline{A} \cap \overline{B}.
- Absorption laws: A \cup (A \cap B) = A, \quad A \cap (A \cup B) = A.
- Complement laws: A \cup \overline{A} = U, \quad A \cap \overline{A} = \varnothing.

These identities are useful for algebraic manipulation of set expressions and for proofs.

## Cardinality and countability

- Cardinality: If a set S has exactly n distinct elements (n a nonnegative integer), we say S is finite and write |S| = n. Otherwise S is infinite.

- Equal cardinality: Sets A and B have the same cardinality (|A| = |B|) iff there exists a bijection (one-to-one correspondence) between A and B.

- Comparisons: If there exists an injection from A to B, we write |A| \le |B|. If |A| \le |B| and |B| \le |A| then |A| = |B| (SchroederBernstein theorem).

- Countability: A set is countable if it is finite or has the same cardinality as the natural numbers. Examples: \mathbb{N}, \mathbb{Z}, and \mathbb{Q} are countable; \mathbb{R} is uncountable.

## Computability (brief remark)

- A function is computable if there is an algorithm (or program) that, given an input, produces the function's value in finite time. Functions with no such algorithm are called uncomputable (undecidable in certain settings).

## Theorems (basic)

- For every set S: \varnothing \subseteq S and S \subseteq S.
- If A and B are countable sets, then A \cup B is countable.
- SchroederBernstein theorem: If |A| \le |B| and |B| \le |A|, then |A| = |B| (there exists a bijection between A and B).

## Examples

- Example 1: If A = \{1,2,3\} and B = \{2,3,4\} then A \cup B = \{1,2,3,4\}, A \cap B = \{2,3\}, and A \setminus B = \{1\}.
- Example 2: For sets A = \{0,1\} and B = \{a,b\}, the Cartesian product A \times B = \{(0,a),(0,b),(1,a),(1,b)\}.

## Remarks and references

- This note focuses on elementary set theory used in discrete mathematics. For deeper treatments see standard references (Rosen, or set-theory texts for advanced topics such as ordinals, cardinals, and ZF axioms).

## References

1. Kenneth H. Rosen, Discrete Mathematics and Its Applications, 8th ed.
