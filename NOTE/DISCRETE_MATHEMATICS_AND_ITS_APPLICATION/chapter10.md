# CHAPTER 10 Graphs

[TOC]



## Graphs and Graph Models

**Definition** A `graph` $G = (V, E)$ consists of $V$, a nonempty set of `vertices (or nodes)` and $E$, a set of `edges`. Each edge has either one or two vertices associated with it, called it `endpoints`. An edge is said to `connect` its endpoints.

**Definition** A `directed graph (or digraph)` $(V, E)$ consists of a nonempty set of vertices $V$ and a set of `directed edges (or arcs)` $E$. Each directed edge is associated with an ordered pair of vertices. The directed edge associated with the ordered pair $(u, v)$ is said to `start` at $u$ and `end` at $v$.



## Graph Terminology and Special Types of Graphs

**Definition** Two vertices $u$ and $v$ in an undirected graph $G$ are called `adjacent`(or `neighbors`) in $G$ if $u$ and $v$ are endpoints of an edge $e$ of $G$. Such an edge $e$ is called `incident` with the vertices $u$ and $v$ and $e$ is said to `connect` $u$ and $v$.

**Definition** The set of all neighbors of a vertex $v$ of $G = (V, E)$, denoted by $N(v)$, is called the `neighborhood` of $v$. If $A$ is a subset of $V$, we denote by $N(A)$ the set of all vertices in $G$ that are adjacent to at least one vertex in $A$. So, $N(A) = \cup_{v \in A}N(v)$.

