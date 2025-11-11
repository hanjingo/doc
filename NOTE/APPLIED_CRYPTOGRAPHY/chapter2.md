# CHAPTER 2 Protocol Building Blocks

[TOC]



## INTRODUCTION TO PROTOCOLS

A **protocol** is a series of steps, involving two or more parties, designed to accomplish a task.

A **cryptographic protocol** is a protocol that uses cryptography.

People can try various ways to attack a protocol. Someone not involved in the protocol can eavesdrop on some or all of the protocol. This is called a **passive attack**, because the attacker does not affect the protocol.

Alternatively, an attacker could try to alter the protocol to his own advantage. He could pretend to be someone else, introduce new messages in the protocol, delete existing messages, substitute one message for another, replay old messages, interrupt a communications channel, or alter stored information in a computer. These are called **active attacks**, because they require active intervention.



## COMMUNICATIONS USING SYMMETRIC CRYPTOGRAPHY

In summary, symmetric cryptosystems have the following problems:

- Keys must be distributed in secret.
- If a key is compromised (stolen, guessed, extorted, bribed, etc.), then others can decrypt all message traffic encrypted with that key.
- Assuming a separate key is used for each pair of users in a network, the total number of keys increases rapidly as the number of users increases. A network of $n$ users requires $n(n - 1)/2$ keys.



## ONE-WAY FUNCTIONS

A **trapdoor one-way function** is a special type of one-way function, one with a secret trapdoor. It is easy to compute $f(x)$ given $x$, and hard to compute $x$ given $f(x)$.



## ONE-WAY HASH FUNCTIONS

A hash function is a function, mathematical or otherwise, that takes a variable-length input string(called a **pre-image**) and converts it to a fixed-length (generally smaller) output string(called a **hash value**). A simple hash function would be a function that takes a pre-image and returns a byte consisting of the XOR of all the input bytes.

A **message authentication code** (MAC), also known as a data authentication code (DAC), is a one-way hash function with the addition of a secret key.



## COMMUNICATIONS USING PUBLIC-KEY CRYPTOGRAPHY

**Public-key cryptography** uses two different keys--one public and the other private. It is computationally hard to deduce the private key from the public key. Anyone with the public key can encrypt a message, but not decrypt it. Only the person with the private key can decrypt the message.

### Hybrid Cryptosystems

In the real world, public-key algorithms are not a substitute for symmetric algorithms. They are not used to encrypt messages; they are used to encrypt keys. There are two reasons for this:

1. Public-key algorithms are slow.
2. Public-key crypto systems are vulnerable to chosen-plaintext attacks. If $C = E(P)$, when $P$ is one plaintext out of a set of $n$ possible plaintext, then a cryptanalyst only has to encrypt all $n$ possible plaintexts and compare the results with $C$ (remember, the encryption key is public). He won't be able to recover the decryption key this way, but he will be able to determine $P$.



## DIGITAL SIGNATURES

What is it about a signature that is so compelling:

1. The signature is authentic. The signature convinces the document's recipient that the signer deliberately signed the document.
2. The signature is unforgeable. The signature is proof that the signer, and no one else, deliberately signed the document.
3. The signature is not reusable. The signature is part of the document; an unscrupulous person cannot move the signature to a different document.
4. The signed document is unalterable. After the document is signed, it can not be altered.
5. The signature cannot be repudiated. The signature and the document are physical things. The signer cannot later claim that he or she didn't sign it.

### Algorithms and Terminology

The signing process is called **encrypting with a private key**.

The verification process is called **decrypting with a public key**.

Signing a message with private key $K$ is $S_K(M)$.

Verifying a signature with the corresponding public key is $V_K(M)$.

The bit string attached to the document when signed will be called the **digital signature**, or just the **signature**.



## RANDOM AND PSEUDO-RANDOM-SEQUENCE GENERATION

### Pseudo-Random Sequences

A sequence generator is pseudo-random if it has this property:

1. It looks random. This means that it passes all the statistical tests of randomness that we can find.
2. It is unpredictable. It must be computationally infeasible to predict what the next random bit will be, given complete knowledge of the algorithm or hardware generating the sequence and all of the previous bits in the stream.
3. It cannot be reliably reproduced. If you run the sequence generator twice with the exact same input (at least as exact as humanly possible), you will get two completely unrelated random sequences.