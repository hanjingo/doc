[中文版](shortest_path_problem_zh.md) | English

# Shortest-Path Algorithms

[TOC]

## Introduction

Finding shortest paths in graphs is a central problem in algorithms and has many variants: unweighted vs weighted, nonnegative vs negative edge weights, single-source vs all-pairs, and static vs dynamic graphs. This note summarizes common algorithms (BFS for unweighted graphs, Dijkstra for nonnegative weights, Bellman–Ford for graphs with negative edges, and A* for heuristic-guided search), gives implementation sketches and complexity notes, and points to further reading.

## Breadth-First Search (BFS) — unweighted shortest paths

BFS computes shortest path distances (in number of edges) from a source vertex s in an unweighted graph (directed or undirected). It explores the graph in layers: first all vertices at distance 0 (s), then distance 1, then distance 2, and so on.

Key properties:
- Correctness: BFS finds shortest paths in unweighted graphs.
- Complexity: O(V + E) time using adjacency lists and O(V) space for the queue and distance array.

Typical implementation (queue-based):

```c++
void BFS(Graph& G, Vertex s) {
    for (Vertex v : G.vertices()) {
        v.dist = INF; v.parent = NULL;
    }
    queue<Vertex> q;
    s.dist = 0; q.push(s);
    while (!q.empty()) {
        Vertex v = q.front(); q.pop();
        for (Vertex w : G.adjacent(v)) {
            if (w.dist == INF) {
                w.dist = v.dist + 1;
                w.parent = v;
                q.push(w);
            }
        }
    }
}
```

Include diagrams (repository `res/`) to illustrate layered exploration.

## Dijkstra's algorithm — single-source, nonnegative weights

Dijkstra's algorithm computes shortest paths from a single source in graphs with nonnegative edge weights. It is a generalization of the unweighted layered approach: the algorithm repeatedly selects the vertex with the smallest tentative distance and relaxes its outgoing edges.

Correctness relies on the nonnegativity of edge weights (once the smallest tentative distance vertex is selected, its distance is final).

Priority-queue implementation (sketch):

```c++
void Dijkstra(Graph& G, Vertex s) {
    for (v : G.vertices()) { v.dist = INF; v.visited = false; }
    s.dist = 0;
    using P = pair<Distance, Vertex>;
    priority_queue<P, vector<P>, greater<P>> pq;
    pq.push({0, s});
    while (!pq.empty()) {
        auto [d, v] = pq.top(); pq.pop();
        if (v.visited) continue;
        v.visited = true;
        for (auto [w, weight] : G.adjacent_with_weights(v)) {
            if (v.dist + weight < w.dist) {
                w.dist = v.dist + weight;
                w.parent = v;
                pq.push({w.dist, w});
            }
        }
    }
}
```

Complexity:
- Using a binary heap (priority_queue): O((V + E) log V) which is commonly written as O(E log V).
- With a Fibonacci heap: O(E + V log V) (rarely used in practice due to complexity of implementation).

## Bellman–Ford — graphs with negative edge weights

Bellman–Ford computes single-source shortest paths even when some edges have negative weights, and it detects negative-weight cycles reachable from the source.

Algorithm sketch:

1. Initialize distances: dist[s] = 0, others = INF.
2. Repeat V-1 times: relax every edge (u, v) with weight w: if dist[u] + w < dist[v], set dist[v] = dist[u] + w and parent[v] = u.
3. Check for negative cycles: if any edge can still be relaxed, report a negative cycle.

Complexity: O(V * E) time, O(V) space.

## A* Search — heuristic-guided single-source shortest path

A* is used to find shortest paths when a heuristic estimate h(v) approximating the remaining distance to the target is available. A* expands nodes in order of f(v) = g(v) + h(v) where g(v) is the distance from the start to v. If h is admissible (never overestimates), A* is guaranteed to find an optimal path.

Common uses: pathfinding on grids or maps where a heuristic (Euclidean or Manhattan distance) significantly reduces the search space.

Complexity: depends on heuristic quality; worst-case can be exponential, but practical performance is often far better than uninformed search.

Basic sketch (priority queue ordered by f = g + h):

```c++
void AStar(Graph& G, Vertex s, Vertex goal, function<Dist(Vertex)> h) {
    for (v : G.vertices()) { v.g = INF; v.parent = NULL; }
    using P = pair<Dist, Vertex>; // f, vertex
    priority_queue<P, vector<P>, greater<P>> open;
    s.g = 0; open.push({h(s), s});
    while (!open.empty()) {
        auto [f, v] = open.top(); open.pop();
        if (v == goal) return; // reconstruct path via parents
        for (auto [w, weight] : G.adjacent_with_weights(v)) {
            Dist tentative = v.g + weight;
            if (tentative < w.g) {
                w.g = tentative; w.parent = v;
                open.push({w.g + h(w), w});
            }
        }
    }
}
```

## All-pairs shortest paths

- Floyd–Warshall: O(V^3) dynamic programming algorithm that computes shortest paths between all pairs; supports negative weights (but no negative cycles). Useful for dense graphs or when V is small.
- Repeated Dijkstra: run Dijkstra from every source; O(V * (E log V)) total time.

## Practical notes and tips

- Choose BFS for unweighted graphs.
- Use Dijkstra with a binary heap (priority_queue) for general nonnegative weighted graphs — it's simple and fast in practice.
- Use Bellman–Ford if negative weights must be supported or if negative-cycle detection is required.
- Use A* when you have a good admissible heuristic and a specific target; it can dramatically reduce explored nodes.
- Watch out for implementation details: use adjacency lists for sparse graphs, and avoid expensive decrease-key operations by pushing duplicates into the heap and skipping visited entries when popped.

## References

1. Cormen, Leiserson, Rivest, and Stein. Introduction to Algorithms (CLRS).
2. Mark Allen Weiss. Data Structures and Algorithm Analysis in C++.
3. Amit Patel. "A"). (See: https://www.redblobgames.com for excellent pathfinding visualizations and explanations.)
