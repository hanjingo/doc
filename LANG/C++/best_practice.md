# C++最佳实践

[TOC]

## Old C++

### 1尽量以const, enum, inline替换`#define`

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



### 2尽可能使用const

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

  



### 3确定对象被使用前已先被初始化

- 在变量定义时立即进行初始化；

  ```c++
  int a; // 不推荐
  int a = 1; // 推荐
  char s[2] = {'a', 'b'}; // 推荐
  ```

- C++对象的成员变量的初始化动作发生在进入构造函数本体之前，C++不保证初始化内置类型对象；



### 4了解C++编译器的小动作

- C++编译器私自为class创建default构造函数，copy构造函数，copy assignment操作符，以及析构函数；

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



### 5正确定义构造函数

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



### 6正确定义析构函数

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



### 7正确定义operator=

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

- 对底层资源使用“引用计数法”(reference-count)，抑制copying；



### 8正确定义成员变量

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



### 9小心重载

- 禁止重载`&&`,`||`或`,`



### 10防止资源泄漏

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

- 最好不要对数组形式做typedefs动作；

  - 如果你在new表达式中使用`[]`，必须要在相应的delete表达式中使用`[]`；
  - 如果你在new表达式中不使用`[]`，一定不要在相应的delete表达式中使用`[]`；
  
- C++需要保证删除null指针永远安全，即operator delete应该在收到null指针时不做任何事;

- 使用智能指针来保存动态分配的资源；

  TODO



### 11函数参数定义

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




### 12尽量避免类型转换

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



### 13谨慎使用inline函数

- 过度使用inline函数会造成代码膨胀；
- 将大多数inlining行为限制在小型，被频繁调用的函数身上；
- 一个inline函数是否真inline取决于编译器；
  - 有些编译器拒绝将太过复杂（例如带有循环或递归）的函数inlining;
  - 如果函数里调用了virtual函数，也会使inline失效；
- 不要仅仅因为函数定义在头文件，就将它们声明为inline；



### 14降低文件间的编译依赖关系

- 使用PIMPL(pointer to implementation, 指向实现的指针)将实现与定义分离；

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



### 15使用继承的一些注意点

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




### 16谨慎使用virtual函数

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



### 17typename与class的区别

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



### 18模版使用心得

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



### 19不要对类使用memcpy或memcmp操作

- memcpy和memcmp会扰乱类型系统；



