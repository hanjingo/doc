[中文版](minimum_spanning_tree_zh.md) | English

# Minimum Spanning Tree

[TOC]



Informally, a minimum spanning tree of an undirected graph G is a tree formed from graph edges that connects all the vertices of G at the lowest total cost. A minimum spanning tree exists if and only if G is connected.

![minimum_spanning_tree](res/minimum_spanning_tree.png)

*graph G and it's mimimum spanning trees*

## Prim's Algorithm

Prim’s algorithm is a Greedy algorithm like Kruskal's algorithm. This algorithm always starts with a single node and moves through several adjacent nodes, in order to explore all of the connected edges along the way.

### Implement

Algorithm:

1. The algorithm starts with an empty spanning tree.
2. The idea is to maintain two sets of vertices. The first set contains the vertices already included in the MST, and the other set contains the vertices not yet included.
3. At every step, it considers all the edges that connect the two sets and picks the minimum-weight edge from these edges. After picking the edge, it moves the other endpoint of the edge to the set containing the MST. 

Example:

![prim_algo1](res/prim_algo1.png)

![prim_algo2](res/prim_algo2.png)

![prim_algo3](res/prim_algo3.png)

![prim_algo4](res/prim_algo4.png)

![prim_algo5](res/prim_algo5.png)

![prim_algo6](res/prim_algo6.png)

![prim_algo7](res/prim_algo7.png)

![prim_algo8](res/prim_algo8.png)

![prim_algo9](res/prim_algo9.png)

![prim_algo10](res/prim_algo10.png)

![prim_algo11](res/prim_algo11.png)

![prim_algo12](res/prim_algo12.png)





## Reference

[1] [Prim’s Algorithm for Minimum Spanning Tree (MST)](https://www.geeksforgeeks.org/dsa/prims-minimum-spanning-tree-mst-greedy-algo-5/)



---







## Prim's Algorithm

One way to compute a minimum spanning tree is to grow the tree in successive stages. In each stage, one node is picked as the root, and we add an edge, and thus an associated vertex, to the tree.

![prim_example1](res/prim_example1.png)

*在每一步之后的Prim算法*

![prim_example2](res/prim_example2.png)

*Initial configuration of table used in Prim's algorithm*

![prim_example3](res/prim_example3.png)

*The table after $v_1$ is declared known*

![prim_example4](res/prim_example4.png)

*The table after $v_4$* is declared known

![prim_example5](res/prim_example5.png)

*The table after $v_2$ and $v_3$are ceclared known*

![prim_example6](res/prim_example6.png)

*The table after $v_7$* is declared known

![prim_example7](res/prim_example7.png)

*The table after $v_6$ and $v_5$ are selected (Prim's algorithm terminates)*



### Kruskal's Algorithm

A second greedy strategy is to continually select the edges in order of smallest weight and accept an edge if it does not cause a cycle.

![Kruskal_example1](res/Kruskal_example1.png)

*Action of Kruskal's algorithm on G*

![Kruskal_example2](res/Kruskal_example2.png)

Formally, Kruskal's algorithm maintains a forest--a collection of trees. Initially, there are $|V|$ single-node trees. Adding an edge merges two trees into one. When the algorithm terminates, there is only one tree, and this is the minimum spanning tree.

### Example.Pseudocode for Kruskal's algorithm

```c++
void Graph::kruskal()
{
    int edgesAccepted = 0;
    DisjSet ds(NUM_VERTICES);
    PriorityQueue<Edge> pq(getEdges());
    Edge e;
    Vertex u, v;
    
    while (edgesAccepted < NUM_VERTICES - 1)
    {
        pq.deleteMin(e);  // Edge e = (u, v)
        SetType uset = ds.find(u);
        SetType vset = ds.find(v);
        if (uset != vset)
        {
            // Accept the edge
            edgesAccepted++;
            ds.unionSets(uset, vset);
        }
    }
}
```

The worst-case running time of this algorithm is $O(|E|log|E|)$, which is dominated by the heap operations. Notice that since $|E|=O(|V|^2)$, this running time is actually $O(|E|log|V|)$. In practice, the algorithm is much faster than this time bound would indicate.
