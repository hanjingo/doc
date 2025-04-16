# Matrix

[TOC]



## Definition

**Definition**: A `matrix` is a rectangular array of numbers. A matrix with `m rows` and `n` columns is called an $m \times n$ matrix. The plural of matrix is `matrices`. A matrix with the same number of rows as columns is called `squal`. Two matrices are `equal` if they have the same number of rows and the same number of columns and the corresponding entries in every position are equal.

**Definition** Let $m$ and $n$ be positive integers and let
$$
A = 
\begin{bmatrix}
a_{11} & a_{12} & \dots & a_{1n} \\
a_{21} & a_{22} & \dots & a_{2n} \\
\vdots & \vdots &       & \vdots \\
a_{m1} & a_{m2} & \dots & a_{mn}
\end{bmatrix}
$$
, The $i$th row of **A** is the $1 \times n$ matrix $[a_{i1}, a_{i2}, ..., a_{in}]$. The $j$th column of $A$ is the $m \times 1$ matrix:
$$
\begin{bmatrix}
a_{1j} \\
a_{2j} \\
\vdots \\
a_{mj}
\end{bmatrix}
$$
, The $(i, j)$th `element` or `entry` of $A$ is the element $a_{ij}$, that is, the number in the $i$th row and $j$th column of $A$. A convenient shorthand notation for expressing the matrix $A$ is to write $A = [a_{ij}]$, which indicates that $A$ is the matrix with its $(i,j)$th element equal to $a_{ij}$.

**Definition**: Let $A = [a_{ij}]$ and $B = [b_{ij}]$ be $m \times n$ matrices. The `sum of A` and `B`, denoted by $A + B$, is the $m \times n$ matrix that has $a_{ij} + b_{ij}$ as its $(i,j)$th element. In other words, $A + B = [a_{ij} + b_{ij}]$.

**Definition**: Let $A$ be an $m \times k$ matrix and $B$ be a $k \times n$ matrix. The `product` of $A$ and $B$, denoted by $AB$, is the $m \times n$ matrix with its $(i, j)$th entry equal to the sum of the products of the corresponding elements from the $i$th row of $A$ and the $j$th column of $B$. In other words, if $AB = [c_{ij}]$, then $c_{ij} = a_{i1}b_{1j} + a_{i2}b_{2j} + ... + a_{ik}b_{kj}$.

**Definition**: The `identity matrix of order n` is the $n \times n$ matrix $I_n = [\delta_{ij}]$, (the `Kronecker delta`) where $\delta_{ij} = 1$ if $i = j$ and $\delta_{ij} = 0$ if $i \neq j$. Hence:
$$
I_n = 
\begin{bmatrix}
1 & 0 & \dots & 0 \\
0 & 1 & \dots & 0 \\
\vdots & \vdots & & \vdots \\
0 & 0 & \dots & 1
\end{bmatrix}
$$
**Definition**: Let $A = [a_{ij}]$ be an $m \times n$ matrix. The `transpose` of $A$, denoted by $A^t$, is the $n \times m$ matrix obtained by interchanging the rows and columns of $A$. In other words, if $A^t = [b_{ij}]$, then $b_{ij} = a_{ji}$ for $i = 1, 2, ..., n$ and $j = 1, 2, ..., m$.

**Definition**: A square matrix $A$ is called `symmetric` if $A = A^t$. Thus, $A = [a_{ij}]$ is symmetric if $a_{ij} = a_{ji}$ for all $i$ and $j$ with $1 \leq i \leq n$ and $1 \leq j \leq n$.

A matrix all of whose entries are either 0 or 1 is called a **zero-one matrix**.

**Definition**: Let $A = [a_{ij}]$ and $B = [b_{ij}]$ be $m \times n$ zero-one matrices. Then the `join` of $A$ and $B$ is the zero-one matrix with $(i,j)$th entry $a_{ij} \vee b_{ij}$. The join of $A$ and $B$ is denoted by $A \vee B$. The `meet` of $A$ and $B$ is the zero-one matrix with $(i,j)$th entry $a_{ij} \wedge b_{ij}$. The meet of $A$ and $B$ is denoted by $A \wedge B$.

**Definition**: Let $A = [a_{ij}]$ be an $m \times k$ zero-one matrix and $B = [b_{ij}]$ be a $k \times n$ zero-one matrix. Then the `Boolean product` of $A$ and $B$, denoted by $A \odot B$, is the $m \times n$ matrix with $(i,j)$th entry $c_{ij}$ where: $c_{ij} = (a_{i1} \wedge b_{1j}) \vee (a_{i2} \wedge b_{2j}) \vee ... \vee (a_{ik} \wedge b_{kj})$.

**Definition**: Let $A$ be a square zero-one matrix and let $r$ be a positive integer. The $r$th `Boolean power` of $A$ is the Boolean product of $r$ factors of $A$. The $r$th Boolean product of $A$ is denoted by $A^{[r]}$. Hence:
$$
A^{[r]} = \underbrace{A \odot A \odot A \odot ... \odot A.}_{r\ times}
$$
, (This is well defined because the Boolean product of matrices is associative.) We also define $A^{[0]}$ to be $I_n$.



## References

[1] Kenneth H. Rosen . Discrete Mathematics and Its Applications . 8Edition