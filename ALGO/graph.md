# Graph

[TOC]



A Graph is composed of a set of vertices($V$) and a set of edges($E$). The vertices are connected to each other through edges.

## Types

![directed_undirected_graph](res/directed_undirected_graph.png)

![weighted_unweighted_graph](res/weighted_unweighted_graph.png)

![cyclic_acyclic_graph](res/cyclic_acyclic_graph.png)

![connected_disconnected_graph](res/connected_disconnected_graph.png)



## Representation

### Adjacency Matrix

![adjacency_matrix_undirected_graph](res/adjacency_matrix_undirected_graph.png)

![adjacency_matrix_directed_graph](res/adjacency_matrix_directed_graph.png)

For each $edge(u, v)$, we set $A[u][v]$ to true; otherwise, the entry in the array is false. If the edge has a weight associated with it, then we can set $A[u][v]$ equal to the weight and use either a very large or a very small weight as a sentinel to indicate nonexistent edges.

### Adjacency List

![adjacency_list_undirected_graph](res/adjacency_list_undirected_graph.png)

![adjacency_list_directed_graph](res/adjacency_list_directed_graph.png)

For each vertex, we keep a list of all adjacent vertices. The space requirement is then $O(|E| + |V|)$, which is linear in the size of the graph.



## Cycles



## Connectivity



## Maximum Flow



## Shortest-Path Algorithms

### Unweighted Shortest Paths

### Dijkstra's Algorithm

### Graphs with Negative Edge Costs

### Acyclic Graphs



## Minimum Spanning Tree



## Topological Sort



## Reference

[1] Thomas H.Cormen; Charles E.Leiserson; Ronald L. Rivest; Clifford Stein. Introduction to Algorithms. 3ED

[2] Mark Allen Weiss. Data Structures and Algorithm Analysis in C++. 4ED

[3] [Representation of Graph](https://www.geeksforgeeks.org/dsa/graph-and-its-representations/)

