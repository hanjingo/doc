# Matrices and Systems of Equations

[TOC]



## Systems of Linear Equations

A **linear equation in n unknowns** is an equation of the form:
$$
a_1 x_1 + a_2 x_2 + \cdots + a_n x_n = b
$$
where $a_1, a_2, ..., a_n$ and $b$ are real numbers and $x_1, x_2, ..., x_n$ are variables. A `linear system` of $m$ equations in $n$ unknowns is then a system of the form:
$$
a_{11}x_{1} + a_{12}x_{2} + \cdots + a_{1n}x_{n} = b_1 \\
a_{21}x_{1} + a_{22}x_{2} + \cdots + a_{2n}x_{n} = b_2 \\
\vdots \\
a_{m1}x_{1} + a_{m2}x_{2} + \cdots + a_{mn}x_{n} = b_m
$$
where the $a_{ij}$'s and the $b_i$'s are all real numbers. We will refer to systems of. the above form as $m \times n$ linear systems.

By a **solution** of $m \times n$ system, we mean an ordered $n$-tuple of numbers $(x_1, x_2, ..., x_n)$ that satisfies all the equations of the system.

If a linear system has no solution, we say that the system is **inconsistent**.

If the system has at least one solution, we say tht it is **consistent**.

The set of all solutions of a linear system is called the **solution set** of the system. To solve a consistent system, we must find its solution set.

### Equivalent Systems

**Definition 1:** Two systems of equations involving the same variables are said to be **equivalent** if they have the same solutions set.

There are three operations that can be used on a system to obtain an equivalent system:

1. The order in which any two euqations are written may be interchanged

   For example, the systems:
   $$
   x_1 + 2x_2 = 4 \\
   3x_1 - x_2 = 2 \\
   4x_1 + x_2 = 6
   $$
   and
   $$
   4x_1 + x_2 = 6 \\
   3x_1 - x_2 = 2 \\
   x_1 + 2x_2 = 4
   $$
   are equivalent.

2. Both sides of an equation may be multiplied by the same nonzero real number

   For example, the systems:
   $$
   x_1 + x_2 + x_3 = 3 \\
   -2x_1 - x_2 + 4x_3 = 1
   $$
   and
   $$
   2x_1 + 2x_2 + 2x_3 = 6 \\
   -2x_1 - x_2 + 4x_3 = 1
   $$
   are equivalent.

3. A multiple of one equation may be added to (or subtracted from) another

   For example, the systems:
   $$
   a_{i1}x_1 + \cdots + a_{in}x_n = b_i \\
   a_{j1}x_1 + \cdots + a_{jn}x_n = b_j
   $$
   and
   $$
   a_{i1}x_1 + \cdots + a_{in}x_n = b_i \\
   (a_{j1} + \alpha a_{i1})x_1 + \cdots + (a_{jn} + \alpha a_{in})x_n = b_j + \alpha b_i
   $$
   are equivalent.

### n x n Systems

**Definition 2:** A system is said to be in **strict triangular form** if, in the $k$th equation, the coefficients of the first $k - 1$ variables are all zero and the coefficient of $x_k$ is nonzero ($k = 1, ..., n$).

For example: 

> The system
> $$
> \begin{equation}\begin{split}
> 3x_1 + 2x_2 + x_3 &= 1 \\
> x_2 - x_3 &= 2 \\
> 2x_3 &= 4
> \end{split}\end{equation}
> $$
> is in strict triangular form, since in the second equation the coefficients are 0, 1, -1, respectively, and in the third equation the coefficients are 0, 0, 2, respectively.

The term **matrix** means a rectangular array of numbers. A matrix having $m$ rows and $n$ columns is said to be $m \times n$. A matrix is said to be **square** if it has the same number of rows and columns, that is, if $m = n$.

In general, when an $m \times r$ matrix B is attached to an $m \times n$ matrix A, the **augmented matrix** is denoted by $(A | B)$. Thus, if 
$$
A = 
\begin{bmatrix}
a_{11} & a_{12} & \cdots & a_{1n} \\
a_{21} & a_{22} & \cdots & a_{2n} \\
\vdots \\
a_{m1} & a_{m2} & \cdots & a_{mn}
\end{bmatrix},

B = 
\begin{bmatrix}
b_{11} & b_{12} & \cdots & b_{1r} \\
b_{21} & b_{22} & \cdots & b_{2r} \\
\vdots \\
b_{m1} & b_{m2} & \cdots & b_{mr}
\end{bmatrix}
$$
then
$$
\left[\begin{array}{ccc|ccc}
a_{11} & \cdots & a_{1n} & b_{11} & \cdots & b_{1r} \\
\vdots &  &  & \vdots &  &  \\
a_{m1} & \cdots & a_{mn} & b_{m1} & \cdots & b_{mr}
\end{array}\right]
$$
With each system of equations, we may associate an augmented matrix of the form
$$
\left[\begin{array}{ccc|c}
a_{11} & \cdots & a_{1n} & b_{1} \\
\vdots &  & & \vdots \\
a_{m1} & \cdots & a_{mn} & b_{m}
\end{array}\right]
$$
In general, if an $n \times n$ linear system can be reduced to strictly triangular form, then it will have a unique solution that can be obtained by performing back substitution on the triangular system.

### Elementary Row Operations

1. Interchange two rows.
2. Multiply a row by a nonzero real number.
3. Replace a row by the sum of that row and a multiple of another row.

For example:

