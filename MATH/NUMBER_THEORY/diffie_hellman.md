
# Diffie–Hellman Key Exchange — Practical Guide

This document summarizes the Diffie–Hellman key exchange family: the mathematics, finite-field (classical) DH, elliptic-curve DH (ECDH and X25519/X448), authenticated uses, parameter validation, common attacks, implementation pitfalls, and practical recommendations for engineers building secure key agreement protocols.

Goal: provide a compact, actionable reference — explain what to check in implementations, how to choose parameters, and how to combine DH with KDFs and AEAD to build secure channels.

## High-level idea

Diffie–Hellman (DH) allows two parties to derive a shared secret over an insecure channel without prior shared secrets. At a high level:

1. Both parties agree on public domain parameters (a group G and generator g).
2. Each party picks a private exponent (a, b) and computes the public value (g^a, g^b).
3. They exchange public values and compute the shared secret as (g^b)^a = (g^a)^b = g^{ab}.

The shared secret is then converted into symmetric keys via a key-derivation function (KDF) and used with authenticated encryption.

## Variants

- Finite-field DH (modular exponentiation): Group G = Z_p^* with large prime p (often a safe prime) and generator g. Security relies on the hardness of discrete logarithm modulo p.
- Elliptic-curve DH (ECDH): uses point multiplication on an elliptic curve; security relies on the elliptic-curve discrete logarithm problem (ECDLP). Curves include NIST P-256/P-384, brainpool, and modern curves like Curve25519 (X25519) and Curve448 (X448).
- Diffie–Hellman over other groups (pairing-friendly or post-quantum KEMs) exist — use only well-studied groups and standardized KEMs.

Modern guidance strongly prefers elliptic-curve Diffie–Hellman with vetted curves (X25519/X448 or NIST curves where policy requires them) because of smaller keys and better performance.

## Key derivation and usage (KEM/DEM, HKDF)

DH produces a raw shared value (group element). Do not use it directly. Use a KDF to derive symmetric keys and associated nonces. Typical pattern:

1. Perform authenticated DH exchange to obtain raw shared_secret.
2. Compute key_material = KDF(shared_secret || transcript || context)
3. Split key_material into K_enc, K_mac (if needed), and base nonce or IV.
4. Use AEAD (e.g., AES-GCM or ChaCha20-Poly1305) with derived keys and nonces.

Use HKDF (RFC 5869) with a strong hash (SHA-256/512) for KDF operations, and include protocol transcript or context (identities, nonces) in the KDF info to bind keys to the session.

## Authentication and MitM protection

Raw DH is unauthenticated and vulnerable to man-in-the-middle (MitM) attacks. Always authenticate the key exchange using one of:

- Public-key signatures (e.g., signing ephemeral DH parameters with long-term private keys).
- Static public keys verified by certificates (e.g., authenticated ECDHE in TLS where ephemeral keys are authenticated by server certificate signatures).
- Pre-shared keys (PSK) or out-of-band key confirmation.
- Authenticated KEMs / key-encapsulation mechanisms that include recipient authentication.

Prefer ephemeral (ephemeral-static or ephemeral-ephemeral) DH with authentication to get forward secrecy and authentication.

## Parameter selection and validation

Finite-field DH (FFDHE):

- Use standardized, well‑known safe groups (RFC 7919 provides FFDHE groups like 2048-, 3072-, 4096-bit primes). Avoid ad-hoc primes.
- Prefer at least 2048-bit groups for short-term security; 3072-bit for longer-term security. Follow current guidance from standards bodies for required sizes.

Elliptic-curve DH (ECDH):

- Prefer X25519 (Curve25519) and X448 (Curve448) for new designs: they offer simple APIs, constant-time behavior, and are easy to implement correctly.
- When using prime-order curves like P-256/P-384, validate public keys and consider cofactor handling.

Validation checks (critical):

- Verify that received group elements are in the intended subgroup (prevent small-subgroup attacks).
- For finite-field DH: check 1 < g^x < p-1 and optionally check (g^x)^q != 1 when p = 2q+1 (safe prime) to ensure subgroup correctness.
- For ECDH: validate that the public point is on the curve and not the point at infinity. For curves with cofactor != 1, apply cofactor-multiplication or reject points as appropriate.
- Reject low or trivial public values (1, 0, p-1, point-at-infinity) and check for malformed encodings.

