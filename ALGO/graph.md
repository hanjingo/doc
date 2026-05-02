English | [中文版](graph_zh.md)

# Graph Algorithm

[TOC]



A Graph $G = (V, E)$ is composed of a set of vertices($V$) and a set of edges($E$). The vertices are connected to each other through edges.

## Properties

- Each graph edge is a pair $(v, w)$, where $v, w \in V$. Edges are sometimes refered to as **arcs**.
- A directed graph is **acyclic** if it has no cycles.
- A directed graph with this property is called **strongly connected**.
- If a directed graph is not strongly connected, but the underlying graph (without direction to the arcs) is connected, then the graph is said to be **weakly connected**.
- An undirected graph is **connected** if there is a path from every vertex to every other vertex.
- A **path** in a graph is a sequence of vertices $w_1, w_2, w_3, ..., w_N$ such that $(w_i, w_{i+1}) \in E$ for $1 \leq i < N$.
- A **cycle** in a directed graph is a path of length at least 1 such that $w_1 = w_N$.
- A **complete graph** is a graph in which there is an edge between every pair of vertices.

---



## Types

### Finite Graphs

![finite_graph](res/finite_graph.png)

A **finite graph** is a graph with a finite number of vertices and edges. In other words, both the number of vertices and the number of edges in a finite graph are limited and can be counted.

### Infinite Graph

![infinite_graph](res/infinite_graph.png)

A graph is called an **infinite graph** if it has an infinite number of vertices and an infinite number of edges.

### Trivial Graph

![trivial_graph](res/trivial_graph.png)

A finite graph is said to be **trivial** if it contains only one vertex and no edges. It is also known as a singleton graph or a single-vertex graph.

### Simple Graph

![simple_graph](res/simple_graph.png)

A **simple graph** is a graph that does not contain more than one edge between any pair of vertices.

### Multi Graph

![multi_graph](res/multi_graph.png)

Any graph that contains some parallel edges but doesn’t contain any self-loops is called a **multigraph**.

### Null Graph

![null_graph](res/null_graph.png)

A graph of order n and size zero is a graph where there are only isolated vertices with no edges connecting any pair of vertices. A **null graph** is a graph with no edges.

### Complete Graph

![complete_graph](res/complete_graph.png)

A simple graph with n vertices is called a **complete graph** if the degree of each vertex is n-1, that is, one vertex is attached with n-1 edges or the rest of the vertices in the graph. A complete graph is also called **Full Graph**. 

### Directed Graph

![directed_graph](res/directed_graph.png)

*A* **directed graph** is a graph where the edges have a direction associated with them. Directed graphs are sometimes referred to as **digraphs**.

### Undirected Graph

![undirected_graph](res/undirected_graph.png)

An **undirected graph** is a graph where edges do not have a specific direction, meaning connections go both ways. If two places are connected, you can travel in either direction.

### Weighted Graph

![weighted_graph](res/weighted_graph.png)

A **weighted graph** is a graph where each edge has a number (weight) that represents distance, cost, or time. These graphs help find the shortest or cheapest paths.

### Unweighted Graph

![unweighted_graph](res/unweighted_graph.png)

An **unweighted graph** is a graph where all edges are treated equally, with no extra values like distance or cost. It simply shows connections between points.

### Pseudo Graph

![pseudo_graph](res/pseudo_graph.png)

A **pseudograph** is a type of graph that allows for the existence of self-loops (edges that connect a vertex to itself) and multiple edges (more than one edge connecting two vertices).

### Regular Graph

![regular_graph](res/regular_graph.png)

A **regular graph** is a type of undirected graph in which every vertex has the same number of edges (or neighbors). In other words, all vertices in a regular graph have the same degree.

### Sparse Graph

![sparse_graph](res/sparse_graph.png)

A **sparse graph** is a type of graph with relatively few edges compared to the number of vertices.

### Dense Graph

![dense_graph](res/dense_graph.png)

A **dense graph** is a type of graph with many edges compared to the number of vertices.

### Cyclic Graph

![cyclic_graph](res/cyclic_graph.png)

A graph G consisting of n vertices and n> = 3 that is V1, V2, V3... Vn and edges (V1, V2), (V2, V3), (V3, V4)... (Vn, V1) are called **cyclic graph**. 

### Connected Graph

![connected_disconnected_graph](res/connected_disconnected_graph.png)

Graph is said to be **connected** if there exists at least one path between each and every pair of vertices in graph G, otherwise, it is **disconnected**.

### Biconnected Graph

![biconnected_graph](res/biconnected_graph.png)

A graph is said to be **Biconnected** if: 

1. It is connected, i.e. it is possible to reach every vertex from every other vertex, by a simple path. 
2. Even after removing any vertex the graph remains connected.

---



## Representation

### Adjacency Matrix

![adjacency_matrix_undirected_graph](res/adjacency_matrix_undirected_graph.png)

![adjacency_matrix_directed_graph](res/adjacency_matrix_directed_graph.png)

For each $edge(u, v)$, we set $A[u][v]$ to true; otherwise, the entry in the array is false. If the edge has a weight associated with it, then we can set $A[u][v]$ equal to the weight and use either a very large or a very small weight as a sentinel to indicate nonexistent edges.

