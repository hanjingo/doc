# Chapter 21 Identification Schemes

[TOC]



## FEIGE-FIAT-SHAMIR

### Feige-Fiat-Shamir Identification Scheme

Before issuing any private keys, the arbitrator chooses a random modulus, $n$, which is the product of two large primes. In real life, $n$ should be at least 512 bits long and probably closer to 1024 bits. This $n$ can be shared among a group of provers. (Choosing a Blum integer makes computation easier, but it is not required for security). To generate Peggy's public and private keys, first choose $k$ different numbers: $v_1, v_2, ..., v_k$, where each $v_i$, is a quadratic residue mod $n$. In other words, choose $v_i$ such that $x^2 = v_i$ mod $n$ has a solution and $v_i^{-1}$ mod $n$ exists. This string, $v_1, v_2, ..., v_k$, is the public key. Then calculate the smallest $s_i$ such that $s_i = \sqrt(v_i^{-1}) \mod n$. This string $s_1, s_2, ..., s_k$ is the private key.

And the protocol is:

1.  Peggy picks a random $r$, when $r$ is less than $n$. She teh computes $x = r^2 \mod n$, and sends $x$ to Victor.
2. Victor sends Peggy a random binary string $k$-bits long: $b_1, b_2, ..., b_k$.
3. Peggy computes $y = r * (s_1^{b_1} * S_2^{b_2} * ... * s_k^{b_k}) \mod n$. (She multiplies together whichever values of $s_1$ that correspond to $b_i = 1$. If Victor's first bit is a 1, then $s_1$ is part of the product; if Victor's first bit is a 0, then $s_1$ is not part of the product, and so on.) She sends $y$ to Victor.
4. Victor verifies that $x = y^2 + (v_1^{b_1} * v_2^{b_2} * ... * v_k^{b_k}) \mod n$. (He multiplies together the values of $v_i$ Based on the random binary string. If his first bit is a 1, then $v_1$ is part of the product; if his first bit is a 0, then $v_1$ is not part of the product, and so on.)

Peggy and Victor repeat this protocol $t$ times, until Victor is convinced that Peggy knows $s_1, s_2, ..., s_k$.

The chance that Peggy can fool Victor is 1 in $2^{kt}$. The authors recommend a 1 in $2^{20}$ chance of a cheater fooling Victor and suggest that $k = 5$ and $t = 4$. If you are more paranoid, increase these numbers.

### Fiat-Shamir Sigmature Scheme

The setup is the same as the identification scheme. Choose $n$ to be the product of two large primes. Generate the public key, $v_1, v_2, ..., v_k$ and the private key, $s_1, s_2, ..., s_k$, such that $s_i= sqrt(v_i^{-1}) \mod n$:

1. Alice picks $t$ random integers between 1 and $n:r_1, r_2, ..., r_t$, and computes $x_1, x_2, ..., x_t$ such that $x_i = r_i^{2} \mod n$.

2. Alice hashes the concatenation of the message and the string of $x_i s$ to generate a bit stream: $H(m, x_1, x_2, ..., x_t)$. She uses the first $k * t$ bits of this string as values of $b_{ij}$, where $i$ goes from 1 to t, and $j$ goes from 1 to $k$.

3. Alice computes $y_1, y_2, ..., y_t$, where:
   $$
   y_i = r_i * (s_1^{b_{i1}} * s_2^{b_{i2}} * ... * s_k^{b_{ik}}) \mod n
   $$
   (For each $i$, she multiplies together the values of the $s_i$ based on the random $b_{i, j}$ Values. If $b_{i, 1}$ is a 1, then $s_1$ is multiplied; f $b_{i,1}$ is a 0, then $s_1$ is not multiplied.)

4. Alice sends Bob $m$, all the bit values of $b_{i,j}$, and all the value of $y_i$. He already has Alice's public key: $v_1, v_2, ..., v_k$.

5. Bob computes $z_1, z_2, ..., z_t$, where:
   $$
   z_i = y_i^{2} * (v_1^{b_{i1}} * v_2^{b_{i2}} * ... * s_k^{b_{ik}}) \mod n
   $$
   (For each $i$, she multiplies together the values of the $s_i$ based on the $b_{i, j}$ values.) Also note that $z_i$ should be equal to $x_i$.

6. Bob verifies that the first $k * t$ bits of $H(m, z_1, z_2, ..., z_t)$ are the $b_{i,j}$ values that Alice sent him.

As with the identification scheme, the security of this signature scheme is proportional to $1/2^{kt}$. It also depends on the difficulty of factoring $n$. Fiat and Shamir pointed out that forging a signature is easier when the complexity of factoring $n$ is considerably lower than $2^{kt}$. And, because of birthday-type attacks, they recommend that $k * t$ be increased from 20 to at least 72. They suggest $k = 9$ and $t = 8$.

Silvio Micali and Adi Shamir improved the Fiat-Shamir protocol. They chose $v_1, v_2, ..., v_k$ to be the first $k$ prime numbers. So:
$$
v_1 = 2, v_2 = 3, v_3 = 5, \text{and so on.}
$$
This is the public key.

The private key, $s_1, s_2, ..., s_k$ is a random square root, determined by:
$$
s_i = sqrt(v_i^{-1} \mod n)
$$
In this version, every person must have a different $n$. The modification makes it easier to verify signatures. The time required to generate signatures, and the security of those signatures, is unaffected.



