# progress_timer

[TOC]



`progress_timer`继承自`timer`，会在析构时自动输出时间，不需要手动调用`elapsed()`。

添加以下语句以使用`progress_timer`：

```c++
#include <boost/progress.hpp>
using namespace boost;
```



## 用法

```c++
#include <boost/progress.hpp>
int main()
{
    {
    	boost::progress_timer t; // 声明对象1，自动开始计时
     	...
    }
    // 退出作用域，自动调用析构函数
    {
        boost::progress_timer t; // 声明对象2，自动开始计时
        ...
    }
    // 退出作用域，自动调用析构函数
}
```



## 类摘要

```c++
class progress_timer : public timer, noncopyable
{
public:
    explicit progress_timer();
    progress_timer(std::ostream& os);
    ~progress_timer();
};
```

