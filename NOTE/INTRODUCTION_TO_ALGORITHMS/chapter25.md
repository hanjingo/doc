[中文版](chapter25_zh.md) | English

# 25 All-Pairs Shortest Paths

[TOC]



## Shortest paths and matrix multiplication

$$
\begin{align}
& EXTEND-SHORTEST-PATHS(L, W) \\
& n = L.rows \\
& let\ L' = (l_{ij}')\ be\ a\ new\ n \times n\ matrix \\
& for\ i = 1\ to\ n \\
& \qquad for\ j = 1\ to\ n \\
& \qquad \qquad for\ j = 1\ to\ n \\
& \qquad \qquad \qquad l_{ij}' = \infty \\
& \qquad \qquad \qquad for\ k = 1\ to\ n \\
& \qquad \qquad \qquad \qquad l_{ij}' = min(l_{ij}', l_{k} + w_{kj}) \\
& return\ L'
\end{align}
$$

$$
\begin{align}
& SQUARE-MATRIX-MULTIPLY(A, B) \\
& n = A.rows \\
& let\ C\ be\ a\ new\ n \times n\ matrix \\
& for\ i = 1\ to\ n \\
& \qquad for\ j = 1\ to\ n \\
& \qquad \qquad c_{ij} = 0 \\
& \qquad \qquad for\ k = 1\ to\ n \\
& \qquad \qquad \qquad c_{ij} = c_{ij} + a_{k} \cdot b_{kj} \\
& return\ C
\end{align}
$$

$$
\begin{align}
& SLOW-ALL-PAIRS-SHORTEST-PATHS(W) \\
& n = W.rows \\
& L^{(1)} = W \\
& for\ m = 2\ to\ n - 1 \\
& \qquad let\ L^{(m)}\ be\ a\ new\ n \times n\ matrix \\
& \qquad L^{(m)} = EXTEND-SHORTEST-PATHS(L^{(m - 1)}, W) \\
& return\ L^{(n - 1)}
\end{align}
$$

![25_1](res/25_1.png)

![25_2](res/25_2.png)
$$
\begin{align}
& FASTER-ALL-PAIRS-SHORTEST-PATHS(W) \\
& n = W \cdot rows \\
& L^{(1)} = W \\
& m = 1 \\
& while\ m < n - 1 \\
& \qquad let\ L^{(2m)}\ be\ a\ new\ n \times n\ matrix \\
& \qquad L^{(2m)} = EXTEND-SHORTEST-PATHS(L^{(m)}, L^{(m)}) \\
& \qquad m = 2m \\
& return\ L^{(m)}
\end{align}
$$



## The Floyd-Warshall algorithm

![25_3](res/25_3.png)
$$
\begin{align}
& FLOYD-WARSHALL(W) \\
& n = W.rows \\
& D^{(0)} = W \\
& for\ k = 1\ to\ n \\
& \qquad let\ D^{(k)} = (d_{ij}^{(k)})\ be\ a\ new\ n \times n\ matrix \\
& \qquad for\ i = 1\ to\ n \\
& \qquad \qquad for\ j = 1\ to\ n \\
& \qquad \qquad \qquad d_{ij}^{(k)} = min(d_{ij}^{(k - 1)}, d_{ik}^{(k - 1)} + d_{kj}^{(k - 1)}) \\
& return\ D^{(n)}
\end{align}
$$
![25_4](res/25_4.png)
$$
\begin{align}
& TRANSITIVE-CLOSURE(G) \\
& n = |G.V| \\
& let\ T^{(0)} = (t_{ij}^{(0)})\ be\ a\ new\ n \times n\ matrix \\
& for\ i = 1\ to\ n \\
& \qquad for\ j = 1\ to\ n \\
& \qquad \qquad if\ i == j\ or\ (i.j) \in G.E \\
& \qquad \qquad \qquad t_{ij}^{(0)} = 1 \\
& \qquad \qquad else\ t_{ij}^{(0)} = 0 \\
& for\ k = 1\ to\ n \\
& \qquad let\ T^{(k)} = (t_{ij}^{(k)})\ be\ a\ new\ n \times n\ matrix \\
& \qquad \qquad for\ i = 1\ to\ n \\
& \qquad \qquad \qquad for\ j = 1\ to\ n \\
& \qquad \qquad \qquad \qquad t_{ij}^{(k)} = t_{ij}^{(k - 1)} \bigvee (t_{ik}^{(k - 1)} \bigwedge t_{kj}^{(k - 1)} \\
& return\ T^{(n)}
\end{align}
$$
![25_5](res/25_5.png)



## Johnson's algorithm for sparse graphs

Johnson's algorithm finds shortest paths between all pairs in $O(V^2lgV + VE)$ time.

**Lemma 25.1 (Reweighting does not change shortest paths)** Given a weighted, directed graph $G = (V, E)$ with weight function $w: E \rightarrow R$, let $h: V \rightarrow R$ be any function mapping vertices to real numbers. For each edge $(u, v) \in E$, define:
$$
\hat{w}(u, v) = w(u, v) + h(u) - h(v)
$$
, Let $p = <v_0, v_1, ..., v_k>$ be any path from vertex $v_0$ to vertex $v_k$. Then $p$ is a shortest path from $v_0$ to $v_k$ with weight function $w$ if and only if it is a shortest path with weight function $\hat{w}$. That is, $w(p) = \delta(v_0, v_k)$ if and only if $\hat{w}(p) = \hat{\delta}(v_0, v_k)$. Furthermore, $G$ has a negative-weight cycle using weight function $w$ if and only if $G$ has a negative-weight cycle using weight function $\hat{w}$.

![25_6](res/25_6.png)
$$
\begin{align}
& JOHNSON(G, w) \\
& compute\ G', where\ G'.V \cup \{s\}, G'.E = G.E \cup \{(s, v): v \in G.V\}, and\ w(s, v) = 0\ for\ all\ v \in G.V \\
& if\ BELLMAN-FORD(G', w, s) == FALSE \\
& \qquad print\ "the\ input\ graph\ contains\ a\ negative-weight\ cycle" \\
& else for\ each\ vertex\ v \in G'.V \\
& \qquad set\ h(v)\ to\ the\ value\ of\ \delta(s, v)\ computed\ by\ the\ Bellman-Ford\ algorithm \\
& \qquad for\ each\ edge(u, v) \in G'.E \\
& \qquad \hat{w}(u, v) = w(u, v) + h(u) - h(v) \\
& \qquad let\ D = (d_{uv}) be\ a\ new\ n \times n\ matrix \\
& \qquad for\ each\ vertex\ u \in G.V \\
& \qquad \qquad run\ DIJKSTRA(G, \hat{w}, u)\ to\ compute\ \hat{\delta}(u, v)\ for\ all\ v \in G.V \\
& \qquad \qquad for\ each\ vertex\ v \in G.V \\
& \qquad \qquad \qquad d_{uv} = \hat{\delta}(u, v) + h(v) - h(u) \\
& return\ D
\end{align}
$$
