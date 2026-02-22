## Chapter 22 Key-Exchange Algorithms

[TOC]



## DIFFIE-HELLMAN

First, Alice and Bob agree on a large prime, $n$ and $g$, such that $g$ is primitive mod $n$. These two integers don't have to be secret; Alice and Bob can agree to them over some insecure channel. They can even be common among a group of users. It doesn't matter. Then, the protocol goes as follows:

1. Alice chooses a random large integer $x$ and sends Bob:
   $$
   X = g^x \mod n
   $$

2. Bob chooses a random large integer $y$ and sends Alice:
   $$
   Y = g^y \mod n
   $$

3. Alice computes:
   $$
   k = Y^x \mod n
   $$

4. Bob computes:
   $$
   k' = X^y \mod n
   $$

Both $k$ and $k'$ are equal to $g^{xy} \mod n$. No one listening on the channel can compute that value; they only know $n$, $g$, $X$ and $Y$. Unless they can compute the discrete logarithm and recover $x$ or $y$, they do not solve the problem. So, $k$ is the secret key that both Alice and Bob computed independently.

### Diffie-Hellman with Three or More Parties

The Diffie-Hellman key-exchange protocol can easily be extended to work with three or more people. In this example, Alice, Bob, and Carol together generate a secret key:

1. Alice chooses a random large integer $x$ and sends Bob:
   $$
   X = g^x \mod n
   $$

2. Bob chooses a random large integer $y$ and sends Carol:
   $$
   Y = g^y \mod n
   $$

3. Carol chooses a random large integer $z$​ and sends Alice:
   $$
   Z = g^z \mod n
   $$

4. Alice sends Bob:
   $$
   Z' = Z^x \mod n
   $$

5. Bob sends Carol:
   $$
   X' = X^y \mod n
   $$

