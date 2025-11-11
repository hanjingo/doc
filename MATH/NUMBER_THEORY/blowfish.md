
# Blowfish — Overview and Implementation Notes

This note summarizes Blowfish: the block cipher designed by Bruce Schneier in 1993. It explains the algorithm structure, key schedule and S-boxes, implementation considerations, known limitations, and practical guidance for engineers maintaining or documenting systems that still use Blowfish.

## Quick facts

- Block size: 64 bits
- Key length: variable, 32 bits up to 448 bits (effective entropy depends on key choice)
- Structure: 16-round Feistel network
- Internal state: 18-entry P-array and four 256-entry S-boxes (32-bit entries)
- Status: widely deployed historically (e.g., OpenBSD bcrypt, legacy VPNs); largely superseded by AES for new systems

## Design overview

Blowfish is a symmetric-key block cipher that uses a Feistel network with 16 rounds. Its security comes from complex keyed S-boxes and a large key-dependent P-array. The algorithm was designed for speed in software and to avoid export restrictions of the early 1990s.

High-level encryption of a 64-bit block:

1. Split the input block into two 32-bit halves L and R.
2. For i = 0..15:
	 - L = L XOR P[i]
	 - R = R XOR F(L)
	 - swap(L, R)
3. After 16 rounds, swap(L, R) to undo the last swap.
4. R = R XOR P[16]
5. L = L XOR P[17]
6. Concatenate L and R to produce ciphertext.

Here F is a keyed nonlinear function built from the S-box lookups and additions/XORs.

Decryption is identical to encryption with the P-array applied in reverse order.

## The F function and internal tables

F(x) is the basic nonlinear building block and uses the four S-boxes:

- Split 32-bit input x into four bytes: a, b, c, d.
- Compute: ((S1[a] + S2[b]) XOR S3[c]) + S4[d]

The S-box contents and the P-array are key-dependent: they are initialized with a fixed string (derived from the fractional part of pi in the reference implementation) and then modified repeatedly during key scheduling by encrypting all-zero blocks and XORing results into the tables.

## Key schedule (setup)

Blowfish's key schedule is intentionally expensive and key-dependent:

1. Initialize P-array and S-boxes with fixed constants (the hex digits of pi in the reference implementation).
2. XOR the P-array entries with the key material, cycling the key as needed.
3. Encrypt an all-zero 64-bit block; replace P[0] and P[1] with the 64-bit output.
4. Encrypt the output again; replace P[2] and P[3]; continue this process through the entire P-array and S-box entries.

This process ensures the P-array and S-boxes are strongly dependent on the full key. The downside is that key setup is relatively slow compared to many modern ciphers — a trade-off that was acceptable for many use cases at the time of design but less attractive for systems that need frequent rekeying.

## Security, known properties, and limitations

- Block size limitation: Blowfish uses a 64-bit block size. For large volumes of data this risks block-collision issues (birthday bound) and increases the chance of block replay or pattern leakage under insecure modes of operation. For high-throughput or long-lived data channels, prefer ciphers with 128-bit blocks (e.g., AES).
- Key length: configurable up to 448 bits; key entropy matters. Many historical deployments used shorter keys.
- Cryptanalysis: no practical full-key attacks against properly used Blowfish are widely known, but reduced-round and related-key results exist in literature. Because of the 64-bit block size and better modern alternatives, Blowfish is no longer recommended for new systems.
- Implementation attacks: like any software cipher, Blowfish is susceptible to side-channel attacks (timing, cache) unless implemented with countermeasures.

Because of the 64-bit block size and the availability of AES, Blowfish is generally considered legacy; prefer modern algorithms for new designs.

## Modes of operation and safety

Blowfish is a block cipher and must be used with a secure mode (CBC, CTR, GCM with authenticated encryption, etc.). When used with CBC or other non-authenticated modes, always add an authentication layer (Encrypt-then-MAC) or use an AEAD construction where possible.

Avoid ECB mode and never reuse IV/nonce where uniqueness is required (CTR/OF B/ ...). For Blowfish specifically, the 64-bit block size makes CTR/CBC more sensitive to reuse and long-message issues; ensure proper IV handling.

## Implementation notes and pitfalls

- Key setup cost: Blowfish's expensive key schedule makes it a poor choice for protocols that frequently regenerate keys (e.g., per-message keys). For long-lived keys used across many blocks, the cost amortizes.
- Endianness and bit operations: implementers must be careful with byte order and word assembly when translating the reference pseudocode to languages with different native endianness.
- Memory access pattern: S-box lookups are table indexed by secret-dependent bytes; naive implementations may leak through cache timing. Consider constant-time techniques if side-channel resistance is required.
- Block size: watch out for birthday-bound effects on large datasets; rotate keys or move to 128-bit-block ciphers for large-volume encryption.

## Use cases and migration guidance

- Where Blowfish still appears:
	- Legacy systems and older software stacks (some VPNs, file formats, password hashing wrappers historically derived from Blowfish)
	- bcrypt: note that bcrypt uses the Blowfish key setup/eksblowfish as part of its adaptive key stretching — bcrypt remains widely used for password hashing though modern alternatives (Argon2) are preferred.

- Migration guidance:
	- For general-purpose encryption and new systems: use AES (AES-GCM or AES-CTR+AEAD) or ChaCha20-Poly1305 depending on performance needs.
	- For password hashing: migrate from bcrypt to Argon2id where feasible for stronger memory-hard properties.

## Compact pseudocode (encrypt single block — conceptual)

function Blowfish_Encrypt_Block(L, R, P, S):
		for i in 0..15:
				L = L XOR P[i]
				R = R XOR F(L, S)
				swap(L, R)
		swap(L, R)            # undo final swap
		R = R XOR P[16]
		L = L XOR P[17]
		return (L, R)

function F(x, S):
		a = (x >> 24) & 0xFF
		b = (x >> 16) & 0xFF
		c = (x >> 8) & 0xFF
		d = x & 0xFF
		return ((S[0][a] + S[1][b]) XOR S[2][c]) + S[3][d]

This pseudocode intentionally omits byte-order and low-level details — use a vetted reference implementation or library as the canonical source.

## References and further reading

- Bruce Schneier, "Description of a New Variable-Length Key, 64-Bit Block Cipher (Blowfish)" (original paper and reference implementation).
- Cryptanalysis papers on Blowfish variants and reduced-round results.
- bcrypt design notes (uses Blowfish key schedule) — see bcrypt documentation for password-hashing details.