# CHAPTER 3 Basic Protocols

[TOC]



## KEY EXCHANGE

A common cryptographic technique is to encrypt each individual conversation with a separate key. This is called a session key, because it is used for only one particular communications session.

### Key Exchange with Symmetric Cryptography

This protocol assumes that Alice and Bob, users on a network, each share a secret key with the Key Distribution Center (KDC)--Trent in our protocols. These keys must be in place before the start of the protocol:

1. Alice calls Trent and requests a session key to communicate with Bob.
2. Trent generates a random session key. He encrypts two copies of it: one in Alice's key and the other in Bob's key. Trent sends both copies to Alice.
3. Alice decrypts her copy of the session key.
4. Alice sends Bob his copy of the session key.
5. Bob decrypts his copy of the session key.
6. Both Alice and Bob use this session key to communicate securely.

### Key Exchange with Public-Key Cryptography

Alice and Bob use public-key cryptography to agree on a session key, and use that session key to encrypt data. In some practical implementations, both Alice's and Bob's signed public keys will be available on a database. This makes the key-exchange protocol even easier, and Alice can send a secure message to Bob even if he has never heard of her:

1. Alice gets Bob's public key from the KDC.
2. Alice generates a random session key, encrypts it using Bob's public key, and sends it to Bob.
3. Bob then decrypts Alice's message using his private key.
4. Both of them encrypt their communications using the same session key.

### Interlock Protocol

The **interlock protocol**, invented by Ron Rivest and Ali Shamir, has a good chance of foiling the man-in-the-middle attack. Here's how it works:

1. Alice sends Bob her public key.
2. Bob sends Alice his public key.
3. Alice encrypts her message using Bob's public key. She sends half of the encrypted message to Bob.
4. Bob encrypts his message using Alice's public key. he sends half of the encrypted message to Alice.
5. Alice sends the other half of her encrypted message to Bob.
6. Bob puts the two halves of Alice's message together and decrypts it with his private key. Bob sends the other half of his encrypted message to Alice.
7. Alice puts the two halves of Bob's message together and decrypts it with her private key.

### Key and Message Transmission

Alice and Bob need not complete the key-exchange protocol before exchanging messages. In this protocol, Alice sends Bob the message, $M$, without any previous key exchange protocol:

1. Alice generates a random session key, $K$ and encrypts $M$ using $K$.
   $$
   E_K(M)
   $$

2. Alice gets Bob's public key from the database.

3. Alice encrypts $K$ with Bob's public key.
   $$
   E_B(K)
   $$

4. Alice sends both the encrypted message and encrypted session key to Bob.
   $$
   E_K(M), E_B(K)
   $$

   (For added security against man-in-the-middle attacks, Alice can sign the transmission)

5. Bob decrypts Alice's session key, $K$, using his private key.

6. Bob decrypts Alice's message using the session key.

### Key and Message Broadcast

There is no reason Alice can't send the encrypted message to several people. In this example, Alice send the encrypted message to Bob, Carol, and Dave:

1. Alice generates a random session key, $K$, and encrypts $M$ using $K$.
   $$
   E_K(M)
   $$

2. Alice gets Bob's, Carol's, and Dave's public keys from the database.

3. Alice encrypts $K$ with Bob's public key, encrypts $K$ with Carol's public key, and then encrypts $K$ with Dave's public key.
   $$
   E_B(K), E_C(K), E_D(K)
   $$

4. Alice broadcasts the encrypted message and all the encrypted keys to anybody who cares to receive it.
   $$
   E_B(K), E_C(K), E_D(K), E_K(M)
   $$

5. Only Bob, Carol, and Dave can decrypt the key, $K$, each using his or her private key.

6. Only Bob, Carol, and Dave can decrypt Alice's message using $K$.



## AUTHENTICATION

### Authentication Using One-Way Functions

What Roger Needham and Mike Guy realized is that the host does not need to know the passwords; the host just has to be able to differentiate valid passwords from invalid passwords. This is easy with one-way functions. Instead of storing passwords, the host stores one-way functions of the passwords:

