# 第15章 动态规划



动态规划通常用来求解**最优化问题（optimization problem）**。

## 15.1 钢条切割

**钢条切割问题**：给定一段长度为$n$英寸的钢条和一个价格表$p_i(i = 1, 2, ..., n)$，求切割钢条方案，使得销售收益$r_n$最大。注意，如果长度为$n$英寸的钢条的价格$p_n$足够大，最优解可能就是完全不需要切割。

![15_2](res/15_2.png)

**自顶向下递归实现**
$$
\begin{align}
& CUT-ROD(p, n) \\
& if\ n == 0 \\
& \qquad return\ 0 \\
& q = - \infty \\
& for\ i = 1\ to\ n \\
& \qquad q = max(q, p[i] + CUT-ROD(p, n - i)) \\
& return\ q \\
\end{align}
$$
![15_3](res/15_3.png)

CUR-ROD的运行时间：$T(n) = 1 + \sum_{j = 0}^{n - 1} T(j) = 2^n$。

**使用动态规划方法求解最优钢条切割问题**

- 带备忘的自顶向下法（top-down with memoization）
  $$
  \begin{align}
  & MEMOIZED-CUT-ROD(p, n) \\
  & let\ r[0..n]\ be\ a\ new\ array \\
  & for\ i = 0\ to\ n \\
  & \qquad r[i] = - \infty \\
  & return\ MEMOIZED-CUT-ROD-AUX(p, n, r)
  \end{align}
  $$

  $$
  \begin{align}
  & MEMOIZED-CUT-ROD-AUX(p, n, r) \\
  & if\ r[n] \geqslant 0 \\
  & \qquad return\ r[n] \\
  & if\ n == 0 \\
  & \qquad q = 0 \\
  & else\ q = - \infty \\
  & \qquad for\ i = 1\ to\ n \\
  & \qquad \qquad q = max(q, p[i] + MEMOIZED-CUT-ROD-AUX(p, n - i, r)) \\
  & r[n] = q \\
  & return\ q
  \end{align}
  $$

- 自底向上法(bottom-up method)
  $$
  \begin{align}
  & BOTTOM-UP-CUT-ROD(p, n) \\
  & let\ r[0..n]\ be\ a\ new\ array \\
  & r[0] = 0 \\
  & for\ j = 1\ to\ n \\
  & \qquad q = - \infty \\
  & \qquad for\ i = 1\ to\ j \\
  & \qquad \qquad q = max(q, p[i] + r[j - i]) \\
  & \qquad r[j] = q \\
  & return\ r[n]
  \end{align}
  $$

**子问题图**

![15_4](res/15_4.png)

**重构解**
$$
\begin{align}
& EXTENDED-BOTTOM-UP-CUT-ROD(p, n) \\
& let\ r[0..n]\ and\ s[0..n]\ be\ new\ arrays \\
& r[0] = 0 \\
& for\ j = 1\ to\ n \\
& \qquad q = - \infty \\
& \qquad for\ i = 1\ to\ j \\
& \qquad \qquad if\ q < p[i] + r[j - 1] \\
& \qquad \qquad \qquad q = p[i] + r[j - i] \\
& \qquad \qquad \qquad s[j] = i \\
& \qquad r[j] = q \\
& return\ r\ and\ s
\end{align}
$$

$$
\begin{align}
& PRINT-CUT-ROD-SOLUTION(p, n) \\
& (r, s) = EXTENDED-BOTTOM-UP-CUT-ROD(p, n) \\
& while\ n > 0 \\
& \qquad print\ s[n] \\
& \qquad n = n - s[n]
\end{align}
$$



## 15.2 矩阵链乘法

