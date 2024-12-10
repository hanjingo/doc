# 第五章 概率分析和随机算法



## 5.1 雇用问题

### 最坏情形分析

### 概率分析

### 随机算法



## 5.2 指示器随机变量

随机变量(indicator random variable)：为概率与期望之间的转换提供了一个便利方法；给定一个样本空间$S$和一个事件$A$，那么事件$A$对应的指示器随机变量$I\{A\}$定义为：
$$
I{A} =
\begin{cases}
1, & \text{如果A发生}  \\
0, & \text{如果A不发生}
\end{cases}
$$
**引理5.1** 给定一个样本空间$S$和$S$中的一个事件$A$，设$X_A = I\{A\}$，那么$E[X_A]=Pr\{A\}$。

**证明** 根据随机变量与期望值的定义，我们有$E[X_A] = E[I\{A\}] = 1 \cdot Pr\{A\} + 0 \cdot Pr\{\overline{A}\} = Pr\{A\}$，其中$\overline A$表示$S-A$，即$A$的补。

**引理5.2** 假设应聘者以随机次序出现，算法HIRE-ASSISTANT总的雇用费用平均情形下为$O(c_h ln\ n)$。

**证明** 根据雇用费用的定义，可以立即推出这个界，说明雇用的人数期望值大约是$lg\ n$。



## 5.3 随机算法

```c++
RANDOMIZED-HIRE-ASSISTANT(n)
randomly permute the list of candidates
best = 0
for i = 1 to n
    interview candidate i
    if candidate i is better than candidate best
        best = i
        hire candidate i
```

**引理5.3** 过程RANDOMIZED-HIRE-ASSISTANT的雇用期望是$O(c_h ln\ n)$。

**证明** 对输入数组进行变换后，我们已经到了和HIRE-ASSISTANT概率分析时相同的情况。

### 随机排列数组

```c++
PERMUTE-BY-SORTING(A)
n = A.length
let P[1. .n] be a new array
for i = 1 to n
    P[i] = RANDOM(1, n^3)
sort A, suing P as sort keys
```

**引理5.4** 假设所有优先级都不同，则过程PERMUTE-BY-SORTING产生输入的均匀随机排列。

**证明** 我们从考虑每个元素$A[i]$分配到第$i$个最小优先级的特殊排列开始，并说明这个排列正好发生的概率是$1/n!$。对$i=1, 2, ..., n$，设$E_i$代表元素$A[i]$分配到第$i$个最小优先级的事件。然后我们想计算对所有的$i$，事件$E_i$发生的概率，即$Pr\{E_1 \cap E_2 \cap E_3 \cap ... \cap E_{n-1} \cap E_n\} = (\frac{1}{n})(\frac{1}{n-1})...(\frac{1}{2})(\frac{1}{1}) = \frac{1}{n!}$。

**引理5.5** 过程RANDOMIZE-IN-PLACE可计算出一个均匀随机排列。

**证明** 我们使用下面的循环不变式：在第2~3行for循环的第i次迭代以前，对每个可能的(i-1)排列，子数组A[1..i-1]包含这个(i-1)排列的概率是(n-i+1)!/n!。



## 5.4 概率分析和指示器随机变量的进一步使用

### 5.4.1 生日悖论

### 5.4.2 球与箱子

### 5.4.3 特征序列

### 5.4.4 在线雇用问题

