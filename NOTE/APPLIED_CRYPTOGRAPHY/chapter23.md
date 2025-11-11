# CHAPTER 23 Special Algorithms for Protocols

[TOC]



## MULTIPLE-kEY PUBLIC-kEY CRYPTOGRAPHY

This is a generalization of RSA. The modulus, $n$ is the product of two primes, $p$ and $q$. However, instead of choosing $e$ and $d$ such that $ed = 1 \mod ((p - 1)(q - 1))$, choose $t$ keys, $K_i$; such that:
$$
K_1 * K_2 * ... * K_t \equiv 1 \mod ((p - 1)(q - 1))
$$
, since:
$$
M^{K_1 \cdot K_2 \cdot ... \cdot K_t} = M
$$
, this is a multiple-key scheme.



## SECRET-SHARING ALGORITHMS

### LaGrange Interpolating Polynomial Scheme

Adi Shamir uses polynomial equations in a finite field to construct a threshold scheme. Choose a prime, $p$, which is both larger than the number of possible shadows and larger than the largest possible secret. To share a secret, generate an arbitrary polynomial of degree $m - 1$.

The shadows are obtained by evaluating the polynomial at $n$ different points:
$$
K_i = F(x_i)
$$
In other words, the first shadow could be the polynomial evaluated at $x = 1$, the second shadow could be the polynomial evaluated at $x = 2$, and so forth.

Since the quadratic polynomial has three unknown coefficients, $a$, $b$ and $M$, any three shadows can be used to create three equations. Two shadows cannot. One shadow cannot. Four or five shadows are redundant.

### Vector Scheme

George Blakley invented a scheme using points in space. The messge is defined as a point in $m$-dimensional space. Each shadow is the equation of an $(m - 1)$-dimensional hyperplane that includes the point. The intersection of any $m$ of the hyperplanes exactly determines the point.

### Asmuth-Bloom

This scheme uses prime numbers. For an $(m, n)$-threshold scheme, choose a large prime, $p$, greater than $M$. Then choose $n$ numbers less than $p$, $d_1$, $d_2$, ..., $d_n$ such that:

1. The $d$ values are in increasing order; $d_i < d_{i + 1}$
2. Each $d_i$ is relatively prime to every other $d_i$
3. $d_1 * d_2 * ... * d_m > p * d_{n - m + 2} * d_{n - m + 3} * ... * d_n$

To distribute the shadows, first choose a random value $r$ and compute
$$
M' = M + rp
$$
The shadows, $k_i$, are:
$$
k_i = M' \mod d_i
$$
Any $m$ shadows can get together and reconstruct $M$ using the Chinese remainder theorem, but any $m - 1$ cannot.

### Karnin-Greene-Hellman

This scheme uses matrix multiplication. Choose $n + 1$ $m$-dimensional vectors, $V_0, V_1, ..., V_n$, such that any possible $m * m$ matrix formed out of those vectors has rank $m$. The vector $U$ is a row vector of dimension $m + 1$.

$M$ is the matrix product $U \cdot V_0$. The shadows are the products $U \cdot V_i$, where $i$ is a number from 1 to $n$.

Any $m$ shadows can be used to solve the $m * m$ system of linear equations, where the unknowns are the coefficients of $U$. $UV_0$ can be computed from $U$. Any $m - 1$ shadows cannotsolve the system of linear equations and therefore cannot recover the secret.

### Sharing a Secret with Cheaters

Choose a prime, $p$, that is both larger than $n$ and larger than:
$$
(s - 1)(m - 1)/e + m
$$
Where $s$ is the largest possible secret and $e$ is the probability of successful cheating. You can make $e$ as small as you want; it just makes the computation more complex. Construct your shadows as before, except instead of using 1, 2, 3, ..., n for $x_i$, choose random numbers between 1 and $p - 1$ for $x_i$.



## SUBLIMINAL CHANNEL

### Ong-Schnorr-Shamir

This subliminal channel, designed by Gustavus Simmons, uses the One-Schnorr-Shamir identification scheme. As in the original scheme, the sender(Alice) chooses a public modulus, $n$, and a private key, $k$, suchthat $n$ and $k$ are relatively prime. Unlike the original scheme, $k$ is shared between Alice and Bob, the recipient of the subliminal message.

