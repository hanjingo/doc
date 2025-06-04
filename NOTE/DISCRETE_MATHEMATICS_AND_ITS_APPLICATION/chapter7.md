# CHAPTER 7 Discrete Probability

[TOC]



## An Introduction to Discrete Probability

**Definition** If $S$ is a finite nonempty sample space of equally likely outcomes, and $E$ is an event, that is, a subset of $S$, then the `probability` of $E$ is $p(E) = \frac{|E|}{|S|}$.

**THEOREM** Let $E$ be an event in a sample space $S$. The probability of the event $\overline{E} = S - E$, the complementary event of $E$, is given by $p(\overline{E}) = 1 - p(E)$.

**THEOREM** Let $E_1$ and $E_2$ be events in the sample space $S$. Then $p(E_1 \cup E_2) = p(E_1) + p(E_2) - p(E_1 \cap E_2)$.



## Probability Theory

**Assigning Probabilities** Let $S$ be the sample space of an experiment with a finite or countable number of outcomes. We assign a probability $p(s)$ to each outcome $s$. We require that two conditions be met:

1. $0 \leq p(s) \leq 1$ for each $s \in S$.
2. $\sum_{s \in S} p(s) = 1$.

, condition 1 states that the probability of each outcome is a nonnegative real number no greater than 1. Condition 2 states that the sum of the probabilities of all possible outcomes should be 1; that is, when we do the experiment, it is a certainty that one of these outcomes occurs.

The function $p$ from the set of all outcomes of the sample space $S$ is called a **probability distribution**.

**Definition** Suppose that $S$ is a set with $n$ elements. The `uniform distribution` assigns the probability $1/n$ to each element of $S$.

**Definition** The `probability` of the event $E$ is the sum of the probabilities of the outcomes in $E$. That is, $p(E) = \sum_{s \in E}p(s)$.  (Note that when $E$ is an infinite set, $\sum_{s \in E} p(s)$ is a convergent infinite series.)

**THEOREM** If $E_1, E_2, \cdots$ is a sequence of pairwise disjoint events in a sample space $S$, then $p \left(\bigcup_{i} E_i \right) = \sum_{i}p(E_i)$. (Note that this theorem applies when the sequence $E_1, E_2, \cdots$ consists of a finite number or a countably infinite number of pairwise disjoint events.)

**Definition** Let $E$ and $F$ be events with $p(F) > 0$. The `conditional probability` of $E$ given $F$, denoted by $p(E|F)$, is defined as $p(E|F) = \frac{p(E \cap F)}{p(F)}$.

**Definition** The events $E$ and $F$ are `independent` if and only if $p(E \cap F) = p(E)p(F)$.

**Definition** The events $E_1, E_2, \cdots, E_n$ are `pairwise independent` if and only if $p(E_i \cap E_j) = p(E_i)p(E_j)$ for all pairs of integers $i$ and $j$ with $1 \leq i < j \leq n$. These events are `mutually independent` if $p(E_{i_1} \cap E_{i_2} \cap \cdots \cap E_{i_m}) = p(E_{i_1}) p(E_{i_2}) \cdots p(E_{i_m})$ whenever $i_j, j = 1, 2, \cdots, m$, are integers with $1 \leq i_1 < i_2 < \cdots < i_m \leq n$ and $m \geq 2$.

**THEOREM** The probability of exactly $k$ successes in $n$ independent Bernoulli trials, with probability of success $p$ and probability of failure $q = 1 - p$, is $C(n, k)p^{k} q^{n - k}$.

**Definition** A `random variable` is a function from the sample space of an experiment to the set of real numbers. That is, a random variable assigns a real number to each possible outcome.

**Definition** The `distribution` of a random variable $X$ on a sample space $S$ is the set of pairs $(r, p(X = r))$ for all $r \in X(S)$, where $p(X = r)$ is the probability that $X$ takes the value $r$. (The set of pairs in this distribution is determinend by the probabilities $p(X = r)$ for $r \in X(S)$.)

**THEOREM** THE PROBABILISTIC METHOD: If the probability that an element chosen at random from a $S$ does not have a particular property is less than 1, there exists an element in $S$ with this property.

**THEOREM** If $k$ is an integer with $k \geq 2$, then $R(k, k) \geq 2^{k/2}$.



## Bayes' Theorem

