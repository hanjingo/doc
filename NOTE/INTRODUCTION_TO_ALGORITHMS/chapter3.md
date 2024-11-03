# 3 Growth of Functions



## 3.1 asymptotic notation

**$\theta$-notation**

For a given function $g(n)$ we denote by $\theta(g(n))$ the set of functions:
$$
\theta(g(n)) = \{f(n):\text{there exist positive constants} c_1, c_2 \text{ and } n_0 \text{ such that}\}\\ 
0 \leq c_1 g(n) \leq f(n) \leq c_2 g(n) \text{ for all } n \geq n_0 \}
$$
For all $n \geq n_0$, the function $f(n)$ is equal to $g(n)$ to within a constant factor. We say that $g(n)$ is an `asymptotically tight bound` for $f(n)$.

Graphic examples of the $\theta$:

![3_1](res/3_1.png)

**$O$-notation**

The $\theta$-notation asymptotically bounds a function from above and below. When we have only an `asymptotic upper bound`, we use $O$-notation. For a given function $g(n)$, we denote by $O(g(n))$ (pronounced "big-oh of g of n" or sometimes just "oh of g of n") the set of functions:
$$
O(g(n)) = \{f(n)：\text{there exist positive constants}\ c \text{ and } n_0 \text{ such that}\\
0 \leq f(n) \leq cg(n) \text{ for all } n \geq n_0\}
$$
, we use $O$-notation to give an upper bound on a function, to within a constant factor.

**$\Omega$-notation**

Just as $O$-notation provides an asymptotic upper bound on a function, $\Omega$-notation provides an `asymptotic lower bound`. For a given function $g(n)$, we denote by $\Omega(g(n))$ (pronounced "big-omega of g of n" or sometimes just "omega of g of n") the set of functions:
$$
\Omega(g(n)) = \{f(n): \text{there exist positive constants } c \text{ and } n_0 \text{ such\ that}\\
0 \leq cg(n) \leq f(n) \text{ for all } n \geq n_0\}
$$
**Theorem 3.1** For any two functions $f(n)$ and $g(n)$, we have $f(n) = \theta(g(n))$ if and only if $f(n) = O(g(n))$ and $f(n) = \Omega(g(n))$.

**$o$-notation**

We use $o$-notation to denote an upper bound that is not asymptotically tight. We formally define $o(g(n))$ ("little-oh of g of n") as the set:
$$
o(g(n)) = \{f(n): \text{for any positive constant } c > 0，\text{ there exists a constant}\\
n_0 > 0 \text{ such that } 0 \leq f(n) < cg(n) \text{ for all } n \geq n_0\}
$$
Intuitively, in $o$-notation, the function $f(n)$ becomes insignificant relative to $g(n)$ as $n$ approaches infinity; that is: $\lim_{n \to \infty} \frac{f(n)}{g(n)} = 0$.

**$\omega$-notation**

$\omega$-notation is to $\Omega$-notation as $o$-notation is to $O$-notation. We use $\omega$-notation to denote a lower bound that is not asymptotically tight. One way to define it is by: $f(n) \in \omega(g(n))$ if and only if $g(n) \in o(f(n))$.

, formally, however, we define $\omega(g(n))$ ("little-omega of g of n") as the set:
$$
\omega(g(n)) = \{f(n): \text{for any positive constant } c > 0, \text{there exists a constant}\\
n_0 > 0 \text{ such that } 0 \leq cg(n) \text{ for all } n \geq n_0\}
$$
, the relation $f(n) = \omega(g(n))$ implies that: $\lim_{n \to \infty} \frac{f(n)}{g(n)} = \infty$, if the limit exists. That is, $f(n)$ becomes arbitrarily large relative to $g(n)$ as $n$ approaches infinity.

**Comparing functions**

For the following, assume that $f(n)$ and $g(n)$ are asymptotically positive.