### Adjacency List

![adjacency_list_undirected_graph](res/adjacency_list_undirected_graph.png)

![adjacency_list_directed_graph](res/adjacency_list_directed_graph.png)

For each vertex, we keep a list of all adjacent vertices. The space requirement is then $O(|E| + |V|)$, which is linear in the size of the graph.

---



## Breadth-first search (BFS)

**Breadth-first search** is a graph traversal algorithm that starts from a source node and explores the graph level by level. First, it visits all nodes directly adjacent to the source. Then, it moves on to visit the adjacent nodes of those nodes, and this process continues until all reachable nodes are visited.

Algorithm:
$$
\begin{align}
& BFS(G, s) \\
& for\ each\ vertex\ u \in G.V - \{s\} \\
& \qquad u.color = WHITE \\
& \qquad u.d = \infty \\
& \qquad u.\pi = NIL \\
& s.color = GRAY \\
& s.d = 0 \\
& s.\pi = NIL \\
& Q = \phi \\
& ENQUEUE(Q, s) \\
& while\ Q \neq \phi \\
& u = DEQUEUE(Q) \\
& for\ each\ u \in G.Adj[u] \\
& \qquad if\ u.color == WHITE \\
& \qquad \qquad u.color = GRAY \\
& \qquad \qquad u.d = u.d + 1 \\
& \qquad \qquad u.\pi = u \\
& \qquad \qquad ENQUEUE(Q, u) \\
& u.color = BLACK
\end{align}
$$
Examples:

![bfs_example1](res/bfs_example1.png)

![bfs_example2](res/bfs_example2.png)

![bfs_example3](res/bfs_example3.png)

![bfs_example4](res/bfs_example4.png)

![bfs_example5](res/bfs_example5.png)

![bfs_example6](res/bfs_example6.png)

![bfs_example7](res/bfs_example7.png)

![bfs_example8](res/bfs_example8.png)

![bfs_example9](res/bfs_example9.png)

Implements:

```c++
std::vector<int> bfs(std::vector<std::vector<int>>& arr)
{
  int v = arr.size();
  std::vector<bool> visited(arr.size(), false);
  std::vector<int> ret;
  std::queue<int> q;
  int src = 0;
  visited[src] = true;
  q.push(src);
  while (!q.empty())
  {
    int curr = q.front();
    q.pop();
    ret.push_back(curr);
    for (int x : arr[curr])
    {
      if (!visited[x])
      {
        visited[x] = true;
        q.push(x);
      }
    }
  }
  return ret;
}
```

Complexity:

| Scenario     | Time Complexity | Space Complexity |
| :----------- | :-------------- | :--------------- |
| Best Case    | $O(|V|)$        | $O(|V|)$         |
| Average Case | $O(|V| + |E|)$  | $O(|V|)$         |
| Worst Case   | $O(|V| + |E|)$  | $O(|V|)$         |

For the adjacency-list implementation above, each reachable vertex is enqueued and dequeued at most once, and each reachable edge is examined at most once, giving traversal cost $O(|V| + |E|)$. In this code, the `visited` array is initialized for all vertices, so even when BFS quickly finishes (for example, source with no outgoing edges), total time is still $O(|V|)$. Space is $O(|V|)$ due to `visited`, `queue`, and output storage.

### Math Fundamentals

**Lemma** Let $G = (V, E)$ be a directed or undirected graph, and let $s \in V$ be an arbitrary vertex. Then, for any edge $(u, v) \in E$, $\delta(s, v) \leq \delta(s, u) + 1 $

**Lemma** Let $G=(V, E)$ be a directed or undirected graph, and suppose that BFS is run on $G$ from a given source vertex $s \in V$. Then upon termination, for each vertex $v \in V$, the value $v.d$ computed by BFS satisfies $u.d \geq \delta(s, u)$.

**Lemma** Suppose that during the execution of BFS on a graph $G = (V, E)$, the queue $Q$ contains the vertices $<v_1, v_2, ..., v_r>$, where $v_1$ is the head of $Q$ and $v_r$ is the tail. Then, $v_r.d \leq v_1.d + 1$ and $v_i.d \leq v_{i + 1}.d$ for $i = 1, 2, ..., r - 1$.

**Corollary** Suppose that vertices $v_i$ and $v_j$ are enqueued during the execution of BFS, and that $v_i$ is enqueued before $v_j$. Then $v_i.d \leq v_j.d$ at the time that $v_j$ is enqueued.

**Theorem (Correctness of breadth-first search)** Let $G = (V, E)$ be a directed or undirected graph, and suppose that BFS is run on $G$ from a given source vertex $s \in V$. Then, during its execution, BFS discovers every vertex $v \in V$ that is reachable from the source $s$, and upon termination, $v.d = \delta(s, v)$ for all $v \in V$. Moreover, for any vertex $v \neq s$ that is reachable from $s$, one of the shortest paths from $s$ to $v$ is a shortest path from $s$ to $v.\pi$ followed by the edge$(v.\pi, v)$.

### Breadth-first Tree

