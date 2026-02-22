[中文版](chapter11_zh.md) | English

# 11 Hash Tables

[TOC]



## Direct-address tables

![11_1](res/11_1.png)



## Hash tables

![11_2](res/11_2.png)

![11_3](res/11_3.png)

### Collision resolution by chaining

```c++
CHAINED-HASH-INSERT(T, x)
insert x at the head of list T[h(x.key)]
```

```c++
CHAINED-HASH-SEARCH(T, k)
search for an element with key k in list T[h(k)]
```

```c++
CHAINED-HASH-DELETE(T, x)
delete x from the list T[h(x.key)]
```

### Analysis of hashing with chaining

**Theorem 11.1** In a hash table in which collisions are resolved by chaining, an unsuccessful search takes average-case time $\theta(1 + \alpha)$, under the assumption of simple uniform hashing.

**Proof** Under the assumption of simple uniform hashing, any key $k$ not already stored in the table is 

**Theorem 11.2** In a hash table in which collisions are resolved by chaining, a successful search takes average-case time $\theta(1 + \alpha)$, under the assumption of simple uniform hashing.

**Proof** We assume that the element being searched for is equally likely to be any of the $n$ elements stored in the table. The number of elements examined during a successful search for an element $x$ is one more than the number of elements that appear before $x$ in $x$'s list. Because new elements are placed at the front of the list, elements before $x$ in the list were all inserted after $x$ was inserted. To find the expected number of elements examined, we take the average, over the $n$ elements $x$ in the table, of 1 plus the expected number of elements added to $x$'s list after $x$ was added to the list. Let $x_i$ denote the $i$th element inserted into the table, for $i = 1, 2, ..., n$ and let $k_i = x_i key$. For keys $k_i$ and $k_j$, we define the indicator random variable $X_{ij} = I\{h(k_i) = h(k_j)\}$. Under the assumption of simple uniform hashing, we have $Pr\{h(k_i) = h(k_j)\} = 1/m$, and so by Lemma 5.1, $E[X_{ij}] = 1/m$. Thus, the expected number of elements examined in a successful search is:
$$
\begin{equation}\begin{split}
E\left[ \frac{1}{n}\sum_{i=1}^{n}(1+\sum_{j=i+1}^{n}X_{ij}) \right] \\
&= \frac{1}{n} \sum_{i=1}^{n} \left(1 + \sum_{j=i+1}^{n}E[X_{ij}]\right) \text{(by linearity of expectation)} \\
&= \frac{1}{n} \sum_{i=1}^{n} \left(1 + \sum_{j=i+1}^{n} \frac{1}{m} \right) \\
&= 1 + \frac{1}{nm} \sum_{i=1}^{n}(n - i) \\
&= 1 + \frac{1}{nm} \left(\sum_{i=1}^{n}n - \sum_{i=1}^{n}i \right) \\
&= 1 + \frac{1}{nm} \left(n^2 - \frac{n(n+1)}{2} \right) \text{(by equation (A.1))} \\
&= 1 + \frac{n - 1}{2m} \\
&= 1 + \frac{\alpha}{2} - \frac{\alpha}{2n}
\end{split}\end{equation}
$$
Thus, the total time required for a successful search (including the time for computing the hash function) is $\Theta(2 + \alpha/2 - \alpha/2n) = \Theta(1 + \alpha)$.



## Hash functions

What makes a good hash function?

A good hash function satisfies (approximately) the assumption of simple uniform hashing: each key is equally likely to hash to any of the $m$ slots, independently of where any other key has hashed to.

Occasionally we do know the distribution. For example, if we know that the keys are random real numbers $k$ independently and uniformly distributed in the range $0 \leq k < 1$, then the hash function $h(k) = \lfloor km \rfloor$ satisfies the condition of simple uniform hashing.

### The division method

In the **division method** for creating hash functions, we map a key $k$ into one of $m$ slots by taking the remainder of $k$ divided by $m$. That is, the hash function is $h(k) = k\ mod\ m$.

