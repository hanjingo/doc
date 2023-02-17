# 第35章 近似算法



如果对规模为$n$的任意输入，近似算法所产生的近似解的代价$C$与最优解的代价$C^{*}$只差一个因子$\rho (n)$：
$$
max(\frac{C}{C^{*}}, \frac{C^{*}}{C}) \leqslant \rho(n)
$$

## 35.1 顶点覆盖问题

$$
\begin{align}
& APPROX-VERTEX-COVER(G) \\
& C = \phi \\
& E' = G.E \\
& while\ E' \neq \phi \\
& \qquad let\ (u, v)\ be\ an\ arbitrary\ edge\ of\ E' \\
& \qquad C = C \cup \{u, v\} \\
& \qquad remove\ from\ E'\ Every\ edge\ incident\ on\ either\ u\ or\ v \\
& return\ C
\end{align}
$$

**定理 35.1** $APPROX-VERTEX-COVER$是一个多项式时间的2近似算法。

![35_1](res/35_1.png)



## 35.2 旅行商问题

### 35.2.1 满足三角不等式的旅行商问题

$$
\begin{align}
& APPROX-TSP-TOUR(G, c) \\
& select\ a\ verte\ r \in G.V\ to\ be\ a\ "root"\ vertex \\
& compute\ a\ minimum\ spanning\ tree\ T\ for\ G\ from\ root\ r\ using\ MST-PRIM(G, c, r) \\
& let\ H\ be\ a\ list\ of\ vertices,\ ordered\ according\ to\ when\ they\ are\ first\ visited\ in\ a\ preorder\ tree\ walk\ of\ T \\
& return\ the\ hamiltonian\ cycle\ H
\end{align}
$$

![35_2](res/35_2.png)

**定理 35.2** $APPROX-TSP-TOUR$是一个用于解决满足三角不等式的旅行商问题的多项式时间2近似算法。

### 35.2.2 一般旅行商问题

**定理 35.3** 如果$P \neq NP$，则对任何常数$\rho \geqslant 1$，一般旅行商问题不存在具有近似比为$\rho$的多项式时间近似算法。



## 35.3 集合覆盖问题

![35_3](res/35_3.png)

**一个贪心近似算法**
$$
\begin{align}
& GREEDY-SET-COVER(x, F) \\
& U = X \\
& e = \phi \\
& while\ U \neq \phi \\
& \qquad select\ an\ S \in F\ that\ maximizes\ |S \cap U| \\
& \qquad U = U - S \\
& \qquad e = e \cup \{S\} \\
& return\ e
\end{align}
$$
**定理 35.4** $GREEDY-SET-COVER$是一个多项式时间的$\rho(n)$近似算法，其中：$\rho (n) = H(max\{|S|: S \in F \})$。

**推论 35.5** $GREEDY-SET-COVER$是一个多项式时间的$(ln |X| + 1)$近似算法。



## 35.4 随机化和线性规划

**定理 35.6** 给定$MAX-3-CNF$可满足性问题的一个实例，它有$n$个变量$x_1, x_2, ..., x_n$和$m$个子句，以$1/2$概率独立地将每个变量设置为$1$并以$1/2$概率独立地将每个变量设置为$0$的随机化近似算法是一个随机化的$8/7$近似算法。
$$
\begin{align}
& APPROX-MIN-WEIGHT-VC(G, w) \\
& C = \phi \\
& compute\ \overline{x}, an\ optimal\ solution\ to\ the\ linear\ program\ in\ lines(35.17) - (35.20) \\
& for\ each\ v \in V \\
& \qquad if\ \overline{x}(v) \geqslant 1/2 \\
& \qquad \qquad C = C \cup \{v\} \\
& return\ C
\end{align}
$$
**定理 35.7** 算法$APPROX-MIN-WEIGHT-VC$是求解最小权值顶点覆盖问题的一个多项式时间的2近似算法。



## 35.5 子集和问题

**一个指数时间的准确算法**
$$
\begin{align}
& EXACT-SUBSET-SUM(S, t) \\
& n = |S| \\
& L_0 = <0> \\
& for\ i = 1\ to\ n \\
& \qquad L_i = MERGE-LISTS(L_{i - 1}, L_{i - 1} + x_i) \\
& \qquad remove\ from\ L_i\ every\ element\ that\ is\ greater\ than\ t \\
& return\ the\ largest\ element\ in\ L_n
\end{align}
$$
**一个完全多项式时间近似模式**
$$
\begin{align}
& TRIM(L, \delta) \\
& let\ m\ be\ the\ length\ of\ L \\
& L' = <y_1> \\
& last = y_1 \\
& for\ i = 2\ to\ m \\
& \qquad if\ y_i > last.(1 + \delta) \\
& \qquad \qquad append\ y_i\ onto\ the\ end\ of\ L' \\
& \qquad \qquad last = y_i \\
& return\ L'
\end{align}
$$

$$
\begin{align}
& APPROX-SUBSET-SUM(S, t, \epsilon) \\
& n = |S| \\
& L_0 = <0> \\
& for\ i = 1\ to\ n \\
& \qquad L_i = MERGE-LISTS(L_{i - 1}, L_{i - 1} + x_i) \\
& \qquad L_i = TRIM(L_i, \epsilon / 2n) \\
& \qquad remove\ from\ L_i\ every\ element\ that\ is\ greater\ than\ t \\
& let\ z^{*}\ be\ the\ largest\ value\ in\ L_n \\
& return\ z^{*}
\end{align}
$$

**定理 35.8** $APPROX-SUBSET-SUM$是子集和问题的一个完全多项式时间近似模式。

