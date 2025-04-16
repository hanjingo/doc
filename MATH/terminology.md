English | [中文版](terminology_zh.md)

# Terminology

[TOC]



## Logic & Proof

- **Argument**

  a sequence of statements.

- **Argument form**

  a sequence fo compound propositions involving propositional variables.

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
  
  a proof that $p \rightarrow q$ is true that proceeds by showing that $q$ must be true when $p$ is true.
  
- **Domain (or universe) of discourse**
  
  the values a variable in a propositional function may take.
  
- **Exhaustive proof**
  
  a proof that establishes a result by checking a list of all possible cases.
  
- **Fallacy**
  
  an invalid argument form often used incorrectly as a rule of inference (or sometimes, more generally, an incorrect argument).
  
- **Free variable**
  
  a variable not bound in a propositional function.
  
- **Lemma**
  
  a theorem used to prove other theorems.
  
- **Logic circuit**

  a switching circuit made up of logic gates that produces one or more output bits.

- **Logically equivalent compound propositions**

  compound propositions that always have the same truth values.

- **Logically equivalent expressions**

  expression that have the same truth value no matter which propositional functions and domains are used.

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

  a proof that $p \rightarrow q$ is true that proceeds by showing that $p$ must be false when $q$ is false.

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



## Matrix

- **Matrix**: a rectangular array of numbers.
- **Symmetric matrix**: a matrix is symmetric if it equals its transpose.
- **Zero-one matrix**: a matrix with each entry equal to either 0 or 1.
- **$I_n$ (identity matrix of order $n$)** the $n \times n$ matrix that has entries equal to 1 on its diagonal and 0s elsewhere.
- **$A^t (\text{transpose of } A)$**: the matrix obtained from $A$ by interchanging the rows and columns.



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
