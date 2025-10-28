# CHAPTER 23 Special Algorithms for Protocols

[TOC]



## MULTIPLE-kEY PUBLIC-kEY CRYPTOGRAPHY

This is a generalization of RSA. The modulus, $n$ is the product of two primes, $p$ and $q$. However, instead of choosing $e$ and $d$ such that $ed = 1 \mod ((p - 1)(q - 1))$, choose $t$ keys, $K_i$; such that:
$$
K_1 * K_2 * ... * K_t \equiv 1 \mod ((p - 1)(q - 1))
$$
, since:
$$
M^{K_1 \cdot K_2 \cdot ... \cdot K_t} = M
$$
, this is a multiple-key scheme.



## SECRET-SHARING ALGORITHMS

### LaGrange Interpolating Polynomial Scheme

Adi Shamir uses polynomial equations in a finite field to construct a threshold scheme. Choose a prime, $p$, which is both larger than the number of possible shadows and larger than the largest possible secret. To share a secret, generate an arbitrary polynomial of degree $m - 1$.

The shadows are obtained by evaluating the polynomial at $n$ different points:
$$
K_i = F(x_i)
$$
In other words, the first shadow could be the polynomial evaluated at $x = 1$, the second shadow could be the polynomial evaluated at $x = 2$, and so forth.

Since the quadratic polynomial has three unknown coefficients, $a$, $b$ and $M$, any three shadows can be used to create three equations. Two shadows cannot. One shadow cannot. Four or five shadows are redundant.

### Vector Scheme

George Blakley invented a scheme using points in space. The messge is defined as a point in $m$-dimensional space. Each shadow is the equation of an $(m - 1)$-dimensional hyperplane that includes the point. The intersection of any $m$ of the hyperplanes exactly determines the point.

### Asmuth-Bloom

This scheme uses prime numbers. For an $(m, n)$-threshold scheme, choose a large prime, $p$, greater than $M$