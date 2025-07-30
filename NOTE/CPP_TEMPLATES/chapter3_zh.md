# Chapter3 类模板

[TOC]



## 3.1 类模板Stack的实现

```c++
template<typename T>
class Stack{
    Stack(Stack<T> const&);
    ~Stack();
    Stack<T> operator=(Stack<T> const &);
};
```

### 3.1.1 类模板的声明

### 3.1.2 成员函数的实现



## 3.2 类模板Stack的使用

为了使用类模板对象，必须显式指定模板实参。

只有那些被调用的成员函数，才会产生这些函数的实例化代码。对于类模板，成员函数只有在被使用的时候才会实例化。这样做的好处：

1. 可以节省空间和时间；
2. 对于"未能提供所有成员函数中所有操作的"类型，可以使用该类型来实例化类模板，只要对那些“未能提供某些操作的”成员函数，模板内部不使用就可以。

模板实参可以是任何类型，但是需要注意以下几点：

1. 该类型必须提供被调用的所有操作；
2. 需要在两个靠在一起的模板尖括号（>）之间留一个空格，否则，编译器会认为是在使用`operator>>`，这将导致语法错误
    ```c++
    Stack<Stack<int> > ss;
    ```



## 3.3 类模板的特化

和函数模板的重载类似，通过特化类模板，可以优化基于某种特定类型的实现，或者克服某种特定类型在实例化模板时所出现的不足。

```c++
template<>
class Stack<std::string> {
    ...
}
```

**注意1：特化的实现可以和基本类模板（prinmary template）的实现完全不同**

**注意2：如果要特化一个类模板，必须要特化该类模板的所有成员函数。**



## 3.4 局部特化

类模板可以被局部特化，可以在特定的环境下指定类模板的特定实现，并且要求某些模板参数仍必须由用户来定义。

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

**注意1：如果有多个局部特化同等程度地匹配某个声明，则该声明具有二义性；为了消除二义性，需要额外提供一个指向相同类型指针的特化。**

**注意2：在C++11之前，只有类模板才能有缺省的模板实参，但是C++11之后，函数模板也能有缺省的实参。**



## 3.5 缺省模板实参

可以为模板参数定义缺省值，这些值被称为缺省模板实参；而且，它们还可以引用之前的模板参数。

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



## 3.6 小结

- 类模板是具有如下性质的类：在类的实现中，可以有一个或多个类型还没有被指定。
- 为了使用类模板，你可以传入某个具体类型作为模板实参，然后编译起将会基于该类型来实例化类模板。
- 对于类模板而言，只有那些被调用的成员函数才会被实例化。
- 可以用某种特定类型特化类模板。
- 可以用某种特定类型局部特化类模板。
- 可以为类模板的参数定义缺省值，这些值还可以引用之前的模板参数。

