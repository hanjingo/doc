# CHAPTER6 Formal Relational Query Languages



The `select` operation selects tuples that satisfy a given predicate.

The `project` operation allows us to produce this relation. The project operation is a unary operation that returns its argument relation, with certain attributes left out.

For a union operation $r \cup s$ to be valid, we require that two conditions hold:

1. The relations $r$ and $s$ must be of the same arity. That is, they must have the same number of attributes.
2. The domains of the $i$th attribute of $r$ and the $i$th attribute of $s$ must be the same, for all $i$.

The `set-difference` operation, denoted by $-$, allows us to find tuples that are in one relation but are not in another. The expression $r - s$ produces a relation containing those tuples in $r$ but not in $s$.

The `Cartesian-product` operation, denoted by a cross ($\times$), allows us to combine information from any two relations. We write the Cartesian product of relations $r_1$ and $r_2$ as $r_1 \times r_2$.

The `rename` operator, denoted by the lowercase Greek letter rho($\rho$), lets us do this. Given a relational-algebra expression $E$, the expression:
$$
\rho_x(E)
$$
, returns the result of an expression $E$ under the name $x$.

A second form of the rename operation is as follows: Assume that a relational-algebra expression $E$ has arity $n$. Then, the expression:
$$
\rho_{x(A_1, A_2, ..., A_n)}(E)
$$
, returns the result of an expression $E$ under the name $x$, and with the attributes renamed to $A_1, A_2, ..., A_n$.

A basic expression in the relational algebra consists of either one of the following:

- A relation in the database.
- A constant relation.

, the following are all relational-algebra expressions:

- $E_1 \cup E_2$
- $E_1 - E_2$
- $E_x \times E_2$
- $\sigma_p(E_1)$, where $P$ is a predicate on attributes in $E_1$
- $\Pi_S(E_1)$, where $S$ is a list consisting of some of the attributes in $E_1$
- $\rho_x(E_1)$, where $x$ is the new name for the result of $E_1$



## Summary

TODO