[返回顶部](#C++最佳实践)

---

## New C++

### 1正确使用模版类型推导

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



### 2正确进行型别推导

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



### 3正确使用decltype

- 绝大多数情况下，`decltype`会得出变量或表达式的型别而不做任何修改；

- 对于型别为T的左值表达式，除非该表达式仅有一个名字，`decltype`总是得出型别`T&`；

- c++14支持`decltype(auto)`，和auto一样，它会从其初始化表达式出发来推导型别，但是它的型别推导使用的是`decltype`的规则；

  ```c++
  Widget w;
  const Widget& cw = w;
  decltype(auto) myWidget2 = cw; // decltype型别推导：const Widget&
  ```



### 4优先使用auto

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



### 5优先使用初始化列表

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

* 在构造函数重载决议期间，只要有任何可能，大括号初始化物就会与带有std::initializer_list型别的形参相匹配，即使其他重载版本有着貌似更加匹配的形参表；

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



### 6优先选用nullptr

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



### 7优先选用using而非typedef

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



### 8优先选用enum class

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



### 9优先选用delete

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



### 10优先使用override

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



### 11优先选用const_iterator

- 当迭代器指向的内容不需要修改时，优先选用const_iterator，而非iterator；

  ```c++
  std::vector<int> values;
  // 容器的成员函数`cbegin`,`cend`等都返回`const_iterator`型别
  auto it = std::find(values.cbegin(), values.cend(), 1983);
  values.insert(it, 1998);
  ```

[返回顶部](#C++最佳实践)




### 12只要函数不会发射异常就加上noexcept声明

* 相对于不带noexcept声明的函数，带有noexcept声明的函数有更多机会得到优化；

  `noexcept`对函数的优化：优化器不需要在异常传出函数的前提下，将执行期栈保持在可开解状态；也不需要在异常逸出函数的前提下，保证所有其中的对象以其被构造顺序的逆序完成析构。

  ```c++
  RetType function(params) noexcept; // 最优化
  RetType function(params) trow();   // 优化不够
  RetType function(params);          // 优化不够
  ```

[返回顶部](#C++最佳实践)



### 13尽可能使用constexpr

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



### 14正确使用三大智能指针

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



### 15优先使用make系列函数而非直接使用new

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



### 16正确使用万能引用和右值引用

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



### 17正确使用std::move和std::forward

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



### 18完美转发的失败场景

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



### 19正确使用lambda

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



### 20保证线程安全性

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

### 1数据结构的适用场景

| 数据结构           | 适用场景                                         |
| ------------------ | ------------------------------------------------ |
| vector             | 随机访问的情况，不适宜插入，删除等操作频繁的操作 |
| list               |                                                  |
| deque              |                                                  |
| stack              | 先进后出（一端进出），不允许遍历的情形           |
| queue              | FIFO（先进先出），不允许遍历的情形               |
| heap               |                                                  |
| priority queue     |                                                  |
| slist              |                                                  |
| binary search tree |                                                  |
| AVL tree           |                                                  |
| RB tree            |                                                  |
| set                |                                                  |
| map                |                                                  |
| multiset           |                                                  |
| multimap           |                                                  |
| hashtable          |                                                  |
| hash set           |                                                  |
| hash map           |                                                  |
| hash multiset      |                                                  |
| hash multimap      |                                                  |

[返回顶部](#C++最佳实践)



### 2使用置入函数(push_xx)来代替插入函数(insert_xx)

- 从原理上说，置入函数(`push_xx`)应该有时比对应的插入函数(`insert_xx`)高效，而且不应该有更低效的可能；
- 从实践上说，置入函数在以下几个前提成立时，极有可能会运行的更快：
  1. 待添加的值是以构造h而非赋值方式加入容器；
  2. 传递的实参类型与容器持有之物的型别不同；
  3. 容器不会由于存在重复值而拒绝待添加的值；
- 置入函数可能会执行在插入函数中会被拒绝的型别转换；

[返回顶部](#C++最佳实践)



### 3使用vector和string代替数组

vector和string的优点如下：

- 能够自动管理内存
- 具有丰富的接口
- 与C的内存模型兼容
- 更构提供更大范围的检查
- 效率还可以接受
- 有助于优化

[返回顶部](#C++最佳实践)



### 4使用范围操作来代替多次单元素操作

- `vector::invert(position, first, last)`的效率要大于多次调用`vector::insert(position, x)`，多次调用`vector::insert(position, x)`可能会导致多次内存重新分配；

[返回顶部](#C++最佳实践)



### 5使用STL算法调用代替手工编写的循环

- STL算法的效率经常要比手工编写的循环要高；

- STL算法的正确性比手工编写的循环要高；

  ```c++
  // 手工循环
  deque<double>::iterator current = d.begin();
  for(size_t i = 0; i < max; ++i) {
  	current = d.insert(current, data[i] + 41);
    ++current;
  }
  ```

  ```c++
  // STL算法
  std::transform(data, data + max, inserter(d, d.begin()), _1 + 41);
  ```

[返回顶部](#C++最佳实践)



### 6正确使用STL查找算法

- 对于无序范围，`find/find_if`和`count/count_if`都能以线性时间找到结果；但是`find/find_if`效率更高，因为在找到之后立即终止查找；
- 对于有序范围，应该使用二分查找算法，因为他们都是对数时间，常见的二分查找算法如下：
  - `binary_search`
  - `lower_bound`
  - `upper_bound`
  - `equal_range`

[返回顶部](#C++最佳实践)



### 7正确使用STL排序算法

- 排序算法开销排序如下：`partition < stable_partition < nth_element < partial_sort < sort < stable_sort`；

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