1. Alice sends the host her password.
2. The host performs a one-way function on the password.
3. The host compares the results of the one-way function to the value it previously stored.



## AUTHENTICATION AND KEY EXCHANGE

![tbl3_1](res/tbl3_1.png)

### Wide-Mouth Frog

The Wide-Mouth Frog protocol is probably the simplest symmetric key-management protocol that uses a trusted server. Both Alice and Bob share a secret key with Trent. The keys are just used for key distribution and not to encrypt any actual messages between users. Just by using two messages, Alice transfers a session key to Bob:

1. Alice concatenates a timestamp, Bob's name, and a random session key and encrypts the whole message with the key she shares with Trent. She sends this to Trent, along with her name.
   $$
   A, E_A(T_A, B, K)
   $$

2. Trent decrypts the message from Alice. Then he concatenates a new timestamp, Alice's name, and the random session key; he encrypts the whole message with the key he shares with Bob. Trent sends to Bob:
   $$
   E_B(T_B, A, K)
   $$

### Yahalom

In this protocol, both Alice and Bob share a secret key with Trent:

1. Alice concatenates her name and a random number, and sends it to Bob.
   $$
   A, R_A
   $$

2. Bob concatenates Alice's name, Alice's random number, his own random number, and encrypts it with the key he shares with Trent. He sends this to Trent, along with his name.
   $$
   B, E_B(A, R_A, R_B)
   $$

3. Trent generates two messages. The first consists of Bob's name, a random session key, Alice's random number, and Bob's random number, all encrypted with the key he shares with Alice. The second consists of Alice's name and the random session key, encrypted with the key he shares with Bob. He sent both messages to Alice.
   $$
   E_A(B, K, R_A, R_B), E_B(A, K)
   $$

4. Alice decrypts the first message, extracts $K$, and confirms that $R_A$ has the same value as it did in step 1. Alice sends Bob two messages. The first is the message received from Trent, encrypted with Bob's key. The second is $R_B$, encrypted with the session key.
   $$
   E_B(A, K), E_K(R_B)
   $$

5. Bob decrypts the message encrypted with his key, extracts $K$, and confirms that $R_B$ has the same value as it did in step 2.

### Needham-Schroeder

This protocol, invented by Roger Needham and Michael Schroeder, also uses symmetric cryptography and Trent.

1. Alice sends a message to Trent consisting of her name, Bob's name, and a random number.
   $$
   A, B, R_A
   $$

2. Trent generates a random session key. He encrypts a message consisting of a random session key and Alice's name with the secret key he shares with Bob. Then he encrypts Alice's random value, Bob's name, the key, and the encrypted message with the secret key he shares with Alice. Finally, he sends her the encrypted message:
   $$
   E_A(R_A, B, K, E_B(K, A))
   $$

3. Alice decrypts the message and extracts $K$. She confirms that $A_A$ is the same value that she sent Trent in step 1. Then she sends Bob the message that Trent encrypted in his key.
   $$
   E_B(K, A)
   $$

4. Bob decrypts the message and extracts $K$. He then generates another random value, $R_B$. He encrypts the message with $K$ and sends it to Alice.
   $$
   E_K(R_B)
   $$

5. Alice decrypts the message with $K$. She generates $R_B - 1$ and encrypts it with $K$. Then she sends the message back to Bob.
   $$
   E_K(R_B - 1)
   $$

6. Bob decrypts the message with $K$ and verifies that it is $R_B - 1$.

### Otway-Rees

This protocol also uses symmetric cryptography.

1. Alice generates a message consisting of an index number, her name, Bob's name, and a random number, all encrypted in the key she shares with Trent. She sends this message to Bob along with the index number, her name, and his name:
   $$
   I, A, B, E_A(R_A, I, A, B)
   $$

