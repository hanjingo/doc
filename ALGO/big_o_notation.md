[中文版](big_o_notation_zh.md) | English

# Asymptotic Notation and Basic Growth Rates

[TOC]

## Introduction

This note summarizes the common asymptotic notations used to describe algorithm running times (Big-O, Omega, Theta, little-o), lists useful rules, and provides common examples and summation facts used in algorithm analysis. It is adapted and condensed from standard references (see References).

## Asymptotic definitions

Let T(n) and f(n) be functions that map positive integers to positive real numbers. We use the following notations to classify growth rates as n \rightarrow \infty.

- Big-O: T(n) = O(f(n)) if there exist positive constants c and n_0 such that for all n \ge n_0, T(n) \le c f(n). Intuitively, f(n) is an upper bound on T(n) up to constant factors.

- Big-Omega: T(n) = \Omega(f(n)) if there exist positive constants c and n_0 such that for all n \ge n_0, T(n) \ge c f(n). This means f(n) is a lower bound on T(n) up to constant factors.

- Theta: T(n) = \Theta(f(n)) iff T(n) = O(f(n)) and T(n) = \Omega(f(n)). This indicates f(n) tightly bounds T(n) up to constant factors.

- little-o: T(n) = o(f(n)) if for every positive constant c there exists n_0 such that for all n \ge n_0, T(n) < c f(n). Equivalently, \lim_{n\to\infty} T(n)/f(n) = 0.

Remarks: constants and lower-order terms are ignored in asymptotic notation. For example, 3n^2 + 10n + 7 = \Theta(n^2).

## Useful rules and properties

- Addition: If T_1(n) = O(f(n)) and T_2(n) = O(g(n)), then T_1(n) + T_2(n) = O(max(f(n), g(n))).
- Multiplication by constants: If a is a constant, a \cdot T(n) = O(T(n)).
- Multiplication: If T_1(n) = O(f(n)) and T_2(n) = O(g(n)), then T_1(n)\cdot T_2(n) = O(f(n)\cdot g(n)).
- Transitivity: If T(n) = O(f(n)) and f(n) = O(g(n)), then T(n) = O(g(n)).
- Polynomials: If T(n) is a polynomial of degree k, then T(n) = \Theta(n^k).
- Logs: For any constant k, (log n)^k = o(n^\epsilon) for any \epsilon > 0; in particular (log n)^k = O(n).

## Common growth classes (ordered from slowest to fastest)

- Constant: 1
- Logarithmic: log n
- Polylogarithmic: (log n)^k
- Linear: n
- n log n
- Polynomial: n^c (c > 1)
- Exponential: a^n (a > 1)

Remember: when comparing two functions for asymptotic growth, look at their dominant terms and ignore constant factors.

## Common summations and identities

- Geometric series: \sum_{i=0}^{N} a^i = (a^{N+1}-1)/(a-1) for a \neq 1. If |a| < 1 the infinite sum converges to 1/(1-a).
- Powers: \sum_{i=1}^{N} i = N(N+1)/2 = \Theta(N^2).
- Squares: \sum_{i=1}^{N} i^2 = N(N+1)(2N+1)/6 = \Theta(N^3).
- General polynomial sums: \sum_{i=1}^{N} i^k = \Theta(N^{k+1}).
- Harmonic numbers: H_N = \sum_{i=1}^{N} 1/i = \Theta(\log N).

Useful approximation: \sum_{i=1}^{N} f(i) \approx \int_{1}^{N} f(x) dx when f is smooth and monotone; this often helps get intuition for summation growth.

## Examples and typical uses

- If an algorithm does a constant amount of work per element over n elements, its running time is O(n).
- Binary search on a sorted array runs in O(\log n).
- Merge sort and other divide-and-conquer algorithms often have recurrences; the Master Theorem (see CLRS) provides a quick way to solve many of them.

## Notes on model and constants

Asymptotic notation hides constant factors and lower-order terms. Two algorithms with the same asymptotic class (e.g., O(n log n)) can have very different actual running times due to constants, memory access patterns, and implementation details. For algorithm engineering it's important to measure and consider these factors.

## Quick reference: small list of identities

- log(ab) = log a + log b
- log(a^b) = b log a
- If 0 < a < b then n^a = o(n^b).

## References

1. Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein. Introduction to Algorithms. 3rd ed.
2. Additional classroom notes and standard algorithm texts.
[中文版](big_o_notation_zh.md) | English

# Asymptotic Notation and Basic Growth Rates

[TOC]

## Introduction

This note summarizes the common asymptotic notations used to describe algorithm running times (Big-O, Omega, Theta, little-o), lists useful rules, and provides common examples and summation facts used in algorithm analysis. It is adapted and condensed from standard references (see References).

## Asymptotic definitions

Let T(n) and f(n) be functions that map positive integers to positive real numbers. We use the following notations to classify growth rates as n \rightarrow \infty.

- Big-O: T(n) = O(f(n)) if there exist positive constants c and n_0 such that for all n \ge n_0, T(n) \le c f(n). Intuitively, f(n) is an upper bound on T(n) up to constant factors.

- Big-Omega: T(n) = \Omega(f(n)) if there exist positive constants c and n_0 such that for all n \ge n_0, T(n) \ge c f(n). This means f(n) is a lower bound on T(n) up to constant factors.

- Theta: T(n) = \Theta(f(n)) iff T(n) = O(f(n)) and T(n) = \Omega(f(n)). This indicates f(n) tightly bounds T(n) up to constant factors.

- little-o: T(n) = o(f(n)) if for every positive constant c there exists n_0 such that for all n \ge n_0, T(n) < c f(n). Equivalently, \lim_{n\to\infty} T(n)/f(n) = 0.

Remarks: constants and lower-order terms are ignored in asymptotic notation. For example, 3n^2 + 10n + 7 = \Theta(n^2).

## Useful rules and properties

- Addition: If T_1(n) = O(f(n)) and T_2(n) = O(g(n)), then T_1(n) + T_2(n) = O(max(f(n), g(n))).
- Multiplication by constants: If a is a constant, a \cdot T(n) = O(T(n)).
- Multiplication: If T_1(n) = O(f(n)) and T_2(n) = O(g(n)), then T_1(n)\cdot T_2(n) = O(f(n)\cdot g(n)).
- Transitivity: If T(n) = O(f(n)) and f(n) = O(g(n)), then T(n) = O(g(n)).
- Polynomials: If T(n) is a polynomial of degree k, then T(n) = \Theta(n^k).
- Logs: For any constant k, (log n)^k = o(n^\epsilon) for any \epsilon > 0; in particular (log n)^k = O(n).

## Common growth classes (ordered from slowest to fastest)

- Constant: 1
- Logarithmic: log n
- Polylogarithmic: (log n)^k
- Linear: n
- n log n
- Polynomial: n^c (c > 1)
- Exponential: a^n (a > 1)

Remember: when comparing two functions for asymptotic growth, look at their dominant terms and ignore constant factors.

## Common summations and identities

- Geometric series: \sum_{i=0}^{N} a^i = (a^{N+1}-1)/(a-1) for a \neq 1. If |a| < 1 the infinite sum converges to 1/(1-a).
- Powers: \sum_{i=1}^{N} i = N(N+1)/2 = \Theta(N^2).
- Squares: \sum_{i=1}^{N} i^2 = N(N+1)(2N+1)/6 = \Theta(N^3).
- General polynomial sums: \sum_{i=1}^{N} i^k = \Theta(N^{k+1}).
- Harmonic numbers: H_N = \sum_{i=1}^{N} 1/i = \Theta(\log N).

Useful approximation: \sum_{i=1}^{N} f(i) \approx \int_{1}^{N} f(x) dx when f is smooth and monotone; this often helps get intuition for summation growth.

## Examples and typical uses

- If an algorithm does a constant amount of work per element over n elements, its running time is O(n).
- Binary search on a sorted array runs in O(\log n).
- Merge sort and other divide-and-conquer algorithms often have recurrences; the Master Theorem (see CLRS) provides a quick way to solve many of them.

## Notes on model and constants

Asymptotic notation hides constant factors and lower-order terms. Two algorithms with the same asymptotic class (e.g., O(n log n)) can have very different actual running times due to constants, memory access patterns, and implementation details. For algorithm engineering it's important to measure and consider these factors.

## Quick reference: small list of identities

- log(ab) = log a + log b
- log(a^b) = b log a
- If 0 < a < b then n^a = o(n^b).

## References

1. Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein. Introduction to Algorithms. 3rd ed.
2. Additional classroom notes and standard algorithm texts.
