# CHAPTER 10 Graphs

[TOC]



## Graphs and Graph Models

**Definition** A `graph` $G = (V, E)$ consists of $V$, a nonempty set of `vertices (or nodes)` and $E$, a set of `edges`. Each edge has either one or two vertices associated with it, called it `endpoints`. An edge is said to `connect` its endpoints.

**Definition** A `directed graph (or digraph)` $(V, E)$ consists of a nonempty set of vertices $V$ and a set of `directed edges (or arcs)` $E$. Each directed edge is associated with an ordered pair of vertices. The directed edge associated with the ordered pair $(u, v)$ is said to `start` at $u$ and `end` at $v$.



## Graph Terminology and Special Types of Graphs

**Definition** Two vertices $u$ and $v$ in an undirected graph $G$ are called `adjacent`(or `neighbors`) in $G$ if $u$ and $v$ are endpoints of an edge $e$ of $G$. Such an edge $e$ is called `incident` with the vertices $u$ and $v$ and $e$ is said to `connect` $u$ and $v$.

**Definition** The set of all neighbors of a vertex $v$ of $G = (V, E)$, denoted by $N(v)$, is called the `neighborhood` of $v$. If $A$ is a subset of $V$, we denote by $N(A)$ the set of all vertices in $G$ that are adjacent to at least one vertex in $A$. So, $N(A) = \cup_{v \in A}N(v)$.

**Definition** The `degree of a vertex in an undirected graph` is the number of edges incident with it, except that a loop at a vertex contributes twice to the degree of that vertex. The degree of the vertex $v$ is denoted by $deg(v)$.

**THEOREM** THE HANDSHAKEING THEOREM Let $G = (V, E)$ be an undirected graph with $m$ edges. Then $2m = \sum_{v \in V} deg(v)$. (Note that this applies even if multiple edges and loops are present.)

**THEOREM** An undirected graph has an even number of vertices of odd degree.

**Definition** When $(u, v)$ is an edge of the graph $G$ with directed edges, $u$ is said to be `adjacent to` $v$ and $v$ is said to be `adjacent from` $u$. The vertex $u$ is called the `initial vertex of` $(u, v)$, and $v$ is called the `terminal` or `end vertex` of $(u, v)$. The initial vertex and terminal vertex of a loop are the same.

**Definition** In a graph with directed edges the `in-degree of a vertex v`, denoted by $deg ^{-}(v)$, is the number of edges with $v$ as their terminal vertex. The `out-degree of v`, denoted by $deg ^{+}(v)$, is the number of edges with $v$ as their initial vertex. (Note that a loop at a vertex contributes 1 to both the in-degree and the out-degree of this vertex.)

**THEOREM** Let $G = (V, E)$ be a graph with directed edges. Then $\sum_{v \in V}deg^{-}(v) = \sum_{v \in V}deg^{+}(v) = |E|$.

**Definition** A simple graph $G$ is called `bipartite` if its vertex set $V$ can be partitioned into two disjoint sets $V_1$ and $V_2$ such that every edge in the graph connects a vertex in $V_1$ and a vertex in $V_2$ (so that no edge in $G$ connects either two vertices in $V_1$ or two vertices in $V_2$). When this condition holds, we call pair $(V_1, V_2)$ a `bipartition` of the vertex set $V$ of $G$.

**THEOREM** A simple graph is bipartite if and only if it is possible to assign one of two different colors to each vertex of the graph so that no two adjacent vertices are assigned the same color.

**THEOREM** HALL'S MARRIAGE THEOREM: The bipartite graph $G = (V, E)$ with bipartition $(V_1, V_2)$ has a complete matching from $V_1$ to $V_2$ if and only if $|N(A)| \geq |A|$ for all subsets $A$ of $V_1$.

**Definition** A `subgraph of a graph` $G = (V, E)$ is a graph $H = (W, F)$, where $W \subseteq V$ and $F \subseteq E$. A subgraph $H$ of $G$ is a `proper subgraph` of $G$ if $H \neq G$.

**Definition** Let $G = (V, E)$ be a simple graph. The **subgraph induced** by a subset $W$ of the vertex set $V$ is the graph $(W, F)$, where the edge set $F$ contains an edge in $E$ if and only if both endpoints of this edge are in $W$.

