# CHAPTER 4 Number Theory and Cryptography

[TOC]



## Divisibility and Modular Arithmetic

**Definition**: If $a$ and $b$ are integers with $a \neq 0$, We say that $\text{a divides b}$ if there is an integer $c$ such that $b = ac$ (or equivalently, if $\frac{b}{a}$ is an integer). When $a$ divides $b$ we say that $a$ is a `factor` or `divisor` of $b$, and that $b$ is a `multiple` of $a$. The notation $a \mid b$ denotes that $a$ divides $b$. We write $a \nmid b$ when $a$ does not divide $b$.

**THEOREM**: Let $a, b$ and $c$ be integers, where $a \neq 0$. Then:

> if $a \mid b$ and $a \mid c$, then $a \mid (b + c)$;
>
> if $a \mid b$, then $a \mid bc$ for all integers $c$;
>
> if $a \mid b$ and $b \mid c$, then $a \mid c$.

**COROLLARY**: If $a$, $b$ and $c$ are integers, where $a \neq 0$, such that $a \mid b$ and $a \mid c$, then $a \mid mb + nc$ whenever $m$ and $n$ are integers.

**THEOREM**: THE DIVISION ALGORITHM, Let $a$ be an integer and $d$ a positive integer. Then there are unique integers $q$ and $r$, with $0 \leq r < d$, such that $a = dq + r$.

**Definition**: In the equality given in the division algorithm, $d$ is called the $divisor$, $a$ is called the $dividend$, $q$ is called the $quotient$, and $r$ is called the $remainder$. This notation is used to express the quotient and remainder.

**Definition**: If $a$ and $b$ are integers and $m$ is a positive integer, then $a$ is $\text{congruent to b modulo m}$ if $m$ divides $a - b$. We use the notation $a \equiv b$ (mod $m$) to indicate that $a$ is congruent to $b$ modulo $m$. We say that $a \equiv b$ (mod $m$) is a **congruence** and that $m$ is its **modulus** (plural **moduli**). If $a$ and $b$ are not congruent modulo $m$, we write $x \not\equiv y$ (mod $m$).

**THEOREM**: Let $a$ and $b$ be integers, and let $m$ be a positive integer. Then $a \equiv b$(mod $m$) if and only if $\text{a mod m = b mod m}$.

**THEOREM**: Let $m$ be a positive integer. The integers $a$ and $b$ are congruent modulo $m$ if and only if there is an integer $k$ such that $a = b + km$.

**THEOREM**: Let $m$ be a positive integer. If $a \equiv b (\bmod m)$ and $c \equiv d (\bmod m)$, then $a + c \equiv b + d (\bmod m)$ and $ac \equiv bd(\bmod m)$.

**COROLLARY** Let $m$ be a positive integer and let $a$ and $b$ be integers. Then $(a + b)\bmod m = ((a\ \bmod m) + (b\ \bmod m)) \bmod m$ and $ab\ \bmod m = ((a\ \bmod m)(b\ \bmod m))\ \bmod m$.

**Arithmetic Modulo m**: We can define arithmetic operations on $Z_m$, the set of nonnegative integers less than $m$, that is, the set $\{0, 1, ..., m - 1\}$. In particular, we define the addition of these integers, denoted by $+_{m}$ by:
$$
a +_{m} b = (a + b)\bmod m
$$
, where the addition on the right-hand side of this equation is the ordinary addition of integers, and we define multiplication of these integers, denoted by $\cdot_{m}$ by:
$$
a\ \cdot_{m}\ b = (a \cdot b)\bmod m
$$
, where the multiplication on the right-hand side of this equation is the ordinary multiplication of integers. The operations $+_{m}$ and $\cdot_{m}$ are called addition and multiplication modulo $m$ and when we use these operations, we are said to be doing **arithmetic modulo** $m$.

The operations $+_{m}$ and $\cdot_{m}$ satisfy many of the same properties of ordinary addition and multiplication of integers. In particular, they satisfy these properties:

- **Closure** If $a$ and $b$ belong to $Z_m$, then $a +_{m} b$ and $a \cdot_{m} b$ belong to $Z_m$.
- **Associativity** If $a, b$ and $c$ belong to $Z_m$, then $(a +_{m} b) +_{m} (b +_{m} c)$ and $(a \cdot_{m} b) \cdot_{m} c = a \cdot_{m}(b \cdot_{m} c)$.
- **Commutativity**: If $a$ and $b$ belong to $Z_{m}$, then $a +_{m} b = b +_{m} a$ and $a \cdot_{m} b = b \cdot_{m} a$.
- **Identity elements**: The elements 0 and 1 are identity elements for addition and multiplication modulo $m$, respectively. That is, if $a$ belongs to $Z_m$, then $a +_{m} 0 = 0 +_{m} a = a \text{ and } a \cdot_{m} 1 = 1 \cdot_{m} a = a$.
- **Additive inverses**: If $a \neq 0$ belongs to $Z_m$, then $m - a$ is an additive inverse of $a$ modulo $m$ and 0 is its own additive inverse. That is, $a +_{m} (m - a) = 0$ and $0 +_{m} 0 = 0$.
- **Distributivity**: If $a$, $b$ and $c$ belong to $Z_m$, then $a \cdot_{m} (b +_{m} c) = (a \cdot_{m} b) +_{m} (a \cdot_{m} c)$ and $(a +_{m} b) \cdot_{m} c = (a \cdot_{m} c) +_{m} (b \cdot_{m} c)$.



## Integer Representations and Algorithms

**THEOREM**: Let $b$ be an integer greater than 1. Then if $n$ is a positive integer, it can be expressed uniquely in the form $n = a_{k}b^{k} + a_{k-1}b^{k-1} + \cdots + a_{1}b + a_{0}$, where $k$ is a nonnegative integer, $a_0, a_1, ..., a_k$ are nonnegative integers less than $b$, and $a_{k} \neq 0$.



## Primes and Greatest Common Divisors

**Definition** An integer $p$ greater than 1 is called `prime` if the only positive factors of $p$ are 1 and $p$. A positive integer that is greater than 1 and is not prime is called `composite`.

**THEOREM**: THE FUNDAMENTAL THEOREM OF ARITHMETIC Every integer greater than 1 can be written uniquely as a prime or as the product of two more primes, where the prime factors are written in order of nondecreasing size.

**THEOREM**: If $n$ is a composite integer, then $n$ has a prime divisor less than or equal to $\sqrt{n}$.

The **sieve of Eratosthenes** is used to find all primes not exceeding a specified positive integer.

**THEOREM** There are infinitely many primes.

**THEOREM** THE PRIME NUMBER THEOREM: The ratio of $\pi(x)$, the number of primes not exceeding $x$, and $x / \ln\ x$ approaches 1 as $x$ grows without bound. (Here $\ln\ x$ is the natural logarithm of $x$.)

**Definition** Let $a$ and $b$ be integers, not both zero. The largest integer $d$ such that $d \mid a$ and $d \mid b$ is called the `greatest common divisor` of $a$ and $b$. The greatest common divisor of $a$ and $b$ is denoted by $gcd(a, b)$.

**Definition** The integers $a$ and $b$ are `relatively prime` if their greatest common divisor is 1.

**Definition** The integers $a_1, a_2, \cdots, a_n$ are `pairwise relatively prime` if $gcd(a_i, a_j) = 1$ whenever $1 \leq i < j \leq n$.

**Definition** The `least common multiple` of the positive integers $a$ and $b$ is the smallest positive integer that is divisible by both $a$ and $b$. The least common multiple of $a$ and $b$ is denoted by $lcm(a, b)$.

**THEOREM** Let $a$ and $b$ be positive integers. Then $ab = gcd(a, b) \cdot lcm(a, b)$.

**LEMMA** Let $a = bq + r$, where $a, b, q$ and $r$ are integers. Then $gcd(a, b) = gcd(b, r)$.

