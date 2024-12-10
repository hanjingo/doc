# Chapter 2 A Simple Syntax-Directed Translator

[TOC]



## Introduction

`abstract syntax trees` or simply `syntax trees`, represent the hierarchical syntactic structure of the source program.



## Syntax Definition

### Definition of Grammars

A `context-free grammar` has four components:

1. A set of `terminal` symbols, sometimes referred to as "tokens". The terminals are the elementary symbols of the language defined by the grammar.
2. A set of `nonterminals`, sometimes called "syntactic variables". Each nonterminal represents a set of strings of terminals, in a manner we shall describe.
3. A set of `productions`, where each production consists of a nonterminal, called the `head` or `left side` of the production, an arrow, and a sequence of terminals and/or nonterminals, called the `body` or `right side` of teh production. The intuitive intent of a production is to specify one of the written forms of a construct; if the head nonterminal represents a construct, then the body represents a written form of the construct.
4. A designation of one of the nonterminals as the `start` symbol.

### Derivations

A grammar derives strings by beginning with the start symbol and repeatedly replacing a nonterminal by the body of a production for that nonterminal. The terminal strings that can be derived from the start symbol form the `language` defined by the grammar.

### Parse Trees

Formally, given a context-free grammar, a `parse tree` according to the grammar is a tree with the following properties:

1. The root is labeled by the start symbol.
2. Each leaf is labeled by a terminal or by $\epsilon$.
3. Each interior node is labeled by a nonterminal.
4. If $A$ is the nonterminal labeling some interior node and $X_1, X_2, ..., X_n$ are the labels of the children of that node from left to right, then there must be a production $A \rightarrow X_1X_2...X_n$. Here, $X_1, X_2, ..., X_n$ each stand for a symbol that is either a terminal or a nonterminal. As a special case, if $A \rightarrow \epsilon$ is a production, then a node labeled $A$ may have a single child labeled $\epsilon$.

### Ambiguity

A grammar can have more than one parse tree generating a given string of terminals. Such a grammar is said to be `ambiguous`.



## Syntax-Directed Translation

Syntax-directed translation is done by attaching rules or program fragments to productions in a grammar:

- `Attributes`. An `attribute` is any quantity associated with a programming construct.
- `(Syntax-directed) translation schemes`. A `translation scheme` is a notation for attaching program fragments to the productions of a grammar.`

### Postfix Notation

The `postfix notation` for an expression $E$ can be defined inductively as follows:

1. If $E$ is a variable or constant, then the postfix notation for $E$ is $E$ itself.
2. If $E$ is an expression of the form $E_1$ op $E_2$, where op is any binary operator, then the postfix notation for $E$ is $E_1'$ $E_2'$ op, where $E_1'$ and $E_2'$ are the postfix notations for $E_1$ and $E_2$, respectively.
3. If $E$ is a parenthesized expression of the form $(E_1)$, then the postfix notation for $E$ is the same as the postfix notation for $E_1$.

### Synthesized Attributes

An attribute is said to be `synthesized` if its value at a parse-tree node $N$ is determined from attribute values at the child of $N$ and at $N$ itself. Synthesized attributes have the desirable property that they can be evaluated during a single bottom-up traversal of a parse tree.

### 2.3.3 简单语法制导定义

简单语法制导定义：要得到代表产生式头部的非终结符号的翻译结果的字符串，只需要将产生式体中各非终结符号的翻译结果按照它们在非终结符号中的出现顺序连接起来，并在其中穿插一些附加的串即可。

### 2.3.4 树的遍历

### 2.3.5 翻译方案

动作在第一次访问一个节点时被执行，那么我们将这种🏪称为`前序遍历（preorder traversal）`。如果动作在我们最后离开一个节点前被执行，则称这种遍历为`后序遍历（postorder traversal）`。

### 2.3.6 2.3节的练习



## 2.4 语法分析

语法分析是决定如何用一个文法生成一个终结符号串的过程。大多数语法分析方法可以归为以下两类：

- 自顶向下（top-down）方法：构造过程从根节点开始，逐步向叶子节点方向进行。
- 自底向上（bottom-up）方法：构造过程从叶子节点开始，逐步构造出根节点。

### 2.4.1 自顶向下分析方法

在自顶向下地构造一颗语法分析树时，反复执行下面两个步骤：

1. 在标号为非终结符号$A$的节点$N$上，选择$A$的一个产生式，并为该产生式体中的各个符号构造出N的子节点。
2. 寻找下一个节点来构造子树，通常选择的是语法分析树最左边的尚未扩展的非终结符。

### 2.4.2 预测分析法

`递归下降分析方法（recursive-descent parsing）`是一种自顶向下的语法分析方法，它使用一组递归过程来处理输入。文法的每个非终结符都有一个相关联的过程。

`预测分析法（predictive parsing）`是递归下降分析方法的简单形式。在该分析法中，各个非终结符号对应的过程中的控制流可以由向前看符号无二义地确定。

### 2.4.3 何时使用$\epsilon$产生式

### 2.4.4 设计一个预测分析器

### 2.4.5 左递归

递归下降语法分析器有可能进入无限循环。当出现如下所示的“左递归”产生式时，分析器就会出现无限循环：

$$
expr \rightarrow expr + term
$$

### 2.4.6 2.4节的练习



## 2.5 简单表达式的翻译器

### 2.5.1 抽象语法和具体语法

`抽象语法树（abstract syntax tree）`：每个内部节点代表一个运算符，该节点的子节点代表这个运算符的运算分量。

### 2.5.2 调整翻译方案

### 2.5.3 非终结符号的过程

### 2.5.4 翻译器的简化

如果一个过程体中执行的最后一条语句是对该过程的递归调用，那么这个调用就称为是`尾递归的（tail recursive）`。

### 2.5.5 完整的程序



## 2.6 词法分析

构成一个词法单元的输入字符序列称为`词素（lexem）`。

### 2.6.1 剔除空白和注释

### 2.6.2 预读

### 2.6.3 常量

### 2.6.4 识别关键字和标识符

### 2.6.5 词法分析器

### 2.6.6 2.6节的练习



## 2.7 符号表

`符号表（symbol table）`是一种供编译器用于保存有关源程序构造的各种信息的数据结构。这些信息在编译器的分析阶段被逐步收集并放入符号表，它们在综合阶段用于生成目标代码。

### 2.7.1 为每个作用域设置一个符号表

### 2.7.2 符号表的使用



## 2.8 生成中间代码

### 2.8.1 两种中间表示形式

两种最重要的中间表示形式：

- 树型结构，包括语法分析树和（抽象）语法树。
- 线性表示形成，特别是“三地址代码”。

`静态检查（static check）`：编译器检查源程序是否遵循源语言的语法和语义规则。

### 2.8.2 语法树的构造

一个语句序列的表示方法如下：用一个叶子节点null表示一个空语句序列，用运算符seq表示一个语句序列。规则如下：
$$
stmts \rightarrow stmts_1\ stmt \{stmts.n = new\ Seq(stmts_1.n, stmt.n);\}
$$

### 2.8.3 静态检查

静态检查是指在编译过程中完成的各种一致性检查。这些检查不但可以确保一个程序被顺利地编译，而且还能再程序运行之前发现编程错误。静态检查包括：

- 语法检查：语法要求比文法中的要求的更多。
- 类型检查：一种语言的类型规则确保一个运算符或函数被应用到类型和数量都正确的运算分量上。

### 2.8.4 三地址码

### 2.8.5 2.8节的练习



## 2.9 总结

- 构造一个语法制导编译器要从源语言的文法开始。
- 在描述一个翻译器时，在程序构造中附加属性是非常有用的。
- 词法分析器从输入中逐个读取字符，并输出一个词法单元的流，其中词法单元由一个终结符号以及以属性值形式出现的附加信息组成。
- 语法分析要解决的问题是指出如何从一个文法的开始符号推导出一个给定的终结符号串。
- 使用被称为预测语法分析法的自顶向下（从语法分析树的根节点到叶子节点）方法可以手工建立高效的语法分析器。
- 语法制导翻译通过在文法中添加规则或程序片段来完成。
- 语法分析的结果是源代码的一种中间表示形式，称为中间代码。
- 符号表是存放有关标识符的信息的数据结构。

