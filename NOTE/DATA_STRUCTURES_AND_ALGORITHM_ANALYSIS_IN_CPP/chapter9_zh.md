# 第九章 图论算法

[TOC]



## 9.1 若干定义

- `图（grph）` $G = (V, E)$由`顶点(vertex)`的集$V$和`边（edge）`的集$E$组成。
- `边` 也叫`弧（arc）`，图的每一个点对$(v, w)，其中v, w \in V$。
- `有向图（digraph）`点对有序的图。
- `路径（path）` 一个顶点序列$w_1$, $w_2$, $w_3$, ..., $w_N$，其中$(w_i, w_{i+1}) \in E, 1 \leqslant i < N$。
- `回路（cycle）` 有向图中满足$w_1 = w_N$且长至少为1的一条路径。
- `无环（acyclic）` 没有回路的有向图（简称：DAG）；
- `连通无向图` 无向图中从每一个顶点到每个其他顶点都存在一条路径，也称作强连通的（strongly connected）。
- `弱连通(weakly connected)有向图` 有向图不是强连通的，但是它的基础图（underlying graph，即其弧上去掉方向所形成的图）是联通的 。
- `完全图（complete graph）` 每一对顶点间都存在一条边的图。

![9_1](res/9_1.png)

*一个有向图*

表示图的方法：

- `邻接矩阵（adjacent matrix）表示法` 

  使用二维数组，对于每条边$(u, v)$，置$A[u][v] = true$；否则，数组的项就是false。如果边有一个权，那么可以置$A[u][v]$等于该权，而使用一个很大或者很小的权作为标记表示不存在的边。

  这种表示的优点是非常简单，但是，它的空间需求则为$\Theta(|V|^2)$，如果图的边不是很多，那么这种表示的代价非常大；邻接矩阵适合于稠密（dense）的图：$|E| = \Theta(|V|^2)$。

- `邻接表（adjacency list）`

  对于每一个顶点，使用一个表存放所有邻接的顶点；此时的空间需求为$O(|E|+|V|)$，它对于图的大小而言是线性的。

  ![9_2](res/9_2.png)

  *图的邻接表表示*



## 9.2 拓扑排序

`拓扑排序（topological sort）` 是对有向无环图的顶点的一种排序，它使得如果存在一条从$v_i$到$v_j$的路径，那么在排序中$v_j$出现在$v_i$的后面。

![9_3](res/9_3.png)

*表示课程结构的无环图*

![9_4](res/9_4.png)*一个无环图*

```c++
// 简单的拓扑排序伪代码
void Graph::topsort()
{
	for (int counter = 0; counter < NUM_VERTICES; counter++)
  {
  	Vertex v = findNewVertexOfIndegreeZero(); // 扫描数组，寻找一个尚未被分配拓扑编号的入度为0的顶点
    if (v == NOT_A_VERTEX)
      throw CycleFoundException();
    v.topNum = counter;
    for each Vertex w adjacent to v
      w.indegree--;
  }
}
```

![9_6](res/9_6.png)

*对上图中的图应用拓扑排序的结果*



## 9.3 最短路径算法

输入是一个加权图：与每条边$(v_i, v_j)$相联系的是穿越该边的代价（或称为值）$c_{i,j}$。一条路径$v_1 v_2 ... v_N$的值是$\sum_{i=1}^{N-1} c_{i,i+1}$叫做`加权路径长（weighted path length）`。而`无权路径长（unweighted path length）`只是路径上的边数，即$N-1$。

```c++
// 施行拓扑排序的伪代码
void Graph::topsort()
{
	Queue<Vertex> q;
  int counter = 0;
  
  q.makeEmpty();
  for each Vertex v
    if (v.indegree == 0)
      q.enqueue(v);
  
  while (!q.isEmpty())
  {
  	Vertex v = q.dequeue();
    v.topNum = ++counter;
    
    for each Vertex w adjacent to v
      if (--w.indegree == 0)
        q.enqueue(w);
  }
  
  if (counter != NUM_VERTICES)
    throw CycleFoundException();
}
```

