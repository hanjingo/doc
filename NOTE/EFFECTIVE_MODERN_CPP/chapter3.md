[TOC]

# 第三章 转向现代c++

## 条款7:在创建对象时注意区分()和{}
* 大括号初始化可以应用的语境最为宽泛，可以阻止隐式窄化型别转换，还对最令人苦恼之解析语法免疫。
* 在构造函数重载决议期间，只要有任何可能，大括号初始化物就会与带有std::initializer_list型别的形参相匹配，即使其他重载版本有着貌似更加匹配的形参表。
* 使用小括号还是大括号，会造成结果大相径庭的一个例子是：使用两个实参来创建一个std::vector<数值型别>对象。
* 在模板内容进行对象创建时，到底应该使用小括号还是大括号会成为一个棘手问题。

大括号初始化示例：

```c++
std::vector<int> v{ 1, 3, 5 }; // v的初始内容为1, 3, 5

class Widget {
private:
    int x{ 0 }; // 推荐
    int y = 0;  // 可行
    int z(0);   // 不可行
};

std::atomic<int> ai1{ 0 }; // 可行
std::atomic<int> ai2(0);   // 可行
std::atomic<int> ai3 = 0;  // 不可行

double x, y, z;
int sum1{ x + y + z }; // 错误！double型别之和可能无法用int表达
int sum2(x + y + z);   // 没问题
int sum3 = x + y + z;  // 没问题

Widget w1(10); // 调用Widget的构造函数，传入形参10
Widget w2();   // 最令人苦恼之介些语法现身！
               // 这个语句声明了一个名为w2，返回一个Widget型别对象的函数
Widget w3{};   // 调用没有形参的Widget构造函数
```

如果有一个或多个构造函数声明了任何一个具备`std::initializer_list`型别的行参，那么采用了大括号初始化语法的调用语句会强烈地优先选用带有`std::initializer_list`型别形参的重载版本。例：

```c++
class Widget {
pubic:
    Widget(int i, bool b);
    Widget(int i, double d);
    Widget(std::initializer_list<long double> il);
};
Widget w1(10, true); // 使用小括号
Widget w2{10, true}; // 使用大括号，调用的是带有std::initializer_list型别形参的构造函数
                     // (10和true被强制转换为long double)
Widget w3(10, 5.0);
Widget w4{10, 5.0};  // 使用大括号，调用的是带有std::initializer_list型别形参的构造函数
                     // (10和5.0倍强制转换为long double)
```

`std::initializer_list`的强制性：只有在找不到任何办法把大括号初始化物中的实参转换为`std::initializer_list`模版中的型别时，编译器才会退而去检查普通的重载决议，例：

```c++
class Widget {
public:
    Widget(int i, bool b);
    Widget(int i, double d);
    Widget(std::initializer_list<bool> il); // 容器元素型别现在是bool了
};

Widget w{10, 5.0};   // 错误！要求窄化型别转换
Widget w1(10, true); // 调用第一个构造函数
Widget w2{10, true}; // 调用第一个构造函数
Widget w3(10, 5.0);  // 调用第二个构造函数
Widget w4{10, 5.0};  // 调用第二个构造函数
```

一个对象既支持默认构造函数，又支持带有`std::initializer_list`型别形参的构造函数，当使用一对空的大括号来构造时，应该执行默认构造。例：

```c++
class Widget {
public:
    Widget(); // 默认构造函数
    Widget(std::initializer_list<int> il); // 带有std::initializer_list型别形参的构造函数
};

Widget w1;     // 调用的是默认构造函数
Widget w2{};   // 调用的仍然是默认构造函数
Widget w3();   // 变成了函数声明语句
Widget w4({}); // 带有std::initializer_list型别形参的构造函数
               // 传入一个空的std::initializer_list
Widget w5{{}};
```



## 条款8:优先选用nullptr，而非0或NULL
* 相对于0或NULL，优先选用nullptr。
* 避免在整型和指针型别之间重载。

`nullptr`无法视作任何一种整型，调用重载函数f时传入`nullptr`会调用`void*`的版本，例：

```c++
f(nullptr); // 调用的是f(void*)这个重载版本
```



## 条款9:优先选用别名声明，而非typedef
* typedef不支持模板化，但别名声明支持。
* 别名模板可以让人免写"::type"后缀，并且在模板内，对于内嵌typedef的引用经常要求加上typename前缀。

`typedef`和`using`的作用基本是一致的，例：

```c++
// FP的型别是一个指涉到函数的指针，该函数形参包括一个int和一个const std::string&，没有返回值
typedef void (*FP)(int, const std::string&);  // 使用typedef

// 和以上这句意义相同
using FP = void (*)(int, const std::string&); // 使用别名
```

