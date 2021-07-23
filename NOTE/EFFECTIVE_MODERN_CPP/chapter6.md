[TOC]

# 第六章 lambda表达式

- lambda表达式，顾名思义，是表达式的一种。他是源代码组成部分，比如在下面这段代码中高亮部分就是lambda式:

```c++
std::find_if(container.begin(), container.end(),
				[](int val) {return 0 < val && val < 10; });
```
- 闭包是lambda式创建的运行期对象，根据不同的补货模式，闭包会持有数据的副本或引用。
- 闭包类就是实例化闭包的类。每个lambda式都会触发编译器生成一个独一无二的闭包类。而闭包类中的语句会变成他的闭包类成员函数的可执行指令。



## 条款31: 避免默认捕获模式
- 按引用的默认捕获会导致空悬指针问题。
- 按值的默认捕获极易受空悬指针影响(尤其是this),并会误导人们认为lambda式是自洽的。

例：

```c++
template<typename C>
void workWithContainer(const C& container)
{
    auto calc1 = computeSomeValue1();
    auto calc2 = computeSomeValue2();

    auto divisor = computeDivisor(calc1, calc2);

    using ContElemT = typename C::value_type; // 为实现范型算法，取得容器中的元素型别
    
    using std::begin;
    using std::end;

    if (std::all_of(begin(container), end(container),
                [&](const auto& value)
                { return value % divisor == 0; }) 
       ){
        ...
    } else {
        ...
    }
}
```

按值默认捕获，例：

```c++
void Widget::addFilter() const
{
    auto divisorCopy = divisor; // 复制成员变量

    filters.emplace_back(
            [=](int value)                       // 捕获副本
            { return value % divisorCopy == 0; } // 使用副本
    );
};
```

使用默认值捕获模式无法与闭包外部数据的变化绝缘，例：

```c++
void addDivisorFilter()
{
    static auto calc1 = computeSomeValue1(); 
    static auto calc2 = computeSomeValue2();

    static auto divisor = computeDivisor(calc1, calc2);

    filters.emplace_back(
            [=](int value)                   // 未捕获任何东西
            { return value % divisor == 0; } // 指涉到前述以static声明的对象
    );

    ++divisor;                               // 意外修改了divisor
}
```



## 条款32: 使用初始化捕获将对象移入闭包
- 使用c++14的初始化捕获将对象移入闭包。
- 在c++11中，经由手工实现的类或`std::bind`去模拟初始化捕获。

使用初始化捕获，则有机会指定：

1. 由lambda生成的闭包类中的成员变量的名字。
2. 一个表达式，用以初始化该成员变量。

使用初始化捕获将`std::unique_ptr`移动到闭包内，例：

```c++
class Widget {
public:
    ...

    bool isValidated() const;
    bool isProcessed() const;
    bool isArchived() const;

private:
    ...
};

auto pw = std::make_unique<Widget>(); // 创建Widget

auto func = [pw = std::move(pw)] // 采用std::move(pw)初始化闭包类的数据成员
            { return pw->isValidated()
                     && pw->isArchived(); }

auto func1 = [pw = std::make_unique<Widget>()] // 以make_unique的调用结果初始化闭包类的成员
             { return pw->isValidated() 
                      && pw->isArchived(); };
```

可以使用以下步骤模拟初始化捕获：

1. 把需要捕获的对象移动到`std::bind`产生的函数对象中。
2. 给到lambda式一个指涉到欲“捕获”的对象的引用。

使用`std::bind`模拟初始化捕获，例：

```c++
auto func = 
    std::bind( // c++11中针对可变lambda式的模拟初始化捕获
        [](std::vector<double>& data) mutable
        { ... },
        std::move(data)
    );
```

以下为捕获的基础知识：

- 移动构造一个对象入c++11闭包是不可能实现的，但移动一个对象入绑定对象则是可能实现的。
- 欲在c++11中模拟移动捕获包括以下步骤：先移动构造一个对象入绑定对象，然后按引用把该移动构造所得的对象传递给lambda式。
- 因为绑定对象的生命期和闭包相同，所以针对绑定对象中的对象和闭包里的对象可以采用同样手法加以处置。



## 条款33: 对`auto&&`型别的形参使用`decltype`,以`std::forward`之
- 对`auto&&`型别的形参使用`decltype`,以`std::forward`之。

例：

```c++
auto f = [](auto&& param){ 
    return func(normalize(std::forward<decltype(param)>(param)));
};
```



## 条款34: 优先选用lambda式，而非`std::bind`
- lambda式比起使用`std::bind`而言，可读性更好，表达力更强，可能运行效率也更高。
- 仅在c++11中，`std::bind`在实现移动捕获，或是绑定到具备模板化的函数调用运算符的对象的场合中，可能尚有余热可以发挥。

使用lambda，例：

```c++
using Time = std::chrono::steady_clock::time_point;

enum class Sound { Beap, Siren, Whistle };

using Duration = std::chrono::steady_clock::duration;

void setAlarm(Time t, Sound s, Duration d);

auto setSoundL = 
    [](Sound s)
    {
        // 使std::chrono组件不加限定修饰词即可用
        using namespace std::chrono;
        using namespace std::literals; // 汇入c++14实现的后缀

        setAlarm(steady_clock::now() + 1h,
                 s,
                 30s);
    };
```

使用`std::bind`，例：

```c++
using SetAlarm3ParamType = void(*)(Time t, Sound s, Duration d);

auto setSoundB = 
    std::bind(static_cast<SetAlarm3ParamType>(setAlarm),
              std::bind(std::plus<>(),
                        steady_clock::now(),
                        1h),
              _1,
              30s);
```

`std::bind`在以下受限的场景中还有使用价值：

- **移动捕获**。c++11的lambda式没有提供移动捕获特性，但可以通过结合`std::bind`和lambda式来模拟移动捕获。
- **多态函数对象**。因为绑定对象的函数调用运算符利用了完美转发，他就可以接受任何型别的参数。