For a graph $G = (V, E)$ with source $s$, we define the **predecessor subgraph** of $G$ as $G_{\pi} = (V_{\pi}, E_{\pi})$, where: $V_{\pi} = \{ v \in V : v.\pi \neq NIL \} \cup \{s\}$ and $E_{\pi} = \{(v.\pi, v) : v \in V_{\pi} - \{s\}\}$. The Predecessor subgraph $G_{\pi}$ is a **breadth-first tree** if $V_{\pi}$ consists of the vertices reachable from $s$ and for all $v \in V_{\pi}$, the subgraph $G_{\pi}$ contains a unique, simple path from $s$ to $v$ that is also the shortest path from $s$ to $v$ in $G$. A breadth-first tree is in fact a tree, since it is connected and $|E_{\pi}| = |V_{\pi}| - 1$. We call the edges in $E_{\pi}$ **tree edges**.

**Lemma** When applied to a directed or undirected graph $G = (V, E)$, procedure BFS constructs $\pi$ so that the predecessor subgraph $G_{\pi} = (V_{\pi}, E_{\pi})$ is a breadth-first tree.

---



## Depth-first search (DFS)

In Depth First Search (or DFS) for a graph, we traverse all adjacent vertices one by one. When we traverse an adjacent vertex, we completely finish the traversal of all vertices reachable through that adjacent vertex.

Algorithms:

$$
\begin{align}
& PRINT-PATH(G, s, v) \\
& if\ v == s \\
& \qquad print\ s \\
& elseif\ v.\pi == NIL \\
& \qquad print\ "no\ path\ from"\ s\ "exists" \\
& else\ PRINT-PATH(G, s, v.\pi) \\
& \qquad print\ v 
\end{align}
$$

$$
\begin{align}
& EFS(G) \\
& for\ each\ vertex\ u\ \in G.V \\
& \qquad u.color = WHITE \\
& \qquad u.\pi = NIL \\
& time = 0 \\
& for\ each\ vertex\ u \in G.V \\
& \qquad if\ u.color == WHITE \\
& \qquad \qquad DFS-VISIT(G, u)
\end{align}
$$

$$
\begin{align}
& DFS-VISIT(G, u) \\
& time = time + 1 \\
& u.d = time \\
& u.color = GRAY \\
& for\ each\ v \in G:Adj[u] \\
& \qquad if\ v.color == WHITE \\
& \qquad \qquad v.\pi = u \\
& \qquad \qquad DFS-VISIT(G, v) \\
& u.color = BLACK \\
& time = time + 1 \\
& u.f = time
\end{align}
$$

Examples:

![dfs_example1](res/dfs_example1.png)

![dfs_example2](res/dfs_example2.png)

![dfs_example3](res/dfs_example3.png)

![dfs_example4](res/dfs_example4.png)

![dfs_example5](res/dfs_example5.png)

![dfs_example6](res/dfs_example6.png)

![dfs_example7](res/dfs_example7.png)

![dfs_example8](res/dfs_example8.png)

![dfs_example9](res/dfs_example9.png)

Implement:

```c++
void dfs(std::vector<std::vector<int>>& arr,
         std::vector<bool>& visited, 
         int s, 
         std::vector<int>& ret)
{
  visited[s] = true;
  ret.push_back(s);
  for (int i : arr[s])
    if (visited[i] == false)
      dfs(arr, visited, i, ret);
}

std::vector<int> dfs(std::vector<std::vector<int>>& arr)
{
  std::vector<bool> visited(arr.size(), false);
  std::vector<int> ret;
  for (int i = 0; i < arr.size(); i++)
  {
    if (visited[i] == false)
      dfs(arr, visited, i, ret);
  }
  return ret;
}
```

Complexity:

| Scenario     | Time Complexity | Space Complexity |
| :----------- | :-------------- | :--------------- |
| Best Case    | $O(|V| + |E|)$  | $O(|V|)$         |
| Average Case | $O(|V| + |E|)$  | $O(|V|)$         |
| Worst Case   | $O(|V| + |E|)$  | $O(|V|)$         |

For the adjacency-list implementation above, the outer loop guarantees all vertices are considered, and each vertex is visited at most once. Across the full traversal, each edge is examined at most once in directed graphs (or twice in undirected graphs, once per endpoint), so total time is $O(|V| + |E|)$. Auxiliary space is $O(|V|)$ from `visited` plus recursion call stack (up to $O(|V|)$ in the worst case), and the result vector can also store up to $|V|$ vertices.

### Properties of depth-first search

![dfs_properties](res/dfs_properties.png)

### depth-first forest

We define the **predecessor subgraph** of a depth-first search slightly differently from that of a breadth-first search: we let $G_{\pi} = (V, E_{\pi})$, where $E_{\pi} = \{(v.\pi, v):v \in V \text{ and } v.\pi \neq NIL\}$. The predecessor subgraph of a depth-first search forms a **depth-first forest** comprising several **depth-first trees**. The edges in $E_{\pi}$ are **tree edges**.

We can define four edge types in terms of the depth-first forest $G_{\pi}$ produced by a depth-first search on $G$:

