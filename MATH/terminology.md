English | [中文版](terminology_zh.md)

# Terminology

[TOC]



## Algorithm

- **Algorithm**: a finite sequence of precise instructions for performing a computation or solving a problem.
- **Algorithmic paradigm**: a general approach for constructing algorithms based on a particular concept.
- **Average-case time complexity**: the average amount of time required for an algorithm to solve a problem of a given size.
- **Binary search algorithm**: a procedure for searching an ordered list by successively splitting the list in half.
- **Brute force**: the algorithmic paradigm based on constructing algorithms for solving problems in a naive manner from the statement of the problem and definitions.
- **Greedy algorithm**: an algorithm that makes the best choice at each step according to some specified condition.
- **Intractable problem**: a problem for which no worst-case polynomial-time algorithm exists for solving it.
- **Linear search algorithm**: a procedure for searching a list element by element.
- **Searching algorithm**: the problem of locating an element in a list.
- **Solvable problem**: a problem that can be solved by an algorithm.
- **Sorting**: the reordering of the elements of a list into prescribed order.
- **Space complexity**: the amount of space in computer memory required for an algorithm to solve a problem.
- **String searching**: given a string, determine all the occurrences where this string occurs within a longer string.
- **Time complexity**: the amount of time required for an algorithm to solve a problem.
- **Tractable problem**: a problem for which no worst-case polynomial-time algorithm that solves it.
- **Unsolvable problem**: a problem that cannot be solved by an algorithm.
- **Worst-case time complexity**: the greatest amount of time required for an algorithm to solve a problem of a given size.
- **$f(x)$ is $O(g(x))$**: the fact that $|f(x)| \leq C|g(x)|$ for all $x > k$ for some constants $C$ and $k$.
- **Witness to the relationship $f(x)$ is $O(g(x))$**: a pair $C$ and $k$ such that $|f(x)| \leq C|g(x)|$ whenever $x > k$.
- **$f(x)$ is $\Omega(g(x))$**: the fact that $|f(x)| \geq c|g(x)|$ for all $x > k$ for some positive constants $C$ and $k$.
- **$f(x)$ is $\Theta(g(x))$**: the fact that $f(x)$ is both $O(g(x))$ and $\Omega(g(x))$.



## Functions

- **Codomain of $f$**: the set $B$, where $f$ is a function from $A$ to $B$.
- **Computable function**: a function for which there is a computer program in some programming language that finds its values.
- **Domain of $f$**: the set $A$, where $f$ is a function from $A$ to $B$.
- **Function from $A$ to $B$**: an assignment of exactly one element of $B$ to each element of $A$.
- **Inverse of $f$**: the function that reverses the correspondence given by $f$ (when $f$ is a bijection).
- **Onto function, surjection**: a function from $A$ to $B$ such that every element of $B$ is the image of some element in $A$.
- **One-to-one function, injection**: a function such that the images of images of elements in its domain are distinct.
- **One-to-one correspondence, bijection**: a function that is both one-to-one and onto.
- **Partial function**: an assignment to each element in a subset of the domain a unique element in the codomain.
- **Range of $f$**: the set of images of $f$.
- **Uncomputable function**: a function for which no computer program in a programming language exists that finds its values.
- **$b$ is the image of $a$ under f**: $b = f(a)$.
- **$a$ is a preimage of $b$ under $f$**: $f(a) = b$.
- **$f \circ g$ (composition of $f$ and $g$)**: the function that assigns $f(g(x))$ to $x$.
- **$\lfloor x \rfloor$ (floor function)**: the largest integer not exceeding $x$.
- **$\lceil x \rceil$ (ceiling function)**: the smallest integer greater than or equal to $x$.



## Generalized Permutations and Combinations