### The multiplication method

The **multiplication method** for creating hash functions operates in two steps:

1. We multiply the key $k$ by a constant $A$ in the range $0 < A < 1$ and extract the fractional part of $kA$.

2. We multiply this value by $m$ and take the floor of the result. In short, the hash function is

   $h(k) = \lfloor m(kA\ mod\ 1) \rfloor$

   where "k A mod 1" means the fractional part of $k A$, that is, $k A - \lfloor k A \rfloor$.

![11_4](res/11_4.png)

### Universal hashing

**Theorem 11.3** Suppose that a hash function $h$ is chosen randomly from a universal collection of hash functions and has been used to hash $n$ keys into a table $T$ of size $m$, using chaining to resolve collisions. If key $k$ is not in the table, then the expected length $E[n_{h(k)}]$ of the list that key $k$ hashes to is at most the load factor $\alpha = n / m$. If key $k$ is in the table, then the expected length $E[n_{h(k)}]$ of the list containing key $k$ is at most $1 + \alpha$.

**Proof** We note that the expectations here are over the choice of the hash function and do not depend on any assumptions about the distribution of the keys. For each pair $k$ and $l$ of distinct keys, define the indicator random variable $X_{kl} = I\{h(k) = h(l)\}$. Since by the definition of a universal collection of hash functions, a single pair of keys collides with probability at most $1/m$, we have $Pr\{h(k) = h(l)\} \leq 1/m$. By lemma 5.1, therefore, we have $E[X_{kl}] \leq 1/m$.

Next we define, for each key $k$, the random variable $Y_k$ that equals the number of keys other than $k$ that hash to the same slot as $k$, so that
$$
Y_k = \sum_{l \in T, l \neq k}X_{kl}
$$
Thus we have
$$
\begin{equation}\begin{split}
E[Y_k] &= E\left[ \sum_{l \in T, l \neq k}X_{kl} \right] \\
&= \sum_{l \in T, l \neq k}X_{kl} E[X_{kl}] \quad \text{ (by linearity of expectation)} \\
& \leq \sum_{l \in T, l \neq k}\frac{1}{m}.
\end{split}\end{equation}
$$
The remainder of the proof depends on whether key $k$ is in table $T$.

- If $k \notin T$, then $n_{h(k)} = Y_k$ and $|\{l:l \in T \text{ and } l \neq k\}| = n$. Thus $E[n_{h(k)}] = E[Y_k] \leq n/m = \alpha$.
- If $k \in T$, then because key $k$ appears in list $T[h(k)]$ and the count $Y_k$ does not include key $k$, we have $n_{h(k)} = Y_k + 1$ and $|\{l:l \in T \text{ and } l \neq k\}| = n - 1$. Thus $E[n_{h(k)}] = E[Y_k] + 1 \leq (n - 1)/m + 1 = 1 + \alpha - 1/m < 1 + \alpha$.

**Corollary 11.4** Using universal hashing and collision resolution by chaining in an initially empty table with $m$ slots, it takes the expected time $\theta(n)$ to handle any sequence of $n$ $INSERT$, $SEARCH$, and $DELETE$ operations containing $O(m)\ INSERT$ oerations. 

**Proof** Since the number of insertions is $O(m)$, we have $n = O(m)$ and so $\alpha = O(1)$. The `INSERT` and `DELETE` operations take constant time and, by The orem 11.3, the expected time for each `SEARCH` operation is $O(1)$. By linearity of expectation, therefore, the expected time for the entire sequence of $n$ operations is $O(n)$. Since each operation takes $\Omega(1)$ time, the $\Theta(n)$ bound follows.

**Theorem 11.5** The class $H_{pm}$ of hash functions defined by $h_{ab}(k) = ((ak + b)mod\ p)mod\ m$ and $H_{pm} = \{h_{ab}: a \in Z_p^{*}, b \in Z_p\}$ is universal.

**Proof** TODO



## Open addressing

In **open addressing**, all elements occupy the hash table itself.

