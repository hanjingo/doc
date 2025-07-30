# 第19章 类型区分

[TOC]



对于一个模版参数，如果能够知道它究竟是内建类型，指针类型，class类型或者其他类型中的哪一种，将会是非常有用的。

## 19.1 辨别基本类型



## 19.2 辨别组合类型

组合类型是指一些构造自其他类型的类型。简单的组合类型包括：普通类型，指针类型，引用类型和数组类型。



## 19.3 辨别函数类型

分辨函数类型有2种常见的手段：

- 使用针对函数的特化语法：

```c++
template<typename R>
class Compoud<R()>{...} // 类似的一系列特化

template<typename R, typename P1>
class Compoud<R(P1, ...)>{...} // 类似的一系列特化
```

- 利用SFINAE原则：因为数组的元素不是为void值，引用或者函数（void, 引用在前面已经可以被正确的识别了）。

```c++
template<typename U> static char test(...);
template<typename U> static int test(U(*)[1]);
enum {Yes = sizeof(test<T>(0) == 1)};s
```

- 还有一些其它的，不常用的手法也可以解决。



## 19.4 运用重载解析辨别枚举类型

重载解析是一个过程，它会根据函数参数的类型，在多个同名函数中选择出一个合适的函数。利用从枚举类型到整型的隐式转型：它能够帮助我们分辨枚举类型。



## 19.5 辨别class类型

如果T是非基本类型，非指针，非引用，非成员函数指针时（前面已经识别），还能够被隐式的转换为整型，那么T就一定是枚举类型。

```c++
enum {
    Yes = IsFundaT<T>::No &&
        !CompoundT<T>::IsRefT &&
        !CompoundT<T>::IsPtrT && 
        !CompoundT<T>::IsPtrMemT &&
        sizeof(enum_check(ConsumeUDC<T>())) == 1
};
```


## 19.6 辨别所有类型的函数模版



## 19.7 本章后记

