# Cipher Modes and Stream Modes — Overview and Best Practices

This note summarizes the common block-cipher modes and stream-cipher modes used in practical cryptography. It explains how each mode works, initialization and padding requirements, error propagation characteristics, typical use cases, and security considerations. The intent is to provide a concise reference for engineers choosing modes for encryption systems.

## Quick overview

- ECB (Electronic Codebook): encrypts each block independently — not semantically secure for multi-block messages.
- CBC (Cipher Block Chaining): classic mode that hides block patterns using an IV; requires padding.
- PCBC (Propagating CBC): variant that propagates changes; largely historical and rarely used.
- CFB (Cipher Feedback): turns a block cipher into a stream-like mode; supports partial-block encryption.
- OFB (Output Feedback): produces a synchronous keystream from a block cipher; no error extension.
- CTR (Counter): converts a block cipher into a stream cipher using a counter; supports parallelism and random access.
- Stream ciphers: true keystream generators (e.g., ChaCha20); efficient for streaming data.
- Self-synchronizing stream ciphers: keystream depends on previous ciphertext bits and auto-resynchronize.

When possible, prefer authenticated encryption (AEAD) modes such as AES-GCM or ChaCha20-Poly1305, which provide confidentiality and integrity in a single primitive.

## ECB

ECB encrypts each block independently:

- Encryption: C_i = E_K(P_i)
- Decryption: P_i = D_K(C_i)

Problems and considerations:

- Identical plaintext blocks produce identical ciphertext blocks — leaks structure and enables pattern analysis or block-replay attacks.
- No integrity protection: easy to rearrange or substitute ciphertext blocks.

Use cases: encrypting a single block of data (e.g., an individual key) where no repetition of blocks occurs. Avoid ECB for multi-block plaintexts.

## CBC

CBC hides repeated blocks by XORing each plaintext block with the previous ciphertext block before encryption:

- Encryption: C_i = E_K(P_i ⊕ C_{i-1}), with C_0 = IV
- Decryption: P_i = D_K(C_i) ⊕ C_{i-1}

Notes:

- IV requirements: IV should be unpredictable or unique per message. Random IVs are typical; non-repeating nonces may suffice in some protocols.
- Padding: required for non-block-aligned messages (PKCS#7, ISO/IEC 7816-4, or ciphertext stealing to avoid padding length expansion).
- Error propagation: a single-bit error in C_i corrupts whole P_i and flips corresponding bits in P_{i+1}; CBC is self-recovering after two blocks.
- Integrity: CBC does not provide authentication; use Encrypt-then-MAC (recommended) or an AEAD construction.

CBC is still used for file and disk encryption when combined with authentication.

## CFB

CFB turns a block cipher into a stream cipher and can operate on sub-block sizes (e.g., 8-bit CFB):

# Cipher Modes and Stream Modes — Overview and Best Practices

This note summarizes the common block-cipher modes and stream-cipher modes used in practical cryptography. It explains how each mode works, initialization and padding requirements, error propagation characteristics, typical use cases, and security considerations. The intent is to provide a concise reference for engineers choosing modes for encryption systems.

## Quick overview

- ECB (Electronic Codebook): encrypts each block independently — not semantically secure for multi-block messages.
- CBC (Cipher Block Chaining): classic mode that hides block patterns using an IV; requires padding.
- PCBC (Propagating CBC): variant that propagates changes; largely historical and rarely used.
- CFB (Cipher Feedback): turns a block cipher into a stream-like mode; supports partial-block encryption.
- OFB (Output Feedback): produces a synchronous keystream from a block cipher; no error extension.
- CTR (Counter): converts a block cipher into a stream cipher using a counter; supports parallelism and random access.
- Stream ciphers: true keystream generators (e.g., ChaCha20); efficient for streaming data.
- Self-synchronizing stream ciphers: keystream depends on previous ciphertext bits and auto-resynchronize.

When possible, prefer authenticated encryption (AEAD) modes such as AES-GCM or ChaCha20-Poly1305, which provide confidentiality and integrity in a single primitive.

## Electronic Codebook (ECB)

ECB encrypts each block independently:

- Encryption: C_i = E_K(P_i)
- Decryption: P_i = D_K(C_i)

Problems and considerations:

- Identical plaintext blocks produce identical ciphertext blocks — leaks structure and enables pattern analysis or block-replay attacks.
- No integrity protection: easy to rearrange or substitute ciphertext blocks.

Use cases: encrypting a single block of data (e.g., an individual key) where no repetition of blocks occurs. Avoid ECB for multi-block plaintexts.

## Cipher Block Chaining (CBC)

CBC hides repeated blocks by XORing each plaintext block with the previous ciphertext block before encryption:

- Encryption: C_i = E_K(P_i ⊕ C_{i-1}), with C_0 = IV
- Decryption: P_i = D_K(C_i) ⊕ C_{i-1}

Notes:

- IV requirements: IV should be unpredictable or unique per message. Random IVs are typical; non-repeating nonces may suffice in some protocols.
- Padding: required for non-block-aligned messages (PKCS#7, ISO/IEC 7816-4, or ciphertext stealing to avoid padding length expansion).
- Error propagation: a single-bit error in C_i corrupts whole P_i and flips corresponding bits in P_{i+1}; CBC is self-recovering after two blocks.
- Integrity: CBC does not provide authentication; use Encrypt-then-MAC (recommended) or an AEAD construction.

CBC is still used for file and disk encryption when combined with authentication.

## Propagating CBC (PCBC)

PCBC modifies CBC so both plaintext and ciphertext differences feed back into the next block:

- Encryption: C_i = E_K(P_i ⊕ C_{i-1} ⊕ P_{i-1})

PCBC causes any bit change to propagate through subsequent blocks, which was intended to amplify tampering effects. However, it has weaker security properties in practice and is now considered historical; avoid using PCBC in new designs.

## Cipher Feedback (CFB)

CFB turns a block cipher into a stream cipher and can operate on sub-block sizes (e.g., 8-bit CFB):

- Encryption (r-bit CFB): C_i = P_i ⊕ MSB_r(E_K(C_{i-1})), with C_0 = IV
- Decryption: P_i = C_i ⊕ MSB_r(E_K(C_{i-1}))

Notes:

- IV must be unique; it need not be secret.
- Self-synchronizing: the receiver will resynchronize automatically after receiving enough ciphertext (bounded by the feedback register size).
- Error propagation: a ciphertext error affects the corresponding plaintext and a bounded number of following plaintext bits until the corrupted bits shift out of the register.

CFB is useful when you need to encrypt data in small units without a dedicated stream cipher, but like CBC it provides no integrity guarantees by itself.

## Output Feedback (OFB)

OFB produces a keystream independent of plaintext or ciphertext:

- S_0 = IV; S_i = E_K(S_{i-1}); C_i = P_i ⊕ MSB_r(S_i)

Notes:

- IV must be unique (never reuse IV/nonce with the same key), otherwise keystream reuse leaks plaintext via XOR.
- No error extension: a bit error in ciphertext yields a single-bit error in decrypted plaintext.
- Synchronization loss (dropped or inserted bits) is fatal — both sides must agree on keystream position.
- OFB with feedback size smaller than block size has security caveats; prefer full-block OFB or CTR.

OFB is chosen when a synchronous keystream with minimal error propagation is required, but always pair with a MAC or use AEAD for integrity.

## Counter (CTR) mode

CTR uses a nonce and a counter to generate a keystream:

- S_i = E_K(Nonce || Counter_i)
- C_i = P_i ⊕ S_i

Notes:

- Nonce/IV rules: the (Nonce, Counter) input must never repeat for the same key; nonce reuse with CTR completely breaks confidentiality.
- Supports random access and parallel encryption/decryption (blocks independent).
- No error extension: single-bit errors only affect corresponding plaintext bits.
- Highly efficient and widely used in modern systems.

CTR is often preferred for performance and random-access use cases but must be combined with authentication (use AEAD where available).

## Stream ciphers

Stream ciphers generate a keystream K = k_1, k_2, ... and encrypt as C_i = P_i ⊕ k_i.

Two main categories:

- Synchronous stream ciphers: keystream depends only on key and internal state; both ends must remain synchronized. Loss of data or skipped bytes requires explicit resynchronization.
- Self-synchronizing stream ciphers (ciphertext autokey): keystream depends on a fixed number of previous ciphertext bits and re-synchronizes automatically after receiving enough ciphertext.

Examples and notes:

- RC4: historical, avoid for new systems due to biases and vulnerabilities.
- ChaCha20: modern, fast, and used with Poly1305 for AEAD (ChaCha20-Poly1305).

Strict nonce/keystream management is critical: never reuse the same keystream (nonce+key) twice.

## Self-synchronizing stream ciphers

Self-synchronizing (also called ciphertext-autokey) stream ciphers derive the keystream from a fixed number n of previous ciphertext bits. This property allows automatic resynchronization after loss or reordering of data up to n bits, which can be useful on unreliable channels.

Key points:

- Resynchronization: the receiver recovers correct keystream state after receiving n correct ciphertext bits.
- Error propagation: a single-bit error affects the next n plaintext bits while the corrupted bits remain in the feedback window.
- Use cases: low-bandwidth or noisy channels where automatic recovery is preferable to explicit resynchronization.

Examples are mostly academic or historical; modern designs favor synchronous stream ciphers with authenticated transport layers.

## Other modes and historical variants (BC, PCBC, CBCC, OFBNLF)

Several less-common or historical modes appear in literature or legacy systems. Many have fallen out of favor due to subtle security or implementation pitfalls.

- PCBC (Propagating CBC): discussed earlier — amplifies changes but has weaker security in practice.
- BC / CBCC / OFBNLF and other acronymed variants: often represent protocol-specific tweaks or early-mode experiments; they are generally not standardized and should be avoided unless maintaining or documenting legacy systems.

Recommendation: avoid obscure or custom modes. Prefer standardized, well-vetted modes and AEAD constructions.

## Padding and ciphertext stealing

When plaintext length is not a multiple of the block size, the final partial block can be handled by:

- Padding (PKCS#7, ISO/IEC 7816-4, or zero-padding when length is known separately). Choose a padding scheme that is unambiguous and resistant to padding oracle attacks.
- Ciphertext stealing (CTS): avoids padding size expansion by encrypting the last two blocks in a way that preserves plaintext length while ensuring every plaintext bit is processed by the block cipher.

If using padding, validate and remove padding in a constant-time manner to avoid oracle leaks.

## Integrity: always authenticate ciphertext

Classical confidentiality-only modes do not provide integrity. Use one of the following patterns:

- Encrypt-then-MAC (recommended): compute a MAC over ciphertext and associated data; verify the MAC before decrypting.
- Authenticated encryption (AEAD): use AES-GCM, AES-CCM, or ChaCha20-Poly1305 to provide confidentiality and integrity in a single primitive.

Never rely on unauthenticated encryption in adversarial environments.

## Practical recommendations

1. Prefer AEAD modes (AES-GCM, ChaCha20-Poly1305) for new designs.
2. If using CBC/CFB/CTR/OFB, pair encryption with a strong MAC (HMAC-SHA256 or better) using Encrypt-then-MAC.
3. Never reuse IVs/nonces for CTR/OFB/CFB/any stream-mode under the same key.
4. Use random IVs for CBC; include the IV with ciphertext so the recipient can decrypt.
5. Avoid ECB for multi-block messages.
6. Prefer CTR for parallelism and random access; prefer CBC for simple sequential encryption when authentication is also enforced.

## Short reference table

| Mode | Keystream / Block | IV/Nonce requirement | Error propagation | Random access | Integrity |
|------|--------------------|----------------------|-------------------|---------------|-----------|
| ECB | Block cipher output | none | no propagation | no | no |
| CBC | Block cipher feedback | random IV | 2-block effect | no | no (use MAC) |
| PCBC | block+plaintext feedback | random IV | full propagation | no | no |
| CFB | block cipher -> stream | unique IV | limited (register length) | no | no |
| OFB | keystream from cipher | unique IV/nonce | none | no | no |
| CTR | keystream from counter | unique nonce | none | yes | no (use AEAD) |
| Stream | keystream generator | initial state / nonce | depends | depends | no |

## Final notes

Modes are tools; choose them according to application constraints (streaming vs file, random access needs, performance, parallelism) and always protect integrity. When in doubt, use an authenticated encryption primitive and a vetted crypto library.
