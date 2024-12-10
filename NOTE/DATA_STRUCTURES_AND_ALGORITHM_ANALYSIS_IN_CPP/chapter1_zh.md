# 第一章 引论

[TOC]



## 本书讨论的内容



## 数学知识复习

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



## 递归的简单介绍



## C++类

### 基本class语法

### 特别的构造函数语法与访问函数

### 接口与实现的分离

### vector和string



## C++细节

### 指针

### 参数传递

### 返回值传递

### 引用变量

### 三大函数：析构函数，复制构造函数和operator=

### C风格的数据和字符串



## 模版

### 函数模版

### 类模版

### Object,Comparable和例子

### 函数对象

### 类模版的分离编译



## 使用矩阵

### 数据成员，构造函数和基本访问函数

### operator[]

### 析构函数，复制赋值和复制构造函数

