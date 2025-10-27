# Algorithms (Discrete Mathematics)

[TOC]

## Introduction

This note summarizes fundamental concepts of algorithms as presented in the Discrete Mathematics context (based primarily on Kenneth H. Rosen, Discrete Mathematics and Its Applications, 8th ed.). It collects definitions, important properties, common algorithmic paradigms, typical examples, and a compact guide to asymptotic analysis. The aim is to provide a concise reference suitable for students of discrete mathematics.

## What is an algorithm?

An algorithm is a finite, well-defined sequence of instructions for solving a problem or performing a computation. A good algorithm should be:

- Correct: produce the intended output for all valid inputs.
- Finite: terminate after a finite number of steps for any valid input.
- Precise: each step must be unambiguous and executable.
- Effective: every step can, in principle, be carried out exactly.
- General: applicable to all instances of the problem, not just particular cases.

## Asymptotic notation (brief)

Let $f$ and $g$ be real- or integer-valued functions defined on sufficiently large inputs.

- Big-O: $f(x)=O(g(x))$ if there exist positive constants $C$ and $k$ such that $|f(x)|\le C|g(x)|$ for all $x>k$. (Upper bound.)
- Big-Omega: $f(x)=\Omega(g(x))$ if there exist positive constants $C$ and $k$ such that $|f(x)|\ge C|g(x)|$ for all $x>k$. (Lower bound.)
- Big-Theta: $f(x)=\Theta(g(x))$ if $f(x)$ is both $O(g(x))$ and $\Omega(g(x))$ (tight bound).

Common asymptotic classes: $\Theta(1)$ (constant), $\Theta(\log n)$ (logarithmic), $\Theta(n)$ (linear), $\Theta(n\log n)$, $\Theta(n^b)$ (polynomial), $\Theta(b^n)$ (exponential), $\Theta(n!)$ (factorial).

Example: any polynomial $f(x)=a_n x^n+\cdots+a_0$ with $a_n\neq0$ satisfies $f(x)=O(x^n)$.

## Properties of algorithms

- Input and output: an algorithm accepts an input (from a specified set) and produces output values.
- Determinism: the steps of the algorithm are precisely defined so that the behavior is predictable.
- Correctness: we often prove correctness by induction or by invariants.
- Termination: an algorithm must terminate after a finite number of steps.

## Common algorithmic paradigms

- Divide and conquer: split a problem into smaller subproblems, solve them recursively, and combine the solutions. (E.g., merge sort.) Often analyzed using recurrence relations.
- Greedy algorithms: repeatedly take the locally optimal choice, hoping to reach a global optimum. Requires proof of correctness for each problem (e.g., matroids, interval scheduling, some shortest-path/ MST formulations).
- Dynamic programming: break problems into overlapping subproblems and store intermediate results to avoid recomputation (e.g., knapsack, longest common subsequence).
- Backtracking / Branch-and-bound: systematic search with pruning for combinatorial problems (e.g., n-queens, SAT solvers).

## Representative algorithms (short descriptions)

Searching:

- Linear search: scan the list item by item until the target is found or the list ends. Time: $\Theta(n)$.
- Binary search: on a sorted array, repeatedly compare the target to the middle element and narrow the search interval by half. Time: $\Theta(\log n)$.

Sorting (selected):

- Bubble sort: repeatedly swap adjacent out-of-order elements. Simple but inefficient: worst-case $\Theta(n^2)$.
- Insertion sort: build a sorted prefix by inserting each new element in place. Best-case $\Theta(n)$ (nearly sorted data), average/worst $\Theta(n^2)$.
- Merge sort / Quick sort / Heap sort: more efficient general-purpose sorts with average/worst complexities of $\Theta(n\log n)$ (merge and heap are $\Theta(n\log n)$ worst-case; quicksort average $\Theta(n\log n)$ but worst-case $\Theta(n^2)$ without careful pivoting).

String matching:

- Naive (brute-force) matching and more advanced algorithms such as Knuth–Morris–Pratt (KMP) and Boyer–Moore, which improve running time by using structure in patterns.

Greedy algorithms and NP/undecidable remarks:

- Greedy algorithms are widely used for optimization problems; correctness must be justified per-problem.
- Some problems are computationally intractable (e.g., NP-hard) or undecidable (e.g., the Halting Problem: there is no general algorithm that decides for every program-input pair whether the program halts).

## Recurrence relations and the Master theorem

Many divide-and-conquer algorithms satisfy recurrences of the form
$$
T(n)=a\,T(n/b)+f(n),
$$
where $a\ge1$ and $b>1$. The Master theorem gives common cases for the asymptotic growth of $T(n)$:

- If $f(n)=O\big(n^{\log_b a-\epsilon}\big)$ for some $\epsilon>0$, then $T(n)=\Theta(n^{\log_b a})$.
- If $f(n)=\Theta\big(n^{\log_b a}\big)$, then $T(n)=\Theta(n^{\log_b a}\log n)$.
- If $f(n)=\Omega\big(n^{\log_b a+\epsilon}\big)$ for some $\epsilon>0$ and a regularity condition holds, then $T(n)=\Theta(f(n))$.

Recurrences and generating functions are also useful tools for precise counting and analysis of algorithmic costs.

## Complexity terminology (quick table)

| Notation | Meaning |
|---:|:---|
| $\Theta(1)$ | constant time |
| $\Theta(\log n)$ | logarithmic time |
| $\Theta(n)$ | linear time |
| $\Theta(n\log n)$ | linearithmic time |
| $\Theta(n^b)$ | polynomial time |
| $\Theta(b^n)$ | exponential time |
| $\Theta(n!)$ | factorial time |

## Further reading and references

[1] Kenneth H. Rosen, Discrete Mathematics and Its Applications, 8th Edition.

Other recommended readings for algorithms and analysis:

- Cormen, Leiserson, Rivest, and Stein, Introduction to Algorithms (CLRS).
- Kleinberg and Tardos, Algorithm Design.
