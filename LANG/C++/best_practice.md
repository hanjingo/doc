English | [中文版](best_practice_zh.md)

# C++ Best Practice

[TOC]



## C++98

### 1.Prefer `const`, `enums` and `inlines` to `#define`

- For simple constants, prefer const objects or enums to `#defines`; because `#define` may be treated as if it's not part of the language per se.

  ```c++
  #define ASPECT_RATIO 1.653
  ```

  modified to：

  ```c++
  const double AspectRatio = 1.653;
  ```

- For function-like macros, prefer inline functions to `#defines`.

- Replace `#ifndef ... #define ... #endif` by `#pragma once`(C++11).

[TOP](#C++ Best Practice)



### 2.Use const whenever possible.

- Declaring something const helps compilers detect usage errors. const can be applied to objects at any scope, to function parameters and return types, and to member functions as a whole.
- When const and non-const member functions have essentially identical implementations, code duplication can be avoided by having the non-const version call the const version.
- Compilers enforce bitwise constness, but you should program using logical constness.

[TOP](#C++ Best Practice)



### 3.Make sure that objects are initialized before they're used.

- Base classes are initialized before derived classes, and within a class data members are initialized in the order in which they are declared.

[TOP](#C++ Best Practice)



### 4.Understand  the compiler

- Compilers may implicitly generate a class's default constructor, copy constructor, copy assignment operator, and destructor.

  ```c++
  class Empty {};
  ```

  coverts to:

  ```c++
  class Empty {
  public:
    Empty() { ... }                 // default constructor
    Empty(const Empty& rhs) { ... } // copy constructor
    ~Empty() { ... }                // destructor
    Empty& operator=(const Empty& rhs) { ... } // copy assignment operator
  };
  ```

- To disallow functionality automatically provided by compilers, declare the corresponding member functions `private` and give no implementations. Using a base class like `Uncopyable` is one way to do this.

  ```c++
  class HomeForSale {
  public:
    ...
  private:
    ...
    HomeForSale(const HomeForSale&); // declarations only
    HomeForSale& operator=(const HomeForSale&); // declarations only
  }
  ```

[TOP](#C++ Best Practice)



### 5.Define constructor correctly

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

[TOP](#C++ Best Practice)



### 6.Define destructor correctly

- Polymorphic base classes should declare virtual destructors. If a class has any virtual functions, it should have a virtual destructor.

- Give the base class a virtual destructor. Then deleting a derived class object will do exactly what you want. It will destroy the entire object, including all its derived class parts:

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

- **Destructors should never emit exceptions.**

- **Never call virtual functions during construction or destruction.**

  Don't call virtual functions during construction or destruction, because such calls will never go to a more derived class than that of the currently executing constructor or destructor.

  ```c++
  class Transaction {
  public:
    Transaction()
    { init(); }
    virtual void logTransaction() const = 0;
  private:
    void init()
    {
    	logTransaction(); // call virtual function，incorrect
    }
  };
  ```

[TOP](#C++ Best Practice)



### 7.Defined operator= correctly

- Make sure operator= is well-behaved when an object is assigned to itself. Techniques include comparing addresses of source and target objects, careful statement ordering, and copy-and-swap.

  ```c++
  w = w; 		 // assignment to self
  a[i] = a[j]; // potential assignment to self
  *px = *py; 	 // potential assignment to self
  ```
  
  solution:

  ```c++
  Widget& Widget::operator=(const Widget& rhs)
  {
  	Widget temp(rhs); // make a copy of rhs's data
    	swap(temp);       // swap *this's data with the copy's
  	return *this;
  }
  ```
  
- Copying functions should be sure to copy all of an object's data members and all of its base class parts.

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

- Have assignment operators return a reference to `*this`.

  ```c++
  class Widget {
  public:
    Widget& operator=(const Widget& rhs) // return type is a reference to the current class
    {
    	return* this; // return the left-hand object
    }
    Widget& operator+=(const Widget& rhs) // the convention applies to +=, -=, *=, etc.
    {
    	return *this;
    }
    Widget& operator=(int rhs)
    {
    	return *this;
    }
  };
  ```

- In many cases, it makes no sense to allow RAII objects to be copied.

- Reference-count the underlying resource.

[TOP](#C++ Best Practice)



### 8.Defined member correctly

- Prefer non-member non-friend functions to member functions. Doing so increases encapsulation, packaging flexibility, and functional extensibility.

  ```c++
  class WebBrowser {
  public:
      void clearEverything();
  }
  ```

  Better way:

  ```c++
  namespace WebBrowserStuff {
      class WebBrowser { ... };
      void clearBrowser(WebBrowser& wb);
  };
  ```

- Whenever you can avoid friend functions, you should, because, much as in real life, friends are often more trouble than they're worth.

- Make `operator*` a non-member function, thus allowing compilers to perform implict type conversions on all arguments:

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

[TOP](#C++ Best Practice)



### 9.Becareful about overload

- Never overload `&&`, `||` or `,`.

[TOP](#C++ Best Practice)



### 10.Avoid resource leak

- 推荐自定义new和delete来替换编译器的operator new和operator delete；

- Use RAII objects to manage resources.

  `Resource Acquisition Is Initialization (RAII)` is so common to acquire a resource and initialize a resource-managing object in the same statement.

- 成对使用new和delete；

  使用typedef时必须要说清楚，当以new创建该种typedef类型对象时，应该以哪种delete方式删除；

  ```c++
  typedef std::string AddressLines[4];
  std::string* pal = new AddressLines;
  
  delete pal; // undefined!
  delete [ ] pal; // fine
  ```

- When you write a placement version of operator new, be sure to write the corresponding placement version of operator delete. If you don't, your program may experience subtle, intermittent memory leaks.

- Abstain from `typedefs` for array types.

  - If you use `[]` in a new expression, you must use `[]` in the corresponding `delete` expression.
  - If you don't use `[]` in a new expression, don't use `[]` in the matching `delete` expression.
  
- Operator delete should do nothing if passed a pointer that is null. Class-specific versions should handle blocks that are larger than expected.

- Store newed objects in smart pointers in standalone statements. Failure to do this can lead to subtle resource leaks when exceptions are thrown.

[TOP](#C++ Best Practice)




### 11.Param define

- C++ compilers are granted considerable latitude in determining the order in which these things are to be done.

  ```c++
  void f(int, int);
  int a = 5;
  f(++a, ++a); // unknow order
  ```
  
- 始终使用const限制所有指向只输入参数的指针和引用；

- If you have an object of a built-in type (e.g., an int), it's often mroe efficient to pass it by value than by reference.

- The only types for which you can reasonably assume that pass-by-value is inexpensive are built-in types and STL iterator and function object types. For everything else, follow the advice of this item and prefer pass-by-reference-to-const over pass-by-value.

  ```c++
  void printNameAndDisplay(Window w) // incorrect! parameter may be sliced!
  {
      std::cout << w.name();
      w.display();
  }
  WindowWithScrollBars wwsb;
  printNameAndDisplay(wwsb);
  
  void printNameAndDisplay(const Window& w) // pass-by-reference
  {
      std::cout << w.name();
      w.display();
  }
  ```
  
- Avoid returning handles (references, pointers, or iterators) to object internals. Not returning handles increases encapsulation, helps const member functions act const, and minimizes the creation of dangling handles.

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

- Do not use C style varargs `...`；

[TOP](#C++ Best Practice)




### 12.Avoid type conversion

- Avoid casts whenever practical, especially dynamic_casts in performance-sensitive code. If a design requires casting, try to develop a cast-free alternative.

- When casting is necessary, try to hide it inside a function. Clients can then call the function instead of putting casts in their own code.

- Prefer C++ style casts to old-style casts. They are easier to see, and they are more specific about what they do.

  c-style casts:

  - `(T)expression`
  - `T(expression)`

  c++-style casts:

  - `const_cast<T>(expression)`
  - `dynamic_cast<T>(expression)`
  - `reinterpret_cast<T>(ecpression)`
  - `static_cast<T>(expression)`
  
- Implicit type conversions is generally a bad idea. You should avoid that by:

  - using `explicit`

    ```c++
    class Widget {
    	explicit Widget(unsigned int widgetizationFactor);
    };
    ```

  - Implace conversion operator by naming function

    ```c++
    class String {
      const char* as_char_pointer() const;
    };
    ```

[TOP](#C++ Best Practice)



### 13.Becareful about inline function.

- Inline could increase the size of your object code.
- Limit most inlining to small, frequently called functions. This facilitates debugging and binary upgradability, minimizes potential code bloat, and maximizes the chances of greater program speed.
- `inline` is a request that compilers may ignore
  - Most compilers refuse to inline functions they deem too complicated.
  - All but the most trivial calls to virtual functions defy inlining.
- Don't declare function templates inline jsut because they appear in header files.

[TOP](#C++ Best Practice)



### 14.Minimize compilation dependencies between files.

- Use `PIMPL(pointer to implementation)` to separate the dependencies on definitions and declarations.

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
      std::shared_ptr<Impl> pImpl; // use smart pointer
  };
  ```

  ```c++
  // Widget.cpp
  #include "widget.h"
  
  struct Widget::Impl { ... };
  Widget::~Widget() = delete;
  Widget::Widget(const Widget& rhs) : pImpl(std::make_unique<Impl>(*rhs.pImpl)) {}// copy constructor
  Widget& Widget::operator=(const Widget& rhs) // copy operator =
  {
      *pImpl = *rhs.pImpl;
      return *this;
  }
  ```

- The general idea behind minimizing compilation dependencies is to depend on declarations instead of definitions. Two approaches based on this idea are Handle classes and Interface classes.

- Library header files should exist in full and declaration-only forms. This applies regardless of whethre templates are involved.

[TOP](#C++ Best Practice)



### 15.Inheritance usage

- Use composition whenever you can, and use private inheritance whenever you must.

- Names in derived classes hide names in base classes. Under public inheritance, this is never desirable.

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

- Differentiate between inheritance of interface and inheritance of implementation.

  - Pure virtual functions specify inheritance of interface only.

    ```c++
    class Shape{
    public:
        virtual void draw() const = 0;
    }
    ```

  - Simple (impure) virtual functions specify inheritance of interface plus inheritance of a default implementation.

    ```c++
    class Shape{
    public:
        virtual void error(const std::string& msg);
    }
    ```
	
- Never redefine an inherited default parameter value, because default parameter values are statically bound, while virtual functions - the only function you should be redefining - are dynamically bound. 

- Private inheritance means is-implemented-in-terms of. It's usually inferior to composition, but  it makes sense when a derived class needs access to protected base class members or needs to redefine inherited virtual functions.

- Multiple inheritance is more complex than single inheritance. It can lead to new ambiguity issues and to the need for virtual inheritance.

- Virtual inheritance imposes costs in size, speed, and complexity of initialization and assignment. It's most practical when virtual base classes have no data.

- Multiple inheritance does have legitimate uses. One scenario involves combining public inheritance from an Interface class with private inheritance from a class that helps with implementation.

[TOP](#C++ Best Practice)




### 16.Virtual function usage

- Alternatives to virtual functions include:

  - non-virtual interface(NVI)

    The template Method Pattern via the Non-Virtual Interface Idiom.

    ```c++
    class GameCharacter {
    public:
        int healthValue() const
        {
            int retVal = doHealthValue();
            return retVal;
        }
    private:
        virtual int doHealthValue() const { ... } // derived classes may redefine this
    };
    ```

  - Strategy design pattern

    The Strategy Pattern via Function Pointers.

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

[TOP](#C++ Best Practice)



### 17.Difference between typename and class

- When declaring a template type parameter, `class` and `typename`

  ```c++
  template<class T> class Widget;    // uses "class"
  template<typename T> class Widget; // uses "typename"
  ```

- `typename` should be used to identify only nested dependent type names; other names shouldn't have it.

  ```c++
  template<typename C>                // tyepname allowed (as is "class")
  void f(const C& container,          // tyepname not allowed
         typename C::iterator iter);  // typename required
  ```

- `typename` must not precede nested dependent type names in a list of base classes or as a base class identifier in a member initialization list.

  ```c++
  template<typename T>
  class Derived: public Base<T>::Nested { // base class list: typename not allowed
  public: 
      explicit Derived(int x) : Base<T>::Nested(x) // base class identifier in men. ini, list: typename not allowed
      {
          typename Base<T>::Nested temp; // typename allowed
          ...
      }
  }
  ```

[TOP](#C++ Best Practice)



### 18.Template usage

- Know how to access names in templatized base classes.

  1. You can preface calls to base class functions with `this->`

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

  2. Use `using`

     ```c++
     template<typename Company>
     class LoggingMsgSender: public MsgSender<Company> {
     public:
         using MsgSender<Company>::sendClear; // tell compilers to assume that sendClear is in the base class
         void sendClearMsg(cosnt MsgInfo& info)
         {
             sendClear(info);
         }
     };
     ```

  3. Get your code to compile is to explicitly specify that the function being called is in the base class

     ```c++
     template<typename Company>
     class LoggingMsgSender: public MsgSender<Company> {
     public:
         void sendClearMsg(const MsgInfo& info)
         {
             MsgSender<Company>::sendClear(info); // okay,assumes that sendClear will be inherited
         }
     }
     ```

- Non-template code could make code expand

  ```c++
  teplate<typename T, std::size_t n>
  class SquareMatrix {
  public:
      void invert();
  };
  
  SquareMatrix<double, 5> sm1;  // call SquareMatrix<double, 5>::invert
  sm1.invert();
  
  SquareMatrix<double, 10> sm2; // call SquareMatrix<double, 10>::invert
  sm2.invert();
  ```

[TOP](#C++ Best Practice)



### 19.Do not use memcpy or memcmp in class

- Memcpy and memcmp can destrube type system.

[TOP](#C++ Best Practice)

---



## C++ 11 and above

### 1.Understand template type deduction.

- During template type deduction, arguments that are references are treated as non-references, i.e., their reference-ness is ignored. For example:

  ```c++
  template<typename T>
  void f(T& param);
  int x = 27;
  const int cx = x;
  const int& rx = x;
  // The deduced types for param and T in various calls are as follows:
  f(x);   // T is int, param's type is int&
  f(cx);  // T is const int, param's type is const int&
  f(rx);  // T is const int, param's type is const int&
  ```

- When decuding types for universal reference parameters, lvalue arguments get special treatment.

  ```c++
  template<typename T>
  void f(T&& param);
  int x = 27;
  const int cx = x;
  const int& rx = x;
  f(x);   // x is lvalue, so T is int&, param's type is also int& 
  f(cx);  // cx is lvalue, so T is const int&, param's type is also const int&
  f(rx);  // rx is lvalue, so T is const int&, param's type is also const int&
  f(27);  // 27 is rvalue, so T is int, param's type is therefore int&&
  ```

- When deducing types for by-value parameters, const and/or volatile arguments are treated as non-const and non-volatile.

  ```c++
  template<typename T>
  void f(T param);
  const char* const ptr = "abc";  // ptr is const pointer to const object
  f(ptr);                         // pass arg of type const char* const
  ```

- During template type deduction, arguments that are array or function names decay to pointers, unless they're used to initialize references.

  ```c++
  void someFunc(int, double);
  template<typename T>
  void f1(T param);
  f1(someFunc);   // param deduced as ptr-to-func type is void(*)(int, double)
  
  template<typename T>
  vid f2(T& param);
  f2(someFunc);   // param deduced as ref-to-func; type is void(&)(int, double)
  ```



### 2.Understand auto type deduction

- auto type deduction is usually the same as template type deduction, but auto type deduction assumes that a braced initializer represents a std::initializer_list, and template type deduction doesn't.

  ```c++
  auto x = { 11, 23, 9 }; // s's type is std::initializer_list<int>
  
  template<typename T>    // template with parameter declaration equivalent to x's declaration
  void f(T param);
  f({ 11, 23, 9 });       // error! can't deduce type for T
  ```

- auto in a function return type or a lambda parameter implies template type deduction, not auto type deduction.

  ```c++
  std::vector<int> v;
  ...
  auto resetV = [&v](const auto& newValue) { v = newValue; }; // c++14
  ...
  resetV({ 1, 2, 3 });    // error! can't deduce type for {1, 2, 3}
  ```



### 3.Understand decltype

- decltype almost always yields the type of a variable or expression without any modifications.

- For lvalue expressions of type T other than names, decltype always report a type of T&.

- C++14 supports `decltype(auto)`, which, like auto, deduces a type from its initializer, but it performs the type deduction using the decltype rules.

  ```c++
  Widget w;
  const Widget& cw = w;
  decltype(auto) myWidget2 = cw; // decltype type deduction: const Widget&
  ```



### 4.Prefer auto

* auto variables must be initialized, are generally immune to type mismatches that can lead to portability or efficiency problems, can ease the process of refactoring, and typically require less typing than variables with explicitly specified types.

  ```c++
  int x1;      // potentially uninitialized
  auto x2;     // error! initializer required
  auto x3 = 0; // fine, x's value is well-defined
  auto derefLess = [](const auto& p1, const auto& p2) { return *p1 < *p2; }; // comparison func.
  ```

* "Invisible" proxy types can cause auto to deduce the "wrong" type for an initializing expression.

  ```c++
  std::vector<bool> features(const Widget& w);
  Widget w;
  auto highPriority = features(w)[5]; // highPriority is std::vector<bool>::reference type
  ```

* The explicitly typed initializer idiom forces auto to deduce the type you want it to have.

  ```c++
  std::vector<bool> features(const Widget& w);
  Widget w;
  auto highPriority = static_cast<bool>(features(w)[5]); // force deduce highPriority to bool
  ```

- Use `decltype` and `std::forward` for `auto&&` params;

  ```c++
  auto f = [](auto&& param) { 
      return func(normalize(std::forward<decltype(param)>(param)));
  };
  ```

[TOP](#C++ Best Practice)



### 5.Using {} when creating objects

* Braced initialization is the most widely usable initialization syntax, it prevents narrowing conversions, and it's immune to C++'s most vexing parse.'

  ```c++
  std::vector<int> v{ 1, 3, 5 };
  class Widget {
  private:
      int x{ 0 }; // fine, x's default value is 0
      int y = 0;  // also fine
      int z(0);   // error!
  };
  ```

* During constructor overload resolution, braced initializers are matched to `std::initializer_list` parameters if at all possible, even if other constructors offer seemingly better matches.

  ```c++
  class Widget {
  pubic:
      Widget(int i, bool b);
      Widget(int i, double d);
      Widget(std::initializer_list<long double> il);
  };
  Widget w1(10, true); // uses parens and, as before, calls first ctor
  Widget w2{10, true}; // uses braces, but now calls std::initializer_list ctor(10 and true convert to long double)
  Widget w3(10, 5.0);  // uses parens and, as before, calls second ctor
  Widget w4{10, 5.0};  // uses braces, but now calls std::initializer_list ctor (10 and 5.0 convert to long double)
  ```

[TOP](#C++ Best Practice)



### 6.Prefer nullptr to 0 and NULL.

* Prefer nullptr to 0 and NULL;

* Avoid overloading on integral and pointer types.

  ```c++
  void f(int);
  void f(bool);
  void f(void*);
  f(0);       // calls f(int), not f(void*)
  f(NULL);    // might not compile, but typically calls f(int). Never calls f(void*)
  f(nullptr); // calls f(void*) overload
  ```

[TOP](#C++ Best Practice)



### 7.Prefer alias declarations (using) to typedefs

* `typedef` and `using` has the same function.

  ```c++
  typedef void (*FP)(int, const std::string&);  // typedef
  using FP = void (*)(int, const std::string&); // alias declaration
  ```

* `typedef` don't support templatization, but alias declarations do.

  ```c++
  // typedef
  template<typename T>
  struct MyAllocList {
      typedef std::list<T, MyAlloc<T>> type;   // synonym for std::list<T, MyAlloc<T>>
  };
  MyAllocList<Widget>::type lw;
  ```
  
  ```c++
  // alias declaration
  template<typename T>
  using MyAllocList = std::list<T, MyAlloc<T>>; // synonym for std::list<T, MyAlloc<T>>
  MyAllocList<Widget> lw;
  ```

[TOP](#C++ Best Practice)



### 8.Prefer enum class

* Scoped enums reduce namespace pollution.

  ```c++
  enum class Color { black, white, red }; // black,white,red are scoped to Color
  auto white = false;     // fine, no other "white" in scope
  Color c = white;        // error! no enumerator named "white" is in this scope
  Color c = Color::white; // fine
  auto c = Color::white;  // also fine
  ```

* Enumerator of scoped enums are visible only within the enum. They convert to other types only with a cast.

  ```c++
  // unscoped enum
  enum Color { black, white, red }; 
  std::vector<std::size_t> primeFactors(std::size_t x);
  Color c = red;
  if(c < 14.5) {
      auto factors = primeFactors(c);
  }
  ```

  ```c++
  // enum is now scoped
  enum class Color { black, white, red };
  Color c = Color::red;
  if (c < 14.5) {                     // error! can't compare Color and double
      auto factors = primeFactors(c); // error! can't pass Color to function expecting std::size_t
  }
  ```

* Both scoped and unscoped enums support the specification of the underlying type. The default underlying type for scoped enums is int. Unscoped enums have no default underlying type.

* Scoped enums may always be forwar-declared. Unscoped enums may be forward-declared only if their declaration specifies an underlying type.

  ```c++
  enum Color;       // error
  enum class Color; // fine
  ```

[TOP](#C++ Best Practice)



### 9.Prefer deleted functions

* Prefer deleted functions to private undefined ones.

  ```c++
  // private not defined function
  template <class charT, class traits = char_traits<charT> >
  class basic_ios : public ios_base {
  public:
  		...
  private:
      basic_ios(const basic_ios&);            // not defined
      basic_ios& operator=(const basic_ios&); // not defined
  };
  ```

  ```c++
  // delete function
  template <class charT, class traits = char_traits<charT> >
  class basic_ios : public ios_base {
  public: // declare
      basic_ios(const basic_ios&) = delete;
      basic_ios& operator=(const basic_ios&) = delete;
  }
  ```

* Any function may be deleted, including non-member functions and template instantiations.

  ```c++
  // c++11 delete function
  class Widget {
  public:
      template<typename T>
      void processPointer(T* ptr) { ... }
  };
  template<>
  void Widget::processPointer<void>(void*) = delete; // still public, but deleted
  ```
  
  ```c++
  // c++98 private not defined function
  class Widget {
  public:
      template<typename T>
      void processPointer(T* ptr) { ... }
  private:
      template<> // might not compile
      void processPointer<void>(void*);
  };
  ```
  

[TOP](#C++ Best Practice)



### 10.Declare overriding functions override

- Member function reference qualifiers make it possible to treat lvalue and rvalue objects (*this) differently.

- For overriding to occur, several requirements must be met:

  - The base class function must be virtual.
  - The base and derived function names must be identical (except in the case of destructors).
  - The parameter types of the base and derived functions must be identical.
  - The constness of the base and derived functions must be identical.
  - The return types and exception specifications of the base and derived functions must be compatible
  - (C++11 adds)The functions' `reference qualifiers`(&, && ...) must be identical.

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

[TOP](#C++ Best Practice)



### 11.Prefer const_iterators to iterators

- Prefer const_iterators to iteratos.

  ```c++
  std::vector<int> values;
  // member function `cbegin`,`cend` return `const_iterator`
  auto it = std::find(values.cbegin(), values.cend(), 1983);
  values.insert(it, 1998);
  ```

[TOP](#C++ Best Practice)




### 12.Declare functions noexcept if they won't emit exceptions.

* noexcept is part of a function's interface, and that means that callers may depend on it.

* noexcept functions are more optimizable than non-noexcept function.

* noexcept is particularly valuable for the move operations, swap, memory deallocation functions, and destructors.

* Most functions are exception-neutral rather than noexcept.

  ```c++
  RetType function(params) noexcept; // most optimizable
  RetType function(params) trow();   // less optimizable
  RetType function(params);          // less optimizable
  ```

[TOP](#C++ Best Practice)



### 13.Use constexpr whenever possible.

- constexpr objects are const and are initialized with values known during compilation.

  ```c++
  constexpr auto arraySize2 = 10;    // fine, 10 is a compile-time constant
  ```

- constexpr functions can produce compile-time results when called with arguments whose values are known during compilation.

  ```c++
  int sz; // non-constexpr variable
  
  constexpr auto arraySize1 = sz;    // error! sz's value not known at compilation
  std::array<int, sz> data1;         // error! same problem
  constexpr auto arraySize2 = 10;    // fine, 10 is a compile-time constant
  std::array<int, arraySize2> data2; // fine, arraySize2 is constexpr
  
  // Note that const doesn't offer the same guarantee as constexpr, because const objects need not be initialized with values known during compilation
  int sz; 					   // as before
  const auto arraySize = sz; 	     // find, arraySize is const copy of sz
  std::array<int, arraySize> data; // error! arraySize's value not known at compilation
  ```

- In C++11, constexpr functions may contain no more than a single executable statement: a return.

  ```c++
  constexpr int pow(int base, int exp) noexcept
  {
      return (exp == 0 ? 1 : base * pow(base, exp - 1));
  }
  ```

[TOP](#C++ Best Practice)



### 14.Understand smartpointer

* Use `std::unique_ptr` for exclusive-ownership resource management.

  ```c++
  class Investment { ... };
  template<typename... Ts> makeInvestment(Ts&&... params);
  ```

* By default, resource destruction takes place via `delete`, but custom deleters can be specified. Stateful deleters and function pointers as deleters increase the size of `std::unique_ptr` objects.

  ```c++
  auto delInvmt1 = [](Investment* pInvestment) // custom deleter as stateless lambda
                   {
                      makeLogEntry(PInvestment);
                      delete pInvestment;
                   };
  template<typename... Ts>
  std::unique_ptr<Investmet, decltype(delInvmt1)> // return type has size of Investment*
  makeInvestment(Ts&&... args);
  
  void delInvmt2(Investment* pInvestment) // custom deleter as function
  {
      makeLogEntry(pInvestmenbt);         
      delete pInvestment;
  }
  template<typename... Ts>                // return type has size of Investment* plus at least size of function pointer!
  std::unique_ptr<Investment,
                  void (*)(Investment*)>
  makeInvestment(Ts&&... params);
  ```

* Use `std::shared_ptr` for shared-ownership resource management.

  ```c++
  auto customDeleter1 = [](Widget *pw){...};
  auto customDeleter2 = [](Widget *pw){...};
  std::shared_ptr<Widget> pw1(new Widget, customDeleter1);
  std::shared_ptr<Widget> pw2(new Widget, customDeleter2);
  ```

* Avoid creating `std::shared_ptrs` from variables of raw pointer type.

  ```c++
  class Widget {
  public:
    void process();
    ...
  };
  std::vector<std::shared_ptr<Widget> > processedWidgets;
  void Widget::process()
  {
  	processedWidgets.emplace_back(this); // add a raw pointer to a cotainer, this could cause undefined behavior 
  }
  ```

  to avoid this, we could do that:

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

* The rules for control block creation are used:

  - `std::make_shared` always creates a control block.
  - A control block is created when a `std::shared_ptr` is constructed from a unique-ownership pointer (i.e., a std::unique_ptr or std::auto_ptr).
  - When a `std::shared_ptr` constructor is called with a raw pointer, it creates a control block.
  
* The existence of the reference count has performance implications:

  - `std::shared_ptr`are twice size of a raw pointer.
  - Memory for the reference count must be dynamically allocated.
  - Increments and decrements of the reference count must be atomic.
  
* Use `std::weak_ptr` for `std::sahred_ptr` like pointers that can dangle.

  ```c++
  auto spw = std::make_shared<Widget>(); // after spw is constructed, the pointed-to Widget's ref count (RC) is 1.
  std::weak_ptr<Widget> wpw(spw) // wpw points to same Widget as spws. RC remains 1
  spw = nullptr; // RC goes to 0, and the Widget is destroyed wpw now dangles
  ```

[TOP](#C++ Best Practice)



### 15.Prefer `std::make_unique` and `std::make_shared` to direct use of new

- Compared to direct use of `new`, `make` functions eliminate soruce code duplication, improve exception safety, and, for `std::make_shared` and `std::allocate_shared`, generat code that's smaller and faster.

  ```c++
  auto upw1(std::make_unique<Widget>());    // with make func
  std::unique_ptr<Widget> upw2(new Widget); // without make func
  auto spw1(std::make_shared<Widget>());    // with make func
  std::shared_ptr<Widget> spw2(new Widget); // without make func
  
  void processWidget(std::shared_ptr<Widget> spw, int priority);
  int computePriority();
  processWidget(std::shared_ptr<Widget>(new Widget), computePriority()); // potential resource leak!
  processWidget(std::make_shared<Widget>(), computePriority());          // no potential resource leak
  
  std::shared_ptr<Widget> spw(new Widget); // memory allocation twice
  auto spw = std::make_shared<Widget>();   // memory allocation once
  ```

- For `std::shre_ptrs`, additional situations where `make` functions may be ill-advised include:

  1. classes with custom memory management.

     ```c++
     std::unique_ptr<Widget, decltype(widgetDeleter)> upw(new Widget, widgetDeleter);
     std::shared_ptr<Widget> spw(new Widget, widgetDeleter);
     ```

  2. systems with memory concerns, very large objects, and `std::weak_ptrs` that outlive the corresponding `std::shared_ptrs`；

[TOP](#C++ Best Practice)



### 16.Understand universal references and 

- If a function template parameter has type `T&&` for a deduced type `T`, or if an object is declared using `auto&&`, the parameter or object is a universal reference.

  ```c++
  template<typename T>
  void f(T&& param);  // universal reference
  std::vector<int> v;
  f(v); // error! can't bind lvalue to rvalue reference
  
  Widget&& var1 = Widget();
  auto&& var2 = var1; // universal reference
  ```

- If the form of the type declaration isn't precisely `type&&`, or if type deduction does not occur, `type&&` denotes an rvalue reference.

  ```c++
  void f(Widget&& param);         // rvalue reference
  Widget&& var1 = Widget();       // rvalue reference
  template<typename T>
  void f(std::vector<T>&& param); // rvalue reference
  ```

- Universal references correspond to rvalue references if they're initialized with rvalues. They correspond to lvalue references if they'are initialized with lvalue.

- Constraining templates via `std::enable_if` permits the use of universal references and overloading together, but it controls the conditions under which compilers may use the universal reference overloads.

  ```c++
  // incorrect example
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
  logAndAdd(petName); // copy lvalue into multiset
  logAndAdd(std::string("Persephone")); // move rvalue instead of copying it
  logAndAdd("Patty Dog"); // create std::string in multiset instead of copying a temporary std::string
  short nameIdx = 0;
  logAndAdd(nameIdx); // error! match universal reference here
  ```

  ```c++
  // use std::enable_if
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
    // ctor for std::strings and args convertible to std::strings
    explicit Person(T&& n) : name(std::forward<T>(n)) {
      static_assert(std::is_constructible<std::string, T>::value,
                  		"Parameter n can't be used to construct a std::string")
    }
    // ctor for integral args
    explicit Person(int idx) : name(nameFromIdx(idx)) {...}
    ...
  private:
    std::string name;
  };
  ```
  
- Universal reference parameters often have efficiency advantages, but they typically have usability disadvantages.

[TOP](#C++ Best Practice)



### 17.Understand std::move and std::forward

- `std::move` performs an unconditional cast to an rvalue. In and of itself, it doesn't move anything. `std::forward` casts its argument to an rvalue only if that argument is bound to an rvalue.

  ```c++
  void process(const Widget& lvalArg); // process lavlues
  void process(Widget&& rvalArg);      // process rvalues
  
  template<typename T> // template that passes param to process
  void logAndProcess(T&& param)
  {
      process(std::forward<T>(param));
  }
  ```

- To avoid paying for a copy operation when copying param into a data member, apply `std::move`.

  ```c++
  class Annotation {
  public:
      // "move" text into value; this code doesn't do what it seems to!
      explicit Annotation(const std::string text) : value(std::move(text)) 
      { ... }
  private:
      std::string value;
  };
  ```
  
- Use `std::move` on rvalue references, `std::forward` on universal references.

  ```c++
  class Widget {
  public:
    // rvalue references
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
    // universal references
    template<typename T>
    void setName(T&& newName) { name = std::forward<T>(newName); }
  }
  ```

- Never apply `std::move` or `std::forward` to local objects if they would otherwise be eligible for the return value optimization.

  ```c++
  Widget makeWidget()
  {
  	Widget w;
    ...
    return std::move(w); // move w into return value (don't do this!)
  }
  ```

- There are thuse several scenarious in which C++11's move semantics do you no good:

  1. `No move operations:` The object to be moved from fails to offer move operations. The move request therefore becomes a copy request.
2. `Move not faster:` The object to be moved from has move operations that are no faster than its copy operations.
  3. `Move not usable:` The context in which the moving would take place requires a move operation that emits no exceptions, but that operation isn't declared `noexcept`.

- For copyable, cheap-to-move parameters that are always copied, pass by value may be nearly as efficient as pass by reference, it's easier to implement, and it can generate less object code.

- Copying parameters via construction may be significantly more expensive than copying them via assignment.

- Pass by value is subject to the slicing problem, so it's typically inappropriate for base class parameter types.

[TOP](#C++ Best Practice)



### 18.Perfect forwarding fails

Perfect forwarding fails when template type deduction fails or when it deduces the wrong type. The kinds of arguments that lead to forwarding failure are:

- braced initializers.

  ```c++
  void f(const std::vector<int>& v);
  f({1, 2, 3});   // fine, "{1, 2, 3}" implicitly converted to std::vector<int>
  fwd({1, 2, 3}); // error! doesn't compile
  ```

- null pointers expressed as 0 or NULL.

  When you try to pass 0 or NULL as a null pointer to a template, type deduction goes awry, deducing an integral type (typically int) instead of a pointer type for the argument you pass.

- declaration-only integral `const static` data members.

  ```c++
  class Widget {
  public:
      static const std::size_t MinVals = 28; // MinVals' declaration
      ...
  };
  ...
  std::vector<int> widgetData;
  widgetData.reserve(Widget::MinVals) // use of MinVals
  void f(std::size_t val);
  f(Widget::MinVals);   // fine, treated as "f(28)"
  fwd(Widget::MinVals); // error! shouldn't link
  ```

- template and overloaded function names

  ```c++
  void f(int (*pf)(int));
  void f(int pf(int));
  int processVal(int value);
  int processVal(int value, int priority);
  
  f(processVal);       // fine
  fwd(processVal);     // error!
  
  template<typename T>
  T workOnVal(T param) // template for processing values
  { ... }
  
  fwd(workOnVal);                               // error! which workOnVal
  using ProcessFuncType = int (*)(int);         // make typedef
  ProcessFuncType processValPtr = processVal;   // specify needed signature for processVal
  fwd(processValPtr);                           // fine
  fwd(static_cast<ProcessFuncType>(workOnVal)); // also fine
  ```

- bitfields

  ```c++
  struct IPv4Header {
      std::uint32_t version:4,
                    IHL:4,
                    DSCP:6,
                    ECH:2,
                    totalLength:16;
      ...
  };
  
  void f(std::size_t sz); // function to call
  IPv4Header h;
  ...
  f(h.totalLength); // fine
  fwd(h.totalLength); // error!
  ```

[TOP](#C++ Best Practice)



### 19.Understand Lambda

- Avoid default capture modes.

  Default by-reference capture can lead to dangling references. Default by-value capture lures you into thinking you're immune to that problem (you're not), and it lulls you into thinking your closures are self-contained (they may not be).

  ```c++
  // Default by-reference capture
  auto divisor = computeDivisor(calc1, calc2);
  filters.emplace_back([&](int value) { return value % divisor == 0; }); // danger! ref to divisor will dangle!
  ```

  ```c++
  // Default by-value capture
  static auto divisor = computeDivisor(calc1, calc2);
  filter.emplace_back([=](int value) { return value % divisor == 0; }); // now divisor can't dangle
  ++divisor; // divisor been modified
  ```

- Use init capture to move objects into closures.

  ```c++
  auto func = [pw = std::move(pw)] {...}               // init data mbr in closure std::move(pw)
  auto func1 = [pw = std::make_unique<Widget>()] {...} // init data mbr in closure result of call to make_unique
  auto func2 = std::bind( // c++11 emulation of init capture for mutable lambda
    [](std::vector<double>& data) mutable { ... }, 
    std::move(data) );
  ```

- The most important reason to prefer lambdas over `std::bind` is that lambdas are more readable.

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

[TOP](#C++ Best Practice)



### 20.Ensure thread safety

- Use `std::atomic` can get better performance compare with `std::mutex`.

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

- Specify `std::launch::async` if asynchronicity is essential.

  ```c++
  auto f = std::async(std::launch::async | std::launch::deferred, // run f either async or deferred
                      f);
  ```

- Join-on-destruction can lead to difficult-to-debug performance anomalies and undefined behavior.

  ```c++
  class ThreadRAII {
  public:
    enum class DtorAction { join, detach }; // enum class
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

- Declare `std::thread` objects last in lists of data members.

- 考虑针对一次性事件通信使用以void为模板型别实参的期值；

  ```c++
  std::promise<void> p;
  void detect()                               // now for multiple reacting tasks
  {
      auto sf = p.get_future().share();       // sf's type is std::shared_future<void>
      std::vector<std::thread> vt;            // container for reacting threads
      for (int i = 0; i < threadsToRun; ++i ) {
          vt.emplace_back([sf]{ sf.wait(); react(); }); // wait on local copy of sf
      }
      ...                                     // detect hangs if this "..." code throws!
      p.set_value();                          // unsuspend all threads
      ...
      for (auto& t : vt)                      // make all threads unjoinable
          t.join();
  }
  ```

- Use `std::atomic` for concurrency, volatile for special memory.

[TOP](#C++ Best Practice)



---



## API Design

TODO

[TOP](#C++ Best Practice)

---



## Tools

TODO

[TOP](#C++ Best Practice)



---

## Reference

[1] Scott Meyers.Effective Modern C++

[2] Andrei Alexandrescu.C++ Coding Standard-101Rule Guideline And Best Practices.Herb Sutter.2016

[3] Herb·Sart.C++ Best Practices.Sutter.2005

[4] 侯捷.STL源码刨析.2003

[5] [美]Scott Meyers.Effective STL.1th Edition

[6] [C++ Core Guidelines](http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines?utm_source=wechat_session&utm_medium=social&utm_oi=974639756117843968#f7-for-general-use-take-t-or-t-arguments-rather-than-smart-pointers)

[7] [Modern C++中lambda表达式的陷阱](https://blog.csdn.net/czyt1988/article/details/80149695)

[8] [360 安全规则集合](https://github.com/Qihoo360/safe-rules)