**Definition** The `union` of two simple graphs $G_1 = (V_1, E_1)$ and $G_2 = (V_2, E_2)$ is the simple graph with vertex set $V_1 \cup V_2$ and edge set $E_1 \cup E_2$. The union of $G_1$ and $G_2$ is denoted by $G_1 \cup G_2$.



## Representing Graphs and Graph Isomorphism

The **adjacency matrix A** (or $A_G$) of $G$, with respect to this listing of the vertices, is the $n \times n$ zero-one matrix with 1 as its $(i, j)$th entry when $V_i$ and $v_j$ are adjacent, and 0 as its $(i, j)$th entry when they are not adjacent. In other words, if its adjacency matrix is $A = [a_{ij}]$, then:
$$
a_{ij} = 
\begin{cases}
1, &\text{if } \{v_i, v_j\} \text{ is an edge of G} \\
0, &\text{otherwise}
\end{cases}
$$
Let $G = (V, E)$ be an undirected graph. Suppose that $v_1, v_2, ..., v_n$ are the vertices and $e_1, e_2, ..., e_m$ are the edges of $G$. Then the **incidence matrix** with respect to this ordering of $V$ and $E$ is the $n \times m$ matrix $M = [m_{ij}]$, where:
$$
m_{ij}
\begin{cases}
1, &\text{when edge } e_j \text{ is incident with } v_i \\
0, &\text{otherwise}
\end{cases}
$$
**Definition** The simple graphs $G_1 = (V_1, E_1)$ and $G_2 = (V_2, E_2)$ are `isomorphic` if there exists a one-to-one and onto function $f$ from $V_1$ to $V_2$ with the property that $a$ and $b$ are adjacent in $G_1$ if and only if $f(a)$ and $f(b)$ are adjacent in $G_2$, for all $a$ and $b$ in $V_1$. Such a function $f$ is called an `isomorphism.*` Two simple graphs that are not isomorphic are called `nonisomorphic`.



## Connectivity

**Definition** Let $n$ be a nonnegative integer and $G$ an undirected graph. A `path of length` $n$ from $u$ to $v$ in $G$ is a sequence of $n$ edges $e_1, ..., e_n$ of $G$ for which there exists a sequence $x_0 = u, x_1, ..., x_{n - 1}, x_n = v$ of vertices such that $e_i$ has, for $i = 1, ..., n$, the endpoints $x_{i - 1}$ and $x_i$. When the graph is simple, we denote this path by its vertex sequence $x_0, x_1, ..., x_n$ (because listing these vertices uniquely determines the path). The path is a `circuit` if it begins and ends at the same vertex, that is, if $u = v$, and has length greater than zero. The path or circuit is said to pass through the vertices $x_1, x_2, ..., x_{n - 1}$ or `traverse` the edges $e_1, e_2, ..., e_n$. A path or circuit is `simple` if it does not contain the same edge more than once.

**Definition** Let $n$ be a nonnegative integer and $G$ a directed graph. A `path` of length $n$ from $u$ to $v$ in $G$ is a sequence of edges $e_1, e_2, ..., e_n$ of $G$ such that $e_1$ is associated with $(x_0, x_1)$, $e_2$ is associated with $(x_1, x_2)$, and so on, with $e_n$ associated with $(x_{n - 1}, x_n)$, where $x_0 = u$ and $x_n = v$. When there are no multiple edges in the directed graph, this path is denoted by its vertex sequence $x_0, x_1, x_2, ..., x_n$. A path of length greater than zero that begins and ends at the same vertex is called a `circuit` or `cycle`. A path or circuit is called `simple` if it does not contain the same edge more than once.

**Definition** An undirected graph is called `connected` if there is a path between every pair of distinct vertices of the graph. An undirected graph that is not `connected` is called `disconnected`. We say that we `disconnect` a graph when we remove vertices or edges, or both, to produce a disconnected subgraph.

**THEOREM** There is a simple path between every pair of distinct vertices of a connected undirected graph.

**Definition** A directed graph is `strongly connected` if there is a path from $a$ to $b$ and from $b$ to $a$ whenever $a$ and $b$ are vertices in the graph.

