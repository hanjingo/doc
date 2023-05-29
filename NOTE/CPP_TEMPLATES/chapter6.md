# Chapter6 Using Template in Practice

<!-- vim-markdown-toc GFM -->

* [6.1 The Inclusion Model](#61-the-inclusion-model)
    - [6.1.1 Linker Errors](#611-linker-errors)
    - [6.1.2 Templates in Header Files](#612-templates-in-header-files)
* [6.2 Explicit Instantiation](#62-explicit-instantiation)
    - [6.2.1 Example of Explicit Instantiation](#621-example-of-explicit-instantiation)
    - [6.2.2 Combining the Inclusion Model and Explicit Instantiation](#622-combining-the-inclusion-model-and-explicit-instantiation)
* [6.3 The Separation Model](#63-the-separation-model)
    - [6.3.1 The Keyword export](#631-the-keyword-export)
    - [6.3.2 Limitations of the Separation Model](#632-limitations-of-the-separation-model)
    - [6.3.3 Preparing for the Separation Model](#633-preparing-for-the-separation-model)
* [6.4 Templates and inline](#64-templates-and-inline)
* [6.5 Precompiled Headers](#65-precompiled-headers)
* [6.6 Debugging Templates](#66-debugging-templates)
    - [6.6.1 Decoding the Error Novel](#661-decoding-the-error-novel)
    - [6.6.2 Shallow Instantiation](#662-shallow-instantiation)
    - [6.6.3 Long Symbols](#663-long-symbols)
    - [6.6.4 Tracers](#664-tracers)
    - [6.6.5 Oracles](#665-oracles)
    - [6.6.6 Archetypes](#666-archetypes)
* [6.7 Afternotes](#67-afternotes)
* [6.8 Summary](#68-summary)

<!-- vim-markdown-toc -->



## 6.1 The Inclusion Model

### 6.1.1 Linker Errors

Most C and C++ programmers organize their nontemplate code largely as follows:

-Classes and other types are entirely placed in header files. Typically, this is a file with a `.hpp`(or `.H`, `.h`, `.hh`, `.hxx`)filename extension.
- For global variables and (noninline) functions, only a declaration is put in a header file, and the definition goes into a so-called dot-C file. Typically, this is a file with a `.cpp`(or `.C`, `.c`, `.cc`, or `.hxx`) filename extension.

### 6.1.2 Templates in Header Files

inclusion model: We include the definitions of a template in the header file that declares that template.



## 6.2 Explicit Instantiation

### 6.2.1 Example of Explicit Instantiation

```c++
template class Stack<int>;                      // 显式实例化类模板
template Stack<int>::Stack();                   // 显式实例化类模板的成员函数
template void PrintType<double>(double const&); // 显式实例化函数模板
```

### 6.2.2 Combining the Inclusion Model and Explicit Instantiation



## 6.3 The Separation Model

### 6.3.1 The Keyword export

In principle, it is quite simple to make use of the export facility: Define the template in just one file, and mark that definition and all its nondefining declarations with the keyword export.

However, note that the keyword export cannot be combined with inline and must always precede the keyword template.

### 6.3.2 Limitations of the Separation Model

### 6.3.3 Preparing for the Separation Model



## 6.4 Templates and inline

Both function templates and inline functions can be defined in multiple translation units. This is usually achieved by placing the definition in a header file that is included by multiple dot-C files.



## 6.5 Precompiled Headers

precompiled headers:



## 6.6 Debugging Templates

- In this section we deal mostly with the constraints that lead to compilation errors when violated, and we call these constraints `syntactic constraints`.
- The other kind of constraint we call `semantic constraints`, For example, we may require that there be a `<`operator defined on a template type parameter(which is a syntactic constraint), but usually we'll also require that the operator actually defines some sort of ordering on its domain(which is a semantic constraint).

### 6.6.1 Decoding the Error Novel

### 6.6.2 Shallow Instantiation

### 6.6.3 Long Symbols

Instantiated template code can result in very long symbols.

### 6.6.4 Tracers

### 6.6.5 Oracles

### 6.6.6 Archetypes



## 6.7 Afternotes

The organization of source code in header files and dot-C files is a practical consequence of various incarnations of the so-called one-definition rule or ODR.



## 6.8 Summary

- Templates challenge the classic compiler-plus-linker model. Therefore there are different approaches to organize template code: the inclusion model, explicit instantiation, and the separation model.
- Usually, you should use the inclusion model (that is, put all template code in header files).
- By separating template code into different header files for declarations and definitions, you can ore easily switch between the inclusion model and explicit instantiation.
- The C++ standard defines a separate compilation model for templates(using the keyword export). It is not yet widely available, however.
- Debugging code with templates can be challenging.
- Template instances may have very long names.
- To take advantage of precompiled headers, be sure to keep the same order for `#include` directives.



## Glossary

<div style="width: 50%; float:left;"></div>
<div style="width: 50%; float:left;"></div>
<div style="width: 50%; float:left;"></div>
<div style="width: 50%; float:left;"></div>
<div style="width: 50%; float:left;"></div>
<div style="width: 50%; float:left;"></div>
<div style="width: 50%; float:left;"></div>
<div style="width: 50%; float:left;"></div>
<div style="width: 50%; float:left;"></div>
