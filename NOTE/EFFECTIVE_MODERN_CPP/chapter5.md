[TOC]

# 第五章 右值引用，移动语义和完美转发

- **移动语义**使得编译器第一使用不那么昂贵的移动操作，来替换昂贵的复制操作。
- 完美转发使得人们可以撰写接收任意实参的函数模板，并将其转发到其他函数，目标函数会接收到与转发函数所接受的完全相同的实参。



## 条款23: 理解std::move和std::forward
- `std::move`实施的是无条件的向右值型别的强制型别转换。就其本身而言，它不会执行移动操作。
- 仅当传入的实参被绑定到右值时，`std::forward`才针对该实参实施向右值型别的强制型别转换。
- 在运行期，`std::move`和`std::forward`都不会做任何操作.

c++11的move实现，例：

```c++
template<typename T>
typename remove_reference<T>::type&& move(T&& param)
{
    using ReturnType = typename remove_reference<T>::type&&; // 别名
    
    return static_cast<ReturnType>(param);
}
```

c++14的move实现，例：

```c++
template<typename T>
decltype(auto) move(T&& param)
{
    using ReturnType = remove_reference_t<T>&&;
    
    return static_cast<ReturnType>(param);
}
```

使用`std::move`来避免复制入参数据成员的过程产生的复制操作成本，例：

```c++
class Annotation {
public:
    explicit Annotation(const std::string text)
    : value(std::move(text)) // 将text移动入value
    { ... }

private:
    std::string value;
};
```

使用`std::forward`来有条件的强制类型转换，例：

```c++
void process(const Widget& lvalArg); // 处理左值
void process(Widget&& rvalArg);      // 处理右值

template<typename T> // 把param传递给process的函数模版
void logAndProcess(T&& param)
{
    auto now = std::chrono::system_clock::now();

    makeLogEntry("Calling 'process'", now);
    process(std::forward<T>(param));
}
```



## 条款24: 区分万能引用和右值引用
- 如果函数模板形参具备`T&&`型别，并且T的型别系推导而来，或如果对象使用`auto&&`声明型别，则该形参或对象就是个万能引用。
- 如果型别声明并不精确的具备`type&&`的形式，或者型别推导并未发生，则`type&&`就代表右值引用。
- 若采用右值来初始化万能引用，就会得到一个右值引用。若采用左值来初始化万能引用，就会得到一个左值引用。

万能引用的场景（即涉及到型别推导的场景），例：

```c++
template<typename T>
void f(T&& param);  // 万能引用
std::vector<int> v;
f(v); // 错误！不能给一个右值引用绑定一个左值

Widget&& var1 = Widget();
auto&& var2 = var1; // 万能引用
```

右值引用的场景，例：

```c++
void f(Widget&& param);         // 右值引用

Widget&& var1 = Widget();       // 右值引用

template<typename T>
void f(std::vector<T>&& param); // 右值引用
```



## 条款25: 针对右值引用实施`std::move`,针对万能引用实施`std::forward`
- 针对右值引用的最后一次使用实施`std::move`,针对万能引用的最后一次使用实施`std::forward`。
- 作为按值返回的函数的右值引用和万能引用，依上一条所述采取相同行为。
- 若局部对象可能适用于返回值优化，则请勿针对其实施`std::move`或`std::forward`。

针对右值引用实施`std::move`，例：

```c++
class Widget {
public:
    Widget(Widget&& rhs)
    : name(std::move(rhs.name)),
      p(std::move(rhs.p))
      { ... }
    ...

private:
    std::string name;
    std::shared_ptr<SomeDataStructure> p;
};
```

针对万能引用实施`std::forward`，例：

```c++
class Widget {
public:
    template<typename T>
    void setName(T&& newName) // 万能引用
    { name = std::forward<T>(newName); }
    ...
};
```

编译器若要在一个按值返回的函数里省略对局部对象的复制（或移动），需要满足以下两个条件：

1. 局部对象型别和函数返回值型别相同
2. 返回的就是局部对象本身