**THEOREM** If $a$ and $b$ are positive integers, then there exist integers $s$ and $t$ such that $gcd(a, b) = sa + tb$.

**LEMMA** If $a, b$ and $c$ are positive integers such that $gcd(a, b) = 1$ and $a \mid bc$, then $a \mid c$.

**LEMMA** If $p$ is a prime and $p \mid a_1 a_2 \cdots a_n$, where each $a_i$ is an integer, then $p \mid a_i$ for some $i$.

**THEOREM** Let $m$ be a positive integer, and let $a, b$ and $c$ be integers. If $ac \equiv bc (\bmod m)$ and $gcd(c, m) = 1$, then $a \equiv b (\bmod m)$.



## Solving Congruences

A congruence of the form $ax \equiv b (\bmod m)$, where $m$ is a positive integer, $a$ and $b$ are integers, and $x$ is a variable, is called a **linear congruence**.

**THEOREM** If $a$ and $m$ are relatively prime integers and $m > 1$, then an inverse of $a$ modulo $m$ exists. Furthermore, this inverse is unique modulo $m$. (That is, there is a unique positive integer $\overline{a}$ less than $m$ that is an inverse of $a$ modulo $m$ and every other inverse of $a$ modulo $m$ is congruent to $\overline{a}$ modulo $m$.)

**THEOREM** THE CHINESE REMAINDER THEOREM: Let $m_1, m_2, \cdots, m_m$ be pairwise relatively prime positive integers greater than one and $a_1, a_2, \cdots, a_n$ arbitrary integers. Then the system:
$$
x \equiv a_1 (\bmod m_1) \\
x \equiv a_2 (\bmod m_2) \\
\vdots \\
x \equiv a_n (\bmod m_n)
$$
, has a unique solution modulo $m = m_1 m_2 \cdots m_n$. (That is, there is a solution $x$ with $0 \leq x < m$, and all other solutions are congruent modulo $m$ to this solution.)

Suppose that $m_1, m_2, \cdots, m_n$ are pairwise relatively prime moduli and let $m$ be their product. By the Chinese remainder theorem, we can show that an integer $a$ with $0 \leq a < m$ can be uniquely represented by the $n$-tuple consisting of its remainders upon division by $m_i, i = 1, 2, \cdots, n$. That is, we can uniquely represent $a$ by $(a \mod m_1, a \mod m_2, \cdots, a \mod m_n)$.

**THEOREM** FERMAT'S LITTLE THEOREM: If $p$ is prime and $a$ is an integer not divisible by $p$, then $a^{p - 1} \equiv 1 (\bmod p)$. Furthermore, for every integer $a$ we have $a^{p} \equiv (\bmod p)$.

**Definition** Let $b$ be a positive integer. If $n$ is a composite positive integer, and $b^{n - 1} \equiv 1 (\bmod n)$, then $n$ is called a `pseudoprime to the base` b.

**Definition** A composite integer $n$ that satisfies the congruence $b^{n - 1} \equiv 1 (\bmod n)$ for all positive integers $b$ with $gcd(b, n) = 1$ is called a `Carmichael number`.

**Definition** A `primitive root` modulo a prime $p$ is an integer $r$ in $Z_{p}$ such that every nonzero element of $Z_{p}$ is a power of $r$.

**Definition** Suppose that $p$ is a prime, $r$ is a primitive root modulo $p$, and $a$ is an integer between 1 and $p - 1$ inclusive. If $r^{e}\ \bmod p = a$ and $0 \leq e \leq p - 1$, we say that $e$ is the `discrete logarithm` of $a$ modulo $p$ to the base $r$ and we write $log_{r}a = e$ (where the prime $p$ is understood).

The most commonly used pocedure for generating pseudorandom numbers is the **linear congruential method**. We choose four integers: the **modulus** $m$, **multiplier** $a$, **increment** $c$, and **seed** $x_0$, with $2 \leq a < m, 0 \leq c < m$, and $0 \leq x_0 < m$. We generate a sequence of pseudorandom numbers $\{x_n\}$, with $0 \leq x_n < m$ for all $n$, by successively using the recursively defined function $x_{n + 1} = (ax_n + c) \bmod m$.



