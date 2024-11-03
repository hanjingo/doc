# 5 Probabilistic Analysis and Randomized Algorithms



## 5.1 The hiring problem



## 5.2 Indicator random variables

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



## 5.3 Randomly permuting arrays

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
Pr\{E_1\} \cdot Pr\{E_2|E_1\} TODO
$$


**引理5.4** 假设所有优先级都不同，则过程PERMUTE-BY-SORTING产生输入的均匀随机排列。

**证明** 我们从考虑每个元素$A[i]$分配到第$i$个最小优先级的特殊排列开始，并说明这个排列正好发生的概率是$1/n!$。对$i=1, 2, ..., n$，设$E_i$代表元素$A[i]$分配到第$i$个最小优先级的事件。然后我们想计算对所有的$i$，事件$E_i$发生的概率，即$Pr\{E_1 \cap E_2 \cap E_3 \cap ... \cap E_{n-1} \cap E_n\} = (\frac{1}{n})(\frac{1}{n-1})...(\frac{1}{2})(\frac{1}{1}) = \frac{1}{n!}$。

**引理5.5** 过程RANDOMIZE-IN-PLACE可计算出一个均匀随机排列。

**证明** 我们使用下面的循环不变式：在第2~3行for循环的第i次迭代以前，对每个可能的(i-1)排列，子数组A[1..i-1]包含这个(i-1)排列的概率是(n-i+1)!/n!。

