# 7 Templates and Generic Programming

[toc]

## 条款41 了解隐式接口和编译期多态

通常显式接口由函数的签名式（函数名称，参数类型，返回类型）构成；例：

```c++
class Widget {
public:
    Widget();
    virtual ~Widget();
    virtual std::size_t size() const;
    virtual void normalize();
    void swap(Widget& other);
};
```

隐式接口由有效表达式（valid expressions）组成；例：

```c++
template<typename T>
void doProcessing(T& w)
{
    ...
}
```

总结：

- classes和templates都支持接口（interfaces）和多态（polymorphism）；
- 对classes而言接口是显式的（explicit），以函数签名为中心；多态则是通过virtual函数发生于运行期；
- 对template参数而言，接口是隐式的（implicit），奠基于有效表达式；多态则是通过template具现化和函数重载解析（function overloading resolution）发生于编译期；


## 条款42 了解typename的双重意义

声明template参数时，关键字class或typename意义完全相同；例：

```c++
template<class T> class Widget;    // 等价
template<typename T> class Widget; // 等价
```

一般性规则：任何时候当你想要在template中指涉一个嵌套从属类型名称，就必须在紧邻它的前一个位置放上关键字typename；例：

```c++
template<typename C>                // 允许使用typename或class
void f(const C& container,          // C并不是嵌套从属类型名称，不需要使用typename
       typename C::iterator iter);  // C::iterator是个嵌套从属类型名称，必须使用typename
```

typename不可出现在base classes list内的嵌套从属类型名称之前，也不可在member initialization list（成员初始化列表）中作为base class修饰符；例：

```c++
template<typename T>
class Derived: public Base<T>::Nested { // base class list中不允许typename
public: 
    explicit Derived(int x) : Base<T>::Nested(x) // 成员初始化列表不允许typename
    {
        typename Base<T>::Nested temp; // 这里可以
        ...
    }
}
```

总结：

- 声明template参数时，前缀关键字class和typename可互换；
- 请使用关键字typename标识嵌套从属类型名称，但不得在base class lists（基类列）或member initialization list（成员初值列）内以它作为base class修饰符；


## 条款43 学习处理模板化基类内的名称

处理模板化基类内名称的三种方法：

```c++
class MsgInfo { ... };
template<typename Company>
class MsgSender {
public:
    void sendClear(const MsgInfo& info) { ... }
}
```

1. 在base class函数调用动作之前加上“this->”；

```c++
template<typename Company>
class LoggingMsgSender: public MsgSender<Company> {
public:
    ...
    void sendClearMsg(const MsgInfo& info)
    {
        this->sendClear(info);
    }
};
```

2. 使用using声明式；

```c++
template<typename Company>
class LoggingMsgSender: public MsgSender<Company> {
public:
    using MsgSender<Company>::sendClear; // 告诉编译器，请它假设sendClear位于base class内
    void sendClearMsg(cosnt MsgInfo& info)
    {
        sendClear(info);
    }
};
```

3. 明确指出被调用的函数位于base class内；

```c++
template<typename Company>
class LoggingMsgSender: public MsgSender<Company> {
public:
    void sendClearMsg(const MsgInfo& info)
    {
        MsgSender<Company>::sendClear(info); // 假设sendClear将被继承下来
    }
}
```

总结：

- 可在derived class templates内通过"this->"指涉base class templates内的成员名称，或借由一个明白写出的“base class资格修饰符”完成；


## 条款44 将与参数无关的代码抽离templates

使用非类型模板参数（non-type template parameters）会造成代码膨胀；例：

```c++
teplate<typename T, std::size_t n>
class SquareMatrix {
public:
    void invert();
};

SquareMatrix<double, 5> sm1;  // 实现一份invert
sm1.invert();

SquareMatrix<double, 10> sm2; // 再实现一份invert
sm2.invert();
```

1.以函数参数或class成员变量替换template参数，消除非类型模板参数带来的代码膨胀；例：

```c++
template<typename T>
class SquareMatrixBase {
protected:
    void invert(std::size_t matrixSize);
};
template<typename T, std::size_t n>
class SquareMatrix: private SquareMatrixBase<T> {
private:
    using SquareMatrixBase<T>::invert; // 避免遮盖SquareMatrixBase::invert
public:
    void insert() { this->invert(n); } // 制造一个inline调用，调用SquareMatrixBase::invert
};
```