- **Combinatorics**: the study of arrangements of objects.
- **Enumeration**: the counting of arrangements of objects.
- **Tree diagram**: a diagram made up of a root, branches leaving the root, and other branches leaving some of the endpoints of branches.
- **Permutation**: an ordered arrangement of the elements of a set.
- **$r$-permutation**: an ordered arrangement of $r$ elements of a set.
- **P(n, r)**: the number of $r$-Permutation of a set with $n$ elements.
- **$r$-combination**: an unordered selection of $r$ elements of a set.
- **C(n, r)**: the number of $r$-combinations of a set with $n$ elements.
- **Binomial coefficient $n \choose r$**: also the number of $r$-combinations of a set with $n$ elements.
- **Combinatorial proof**: a proof that uses counting arguments rather than algebraic manipulation to prove a result.
- **Pascal's triangle**: a representation of the binomial coefficients, where the $i$th row of the triangle contains ${i \choose j}$ for $j = 0, 1, 2, \cdots, i$.
- **$S(n, j)$**: the Stirling number of the second kind denoting the number of ways to distribute $n$ distinguishable objects into $j$ indistinguishable boxes so that no box is empty.



## Linear Recurrence

- **Characteristic roots of a linear homogeneous recurrence relation with constant coefficients**

  the roots of the polynomial associated with a linear homogeneous recurrence relation with constant coefficients.

- **Derangement**

  a permutation of objects such that no object is in its original place.

- **Divide-and-conquer algorithm**

  an algorithm that solves a problem recursively by splitting it into a fixed number of smaller nonoverlapping subproblems of the same type.

- **Dynamic programming**

  an algorithmic paradigm that finds the solution to an optimization problem by recursively breaking down the problem into overlapping subproblems and combining their solutions with the help of a recurrence relation.

- **Generating function of a sequence**

  the formal series that has the $n$th term of the sequence as the coefficient of $x^n$.

- **Initial conditions for a recurrence relation**

  the values of the terms of a sequence satisfying the recurrence relation before this relation takes effect.

- **Linear homogeneous recurrence relation with constant coefficients**

  a recurrence relation that expresses the terms of a sequence, except initial terms, as a linear combination of previous terms.

- **Linear nonhomogeneous recurrence relation with constant coefficients**

  a recurrence relation that expresses the terms of a sequence, except for initial terms, as linear combination of previous terms plus a function that is not identically zero that depends only on the inex.

- **Recurrence relation**

  a formula expressing terms of a sequence, except for some initial terms, as a function of one or more previous terms of the sequence.

- **Sieve of Eratosthenes**

  a procedure for finding the primes less than a specified positive integer.



## Induction And Recursion

- **Basis step**

  the proof of $P(1)$ in a proof by mathematical induction of $\forall n P(n)$.

- **Final assertion**

  the statement specifying the properties the output values should have if the program worked correctly.

- **Geometric progression**

  a sequence of the form $a, ar, ar^2, \cdots, $ where $a$ and $r$ are real numbers.

- **Inductive step**

  the proof of $P(k) \rightarrow P(k + 1)$ for all positive integers $k$ in a proof by mathematical induction of $\forall n P(n)$.

- **Initial assertion**

  the statement specifying the properties of the input values of a program.

- **Iteration**

  a procedure based on the repeated use of operations in a loop.

- **Loop invariant**

  a property that remains true during every traversal of a loop.

- **Program correctness**

  verification that a procedure always produces the correct result.

- **Recursive algorithm**

  an algorithm that proceeds by reducing a problem to the same problem with a smaller input.

- **Recursive definition of a function**

  a definition of a function that specifies an initial set of values and a rule for obtaining values of this function at integers from its values at smaller integers.

- **Recursive definition of a set**

  a definition of a set that specifies an initial set of elements in the set and a rule for obtaining other elements from those in the set.

- **Sequence**

  a function with domain that is a subset of the set of integers.

- **Strong induction**

  The statement $\forall n P(n)$ is true if $P(1)$ is true and $\forall k [(P(1) \wedge \cdots \wedge P(k)) \rightarrow P(k + 1)]$ is true.

- **Structural induction**

  a technique for proving results about recursively defined sets.

- **Merge sort**

  a sorting algorithm that sorts a list by splitting it in two, sorting each of the two resulting lists, and merging the results into a sorted list.