## 条款26: 避免依万能引用型别进行重载
- 把万能引用作为重载候选型别，几乎总会让该重载版本在始料未及的情况下被调用到。
- 完美转发构造函数的问题尤其严重，因为对于非常量的左值型别而言，他们一般都会形成对于复制构造函数的更佳匹配，并且他们还会劫持派生类中对基类的复制和移动构造函数的更佳匹配，并且他们还会劫持派生类中对基类的复制和移动构造函数的调用。

例：

```c++
template<typename T>
void logAndAdd(T&& name)
{
    auto now = std::chrono::system_clock::now();
    log(now, "logAndAdd");
    names.emplace(std::forward<T>(name));
}

std::string nameFromIdx(int idx); // 返回索引对应的名字

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

logAndAdd(22); // 调用了形参型别为int的重载版本
```



## 条款27: 熟悉依万能引用型别进行重载的替代方案
- 如果不能使用万能引用和重载的组合，则替代方案包括使用彼此不同的函数名字，传递`const T&`型别的形参，传值和标签分派。
- 经由`std::enable_if`对模板施加限制，就可以将万能引用和重载一起使用，不过这种技术控制了编译器可以调用到接受万能引用的重载版本的条件。
- 万能引用形参通常在性能方面具备优势，但在易用性方面一般会有劣势。

使用`std::enable_if`对模版施加限制，例：

```c++
class Person {
public:
    template<
        typename T,
        typename = std::enable_if_t< // enable_if_t
            !std::is_base_of<Person, std::decay_t<T>>::value
            &&
            !std::is_integral<std::remove_reference_t<T>>::value
        >
    >

    explicit Person(T&& n)   // 接受std::string型别以及可以强制转型到std::string的实参型别的构造函数
    : name(std::forward<T>(n))
    { 
        // 断言可以从T型别的对象构造一个std::string型别的对象
        static_assert(
                std::is_constructible<std::string, T>::value,
                "Parameter n can't be used to construct a std::string")
    }

    explicit Person(int idx) // 接受整型实参的构造函数
    : name(nameFromIdx(idx))
    { ... }

    ...
    private:
        std::string name;
}
```



## 条款28: 理解引用折叠
- 引用折叠会在四种语境中发生:
    - 模板实例化
    - auto型别生成
    - 创建和运用typedef和别名声明
    - decltype。
- 当编译器在引用折叠的语境下生成引用的引用时，结果会变成单个引用。如果原始的引用中有任一引用为左值引用，则结果为左值引用。否则，结果为右值引用。
- 万能引用就是在型别推导的过程会区别左值和右值，以及会发生引用折叠的语境中的右值引用。



## 条款29: 假定移动操作不存在，成本高，未使用
- 假定移动操作不存在，成本高，未使用。
- 对于那些型别或对于移动语义的支持情况已知的代码，则无需做以上假定。

c++11在以下场景不会带来好处：

- 没有移动操作：待移动的对象未能提供移动操作，因此，移动请求就变成了复制请求。
- 移动未能更快：待移动的对象虽然有移动操作，但并不比其复制操作更快。
- 移动不可用：移动本可以发生的语境下，要求移动操作不可发射异常，但该操作未加上noexcept声明。



## 条款30: 熟悉完美转发的失败情形
- 完美转发的失败情形，是源于模板型别推到失败或推导结果是错误的型别。
- 会导致完美转发失败的实参种类有大括号初始化物，以值0或NULL表达的空指针，仅有声明的整形`static const`成员变量，模板或重载的函数名字，以及位域。

完美转发在下面两个条件中任何一个成立时失败：

- 编译器无法为一个或多个fwd的形参推导出型别结果。
- 编译器为一个或多个fwd的形参推导出“错误的”型别结果。

完美转发失败的情形：

-  大括号初始化物

```c++
void f(const std::vector<int>& v);

f({1, 2, 3}); // 没问题，“{1, 2, 3}”会隐式转换为std::vector<int>

fwd({1, 2, 3}); // 错误！无法通过编译
```

-  0和NULL用作空指针
如果把0和NULL以空指针之名传递给模版，型别推导就会发生行为扭曲，推导结果会是整型而非所传递实参的指针型别。（修正方案：用nullptr）。

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