6. Carol sends Alice:
   $$
   Y^{'} = Y^z \mod n
   $$

7. Alice computes:
   $$
   k = Y^{'x} \mod n
   $$

8. Bob computes:
   $$
   k = Z^{'y} \mod n
   $$

9. Carol computes:
   $$
   k = X^{'z} \mod n
   $$

The secret key, $k$, is equal to $g^{xyz} \mod n$, and no one else listening in on the communications can compute that value. The protocol can be easily extended to four or more people; just add more people and more rounds of computation.

### Extended Diffie-Hellman

Diffie-Hellman also works in commutitive rings and Galois field $GF(2^k)$.

### Hughes

This variant of Diffie-Hellman allows Alice to generate a key and send it to Bob:

1. Alice chooses a random large integer $x$ and generates:
   $$
   k = g^x \mod n
   $$

2. Bob chooses a random large integer $y$ and sends Alice:
   $$
   Y = g^y \mod n
   $$

3. Alice sends Bob:
   $$
   X = Y^x \mod n
   $$

4. Bob computes:
   $$
   z = y^{-1} \\
   k' = X^z \mod n
   $$

If everything goes correctly, $k = k'$.

The advantage of this protocol over Diffie-Hellman is that $k$ can be computed before any interaction, and Alice can encrypt a message using $k$ prior to contacting Bob. She can send it to a variety of people and interact with them to exchange the key individually later.



## STATION-TO-STATION PROTOCOL

This protocol assumes that Alice has a certificate with Bob's public key and that Bob has a certificate with Alice's public key. These certificates have been signed by some trusted authority outside this protocol. Here's how Alice and Bob generate a secret key, $k$:

1. Alice generates a random number, $x$, and sends it to Bob.

2. Bob generates a random number, $y$. Using the Diffie-Hellman protocol he computes their shared key based on $x$ and $y: k$. He signs $x$ and $y$, and encrypts the signature using $k$. He then sends that, along with $y$, to Alice.
   $$
   y,E_{k}(S_B(x,y))
   $$

3. Alice also computes $k$. She decrypts the rest of Bob's message and verifies his signature. Then she sends Bob a signed message consisting of $x$ and $y$, encrypted in their shared key
   $$
   E_k(S_A(x, y))
   $$

4. Bob decrypts the message and verifies Alice's signature.



## SHAMIR'S THREE-PASS PROTOCOL

This assumes the existence of a symmetric cipher that is commutative, that is:
$$
E_A(E_B(P)) = E_B(E_A(P))
$$
Alice's secret key is $A$; Bob's secret key is $B$. Alice wants to send a message, $M$, to Bob. Here's the protocol:

1. Alice encrypts $M$ with her key and sends Bob:
   $$
   C_1 = E_A(M)
   $$

2. Bob encrypts $C_1$ with his key and sends Alice:
   $$
   C_2 = E_B(E_A(M))
   $$

3. Alice decrypts $C_2$ with her key and sends Bob:
   $$
   C_3 = D_A(E_B(E_A(M))) = D_A(E_A(E_B(M))) = E_B(M)
   $$

4. Bob decrypts $C_3$ with his key to recover $M$.

One-time pads are commutative and have perfect secrecy, but hey will not work with this protocol. With a one-time pad, the three ciphertext messages would be:
$$
C_1 = P \oplus A \\
C_2 = P \oplus A \oplus B \\
C_3 = P \oplus B
$$
Eve, who can record the three messages as they pass between Alice and Bob, simply XORs them together to retrieve the message:
$$
C_1 \oplus C_2 \oplus C_3 = (P \oplus A) \oplus (P \oplus A \oplus B) \oplus (P \oplus B) = P
$$
This clearly won't work.

Shamir (and independently, Jim Omura) described an encryption algorithm that will work with this protocol, one similar to RSA. Let $p$ be a large prime for which $p - 1$ has a large prime factor. Choose an encryption key, $e$, such that $e$ is relatively prime to $p - 1$. Calculate $d$ such that $de \equiv 1 (\mod p - 1)$​.

To encrypt a message, calculate:
$$
C = M^e \mod p
$$
To decrypt a message, calculate:
$$
M = C^d \mod p
$$
There seems to be no way for Eve to recover $M$ without solving the discrete logarithm problem, but this has never been proved.



## ENCRYPTED KEY EXCHANGE

### The Basic EKE Protocol

Alice and Bob (two users, a user and the host, or whoever) share a common password, $P$. Using this protocol, they can authenticate each other and generate a common session key, $K$:

1. Alice generates a random public-key/private-key key pair. She encrypts the public key, $K'$, using a symmetric algorithm and $P$ as the key: $E_p(K')$. She sends Bob:
   $$
   A, E_P(K')
   $$

2. Bob knows $P$. He decrypts the message to obtain $K'$. Then, he generates a random session key, $K$, and encrypts it with the public key he received from Alice and $P$ as the key. He sends Alice:
   $$
   E_P(E_{K'}(K))
   $$

3. Alice decrypts the message to obtain $K$. She generates a random string, $R_A$, encrypts it with $K$, and sends Bob:
   $$
   E_K(R_A)
   $$

4. Bob decrypts the message to obtain $R_A$. He generates another random string, $R_B$, encrypts both strings with $K$, and sends Alice the results:
   $$
   E_K(R_A, R_B)
   $$

5. Alice decrypts the message to obtain $R_A$ and $R_B$. Assuming the $R_A$ she received from Bob is the same as the one she sent to Bob in Step3, she encrypts $R_B$ with $K$ and sends it to Bob:
   $$
   E_K(R_B)
   $$

6. Bob decrypts the message to obtain $R_B$. Assuming the $R_B$ he received from Alice is the same one he sent to Alice in step4, the protocol is complete. Both parties now communicate using $K$ as the session key.

### Implementing EKE with EIGamal

Implementing EKE with the ElGamal algorithm is straightforward, and there is even a simplification of the basic protocol. Notation $g$ and $p$ are parts of the public key and are common to all users. The private key is a random number $r$. The public key is $g^r \mod p$. The message Alice sends to Bob in step1 becomes:
$$
Alice, g^r \mod p
$$
Note that this public key does not have to be encrypted with $P$. This is not true in general, but it is true for the ElGamal algorithm.

Bob chooses a random number, $R$ (for the ElGamal algorithm and independent of any random numbers chosen for EKE), and the message he sends to Alice in step2 becomes:
$$
E_p(g^R \mod p, Kg^{Rr} \mod p)
$$

### Implementing EKE with Diffie-Hellman

With the Diffie-Hellman protocol, $K$ is generated automatically. The final protocol is even simpler. A value for $g$ and $n$ is set for all users on the network.

1. Alice picks a random number, $r_A$, and sends Bob
   $$
   A, g^{r_A} \mod n
   $$
   With Diffie-Hellman, Alice does not have to encrypt her first message with $P$.

2. Bob picks a random number, $r_B$, and calculates
   $$
   K = g^{r_A * r_B} \mod n
   $$
   He generates a random string $R_B$, then calculates and sends Alice:
   $$
   E_p(g^{r_B} \mod n), E_k(R_B)
   $$

3. Alice decrypts the first half of Bob's message to obtain $g^{r_B} \mod n$. Then she calculates $K$ and uses $K$ to decrypt $R_B$. She generates another random string, $R_A$, encrypts both strings with $K$, and sends Bob the result.
   $$
   E_k(R_A, R_B)
   $$

4. Bob decrypts the message to obtain $R_A$ and $R_B$. Assuming the $R_B$ he received from Alice is the same as the one he sent to Alice in step 2, he encrypts $R_A$ with $K$ and sends it to Alice.
   $$
   E_k(R_A)
   $$

5. Alice decrypts the message to maintain $R_A$. Assuming the $R_A$ she received from Bob is the same as the one she sent to Bob in step 3, the protocol is complete. Both parties now communicate using $K$ as the session key.

### Augmented EKE

Alice's password $P$ (or perhaps some simple hash of it) will serve as the private key and as $P'$.

1. Alice picks her random exponent $R_a$ and transmits
   $$
   E_{p'}(g^{R_A} \mod n)
   $$

2. Bob, who knows only $P'$ and cannot derive $P$ from it, chooses $R_b$ and sends
   $$
   E_{p'}(g^{R_A} \mod n)
   $$

3. Both Alice and Bob calculate the shared session key $K = g^{r_A \cdot r_B} \mod n$. Finally, Alice proves that she knows $P$ itself, and not just $P'$, by sending
   $$
   E_k(S_p(K))
   $$



## FORTIFIED KEY NEGOTIATION

Here's the protocol. Alice and Bob share a secret password, $P$, and have just exchanged a secret key, $K$, using Diffie-Hellman key exchange. They use $P$ to check that their two session keys are the same (and that Eve is not attempting a man-in-the-middle attack), without giving $P$ away to Eve.

1. Alice sends Bob
   $$
   H'(P, K)
   $$

2. Bob computes $H'(P, K)$ and compares his result with what he received from Alice. If they match he sends Alice
   $$
   H'(H(P, K))
   $$

3. Alice computes $H'(H(P, K))$ and compares her result with what she received from Bob.