- **Well-ordering property**

  Every nonempty set of nonnegative integers has a least element.



## Logic & Proof

- **Argument**

  a sequence of statements.

- **Argument form**

  a sequence of compound propositions involving propositional variables.

- **Axiom**

  a statement that is assumed to be true and that can be used as a basis for proving theorems.

- **Bit operation**

  an operation on a bit or bits.

- **Bitwise operations**

  operations on bit strings that operate on each bit in one string and the corresponding bit in the other string.

- **Bound variable**

  a variable that is quantified.

- **Circular reasoning or begging the question**

  reasoning where one or more steps are based on the truth of the statement being proved.

- **Compound Proposition**

  a proposition constructed by combining propositions using logical operators.

- **Conclusion**

  the final statement in an argument or argument form.

- **Conjecture**

  a mathematical assertion proposed to be true, but that has not been proved.

- **Consistent compound propositions**

  compound propositions for which there is an assignment of truth values to the variables that make all these propositions true.

- **Constructive existence proof**

  a proof that an element with a specified property exists that explicitly finds such an element.

- **Contradiction**

  a compound proposition that is always false.

- **Contingency**

  a compound proposition that is sometimes true and sometimes false.

- **Corollary**

  a proposition that can be proved as a consequence of a theorem that has just been proved.

- **Counterexample**

  an element $x$ such that $P(x)$ is false.

- **Definition**
  An explanation of the mathematical meaning of a word.
  
- **Direct proof**
  
  a proof that $p \rightarrow q$ It is true that proceeds by showing that $q$ must be true when $p$ is true.
  
- **Domain (or universe) of discourse**
  
  the values a variable in a propositional function may take.
  
- **Exhaustive proof**
  
  a proof that establishes a result by checking a list of all possible cases.
  
- **Fallacy**
  
  an invalid argument form is often used incorrectly as a rule of inference (or sometimes, more generally, an incorrect argument).
  
- **Free variable**
  
  a variable not bound in a propositional function.
  
- **Lemma**
  
  a theorem used to prove other theorems.
  
- **Logic circuit**

  a switching circuit made up of logic gates that produces one or more output bits.

- **Logically equivalent compound propositions**

  compound propositions that always have the same truth values.

- **Logically equivalent expressions**

  expressions that have the same truth value no matter which propositional functions and domains are used.

- **Logic gate**

  a logic element that performs a logical operation on one or more bits to produce an output bit.

- **Logical operators**

  operators used to combine propositions.

- **Nonconstructive existence proof**

  a proof that an element with a specified property exists that does not explicitly find such an element.

- **Paradox**

  a logical inconsistency.

- **Predicate**

  part of a sentence that attributes a property to the subject.

- **Premise**

  a statement, in an argument, or argument form, other than the final one.

- **Proof**

  a demonstration that a theorem is true.

- **Proof by contraposition**

  a proof that $p \rightarrow q$ It is true that proceeds by showing that $p$ must be false when $q$ is false.

- **Proof by cases**

  a proof is broken into separate cases, where these cases cover all possibilities.

- **Proof by contradiction**

  a proof that $p$ is true based on the truth of the conditional statement $\neg p \rightarrow q$, where $q$ is a contradiction.

- **Proposition**

  a statement that is true or false.

- **Propositional function**

  a statement containing one or more variables that becomes a proposition when each of its variables is assigned a value or is bound by a quantifier.

- **Rational number**

  a number that can be expressed as the ratio of two integers $p$ and $q$ such that $q \neq 0$.

- **Rule of inference**

  a valid argument form that can be used in the demonstration that arguments are valid.

- **Satisfiable compound proposition**

  a compound proposition for which there is an assignment of truth values to its variables that makes it true.

- **Scope of a quantifier**

  portion of a statement where the quantifier binds its variable.

- **Tautology**

  a compound proposition that is always true.

- **Theorem**

  a mathematical assertion that can be shown to be true.

- **Trivial proof**

  a proof that $p \rightarrow q$ is true based on the fact that $q$ is true.

