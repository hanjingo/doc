[中文版](chapter5_zh.md) | English

# 5 Probabilistic Analysis and Randomized Algorithms

[TOC]



## Indicator random variables

Indicator random variables provide a convenient method for converting between probabilities and expectations. Suppose we are given a sample space $S$ and an event $A$. Then the `indicator random variable I{A}` associated with event $A$ is defined as:
$$
I{A} =
\begin{cases}
1, & \text{if A occurs}  \\
0, & \text{if A does not occur}
\end{cases}
$$

**Lemma 5.1** Given a sample space $S$ and an event $A$ in the sample space $S$, let $X_A = I\{A\}$, Then $E[X_A]=Pr\{A\}$.

**Proof** By the definition of an indicator random variable from above equation and the definition of expected value, we have:
$$
\begin{equation}\begin{split} 
E[X_A] &= E[I\{A\}] \\
&= 1 \cdot Pr\{A\} + 0 \cdot Pr\{\overline{A}\} \\
&= Pr\{A\}
\end{split}\end{equation}
$$

, where $\overline A$ denotes $S-A$, the complement of $A$.

**Lemma 5.2** Assuming that the candidates are presented in a random order, algorithm HIRE-ASSISTANT has an average-case total hiring cost of $O(c_h ln\ n)$.

**Proof** The bound follows immediately from our definition of the hiring cost and equation $E[X] = ln\ n + O(1)$, which shows that the expected number of hires is approximately $ln\ n$.



## Randomly permuting arrays

```c++
RANDOMIZED-HIRE-ASSISTANT(n)
randomly permute the list of candidates
best = 0
for i = 1 to n
    interview candidate i
    if candidate i is better than candidate best
        best = i
        hire candidate i
```

**Lemma 5.3** The expected hiring cost of the procedure RANDOMIZED-HIRE-ASSISTANT is $O(c_h ln\ n)$.

**Proof** After permuting the input array, we have achieved a situation identical to that of the probabilistic analysis of HIRE-ASSISTANT.

**Randomly permuting arrays**

```c++
PERMUTE-BY-SORTING(A)
n = A.length
let P[1. .n] be a new array
for i = 1 to n
    P[i] = RANDOM(1, n^3)
sort A, suing P as sort keys
```

**Lemma 5.4** Procedure PERMUTE-BY-SORTING produces a uniform random permutation of the input, assuming that all priorities are distinct.

**Proof** We start by considering the particular permutation in which each element $A[i]$ receives the $i$th smallest priority. We shall show that this permutation occurs with probability exactly $1/n!$. For $i = 1,2,...,n$, let $E_i$ be the event that element $A[i]$ receives the $i$th smallest priority. Then we wish to compute the probability that for all $i$, event $E_i$ occurs, which is:
$$
Pr\{E_1 \cap E_2 \cap E_3 \cap ... \cap E_{n-1} \cap E_n\}
$$
, Using Exercise C.2-5, this probability is equal to:
$$
Pr\{E_1\} \cdot Pr\{E_2|E_1\} \cdot Pr\{E_3|E_2 \cap E_1\} \cdot Pr\{E_4 | E_3 \cap E_2 \cap E_1\} \\
... Pr\{E_i | E_{i - 1} \cap E_{i - 2} \cap ... \cap E_1\} ... Pr{E_n | E_{n - 1} \cap ... \cap E_1}
$$

We have that $Pr\{E_1\} = 1 / n$ because it is the probability that one priority chosen randomly out of a set of $n$ is the smallest priority. Next, we observe

**Lemma 5.5** Procedure $RANDOMIZE-IN-PLACE$ computes a uniform random permutation.

**Proof** We use the following loop invariant: Just prior to the $i$th iteration of the `for` loop of lines 2-3, for each possible $(i - 1)$-permutation of the $n$ elements, the subarray $A[1...i - 1]$ contains this $(i - 1)$-permutation with probability $(n - i + 1)!/n!$.



## Probabilistic analysis and further uses of indicator random variables

### The birthday paradox