2. Bob generates a message consisting of a new random number, the index number, Alice's name, and Bob's name, all encrypted in the key he shares with Trent. He sends it to Trent, along with Alice's encrypted message, the index number, her name, and his name:
   $$
   I, A, B, E_A(R_A, I, A, B), E_B(R_B, I, A, B)
   $$

3. Trent generates a random session key. Then he cretes two messages. One is Alice's random number and the session key, encrypted in the key he shares with Alice. The other is Bob's random number and the session key, encrypted in the key he shares with Bob. He sends these two messages, along with the index number, to Bob:
   $$
   I, E_A(R_A, K), E_B(R_B, K)
   $$

4. Bob sends Alice the message encrypted in her key, along with the index number:
   $$
   I, E_A(R_A, K)
   $$

5. Alice decrypts the message to recover her key and random number. She then confirms that both have not changed int he protocol.

### Kerberos

Kerberos is a variant of Needham-Schroeder. Alice wantsto generate a session key for a conversation with Bob:

1. Alice sends a message to Trent with her identity and Bob's identity.
   $$
   A, B
   $$

2. Trent generates a message with a timestamp, a lifetime, $L$, a random session key, and Alice's identity. He encrypts this in the key he shares with Bob. Then he takes the timestamp, the lifetime, the session key, and Bob's identity, and encrypts these in the key he shares with Alice. He sends both encrypted messages to Alice.
   $$
   E_A(T, L, K, B), E_B(T, L, K, A)
   $$

3. Alice generates a message with her identity and the timestamp, encrypts it in $K$, and sends it to Bob. Alice also sends Bob the message encrytped in Bob's key from Trent.
   $$
   E_K(A, T), E_B(T, L, K, A)
   $$

4. Bob creates a message consisting of the timestamp plus one, encrypts it in $K$, and sends it to Alice.
   $$
   E_K(T + 1)
   $$

### Neuman-Stubblebine

It is an enhancement to Yahalom and is an excellent protocol.

1. Alice concatenates her name and a random number and sends it to Bob.
   $$
   A, R_A
   $$

2. Bob concatenates Alice's name, her random number, and a timestamp, and encrypts with the key he shares with Trent. He sends it to Trent along with his name and a new random number.
   $$
   B, R_B, E_B(A, R_A, T_B)
   $$

3. Trent generates a random session key. Then he creates two messages. The first is Bob's name, Alice's random number, a random session key, and the timestamp, all encrypted with the key he shares with Alice. The send is Alice's name, the session key, and the timestamp, all encrypted with the key he shares with Bob. He sends these both to Alice, along with Bob's random number.
   $$
   E_A(B, R_A, K, T_B), E_A(A, K, T_B), R_B
   $$

4. Alice decrypts the message encrypted with ehr key, extracts $K$, and confirms that $R_A$ has the same value as it did in step 1. Alice sends Bob two messages. The first is the message received from Trent, encrypted with Bob's key. The second is $R_B$, encrypted with the session key.
   $$
   E_B(A, K, T_B), E_K(R_B)
   $$

5. Bob decrypts the message encrypted with his key, extracts $K$, and confirms that $T_B$ and $R_B$ have the same value they did in step 2.

### DASS

The Distributed Authentication Security Service (DASS) protocols, developed at Digital Equipment Corporation, also provide for mutual authentication and key exchange. Unlike the previous protocols, DASS uses both public key and symmetric cryptography. Alice and Bob each have a private key. Trent has signed copies of their public keys.

1. Alice sends a message to Trent, consisting of Bob's name.
   $$
   B
   $$

2. Trent sends Alice Bob's public key, $K_B$, signed with Trent's private key, $T$. The signed message includes Bob's name.
   $$
   S_T(B, K_B)
   $$

3. Alice verifies Trent's signature to confirm that the key she received is actually Bob's public key. She generates a random session key, and a random public-key/private-key key pair: $K_p$. She encrypts a timestamp with $K$. Then she signs a key lifetime, $L$, her name, and $K_p$ with her private key, $K_A$. Finally, she encrypts $K$ with Bob's public key, and signs it with $K_p$. She sends all of this to Bob.
   $$
   E_K(T_A), S_{K_A}(L, A, K_P), S_{K_P}(E_{K_B}(K))
   $$