`typedef`和`using`有以下区别：

- 别名声明可以模版化（别名模版，alias template），typedef不行。例：

```c++
// 使用别名
template<typename T>
using MyAllocList = std::list<T, MyAlloc<T>>; // std::list<T, MyAlloc<T>>的同义词
MyAllocList<Widget> lw;

// 使用typedef
template<typename T>
struct MyAllocList {
    typedef std::list<T, MyAlloc<T>> type;   // MyAllocList<T>::type是std::list<T, MyAlloc<T>>的同义词
};
MyAllocList<Widget>::type lw;
```



## 条款10:优先选用限定作用域的枚举型别，而非不限作用域的枚举型别
* c++98风格的枚举型别，现在称为不限范围的枚举型别。
* 限定作用域的枚举型别仅在枚举型别内可见。他们只能通过强制型别转换以转换至其他型别。
* 限定作用域的枚举型别和不限定范围的枚举型别都支持底层型别指定。限定作用域的枚举型别的默认底层型别是int，而不限范围的枚举型别没有默认底层型别。
* 限定作用域的枚举型别总是可以进行前置声明，而不限范围的枚举型别却只有在指定了默认底层型别的前提下才可以进行前置声明。

限定作用域的枚举型别，通过“enum class”来声明，例：

```c++
enum class Color { black, white, red }; // black,white,red所在作用域被限定在Color内

auto white = false;     // 没问题，范围内并无其它“white”
Color c = white;        // 错误！范围内并无名为“white”的枚举量
Color c = Color::white; // 没问题
auto c = Color::white;  // 没问题
```

应该选限定作用域枚举类型的理由：

1. 它降低了名字空间污染

2. 它的枚举量是更强型别的(strongly typed)，不限范围的枚举型别中的枚举量可以隐式转换到整数型别。例：

    不限范围型别枚举：

    ```c++
    enum Color { black, white, red }; // 不限定范围的枚举型别
    
    std::vector<std::size_t>          // 函数，返回x的质因数
        primeFactors(std::size_t x);
    
    Color c = red;
    
    if(c < 14.5) {
        auto factors = primeFactors(c);
    }
    ```
    
    限制范围型别枚举：

    ```c++
    enum class Color { black, white, red }; // 限定范围的枚举型别
    
    Color c = Color::red;
    
    if (c < 14.5) {                     // 错误！不能将Color型别和double型别比较
        auto factors = primeFactors(c); // 错误！不能讲Color型别传入
    }
    ```

    可以使用强制类型转换“限制范围型别枚举值”：

    ```c++
    if (static_cast<double>(c) < 14.5) { // 可以，有点嗦嗨
        auto factors = primeFactors(static_cast<std::size_t>(c)); // 可以
    }
    ```

当需要引用c++11中的`std::tuple`型别的各个域时，使用不限范围的枚举型别会比较简洁。例：

```c++
// 不限定范围
enum UserInfoFields { uiName, uiEmail, uiReputation };
UserInfo uInfo;
auto val = std::get<uiEmail>(uInfo); // 方便一点

// 限定范围
enum class UserInfoFields { uiName, uiEmail, uiReputation };
UserInfo uInfo;
auto val = std::get<static_cast<std::size_t>(UserInfoFields::uiEmail)>(uInfo); // 啰嗦
```



## 条款11:优先选用删除函数，而非private未定义函数
* 优先选用删除函数，而非private未定义函数。
* 任何函数都可以删除，包括非成员函数和模板具现。

如果想阻止其他人调用某个特定函数，有2种方法：

- private未定义函数

```c++
template <class charT, class traits = char_traits<charT> >
class basic_ios : public ios_base {
public:
		...
private:
    basic_ios(const basic_ios&);            // 未定义
    basic_ios& operator=(const basic_ios&); // 未定义
};
```

- 删除函数`delete`

```c++
template <class charT, class traits = char_traits<charT> >
class basic_ios : public ios_base {
public: // 习惯把delete函数声明为public
    basic_ios(const basic_ios&) = delete;
    basic_ios& operator=(const basic_ios&) = delete;
}
```

如何删除函数模版

```c++
// c++98
class Widget {
public:
    template<typename T>
    void processPointer(T* ptr) { ... }

private:
    template<> // 可能编译不过
    void processPointer<void>(void*);
};


// c++11
class Widget {
public:
    template<typename T>
    void processPointer(T* ptr) { ... }
};

template<>
void Widget::processPointer<void>(void*) = delete; // 仍然具备public访问权限，但被删除了
```



## 条款12:为意在改写的函数添加override声明
* 为意在改写的函数添加override声明。
* 成员函数引用饰词使得对于左值和右值对象(*this)的处理能够区分开来。

