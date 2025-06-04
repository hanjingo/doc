# Expected Value and Variance

[TOC]



## Definition

**Definition** The `expected value`, also called the `expectation` or `mean`, of the random variable $X$ on the sample space $S$ is equal to:
$$
E(X) = \sum_{s \in S}p(s)X(s).
$$
, the `deviation` of $X$ at $s \in S$ is $X(s) - E(X)$, the difference between the value of $X$ and the mean of $X$.

**Definition** A random variable $X$ has a `geometric distribution with parameter` $p$ if $p(X = k) = (1 - p)^{k - 1}p$ for $k = 1, 2, 3, \cdots$, where $p$ is a real number with $0 \leq p \leq 1$.

**Definition** The random variables $X$ and $Y$ on a sample space $S$ are `independent` if $p(X = r_1 \text{ and } Y = r_2) = p(X = r_1) \cdot p(y = r_2)$, or in words, if the probability that $X = r_1$ and $Y = r_2$ equals the product of the probabilities that $X = r_1$ and $Y = r_2$, for all real numbers $r_1$ and $r_2$.

**Definition** Let $X$ be a random variable on a sample space $S$. The `variance` of $X$, denoted by $V(X)$, is $V(X) = \sum_{s \in S}(X(s) - E(X))^2 p(s)$. That is, $V(X)$ is the weighted average of the square of the deviation of $X$. The `standard deviation` of $X$, denoted $\sigma (X)$, is defined to be $\sqrt{V(X)}$.



## THEOREM

**THEOREM** If $X$ is a random variable and $p(X = r)$ is the probability that $X = r$, so that $p(X = r) = \sum_{s \in S, X(s) = r}$, then $E(X) = \sum_{r \in X(S)} p(X = r)r$.

**THEOREM** The expected number of successes when $n$ mutually independent Bernoulli trials are performed, where $p$ is the probability of success on each trial, is $np$.

**THEOREM** If $X_i, i = 1, 2, \cdots, n$ with $n$ a positive integer, are random variables on $S$, and if $a$ and $b$ are real numbers, then:

1. $E(X_1 + X_2 + \cdots + X_n) = E(X_1) + E(X_2) + \cdots + E(X_n)$
2. $E(aX + b) = aE(X) + b$

**THEOREM** If the random variable $X$ has the geometric distribution with parmeter $p$, then $E(X) = 1/p$.

**THEOREM** If $X$ and $Y$ are independent random variables on a sample space $S$, then $E(XY) = E(X)E(Y)$.

**THEOREM** If $X$ is a random variable on a sample space $S$, then $V(X) = E(X^2) - E(X)^2$.

**THEOREM** BIENAYME'S FORMULA: If $X$ and $Y$ are two independent random variables on a sample space $S$, then $V(X + Y) = V(X) + V(Y)$. Furthermore, if $X_i, i = 1, 2, \cdots, n$, with $n$ a positive integer, are pairwise independent random variables on $S$, then $V(X_1 + X_2 + \cdots + X_n) = V(X_1) + V(X_2) + \cdots + V(X_n)$.

**THEOREM** CHEBYSHEV'S INEQUALITY: Let $X$ be a random variable on a sample space $S$ with probability function $p$. If $r$ is a positive real number, then $p(|X(s) - E(X)| \geq r) \leq V(X) / r^2$.



## COROLLARY

**COROLLARY** If $X$ is a random variable on a sample space $S$ and $E(X) = \mu$, then $V(X) = E((X - \mu)^2)$