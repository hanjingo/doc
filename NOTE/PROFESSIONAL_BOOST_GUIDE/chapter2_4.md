# progress_display

`progress_display`用于在控制台上显示程序的执行进度，需要包含以下代码以使用`progress_display`：

```c++
#include <boost/progress.hpp>
using namespace boost;
```



## 类摘要

```c++
class progress_display : noncopyable
{
public:
    progress_display(unsigned long expected_count);
    progress_display(unsigned long expected_count,
                     std::ostream& os,
                     const std::string& s1 = "\n",
                     const std::string& s2 = "",
                     const std:;string& s3 = "");
    void restart(unsigned long expected_count);
    unsigned long operator+=(unsigned long increment);
    unsigned long operator++();
    unsigned long count() const;
    unsigned long expected_count() const; // 进度显示的基数
};
```



## 用法

```c++
#include <boost/progress.hpp>
using namespace boost;

int main()
{
    vector<string> v(100);
    ofstream fs("./test.txt");
    
    progress_display pd(v.size()); // 声明一个基数为v的对象
    
    // 遍历
    for (auto& x : v)
    {
        fs << x << endl;
        ++pd;
    }
}
```



## 注意事项

`progress_display`无法把进度显示输出与程序的输出分离。
