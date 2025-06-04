# Bayes' Theorem

[TOC]



## THEOREM

**THEOREM** BAYES' THEOREM: Suppose that $E$ and $F$ are events from a sample space $S$ such that $p(E) \neq 0$ and $p(F) \neq 0$. Then
$$
p(F|E) = \frac{p(E|F)p(F)}{p(E|F)p(F) + p(E|\overline{F})p(\overline{F})}
$$
**THEOREM** GENERALIZED BAYES' THEOREM: Suppose that $E$ is an event from a sample space $S$ and that $F_1, F_2, \cdots, F_n$ are mutually exclusive events such that $\bigcup_{i = 1}^{n} F_i = S$. Assume that $p(E) \neq 0$ and $p(F_i) \neq 0$ for $i = 1, 2, \cdots, n$. Then $p(F_j | E) = \frac{p(E|F_j)p(F_j)}{\sum_{i = 1}^{n}p(E|F_i) p(F_i)}$.