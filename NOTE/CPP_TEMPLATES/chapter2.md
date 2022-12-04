# Chapter2 Function Templates


<!-- vim-markdown-toc GFM -->

* [2.1 A First Look at Function Templates](#21-a-first-look-at-function-templates)
    - [2.1.1 Defining the Template](#211-defining-the-template)
    - [2.1.2 Using the Template](#212-using-the-template)
* [2.2 Argument Deduction](#22-argument-deduction)
* [2.3 Template Parameters](#23-template-parameters)
* [2.4 Overloading Function Templates](#24-overloading-function-templates)

<!-- vim-markdown-toc -->



## 2.1 A First Look at Function Templates

Function templates provide a functional behavior that can be called for different types.

### 2.1.1 Defining the Template

```c++
template<typename T>
inline T const& max(T const& a, T const& b)
{
    return a < b ? b : a;
}
```

### 2.1.2 Using the Template

1. Without instantiation, the template code itself is checked for correct syntax. Syntax errors are discovered, such as missing semicolons.

2. At he time of instantiation, the template code is checked to ensure that all calls are valid. Invalid calls are discovered, such as unsupported function calls.



## 2.2 Argument Deduction



## 2.3 Template Parameters

Function templates have two kinds of parameters:

1. Template parameters, which are declared in angle brackets before the function template name:

```c++
template<typename T>
```

2. Call parameters, which are declared in parentheses after the function template name:

```c++
max(T const& a, T const& b)
```

specify the template argument list explicitly:

1. 

```c++
template <typename T1, typename T2, typename RT>
inline RT max(T1 const& a, T2 const& b);
max<int, double, double>(4, 4, 2);
```



## 2.4 Overloading Function Templates


