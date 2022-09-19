# date_time

[TOC]



## 编译与使用

`date_time`需要编译才能使用，在jamfile里添加以下语句以编译：

```jamfile
lib boost_date_time;
```

添加以下语句以启用data_time库：

```c++
// 处理日期的组件
#include <boost/date_time/gregorian/gregorian.hpp>
using namespace boost::gregorian;

// 处理时间的组件
#include <boost/date_time/posix_time/posix_time.hpp>
using namespace boost::posix_time;
```



## 基本概念

`date_time`使用`special_values`枚举了以下一些特殊的时间：

- `pos_infin` 正无限
- `neg_infin` 负无限
- `not_a_date_time` 无效时间
- `min_date_time` 可表示的最小日期或时间
- `max_date_time` 可表示的最大日期或时间



## 处理日期

添加以下语句已使用`date_time`的日期功能：

```c++
#include <boost/date_time/gregorian/gregorian.hpp>
using namespace boost::gregorian;
```

### 日期

date类摘要如下：

```c++
template<typename T, typename calendar, typename duration_type_>
class date {
public:
    // 构造函数
	date(year_type, month_type, day_type);
    date(const ymd_type &);
    
    // 基本操作
    year_type        year() const;
    month_type       month() const;
    day_type         day() const;
    day_of_week_type day_of_week() const;
    ymd_type         year_month_day() const;
    
    // 比较操作
    bool operator<(const date_type &) const;
    bool operator==(const date_type &) const;
    
    // 有效性验证
    bool is_special() const;
    bool is_not_a_date() const;
    bool is_infinity() const;
    bool is_pos_infinity() const;
    bool is_neg_infinity() const;
    special_values as_special() const;
    
    duration_type operator-(const date_type &) const;
    ...
};
```

### 创建日期对象

例：

```c++
// 常规方法
date d1;               // 一个无效的日期
date d2(2010,1,1);     // 使用数字构造日期
date d3(2000, Jan, 1); // 使用引文指定月份
date d4(d2);           // 拷贝构造

// 根据字符串创建
date d5 = from_string("1999-12-31");
date d6(from_string("2015/1/1"));
date d7= from_undelimited_string("20011118");

// 特殊日期
date d8(neg_infin);        // 负无限日期
date d9(pos_infin);        // 正无限日期
date d10(not_a_date_time); // 无效日期
date d11(max_date_time);   // 最大可能日期 9999-12-31
date d12(min_date_time);   // 最小可能日期 1400-01-01
```

### 访问日期

例：

```c++
date d(2014, 4, 1);
assert(d.year()  == 2014); // 年
assert(d.monty() == 4);    // 月
assert(d.day()   == 1);    // 日
```

*返回年月日*

```c++
date::ymd_type ymd = d.year_monty_day(); // 一次性返回年月日
assert(ymd.year  == 2014);
assert(ymd.month == 4);
assert(ymd.day   == 1);
```

*一次性返回年月日*

```c++
date d(2014, 4, 1);
d.day_of_week();  // 星期几
d.day_of_year();  // 当年的第几天
d.end_of_month(); // 当月的最后一天的日期信息
```

*返回星期数/天数/月最后一天信息*

```c++
date(2014, 1, 10).week_number(); // 当年的第几周
```

*当年的第几周*

### 日期的输出

date提供以下函数来转换成字符串：

- `to_simple_string(date d)` 转换为`YYYY-mmm-DD`格式的字符串，其中的`mmm`为3字符的英文月份名；
- `to_iso_string(date d)` 转换为YYYYMMDD格式的数字字符串；
- `to_iso_extended_string(date d)` 转换为`YYYY-MM-DD`格式的数字字符串。

date也支持流输入输出，默认使用`YYYY-mmm-DD`格式；例：、

```c++
date d(2008, 11, 20);
cout << to_simple_string(d) << endl;
cout << to_iso_string(d) << endl;
cout << to_iso_extended_string(d) << endl;
cout << d << endl;

cin >> d;
cout << d;
```

### 转换tm结构

date支持与C标准库中的tm结构相互转换，转换的规则和函数如下：

- `to_tm(date)` date转换到tm。tm的时分秒成员（tm_hour, tm_min, tm_sec）均置为0，夏令时标志tm_isdst置为-1（表示未知）。
- `date_from_tm(tm datetm)` tm转换到date。只使用年，月，日三个成员（tm_year, tm_mon, tm_mday），其它成员均被忽略。

例：

```c++
date d(2014, 2, 1);
tm t = to_tm(d);
assert(t.tm_hour == 0 && t.tm_min == 0);
assert(t.tm_year == 114 && t.tm_mday == 1);

date d2 = date_from_tm(t);
assert(d == d2);
```

