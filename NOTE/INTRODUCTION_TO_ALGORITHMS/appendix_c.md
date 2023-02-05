# 计数与概率



## C.1 计数

**和规则** 

指从两个不相交集合之一中选择一个元素的方法数等于这两个集合的基数和，即$|A \cup B| = |A| + |B|$。

**积规则** 

指选出一个有序对的方法数等于选出第一个元素的方法数与选出第二个元素的方法数的乘积，即$|A \times B| = |A| \cdot |B|$。

**串** 

有限集$S$上的串是集合$S$中元素构成的一个序列；有时称长度为$k$的串为**k串**，串s的**子串s'**是s中连续若干个元素的有序序列；一个串的**k子串**是该串的长度为k的子串。

**排列** 

有限集S的一个排列是S中元素的一个有序序列，其中每个元素出现且仅出现一次。对于n集合的k排列，其可能的k排列数目为：$n(n-1)(n-2)...(n-k+1) = \frac{n!}{(n-k)!}$。

**组合** 

$n$集合$S$的一个$k$组合是$S$的一个$k$子集；$n$集合的$k$组合的数目就是$k$排列的数目除以$k!$，得到：$\frac{n!}{k!(n-k)!}$。

**二项系数**

符号${n \choose k}$表示$n$集合中$k$组合的数目，由等式$\frac{n!}{k!(n-k)!}$得到：${n \choose k} = \frac{n!}{k!(n-k)!}$。此公式对$k$与$n - k$是对称的：${n \choose k} = {n \choose n-k}$。因为这些数出现在二项展开式中，所以称其为**二项式系数**：$(x + y) ^ n = \sum_{k=0}^{n} {n \choose k} x^k y^{n-k}$。

**二项式界**

有时我们需要确定二项式系数大小的界。对于$1 \leqslant k \leqslant n$，有下界

${n \choose k} = \frac{n(n-1)...(n-k+1)}{k(k-1)...1} = (\frac{n}{l})(\frac{n-1}{k-1})...(\frac{n-k+1}{1}) \geqslant (\frac{n}{k})^k$

利用由斯特林近似得到的不等式$k! \geqslant (k/e)^k$，可以获得其上界

${n \choose k} = \frac{n(n-1)...(n-k+1)}{k(k-1)...1} \leqslant \frac{n^k}{k!} \leqslant (\frac{en}{k})^k$

对于所有满足$0 \leqslant k \leqslant n$的整数$k$，用归纳法可以证明其界

${n \choose k} \leqslant \frac{n^n}{k^k (n-k)^{n-k}}$

为了方便起见，假设$0^0 = 1$。对于$k = \lambda n$，其中$0 \leqslant \lambda \leqslant 1$，可以将界写作

${n \choose \lambda n} \leqslant \frac{n^n}{(\lambda n)^{\lambda n} ((1 - \lambda)n)^{(1 - \lambda)n}} = ((\frac{1}{\lambda})^{\lambda}) (\frac{1}{1 - \lambda} ^ {1 - \lambda}) ^ n = 2 ^{nH(\lambda)}$

其中

$H(\lambda) = -\lambda lg\lambda - (1 - \lambda) lg(1 - \lambda)$

是一个**（二进制）熵函数**。



## C.2 概率

**概率论公理**

样本空间$S$上的**概率分布**$Pr\{\}$是一个从$S$的事件到实数的映射，它满足如下**概率论公理**：

1. 对于任意事件$A, Pr{A} \geqslant 0$。
2. $Pr\{S\} = 1$。
3. 对于两个互斥事件$A$与$B$，有$Pr\{A \bigcup B\} = Pr\{A\} + Pr\{B\}$。更一般地，对于任意（有限或者可数无限）事件序列$A_1, A_2, ..., $若其两两互斥，则有$Pr\{\underset{i}{\cup} A_i\} = \sum_{i} Pr\{A_i\}$，我们称$Pr\{A\}$为事件$A$的概率。

空事件$\emptyset$的概率为$Pr\{\empty\} = 0$。

如果$A \subseteq B$，则$Pr\{A\} \leqslant Pr\{B\}$。

用$\overline A$来表示事件$S - A$（$A$的补），则有$Pr\{\overline A\} = 1 - Pr\{A\}$。

对于任意两个事件$A$和$B$有：
$$
\begin{equation}\begin{split} 
Pr\{A \cup B\} &= Pr{A} + Pr\{B\} - Pr\{A \cap B\} \\ 
&\leqslant Pr\{A\} + Pr\{B\}
\end{split}\end{equation}
$$
**离散概率分布**

