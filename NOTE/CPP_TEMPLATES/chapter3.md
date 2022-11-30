# Chapter3 Class Templates

<!-- vim-markdown-toc GFM -->

* [3.1 Implementation of Class Template Stack](#31-implementation-of-class-template-stack)
    - [3.1.1 Declaration of Class Templates](#311-declaration-of-class-templates)
    - [3.1.2 Implementation of Member Functions](#312-implementation-of-member-functions)
* [3.2 Use of Class Template Stack](#32-use-of-class-template-stack)
* [3.3 Specializations of Class Templates](#33-specializations-of-class-templates)

<!-- vim-markdown-toc -->



## 3.1 Implementation of Class Template Stack

### 3.1.1 Declaration of Class Templates

```c++
template<typename T>
class Stack{
    Stack(Stack<T> const&);
    ~Stack();
    Stack<T> operator=(Stack<T> const &);
};
```

### 3.1.2 Implementation of Member Functions



## 3.2 Use of Class Template Stack

To use an object of a class template, you must specify the template arguments explicitly.

Template arguments may be any type:

1. The only requirement is that any operation that is called is possible according to this type.
2. Note that you have to put whitespace between the two closing template brackets.



## 3.3 Specializations of Class Templates

You can specialize a class template for certain template arguments. Similar to the overloading of function templates, specializing class templates allows you to optimize implementations for certain types or to fix a misbehavior of certain types for an instantiation of the class template.

warning:

1. if you specialize a class template, you must also specialize all member functions.
