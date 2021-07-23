[TOC]

# 第二章 auto

## 条款5:优先选用auto,而非显式型别声明
* auto变量必须初始化，基本上对会导致兼容性和效率问题的型别不匹配现象免疫，还可以简化重构流程，通常也比显式指定型别要少打一些字。
* auto型别的变量都有着条款2和条款6中所描述的毛病。

auto必须初始化，例：

```c++
int x1;      // 有潜在的未初始化风险
auto x2;     // 编译错误！必须有初始化物
auto x3 = 0; // 没问题
```

使用auto来表示只有编译器才掌握的型别，例：

```c++
auto derefUPLess = [](const std::unique_ptr<Widget>& p1, // 使用std::unique_ptr来指向形参对象
        const std::unique_ptr<Widget>& p2) { return *p1 < *p2; };
```

使用auto来表示lambda，例：

```c++
auto derefLess = 
    [](const auto& p1, // 可以应用于任何类似指针之物指涉到的值
       const auto& p2)
    { return *p1 < *p2; };
```



## 条款6:当auto推导的型别不符合要求时，使用带显式型别的初始化物习惯用法
* 隐形的代理型可以导致auto根据初始化表达式推导出“错误的”型别。
* 带显式型别的初始化物习惯用法强制auto推导出你想要的型别。

隐式代理型别可以导致auto类型推导错误，例：

```c++
std::vector<bool> features(const Widget& w);

Widget w;
auto highPriority = features(w)[5]; 
// 这里的highPriority不再是bool了,
// std::vector<bool>[]返回的是个std::vector<bool>::reference型别的对象

processWidget(w, highPriority); // 未定义行为!!!

// std::vector<bool>::reference的定义如下
namespace std {
    template <class Allocator>
    class vector<bool, Allocator> {
    public:
        ...
        class reference { ... };
        
        reference operator[](size_type n);
        ...
    };
}
```

可以使用强制初始化的方法避免上面的问题

```c++
auto highPriority = static_cast<bool>(features(w)[5]);
```