The public key is calculated:
$$
h = -k^2 \mod n
$$
If Alice wants to send the subliminal message $M$ by means of the innocuous message $M'$, she first confirms that $M'$ and $n$ are relatively prime, and that $M$ and $n$ are relatively prime.

Alice calculates:
$$
S_1 = 1/2 * ((M'/M + M)) \mod n \\
S_2 = k/2 * ((M'/M - M)) \mod n
$$
Together, the pair, $S_1$ and $S_2$, is the signature under the traditional Ong-Schnorr-Shamir scheme and the carrier of the subliminal message.

Walter the warden can authenticate the message as described by the Ong-Schnorr-Shamir signature scheme, but Bob can do better. He can authenticate the message. He confirms that:
$$
S_1^2 - S_2^2/k^2 \equiv M' (\mod n)
$$
If the message is authentic, the receiver can recover the subliminal message using this formula:
$$
M = M'/(S_1 + S_2 K^{-1}) \mod n
$$

### ElGammal

Key generation is the same as the basic ElGamal signature scheme. First choose a prime, $p$, and two random numbers, $g$ and $r$, such that both $g$ and $r$ are less than $p$. Then calculate:
$$
K = g^r \mod p
$$
The public key is $K$, $g$, and $p$. The private key is $r$. Besides Alice, Bob also knows $r$; it is the key that is used to send and read the subliminal message in addition to being the key used to sign the innocuous message.

To send a subliminal message $M$ using the innocuous message $M'$, $M$ and $p$ must be all relatively prime to each other, and $M$ and $p - 1$ must be relatively prime. Alice calculates:
$$
X = g^M \mod p
$$
and solves the following equation for $Y$ (using the extended Euclidean algorithm):
$$
M' = rX + MY \mod (p - 1)
$$
As in the basic ElGamal scheme, the signature is the pair: $X$ and $Y$.

Walter can verify the ElGamal signature. He confirms that:
$$
K^X X^Y = g^{M'}(\mod p)
$$
Bob can recover the subliminal message. First he confirms that:
$$
(g^r)^X X^Y = g^{M'}(\mod p)
$$
If it does, he accepts the message as genuine (not from Walter).

Then, to recover $M$, he computes:
$$
M = (Y^{-1}(M' - rX)) \mod (p - 1)
$$

### ESIGN

In ESIGN, the secret key is a pair of large prime numbers, $p$ and $q$, and the public key is $n = p^2q$. With a subliminal channel, the private key is three primes, $p$, $q$, and $r$, and the public key is $n$, such that:
$$
n = p^2 qr
$$
The variable, $r$, is the extra piece of information that Bob needs to read the subliminal message.

To sign a normal message, Alice first picks a random number, $x$, such that $x$ is less than $pqr$ and computes:
$$
w, \text{the least integer that is larger than }(H(m) - x^k \mod n) / pqr \\
s = x + ((w/kx^{k - 1}) \mod p)pqr
$$
$H(m)$ is the hash of the message; $k$ is a security parameter. The value $s$ is the signature.

To verify the signature, Bob computes $s^k \mod n$. He also computes $a$, which is the least integer larger thant he number of bits of $n$ divided by 3. If $H(m)$ is less than or equal to $s^k \mod n$, and if $x^k \mod n$ is less than $H(m) + 2^a$, then the signature is considered valid.

To send a subliminal message, $M$, using the innocuous message, $M'$, Alice calculates $s$ using $M$ in place of $H(m)$. This means that the message must be smaller than $p^2qr$. She then chooses a random value, $u$, and calculates:
$$
x' = M' + ur
$$
Then, use this $x'$ value as the "random number" $x$ to sign $M'$. This second $s$ value is sent as a signature.

Walter can verify that $s$ (the second $s$) is a valid signature of $M'$.

Bob can also authenticate the message in the same way. But, since he also knows $r$, he can calculate
$$
s = x' + ypqr = M + ur + ypqr \equiv M(\mod r)
$$

### Foiling the DSA Subliminal Channel

Here's the protocol:

1. Alice chooses $k'$ and sends Bob:
   $$
   u = g^{k'} \mod p
   $$

2. Bob chooses $k''$ and sends it to Alice.

3. Alice calculates $k = k'k'' \mod (p - 1)$. She uses $k$ to sign her message, $M$, with the DSA and sends Bob the signature: $r$ and $s$.

4. Bob verifies that
   $$
   ((u^{k''} \mod p) \mod q) = r
   $$

If it does, he knows that $k$ was used to sign $M$.



## UNDENIABLE DIGITAL SIGNATURES

This undeniable signature algorithm is by David Chaum. First, a large prime, $p$, and a primitive element, $g$, are made public, and used by a group of signers. Alice has a private key, $x$, and a public key, $g^x \mod p$.

To sign a message, Alice computes $z = m^x \mod p$. That's all she has to do. Verification is a little more complicated.

1. Bob chooses two random numbers, $a$ and $b$, both less than $p$, and sends Alice:
   $$
   c = z^a(g^x)^b \mod p
   $$

2. Alice computes $t = x^{-1} \mod (p - 1)$, and sends Bob:
   $$
   d = c^t \mod p
   $$

3. Bob confirms that
   $$
   d \equiv m^a g^b (\mod p)
   $$

If it is, he accepts the signature as genuine.

### Convertible Undeniable Signatures

Like ElGamal, first choose two primes, $p$ and $q$, such that $q$ divides $p - 1$. Now you have to create a number, $g$, less than $q$. First choose a random number, $h$, between 2 and $p - 1$. Calculate:
$$
g = h^{(p - 1)/q} \mod p
$$
If $g$ equals the 1, choose another random $h$. If it doesn't, stick with the $g$ you have.

The private keys are two different random numbers, $x$ and $z$, both less than $q$. The public keys are $p, q, g, y$ and $u$, where:
$$
y = g^x \mod p \\
u = g^z \mod p
$$
To compute the convertible undeniable signature of message $m$ (which is actually the hash of a message), first choose a random number, $t$, between 1 and $q - 1$. Then compute
$$
T = g^t \mod p
$$
and
$$
m' = Ttzm \mod q
$$
Now, compute the standard ElGamal signature on $m'$. Choose a random number, $R$, such that $R$ is less than and relatively prime to $p - 1$. Then compute $r = g^R \mod p$, and use the extended Euclidean algorithm to compute $s$, such that:
$$
m' \equiv rx + Rx(\mod q)
$$
The signature is the ElGamal signature $(r, s)$, and $T$.

Here's how Alie verifies her signature to Box:

1. Bob generates two random numbers, $a$ and $b$. He computes $c = T^{Tma} g^b \mod p$ and sends that to Alice.
2. Alice generates a random number, $k$, and computes $h_1 = cg^k \mod p$, and $h_2 = h_1^z \mod p$, and sends both of those numbers to Bob.
3. Bob sends Alice $a$ and $b$.
4. Alice verifies that $c = T^{Tma}g^b \mod p$. She sends $k$ to Bob.
5. Bob verifies that $h_1 = T^{Tma} g^{b + k} \mod p$, and that $h_2 = y^{ra} r^{sa} u^{b + k} \mod p$.

Alice can convert all of her undeniable signatures to normal signatures by publishing $z$. Now, anyone can verify her signature without her help.



## DESIGNATED CONFIRMER SIGNATURES

First, a large prime, $p$ and a primitive element, $g$, are made public and used by a group of users. The product of two primes, $n$, is also public. Carol has a private key, $z$, and a public key is $h = g^x \mod p$.

In this protocol, Alice can sign $m$ such that Bob is convinced that the signature is valid, but cannot convince a third party.

1. Alice chooses a random $x$ and computes:
   $$
   a = g^x \mod p \\
   b = h^x \mod p
   $$
   She computes the hash of $m$, $H(m)$, and the hash of $a$ and $b$ concatenated, $H(a, b)$. She then computes
   $$
   j = (H(m) \oplus H(a, b))^{1/3} \mod n
   $$
   
   and sends $a$, $b$ and $j$ to Bob.
   
1. Bob choose two random numbers, $s$ and $t$, both less than $p$, and sends Alice
   $$
   c = g^s h^t \mod p
   $$
   
1. Alice chooses a random $q$ less than $p$, and sends Bob
   $$
   d = g^q \mod p \\
   e = (cd)^x \mod p
   $$
   
1. Bob sends Alice $s$ and $t$.
   
1. Alice confirms that
   $$
   g^s h^t = c (\mod p)
   $$
   Then she sends Bob $q$.
   
1. Bob confirms
   $$
   d \equiv g^q(\mod p) \\
   e/a^q \equiv a^s b^t(\mod p) \\
   H(m) \oplus H(a, b) \equiv j^{1/3} \mod n
   $$
   If they all check out, he accepts the signature as genuine.

Bob cannot usea transcript of this proof to convince Dave that the signature is genuine, but Dave can conduct a protocol with Alice's designated confirmer, Carol. Here's how Carol convinces Dave that $a$ and $b$ Constitute a valid signature.

1. Dave chooses a random $u$ and $v$, both less than $p$, and sends Carol
   $$
   k = g^u a^v \mod p
   $$

2. Carol chooses a random $w$, less than $p$, and sends Dave
   $$
   l = g^w \mod p \\
   y = (kl)^z \mod p
   $$

3. Dave sends Carol $u$ and $v$.

4. Carol confirms that 
   $$
   g^u a^v \equiv k (\mod p)
   $$
   Then she sends Dave $w$.

5. Dave confirms that
   $$
   g^w \equiv l(\mod p) \\
   y/h^w \equiv h^u b^v(\mod p)
   $$
   If they both check out, he accepts the signature as genuine.



## COMPUTING WITH ENCRYPTED DATA

### The Discrete Logarithm Problem

There is a large prime, $p$, and a generator, $g$. Alice has a particular value for $x$, and wants to know $e$, such that
$$
g^e \equiv x(\mod p)
$$
This is a hard problem, and Alice lacks the computational power to compute the result. Bob has the power to solve the problem--he represents the government, or a large computing organization, or whatever. Here's how Bob can do it without Alice revealing $x$:

1. Alice chooses a random number, $r$ less than $p$.

2. Alice computes
   $$
   x' = xg^r \mod p
   $$

3. Alice asks Bob to solve
   $$
   g^{e'} \equiv x'(\mod p)
   $$

4. Bob computes $e'$ and sends it to Alice.

5. Alice recovers $e$ by computing
   $$
   e = (e' - r) \mod (p - 1)
   $$



## FAIR COIN FLIPS

### Coin Flipping Using Square Roots

1. Alice chooses two large primes, $p$ and $q$, and sends their product, $n$ to Bob.

2. Bob chooses a random positive integer, $r$, such that $r$ is less than $n/2$. Bob computes
   $$
   z = r^2 \mod n
   $$
   and sends $z$ to Alice.

3. Alice computes the four square roots of $z (\mod n)$. She can do this because she knows the factorization of $n$. Let's call them $+x, -x, +y$, and $-y$. Call $x'$ the smaller of these two numbers:
   $$
   x \mod n \\
   -x \mod n
   $$
   Similarly, call $y'$ the smaller of these two numbers:
   $$
   y \mod n \\
   -y \mod n
   $$
   Note that $r$ is equal to either $x'$ or $y'$.

4. Alice guesses whether $r = x'$ or $r = y'$, and sends her guess to Bob.

5. If Alice's guess is correct, the result of the coin flip is heads. If Alice's guess is incorrect, the result of the coin flip is tails. Bob announces the result of the coin flip.

   (Verification subprotocol)

6. Alice sends $p$ and $q$ to Bob.

7. Bob computes $x'$ and $y'$ and sends them to Alice.

8. Alice calculates $r$.

Alice has no way of knowing $r$, so her guess is real. She only tells Bob one bit of her guess in step 4 to prevent Bob from getting both $x'$ and $y'$. If Bob has both of those numbers, he can change $r$ after step 4.