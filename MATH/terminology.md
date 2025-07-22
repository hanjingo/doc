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



## Boolean Algebra

- **AND gate**: a device that accepts the values of two or more Boolean variables as input and produces their Boolean product as output.
- **Boolean algebra**: a set $B$ with two binary operations $\vee$ and $\wedge$, elements 0 and 1, and a complementation operator $\overline{}$ that satisfies the identity, complement, associative, commutative, and distributive laws.
- **Boolean expressions**: the expressions obtained recursively by specifying that 0, 1, $x_1$, ..., $x_n$ are Boolean expressions and $\overline{E_1}$, $E_1 + E_2$, and $(E_1 E_2)$ are Boolean expressions if $E_1$ and $E_2$​ are.
- **Boolean function of degree $n$**: a function from $B^n$ to $B$ where $B = \{0, 1\}$.
- **Boolean variable**: a variable that assumes only the values 0 and 1.
- **Don't care condition**: a combination of input values for a circuit that is not possible or never occurs.
- **Dual of a boolean expression**: the expression obtained by interchanging $+$ signs and $\cdot$ signs and interchanging $0s$ and $1s$.
- **Essential prime implicant of a Boolean function**: a prime implicant of the Boolean function that must be included in a minimization of this function.
- **Full adder**: a circuit that adds two bits and a carry, producing a sum bit and a carry bit.
- **Functionally complete**: a set of Boolean operators is called functionally complete if every Boolean function can be represented using these operators.
- **Half adder**: a circuit that adds two bits, producing a sum bit and a carry bit.
- **Implicant of a Boolean function**: a product of literals with the property that if this product has the value 1, then the value of this Boolean function is 1.
- **Inverter**: a device that accepts the value of a Boolean variable as input and produces the complement of the input.
- **K-map for $n$ variables**: a rectangle divided into $2^n$ cells where each cell represents a minterm in the variables.
- **Literal of the Boolean variable $x$**: either $x$ or $\overline{x}$.
- **Minimization of a Boolean function**: representing a Boolean function as the sum of the fewest products of literals such that these products contain the fewest literals possible among all sums of products that represent this Boolean function.
- **Minterm of $x_1, x_2, ..., x_n$**: a Boolean product $y_1 y_2 \cdots y_n$, where each $y_i$ is either $x_i$ or $\overline{x_i}$.
- **OR gate**: a device that accepts the values of two or more Boolean variables as input and produces their Boolean sum as output.
- **Prime implicant of a Boolean function**: a product of literals that is an implicant of the Boolean function and no product obtained by deleting a literal is also an implicant of this function.
- **Sum-of-products expansion** (or disjunctive normal form): the representation of a Boolean function as a disjunction of minterms.
- **$\overline{x}$(complement of $x$)**: an expression with the value 1 when $x$ has the value 0 and the value 0 when $x$ has the value 1.
- **$x \cdot y$ (or $xy$) (Boolean product or conjunction of $x$ and $y$)**: an expression with the value 1 when both $x$ and $y$ have the value 1 and the value 0 otherwise.
- **$x + y$(Boolean sum or disjunction of $x$ and $y$)**: an expression with the value 1 when either $x$ or $y$, or both, has the value 1, and 0 otherwise.
- **$x | y (\text{or x NAND y})$**: the expression that has the value 0 when both $x$ and $y$ have the value 1 and the value 1 otherwise.
- **$x \downarrow y (\text{or x NOR y})$**: the expression that has the value 0 when either $x$ or $y$ or both have the value 1 and the value 0 otherwise.



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



## Modeling Computation

