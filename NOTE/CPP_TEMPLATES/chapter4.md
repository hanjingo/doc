# Chapter 4.Nontype Template Paramters



## 4.1 Nontype Class Template Parameters

```c++
template <typename T, int MAXSIZE=66>
class Stack{
    ...
}
```



## 4.2 Nontype Function Template Parameters

You can also define nontype parameters for function templates. For example, the following function template defines a group of functions for which a certain value can be added:

```c++
template <typename T, int VAL = 6>
T addValue(T const& x) {
    return x + VAL;
}
```



## 4.3 Restrictions for Nontype Template Parameters

Note that nontype template parameters carry some restrictions. In general, they may be constant integral values(including enumerations) or pointers to objects with external linkage.

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



## 4.4 Summary

- Templates can have template parameters that are values rather than types.
- You cannot use floating-point numbers, class-type objects, and objects with internal linkage(such as string literals) as arguments for nontype template parameters.



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