- **Truth table**

  a table displaying all possible truth values of propositions.

- **Uniqueness proof**

  a proof that there is exactly one element satisfying a specified property.

- **Vacuous proof**

  a proof that $p \rightarrow q$ is true based on the fact that $p$ is false.

- **Valid argument**

  an argument with a valid argument form.

- **Valid argument form**

  a sequence of compound propositions involving propositional variables where the truth of all the premises implies the truth of the conclusion.

- **Without loss of generality**

  an assumption in a proof that makes it possible to prove a theorem by reducing the number of cases to consider in the proof.



## Sequence

- **Arithmetic progression**: a sequence of the form $a, a + d, a + 2d, ...$, where $a$ and $d$ are real numbers.
- **Geometric progression**: a sequence of the form $a, ar, ar^2, ...$, where $a$ and $r$ are real numbers.
- **Recurrence relation**: an equation that expresses the $n$th term $a_n$ of a sequence in terms of one or more of the previous terms of the sequence for all integers $n$ greater than a particular integer.
- **Sequence**: a function with domain that is a subset of the set of integers.
- **$\sum_{i = 1}^{n}a_i$**: the sum $a_1 + a_2 + ... + a_n$.
- $\prod_{i=1}^{n}a_i$: the product $a_1 a_2 ... a_n$.



## Sets And Operations

- **Cardinality**: two sets $A$ and $B$ have the same cardinality if there is a  one-to-one correspondence from A to B.
- **Countable set**: a set that either is finite or can be placed in one-to-one correspondence with the set of positive integers.
- **$\emptyset$(empty set, null set)**: the set with no members.
- **Finite set**: a set with $n$ elements, where $n$ is a nonnegative integer.
- **Infinite set**: a set that is not finite.
- **Multiset**: an unordered collection of objects where objects can occur multiple times.
- **Roster method**: a method that describes a set by listing its elements.
- **Set**: an unordered collection of distinct objects.
- **Uncountable set**: a set that is not countable.
- **Universal set**: the set containing all objects under consideration.
- **Venn diagram**: a graphical representation of a set or sets.
- **|S| (the cardinality of S)**: the number of elements in $S$.
- **P(S) (the power set of S)**: the set of all subsets of $S$.
- **$S = T$ (set equality)**: $S$ and $T$ have the same elements.
- **$S \subseteq T$ (S is a subset of T)**: every element of $S$ is also an element of T.
- **$S \subset T$ (S is a proper subset of T)**: $S$ is a subset of $T$ and $S \neq T$.
- **$A \cup B$ (the union of A and B)**: the set containing those elements that are in at least one of A and B.
- **$A \cap B$ (the intersection of A and B)**: the set containing those elements that are in both $A$ and $B$.
- **$A - B$ (the difference of A and B)**: the set containing those elements that are in $A$ but not in $B$.
- **$\overline{A}$ (the complement of A)**: the set of elements in the universal set that are not in $A$.
- **$A \oplus B$ (the symmetric difference of A and B)**: the set containing those elements in exactly one of $A$ and $B$.



## Matrix

- **Matrix**: a rectangular array of numbers.
- **Symmetric matrix**: a matrix is symmetric if it equals its transpose.
- **Zero-one matrix**: a matrix with each entry equal to either 0 or 1.
- **$I_n$ (identity matrix of order $n$)** the $n \times n$ matrix that has entries equal to 1 on its diagonal and 0s elsewhere.
- **$A^t (\text{transpose of } A)$**: the matrix obtained from $A$ by interchanging the rows and columns.



## Number Theory

- **Affine cipher**: a cipher that encrypts the plaintext letter $p$ as $(ap + b) \mod m$ for integers $a$ and $b$ with $\gcd(a, 26) = 1$.

- **Bezout coefficients of $a$ and $b$**: integers $s$ and $t$ such that the **Bezout identity** $sa + tb = \gcd(a, b)$ holds.

- **Binary representation**: the base 2 representation of an integer.

- **Block cipher**: a cipher that encrypts blocks of characters of a fixed size.

