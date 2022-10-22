# Chapter5 技巧性基础知识


<!-- vim-markdown-toc GFM -->

* [5.1关键字typename](#51关键字typename)
* [5.2使用`this->`](#52使用this-)
* [5.3成员模板](#53成员模板)
* [5.4 模板的模板参数](#54-模板的模板参数)
* [5.5 零初始化](#55-零初始化)
* [5.6 使用字符串作为函数模板的实参](#56-使用字符串作为函数模板的实参)
* [5.7 小结](#57-小结)

<!-- vim-markdown-toc -->



## 5.1关键字typename

在C++标准化过程中，引入关键字`typename`是为了说明：模板内部的标识符可以是一个类型（而不只是类class），例：

```c++
template <typename T>
class MyClass{
    typename T::SubType *ptr;
}
```

在这个程序中，第2个typename被用来说明：SubType是定义于类T内部的一种类型。因此，ptr是一个指向`T::SubType`类型的指针。

如果不使用typename，SubType就会被认为是一个静态成员，那么它应该是一个具体变量或对象，于是表达式`T::Subtype* ptr`会被看作是类T的静态成员SubType和ptr的乘积。

**注意：通常当某个依赖于模板参数的名称是一个类型时，就应该使用typename明确的标识**

```c++
template <int N>
void printBitset(std::bitset<N> const& bs)
{
    std::cout << bs.template to_string<char, char_traits<char>, allocator<char> >();
}
```

只有当该前面存在依赖于模板参数的对象时，我们才需要在模板内部使用`.template`标记（和类似的诸如`->template`的标记），而且这些标记也只能在模板中才能使用。



## 5.2使用`this->`

对于那些在基类中声明，并且依赖于模板参数的符号（函数或者变量等），你应该在它们前面使用`this->`或者`Base<T>::`：

```c++
template <typename T>
class Derived : public Base<T> {...}
```

如果希望完全避免不确定性，你可以（使用诸如`this->`和`Base<T>::`等）限定（模板中）所有成员的访问。因为C++标准规定非依赖型名称不会在依赖型基类中进行查找（原因：非依赖名称的查找是在模板的定义时而非实例化时，这个时候依赖基类的定义也是不完全的。加上`this->`时就把名称变成了依赖的，于是名称查找就推迟了实例化时，这时基类已完全，所以可以去基类查找）。



## 5.3成员模板

类成员也可以是模板。嵌套类和成员函数都可以作为模板。

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

**注意1：模板赋值运算符并没有取代缺省赋值运算符。对于相同类型Stack之间的赋值，仍然会调用缺省赋值运算符，所以需要两个版本的operator=。**

**注意2：对于类模板而言，只有那些被调用的成员函数才会被实例化。**



## 5.4 模板的模板参数

把类模板作为模板参数是很有用的，我们称之为“模板的模板参数”。借助“模板的模板参数”，可以实现只指定容器的类型而不需要指定所含元素的类型：

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



## 5.5 零初始化

任何未被初始化的局部变量都具有一个`不确定（undefined）`值，为避免这种情况，需要显式初始化：

```c++
template <typename T>
void foo()
{
    T x = T();
}
```



## 5.6 使用字符串作为函数模板的实参

对于非引用类型的参数，在实参演绎的过程中，会出现数组到指针（array-to-pointer）的类型转换（这种转换通常也被称为decay，普通的函数调用也经常遇见数组退化为指针的情况，属于C语言的内容）。

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

decay问题的解决方法：

- 使用非引用参数，取代引用参数（可能会导致无用的拷贝）。
- 进行重载，编写接收引用参数和非引用参数的两个重载函数（可能会导致二义性）。
- 对具体类型进行重载。
- 重载数组类型

```c++
template <typename T, int N, int M>
T const* max(T const (&a)[N], T const (&b)[M])
{
    return a < b ? b : a;
}
```

- 强制要求应用程序程序员使用显式类型转换。



## 5.7 小结

- 如果要访问依赖于模板参数的类型名称，应该在类型名称前添加关键字typename。
- 嵌套类和成员函数也可以是模板。
- 赋值运算符的模板版本并没有取代缺省运算符。
- 类模板也可以作为模板参数，我们称之为模板的模板参数。
- 模板的模板实参必须精确地匹配，匹配时并不会考虑“模板的模板实参”的缺省模板实参（例如`std::deque`的allocator）。
- 通过显式调用缺省构造函数，可以确保模板的变量和成员都已经用一个缺省值完成初始化，这种方法对内建类型的变量和成员也适用。
- 对于字符串，在实参演绎过程中，当且仅当参数不是引用时，才会出现数组到指针（array-to-pointer）的类型转换（称为decay）。

