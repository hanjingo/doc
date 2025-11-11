
# SHA Family — Overview, Notes, and Practical Guidance

This note summarizes the Secure Hash Algorithm (SHA) family: SHA-1, SHA-2 (SHA-224, SHA-256, SHA-384, SHA-512, and variants), and SHA-3 (Keccak). It explains high-level construction, common pitfalls (length-extension), HMAC use, test vectors, and migration recommendations for engineers.

## Quick facts

- Output sizes:
	- SHA-1: 160 bits
	- SHA-2: 224, 256, 384, 512 bits (and truncated variants)
	- SHA-3 (Keccak): variable output (commonly 224/256/384/512)
- Block sizes:
	- SHA-1 / SHA-256: 512-bit blocks
	- SHA-384 / SHA-512: 1024-bit internal block (512-bit message blocks but different word size)
	- SHA-3: sponge construction with rate/capacity parameters
- Construction:
	- SHA-1/SHA-2: Merkle–Damgård-like compression function (iterated), with internal state and fixed permutations
	- SHA-3: sponge construction (Keccak) — different internal design and security proofs
- Typical uses: hashing, message integrity, building HMAC, PRFs in key-derivation, and digital signatures (hash-then-sign)

## Short history and security status

- SHA-1: Designed in 1995; collisions were shown practically feasible (first full collision demonstrated 2017). SHA-1 is deprecated for collision-resistant uses (certificates, signatures); avoid for security-critical integrity.
- SHA-2: Designed as a stronger replacement; still considered secure when using appropriate digest lengths (SHA-256, SHA-384, SHA-512). No practical collisions are known as of this writing.
- SHA-3: A distinct design (Keccak) standardized in 2015. SHA-3 provides an alternative construction with different security assumptions; useful if diversity or resistance to certain structural attacks is desired.

Prefer SHA-2 or SHA-3 for new systems; treat SHA-1 as legacy only.

## High-level algorithm notes

- SHA-1 / SHA-2:
	- Process input in fixed-size blocks; pad the final block by appending a 1-bit, zeroes, and the length field (big-endian for SHA-2).
	- Maintain an internal state (chain variables); each block is processed with a compression function that mixes message words and state using bitwise operations and rotations.
	- Output the final state as the message digest (possibly truncated).
- SHA-3 (Keccak):
	- Uses a sponge construction with a chosen rate (r) and capacity (c). Data is absorbed into the sponge, then squeezed to produce output. Padding and domain separation are different from SHA-2.

Implementers should refer to the RFCs and specification tables for exact constants and permutations. Use vetted libraries for production use.

## Length-extension and HMAC guidance

- Length-extension attack: Merkle–Damgård hashes (SHA-1 and SHA-2) are vulnerable to length-extension attacks: given H(m) and len(m), an attacker can compute H(m || padding || m2) for chosen m2 without knowing m. This makes naive constructions such as H(key || message) insecure as MACs.
- HMAC: Use HMAC (e.g., HMAC-SHA256) for keyed message authentication. HMAC is designed to avoid length-extension problems and remains secure when the underlying hash is collision-resistant for typical parameters.

Practical rule: always use HMAC for MACs, and prefer HMAC-SHA256 or HMAC-SHA-512 depending on security/performance tradeoffs.

## Test vectors (basic)

- SHA-1("") = da39a3ee5e6b4b0d3255bfef95601890afd80709
- SHA-256("") = e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855
- SHA-512("") = cf83e1357eefb8bdf1542850d66d8007d620e4050b5715dc83f4a921d36ce9ce
	47d0d13c5d85f2b0ff8318d2877eec2f63b931bd47417a81a538327af927da3e

Use these to validate a hashing implementation.

## Implementation pitfalls and performance

- Endianness and padding: ensure consistent byte-order and length-encoding when interoperating. SHA-1/SHA-2 use big-endian bit-ordering in the length field; implementations often differ in byte/word layout—verify with test vectors.
- Constant-time: hashes operate on public data; constant-time is usually not required, but be careful when using hash outputs in branch conditions with secret data.
- Streaming: use incremental (streaming) APIs provided by libraries for large data to avoid high memory usage.
- Hardware acceleration: many CPUs provide SHA extensions (ARMv8, Intel SHA extensions) or use dedicated hardware for performance.

## Choosing between SHA-2 and SHA-3

- SHA-2 is widely used, well-optimized, and safe for nearly all current applications.
- SHA-3 provides a different internal design (sponge) and can be used when algorithmic diversity is desired or when specific properties of Keccak are needed.
- For most applications, prefer SHA-256 or SHA-512 (SHA-512/256 variant if you need 256-bit output with better performance on 64-bit platforms).

## Migration and practical guidance

- Replace SHA-1: migrate signatures, certificates, and code that rely on SHA-1 for integrity to SHA-2 or SHA-3 as soon as possible.
- Password hashing: do not use plain SHA-family hashes for passwords. Use Argon2id, scrypt, bcrypt, or PBKDF2 with appropriate parameters.
- Key-derivation: prefer HKDF (HMAC-based KDF) with SHA-256/512 rather than ad-hoc hash-based KDFs.

## When to use SHA-3

- If you need a hash with fundamentally different construction from SHA-2 (for diversity), or specific sponge properties (e.g., extendable output functions — XOFs like SHAKE128/256), choose SHA-3.
- SHAKE128/256: extendable-output functions useful for variable-length output (KDFs, XOF needs).

## References

- FIPS 180-4 (SHA-1/SHA-2) and FIPS 202 (SHA-3 / Keccak)
- RFC 6234 (overview and test vectors) and RFC 7693 (SHA-3) for implementation details
- NIST migration guidance and deprecation notes for SHA-1