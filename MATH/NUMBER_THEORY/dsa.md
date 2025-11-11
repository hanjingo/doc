
# Digital Signature Algorithm (DSA) — Practical Overview

This document summarizes the Digital Signature Algorithm (DSA): its mathematical basis, parameter and key generation, signing and verification procedures, known pitfalls (especially nonce reuse), recommended parameter sizes, and implementation guidance. The intent is a compact, practical reference for engineers who must implement, audit, or migrate systems that use DSA.

## What DSA is

DSA is a public-key signature algorithm standardized in FIPS 186. It produces a signature for a message using a private key; anyone with the corresponding public key can verify the signature. DSA relies on discrete-logarithm hardness in a cyclic group (classically Z_p^*). Elliptic-curve variants (ECDSA) follow the same high-level pattern but operate over elliptic-curve groups.

## Parameters and key generation (classic DSA)

Classic DSA uses three domain parameters:

- p: a large prime modulus (e.g., 2048 bits)
- q: a prime divisor of p - 1 (typically 160–256 bits depending on p)
- g: generator of a subgroup of order q in Z_p^*

Key generation:

1. Choose domain parameters (p, q, g) as specified by standards (FIPS profiles) or take well-known parameters.
2. Select private key x uniformly from [1, q - 1].
3. Compute public key y = g^x mod p.

Protect x (private key) as sensitive material; publish (p, q, g, y) as the public key set.

## Signing and verification (conceptual)

Signing a message M (conceptual):

1. Compute digest H = Hash(M) using an approved hash (e.g., SHA-256). If q is smaller than hash output, reduce H modulo q per the standard.
2. Select a fresh per-signature nonce k uniformly from [1, q - 1].
3. Compute r = (g^k mod p) mod q. If r = 0, choose a new k.
4. Compute s = k^{-1} (H + x * r) mod q. If s = 0, choose a new k.
5. Signature is the pair (r, s).

Verification given (r, s) and message M:

1. Check 0 < r, s < q; otherwise reject.
2. Compute H = Hash(M) and w = s^{-1} mod q.
3. Compute u1 = (H * w) mod q and u2 = (r * w) mod q.
4. Compute v = ((g^{u1} * y^{u2} mod p) mod q).
5. Accept if v == r, else reject.

Note: all modular inverses, exponentiations, and multiplications must be implemented correctly and checked for edge cases.

## Critical security considerations

- Nonce reuse (k): reusing k across two signatures with the same private key leaks x and enables full key recovery. Similarly, poor randomness or partial leakage of k is catastrophic. Always use a fresh unpredictable nonce per signature.
- Deterministic k (RFC 6979): to avoid entropy failures, consider deterministic nonce generation per RFC 6979 — derive k deterministically from the private key and message hash using HMAC-DRBG. This eliminates dependence on external RNGs while preserving per-message uniqueness.
- Hash size and q: when the hash output length exceeds q, truncate or reduce the hash to the bit-length of q per the standard. Use appropriate hash functions for the chosen q size (e.g., SHA-256+q=256-bit).
- Side-channels: signing involves secret-dependent operations (modular exponentiations and multiplications). Use constant-time implementations and blinding techniques to mitigate timing and power analysis attacks.

## Parameter sizes and recommendations

- Use FIPS-approved parameter sizes. Historically (examples):
	- p ≈ 2048 bits and q ≈ 224 or 256 bits (modern minimums)
	- For long-term security or higher assurance, use larger p (3072 bits) and q = 256 bits.
- Consider migrating to ECDSA or EdDSA (Ed25519) for better performance and smaller keys/signatures, unless policy requires DSA.

## Implementation pitfalls and hardening

- Randomness: use a cryptographically secure RNG for k if not using RFC 6979. Validate RNG outputs and include entropy health checks where possible.
- Deterministic k: RFC 6979 is strongly recommended when RNG reliability is a concern; many libraries support it.
- Input validation: check that r and s are in the correct range and that public keys y satisfy 1 < y < p - 1 (and optional subgroup checks) before verification.
- Fault injection and side-channels: apply constant-time arithmetic and, where possible, use hardware protections or library-level mitigations (blinding, detection of faults, and re-computation/verification of results).
- Reuse of keys across algorithms: avoid using the same DSA key for multiple algorithms or protocols unless explicitly allowed and standardized.

## Comparison to other signature schemes

- ECDSA: elliptic-curve analogue of DSA — smaller keys and signatures for similar security; beware of implementation pitfalls and use constant-time curve operations.
- EdDSA (Ed25519): modern signature scheme with deterministic signing, simpler API, and better resistance to implementation mistakes; recommended for new designs where elliptic curves are appropriate.

## Interoperability and migration

- If you must interoperate with legacy systems requiring DSA, follow standard parameter profiles and be strict about validation and nonce usage.
- For new systems prefer Ed25519/Ed448 or ECDSA with modern curves, using secure library implementations and RFC-specified parameter handling.

## References and standards

- FIPS 186-4: Digital Signature Standard (DSA, RSA, ECDSA)
- RFC 6979: Deterministic generation of DSA/ECDSA nonces using HMAC-DRBG
- Academic literature on nonce reuse attacks and side-channel attacks against signature schemes