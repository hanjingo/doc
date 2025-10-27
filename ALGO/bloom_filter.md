
English | [中文版](bloom_filter_zh.md)

# Bloom Filter

[TOC]

## Overview

A Bloom filter is a space-efficient probabilistic data structure used to test whether an element is a member of a set. It can definitively report that an element is not in the set, or report that an element is probably in the set (with some false-positive probability). Bloom filters support very fast insert and query operations and are widely used when memory is limited and occasional false positives are acceptable (for example, cache filtering, databases, and distributed systems).

This note summarizes the Bloom filter data structure, its operations, basic probability analysis for false positives, practical parameter choices, limitations (deletion, false positives), and common variants.

## Data structure

A Bloom filter is implemented as a bit array B of m bits (initially all 0) together with k independent hash functions h_1,...,h_k, each mapping set elements to {0,...,m-1} uniformly.

To insert an element x: compute the k positions h_1(x),...,h_k(x) and set those bits in B to 1.

To query an element x: compute positions h_1(x),...,h_k(x). If any of these bits is 0, x is definitely not in the set. If all are 1, x is considered to be (probably) in the set — this may be a false positive.

Key properties:
- Space: uses m bits (plus small overhead for hash functions).
- Time: insert and query cost O(k) hash computations and bit accesses.
- No false negatives: an inserted element will never be reported as absent.

## Why multiple hash functions?

Using multiple hash functions reduces the probability that all the k bits for a non-inserted element are 1 purely by chance. With a well-chosen k and m relative to expected number of inserted elements n, Bloom filters achieve low false-positive probabilities while remaining compact.

## False-positive probability (sketch)

Assume simple uniform hashing so each hash maps uniformly to m bit positions and different hashes behave independently.

- Probability a particular bit remains 0 after inserting n elements (each setting k bits) is approximately:
	\[
	\left(1 - \frac{1}{m}\right)^{kn} \approx e^{-kn/m}.
	\]
- Therefore probability that a given bit is 1 is roughly p_1 = 1 - e^{-kn/m}.
- For a queried element not in the set, the probability that all k bits are 1 (a false positive) is approximately:
	\[
	p_{fp} \approx \left(1 - e^{-kn/m}\right)^k.
	\]

For fixed m and n, the false-positive probability is minimized when k \approx (m/n) \ln 2, giving
	\[
	p_{fp,min} \approx \left(\tfrac{1}{2}\right)^k \approx \left(0.6185\right)^{m/n}.
	\]

This formula guides choosing m and k for a desired false-positive rate.

## Deletion and variants

Standard Bloom filters do not support deletions: clearing the k bits for an element may unset bits used by other elements, causing false negatives. Two common variants address this:

- Counting Bloom filter: replace bits with small counters that are incremented on insertion and decremented on deletion. Counters must be wide enough to avoid overflow under expected workloads.
- Stable / Scalable Bloom filters and other variants: trade-offs to support dynamic growth or bounded false-positive rates; see references for details.

## Practical choices and tips

- Choose m (bits) proportional to expected number of elements n and desired false-positive probability p. A common rule is m \approx -\tfrac{n \ln p}{(\ln 2)^2} and k \approx (m/n) \ln 2.
- Use independent or pairwise-independent hash functions; in practice, two good hash functions and using combinations (e.g., double hashing) is common and efficient.
- If memory is tight, tune k and m to balance space and acceptable p. Larger k increases CPU per operation; too-large k can increase p if m is fixed.

## Advantages and disadvantages

Advantages:
- Very compact representation for large sets.
- Fast inserts and queries (O(k)).
- No need to store the original elements (good for privacy or memory-limited scenarios).

Disadvantages:
- False positives are possible.
- Standard Bloom filter cannot delete elements safely.
- Does not store elements themselves, so cannot enumerate set members (only membership queries).

## Applications

- Database query filters (avoid expensive disk seeks)
- Cache/memory filters to reduce lookups to backing store
- Network systems (e.g., peer-to-peer, routers) for membership summaries
- Big-data systems to reduce I/O or network transfer

## References

1. Burton H. Bloom, "Space/Time Trade-offs in Hash Coding with Allowable Errors", Communications of the ACM, 1970.
2. Wikipedia: Bloom filter.
3. Survey and implementation notes (see project references and online resources).


