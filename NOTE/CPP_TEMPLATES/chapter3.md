# Chapter3 Class Templates

<!-- vim-markdown-toc GFM -->

* [3.1 Implementation of Class Template Stack](#31-implementation-of-class-template-stack)
    - [3.1.1 Declaration of Class Templates](#311-declaration-of-class-templates)
    - [3.1.2 Implementation of Member Functions](#312-implementation-of-member-functions)
* [3.2 Use of Class Template Stack](#32-use-of-class-template-stack)
* [3.3 Specializations of Class Templates](#33-specializations-of-class-templates)

<!-- vim-markdown-toc -->



## 3.1 Implementation of Class Template Stack

### 3.1.1 Declaration of Class Templates

```c++
template<typename T>
class Stack{
    Stack(Stack<T> const&);
    ~Stack();
    Stack<T> operator=(Stack<T> const &);
};
```

### 3.1.2 Implementation of Member Functions



## 3.2 Use of Class Template Stack

To use an object of a class template, you must specify the template arguments explicitly.

Template arguments may be any type:

1. The only requirement is that any operation that is called is possible according to this type.
2. Note that you have to put whitespace between the two closing template brackets.



## 3.3 Specializations of Class Templates

You can specialize a class template for certain template arguments. Similar to the overloading of function templates, specializing class templates allows you to optimize implementations for certain types or to fix a misbehavior of certain types for an instantiation of the class template.

```c++
template<>
class Stack<std::string> {
    ...
}
```

warning:

1. if you specialize a class template, you must also specialize all member functions.
2. it does demonstrate that the implementation of a specialization might look very different from the implementation of the primary template.



## 3.4 Partial Specialization

Class templates can be partially specialized. You can specify special implemetations for particular circumstances, but some template parameters must still be defined by the user.

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



## 3.5 Default Template Arguments

For class templates you can also define default values for template parameters. These values are called `default template arguments`. They may even refer to previous template parameters.

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



## 3.6 Summary

- A class template is class that is implemented with one or more type parameters left open.
- To use a class template, you pass the open types as template arguments. The class template is then instantiated (and compiled) for these types.
- For class templates, only those member functions that are called are instantiated.
- You can specialize class templates for certain types.
- You can partially specialize class templates for certain types.
- You can define default values for class template parameters. These may refer to previous template parameters.

