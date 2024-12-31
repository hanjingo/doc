[中文版](chapter31_zh.md) | English

# 第31章 数论算法

[TOC]



## Elementary number-theoretic notions

**Divisibility and divisors**

The notation $d|a$ (read "d **divides** a") means that $a = kd$ for some integer $k$.

If $d$ does not divide $a$, we write $d \nmid a$.

If $d | a$ and $d \geq 0$, we say that $d$ is a **divisor** of $a$.

**Prime and composite numbers**

An integer $a > 1$ whose only divisors are the trivial divisors 1 and $a$ is a **prime number** or, more simply, a **prime**.

An integer $a > 1$ that is not prime is a **composite number** or, more simply, a **composite**.

**The division theorem, remainders, and modular equivalence**

**Theorem 31.1 (Division theorem)** For any integer $a$ and any positive integer $n$, there exist unique integers $q$ and $r$ such that $0 \leq r < n$ and $a = qn + r$.

**Common divisors and greatest common divisors**

An important property of common divisors is that: $d \mid a\ and\ d \mid b\ implies\ d \mid (a + b)\ and\ d \mid (a - b)$

More generally, we have that: $d \mid a\ and\ d \mid b\ implies\ d \mid (ax + by)$

The **greatest common divisor** of two integers $a$ and $b$, not both zero, is the largest of the common divisors of $a$ and $b$; we denote it by $gcd(a, b)$. The following are elementary properties of the gcd function:
$$
\begin{equation}\begin{split} 
gcd(a, b) &= gcd(b, a) \\ 
gcd(a, b) &= gcd(-a, b) \\ 
gcd(a, b) &= gcd(|a|, |b|) \\ 
gcd(a, 0) &= |a| \\ 
gcd(a, ka) &= |a| \text{ for any } k \in Z \\ 
\end{split}\end{equation}
$$
**Theorem 31.2** If $a$ and $b$ are any integers, not both zero, then $gcd(a, b)$ is the smallest positive element of the set $\{ax + by: x, y \in Z\}$ of linear combinations of $a$ and $b$.

**Corollary 31.3** For any integers $a$ and $b$, if $d | a$ and $d | b$, then $d | gcd(a, b)$.

**Corollary 31.4** For all integers $a$ and $b$ and any nonnegative integer $n$, $gcd(an, bn) = n\ gcd(a, b)$.

**Corollary 31.5** For all positive integers $n, a, and\ b$, if $n | ab$ and $gcd(a, n) = 1$, then $n | b$.

Two integers $a$ and $b$ are **relatively prime** if their only common divisor is 1, that is, if $gcd(a, b) = 1$.

**Theorem 31.6** For any integers $a$, $b$, and $p$, if both $gcd(a, p) = 1$ and $gcd(b, p) = 1$, then $gcd(ab, p) = 1$.

**Theorem 31.7** For all primes $p$ and all integers $a$ and $b$, if $p | ab$, then $p | a$ or $p | b$ (or both).

**Theorem 31.8 (Unique factorization)** There is exactly one way to write any composite integer $a$ as a product of the form
$$
a = p_1^{e_1} p_2^{e_2} ... p_r^{e_r}
$$
 , where the $p_i$ are prime, $p_1 < p_2 < ... < p_r$, and the $e_i$ are positive integers.



## Greatest common divisor

**Theorem 31.9 (GCD recursion theorem)** For any nonnegative integer $a$ and any positive integer $b$, $gcd(a, b) = gcd(b, a\ mod\ b)$.

**Euclid's algorithm**

The `Elements` of Euclid (circa 300 B.C.) describes the following gcd algorithm, although it may be of even earlier origin. The inputs $a$ and $b$ are arbitrary nonnegative integers:
$$
\begin{align}
& EUCLID(a, b) \\
& if\ b == 0 \\
& \qquad return\ a \\
& else\ return\ EUCLID(b, a\ mod\ b)
\end{align}
$$
**Lemma 31.10** If $a > b \geq 1$ and the call $EUCLID(a, b)$ performs $k \geq 1$ recursive calls, then $a \geq F_{k + 2}\ and\ b \geq F_{k + 1}$