## GUILLOU-QUISQUATER

### Guillou-Quisquater Identification Scheme

Peggy sends Victor her credentials, $j$. Now, she wants to prove to Victor that those credentials are hers. To do this, she has to convince Victor that she knows $B$. Here's the protocol:

1. Peggy picks a random integer $r$, such that $r$ is between 1 and $n - 1$. She computes $T = r^v \mod n$ and sends it to Victor.
2. Victor picks a random integer, $d$, such that $d$ is between zero and $v - 1$. He sends $d$ to Peggy.
3. Peggy computes $D = rB^d \mod n$, and sends it to Victor.
4. Victor computes $T' = D^v J^d \mod n$. If $T \equiv T'(\mod n)$, then the authentication succeeds.

The math isn't that complex:
$$
T' = D^v J^d = (rB^d)^v J^d = r^v B^{dv} J^d = r^v(JB^v)^d = r^v \equiv T(\mod n)
$$
Since $B$ was constructed to satisfy:
$$
JB^v \equiv 1 (\mod n)
$$

### Guillou-Quisquater Signature Scheme

The public and private key setup is the same as before. Here's the protocol:

1. Alice picks a random integer $r$, such that $r$ is between 1 and $n - 1$. She computes $T = r^v \mod n$.
2. Alice computes $d = H(M, T)$, where $M$ is the messge being signed and $H(x)$ is a one-way hash function. The $d$ produced by the hash function must be between 0 and $v - 1$. If the output of the hash function is not within this range, it must be reduced modulo $v$.
3. Alice computes $D = rB^d \mod n$. The signature consists of the message, $M$, the two calculated values, $d$ and $D$, and her credentials, $J$. She sends this signature to Bob.
4. Bob computes $T' = D^v J^d \mod n$. He then computes $d' = H(M, T')$. If $d = d'$, then Alice must know $B$ and the signature is vlaid.

### Multiple Signatures

Alice and Bob have their own unique $J$ and $B$ values: $(J_A, B_A)$ and $(J_B, B_B)$. The values $n$ and $v$ are common to the system:

1. Alice picks a random integer, $r_A$ such that $r_A$ is between 1 and $n - 1$. She computes $T_A = r_A^v \mod n$ and sends $T_A$ to Bob.
2. Bob picks a random integer, $r_B$, such that $r_B$ is between 1 and $n - 1$. He computes $T_B = r_B^v \mod n$ and sends $T_B$ to Alice.
3. Alice and Bob each compute $T = (T_A T_B) \mod n$.
4. Alice and Bob each compute $d = H(M, T)$, where $M$ is the message being signed and $H(X)$ is a one-way hash function. The $d$ produced by the hash function must be between 0 and $v - 1$. If the output of the hash function is not within this range, it must be reduced modulo $v$.
5. Alice computes $D_A = r_A B_A^d \mod n$ and sends $D_A$ to Bob.
6. Bob computes $D_B = r_B B_B^d \mod n$ and sends $D_B$ to Alice.
7. Alice and Bob each compute $D = D_A D_B \mod n$. The signature consists of the message, $M$, the two calculated values, $d$ and $D$, and both of their credentials: $J_A$ and $J_B$.
8. Carol computes $J = J_A J_B \mod n$.
9. Carol computes $T' = D^v J^d \mod n$. She then computes $d' = H(M, T')$. If $d \equiv d'$, then the multiple signature is valid. 



## SCHNORR

Claus Schnorr's authentication and signature scheme gets its security from the difficulty of calculating discrete logarithms. To generate a key pair, first choose two primes, $p$ and $q$, such that $q$ is a prime factor of $p - 1$. Then, choose an $a$ not equal to 1, such that $a^q \equiv 1 (\mod p)$. All these numbers can be common to a group of users and can be freely published.

To generate a particular public-key/private-key key pair, choose a random number less than $q$. This is the private key $s$. Then calculate $v = a^{-s} \mod p$. This is the public key.

### Authentication Protocol

1. Peggy picks a random number, $r$, less than $q$, and computes $x = a^r \mod p$. This is the preprocessing stage and can be done long before Victor is present.
2. Peggy sends $x$ to Victor.
3. Victor sends Peggy a random number, $e$, between 0 and $2^t - 1$.
4. Peggy computes $y = (r + se) \mod q$ and sends $y$ to Victor.
5. Victor verifies that $x = a^t v^e \mod p$

The security is based on the parameter $t$. The difficulty of breaking the algorithm is about $2^t$. Schnorr recommended that $p$ be about 512 bits, $q$ be about 140 bits, and $t$ be 72.

### Digital Signature Protocol

Schnorr can also be used as a digital signature protocol on a message, $M$. The public-key/private-key key pair is the same, but we're now adding a one-way hash function, $H(M)$:

1. Alice picks a random number, $r$, less than $q$, and computes $x = a^r \mod p$. This computation is the preprocessing stage.

2. Alice concatenates $M$ and $x$, and hashes the result:
   $$
   e = H(M, x)
   $$

3. Alice computes $y = (r + se) \mod q$. The signature is $e$ and $y$; she sends these to Bob.

4. Bob computes $x' = a^y v^e \mod p$. He then confirms that the concatenation of $M$ and $x'$ hashes to $e$:
   $$
   e = H(M, x')
   $$
   If it does, he accepts the signature as valid.
