# C++最佳实践

[TOC]

## STL

TODO

## 现代C++

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

---

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

---

### 3正确使用decltype

- 绝大多数情况下，`decltype`会得出变量或表达式的型别而不做任何修改；

- 对于型别为T的左值表达式，除非该表达式仅有一个名字，`decltype`总是得出型别`T&`；

- c++14支持`decltype(auto)`，和auto一样，它会从其初始化表达式出发来推导型别，但是它的型别推导使用的是`decltype`的规则；

  ```c++
  Widget w;
  const Widget& cw = w;
  decltype(auto) myWidget2 = cw; // decltype型别推导：const Widget&
  ```

---

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

---

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

---

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

---

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

---

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

---

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
  

---

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

---

### 11优先选用cost_iterator

- 当迭代器指向的内容不需要修改时，优先选用const_iterator，而非iterator；

  ```c++
  std::vector<int> values;
  // 容器的成员函数`cbegin`,`cend`等都返回`const_iterator`型别
  auto it = std::find(values.cbegin(), values.cend(), 1983);
  values.insert(it, 1998);
  ```


---

### 12只要函数不会发射异常就加上noexcept声明

* 相对于不带noexcept声明的函数，带有noexcept声明的函数有更多机会得到优化；

  `noexcept`对函数的优化：优化器不需要在异常传出函数的前提下，将执行期栈保持在可开解状态；也不需要在异常逸出函数的前提下，保证所有其中的对象以其被构造顺序的逆序完成析构。

  ```c++
  RetType function(params) noexcept; // 最优化
  RetType function(params) trow();   // 优化不够
  RetType function(params);          // 优化不够
  ```

---

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

---

### 14保证const成员函数的线程安全性

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

---

### 15正确使用三大智能指针

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

---

### 16优先使用make系列函数而非直接使用new

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

---

### 17推荐使用Pimpl用法

pimpl（pointer to implementation，指涉到实现的指针）：把某类的数据成员用一个指涉到某实现类（或结构体）的指针替代，然后把原来在主类中的数据成员放置到实现类中，并通过指针间接访问这些数据成员

- Pimpl惯用法通过降低类的客户和类实现者之间的依赖性，减少了构建遍数；

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

---

### 18正确使用万能引用和右值引用

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

---

### 19正确使用std::move和std::forward

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
---

### 20完美转发的失败场景

完美转发的失败情形，是源于模板型别推到失败或推导结果是错误的类型；

完美转发失败的情形：

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

---

### 21正确使用lambda

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

---

### 22正确的并发操作

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

---

### 23正确使用容器

- 从原理上说，置入函数应该有时比对应的插入函数高效，而且不应该有更低效的可能；
- 从实践上说，置入函数在以下几个前提成立时，极有可能会运行的更快：
  1. 待添加的值是以构造h而非赋值方式加入容器；
  2. 传递的实参型别与容器持有之物的型别不同；
  3. 容器不会由于存在重复值而拒绝待添加的值；
- 置入函数可能会执行在插入函数中会被拒绝的型别转换；

---

## 参考

[1] Effective Modern C++.Scott Meyers

[2] C++ Coding Standard-101Rule Guideline And Best Practices.Herb Sutter, Andrei Alexandrescu.2016