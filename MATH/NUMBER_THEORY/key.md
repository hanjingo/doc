
# Keys — Length, Generation, Management, and Best Practices

[TOC]

This note summarizes practical and theoretical guidance on cryptographic keys: how long they should be, how to generate them securely, how to store and distribute them, and best practices for lifetime, rotation, and verification. It consolidates material from Bruce Schneier's "Applied Cryptography" (chapters on Key Length and Key Management) and expands it with modern recommendations (key derivation functions, hardware security, and common standards).

## Key length: security and comparison

Choice of key length is the single most important parameter for resisting brute-force attacks. Key length recommendations depend on algorithm type:

- Symmetric keys (block/stream ciphers): use at least 128 bits for long-term security (AES-128). For higher margin and future-proofing, AES-256 is recommended.
- Public-key (asymmetric) keys: security is measured differently; recommended minimums (2020s guidance):
	- RSA: 2048 bits minimum; 3072 bits recommended if you need >2030 security.
	- Diffie–Hellman (MODP): choose modulus sizes comparable to RSA recommendations.
	- Elliptic Curve Cryptography (ECC): curves with ~256-bit field size (e.g., P-256, secp256r1) provide roughly 128-bit symmetric-equivalent security; P-384 provides ~192-bit security.
- Hash output sizes (one-way functions): use at least 256-bit output (SHA-256 family) to avoid practical collision attacks; SHA-3 and SHA-2 with 256/384/512 outputs are common.

