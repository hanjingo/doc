[TOC]

# 第四章 智能指针

裸指针的缺点:

1. 裸指针的声明中并没有指出，裸指针指涉到的是单个对象还是一个数组。
2. 裸指针在声明中也没有提示在使用完指涉的对象以后，是否需要析构它。换言之，你从声明中看不出来指针是否拥有其指涉的对象。
3. 即使知道需要析构指针所指涉的对象，也不可能知道如何析构才是适当的。是应该使用delete运算符呢，还是别有它途。
4. 即使知道了应该使用delete运算符，参见理由1，还是会发生到底应该用单个对象形式("delete")还是数组形式("delete[]")的疑问。一旦用错，就会导致未定义的行为。
5. 即启用够确信，指针拥有其指涉的对象，并且也确知应该如何析构，要保证析构在所有代码路径上都仅执行一次（包括那些异常的路径）仍然困难重重。只要少在一条路径上执行，就会导致资源泄漏。而如果析构在一条路径上执行了多于一次，则会导致未定义的行为。
6. 没有什么正规的方式能检测出指针是否空悬(dangle),也就是说，它指涉的内存是否已经不再持有指针本应该指涉的对象。如果一个对象已经被析构了，而某些指针仍然指涉到它，就会产生空悬指针。

# 条款18: 使用std::unique_ptr管理具备专属所有权的资源
* `std::unique_ptr`是小巧，高速的，具备只移型别的智能指针，对托管资源实施专属所有权语义。
* 默认地，资源析构采用delete运算符来实现，但可以指定自定义删除器。有状态的删除器和采用函数指针实现的删除器会增加`std::unique_ptr`型别的对象尺寸。
* 将`std::unique_ptr`转换成`std::shared_ptr`是容易实现的。

例：

```c++
template<typename... Ts>
auto makeInvestment(Ts&&... params)
{
    auto delInvmt = [](Investment* pInvestment)
                    {
                        makeLogEntry(pInvestment); // 现在自定义析构函数位于makeInvestment内部了
                        delete pInvestment;
                    };
    std::unique_ptr<Investment, decltype(delInvmt)>
        pInv(nullptr, delInvmt);    // 同前
    if (...)
    {
        pInv.reset(new Stock(std::forward<Ts>(params)...));
    }
    else if (...)
    {
        pInv.reset(new Bond(std::forward<Ts>(params)...));
    }
    else if (...)
    {
        pInv.reset(new RealEstate(std::forward<Ts>(params)...));
    }
    return pInv;
}

auto delInvmt1 = [](Investment* pInvestment) // 使用无状态lambda表达式
                 {
                    makeLogEntry(PInvestment);
                    delete pInvestment;
                 };

template<typename... Ts>
std::unique_ptr<Investmet, decltype(delInvmt1)> // 与Investment*相同
makeInvestment(Ts&&... args);

void delInvmt2(Investment* pInvestment) // 使用函数
{                                       // 使用自定义析构器
    makeLogEntry(pInvestmenbt);         
    delete pInvestment;
}

template<typename... Ts>                // 返回值尺寸等于
std::unique_ptr<Investment,             // Investment*的尺寸
                void (*)(Investment*)>  // 加上至少函数指针的尺寸！
makeInvestment(Ts&&... params);

std::shared_ptr<Investment> sp =    // 将std::unique_ptr型别的对象转换为std::shared_ptr型别
    makeInvestment(arguments);
```



# 条款19: 使用`std::shared_ptr`管理具备共享所有权的资源
引用计数会带来一些性能影响：
- `std::shared_ptr`的尺寸是裸指针的两倍。
- 引用计数的内存必须动态分配
- 引用计数的递增和递减必须是原子操作

例：

```c++
auto loggingDel = [](Widget *pw)    // 自定义析构器
                  {
                    makeLogEntry(pw);
                    delete pw;
                  };

std::unique_ptr< // 析构器型别是智能指针型别的一部分
    Widget, decltype(loggingDel)
    > upw(new Widget, loggingDel);

std::shared_ptr<Widget> // 析构器型别不是智能指针型别的一部分
    spw(new Widget, loggingDel);
```

控制块的创建遵循了以下规则:
- `std::make_shared`总是创建一个控制块。
- 从具备专属所有权的指针(即`std::unique_ptr`或`std::auto_ptr`指针) 出发构造一个`std::shared_ptr`时，会创建一个控制块。
- 当`std::shared_ptr`构造函数使用裸指针作为实参来调用时，它会创建一个控制块。

从同一个裸指针出发来构造不止一个`std::shared_ptr`是**行不通的**，被指涉的对象将会有多重的控制块。例：

```c++
auto pw = new Widget; // pw是个裸指针
...
std::shared_ptr<Widget> spw1(pw, loggingDel); // 为*pw创建第一个控制块
...
std::shared_ptr<Widget> spw2(pw, loggingDel); // 为*pw创建第二个控制块
```

为了避免用户在`std::shared_ptr`指涉到该对象前就调用了引发`shared_from_this`的成员函数，继承自`std::enable_shared_from_this`的类通常会将其构造函数声明为private访问层级，并且只允许用户通过调用返回`std::shared_pte`的工厂函数来创建对象。例：