> $$
> \begin{equation}\begin{split}
> -x_2 - x_3 + x_4 &= 0 \\
> x_1 + x_2 + x_3 + x_4 &= 6 \\
> 2x_1 + 4x_2 + x_3 - 2x_4 &= -1 \\
> 3x_1 + x_2 + 2x_3 + 2x_4 &= 3
> \end{split}\end{equation}
> $$
>
> The augmented matrix for this system is:
> $$
> \left[\begin{array}{cccc|c}
> 0 & -1 & -1 & 1 & 0 \\
> 1 & 1 & 1 & 1 & 6 \\
> 2 & 4 & 1 & -2 & -1 \\
> 3 & 1 & -2 & 2 & 3
> \end{array}\right]
> $$
> Since it is not possible to eliminate any entries by using 0 as a pivot element, we will use row [operation 1](#Elementary Row Operations) to interchange the first two rows of the augmented matrix. The new first row will be the pivotal row and the pivot element will be 1:
> $$
> \left[\begin{array}{cccc|c}
> 1 & 1 & 1 & 1 & 6 \\
> 0 & -1 & -1 & 1 & 0 \\
> 2 & 4 & 1 & -2 & -1 \\
> 3 & 1 & -2 & 2 & 3
> \end{array}\right]
> $$
> Row [operation 3](#Elementary Row Operations) is then used twice to eliminate the two nonzero entries in the first column:
> $$
> \left[\begin{array}{cccc|c}
> 1 & 1 & 1 & 1 & 6 \\
> 0 & -1 & -1 & 1 & 0 \\
> 0 & 2 & -1 & -4 & -13 \\
> 0 & -2 & -5 & -1 & -15
> \end{array}\right]
> $$
> Next, the second row is used as the pivotal row to eliminate the entries in the second column below the pivot element -1:
> $$
> \left[\begin{array}{cccc|c}
> 1 & 1 & 1 & 1 & 6 \\
> 0 & -1 & -1 & 1 & 0 \\
> 0 & 0 & -3 & -2 & -13 \\
> 0 & 0 & -3 & -3 & -15
> \end{array}\right]
> $$
> Finally, the tired row is used as the pivotal row to eliminate the last element in the third column:
> $$
> \left[\begin{array}{cccc|c}
> 1 & 1 & 1 & 1 & 6 \\
> 0 & -1 & -1 & 1 & 0 \\
> 0 & 0 & -3 & -2 & -13 \\
> 0 & 0 & 0 & -1 & -2
> \end{array}\right]
> $$
> This augmented matrix represents a strictly triangular system. Solving by back substitution, we obtain the solution (2, -1, 3, 2).



## Row Echelon Form

The variables corresponding to the first nonzero elements in each row of the reduced matrix will be referred to as **lead variables**.

The remaining variables corresponding to the columns skipped in the reduction process will  be referred to as **free variables**.

For example:

> The system:
> $$
> \begin{equation}\begin{split}
> x_1 + x_2 + x_3 + x_4 + x_5 &= 1 \\
> x_3 + x_4 + 2x_5 &= 0 \\
> x_5 &= 3
> \end{split}\end{equation}
> $$
> Thus, $x_1, x_3$, and $x_5$ are the lead variables. $x_2$ and $x_4$ are the free variables.

**Definition 3:** A matrix is aid to be in **row echelon form** if:

1. The first nonzero entry in each nonzero row is **1**.
2. If row $k$ does not consist entirely of zeros, the number of leading zero entries in row $k + 1$ is greater than the number of leading zero entries in row $k$.
3. If there are rows whose entries are all zero they are below the rows having nonzero entries.

For example:

> The following matrices are not in row echelon form:
> $$
> \begin{bmatrix}
> 2 & 4 & 6 \\
> 0 & 3 & 5 \\
> 0 & 0 & 4
> \end{bmatrix},
> 
> \begin{bmatrix}
> 0 & 0 & 0 \\
> 0 & 1 & 0
> \end{bmatrix},
> 
> \begin{bmatrix}
> 0 & 1\\
> 1 & 0
> \end{bmatrix}
> $$
> The first matrix does not satisfy condition 1. The second matrix fails to satisfy condtion 3, and the third matrix fails to satisfy condition 2.

**Definition 4**: The process of using [row operations 1, 2, and 3](#Elementary Row Operations)  to transform a liner system into one whose augmented matrix is in row echelon form is called **Gaussian elimination**.

(**Note** that [row operation 2](#Elementary Row Operations) is necessary in order to scale the rows so that the leading coefficients are all 1. If the row echelon form of the augmented matrix contains a row of the form: 
$$
\left[\begin{array}{cccc|c}
0 & 0 & \cdots & 0 & 1 
\end{array}\right]
$$
the system is inconsistent. Otherwise, the system will be consistent. If the system is consistent and the nonzero rows of the row echelon form of the matrix form a strictly triangular system, the system will have a unique solution.)

### Overdetermined Systems

A linear system is said to be **overdetermined** if there are more equations than unknowns. Overdetermined systems are **usually** (but not always) inconsistent.

For example:

> The system:
> $$
> x_1 + x_2 = 1 \\
> x_1 - x_2 = 3 \\
> -x_1 + 2x_2 = -2
> $$
> By using Gaussian elimination to put these systems into row echelon form:
> $$
> \left[\begin{array}{cc|c}
> 1 & 1 & 1  \\
> 1 & -1 & 3  \\
> -1 & 2 & -2
> \end{array}\right]
> 
> \rightarrow
> 
> \left[\begin{array}{cc|c}
> 1 & 1 & 1  \\
> 0 & 1 & -1  \\
> 0 & 0 & 1
> \end{array}\right]
> $$
> The last row of the reduced matrix tells us that $0x_1 + 0x_2 = 1$. Since this is never possible, the system must be inconsistent.

### Underdetermined Systems

A system of $m$ linear equations in $n$ unknowns is said to be **underdetermined** if there are fewer equations than unknowns ($m < n$).

*(Although it is possible for underdetermined systems to be inconsistent, they are usually consistent with infinitely many solutions. It is not possible for an underdetermined system to have a unique solution. The reason for this is that any row echelon form of the coefficient matrix will involve $r \leq m$ nonzero rows. Thus, there will be $r$ lead variables and $n - r$ free variables, where $n - r \geq n - m > 0$. If the system is consistent, we can assign the free variables arbitrary values and solve for the lead variables. Therefore, a consistent underdetermined system will have infinitely many solutions.)*

For example:

> System:
> $$
> \left[\begin{array}{ccc|c}
> 1 & 2 & 1 & 1 \\
> 2 & 4 & 2 & 3 \\
> \end{array}\right]
> 
> \rightarrow
> 
> \left[\begin{array}{ccc|c}
> 1 & 2 & 1 & 1 \\
> 0 & 0 & 0 & 1 \\
> \end{array}\right]
> $$
> is inconsistent.

### Reduced Row Echelon Form

**Definition 5** A matrix is said to be in **reduced row echelon form** if:

1. The matrix is in row echelon form.
2. The first nonzero entry in each **row** is the only nonzero entry in its **column**.

For example:

> The following matrices are in reduced row echelon form:
> $$
> \begin{bmatrix}
> 1 & 0 \\
> 0 & 1
> \end{bmatrix},
> 
> \begin{bmatrix}
> 1 & 0 & 0 & 3 \\
> 0 & 1 & 0 & 2 \\
> 0 & 0 & 1 & 1
> \end{bmatrix},
> 
> \begin{bmatrix}
> 0 & 1 & 2 & 0 \\
> 0 & 0 & 0 & 1 \\
> 0 & 0 & 0 & 0
> \end{bmatrix},
> 
> \begin{bmatrix}
> 1 & 2 & 0 & 1 \\
> 0 & 0 & 1 & 3 \\
> 0 & 0 & 0 & 0
> \end{bmatrix}
> $$

The process of using elementary row operations to transform a matrix into reduced row echelon form is called **Gauss-Jordan reduction**.

For example:

> Solve the system: 
> $$
> \begin{equation}\begin{split}
> -x_1 + x_2 - x_3 + 3x_4 &= 0 \\
> 3x_1 + x_2 - x_3 - x_4 &= 0 \\
> 2x_1 - x_2 - 2x_3 - x_4 &= 0
> \end{split}\end{equation}
> $$
> By Using Gauss-Jordan reduction:
> $$
> \left[\begin{array}{cccc|c}
> -1 & 1 & -1 & 3 & 0 \\
> 3 & 1 & -1 & -1 & 0 \\
> 2 & -1 & -2 & -1 & 0 
> \end{array}\right]
> 
> \rightarrow
> 
> \left[\begin{array}{cccc|c}
> -1 & 1 & -1 & 3 & 0 \\
> 0 & 4 & -4 & 8 & 0 \\
> 0 & 1 & -4 & 5 & 0 \\
> \end{array}\right]
> 
> \rightarrow
> 
> \left[\begin{array}{cccc|c}
> -1 & 1 & -1 & 3 & 0 \\
> 0 & 4 & -4 & 8 & 0 \\
> 0 & 0 & -3 & 3 & 0 \\
> \end{array}\right]
> 
> \\
> \rightarrow
> 
> \left[\begin{array}{cccc|c}
> 1 & -1 & 1 & -3 & 0 \\
> 0 & 1 & -1 & 2 & 0 \\
> 0 & 0 & 1 & -1 & 0 \\
> \end{array}\right]
> 
> \rightarrow
> 
> \left[\begin{array}{cccc|c}
> 1 & -1 & 0 & -2 & 0 \\
> 0 & 1 & 0 & 1 & 0 \\
> 0 & 0 & 1 & -1 & 0 \\
> \end{array}\right]
> 
> \rightarrow
> 
> \left[\begin{array}{cccc|c}
> 1 & 0 & 0 & -1 & 0 \\
> 0 & 1 & 0 & 1 & 0 \\
> 0 & 0 & 1 & -1 & 0 \\
> \end{array}\right]
> $$
> If we set $x_4$ equal to any real number $\alpha$, then $x_1 = \alpha, x_2 = -\alpha$, and $x_3 = \alpha$. Thus, all ordered 4-tuples of the form ($\alpha, -\alpha, \alpha, \alpha$) are solutions of the system.

### Homogeneous Systems

A system of linear equations is said to be **homogeneous** if the constants on the right-hand side are all zero.

*(Homogeneous systems are always consistent. It is straightforward to find a solution; just set all the variables equal to zero. Thus, if an $m \times n$ A homogeneous system has a unique solution; it must be the trivial solution (0, 0, ..., 0).)*

For example:

> The homogeneous system:
> $$
> \left[\begin{array}{cccc|c}
> -1 & 1 & -1 & 3 & 0 \\
> 3 & 1 & -1 & -1 & 0 \\
> 2 & -1 & -2 & -1 & 0 
> \end{array}\right]
> $$
> consisted of $m = 3$ equations in $n = 4$ unknowns.

 **Theorem 1**: An $m \times n$ homogeneous system of linear equations has a nontrivial solution if n > m. 



## Matrix Arithmetic

The entries of a matrix are called **scalars**. (They are usually either real or complex numbers.)

### Matrix Notation

If we wish to refer to matrices without specifically writing out all their entries, we will use uppercase A, B, C, and so on. In general, $a_{ij}$ will denote the entry of the matrix A that is in the $i$th row and the $j$th column. We will refer to this entry as the ($i$, $j$) entry of A. Thus, if A is an $m \times n$ matrix, then:
$$
A =
\begin{bmatrix}
a_{11} & a_{12} & \cdots & a_{1n} \\
a_{21} & a_{22} & \cdots & a_{2n} \\
\vdots \\
a_{m1} & a_{m2} & \cdots & a_{mn}
\end{bmatrix}
$$
We will sometime shorten this to $A = (a_{ij})$. Similarly, a matrix B may be referred to as ($b_{ij}$), amatrix C as ($c_{ij}$), and so on.

### Vectors

Matrices that have only one row or one column are of special interest, since they are used to represent solutions of linear systems. A solution of a system of $m$ linear equations in $n$ unknown is an $n$-tuple of real numbers. We will refer to an $n$-tuple of real numbers as a **vector**. If an $n$-tuple is represented in terms of a $1 \times n$ matrix, then we will refer to it as a **row vector**. Alternatively, if the $n$-tuple is represented by an $n \times 1$ matrix, then we will refer to it as a **column vector**.

For example:

> The solution of the linear system:
> $$
> x_1 + x_2 = 3 \\
> x_1 - x_2 = 1
> $$
> can be represented by the row vector $(2, 1)$ or the column vector $\begin{bmatrix} 2 \\ 1 \end{bmatrix}$.

The set of all $n \times 1$ matrices of real numbers is called **Euclidean n-space** and is usually denoted by $\mathbb{R}^n$. 

If A is an $m \times n$ matrix, then the row vectors of A are given by:
$$
\vec{a_i} = (a_{i1}, a_{i2}, ..., a_{in})\quad i = 1, ..., m
$$
and the column vectors are given by:
$$
a_j = \begin{bmatrix}
y_1 \\
y_2 \\
y_3 \\
y_4
\end{bmatrix}

\quad

j = 1, ..., n
$$
The matrix A can be represented in terms of either its column vectors or its row vectors:
$$
A = (a_1, a_2, ..., a_n) \text{ or } A = \begin{bmatrix}
\vec{a_1} \\
\vec{a_2} \\
\vdots \\
\vec{a_m}
\end{bmatrix}
$$
Similarly, if B is an $n \times r$ matrix, then:
$$
B = (b_1, b_2, ..., b_r) = \begin{bmatrix}
\vec{b_1} \\
\vec{b_2} \\
\vdots \\
\vec{b_n}
\end{bmatrix}
$$
For example:

> If:
>
> $$
> A = \begin{bmatrix}
> 3 & 2 & 5 \\
> -1 & 8 & 4
> \end{bmatrix}
> $$
>
> Then:
> $$
> a_1 =
> \begin{bmatrix}
> 3 \\
> -1
> \end{bmatrix},
> 
> a_2 = 
> \begin{bmatrix}
> 2 \\
> 8
> \end{bmatrix},
> 
> a_3 = 
> \begin{bmatrix}
> 5 \\
> 4
> \end{bmatrix}
> $$
> and
> $$
> \vec{a_1} = (3, 2, 5), \vec{a_2} = (-1, 8, 4)
> $$

### Equality

**Definition 6** Two $m \times n$ matrices A and B are said to be **equal** if $a_{ij} = b_{ij}$ for each $i$ and $j$.

### Scalar Multiplication

**Definition 7** If A is an $m \times n$ matrix and $\alpha$ is a scalar, then $\alpha A$ is the $m \times n$ matrix whose ($i, j$) entry is $\alpha a_{ij}$.

For example:

> If:
> $$
> A = \begin{bmatrix}
> 4 & 8 & 2 \\
> 6 & 8 & 10
> \end{bmatrix}
> $$
> then
> $$
> \frac{1}{2}A = 
> \begin{bmatrix}
> 2 & 4 & 1 \\
> 3 & 4 & 5
> \end{bmatrix}
> 
> \text{ and }
> 
> 3A = 
> \begin{bmatrix}
> 12 & 24 & 6 \\
> 18 & 24 & 30
> \end{bmatrix}
> $$
> 

### Matrix Addition

**Definition 8** If $A = (a_{ij})$ and $B = (b_{ij})$ are both $m \times n$ matrices, then the sum $A + B$ is the $m \times n$ matrix whose ($i, j$) entry is $a_{ij} + b_{ij}$ for each ordered pair ($i, j$).

For example:

> $$
> \begin{bmatrix}
> 3 & 2 & 1 \\
> 4 & 5 & 6
> \end{bmatrix}
> + 
> \begin{bmatrix}
> 2 & 2 & 2 \\
> 1 & 2 & 3
> \end{bmatrix}
> = 
> \begin{bmatrix}
> 5 & 4 & 3 \\
> 5 & 7 & 9
> \end{bmatrix}
> $$

If $O$ represents the matrix, with the same dimensions as A, whose entries are all 0, then
$$
A + O = O + A = A
$$
We will refer to $O$ as the **zero matrix**. It acts as an additive identity on the set of all $m \times n$ matrices. Furthermore, each $m \times n$ matrix A has an additive inverse. Indeed,
$$
A + (-1)A = O = (-1)A + A
$$
It is customary to denote the additive inverse by $-A$. Thus,
$$
-A = (-1)A
$$

### Linear Systems

**Definition 9** If $a_1, a_2, ..., a_n$ are vectors in $\mathbb{R}^m$ and $c_1, c_2, ..., c_n$ are scalars, then a sum of the form $c_1 a_1 + c_2 a_2 + \cdots + c_n a_n$ is said to be a **linear combination** of the vectors $a_1, a_2, \cdots, a_n$.

*(If A is an $m \times n$ matrix and x is a vector in $\mathbb{R}^n$, then $Ax = x_1 a_1 + x_2 a_2 + \cdots + x_n a_n $)*

**Theorem 2** (Consistency Theorem for Linear Systems): A linear system $Ax = b$ is consistent if and only if $b$ can be written as a linear combination of the column vectors of A.

For example:

> The linear system:
> $$
> x_1 + 2x_2 = 1 \\
> 2x_1 + 4x_2 = 1
> $$
> is inconsistent since the vector $\begin{bmatrix} 1 \\ 1 \end{bmatrix}$ cannot be written as a linear combination of the column vectors $\begin{bmatrix} 1 \\ 2 \end{bmatrix}$ and $\begin{bmatrix} 2 \\ 4 \end{bmatrix}$. Note that any linear combination of these vectors would be of the form:
> $$
> x_1 
> \begin{bmatrix} 
> 1 \\ 
> 2 
> \end{bmatrix}
> 
> + 
> 
> x_2
> \begin{bmatrix} 
> 2 \\ 
> 4 
> \end{bmatrix}
> 
> = 
> 
> \begin{bmatrix} 
> x_1 + 2x_2 \\ 
> 2x_1 + 4x_2
> \end{bmatrix}
> $$
> and hence the second entry of the vector must be double the first entry.

### Matrix Multiplication

**NOTE: More generally, it is possible to multiply a matrix A times a matrix B if the number of columns of A equals the number of rows of B.**

**Definition 10** If $A = (a_{ij})$ is an $m \times n$ matrix and $B = (b_{ij})$ is an $n \times r$ matrix, then the product $AB = C = (c_{ij})$ is the $m \times r$ matrix whose entries are defined by $c_{ij} = \vec{a_i}b_j = \sum_{k = 1}^{n}a_{ik}b_{kj}$.

For example:

> If
> $$
> A =
> \begin{bmatrix} 
> 3 & -2 \\ 
> 2 & 4 \\
> 1 & -3
> \end{bmatrix}
> \text{ and }
> B = 
> \begin{bmatrix} 
> -2 & 1 & 3 \\ 
> 4 & 1 & 6
> \end{bmatrix}\\
> $$
> then
> $$
> \begin{equation}\begin{split}
> AB &= 
> \begin{bmatrix} 
> 3 & -2 \\ 
> 2 & 4 \\
> 1 & -3
> \end{bmatrix}
> \begin{bmatrix} 
> -2 & 1 & 3 \\ 
> 4 & 1 & 6
> \end{bmatrix} \\
> &=
> \begin{bmatrix} 
> 3 \cdot (-2) - 2 \cdot 4 & 3 \cdot 1 - 2 \cdot 1 & 3 \cdot 3 - 2 \cdot 6 \\ 
> 2 \cdot (-2) + 4 \cdot 4 & 2 \cdot 1 + 4 \cdot 1 & 2 \cdot 3 + 4 \cdot 6 \\
> 1 \cdot (-2) - 3 \cdot 4 & 1 \cdot 1 - 3 \cdot 1 & 1 \cdot 3 - 3 \cdot 6
> \end{bmatrix} \\
> &=
> \begin{bmatrix} 
> -14 & 1 & -3 \\ 
> 12 & 6 & 30 \\
> -14 & -2 & -15
> \end{bmatrix}
> \end{split}\end{equation}
> $$
>
> $$
> \begin{equation}\begin{split}
> BA &= 
> \begin{bmatrix} 
> -2 & 1 & 3 \\ 
> 4 & 1 & 6
> \end{bmatrix}
> \begin{bmatrix} 
> 3 & -2 \\ 
> 2 & 4 \\
> 1 & -3
> \end{bmatrix} \\
> &=
> \begin{bmatrix} 
> -2 \cdot 3 + 1 \cdot 2 + 3 \cdot 1 & -2 \cdot (-2) + 1 \cdot 4 + 3 \cdot (-3) \\
> 4 \cdot 3 + 1 \cdot 2 + 6 \cdot 1 & 4 \cdot (-2) + 1 \cdot 4 + 6 \cdot (-3) \\
> \end{bmatrix} \\
> &=
> \begin{bmatrix} 
> -1 & -1 \\ 
> 20 & -22
> \end{bmatrix}
> \end{split}\end{equation}
> $$

**Notice**: If A and B are both $n \times n$ matrices, then AB and BA will also be $n \times n$ matrices, but, in general, they will not be equal. **Multiplication of matrices** is **not** commutative.

For example:

> If
> $$
> A =
> \begin{bmatrix} 
> 1 & 1 \\ 
> 0 & 0
> \end{bmatrix}
> $$
> and
> $$
> B =
> \begin{bmatrix} 
> 1 & 1 \\ 
> 2 & 2
> \end{bmatrix}
> $$
> then
> $$
> AB =
> \begin{bmatrix} 
> 1 & 1 \\ 
> 0 & 0
> \end{bmatrix}
> \begin{bmatrix} 
> 1 & 1 \\ 
> 2 & 2
> \end{bmatrix}
> =
> \begin{bmatrix} 
> 3 & 3 \\ 
> 0 & 0
> \end{bmatrix}
> $$
> and
> $$
> BA =
> \begin{bmatrix} 
> 1 & 1 \\ 
> 2 & 2
> \end{bmatrix}
> \begin{bmatrix} 
> 1 & 1 \\ 
> 0 & 0
> \end{bmatrix}
> =
> \begin{bmatrix} 
> 1 & 1 \\ 
> 2 & 2
> \end{bmatrix}
> $$
> Hence, $AB \neq BA$.

### Notational Rules

Just as in ordinary algebra, if an expression involves both multiplication and addition and there are no parentheses to indicate the order of the operations, **multiplications are carried out before additions**. This is true for both scalar and matrix multiplications.

For example:

> If
> $$
> A =
> \begin{bmatrix} 
> 3 & 4 \\ 
> 1 & 2
> \end{bmatrix},
> B =
> \begin{bmatrix} 
> 1 & 3 \\ 
> 2 & 1
> \end{bmatrix},
> C = 
> \begin{bmatrix} 
> -2 & 1 \\ 
> 3 & 2
> \end{bmatrix}
> $$
> then
> $$
> A + BC = 
> \begin{bmatrix} 
> 3 & 4 \\ 
> 1 & 2
> \end{bmatrix}
> +
> \begin{bmatrix} 
> 7 & 7 \\ 
> -1 & 4
> \end{bmatrix}
> =
> \begin{bmatrix} 
> 10 & 11 \\ 
> 0 & 6
> \end{bmatrix}
> $$
> and
> $$
> 3A + B = 
> \begin{bmatrix} 
> 9 & 12 \\ 
> 3 & 6
> \end{bmatrix}
> +
> \begin{bmatrix} 
> 1 & 3 \\ 
> 2 & 1
> \end{bmatrix}
> =
> \begin{bmatrix} 
> 10 & 15 \\ 
> 5 & 7
> \end{bmatrix}
> $$

### The Transpose of a Matrix

**Definition 11** The **transpose** of an $m \times n$ matrix A is the $n \times m$ matrix B defined by $b_{ji} = a_{ij}$, for $j = 1, ..., n$ and $i = 1, ..., m$. The transpose of A is denoted by $A^{T}$.

For example:

> If
> $$
> A =
> \begin{bmatrix} 
> 1 & 2 & 3 \\ 
> 4 & 5 & 6
> \end{bmatrix}
> $$
> then
> $$
> A^T = 
> \begin{bmatrix} 
> 1 & 4 \\ 
> 2 & 5 \\
> 3 & 6
> \end{bmatrix}
> $$

**Definition 12** An $n \times n$ matrix A is said to be **symmetric** if $A^T = A$.

For example:

> The following are some examples of symmetric matrices:
> $$
> \begin{bmatrix} 
> 1 & 0 \\ 
> 0 & -4
> \end{bmatrix},
> \begin{bmatrix} 
> 2 & 3 & 4 \\ 
> 3 & 1 & 5 \\
> 4 & 5 & 3
> \end{bmatrix},
> \begin{bmatrix} 
> 0 & 1 \\ 
> 0 & -4
> \end{bmatrix},
> $$
> 



## Matrix Algebra

**WARNING:** In general, $AB \neq BA$. Matrix multiplication is **not commutative**.

### Algebraic Rules

**Theorem 3**: Each of the following statements is valid for any scalars $\alpha$ and $\beta$ and for any matrices A, B, and C for which the indicated operations are defined:

1. $A + B = B + A$
2. $(A + B) + C = A + (B + C)$
3. $(AB)C = A(BC)$
4. $A(B + C) = AB + AC$
5. $(A + B)C = AC + BC$
6. $(\alpha \beta)A = \alpha(\beta A)$
7. $\alpha(AB) = (\alpha A)B = A(\alpha B)$
8. $(\alpha + \beta)A = \alpha A + \beta A$
9. $\alpha(A + B) = \alpha A + \alpha B$

For example:

> If:
> $$
> A =
> \begin{bmatrix} 
> 1 & 2 \\ 
> 3 & 4
> \end{bmatrix},
> 
> B = 
> \begin{bmatrix} 
> 2 & 1 \\ 
> -3 & 2
> \end{bmatrix},
> 
> \text{ and }
> 
> C = 
> \begin{bmatrix} 
> 1 & 0 \\ 
> 2 & 1
> \end{bmatrix}
> $$
> verify that $A(BC) = (AB)C$ and $A(B + C) = AB + AC$.
>
> Solution:
> $$
> A(BC) = 
> \begin{bmatrix} 
> 1 & 2 \\ 
> 3 & 4
> \end{bmatrix}
> \begin{bmatrix} 
> 4 & 1 \\ 
> 1 & 2
> \end{bmatrix}
> =
> \begin{bmatrix} 
> 6 & 5 \\ 
> 16 & 11
> \end{bmatrix}
> $$
>
> $$
> (AB)C = 
> \begin{bmatrix} 
> -4 & 5 \\ 
> -6 & 11
> \end{bmatrix}
> \begin{bmatrix} 
> 1 & 0 \\ 
> 2 & 1
> \end{bmatrix}
> =
> \begin{bmatrix} 
> 6 & 5 \\ 
> 16 & 11
> \end{bmatrix}
> $$
>
> Thus,
> $$
> A(BC) = 
> \begin{bmatrix} 
> 6 & 5 \\ 
> 16 & 11
> \end{bmatrix}
> = (AB)C
> $$
>
> $$
> A(B + C) = 
> \begin{bmatrix} 
> 1 & 2 \\ 
> 3 & 4
> \end{bmatrix}
> \begin{bmatrix} 
> 3 & 1 \\ 
> -1 & 3
> \end{bmatrix}
> =
> \begin{bmatrix} 
> 1 & 7 \\ 
> 5 & 15
> \end{bmatrix}
> $$
>
> $$
> AB + AC = 
> \begin{bmatrix} 
> -4 & 5 \\ 
> -6 & 11
> \end{bmatrix}
> +
> \begin{bmatrix} 
> 5 & 2 \\ 
> 11 & 4
> \end{bmatrix}
> =
> \begin{bmatrix} 
> 1 & 7 \\ 
> 5 & 15
> \end{bmatrix}
> $$
>
> Therefore,
> $$
> A(B + C) = AB + AC
> $$

### Notation

In the case where an $n \times n$ matrix is multiplied by itself a number of times, it is convenient to use exponential notation. Thus, if $k$ is a positive integer, then:
$$
A^k = \underbrace{A A \cdots A}_{b\text{ times}}
$$
For example:

> If:
> $$
> A =
> \begin{bmatrix} 
> 1 & 1 \\ 
> 1 & 1
> \end{bmatrix}
> $$
> then
> $$
> A^2 =
> \begin{bmatrix} 
> 1 & 1 \\ 
> 1 & 1
> \end{bmatrix}
> \begin{bmatrix} 
> 1 & 1 \\ 
> 1 & 1
> \end{bmatrix}
> =
> \begin{bmatrix} 
> 2 & 2 \\ 
> 2 & 2
> \end{bmatrix}
> $$
>
> $$
> A^3 = AAA = AA^2 = 
> \begin{bmatrix} 
> 1 & 1 \\ 
> 1 & 1
> \end{bmatrix}
> \begin{bmatrix} 
> 2 & 2 \\ 
> 2 & 2
> \end{bmatrix}
> =
> \begin{bmatrix} 
> 4 & 4\\ 
> 4 & 4
> \end{bmatrix}
> $$
>
> and, in general,
> $$
> A^n = 
> \begin{bmatrix} 
> 2^{n - 1} & 2^{n - 1} \\ 
> 2^{n - 1} & 2^{n - 1}
> \end{bmatrix}
> $$

### The Identity Matrix

**Definition 12** The $n \times n$ **identity matrix** is the matrix $I = (\delta_{ij})$, where
$$
\delta_{ij} = 
\begin{cases}
1, &\text{if } i = j \\
0, &\text{if } i \neq j
\end{cases}
$$
*(The column vector of the $n \times n$ identity matrix $I$ are the standard vectors used to define a coordinate system in Euclidean $n$-space. The standard notation for the $j$th column vector if $I$ is $e_j$, rather than the usual $i_j$. Thus, the $n \times n$ An identity matrix can be written $I = (e_1, e_2, ..., e_n)$.)*

For example:

> $$
> \begin{bmatrix} 
> 1 & 0 & 0 \\ 
> 0 & 1 & 0 \\
> 0 & 0 & 1
> \end{bmatrix}
> \begin{bmatrix} 
> 3 & 4 & 1 \\ 
> 2 & 6 & 3 \\
> 0 & 1 & 8
> \end{bmatrix}
> =
> \begin{bmatrix} 
> 3 & 4 & 1 \\ 
> 2 & 6 & 3 \\
> 0 & 1 & 8
> \end{bmatrix}
> $$
>
> and
> $$
> \begin{bmatrix} 
> 3 & 4 & 1 \\ 
> 2 & 6 & 3 \\
> 0 & 1 & 8
> \end{bmatrix}
> \begin{bmatrix} 
> 1 & 0 & 0 \\ 
> 0 & 1 & 0 \\
> 0 & 0 & 1
> \end{bmatrix}
> =
> \begin{bmatrix} 
> 3 & 4 & 1 \\ 
> 2 & 6 & 3 \\
> 0 & 1 & 8
> \end{bmatrix}
> $$

### Matrix Inversion

**Definition 13** An $n \times n$ matrix A is said to be **nonsingular** or **invertible** if there exists a matrix B such that $AB = BA = I$. ($I$ is Identity Matrix) The matrix B is said to be a **multiplicative inverse** of A.

*(If B and C are both multiplicative inverses of A, then $B = BI = B(AC) = (BA)C = IC = C$. Thus, a matrix can have at most one multiplicative inverse. We will refer to the multiplicative inverse of a nonsingular matrix A as simply the **inverse** of A and denote it by $A^{-1}$.)*

For example:

> The matrices:
> $$
> \begin{bmatrix} 
> 2 & 4 \\ 
> 3 & 1
> \end{bmatrix}
> 
> \text{ and }
> 
> \begin{bmatrix} 
> -\frac{1}{10} & \frac{2}{5} \\ 
> \frac{3}{10} & -\frac{1}{5}
> \end{bmatrix}
> $$
> are inverses of each other, since
> $$
> \begin{bmatrix} 
> 2 & 4 \\ 
> 3 & 1
> \end{bmatrix}
> \begin{bmatrix} 
> -\frac{1}{10} & \frac{2}{5} \\ 
> \frac{3}{10} & -\frac{1}{5}
> \end{bmatrix}
> =
> \begin{bmatrix} 
> 1 & 0 \\ 
> 0 & 1
> \end{bmatrix}
> $$
> and
> $$
> \begin{bmatrix} 
> -\frac{1}{10} & \frac{2}{5} \\ 
> \frac{3}{10} & -\frac{1}{5}
> \end{bmatrix}
> \begin{bmatrix} 
> 2 & 4 \\ 
> 3 & 1
> \end{bmatrix}
> =
> \begin{bmatrix} 
> 1 & 0 \\ 
> 0 & 1
> \end{bmatrix}
> $$

**Definition 14** An $n \times n$ matrix is said to be **singular** if it does not have a multiplicative inverse.

*(**Note:** Only square matrices have multiplicative inverses. One should not use the terms **singular** and **nonsingular** when referring to nonsquare matrices.)*

**Theorem 4** If A and B are nonsingular $n \times n$ matrices, then AB is also **nonsingular** and $(AB)^{-1} = B^{-1}A^{-1}$.

### Algebraic Rules for Transposes

Algebraic Rules for Transposes:

1. $(A^T)^T = A$
2. $(\alpha A)^T = \alpha A^T$
3. $(A + B)^T = A^T + B^T$
4. $(AB)^T = B^T A^T$

For example:

> Let:
> $$
> A =
> \begin{bmatrix} 
> 1 & 2 & 1 \\ 
> 3 & 3 & 5 \\
> 2 & 4 & 1
> \end{bmatrix},
> B =
> \begin{bmatrix} 
> 1 & 0 & 2 \\ 
> 2 & 1 & 1 \\
> 5 & 4 & 1
> \end{bmatrix}
> $$
> Note that, on the one hand, the (3, 2) entry of AB is computed taking the scalar product of the third row of A and the second column of B.
> $$
> AB = 
> \begin{bmatrix} 
> 1 & 2 & 1 \\ 
> 3 & 3 & 5 \\
> 2 & 4 & 1
> \end{bmatrix}
> \begin{bmatrix} 
> 1 & 0 & 2 \\ 
> 2 & 1 & 1 \\
> 5 & 4 & 1
> \end{bmatrix}
> =
> \begin{bmatrix} 
> 10 & 6 & 5 \\ 
> 34 & 23 & 14 \\
> 15 & 8 & 9
> \end{bmatrix}
> $$
> When the product is transposed, the (3, 2) entry of AB becomes the (2, 3) entry of $(AB)^T$.
> $$
> (AB)^T = 
> \begin{bmatrix} 
> 10 & 34 & 15 \\ 
> 6 & 23 & 8 \\
> 5 & 14 & 9
> \end{bmatrix}
> $$
> On the other hand, the (2, 3) entry of $B^T A^T$ is computed by taking the scalar product of the second row of $B^T$ and the third column of $A^T$.
> $$
> B^T A^T =
> \begin{bmatrix} 
> 1 & 2 & 5 \\ 
> 0 & 1 & 4 \\
> 2 & 1 & 1
> \end{bmatrix}
> \begin{bmatrix} 
> 1 & 3 & 2 \\ 
> 2 & 3 & 4 \\
> 1 & 5 & 1
> \end{bmatrix}
> =
> \begin{bmatrix} 
> 10 & 34 & 15 \\ 
> 6 & 23 & 8 \\
> 5 & 14 & 9
> \end{bmatrix}
> $$
> In both caes, the arithmetic for computing the (2, 3) entry is the same.

### Symmetric Matrices and Networks

A matrix A is symmetric if $A^T = A$.

**Theorem 5** If A is an $n \times n$ adjacency matrix of a graph and $a_{ij}^{(k)}$ represents the ($i, j$) entry of $A^k$, then $a_{ij}^{(k)}$ is equal to the number of walks of length $k$ from $V_i$ to $V_j$.



## Elementary Matrices

### Equivalent Systems

Given an $m \times n$ linear system $Ax = b$, we can obtain an equivalent system by multiplying both sides of the equation by a nonsingular $m \times m$ matrix $M$:
$$
Ax = b \quad (1) \\
M Ax = M b \quad (2)
$$
Clearly, any solution of (1) will also be a solution of (2). However, if $\hat{x}$ is a solution of (2), then
$$
M^{-1}(M A\hat{x}) = M^{-1}(M b) \\
A\hat{x} = b
$$
and it follows that the two systems are equivalent.

### Elementary Matrices

If we start with the identity matrix $I$ and then perform exactly one elementary row operation, the resulting matrix is called an **elementary** matrix.

There are three types of elementary matrices corresponding to the three types of elementary row operations:

- Type 1: An elementary matrix of type $I$ is a matrix obtained by interchanging two rows of $I$.

  For example:

  > The matrix:
  >
  > $$
  > E_1 = 
  > \begin{bmatrix} 
  > 0 & 1 & 0 \\ 
  > 1 & 0 & 0 \\
  > 0 & 0 & 1
  > \end{bmatrix}
  > $$
  >
  > is an elementary matrix of type 1 since it was obtained by interchanging the first two rows of $I$. If A is a $3 \times$ matrix, then
  > $$
  > E_1 A =
  > \begin{bmatrix} 
  > 0 & 1 & 0 \\ 
  > 1 & 0 & 0 \\
  > 0 & 0 & 1
  > \end{bmatrix}
  > \begin{bmatrix} 
  > a_{11} & a_{12} & a_{13} \\ 
  > a_{21} & a_{22} & a_{23} \\
  > a_{31} & a_{32} & a_{33}
  > \end{bmatrix}
  > =
  > \begin{bmatrix} 
  > a_{21} & a_{22} & a_{23} \\ 
  > a_{11} & a_{12} & a_{13} \\
  > a_{31} & a_{32} & a_{33}
  > \end{bmatrix}
  > $$
  >
  > $$
  > A E_1 =
  > \begin{bmatrix} 
  > a_{11} & a_{12} & a_{13} \\ 
  > a_{21} & a_{22} & a_{23} \\
  > a_{31} & a_{32} & a_{33}
  > \end{bmatrix}
  > \begin{bmatrix} 
  > 0 & 1 & 0 \\ 
  > 1 & 0 & 0 \\
  > 0 & 0 & 1
  > \end{bmatrix}
  > =
  > \begin{bmatrix} 
  > a_{12} & a_{11} & a_{13} \\ 
  > a_{22} & a_{21} & a_{23} \\
  > a_{32} & a_{31} & a_{33}
  > \end{bmatrix}
  > $$
  >
  > Multiplying A on the left by $E_1$ interchanges the first and second rows of A. Right multiplication of A by $E_1$ is equivalent to the elementary column operation of interchanging the first and second columns.

- Type 2: An elementary matrix of type 2 is a matrix obtained by multiplying a row of $I$ by a nonzero constant.

  For example:

  > The matrix:
  > $$
  > E_2 =
  > \begin{bmatrix} 
  > 1 & 0 & 0 \\ 
  > 0 & 1 & 0 \\
  > 0 & 0 & 3
  > \end{bmatrix}
  > $$
  > is an elementary matrix of type 2. If A is a $3 \times 3$ matrix, then
  > $$
  > E_2 A =
  > \begin{bmatrix} 
  > 1 & 0 & 0 \\ 
  > 0 & 1 & 0 \\
  > 0 & 0 & 3
  > \end{bmatrix}
  > \begin{bmatrix} 
  > a_{11} & a_{12} & a_{13} \\ 
  > a_{21} & a_{22} & a_{23} \\
  > a_{31} & a_{32} & a_{33}
  > \end{bmatrix}
  > =
  > \begin{bmatrix} 
  > a_{11} & a_{12} & a_{13} \\ 
  > a_{21} & a_{22} & a_{23} \\
  > 3a_{31} & 3a_{32} & 3a_{33}
  > \end{bmatrix}
  > $$
  >
  > $$
  > A E_2 =
  > \begin{bmatrix} 
  > a_{11} & a_{12} & a_{13} \\ 
  > a_{21} & a_{22} & a_{23} \\
  > a_{31} & a_{32} & a_{33}
  > \end{bmatrix}
  > \begin{bmatrix} 
  > 1 & 0 & 0 \\ 
  > 0 & 1 & 0 \\
  > 0 & 0 & 3
  > \end{bmatrix}
  > =
  > \begin{bmatrix} 
  > a_{11} & a_{12} & 3a_{13} \\ 
  > a_{21} & a_{22} & 3a_{23} \\
  > a_{31} & a_{32} & 3a_{33}
  > \end{bmatrix}
  > $$
  >
  > Multiplication on the left by $E_2$ performs the elementary row operation of multiplying the third row by 3, while multiplication on the right by $E_2$ performs the elementary column operation of multiplying the third column by 3.

- Type 3: An elementary matrix of type 3 is a matrix obtained from $I$ by adding a multiple of one row to another row.

  For example:

  > The matrix:
  > $$
  > E_3 =
  > \begin{bmatrix} 
  > 1 & 0 & 3 \\ 
  > 0 & 1 & 0 \\
  > 0 & 0 & 1
  > \end{bmatrix}
  > $$
  > is an elementray matrix of type 3. If A is a $3 \times 3$ matrix, then
  > $$
  > E_3 A =
  > \begin{bmatrix} 
  > a_{11} + 3a_{31} & a_{12} + 3a_{32} & a_{13} + 3a_{33} \\ 
  > a_{21} & a_{22} & a_{23} \\
  > a_{31} & a_{32} & a_{33}
  > \end{bmatrix}
  > 
  > A E_3 =
  > \begin{bmatrix} 
  > a_{11} & a_{12} & 3a_{11} + a_{13} \\ 
  > a_{21} & a_{22} & 3a_{21} + a_{23} \\
  > a_{31} & a_{32} & 3a_{31} + a_{33}
  > \end{bmatrix}
  > $$
  > Multiplication on the left by $E_3$ adds 3 times the third row to the first row. Multiplication on the right adds 3 times the first column to the third column.

**Theorem 6** If $E$ is an elementary matrix, then $E$ is nonsingular and $E^{-1}$ is an **elementary matrix** of the same type.

**Definition 15** A matrix $B$ is **row equivalent** to a matrix $A$ if there exists a finite sequence $E_1, E_2, ..., E_k$ of elementary matrices such that $B = E_{k} E_{k - 1} \cdots E_1A$ .

(The following properties of row equivalent matrices are easily established:

1. If $A$ is row equivalent to $B$, then $B$ is row equivalent to $A$.
2. If $A$ is row equivalent to $B$, and $B$ is row equivalent to $C$, then $A$ is row equivalent to $C$.)

**Theorem 7** (Equivalent Conditions for Nonsingularity) Let $A$ be an $n \times n$ matrix. The following are equivalent:

1. $A$ is nonsingular.
2. $Ax = 0$ has only the trivial solution 0.
3. $A$ is row equivalent to $I$.

**Corollary 1** The system $Ax = b$ of $n$ linear equations in $n$ unknowns have a unique solution if and only if $A$ is nonsingular.

For example:

> Compute $A^{-1}$ if:
> $$
> A =
> \begin{bmatrix} 
> 1 & 4 & 3 \\ 
> -1 & -2 & 0 \\
> 2 & 2 & 3
> \end{bmatrix}
> $$
> Solution:
> $$
> \left[\begin{array}{ccc|ccc}
> 1 & 4 & 3 & 1 & 0 & 0 \\
> -1 & -2 & 0 & 0 & 1 & 0 \\
> 2 & 2 & 3 & 0 & 0 & 1 \\
> \end{array}\right]
> \rightarrow
> \left[\begin{array}{ccc|ccc}
> 1 & 4 & 3 & 1 & 0 & 0 \\
> 0 & 2 & 3 & 1 & 1 & 0 \\
> 0 & -6 & -3 & -2 & 0 & 1 \\
> \end{array}\right]
> \rightarrow
> \left[\begin{array}{ccc|ccc}
> 1 & 4 & 3 & 1 & 0 & 0 \\
> 0 & 2 & 3 & 1 & 1 & 0 \\
> 0 & 0 & 6 & 1 & 3 & 1 \\
> \end{array}\right]
> \rightarrow \\
> \left[\begin{array}{ccc|ccc}
> 1 & 4 & 0 & \frac{1}{2} & -\frac{3}{2} & -\frac{1}{2} \\
> 0 & 2 & 0 & \frac{1}{2} & -\frac{1}{2} & -\frac{1}{2} \\
> 0 & 0 & 6 & 1 & 3 & 1 \\
> \end{array}\right]
> \rightarrow 
> \left[\begin{array}{ccc|ccc}
> 1 & 0 & 0 & -\frac{1}{2} & -\frac{1}{2} & \frac{1}{2} \\
> 0 & 2 & 0 & \frac{1}{2} & -\frac{1}{2} & -\frac{1}{2} \\
> 0 & 0 & 6 & 1 & 3 & 1 \\
> \end{array}\right]
> \rightarrow 
> \left[\begin{array}{ccc|ccc}
> 1 & 0 & 0 & -\frac{1}{2} & -\frac{1}{2} & \frac{1}{2} \\
> 0 & 1 & 0 & \frac{1}{4} & -\frac{1}{4} & -\frac{1}{4} \\
> 0 & 0 & 1 & \frac{1}{6} & -\frac{1}{2} & -\frac{1}{6} \\
> \end{array}\right]
> $$
> Thus,
> $$
> A^{-1} =
> \begin{bmatrix} 
> -\frac{1}{2} & -\frac{1}{2} & \frac{1}{2} \\ 
> \frac{1}{4} & -\frac{1}{4} & -\frac{1}{4} \\
> \frac{1}{6} & \frac{1}{2} & \frac{1}{6}
> \end{bmatrix}
> $$

### Diagonal and Triangular Matrices

An $n \times n$ matrix A is said to be **upper triangular** if $a_{ij} = 0$ for $i > j$ and **lower triangular** if $a_{ij} = 0$ for $i < j$. Also, A is said to be **triangular** if it is either upper triangular or lower triangular.

For example:

> The matrix:
> $$
> \begin{bmatrix} 
> 3 & 2 & 1 \\ 
> 0 & 2 & 1 \\
> 0 & 0 & 5
> \end{bmatrix}
> $$
> is upper triangular.
>
> The matrix:
> $$
> \begin{bmatrix} 
> 1 & 0 & 0 \\ 
> 6 & 0 & 0 \\
> 1 & 4 & 3
> \end{bmatrix}
> $$
> is lower triangular.

An $n \times n$ matrix A is **diagonal** if $a_{ij} = 0$ whenever $i \neq j$. A diagonal matrix is both upper triangular and lower triangular.

For example:

> The matrices:
> 
> 
> $$
> \begin{bmatrix} 
> 1 & 0  \\ 
> 0 & 2
> \end{bmatrix},
> \begin{bmatrix} 
> 1 & 0 & 0 \\ 
> 0 & 3 & 0 \\
> 0 & 0 & 1
> \end{bmatrix},
> \begin{bmatrix} 
> 0 & 0 & 0 \\
> 0 & 2 & 0 \\
> 0 & 0 & 0
> \end{bmatrix}
> $$
>
> are all diagonal.

### Triangular Factorization

If an $n \times n$ matrix A can be reduced to strict upper triangular form using only [row operation 3](#Elementary Row Operations), then it is possible to represent the reduction process in terms of a matrix factorization.

If the matrix $L$ is lower triangular with 1's on the diagonal. Way say that $L$ is **unit lower triangular**. The factorization of the matrix A into a product of a unit lower triangular matrix $L$ times a strictly upper triangular matrix $U$ is often referred to as an **LU factorization**.

In general, if an $n \times n$ matrix A can be reduced to strict upper triangular form using only [row operation 3](#Elementary Row Operations), then A has an LU factorization. The matrix $L$ is unit lower triangular, and if $i > j$, then $l_{ij}$ is the multiple of the $j$th row subtracted from the $i$th row during the reduction process.

For example:

> Let:
> $$
> A =
> \begin{bmatrix} 
> 2 & 4 & 2 \\ 
> 1 & 5 & 2 \\
> 4 & -1 & 9
> \end{bmatrix}
> $$
> and let us use only [row operation 3](#Elementary Row Operations) to carry out the reduction process. At the first step, we subtract $\frac{1}{2}$ times the first row from the second and then we subtract twice the first row from the third.
> $$
> \begin{bmatrix} 
> 2 & 4 & 2 \\ 
> 1 & 5 & 2 \\
> 4 & -1 & 9
> \end{bmatrix}
> \rightarrow
> \begin{bmatrix} 
> 2 & 4 & 2 \\ 
> 0 & 3 & 1 \\
> 0 & -9 & 5
> \end{bmatrix}
> $$
> To keep track of the multiples of the first row that were subtracted, we set $l_{21} = \frac{1}{2}$ and $l_{31} = 2$. We complete the elimination process by eliminating the -9 in the ($3, 2$) position.
> $$
> \begin{bmatrix} 
> 2 & 4 & 2 \\ 
> 0 & 3 & 1 \\
> 0 & -9 & 5
> \end{bmatrix}
> \rightarrow
> \begin{bmatrix} 
> 2 & 4 & 2 \\ 
> 0 & 3 & 1 \\
> 0 & 0 & 8
> \end{bmatrix}
> $$
> Let $l_{32} = -3$, the multiple of the second row subtracted from the third row. If we call the resulting matrix $U$ and set
> $$
> L =
> \begin{bmatrix} 
> 1 & 0 & 0 \\ 
> l_{21} & 1 & 0 \\
> l_{31} & l_{32} & 1
> \end{bmatrix}
> =
> \begin{bmatrix} 
> 1 & 0 & 0 \\ 
> \frac{1}{2} & 1 & 0 \\
> 2 & -3 & 1
> \end{bmatrix}
> $$
> then it is easily verified that
> $$
> LU =
> \begin{bmatrix} 
> 1 & 0 & 0 \\ 
> \frac{1}{2} & 1 & 0 \\
> 2 & -3 & 1
> \end{bmatrix}
> \begin{bmatrix} 
> 2 & 4 & 2 \\ 
> 0 & 3 & 1 \\
> 0 & 0 & 8
> \end{bmatrix}
> =
> \begin{bmatrix} 
> 2 & 4 & 2 \\ 
> 1 & 5 & 2 \\
> 4 & -1 & 9
> \end{bmatrix}
> = A
> $$



## Partitioned Matrices

In general, if A is an $m \times n$ matrix and B is an $n \times r$ matrix that has been partitioned into columns $[b_1 \cdots b_r]$, then the block multiplication of A times B is given by:
$$
AB = (Ab_1\quad Ab_2\quad \cdots \quad Ab_r)
$$
In particular,
$$
(a_1 \quad \cdots \quad a_n) = A = AI = (Ae_1 \quad \cdots \quad Ae_n)
$$
Let A be an $m \times n$ matrix. If we partition A into rows, then
$$
A =
\begin{bmatrix} 
\vec{a_1} \\ 
\vec{a_2} \\
\vdots \\
\vec{a_m}
\end{bmatrix}
$$
If B is an $n \times r$ matrix, the $i$th row of the product AB is determined by multiplying the $i$th row of A times B. Thus, the $i$th row of AB is $\vec{a_i} B$. In general, the product AB can be partitioned into rows as follows:
$$
AB =
\begin{bmatrix} 
\vec{a_1} B \\ 
\vec{a_2} B \\
\vdots \\
\vec{a_m} B
\end{bmatrix}
$$

### Block Multiplication

Let A be an $m \times n$ matrix and B an $n \times r$ matrix. It is often useful to partition A and B and express the product in terms of the submatrices of A and B. 

### Outer Product Expansions

Given two vectors $x$ and $y$ in $\mathbb{R}^n$, it is possible to perform a matrix multiplication of the vectors if we transpose one of the vectors first. The matrix product $x^T y$ is the product of a row vector (a $1 \times n$ matrix) and a column vector (an $n \times 1$ matrix). The result will be a $1 \times 1$ matrix, or simply a scalar:
$$
x^T y =
\begin{bmatrix} 
x_1 & x_2 & \cdots & x_n
\end{bmatrix}

\begin{bmatrix} 
y_1 \\
y_2 \\
\vdots \\
y_n
\end{bmatrix}

= 

x_1 y_1 + x_2 y_2 + \cdots + x_n y_n
$$
This type of product is referred to as a **scalar product** or an **inner product**.

The matrix product $xy^T$ is the product of an $n \times 1$ matrix times a $1 \times n$ matrix. The result is a full $n \times n$ matrix
$$
xy^T =
\begin{bmatrix} 
x_1 \\
x_2 \\
\vdots \\
x_n
\end{bmatrix}

\begin{bmatrix} 
y_1 & y_2 & \cdots & y_n
\end{bmatrix}

=
\begin{bmatrix} 
x_1 y_1 & x_1 y_2 & \cdots & x_1 y_n \\
x_2 y_1 & x_2 y_2 & \cdots & x_2 y_n \\
\vdots \\
x_n y_1 & x_n y_2 & \cdots & x_n y_n \\
\end{bmatrix}
$$
The product $xy^T$ is referred to as the **outer product** of $x$ and $y$. The outer product matrix has a special structure in that each of its rows is a multiple of $y^T$ and each of its column vectors is a multiple of $x$.

For example:

> If:
> $$
> x =
> \begin{bmatrix} 
> 4 \\
> 1 \\
> 3
> \end{bmatrix}
> $$
> and
> $$
> y =
> \begin{bmatrix} 
> 3 \\
> 5 \\
> 2
> \end{bmatrix}
> $$
> then
> $$
> xy^T = 
> \begin{bmatrix} 
> 4 \\
> 1 \\
> 3
> \end{bmatrix}
> \begin{bmatrix} 
> 3 & 5 & 2
> \end{bmatrix}
> =
> \begin{bmatrix} 
> 12 & 20 & 8 \\
> 3 & 5 & 2 \\
> 9 & 15 & 6
> \end{bmatrix}
> $$
> Note that each row is a multiple of (3, 5, 2) and each column is a multiple of $x$.

Suppose that we start with an $m \times n$ matrix $X$ and a $k \times n$ matrix $Y$. We can then form a matrix product $XY^T$. If we partition $X$ into columns and $Y^T$ into rows and perform the block multiplication, we see that $XY^T$ can be represented as a sum of outer products of vectors:
$$
XY^T =
\begin{bmatrix} 
x_1 & x_2 & \cdots & x_n
\end{bmatrix}
\begin{bmatrix} 
y_{1}^{T} \\
y_{2}^{T} \\
\vdots \\
y_{n}^{T}
\end{bmatrix}
=
x_1 y_{1}^{T} + x_2 y_{2}^{T} + \cdots + x_n y_{n}^{T}
$$
This representation is referred to as an **outer product expansion**.

For example:

> Given
> $$
> X =
> \begin{bmatrix} 
> 3 & 1\\
> 2 & 4\\
> 1 & 2
> \end{bmatrix}
> \text{ and }
> Y =
> \begin{bmatrix} 
> 1 & 2\\
> 2 & 4\\
> 3 & 1
> \end{bmatrix}
> $$
> compute the outer product expansion of $XY^T$.
>
> SOLUTION
> $$
> \begin{equation}\begin{split} 
> XY^T &= 
> \begin{bmatrix} 
> 3 & 1\\
> 2 & 4\\
> 1 & 2
> \end{bmatrix}
> \begin{bmatrix} 
> 1 & 2 & 3 \\
> 2 & 4 & 1 
> \end{bmatrix} \\
> 
> &=
> \begin{bmatrix} 
> 3\\
> 2\\
> 1
> \end{bmatrix}
> \begin{bmatrix} 
> 1 & 2 & 3
> \end{bmatrix}
> +
> \begin{bmatrix} 
> 1\\
> 4\\
> 2
> \end{bmatrix}
> \begin{bmatrix} 
> 2 & 4 & 1
> \end{bmatrix} \\
> 
> &=
> \begin{bmatrix} 
> 3 & 6 & 9 \\
> 2 & 4 & 6 \\
> 1 & 2 & 3
> \end{bmatrix}
> +
> \begin{bmatrix} 
> 2 & 4 & 1 \\
> 8 & 16 & 4 \\
> 4 & 8 & 2
> \end{bmatrix}
> \end{split}\end{equation}
> $$



## Example 1: Using numpy

Implement (by numpy):

```python
import numpy as np

# arumented matrix example
def calc_arumented_matrix():
  # 4x_1 - 3x_2 = 4
  # 2/3 x_1 + 4x_2 = 3
  A = np.array([[4, 3], [2/3, 4]], dtype=float)
  B = np.array([4, 3], dtype=float)

  x = np.linalg.solve(A, B)
  print(x) 
  
calc_arumented_matrix() # [0.5        0.66666667]

# matrix multiple example
def calc_mat_mul():
    A = np.array([[3, 5, 1], 
                  [-2, 0, 2]])
    B = np.array([[2, 1], 
                  [1, 3], 
                  [4, 1]])
    if not A.shape[1] == B.shape[0]:
        raise ValueError("Cannot multiply: number of columns in A must equal number of rows in B.")
    
    result = np.dot(A, B)
    print(result) # [[15 19]
 									#	 [ 4  0]]

calc_mat_mul()

# matrix addit
```



## Example 2: Plot systems by matplot

Graph the lines and determine geometrically the number of solutions
$$
x_1 + x_2 = 4 \\
x_1 - x_2 = 2
$$
 Implement (by matplot and numpy):

```python
import numpy as np
import matplotlib.pyplot as plt

# support for negative sign in plot
plt.rcParams['axes.unicode_minus'] = False

# create a range of x1 values to plot the equations
x1 = np.linspace(-5, 10, 100)

# x1 + x2 = 4  => x2 = 4 - x1
# x1 - x2 = 2  => x2 = x1 - 2
x2_eq1 = 4 - x1
x2_eq2 = x1 - 2

# create a plot to visualize the two equations and their intersection point
plt.figure(figsize=(8, 6))

# plot the two lines representing the equations
plt.plot(x1, x2_eq1, label='x₁ + x₂ = 4', linewidth=2, color='blue')
plt.plot(x1, x2_eq2, label='x₁ - x₂ = 2', linewidth=2, color='red')

# mark the solution point where the two lines intersect
# x1 = 3, x2 = 1
x1_solution = 3
x2_solution = 1
plt.plot(x1_solution, x2_solution, 'go', markersize=10, label=f'result: ({x1_solution}, {x2_solution})')

# plot arrows to indicate the solution point
plt.annotate(f'({x1_solution}, {x2_solution})', 
         xy=(x1_solution, x2_solution), 
         xytext=(x1_solution+0.5, x2_solution+0.5),
         arrowprops=dict(arrowstyle='->', color='green'))

# set the limits and labels for the plot
plt.grid(True, alpha=0.3)
plt.xlabel('x₁', fontsize=12)
plt.ylabel('x₂', fontsize=12)
plt.title('the illustration of the solution', fontsize=14)

# set the limits for x and y axes to better visualize the intersection point
plt.xlim(-2, 8)
plt.ylim(-3, 7)

# customize the axes to pass through the origin (0, 0)
ax = plt.gca()
ax.spines['left'].set_position('zero')
ax.spines['bottom'].set_position('zero')
ax.spines['right'].set_color('none')
ax.spines['top'].set_color('none')

plt.legend()
plt.show()
```



## Example 3: Proof of Theorem 1 by using matplot

For a homogeneous linear system consisting of two equations in three unknowns:
$$
x_1 + x_2 + x_3 = 0 \\
x_1 - x_2 - x_3 = 0
$$
 Implement (by matplot and numpy):

```python
import numpy as np
import matplotlib.pyplot as plt

# Create figure
fig = plt.figure(figsize=(10, 8))
ax = fig.add_subplot(111, projection='3d')

# Grid
x = np.linspace(-5, 5, 40)
y = np.linspace(-5, 5, 40)

X, Y = np.meshgrid(x, y)

# Planes
# x1 + x2 + x3 = 0
Z1 = -X - Y

# x1 - x2 - x3 = 0
Z2 = X - Y

# Draw planes
plane1 = ax.plot_surface(X, Y, Z1, alpha=0.6)
plane2 = ax.plot_surface(X, Y, Z2, alpha=0.6)

# Intersection line
t = np.linspace(-5, 5, 100)

x_line = np.zeros_like(t)
y_line = -t
z_line = t

ax.plot(x_line, y_line, z_line, linewidth=3)

# Add equation labels onto the planes
ax.text(
    2, 2, -4,
    r'$x_1 + x_2 + x_3 = 0$',
    fontsize=12
)

ax.text(
    2, -2, 4,
    r'$x_1 - x_2 - x_3 = 0$',
    fontsize=12
)

# Add intersection line label
ax.text(
    0, -4, 4,
    r'Intersection Line',
    fontsize=12
)

# Axis labels
ax.set_xlabel(r'$x_1$')
ax.set_ylabel(r'$x_2$')
ax.set_zlabel(r'$x_3$')

# Title
ax.set_title('Visualization of Two Linear Equations')

plt.show()
```





## Reference

[1] Steven J. Leon. LINEAR ALGEBRA with Applications. 10ED