### 日期长度

日期长度是以天为单位的时长，是度量时间长度的一个标量。可以是任意的整数，其类摘要如下：

```c++
class date_duration
{
public:
    date_duration(long);
    date_duration(special_values);
    long days() const;
    bool is_special() const;     // 是否为特殊值
    bool is_negative() const;    // 是否为负值
    bool operator==(const date_duration &) const;
    ...
    static date_duration unit(); // 时长单位
}
```

例：

```c++
days dd1(10), dd2(-100), dd3(255);
assert(dd1 > dd2 && dd1 < dd3);
assert(dd1 + dd2 == days(-90));
assert((dd1 + dd3).days() == 265);
assert(dd3 / 5 == days(51));

weeks w(3); // 3个星期
assert(w.days() == 21);

months m(5); // 5个月
years y(2);  // 2年
months m2 = y + m;
assert(m2.number_of_months() == 29);
assert((y * 2).number_of_years() == 4);
```

### 日期运算

date支持加减运算，date主要是与时长配合运算。例：

```c++
#include <boost/date_time/gregorian/gregorian.hpp>
using namespace boost::gregorian;

int main()
{
    date d1(2000, 1, 1), d2(2014, 11, 18);
    cout << d2 - d1 << endl;
    assert(d1 + (d2 - d1) == d2);
    
    d1 += days(10);
    assert(d1.day() == 11);
    d1 += months(2);
    assert(d1.month() == 3 && d1.day() == 11);
    d1 -= weeks(1);
    assert(d1.day() == 4);
    
    d2 -= years(10);
    assert(d2.year() == d1.year() + 4);
}
```

日期与特殊日期长度，特殊日期与日期长度进行运算的结果也是特殊日期。例：

```c++
date d1(2014, 1, 1);

date d2 = d1 + days(pos_infin);
assert(d2.is_pos_infinity());

d2 = d1 + days(not_a_date_time);
assert(d2.is_not_a_date());
d2 = date(neg_infin);
days dd = d1 - d2;
assert(dd.is_special() && !dd.is_negative());
```

### 日期区间

date_time库使用date_period类来表示日期区间的概念，它是时间轴上的一个左闭右开区间，端点是两个date对象。区间的左边界必须小于右边界，否则date_period将表示一个无效的日期区间。类摘要如下：

```c++
class date_period
{
public:
    period(date, date);
    period(date, days);
    
    date begin() const;   // 返回左端点
    date end() const;     // 返回last()后的第一天
    date last() const;    // 返回右端点
    days length() const;  // 返回日期区间长度
    bool is_null() const; // 是否为空（左大右小或日期长度为0）
    
    bool operator==(const period &) const; // 比较操作
    bool operator<(const period &) const;
    
    void shift(const days &);  // 平移
    void expand(const days &); // 扩展
    
    bool contains(const date &) const; // 区间运算
    bool contains(const period &) const;
    bool intersects(const period &) const;
    bool is_adjacent(const period &) const;
    bool is_before(const date &) const;
    bool is_after(const date &) const;
    period intersection(cosnt period &) const;
    period merge(const period &) const;
    period span(const period &) const;
};
```

### 日期区间运算

例：

```c++
date_period dp(date(2014, 1, 1), days(20));

dp.shift(days(3));
assert(dp.begin().day() == 4);
assert(dp.length().days() == 20);

dp.expand(days(3));
assert(dp.begin().day() == 1);
assert(dp.length().days() == 26);
```

`date_period`还可以使用成员函数判断某个日期是否在区间内，或者计算日期区间的交集：

- `is_before()/is_after()` 日期区间是否在日期前或后；
- `contains()` 日期区间是否包含另一个区间或者日期；
- `intersects()` 两个日期区间是否存在交集；
- `intersection()` 返回两个区间的交集，如果无交集返回一个无效区间；
- `is_adjacent()` 两个日期区间是否相邻。

例：

```c++
date_period dp(date(2010, 1, 1), days(20));  // [1-1, 1-20]
assert(dp.is_after(date(2009, 12, 1)));
assert(dp.is_before(date(2010, 2, 1)));
assert(dp.contains(date(2010, 1, 10)));

date_period dp2(date(2010, 1, 5), days(10)); // [1-5, 1-15]
assert(dp.contains(dp2));

assert(dp.intersects(dp2));
assert(dp.intersection(dp2) == dp2);

date_period dp3(date(2010, 1, 21), days(5)); // [1-21, 1-26]
assert(!dp3.intersects(dp2));
assert(dp3.intersection(dp2).is_null());

assert(dp.is_adjacent(dp3));
assert(!dp.intersects(dp3));
```

`date_period`提供了两种并集操作：

