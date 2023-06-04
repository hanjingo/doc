# 附录D C++线程类库参考

[TOC]



## D.1<chrono>头文件
<chrono>头文件作为time_point的提供者，具有代表时间点的类，duration类和时钟类。每个时钟都有一个`is_steady`静态数据成员，这个成员用来表示该时钟是否是一个稳定的时钟（以匀速计时的时钟，且不可调节）。`std::chrono::steady_clock`是唯一能保证稳定的时钟类。

头文件正文

```c++
namespace std
{
    namespace chrono
    {
        template<typename Rep, typename Period = rtio<1>>
        class duration;
        template<
            typename Clock,
            typename Duration = typename Clock::duration>
        class time_point;
        class system_clock;
        class steady_clock;
        typedef unspecified-clock-type high_resolution_clock;
    }
}
```

### D.1.1 std::chrono::duration类型模板

`std::chrono::duration`类模板可以用来表示时间。模板参数`Rep`和`Period`是用来存储持续时间的数据类型，`std::ratio`实例代表了时间的长度，其表示了在两次“时钟滴答”后的时间（时钟周期）。因此，`std::chrono::duration<int, std::milli>`即为，时间以毫秒数的形式存储到int类型中，而`std::chrono::duration<short, std::ratio<1, 50>>`则是记录1/50秒的个数，并将个数存入short类型的变量中，还有`std::chrono::duration<long long, std::ratio<60,1>>`则是将分钟数存储到`long long`类型的变量中。

类的定义：

```c++
template <class Rep, class Period=ratio<1> >
class duration
{
public:
    typedef Rep rep;
    typedef Period period;

    constexpr duration() = default;
    ~duration() = defualt;

    duration(const duration&) = default;
    duration& operator=(const duration&) = default;

    template <class Rep2>
    constexpr explicit duration(const Rep2& r);

    template <class Rep2, class Period2>
    constexpr duration(const duration<Rep2, Period2>& d);

    constexpr rep count() const;
    constexpr duration operator+() const;
    constexpr duration operator-() const;

    duration& operator++();
    duration operator++(int);
    duration& operator--();
    duration operator--(int);

    duration& operator+=(const duration& d);
    duration& operator-=(const duration& d);
    duration& operator*=(const rep& rhs);
    duration& operator/=(const rep& rhs);

    duration& operator%=(const rep& rhs);
    duration& operator%=(const duration& rhs);

    static constexpr duration zero();
    static constexpr duration min();
    static constexpr duration max();
};

template <class Rep1, class Period1, class Rep2, class Period2>
constexpr bool operator==(
        const duration<Rep1, Period1>& lhs,
        const duration<Rep2, Period2>& rhs);

template <class Rep1, class Period1, class Rep2, class Period2>
constexpr bool operator!=(
        const duration<Rep1, Period1>& lhs,
        const duration<Rep2, Period2>& rhs);

template <class Rep1, class>
```
要求

`Rep`必须是内置数据类型或是自定义的类数值类型。

`Period`必须是`std::ratio<>`实例。

### `std::chrono::duration::Rep`类型
用来记录`dration`中时钟周期的数量

声明

```c++
typedef Rep rep;
```

`rep`类型用来记录`duration`对象内部的表示

### `std::chrono::duration::Period`类型
这个类型必须是一个`std::ratio`的特化实例，用来表示在继续时间中，1s所要记录的此书。例如，当`period`是`std::ratio<1, 50>`, `duration`变量的`count()`就会在N秒钟返回50N。

声明

```c++
typedef Period period;
```

### `std::chrono::duration`默认构造函数
使用默认值构造`std::chrono::duration`实例

声明

```c++
constexpr duration() = default;
```

效果

`duration`内部值（例如`rep`类型的值）都已初始化。

### `std::chrono::duration`需要计数值的转换构造函数
通过给定的数值来构造`std::chrono::duration`实例。

声明

```c++
template <class Rep2>;
constexpr explicit duration(const Rep2& r);
```

效果

`duration`对象的内部值会使用`static_cast<rep>(r)`进行初始化。

结果

当Rep2隐式转换为Rep，Rep是浮点类型或Rep2不是浮点类型，这个构造函数才能使用。

后验条件

```c++
this->count()==static_cast<rep>(r)
```

### `std::chrono::duration`需要另一个`std::chrono::duration`值的转化构造函数

通过另一个`std::chrono::duration`类实例中的计数值来构造一个`std::chrono::duration`类实例。

声明

```c++
template<class Rep2, class Period>
constexpr duration(const duration<Rep2, Period2>& d);
```

结果

`duration`对象的内部值通过`duration_cast<duration<Rep, Period>>(d).count()`初始化。

要求

当Rep是一个浮点类或Rep2不是浮点类，且Period2是Period数的倍数(比如，`ratio_divide<Period2,Period>::den==1`)时，才能调用该重载。当一个较小的数据转换为一个较大的数据时，使用该构造函数就能避免数位截断和精度损失。

后验条件

```c++
this->count() == duration_cast&lt; duration<Rep, Period>(d).count()
```

例子

```c++
duration<int, ratio<1, 1000>> ms(5);      // 5ms
duration<int, ratio<1, 1>> s(ms);         // 错误；不能将ms当作s进行存储
duration<double, ratio<1, 1>> s2(ms);     // 合法:s2.count() == 0.005
duration<int, ration<1, 1000000>> us<ms>; // 合法:us.count() == 5000
```

### `std::chrono::duration::count`成员函数

查询持续时长。

声明

```c++
constexpr rep count() const;
```

返回

返回`duration`的内部值，其值类型和`rep`一样

### `std::chrono::duration::operator+`加法操作符

这是一个空操作：指挥返回`*this`的副本。

声明

```c++
constexpr duration operator+() const;
```

返回`*this`

### `std::chrono::duration::operator-`减法操作符

返回将内部值只为负数的`*this`副本。

声明

```c++
constexpr duration operator-() const;
```

返回`duration(--this->count());`

### `std::chrono::duration::operator++` 前置自加操作符

增加内部计数

声明`duration& operator++();`

返回`*this`

### `std::chrono::duration::operator++`后置自增运算符

