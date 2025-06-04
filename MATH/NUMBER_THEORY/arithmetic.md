# Arithmetic

[TOC]



## Definition

**Definition**: If $a$ and $b$ are integers with $a \neq 0$, We say that $\text{a divides b}$ if there is an integer $c$ such that $b = ac$ (or equivalently, if $\frac{b}{a}$ is an integer). When $a$ divides $b$ we say that $a$ is a `factor` or `divisor` of $b$, and that $b$ is a `multiple` of $a$. The notation $a \mid b$ denotes that $a$ divides $b$. We write $a \nmid b$ when $a$ does not divide $b$.

**Definition**: In the equality given in the division algorithm, $d$ is called the $divisor$, $a$ is called the $dividend$, $q$ is called the $quotient$, and $r$ is called the $remainder$. This notation is used to express the quotient and remainder.

**Definition**: If $a$ and $b$ are integers and $m$ is a positive integer, then $a$ is $\text{congruent to b modulo m}$ if $m$ divides $a - b$. We use the notation $a \equiv b$ (mod $m$) to indicate that $a$ is congruent to $b$ modulo $m$. We say that $a \equiv b$ (mod $m$) is a **congruence** and that $m$ is its **modulus** (plural **moduli**). If $a$ and $b$ are not congruent modulo $m$, we write $x \not\equiv y$ (mod $m$).

**Definition** An integer $p$ greater than 1 is called `prime` if the only positive factors of $p$ are 1 and $p$. A positive integer that is greater than 1 and is not prime is called `composite`.

**Definition** Let $a$ and $b$ be integers, not both zero. The largest integer $d$ such that $d \mid a$ and $d \mid b$ is called the `greatest common divisor` of $a$ and $b$. The greatest common divisor of $a$ and $b$ is denoted by $gcd(a, b)$.

**Definition** The integers $a$ and $b$ are `relatively prime` if their greatest common divisor is 1.

**Definition** The integers $a_1, a_2, \cdots, a_n$ are `pairwise relatively prime` if $gcd(a_i, a_j) = 1$ whenever $1 \leq i < j \leq n$.

**Definition** The `least common multiple` of the positive integers $a$ and $b$ is the smallest positive integer that is divisible by both $a$ and $b$. The least common multiple of $a$ and $b$ is denoted by $lcm(a, b)$.

**Definition** Let $b$ be a positive integer. If $n$ is a composite positive integer, and $b^{n - 1} \equiv 1 (\bmod n)$, then $n$ is called a `pseudoprime to the base` b.

**Definition** A composite integer $n$ that satisfies the congruence $b^{n - 1} \equiv 1 (\bmod n)$ for all positive integers $b$ with $gcd(b, n) = 1$ is called a `Carmichael number`.

**Definition** A `primitive root` modulo a prime $p$ is an integer $r$ in $Z_{p}$ such that every nonzero element of $Z_{p}$ is a power of $r$.

**Definition** Suppose that $p$ is a prime, $r$ is a primitive root modulo $p$, and $a$ is an integer between 1 and $p - 1$ inclusive. If $r^{e}\ \bmod p = a$ and $0 \leq e \leq p - 1$, we say that $e$ is the `discrete logarithm` of $a$ modulo $p$ to the base $r$ and we write $log_{r}a = e$ (where the prime $p$ is understood).



## Theorem

**THEOREM**: Let $a, b$ and $c$ be integers, where $a \neq 0$. Then:

> if $a \mid b$ and $a \mid c$, then $a \mid (b + c)$;
>
> if $a \mid b$, then $a \mid bc$ for all integers $c$;
>
> if $a \mid b$ and $b \mid c$, then $a \mid c$.

**THEOREM**: THE DIVISION ALGORITHM, Let $a$ be an integer and $d$ a positive integer. Then there are unique integers $q$ and $r$, with $0 \leq r < d$, such that $a = dq + r$.

**THEOREM**: Let $a$ and $b$ be integers, and let $m$ be a positive integer. Then $a \equiv b$(mod $m$) if and only if $\text{a mod m = b mod m}$.

**THEOREM**: Let $m$ be a positive integer. The integers $a$ and $b$ are congruent modulo $m$ if and only if there is an integer $k$ such that $a = b + km$.

