# Chapter 5 Syntax-Directed Translation

[TOC]



## Syntax-Directed Definitions

A `syntax-directed definition (SDD)` is a context-free grammar together with attributes and rules. Attributes are associated with grammar symbols and rules are associated with productions.

### Inherited and Synthesized Attributes

Two kinds of attributes for nonterminals:

1. A `synthesized attribute` for a nonterminal $A$ at a parse-tree node $N$ is defined by a semantic rule associated with the production at $N$.
2. An `inherited attribute` for a nonterminal $B$ at a parse-tree node $N$ is defined by a semantic rule associated with the production at the parent of $N$.

### Evaluating an SDD at the Nodes of a Parse Tree

A parse tree, showing the value(s) of its attribute(s) is called an `annotated parse tree`.



## Evaluation Orders for SDD's

### Dependency Graphs

A `dependency graph` depicts the flow of information among the attribute instances in a particular parse tree:

- For each parse-tee node, say a node labeled by grammar symbol $X$, the dependency graph has a node for each attribute associated with $X$.
- Suppose that a semantic rule associated with a production $p$ defines the value of synthesized attribute $A.b$ in terms of the value of $X.c$ (the rule may define $A.b$ in terms of other attributes in addition to $X.c$). Then, the dependency graph has an edge from $X.c$ to $A.b$. More precisely, at every node $N$ labeled $A$ where production $p$ is applied, create an edge to attribute $b$ at $N$, from the attribute $c$ at the child of $N$ corresponding to this instance of the symbol $X$ in the body of the production.
- Suppose that a semantic rule associated with a production $p$ defines the value of inherited attribute $B.c$ in terms of the value of $X.a$. Then, the dependency graph has an edge from $X.a$ to $B.$. For each node $N$ labeled $B$ that corresponds to an occurrence of this $B$ in the body of production $p$, create an edge to attribute $c$ at $N$ from the attribute $a$ at the node $M$ that corresponds to this occurrence of $X$. Note that $M$ could be either the parent or a sibling of $N$.

### S-Attributed Definitions

The two classes introduced in this section can be implemented efficiently in connection with top-down or bottom-up parsing:

1. An SDD is `S-attributed` if every attribute is synthesized.
2. `L-attributed definitions`, each attribute must be either:
   - Synthesized, or
   - Inherited, but with the rules limited as follows. Suppose that there is a production $A \rightarrow X_1 X_2 \cdots X_n$, and that there is an inherited attribute $Xi.a$ computed by a rule associated with this production. Then the rule may use only:
     1. Inherited attributes associated with the head $A$.
     2. Either inherited or synthesized attributes associated with the occurrences of symbols $X_1, X_2, \cdots, X_{i-1}$ located to the left of $X_i$.
     3. Inherited or synthesized attributes associated with this occurrence of $X_i$ itself, but only in such a way that there are no cycles in a dependency graph formed by the attributes of this $X_i$.

### Semantic Rules with Controlled Side Effects

We shall control side effects in SDD's in one of the following ways:

- Permit incidental side effects that do not constrain attribute evaluation.
- Constrain the allowable evaluation orders, so that the same translation is produced for any allowable order.



## Applications of Syntax-Directed Translation

### Construction of Syntax Trees

Syntax tree:

- If the node is a leaf, an additional field holds the lexical value for the leaf. A constructor function $Leaf(op, val)$ creates a leaf object. Alternatively, if nodes are viewed as records, then $Leaf$ returns a pointer to a new record for a leaf.
- If the node is an interior node, there are as many additional fields as the node has children in the syntax tree. A constructor function `Node` takes two or more arguments: $Node(op, c_1, c_2, ..., c_k)$ creates an object with first field $op$ and $k$ additional fields for the $k$ children $c_1, ..., c_k$.

![5_11](res/5_11.png)



## Syntax-Directed Translation Schemes

A `syntax-directed translation scheme (SDT)` is a context free grammar with program fragments embedded within production bodies. The program fragments are called `semantic actions` and can appear at any position within a production body. By convention, we place curly braces around actions; if braces are needed as grammar symbols, then we quote them. 

