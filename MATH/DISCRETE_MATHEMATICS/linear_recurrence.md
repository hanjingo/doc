# Linear Recurrence Relations

[TOC]

## Introduction

This note summarizes linear recurrence relations with constant coefficients and the common methods used to solve them in discrete mathematics: the characteristic-equation method for homogeneous recurrences, techniques for nonhomogeneous recurrences (method of undetermined coefficients and annihilators), and generating functions. It also recalls the Master theorem for many divide-and-conquer recurrences and a few useful analytic facts.

## Definitions

- A linear homogeneous recurrence relation of degree k with constant coefficients has the form
  $$a_n = c_1 a_{n-1} + c_2 a_{n-2} + \cdots + c_k a_{n-k},$$
  where the coefficients $c_1,\dots,c_k$ are constants and $c_k\neq0$.
- A linear nonhomogeneous recurrence adds a forcing term $F(n)$:
  $$a_n = c_1 a_{n-1} + \cdots + c_k a_{n-k} + F(n).$$
- The ordinary generating function of a sequence $(a_n)_{n\ge0}$ is the formal power series
  $$G(x)=\sum_{n=0}^{\infty} a_n x^n.$$ 

## Homogeneous recurrences: characteristic equation

Form the characteristic polynomial
$$p(r)=r^k - c_1 r^{k-1} - \cdots - c_{k-1} r - c_k.$$ 
If $p(r)$ has $k$ distinct roots $r_1,\dots,r_k$, then the general solution of the homogeneous recurrence is
$$a_n = \alpha_1 r_1^n + \alpha_2 r_2^n + \cdots + \alpha_k r_k^n,$$
where the constants $\alpha_i$ are determined by initial conditions.

If a root $r$ has multiplicity $m$, its contribution becomes
$$ (\beta_0 + \beta_1 n + \cdots + \beta_{m-1} n^{m-1}) r^n. $$
Combining contributions for all distinct roots gives the full homogeneous solution.

Example: the Fibonacci recurrence $F_n=F_{n-1}+F_{n-2}$ has characteristic polynomial $r^2-r-1=0$ with roots $\phi=(1+\sqrt5)/2$ and $\hat\phi=(1-\sqrt5)/2$, leading to Binet's formula
$$F_n=\frac{\phi^n-\hat\phi^n}{\sqrt5}.$$ 

## Nonhomogeneous recurrences

If $a_n^{(p)}$ is any particular solution to the nonhomogeneous recurrence, the general solution is
$$a_n = a_n^{(h)} + a_n^{(p)},$$
where $a_n^{(h)}$ is the general solution of the associated homogeneous recurrence.

Method of undetermined coefficients: when $F(n)$ is a combination of polynomials, exponentials $s^n$, or products with powers of $n$, guess a particular solution of similar form. If the guessed form conflicts with the homogeneous solution (i.e., $s$ is a root of the characteristic polynomial of multiplicity $m$), multiply the guess by $n^m$.

Example: for $a_n = 2a_{n-1} + 3$, guess a particular constant solution $a_n^{(p)}=A$ and solve $A=2A+3$ to find $A=-3$; combine with homogeneous solution $\alpha 2^n$.

## Generating functions

Generating functions turn recurrences into algebraic equations for $G(x)$. For many linear recurrences with constant coefficients the generating function is rational; extract coefficients by partial fractions or known power series expansions to obtain closed forms.

Example: Fibonacci generating function
$$G(x)=\sum_{n\ge0}F_n x^n = \frac{x}{1-x-x^2}.$$ 

## Master theorem (divide-and-conquer recurrences)

For recurrences of the form
$$T(n)=a\,T(n/b)+f(n),$$
with $a\ge1$, $b>1$, let $\alpha=\log_b a$. Then:

- If $f(n)=O(n^{\alpha-\epsilon})$ for some $\epsilon>0$, then $T(n)=\Theta(n^{\alpha})$.
- If $f(n)=\Theta(n^{\alpha})$, then $T(n)=\Theta(n^{\alpha}\log n)$.
- If $f(n)=\Omega(n^{\alpha+\epsilon})$ for some $\epsilon>0$ and a regularity condition holds (e.g., $af(n/b)\leq c f(n)$ for some $c<1$), then $T(n)=\Theta(f(n))$.

The Master theorem is a practical tool for analyzing many divide-and-conquer algorithms (merge sort, some versions of quicksort, binary tree recurrences).

## Useful analytic facts

- Extended binomial coefficients: for real $u$ and integer $k\ge0$,
  $$\binom{u}{k}=\frac{u(u-1)\cdots(u-k+1)}{k!},\qquad \binom{u}{0}=1.$$ 
  The extended binomial series (valid for $|x|<1$) is
  $$(1+x)^u=\sum_{k=0}^\infty \binom{u}{k} x^k.$$ 
- Operations on generating functions: if $F(x)=\sum a_n x^n$ and $H(x)=\sum b_n x^n$, then
  $$F(x)+H(x)=\sum (a_n+b_n)x^n,\qquad F(x)H(x)=\sum\left(\sum_{j=0}^n a_j b_{n-j}\right)x^n.$$ 

## Remarks and references

- For methods such as annihilators, convolution, or combinatorial generating functions, see detailed treatments in Rosen and in standard algorithm analysis texts.
- Common pitfalls: always check multiplicities of characteristic roots when guessing particular solutions; use initial conditions to solve for constants.

## References

[1] Kenneth H. Rosen. Discrete Mathematics and Its Applications. 8th Edition.