**THEOREM** BAYES' THEOREM Suppose that $E$ and $F$ are events from a sample space $S$ such that $p(E) \neq 0$ and $p(F) \neq 0$. Then
$$
p(F|E) = \frac{p(E|F)p(F)}{p(E|F)p(F) + p(E|\overline{F})p(\overline{F})}
$$
**THEOREM** GENERALIZED BAYES' THEOREM: Suppose that $E$ is an event from a sample space $S$ and that $F_1, F_2, \cdots, F_n$ are mutually exclusive events such that $\bigcup_{i = 1}^{n} F_i = S$. Assume that $p(E) \neq 0$ and $p(F_i) \neq 0$ for $i = 1, 2, \cdots, n$. Then $p(F_j | E) = \frac{p(E|F_j)p(F_j)}{\sum_{i = 1}^{n}p(E|F_i) p(F_i)}$.



## Expected Value and Variance

**Definition** The `expected value`, also called the `expectation` or `mean`, of the random variable $X$ on the sample space $S$ is equal to:
$$
E(X) = \sum_{s \in S}p(s)X(s).
$$
, the `deviation` of $X$ at $s \in S$ is $X(s) - E(X)$, the difference between the value of $X$ and the mean of $X$.

**THEOREM** If $X$ is a random variable and $p(X = r)$ is the probability that $X = r$, so that $p(X = r) = \sum_{s \in S, X(s) = r}$, then $E(X) = \sum_{r \in X(S)} p(X = r)r$.

**THEOREM** The expected number of successes when $n$ mutually independent Bernoulli trials are performed, where $p$ is the probability of success on each trial, is $np$.

**THEOREM** If $X_i, i = 1, 2, \cdots, n$ with $n$ a positive integer, are random variables on $S$, and if $a$ and $b$ are real numbers, then:

1. $E(X_1 + X_2 + \cdots + X_n) = E(X_1) + E(X_2) + \cdots + E(X_n)$
2. $E(aX + b) = aE(X) + b$

**Definition** A random variable $X$ has a `geometric distribution with parameter` $p$ if $p(X = k) = (1 - p)^{k - 1}p$ for $k = 1, 2, 3, \cdots$, where $p$ is a real number with $0 \leq p \leq 1$.

**THEOREM** If the random variable $X$ has the geometric distribution with parmeter $p$, then $E(X) = 1/p$.

**Definition** The random variables $X$ and $Y$ on a sample space $S$ are `independent` if $p(X = r_1 \text{ and } Y = r_2) = p(X = r_1) \cdot p(y = r_2)$, or in words, if the probability that $X = r_1$ and $Y = r_2$ equals the product of the probabilities that $X = r_1$ and $Y = r_2$, for all real numbers $r_1$ and $r_2$.

**THEOREM** If $X$ and $Y$ are independent random variables on a sample space $S$, then $E(XY) = E(X)E(Y)$.

**Definition** Let $X$ be a random variable on a sample space $S$. The `variance` of $X$, denoted by $V(X)$, is $V(X) = \sum_{s \in S}(X(s) - E(X))^2 p(s)$. That is, $V(X)$ is the weighted average of the square of the deviation of $X$. The `standard deviation` of $X$, denoted $\sigma (X)$, is defined to be $\sqrt{V(X)}$.

**THEOREM** If $X$ is a random variable on a sample space $S$, then $V(X) = E(X^2) - E(X)^2$.

**COROLLARY** If $X$ is a random variable on a sample space $S$ and $E(X) = \mu$, then $V(X) = E((X - \mu)^2)$

**THEOREM** BIENAYME'S FORMULA: If $X$ and $Y$ are two independent random variables on a sample space $S$, then $V(X + Y) = V(X) + V(Y)$. Furthermore, if $X_i, i = 1, 2, \cdots, n$, with $n$ a positive integer, are pairwise independent random variables on $S$, then $V(X_1 + X_2 + \cdots + X_n) = V(X_1) + V(X_2) + \cdots + V(X_n)$.

**THEOREM** CHEBYSHEV'S INEQUALITY: Let $X$ be a random variable on a sample space $S$ with probability function $p$. If $r$ is a positive real number, then $p(|X(s) - E(X)| \geq r) \leq V(X) / r^2$.



## Key Terms and Results

### TERMS

**Sample space**: the set of possible outcomes of an experiment.

**Event**: a subset of the sample space of an experiment.

