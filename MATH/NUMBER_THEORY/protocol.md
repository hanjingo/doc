# Encryption / Decryption Protocols — Practical Guide

This document collects practical guidance for building and reviewing encryption and decryption protocols. It consolidates best practices for symmetric and public-key protocols, hybrid encryption, authenticated encryption (AEAD), key exchange and key derivation, nonce/IV management, authentication and replay protection, error handling, and operational controls. The goal is to help engineers design secure, interoperable systems and avoid common pitfalls.

## High-level goals for secure protocols

- Confidentiality: prevent unauthorized parties from reading plaintext.
- Integrity: detect accidental or malicious modification of ciphertext.
- Authenticity: ensure the sender is who they claim to be (or that the key used is authorized).
- Freshness / replay protection: prevent old messages from being replayed.
- Forward secrecy: compromise of long-term keys should not expose past session keys.

Design protocols with these goals in mind and prefer standardized constructions (TLS, SSH, IPsec) over home-grown designs.

## Prefer authenticated encryption (AEAD)

Use AEAD primitives (e.g., AES-GCM, AES-CCM, ChaCha20-Poly1305) whenever possible. AEAD combines confidentiality and integrity in a single primitive and avoids many composition mistakes.

If AEAD is unavailable and you must combine primitives:

- Use Encrypt-then-MAC (EtM): compute ciphertext = Enc_K1(plaintext) then tag = MAC_K2(ciphertext || associated_data); verify MAC before decryption.
- Avoid MAC-then-Encrypt and plain Encrypt-then-Decrypt without authentication.

Include associated data (A) in the authenticated input when context (headers, sequence numbers, protocol metadata) must be bound to the ciphertext.

## Hybrid encryption: how to use public-key crypto safely

Public-key schemes (RSA, ECIES) are typically used to protect symmetric keys rather than bulk data. Typical pattern:

1. Generate a fresh symmetric key K_s (and optionally a nonce/IV) per message or session.
2. Encrypt bulk data with an AEAD scheme using K_s.
3. Encrypt K_s with the recipient's public key using a secure KEM/DEM or RSA-OAEP.
4. Send (encrypted_K_s, nonce, ciphertext, tag, associated_data).

This hybrid approach limits expensive public-key operations and leverages AEAD for integrity.

Use standardized KEMs (e.g., ECIES variants, KEMs in TLS 1.3) and prefer ephemeral keys for forward secrecy.

## Key exchange and forward secrecy