如果一个概率分布定义在有限或者无限可数的样本空间上，则该概率分布是**离散的**。令$S$是样本空间，则对于任意事件$A$，因为基本事件是互斥的，所以有$Pr\{A\} = \sum_{s \in A} Pr\{s\}$；如果$S$是有限的，且每个基本事件$s \in S$的概率为$Pr\{s\} = 1 / |S|$，则得到的概率分布为$S$上的均匀概率分布。

**连续均匀概率分布**

对于闭区间$[c, d]$，其中$a \leqslant c \leqslant d \leqslant b$，连续均匀概率分布定义事件$[c, d]$的概率为$Pr\{[c, d]\} = \frac{d - c}{b - a}$；（注意，对于任意点$x = [x, x]$，其概率为0）。

**条件概率与独立**

已知事件$B$发生，事件$A$的条件概率的定义为$Pr\{A|B\} = \frac{Pr\{A \cap B\}}{Pr\{B\}}$；（其中$Pr\{B\} \neq 0$）。

对于所有$1 \leqslant i < j \leqslant n$，有$Pr\{A_i \cap A_j\} = Pr\{A_i\}Pr\{A_j\}$，则称事件$A_1, A_2, ..., A_n$**两两独立**。

对于所有$1 \leqslant k \leqslant n$且$1 \leqslant i_i < i_2 < ... < i_k \leqslant n$，均满足$Pr\{A_{i_1} \cap A_{i_2} ... \cap A_{i_k} \} = Pr\{A_{i_1}\} Pr\{A_{i_2}\} ... Pr\{A_{i_k}\}$，则称这些事件**（相互）独立**。

**贝叶斯定理**

**贝叶斯定理**：根据条件概率的定义$Pr\{A|B\} = \frac{Pr\{A \cap B\}}{Pr\{B\}}$与交换律$A \cap B = B \cap A$，对于两个概率不为0的事件$A$和$B$，有：

$Pr\{A \cap B\} = Pr\{B\}Pr\{A | B\} = Pr\{A\}Pr\{B|A\}$，

计算$Pr\{A | B\}$，得到：

$Pr\{A|B\} = \frac{Pr\{A\}Pr\{B|A\}}{Pr\{B\}}$。

因为$B = (B \cap A) \cup (B \cap \overline A)$，且$B \cap A$与$B \cap \overline A$是互斥事件，所以将$Pr\{B\} = Pr\{B \cap A\} + Pr\{B \cap \overline A\} = Pr\{A\}Pr\{B|A\} + Pr\{\overline A\}Pr\{B| \overline A\}$代入贝叶斯公式，得到贝叶斯定理的等价形式：

$Pr\{A|B\} = \frac{Pr\{A\} Pr\{B|A\}}{Pr\{A\}Pr\{B|A\} + Pr\{\overline A\}Pr\{B|\overline A\}}$



## C.3 离散随机变量

对于随机变量$X$和实数$x$，定义事件$X = x$为$\{s \in S: X(x) = x\}$；因此：

>  $Pr{X = x} = \sum_{s \in S: X(x) = x} Pr\{s\}$
>
> 函数：
>
> $f(x) = Pr\{X = x\}$
>
> 是随机变量$X$的**概率密度函数**。由概率公理可知，$Pr\{X = x\} \geqslant 0$且$\sum_{x} Pr\{X = x\} = 1$。

对于随机变量$X$和$Y$，则函数：

> $f(x, y) = Pr\{X = x 且 Y = y\}$
>
> 是$X$和$Y$的**联合概率密度函数**。对于定值$y$：
>
> $Pr\{Y = y\} = \sum_{x} Pr\{X = x 且 Y = y\}$
>
> 类似地，对于定值$x$：
>
> $Pr\{X = x\} = \sum_{y} Pr\{X = x 且 Y = y\}$
>
> 使用条件概率的定义，有：
>
> $Pr\{X = x | Y = y\} = \frac{Pr\{X = x 且 Y = y\}}{Pr\{Y = y\}}$。

**随机变量的期望值**

对于离散随机变量$X$的**期望值**（**期望**或**均值**）是$E[X] = \sum_{x} x \cdot Pr\{X = x\}$。

**期望的线性性质**：两个随机变量的和的期望与它们的期望之和相等，即$E[X + Y] = E[X] + E[Y]$。

如果$X$是随机变量，任何函数$g(x)$定义一个新的随机变量$g(X)$。如果$g(x)$的期望有定义，则：

