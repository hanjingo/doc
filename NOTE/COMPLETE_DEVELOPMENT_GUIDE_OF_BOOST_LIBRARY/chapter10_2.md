# chrono
chrono库提供宏BOOST_CHRONO_HEADER_ONLY,可以把chrono库完全头文件化，不需要编译或链接。

chrono库位于名字空间boost::chrono,使用标准之外的扩展功能需要定义宏BOOST_CHRONO_EXTENSIONS,包含的头文件如下:
```c++
#define BOOST_CHRONO_HEADER_ONLY // 无须编译即可使用chrono库
#define BOOST_CHRONO_EXTENSIONS  // 使用扩展功能
#include <boost/chrono.hpp>      // chrono库的头文件
using namespace boost::chrono;
```

## 时间长度
chrono库定义了时间长度的表示-duration,其类摘要如下:
```c++
template < class Rep, class Period = ratio<1> >
class duration {
public:
    typedef Rep rep;                         // 内部的类型定义
    typedef Period period;
private:
    rep rep_;                                // 时间单位的计数
public:
    constexpr duration();                    // 构造函数
    constexpr explitcit duration(const Rep2& r);
    constexpr duration(const duration& d);

    constexpr rep count() const;             // 返回时间单位的计数
    duration& operator++();
    duration& operator+=(const duration& d); // 重载算术操作符
    duration& operator*=(const rep& rhs);
    ...
    static constexpr duration zero();        // 零值
    static constexpr duration min();         // 最小值
    static constexpr duration max();         // 最大值
};
```
chrono库与定义了常用的时间单位，如hours,minutes,seconds,milliseconds等，但它与date_time库time_duration使用派生子类的方式不同，
chrono库通过在模板参数里使用不同的ratio来定义时间单位，因此每一个时间单位都是不同的类型:
```c++
typedef duration<boost::int_least64_t, nano> nanoseconds;
typedef duration<boost::int_least64_t, micro> microseconds;
typedef duration<boost::int_least64_t, milli> milliseconds;
typedef duration<boost::int_least64_t       > seconds;
typedef duration< boost::int_least32_t, ratio<60> > minutes;
typedef duration< boost::int_least32_t, ratio<3600> > hours;
```
除了这些预定义的时间单位，我们也可以用typedef来简化duration类型，实现任意的时间分辨率，duration赋予了我们极大的灵活性。例:
```c++
typedef duration<long, ratio<30>> half_min;   // 半分钟
typedef duration<int, ratio<60*15>> quater;   // 一刻钟
typedef duration<double,ratio<3600*25>> day;  // 一天

typedef duration<int,60*60> myhour;			  // 编译错误，不能直接用整数
typedef duration<int, ratio<-1, 1000>> my_ms; // 编译错误，不能用负数
```

## 使用时间长度
### 基本运算
```c++
seconds s(10);
minutes m(5);
hours h(1);
milliseconds ms(100);

assert(s.count() == 10);
assert(ms.count() == 100);
// duration可以像int，double一样执行各种算术运算和比较运算，也能够直接流输出
s * = 3;
s += seconds(30);
s = s - seconds(20);
assert(s < seconds(50));
cout << s << endl;
```

## 类型转换
chrone库提供一个模板函数duration_cast()来转换不同类型的时间单位，他只是执行简单的舍入取整:
```c++
seconds s(30);
auto m = duration_cast<minutes>(s);
cout << m << endl;

seconds s2(301);
cout << duration_cast<minutes>(s2) << endl;
```
chrono库还有3个c++标准之外的扩展函数:floor(), ceil()和round().
- floor(): 与duration_cast()相同，取下界，他是简单的截断处理
- ceil(): 取上界
- round(): 四舍五入操作
这3个转换函数的用法如下:
```c++
seconds s(3600 + 50);

cout << floor<minutes>(s) << endl;
cout << ceil<minutes>(s) << endl;

cout << round<minutes>(s) << endl;
cout << round<hours>(s) << endl;
```

