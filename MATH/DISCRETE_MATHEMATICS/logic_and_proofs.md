# Logic And Proofs

[TOC]



## Definition

**Definition** Let $p$ be a proposition. The negation of $p$, denoted by $\neg{p}$ (also denoted by $\over{p}$), is the statement "It is not the case that $p$".

> The proposition $\neg p$ is read "not $p$". The truth value of the negation of $p$, $\neg p$, is the opposite of the truth value of $p$.

**Definition** Let $p$ and $q$ be propositions. The `conjunction` of $p$ and $q$, denoted by $p \and q$, is the proposition "p and q". The conjunction $p \and q$ is true when both $p$ and $q$​ are true and is false otherwise.

**Definition** Let $p$ and $q$ be propositions. The `disjunction` of $p$ and $q$, denoted by $p \or q$, is the proposition "p or q". The disjunction $p \or q$ is false when both $p$ and $q$ are false and is true otherwise.

**Definition** Let $p$ and $q$ be propositions. The `exclusive` or of $p$ and $q$, denoted by $p \oplus q$ (or $p$ XOR $q$), is the proposition that is true when exactly one of $p$ and $q$ is true and is false otherwise.

**Definition** Let $p$ and $q$ be propositions. The `conditional statement` $p \rightarrow q$ is the proposition "if p, then q". The conditional statement $p \rightarrow q$ is false when $p$ is true and $q$ is false, and true otherwise. In the conditional statement $p \rightarrow q$, $p$ is called the hypothesis (or `antecedent` or `premise`) and $q$​ is called the `conclusion` (or `consequence`).

**Definition** Let $p$ and $q$ be propositions. The `biconditional statement` $p \leftrightarrow q$ is the proposition "$p$ if and only if $q$". The biconditional statement $p \leftrightarrow q$ is true when $p$ and $q$ have the same truth values, and is false otherwise. Biconditional statements are also called `bi-implications`.

**Definition** A `bit string` is a sequence of zero more bits. The length of this string is the number of bits in the string.

**Definition**: A compound proposition that is always true, no matter what the truth values of the propositional variables that occur in it, is called a `tautology`. A compound proposition that is always false is called a `contradiction`. A compound proposition that is neither a tautology nor a contradiction is called a `contingency`.

**Definition**: The compound propositions $p$ and $q$ are called `logically equivalent` if $p \leftrightarrow q$ is a tautology. The notation $p \equiv q$ denotes that $p$ and $q$ are logically equivalent.

**Definition**: The `universal quantification` of $P(x)$ is the statement "P(x) for all values of x in the domain." The notation $\forall x P(x)$ denotes the universal quantification of $P(x)$. Here $\forall$ is called the **universal quantifier**. We read $\forall x P(x)$ as "for all $xP(x)$" or "for every $xP(x)$". An element for which $P(x)$ is false is called a **counterexample** to $\forall x P(x)$.

**Definition**: The `existential quantification` of P(x) is the proposition "There exists an element x in the domain such taht P(x)." We use the notation $\exists x P(x)$ for the existential quantification of $P(x)$. Here $\exists$ is called the `existential quantifier`.

**Definition**: Statements involving predicates and quantifiers are `logically equivalent` if and only if they have the same truth value no matter which predicates are substituted into these statements and which domain of discourse is used for the variables in these propositional functions. We use the notation $S \equiv T$ to indicate that two statements $S$ and $T$ involving predicates and quantifiers are logically equivalent.

**Definition**: An `argument` in propositional logic is a sequence of propositions. All but the final proposition in the argument are called `premises,` and the final proposition is called the `conclusion`. An argument is `valid` if the truth of all its premises implies that the conclusion is true. An `argument form` in propositional logic is a sequence of compound propositions involving propositional variables. An argument form is `valid` if no matter which particular propositions are substituted for the propositional variables in its premises, the conclusion is true if the premises are all true.

**Definition**: The integer $n$ is `even` if there exists an integer $k$ such that $n = 2k$, and $n$ is `odd` if there exists an integer $k$ such that $n = 2k + 1$. (Note that every integer is either even or odd, and no integer is both even and odd.) Two integers have the `same parity` when both are even or both are odd; they have `opposite parity` when one is even and the other is odd.

**Definition**: The real number $r$ is `rational` if there exist integers $p$ and $q$ with $q \neq 0$ such that $r = p / q$. A real number that is not rational is called `irrational`.



## Theorem

**THEOREM**: FERMAT'S LAST THEOREM The equation $x^n + y^n = z^n$ has no solutions in integers x, y, and z with $xyz \neq 0$ whenever $n$ is an integer with $n > 2$.



## References

[1] Kenneth H. Rosen . Discrete Mathematics and Its Applications . 8Edition
