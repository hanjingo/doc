# CHAPTER 1 The Foundations: Logic and Proofs

[TOC]



## Propositional Logic

A `proposition` is a declarative sentence (that is, a sentence that declares a fact) that is either true or false, but not both.

**Definition** Let $p$ be a proposition. The negation of $p$, denoted by $\neg{p}$ (also denoted by $\over{p}$), is the statement "It is not the case that $p$".

> The proposition $\neg p$ is read "not $p$". The truth value of the negation of $p$, $\neg p$, is the opposite of the truth value of $p$.

**Definition** Let $p$ and $q$ be propositions. The `conjunction` of $p$ and $q$, denoted by $p \and q$, is the proposition "p and q". The conjunction $p \and q$ is true when both $p$ and $q$​ are true and is false otherwise.

**Definition** Let $p$ and $q$ be propositions. The `disjunction` of $p$ and $q$, denoted by $p \or q$, is the proposition "p or q". The disjunction $p \or q$ is false when both $p$ and $q$ are false and is true otherwise.

**Definition** Let $p$ and $q$ be propositions. The `exclusive` or of $p$ and $q$, denoted by $p \oplus q$ (or $p$ XOR $q$), is the proposition that is true when exactly one of $p$ and $q$ is true and is false otherwise.

**Definition** Let $p$ and $q$ be propositions. The `conditional statement` $p \rightarrow q$ is the proposition "if p, then q". The conditional statement $p \rightarrow q$ is false when $p$ is true and $q$ is false, and true otherwise. In the conditional statement $p \rightarrow q$, $p$ is called the hypothesis (or `antecedent` or `premise`) and $q$​ is called the `conclusion` (or `consequence`).

The proposition $q \rightarrow p$ is called the **converse** of $p \rightarrow q$. The **contrapositive** of $p \rightarrow q$ is the proposition $\neg q \rightarrow \neg p$. The proposition $\neg p \rightarrow \neg q$ is called the **inverse** of $p \rightarrow q$. We will see that of these three conditional statements formed from $p \rightarrow q$, only the contrapositive always has the same truth value as $p \rightarrow q$​.

**Definition** Let $p$ and $q$ be propositions. The `biconditional statement` $p \leftrightarrow q$ is the proposition "$p$ if and only if $q$". The biconditional statement $p \leftrightarrow q$ is true when $p$ and $q$ have the same truth values, and is false otherwise. Biconditional statements are also called `bi-implications`.

TABLE. Precedence of Logical Operators:

| Operator                           | Precedence |
| ---------------------------------- | ---------- |
| $\neg$                             | 1          |
| $\and$<br>$\or$                    | 2<br>3     |
| $\rightarrow$<br>$\leftrightarrow$ | 4<br>5     |

A **bit** is a symbol with two possible values, namely, 0(zero) and 1(one).

**Definition** A bit string is a sequence of zero more bits. The length of this string is the number of bits in the string.



## Applications of Propositional Logic

System specifications should be **consistent**, that is, they should not contain conflicting requirements that could be used to derive a contradiction. When specifications are not consistent, there would be no way to develop a system that satisfies all specifications.



## Vocabulary

proposition `/ˌprɒpəˈzɪʃn/` n. 论点；主张; 建议；提案; 命题

imprecise  `/ˌɪmprɪ'saɪs/` adj. 不精确的

ambiguous `/æm'bɪɡjuəs/` adj. 模棱两可的；含糊不清的

inference  `/ˈɪnf(ə)rəns/` n. 推理；推论；推断；结论

coaster `/'kəʊstə(r)/` n. 杯垫；小托盘；惯性运转装置；沿海航行船

contradiction  `/ˌkɒntrəˈdɪkʃn/` n. 矛盾；反驳；否认；不一致

pirate `/'paɪrət/` n. 海盗；盗版者；v. 盗版；抢劫；剽窃

inscribe `/ɪnˈskraɪb/` vt. 题写；题献；铭记；雕

inscription n. `/ɪn'skrɪpʃ(ə)n/` (作者)题词, 献词