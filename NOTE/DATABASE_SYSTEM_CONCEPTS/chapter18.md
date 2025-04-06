# Chapter18 Parallel Databases



We present three basic data-partitioning strategies. Assume that there are $n$ disks, $D_0, D_1, \cdots, d_{n-1}$, across which the data are to be partitioned:

- `Round-robin`. This strategy scans the relation in any order and sends the $i$th tuple to disk number $D_{i\ mod\ n}$. The round-robin scheme ensures an even distribution of tuples across disks; that is, each disk has approximately the same number of tuples as the others.
- `Hash partitioning`. This declustering strategy designates one or more attibutes from the given relation's schema as the partitioning attributes. A hash function is chosen whose range is $\{0, 1, \cdots, n - 1\}$. Each tuple of the original relation is hashed on the partitioning attributes. If teh hash function returns $i$, then the tuple is placed on disk $D_i$.
- `Range partitioning`. This strategy distributes tuples by assigning contiguous attribute-value ranges to eah disk. It chooses a partitioning attribute, A, and a `partitioning vector` $[v_0, v_1, \cdots, v_{n-2}]$, such that, if $i < j$, then $v_i < v_j$. The relation is partitioned as follows: Consider a tuple $t$ such that $t[A] = x$. If $x < v_0$, then $t$ goes on disk $D_0$ If $x \geq v_{n-2}$, then $t$ goes on disk $D_{n-1}$. If $v_i \leq x < v_{i+1}$, then $t$ goes on disk $D_{i + 1}$.

When a relation is partitioned (by a technique other than round-robin), there may be a `skew` in the distribution of tuples, with a high percentage of tuples placed in some partitions and fewer tuples in other partitions. The ways that skew may appear are classified as:

- Attribute-value skew.
- Partition skew.

TODO
