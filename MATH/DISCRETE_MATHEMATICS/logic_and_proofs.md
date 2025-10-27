# Logic and Proofs

[TOC]

## Introduction

This note summarizes core concepts in propositional logic, predicate logic, and common proof techniques used in discrete mathematics. It collects definitions of logical connectives and quantifiers, standard equivalences and inference rules, types of proofs (direct, contrapositive, contradiction, induction, proof by cases), and short examples to illustrate the methods.

## Propositional logic — connectives and truth

- Proposition: a declarative statement that is true or false (but not both).
- Negation: $\neg p$ is "not $p$"; it has the opposite truth value of $p$.
- Conjunction: $p\land q$ is "$p$ and $q$"; true iff both $p$ and $q$ are true.
- Disjunction: $p\lor q$ is "$p$ or $q$" (inclusive); true iff at least one of $p,q$ is true.
- Exclusive-or: $p\oplus q$ is true iff exactly one of $p,q$ is true.
- Conditional: $p\rightarrow q$ is "if $p$ then $q"; false only when $p$ is true and $q$ is false.
- Biconditional: $p\leftrightarrow q$ is "$p$ iff $q$"; true when $p$ and $q$ have the same truth value.

Truth tables enumerate all truth-value combinations and are the basic tool to verify equivalences and compute compound propositions.

## Logical equivalence and common identities

- Logical equivalence: $p\equiv q$ means $p\leftrightarrow q$ is a tautology.
- De Morgan's laws: $\neg(p\land q)\equiv\neg p\lor\neg q$ and $\neg(p\lor q)\equiv\neg p\land\neg q$.
- Distribution, associativity, commutativity, and double negation are standard algebraic rules for logical formulas.
- Contrapositive: $p\rightarrow q$ is equivalent to $\neg q\rightarrow\neg p$ (useful in proofs).

Inference rules (examples): Modus ponens: from $p$ and $p\rightarrow q$ infer $q$. Modus tollens: from $\neg q$ and $p\rightarrow q$ infer $\neg p$.

## Predicates and quantifiers

- Predicate: a propositional function $P(x)$ depending on variable(s).
- Universal quantifier: $\forall x\,P(x)$ means "$P(x)$ holds for all $x$ in the domain." A single counterexample disproves a universal claim.
- Existential quantifier: $\exists x\,P(x)$ means "there exists $x$ in the domain with $P(x)$ true."

Negation of quantified statements: $\neg(\forall x\,P(x))\equiv\exists x\,\neg P(x)$ and $\neg(\exists x\,P(x))\equiv\forall x\,\neg P(x)$.

Order of quantifiers matters: $\forall x\exists y\,Q(x,y)$ is generally not equivalent to $\exists y\forall x\,Q(x,y)$.

## Arguments, validity, and proof structure

- An argument is a sequence of premises and a conclusion. An argument is valid if whenever all premises are true, the conclusion must be true.
- A proof is a sequence of logical deductions from axioms or premises that establishes a conclusion.

Common proof styles:
- Direct proof: assume hypotheses and derive the conclusion by legal steps.
- Proof by contrapositive: to prove $p\rightarrow q$, show $\neg q\rightarrow\neg p$.
- Proof by contradiction: assume the negation of the desired conclusion and derive a contradiction.
- Proof by cases: split into exhaustive cases and prove the statement in each case.
- Existence proofs: constructive (exhibit an example) or nonconstructive (use logic or counting arguments to show existence).
- Uniqueness proofs: show existence and that any two satisfying objects must be equal.

Template for a typical induction proof (see Induction notes for more): base case, inductive hypothesis, inductive step, conclude by induction.

## Examples (short)

- Parity: prove that the sum of two even integers is even. Direct proof: let $m=2k$, $n=2\ell$, then $m+n=2(k+\ell)$.

- Irrationality of $\sqrt2$ (classical contradiction): assume $\sqrt2=p/q$ in lowest terms, derive that both $p$ and $q$ are even, contradicting lowest terms.

- Proof by contrapositive: to show "if $n^2$ is even then $n$ is even", prove contrapositive: if $n$ is odd then $n^2$ is odd.

## Useful proof techniques and tips

- Always state clearly what you assume and what you must prove.
- For quantifiers, specify the domain of discourse.
- When using induction, check base cases carefully (sometimes more than one base may be needed).
- Use counterexamples to disprove universal statements or purported equivalences.

## Common definitions used in examples

- Even/odd: $n$ is even if $\exists k\in\mathbb{Z}$ with $n=2k$; odd if $\exists k\in\mathbb{Z}$ with $n=2k+1$.
- Rational/irrational: real $r$ is rational if $\exists p,q\in\mathbb{Z}$, $q\neq0$, with $r=p/q$; otherwise irrational.

## References

[1] Kenneth H. Rosen. Discrete Mathematics and Its Applications. 8th Edition.

