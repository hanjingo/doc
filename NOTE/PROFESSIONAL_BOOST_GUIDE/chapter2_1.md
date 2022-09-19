# timer

[TOC]



使用timer需要添加以下语句：

```c++
#include <boost/timer.hpp>
using namespace boost;
```



## 用法

```c++
#include <boost/timer.hpp>
using namespace boost;

int main()
{
    timer t;
    cout << "max timespan:"
         << t.elapsed_max() / 3600 << "h" << endl; // 最大可度量时间（h）
    cout << "min timespan:"
         << t.elapsed_min() << "s" << endl;        // 最小可度量时间（s）
    cout << "now time elapsed:"
         << t.elapsed() << "s" << endl;            // 已经流逝的时间
}
```



## 类摘要

```c++
class timer
{
public:
    timer() { _start_time = std::clock(); }
    void restart() { _start_time = std::clock(); }
    
    double elapsed() const 
    { return double(std::clock() - _start_time) / CLOCKS_PER_SEC; }
    
    double elapsed_min() const
    { return double(1) / double(CLOCKS_PER_SEC); }
    
    double elapsed_max() const
    { 
        return (double((std::numeric_limits<std::clock_t>::max)()) - 
              double(_start_time)) / double(CLOCKS_PER_SEC);
    }
private:
    std::clock_t _start_time;
};
```



## 使用建议

timer不适用于高精度和大跨度的时间测量任务，其精度依赖于操作系统或编译器。
