# MD5 — Message-Digest Algorithm 5 (summary and implementation notes)

This document summarizes MD5: its design, high-level algorithm, common implementation notes, known weaknesses, typical historical uses, and recommended replacements. The goal is a practical, concise reference for engineers maintaining or documenting systems that still encounter MD5.

## Quick facts

- Designer: Ronald Rivest (1991)
- Output: 128-bit digest
- Input: arbitrary-length message (processed in 512-bit blocks)
- Internal state: four 32-bit words (A, B, C, D)
- Construction: Merkle–Damgård iterated hash with an MD-style compression function
- Status: broken for collision resistance and unsuitable for cryptographic uses

## Historical context and use

MD5 was designed as an update to earlier MD-family hashes (MD2/MD4). For many years MD5 was widely used for checksums, file integrity, and non-cryptographic identifiers. Over time, cryptanalytic advances discovered practical collision attacks (around 2004–2005) and later chosen-prefix collisions and other practical abuses. Today MD5 is considered cryptographically broken and must not be used for security-sensitive tasks such as digital signatures, TLS certificates, password hashing, or any purpose requiring collision resistance.

That said, MD5 may still appear in legacy protocols, existing file checksums, or non-adversarial integrity checks where collision resistance is not required; even then, prefer modern hashes where possible.

## High-level algorithm

MD5 processes the message in 512-bit (64-byte) blocks. The algorithm follows the Merkle–Damgård paradigm:

1. Append padding: a single 1-bit, enough 0-bits to reach 64 bits shy of a 512-bit block, then append the original message length as a 64-bit little-endian integer.
2. Initialize the 128-bit state (A, B, C, D) to fixed constants.
3. For each 512-bit block, run the MD5 compression function which performs 64 operations organized into four rounds (16 operations each). Each operation uses one of four nonlinear functions (F, G, H, I), adds a 32-bit word from the block, adds a fixed constant, rotates left by a specified amount, and accumulates into the state.
4. After processing all blocks, the final digest is the concatenation of A, B, C, D (little-endian) producing a 128-bit output.

## Round functions and operations (conceptual)

MD5 uses four nonlinear functions (32-bit word operations):

- F(X,Y,Z) = (X & Y) | (~X & Z)
- G(X,Y,Z) = (X & Z) | (Y & ~Z)
- H(X,Y,Z) = X ^ Y ^ Z
- I(X,Y,Z) = Y ^ (X | ~Z)

Each of the 64 steps uses one of these functions (16 steps per function), a 32-bit subword from the current 512-bit message block (a specific ordering), and a fixed additive constant derived from the sine function. After combining these with the current state words, the result is rotated left by an amount that depends on the step number and added into one of the state words.

The precise step order, rotation amounts, and constants are part of the MD5 specification; implementers should copy these tables from an authoritative source or use a vetted library.

## Padding and length encoding

Padding is always appended, even for messages whose length is already a multiple of the block size. The padding ensures the final message length (in bits) is congruent to 448 mod 512 before appending the 64-bit length. MD5 uses little-endian encoding for the length field.

Important: when implementing or verifying MD5 compatibility with other implementations, confirm the byte-order (endianness) assumptions for both message words and length encoding.

## Common test vectors

- MD5("") = d41d8cd98f00b204e9800998ecf8427e
- MD5("a") = 0cc175b9c0f1b6a831c399e269772661
- MD5("abc") = 900150983cd24fb0d6963f7d28e17f72
- MD5("message digest") = f96b697d7cb7938d525a2f31aaf161d0

Use these to validate implementations.

## Security weaknesses and attacks

- Collision attacks: practical collision-finding attacks were demonstrated in the mid-2000s. Attackers can find two different messages with the same MD5 digest without exhaustive search.
- Chosen-prefix collisions: more advanced techniques allow attackers to create collisions for chosen prefixes (useful in real-world attacks against certificate issuance and other protocols where attackers control parts of the input).
- Length-extension attacks: MD5 is vulnerable to length-extension attacks because it uses a Merkle–Damgård construction — given MD5(m) and len(m), an attacker can compute MD5(m || padding || m2) for attacker-chosen m2 without knowing m. This makes naive HMAC-like uses insecure; use HMAC (which mitigates length extension) or prefer modern hash constructions.
- Preimage resistance: MD5 still has higher difficulty for preimage attacks than collisions, but preimage safety is not sufficient for cryptographic use given the collision vulnerabilities and the availability of other secure hashes.

Because of collision and chosen-prefix attack feasibility, MD5 must not be used for signatures, certificates, code signing, or other authentication/integrity where adversaries may attempt to craft collisions.

## Practical guidance and migration

- Replacement: use SHA-256 or SHA-2 family for general-purpose hashing; for performance-sensitive use, consider BLAKE2 or BLAKE3; for modern security and standardized use, prefer SHA-3 family where appropriate.
- HMAC: if you need a keyed MAC and are currently using MD5-based HMAC (HMAC-MD5), migrate to HMAC-SHA256 or HMAC-SHA-512.
- Backward compatibility: when interacting with legacy systems that require MD5 (e.g., legacy file formats or protocols), isolate that usage and plan migration. Do not accept MD5-based signatures or certificates.
- Non-adversarial checksums: MD5 is still sometimes used for accidental corruption detection in non-adversarial contexts (e.g., quick file checksums), but safer non-cryptographic checksums (CRC32) or stronger content hashes are preferable.

## Implementation notes and pitfalls

- Use a trusted, well-reviewed cryptographic library rather than rolling your own MD5 implementation.
- Beware of byte-order and encoding differences between languages and libraries when verifying test vectors.
- Avoid using MD5 for password hashing — instead use slow, memory-hard functions such as Argon2id, scrypt, bcrypt, or PBKDF2 with a sufficiently large iteration count.

## Appendix: minimal pseudocode for padding (conceptual)

Given message M (bytes):

1. bit_len = len(M) * 8
2. append 0x80 (one bit 1 followed by seven 0 bits)
3. append zero bytes until (len(M) mod 64) == 56
4. append bit_len as 8-byte little-endian integer

Then process the resulting message in 64-byte blocks with the compression function.

## References and further reading

- RFC 1321 — The MD5 Message-Digest Algorithm (original specification)
- Research papers and public analyses describing collision attacks (Wang et al., chosen-prefix follow-ups)
- NIST and modern guidance recommending migration to stronger hashes