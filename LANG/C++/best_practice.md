# C++最佳实践


<!-- vim-markdown-toc GFM -->

* [Old C++](#old-c)
    - [1.尽量以const, enum, inline替换`#define`](#1尽量以const-enum-inline替换define)
    - [2.尽可能使用const](#2尽可能使用const)
    - [3.确定对象被使用前已先被初始化](#3确定对象被使用前已先被初始化)
    - [4.了解C++编译器的小动作](#4了解c编译器的小动作)
    - [5.正确定义构造函数](#5正确定义构造函数)
    - [6.正确定义析构函数](#6正确定义析构函数)
    - [7.正确定义operator=](#7正确定义operator)
    - [8.正确定义成员变量](#8正确定义成员变量)
    - [9.小心重载](#9小心重载)
    - [10.防止资源泄漏](#10防止资源泄漏)
    - [11.函数参数定义](#11函数参数定义)
    - [12.尽量避免类型转换](#12尽量避免类型转换)
    - [13.谨慎使用inline函数](#13谨慎使用inline函数)
    - [14.降低文件间的编译依赖关系](#14降低文件间的编译依赖关系)
    - [15.使用继承的一些注意点](#15使用继承的一些注意点)
    - [16.谨慎使用virtual函数](#16谨慎使用virtual函数)
    - [17.typename与class的区别](#17typename与class的区别)
    - [18.模版使用心得](#18模版使用心得)
    - [19.不要对类使用memcpy或memcmp操作](#19不要对类使用memcpy或memcmp操作)
* [New C++](#new-c)
    - [1.正确使用模版类型推导](#1正确使用模版类型推导)
    - [2.正确进行型别推导](#2正确进行型别推导)
    - [3.正确使用decltype](#3正确使用decltype)
    - [4.优先使用auto](#4优先使用auto)
    - [5.优先使用初始化列表](#5优先使用初始化列表)
    - [6.优先选用nullptr](#6优先选用nullptr)
    - [7.优先选用using而非typedef](#7优先选用using而非typedef)
    - [8.优先选用enum class](#8优先选用enum-class)
    - [9.优先选用delete](#9优先选用delete)
    - [10.优先使用override](#10优先使用override)
    - [11.优先选用const_iterator](#11优先选用const_iterator)
    - [12.只要函数不会发射异常就加上noexcept声明](#12只要函数不会发射异常就加上noexcept声明)
    - [13.尽可能使用constexpr](#13尽可能使用constexpr)
    - [14.正确使用三大智能指针](#14正确使用三大智能指针)
    - [15.优先使用make系列函数而非直接使用new](#15优先使用make系列函数而非直接使用new)
    - [16.正确使用万能引用和右值引用](#16正确使用万能引用和右值引用)
    - [17.正确使用std::move和std::forward](#17正确使用stdmove和stdforward)
    - [18.完美转发的失败场景](#18完美转发的失败场景)
    - [19.正确使用lambda](#19正确使用lambda)
    - [20.保证线程安全性](#20保证线程安全性)
* [STL](#stl)
    - [1.选择合适的算法](#1选择合适的算法)
    - [2.选择合适的容器](#2选择合适的容器)
    - [3.尽量使用empty函数判空而不是检查size()==0](#3尽量使用empty函数判空而不是检查size0)
    - [4.区间成员函数优先于与之对应的单元素成员函数](#4区间成员函数优先于与之对应的单元素成员函数)
    - [5.小心C++编译器的分析机制-尽可能地将代码解释为函数声明](#5小心c编译器的分析机制-尽可能地将代码解释为函数声明)
    - [6.如果容器中包含了通过new操作创建的指针，切记在容器对象析构前将指针delete掉](#6如果容器中包含了通过new操作创建的指针切记在容器对象析构前将指针delete掉)
    - [7.禁止创建包含auto_ptr的容器对象](#7禁止创建包含auto_ptr的容器对象)
    - [8.STL容器的线程安全性不够](#8stl容器的线程安全性不够)
    - [9.推荐使用vector和string而不是动态分配的数组](#9推荐使用vector和string而不是动态分配的数组)
    - [10.使用reserve来避免不必要的重新分配](#10使用reserve来避免不必要的重新分配)
    - [11.避免使用`vector<bool>`](#11避免使用vectorbool)
    - [12.包含指针的关联容器指定比较类型](#12包含指针的关联容器指定比较类型)
    - [13.禁止直接修改set或multiset中的键](#13禁止直接修改set或multiset中的键)
    - [14.当效率至关重要时，根据不同情况选择map::operator[]或map::insert](#14当效率至关重要时根据不同情况选择mapoperator或mapinsert)
    - [15.避免混用不同类型的迭代器，优先使用iterator而不是其它类型的迭代器](#15避免混用不同类型的迭代器优先使用iterator而不是其它类型的迭代器)
    - [16.对于逐个字符的输入考虑使用istreambuf_iterator](#16对于逐个字符的输入考虑使用istreambuf_iterator)
    - [17.尽量使用封装技术](#17尽量使用封装技术)
    - [18.使用erase-remove方法完全删除元素](#18使用erase-remove方法完全删除元素)
    - [19.使用函数对象而不是函数作为STL算法的参数](#19使用函数对象而不是函数作为stl算法的参数)
    - [20.容器的成员函数优先于同名的算法](#20容器的成员函数优先于同名的算法)
    - [21.确保容器中的对象拷贝正确而高效](#21确保容器中的对象拷贝正确而高效)
* [接口设计](#接口设计)
* [工具](#工具)
* [参考](#参考)

<!-- vim-markdown-toc -->

## Old C++

### 1.尽量以const, enum, inline替换`#define`

- 对于单纯常量，最好以const对象或enums替换`#define`；因为预处理的名称可能并为进入记号表(symbol table)，会给调试带来困难;

  ```c++
  #define ASPECT_RATIO 1.653 // 大写名称通常用于宏
  ```

  修改为：

  ```c++
  const double AspectRatio = 1.653;
  ```

- 对于形似函数的宏（macros），最好改用inline函数替换`#defines`；

- 对于`#ifndef ... #define ... #endif`的，可以使用`#pragma once`来代替；

[返回顶部](#C++最佳实践)



### 2.尽可能使用const

- const可被施加于任何作用域内的对象，函数参数，函数返回类型，成员函数；

- const的使用具有传播性，在一个地方使用，在其它地方也要使用；

- 不要强制转换const；

- 保证const成员函数的线程安全性，除非可以确信它们不会用在并发语境中；

  ```c++
  class Polynomial {
  public:
    using RootType = std::vector<double>;
    
    RootsType roots() const
    {
      std::locak_guard<std::mutex> g(m); // 加上互斥量
      if (!rootsAreValid) {
        ...
        rootsAreValid = true;
      }
      return rootVals;
    }	// 解除互斥量
    
  private:
    mutable std::mutex m;
    mutable bool rootsAreValid{ false };
    mutable RootsType rootVals{};
  };
  ```


[返回顶部](#C++最佳实践)



### 3.确定对象被使用前已先被初始化

- 在变量定义时立即进行初始化；

  ```c++
  int a; // 不推荐
  int a = 1; // 推荐
  char s[2] = {'a', 'b'}; // 推荐
  ```

- C++对象的成员变量的初始化动作发生在进入构造函数本体之前，C++不保证初始化内置类型对象；

[返回顶部](#C++最佳实践)



### 4.了解C++编译器的小动作

- C++编译器私自为class创建default constructor函数，copy constructor函数，copy assignment操作符，以及析构函数；

  ```c++
  class Empty {};
  ```

  编译器将上面自动转化为：

  ```c++
  class Empty {
  public:
    Empty() { ... }                 // default构造函数
    Empty(const Empty& rhs) { ... } // copy构造函数
    ~Empty() { ... }                // 析构函数
    Empty& operator=(const Empty& rhs) { ... } // copy assignment操作符
  };
  ```

- 如果不想使用编译器自动生成的函数，可以将它们声明为private并且不实现它们；

  ```c++
  class HomeForSale {
  public:
    ...
  private:
    ...
    HomeForSale(const HomeForSale&); // 只声明不实现
    HomeForSale& operator=(const HomeForSale&); // 只声明不实现
  }
  ```

- 避免隐式转换；

[返回顶部](#C++最佳实践)



### 5.正确定义构造函数

- 成员变量初始化的顺序要与类定义中声明的顺序始终保持一致；

- 构造对象时推荐使用成员初始化列表，这样可以避免一次赋值动作；

  ```c++
  class A {
  	string s1, s2;
  public:
    A():s1("hello"),s2("work"){};
  }
  ```

- **禁止在构造函数中调用虚拟函数**；

[返回顶部](#C++最佳实践)



### 6.正确定义析构函数

- 如果class带有任何virtual函数，最好给他一个virtual析构函数；

- 给基类一个virtual析构函数，删除派生类对象会销毁所有派生成员；

  ```c++
  class TimeKeeper {
  public:
    TimeKeeper();
    virtual ~TimeKeeper();
    ...
  };
  TimeKeeper* ptk = getTimeKeeper();
  delete ptk;
  ```

- **禁止在析构函数中抛出异常；**

- **禁止在析构函数中调用virtual函数；**

  由于基类构造函数的执行早于派生类构造函数，当基类构造函数执行时派生类的成员变量尚未初始化；

  ```c++
  class Transaction {
  public:
    Transaction()
    { init(); }
    virtual void logTransaction() const = 0;
  private:
    void init()
    {
    	logTransaction(); // 这里调用了virtual function，会报错
    }
  };
  ```

- 将基类析构函数设为公用且虚拟的或保护且非虚拟的；

[返回顶部](#C++最佳实践)



### 7.正确定义operator=

- 避免operator=的自我赋值

  自我赋值的情况：

  ```c++
  w = w; // 自我赋值
  a[i] = a[j]; // 当i==j时，自我赋值
  *px = *py; // 当px和py指向同一个对象时，自我赋值
  ```

  处理方法：

  ```c++
  // 比较安全
  Widget& Widget::operator=(const Widget& rhs)
  {
  	Widget temp(rhs); // 制作副本
    swap(temp);       // 交换数据
    return *this;
  }
  ```

- Copying函数应该确保复制对象内的所有成员变量及所有基类成员

  ```c++
  class PriorityCustomer : public Customer {
  public:
    PriorityCustomer(const PriorityCustomer& rhs);
    PriorityCustomer& operator=(const PriorityCustomer& rhs);
  private:
    int priority;
  };
  PriorityCustomer::PriorityCustomer(const PriorityCustomer& rhs)
    : Customer(rhs),
      priority(rhs.priority)
  {
    logCall("PriorityCustomer copy constructor");    
  }
  PriorityCustomer& PriorityCustomer::operator=(const PriorityCustomer& rhs)
  {
  	logCal("PriorityCustomer copy assignment operator");
    Customer::operator=(rhs);
    priority = rhs.priority;
    return *this;
  }
  ```

- 赋值操作必须返回一个指向操作符的左侧实参引用

  ```c++
  class Widget {
  public:
    Widget& operator=(const Widget& rhs) // 返回类型是个reference，指向当前对象
    {
    	return* this; // 返回左侧对象
    }
    Widget& operator+=(const Widget& rhs) // 适用于+=, -=, *=等等
    {
    	return *this;
    }
    Widget& operator=(int rhs)
    {
    	return *this;
    }
  };
  ```

- 禁止RAII对象被复制;

- 对底层资源使用`引用计数法(reference-count)`，抑制copying；

[返回顶部](#C++最佳实践)



### 8.正确定义成员变量

- 将成员变量声明为private，这可赋予客户访问数据的一致性，可细微划分访问控制，允诺约束条件获得保证，并提供class作者以充分的实现弹性；

- 尽量以非成员函数替换成员函数，这样做可以增加封装性，类弹性和扩充性；

  ```c++
  class WebBrowser {
  public:
      void clearEverything();
  }
  ```

  优化为：

  ```c++
  namespace WebBrowserStuff {
      class WebBrowser { ... };
      void clearBrowser(WebBrowser& wb);
  };
  ```

- 无论何时如果可以避免friend函数就该避免；

- 若所有参数皆需类型转换，最好采用非成员函数；

  ```c++
  class Rational {
      ...
  };
  const Rational operator*(const Rational& lhs,
                           const Rational& rhs)
  {
      return Rational(lhs.numerator() * rhs.numerator(),
                      lhs.denominator() * rhs.denominator());
  }
  Rational oneFourth(1, 4);
  Rational result;
  result = oneFourth * 2;
  result = 2 * oneFourth;
  ```

[返回顶部](#C++最佳实践)



### 9.小心重载

- 禁止重载`&&`, `||`或`,`

[返回顶部](#C++最佳实践)



### 10.防止资源泄漏

- 推荐自定义new和delete来替换编译器的operator new和operator delete；

- 使用RAII对象；

  资源在构造期间获得，在析构期间释放（Resource Acquisition Is Initialization, RAII）；在实现RAII时，要小心复制构造和赋值；

- 成对使用new和delete；

  使用typedef时必须要说清楚，当以new创建该种typedef类型对象时，应该以哪种delete方式删除；

  ```c++
  typedef std::string AddressLines[4];
  std::string* pal = new AddressLines;
  
  delete pal; // 行为未定义
  delete [ ] pal; // 很好
  ```

- 成对实现placement operator new和placement operator delete，防止内存泄漏；

- 最好不要对数组形式做typedef；

  - 如果在new表达式中使用`[]`，必须要在相应的delete表达式中使用`[]`；
  - 如果在new表达式中不使用`[]`，一定不要在相应的delete表达式中使用`[]`；
  
- C++需要保证删除null指针永远安全，即operator delete应该在收到null指针时不做任何事;

- 使用智能指针来保存动态分配的资源；

[返回顶部](#C++最佳实践)




### 11.函数参数定义

- 函数参数的求值顺序是不确定的，不要依赖具体的顺序；

  ```c++
  void f(int, int);
  int a = 5;
  f(++a, ++a); // 求值顺序未知
  ```
  
- 始终使用const限制所有指向只输入参数的指针和引用；

- 通过传值的方式来传递原始类型(int, char, float, ...)和复制开销较低的值对象；

- 尽量以传引用的方式来传递复制开销较大的对象（此规则**不适用于**：内置类型，以及STL的迭代器和函数对象）；

  ```c++
  void printNameAndDisplay(Window w) // 传值
  {
      std::cout << w.name();
      w.display();
  }
  WindowWithScrollBars wwsb;
  printNameAndDisplay(wwsb);
  
  void printNameAndDisplay(const Window& w) // 传引用
  {
      std::cout << w.name();
      w.display();
  }
  ```
  
- 返回指针，引用，迭代器时加上const（最好不要直接返回指针和引用，即使你这么做，编译器也会用NRV帮你转成传入参数的形式）;

  ```c++
  struct RectData {
      Point ulhc;
      Point lrhc;
  };
  
  class Rectangle {
  private:
      std::shared_ptr<RectData> pData;
  public:
      ...
      const Point& upperLeft() const { return pData->ulhc; }
      const Point& lowerRight() const { return pData->lrhc; }
      ...
  };
  ```

- 不要使用C语言风格的可变长参数`...`；

[返回顶部](#C++最佳实践)




### 12.尽量避免类型转换

- 强制类型转换对效率有较大的影响；

- 如果一定要进行强制类型转换，最好使用新式转换函数；

  旧式强制转换函数：

  - `(T)expression`
  - `T(expression)`

  新式强制转换函数:

  - `const_cast`
  - `dynamic_cast`
  - `reinterpret_cast`
  - `static_cast`
  
- 防止隐式类型转换；

  - 使用explicit关键字；

    ```c++
    class Widget {
    	explicit Widget(unsigned int widgetizationFactor);
    };
    ```

  - 使用提供转换的命名函数代替转换操作符；

    ```c++
    class String {
      const char* as_char_pointer() const;
    };
    ```

[返回顶部](#C++最佳实践)



### 13.谨慎使用inline函数

- 过度使用inline函数会造成代码膨胀；
- 将大多数inlining行为限制在小型，被频繁调用的函数身上；
- 一个inline函数是否真inline取决于编译器；
  - 有些编译器拒绝将太过复杂（例如带有循环或递归）的函数inlining;
  - 如果函数里调用了virtual函数，也会使inline失效；
- 不要仅仅因为函数定义在头文件，就将它们声明为inline；

[返回顶部](#C++最佳实践)



### 14.降低文件间的编译依赖关系

- 使用`PIMPL(pointer to implementation, 指向实现的指针)`将实现与定义分离；

  ```c++
  // Widget.h
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
  ```

  ```c++
  // Widget.cpp
  #include "widget.h"
  
  struct Widget::Impl { ... };
  Widget::~Widget() = delete;
  Widget::Widget(const Widget& rhs) : pImpl(std::make_unique<Impl>(*rhs.pImpl)) {}// 复制构造函数
  Widget& Widget::operator=(const Widget& rhs) // 复制赋值运算符
  {
      *pImpl = *rhs.pImpl;
      return *this;
  }
  ```

- 为了将实现与定义分离，尽量不要在头文件中定义函数；

[返回顶部](#C++最佳实践)



### 15.使用继承的一些注意点

- 尽量使用组合来代替继承；

  相比于继承，组合具有以下优点：

  1. 更大的灵活性
  2. 缩短编译时间：以指针（或智能指针）保存对象，能够减少头文件的依赖性，因为声明对象的指针不需要对象的完整类型定义；
  3. 更强的适用性
  4. 更健壮，更安全；
  5. 降低复杂性；

  以下情况不能用组合代替继承：

  1. 需要改写虚函数
  2. 需要访问保护成员
  3. 需要在基类之前构造已经使用过的对象或在基类之后销毁此对象
  4. 需要操心虚基类
  5. 能够确定空基类优化能带来好处
  6. 需要控制多态行为

- 派生类中定义的成员会覆盖基类中的同名成员；

  ```c++
  class Base {
  public:
  	virtual void mf1() = 0;
  	virtual void mf1(int);
  };
  class Derived: private Base {
  public:
  	virtual void mf1() { Base::mf1(); } // 转交函数，暗自成为inline
  };
  Derived d;
  int x;
  d.mf1();  // 正确，调用的事Derived::mf1
  d.mf1(x); // 错误，Base::mf1()被遮掩了
  ```

- 区分接口继承和实现继承；

  - 接口继承：声明纯虚函数，让派生类只继承函数接口；

    ```c++
    class Shape{
    public:
        virtual void draw() const = 0;
    }
    ```

  - 实现继承：声明非纯虚函数，让派生类继承该函数的接口和缺省实现；

    ```c++
    class Shape{
    public:
        virtual void error(const std::string& msg);
    }
    ```
	
- 禁止重新定义继承的非虚函数；（待确认）

- 禁止重新定义继承的缺省参数值，因为缺省参数值都是静态绑定的；

  ```c++
  TODO
  ```

- 必要时才使用private继承；

- 不推荐使用多重继承，因为他会导致歧义；

- 虚继承会带来一些成本（类尺寸变大，运行效率降低，加大初始化（及赋值）的复杂度），尽量避免使用虚继承；如果一定要使用，避免在虚基类中定义no-virtual成员；

  ```c++
  TODO
  ```

- 推荐将虚函数声明为非公用的，将公用函数声明为非虚函数；

[返回顶部](#C++最佳实践)




### 16.谨慎使用virtual函数

- 动态绑定的一些替代方法：

  - non-virtual interface(NVI)

    TemplateMethod设计模式的一种特殊形式，令客户通过public non-virtual成员函数间接调用private virtual函数；例：

    ```c++
    class GameCharacter {
    public:
        int healthValue() const
        {
            int retVal = doHealthValue();
            return retVal;
        }
    private:
        virtual int doHealthValue() const { ... } // derived classes可重新定义它
    };
    ```

  - Strategy设计模式

    以`std::function`成员变量替换virtual函数，例：

    ```c++
    class GameCharacter;
    int defaultHealthCalc(const GameCharacter& gc);
    
    class GameCharacter {
    public:
        typedef std::function<int (const GameCharacter&)> HealthCalcFunc;
        explicit GameCharacter(HealthCalcFunc hcf = defaultHealthCalc) : healthFunc(hcf) {}
        int healthValue() const { return healthFunc(*this); }
    private:
        HealthCalcFunc healthFunc;
    };
    ```

[返回顶部](#C++最佳实践)



### 17.typename与class的区别

- 大部分情况下，关键字class或typename意义完全相同；

  ```c++
  template<class T> class Widget;    // 等价
  template<typename T> class Widget; // 等价
  ```

- 当需要在template中声明一个嵌套从属类型名称时，使用typename；

  ```c++
  template<typename C>                // 允许使用typename或class
  void f(const C& container,          // C并不是嵌套从属类型名称，不需要使用typename
         typename C::iterator iter);  // C::iterator是个嵌套从属类型名称，必须使用typename
  ```

- typename不能出现在成员初始化列表中；

  ```c++
  template<typename T>
  class Derived: public Base<T>::Nested { // 不允许typename
  public: 
      explicit Derived(int x) : Base<T>::Nested(x) // 成员初始化列表不允许typename
      {
          typename Base<T>::Nested temp; // 这里可以
          ...
      }
  }
  ```

[返回顶部](#C++最佳实践)



### 18.模版使用心得

- 处理模版化基类名称的三种方法：

  1. 在基类函数调用之前加上`this->`

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

  2. 使用using

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

  3. 明确指出被调用的函数属于基类

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

- 非类型模板参数会造成代码膨胀

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

- 使用成员函数模版生成可接受所有兼容类型的函数

- 需要类型转换时，为模版定义非成员函数

[返回顶部](#C++最佳实践)



### 19.不要对类使用memcpy或memcmp操作

- memcpy和memcmp会扰乱类型系统；

[返回顶部](#C++最佳实践)

---



## New C++

### 1.正确使用模版类型推导

- 在模板型别推导过程中，具有引用型别的实参会被当成非引用型别来处理，其引用性会被忽略；

  ```c++
  template<typename T>
  void f(T& param);
  int x = 27;
  const int cx = x;
  const int& rx = x;
  // 在各次调用中，对param和T的型别推导结果如下:
  f(x);   //T的型别是 int, param的型别是 int&
  f(cx);  //T的型别是 const int, param的型别是 const int&
  f(rx);  //T的型别是 const int, param的型别是 const int&
  ```

- 对万能引用形参进行推导时，左值实参会进行特殊处理；

  ```c++
  template<typename T>
  void f(T&& param);
  int x = 27;
  const int cx = x;
  const int& rx = x;
  f(x);   //x是个左值，所以T的型别是int&, param的型别也是int&
  f(cx);  //cx是个左值，所以T的型别是const int&, param的型别也是 const int&
  f(rx);  //rx是个左值，所以T的型别是const int&, param的型别也是 const int&
  f(27);  //27是个右值，所以T的型别是int，这么一来，param的型别就成了 int&&
  ```

- 对按值传递的形参进行推导时，若实参型别中带有const或volatile，则他们还是会被当作不带const或volatile的型别来处理；

  ```c++
  template<typename T>
  void f(T param);
  const char* const ptr = "abc";  //ptr是个指向const对象的const指针
  f(ptr);                         //传递型别为const char* const的实参
  ```

- 在模板型别推导过程中，数组或函数型别的实参会退化成对应的指针，除非他们被用来初始化引用；

  ```c++
  void someFunc(int, double);
  template<typename T>
  void f1(T param);
  f1(someFunc);   //param被推导为函数指针，具体型别是 void(*)(int, double)
  
  template<typename T>
  vid f2(T& param);
  f2(someFunc);   //param被推导为函数引用，具体型别是 void(&)(int, double)
  ```



### 2.正确进行型别推导

- 在一般情况下，auto型别推导和模版型别推导是一模一样的，但是auto型别推导会假定用大括号括起来的初始化表达式代表一个`std::initializer_list`(初始化列表)，但模版型别推导却不会；

  ```c++
  auto x = { 11, 23, 9 }; // x的型别是 std::initializer_list<int>
  
  template<typename T>    // 带有形参的模版
  void f(T param);        // 与x的声明等价的声明式
  f({ 11, 23, 9 });       // 错误！无法推导T的型别
  ```

- 在函数返回值或lambda式的形参中使用auto，意思是使用模版型别推导而非auto型别推导；

  ```c++
  std::vector<int> v;
  ...
  auto resetV = [&v](const auto& newValue) { v = newValue; }; // c++14
  ...
  resetV({ 1, 2, 3 });    // 错误！无法为{ 1, 2, 3 }完成型别推导
  ```



### 3.正确使用decltype

- 绝大多数情况下，`decltype`会得出变量或表达式的型别而不做任何修改；

- 对于型别为T的左值表达式，除非该表达式仅有一个名字，`decltype`总是得出型别`T&`；

- c++14支持`decltype(auto)`，和auto一样，它会从其初始化表达式出发来推导型别，但是它的型别推导使用的是`decltype`的规则；

  ```c++
  Widget w;
  const Widget& cw = w;
  decltype(auto) myWidget2 = cw; // decltype型别推导：const Widget&
  ```



### 4.优先使用auto

* auto变量必须初始化，避免致兼容性和效率问题的型别不匹配现象，还可以简化重构流程，简化代码；

  ```c++
  int x1;      // 有潜在的未初始化风险
  auto x2;     // 编译错误！必须有初始化物
  auto x3 = 0; // 没问题
  auto derefLess = [](const auto& p1, const auto& p2) { return *p1 < *p2; }; // 使用auto表示lambda
  ```

* 隐形代理型别可以导致auto类型推导错误；

  ```c++
  std::vector<bool> features(const Widget& w);
  Widget w;
  auto highPriority = features(w)[5]; // highPriority是std::vector<bool>::reference型别
  ```

* 带显式型别的初始化物习惯用法强制auto推导出你想要的型别；

  ```c++
  std::vector<bool> features(const Widget& w);
  Widget w;
  auto highPriority = static_cast<bool>(features(w)[5]); // highPriority被强制初始化为bool
  ```

- 对`auto&&`型别的形参使用`decltype`和`std::forward`；

  ```c++
  auto f = [](auto&& param) { 
      return func(normalize(std::forward<decltype(param)>(param)));
  };
  ```

[返回顶部](#C++最佳实践)



### 5.优先使用初始化列表

* 大括号初始化可以应用的语境最为广泛，可以阻止隐式窄化型别转换；

  ```c++
  std::vector<int> v{ 1, 3, 5 }; // v的初始内容为1, 3, 5
  class Widget {
  private:
      int x{ 0 }; // 推荐
      int y = 0;  // 可行
      int z(0);   // 不可行
  };
  ```

* 在构造函数重载决议期间，只要有任何可能，大括号初始化物就会与带有`std::initializer_list`型别的形参相匹配，即使其他重载版本有着貌似更加匹配的形参表；

  ```c++
  class Widget {
  pubic:
      Widget(int i, bool b);
      Widget(int i, double d);
      Widget(std::initializer_list<long double> il);
  };
  Widget w1(10, true); // 调用第一个构造函数
  Widget w2{10, true}; // 调用第三个构造函数；使用大括号，调用的是带有std::initializer_list型别形参的构造函数(10和true被强制转换为long double)
  Widget w3(10, 5.0);  // 调用第二个构造函数
  Widget w4{10, 5.0};  // 调用第三个构造函数；使用大括号，调用的是带有std::initializer_list型别形参的构造函数(10和5.0倍强制转换为long double)
  ```

[返回顶部](#C++最佳实践)



### 6.优先选用nullptr

* 相对于0或NULL，优先选用nullptr；

* 避免在整型和指针型别之间重载；

  ```c++
  void f(int);
  void f(bool);
  void f(void*);
  f(0);       // 调用的是f(int)，而不是f(void*)
  f(NULL);    // 可能通不过编译，但一般会调用f(int)，从来不会调用f(void*) 
  f(nullptr); // 调用的是f(void*)
  ```

[返回顶部](#C++最佳实践)



### 7.优先选用using而非typedef

* `typedef`和`using`的作用基本是一致的;

  ```c++
  typedef void (*FP)(int, const std::string&);  // 使用typedef
  using FP = void (*)(int, const std::string&); // 使用别名
  ```

* typedef不支持模板化，但别名声明支持；

  ```c++
  // 使用typedef
  template<typename T>
  struct MyAllocList {
      typedef std::list<T, MyAlloc<T>> type;   // MyAllocList<T>::type是std::list<T, MyAlloc<T>>的同义词
  };
  MyAllocList<Widget>::type lw;
  ```
  
  ```c++
  // 使用别名
  template<typename T>
  using MyAllocList = std::list<T, MyAlloc<T>>; // std::list<T, MyAlloc<T>>的同义词
  MyAllocList<Widget> lw;
  ```

[返回顶部](#C++最佳实践)



### 8.优先选用enum class

* 限定作用域枚举类型降低了名字空间污染；

  ```c++
  enum class Color { black, white, red }; // black,white,red所在作用域被限定在Color内
  auto white = false;     // 没问题，范围内并无其它“white”
  Color c = white;        // 错误！范围内并无名为“white”的枚举量
  Color c = Color::white; // 没问题
  auto c = Color::white;  // 没问题
  ```

* 限定作用域的枚举型别仅在枚举型别内可见，只能通过强制型别转换以转换至其他型别，不限范围的枚举型别中的枚举量可以隐式转换到整数型别；

  ```c++
  // 不限定范围枚举型别
  enum Color { black, white, red }; 
  std::vector<std::size_t> primeFactors(std::size_t x);
  Color c = red;
  if(c < 14.5) {
      auto factors = primeFactors(c);
  }
  ```

  ```c++
  // 限定范围枚举型别
  enum class Color { black, white, red };
  Color c = Color::red;
  if (c < 14.5) {                     // 错误！不能将Color型别和double型别比较
      auto factors = primeFactors(c); // 错误！不能将Color型别传入
  }
  ```

* 限定作用域的枚举型别和不限定范围的枚举型别都支持底层型别指定，限定作用域的枚举型别的默认底层型别是int，而不限范围的枚举型别没有默认底层型别；

* 限定作用域的枚举型别总是可以进行前置声明，而不限范围的枚举型别却只有在指定了默认底层型别的前提下才可以进行前置声明；

  ```c++
  enum Color;       // 错误
  enum class Color; // 没问题
  ```

[返回顶部](#C++最佳实践)



### 9.优先选用delete

* 优先选用删除函数(delete)，而非private未定义函数；

  ```c++
  // private未定义函数
  template <class charT, class traits = char_traits<charT> >
  class basic_ios : public ios_base {
  public:
  		...
  private:
      basic_ios(const basic_ios&);            // 未定义
      basic_ios& operator=(const basic_ios&); // 未定义
  };
  ```

  ```c++
  // 删除函数delete
  template <class charT, class traits = char_traits<charT> >
  class basic_ios : public ios_base {
  public: // 习惯把delete函数声明为public
      basic_ios(const basic_ios&) = delete;
      basic_ios& operator=(const basic_ios&) = delete;
  }
  ```

* 任何函数都可以删除(delete)，包括非成员函数和模板实现；

  ```c++
  // c++11 删除函数delete
  class Widget {
  public:
      template<typename T>
      void processPointer(T* ptr) { ... }
  };
  template<>
  void Widget::processPointer<void>(void*) = delete; // 仍然具备public访问权限，但被删除了
  ```
  
  ```c++
  // c++98 private未定义函数
  class Widget {
  public:
      template<typename T>
      void processPointer(T* ptr) { ... }
  private:
      template<> // 可能编译不过
      void processPointer<void>(void*);
  };
  ```
  

[返回顶部](#C++最佳实践)



### 10.优先使用override

- override让编译器在想要改的函数实际上并未修改时提醒你；

- 评估改写函数造成的影响；

- 支持重写的基本条件：

  - 基类中的函数必须是虚函数
  - 基类和派生类中的函数名字必须完全相同（析构函数例外）
  - 基类和派生类中的函数形参型别必须完全相同
  - 基类和派生类中的函数常量性（constness）必须完全相同
  - 基类和派生类中的函数返回值和异常规格必须兼容
  - (c++11新增)基类和派生类中的函数引用饰词（reference qualifier，`&`, `&&` ...）必须完全相同

  ```c++
  class Base {
  public:
      virtual void mf1() const;
      virtual void mf2(int x);
      virtual void mf3() &;
      virtual void mf4() const;
  };
  
  class Derived : public Base {
  public:
      virtual void mf1() const override;
      virtual void mf2(int x) override;
      virtual void mf3() & override;
      void mf4() const override;
  };
  ```

[返回顶部](#C++最佳实践)



### 11.优先选用const_iterator

- 当迭代器指向的内容不需要修改时，优先选用const_iterator，而非iterator；

  ```c++
  std::vector<int> values;
  // 容器的成员函数`cbegin`,`cend`等都返回`const_iterator`型别
  auto it = std::find(values.cbegin(), values.cend(), 1983);
  values.insert(it, 1998);
  ```

[返回顶部](#C++最佳实践)




### 12.只要函数不会发射异常就加上noexcept声明

* 相对于不带noexcept声明的函数，带有noexcept声明的函数有更多机会得到优化；

  `noexcept`对函数的优化：优化器不需要在异常传出函数的前提下，将执行期栈保持在可开解状态；也不需要在异常逸出函数的前提下，保证所有其中的对象以其被构造顺序的逆序完成析构。

  ```c++
  RetType function(params) noexcept; // 最优化
  RetType function(params) trow();   // 优化不够
  RetType function(params);          // 优化不够
  ```

[返回顶部](#C++最佳实践)



### 13.尽可能使用constexpr

- constexpr具备const的所有属性，并且由编译期已知的值完成初始化；

  ```c++
  constexpr auto arraySize2 = 10;    // 没问题，10是个编译期常量
  ```

- constexpr函数在调用时若传入的实参值是编译期已知的，则会产出编译期结果；

  ```c++
  int sz; // 非constexpr变量
  
  constexpr auto arraySize1 = sz;    // 错误！sz的值在编译期未知
  std::array<int, sz> data1;         // 错误！一样的问题
  constexpr auto arraySize2 = 10;    // 没问题，10是个编译期常量
  std::array<int, arraySize2> data2; // 没问题，arraySize2是个constexpr
  
  // const并未提供和constexpr同样的保证，因为const对象不一定经由编译期已知值来初始化
  int sz; 						             // 仍然是非constexpr变量
  const auto arraySize = sz; 	     // 没问题，arraySize是sz的一个const副本
  std::array<int, arraySize> data; // 错误！arraySize
  ```

- c++11中，constexpr函数不得包含多于一个可执行语句，即一条return语句；

  ```c++
  constexpr int pow(int base, int exp) noexcept
  {
      return (exp == 0 ? 1 : base * pow(base, exp - 1));
  }
  ```

[返回顶部](#C++最佳实践)



### 14.正确使用三大智能指针

* 使用`std::unique_ptr`管理具备专属所有权的资源;

  ```c++
  class Investment { ... };
  template<typename... Ts> makeInvestment(Ts&&... params);
  ```

* 有状态的删除器和采用函数指针实现的删除器会增加`std::unique_ptr`型别的对象尺寸；

  ```c++
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
  ```

* 使用`std::shared_ptr`管理具备共享所有权的资源；

  ```c++
  auto customDeleter1 = [](Widget *pw){...};
  auto customDeleter2 = [](Widget *pw){...};
  std::shared_ptr<Widget> pw1(new Widget, customDeleter1);
  std::shared_ptr<Widget> pw2(new Widget, customDeleter2);
  ```

* 避免使用裸指针型别的变量来创建`std::shard_ptr`指针；

  ```c++
  class Widget {
  public:
    void process();
    ...
  };
  std::vector<std::shared_ptr<Widget> > processedWidgets;
  void Widget::process()
  {
  	processedWidgets.emplace_back(this); // 将裸指针(this)传入，并套上一层std::shared_ptr，可能会引发未定义行为；
  }
  ```

  对于上述情况可以采用以下方法避免：

  ```c++
  class Widget : public std::enable_shared_from_this<Widget> {
  public:
    void process();
    ...
  };
  void Widget::process()
  {
  	processedWidgets.emplace_back(shared_from_this());
  }
  ```

* 引用计数会对以下性能造成影响：

  - `std::shared_ptr`的尺寸是裸指针的两倍；
  - 引用计数的内存必须动态分配；
  - 引用计数的递增和递减必须是原子操作；
  
* 对于功能类似于`std::shared_ptr`，但是可能有空悬指针的情况使用`std::weak_ptr`；

  ```c++
  auto spw = std::make_shared<Widget>(); // spw构造完成后，指涉到Widget的引用计数设置为1
  std::weak_ptr<Widget> wpw(spw) // wpw和spw指涉到同一个Widget。引用计数保持为1
  spw = nullptr; // 引用计数变为0，Widget对象被析构。wpw空悬（expired）
  ```

[返回顶部](#C++最佳实践)



### 15.优先使用make系列函数而非直接使用new

- make系列函数消除了重复代码，改进了异常安全性，生成的目标代码会尺寸更小，速度更快；

  ```c++
  auto upw1(std::make_unique<Widget>());    // 使用make_unique，简洁
  std::unique_ptr<Widget> upw2(new Widget); // 不使用make_unique，重复
  auto spw1(std::make_shared<Widget>());    // 使用make_shared，简洁
  std::shared_ptr<Widget> spw2(new Widget); // 不使用make_shared，重复
  
  void processWidget(std::shared_ptr<Widget> spw, int priority);
  int computePriority();
  processWidget(std::shared_ptr<Widget>(new Widget), computePriority()); // 潜在的资源泄漏风险
  processWidget(std::make_shared<Widget>(), computePriority());          // 避免发生潜在的资源泄漏风险
  
  std::shared_ptr<Widget> spw(new Widget); // 引发2次内存分配
  auto spw = std::make_shared<Widget>();   // 1次内存分配
  ```

- 对于`std::shared_ptr`，不建议使用make系列函数的额外场景包括：

  1. 自定义内存管理的类；

     ```c++
     std::unique_ptr<Widget, decltype(widgetDeleter)> upw(new Widget, widgetDeleter);
     std::shared_ptr<Widget> spw(new Widget, widgetDeleter);
     ```

  2. 内存紧张的系统，非常大的对象，以及存在比指涉到相同对象的`std::shared_ptr`生存期更久的`std::weak_ptr`；

[返回顶部](#C++最佳实践)



### 16.正确使用万能引用和右值引用

- 如果函数模板形参具备`T&&`型别，并且T的型别系推导而来，或如果对象使用`auto&&`声明型别，则该形参或对象就是个万能引用；

  ```c++
  template<typename T>
  void f(T&& param);  // 万能引用
  std::vector<int> v;
  f(v); // 错误！不能给一个右值引用绑定一个左值
  
  Widget&& var1 = Widget();
  auto&& var2 = var1; // 万能引用
  ```

- 如果型别声明并不精确的具备`type&&`的形式，或者型别推导并未发生，则`type&&`就代表右值引用；

  ```c++
  void f(Widget&& param);         // 右值引用
  Widget&& var1 = Widget();       // 右值引用
  template<typename T>
  void f(std::vector<T>&& param); // 右值引用
  ```

- 若采用右值来初始化万能引用，就会得到一个右值引用；若采用左值来初始化万能引用，就会得到一个左值引用；

- 禁止把万能引用作为重载函数的形参，如果一定要这么用，可以使用`std::enable_if`对模板施加限制；

  ```c++
  // 错误示例
  template<typename T>
  void logAndAdd(T&& name)
  {
      auto now = std::chrono::system_clock::now();
      log(now, "logAndAdd");
      names.emplace(std::forward<T>(name));
  }
  std::string nameFromIdx(int idx);
  void logAndAdd(int idx)
  {
      auto now = std::chrono::system_clock::now();
      log(now, "logAndAdd");
      names.emplace(nameFromIdx(idx));
  }
  std::string petName("Darla");
  logAndAdd(petName);
  logAndAdd(std::string("Persephone")); // 对右值实施移动而非复制
  logAndAdd("Patty Dog"); // 在multiset中直接构造一个std::string对象，而非复制一个std::string型别的临时对象
  short nameIdx = 0;
  logAndAdd(nameIdx); // 错误，这里优先匹配的是万能引用
  ```

  ```c++
  // 使用std::enable_if
  class Person {
  public:
    template<
    	typename T,
    	typename = std::enable_if_t<
        !std::is_base_of<Person, std::decay_t<T>>::value
        &&
        !std::is_integral<std::remove_reference_t<T>>::value
      >
    >
    // 接受std::string型别以及可以强制转型到std::string的实参型别的构造函数
    explicit Person(T&& n) : name(std::forward<T>(n)) {
    	// 断言可以从T型别的对象构造一个std::string型别的对象
      static_assert(std::is_constructible<std::string, T>::value,
                  		"Parameter n can't be used to construct a std::string")
    }
    // 接受整型实参的构造函数
    explicit Person(int idx) : name(nameFromIdx(idx)) {...}
    ...
  private:
    std::string name;
  };
  ```

- 万能引用形参通常在性能方面具备优势，但在易用性方面一般会有劣势，使用时要权衡利弊；

[返回顶部](#C++最佳实践)



### 17.正确使用std::move和std::forward

- `std::move`实施的是无条件的向右值型别的强制型别转换（不会执行移动操作），`std::forward`实施的是有条件的强制类型转换（仅当传入的实参被绑定到右值时，`std::forward`才针对该实参实施向右值型别的强制型别转换）；

  ```c++
  void process(const Widget& lvalArg); // 处理左值
  void process(Widget&& rvalArg);      // 处理右值
  
  template<typename T> // 把param传递给process的函数模版
  void logAndProcess(T&& param)
  {
      process(std::forward<T>(param)); // 强制类型转换
  }
  ```

- 使用`std::move`可以避免复制入参数据成员的过程产生的复制操作成本；

  ```c++
  class Annotation {
  public:
      // 将text移动入value
      explicit Annotation(const std::string text) : value(std::move(text)) 
      { ... }
  private:
      std::string value;
  };
  ```
  
- 针对右值引用实施`std::move`，针对万能引用实施`std::forward`；

  ```c++
  class Widget {
  public:
    // 右值引用
    Widget(Widget&& rhs) : name(std::move(rhs.name)), p(std::move(rhs.p)) {...}
  	...
  private:
    std::string name;
    std::shared_ptr<SomeDataStructure> p;
  };
  ```

  ```c++
  class Widget {
  public:
    // 万能引用
    template<typename T>
    void setName(T&& newName) { name = std::forward<T>(newName); }
  }
  ```

- 若局部对象可能适用于返回值优化(RVO, return value optimization)，禁止对其进行`std::move`或`std::forward`；

  ```c++
  Widget makeWidget()
  {
  	Widget w;
    ...
    return std::move(w); // 禁止操作，这样会导致跳过RVO优化
  }
  ```

- 移动操作在以下场景无效：

  1. 没有移动操作

     待移动的对象未能提供移动操作，因此，移动请求就变成了复制请求；

  2. 移动未能更快

     待移动的对象虽然有移动操作，但并不比其复制操作更快；

  3. 移动不可用

     移动本可以发生的语境下，要求移动操作不可发射异常，但该操作未加上noexcept声明；
  
- 对于可复制的，在移动成本低廉的并且一定会被复制的形参而言，按值传递可能会和按引用传递的具备相近的效率，并可能生成更少量的目标代码；

- 经由构造复制形参的成本可能比经由赋值复制形参高出很多；

- 按值传递肯定会导致切片问题，所以基类型别特别不适用于按值传递；

[返回顶部](#C++最佳实践)



### 18.完美转发的失败场景

完美转发的失败情形，是源于模板型别推到失败或推导结果是错误的类型，失败的情形如下：

- 大括号初始化物

  ```c++
  void f(const std::vector<int>& v);
  f({1, 2, 3});   // 没问题，“{1, 2, 3}”会隐式转换为std::vector<int>
  fwd({1, 2, 3}); // 错误！无法通过编译
  ```

- 0和NULL用作空指针

  如果把0和NULL以空指针之名传递给模版，型别推导就会发生行为扭曲，推导结果会是整型而非所传递实参的指针型别（修正方案：用nullptr）;

- 仅有声明的整形`static const`成员变量

  ```c++
  class Widget {
  public:
      static const std::size_t MinVals = 28; // 给出了MinVals的声明
      ...
  };
  ...
  std::vector<int> widgetData;
  widgetData.reserve(Widget::MinVals) // 此处用到了MinVals
  void f(std::size_t val);
  f(Widget::MinVals);   // 没问题，当“f(28)”处理
  fwd(Widget::MinVals); // 错误！可能无法链接
  ```

- 重载的函数名字和模版名字

  ```c++
  void f(int (*pf)(int));
  void f(int pf(int));
  int processVal(int value);
  int processVal(int value, int priority);
  
  f(processVal);       // 没问题
  fwd(processVal);     // 错误
  
  template<typename T>
  T workOnVal(T param) // 处理值的模版
  { ... }
  
  fwd(workOnVal);                               // 错误！workOnVal的哪个实例？
  using ProcessFuncType = int (*)(int);         // 相当于创建一个typedef；
  ProcessFuncType processValPtr = processVal;   // 指定了需要的processVal签名
  fwd(processValPtr);                           // 没问题
  fwd(static_cast<ProcessFuncType>(workOnVal)); // 没问题
  ```

- 位域被用作函数实参

  ```c++
  struct IPv4Header {
      std::uint32_t version:4,
                    IHL:4,
                    DSCP:6,
                    ECH:2,
                    totalLength:16;
      ...
  };
  
  void f(std::size_t sz); // 待调用的函数
  IPv4Header h;
  ...
  f(h.totalLength); // 没问题
  fwd(h.totalLength); // 错误!
  ```

[返回顶部](#C++最佳实践)



### 19.正确使用lambda

- 避免默认捕获模式；

  按引用的默认捕获会导致空悬指针问题，按值的默认捕获极易受空悬指针影响(尤其是this),并会误导人们认为lambda式是自洽的；

  ```c++
  // 引用默认捕获空悬指针
  auto divisor = computeDivisor(calc1, calc2);
  filters.emplace_back([&](int value) { return value % divisor == 0; }); // 对divisor的指涉可能空悬
  ```

  ```c++
  // 值默认捕获收到外部影响
  static auto divisor = computeDivisor(calc1, calc2);
  filter.emplace_back([=](int value) { return value % divisor == 0; }); // 未捕获任何东西
  ++divisor; // 意外修改了divisor
  ```

- 使用初始化捕获将对象移入闭包；

  ```c++
  auto func = [pw = std::move(pw)] {...}               // 采用std::move(pw)初始化闭包类的数据成员
  auto func1 = [pw = std::make_unique<Widget>()] {...} // 以make_unique的调用结果初始化闭包类的成员
  auto func2 = std::bind( // c++11中针对可变lambda式的模拟初始化捕获
    [](std::vector<double>& data) mutable { ... }, 
    std::move(data) );
  ```

- lambda式比起使用`std::bind`而言，可读性更好，表达力更强，可能运行效率也更高；

  ```c++
  using setAlarm = void(*)(Time t, Sound s, Duration d);
  auto setSoundL = [](Sound s) {
  	setAlarm(steady_clock::now() + 1h, s, 30s);
  };
  auto setSoundB = std::bind(static_cast<SetAlarm3ParamType>(setAlarm),
                						 std::bind(std::plus<>(), steady_clock::now(), 1h),
                             _1,
                             30s);
  ```

[返回顶部](#C++最佳实践)



### 20.保证线程安全性

- 运用`std::atomic`型别的变量会比运用互斥量提供更好的性能；

  ```c++
  class Widget {
  public:
      ...
      int magicValue()n const
      {
          if(cacheValid) return cachedValue;
          else {
              auto val1 = expensiveComputation1();
              auto val2 = expensiveComputation2();
              cachedValue = val1 + val2;
              cacheValid = true;
              return cachedValue;
          }
      }
  private:
      mutable std::atomic<bool> cacheValid{ false };
      mutable std::atomic<int> cachedValue;
  };
  ```

- 如果异步是必要的，则使用`std::async`，`std::launch::async`和`std::luanch::deferred`相配合；

  ```c++
  auto f = std::async(std::launch::async | std::launch::deferred, // 采用异步或推迟的方式
                      f);
  ```

- 在析构时调用join可能导致难以调试的性能异常，在析构时调用detach可能导致难以调试的未定义行为；

  ```c++
  class ThreadRAII {
  public:
    enum class DtorAction { join, detach }; // 枚举类
    ThreadRAII(std::thread&& t, DtorAction a) : action(a), t(std::move(t)) {};
    
    ~ThreadRAII() {
    	if(t.joinable()) {
      	if (action == DtorAction::join)
          t.json();
        else
          t.detach();
      }
    };
    
    std::thread& get() { return t; }
  private:
    DtorAction action;
    std::thread t;
  };
  ```

- 在成员列表的最后再声明`std::thread`型别对象；

- 考虑针对一次性事件通信使用以void为模板型别实参的期值；

  ```c++
  std::promise<void> p;
  void detect()                               // 现在可以处理多个反应任务了
  {
      auto sf = p.get_future().share();       // sf的型别是std::shared_future<void>
      std::vector<std::thread> vt;            // 反应任务的容器
      for (int i = 0; i < threadsToRun; ++i ) {
          vt.emplace_back([sf]{ sf.wait(); react(); }); // sf局部副本之上的wait
      }
      ...                                     // 若此处抛出异常，则detect会失去响应
      p.set_value();                          // 让所有线程取消暂停
      ...
      for (auto& t : vt)                      // 把所有线程设置为不可联结状态
          t.join();
  }
  ```

- `std::atomic`用于多线程访问的数据，且不用互斥量；

- volatile用于读写操作不可以被优化掉的内存；

[返回顶部](#C++最佳实践)



---

## STL

### 1.选择合适的算法

排序算法：

| 需求                                                         | sort | stable_sort | partial | stable_partition | nth_element |
| ------------------------------------------------------------ | ---- | ----------- | ------- | ---------------- | ----------- |
| 需要对vector，string，deque或者数组中的元素执行一次完全排序  | *    | *           |         |                  |             |
| 有一个vector，string，deque或者数组，并且只需对等价性最前面的n个元素进行排序 |      |             | *       |                  |             |
| 有一个vector，string，deque或者数组，并且需要找到第n个位置上的元素，或者，需要找到等价性最前面的n个元素但又不必对这n个元素进行排序 |      |             |         |                  | *           |
| 需要将一个标准序列容器中的元素按照是否满足某个特定的条件区分开来 |      |             | *       | *                |             |
| 需要对list中的数据排序                                       |      |             | *       | *                |             |

[返回顶部](#C++最佳实践)



### 2.选择合适的容器

| 需求                                                         | vector | list | deque | set<br>multiset | map<br>multimap | stack | queue<br>priority queues |
| ------------------------------------------------------------ | ------ | ---- | ----- | --------------- | --------------- | ----- | ------------------------ |
| 在容器的任意位置插入新元素                                   | *      | *    | *     |                 |                 |       |                          |
| 不关心容器中的元素是如何排序的                               |        |      |       |                 |                 |       |                          |
| 随机访问迭代器                                               | *      |      | *     |                 |                 |       |                          |
| 当发生元素的插入或删除操作时，避免移动容器中原来的元素       |        | *    |       | *               | *               |       |                          |
| 数据的布局需要和C兼容                                        | *      |      |       |                 |                 |       |                          |
| 对元素的查找速度敏感                                         | *      |      |       | *               | *               |       |                          |
| 使迭代器，指针或引用变为无效的次数最少                       |        | *    |       |                 |                 |       |                          |
| 使用随机访问迭代器，没有删除操作，且插入操作只发生在容器尾部 |        |      | *     |                 |                 |       |                          |

[返回顶部](#C++最佳实践)



### 3.尽量使用empty函数判空而不是检查size()==0

- empty对所有的标准容器的操作都是**常数时间**，且empty函数常常会被内联，而size对于一些list的操作是**线性时间**；

[返回顶部](#C++最佳实践)



### 4.区间成员函数优先于与之对应的单元素成员函数

- 通过使用区间成员函数，通常可以少写一些代码；
- 使用区间成员函数通常会得到意图清晰和更加直接的代码；
- 使用单元素的成员函数比使用区间成员函数需要更多地调用内存分配子，更频繁地拷贝对象，且做了冗余操作；
- 当需要给容器一组全新的值时，使用assign而不是operator=；

使用单元素成员函数进行插入：

```c++
int data[numValues];
vector<int> v;
vector<int>::iterator insertLoc(v.begin());
for (int i = 0; i < numValues; ++i) {
    insertLoc = v.insert(insertLoc, data[i]);
    ++insertLoc;
}
```

使用区间成员函数进行插入：

```c++
int data[numValues];
vector<int> v;
v.insert(v.begin(), data, data + numValues); // 使用区间插入效率比单元素插入高得多
```

[返回顶部](#C++最佳实践)



### 5.小心C++编译器的分析机制-尽可能地将代码解释为函数声明

错误的做法：

```c++
list<int> data(istream_iterator<int>(dataFile), 
               istream_iterator<int>()); // 参数没有名称，类型是指向不带参数的函数的指针，该函数返回一个istream_iterator<int>
```

正确的做法：

```c++
istream_iterator<int> dataBegin(dataFile);
istream_iterator<int> dataEnd;
list<int> data(dataBegin, dataEnd);
```

[返回顶部](#C++最佳实践)



### 6.如果容器中包含了通过new操作创建的指针，切记在容器对象析构前将指针delete掉

- 指针容器在自己被析构时会析构所包含的每个元素，但对指针的析构函数不做处理，也不会调用delete；

  错误的做法：

  ```c++
  void doSomething()
  {
      vector<Widget*> vwp;
      for (int i = 0; i < SOME_MAGIC_NUMBER; ++i)
          vwp.push_back(new Widget); // 使用了new创建指针
  }
  ... // 发生内存泄漏！！！当vwp的作用域结束时，它的元素全部被析构，但是通过new创建的对象没有被删除；
  ```

  正确的做法：

  ```c++
  void doSomething()
  {
      vector<Widget*> vwp;
      for (int i = 0; i < SOME_MAGIC_NUMBER; ++i)
          vwp.push_back(new Widget); // 使用了new创建指针
      
      // 手动释放
      for (vector<Widget*>::iterator i = vwp.begin(); i != vwp.end(); ++i)
          delete *i;
  }
  ```

[返回顶部](#C++最佳实践)



### 7.禁止创建包含auto_ptr的容器对象

- COAP（auto_ptr的容器）不可移植；

- 拷贝一个auto_ptr意味着改变它的值；

  ```c++
  auto_ptr<Widget> pw1(new Widget); // pw1指向一个Widget。
  auto_ptr<Widget> pw2(pw1);        // pw2指向pw1的Widget；pw1被置为NULL（Widget的所有权从pw1转移到了pw2）。
  pw1 = pw2;                        // pw1指向Widget，pw2被置为NULL。
  ```

[返回顶部](#C++最佳实践)



### 8.STL容器的线程安全性不够

- **多个线程读是安全的**，多个线程可以同时读同一个容器的内容，并且保证是正确的；在读的过程中，不能对容器有任何写入操作；

- **多个线程对不同的容器做写入操作是安全的**，多个线程可以同时对不同的容器做写入操作；

- 建议使用RAII（Resource Acquisition Is Initialization）的方式来手动控制同步；

  ```c++
  TODO
  ```

[返回顶部](#C++最佳实践)



### 9.推荐使用vector和string而不是动态分配的数组

- 大多数情况下，推荐使用vector和string替换动态分配的数组；
- 在多线程环境中，推荐使用内置数组代替含有引用计数的string；多线程下，为保证string的引用计数的安全性而采取的措施，会影响效率；

[返回顶部](#C++最佳实践)



### 10.使用reserve来避免不必要的重新分配

- 尽早使用reserve，把容器的容量设置为足够大，以避免重新分配；

  ```c++
  vector<int> v;
  v.reserve(1000); // 预先分配容量，防止push_back的过程中进行扩容
  for (int i = 1; i <= 1000; ++i)
      v.push_back(i);
  ```

[返回顶部](#C++最佳实践)



### 11.避免使用`vector<bool>`

- `vector<bool>`是一个假的容器，为了节省空间，它并不真的存储bool，而是使用类似1个字节存储8个bool的位域（bitfield）方式来存放；

[返回顶部](#C++最佳实践)



### 12.包含指针的关联容器指定比较类型

- 当创建包含指针的关联容器时，容器会按照**指针的值**而不是**指针指向的内容**进行排序；

- 每当创建包含指针的关联容器时，同时也要指定容器的比较类型；

  创建比较函数通用模版：

  ```c++
  struct DereferenceLess // 定义一个比较函数的通用模板
  {
      template<typename PtrType>
      bool operator()(PtrType pT1, PtrType pT2) const 
      {
          return *pT1 < *pT2;
      }
  }
  
  set<string*, DereferenceLess> ssp;
  
  // 普通方法打印
  for (StringPtrSet::const_iterator i = ssp.begin(); i != ssp.end(); ++i)
      cout << i << endl;
  
  // 使用for_each算法打印
  void print(const string *ps)
  {
      cout << *ps << endl;
  }
  for_each(ssp.begin(), ssp.end(), print);
  ```

- `>=`对于关联容器来说不是一个合法的比较函数，相等的值从来不会有前后顺序关系；

  ```c++
  set<int, less_equal<int> > s;
  s.insert(10);
  
  struct StringPtrGreater : public binary_function<const string*, const string*, bool> 
  {
      bool operator()(const string *ps1, const string *ps2) const
      {
          return !(*ps1 < *ps2); // !(<)等价于>=；不能直接把比较结果取反来改变排列顺序，这对于关联容器不是一个合法的比较函数
      }
  };
  ```

[返回顶部](#C++最佳实践)



### 13.禁止直接修改set或multiset中的键

- 对于map和multimap，键的类型是const，如果有程序试图修改容器中的键，会影响到容器的排序性，它将无法通过编译；

  ```c++
  map<int, string> m;
  m.begin()->first = 10; // 错误；map的键不能被修改
  
  multimap<int, string> mm;
  mm.begin()->first = 20; // 错误；multimap的键不能被修改
  ```

- 对于set和multiset，修改元素的值这一行为具有不可移植性；

[返回顶部](#C++最佳实践)



### 14.当效率至关重要时，根据不同情况选择map::operator[]或map::insert

- 当向映射表中添加元素时，要优先选用insert，而不是operator[]；

  ```c++
  class Widget {
  public:
      Widget();
      Widget(double weight);
      Widget& operator=(double weight);
      ...
  };
  
  map<int, Widget> m;
  // 低效
  m[1] = 1.50; // 效率低，先判断存不存在，存在就更新，不存在就插入（空的map，键1肯定不存在）
  // 高效
  m.insert(IntWidgetMap::value_type(1, 1.50)); // 效率高，不判断直接插入
  ```

- 当更新已经在映射表中的元素的值时，要优先选择operator[]；

[返回顶部](#C++最佳实践)



### 15.避免混用不同类型的迭代器，优先使用iterator而不是其它类型的迭代器

- 尽量使用iterator而不是const或reverse型的迭代器，可以使容器的使用更为简单而有效，并且可以避免潜在的问题，原因如下：

  - 有些版本的insert和erase函数要求使用iterator。如果你需要调用这些函数，那你就必须使用iterator。const和reverse型的迭代器不能满足这些函数的要求。
  - 要想隐式地将一个const_iterator转换成iterator是不可能的。
  - 从reverse_iterator转换而来的iterator在使用之前可能需要相应的调整。

- 避免混用不同类型的迭代器；

  ```c++
  typedef deque<int> IntDeque;
  typedef IntDeque::iterator Iter;
  typedef IntDeque::const_iterator ConstIter;
  Iter i;
  ConstIter ci;
  ...
  if (i == ci) // 比较一个iterator和一个const_iterator（iterator在比较前会被隐式转化为const_iterator）
      ...
  ```

[返回顶部](#C++最佳实践)



### 16.对于逐个字符的输入考虑使用istreambuf_iterator

- istream_iterator内部执行了格式化输入（构造析构对象，流标志检查，错误检查，...），导致其效率不佳；

  ```c++
  ifstream inputFile("interestingData.txt");
  inputFile.unsetf(ios::skipws); // 禁止忽略空格
  string fileData((istream_iterator<char>(inputFile)), istream_iterator<char>()); // 将inputFile读入fileData
  ```

- istreambuf_iterator从流读取单个字符，从流的缓冲区读取下一个字符，效率更佳；

  ```c++
  ifstream inputFile("interestingData.txt");
  string fileData((istreambuf_iterator<char>(inputFile)), istreambuf_iterator<char>()); // istreambuf_iterator不会跳过任何字符（包括空格）
  ```

[返回顶部](#C++最佳实践)



### 17.尽量使用封装技术

- 尽量使用封装（encapsulation）技术来将一种容器类型转换到另一种;

  ```c++
  class Widget {...};
  typedef vector<Widget> WidgetContainer;
  typedef WidgetContainer::iterator WCIterator; // 封装
  WidgetContainer cw;
  Widget bestWidget;
  ...
  WCIterator i = find(cw.begin(), cw.end(), bestWidget);
  ```

- 把容器隐藏在一个类中，并尽量减少那些通过类接口（而使外部）可见的，与容器相关的信息，来减少在替换容器类型时所需要修改的代码；

  ```c++
  class CustomerList {
  private:
    typedef list<Customer> CustomerContainer;
    typedef CustumorContainer::iterator CCIterator;
    
    CustomerContainer customers; // 隐藏容器，通过对外接口访问
  public:
    ...
  };
  ```

[返回顶部](#C++最佳实践)



### 18.使用erase-remove方法完全删除元素

- remove不是真正意义上的删除，用remove删除元素，它只是移动被删除的元素到容器**尾部**，而容器中的元素数目并不会减少；

  ```c++
  vector<int> v;
  v.reserve(10);
  for (int i = 1; i <= 10; ++i)
      v.push_back(i);
  
  cout << v.size();               // 输出10
  v[3] = v[5] = v[9] = 99;
  remove(v.begin(), v.end(), 99); // 删除所有值等于99的元素
  cout << v.size();               // 依然输出10
  ```

- 当容器中存放的是指向动态分配的对象的指针的时候，应该避免使用remove和类似的算法（remove_if，unique），因为这样会造成内存泄漏；

  ```c++
  class Widget {
  public:
      bool isCertified() const;
  };
  vector<Widget*> v;
  v.push_back(new Widget);
  
  v.erase(remove_if(v.begin(), v.end(), fun(&Widget::isCertified)), v.end()); // 内存泄漏
  ```

- 推荐使用erase与remove合作（erase-remove）来真正删除元素；

  ```c++
  vector<int> v;
  v.reserve(10);
  for (int i = 1; i <= 10; ++i)
      v.push_back(i);
  
  cout << v.size();                        // 输出10
  v[3] = v[5] = v[9] = 99;
  v.erase(remove(v.begin(), v.end(), 99)); // 删除remove函数返回的迭代器所指向的元素
  cout << v.size();                        // 输出7
  ```

[返回顶部](#C++最佳实践)



### 19.使用函数对象而不是函数作为STL算法的参数

- 将函数对象（即可以被伪装成函数的对象）传递给STL算法往往比传递实际的函数更加高效；

  ```c++
  vector<double> v;
  
  sort(v.begin(), v.end(), greater<double>()); // 使用函数对象做参数（高效）
  
  inline bool doubleGreater(double d1, double d2) { return d1 > d2; }
  sort(v.begin(), v.end(), doubleGreater); // 使用函数做参数（低效）
  ```

- 由于编译器或STL的问题，有时候用函数做参数可能会编译不过；

  ```c++
  set<string> s;
  
  // 用函数做参数，可能无法通过编译
  transform(s.begin(), s.end(), ostream_iterator<string::size_type>(count, "\n"), mem_fun_ref(&string::size));
  
  // 用函数对象做参数
  struct StringSize : public unary_function<string, string::size_type> {
      string::size_type operator()(const string& s) const
      {
          return s.size();
      }
  };
  transform(s.begin(), s.end(), ostream_iterator<string::size_type>(count, "\n"), StringSize());
  ```

- 使用函数对象做参数有助于避免一些语言本身的缺陷;

  用函数做参数在语法上没问题，但是有些情况下STL不支持：

  ```c++
  template<typename FPType>
  FPType average(FPType val1, FPType val2)
  {
      return (val1 + val2) / 2;
  }
  template<typename InputIter1, typename InputIter2>
  void writeAverages(InputIter1 begin1, InputIter1 end1, InputIter2 begin2, ostream& s)
  {
      transform(begin1, end1, begin2, 
                ostream_iterator<typename iterator_traits<InputIter1>::value_type(s, "\n")>,
                average<typename iterator_traits<InputIter1>::value_type>); // STL标准不支持，因为它觉得有二义性
  }
  ```

- 函数指针和函数对象在函数之间按值传递（用class/struct包裹的函数例外）；

  ```c++
  // 将函数用class包裹时，强制按引用传递
  class DoSomething : public unary_function<int, void> {
  public:
      void operator()(int x) {...}
  };
  
  typedef deque<int>::iterator DequeIntIter;
  deque<int> di;
  DoSomething d; // 创建一个函数对象
  // 用类型参数DequeIntIter和DoSomething&来调用for_each，这将强制d按引用传递并返回
  for_each<DequeIntIter, DoSomething&>(di.begin(), di.end(), d); 
  ```

[返回顶部](#C++最佳实践)



### 20.容器的成员函数优先于同名的算法

- 成员函数往往速度快；
- 成员函数通常与容器（特别是关联容器）结合得更加紧密。

```c++
set<int> s;

set<int>::iterator i = s.find(727); // 使用find成员函数，速度更快
if (i != s.end())
    ...
    
set<int>::iterator i = find(s.begin(), s.end(), 727); // 使用find算法，速度慢
if (i != s.end())
    ...
```

[返回顶部](#C++最佳实践)



### 21.确保容器中的对象拷贝正确而高效

- 向容器中填充对象，而对象的拷贝又很费时时，这一操作会成为程序的性能瓶颈；

- 当存在继承关系时，向基类容器的拷贝动作会剥离派生类的信息（拷贝指针时可以避免这个问题）；

  ```c++
  vector<Widget> vw;
  class SpecialWidget : public Widget{...};
  SpecialWidget sw;
  vw.push_back(sw); // 派生类特有的部分在拷贝时被丢弃了
  ```

- 尽量避免不必要的拷贝；

  ```c++
  Widget w[n]; // 创建有n个Widget对象的数组，每个对象都使用默认构造函数来创建（浪费）
  vector<Widget> vw; // 创建了包含0个Widget对象的vector，当需要时它会增长（避免了拷贝）
  ```

[返回顶部](#C++最佳实践)

---



## 接口设计



[返回顶部](#C++最佳实践)

---



## 工具

TODO



---

## 参考

[1] Scott Meyers.Effective Modern C++

[2] Andrei Alexandrescu.C++ Coding Standard-101Rule Guideline And Best Practices.Herb Sutter.2016

[3] Herb·萨特.C++ Best Practices.Sutter.2005

[4] 侯捷.STL源码刨析.2003

[5] [美]Scott Meyers.Effective STL.1th Edition

[6] [C++ Core Guidelines](http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines?utm_source=wechat_session&utm_medium=social&utm_oi=974639756117843968#f7-for-general-use-take-t-or-t-arguments-rather-than-smart-pointers)

[7] [Modern C++中lambda表达式的陷阱](https://blog.csdn.net/czyt1988/article/details/80149695)

[8] [360 安全规则集合](https://github.com/Qihoo360/safe-rules)

