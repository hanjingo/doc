# 最小生成树


<!-- vim-markdown-toc GFM -->

* [Prim算法](#prim算法)
* [Kruskal算法](#kruskal算法)
    - [实现](#实现)

<!-- vim-markdown-toc -->



`最小生成树(minimum spanning tree)` 

![minimum_spanning_tree](res/minimum_spanning_tree.png)

*图G和它的最小生成树*



## Prim算法

计算最小生成树的一种方法是使其连续地一步步长成。在每一步，都要把一个结点当作根并往上加边，这样也就把相关联地顶点加到增长中的树上了。

![prim_example1](res/prim_example1.png)

*在每一步之后的Prim算法*

![prim_example2](res/prim_example2.png)

*在Prim算法中使用的表的初始状态*

![prim_example3](res/prim_example3.png)

*在$v_1$声明为已知（known）后的表*

![prim_example4](res/prim_example4.png)

*在$v_4$声明为已知后的表*

![prim_example5](res/prim_example5.png)

*在$v_2$和$v_3$先后声明为已知后的表*

![prim_example6](res/prim_example6.png)

*在$v_7$声明为已知后的表*

![prim_example7](res/prim_example7.png)

*在$v_6$和$v_5$选取后的表（Prim算法终止）*



## Kruskal算法

连续地按照最小的权选择边，并且当所选的边不产生回路时就把它作为取定的边。

![Kruskal_example1](res/Kruskal_example1.png)

*Kruskal算法施于图G的过程*

![Kruskal_example2](res/Kruskal_example2.png)

*Kruskal算法是在处理一个森林 - 树的集合。开始的时候，存在$|V|$棵单节点树，而添加一边则将两棵树合并成一棵树。当算法终止的时候，就只有一棵树了，这棵树就是最小生成树。*

### 实现

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

该算法的最坏情形运行时间为$O(|E|log|E|)$，它受堆操作控制。注意，由于$|E|=O(|V|^2)$，因此这个运行时间实际上是$O(|E|log|V|)$。在实践中，该算法要比这个时间界指示的时间快得多。
