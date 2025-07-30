# 1 Matrices and Systems of Equations

[TOC]



## System of Linear Equations

A `linear equation in n unknowns` is an equation of the form:
$$
a_{1}x_{1} + a_{2}x_{2} + \cdots + a_{n}x_{n} = b
$$
, where $a_1, a_2, ..., a_n$ and $b$ are real numbers and $x_1, x_2, ..., x_n$ are variables. A `linear system` of $m$ equations in $n$ unknowns is then a system of the form:
$$
a_{11}x_{1} + a_{12}x_{2} + \cdots + a_{1n}x_{n} = b_{1} \\
a_{21}x_{1} + a_{22}x_{2} + \cdots + a_{2n}x_{n} = b_{2} \\
\vdots \\
a_{m1}x_{1} + a_{m2}x_{2} + \cdots + a_{mn}x_{n} = b_{m} 
$$
, where the $a_{ij}$'s and the $b_{i}$'s are all real numbers.

By a solution of an $m \times n$ system, we mean an ordered $n$-tuple of numbers $(x_1, x_2, ..., x_n)$ that satisfies all the equations of the system.

If a linear system has no solution, we say that the system is `inconsistent`. If the system has at least one solution, we say that it is `consistent`.

The set of all solutions of a linear system is called the `solution set` of the system. If a system is inconsistent, its solution set is empty. A consistent system will have a nonempty solution set. To solve a consistent system, we must find its solution set.

**Definition** Two systems of equations involving the same variables are said to be **equivalent** if they have the same solution set.

There are three operations that can be used on a system to obtain an equivalent system:

1. The order in which any two equations are written may be interchanged.
2. Both sides of an equation may be multiplied by the same nonzero real number.
3. A multiple of one equation may be added to (or subtracted from) another.

**Definition** A system is said to be in **strict triangular form** if, in the $k$th equation, the coefficients of the first $k - 1$ variables are all zero and the coefficient of $x_{k}$ is nonzero $(k = 1, ..., n)$.

Any $n \times n$ strictly triangular system can be solved by `back substitution`: First, the $n$th equation is solved for the value of $x_{n}$. This value is used in the $(n - 1)$st equation to solve for $x_{n - 1}$. The values $x_{n}$ and $x_{n - 1}$ are used in the $(n - 2)$nd equation to solve for $x_{n - 2}$, and so on.

The term `matrix` means a rectangular array of numbers. A matrix having $m$ rows and $n$ columns is said to be $m \times n$. A matrix is said to be `square` if it has the same number of rows and columns, that is, if $m = n$.

If we attach to the coefficient matrix an additional column whose entries are the numbers on the right-hand side of the system, we obtain the new matrix:
$$
\begin{bmatrix}
1 & 2 & 1 &| & 3 \\
3 & -1 & -3 &| & -1 \\
2 & 3 & 1 &| & 4
\end{bmatrix}
$$
, we will refer to this new matrix as the `augmented matrix`. In general, when an $m \times r$ matrix $B$ is attached to an $m \times n$ matrix $A$ in this way, the augmented matrix is denoted by $(A|B)$. Thus, if:
$$
A =
\begin{bmatrix}
a_{11} & a_{12} & \dots & a_{1n}\\
a_{21} & a_{22} & \dots & a_{2n}\\
\vdots \\
a_{m1} & a_{m2} & \dots & a_{mn}\\
\end{bmatrix},

B =
\begin{bmatrix}
b_{11} & b_{12} & \dots & b_{1r}\\
b_{21} & b_{22} & \dots & b_{2r}\\
\vdots \\
b_{m1} & b_{m2} & \dots & b_{mr}\\
\end{bmatrix},
$$
, then:
$$
(A|B) = \\
\begin{bmatrix}
a_{11} & \dots & a_{1n} &| & b_{11} & \dots & b_{1r} \\
\vdots \\
a_{m1} & \dots & a_{mn} &| & a_{m1} & \dots & a_{mr} \\
\end{bmatrix}
$$
, with each system of equations, we may associate an augmented matrix of the form:
$$
\begin{bmatrix}
a_{11} & \dots & a_{1n} &| & b_{11} \\
\vdots \\
a_{m1} & \dots & a_{mn} &| & a_{m1}  \\
\end{bmatrix}
$$
The following row operations may be applied to the augmented matrix:

1. Interchange two rows.
2. Multiply a row by a nonzero real number.
3. Replace a row by the sum of that row and multiple of another row.

In general, if an $n \times n$ linear system can be reduced to strictly triangular form, then it will have a unique solution that can be obtained by performing back substitution on the triangular system.
