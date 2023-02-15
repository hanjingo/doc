# 第29章 线性规划



![29_2](res/29_2.png)



## 29.1 标准型和松弛型

**标准型**

在标准型中，我们已知$n$个实数$c_1, c_2, ..., c_n$；$m$个实数$b_1, b_2, ..., b_m$，以及$mn$个实数$a_{ij}$，其中$i = 1, 2, ..., m, j = 1, 2, ..., n$。我们希望找到$n$个实数$x_1, x_2, ..., x_n$，最大化$\sum_{j = 1}^{n} c_j x_j$，满足约束条件：
$$
\begin{equation}\begin{split} 
\sum_{j = 1}^{n}a_{ij}x_{j} &\leqslant b_i, i = 1, 2, ..., m \\
x_j &\geqslant 0, j = 1, 2, ..., n
\end{split}\end{equation}
$$


## 29.2 将问题表达为线性规划

![29_3](res/29_3.png)



## 29.3 单纯形算法

**引理 29.1** 考虑当$a_{le} \neq 0$时对$PIVOT(N, B, A, b, c, v, l, e)$的调用。令调用返回值为$(\hat{N}, \hat{B}, \hat{A}, \hat{b}, \hat{c}, \hat{v})$，令$\overline x$表示调用之后的基本解。那么：

1. 对每个$j \in \hat{N}, \overline{x_j} = 0$。
2. $\overline{x_e} = b_l / a_{le}$。
3. 对每个$i \in \hat{B} - \{e\}, \overline{x_i} = b_i - a_{ie}\hat{b_e}$。

$$
\begin{align}
& SIMPLEX(A, b, c) \\
& (N, B, A, b, c) = INITIALIZE-SIMPLEX(A, b, c) \\
& let\ \Delta\ be\ a\ new\ vector\ of\ length\ m \\
& while\ some\ index\ j \in N\ has\ c_j > 0 \\
& \qquad choose\ an\ index\ e \in N\ for\ which\ c_e > 0 \\
& \qquad for\ each\ index\ i \in B \\
& \qquad \qquad if\ a_{ie} > 0 \\
& \qquad \qquad \qquad \Delta_{i} = b_i / a_{ie} \\
& \qquad \qquad else\ \Delta_{i} = \infty \\
& \qquad choose\ an\ index\ l \in B\ that\ minimizes\ \Delta_{l} \\
& \qquad if\ \Delta_{l} == \infty \\
& \qquad \qquad return\ "unbounded" \\
& \qquad else(N, B, A, b, c, v) = PIVOT(N, B, A, b, c, v, l, e) \\
& for\ i = 1\ to\ n \\
& \qquad if\ i \in B \\
& \qquad \qquad \overline{x_i} = b_i \\
& \qquad else\ \overline{x_i} = 0 \\
& return\ (\overline{x_1}, \overline{x_2}, ..., \overline{x_n})
\end{align}
$$

**引理 29.2** 给定一个线性规划$(A, b, c)$。假设在$SIMPLEX$第1行中对$INITIALIZE-SIMPLEX$的调用返回一个基本解可行的松弛型。如果$SIMPLEX$在第17行返回一个解，则这个解是此线性规划的一个可行解。如果$SIMPLEX$在第11行返回“无界”，则此线性规划是无界的。

**引理 29.3** 设$I$是一个下标集合。对于每一个$j \in I$，设$a_j$和$\beta_{j}$是实数，并令$x_j$是一个实数变量。设$\gamma$是任意的实数。假设对于变量$x_j$的任何设置，我们有：
$$
\sum_{j \in I}\alpha_{j}x_{j} = \gamma + \sum_{j \in I}\beta_{j}x_{j}
$$
那么对于任意的$j \in I, \alpha_{j} = \beta_{j}$，且$\gamma = 0$。

**引理 29.4** 设$(A, b, c)$是一个线性规划的标准形式。给定基本变量的一个集合$B$，那么关联的松弛型是唯一确定的。

**引理 29.5** 如果$SIMPLEX$在至多${n+m \choose m}$次迭代内不终止，那么它是循环的。

**引理 29.6** 如果$SIMPLEX$的第4行和第9行总是通过选择具有最小下标的变量来打破目标值不变的局面，那么$SIMPLEX$必然终止。

**引理 29.7** 假设$INITIALIZE-SIMPLEX$返回一个基本解可行的松弛型，则$SIMPLEX$要么报告一个线性规则是无界的，要么在至多${n + m \choose m}$次循环内终止，并得到一个可行解。



## 29.4 对偶性

