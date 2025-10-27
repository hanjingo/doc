[中文版](huffman_zh.md) | English

# Huffman Coding (overview)

[TOC]

## Overview

Huffman coding is a classic algorithm for lossless prefix coding that produces an optimal variable-length code for a known set of symbol frequencies. Given a set of symbols and their weights (frequencies or probabilities), Huffman's greedy algorithm constructs a prefix-free binary code that minimizes the expected codeword length. Huffman codes are widely used in compression systems (DEFLATE, JPEG Huffman stage, various file formats) and are fundamental in information theory and algorithms courses.

This note summarizes the prefix-code model, the Huffman algorithm, its correctness and complexity, canonical Huffman codes (useful in practice), a short example, and common variants.

## Prefix codes and objective

A prefix code assigns a binary codeword to each symbol such that no codeword is a prefix of another. This property allows unambiguous decoding by reading bits until a complete codeword is found.

Objective: Given symbols S = {s_1,...,s_n} with positive weights w_i (typically symbol frequencies), find a prefix code that minimizes the expected code length:

	E[L] = \sum_{i=1}^{n} w_i \cdot l_i,

where l_i is the length of the codeword for s_i. Under Kraft's inequality, feasible codeword lengths correspond to leaves of a binary tree; minimizing expected length is equivalent to finding a binary tree with weighted external path length minimal.

## Huffman's greedy algorithm

Huffman's algorithm builds an optimal binary tree bottom-up:

1. Initialize a forest of n single-node trees, each node labeled with a symbol and weight w_i.
2. Repeat until only one tree remains:
	 a. Pick two trees with smallest weights (ties broken arbitrarily). Let their roots have weights x and y.
	 b. Create a new node with weight x+y and make the two trees its children.
3. The final tree is the Huffman tree. Assign codewords by giving left/right children bits (e.g., 0 for left, 1 for right) and reading bits from root to leaf.

This greedy choice—merging two least-weight trees—minimizes the increase in total weighted path length at each step and leads to a globally optimal solution.

## Correctness sketch

The standard proof uses an exchange argument: in an optimal tree, the two symbols with smallest weights appear as siblings at maximum depth; merging them and replacing by a single symbol of weight x+y reduces the problem size while preserving optimality. Inductively, Huffman's greedy merge reproduces an optimal tree.

## Complexity

- Using a binary heap (priority queue) of size n to repeatedly extract and insert weights, Huffman's algorithm runs in O(n log n) time and O(n) space.
- Special cases: if weights are already sorted, a two-queue method achieves O(n) time.

## Canonical Huffman codes (practical)

Canonical Huffman codes are a convenient representation that stores only codeword lengths (not full bit patterns). From the multiset of code lengths, canonical codes are constructed deterministically so that shorter codes have lexicographically smaller binary values and codes of the same length are consecutive. Benefits:

- Compact transmission: only the length for each symbol needs to be transmitted.
- Fast encoder/decoder construction: decoder builds lookup tables from lengths.

Construction sketch: sort symbols by (length, symbol id). Assign the smallest code of each length incrementally so codes of equal length are lexicographically contiguous.

Canonical representations are used in DEFLATE's dynamic Huffman blocks and in many practical compressors.

## Example

Symbols and frequencies: A:45, B:13, C:12, D:16, E:9, F:5 (classical example).

Huffman merges (weights): 5+9=14, 12+13=25, 14+16=30, 25+30=55, 45+55=100. The resulting code lengths (one valid assignment) give average length equal to the weighted external path length; Huffman yields optimal expected length among prefix codes.

## Variants and extensions

- Adaptive (online) Huffman coding: updates the code as data arrives (FGK algorithm, Vitter algorithm) — useful when symbol frequencies are not known in advance.
- Extended alphabets / r-ary Huffman: Huffman can be generalized to non-binary alphabets where codewords over an r-ary alphabet are desired.
- Length-limited Huffman: computing an optimal Huffman code subject to a maximum codeword length (solved by the Package-Merge algorithm).
- Arithmetic coding and range coding: often achieve better compression than Huffman for high-precision probability models but are more computationally and implementationally complex; they produce near-optimal fractional bit-per-symbol codes.

## Practical notes

- Huffman is optimal for symbol-by-symbol coding when symbol frequencies are known and codes must be prefix-free.
- For contexts where symbol probabilities vary by context (Markov models), combine Huffman with context modeling or use arithmetic coding.
- In practice, canonical Huffman codes + code-length transmission strikes a good balance between compression and compact representation of the codebook.

## Relation to DEFLATE

DEFLATE uses Huffman coding for the literal/length and distance alphabets. Dynamic DEFLATE blocks transmit code lengths in a compact run-length encoded form; decoders reconstruct canonical Huffman codes from those lengths.

## References

1. Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein. Introduction to Algorithms (CLRS) — section on Huffman codes.
2. D. A. Huffman, "A Method for the Construction of Minimum-Redundancy Codes", Proceedings of the I.R.E., 1952.
3. Practical notes: RFC 1951 (DEFLATE) and other compressor documentation.