### 时钟
- system_clock: 如实反映计算机世界里的实际时间的时钟
- steady_clock: 稳定的时钟，不会因为系统时间调整而变化
- high_resolution_clock: 高分辨率的时钟，但通常是前2者的typedef
此外chrono库还定义了4个度量程序云溪是那个时间的时钟:
- process_real_cpu_clock: 进程执行的实际时间
- process_user_cpu_clock: 用户cpu时间
- process_system_cpu_clock: 系统cpu时间
- thread_clock: 线程执行的实际时间
system_clock的类摘要如下:
```c++
class system_clock
{
public:
    typedef some_define duration;           // 时间单位
    typedef duration::rep rep;              // 计数单位
    typedef duration::period period;        // ratio
    typedef chrono::time_point time_point;  // 时间点

    static constexpr bool is_steady;        // 是否是稳定时钟
    static time_point now();                // 获取当前时间

    // 转换c里的time_t结构
    static std::time_t to_time_t(const time_point& t);
    static time_point from_time_t(std::time_t t);
};
```
使用辅助类clock_string的2个静态成员函数name(),since()可以获取时钟的描述信息，声明如下:
```c++
template<class clock, class CharT>
struct clock_string
{
    static std::basic_string<CharT> name();
    static std::basic_string<CharT> since();
};

template<typename T>
using clock_desc = clock_string<T, char>; // 定义模板别名

cout << clock_desc<system_clock>::name() << endl;
cout << clock_desc<system_clock>::since() << endl;

cout << clock_desc<steady_clock>::name() << endl;
cout << clock_desc<stready_clock>::since() << endl;

cout << clock_desc<process_read_cpu_clock>::name() << endl;
cout << clock_desc<process_real_cpu_clock>::since() << endl;
```

### 时间点
```c++
template <class Clock, class Duration = typename Clock::duration>
class time_point {
public:
    typedef Clock clock;
    typedef Duration duration;
    typedef typename duration::rep rep;
    typedef typename duration::peeriod period;

private
    duration d_;

public:
    constexpr time_point();
    constexpr explicit time_point(const duration& d);

    constexpr duration time_since_epoch() const;

    time_point& operator+=(const duration& d);
    time_point& operator-=(const duration& d);

    static constexpr time_point min();
    static constexpr time_point max();

#ifdef BOOST_CHRONO_EXTENSIONS
    constexpr time_point operator+();
    constexpr time_point operator-();
    time_point&          operator++();
    time_point           operator++(int);
    time_point&          operator--();
    time_point           operator--(int);
    time_point&          operator-=(const rep& d);
#endif
};
```
用法示例:
```c++
auto tp1 = system_clock::now();
cout << tp1 << endl;

auto d = tp1.time_since_epoch(); // 获取自时间起点以来的时间长度
cout << duration_cast<hours>(d) << endl; // 转换为小时
cout << duration_cast<day>(d) << endl; // 转换为自定义的天

auto tp2 = tp1 + minutes(1);
cout << tp1 << endl;
```
改用不同的的时钟，time_point会有不同的数值和含义:
```c++
auto tp = steady_clock::now();
cout << tp << endl;

auto d = tp.time_since_epoch();
cout << round<minutes>(d) << endl;
cout << round<hours>(d) << endl;
```

## 综合应用
1. 自定义字面值
```c++
hours operator"" _h(unsigned long long n)         // 小时字面值
{ return hours(n); }

seconds operator"" _s(unsigned long long n)       // 秒字面值
{ return seconds(n); }

milliseconds operator"" _ms(unsigned long long n) // 毫秒字面值
{ return milliseconds(n); }

auto h = 5_h;
auto s = 45_s;
auto ms = 200_ms;
```

2. 将时间点转换为实际时间
```c++
auto tp = system_clock::now();
auto t = system_clock::to_time_t(tp); // 转换为time_t结构
cout << std::ctime(&t) << endl;
```

3. 高精度计时器
```c++
class steady_timer final
{
private:
    typedef boost::chrono::steady_clock_type;          // 定义时钟类型
    typedef clock_type::time_point time_point_type;    // 定义时间点类型
    typedef boost::chrono::microseconds duration_type; // 使用微秒精度
    time_point_type m_start = clock_type::now()        // 构造是记录时间点

public:
    void restart()                                     // 重启计时器
    { m_start = clock_type::now(); }
    duration_type elapsed() const
    {
        return round<duration_type>(                   // 转换时间为微秒
            clock_type::now() - m_start);              // 计算流逝的时间
    }
}
```

## cpu_timer
cpu_timer库需要chrono库的支持，因此必须先编译chrono,在jamfile里指定lib的语句如下
```sh
lib boost_timer : boost_chrono : <name>boost_timer;
```
cpu_timer位于名字空间boost::timer,需要包含的头文件如下
```c++
#include <boost/timer/timer.hpp>
using namespace boost::timer;
```

### 时间类型
cpu_timer库在boost::timer名字空间里定义了库使用的时间类型nanosecond_type和cpu_timers,声明如下:
```c++

```