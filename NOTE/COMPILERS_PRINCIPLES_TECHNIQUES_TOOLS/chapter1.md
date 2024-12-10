# Introduction

[TOC]



## The Structure of a Compiler

there are two parts to this mapping:

- analysis part: breaks up the source program into constituent pieces and imposes a grammatical structure on them. It then uses this structure to create an intermediate representation of the source program.

- synthesis part: Construct the desired target program from the intermediate representation and the information in the symbol table.


### Lexical Analysis

The first phase of a compiler is called *lexical analysis* or *scanning*. The lexical analyzer reads the stream of characters making up the source program and groups the characters into meaningful sequences called *lexemes*.

### Syntax Analysis

The second phase of the compiler is *syntax analysis* or *parsing*. The parser uses the first components of the tokens produced by the lexical analyzer to create a tree-like intermediate representation that depicts the grammatical structure of the token stream.

### Semantic Analysis

The *semantic analyzer* uses the syntax tree and the information in the symbol table to check the source program for semantic consistency with the language definition. It also gathers type information and saves it in either the syntax tree or the symbol table, for subsequent use during intermediate-code generation.

### Code Generation

The code generator takes as input an intermediate representation of the source program and maps it into the target language.

### Symbol-Table Management

The symbol table is a data structure containing a record for each variable name, with fields for the attributes of the name.

### The Grouping of Phases into Passes

we can produce compilers for different source languages for one target machine by combining different front ends with the back end for that target machine.

### Compiler-Construction Tools

Some commonly used compiler-construction tools include:

1. *Parser generators* that automatically produce syntax analyzers from a grammatical description of a programming language.

2. *Scanner generators* that produce lexical analyzers from a regular-expression description of the tokens of a language.

3. *Syntax-directed translation engines* that produce collections of routines for walking a parse tree and generating intermediate code.

4. *Code-generator generators* that produce a code generator from a collection of rules for translating each operation of the intermediate language into the machine language for a target machine.

5. *Data_flow analysis engines* that facilitate the gathering of information about how values are transmitted from one part of a program to each other part. Data-flow analysis is a key part of code optimization.

6. *Compiler-construction toolkits* that provide an integrated set of routines for constructing various phases of a compiler.



## The Science of Building a Compiler

### The Science of Code Optimization

Compiler optimizations must meet the following design objectives:

- The optimization must be correct, that is, preserve the meaning of the compiled program.

- The optimization must improve the performance of many programs.

- The compilation time must be kept reasonable.

- The engineering effort required must be manageable.




## Applications of Compiler Technology

### Implementation of High-Level Programming Languages

A high-level programming language defines a programming abstraction: the programmer expresses an algorithm using the language, and the compiler must translate that program to the target language.

The key ideas behind object orientation are:

1. Data abstraction and,
2. Inheritance of properties.

### Optimizations for Computer Architectures

Almost all high-performance systems take advantage of the same two basic techniques:

- parallelism,
- memory hierarchies.

### Software Productivity Tools

- Type Checking

  Type checking is an effective and well-established technique to catch inconsistencies in programs.

- Bounds Checking

  It is easier to make mistakes when programming in a lower-level language than a higher-level one.

- Memory-Management Tools

  Automatic memory management obliterates all memory-management errors (e.g., "memory leaks"), which are a major source of problems in C and C++ programs.



## Programming Language Basics

### The Static/Dynamic Distinction

A policy that allows the compiler to decide an issue, then we say that language uses a `static policy` or that the issue can be decided at `compile time`.

A policy that only allows a decision to be made when we execute the program is said to be a `dynamic policy` or to require a decision at `run time`.

### Environments and States

The association of names with locations in memory (the `store`) and then with values can be described by two mappings that change as the program runs:

1. The `environment` is a mapping from names to locations in the store.
2. The `state` is a mapping from locations in store to their values.

### Static Scope and Block Structure

In C, the syntax of blocks is given by:

1. One type of statement is a block. Blocks can appear anywhere that other types of statements, such as assignment statements, can appear.
2. A block is a sequence of declarations followed by a sequence of statements, all surrounded by braces.

### Dynamic Scope

`dynamic scope`: a use of a name $x$ refers to the declaration of $x$ in the most recently called, not-yet-terminated, procedure with such a declaration.

### Parameter Passing Mechanisms

**Call-by-Value**

In `call-by-value`, the actual parameter is evaluated (if it is an expression) or copied (if it is a variable). The value is placed in the location belonging to the corresponding formal parameter of the called procedure.

**Call-by-Reference**

In `call-by-reference`, the address of the actual parameter is passed to the callee as the value of the corresponding formal parameter. Uses of the formal parameter in the code of the callee are implemented by following this pointer to the location indicated by the caller. Changes to the formal parameter thus appear as changes to the actual parameter.

**Call-by-Name**

It requires that the callee execute as if the actual parameter were substituted literally for the formal parameter in the code of the callee, as if the formal parameter were a macro standing for the actual parameter (with renaming of local names in the called procedure, to keep them distinct).

