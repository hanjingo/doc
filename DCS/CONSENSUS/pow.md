English | [中文版](pow_zh.md)

# Proof of Work (PoW)

[TOC]



PoW is a consensus mechanism used primarily in cryptocurrencies like Bitcoin.

## Summary

Repeatedly compute the hash of the block header, constantly modifying a parameter, until a hash value that matches the target is found; this is the core idea of the algorithm.



## Key Concepts

- Difficulty determines approximately how many computations are needed to complete one operation.

- Hash computation takes an input of any length and returns a fixed-length output; the generated hash is uniformly distributed.



## Bitcoin

Constant difficulty formula:
`new difficulty = old difficulty * (time spent on last 2016 blocks / 20160 minutes)`
`target = max target / difficulty`



## References

[1] [Consensus Algorithms in Distributed System](https://www.geeksforgeeks.org/operating-systems/consensus-algorithms-in-distributed-system/)
