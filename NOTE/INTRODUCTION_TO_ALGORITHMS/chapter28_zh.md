# 第28章 矩阵运算



## 28.1 求解线性方程组

$$
\begin{bmatrix}
a_{11} & a_{12} & \dots & a_{1n} \\
a_{21} & a_{22} & \dots & a_{2n} \\
\vdots & \vdots & \ddots& \vdots \\
a_{n1} & a_{n2} & \dots & a_{nn} \\
\end{bmatrix}

\begin{bmatrix}
x_1 \\
x_2 \\
\vdots \\
x_n
\end{bmatrix}

= 

\begin{bmatrix}
b_1 \\
b_2 \\
\vdots \\
b_n
\end{bmatrix}
$$

或等价地，设$A = (a_{ij}), x = (x_i) 和 b = (b_i)$，记为：
$$
Ax = b
$$
如果$A$是非奇异矩阵，那么它具有逆$A ^ {-1}$，于是
$$
x = A ^ {-1} b
$$
**LUP分解综述**

LUP分解背后的思想就是找出三个$n \times n$矩阵$L, U和P$，满足
$$
PA = LU
$$
($L$是一个单位下三角矩阵，$U$是一个上三角举证，$P$是一个置换矩阵。我们称满足上面公式的矩阵$L, U和P$为矩阵$A$的**LUP分解**)。
$$
\begin{align}
& LUP-SOLVE(L, U, \pi, b) \\
& n = L.rows \\
& let\ x\ and\ y\ be\ a\ new\ vector\ of\ length\ n \\
& for\ i = 1\ to\ n \\
& \qquad y_i = b_{\pi[i]} - \sum_{j = 1}^{i - 1}l_{ij}y_i \\
& for\ i = n\ downto\ 1 \\
& \qquad x_i = (y_i - \sum_{j = i + 1}^{n}u_{ij}x_j) / u_{ij} \\
& return\ x
\end{align}
$$
**计算一个LU分解**
$$
\begin{align}
& LU-DECOMPOSITION(A) \\
& n = A.rows \\
& let\ L\ and\ U\ be\ new\ n \times n\ matrices \\
& initialize\ U\ with\ 0s\ below\ the\ diagonal \\
& initialize\ L\ with\ 1s\ on\ the\ diagonal\ and\ 0s\ above\ the\ diagonal \\
& for\ k = 1\ to\ n \\
& \qquad u_{kk} = a_{kk} \\
& \qquad for\ i = k + 1\ to\ n \\
& \qquad \qquad l_{ik} = a_{ik} / u_{kk} \\
& \qquad \qquad u_{ki} = a_{ki} \\
& \qquad for\ i = k + 1\ to\ n \\
& \qquad \qquad for\ j = k + 1\ to\ n \\
& \qquad \qquad \qquad a_{ij} = a_{ij} - l_{ij}u_{kj} \\
& return\ L\ and\ U
\end{align}
$$
![28_1](res/28_1.png)
$$
\begin{align}
& LUP-DECOMPOSITION(A) \\
& n = A.rows \\
& let\ \pi[1..n]\ be\ a\ new\ array \\
& for\ i = 1\ to\ n \\
& \qquad \pi[i] = i \\
& for\ k = 1\ to\ n \\
& \qquad p = 0 \\
& \qquad \qquad for\ i = k\ to\ n \\
& \qquad \qquad \qquad if\ |a_{ik}| > p \\
& \qquad \qquad \qquad \qquad p = |a_{ik}| \\
& \qquad \qquad \qquad \qquad k' = i \\
& \qquad if\ p == 0 \\
& \qquad \qquad error\ "singular\ matrix" \\
& \qquad exchange\ \pi[k]\ with\ \pi[k'] \\
& \qquad for\ i = 1\ to\ n \\
& \qquad \qquad exchange\ a_{ki}\ with\ a_{k'i} \\
& \qquad for\ i = k + 1\ to\ n \\
& \qquad \qquad a_{ik} = a_{ik} / a_{kk} \\
& \qquad \qquad for\ j = k + 1\ to\ n \\
& \qquad \qquad \qquad a_{ij} = a_{ij} - a_{ik}a_{kj}
\end{align}
$$
![28_2](res/28_2.png)



## 28.2 矩阵求逆

**定理 28.1**（矩阵乘法不比矩阵求逆困难）如果能在$I(n)$时间内求出一个$n \times n$矩阵的逆，其中$I(n) = \Omega(n^2)$且$I(n)$满足正则性条件$I(3n) = O(I(n))$，那么可以在$O(I(n))$时间内求出两个$n \times n$矩阵的乘积。

**定理 28.2**（矩阵求逆运算不比矩阵乘法运算更难）如果能在$M(n)$时间内计算出两个$n \times n$实数矩阵的乘积，其中$M(n) = \Omega(n ^ 2)$且$M(n)$满足两个正则性条件：对任意的$k(0 \leqslant k \leqslant n)$，$M(n + k) = O(M(n))$；对某个常数$c < 1/2, M(n/2) \leqslant cM(n)$。那么可以在$O(M(n))$时间内计算出任何一个$n \times n$非奇异实数矩阵的逆。



## 28.3 对称正定矩阵的最小二乘逼近

**引理 28.3** 任何对称正定矩阵都是非奇异矩阵。

**引理 28.4** 如果$A$是一个对称正定矩阵，那么$A$的每个主子矩阵都是对称正定的。

**引理 28.5**（舒尔补引理）如果$A$是一个对称正定矩阵，$A_k$是$A$的$k \times k$主子矩阵，那么$A$关于$A_k$的舒尔补是对称正定的。

**推论 28.6** 一个对称正定矩阵的LU分解永远不会出现除数为0的情形。

![28_3](res/28_3.png)