- **Carmichael number**: a composite integer $n$ such that $n$ is a pseudoprime to the base $b$ for all positive integers $b$ with $\gcd(b, n) = 1$.

- **Character cipher**: a cipher that encrypts characters one by one.

- **Composite**: an integer greater than 1 that is not prime.

- **Cryptanalysis**: the process of recovering the plaintext from ciphertext without knowledge of the encryption method, or with knowledge of the encryption method, but not the key.

- **Cryptosystem**: a five-tuple $(\mathcal{P}, \mathcal{C}, \mathcal{K}, \mathcal{E}, \mathcal{D})$ where $\mathcal{P}$ is the set of plaintext messages, $\mathcal{C}$ is the set of ciphertext messages, $\mathcal{K}$ is the set of keys, $\mathcal{E}$ is the set of encryption functions, and $\mathcal{D}$ is the set of decryption functions.

- **Decryption**: the process of returning a secret message to its original form.

- **Digital signature**: a method that a recipient can use to determine that the purported sender of a message actually sent the message.

- **Discrete logarithm of $a$ to the base $r$ modulo $p$**: the integer $e$ with $0 \leq e \leq p - 1$ such that $r^e \equiv a (\mod p)$.

- **Encryption**: the process of making a message secret.

- **Encryption key**: a value that determines which of a family of encryption functions is to be used.

- **Fully homomorphic cryptosystem**: a cryptosystem that allows arbitrary computations to be run on encrypted data so that the output is the encryption of the unencrypted output of the unencrypted input.

- **Fundamental theorem of arithmetic**: Every positive integer can be written uniquely as the product of primes, where the prime factors are written in order of increasing size.

  If $a$ and $b$ are positive integers, then $ab = \gcd(a, b) \cdot lcm(a,b)$.

  If $m$ is a positive integer and $\gcd(a, m) = 1$, then $a$ has a unique inverse modulo $m$.

- **Hexadecimal representation**: the base 16 representation of an integer.

- **Inverse of $a$ modulo $m$**: an integer $\overline{a}$ such that $\overline{a}a \equiv 1 (\mod m)$.

- **Key exchange protocol**: a protocol sued for two parties to generate a shared key.

- **Linear combination of $a$ and $b$ with integer coefficients**: an expression of the form $sa + tb$, where $s$ and $t$ are integers.

- **Linear congruence**: a congruence of the form $ax \equiv b (\mod m)$, where $x$ is an integer variable.

- **Mersenne prime**: a prime of the form $2^p - 1$, where $p$ is prime.

- **Modular arithmetic**: arithmetic done modulo an integer $m \geq 2$.

- **Octal representation** the base 8 representation of an integer.

- **Pairwise relatively prime integers**: a set of integers with the property that every pair of these integers is relatively prime.

- **Prime**: an integer greater than 1 with exactly two positive integer divisors.

- **Private key encryption**: encryption where both encryption keys and decryption keys must be kept secret.

- **Pseudoprime to the base $b$**: a composite integer $n$ such that $b^{n - 1} \equiv 1 (\mod n)$.

- **Primitive root of a prime $p$**: an integer $r$ in $Z_p$ such that every integer not divisible by $p$ is congruent modulo $p$ to a power of $r$.

- **Public key encryption**: encryption where encryption keys are public knowledge, but decryption keys are kept secret.

- **Relatively prime integers**: integers $a$ and $b$ such that $\gcd(a, b) = 1$.

- **RSA cryptosystem**: the cryptosystem where $\mathcal{P}$ and $\mathcal{C}$ are both $Z_{26}$, $\mathcal{K}$ is the set of pairs $k = (n, e)$ where $n = pq$ where $p$ and $q$ are large primes and $e$ is a positive integer, $E_{k}(p) = p^e \mod n$, and $D_k(c) = c^d \mod n$ where $d$ is the inverse of $e$ modulo $(p - 1)(q - 1)$.

- **Shift cipher**: a cipher that encrypts the plaintext letter $p$ as $(p + k) \mod m$ for an integer $k$.