**Transitivity**
$$
f(n) = \theta(g(n))\ and\ g(n) = \theta(h(n)) &imply\ f(n) = \theta(h(n)) \\
f(n) = O(g(n))\ and\ g(n) = O(h(n)) &imply\ f(n)=O(h(n)) \\
f(n) = \Omega(g(n))\ and\ g(n) = \Omega(h(n)) &imply\ f(n)=\Omega(h(n)) \\
f(n) = o(g(n))\ and\ g(n) = o(h(n)) &imply\ f(n)=o(h(n)) \\
f(n) = \omega(g(n))\ and\ g(n) = \omega(h(n)) &imply\ f(n)=\omega(h(n))
$$
**Reflexivity**
$$
f(n) = \theta(f(n)) \\
f(n) = O(f(n)) \\
f(n) = \Omega(f(n))
$$
**Symmetry**
$$
f(n) = \theta(g(n)) \text{ if and only if } g(n)=\theta(f(n))
$$
**Transpose symmetry**
$$
f(n) = O(g(n)) \text{ if and only if } g(n)=\Omega(f(n)) \\
f(n) = o(g(n)) \text{ if and only if } g(n)=\omega(f(n))
$$
**Trichotomy**: For any two real numbers $a$ and $b$, exactly one of the following must hold: $a < b, a = b, or\ a > b$.



## 3.2 Standard notations and common functions

**Monotonicity**

A function $f(n)$ is monotonically increasing if $m \leq n$ implies $f(m) \leq f(n)$. Similarly, it is monotonically decreasing if $m \leq n$ implies $f(m) \geq f(n)$. A function $f(n)$ is strictly increasing if $m < n$ implies $f(m) < f(n)$ and strictly decreasing if $m < n$ implies $f(m) > f(n)$.

**Floors and ceilings**

For any real number $x$, we denote the greatest integer less than or equal to $x$ by $\lfloor x \rfloor$ (read "the floor of $x$") and the least integer greater than or equal to $x$ by $\lceil x \rceil$ (read "the ceiling of $x$"). For all real $x$,
$$
x - 1 < \lfloor x \rfloor \leqslant x \leqslant \lceil x \rceil < x + 1
$$
, for any integer $n$,
$$
\lceil n/2 \rceil + \lfloor n/2 \rfloor = n
$$
, and for any real number $x \geq 0$ and integers $a, b > 0$,
$$
\lceil \frac{\lceil x/a \rceil}{b} \rceil = \lceil \frac{x}{ab} \rceil
$$

$$
\lfloor \frac{\lfloor x/a \rfloor}{b} \rfloor = \lfloor \frac{x}{ab} \rfloor
$$

$$
\lceil \frac{a}{b} \rceil \leqslant \frac{a + (b - 1)}{b}
$$

$$
\lfloor \frac{a}{b} \rfloor \geqslant \frac{a - (b - 1)}{b}
$$

, the floor function $f(x) = \lfloor x \rfloor$ is monotonically increasing, as is the ceiling function $f(x) = \lceil x \rceil$.

**Modular arithmetic**

For any integer $a$ and any positive integer $n$, the value $a\ mod\ n$ is the remainder (or residue) of the quotient $a/n$:
$$
a\ mod\ n = a - n \lfloor a/n \rfloor
$$
, it follows that:
$$
0 \leq a\ mod\ n < n
$$


**Polynomials**

Given a nonnegative integer $d$, a `polynomial in n of degree d` is a function $p(n)$ of the form:
$$
p(n) = \sum_{i=0}^{d} a_in^i
$$
, where the constants $a_0, a_1, ..., a_d$ are the `coefficients` of the polynomial and $a_d \neq 0$. A polynomial is asymptotically positive if and only if $a_d > 0$. For an asymptotically positive polynomial $p(n)$ of degree $d$, we have $p(n) = \theta(n^d)$. For any real constant $a \geq 0$, the function $n^a$ is monotonically increasing, and for any real constant $a \leq 0$, the function $n^a$ is monotonically decreasing. We say that a function $f(n)$ is `polynomially bounded` if $f(n) = O(n^k)$ for some constant $k$.

**Exponentials**

For all real constants $a$ and $b$ such that $a > 1$:
$$
\lim_{n \to \infty} \frac{n^b}{a^n} = 0
$$
, from which we can conclude that:
$$
n^b = o(a^n)
$$
, thus, any exponential function with a base strictly greater than 1 grows faster than any polynomial function.