Do not skip public-key validation even when using high-level libraries — understand if the library performs validation and which checks it does.

## Common attacks and mitigations

- Man-in-the-middle: Mitigation — authenticate the key exchange (certificates, signatures, PSKs).
- Small-subgroup and invalid-curve attacks: Mitigation — validate public keys, use safe primes or cofactor-handling, and check subgroup membership.
- Replay and reflection attacks: Mitigation — include nonces, session identifiers, and transcript binding in KDF; require freshness through nonces/timestamps or sequence numbers.
- Side-channel attacks (timing, power): Mitigation — constant-time scalar multiplication, blinding, and side-channel resistant implementations.
- Logjam (downgrades to weak DH groups): Mitigation — disallow legacy small groups (e.g., < 1024-bit) and enforce minimum group sizes; use secure negotiation protocols (TLS 1.3 avoids many downgrade problems).
- Precomputation attacks on static keys: Mitigation — use ephemeral keys for forward secrecy or protect static private keys with HSMs.

## Ephemeral vs static keys, forward secrecy

- Ephemeral DH: parties generate ephemeral keys per session; provides forward secrecy.
- Static DH: one or both parties reuse the same key long-term; no forward secrecy for sessions protected only by static keys.

Best practice: use ephemeral keys (e.g., ECDHE) authenticated by long-term credentials (certificates or signatures). This gives both authentication and forward secrecy.

## Implementation best practices

- Use well-reviewed cryptographic libraries (libsodium, BoringSSL/OpenSSL, NSS, etc.) instead of writing raw DH/ECDH code.
- Prefer high-level APIs (e.g., X25519 APIs) that return shared secrets in fixed-size encodings and perform required checks.
- Always derive keys with HKDF and bind protocol context (transcript, identities) into the derivation.
- Use AEAD for payload encryption and bind AEAD associated data to the session metadata.
- Enforce minimal key and group sizes in configuration and reject deprecated groups.
- Protect private keys at rest using HSMs or secure key stores; use hardware acceleration when available for performance and side-channel resistance.

## Example pseudocode (modular DH and X25519)

Modular DH (conceptual):

1. Domain parameters: prime p, generator g.
2. Alice: a = random(1..p-2); A = powmod(g, a, p)
3. Bob: b = random(1..p-2); B = powmod(g, b, p)
4. Exchange A and B.
5. Alice computes s = powmod(B, a, p); Bob computes s = powmod(A, b, p).
6. shared_secret = KDF(s || A || B || context)

X25519 (conceptual / recommended for EC):

1. Alice: a = random_scalar(); A = X25519_basepoint(a)
2. Bob: b = random_scalar(); B = X25519_basepoint(b)
3. Exchange A and B (32-byte public values)
4. Alice computes s = X25519(a, B); Bob computes s = X25519(b, A)
5. shared_secret = HKDF(s, salt, info)

Notes: X25519 performs required clamping of private scalars and works with simple fixed-length encodings; it avoids many common pitfalls of general ECDH.

## Recommended parameters (brief)

- X25519/X448: recommended for most new applications requiring ECDH.
- NIST P-256/P-384: widely supported; acceptable when policy requires them and implementations validate points.
- FFDHE groups: use at least 2048-bit (RFC 7919 ffdhe2048) as a minimal practical choice; use 3072-bit for longer-term protection.

Follow current standards and organizational policy (NIST, IETF) for precise sizing and transition timelines.

## TLS and protocol examples

- TLS 1.3 uses ephemeral (EC)DH with authenticated key exchange and AEAD ciphers by default — prefer TLS 1.3 for transport security rather than building a custom key exchange.
- In other protocols, follow patterns used in Noise, Signal, and modern KEM designs: ephemeral ECDH, HKDF-based key schedule, AEAD for transport.

## References and further reading

- RFC 7919 (FFDHE), RFC 7748 (Curve25519 and Curve448), RFC 5903/4492 (ECDH in TLS context), RFC 8446 (TLS 1.3), RFC 5869 (HKDF)
- Academic literature on discrete-log and ECDLP hardness, small-subgroup and invalid-curve attacks, and side-channel resistance.
