# 第12章 特化与重载


<!-- vim-markdown-toc GFM -->

* [12.1 当泛型代码不再适用的时候](#121-当泛型代码不再适用的时候)
    - [12.1.1 透明自定义](#1211-透明自定义)
    - [12.1.2 语义的透明性](#1212-语义的透明性)
* [12.2 重载函数模板](#122-重载函数模板)
    - [12.2.1 签名](#1221-签名)
    - [12.2.2 重载的函数模板的局部排序](#1222-重载的函数模板的局部排序)
    - [12.2.3 正式的排序原则](#1223-正式的排序原则)
    - [12.2.4 模板和非模板](#1224-模板和非模板)
* [12.3 显式特化](#123-显式特化)
    - [12.3.1 全局的类模板特化](#1231-全局的类模板特化)
    - [12.3.2 全局的函数模板特化](#1232-全局的函数模板特化)
    - [12.3.3 全局成员特化](#1233-全局成员特化)
* [12.4 局部的类模板特化](#124-局部的类模板特化)
* [12.5 本章后记](#125-本章后记)

<!-- vim-markdown-toc -->

## 12.1 当泛型代码不再适用的时候

### 12.1.1 透明自定义

C++模板提供了多种透明自定义函数模板和类模板的方法。对于函数模板而言，我们可以通过重载机制来实现这种方法。

### 12.1.2 语义的透明性



## 12.2 重载函数模板

两个同名的函数模板可以同时存在，还可以对它们进行实例化，使它们具有相同的参数类型。

### 12.2.1 签名

只要具有不同的签名，两个函数就可以在同一个程序中同时存在。例：

```c++
template<typename T1, typename T2>
void f1(T1, T2);

template<typename T1, typename T2>
void f1(T2, T1);

template<typename T>
long f2(T);

template<typename T>
char f2(T);
```

我们对函数的签名定义如下：

1. 非受限函数的名称（或者产生自函数模板的这类名称）。
2. 函数名称所属的类作用域或者名字空间作用域：如果函数名称是具有内部链接的，还包括该名称声明所在的翻译单元。
3. 函数的const, volatile或者const volatile限定符（前提是它是一个具有这类限定符的成员函数）。
4. 函数参数的类型（如果这个函数是产生自函数模板的，那么指的是模板参数被替换之前的类型）。
5. 如果这个函数是产生自函数模板，那么包括它的返回类型。
6. 如果这个函数是产生自函数模板，那么包括模板参数和模板实参。

### 12.2.2 重载的函数模板的局部排序

### 12.2.3 正式的排序原则

通过替换模板参数，我们将为不同模板虚构不同的实参类型（如果是转型函数模板，那么还包括返回类型）列表，流程如下：

1. 用唯一的“虚构”类型替换每个模板类型参数。
2. 用唯一的“虚构”类模板替换每个模板的模板参数。
3. 用唯一的适当类型的“虚构”值替换每个非类型参数。

### 12.2.4 模板和非模板

函数模板也可以和非模板函数同时重载。当其它的所有条件都是一样的时候，实际的函数调用将会优先选择非模板函数。



## 12.3 显式特化

### 12.3.1 全局的类模板特化

### 12.3.2 全局的函数模板特化

函数模板特化引入了重载和实参演绎这两个概念。

如果可以借助实参演绎（用实参类型来演绎声明中给出的参数类型）来确定模板的特殊化版本，那么全局特化就可以不声明显式的模板实参。

全局函数模板特化不能包含缺省的实参值。然而，对于基本（即要被特化的）模板所指定的任何缺省实参，显式特化版本都可以应用这些缺省实参值。

全局特化声明的声明对象并不是一个模板，因此对于非内联的全局函数模板特化而言，在同个程序中它的定义只能出现一次。然而，我们仍然必须确保：全局函数模板特化的声明必须紧跟在模板定义的后面，以避免试图使用一个由模板直接生成的函数。

### 12.3.3 全局成员特化

类模板的成员函数和普通的静态成员变量也可以被全局特化；实现特化的语法会要求给每个外围类模板加上`template<>`前缀。如果要对一个成员模板进行特化，也必须加上另一个`template<>`前缀。

```c++
template<>
class Outer<bool>::Inner<wchar_t>{
    public:
    	enum{count = 2};
};
```



## 12.4 局部的类模板特化

当进行匹配的时候，全局特化会优于局部特化。

局部特化声明的参数列表和实参列表的约束：

1. 局部特化的实参必须和基本模板的相应参数在种类上（可以是类型，非类型或者模板）是匹配的。
2. 局部特化的参数列表不能具有缺省实参；但局部特化仍然可以使用基本类模板的缺省实参。
3. 局部特化的非类型实参只能是非类型值，或者是普通的非类型模板参数；而不能是更复杂的依赖型表达式（例如：$2 \times N$，$N$是模板参数）。
4. 局部特化的模板实参列表不能和基本模板的参数里欸包完全等同（不考虑重新命名）。

```c++
template<typename T, int I = 3>
class S;           // 基本模板

template<typename T>
class S<int, T>;   // 错误；参数类型不匹配

template<typename T = int>
class S<T, 10>;    // 错误；不能具有缺省实参

template<int I>
class S<int, I*2>; // 错误；不能有非类型的表达式

template<typename U, int K>
class S<U, K>;     // 错误；局部特化和基本模板之间没有本质的区别
```

类模板局部特化的参数个数可以和基本模板不一样：既可以比基本模板多，也可以比基本模板少。



## 12.5 本章后记