- Use authenticated Diffie–Hellman (Ephemeral DH or ECDHE) for session key agreement and forward secrecy.
- Authenticate DH exchanges with signatures or an authenticated channel (certificates, pre-shared keys) to avoid man-in-the-middle attacks.
- Prefer TLS 1.3 or modern authenticated key exchange protocols (Noise, Signal's X3DH/Double Ratchet) for robust forward secrecy and key management.

## Nonce and IV management

Correct nonce/IV handling is crucial:

- AEAD modes (CTR/ChaCha20/etc.): nonces must never repeat under the same key. Reuse can catastrophically break confidentiality/integrity.
- AES-GCM: reuse of nonce+key can allow tag forgery and plaintext recovery; follow library RFCs (e.g., RFC 5288/5116) for nonce construction.
- CTR: nonce+counter pair must be unique; prefer deterministic counters or random nonces with sufficient length to make collisions negligible.
- CBC: IV should be unpredictable (random) or derived from a secure nonce scheme; do not reuse IVs with the same key for different messages if the mode requires randomness.

Practical patterns:

- Per-session counter: derive a session key and then use a block counter per packet (safe if combined with a unique session nonce).
- Random nonces: use CSPRNG-generated nonces of full length where allowed by the mode; include the nonce with the ciphertext.
- Deterministic IVs: for disk encryption, consider deterministic schemes like SIV (synthetic IV) that provide misuse-resistance.

Document the nonce lifecycle and enforce checks to prevent accidental reuse.

## Associated data and binding context

Always authenticate protocol metadata that affects interpretation: sequence numbers, frame headers, version numbers, sender/recipient IDs, and message types. AEAD `associated_data` is the usual place to include this.

Do not assume implicit binding. Explicitly include and check associated data during decryption.

## Replay protection and sequencing

Common defenses against replays:

- Sequence numbers: include monotonic sequence numbers in associated data and reject out-of-order or previously-seen values.
- Timestamps with bounded skew: include and validate timestamps, but require secure time and check for clock drift.
- Nonce-based single-use tokens: store recent nonces or use stateless techniques like SIV that guarantee uniqueness for given inputs.

Choose the mechanism appropriate for protocol constraints (stateless vs stateful receivers) and document windowing/retention policies.

## Error handling and side-channels

- Be conservative with error messages. Do not reveal whether decryption failed due to authentication failure versus padding/format errors—uniform error signals prevent oracles.
- Use constant-time code paths for secret-dependent branches where feasible.
- Treat timing and response differences as potential oracles (Bleichenbacher-style attacks rely on subtle differences in error behavior).

## Key derivation and lifecycle

- Never derive multiple independent keys by reusing the same raw key material without a proper KDF. Use HKDF (HMAC-based KDF) or other vetted KDFs to derive separate keys for encryption, MAC, and IV/nonce derivation.
- Define clear key lifetimes and rotation policies. Rotate keys before they approach the risk of compromise (e.g., after fixed time or data volume thresholds).
- Use separate keys for different purposes (encryption vs authentication) — derive them via KDF from a single master secret.

Example HKDF usage: derive (K_enc, K_mac, base_nonce) = HKDF(master_secret, info=protocol_context).

## Authentication and certificate handling

- For certificate-based systems, perform proper certificate validation: chain validation, expiration, revocation checking (OCSP/CRLs or stapling), and hostname checks.
- Avoid trusting self-signed certificates unless explicitly provisioned and pinned.
- For signed messages, use modern signature schemes with appropriate padding: RSASSA-PSS or Ed25519/Ed448 rather than PKCS#1 v1.5 signatures.

## Faults, verification and redundancy

- Always verify integrity/authenticity before acting on decrypted data.
- When using CRT optimizations or hardware accelerators, validate results (e.g., re-encrypt or check MAC) to detect faults or tampering.

## Logging, audit, and key compromise response

- Log decryption failures and suspicious events, but avoid logging sensitive plaintext or keys.
- Maintain an incident response plan for key compromise: revoke keys/certificates, rotate keys, and audit recent activity.

## Performance and operational trade-offs

- AEAD with hardware acceleration (AES-NI, ARMv8 SHA/ASM) is fast; ChaCha20-Poly1305 may be faster on systems without AES hardware.
- Measure CPU vs memory vs latency trade-offs for your workload; streaming large payloads favors chunked AEAD with incremental associated data.

## Protocol examples and references

- TLS 1.3: a modern, well-vetted protocol that combines authenticated key exchange (ECDHE), AEAD ciphers, and forward secrecy by default — use it rather than building your own transport security.
- Noise protocol framework: a simple, modern toolbox for building secure channel protocols with clear patterns for key exchange, forward secrecy, and ratcheting.
- RFCs: RFC 5116 (AEAD), RFC 5869 (HKDF), RFC 8017 (PKCS#1) and the TLS RFCs for concrete parameter guidance.

## Checklist (quick)

1. Use AEAD (AES-GCM, ChaCha20-Poly1305) whenever possible.
2. For public-key transport, use hybrid encryption (KEM + AEAD) or authenticated DH (ECDHE) with ephemeral keys for forward secrecy.
3. Ensure nonces/IVs are unique for each key; document and enforce lifecycle.
4. Authenticate associated protocol context explicitly (headers, sequence numbers) via AEAD associated data.
5. Use HKDF to derive separate keys and nonces from a master secret.
6. Validate certificates and use modern signature schemes (PSS, EdDSA).
7. Return uniform errors for decryption/authentication failures and mitigate timing oracles.
8. Plan for key rotation, logging, and compromise recovery.