- **$a | b$ ($a$ divides $b$)**: there is an integer $c$ such that $b = ac$.

- **$a$ and $b$ are congruent modulo $m:m$ divides $a - b$.**

- **$lcm(a, b)$ (least common multiple of $a$ and $b$)**: the smallest positive integer that is divisible by both $a$ and $b$.

- **$a \mod b$**: the remainder when the integer $a$ is divided by the positive integer $b$.

- **$a \equiv b (\mod m)$ ($a$ is congruent to $b$ modulo $m$)**: $a - b$ is divisible by $m$.

- $n = (a_k a_{k - 1} \cdots a_1 a_0)_b$: the base $b$ representation of $n$.

- **$\gcd(a, b)$ (greatest common divisor of $a$ and $b$)**: the largest integer that divides both $a$ and $b$.



## Probability

- **Bernoulli trial**

  an experiment with two possible outcomes.

- **Distribution of a random variable X**

  the set of pairs $(r, p(X = r))$ for $r \in X(S)$.

- **Event**

  a subset of the sample space of an experiment.

- **Expected value of a random variable**

  the weighted average of a random variable, with values of the random variable weighted by the probability of outcomes, that is, $E(X) = \sum_{s \in S}p(s)X(s)$.

- **Geometric distribution**

  the distribution of a random variable $X$ such that $p(X = k) = (1 - p)^{k - 1}p$ for $k = 1, 2, ...$ for some real number $p$ with $0 \leq p \leq 1$.

- **Independent events**

  events $E$ and $F$ such that $p(E \cap F) = p(E)p(F)$.

- **Independent random variables**

  random variables $X$ and $Y$ such that $p(X = r_1 \text{ and } Y = r_2) = p(X = r_1)p(Y = r_2)$ for all real numbers $r_1$ and $r_2$.

- **Mutually independent events**

  events $E_1, E_2, ..., E_n$ such that $p(E_{i_1} \cap E_{i_2} \cap \cdots \cap E_{i_m}) = p(E_{i_1})p(E_{i_2}) \cdots p(E_{i_m})$ whenever $i_j, j = 1, 2, ..., m$ are integers with $1 \leq i_1 < i_2 < \cdots < i_m \leq n$ and $m \geq 2$.

- **Pairwise independent events**

  events $E_1, E_2, ..., E_n$ such that $p(E_i \cap E_j) = p(E_i)p(E_j)$ for all pairs of integers $i$ and $j$ with $1 \leq j < k \leq n$.

- **Probability distribution**

  a function $p$ from the set of all outcomes of a sample space $S$ for which $0 \leq p(x_i) \leq 1$ for $i = 1, 2, ..., n$ and $\sum_{i=1}^{n}p(x_i) = 1$, where $x_1, ..., x_n$ are the possible outcomes.

- **Probability of an event (Laplace's definition)**

  the number of successful outcomes of this event divided by the number of possible outcomes.

- **Probability of an event E**

  the sum of the probabilities of the outcomes in $E$.

- **Probabilistic (or Monte Carlo) algorithm**

  an algorithm in which random choices are made at one or more steps.

- **Probabilistic method**

  a technique for proving the existence of objects in a set with certain properties that proceeds by assigning probabilities to objects and showing that the probability that an object has these properties is positive.

- **Random variable**

  a function that assigns a real number to each possible outcome of an experiment.

- **Sample space**

  the set of possible outcomes of an experiment.

- **Standard deviation of a random variable $X$**

  the square root of the variance of $X$, that is, $\sigma(X) = \sqrt{V(X)}$.

- **Uniform distribution**

  the assignment of equal probabilities to the elements of a finite set.

- **Variance of a random variable $X$**

  the weighted average of the square of the difference between the value of $X$ and its expected value $E(X)$, with weights given by the probability of outcomes, that is, $V(X) = \sum_{s \in S}(X(s) - E(X))^2 p(s)$.

- **$p(E|F)$ (conditional probability of $E$ given $F$)**: the ratio $p(E \cap F) / p(F)$.
