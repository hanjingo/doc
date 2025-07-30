# Chapter4 非类型模板参数

[TOC]



## 4.1 非类型的类模板参数

```c++
template <typename T, int MAXSIZE=66>
class Stack{
    ...
}
```



## 4.2 非类型的函数模板参数

```c++
template <typename T, int VAL = 6>
T addValue(T const& x) {
    return x + VAL;
}
```



## 4.3 非类型模板参数的限制

非类型模板参数是有限制的，通常而言，它们可以是常整数（包括枚举值）或者指向外部链接对象的指针。

```c++
// 错误！浮点数不能作为非类型模板参数
template <double VAT>
double f(double d)
{
    return d * VAT;
}

// 错误！类对象不能作为非类型模板参数
template <std::string name>
class MyClass {
    ...
};

// 错误！字符串文字不能作为非类型模板参数
template <char const* name>
class MyClass {
    ...
};
```

**注意1：浮点数，类对象（class-type）不允许作为非类型模板参数。**

**注意2：由于字符串文字是内部链接对象，所以不能使用它们作为模板实参。**

**注意3：不能使用全局指针作为模板参数。**



## 4.4 小结

- 模板可以具有值模板参数，而不仅仅是类型模板参数。
- 对于非类型模板参数，不能使用浮点数，class类型的对象和内部链接对象作为实参。