Design systems so the easiest attack vector is equally hard across components. For systems that mix symmetric and asymmetric cryptography, avoid mismatched strengths (e.g., don't protect data with AES-128 while using a 1024-bit RSA key to distribute keys).

### Birthday attacks and hash collisions

Collision resistance degrades with the birthday paradox: for an n-bit hash, collisions can be found in about 2^(n/2) work. That is why 128-bit hash outputs are no longer considered collision-safe; 256 bits or more is the practical baseline for collision resistance.

## Key generation and entropy

Security of a cryptosystem depends entirely on the secrecy and quality of keys. Key generation requirements:

- Use a cryptographically secure random number generator (CSPRNG) seeded with sufficient true entropy (hardware RNG, OS-provided entropy pools). Avoid ad-hoc or predictable sources (timestamps, low-entropy passphrases alone).
- For devices with limited entropy (embedded systems, headless servers), use an external entropy source or hardware random number generator (TRNG) and accumulate entropy before key generation.
- Do not derive long-term keys directly from passwords; use a strong key derivation function (KDF) instead.

### Passphrases and key derivation

Human-memorable passphrases have low entropy. To convert passwords/passphrases into cryptographic keys, use a memory- and CPU-hard KDF with parameters tuned to the threat model:

- PBKDF2 (HMAC‑based) — widely available, parameterized by iteration count.
- bcrypt — resists GPU-based brute force better than simple PBKDF2, but has limits.
- scrypt — adds memory hardness to slow specialized hardware attacks.
- Argon2 (Argon2id) — the modern recommendation (winner of the Password Hashing Competition); tune memory and time parameters for your platform.

Always use a per-password unique salt (random, non-secret) stored alongside the derived key material metadata.

### Standards-based generation

Use well-established standards when possible (e.g., ANSI X9.17 / X9.31 for key-generation in legacy systems). Modern practice favors standardized primitives (AES, HMAC, HKDF, NIST SP 800‑90A/B/C RNG constructions) and protocols for entropy and deterministic key derivation.

## Key types and roles

Define and separate key roles clearly:

- Master keys / Root keys: highest-privilege keys used to encrypt other keys or sign certificates. These must be protected with the highest security measures (HSMs, offline storage).
- Key-encryption keys (KEKs) / wrapping keys: used solely to encrypt (wrap) other keys for transport or storage.
- Data keys (session keys): used to encrypt message traffic or payloads; often short-lived and rotated frequently.
- Authentication keys / MAC keys: used for message authentication (HMAC, CMAC).
- Signing keys: asymmetric keys used for digital signatures.

Separate these roles in policy and implementation (different key identifiers, access controls, and usage flags).

## Key management lifecycle

Key management is a lifecycle process. Main phases:

1. Generation — produce high-entropy keys using CSPRNG or KDFs.
2. Distribution — deliver keys securely to authorized parties (see Section 5).
3. Storage — store keys securely at rest (encrypted on disk, in HSMs, or protected by OS key stores).
4. Use — enforce key usage policies and cryptographic usage controls (e.g., separate keys for encryption vs signing).
5. Rotation/Update — periodically replace keys before expiry or after suspected compromise.
6. Revocation — make keys unusable and propagate revocation information (CRLs, OCSP, key revocation lists).
7. Destruction — securely erase keys when they are retired.

Each phase must be governed by policy: who can generate keys, which key types are allowed, lifetime limits, and acceptable cryptographic primitives.

## Key distribution and transfer

Distributing keys securely is a core management problem. Options:

- Out-of-band physical transfer (hardware tokens, USB devices) for high-assurance cases.
- Encrypted transport using an established asymmetric scheme: encrypt keys using the recipient's public key (RSA, ECIES) and sign or MAC the package to protect integrity.
- Use key-encryption keys (KEKs): KEK encrypts data keys; KEKs are distributed/stored with stronger protections.
- Use authenticated key-exchange protocols (Diffie–Hellman, ECDH) inside a protocol that authenticates the parties (TLS, SSH key exchange, or authenticated DH).

When keys are transmitted, always include integrity checking and, where appropriate, error-detection codes — keys corrupted during transfer can render large volumes of data unrecoverable.

## Key verification and checksums

Simple techniques reduce risk of accidental corruption:

- Transmit a key along with a keyed MAC (e.g., HMAC) or a checksum derived with a one-way function. The recipient verifies the MAC before use.
- Use key-wrapping algorithms (RFC 3394 / AES Key Wrap) which combine confidentiality and integrity for key transport.
- For symmetric keys transmitted in the clear (not recommended), include error-detection/correction codes so corrupted keys can be rejected and re-transmitted.

## Secure storage and hardware protection

- Hardware Security Modules (HSMs) provide tamper-resistant storage and cryptographic operations without exposing raw key material to the host.
- Trusted Platform Modules (TPMs) and Secure Enclaves (Intel SGX, ARM TrustZone) offer device-level key protection.
- If HSM/TPM is not available, use OS-provided secure keystores (e.g., Windows DPAPI, macOS Keychain, Linux kernel keyring) and encrypt key material at rest with a high-entropy KEK.

Protect master/root keys with the strongest available controls: offline storage, multi-person control, HSMs, and split knowledge where appropriate.

## Key rotation, expiration, and lifetime

Keys should have explicit lifetimes. Reasons to rotate or expire keys:

- Limit the amount of data encrypted under one key (reduces cryptanalysis advantage and exposure if compromised).
- Reduce damage window after compromise.
- Meet cryptographic-agency or compliance requirements.

Rotation best practices:

- Automate rotation where possible and plan for seamless re-encryption or re-wrapping of data keys.
- Use short-lived session keys for data encryption and keep a small number of longer-lived KEKs.
- Maintain backward-compatibility for decryption during transition windows (key identifiers, versioning, metadata).

## Key backup and escrow

Backups are necessary but increase risk. Backup recommendations:

- Encrypt backups with a KEK that is stored separately and protected (e.g., in an HSM or split across custodians).
- Use threshold schemes (Shamir's Secret Sharing) to distribute backup access across multiple trusted parties so that no single person can recover keys alone.
- For organizational environments, consider formal key escrow policies only with clear legal and operational controls.

## Compromise, revocation, and incident response

Assume keys may be compromised. Prepare:

- An incident-response plan that includes steps to identify affected keys, revoke or rotate keys, and recover encrypted data if possible.
- Revocation mechanisms: publish certificate revocation lists (CRLs), support OCSP for real-time revocation, or use internal revocation services for symmetric keys.
- If a KEK is compromised, all keys encrypted under it must be considered at risk and re-wrapped with a new KEK.

## Key usage control and policy

Enforce usage restrictions:

- Attach usage metadata or control vectors (authorization information) to keys so systems reject using keys for unintended purposes (signing vs encryption).
- Enforce least privilege: limit which principals and systems can access keys and what operations are allowed.
- Log cryptographic operations for audit and non-repudiation purposes where appropriate.

## Key derivation and hierarchical key structures

Key hierarchies reduce exposure by deriving short-lived keys from master keys using KDFs (HKDF, SP 800‑108). Typical pattern:

- Root/master key (highly protected) -> KEK or intermediate keys -> data keys / session keys

Derive keys with labeled context and unique nonces/salts to avoid cross-protocol key reuse.

## Practical recommendations and modern additions

- Prefer authenticated encryption (AEAD) modes: AES‑GCM, AES‑CCM, or ChaCha20-Poly1305 for combined confidentiality and integrity.
- Use established key-wrapping standards (AES Key Wrap, RFC 5649) rather than custom schemes.
- For password-derived keys, prefer Argon2id or scrypt over simple PBKDF2 unless platform compatibility demands otherwise.
- Use standard, vetted libraries and avoid writing your own cryptographic primitives.
- Monitor cryptographic research and be ready to migrate algorithms/lengths (e.g., post-quantum readiness — when quantum-capable adversaries become realistic, symmetric key lengths and public-key algorithms must be reconsidered).

### Recommended minimums (as of mid-2020s)

- Symmetric key: 128 bits (AES-128); 256 bits for long-term confidentiality.
- Hash output: 256 bits (SHA-256 family).
- RSA modulus: 2048 bits minimum; 3072+ bits for long-term security.
- ECC curve: P-256 minimum for 128-bit security equivalence; P-384 for higher assurance.

## Short checklist for secure key management

1. Generate keys with a CSPRNG seeded by real entropy.
2. Use KDFs with salt for password-derived keys.
3. Apply proper key lengths for the algorithm and lifetime.
4. Store master/KEKs in HSMs or secure keystores; wrap data keys.
5. Protect key transport with authenticated encryption and integrity checks.
6. Enforce key usage policies and least privilege.
7. Rotate keys and retire old keys according to policy; keep versioning.
8. Maintain backups protected by separate KEKs or threshold schemes.
9. Prepare an incident response and revocation process.

## Further reading and standards

- Bruce Schneier, Applied Cryptography (Chapters: Key Length, Key Management).
- NIST SP 800‑57: Recommendation for Key Management.
- NIST SP 800‑56: Recommendations for Key Establishment.
- RFC 5869: HKDF (HMAC-based Key Derivation Function).
- RFC 3394 / RFC 5649: AES Key Wrap Algorithms.
- Password Hashing Competition (Argon2 specification).
