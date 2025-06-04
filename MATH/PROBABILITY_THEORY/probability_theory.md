# Probability Theory

[TOC]



## Definition

**Definition** If $S$ is a finite nonempty sample space of equally likely outcomes, and $E$ is an event, that is, a subset of $S$, then the `probability` of $E$ is $p(E) = \frac{|E|}{|S|}$.

**Definition** Suppose that $S$ is a set with $n$ elements. The `uniform distribution` assigns the probability $1/n$ to each element of $S$.

**Definition** The `probability` of the event $E$ is the sum of the probabilities of the outcomes in $E$. That is, $p(E) = \sum_{s \in E}p(s)$.  (Note that when $E$ is an infinite set, $\sum_{s \in E} p(s)$ is a convergent infinite series.)

**Definition** Let $E$ and $F$ be events with $p(F) > 0$. The `conditional probability` of $E$ given $F$, denoted by $p(E|F)$, is defined as $p(E|F) = \frac{p(E \cap F)}{p(F)}$.

**Definition** The events $E$ and $F$ are `independent` if and only if $p(E \cap F) = p(E)p(F)$.

**Definition** The events $E_1, E_2, \cdots, E_n$ are `pairwise independent` if and only if $p(E_i \cap E_j) = p(E_i)p(E_j)$ for all pairs of integers $i$ and $j$ with $1 \leq i < j \leq n$. These events are `mutually independent` if $p(E_{i_1} \cap E_{i_2} \cap \cdots \cap E_{i_m}) = p(E_{i_1}) p(E_{i_2}) \cdots p(E_{i_m})$ whenever $i_j, j = 1, 2, \cdots, m$, are integers with $1 \leq i_1 < i_2 < \cdots < i_m \leq n$ and $m \geq 2$.

**Definition** A `random variable` is a function from the sample space of an experiment to the set of real numbers. That is, a random variable assigns a real number to each possible outcome.

**Definition** The `distribution` of a random variable $X$ on a sample space $S$ is the set of pairs $(r, p(X = r))$ for all $r \in X(S)$, where $p(X = r)$ is the probability that $X$ takes the value $r$. (The set of pairs in this distribution is determinend by the probabilities $p(X = r)$ for $r \in X(S)$.)

**Assigning Probabilities** Let $S$ be the sample space of an experiment with a finite or countable number of outcomes. We assign a probability $p(s)$ to each outcome $s$. We require that two conditions be met:

1. $0 \leq p(s) \leq 1$ for each $s \in S$.
2. $\sum_{s \in S} p(s) = 1$.

, condition 1 states that the probability of each outcome is a nonnegative real number no greater than 1. Condition 2 states that the sum of the probabilities of all possible outcomes should be 1; that is, when we do the experiment, it is a certainty that one of these outcomes occurs.

The function $p$ from the set of all outcomes of the sample space $S$ is called a **probability distribution**.



## Theorem

**THEOREM** Let $E$ be an event in a sample space $S$. The probability of the event $\overline{E} = S - E$, the complementary event of $E$, is given by $p(\overline{E}) = 1 - p(E)$.

**THEOREM** Let $E_1$ and $E_2$ be events in the sample space $S$. Then $p(E_1 \cup E_2) = p(E_1) + p(E_2) - p(E_1 \cap E_2)$.

**THEOREM** If $E_1, E_2, \cdots$ is a sequence of pairwise disjoint events in a sample space $S$, then $p \left(\bigcup_{i} E_i \right) = \sum_{i}p(E_i)$. (Note that this theorem applies when the sequence $E_1, E_2, \cdots$ consists of a finite number or a countably infinite number of pairwise disjoint events.)

**THEOREM** The probability of exactly $k$ successes in $n$ independent Bernoulli trials, with probability of success $p$ and probability of failure $q = 1 - p$, is $C(n, k)p^{k} q^{n - k}$.

**THEOREM** THE PROBABILISTIC METHOD: If the probability that an element chosen at random from a $S$ does not have a particular property is less than 1, there exists an element in $S$ with this property.

**THEOREM** If $k$ is an integer with $k \geq 2$, then $R(k, k) \geq 2^{k/2}$.