# Chapter5 Tricky Basics

[TOC]



The keyword `typename` was introduced during the standardization of C++ to clarify that an identifier inside a template is a type. Consider the following example:

```c++
template <typename T>
class MyClass{
    typename T::SubType *ptr;
    ...
};
```

Here, the second `typename` is used to clarify that `SubType` is a type defined within class  `T`. Thus, `ptr` is a pointer to the type `T::SubType`.

Without `typename`, `SubType` would be considered a static member. Thus it would be a concrete variable or object As a result, the expression 

`T::SubType *ptr` 

would be a multiplication of the static `SubType` member of class `T` with `ptr`.

A very similar problem was discovered after the introduction of `typename`. Consider the following example using the standard `bitset` type:

```c++
template <int N>
void printBitset(std::bitset<N> const& bs)
{
    std::cout << bs.template to_string<char, char_traits<char>, allocator<char> >();
}
```

In conclusion, the `.template` notation (and similar notations such as `->template`) should be used only inside templates and only if they follow something that depends on a template parameter.

For class templates with base classes, using a name `x` by itself is not always equivalent to `this->x`, even though a member `x` is inherited.

```c++
template <typename T>
class Derived : public Base<T> {...}
```

Class members can also be templates. This is possible for both nested classes and member functions.

```c++
template <typename T>
class Stack {
    template<typename T2>
    Stack<T>& operator=(Stack<T2> const& );
};

template <typename T>
template <typename T2>
Stack<T>& Stack<T>::operator=(Stack<T2> const& op2) {
    ...
}
```

Template template parameters examples:

```c++
template <typename T, 
    template<typeanme ELEM, 
    typename ALLOC = std::allocator<ELEM>> // 模板的模板实参必须精确匹配，匹配时并不会考虑“模板的模板实参”的缺省模板实参，必须显式指出这个ALLOC！
    class CONT> // 模板的模板参数只能使用关键字class
class Stack{
    public:
        Stack(){} // 必须定义，因为声明变量s时构造函数必须被调用
        Stack(Stack<T, CONT> const &); // 不必定义，“只有那些被调用的类成员会被实例化”
        ~Stack(){} // 必须定义，因为声明变量s时析构函数必须被调用
        Stack<T, CONT> operator=(Stack<T, CONT> const &); // 不必定义，同上
    private:
        CONT<T> elems;
};
```

For funcamental types such as `int`, `double`, or pointer types, there is no default constructor that initializes them with a useful default value. Instead, any noninitialized local variable has a undefined value:

```c++
template <typename T>
void foo()
{
    T x = T();
}

```

The explanation for this behavior is that during argument deduction array-to-pointer conversion(often called decay) occurs only if the parameter does not have a reference type. This is demonstrated by the following program:

```c++
template <typename T>
inline T const& max(T const& a, T const& b) {
    return a < b ? b : a;
}

std::string s;
::max("apple", "peach");  // OK；相同类型的实参 char[5]
::max("apple", "tomato"); // ERROR；不同类型的实参 char[5], char[6]
::max("apple", s);        // ERROR；不同类型的实参 char[5], std::string

```

- use nonreferences instead of references (however, this can lead to unnecessary copying)
- overload using both reference and nonreference parameters(however, this might lead to ambiguities)
- overload with concrete types(such as `std::string`)
- overload with array types types, for example:
    ```c++
    template<typename T, int N, int M>
    T const* max(T const (&a)[N], T const (&b)[M])
    {
        return a < b ? b : a;
    } 
    ```
- force application programmers to use explicit conversions



## Summary

- To access a type name that depends on a template parameter, you have to qualify the name with a leading typename.
- Nested classes and member functions can also be templates. One application is the ability to implement generic operations with internal type conversions. However, type checking still occurs.
- Template versions of assignment operators don't replace default assignment operators.
- You can also use class templates as template parameters, as so-called template template parameters.
- Template arguments must match exactly. Default template arguments of template template arguments are ignored.
- By explicitly calling a default constructor, you can make sure that variables and members of templates are initialized by a default value even if they are instantiated with a build in type.
- For string literals there is an array-to-pointer conversion during argument deduction if and only if the parameter is not a reference.



## Glossary

<div style="width: 50%; float:left;">tricky `/'trɪki/` 棘手的，狡猾的，巧妙的</div>
<div style="width: 50%; float:left;">relevant `/'reləvənt/` 相关的，切题的，中肯的，有意义的，目的明确的</div>
<div style="width: 50%; float:left;">thumb `/θʌm/` 拇指，翻阅，（搭便车）手势</div>
<div style="width: 50%; float:left;">deque `/'dek/` （计算机）双端队列</div>
<div style="width: 50%; float:left;">insertion `/ɪn'sɜːʃn/` 插入</div>
<div style="width: 50%; float:left;">compilation `/ˌkɒmpɪ'leɪʃn/` 汇集，编写，编辑</div>
<div style="width: 50%; float:left;">gist `/dʒɪst/` 要点，主旨</div>
<div style="width: 50%; float:left;">conform `/kən'fɔːm/` 使一致，遵从</div>
<div style="width: 50%; float:left;">peach `/piːtʃ/` 桃子，桃树，桃红色</div>
<div style="width: 50%; float:left;">stumbled `/'stʌmbl/` 绊倒，蹒跚，犯错误，无意中发现</div>
<div style="width: 50%; float:left;">phenomenon `/fə'nɒmɪnən/` 现象，奇人，奇事</div>
<div style="width: 50%; float:left;">corrigendum `/ˌkɒrɪ'dʒendəm/` 勘误表，（应改正的）错误</div>
<div style="width: 50%; float:left;">concrete `/'kɒŋkriːt/` 具体的，实质性的，混凝土，凝结，结合</div>
<div style="width: 50%; float:left;">explicit `/ɪk'splɪsɪt/` （计算机）显式的，明确的，清晰的</div>
<div style="width: 50%; float:left;">lexicographical `/leksɪkə'græfɪkl/` 词典编篡的</div>