## Cryptography

**CRYPTANALYSIS** The process of recovering plaintext from ciphertext without knowledge of both the encryption method and the key is know as **cryptanalysis** or **breaking codes**.

**BLOCK CIPHERS** Shift ciphers and affine ciphers proceed by replacing each letter of the alphabet by another letter in the alphabet. Because of this, these ciphers are called **character** or **monoalphabetic cipers**.

**Definition** A `cryptosystem` is a five-tuple $(\mathcal{P}, \mathcal{C}, \mathcal{K}, \mathcal{E}, \mathcal{D})$, where $\mathcal{P}$ is the set of plaintext strings, $\mathcal{C}$ is the set of ciphertext strings, $\mathcal{K}$ is the keyspace (the set of all possible keys), $\mathcal{E}$ is the set of encryption functions, and $\mathcal{D}$ is the set of decryption functions. We denote by $E_{k}$ the encryption function in $\mathcal{E}$ corresponding to the key $k$ and $D_{k}$ the decryption function in $\mathcal{D}$ that decrypts ciphertext that was encrypted using $E_{k}$, that is, $D_{k}(E_{k}(p)) = p$, for all plaintext strings $p$.



## Key Terms and Results

### TERMS

- **$a | b$ ($a$ divides $b$)**: there is an integer $c$ such that $b = ac$.

- **$a$ and $b$ are congruent modulo $m:m$ divides $a - b$.**

- **Modular arithmetic**: arithmetic done modulo an integer $m \geq 2$.

- **Prime**: an integer greater than 1 with exactly two positive integer divisors.

- **Composite**: an integer greater than 1 that is not prime.

- **Mersenne prime**: a prime of the form $2^p - 1$, where $p$ is prime.

- **$\gcd(a, b)$ (greatest common divisor of $a$ and $b$)**: the largest integer that divides both $a$ and $b$.

- **Relatively prime integers**: integers $a$ and $b$ such that $\gcd(a, b) = 1$.

- **Pairwise relatively prime integers**: a set of integers with the property that every pair of these integers is relatively prime.

- **$lcm(a, b)$ (least common multiple of $a$ and $b$)**: the smallest positive integer that is divisible by both $a$ and $b$.

- **$a \mod b$**: the remainder when the integer $a$ is divided by the positive integer $b$.

- **$a \equiv b (\mod m)$ ($a$ is congruent to $b$ modulo $m$)**: $a - b$ is divisible by $m$.

- $n = (a_k a_{k - 1} \cdots a_1 a_0)_b$: the base $b$ representation of $n$.

- **Binary representation**: the base 2 representation of an integer.

- **Octal representation** the base 8 representation of an integer.

- **Hexadecimal representation**: the base 16 representation of an integer.

- **Linear combination of $a$ and $b$ with integer coefficients**: an expression of the form $sa + tb$, where $s$ and $t$ are integers.

- **Bezout coefficients of $a$ and $b$**: integers $s$ and $t$ such that the **Bezout identity** $sa + tb = \gcd(a, b)$ holds.

- **Inverse of $a$ modulo $m$**: an integer $\overline{a}$ such that $\overline{a}a \equiv 1 (\mod m)$.

- **Linear congruence**: a congruence of the form $ax \equiv b (\mod m)$, where $x$ is an integer variable.

- **Pseudoprime to the base $b$**: a composite integer $n$ such that $b^{n - 1} \equiv 1 (\mod n)$.

- **Carmichael number**: a composite integer $n$ such that $n$ is a pseudoprime to the base $b$ for all positive integers $b$ with $\gcd(b, n) = 1$.

- **Primitive root of a prime $p$**: an integer $r$ in $Z_p$ such that every integer not divisible by $p$ is congruent modulo $p$ to a power of $r$.