1. **Tree edges** are edges in the depth-first forest $G_{\pi}$. Edge$(u, v)$ is a tree edge if $v$ was first discovered by exploring edge$(u, v)$.
2. **Back edges** are those edges$(u, v)$ connecting a vertex $u$ to an ancestor $v$ in a depth-first tree. We consider self-loops, which may occur in directed graphs, to be back edges.
3. **Forward edges** are those nontree edges$(u, v)$ connecting a vertex $u$ to a descendant $v$ in a depth-first tree.
4. **Cross edges** are all other edges. They can go between vertices in the same depth-first tree, as long as one vertex is not an ancestor of the other, or they can go between vertices in different depth-first trees.

### Math Fundamentals

**Theorem (Parenthesis theorem)** In any depth-first search of a (directed or undirected) graph $G = (V, E)$, for any two vertices $u$ and $v$, exactly one of the following three conditions holds:

- the intervals $[u.d, u.f]$ and $[v.d, v.f]$ are entirely disjoint, and neither $u$ nor $v$ is a descendant of the other in the depth-first forest,
- the interval $[u.d, u.f]$ is contained entirely within the interval $[v.d, v.f]$, and $u$ is a descendant of $v$ in a depth-first tree, or
- the interval $[v.d, v.f]$ is contained entirely within the interval $[u.d, u.f]$, and $v$ is a descendant of $u$ in a depth-first tree.