4. Bob sends a message to Trent (this may be a different Trent), consisting of Alice's name.
   $$
   A
   $$

5. Trent sends Bob Alice's public key, signed in Trent's private key. The signed message includes Alice's name.
   $$
   S_T(A, K_A)
   $$

6. Bob verifies Trent's signature to confirm that the key he received is actually Alice's public key. He then verifies Alice's signature and recovers $K_p$. He verifies the signature and uses his private key to recover $K$. Then he decrypts $T_A$ to make sure this is a current message.

7. If mutual authentication is required, Bob encrypts a new timestamp with $K$, and sends it to Alice.
   $$
   E_K(T_B)
   $$

8. Alice decrypts $T_B$ with $K$ to make sure that the message is current.

### Denning-Sacco

This protocol also uses public-key cryptography. Trent keeps a database of everyone's public keys.

1. Alice sends a message to Trent with her identity and Bob's identity:
   $$
   A, B
   $$

2. Trent sends Alice Bob's public key, $K_B$, signed with Trent's private key, $T$. Trent also sends Alice her own public key, $K_A$, signed with his private key.
   $$
   S_T(B, K_B), S_T(A, K_A)
   $$

3. Alice sends Bob a random session key and a timestamp, signed in her private key and encrypted in Bob's public key, along with both signed public keys.
   $$
   E_B(S_A(K, T_A)), S_T(B, K_B), S_T(A, K_A)
   $$

4. Bob decrypts Alice's message with his private key and then verifies Alice's signature with her public key. He checks to make sure that the timestamp is still valid.

### Woo-Lam

This protocol also uses public-key cryptography:

1. Alice sends a message to Trent with her identity and Bob's identity:
   $$
   A, B
   $$

2. Trent sends Alice Bob's public key, $K_B$, signed with Trent's private key, $T$.
   $$
   S_T(K_B)
   $$

3. Alice verifies Trent's signature. Then she sends Bob her name and a random number, encrypted with Bob's public key.
   $$
   E_{K_B}(A, R_A)
   $$

4. Bob sends Trent hsi name, Alice's name, and Alice's random number encrypted with Trent's public key, $K_T$.
   $$
   A, B, E_{K_T}(R_A)
   $$

5. Trent sends Bob Alice's public key, $K_A$, signed with Trent's private key. He also sends him Alice's random number, a random session key, Alice's name, and Bob's name, all signed with Trent's private key and encrypted with Bob's public key.
   $$
   S_T(K_A), E_{K_B}(S_T(R_A, K, A, B))
   $$

6. Bob verifies Trent's signatures. Then he sends Alice the second part of Trent's message from step 5 and a new random number--all encrypted in Alice's public key.
   $$
   E_{K_A}(S_T(R_A, K, A, B), R_B)
   $$

7. Alice verifies Trent's signature and her random number. Then she sends Bob the second random number, encrypted in the session key.
   $$
   T_K(R_B)
   $$

8. Bob decrypts his random number and verifies that it is unchanged.



## FORMAL ANALYSIS OF AUTHENTICATION AND KEY-EXCHANGE PROTOCOLS

There are four basic approaches to the analysis of cryptographic protocols:

1. Model and verify the protocol using specification languages and verification tools not specifically designed for the analysis of cryptographic protocols.
2. Develop expert systems that a protocol designer can use to develop and investigate different scenarios.
3. Model the requirements of a protocol family using logics for the analysis of knowledge and belief.
4. Develop a formal method based on the algebraic term-rewriting properties of cryptographic systems.



## MULTIPLE-KEY PUBLIC-KEY CRYPTOGRAPHY

Public-key cryptography uses two keys. A message encrypted with one key can be decrypted with the other. Usually one key is private and the other is public.