**单源最短路径问题** 给定一个加权图$G=(V, E)$和一个特定顶点$s$作为输入，找出从$s$到$G$中每一个其他顶点的最短加权路径。

![9_8](res/9_8.png)

*有向图G*

![9_9](res/9_9.png)

*带有负值回路的图*

### 无权最短路径

`广度优先搜索（breadth-first search）` 该方法按层处理顶点：距开始点最近的那些顶点首先被求值，而最远的那些顶点最后被求值。

例：

![9_10](res/9_10.png)

*一个无权有向图G*

![9_11](res/9_11.png)

*将开始结点标记为通过0条边可以到达的结点后的图*

![9_12](res/9_12.png)

*找出所有从s出发路径长为1的顶点之后的图*

![9_13](res/9_13.png)

*找出所有从s出发路径长为2的顶点之后的图*

![9_14](res/9_14.png)

*最后的最短路径*

```c++
// 无权最短路径算法的伪代码
void Graph::unweighted(Vertex s)
{
	for each Vertex v
  {
  	v.dist = INFINITY;
    v.known = false;
  }
  s.dist = 0;
  for (int currDist = 0; currDist < NUM_VERTICES; currDist++)
    for each Vertex v
      if (!v.known && v.dist == currDist)
      {
      	v.known = true;
        for each Vertex w adjacent to v
          if (w.dist == INFINITY)
          {
          	w.dist = currDist + 1;
            w.path = v;
          }
      }
}
```

![9_17](res/9_17.png)

*使用上面伪代码的无权最短路径算法的坏情形*

```c++
// 无权最短路径算法的伪代码（使用邻接表）
void Graph::unweighted(Vertex s)
{
	Queue<Vertex> q;
  
  for each Vertex v
    v.dist = INFINITY;
  
  s.dist = 0;
  q.enqueue(s);
  
  while (!q.isEmpty())
  {
  	Vertex v = q.dequeue();
    for each Vertex w adjacent to v
      if (w.dist == INFINITY)
      {
      	w.dist = v.dist + 1;
        w.path = v;
        q.enqueue(w);
      }
  }
}
```

![9_19](res/9_19.png)

*无权最短路径算法期间数据如何变化*

### Dijkstra算法

Dijkstra算法按阶段进行，在每个阶段，Dijkstra算法选择一个顶点$v$，它在所有unknown顶点中居于最小的$d_v$，同时算法声明从$s$到$v$的最短路径是known的。阶段的其余部分由$d_w$值的更新工作组成。

在无权的情形，若$d_w = \infin$则置$d_w = d_v + 1$。因此，若顶点$v$能提供一条更短路径，则我们本质上就降低了$d_w$的值。如果对加权的情形应用同样的逻辑，那么当$d_w$的新值$d_v + c_{v,w}$是一个改进的值时，就置$d_w = d_v + c_{v, w}$。简言之，使用通向$w$路径上的顶点$v$是不是一个好主意由算法决定。原始的值$d_w$是不用$v$的值；上面所算出的值是使用$v$（和仅仅为known的顶点）的最便宜的路径。

例：

![9_20](res/9_20.png)

*有向图G*

![9_21](res/9_21.png)

*用于Dijkstra算法的表的初始配置*

![9_22](res/9_22.png)

*在$v_1$被声明为known后的表*

![9_23](res/9_23.png)

*在$v_4$被声明为known后*

![9_24](res/9_24.png)

*在$v_2$被声明为known后*

![9_25](res/9_25.png)

*在$v_5$与$v_3$被声明为known后*

![9_26](res/9_26.png)

*在$v_7$被声明为known后*

![9_27](res/9_27.png)

*在$v_6$被声明为known之后，算法终止*

![9_28](res/9_28.png)

*Dijkstra算法的各个阶段*