- **AB(concatenation of A and B)**: the set of all strings formed by concatenating a string in A and a string in B in that order.
- **$A^{*} $ (Kleene closure of A)**: the set of all strings made up by concatenating arbitrarily many strings from A.
- **Alphabet (or vocabulary)**: a set that contains elements used to form strings.
- **Backus-Naur form**: a description of a context-free grammar in which all productions having the same nonterminal as their left-hand side are combined with the different right-hand sides of these productions, each separated by a bar, with nonterminal symbols enclosed in angular brackets and the symbol $\rightarrow$ replaced by $::=$.
- **Computable function**: a function whose values can be computed using a Turing machine.
- **Decision problem**: a problem that asks whether statements from a particular class of statements are true.
- **Derivation (or parse) tree**: an ordered rooted tree where the root represents the starting symbol of a type 2 grammar, internal vertices represent nonterminals, leaves represent terminals, and the children of a vertex are the symbols on the right side of a production, in order from left to right, where the symbol represented by the parent is on the left-hand side.
- **Deterministic finite-state automaton $(S, I, f, s_0, F)$**: a five-tuple containing a set $S$ of states, an input alphabet $I$, a transition function $f$ that assigns a next state to every pair of a state and an input, a starting state $s_0$, and a set of final states $F$.
- **Finite-state machine $(S, I, O, f, g, s_0)$ (or a Mealy machine)**: a six-tuple containing a set $S$ of states, an input alphabet $I$, an output alphabet $O$, a transition function $f$ that assigns a next state to every pair of a state and an input, an output function $g$ that assigns an output to every pair of a state and an input, and a starting state $s_0$.
- **Language**: a subset of the set of all strings over an alphabet.
- **Language recognized by an automaton**: the set of input strings that take the start state to a final state of the automaton.
- **Nondeterministic finite-state automation $(S, I, f, s_0, F)$**: a five-tuple containing a set $S$ of states, an input alphabet $I$, a transition function $f$ that assigns a set of possible next states to every pair of a state and an input, a starting state $s_0$, and a set of final states $F$.
- **Nondeterministic Turing machine**: a Turing machine that may have more than one transition rule corresponding to each (state, tape symbol) pair.
- **Phrase-structure grammar $(V, T, S, P)$**: a description of a language containing a alphabet $V$, a set of terminal symbols $T$, a start symbol $S$, and a set of productions $P$.
- **Regular expression**: an expression defined recursively by specifying that $\theta$, $\lambda$, and $x$, for all $x$ in the input alphabet, are regular expressions, and that $(AB)$, $(A \cup B)$, and $A^{*}$ are regular expressions when $A$ and $B$ are regular expressions.
- **Regular set**: a set defined by a regular expression.
- **Solvable problem**: a problem with the property that there is an effective algorithm that can solve all instances of the problem.
- **The production $w \rightarrow w_1$**: $w$ cna be replaced by $w_1$ whenever it occurs in a string in the language.
- **Turing machine $T = (S, I, f, s_0)$**: a four-tuple consisting of a finite set $S$ of states, an alphabet $I$ containing the blank symbol $B$, a partial function $f$ from $S \times I$ to $S \times I \times \{R, L\}$, and a starting state $s_0$.
- **Type 0 grammar**: any phrase-structure grammar.
- **Type 1 grammar**: a phrsae-structure grammar in which every production is of the form $w_1 \rightarrow w_2$, where $w_1 = lAr$ and $w_2 = lwr$, where $A \in N, l, r, w \in (N \cup T) * and w \neq \lambda$, or $w_1 = S$ and $w_2 = \lambda$ as long as $S$ is not on the right-hand side of another production.
- **Type 2, or context-free, grammar**: a phrase-structure grammar in which every production is of the form $A \rightarrow w_1$, where $A$ is a nonterminal symbol.
- **Type 3, or regular, grammar**: a phrase-structure grammar where every production is of the form $A \rightarrow aB$, $A \rightarrow a$, or $S \rightarrow \lambda$, where $A$ and $B$ are nonterminal symbols, $S$ is the start symbol, and $a$ is a terminal symbol
- **Uncomputable function**: a function whose values cannot be computed using a Turing machine.
- **Unsolvable problem**: a problem with the property that no effective algorithm exists that can solve all instances of the problem.
- **$w_1 \Rightarrow w_2$ ($w_2$ is directly derivable from $w_1$)**: $w_2$ can be obtained from $w_1$ using a production to replace a string in $w_1$ with another string.
- **$w_1 \Rightarrow^* w_2$($w_2$ is derivable from $w_1$)**: $w_2$ can be obtained from $w_1$ using a sequence of productions ot replace strings by other strings.
- **P, the class of polynomial-time problems**: the class of problems that can be solved by a deterministic Turing machine in polynomial time in terms of the size of the input.
- **NP, the class of nondeterministic polynomial-time problems**: the class of problems that can be solved by a nondeterministic Turing machine in polynomial time in terms of the size of the input.
- **NP-complete**: a subset of the class of NP problems with the property that if any one of them is in the class $P$, then all problems in $NP$ are in the class $P$.



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



