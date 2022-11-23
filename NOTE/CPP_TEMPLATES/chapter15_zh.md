# 第15章 trait和policy类

<!-- vim-markdown-toc GFM -->

* [15.1 一个实例：累加一个序列](#151-一个实例累加一个序列)
    - [15.1.1 fixed traits](#1511-fixed-traits)
    - [15.1.2 value trait](#1512-value-trait)
    - [15.1.3 参数化trait](#1513-参数化trait)
    - [15.1.4 policy和policy类](#1514-policy和policy类)
    - [15.1.5 trait和policy区别在何处](#1515-trait和policy区别在何处)
    - [15.1.6 成员模版和模版的模版参数](#1516-成员模版和模版的模版参数)
    - [15.1.7 组合多个policie和/或trait](#1517-组合多个policie和或trait)
    - [15.1.8 运用普通的迭代器进行累积](#1518-运用普通的迭代器进行累积)
* [15.2 类型函数](#152-类型函数)
    - [15.2.1 确定元素的类型](#1521-确定元素的类型)
    - [15.2.2 确定class类型](#1522-确定class类型)
    - [15.2.3 引用和限定符](#1523-引用和限定符)
    - [15.2.4 promotion trait](#1524-promotion-trait)
* [15.3 policy trait](#153-policy-trait)
    - [15.3.1 只读的参数类型](#1531-只读的参数类型)
    - [15.3.2 拷贝，交换和移动](#1532-拷贝交换和移动)
* [15.4 本章后记](#154-本章后记)

<!-- vim-markdown-toc -->



Policy类和trait（或称为trait模版）是两种C++程序设计机制，它们有助于对某些额外参数的管理，这里的额外参数是指：在具有工业强度的设计中所出现的参数。

## 15.1 一个实例：累加一个序列

### 15.1.1 fixed traits

```c++
#ifndef ACCUM_HPP
#define ACCUM_HPP

#include "accumutraits2.hpp"

template<typename T>
inline 
typename AccumulationTraits<T>::Acct accum(T const* beg,
                                           T const* end)
{
    // 返回值的类型是一个元素类型的trait
    typedef typename AccumulationTraits<T>::Acct Acct;
    AccT total = AccT();
    while (beg != end) {
        total += *beg;
        ++beg;
    }
    return total;
}

#endif
```

### 15.1.2 value trait

### 15.1.3 参数化trait

### 15.1.4 policy和policy类

### 15.1.5 trait和policy区别在何处

- trait表述了模版参数的一些自然的额外属性。
- policy表述了范型函数和范型类的一些可配置香味。
- trait可以是fixed trait（也就是说，不需要通过模版参数进行传递的trait）。
- trait参数通常都具有很自然的缺省值。
- trait参数可以紧密依赖于一个或多个主参数。
- trait通常都是用trait模版来实现的。
- 如果不以模版参数的形式进行传递的话，policy class几乎不起作用。
- policy参数并不需要具有缺省值，而且通常都是显式指定这个参数。
- policy参数和属于同一个模版的其它模版参数通常都是正交的。
- policy class一般都包含了成员函数。
- policy既可以用普通类来实现，也可以用类模版来实现。

### 15.1.6 成员模版和模版的模版参数

### 15.1.7 组合多个policie和/或trait

trait和policy通常都不能完全代替多个模版参数；然而，trait和policy确实可以减少模版参数的个数，并把个数限制在可控制的范围内。

### 15.1.8 运用普通的迭代器进行累积



## 15.2 类型函数

类型函数（type function）：一个接收某些类型实参，并且生成一个类型作为函数的返回结果。

sizeof是一个非常有用的，内建的类型函数，它返回一个描述给定类型实参大小（以字节为单位）的敞亮。

### 15.2.1 确定元素的类型

### 15.2.2 确定class类型

SFINAE原则（substitution-failure-is-not-error，替换失败并非错误）。

### 15.2.3 引用和限定符

### 15.2.4 promotion trait



## 15.3 policy trait

### 15.3.1 只读的参数类型

```c++
template<typename T>
class RParam{
    public:
        typedef typename IfThenElse<IsClassT<T>::No,
                T,
                T const&>::Result Type;
};
```

### 15.3.2 拷贝，交换和移动



## 15.4 本章后记


