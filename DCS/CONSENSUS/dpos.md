English | [中文版](dpos_zh.md)

# Delegated Proof of Stake (DPoS)

[TOC]


## Abstract

Nodes elect several delegates, and the delegates are responsible for validation and bookkeeping, instead of all nodes participating; efficiency is much higher than PoS;

The EOS project uses this consensus algorithm;


## Key Points
Last Irreversible Block: The last block recognized by more than 2/3 of the nodes;


## Fork Problem

a, b, c are 3 nodes. When c decides to fork, a and b do not fork; because switching forks requires a cycle time; this causes c's forked chain to be shorter than the non-forked chain of a and b, and DPoS uses the longest chain as the standard;


## Irreversibility

When producing the next block, all records of the previous block must be confirmed


## EOS Speed-up Technology

EOS produces blocks at a speed of 500ms through directional broadcasting; directional broadcasting is much faster than random broadcasting, as it clearly knows the online and offline nodes, so the path is shorter;
