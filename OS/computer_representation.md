# Computer representation — bytes, endianness, and overflow

[TOC]

This short note explains how computers represent integers and floating-point numbers, what "endianness" means, how overflow happens, and practical consequences for code that reads, writes, or communicates binary data. It is a compact, developer-focused complement to the CS:APP material.

## 1. Fixed-width integer representation

Most modern systems use fixed-width binary encodings for integers (commonly 8-, 16-, 32-, or 64-bit types). Two important categorizations:

- Unsigned integers represent values 0..2^N - 1.
- Signed integers are usually represented in two's complement. For an N-bit two's-complement integer, values range from -2^{N-1} to 2^{N-1}-1.

Two's-complement advantages:

- Single zero representation.
- Same binary addition circuitry for signed and unsigned arithmetic (modular arithmetic semantics).

Example (8-bit two's complement):

- 0x01 = 1
- 0xff = -1 (because 255 interpreted as signed 8-bit equals -1)

Be mindful: interpreting the same bytes as signed vs unsigned changes the numeric meaning.

## 2. Integer overflow and wraparound

Because integers are fixed-width, arithmetic can overflow. Rules differ by language:

- In unsigned arithmetic (C/C++), operations wrap modulo 2^N — this is well-defined.
- In signed C/C++ integer overflow is undefined behavior (compiler may assume it never happens), so avoid writing code that relies on signed overflow.

Practical consequences:

- Prefer unsigned arithmetic when you need modular wraparound semantics.
- Use safe checks or builtin intrinsics (e.g., compiler intrinsics or language features) to detect overflow when correctness depends on it.

## 3. Endianness (byte order)

Endianness describes how multi-byte values are laid out in memory:

- Little-endian: least significant byte (LSB) at the lowest address. Example on a little-endian machine for 32-bit 0x11223344 stored at address A:

	Address A   : 0x44 (LSB)
	Address A+1 : 0x33
	Address A+2 : 0x22
	Address A+3 : 0x11 (MSB)

- Big-endian: most significant byte (MSB) at the lowest address. The same 32-bit value laid out as:

	Address A   : 0x11 (MSB)
	Address A+1 : 0x22
	Address A+2 : 0x33
	Address A+3 : 0x44 (LSB)

Common platforms:

- x86/x86-64: little-endian.
- Many network protocols and some RISC platforms use big-endian or define network byte order as big-endian.

Why it matters: reading or writing raw bytes (files, sockets, shared memory, disk) requires a consistent interpretation of byte order across producers and consumers.

## 4. Host order vs network order

Network byte order is a convention (big-endian) used by many network protocols. When serializing integers for network transport, convert between host byte order and network byte order using standard helpers:

- POSIX/BSD-style: `htonl`, `htons`, `ntohl`, `ntohs`.
- On POSIX, `htonl` converts a 32-bit host-order value to network order.

If you write cross-platform or cross-endian code, always define the wire-format explicitly (e.g., use little-endian or big-endian consistently) and convert at the API boundary.

## 5. Byte-swapping and helpers

If you need to change byte order in-place, use tested helper functions instead of hand-coded loops. Examples:

- Compiler intrinsics: GCC/Clang provide `__builtin_bswap32`, `__builtin_bswap64`.
- Standard library: C++20 provides `<bit>` with `std::byteswap` (or equivalent in implementations).

Using intrinsics is faster and less error-prone than manual byte manipulation.

## 6. Floating-point representation (brief)

Most systems implement IEEE 754 binary floating-point (single and double precision). Floating-point is not a simple fixed-point integer:

- Values are represented as sign × mantissa × 2^{exponent}.
- There are rounding modes and special values (NaN, ±Inf, signed zero).

Implications:

- Bit-level layout and endianness also affect floating-point when transferring raw bytes; prefer text or a defined binary format (e.g., IEEE 754 in a chosen endianness) for portability.
- Do not compare floats for equality; use tolerances.

## 7. Alignment and multi-byte access

- Many architectures require or prefer aligned accesses: reading a 32-bit value at an address not divisible by 4 may be slower or fault.
- When reading unaligned data (e.g., packed file formats), use memcpy into an aligned local variable or use platform-provided unaligned access helpers.

## 8. Serialization guidance (practical checklist)

1. Define the on-wire format explicitly: integer sizes (e.g., uint32_t), signedness, and byte order.
2. Use fixed-width types (`uint8_t`, `uint16_t`, `uint32_t`, `uint64_t`).
3. Convert to network or chosen endianness at API boundaries (not throughout your code). Document the choice.
4. Prefer safe routines (`hton*`, `ntoh*`, `byteswap` intrinsics, `memcpy` for unaligned loads) over pointer-casting raw byte buffers.
5. Include versioning and length prefixes for forward/backward compatibility.

## 9. Examples

Interpretation example (32-bit hex 0x0A0B0C0D stored at address p):

- On little-endian machine, bytes at p..p+3 will be: 0x0D 0x0C 0x0B 0x0A.
- On big-endian machine, bytes at p..p+3 will be: 0x0A 0x0B 0x0C 0x0D.

To write portable code that reads a 32-bit big-endian value from a buffer:

```c
uint32_t read_be32(const uint8_t *buf) {
		return ((uint32_t)buf[0] << 24) | ((uint32_t)buf[1] << 16)
				 | ((uint32_t)buf[2] << 8) | (uint32_t)buf[3];
}
```

Or with intrinsics on a little-endian host, memcpy and byteswap may be faster and clearer.

## 10. Summary

- Endianness affects how multi-byte values are laid out; always agree on byte order for persistence and network protocols.
- Use fixed-width integer types and explicit conversions at boundaries.
- Beware of signed-integer overflow (undefined in C/C++) and use unsigned or checked arithmetic when necessary.
- Prefer library helpers and intrinsics for byte-swapping and unaligned access.

## Reference

[1] Randal E. Bryant, David R. O'Hallaron. Computer Systems: A Programmer's Perspective. 3rd ed. (CS:APP)

---

If you want, I can now:
- Expand this into a short tutorial with interactive examples (byte-dumps on little vs big endian).
- Add a small C/C++ code sample that demonstrates `htonl`/`ntohl`, `__builtin_bswap32`, and safe unaligned access.

