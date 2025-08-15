# CBC

[TOC]



`Cipher Block Chaining (CBC)`. random value along with the very first message, and then have the sender and receiver use the computed coded blocks in place of the subsequent random number. Specifically, CBC operates as follows:

1. Before encrypting the message (or the stream of data), the sender generates a random $k$-bit string, called the `Initialization Vector (IV)`. Denote this initialization vector by $c(0)$. The sender sends the IV to the receiver in `cleartext`.
2. For the first block, the sender calculates $m(1) \oplus c(0)$, that is, calculates the exclusive-or of the first block of cleartext with the IV. It then runs the result through the block-cipher algorithm to get the corresponding ciphertext block; that is, $c(1) = K_S(m(1) \oplus c(0))$. The sender sends the encrypted block $c(1)$ to the receiver.
3. For the $i$th block, the sender generates the ith ciphertext block from $c(i) = K_S(m(i) \oplus c(i - 1))$.



## Reference

[1] James F. Kurose, Keith W. Ross . Computer Networking: A Top-Down Approach . 6ED