**THEOREM**: Let $m$ be a positive integer. If $a \equiv b (\bmod m)$ and $c \equiv d (\bmod m)$, then $a + c \equiv b + d (\bmod m)$ and $ac \equiv bd(\bmod m)$.

**THEOREM**: Let $b$ be an integer greater than 1. Then if $n$ is a positive integer, it can be expressed uniquely in the form $n = a_{k}b^{k} + a_{k-1}b^{k-1} + \cdots + a_{1}b + a_{0}$, where $k$ is a nonnegative integer, $a_0, a_1, ..., a_k$ are nonnegative integers less than $b$, and $a_{k} \neq 0$.

**THEOREM**: THE FUNDAMENTAL THEOREM OF ARITHMETIC Every integer greater than 1 can be written uniquely as a prime or as the product of two more primes, where the prime factors are written in order of nondecreasing size.

**THEOREM**: If $n$ is a composite integer, then $n$ has a prime divisor less than or equal to $\sqrt{n}$.

**THEOREM** There are infinitely many primes.

**THEOREM** THE PRIME NUMBER THEOREM: The ratio of $\pi(x)$, the number of primes not exceeding $x$, and $x / \ln\ x$ approaches 1 as $x$ grows without bound. (Here $\ln\ x$ is the natural logarithm of $x$.)

**THEOREM** Let $a$ and $b$ be positive integers. Then $ab = gcd(a, b) \cdot lcm(a, b)$.

**THEOREM** If $a$ and $b$ are positive integers, then there exist integers $s$ and $t$ such that $gcd(a, b) = sa + tb$.

**THEOREM** Let $m$ be a positive integer, and let $a, b$ and $c$ be integers. If $ac \equiv bc (\bmod m)$ and $gcd(c, m) = 1$, then $a \equiv b (\bmod m)$.

**THEOREM** If $a$ and $m$ are relatively prime integers and $m > 1$, then an inverse of $a$ modulo $m$ exists. Furthermore, this inverse is unique modulo $m$. (That is, there is a unique positive integer $\overline{a}$ less than $m$ that is an inverse of $a$ modulo $m$ and every other inverse of $a$ modulo $m$ is congruent to $\overline{a}$ modulo $m$.)

**THEOREM** THE CHINESE REMAINDER THEOREM: Let $m_1, m_2, \cdots, m_m$ be pairwise relatively prime positive integers greater than one and $a_1, a_2, \cdots, a_n$ arbitrary integers. Then the system:
$$
x \equiv a_1 (\bmod m_1) \\
x \equiv a_2 (\bmod m_2) \\
\vdots \\
x \equiv a_n (\bmod m_n)
$$
, has a unique solution modulo $m = m_1 m_2 \cdots m_n$. (That is, there is a solution $x$ with $0 \leq x < m$, and all other solutions are congruent modulo $m$ to this solution.)

**THEOREM** FERMAT'S LITTLE THEOREM: If $p$ is prime and $a$ is an integer not divisible by $p$, then $a^{p - 1} \equiv 1 (\bmod p)$. Furthermore, for every integer $a$ we have $a^{p} \equiv (\bmod p)$.



## Corollary

**COROLLARY**: If $a$, $b$ and $c$ are integers, where $a \neq 0$, such that $a \mid b$ and $a \mid c$, then $a \mid mb + nc$ whenever $m$ and $n$ are integers.

**COROLLARY** Let $m$ be a positive integer and let $a$ and $b$ be integers. Then $(a + b)\bmod m = ((a\ \bmod m) + (b\ \bmod m)) \bmod m$ and $ab\ \bmod m = ((a\ \bmod m)(b\ \bmod m))\ \bmod m$.



## Lemma

**LEMMA** Let $a = bq + r$, where $a, b, q$ and $r$ are integers. Then $gcd(a, b) = gcd(b, r)$.

**LEMMA** If $a, b$ and $c$ are positive integers such that $gcd(a, b) = 1$ and $a \mid bc$, then $a \mid c$.

**LEMMA** If $p$ is a prime and $p \mid a_1 a_2 \cdots a_n$, where each $a_i$ is an integer, then $p \mid a_i$ for some $i$.



## References

[1] Kenneth H. Rosen . Discrete Mathematics and Its Applications . 8Edition