```c++
// Dijkstra算法伪代码
struct Vertex
{
	List     adj;
  bool     known;
  DistType dist;
  Vertex   path;
};

void Graph::printPath(Vertex v)
{
	if (v.path != NOT_A_VERTEX)
  {
  	printPath(v.path);
    cout << " to ";
  }
  cout << v;
}

void Graph::dijkstra(Vertex s)
{
	for each Vertex v
  {
  	v.dist = INFINITY;
    v.known = false;
  }
  
  s.dist = 0;
  
  for (;;)
  {
  	Vertex v = smallest unknown distance vertex;
    if (v == NOT_A_VERTEX)
      break;
    v.known = true;
    
    for each Vertex w adjacent to v
      if (!w.known)
        if (v.dist + cvw < w.dist)
        {
        	// Update w
          decrease(w.dist to v.dist + cvw);
          w.path = v;
        }
  }
}
```

### 具有负边值的图

```c++
// 具有负边值的加权最短路径算法的伪代码
void Graph::weightedNegative(Vertex s)
{
	Queue<Vertex> q;
  
  for each Vertex v
    v.dist = INFINITY;
  
  s.dist = 0;
  q.enqueue(s);
  
  while (!q.isEmpty())
  {
  	Vertex v = q.dequeue();
    for each Vertex w adjacent to v
      if (v.dist + cvw < w.dist)
      {
      	w.dist = v.dist + cvw;
        w.path = v;
        if (w is not already in q)
          q.enqueue(w);
      }
  }
}
```

### 无环图

`关键路径分析（critical path analysis）`

`动作结点图（activity-node graph）`

`事件结点图（event-node graph）`

![9_33](res/9_33.png)

*动作结点图*

![9_34](res/9_34.png)

*事件结点图*

事件结点图中每个事件的最早完成时间：

![9_35](res/9_35.png)

*最早完成时间*

$EC_1 = 0$

$EC_w = \underset{(v,w) \in E}{max} (EC_v + C_{v,w})$

计算能够完成而不影响最后完成时间的最晚时间$LC_i$：

![9_36](res/9_36.png)

*最晚完成时间*

$LC_n = EC_n$

$LC_v = min(LC_w - c_{v,w})$

![9_37](res/9_37.png)

*最早完成时间，最晚完成时间和松弛时间*

每条边的`松弛时间（slack time）`代表对应动作可以被延迟而不推迟整体完成的时间量：

$Slack_{(v, w)} = LC_w - EC_v -c_{v,w}$

### 所有顶点对的最短路径

### 最短路径举例

```c++
// 查找字梯的C++程序
map<string, string> findChain(const map<string, vector<string> >& adjacentWords, const string& first)
{
  map<string, string> previousWord;
  queue<string> q;
  
  q.push(first);
  while (!q.empty())
  {
  	string current = q.front(); q.pop();
    
    map<string, vector<string> >::const_iterator itr;
    itr = adjacentWords.find(current);
    
    const vector<string>& adj = itr->second;
    for (int i = 0; i < adj.size(); i++)
      if (previousWord[adj[i]] == "")
      {
      	previousWord[adj[i]] == current;
        q.push(adj[i]);
      }
  }
  previousWord[first] = "";
  return previousWord;
}

vector<string> getChainFromPrevMap(const map<string, string>& previous, const string& second)
{
	vector<string> result;
  map<string, string>& prev = const_cast<map<string, string> &>(previous);
  
  for (string current = second; current != ""; current = prev[current])
    result.push_back(current);
  
  reverse(result.begin(), result.end());
  return result;
}
```



## 9.4 网络流问题

![9_39](res/9_39.png)

*一个图（左边）和它的最大流*