**Definition** A directed graph is `weakly connected` if there is a path between every two vertices in the underlying undirected graph.

**THEOREM** Let $G$ be a graph with adjacency matrix $A$ with respect to the ordering $v_1, v_2, ..., v_n$ of the vertices of the graph (with directed or undirected edges, with multiple edges and loops allowed). The number of different paths of length $r$ from $v_i$ to $v_j$, where $r$ is a positive integer, equals the $(i, j)$th entry of $A^{r}$.



## Euler and Hamilton Paths

**Definition** An `Euler circuit` in a graph $G$ is a simple circuit containing every edge of $G$. An `Euler path` in $G$ is a simple path containing every edge of $G$.

**THEOREM** A connecgted multigraph with at least two vertices has an Euler circuit if and only if each of its vertices has even degree.

**THEOREM** A connecgted multigraph has an Euler path but not an Euler circuit if and only if it has exactly two vertices of odd degree.

**Definition** A simple path in a graph $G$ that passes through every vertex exactly once is called a `Hamilton path`, and a simple circuit in a graph $G$ that passes through every vertex exactly once is called a `Hamilton circuit`. That is, the simple path $x_0, x_1, ..., x_{n - 1}, x_n$ in the graph $G = (V, E)$ is a Hamilton path if $V = \{x_0, x_1, ..., x_{n - 1}, x_n\}$ and $x_i \neq x_j$ for $0 leq i < j \leq n$, and the simple circuit $x_0, x_1, ..., x_{n - 1}, x_n, x_0$ (with $n > 0$) is a Hamilton circuit if $x_0, x_1, ..., x_{n - 1}, x_n$ is a Hamilton path.

**THEOREM** DIRAC'S THEOREM: If $G$ is a simple graph with $n$ vertices with $n \geq 3$ such that the degree of every vertex in $G$ is at least $n / 2$, then $G$​ has a Hamilton circuit.

**THEOREM** ORE'S THEOREM: If $G$ is a simple graph with $n$ vertices with $n \geq 3$ such that $deg(u) + deg(v) \geq n$ for every pair of nonadjacent vertices $u$ and $v$ in $G$, then $G$ has a Hamilton circuit.

 

## Shortest-Path Problems

**THEOREM** Dijkstra's algorithm finds the length of a shortest path between two vertices in a connected simple undirected weighted graph.

**THEOREM** Dijkstra's algorithm uses $O(n^2)$ operations (additions and comparisons) to find the length of a shortest path between two vertices in a connected simple undirected weighted graph with $n$ vertices.



## Planner Graphs

**Definition** A graph is called `plannar` if it can be drawn in the plane without any edges crossing (where a crossing of edges is the intersection of the lines or arcs representing them at a point other than their common endpoint). Such a drawing is called a `planar representation` of the graph.

**THEOREM** EULER'S FORMULA: Let $G$ be a connected planar simple graph with $e$ edges and $v$ vertices. Let $r$ be the number of regions in a planar representation of $G$. Then $r = e - v + 2$.

**COROLLARY** If $G$ is a connected planar simple graph with $e$ edges and $v$ vertices, where $v \geq 3$, then $e \leq 3v - 6$​.

**COROLLARY** If $G$ is a connected planar simple graph, then $G$ has a vertex of degree not exceeding five.

**COROLLARY** If an connected planar simple graph has $e$ edges and $v$ vertices with $v \geq 3$ and no circuits of length three, then $e \leq 2v - 4$.

**THEOREM** A graph is nonplanar if and only if it contains a subgraph homeomorphic to $K_{3,3}$ or $K_5$.



## Graph Coloring

**Definition** A `coloring` of a simple graph is the assignment of a color to each vertex of the graph so that no two adjacent vertices are assigned the same color.

**Definition** The `chromatic number` of a graph is the least number of colors needed for a coloring of this graph. The chromatic number of a graph $G$ is denoted by $\chi (G)$. (Here $\chi$ is the Greek letter `chi`).

**THEOREM** THE FOUR COLOR THEOREM: The chromatic number of a planar graph is no greater than four.



## Key Terms and Results

TODO
