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