**Corollary (Nesting of descendants' intervals)** Vertex $v$ is a proper descendant of vertex $u$ in the depth-first forest for a (directed or undirected) graph $G$ if and only if $u.d < v.d < v.f < u.f$.

**Theorem (White-path theorem)** In a depth-first forest of a (directed or undirected) graph $G = (V, E)$, vertex $v$ is a descendant of vertex $u$ if and only if at the time $u.d$ that the search discovers $u$, there is a path from $u$ to $v$ consisting entirely of white vertices.

**Theorem** In a depth-first search of an undirected graph $G$, every edge of $G$ is either a tree edge or a back edge.

---



## Topological Sort

A **topological sort** is an ordering of vertices in a directed acyclic graph, such that if there is a path from $v_i$ to $v_j$ appears after $v_i$ in the ordering.

Examples:

![topological_sort_example](res/topological_sort_example.png)

### Math Fundamentals 

**Lemma** A directed graph $G$ is acyclic if and only if a depth-first search of $G$ yields no back edges.

**Theorem** TOPOLOGICAL-SORT produces a topological sort of the directed acyclic graph provided as its input.

### Implement

Topological sorting for a Directed Acyclic Graph (DAG) is a linear ordering of vertices such that for every directed edge uv, vertex u comes before v in the ordering.  Topological Sorting for a graph is not possible if the graph is not a DAG.

Example:

![topological_sort_for_dag_example](res/topological_sort_for_dag_example.png)

Implement:

```c++
int topological_sort_dfs(Graph* graph, int v, int* state, int* stack, int* top)
{
    Node* cur;
    state[v] = 1;
    for (cur = graph->adj[v]; cur != NULL; cur = cur->next)
    {
        int to = cur->vertex;
        if (state[to] == 1)
            return 1;

        if (state[to] == 0)
            if (topological_sort_dfs(graph, to, state, stack, top))
                return 1;
    }

    state[v] = 2;
    stack[(*top)++] = v;
    return 0;
}

void topological_sort(Graph* graph)
{
    int i;
    int* state = (int*)calloc((size_t)graph->V, sizeof(int));
    int* stack = (int*)malloc((size_t)graph->V * sizeof(int));
    int top = 0;
    if (!state || !stack) 
    {
        free(state);
        free(stack);
        return;
    }

    for (i = 0; i < graph->V; ++i) 
    {
        if (state[i] != 0)
            continue;


        if (topological_sort_dfs(graph, i, state, stack, &top))
        {
            free(state);
            free(stack);
            return;
        }
    }

    free(state);
    free(stack);
}
```

Complexity:

| Scenario     | Time Complexity | Space Complexity |
| :----------- | :-------------- | :--------------- |
| Best Case    | $O(|V|)$        | $O(|V|)$         |
| Average Case | $O(|V| + |E|)$  | $O(|V|)$         |
| Worst Case   | $O(|V| + |E|)$  | $O(|V|)$         |

For the DFS-based implementation above (adjacency list), each vertex is colored at most once and each edge is explored at most once, so full traversal costs $O(|V| + |E|)$. The algorithm allocates `state` and `stack` arrays of size $|V|$, and recursive DFS depth can reach $|V|$, so auxiliary space is $O(|V|)$. In sparse best-case inputs (for example, no edges), running time becomes $O(|V|)$.

---



## Minimum Spanning Tree

Informally, a **minimum spanning tree** of an undirected graph G is a tree formed from graph edges that connects all the vertices of G at the lowest total cost. A minimum spanning tree exists if and only if G is connected.

![minimum_spanning_tree](/usr/local/src/github/hanjingo/doc/ALGO/res/minimum_spanning_tree.png)

*graph G and it's mimimum spanning trees*

### Prim's Algorithm

Prim’s algorithm is a Greedy algorithm like Kruskal's algorithm. This algorithm always starts with a single node and moves through several adjacent nodes, in order to explore all of the connected edges along the way.

Algorithm:

1. The algorithm starts with an empty spanning tree.
2. The idea is to maintain two sets of vertices. The first set contains the vertices already included in the MST, and the other set contains the vertices not yet included.
3. At every step, it considers all the edges that connect the two sets and picks the minimum-weight edge from these edges. After picking the edge, it moves the other endpoint of the edge to the set containing the MST. 

Example:

![prim_algo1](/usr/local/src/github/hanjingo/doc/ALGO/res/prim_algo1.png)

![prim_algo2](/usr/local/src/github/hanjingo/doc/ALGO/res/prim_algo2.png)

![prim_algo3](/usr/local/src/github/hanjingo/doc/ALGO/res/prim_algo3.png)

![prim_algo4](/usr/local/src/github/hanjingo/doc/ALGO/res/prim_algo4.png)

![prim_algo5](/usr/local/src/github/hanjingo/doc/ALGO/res/prim_algo5.png)

![prim_algo6](/usr/local/src/github/hanjingo/doc/ALGO/res/prim_algo6.png)

![prim_algo7](/usr/local/src/github/hanjingo/doc/ALGO/res/prim_algo7.png)

![prim_algo8](/usr/local/src/github/hanjingo/doc/ALGO/res/prim_algo8.png)

![prim_algo9](/usr/local/src/github/hanjingo/doc/ALGO/res/prim_algo9.png)

![prim_algo10](/usr/local/src/github/hanjingo/doc/ALGO/res/prim_algo10.png)

![prim_algo11](/usr/local/src/github/hanjingo/doc/ALGO/res/prim_algo11.png)

![prim_algo12](/usr/local/src/github/hanjingo/doc/ALGO/res/prim_algo12.png)

Implement:

```c++
// A utility function to find the vertex with
// minimum key value, from the set of vertices
// not yet included in MST
int min_key(vector<int> &key, vector<bool> &mst_set) 
{
  
    // Initialize min value
    int min = INT_MAX, min_index;
    for (int v = 0; v < mst_set.size(); v++)
        if (mst_set[v] == false && key[v] < min)
            min = key[v], min_index = v;

    return min_index;
}

// Function to construct and print MST for
// a graph represented using adjacency
// matrix representation
void prim_mst(vector<vector<int>> &graph) 
{
    
    int V = graph.size();
  
    // Array to store constructed MST
    vector<int> parent(V);

    // Key values used to pick minimum weight edge in cut
    vector<int> key(V);

    // To represent set of vertices included in MST
    vector<bool> mst_set(V);

    // Initialize all keys as INFINITE
    for (int i = 0; i < V; i++)
        key[i] = INT_MAX, mst_set[i] = false;

    // Always include first 1st vertex in MST.
    // Make key 0 so that this vertex is picked as first
    // vertex.
    key[0] = 0;
  
    // First node is always root of MST
    parent[0] = -1;

    // The MST will have V vertices
    for (int count = 0; count < V - 1; count++) 
    {
        
        // Pick the minimum key vertex from the
        // set of vertices not yet included in MST
        int u = min_key(key, mst_set);

        // Add the picked vertex to the MST Set
        mst_set[u] = true;

        // Update key value and parent index of
        // the adjacent vertices of the picked vertex.
        // Consider only those vertices which are not
        // yet included in MST
        for (int v = 0; v < V; v++)
            // graph[u][v] is non zero only for adjacent
            // vertices of m mst_set[v] is false for vertices
            // not yet included in MST Update the key only
            // if graph[u][v] is smaller than key[v]
            if (graph[u][v] && mst_set[v] == false && graph[u][v] < key[v])
                parent[v] = u, key[v] = graph[u][v];
    }

    // Print the constructed MST
    print_mst(parent, graph);
}
```

Complexity:

| Scenario     | Time Complexity | Space Complexity |
| :----------- | :-------------- | :--------------- |
| Best Case    | $O(|V|^2)$      | $O(|V|)$         |
| Average Case | $O(|V|^2)$      | $O(|V|)$         |
| Worst Case   | $O(|V|^2)$      | $O(|V|)$         |

For this adjacency-matrix implementation, `min_key` scans all vertices in $O(|V|)$ and is called $|V|-1$ times. The inner update loop also scans all vertices each iteration, giving total time $O(|V|^2)$. Auxiliary space is $O(|V|)$ for `parent`, `key`, and `mst_set` (excluding the input graph matrix).

### Kruskal’s Algorithm

A minimum spanning tree (MST) or minimum weight spanning tree for a weighted, connected, and undirected graph is a [spanning tree](https://www.geeksforgeeks.org/dsa/spanning-tree/) (no cycles and connects all vertices) that has minimum weight. The weight of a spanning tree is the sum of all edges in the tree.  

Algorithm:

1. Sort all the edges in a non-decreasing order of their weight. 
2. Pick the smallest edge. Check if it forms a cycle with the spanning tree formed so far. If the cycle is not formed, include this edge. Otherwise, discard it. It uses the Disjoint Sets to detect cycles.
3. Repeat step 2 until there are (V-1) edges in the spanning tree.

Example:

![kruskal_algo1](/usr/local/src/github/hanjingo/doc/ALGO/res/kruskal_algo1.png)

![kruskal_algo2](/usr/local/src/github/hanjingo/doc/ALGO/res/kruskal_algo2.png)

![kruskal_algo3](/usr/local/src/github/hanjingo/doc/ALGO/res/kruskal_algo3.png)

![kruskal_algo4](/usr/local/src/github/hanjingo/doc/ALGO/res/kruskal_algo4.png)

![kruskal_algo5](/usr/local/src/github/hanjingo/doc/ALGO/res/kruskal_algo5.png)

![kruskal_algo6](/usr/local/src/github/hanjingo/doc/ALGO/res/kruskal_algo6.png)

![kruskal_algo7](/usr/local/src/github/hanjingo/doc/ALGO/res/kruskal_algo7.png)

![kruskal_algo8](/usr/local/src/github/hanjingo/doc/ALGO/res/kruskal_algo8.png)

![kruskal_algo9](/usr/local/src/github/hanjingo/doc/ALGO/res/kruskal_algo9.png)

![kruskal_algo10](/usr/local/src/github/hanjingo/doc/ALGO/res/kruskal_algo10.png)

Implement:

```c++
bool comparator(std::vector<int> &a,std::vector<int> &b)
{
   return a[2] < b[2]; 
}

int find(int i, std::vector<int> &parent) 
{
    return (parent[i] == i) ? i : (parent[i] = find(parent[i], parent));
}

void unite(int x, int y, std::vector<int> &parent, std::vector<int> &rank) 
{
    int s1 = find(x, parent), s2 = find(y, parent);
    if (s1 == s2) 
        return;

    if (rank[s1] < rank[s2]) 
        parent[s1] = s2;
    else if (rank[s1] > rank[s2]) 
        parent[s2] = s1;
    else 
        parent[s2] = s1;
        rank[s1]++;
}

int kruskals_mst(int V, std::vector<std::vector<int>> &edges) 
{
    std::vector<int> parent, rank;
    parent.resize(V);
    rank.resize(V);
    for (int i = 0; i < V; i++) 
    {
        parent[i] = i;
        rank[i] = 1;
    }

    // Sort all edges
    std::sort(edges.begin(), edges.end(), comparator);
    
    // Traverse edges in sorted order
    int cost = 0, count = 0;
    for (auto &e : edges) 
    {
        int x = e[0], y = e[1], w = e[2];
        // Make sure that there is no cycle
        if (find(x, parent) == find(y, parent)) 
            continue;

        unite(x, y, parent, rank);
        cost += w;
        if (++count == V - 1) 
            break;
    }
    return cost;
}
```

Complexity:

| Scenario     | Time Complexity | Space Complexity |
| :----------- | :-------------- | :--------------- |
| Best Case    | $O(|E|\log|E|)$ | $O(|V|)$         |
| Average Case | $O(|E|\log|E|)$ | $O(|V|)$         |
| Worst Case   | $O(|E|\log|E|)$ | $O(|V|)$         |

This implementation always sorts all edges first, which costs $O(|E|\log|E|)$ and dominates runtime. The union-find operations (`find` with path compression and `unite` with rank) are nearly constant amortized per edge, so traversal after sorting is $O(|E|\,\alpha(|V|))$. Extra memory is $O(|V|)$ for `parent` and `rank` (excluding the input edge list).

---



## Cycles Detect

### Detect Cycle In a Directed Graph By Using DFS

Algorithms:

In DFS, we go as deep as possible from a starting node. If during this process, we reach a node that we’ve already visited in the same DFS path, it means we’ve gone back to an ancestor — this shows a cycle exists.

Examples:

![dfs_detect_cycle_in_directed_graph1](res/dfs_detect_cycle_in_directed_graph1.png)

![dfs_detect_cycle_in_directed_graph2](res/dfs_detect_cycle_in_directed_graph2.png)

![dfs_detect_cycle_in_directed_graph3](res/dfs_detect_cycle_in_directed_graph3.png)

![dfs_detect_cycle_in_directed_graph4](res/dfs_detect_cycle_in_directed_graph4.png)

![dfs_detect_cycle_in_directed_graph5](res/dfs_detect_cycle_in_directed_graph5.png)

![dfs_detect_cycle_in_directed_graph6](res/dfs_detect_cycle_in_directed_graph6.png)

![dfs_detect_cycle_in_directed_graph7](res/dfs_detect_cycle_in_directed_graph7.png)

Implement:

```c++
// Utility DFS function to detect cycle in a directed graph
bool is_cycle_by_dfs_util(
    vector<vector<int>>& adj, 
    int u, 
    vector<bool>& visited, 
    vector<bool>& rec_stack) 
{
    
    // node is already in recursion stack cycle found
    if (rec_stack[u]) return true;  
    
    // already processed no need to visit again
    if (visited[u]) return false;   

    visited[u] = true;
    rec_stack[u] = true;

    // Recur for all adjacent nodes
    for (int v : adj[u])
        if (is_cycle_by_dfs_util(adj, v, visited, rec_stack))
            return true;

    // remove from recursion stack before backtracking
    rec_stack[u] = false; 
    return false;
}

// Function to detect cycle in a directed graph
bool is_cycle_by_dfs(vector<vector<int>>& adj) 
{
    int V = adj.size();
    vector<bool> visited(V, false);
    vector<bool> rec_stack(V, false);

    // Run DFS from every unvisited node
    for (int i = 0; i < V; i++) 
        if (!visited[i] && is_cycle_by_dfs_util(adj, i, visited, rec_stack))
            return true;

    return false;
}
```

Complexity:

| Scenario     | Time Complexity | Space Complexity |
| :----------- | :-------------- | :--------------- |
| Best Case    | $O(|V|)$        | $O(|V|)$         |
| Average Case | $O(|V| + |E|)$  | $O(|V|)$         |
| Worst Case   | $O(|V| + |E|)$  | $O(|V|)$         |

In this DFS-based cycle detection (adjacency list), each vertex is marked at most once and each directed edge is explored at most once before completion, so the full traversal cost is $O(|V| + |E|)$. The vectors `visited` and `rec_stack` use $O(|V|)$ memory, and recursive depth can be up to $|V|$ in the worst case. Because these vectors are initialized for all vertices, best-case running time is still $O(|V|)$ even if a cycle is detected quickly.

### Detect Cycle In an Undirected Graph By Using DFS

Algorithm:

When we start a DFS from a node, we visit all its connected neighbors one by one. If during this traversal, we reach a node that has already been visited before, it indicates that there might be a cycle, since we’ve come back to a previously explored vertex.

Example:

![dfs_detect_cycle_in_undirected_graph1](res/dfs_detect_cycle_in_undirected_graph1.png)

![dfs_detect_cycle_in_undirected_graph2](res/dfs_detect_cycle_in_undirected_graph2.png)

![dfs_detect_cycle_in_undirected_graph3](res/dfs_detect_cycle_in_undirected_graph3.png)

![dfs_detect_cycle_in_undirected_graph4](res/dfs_detect_cycle_in_undirected_graph4.png)

![dfs_detect_cycle_in_undirected_graph5](res/dfs_detect_cycle_in_undirected_graph5.png)

Implement:

```c++
bool dfs(int v, vector<vector<int>> &adj, vector<bool> &visited, int parent)
{
    // Mark the current node as visited
    visited[v] = true;

    // Recur for all the vertices adjacent to this vertex
    for (int i : adj[v])
    {
        // If an adjacent vertex is not visited, 
        //then recur for that adjacent
        if (!visited[i])
        {
            if (dfs(i, adj, visited, v))
                return true;
        }
        else if (i != parent)
        {
            // If an adjacent vertex is visited and is not
            // parent of current vertex,
            // then there exists a cycle in the graph.
            return true;
        }
    }

    return false;
}

// Returns true if the graph contains a cycle, else false.
bool is_cycle(vector<vector<int>> &adj)
{
    int V= adj.size();
    // Mark all the vertices as not visited
    vector<bool> visited(V, false);

    for (int u = 0; u < V; u++)
    {
        if (!visited[u])
        {
            if (dfs(u, adj, visited, -1))
                return true;
        }
    }

    return false;
}
```

Complexity:

| Scenario     | Time Complexity | Space Complexity |
| :----------- | :-------------- | :--------------- |
| Best Case    | $O(|V|)$        | $O(|V|)$         |
| Average Case | $O(|V| + |E|)$  | $O(|V|)$         |
| Worst Case   | $O(|V| + |E|)$  | $O(|V|)$         |

In this DFS-based undirected cycle check (adjacency list), each vertex is visited at most once and each undirected edge is examined at most twice (once from each endpoint), so full traversal is $O(|V| + |E|)$. The `visited` array requires $O(|V|)$ memory, and recursion depth can reach $|V|$ in the worst case, giving $O(|V|)$ auxiliary space. Since `visited` is initialized for all vertices, best-case time remains $O(|V|)$ even if a cycle is found early.

### Detect a Negative Weight Cycle By Using Bellman-Ford

Algorithm:

1. Initialize a distance array `dist` with all values as `0`
2. Perform edge relaxation **n - 1) times**:
   - For each edge `(u, v, wt)`
   - If `dist[u] + wt < dist[v]`, update `dist[v]`
3. Run one more iteration over all edges:
   - If any edge still relaxes → return `1` (negative cycle exists)
4. If no relaxation happens → return `0`

Implement:

```c++
bool is_negative_cycle(int n, vector<vector<int>> &edges)
{
    vector<int> dist(n, 0);
    // Relax edges n-1 times
    for (int i = 0; i < n - 1; i++)
    {
        for (auto edge : edges)
        {
            int u = edge[0];
            int v = edge[1];
            int wt = edge[2];

            if (dist[u] + wt < dist[v])
            {
                dist[v] = dist[u] + wt;
            }
        }
    }

    // Check for negative cycle
    for (auto edge : edges)
    {
        int u = edge[0];
        int v = edge[1];
        int wt = edge[2];

        if (dist[u] + wt < dist[v])
        {
            // negative cycle found
            return true; 
        }
    }
    return false; 
}
```

Complexity:

| Scenario     | Time Complexity | Space Complexity |
| :----------- | :-------------- | :--------------- |
| Best Case    | $O(|V||E|)$     | $O(|V|)$         |
| Average Case | $O(|V||E|)$     | $O(|V|)$         |
| Worst Case   | $O(|V||E|)$     | $O(|V|)$         |

This implementation performs exactly $|V|-1$ full relaxation passes over all edges, followed by one additional full pass to detect whether any edge can still relax. Therefore, total work is proportional to $|V| \cdot |E|$ in all cases. Auxiliary space is $O(|V|)$ for the `dist` array.

---



## Summary

### BFS vs DFS

![bfs_vs_dfs](res/bfs_vs_dfs.png)

|        Parameters         |                             BFS                              |                             DFS                              |
| :-----------------------: | :----------------------------------------------------------: | :----------------------------------------------------------: |
|      **Stands for**       |             BFS stands for Breadth First Search.             |              DFS stands for Depth First Search.              |
|    **Data Structure**     | BFS(Breadth First Search) uses Queue data structure for finding the shortest path. |      DFS(Depth First Search) uses Stack data structure.      |
|      **Definition**       | BFS is a traversal approach in which we first walk through all nodes on the same level before moving on to the next level. | DFS is also a traversal approach in which the traverse begins at the root node and proceeds through the nodes as far as possible until we reach the node with no unvisited nearby nodes. |
| **Conceptual Difference** |             BFS builds the tree level by level.              |          DFS builds the tree sub-tree by sub-tree.           |
|     **Approach used**     |    It works on the concept of FIFO (First In First Out).     |     It works on the concept of LIFO (Last In First Out).     |
|     **Suitable for**      | BFS is more suitable for searching vertices closer to the given source. | DFS is more suitable when there are solutions away from source. |
|     **Applications**      | BFS is used in various applications such as bipartite graphs, shortest paths, etc. If weight of every edge is same, then BFS gives shortest path from source to every other vertex. | DFS is used in various applications such as acyclic graphs and finding strongly connected components etc. There are many applications where both BFS and DFS can be used like Topological Sorting, Cycle Detection, etc. |

### Prim's Algorithm vs Kruskal's Algorithm

|          Feature          |                       Prim's Algorithm                       |                    Kruskal's Algorithm                    |
| :-----------------------: | :----------------------------------------------------------: | :-------------------------------------------------------: |
|         Approach          |       Vertex-based, grows the MST one vertex at a time       |   Edge-based, adds edges in increasing order of weight    |
|      Data Structure       |                  Priority queue (min-heap)                   |                 Union-Find data structure                 |
|   Graph Representation    |              Adjacency matrix or adjacency list              |                         Edge list                         |
|      Initialization       |               Starts from an arbitrary vertex                |    Starts with all vertices as separate trees (forest)    |
|      Edge Selection       | Chooses the minimum weight edge from the connected vertices  |      Chooses the minimum weight edge from all edges       |
|     Cycle Management      |      Not explicitly managed; grows connected component       |              Uses Union-Find to avoid cycles              |
|        Complexity         | O(V^2) for adjacency matrix, O((E + V) log V) with a priority queue |       O(E log E) or O(E log V), due to edge sorting       |
|       Suitable for        |                         Dense graphs                         |                       Sparse graphs                       |
| Implementation Complexity |              Relatively simpler in dense graphs              |           More complex due to cycle management            |
|        Parallelism        |                   Difficult to parallelize                   |  Easier to parallelize edge sorting and union operations  |
|       Memory Usage        |                More memory for priority queue                |       Less memory if edges can be sorted externally       |
|     Example Use Cases     |      Network design, clustering with dense connections       | Road networks, telecommunications with sparse connections |
|      Starting Point       |                  Requires a starting vertex                  |   No specific starting point, operates on global edges    |
|        Optimal for        |        Dense graphs where the adjacency list is used         |      Sparse graphs, where the edge list is efficient      |

---



## Reference

[1] Thomas H.Cormen; Charles E.Leiserson; Ronald L. Rivest; Clifford Stein. Introduction to Algorithms. 3ED

[2] Mark Allen Weiss. Data Structures and Algorithm Analysis in C++. 4ED

[3] [Graph Algorithms](https://www.geeksforgeeks.org/dsa/graph-data-structure-and-algorithms/)

[4] [Representation of Graph](https://www.geeksforgeeks.org/dsa/graph-and-its-representations/)

[5] [Topological Sorting](https://www.geeksforgeeks.org/dsa/topological-sorting/)

[6] [Types of Graphs with Examples](https://www.geeksforgeeks.org/dsa/graph-types-and-applications/)

[7] [Prim’s Algorithm for Minimum Spanning Tree (MST)](https://www.geeksforgeeks.org/dsa/prims-minimum-spanning-tree-mst-greedy-algo-5/)

[8] [Difference between Prim's and Kruskal's algorithm for MST](https://www.geeksforgeeks.org/dsa/difference-between-prims-and-kruskals-algorithm-for-mst/)