**Theorem 31.11 (Lame's theorem)** For any integer $k \geq 1$, if $a > b \geq 1$ and $b < F_{k + 1}$, then the call $EUCLID(a, b)$ makes fewer than $k$ recursive calls.

**The extended form of Euclid's algorithm**
$$
\begin{align}
& EXTENDED-EUCLID(a, b) \\
& if\ b == 0 \\
& \qquad return(a, 1, 0) \\
& else\ (d', x', y') = EXTENDED-EUCLID(b, a\ mod\ b) \\
& \qquad (d, x, y) = (d' y', x' - \lfloor a/b \rfloor y') \\
& \qquad return\ (d, x, y)
\end{align}
$$
![31_1](res/31_1.png)



## Modular arithmetic

**Finite groups**

A $group (S, \oplus)$ is a set $S$ together with a binary operation $\oplus$ defined on $S$ for which the following properties hold:

1. **Closure:** For all $a, b \in S$, we have $a \oplus b \in S$.
2. **Identity:** There exists an element $e \in S$, called the **identity** of the group, such that $e \oplus a = a \oplus e = a$ for all $a \in S$.
3. **Associativity:** For all $a, b, c \in S$, we have $(a \oplus b) \oplus c = a \oplus (b \oplus c)$.
4. **Inverses:** For each $a \in S$, there exists a unique element $b \in S$, called the **inverse** of $a$, such that $a \oplus b = b \oplus a = e$.

**Theorem 31.12** The system $(Z_n, +_{n})$ is a finite abelian group.

![31_2](res/31_2.png)

**Theorem 31.13** The system $(Z_n^*, \cdot_{n})$ is a finite abelian group.

**Theorem 31.14(A nonempty closed subset of a finite group is a subgroup)** If $(S, \oplus)$ is a finite group and $S'$ is any nonempty subset of $S$ such that $a \oplus b \in S'$ for all $a, b \in S'$, then $(S', \oplus)$ is subgroup of $(S, \oplus)$.

**Theorem 31.15 (Lagrange's theorem)** If $(S, \oplus)$ is a finite group and $(S', \oplus)$ is a subgroup of $(S, \oplus)$, then $|S'|$ is a divisor of $|S|$.

**Corollary 31.16** If $S'$ is a proper subgroup of a finite group $S$, then $|S'| \leq |S| / 2$.

**Theorem 31.17** For any finite group $(S, \oplus)$ and any $a \in S$, the order of $a$ is equal to the size of the subgroup it generates, or $ord(a) = |<a>|$.

**Corollary 31.18** The sequence $a^{(1)}, a^{(2)}, ...$ is periodic with period $t = ord(a)$; that is, $a^{(i)} = a^{(j)}$ if and only if $i \equiv j(mod\ t)$.

**Corollary 31.19** If $(S, \oplus)$ is a finite group with identity $e$, then for all $a \in S$, $a^{(|S|)} = e$.



## Solving modular linear equations

**Theorem 31.20** For any positive integers $a$ and $n$, if $d = gcd(a, n)$, then $ =  = \{0, d, 2d, ..., ((n / d) - 1)d\}$ in $Z_n$, and thus $|<a>| = n / d$.

**Corollary 31.21** The equation $ax \equiv b(mod\ n)$ is solvable for the unknown $x$ if and only if $d | b$, where $d = gcd(a, n)$.

**Corollary 31.22** The equation $ax \equiv b(mod\ n)$ either has $d$ distinct solutions modulo $n$, where $d = gcd(a, n)$, or it has no solutions.

**Theorem 31.23** Let $d = gcd(a, n)$, and suppose that $d = ax' + ny'$ for some integers $x'$ and $y'$ (for example, as computed by $EXTENDED-EUCLID$). If $d | b$, then the equation $ax \equiv b(mod\ n)$ has as one of its solutions the value $x_0$, where:
$$
x_0 = x'(b/d)\ mod\ n
$$
**Theorem 31.24** Suppose that the equation $ax \equiv b(mod\ n)$ is solvable (that is, $d | b$, where $d = gcd(a, n)$) and that $x_0$ is any solution to this equation. Then, this equation has exactly $d$ distinct solutions, modulo $n$, given by $x_i = x_0 + i(n / d)$ for $i = 0, 1, ..., d - 1$.

The following algorithm prints all solutions to this equation. The inputs $a$ and $n$ are arbitrary positive integers, and $b$ is an arbitrary integer:
$$
\begin{align}
& MODULAR-LINEAR-EQUATION-SOLVER(a, b, n) \\
& (d, x', y') = EXTENDED-EUCLID(a, n) \\
& if\ d \mid b \\
& \qquad x_0 = x'(b/d)\ mod\ n \\
& \qquad for\ i = 0\ to\ d - 1 \\
& \qquad \qquad print(x_0 + i(n/d))\ mod\ n \\
& else\ print\ "no\ solutions"
\end{align}
$$
**Corollary 31.25** For any $n > 1$, if $gcd(a, n) = 1$, then the equation $ax \equiv b(mod\ n)$ has a unique solution, modulo $n$.

**Corollary 31.26** For any $n > 1$, if $gcd(a, n) = 1$, then the equation $ax \equiv 1(mod\ n)$ has a unique solution, modulo $n$. Otherwise, it has no solution.



## The Chinese remainder thorem

**Theorem 31.27 (Chinese remainder theorem)** Let $n = n_1 n_2 ... n_k$, where the $n_i$ are pairwise relatively prime. Consider the correspondence:
$$
a \leftrightarrow (a_1, a_2, ..., a_k)
$$
, where $a \in Z_n, a_i \in Z_{n_i}$, and
$$
a_i = a\ mod\ n_i
$$
, for $i = 1, 2, ..., k$.

**Corollary 31.28** If $n_1, n_2, ..., n_k$ are pairwise relatively prime and $n = n_1 n_2 ... n_k$, then for any integers $a_1, a_2, ..., a_k$, the set of simultaneous equations:
$$
x \equiv a_i (mod\ n_i)
$$
, for $i = 1, 2, ..., k$, has a unique solution modulo $n$ for the unknown $x$.

**Corollary 31.29** If $n_1, n_2, ..., n_k$ are pairwise relatively prime and $n = n_1 n_2 ... n_k$, then for all integers $x$ and $a$, 
$$
x \equiv a(mod\ n_i)
$$
, for $i = 1, 2, ..., k$ if and only if
$$
x \equiv a(mod\ n)
$$
![31_3](res/31_3.png)



## Power of an element

**Theorem 31.30 (Euler's theorem)** For any integer $n > 1, a^{\phi(n)} \equiv 1(mod\ n)$ for all $a \in Z_n^{*}$.

**Theorem 31.31 (Fermat's theorem)** If $p$ is prime, then $a^{p - 1} \equiv 1(mod\ p)$ for all $a \in Z_p^{*}$.

**Theorem 31.32** The values of $n > 1$ for which $Z_n^{*}$ is cyclic are 2, 4, $p^e$, and $sp^e$, and $sp^e$, for all primes $p > 2$ and all positive integers $e$.

**Theorem 31.33 (Discrete logarithm theorem)** If $g$ is a primitive root of $Z_n^{*}$, then the equation $g^x \equiv g^y(mod\ n)$ holds if and only if the equation $x \equiv y(mod\ \phi(n))$ holds.

**Theorem 31.34** If $p$ is an odd prime and $e \geq 1$, then the equation $x^2 \equiv 1(mod\ p^e)$ has only two solutions, namely $x = 1$ and $x = -1$.

**Corollary 31.35** If there exists a nontrivial square root of 1, modulo $n$, then $n$ is composite.

The following procedure computes $a^c$ mod $n$ as $c$ is increased by doublings and incrementations from 0 to b:
$$
\begin{align}
& MODULAR-EXPONENTIATION(a, b, n) \\
& c = 0 \\
& d = 1 \\
& let\ <b_k, b_{k - 1}, ..., b_0>\ be\ the\ binary\ representation\ of\ b \\
& for\ i = k\ downto\ 0 \\
& \qquad c = 2c \\
& \qquad d = (d \cdot d)\ mod\ n \\
& \qquad if\ b_i == 1 \\
& \qquad \qquad c = c + 1 \\
& \qquad \qquad d = (d \cdot a)\ mod\ n \\
& return\ d
\end{align}
$$
![31_4](res/31_4.png)



## The RSA public-key cryptosystem

![31_5](res/31_5.png)

![31_6](res/31_6.png)

**Theorem 31.36 (Correctness of RSA)** The RSA equations $P(M) = M^e\ mod\ n$ and $S(C) = C^d\ mod\ n$ define inverse transformations of $Z_n$ satisfying equations $M = S_A(P_A(M))$ and $M = P_A(S_A(M))$.



## Primality testing

**Theorem 31.37 (Prime number theorem)** $\lim_{n \rightarrow \infty} \frac{\pi(n)}{n / ln\ n} = 1$.
$$
\begin{align}
& WITNESS(a, n) \\
& let\ t\ and\ u\ be\ such\ that\ t \geqslant 1, u\ is\ odd, and\ n - 1 = 2^t u \\
& x_0 = MODULAR-EXPONENTIATION(a, u, n) \\
& for\ i = 1\ to\ t \\
& \qquad x_i = x_{i - 1}^2\ mod\ n \\
& \qquad if\ x_i == 1\ and\ x_{i - 1} \neq 1\ and\ x_{i - 1} \neq n - 1 \\
& \qquad \qquad return\ TRUE \\
& if\ x_t \neq 1 \\
& \qquad return\ TRUE \\
& if\ x_t \neq 1 \\
& \qquad return\ TRUE \\
& return\ FALSE
\end{align}
$$

$$
\begin{align}
& MILLER-RABIN(n, s) \\
& for\ j = 1\ to\ s \\
& \qquad a = RANDOM(1, n - 1) \\
& \qquad if\ WITNESS(a, n) \\
& \qquad \qquad return\ COMPOSITE \\
& return\ PRIME
\end{align}
$$

**Theorem 31.38** If $n$ is an odd composite number, then the number of witnesses to the compositeness of $n$ is at least $(n - 2) / 2$.

**Theorem 31.39** For any odd integer $n > 2$ and positive integer $s$, the probability that $MILLER-RABIN(n, s)$ errs is at most $2^{-s}$.



## Integer factorization

$$
\begin{align}
& POLLARD-RHO(n) \\
& i = 1 \\
& x_1 = RANDOM(0, n - 1) \\
& y = x_1 \\
& k = 2 \\
& while\ TRUE \\
& \qquad i = i + 1 \\
& \qquad x_i = (x_{i - 1}^2 - 1)\ mod\ n \\
& \qquad d = gcd(y - x_i, n) \\
& \qquad if\ d \neq 1\ and\ d \neq n \\
& \qquad \qquad print\ d \\
& \qquad if\ i == k \\
& \qquad \qquad y = x_i \\
& \qquad \qquad k = 2k
\end{align}
$$

![31_7](res/31_7.png)