```c++
HASH-INSERT(T, k)
i = 0
repeat
    j = j(k, i)
    if T[j] == NIL
        T[j] = k
        return j
    else i = i + 1
until i == m
error "hash table overflow"
```

```c++
HASH-SEARCH(T, k)
i = 0
repeat
    j = h(k, j)
    if T[j] == k
        return j
    i = i + 1
until T[j] == NIL or i == m
return NIL
```

### Linear probing

Given an ordinary hash function $h': U \rightarrow \{0, 1, ..., m-1\}$, which we refer to as an **auxiliary hash function**, the method of **linear probing** uses the hash function $h(k, i) = (h'(k) + i)\ mod\ m, for\ i=0, 1, ..., m-1$. Given key $k$, we first probe $T[h'(k)]$, i.e., the slot given by the auxiliary hash function. We next probe slot $T[h'(k) + 1]$, and so on up to slot $T[m - 1]$. Then we wrap around to slots $T[0]$, $T[1]$, ... until we finally probe slot $T[h'(k) - 1]$. Because the initial probe determines the entire probe sequence, there are only $m$ distinct probe sequences.

### Quadratic probing

**Quadratic probing** uses a hash function of the form
$$
h(k, i) = (h'(k) + c_1i + c_2i^2)\ mod\ m
$$
, where $h'$ is an auxiliary hash function, $c_1$ and $c_2$ are positive auxiliary constants, and $i = 0, 1, ..., m - 1$.

### Double hashing

Double hashing offers one of the best methods available for open addressing because the permutations produced have many of the characteristics of randomly chosen permutations. **Double hashing** uses a hash function of the form:
$$
h(k, i) = (h_1 (k) + ih_2 (k))\ mod\ m
$$
, where both $h_1$ and $h_2$ are auxiliary hash functions.

![11_5](res/11_5.png)

### Analysis of open-address hashing

**Theorem 11.6** Given an open-address hash table with load factor $\alpha = n / m < 1$, the expected number of probes in an unsuccessful search is at most $1 / (1 - \alpha)$, assuming uniform hashing.

**Proof** TODO

**Corollary 11.7** Inserting an element into an open-address hash table with load factor $\alpha$ requires at most $1 / (1 - \alpha)$ probes, on average, assuming uniform hashing.

**Proof** TODO

**Theorem 11.8** Given an open-address hash table with load factor $\alpha < 1$, the expected number of probes in a successful search is at most $\frac{1}{\alpha} ln \frac{1}{1 - \alpha}$, assuming uniform hashing and assuming that each key in the table is equally likely to be searched for.

**Proof** TODO



## Perfect hashing

![11_6](res/11_6.png)

**Theorem 11.9** Suppose that we store $n$ keys in a hash table of size $m = n^2$ using a hash function $h$ randomly chosen from a universal class of hash functions. Then, the probability is less than $1/2$ that there are any collisions.

**Proof** TODO

**Theorem 11.10** Suppose that we store $n$ keys in a hash table of size $m = n$ using a hash function $h$ randomly chosen from a universal class of hash functions. Then, we have $E[\sum_{j=0}^{m-1} n_j ^ 2] < 2n$, where $n_j$ is the number of keys hashing to slot $j$.

**Proof** TODO

**Corollary 11.11** Suppose that we store $n$ keys in a hash table of size $m = n$ using a hash function $h$ randomly chosen from a universal class of hash functions, and we set the size of each secondary hash table to $m_j = n_j^2$ for $j = 0, 1, ..., m - 1$. Then, the expected amount of storage required for all secondary hash tables in a perfect hashing scheme is less than $2n$.

**Proof** TODO

**Corollary 11.12** Suppose that we store $n$ keys in a hash table of size $m = n$ using a hash function $h$ randomly chosen from a universal class of hash functions, and we set the size of each secondary hash table to $m_j = n_j^2$ for $j = 0, 1, ..., m - 1$. Then, the probability is less than $1 / 2$ that the total storage used for secondary hash tables equals or exceeds $4n$.

**Proof** TODO

