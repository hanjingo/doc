# CHAPTER 4 Intermediate Protocols

[TOC]



## TIMESTAMPING SERVICES

### Aribitrated Solution

This protocol uses Trent, who has a trusted timestamping service, and Alice, who wishes to timestamp a document.

1. Alice transmits a copy of the document to Trent.
2. Trent records the date and time he received the document and retains a copy of the document for safekeeping.

### Improved Arbitrated Solution

One-way hash functions and digital signatures can clear up most of these problems easily:

1. Alice produces a one-way hash of the document.
2. Alice transmits the hash to Trent.
3. Trent appends the date and time he received the hash onto the hash and then digitally signs the result.
4. Trent sends the signed hash with timestamp back to Alice.

### Linking Protocol

If $A$ is Alice's name, the hash value that Alice wants timestamped is $H_n$, and the previous time stamp is $T_{n - 1}$, then the protocol is:

1. Alice sends Trent $H_n$ and $A$.

2. Trent sends back to Alice:
   $$
   T_n = S_k(n, A, H_n, t_n, I_{n - 1}, H_{n - 1}, T_{n - 1}, L_n)
   $$
   Where $L_n$ consists of the following hashed linking information:
   $$
   L_n = H(I_{n - 1}, H_{n - 1}, T_{n - 1}, L_{n - 1})
   $$
   $S_K$ indicates that the message is signed with Trent's private key. Alice's name identifies her as the originator of the request. The parameter $n$ indicates the sequence of the request: This is the $n$th timestamp Trent has issued. The parameter $t_n$ is the time. The additional information is the identification, original hash, time, and hashed timestamp of the previous document Trent stamped.

3. After Trent stamps the next document, he sends Alice the identification of the originator of that document:$I_{n + 1}$.

### Distributed Protocol

Along a similar line, the following protocol does away with Trent altogether.

1. Using $H_n$ as input, Alice generates a string of random values using a cryptographically secure pseudo-random-number generator:
   $$
   V_1, V_2, V_3, ... V_k
   $$

2. Alice interprets each of these values as the identification, $I$, of another person. She sends $H_n$ to each of these people.

3. Each of these people attaches the date and time to the hash, signs the result, and sends it back to Alice.

4. Alice collects and stores all the signatures as the timestamp.



## SUBLIMINAL CHANNEL

In general the protocol looks like this:

1. Alice generates an innocuous message, pretty much at random.
2. Using a secret key shared with Bob, Alice signs the innocuous message in such a way that she hides her subliminal message in the signature.
3. Alice sends this signed message to Bob via Walter.
4. Walter reads the innocuous message and checks the signature. Finding nothing amiss, he passes the signed message to Bob.
5. Bob checks the signature on the innocuous message, confirming that the message came from Alice.
6. Bob ignores the innocuous message and, using the secret key he shares with Alice, extracts the subliminal message.



## UNDENIABLE DIGITAL SIGNATURES

**Undeniable signatures** like a normal digital signature, an undeniable signature depends on the signed document and the signer's private key. But unlike normal digital signatures, an undeniable signature cannot be verified without the signer's consent.

The mathematics are complicated, but the basic idea is simple:

1. Alice presents Bob with a signature.
2. Bob generates a random number and sends it to Alice.
3. Alice does a calculation using the random number and her private key and sends Bob the result. Alice could only do this calculation if the signature is valid.
4. Bob confirms this.



## DESIGNATED CONFIRMER SIGNATURES

Designated confirmer signatures allows a signer to designate someone else to verify his signature.

Designated confirmer signatures are kind of a compromise between normal digital signatures and undeniable signatures.



## PROXY SIGNATURES

**Proxy signatures** is a solution, such that the following properties hold:

- **Distinguishability**. Proxy signatures are distinguishable from normal signatures by anyone.
- **Unforgeability**. Only the original signer and the designated proxy signer can create a valid proxy signature.
- **Proxy signer's deviation**. A proxy signer cannot create a valid proxy signature not detected as a proxy signature.
- **Verifiability**. From a proxy signature, a verifier can be convinced of the original signer's aggrement on the signed message.
- **Identifiability**. An original signer can determine the proxy signer's identity from a proxy signature.
- **Undeniability**. A proxy signer cannot disavow an accepted proxy signature he created.



## GROUP SIGNATURES

The solution to this problem is called a **group signature**. Group signatures have the following properties:

- Only members of the group can sign messages.
- The receiver of the signature can verify that it is a valid signature from the group.
- The receiver of the signature cannot determine which member of the group is the signer.
- In the case of a dispute, the signature can be "opened" to reveal the identity of the signer.



## BIT COMMITMENT

### Bit Commitment Using Symmetric Cryptography

This bit-commitment protocol uses symmetric cryptography:

1. Bob generates a random-bit string, $R$, and sends it to Alice.
   $$
   R
   $$

2. Alice creates a message consisting of the bit she wishes to commit to, $b$(it can actually be several bits), and Bob's random string. She encrypts it with some random key, $K$, and sends the result back to Bob.
   $$
   E_K(R, b)
   $$
   (That is the commitment portion of the protocol. Bob cannot decrypt the message, so he does not know what the bit is.)

   (When it comes time for Alice to reveal hermit, the protocol continues):

3. Alice sends Bob the key.

4. Bob decrypts the message to reveal the bit. He checks his random string to verify the bit's validity.

### Bit Commitment Using One-Way Functions

This protocol uses one-way functions:

1. Alice generates two random-bit strings, $R_1$ and $R_2$.
   $$
   R_1, R_2
   $$

2. Alice creates a message consisting of her random strings and the bit she wishes to commit to (it can actually be several bits).
   $$
   (R_1, R_2, b)
   $$

3. Alice computes the one-way function on the message and sends the result, as well as one of the random strings, to Bob.
   $$
   H(R_1, R_2, b), R_1
   $$
   (This transmission from Alice is evidence of commitment. Alice's one-way function in step 3 prevents Bob from inverting the function and determining the bit.)

   (When it comes time for Alice to reveal her bit, the protocol continues:)

4. Alice sends Bob the original message.
   $$
   (R_1, R_2, b)
   $$

5. Bob computes the one-way function on the message and compares it and $R_1$, with the value and random string he received in step 3. If they match, the bit is valid.

### Bit Commitment Using Pseudo-Random-Sequence Generators

This protocol is even easier:

1. Bob generates a random-bit string and sends it to Alice.
   $$
   R_B
   $$

2. Alice generates a random seed for a pseudo-random-bit generator. Then, for every bit in Bob's random-bit string, she sends Bob either:

   - the output of the generator if Bob's bit is 0, or
   - the XOR of output of the generator and her bit, if Bob's bit is 1.

   (When it comes time for Alice to reveal her bit, the protocol continues:)

3. Alice sends Bob her random seed.

4. Bob completes step 2 to confirm that Alice was acting fairly.

### Blobs

These strings that Alice sends to Bob to commit to a bit are sometimes called **blobs**. A blob is a sequence of bits, although there is no reason in the protocols why it has to be. Blobs have these four properties:

1. Alice can commit to blobs. By committing to a blob, she is committing to a bit.
2. Alice can open any blob she has committed to. When she opens a blob, she can convince Bob of the value of the bit she committed to when she committed to the blob. Thus, she cannot choose to open any blob as either a zero or a one.
3. Bob cannot learn how Alice is able to open any unopened blob she has committed to. This is true even after Alice has opened other blobs.
4. Blobs do not carry any information other than the bit Alice committed to. The blobs themselves, as well as the process by which Alice commits to and opens them, are uncorrelated to anything else that Alice might wish to keep secret from Bob.