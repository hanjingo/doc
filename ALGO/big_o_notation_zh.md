中文版 | [English](big_o_notation.md)

# 大O计数法

[TOC]



## 术语

- `time complexity` 时间复杂度



## 定义

如果有任何正值常数c和$N_0$时，使得当$N \geq N_0$时，$T(N) \leq cF(N)$，那么我们便可将T(N)的复杂度表示为$O(F(N))^3$。

**定义2.1** 如果存在正常数$c$和$n_0$使得当$N \geqslant n_0$时$T(N) \leqslant cf(N)$，则记为$T(N) = O(f(N))$。

**定义2.2** 如果存在正常数$c$和$n_0$使得当$N \geqslant n_0$时$T(N) \geqslant cg(N)$，则记为$T(N)= \Omega (g(N))$。

**定义2.3** $T(N) \Theta (h(N))$当前仅当$T(N) = O(h(N))$和$T(N) = \Omega(h(N)) $。

**定义2.4** 如果对所有的常数$c$存在$n_0$使得当$N > n_0$时$T(N) < cp(N)$，则记为$T(N) = 0(p(N))$。非正式的定义为：如果$T(N) = O(p(N))$且$T(N) \neq \Theta(p(N))$，则$T(N) = o(p(N))$。

**法则1** 如果$T_1(N) = O(f(N))$且$T_2(N) = O(g(N))$，那么

(a) $T_1(N) + T_2(N) = O(f(N) + g(N))$（直观地非正式地表达为$max(O(f(N)), O(g(N)))$）

(b) $T_1(N)T_2(N) = O(f(N)g(N))$

**法则2** 如果$T(N)$是一个$k$次多项式，则$T(N) = \Theta(N^k)$。

**法则3** 对任意常数$k$, $log^kN = O(N)$。它告诉我们对数增长得非常缓慢。

常用的函数阶:

| 符号        | 名称     |
| ----------- | -------- |
| $O(1)$      | 常数     |
| $O(log n)$  | 对数     |
| $O(n)$      | 线性     |
| $O(nlog n)$ | 现行对数 |
| $O(n^2)$    | 平方     |
| $O(n^3)$    | 立方     |
| $O(c^n)$    | 指数     |
| $O(n!)$     | 阶乘     |



## 运行时间的计算

### 一般法则

**法则1：for循环** 一个for循环的运行时间至多是该for循环内语句（包括测试）的运行时间乘以迭代的次数。

**法则2：嵌套循环** 从里向外分析这些循环。在一组嵌套循环内部的一条语句总的运行时间为该语句的运行时间乘以改组所有循环的大小的乘积。

**法则3：顺序语句** 将各个语句的运行时间求和即可。

**法则4：If/Else语句** 对于程序片段

```c++
if (condition)
  S1
else
  S2
```

一个if/else语句的运行时间从不超过判断再加上$S_1$和$S_2$中运行时间较长者的总的运行时间。

### 最大子序列和问题的解

### 运行时间中的对数

对数最常出现的规律为：如果一个算法用常数时间$O(1)$将问题的大小削减为其一部分（通常是1/2），那么该算法就是$O(log\ N)$的；另一方面，如果使用常数时间只是把问题减少一个常数的数量（如将问题减少1），那么这种算法就是$O(N)$的。

1. 二分搜索

   `二分搜索（binary serch）` 给定一个整数$X$和整数$A_0, A_1, ..., A_{N-1}$，后者已经预先排序并在内存中，求下标$i$使得$A_i = X$，如果$X$不在数据中，则返回$i = -1$。

   运行时间是$O(log\ N)$。

2. 欧几里得算法

   **定理2.1** 如果$M > N$，则$M mod N < M/2$。

3. 幂运算



## 数学基础

### 指数

$X^A X^B = X^{A+B}$

$\frac{X^A}{X^B} = X^{A-B}$

$(X^A)^B = X^{AB}$

$X^N + X^N = 2X^N \neq X^{2N}$

$2^N + 2^N = x^{N+1}$

### 对数

**定义1.1** $X^A = B$当且仅当$log_x{B} = A$。

**定理1.1** $log_A{B} = \frac{log_c{B}}{log_c{A}}; A, B, C > 0, A \neq 1。$

**定理1.2** $logAB = logA + logB; A, B > 0$。

一些其他的定理：

$logA/B = logA - logB$

$log(A^B) = B log A$

$log X < X$对所有的$X > 0$成立

$log 1 = 0, log 2 = 1, log1024 = 10, log 1048476 = 20$

### 级数

$\sum_{i = 0}^{N} 2^i = 2^{N+1} - 1$

$\sum_{i=0}^{N} A^i = \frac{A^{N+1} - 1}{A - 1}$， 如果$0 < A < 1$则：$\sum_{i = 0}^{N} \leqslant \frac{1}{1 - A}$，当$N$趋向于$\infty$时，该和趋向于$1/(1-A)$。

$\sum_{N}^{i=1} = \frac{N(N+1)}{2} \approx \frac{N^2}{2}$

$\sum_{i = 1}^{N} i^2 = \frac{N(N+1)(2N+1)}{6} \approx \frac{N^3}{3}$

$\sum_{i=1}^{N} i^k \approx \frac{N^{k+1}}{k+1};k \neq -1$

`欧拉常数（Euler's constant）：` $H_N = \sum_{i=1}^{N} \frac{1}{i} \approx log_e{N}$

$\sum_{i=1}^{N} \frac{1}{i} \approx log_e$

$\sum_{i=1}^{N} f(N) = Nf(N)$

$\sum_{i=n_0}^{N} f(i) = \sum_{i = 1}^{N} f(i) - \sum_{i = 1}^{n_0 - 1}f(i)$

### 模运算

如果$N$整除$A-B$，那么就说$A$与$B$同余（congruent），记为$A \equiv B (mod\ N)$。这意味着无论$A$或$B$被$N$除，所得余数都是相同的。因此，$81 \equiv 61 \equiv 1 (mod\ 10)$。与等号一样，若$A \equiv B (mod\ N)$，则$A + C \equiv B + C(mod\ N)$以及$AD \equiv BD(mod\ N)$。

### 证明方法

1. 归纳法证明

   第一步证明`基准情形（base case）`，就是确定定理对于某个小的值的正确性；然后，进行`归纳假设（inductive hypothesis）`。

2. 通过反例证明

   公式$F_k \leqslant K^2$ 不成立。最容易的证明方法就是计算$F_{11} = 144 > 11^2$。

3. 反证法证明

   反证法证明是通过假设定理不成立，然后证明该假设导致某个已知的性质不成立，从而证明原假设是错误的。



## 参考

- [维基百科-大O符号](https://en.wikipedia.org/wiki/Big_O_notation)
- [大O计数法](https://blog.csdn.net/weixin_44560088/article/details/108052225)
- Introduction to Algorithms.Thomas H Cormen, Charles E Leiserson, Ronald L Rivest, Clifford Stein.Third Edition.2013
- [美]Mark Allen Weiss . 数据结构与算法分析-C++描述 . 3ED

