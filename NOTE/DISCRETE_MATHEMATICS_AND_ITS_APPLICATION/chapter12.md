# CHAPTER 12 Boolean Algebra

[TOC]



## Boolean Functions

Let $B = \{0, 1\}$. Then $B^n = \{(x_1, x_2, ..., x_n) | x_i \in B\ for\ 1 \leq i \leq n \}$ is the set of all possible $n$-tuples of 0s and 1s. The variable $x$ is called a **Boolean variable** if it assumes values only from $B$, that is, if its only possible values are 0 and 1. A function from $B^n$ to $B$ is called a **Boolean function of degree n**.

Boolean functions $F$ and $G$ of $n$ variables are equal if and only if $F(b_1, b_2, ..., b_n) = G(b_1, b_2, ..., b_n)$ whenever $b_1, b_2, ..., b_n$ belong to $B$. Two different Boolean expressions that represent the same function are called **equivalent**. For instance, the Boolean expressions $xy$, $xy + 0$, and $xy \cdot 1$ are equivalent. The **complement** of the Boolean function $F$ is the function $\over{F}$, where $\overline{F}(x_1, ..., x_n) = \overline{F(s_1, ..., x_n)}$. Let $F$ and $G$ be Boolean functions of degree $n$. The **Boolean sum** $F + G$ and the **Boolean product** $FG$ are defined by:
$$
(F + G)(x_1, ..., x_n) = F(x_1, ..., x_n) + G(x_1, ..., x_n), \\
(FG)(x_1, ..., x_n) = F(x_1, ..., x_n)G(x_1, ..., x_n).
$$
![boolean_identities](res/boolean_identities.png)

**Definition** A `Boolean algebra` is a set $B$ with two binary operations $\vee$ and $\wedge$, elements 0 and 1, and a unary operation $\over$ such that these properties hold for all $x$, $y$ and $z$ in $B$:

![boolean_algebra](res/boolean_algebra.png)



## Representing Boolean Functions

**Definition** A `literal` is a Boolean variable or its complement. A `minterm` of the Boolean variables $x_1, x_2, ..., x_n$ is a Boolean product $y_1 y_2 ... y_n$, where $y_i = x_i$ or $y_i = \overline{x_i}$. Hence, a minterm is a product of $n$ literals, with one literal for each variable.



## Logic Gates

![basic_types_of_gates](res/basic_types_of_gates.png)



## Key Terms and Results

TODO

