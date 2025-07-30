# Chapter 3 Class Templates

[TOC]



Declaration of Class Templates:

```c++
template<typename T>
class Stack{
    Stack(Stack<T> const&);
    ~Stack();
    Stack<T> operator=(Stack<T> const &);
};
```


To use an object of a class template, you must specify the template arguments explicitly.

Template arguments may be any type:

1. The only requirement is that any operation that is called is possible according to this type.
2. Note that you have to put whitespace between the two closing template brackets.

You can specialize a class template for certain template arguments. Similar to the overloading of function templates, specializing class templates allows you to optimize implementations for certain types or to fix a misbehavior of certain types for an instantiation of the class template.

```c++
template<>
class Stack<std::string> {
    ...
}
```

warning:

1. if you specialize a class template, you must also specialize all member functions.
2. it does demonstrate that the implementation of specialization might look very different from the implementation of the primary template.

Class templates can be partially specialized. You can specify special implementations for particular circumstances, but some template parameters must still be defined by the user:

```c++
template <typename T>
class MyClass<T, int> {
    ...
};

template<typename T>
class MyClass<T, T> {
    ...
};

template <typename T>
class MyClass<T*, T*> {
    ...
};

MyClass<int, int> m;
MyClass<int*, int*> m;
```

For class templates you can also define default values for template parameters. These values are called `default template arguments`. They may even refer to previous template parameters:

```c++
tempalte <typename T, typename CONT = std::vector<T> >
class Stack {
    private:
        CONT elems;
    ...
};

template <typename T, typename CONT>
void Stack<T, CONT>::push(T const& elem)
{
    elems.push_back(elem);
}

Stack<double, std::deque<double> > s;
s.push(1.1);
```



## Summary

- A class template is class that is implemented with one or more type parameters left open.
- To use a class template, you pass the open types as template arguments. The class template is then instantiated (and compiled) for these types.
- For class templates, only those member functions that are called are instantiated.
- You can specialize class templates for certain types.
- You can partially specialize class templates for certain types.
- You can define default values for class template parameters. These may refer to previous template parameters.



## Glossary

<div style="width: 50%; float:left;">concentrate `/'kɒnsntreɪt/` 专心，集中，浓缩</div>
<div style="width: 50%; float:left;">assignment `/ə'saɪnmənt/` 分配（任务，内存），委托，指定</div>
<div style="width: 50%; float:left;">statement `/'steɪtmənt/` 语句，声明，陈述</div>
<div style="width: 50%; float:left;">qualification `/ˌkwɒlɪfɪ'keɪʃn/` 资格，资历，限制</div>
<div style="width: 50%; float:left;">instantiated `/ɪns'tænʃɪeɪt/` 实例化，举例</div>
<div style="width: 50%; float:left;">refrain `/rɪ'freɪn/` 避免，抑制，克制，重复</div>
<div style="width: 50%; float:left;">occurrence `/ə'kʌrəns/` 发生，出现，事件</div>