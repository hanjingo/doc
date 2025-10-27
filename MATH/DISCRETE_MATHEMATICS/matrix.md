# Matrices

[TOC]

## Introduction

This note summarizes basic definitions and properties of matrices commonly used in discrete mathematics. It focuses on elementary concepts (dimensions, entries, row/column operations), standard matrix arithmetic, and Boolean (zero–one) matrices used for relations and graph adjacency. Definitions follow standard notation; proofs and advanced linear-algebra topics (determinant, eigenvalues) are omitted or only mentioned briefly.

## Basic definitions and notation

- A matrix is a rectangular array of elements (usually numbers). An m × n matrix has m rows and n columns. We write
	$$A = [a_{ij}]_{m\\times n} = \\begin{bmatrix} a_{11} & a_{12} & \\cdots & a_{1n}\\ a_{21} & a_{22} & \\cdots & a_{2n}\\ \\vdots & \\vdots & & \\vdots\\ a_{m1} & a_{m2} & \\cdots & a_{mn} \\end{bmatrix}. $$

- The entry in row i and column j is denoted a_{ij}. The i-th row is the 1×n vector [a_{i1},…,a_{in}] and the j-th column is the m×1 vector with entries a_{1j},…,a_{mj}.

- Two matrices are equal if they have the same dimensions and all corresponding entries are equal.

- A square matrix has the same number of rows and columns (n × n). Common special square matrices:
	- Zero matrix: all entries 0, denoted 0_{m\\times n}.
	- Identity matrix of order n: I_n with (i,i) entries 1 and others 0. Using Kronecker delta, (I_n)_{ij}=\\delta_{ij}.
	- Diagonal matrix: only diagonal entries may be nonzero.
	- Symmetric matrix: A^T = A (so a_{ij} = a_{ji}).

## Basic matrix operations

- Addition and scalar multiplication (only for matrices of the same size):
	- (A + B)_{ij} = a_{ij} + b_{ij}.
	- (cA)_{ij} = c\\,a_{ij} for scalar c.

- Matrix multiplication: If A is m×k and B is k×n, their product AB is m×n with
	$$ (AB)_{ij} = \\sum_{t=1}^k a_{it}b_{tj}. $$
	Note: matrix multiplication is associative and distributive over addition but is generally not commutative: AB \\neq BA in general.

- Identity and inverse (square matrices): For an n×n matrix A, if there exists B such that AB = BA = I_n, then B is the inverse of A and A is invertible.

- Transpose: The transpose of A (m×n) is A^T (n×m) with (A^T)_{ij} = a_{ji}. Transpose properties include (A^T)^T = A, (A + B)^T = A^T + B^T, and (AB)^T = B^T A^T.

## Common properties and identities

- Associativity: (AB)C = A(BC) when dimensions match.
- Distributivity: A(B + C) = AB + AC and (A + B)C = AC + BC.
- Left/right identity: I_m A = A and A I_n = A for compatible sizes.
- If A is m×n and B is n×m, then AB is m×m and BA is n×n (different sizes possible).

## Rank, rows and columns (brief)

- The row rank (dimension of the space spanned by rows) equals the column rank (dimension spanned by columns); this common value is the rank of A. Rank measures linear independence of rows/columns and is \\le min(m,n).

## Boolean (zero–one) matrices

A zero–one matrix is a matrix whose entries are in {0,1}. Such matrices commonly represent relations or adjacency in graphs.

- Join (logical OR) and meet (logical AND): If A and B are m×n zero–one matrices, their join and meet are defined entrywise by
	$$ (A \\vee B)_{ij} = a_{ij} \\vee b_{ij}, \\qquad (A \\wedge B)_{ij} = a_{ij} \\wedge b_{ij}. $$

- Boolean product (used for composition of relations and graph reachability): If A is m×k and B is k×n (zero–one matrices), the Boolean product C = A \\odot B is the m×n zero–one matrix with
	$$ c_{ij} = \\bigvee_{t=1}^k (a_{it} \\wedge b_{tj}), $$
	i.e., c_{ij} = 1 iff there exists t with a_{it}=1 and b_{tj}=1.

- Boolean powers: For a square zero–one matrix A, define A^{[r]} = A \\odot A \\odot \\cdots \\odot A (r factors). Also set A^{[0]} = I_n. Boolean powers are useful for computing reachability in directed graphs: (A^{[r]})_{ij}=1 iff there is a path of length exactly r from i to j.

## Examples

- Example (2×3 matrix):
	$$ A = \\begin{bmatrix}1 & 2 & 0\\ 3 & -1 & 4\\ \\end{bmatrix}. $$
	Here A has 2 rows and 3 columns.

- Example (matrix multiplication): If
	$$ A=\\begin{bmatrix}1 & 2\\ 0 & 3\\end{bmatrix},\\quad B=\\begin{bmatrix}4 & 0\\ 1 & 5\\end{bmatrix},$$
	then
	$$ AB = \\begin{bmatrix}1\\cdot4+2\\cdot1 & 1\\cdot0+2\\cdot5\\ 0\\cdot4+3\\cdot1 & 0\\cdot0+3\\cdot5\\end{bmatrix} = \\begin{bmatrix}6 & 10\\ 3 & 15\\end{bmatrix}. $$

- Example (Boolean adjacency): For a directed graph with adjacency matrix A, the (i,j) entry of A^{[2]} (Boolean power) is 1 iff there exists an intermediate vertex k with edges i→k and k→j.

## Remarks and pointers

- This note covers elementary definitions used in discrete mathematics; further linear-algebra topics (determinant, eigenvalues, singular values, LU decomposition, solving linear systems) are beyond the scope here but are standard results in linear algebra texts.
- For applications to relations and graphs, zero–one matrices and Boolean matrix multiplication are particularly useful; see the chapters on relations and graph theory in Rosen's "Discrete Mathematics and Its Applications."

## References

1. Kenneth H. Rosen, Discrete Mathematics and Its Applications, 8th ed.
