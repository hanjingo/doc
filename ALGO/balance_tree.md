English | [中文版](balance_tree_zh.md)

# Balanced Trees (overview)

[TOC]

## Introduction

Balanced search trees are data structures that maintain sorted data and guarantee logarithmic-time basic operations (search, insert, delete) by keeping the tree's height proportional to the logarithm of the number of nodes. They are essential for implementing ordered maps, sets, databases, and file-system indexes.

This note summarizes common balanced-tree families: AVL trees, Red–Black trees, B-trees (and B+-trees), and multiway search trees (2-3, 2-3-4). For each family we give key properties, a sketch of operations, and typical applications.

## Why balance matters

In an unbalanced binary search tree (BST), worst-case height can be O(n) (degenerate chain), so search/insert/delete degrade to linear time. Balanced trees guarantee height O(log n) so those operations run in O(log n) time. Different balancing schemes trade stricter height bounds for more complicated rebalancing.

## AVL trees (Adelson-Velsky & Landis)

- Type: height-balanced binary search tree.
- Balance condition: for every node, the heights of its left and right subtrees differ by at most 1.
- Height bound: an AVL tree with n nodes has height O(log n) (tighter constant than red–black trees).

Operations (sketch):
- Search: standard BST search, O(h) = O(log n).
- Insert: do a BST insert, then walk up the path to the root updating heights and performing rotations when a node becomes unbalanced. One or two rotations (single or double) restore balance per imbalance.
- Delete: do BST delete, then rebalance walking up; may require multiple rotations along the path.

Rotations: single rotation (left or right) and double rotation (left-right or right-left) are used to restore the AVL balance invariant.

Trade-offs:
- Pros: strict balance → fast lookups, good for read-heavy workloads.
- Cons: insert/delete require more rebalancing than red–black trees; implementation slightly more complex.

## Red–Black trees

- Type: binary search tree with color bits (red or black) per node enforcing approximate balance.
- Invariants (informal): root is black; red nodes have black children (no two consecutive red); every root-to-leaf path has the same number of black nodes (black-height).
- Height bound: at most 2 log2(n+1), so O(log n).

Operations (sketch):
- Search: same as BST, O(log n).
- Insert: insert as in BST, color the new node red, then fix violations by recoloring and rotations; at most O(log n) time, with O(1) rotations on average per insert.
- Delete: more complex than insert: remove node then fix color/structure via recoloring and rotations; worst-case O(log n).

Trade-offs:
- Pros: simpler amortized rotation behavior and lower constant factors for insert/delete than AVL in many workloads; widely used in standard libraries (e.g., Java TreeMap historically used red–black trees). Good compromise between balancing strictness and update cost.
- Cons: less strict height guarantee than AVL, so slightly slower point queries in some cases.

## trees and B-trees

- Multiway balanced search trees generalize BSTs by allowing nodes to contain multiple keys and multiple children. They are widely used for external-memory indexes because they reduce tree height and the number of disk IOs.

- 2-3 trees: each internal node has 2 or 3 children; 2-3-4 trees allow 2,3, or 4 children. They can be implemented as B-trees of small order or simulated by red–black trees (isomorphism between 2-3-4 trees and red–black trees).

- B-trees (order M):
	- Nodes may have up to M children and M-1 keys.
	- All leaves appear at the same depth.
	- Each internal node (except the root) has at least ceil(M/2) children.
	- Designed for block-oriented (disk) storage: choose M so node fits a disk page.

B+-trees are a variant where internal nodes store only keys (no values) and all records are kept in leaves (often in a linked list for fast range queries).

Operations (sketch):
- Search: descend from root choosing child by binary search in node's keys; O(height) ≈ O(log_M n) node accesses.
- Insert: insert into a leaf; if leaf overflows (too many keys), split and push median up; splitting may cascade to root (increase height by 1).
- Delete: remove key; if node underflows (too few keys), try to borrow from siblings (rotate) or merge with a sibling and pull a key down from parent; may cascade.

Trade-offs:
- Pros: low tree height, few disk accesses (good for databases and file systems). B+ trees improve range scans and sequential access.
- Cons: more complex node management; in-memory constant factors larger than simple BSTs.

## Comparison summary

- AVL: strict balance, fast queries, heavier updates.
- Red–Black: weaker balance guarantees, simpler updates, good overall performance — popular in general-purpose libraries.
- B/B+: ideal for external storage and large data (databases, filesystems).
- 2-3-4: pedagogical multiway trees; useful to understand relation to red–black trees.

## Complexity (typical)

- Search: O(log n)
- Insert: O(log n)
- Delete: O(log n)
- Space: O(n)

Constants and actual performance depend on implementation choices, cache and IO behavior, and the ratio of reads to writes.

## Implementation notes and tips

- Use rotations carefully; test rebalancing code thoroughly (many subtle bugs arise in pointer manipulation).
- For in-memory ordered maps where updates are frequent and code simplicity matters, red–black trees are a good default.
- For read-mostly dictionaries where minimal lookup time matters, consider AVL trees.
- For on-disk or large-index structures prefer B-tree variants (B+ tree for range queries and scans).

## References and further reading

1. Cormen, Leiserson, Rivest, and Stein. Introduction to Algorithms (CLRS) — sections on balanced BSTs and B-trees.
2. Knuth, The Art of Computer Programming, Vol. 3: Sorting and Searching — classic source.
3. Wikipedia and dedicated algorithm textbooks; see also the repository's `NOTE/INTRODUCTION_TO_ALGORITHMS` resources for chapter extracts and diagrams.