> $E[g(X)] = \sum_{x} g(x) \cdot Pr\{X = x\}$
>
> 令$g(x) = ax$，则对于任意常数$a$，
>
> $E[aX] = aE[X]$
>
> 所以，期望是线性的：对于任意两个随机变量$X$和$Y$以及任意常数$a$，有：
>
> $E[aX + Y] = aE[X] + E[Y]$
>
> 当两个随机变量$X$和$Y$独立且期望有定义时：
> $$
> \begin{equation}\begin{split} 
> E[XY] &= \sum_x \sum_y xy \cdot Pr\{X = x 且 Y = y\} = \sum_x \sum_y xy \cdot Pr\{X = x\} Pr\{Y = y\} \\
> &= (\sum_x x \cdot Pr\{X = x\})(\sum_y y \cdot Pr\{Y = y\}) = E[X][Y]
> \end{split}\end{equation}
> $$
> 通常，当$n$个随机变量$X_1, X_2, ..., X_n$相互独立时：
>
> $E[X_1 X_2 ... X_n] = E[X_1] E[X_2] ... E[X_n]$
>
> 当随机变量$X$可在自然数集$N = \{0, 1, 2, ...\}$中取值时，有一个很好的的期望计算公式：
> $$
> \begin{equation}\begin{split}
> E[X] &= \sum_{i = 0}^{\infty} i \cdot Pr\{X = i\} = \sum_{i = 0}^{\infty} i (Pr\{X \geqslant i\} - Pr\{X \geqslant i + 1\}) \\
> &= \sum_{i = 1}^{\infty} Pr\{X \geqslant i\}
> \end{split}\end{equation}
> $$

当我们将一个凸函数$f(x)$应用到随机变量$X$上时，假定期望存在且有限，由詹森不等式得：$E[f(X)] \geqslant f(E[X])$；（如果对于所有$x, y$和所有$0 \leqslant \lambda \leqslant 1$，有$f(\lambda x + (1 - \lambda) y ) \leqslant \lambda f(x) + (1 - \lambda) f(x)$，则函数$f(x)$时凸函数）。

**方差和标准差**

**方差**的概念在数学上表达了一个随机变量可能离均值有多远。均值为$E[X]$的随机变量$X$的方差为：

> $$
> \begin{equation}\begin{split}
> Var[X] &= E[(X - E[X])^2] = E[X^2 - 2XE[X] + E^2[X]] \\
> &= E[X^2] - 2E[XE[X]] + E^2[X] \\
> &= E[X^2] - 2E^2[X] + E^2[X] = E[X^2] - E^2[X]
> \end{split}\end{equation}
> $$
>
> 因为$E[X]$是实数而不是随机变量，$E^2[X]$也是实数，所以有$E[E^2[X]] = E^2[X]$。等式$E[XE[X]] = E^2[X]$遵从等式$E[aX] = aE[X]$，其中$a = E[X]$。重写上面的等式得到随机变量平方的期望的一个表达式：
>
> $E[X^2] = Var[X] + E^2[X]$
>
> 随机变量$X$的方差与$aX$的方差的关系为：
>
> $Var[aX] = a^2 Var[X]$
>
> 当$X$和$Y$是独立随机变量时，
>
> $Var[X + Y] = Var[X] + Var[Y]$
>
> 通常，如果$n$个随机变量$X_1, X_2, ..., X_n$是两两独立的，那么：
>
> $Var[\sum_{i = 1}^{n} X_i] = \sum_{i = 1}^{n} Var[X_i]$



## C.4 几何分布与二项分布

**几何分布** 定义随机变量$X$为获得一次成功所需的试验次数，$X$的取值范围为$\{1, 2, ...\}$，且对于$k \geqslant 1$，因为一次成功前有$k - 1$次失败，所以有$Pr\{X = k\} = q^{k - 1} p$。

通过计算得出几何分布的期望：$E[X] = \sum_{k=1}^{\infty}kq^{k-1}p = \frac{p}{q} \sum_{k = 0}^{\infty} kq^k = \frac{p}{q} \cdot \frac{q}{(1 - q)^2} = \frac{p}{q} \cdot \frac{q}{p^2} = 1/p$。

**二项分布** 定义随机变量$X$为$n$次试验中成功的次数，则$X$的取值范围为$\{0, 1, ..., n\}$。对于$k = 0, 1, ..., n$，因为存在${n \choose k}$种方法来选出$n$次试验中哪$k$次成功，而每个发生的概率是$p^k q^{n - k}$，所以$Pr\{X = k\} = {n \choose k}p^k q^{n - k}$。

令$X$是服从二项分布$b(k; n, p)$的随机变量，且令$q = 1 - p$，根据期望的定义，有：
$$
\begin{equation}\begin{split}
E[X] &= \sum_{k = 0}^{n} k \cdot Pr\{X = k\} \\
&= \sum_{k = 0}^{n} k \cdot b(k;n,p) \\
&= \sum_{k = 1}^{n} k {n \choose k} p^k q^{n - k} \\
&= np \sum_{k = 1}^{n} {n - 1 \choose k - 1} p^{k - 1} q^{n - k} \\
&= np \sum_{k = 0}^{n - 1} {n - 1 \choose k} p^k q^{(n - 1) - k} \\
&= np \sum_{k = 0}^{n - 1} b(k; n - 1, p) \\
&= np
\end{split}\end{equation}
$$
令$X_i$是描述第$i$次试验中成功次数的随机变量，则$E[X_i] = p \cdot 1 + q \cdot 0 = p$，并且根据期望的线性性质，$n$次试验中成功次数的期望为：$E[X] = E[\sum_{i = 1}^{n} X_i] = \sum_{i = 1}^{n} E[X_i] = \sum_{i = 1}^{n} p = np$。

