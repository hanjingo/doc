[English](arithmetic.md) | 中文版

# 算术

[TOC]



## 定义

**定义**：如果$a$和$b$是是整数且$a \neq 0$，我们称$a$整除$b$如果有整数$c$使得$b = ac$，或者等价地，如果$b/a$是一个整数。当$a$整除$b$时，我们称$a$是$b$的一个因子或除数，而$b$是$a$的一个倍数。用记号$a \mid b$表示$a$整除$b$。当$a$不能整除$b$时则写成$a \nmid b$​。

**定义**：在除法算法的等式中，$d$称为是除数，$a$称为是被除数，$q$称为是商，$r$称为是余数。下面的记号用来表示商和余数：
$$
q = a \text{ div } d, r = a \text{ mod } d
$$




## 定理

**定理** 令$a$, $b$, $c$为整数，其中$a \neq 0$。则：

- 如果$a \mid b$ 和 $a \mid c$, 则 $a \mid (b + c)$。
- 如果$a \mid b$，那么对所有整数 $c$ 都有 $a \mid bc$。
- 如果 $a \mid b$, $b \mid c$，则$a \mid c$。

**定理** 除法算法（division algorithm）。令$a$为整数，$d$为正整数。则存在唯一的整数$q$和$r$，满足$0 \leq r < d$，使得$a = dq + r$。



## 推论

**推论** 如果$a$, $b$, $c$是整数，其中$a \neq 0$，使得$a \mid b$ 和 $a \mid c$，那么当$m$和$n$是整数时有$a \mid mb + nc$。



## 引用

[1] Kenneth H. Rosen . 离散数学及其应用 . 8Edition
