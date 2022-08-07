# date_time



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

- `to_simple_string(date d)`
- TODO