利用等式$Var[X] = E[X^2] - E^2[X]$，有$Var[X_i] = E[X_i^2] - E^2[X_i]$。因为$X_i$只能取值0和1，所以有$X_i ^ 2 = X_i$，进而有$E[X_i ^ 2] = E[X_i] = p$，因此，

> $Var[X_i] = p - p^2 = p(1 - p) = pq$
>
> 利用$n$次试验之间的独立性来计算$X$的方差，根据等式$Var[\sum_{i = 1}^{n} X_i] = \sum_{i = 1}^{n} Var[X_i]$，有：
>
> $Var[X] = Var[\sum_{i = 1}^{n} X_i] = \sum_{i = 1}^{n} Var[X_i] = \sum_{i = 1}^{n}pq = npq$。

**引理 C.1** 令$n \geqslant 0, 0 < p < 1, q = 1 - p且0 \leqslant k \leqslant n$，则$b(k; n, p) \leqslant (\frac{np}{k})^k (\frac{nq}{n - k})^{n - k}$

**证明** 利用等式${n \choose k} \leqslant \frac{n^n}{k^k (n - k)^{n - k}}$，有$b(k; n, p) = {n \choose k}p^k q^{n - k} \leqslant (\frac{n}{k})^k (\frac{n}{n - k})^{n - k} p^k q^{n - k} = (\frac{np}{k})^k (\frac{nq}{n - k})^{n - k}$。



## C.5 二项分布的尾部

**定理 C.2** 考虑$n$次伯努利试验的序列，其中成功概率为$p$。令$X$是表示成功次数的随机变量，则对于$0 \leqslant k \leqslant n$，至少成功$k$次的概率为：$Pr\{X \geqslant k\} = \sum_{i = k}^{n}b(i; n, p) \leqslant {n \choose k} p^k$。

**推论 C.3** 考虑$n$次伯努利试验的序列，其中成功概率为$p$。若$X$是表示成功次数的随机变量，则对$0 \leqslant k \leqslant n$，至多成功$k$次的概率为：$Pr\{X \leqslant k\} = \sum_{i = 0}^{k}b(i; n, p) \leqslant {n \choose n - k}(1 - p)^{n - k} = {n \choose k}(1 - p)^{n - k}$。

**定理 C.4** 考虑$n$次伯努利试验序列，其中成功概率为$p$，失败概率为$q = 1 - p$。令$X$为表示总成功数的随机变量，则对于$0 < k < np$，少于$k$次成功的概率为：$Pr\{X < k\} = \sum_{i = 0}^{k - 1}b(i; n, p) < \frac{kq}{np - k}b(k; n, p)$。

**推论 C.5** 考虑$n$次伯努利试验，其成功概率为$p$，失败概率为$q = 1 - p$，则对于$0 < k \leqslant np/2$，少于$k$次成功的概率小于少于$k + 1$次成功的概率的一半。

**推论 C.6** 考虑$n$次伯努利试验，其中成功概率为$p$。令$X$为表示成功次数的随机变量，则对于$np < k < n$，获得多于$k$次成功的概率为：$Pr\{X > k\} = \sum_{i = k + 1}^{n}b(i; n, p) < \frac{(n - k)p}{k - np}b(k; n, p)$。

**推论 C.7** 考虑$n$次伯努利试验，其中成功概率为$p$，失败概率为$q = 1 - p$，则对于$(np + n)/2 < k < n$，多于$k$次成功的概率要小于多于$k - 1$次成功的概率的一半。

**定理 C.8** 考虑$n$次伯努利试验，其中在第$i(i = 1, 2, ..., n)$次试验中，成功概率为$p_i$，失败概率为$q_i = 1 - p_i$。令$X$为表示成功总次数的随机变量，并令$\mu = E[X]$。那么，对于$r > \mu$，$Pr\{X - \mu \geqslant r\} \leqslant (\frac{\mu e}{r})^r$。

**推论 C.9** 考虑$n$次伯努利试验的序列，其中每次试验成功概率为$p$，失败概率为$q = 1 - p$，则对$r > np$，$Pr\{X - np \geqslant r\} = \sum_{k = \lceil np + r \rceil}^{n} b(k; n, p) \leqslant (\frac{npe}{r})^r$。