**Probability of an event (Laplace's definition)**: the number of successful outcomes of this event divided by the number of possible outcomes.

**Probability distribution**: a function $p$ from the set of all outcomes of a sample space $S$ for which $0 \leq p(x_i) \leq 1$ for $i = 1, 2, ..., n$ and $\sum_{i=1}^{n}p(x_i) = 1$, where $x_1, ..., x_n$ are the possible outcomes.

**Probability of an event E**: the sum of the probabilities of the outcomes in $E$.

**$p(E|F)$ (conditional probability of $E$ given $F$)**: the ratio $p(E \cap F) / p(F)$.

**Independent events**: events $E$ and $F$ such that $p(E \cap F) = p(E)p(F)$.

**Pairwise independent events**: events $E_1, E_2, ..., E_n$ such that $p(E_i \cap E_j) = p(E_i)p(E_j)$ for all pairs of integers $i$ and $j$ with $1 \leq j < k \leq n$.

**Mutually independent events**: events $E_1, E_2, ..., E_n$ such that $p(E_{i_1} \cap E_{i_2} \cap \cdots \cap E_{i_m}) = p(E_{i_1})p(E_{i_2}) \cdots p(E_{i_m})$ whenever $i_j, j = 1, 2, ..., m$ are integers with $1 \leq i_1 < i_2 < \cdots < i_m \leq n$ and $m \geq 2$.

**Random variable**: a function that assigns a real number to each possible outcome of an experiment.

**Distribution of a random variable X**: the set of pairs $(r, p(X = r))$ for $r \in X(S)$.

**Uniform distribution**: the assignment of equal probabilities to the elements of a finite set.

**Expected value of a random variable**: the weighted average of a random variable, with values of the random variable weighted by the probability of outcomes, that is, $E(X) = \sum_{s \in S}p(s)X(s)$.

**Geometric distribution**: the distribution of a random variable $X$ such that $p(X = k) = (1 - p)^{k - 1}p$ for $k = 1, 2, ...$ for some real number $p$ with $0 \leq p \leq 1$.

**Independent random variables**: random variables $X$ and $Y$ such that $p(X = r_1 \text{ and } Y = r_2) = p(X = r_1)p(Y = r_2)$ for all real numbers $r_1$ and $r_2$.

**Variance of a random variable $X$**: the weighted average of the square of the difference between the value of $X$ and its expected value $E(X)$, with weights given by the probability of outcomes, that is, $V(X) = \sum_{s \in S}(X(s) - E(X))^2 p(s)$.

**Standard deviation of a random variable $X$**: the square root of the variance of $X$, that is, $\sigma(X) = \sqrt{V(X)}$.

**Bernoulli trial**: an experiment with two possible outcomes.

**Probabilistic (or Monte Carlo) algorithm**: an algorithm in which random choices are made at one or more steps.

**Probabilistic method**: a technique for proving the existence of objects in a set with certain properties that proceeds by assigning probabilities to objects and showing that the probability that an object has these properties is positive.

### RESULTS

The probability of exactly $k$ successes when $n$ independent Bernoulli trials are carried out equals $C(n, k)p^k q^{n-k}$, where $p$ is the probability of success and $q = 1 - p$ is the probability of failure.

**Bayes' theorem**: If $E$ and $F$ are events from a sample space $S$ such that $p(E) \neq 0$ and $p(F) \neq 0$, then 
$$
p(F|E) = \frac{p(E|F)p(F)}{p(E|F)p(F) + p(E|\overline{F})p(\overline{F})}
$$
$E(X) = \sum_{r \in X(S)}p(X = r)r$.

**Linearity of expectations**: $E(X_1 + X_2 + \cdots + X_n) = E(X_1) + E(X_2) + \cdots + E(X_n)$ if $X_1, X_2, \cdots, X_n$ are random variables. If $X$ and $Y$ are independent random variables, then $E(XY) = E(X)E(Y)$.

**Bienayme's formula**: If $X_1, X_2, \cdots, X_n$ are independent random variables, then $V(X_1 + X_2 + \cdots + X_n) = V(X_1) + V(X_2) + \cdots + V(X_n)$.

**Chebyshev's inequality**: $p(|E(s) - E(X)| \geq r) \leq V(X)/r^2$, where $X$ is a random variable with probability function $p$ and $r$ is a positive real number.