```c++
class Widget : public std::enable_shared_from_this<Widget> {
public:
    // 将实参完美转发给private构造函数的工厂函数
    template<typename... Ts>
    static std::shared_ptr<Widget> create(Ts&&... params);
    ...
    void process(); // 同前
    ...
private:
    ... // 构造函数
};
```



# 条款20: 对于类似`std::shared_ptr`但有可能空悬的指针使用`std::weak_ptr`
* 使用`std::weak_ptr`来代替可能空悬的`std::shared_ptr`。
* `std::weak_ptr`可能的用武之地包括缓存，观察者列表，以及避免`std::shared_ptr`指针环路

例：

```c++
auto spw = 
    std::make_shared<Widget>(); // spw构造完成后，指涉到Widget的引用计数设置为1
...
std::weak_ptr<Widget> wpw(spw) // wpw和spw指涉到同一个Widget。引用计数保持为1
...
spw = nullptr; // 引用计数变为0，Widget对象被析构。wpw空悬（expired）
```




# 条款21: 优先选用`std::make_unique`和`std::make_shared`,而非直接使用new
- 相比于直接使用new表达式，make系列函数消除了重复代码，改进了异常安全性，并且对于`std::make_shared`和`std::allocated_shared`而言，生成的目标代码会尺寸更小，速度更快。
- 不适于使用make系列函数的场景包括：
    1. 需要定制析构器
    2. 期望直接传递大括号初始物
- 对于`std::shared_ptr`,不建议使用make系列函数的额外场景包括:
    1. 自定义内存管理的类
    2. 内存紧张的系统，非常大的对象，以及存在比指涉到相同对象的`std::shared_ptr`生存期更久的`std::weak_ptr`

使用make系列函数消除了重复代码，例：

```c++
auto upw1(std::make_unique<Widget>()); // 使用make_unique，简洁
std::unique_ptr<Widget> upw2(new Widget); // 不使用make_unique，重复
auto spw1(std::make_shared<Widget>());
std::shared_ptr<Widget> spw2(new Widget);
```

使用make系列函数可以改进异常安全性，例：

```c++
void processWidget(std::shared_ptr<Widget> spw, int priority);
int computePriority();

processWidget(std::shared_ptr<Widget>(new Widget), computePriority()); // 潜在的资源泄漏风险

// 使用std::make_shared避免上述问题
processWidget(std::make_shared<Widget>(), computePriority()); // 不会发生潜在的资源泄漏风险
```

使用make系列函数有利于提升性能，例：

```c++
std::shared_ptr<Widget> spw(new Widget); // 引发2次内存分配

auto spw = std::make_shared<Widget>();   // 1次内存分配
```

创建一个自定义析构器的智能指针，例：

```c++
std::unique_ptr<Widget, decltype(widgetDeleter)>
    upw(new Widget, widgetDeleter);

std::shared_ptr<Widget> spw(new Widget, widgetDeleter);
```




# 条款22: 使用Pimpl习惯用法时，将特殊成员函数的定义放到实现文件中
- Pimpl惯用法通过降低类的客户和类实现者之间的依赖性，减少了构建遍数。
- 对于采用`std::unique_ptr`来实现的pImple指针，须在类的头文件中声明特种成员函数，但在实现文件中实现他们。即使默认函数实现有着正确行为，也必须这样做。
- 上述建议仅适用于`std::unique_ptr`,但不适用`std::shared_ptr`。

pimpl（pointer to implementation，指涉到实现的指针）：把某类的数据成员用一个指涉到某实现类（或结构体）的指针替代，然后把原来在主类中的数据成员放置到实现类中，并通过指针间接访问这些数据成员。例：

- c++98方式：

```c++
class Widget {
public:
    Widget();
    ~Widget();  // 必要的析构函数
    ...

private:
    struct Impl; // 声明实现结构体以及指涉到它的指针
    Impl *pImpl;
};

#include "widget.h"
#include "gadget.h"
#include <string>
#include <vector>

struct Widget::Impl { // Widget::Impl的实现，包括此前在Widget中的数据成员
    std::string name;
    std::vector<double> data;
    Gadget g1, g2, g3;
};

Widget::Widget() // 为本Widget对象分配数据成员所需内存
: pImpl(new Impl)
{}

Widget::~Widget() // 为Widget对象析构数据成员
{ delete pImpl; }
```

- c++11方式

```c++
class Widget {
public:
    Widget();
    ...
    Widget(const Widget& rhs);
    Widget& operator=(const Widget& rhs);

private:
    struct Impl;
    std::shared_ptr<Impl> pImpl; // 使用智能指针
};

#include "widget.h"
#include "gadget.h"
#include <string>
#include <vector>

struct Widget::Impl {};

Widget::~Widget() = delete;

Widget::Widget()
: pImpl(std::make_unique<Impl>(*rhs.pImpl)) // 复制构造函数
{}

Widget& Widget::operator=(const Widget& rhs) // 复制赋值运算符
{
    *pImpl = *rhs.pImpl;
    return *this;
}
```
