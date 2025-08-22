# CHAPTER 15 Combining Block Ciphers

[TOC]



**Multiple encryption** is one combination technique: using an algorithm to encrypt the same plaintext block multiple times with multiple keys.

## DOUBLE ENCRYPTION

First encrypt a block with the first key, then encrypt the resulting ciphertext with the second key. Decryption is the reverse process:
$$
C = D_{K_2}(E_{K_1}(P)) \\
P = D_{K_2}(E_{K_2}(C))
$$
, if the block algorithm is a group, then there is always a $K_3$ such that:
$$
C = E_{k_2}(E_{k_1}(P)) = E_{K_3}(P)
$$
**Meet-in-the-middle attack** works by encrypting from one end, decrypting from the other, and matching the results in the middle. In this attack, the cryptanalyst knows $P_1$, $C_1$, $P_2$ and $C_2$, such that:
$$
C_1 = E_{k_2}(E_{k_1}(P_1)) \\
C_2 = E_{k_2}(E_{k_1}(P_2))
$$
, for each possible $K$, he computes $E_k(P_1)$ and stores the result in memory. After collecting them all, he computes $D_k(C_1)$ for each $K$ and looks for the same result in memory. If he finds it, it is possible that the current key is $K_2$ and the key in memory is $K_1$. He tries encrypting $P_2$ with $K_1$ and $K_2$; if he gets $C_2$ he can be pretty sure(with a probability of success of 1 in $2^{2m - 2n}$, where $m$ is the block size) that he has both $K_1$ and $K_2$. If not, he keeps looking. The maximum number of encryption trials he will probably have to run is $2 * 2^n$, or $2^{n + 1}$. If the probability of error is too large, he can use a third ciphertext block to get a probability of success of 1 in $2^{3m - 2n}$.



## TRIPLE ENCRYPTION

### Triple Encryption with Two Keys

**Encrypt-Decrypt-Encrypt(EDE)** mode operates on a block three times with two keys: with the first key, then with the second key, and finally with the first key again:
$$
C = E_k(D_{k_2}(E_{k_1}(P))) \\
P = D_{k_1}(E_{k_2}(D_{k_1}(C)))
$$
Paul van Oorschot and Michael Wiener provide a known-plaintext attack, requiring $p$ known plaintext. This example assumes EDE mode:

1. Guess the first intermediate value $a$.

2. Tabulate, for each possible $K_1$, the second intermediate value, $b$, when the first intermediate value is $a$, using known plaintext:
   $$
   b = D_{k_1}(C)
   $$

   where $C$ is the resulting ciphertext from a known plaintext.

3. Look up in the table, for each possible $K_2$, elements with a matching second intermediate value, $b$:
   $$
   b = E_{k_2}(a)
   $$

4. The probability of success is $p/m$, where $p$ is the number of known plaintexts and $m$ is the block size. If there is no match, try another $a$ and start again.

### Triple Encryption with Three Keys

If you are going to use triple encryption, I recommend three different keys:
$$
C = E_{k_3}(D_{k_2}(E_{k_2}(P))) \\
P = D_{k_1}(E_{k_2}(D_{k_3}(C)))
$$

### Triple Encryption with Minimum Key (TEMK)

There is a secure way of using triple encryption with two keys that prevents the previous attack, called **Triple Encryption with Minimum Key(TEMK)**. The trick is to derive three keys from two: $X_1$ and $X_2$:
$$
K_1 = E_{X_1}(E_{X_2}(E_{X_1}(T_1))) \\
K_2 = E_{X_1}(E_{X_2}(E_{X_1}(T_2))) \\
K_3 = E_{X_1}(E_{X_2}(E_{X_1}(T_3))) \\
$$
$T_1$, $T_2$ and $T_3$ are constants, which do not have to be secret. This is a special construction that guarantees that for any particular pair of keys, the best attack is a known-plaintext attack.

### Triple-Encryption Modes

TODO