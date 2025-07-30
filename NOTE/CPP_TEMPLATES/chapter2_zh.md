# chapter2 函数模板

[TOC]



## 2.1 初探函数模板

函数模板提供了一种函数行为，该函数行为可以用多种不同的类型进行调用。

### 2.1.1 定义模板

```c++
template<typename T>
inline T const& max(T const& a, T const& b)
{
    return a < b ? b : a;
}
```

class 与typename的区别：

- 从语义上来讲，class和typename是等价的；但是，class这种用法往往会给人误导（这里的class并不意味着只有类才能被用来替代T，事实上基本类型也可以）；
- 对于引入类型参数的这种用法，不能用关键字struct代替typename。

### 2.1.2 使用模板

`模板实例化（instantiation）` 用具体类型代替模板参数的过程：

1. 实例化之前，先检查模板代码本身，查看语法是否正确；
2. 在实例化期间，检查模板代码，查看是否所有的调用都有效。



## 2.2 实参的演绎（deduction）



## 2.3 模板参数

函数模板有两种类型的参数：

1. 模板参数：位于函数模板名称的前面，在一对尖括号内部进行声明

    ```c++
    template<typename T>
    ```

2. 调用参数：位于函数模板名称之后，在一堆圆括号内部进行声明

    ```c++
    max(T const& a, T const& b)
    ```

显式指定函数模板实参的方法：

1. 显式指定所有函数模板实参

```c++
template <typename T1, typename T2, typename RT>
inline RT max(T1 const& a, T2 const& b);
max<int, double, double>(4, 4, 2);
```

2. 显式指定"最后一个不能被隐式演绎的模板实参之前的偶有实参类型"，让演绎过程推导出其余的实参

```c++
template<typename RT, typename T1, typename T2>
inline RT max(T1 const& a, T2 const& b);
max<double>(4, 4.2);
```

`函数模板的实参演绎` 当我们为某些实参调用一个函数模板时，模板参数可以由我们所传递的实参来决定，它使用可以像调用普通函数那样调用函数模板。

**注意1：在实参演绎时，不允许任何的自动类型转换，每个T都必须正确匹配。**
**注意2：模板的实参演绎并不适合返回类型（可以把演绎看成是重载解析的一部分--重载解析是一个不依赖于返回类型选择的过程，唯一的例外就是转型操作符成员的返回类型）**


## 2.4 重载函数模板

函数模板也可以被重载，相同的函数名可以具有不同的函数定义；一个非模板函数可以和一个同名的函数模板同时存在，而且该函数模板还可以被实例化为这个非模板函数。

```c++
inline int const& max(int const& a, int const& b)
{
    return a < b ? b : a;
}

template <typename T>
inline T const& max(T const& a, T const& b)
{
    return a < b ? b : a;
}

template <typename T>
inline T const& max(T const& a, T const& b, T const& c)
{
    return ::max(::max(a, b), c);
}
```

**注意1：模板绝不允许自动类型转换（在实参演绎时，不允许任何的自动类型转换，每个T都必须正确匹配）**
**注意2：函数的所有重载版本的声明都应该位于该函数被调用的位置之前**



## 2.5 小结

- 模板函数为不同的模板实参定义了一个函数家族。
- 当你传递模板实参的时候，可以根据实参的类型来对函数模板进行实例化。
- 你可以显式指定模板参数。
- 你可以冲在函数模板。
- 当重载函数模板的时候，把你的改变限制在：显式地指定模板参数。
- 一定要让函数模板的所有重载版本的声明都位于它们被调用的位置之前。
