
# GOST — Overview and Notes on the GOST Cipher Family

This document summarizes the most commonly encountered "GOST" algorithms in practice: the classic GOST 28147-89 block cipher (often referred to simply as "GOST"), and brief notes on related Russian standards in the GOST family (hash and modern block ciphers). The intent is a concise practical reference for engineers who must understand, maintain, or migrate systems that use GOST algorithms.

Warning: "GOST" can refer to several standards. When working with real systems, confirm the exact standard/version in use (e.g., GOST 28147-89, GOST R 34.11-2012 (Streebog), GOST R 34.12-2015 (Kuznyechik/Magma), GOST R 34.10 signatures).

## Quick facts (GOST 28147-89)

- Block size: 64 bits
- Key length: 256 bits (key treated as eight 32-bit subkeys)
- Rounds: 32 rounds
- Structure: Feistel-like round function using modular addition, S-box substitution, rotation and XOR
- Parameterization: algorithm uses S-boxes (eight 4×16 tables) that historically were implementation-defined; choice of S-boxes affects security.

GOST 28147-89 was standardized in 1989 and became widely used in Soviet and post‑Soviet systems. It is still encountered in legacy protocols and some regional standards.

## High-level description of GOST 28147-89

GOST 28147-89 operates on 64-bit blocks split into two 32-bit words (L, R). Each round uses one of eight 32-bit subkeys derived from the 256-bit key. The round function is:

1. Add the 32-bit subkey to the 32-bit right half modulo 2^32.
2. Split the 32-bit result into eight 4-bit pieces and substitute each with the corresponding S-box value (four bits → four bits), producing a 32-bit value.
3. Rotate the substituted 32-bit word left by 11 bits.
4. XOR the rotated value with the left half to form the new right half; swap halves for the next round.

The key schedule uses the eight 32-bit key words as subkeys: for rounds 1..24 the subkeys are used in order (K1..K8 repeated three times), and for rounds 25..32 the subkeys are used in reverse (K8..K1). Decryption applies the same structure with subkeys used in reverse order.

This simple, regular key schedule and round function are fast in software and easy to implement.

## S-boxes and parameterization

The S-boxes (eight 4-bit substitution tables) are the primary nonlinear component. Historically S-box values were sometimes kept secret or chosen by implementers. Several points:

- Security depends on good S-boxes. Weak or specifically chosen S-boxes may reduce resistance to differential or linear cryptanalysis.
- Some interoperability profiles define standard S-box sets; always confirm which S-box set your implementation expects.
- When migrating, treat S-boxes as part of the cipher parameters — do not assume a single universal S-box set.

## Modes of operation and usage

GOST 28147-89 is a block cipher and must be used with a secure mode (CBC, CTR, etc.). Practical guidance:

- Do not use ECB for multi-block data.
- For confidentiality+integrity prefer AEAD; if unavailable, use Encrypt-then-MAC with a strong MAC (HMAC-SHA256 or similar).
- Because the block size is 64 bits, long messages suffer from birthday-bound concerns for collisions (similar to other 64-bit ciphers). For large data volumes, prefer 128-bit block ciphers.

GOST can be used in TLS-like constructions or legacy VPNs, but modern transports favor AES or ChaCha20-Poly1305.

## Known weaknesses and cryptanalysis

- Block size: the 64-bit block size is a limitation for high-volume encryption (birthday paradox) and increases risks in long-term or high-throughput systems.
- Structural cryptanalysis: research has produced attacks against reduced-round versions and attacks exploiting weak S-box choices. No broadly deployed practical full-key break against properly parameterized GOST 28147-89 has been demonstrated in public literature comparable to breaking DES or single‑DES keyspace, but the algorithm is older and less scrutinized than modern ciphers like AES.
- Parameter sensitivity: insecure or nonstandard S-boxes, or poor key management, can materially weaken security.

Because of those issues and the existence of stronger, better-analyzed ciphers, prefer modern algorithms for new systems.

## Implementation notes and pitfalls

- Verify S-box set: ensure your implementation and peers use the same S-box parameters.
- Endianness and word assembly: be careful with byte/word order when implementing the addition, substitution and rotation operations; test against known vectors.
- Constant-time: avoid secret-dependent memory access patterns to S-box tables where side-channel resistance is required; consider masked S-box techniques or hardware implementations with side-channel protections.
- Key schedule cost: GOST's key schedule is trivial and cheap, but careful key generation and strong entropy are still required.

## Related GOST standards and modern equivalents

The GOST family includes several related standards — don't conflate them:

- GOST 28147-89: classic 64-bit block cipher described above.
- GOST R 34.11-2012 (Streebog): a modern hash function (sometimes called GOST R 34.11) that produces 256- or 512-bit digests. It is a sponge-like construction distinct from MD/SHA families.
- GOST R 34.12-2015: modern block ciphers standardized in Russia. The 2015 standard includes the 128-bit-block cipher "Kuznyechik" (sometimes called "GOST Kuznyechik") and a 64-bit-block cipher "Magma" in some profiles; these are meant to replace older algorithms in certain contexts.
- GOST R 34.10: public-key signature algorithms (elliptic-curve variants are common in modern GOST standards).

When auditing systems, identify the exact standard and version before drawing conclusions about strength or migration paths.

## Interoperability and migration guidance

- If you control both ends, migrate to AES-GCM or ChaCha20-Poly1305 for authenticated encryption. These have wide library support and better security properties.
- If you must interoperate with legacy peers using GOST 28147-89:
  - Confirm S-box parameters and mode of operation.
  - Limit the scope and lifetime of GOST-protected channels; apply additional monitoring and logging.
  - Consider wrapping GOST with AEAD by using Encrypt-then-MAC if native AEAD is not available.
- For new deployments, prefer Kuznyechik (if you need GOST-family compatibility) or standard international ciphers depending on policy.

## Pseudocode (conceptual) — one round and block encrypt

function GOST_Round(R, K):
	t = (R + K) mod 2^32
	t = SboxSubstitute(t)      # eight 4-bit S-boxes
	t = ROTL(t, 11)
	return t

function GOST_Encrypt_Block(L, R, K[8]):
	# K[0..7] repeated in rounds 1..24, then reversed in 25..32
	for i in 1..32:
		Ki = select_subkey(i, K)
		t = GOST_Round(R, Ki)
		tmp = L XOR t
		L = R
		R = tmp
	# After 32 rounds swap halves to produce ciphertext
	return (R, L)

This is conceptual — the exact subkey selection and final swap follow the standard ordering.

## When you will still see GOST

- Legacy government or regional systems where GOST profiles were mandated historically.
- Interoperability with older devices, payment terminals, or archived data formats.

## References and further reading

- GOST 28147-89 specification (historical standard) and regional profiles that define S-boxes and modes.
- GOST R 34.11-2012 (Streebog), GOST R 34.12-2015 (Kuznyechik/Magma), and GOST R 34.10 (signatures) — read the exact standard texts for implementation details.
- Academic cryptanalysis papers on GOST and parameterized S-box attacks.