重写的一些基本条件：
- 基类中的函数必须是虚函数
- 基类和派生类中的函数名字必须完全相同（析构函数例外）
- 基类和派生类中的函数形参型别必须完全相同
- 基类和派生类中的函数常量性（constness）必须完全相同
- 基类和派生类中的函数返回值和异常规格必须兼容
- (c++11新增)基类和派生类中的函数引用饰词（reference qualifier，`&`, `&&` ...）必须完全相同。

例：

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

`override`的好处：

- 让编译器在想要改的函数实际上并未修改时提醒你
- 评估改写函数造成的影响



## 条款13:优先选用const_iterator,而非iterator
* 优先选用const_iterator,而非iterator。
* 在最通用的代码中,优先选用非成员函数版本的begin,end和rebegin等,而非其成员函数版本。

容器的成员函数`begin`,`cbegin`,`cend`等都返回`const_iterator`型别，例：

```c++
std::vector<int> values;
auto it =
    std::find(values.cbegin(), values.cend(), 1983); // 注意cbegin和cend
values.insert(it, 1998);
```

c++11添加了非成员函数`begin`和`end`，c++14添加了`cbegin`,`cend`,`rbegin`,`rend`,`crbegin`和`crend`，例：

```c++
template <typename C, typename V>
void findAndInsert(C& container,        // 在容器中查找targetVal
                   const V& targetVal,  // 第一次出现的位置
                   const V& insertVal)  // 然后在彼处插入insertVal
{
    using std::cbegin;
    using std::cend;
    
    auto it = std::find(cbegin(container), // 非成员函数版本的cbegin
                        cend(container),   // 非成员函数版本的cend
                        targetVal);

    container.insert(it, insertVal);
}
```



## 条款14:只要函数不会发射异常，就为其加上noexcept声明
* noexcept声明是函数接口的组成部分，这意味着调用方可能会对它有依赖。
* 相对于不带noexcept声明的函数，带有noexcept声明的函数有更多机会得到优化。
* noexcept性质对于移动操作,swap,内存释放函数和析构函数最有价值。
* 大多数函数都是异常中立的，不具备noexcept性质。

不同风格的不会发射异常的函数，例：

```c++
int f(int x) throw();  // f不会发射异常：c++98风格
int f(int x) noexcept; // f不会发射异常：c++11风格
```

`noexcept`对函数的优化：优化器不需要在异常传出函数的前提下，将执行期栈保持在可开解状态；也不需要在异常逸出函数的前提下，保证所有其中的对象以其被构造顺序的逆序完成析构。例：

```c++
RetType function(params) noexcept; // 最优化

RetType function(params) trow();   // 优化不够

RetType function(params);          // 优化不够
```



## 条款15:只要有可能使用constexpr,就使用它
* constexpr对象都具备const属性，并由编译期已知的值完成初始化。
* constexpr函数在调用时若传入的实参值是编译期已知的，则会产出编译期结果。
* 比起非constexpr对象或constexpr函数而言，constexpr对象或是constexpr函数可以用在一个作用域更广的语境中。

例：

```c++
int sz; // 非constexpr变量

constexpr auto arraySize1 = sz;    // 错误！sz的值在编译期未知
std::array<int, sz> data1;         // 错误！一样的问题
constexpr auto arraySize2 = 10;    // 没问题，10是个编译期常量
std::array<int, arraySize2> data2; // 没问题，arraySize2是个constexpr

// const并未提供和constexpr同样的保证，因为const对象不一定经由编译期已知值来初始化
int sz; 						 // 仍然是非constexpr变量
const auto arraySize = sz; 	     // 没问题，arraySize是sz的一个const副本
std::array<int, arraySize> data; // 错误！arraySize
```

对constexpr的正确理解：

- constexpr函数可以用在要求编译期常量的语境中。在这样的语境中，若你传给一个constexpr函数的实参值是在编译期已知的，则结果也会在编译期间计算出来。如果任何一个实参值在编译期未知，则你的代码将无法通过编译。
- 在调用constexpr函数时，若传入的值有一个或多个在编译期未知，则它的运作方式和普通函数无异，亦即它也是在运行期执行结果的计算。这意味着，如果函数执行的是同样的操作，仅仅应用的语境一个是要求编译期敞亮的，一个是用于所有其他值的话，那就不必写两个函数。constexpr函数就可以同时满足所有需求。

constexpr的限制：

- c++11中，constexpr函数不得包含多于一个可执行语句，即一条return语句；例：

```c++
constexpr int pow(int base, int exp) noexcept
{
    return (exp == 0 ? 1 : base * pow(base, exp - 1));
}
```
- c++14中，constexpr函数放宽了限制