设给定边容量为$c_{v,w}$的有向图$G=(V, E)$。这些容量可以代表通过一个管道的水的流量或两个交叉路口之间马路上的交通流量。有两个顶点，一个是$s$，称为`源点（source）`，一个是$t$，称为`汇点（sink）`。对于任一条边$(v, w)$，最多有“流”的$c_{v,w}$个单位可以通过。在既不是源点$s$又不是汇点$t$的任一顶点$v$，总的进入的流必须等于总的发出的流。

**一个简单的最大流算法**

`残余图(residual graph)` 它表示对于每条边还能再添加上多少流。

`增长路径（augmenting path）`

![9_40](res/9_40.png)

*图，流图以及残余图的初始阶段*

![9_41](res/9_41.png)

*沿$s$, $b$, $d$, $t$加入2个单位的流后的$G$, $G_f$, $G_r$*

![9_42](res/9_42.png)

*沿$s$, $a$, $c$, $t$加入2个单位的流后的$G$, $G_f$, $G_r$*

![9_43](res/9_43.png)

*沿$s$, $a$, $d$, $t$加入1个单位的流后的$G$, $G_f$, $G_r$ -- 算法终止*

![9_44](res/9_44.png)

*如果初始动作是沿$s$, $a$, $d$, $t$加入3个单位的流得到$G$, $G_f$, $G_r$ -- 算法终止但解不是最优的*

![9_45](res/9_45.png)

*使用正确的算法沿$s$, $a$, $d$, $t$加入3个单位的流后的图*

![9_46](res/9_46.png)

*使用正确算法沿$s$, $b$, $d$, $a$, $c$, $t$加入2个单位的流后的图*

![9_47](res/9_47.png)

*经典的不好的增长情形*



## 9.5 最小生成树

`最小生成树(minimum spanning tree)` 

![9_50](res/9_50.png)

*图G和它的最小生成树*

### 9.5.1 Prim算法

计算最小生成树的一种方法是使其连续地一步步长成。在每一步，都要把一个结点当作根并往上加边，这样也就把相关联地顶点加到增长中的树上了。

![9_51](res/9_51.png)

*在每一步之后的Prim算法*

![9_52](res/9_52.png)

*在Prim算法中使用的表的初始状态*

![9_53](res/9_53.png)

*在$v_1$声明为已知（known）后的表*

![9_54](res/9_54.png)

*在$v_4$声明为已知后的表*

![9_55](res/9_55.png)

*在$v_2$和$v_3$先后声明为已知后的表*

![9_56](res/9_56.png)

*在$v_7$声明为已知后的表*

![9_57](res/9_57.png)

*在$v_6$和$v_5$选取后的表（Prim算法终止）*

### 9.5.2 Kruskal算法

连续地按照最小的权选择边，并且当所选的边不产生回路时就把它作为取定的边。

![9_58](res/9_58.png)

*Kruskal算法施于图G的过程*

![9_59](res/9_59.png)

*Kruskal算法是在处理一个森林 - 树的集合。开始的时候，存在$|V|$棵单节点树，而添加一边则将两棵树合并成一棵树。当算法终止的时候，就只有一棵树了，这棵树就是最小生成树。*

Kruskal算法伪代码：

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



## 9.6 深度优先搜索的应用

深度优先搜索模板（伪代码）：

```c++
void Graph::dfs(Vertex v)
{
    v.visited = true;
    for each Vertex w adjacent to v
        if (!w.visited)
            dfs(w);
}
```

### 9.6.1 无向图

![9_62](res/9_62.png)

*一个无向图*

![9_63](res/9_63.png)

*`深度优先生成树（depth-first spanning tree）`步骤：树的根是A，是第一个被访问到的顶点。图中的每一条边(v, w)都出现在树上。如果处理(v, w)时发现w已被标记，并且处理(w, v)时发现v也被标记，那么我们就画一条虚线，并称之为`后向边(back edge)`，标识这条“边”实际上不是树的一部分。*

### 9.6.2 双连通性

一个连通的无向图中的任一顶点删除之后，剩下的图仍然连通，那么这样的无向连通图就称为`双连通的（biconnected）`。

