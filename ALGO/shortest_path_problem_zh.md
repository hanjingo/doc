

中文版 | [English](shortest_path_problem.md)

# 最短路径算法

[TOC]




## Dijkstra算法

Dijkstra算法按阶段进行，在每个阶段，Dijkstra算法选择一个顶点$v$，它在所有unknown顶点中居于最小的$d_v$，同时算法声明从$s$到$v$的最短路径是known的。阶段的其余部分由$d_w$值的更新工作组成。

在无权的情形，若$d_w = \infin$则置$d_w = d_v + 1$。因此，若顶点$v$能提供一条更短路径，则我们本质上就降低了$d_w$的值。如果对加权的情形应用同样的逻辑，那么当$d_w$的新值$d_v + c_{v,w}$是一个改进的值时，就置$d_w = d_v + c_{v, w}$。简言之，使用通向$w$路径上的顶点$v$是不是一个好主意由算法决定。原始的值$d_w$是不用$v$的值；上面所算出的值是使用$v$​（和仅仅为known的顶点）的最便宜的路径。



## AStar算法

A*搜索算法（英语：A* search algorithm）是一种在图形平面上，有多个节点的路径，求出最低通过成本的算法。

![astar_progress_animation](res/astar_progress_animation.gif)

*A*搜索算法的演示图*

对于有障碍物的情况下，Dijkstra算法运行得较慢；A star算法就是把启发式方法（heuristic approaches）如BFS，和常规方法如Dijsktra算法结合在一起的算法。

该算法综合了最良优先搜索和戴克斯特拉算法的优点：在进行启发式搜索提高算法效率的同时，可以保证找到一条最优路径（需要评估函数满足单调性）。

A*算法的估算函数：
$$
f(n) = g(n) + h(n)
$$

- $g(n)$：表示从起点到任意顶点$n$的实际距离。
- $h(n)$：表示任意顶点$n$到目标顶点的估算距离。

上面的公式需要遵循以下特性：

- 如果$g(n)$为0，即只计算任意顶点$n$到目标的评估函数$h(n)$，而不计算起点到顶点$n$的距离，则算法转化为使用贪心策略的最良优先搜索，速度最快，但可能得不出最优解；
- 如果$h(n)$不大于顶点$n$到目标顶点的实际距离，则一定可以求出最优解，而且$h(n)$越小，需要计算的节点越多，算法效率越低。
- 如果$h(x)$为0，即只需求出起点到任意顶点$n$的最短路径$g(n)$，而不计算任何评估函数$h(n)$，则转换为最短路问题，此时需要计算最多的顶点。



## 参考

[1] [美]Mark Allen Weiss.数据结构与算法分析-C++描述.3ED

[2] [维基百科/A*搜索算法](https://zh.wikipedia.org/zh-cn/A*%E6%90%9C%E5%B0%8B%E6%BC%94%E7%AE%97%E6%B3%95)

[3] [A星算法详解(个人认为最详细,最通俗易懂的一个版本)](https://blog.csdn.net/hitwhylz/article/details/23089415)

[4] [A星算法（A* A Star algorithm）原理以及代码实例，超详细，超简单，大白话谁都能看懂](https://blog.csdn.net/qq_41816368/article/details/134093683)

[5] [A Star Algorithm 总结与实现](https://scm_mos.gitlab.io/motion-planner/a-star/)