**引理 29.8**（线性规划弱对偶性）设$\overline{x}$表示公式$\sum_{j = 1}^{n}c_j x_j$，$\sum_{j = 1}^{n}a_{ij}x_j \leqslant b_i, i = 1, 2, ..., m$，$x_j \geqslant 0, j = 1, 2, ..., n$。中原始线性规划的任意一个可行解，$\overline{y}$表示公式$\sum_{i = 1}^{m}b_i y_i$，$\sum_{i = 1}^{m} a_{ij} y_i \geqslant c_j, j = 1, 2, ..., n$，$y_i \geqslant 0, i = 1, 2, ..., m$中对偶问题的任意一个可行解。那么有：
$$
\sum_{j = 1}^{n} c_j \overline{x_j} \leqslant \sum_{i = 1}^{m} b_i \overline{y_i}
$$
**推论 29.9** 令$\overline{x}$表示一个原始线性规划$(A, b, c)$的一个可行解，令$\overline{y}$表示相应对偶问题的一个可行解。如果
$$
\sum_{j = 1}^{n} c_j \overline{x_j} = \sum_{i = 1}^{m} b_i \overline{y_i}
$$
那么$\overline{x}$和$\overline{y}$分别是原始线性规划和对偶线性规划的最优解。

**定理 29.10**（线性规划对偶性）假设$SIMPLEX$在原始线性规划$(A, b, c)$上返回值$\overline{x} = (\overline{x_1}, \overline{x_2}, ..., \overline{x_n})$。令$N$和$B$分别表示最终松弛型非基本便令和基本变量的集合，令$c'$表示最终松弛型中的系数，令$\overline{y} = (\overline{y_1}, \overline{y_2}, ..., \overline{y_m})$由公式：
$$
\overline{y_i} = 
\begin{cases}
-c_{n + i}', &若(n + i) \in N \\
0, &其它
\end{cases}
$$
定义。那么$\overline{x}$是原始线性规划的一个最优解，$\overline{y}$是对偶性规划的一个最优解，以及：
$$
\sum_{j = 1}^{n} c_j \overline{x_j} = \sum_{i = 1}^{m}b_j \overline{y_i}
$$


## 29.5 初始基本可行解

$$
\begin{align}
& INITIALIZE-SIMPLEX(A, b, c) \\
& let\ k\ be\ the\ index\ of\ the\ minimum\ b_i \\
& if\ b_k \geqslant 0 \\
& \qquad return\ (\{1, 2, ..., n\}, \{n + 1, n + 2, ..., n + m\}, A, b, c, 0) \\
& form\ L_{aux}\ by\ adding\ - x_0\ to\ the\ left-hand\ side\ of\ each\ constraint\ and\ setting\ the\ objective\ function\ to - x_0 \\
& let\ (N, B, A, b, c, v)\ be\ the\ resulting\ slack\ form\ for\ L_{aux} \\
& l = n + k \\
& //\ L_{aux}\ has\ n + 1\ nonbasic\ variables\ and\ m\ basic\ variables \\
& (N, B, A, b, c, v) = PIVOT(N, B, A, b, c, v, l, 0) \\
& //\ The\ basic\ solution\ is\ now\ feasible\ for\ L_{aux} \\
& iterate\ the\ while\ loop\ of\ lines\ 3-12\ of\ SIMPLEX\ until\ an\ optimal\ solution\ to\ L_{aux}\ is\ found
& if\ the\ optimal\ solution\ to\ L_{aux}\ sets\ \overline{x_0}\ to\ 0 \\
& \qquad if\ \overline{x_0}\ is\ basic \\
& \qquad \qquad perform\ one\ (degenerate)\ pivot\ to\ make\ it\ nonbasic \\
& \qquad from\ the\ final\ slack\ form\ of\ L_{aux}, remove\ x_0\ from\ the\ constraints\ and\ restore\ the\ original\ objective\ fuction\ of\ L, but\ replace\ each\ basic\ variable\ in\ this\ objective\ function\ by\ the\ right-hand\ side\ of\ its\ associated\ constraint
& \qquad return\ the\ modified\ final\ slack\ form \\
& else\ return\ "infeasible"
\end{align}
$$

**引理 29.12** 如果一个线性规划$L$没有可行解，那么$INITIALIZE-SIMPLEX$返回"不可行"；否则，它返回一个基本解可行的有效松弛型。

**定理 29.13**（线性规划基本定理）任何以标准型给出的线性规划$L$可能会是如下情形：

1. 有一个有限目标值的最优解。
2. 不可行。
3. 无界。

如果$L$是不可行的。$SIMPLEX$返回"不可行"。如果$L$是无界的，$SIMPLEX$返回"无界"。否则，$SIMPLEX$返回一个有限目标值的最优解。