- `merge()` 返回两个区间的并集，如果区间无交集或者不相邻则返回无效区间；
- `span()` 合并两日期区间及两者间的间隔，相当于广义的`merge()`。

例：

```c++
date_period dp1(date(2010, 1, 1), days(20));
date_period dp2(date(2010, 1, 5), days(10));
date_period dp3(date(2010, 2, 1), days(5));
date_period dp4(date(2010, 1, 15), days(10));

assert(dp1.contains(dp2) && dp1.merge(dp2) == dp1);
assert(!dp1.intersects(dp3) && dp1.merge(dp3).si_null());
assert(dp1.intersects(dp2) && dp1.merge(dp4).end() == dp4.end());
assert(dp1.span(dp3).end() == dp3.end());
```

### 日期迭代器

date_time库为日期处理提供了迭代器的概念，这些迭代器包括：

- day_iterator
- week_interator
- month_iterator
- year_iterator

例，日期迭代器使用：

```c++
date d(2006, 11, 26);

day_iterator d_iter(d); // 步长默认1天
assert(d_iter == d);
++d_iter; // +1天
assert(d_iter == date(2006, 11, 27)); 

year_iterator y_iter(*d_iter, 8); // 步长为8年
assert(y_iter == d + days(1));
++y_iter; // +8年
assert(y_iter->year() == 2014);
```

例，迭代器的错误使用：

```c++
day_iterator itr(day_clock::local_day());
++iter;

iter += 5;             // 错误，编译失败
std::advance(iter, 5); // 错误，编译失败
```

### 其它功能

`boost::gregorian::gregorian_calendar`类提供了一些操作函数。

例：

```c++
typedef gregorian_calendar gre_cal;
cout << "Y2014 is "
     << (gre_cal::is_leep_year(2014) ? "" : "not")
     << " a leap year." << endl;
assert(gre_cal::end_of_month_day(2014, 2) == 28);
```

### 综合运用

例，显示月历：

```c++
date d(2008, 11, 20);

date d_start(d.year(), d.month(), 1); // 当月第一天
date d_end = d.end_of_month();        // 当月最后一天

for (day_iterator d_iter(d_start); d_iter != d_end; ++d_iter) // 构造日期迭代器
{
    cout << *d_iter << " " <<
        d_iter->day_of_week() << endl;
}
```

例，简单的日期计算：

```c++
date d(2008, 11, 20);

date d18years = d + years(18); // +18年
cout << d18years << " is "
     << d18years.day_of_week() << endl;
int count = 0;
for (day_iterator d_iter(date(d18years.year(), 11, 1)); 
     d_iter != d18years.end_of_month(); ++d_iter)
{
    if (d_iter->day_of_week() == sunday)
    {
        ++count;
    }
}
cout << "total " << count << " Sundays." << endl;

count = 0; // 计数器置零
for (month_iterator m_iter(date(d18years.year(), 1, 1)); 
     m_iter < date(d18years.year() + 1, 1, 1); ++m_iter)
{
    count += m_iter->end_of_month().day();
}
cout << "total " << count << " days of year." << endl;
```

例，计算信用卡的免息期：

```c++
class credit_card
{
public:
    string bank_name; // 银行名
    int bill_day_no;  // 记账日
    
    // 构造函数
    credit_card(const char* bname, int no) : 
    	bank_name(bname), bill_day_no(no) {} 
    
    // 计算免息期
    int calc_free_days(date consume_day = day_clock::local_day()) const
    {
        date bill_day(consume_day.year(), consume_day.month(), 
                      bill_day_no); // 得到记账日
        if (consume_day > bill_day) // 消费日是否已经过了记账日
        {
            bill_day += months(1);
        }
        return (bill_day - consume_day).days() + 20; 
    }
    
    // 比较操作
    friend bool operator<(const credit_card& l, const credit_card& r)
    {
        return l.calc_free_days() < r.calc_free_days(); // 比较免息期
    }
};

int main()
{
    credit_card a("A bank", 25);
    credit_card b("B bank", 12);
    credit_card tmp = std::max(a, b);
    cout << "You should use " << tmp.bank_name
         << ", free days = " << tmp.calc_free_days() << endl;
}
```



## 2.7 处理时间

`date_time`提供微秒级别的时间系统，如果需要，最高可达到纳秒级别的精度。

为了使用时间组件，需要包含如下代码：

```c++
#include <boost/date_time/posix_time/posix_time.hpp>
using namespace boost::posix_time;
```

### 2.7.1 时间长度

date_time库使用`time_duration`度量时间长度，如果定义了宏`BOOST_DATE_TIME_POSIX_TIME_STD_CONFIG`，那么它可以精确到纳秒级。

### 2.7.2 操作时间长度