```c++
constexpr int pow(int base, int exp) noexcept
{
    auto result = 1;
    for (int i = 0; i < exp; ++i) result *= base;
    return result;
}
```

c++11中，用户自定义型别的构造函数和其他成员函数也可以是`constexpr`函数；例：

```c++
class Point {
public:
    constexpr Point(double xVal = 0, double yVal = 0) noexcept : x(xVal), y(yVal) {}

    constexpr double xValue() const noexcept { return x; }
    constexpr double yValue() const noexcept { return y; }
    
    void setX(double newX) noexcept { x = newX; }
    void setY(double newY) noexcept { y = newY; }
private:
    double x, y;
};

constexpr Point p1(9.4, 27.7); // 没问题，在编译期“运行”constexpr构造函数
constexpr Point p2(28.8, 5.3); // 没问题

constexpr
Point midpoint(const Point& p1, const Point& p2) noexcept
{
    return { (p1.xValue() + p2.xValue()) / 2,   // 调用constexpr
             (p1.yValue() + p2.yValue()) / 2};  // 成员函数
}

constexpr auto mid = midpoint(p1, p2); // 使用constexpr函数的结果来初始化constexpr对象
```

c++14中，设置器也可以声明为constexpr，例：

```c++
class Point {
public:
    ...
    constexpr void setX(double newX) noexcept
    { x = newX; }
    constexpr void setY(double newY) noexcept
    { y = newY; }
    ...
};
```



## 条款16:保证const成员函数的线程安全性
- 保证const成员函数的线程安全性，除非可以确信它们不会用在并发语境中。
- 运用std::atomic 型别的变量会比运用互斥量提供更好的性能，但前者仅适用对单个变量或内存区域的操作。

保证const成员函数的线程安全性，例：

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

使用atomic来取代mutex，例：

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



## 条款17:理解特种成员函数的生成机制
- 特种成员函数是指那些c++会自行生成的成员函数：默认构造函数，析构函数，复制操作，以及移动操作。- 移动操作仅当类中未包含用户显式声明的复制操作，移动操作和析构函数时才生成。
- 复制构造函数仅当类中不包含用户显式声明的复制构造函数时才生成，如果该类声明了移动操作则复制构造函数将被删除。复制赋值运算符仅当类中不包含用户显式声明的复制赋值运算符才生成，如果该类声明了移动操作则复制赋值运算符被删除。在已经存在显式声明的析构函数的条件下，生成复制操作已经成为了被废弃的行为。
- 成员函数模版在任何情况下都不会抑制特种成员函数的生成。

c++11中，支持特种成员函数的机制如下:
* 默认构造函数: 与c++98的机制相同。仅当类中不包含用户声明的构造函数时才生成。
* 析构函数: 与c++98的机制基本相同，唯一的区别在于析构函数默认为noexcept。与c++98的机制相同，仅当积累的析构函数为虚的，派生类的析构函数才是虚的。
* 复制构造函数: 运行期行为与c++98相同：按成员进行非静态数据成员的复制构造。仅当类中不包含用户声明的复制构造函数时才生成。如果该类声明了移动操作，则复制构造函数将被删除。在已经存在复制赋值运算符或析构函数的条件下，仍然生成复制构造函数已经成为了被废弃的行为。
* 复制赋值运算符: 运行期行为与c++98相同: 按成员进行非静态数据成员的复制赋值。仅当类中不包含用户声明的复制赋值运算符时才生成。如果该类声明了移动操作，则复制构造函数将被删除。在已经存在复制构造函数或析构函数的条件下，仍然生成复制赋值运算符已经成为了被废弃的行为。
* 移动构造函数和移动赋值运算符: 都按成员进行非静态数据成员的移动操作。仅当类中不包含用户声明的复制操作，移动操作和析构函数时才生成。

大三律（Rule of Three）：如果声明了复制构造函数，复制赋值运算符，析构函数中的任何一个，就得同时声明这三个。

通过使用“=default”来默认复制构造函数的行为是正确的，例：

```c++
class Widget {
public:
    ...
    ~Widget(); // 用户定义的析构函数
    ...
    Widget(const Widget&) = default;            // 默认复制构造函数的行为是正确的
    Widget& operator=(const Widget&) = default; // 默认复制赋值运算符的行为是正确的
};
```

通过使用"=default"来声明移动操作又不丧失可复制性，例：

```c++
class Base {
public:
    virtual ~Base() = default; // 使析构函数称为虚的
    Base(Base&&) = default;    // 提供移动操作的支持
    Base& operator=(Base&&) = default;

    Base(const Base&) = default;            // 提供复制操作的支持
    Base& operator=(const Base&) = default;
}
```
