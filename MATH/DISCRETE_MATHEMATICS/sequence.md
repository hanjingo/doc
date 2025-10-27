# Sequences and Summations

[TOC]

## Introduction

This note collects the basic definitions and formulas for sequences and finite sums commonly used in discrete mathematics. It includes notation for summations, standard formulas for arithmetic and geometric series, a few important finite sums, and a short introduction to recurrence relations (with the Fibonacci sequence as an example).

## Definitions

- Sequence: A sequence is a function whose domain is a subset of the integers (often \{0,1,2,...\} or \{1,2,3,...\}) and whose codomain is a set S. We denote the sequence by \{a_n\}, where a_n is the value at index n (the n-th term).

- Arithmetic progression (sequence): A sequence of the form
  $$a,\\ a+d,\\ a+2d,\\ \\dots,\\ a+nd,\\ \\dots$$
  where a is the initial term and d is the common difference.

- Geometric progression (sequence): A sequence of the form
  $$a,\\ ar,\\ ar^2,\\ \\dots,\\ ar^n,\\ \\dots$$
  where a is the initial term and r is the common ratio.

- Recurrence relation: A recurrence relation expresses a_n in terms of earlier terms a_{n-1}, a_{n-2}, \\dots, a_{n-k} for n \\ge n_0. A sequence that satisfies the recurrence together with given initial conditions is a solution of the recurrence. The order of the recurrence is the maximum difference between n and the indices that appear on the right-hand side.

Example (Fibonacci): The Fibonacci sequence \\{f_n\\} is given by
  $$f_0=0,\\quad f_1=1,\\quad f_n=f_{n-1}+f_{n-2}\\ (n\\ge 2).$$

## Summation notation and basic rules

- Sigma notation: The sum of terms a_m, a_{m+1}, , a_n is written
  $$\\sum_{j=m}^n a_j = a_m + a_{m+1} + \\cdots + a_n.$$ 
  The index letter (j here) is arbitrary; one can use i, k, or any other symbol.

- Linearity and basic manipulation rules:
  - Constant factor: \\(\\sum_{j=m}^n c\\,a_j = c\\sum_{j=m}^n a_j\\).
  - Additivity: \\(\\sum_{j=m}^n (a_j + b_j) = \\sum_{j=m}^n a_j + \\sum_{j=m}^n b_j\\).
  - Index shift: \\(\\sum_{j=m}^n a_j = \\sum_{t=m+s}^{n+s} a_{t-s}\\) (substitute t=j+s).
  - Splitting: \\(\\sum_{j=m}^n a_j = \\sum_{j=m}^p a_j + \\sum_{j=p+1}^n a_j\\) for m \\le p < n.

## Important finite sums and formulas

- Arithmetic series (first n+1 terms starting at a):
  If a_k = a + kd (k = 0,\\dots,n), then
  $$\\sum_{k=0}^n (a+kd) = (n+1)a + d\\frac{n(n+1)}{2} = (n+1)\\frac{a + a_n}{2}.$$ 

- Finite geometric series (a \\neq 0):
  For r \\neq 1,
  $$\\sum_{j=0}^n ar^j = a\\frac{r^{n+1}-1}{r-1}.$$ 
  If r = 1, the sum is (n+1)a.

- Infinite geometric series (convergence): If |r|<1 then
  $$\\sum_{j=0}^\\infty ar^j = \\frac{a}{1-r}.$$ 
  If |r| \\ge 1 the infinite sum diverges.

- Some common polynomial sums (starting at k=1):
  $$\\sum_{k=1}^n k = \\frac{n(n+1)}{2},\\qquad
  \\sum_{k=1}^n k^2 = \\frac{n(n+1)(2n+1)}{6},\\qquad
  \\sum_{k=1}^n k^3 = \\left(\\frac{n(n+1)}{2}\\right)^2.$$ 

These formulas are useful for analyzing algorithms and solving simple recurrences.

## Recurrence relations (brief)

- Order and linear recurrences: A linear recurrence with constant coefficients has the form
  $$a_n = c_1 a_{n-1} + c_2 a_{n-2} + \\cdots + c_k a_{n-k} + g(n),$$
  where g(n) is a known function (g(n)=0 gives a homogeneous recurrence). The characteristic-equation method solves homogeneous linear recurrences with constant coefficients by finding roots of the polynomial
  $$x^k - c_1 x^{k-1} - \\cdots - c_k = 0.$$ 

- Example (Fibonacci again): The characteristic equation x^2 - x - 1 = 0 has roots (1  \\\\sqrt{5})/2, leading to Binet's formula (closed form) for f_n. Detailed solution methods are covered in standard discrete-math texts.

## Examples

- Example 1  arithmetic series: For the sequence 2,5,8,11, (a=2,d=3), the sum of the first 5 terms (k=0..4) is
  $$\\sum_{k=0}^4 (2+3k) = 5\\cdot\\frac{2+(2+3\\cdot4)}{2} = 5\\cdot\\frac{2+14}{2} = 40.$$ 

- Example 2  geometric series: For a=1, r=2, the finite sum
  $$\\sum_{j=0}^3 2^j = 1+2+4+8 = 15,$$
  matching the formula 1\\cdot(2^{4}-1)/(2-1)=15.

- Example 3  application to algorithms: If a loop doubles work each iteration for n+1 iterations, total work is a geometric sum; if work increases linearly, the arithmetic sum appears. These identities are commonly used in complexity analysis.

## Remarks and references

- This note covers elementary formulas and notation used in discrete mathematics. For more on solving recurrences and generating functions, see the chapters on sequences and recurrence relations in Rosen''s "Discrete Mathematics and Its Applications."

## References

1. Kenneth H. Rosen, Discrete Mathematics and Its Applications, 8th ed.
