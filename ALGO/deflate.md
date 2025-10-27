[中文版](deflate_zh.md) | English

# DEFLATE (overview)

[TOC]

## Introduction

DEFLATE is a widely used lossless data-compression format that combines LZ77-style sliding-window compression with Huffman coding. It was designed to give good compression ratio and fast performance, and is the compression method used by gzip, zlib, PNG, and many other formats and protocols. The DEFLATE bitstream format is specified in RFC 1951.

This note summarizes the main ideas behind DEFLATE, describes the block types (uncompressed, fixed Huffman, dynamic Huffman), explains the roles of LZ77 and Huffman coding, and gives practical implementation notes and trade-offs.

## High-level design

DEFLATE works in two complementary stages:

- LZ77 (sliding window): replace repeated substrings by (length, distance) pairs that refer to a previous occurrence inside a sliding window (typically up to 32 KB). Literals (single bytes not part of a match) are emitted directly.
- Huffman coding: encode the sequence of literals and length/distance pairs with variable-length prefix codes (Huffman codes) so that frequent symbols use fewer bits.

The stream is organized as a sequence of blocks. Each block has a small header that indicates whether the block is the last one, and which block type is used:

- Type 0: stored (uncompressed) block — raw bytes aligned to byte boundaries.
- Type 1: compressed with fixed (predefined) Huffman codes.
- Type 2: compressed with dynamic Huffman codes — the Huffman code tables are included in the block header and optimized for the block's symbol frequencies.

Dynamic Huffman blocks give the best compression by adapting to local symbol statistics, at the cost of extra header bits and more complex encoder/decoder logic.

## LZ77 stage (matches and literals)

The LZ77 component scans the input and, for each position, either emits a literal byte or finds the longest match within the previous W bytes (W = 32 KiB in standard DEFLATE). A match is emitted as a length and a backward distance. Lengths and distances are mapped to code symbols (with extra bits) defined by the DEFLATE specification.

Important details:
- Maximum match length and encoding: DEFLATE defines length codes that represent ranges of lengths; some codes carry extra bits to specify the exact length within a range.
- Distance coding: distances are similarly encoded by distance codes with optional extra bits.

The choice of which matches to take (greedy longest, lazy matching, optimal parsing via dynamic programming) affects compression ratio and CPU cost. Common approaches in practical compressors (zlib, gzip, 7-zip variants) use heuristics (e.g., longest match with optional lazy matching) to balance speed and ratio.

## Huffman coding stage

DEFLATE encodes the stream of literal and length symbols and distance symbols with Huffman codes. There are two Huffman alphabets:

- Literal/length alphabet: 0..255 = literal bytes, 256 = end-of-block marker, 257..285 = length codes.
- Distance alphabet: codes for backward distances.

In fixed blocks (type 1) DEFLATE uses predefined canonical Huffman codes specified in RFC 1951. In dynamic blocks (type 2), the encoder builds Huffman code lengths from symbol frequencies and transmits a compact representation of the code lengths (encoded with run-length-like codes) so the decoder can reconstruct canonical Huffman codes.

Canonical Huffman codes are used for compact transmission: only the code lengths need to be sent; both encoder and decoder can construct the exact bit patterns deterministically from the lengths.

## Block layout (brief)

Each block begins with a 3-bit header: 1 bit for BFINAL (is this the last block?) and 2 bits for BTYPE (00=stored, 01=fixed, 10=dynamic). For dynamic blocks, a bit-packed representation of the Huffman code lengths follows, organized to compress the lengths themselves.

Stored blocks are byte-aligned and contain a 16-bit LEN and 16-bit NLEN for error detection.

Dynamic blocks contain three code length alphabets: the code lengths for the literal/length codes, the distance codes, and the code-length codes used to compress those lengths. RFC 1951 details the exact ordering and packing.

## Decompression algorithm (outline)

1. Read block header (BFINAL, BTYPE).
2. If stored block, align to next byte, read LEN and NLEN, copy LEN bytes to output.
3. If fixed block, initialize fixed Huffman tables.
4. If dynamic block, read the Huffman code-length representation and build canonical Huffman tables for literal/length and distance alphabets.
5. Decode symbols using the literal/length Huffman table until the end-of-block symbol (256) is seen. For literal values 0..255, output the byte. For length codes, read any extra bits to obtain the match length, then read a distance code (and its extra bits) and copy 'length' bytes from the previously emitted output using the distance.
6. Repeat until BFINAL is set and all blocks processed.

## Compression algorithm (outline)

1. Find matches and emit a mixed stream of literals and length/distance tokens (LZ77 stage).
2. Count symbol frequencies for literal/length and distance alphabets (optionally per-block) and decide block boundaries.
3. For a dynamic block, compute optimal or heuristic Huffman code lengths from frequencies and emit the code-length representation followed by encoded symbols. For fixed blocks, use predefined codes. If compression would be worse than storing, emit a stored block.

Encoder choices (match strategy, block splitting, whether to use fixed/dynamic codes) strongly influence final size and CPU time.

## Practical notes and trade-offs

- Window size: standard DEFLATE uses a 32 KiB sliding window. Larger windows can find longer-distance matches across larger inputs but require changes to the format and are not compatible with standard DEFLATE.
- Match finder: using hash chains, suffix arrays, or other indexing structures affects speed and memory. Hash-chain-based finders (used by zlib's deflate) are a common compromise.
- Optimal parsing: dynamic programming can find the optimal set of matches and code choices for best compression but is slower; many compressors use greedy or lazy heuristics.
- Block size: per-block Huffman tables adapt to local statistics but carry header overhead; small blocks may reduce compression efficiency due to header cost.
- Compression wrappers: DEFLATE by itself is a raw bitstream format. It is commonly wrapped by zlib (RFC 1950) or gzip (RFC 1952) which add simple headers, checksums (Adler-32 for zlib, CRC32 for gzip), and metadata.

## Limitations

- DEFLATE is not ideal for very small inputs due to header overhead and block/meta data.
- It is designed for general-purpose compression; specialized compressors (e.g., Brotli, Zstandard) may give better ratios or speed for certain data classes.

## References and further reading

1. RFC 1951 — DEFLATE compressed data format specification. https://www.rfc-editor.org/rfc/rfc1951
2. zlib home and documentation: https://zlib.net
3. Mark Adler, "An explanation of the DEFLATE compressed data format" (informal guide). http://zlib.net/feldspar.html
4. PNG specification (uses DEFLATE for zlib-compressed image data).