### SDT's With Actions Inside Productions

If we have a production $B \rightarrow X \{a\} Y$, the action $a$ is done after we have recognized $X$ (if $X$ is a terminal) or all the terminals derived from $X$ (if $X$ is a nonterminal). More precisely:

- If the parse is bottom-up, then we perform action $a$ as soon as this occurrence of $X$ appears on the top of the parsing stack.
- If the parse is top-down, we perform $a$ just before we attempt to expand this occurrence of $Y$ (if $Y$ a nonterminal) or check for $Y$ on the input (if $Y$ is a terminal).

Any SDT can be implemented as follows:

1. Ignoring the actions, parse the input and produce a parse tree as a result.
2. Then, examine each interior node $N$, say one for production $A \rightarrow \alpha$. Add additional children to $N$ for the actions in $\alpha$, so the childre of $N$ from left to right have exactly the symbols and actions of $\alpha$.
3. Perform a preorder traversal of the tree, and as soon as a node labeled by an action is visited, perform that action.

### SDT's for L-Attributed Definitions

The rules for turning an L-attributed SDD into an SDT are as follows:

1. Embed the actio that computes the inherited attributes for a nonterminal $A$ immediately before that occurrence of $A$ in the body of teh production. If several inherited attributes for $A$ depend on one another in any acyclic fashion, order the evaluation of attributes so that those needed first are computed first.
2. Place the actions that compute a synthesized attribute for the head of a production at the end of the body of that production.



## Implementing L-Attributed SDD's

The following methods do translation by traversing a parse tree:

1. `Build the parse tree and annotate`.
2. `Build the parse tree, add actions, and execute the actions in preorder.`
3. `Use a recursive-descent parser` with one function for each nonterminal.
4. `Generate code on the fly`, using a recursive-descent parser.
5. `Implement an SDT in conjunction with an LL-parser`.
6. `Implement an SDT in conjunction with an LR-parser`.  

### Translation During Recursive-Descent Parsing

A recursive-descent parser has a function $A$ for each nonterminal $A$. We can extend the parser into a translator as follows:

1. The arguments of function $A$ are the inherited attributes of nonterminal $A$.
2. The return-value of function $A$ is the collection of synthesized attributes of nonterminal $A$.

In the body of function $A$, we need to both parse and handle attributes:

1. Decide upon the production used to expand $A$.
2. Check that each terminal appears on the input when it is required.
3. Preserve, in local variables, the values of all attributes needed to compute inherited attributes for nonterminals in the body or synthesized attributes for the head nonterminal.
4. Call functions corresponding to nonterminals in the body of the selected production, providing them with the proper arguments.

### On-The-Fly Code Generation

In common cases such as our running code-generation example, we can instead incrementally generate pieces of the code into an array or output file by executing actions in an SDT. The elements we need to make this technique work are:

1. There is, for one or more nonterminals, a `main` attribute.
2. The main attributes are synthesized.
3. The rules that evaluate the main attribute(s) ensure that
   - The main attribute is the concatenation of main attributes of nanterminals appearing in the body of the production involved, perhaps with other elements that not main attributes, such as the string `label` or the values of labels $L1$ and $L2$.
   - The main attributes of nontherminals appear in the rule in the same order as the nonterminals themselves appear in the production body.

### L-Attributed SDD's and LL Parsing

We use the following two principles to manage attributes on the stack:

- The inherited attributes of a nonterminal $A$ are placed in the stack record that represents that nonterminal. The code to evaluate these attributes will usually be represented by an action-record immediately above the stack record for $A$; in fact, the conversion of L-attributed SDD's to SDT's ensures that the action-record will be immediately above $A$.
- The synthesized attributes for a nonterminal $A$ are placed in a separate synthesize-record that is immediately below the record for $A$ on the stack.

The principle that makes all this copying of attributes work is:

- All copying takes place among the records that are created during one expansion of one nonterminal. Thus, each of these records knows how far below it on the stack each other record is, and can write values into the records below safely.