- **Discrete logarithm of $a$ to the base $r$ modulo $p$**: the integer $e$ with $0 \leq e \leq p - 1$ such that $r^e \equiv a (\mod p)$.

- **Encryption**: the process of making a message secret.

- **Decryption**: the process of returning a secret message to its original form.

- **Encryption key**: a value that determines which of a family of encryption functions is to be used.

- **Shift cipher**: a cipher that encrypts the plaintext letter $p$ as $(p + k) \mod m$ for an integer $k$.

- **Fundamental theorem of arithmetic**: Every positive integer can be written uniquely as the product of primes, where the prime factors are written in order of increasing size.

  If $a$ and $b$ are positive integers, then $ab = \gcd(a, b) \cdot lcm(a,b)$.

  If $m$ is a positive integer and $\gcd(a, m) = 1$, then $a$ has a unique inverse modulo $m$.

- **Affine cipher**: a cipher that encrypts the plaintext letter $p$ as $(ap + b) \mod m$ for integers $a$ and $b$ with $\gcd(a, 26) = 1$.

- **Character cipher**: a cipher that encrypts characters one by one.

- **Block cipher**: a cipher that encrypts blocks of characters of a fixed size.

- **Cryptanalysis**: the process of recovering the plaintext from ciphertext without knowledge of the encryption method, or with knowledge of the encryption method, but not the key.

- **Cryptosystem**: a five-tuple $(\mathcal{P}, \mathcal{C}, \mathcal{K}, \mathcal{E}, \mathcal{D})$ where $\mathcal{P}$ is the set of plaintext messages, $\mathcal{C}$ is the set of ciphertext messages, $\mathcal{K}$ is the set of keys, $\mathcal{E}$ is the set of encryption functions, and $\mathcal{D}$ is the set of decryption functions.

- **Private key encryption**: encryption where both encryption keys and decryption keys must be kept secret.

- **Public key encryption**: encryption where encryption keys are public knowledge, but decryption keys are kept secret.

- **RSA cryptosystem**: the cryptosystem where $\mathcal{P}$ and $\mathcal{C}$ are both $Z_{26}$, $\mathcal{K}$ is the set of pairs $k = (n, e)$ where $n = pq$ where $p$ and $q$ are large primes and $e$ is a positive integer, $E_{k}(p) = p^e \mod n$, and $D_k(c) = c^d \mod n$ where $d$ is the inverse of $e$ modulo $(p - 1)(q - 1)$.

- **Key exchange protocol**: a protocol sued for two parties to generate a shared key.

- **Digital signature**: a method that a recipient can use to determine that the purported sender of a message actually sent the message.

- **Fully homomorphic cryptosystem**: a cryptosystem that allows arbitrary computations to be run on encrypted data so that the output is the encryption of the unencrypted output of the unencrypted input.

### RESULTS

- **Division algorithm**: Let $a$ and $d$ be integers with $d$ positive. Then there are unique integers $q$ and $r$ with $0 \leq r < d$ such that $a = dq + r$.

  Let $b$ be an integer greater than 1. Then if $n$ is a positive integer, it can be expressed uniquely in the form $n = a_{k}b^{k} + a_{k-1}b^{k-1} + \cdots + a_{1}b + a_0$.

  The algorithm for finding the base $b$ expansion of an integer.

  The conventional algorithms for addition and multiplication of integers.

  The fast modular exponentiation algorithm.

- **Duclidean algorithm**: for finding greatest common divisors by successively using the division algorithm.

- **Bezout's theorem**: If $a$ and $b$ are positive integers, then $\gcd(a, b)$ is a linear combination of $a$ and $b$.

- **Sieve of Eratosthenes**: a procedure for finding all primes not exceeding a specified number $n$.

- **Chinese remainder theorem**: A system of linear congruences modulo pairwise relatively prime integers has a unique solution modulo the product of these moduli.

- **Fermat's little theorem**: If $p$ is prime and $p \nmid a$, then $a^{p - 1} \equiv 1 (\mod p)$.