## Trees

- **Ancestor of a vertex $v$ in a rooted tree**: any vertex on the path from the root to $v$​​.
- **Balanced tree**: a tree in which every leaf is at level $h$ or $h - 1$, where $h$ is the height of the tree.
- **Binary search tree**: a binary tree in which the vertices are labeled with items so that a label of a vertex is greater than the labels of all vertices in the left subtree of this vertex and is less than the labels of all vertices in the right subtree of this vertex.
- **Binary tree**: an $m$-ary tree with $m = 2$(each child may be designated as a left or a right child of its parent).
- **Child of a vertex $v$ in a rooted tree**: any vertex with $v$​​ as its parent.
- **Decision tree**: a rooted tree where each vertex represents a possible outcome of a decision and the leaves represent the possible solutions of a problem.
- **Descendant of a vertex $v$ in a rooted tree**: any vertex that has $v$ as an ancestor.
- **Forest**: an undirected graph with no simple circuits.
- **Full $m$-ary tree**: a tree with the property that every internal vertex has exactly $m$​ children.
- **Game tree**: a rooted tree where vertices represent the possible positions of a game as it progresses and edges represent legal moves between these positions.
- **Height of a tree**: the largest level of the vertices of a tree.
- **Infix notation**: the form of an expression (including a full set of parentheses) obtained from an inorder traversal of the binary tree representing this expression.
- **Inorder traversal**: a listing of the vertices of an ordered rooted tree defined recursively--the first subtree is listed, followed by the root, followed by the other subtrees in the order they occur from left to right.
- **Internal vertex**: a vertex that has children.
- **Leaf**: a vertex with no children.
- **Level of a vertex**: the legth of the path from the root to this vertex.
- **$m$-ary tree**: a tree with the property that every internal vertex has no more than $m$​​ children.
- **Minmax strategy**: the strategy where the first player and second player move to positions represented by a child with maximum and minimum value, respectively.
- **Minimum spanning tree**: a spanning tree with smallest possible sum of weights of its edges.
- **Ordered tree**: a tree in which the children of each internal vertex are linearly ordered.
- **Parent of $v$ in a rooted tree**: the vertex $u$ such that $(u, v)$​​​ is a edge of the rooted tree.
- **Postorder traversal**: a listing of the vertices of an ordered rooted tree defined recursively--the subtrees are listed in the order they occur from left to right, followed by the root.
- **Prefix code**: a code that has the property that the code of a character is never a prefix of the code of another character.
- **Prefix (or Polish) notation**: the form of an expression obtained from a preorder traversal of the tree representing this expression.
- **Postfix (or reverse Polish) notation**: the form of an expression obtained from a postorder traversal of the tree representing this expression.
- **Preorder traversal**: a listing of the vertices of an ordered rooted tree defined recursively--the root is listed, followed by the first subtree, followed by the other in the order they occur from left to right.
- **Rooted tree**: a directed graph with a specified vertex, called the root, such that there is a unique path to every other vertex from this root.
- **Sibling of a vertex $v$ in a rooted tree**: a vertex with the same parent as $v$​.
- **Spanning tree**: a tree containing all vertices of a graph.
- **Subtree**: a subgraph of a tree that is also a tree.
- **Tree**: a connected undirected graph with no simple circuits.
- **Tree traversal**: a listing of the vertices of a tree.
- **Value of a vertex in a game tree**: for a leaf, the payoff to the first player when the game terminates in the position represented by this leaf; for an internal vertex, the maximum or minimum of the values of its children, for an internal vertex at an even or odd level, respectively.



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