2.直接在类中存储参数信息，消除非类型模板参数带来的代码膨胀；例：

```c++
template<typename T>
class SquareMatrixBase {
protected:
    SquareMatrixBase(std::size_t, T* pMem) : size(n), pData(pMem) {} // 存储矩阵大小和一个指针，指向矩阵数值
    void setDataPtr(T* ptr) { pData = ptr; } // 重新赋值给pData
private:
    std::size_t size; // 矩阵大小
    T* pData;         // 指向举证内容
};
template<typename T, std::size_t n>
class SquareMatrix: private SquareMatrixBase<T> {
public:
    SquareMatrix() : SquareMatrixBase<T>(n, 0), pData(new T(n * n)) // 将base class的数据指针设为null，为矩阵内容分配内存；
    { this->setDataPtr(pData.get()); }                              // 将指向该内存的指针存储起来，然后将它的一个副本交给base class；
private:
    boost::scoped_array<T> pData;
};
```

总结：

- Templates生成多个classes和多个函数，所以任何template代码都不该与某个造成膨胀的template阐述产生相依关系；
- 因非类型模板参数（non-type template parameters）而造成的代码膨胀，往往可以消除，做法是以函数参数或class成员变量替换template参数；
- 因类型参数（type parameters）而造成的代码膨胀，往往可降低，做法是让带有完全相同二进制表述（binary representations）的具现类型（instantiation types）共享实现码；


## 条款45 运用成员函数模板接受所有兼容类型

成员函数模板（member function templates）构造模板；例：

```c++
template<typename T>
class SmartPtr {
public:
    template<typename U>
    SmartPtr(const SmartPtr<U>& other) : heldPtr(other.get()) { ... } // 以other的heldPtr，初始化this的heldPtr
    T* get() const { return heldPtr; }
private:
    T* heldPtr; // 这个SmartPtr持有的内置（原始）指针
};
```

成员函数赋值操作；例：

```c++
template<class T>
class shared_ptr {
public:
    template<class Y>
    explicit shared_ptr(Y * p); // 构造，来自任何兼容的内置指针
    
    template<class Y>
    shared_ptr(shared_ptr<Y> const& r);

    template<class Y>
    explicit shared_ptr(weak_ptr<Y> const& r);

    template<class Y>
    explicit shared_ptr(auto_ptr<Y>& r);

    template<class Y>
    shared_ptr& operator=(shared_ptr<Y> const& r); // 赋值，来自任何兼容的shared_ptr或auto_ptr

    template<class Y>
    shared_ptr& operator=(auto_ptr<Y>& r);
}
```

总结：

- 请使用member function templates（成员函数模板）生成“可接受所有兼容类型”的函数；
- 如果你声明member templates用于“泛化copy构造”或“泛化assignment操作”，你还是需要声明正常的copy构造函数和copy assignment操作符；


## 条款46 需要类型转换时请为模板定义非成员函数

利用template class内的friend声明式可以指涉某个特定函数；例：

```c++
template<typename T> class Rational;

template<typename T>
const Rational<T doMultiply(const Rational<T>& lhs, const Rational<T>& rhs);

template<tyename T>
class Pational {
public:
    friend Rational<T> operator*(const Rational<T>& lhs, const Rational<T>& rhs)
    { return doMultiply(lhs, rhs); } // 令friend调用helper
};
```

总结：

- 当我们编写一个class template，而它所提供之“与此template相关的”函数支持“所有参数之隐式类型转换”时，请将那些函数定义为“class template 内部的friend函数”；


## 条款47 请使用traits classes表现类型信息

总结：

- Traits classes使得“类型相关信息”在编译期可用，它们以templates和“templates特化”完成实现；
- 整合重载技术（overloading）后，traits classes有可能在编译期对类型执行`if...else`测试；


## 条款48 认识template元编程

总结：

- Template metaprogramming（TMP，模版元编程）可将工作由运行期移往编译期，因而得以实现早期错误侦测和更高的执行效率；
- TMP可被用来生成“基于政策选择组合”（based on combinations of policy choices）的客户定制代码，也可用来避免生成对某些特殊类型并不适合的代码；