**矩阵链乘法问题（matrix-chain multiplication problem）**：给定$n$个矩阵的链$<A_1, A_2, ..., A_n>$，矩阵$A_i$的规模为$P_{i - 1} \times P_i (1 \leqslant i \leqslant n)$，求完全括号化方案，使得计算乘积$A_1A_2...A_n$所需标量乘法次数最少。
$$
\begin{align}
& MATRIX-MULTIPLY(A, B) \\
& if\ A.columns \neq B.rows \\
& \qquad error\ "incompatible\ dimensions" \\
& else\ let\ C\ be\ a\ new\ A.rows \times B.columns\ matrix \\
& \qquad for\ i = 1\ to\ A.rows \\
& \qquad \qquad for\ j = 1\ to\ B.columns \\
& \qquad \qquad \qquad c_{ij} = 0 \\
& \qquad \qquad \qquad for\ k = 1\ to\ A.columns \\
& \qquad \qquad \qquad \qquad c_{ij} = c_{ij} + a_{ik} \cdot b_{kj} \\
& return\ C
\end{align}
$$
**计算括号话方案的数量**
$$
P(n) = 
\begin{cases}
1, &如果n = 1\\
\sum_{n - 1}^{k = 1}P(k)P(n - k), &如果 n \geqslant 2
\end{cases}
$$
**应用动态规划方法**
$$
\begin{align}
& MATRIX-CHAIN-ORDER(p) \\
& n = p.length - 1 \\
& let\ m[1..n, 1..n]\ and\ s[1..n - 1, 2..n]\ be\ new\ tables \\
& for\ i = 1\ to\ n \\
& \qquad m[i,i] = 0 \\
& for\ l = 2\ to\ n \\
& \qquad for\ i = 1\ to\ n - l + 1 \\
& \qquad \qquad j = i + l - 1 \\
& \qquad \qquad m[i, j] = \infty \\
& \qquad \qquad for\ k = i\ to\ j - 1 \\
& \qquad \qquad \qquad q = m[i, k] + m[k + 1, j] + p_{i - 1}p_kp_j \\
& \qquad \qquad \qquad if\ q < m[i, j] \\
& \qquad \qquad \qquad \qquad m[i, j] = q \\
& \qquad \qquad \qquad \qquad s[i, j] = k \\
& return\ m\ and\ s
\end{align}
$$
![15_5](res/15_5.png)



## 15.3 动态规划原理

**最优子结构**

**一些微妙之处**

在尝试使用动态规划方法时要小心，要注意问题是否具有最优子结构性质。考虑下面两个问题，其中都是给定一个有向图$G=(V, E)$和两个顶点$u, v \in V$。

- **无权（unweighted）最短路径**：找到一条从$u$到$v$的边数最少的路径。这条路径必然是简单路径，因为如果路径中包含环，将环去掉显然会减少边的数量。
- **无权最长路径**：找到一条从$u$到$v$的边数最多的简单路径。这里必须加上简单路径的要求，因为我们可以不停地沿着环走，从而得到任意长的路径。

![15_6](res/15_6.png)

**重叠子问题**
$$
\begin{align}
& RECURSIVE-MATRIX-CHAIN(p, i, j) \\
& if\ i = j \\
& \qquad return\ 0 \\
& m[i, j] = \infty \\
& for\ k = i\ to\ j - 1 \\
& \qquad q = RECURSIVE-MATRIX-CHAIN(p, i, k) \\
& \qquad \qquad + RECURSIVE-MATRIX-CHAIN(p, k + 1, j) \\
& \qquad \qquad + p_{i-1}p_{k}p_{j} \\
& \qquad if\ q < m[i, j] \\
& \qquad \qquad m[i, j] = q \\
& return\ m[i, j]
\end{align}
$$

![15_7](res/15_7.png)

**重构最优解**

**备忘**

$$
\begin{align}
& MEMOIZED-MATRIX-CHAIN(p) \\
& n = p.length - 1 \\
& let\ m[1..n, 1..n]\ be\ a\ new\ table \\
& for\ i = 1\ to\ n \\
& \qquad for\ j = i\ to\ n \\
& \qquad \qquad m[i, j] = \infty \\
& return\ LOOKUP-CHAIN(m, p, 1, n)
\end{align}
$$

$$
\begin{align}
& LOOKUP-CHAIN(m, p, i, j) \\
& if\ m[i, j] < \infty \\
& \qquad return\ m[i, j] \\
& if\ i == j \\
& \qquad m[i, j] = 0 \\
& else\ for\ k = i\ to\ j - 1 \\
& \qquad q = LOOKUP-CHAIN(m, p, i, k) + LOOKUP-CHAIN(m, p, k + 1, j) + p_{i - 1}p_{k}p_{j} \\
& \qquad if\ q < m[i, j] \\
& \qquad \qquad m[i, j] = q \\
& return\ m[i, j]
\end{align}
$$



## 15.4 最长公共子序列