Using $e$ to denote 2.71828..., the base of the natural logarithm function, we have for all real $x$,
$$
e^x = 1 + x + \frac{x^2}{2!} + \frac{x^3}{3!} + ... = \sum_{i=0}^{\infty}\frac{x^i}{i!}
$$
, where "!" denotes the factorial function defined later in this section. For all real $x$, we have the inequality:
$$
e^x \geqslant 1 + x
$$
, where equality holds only when $x = 0$. When $|x| \leq 1$, we have the approximation:
$$
1 + x \leq e^x \leq 1 + x + x^2
$$
, when $x \to 0$, the approximation of $e^x$ by $1 + x$ is quite good:
$$
e^x = 1 + x + \theta(x^2)
$$
, (in this equation, the asymptotic notation is used to describe the limiting behavior as $x \rightarrow 0$ rather than as $x \rightarrow \infty$.) We have for all $x$,
$$
\lim_{n \to \infty}(1 + \frac{x}{n}) ^ n = e^x
$$
**Logarithms**
$$
lgn = log_2n &(\text{binary logarithm}) \\
lnn = log_en &(\text{natural logarithm}) \\
lg^kn = (lgn)^k &(\text{exponentiation}) \\
lglgn = lg(lgn) &(\text{composition})
$$
For all real $a > 0, b > 0, c > 0$, and $n$,
$$
\begin{equation}\begin{split} 
a &= b^{log_b{a}} \\
log_c{(ab)} &= log_c{a} + log_c{b} \\
log_b{a^n} &= n log_b{a} \\
log_b{a} &= \frac{log_c{a}}{log_c{b}} \\
log_b{(1/a)} &= -log_b{a} \\
log_b{a} &= \frac{1}{log_a{b}} \\
a^{log_b{c}} &= c^{log_b{a}}
\end{split}\end{equation}
$$
There is a simple series expansion for $ln(1 + x)$ when $|x| < 1$:
$$
ln(1 + x) = x - \frac{x^2}{2} + \frac{x^3}{3} - \frac{x^4}{4} + \frac{x^5}{5} - ...
$$
, we also have the following inequalities for $x > -1$:
$$
\frac{x}{1+x} \leq ln(1+x) \leq x
$$
, where equality holds only for $x = 0$.

**Factorials**

The notation $n!$ (read "n factorial") is defined for integers $n \geq 0$ as:
$$
f(n)
\begin{cases}
1, &if\ n=0\\
n\cdot (n-1)! &if\ n>0
\end{cases}
$$
, thus, $n!=1 \cdot 2 \cdot 3 \cdot \cdot \cdot n$.

A weak upper bound on the factorial function is $n! \leq n^n$, since each of the $n$ terms in the factorial product is at most $n$. `Stirling's approximation`,
$$
n! = \sqrt{2 \pi n}(\frac{n}{e})^n(1 + \theta(\frac{1}{n}))
$$
, where $e$ is the base of the natural logarithm, gives us a tighter upper bound, and $a$ lower bound as well,
$$
\begin{equation}\begin{split} 
n! &= o(n^n) \\
n! &= \omega(2^n) \\
lg(n!) &= \theta(n\ lg{n})
\end{split}\end{equation}
$$
, where Stirling's approximation is helpful in proving the above equation. The following equation also holds for all $n \geq 1$:
$$
n! = \sqrt{2 \pi n}(\frac{n}{e})^n e^{a_n}
$$
, where:
$$
\frac{1}{12n + 1} < a_n < \frac{1}{12n}
$$
**Functional iteration**

We use the notation $f^{(i)}(n)$ to denote the function $f(n)$ iteratively applied $i$ times to an initial value of $n$. Formally, let $f(n)$ be a function over the real. For non-negative integers $i$, we recursively define:
$$
f^{(i)}(n) = 
\begin{cases}
n, &if\ i=0\\
f(f^{(i-1)}(n)) &if\ i>0
\end{cases}
$$
**The iterated logarithm function**

We define the iterated logarithm function as:
$$
lg^*n = min\{i \geq 0: lg^{(i)} n \leq 1\}
$$
**Fibonacci numbers**

We define the `Fibonacci numbers` by the following recurrence:
$$
\begin{equation}\begin{split} 
F_0 &= 0 \\
F_1 &= 1 \\
F_i &= F_{i-1} + F_{i-2}, \quad i \geqslant 2
\end{split}\end{equation}
$$