如果图不是双连通的，那么，将其删除后图不再连通的那些顶点叫做`割点(articulation point)`。

![9_62](res/9_62.png)

*具有割点C和D的图*

![9_65](res/9_65.png)

*深度优先搜索提供了一种找出连通图中所有割点的线性时间算法：从图中任一顶点开始，执行深度优先搜索并在顶点被访问时给它们编号。对于每一个顶点$v$，我们称其前序编号为$Num(v)$。然后，对于深度优先搜索生成树上的每一个顶点$v$，计算编号最低的顶点，我们称之为$Low(v)$，该点可从$v$开始通过树的零边或多条边，且可能还有一条后向边（以该序）达到。*

![9_66](res/9_66.png)

*从C开始深度优先搜索所得到的深度优先树*

通过对深度优先生成树执行一次后序遍历有效地算出$Low$，根据$Low$地定义可知，$Low(v)$是以下三者中的最小者：

- $Num(v)$；
- 所有向右边$(v, w)$中地最低$Num(w)$；
- 树地所有边$(v, w)$中地最低$Low(w)$。

例，计算割点：

```c++
// 对顶点的Num赋值
void Graph::assignNum(Vertex v)
{
    v.num = counter++;
    v.visited = true;
    for each Vertex w adjacent to v
        if (!w.visited)
        {
            w.parent = v;
            assignNum(w);
        }
}

// 计算Low并检验其是否为割点的伪代码（忽略对根的检验）
void Graph::assignLow(Vertex v)
{
    v.low = v.num;
    for each Vertex w adjacent to v
    {
        if (w.num > v.num)
        {
            assignLow(w);
            if (w.low >= v.num)
                cout << v << " is an articulation point" << endl;
            v.low = min(v.low, w.low);
        }
        else
            if (v.parent != w)
                v.low = min(v.low, w.num);
    }
}
```

### 9.6.3 欧拉回路

![9_70](res/9_70.png)

![9_71](res/9_71.png)

![9_72](res/9_72.png)

![9_73](res/9_73.png)

![9_74](res/9_74.png)

![9_75](res/9_75.png)

例，使用“一笔画完”的方法，画上面的图：

```++
void Graph::findArt(Vertex v)
{
	v.visited = true;
	v.low = v.num = counter++; // Rule 1
	for each Vertex w adjacent to v
	{
		if (!w.visited) // Forward edge
		{
			w.parent = v;
			findArt(w);
			if (w.low >= v.num)
				cout << v << " is an articulation point" << endl;
			v.low = min(v.low, w.low); // Rule 3
		}
		else
			if (v.parent != w) // Back edge
				v.low = min(v.low, w.num); // Rule 2
	}
}
```

### 9.6.4 有向图

![9_76](res/9_76.png)

*一个有向图*

![9_77](res/9_77.png)

*对上图进行深度优先搜索*

### 查找强分支

![9_78](res/9_78.png)

*通过对上面的有向图的后续遍历所编号的$G_r$*

![9_79](res/9_79.png)

*$G_r$的深度优先搜索 - 强分支为{G}, {H, I, J}, {B, A, C, F}, {D}, {E}*



## 9.7 NP完全性介绍

### 9.7.1 难与易

计算基不可能解决碰巧发生的每一个问题，这些”不可能“解出的问题称为`不可判定问题(undecidable problem)`。

### 9.7.2 NP类

`NP(非确定型多项式时间, nondeterministic polynomial-time)`

### 9.7.3 NP完全问题

`NP完全(NP-complete)`问题有一个性质，即NP中的任一问题都能够`多项式地归约(polynomially reduced)`成NP完全问题。

**旅行商问题** 给定一完全图$G=(V, E)$，其边的值以及整数$K$，是否存在一个访问所有顶点并且总值小于等于$K$的简单回路？

![9_80](res/9_80.png)

*哈密尔顿回路问题变换成旅行商问题*