**最长公共子序列问题（longest-common-subsequence problem）**：给定两个序列$X = <x_1, x_2, ..., x_m>$和$Y = <y_1, y_2, ..., y_n>$，求$X$和$Y$长度最长的公共子序列。

**定理 15.1 （LCS的最优子结构）** 令$X = <x_1, x_2, ..., x_m>$和$Y = <y_1, y_2, ..., y_n>$为两个序列，$Z = <z_1, z_2, ..., z_k>$为$X$和$Y$的任意LCS。

1. 如果$x_m \neq y_n$，则$z_k = x_m = y_n$且$Z_{k - 1}$是$X_{m - 1}$和$Y_{n - 1}$的一个LCS。
2. 如果$x_m \neq y_n$，那么$z_k \neq x_m$意味着$Z$是$X_{m - 1}$和$Y$的一个LCS。
3. 如果$x_m \neq y_n$，那么$z_k \neq y_n$意味着$Z$是$X$和$Y_{n - 1}$的一个LCS。

$$
\begin{align}
& LCS-LENGTH(X, Y) \\
& m = X.length \\
& n = Y.length \\
& let\ b[1..m, 1..n]\ and\ c[0..m, 0..n]\ be\ new\ tables \\
& for\ i = 1\ to\ m \\
& \qquad c[i, 0] = 0 \\
& for\ j = 0\ to\ n \\
& \qquad c[0, j] = 0 \\
& for\ i = 1\ to\ m \\
& \qquad for\ j = 1\ to\ n \\
& \qquad \qquad if\ x_i == y_i \\
& \qquad \qquad \qquad c[i, j] = c[i - 1, j - 1] + 1 \\
& \qquad \qquad \qquad b[i, j] = "↖" \\
& \qquad \qquad elseif\ c[i - 1, j] \geqslant c[i, j - 1] \\
& \qquad \qquad \qquad c[i, j] = c[i - 1, j] \\
& \qquad \qquad \qquad b[i, j] = "↑" \\
& \qquad \qquad else\ c[i, j] = c[i, j - 1] \\
& \qquad \qquad \qquad b[i, j] = "←" \\
& return\ c\ and\ b
\end{align}
$$

$$
\begin{align}
& PRINT-LCS(b, X, i, j) \\
& if\ i == 0\ or\ j == 0 \\
& \qquad return \\
& if\ b[i, j] = "↖" \\
& \qquad PRINT-LCS(b, X, i - 1, j - 1) \\
& \qquad print\ x_i \\
& elseif\ b[i, j] = "↑" \\
& \qquad PRINT-LCS(b, X, i - 1, j) \\
& else\ PRINT-LCS(b, X, i, j - 1)
\end{align}
$$

![15_8](res/15_8.png)



## 15.5 最优二叉搜索树

**最优二叉搜索树（optimal binary search tree）问题**：给定一个$n$个不同关键字的已排序的序列$K = <k_1, k_2, ..., k_n>$（因此$k_1 < k_2 < ... < k_n$），对每个关键字$k_i$，都有一个概率$p_i$表示其搜索频率。

![15_9](res/15_9.png)
$$
\begin{align}
& OPTIMAL-BST(p, q, n) \\
& let\ e[1..n + 1, 0..n], w[1..n + 1, 0..n],\ and\ root[1..n, 1..n]\ be\ new\ tables \\
& for\ i = 1\ to\ n + 1 \\
& \qquad e[i, i - 1] = q_{i - 1} \\
& \qquad w[i, i - 1] = q_{i - 1} \\
& for\ l = 1\ to\ n \\
& \qquad for\ i = 1\ to\ n - l + 1 \\
& \qquad \qquad j = i + l - 1 \\
& \qquad \qquad e[i, j] = \infty \\
& \qquad \qquad w[i, j] = w[i, j - 1] + p_j + q_j \\
& \qquad \qquad for\ r = i\ to\ j \\
& \qquad \qquad \qquad t = e[i, r - 1] + e[r + 1, j] + w[i, j] \\
& \qquad \qquad \qquad if\ t < e[i, j] \\
& \qquad \qquad \qquad \qquad e[i, j] = t \\
& \qquad \qquad \qquad \qquad root[i, j] = r \\
& return\ e\ and\ root
\end{align}
$$
![15_10](res/15_10.png)
