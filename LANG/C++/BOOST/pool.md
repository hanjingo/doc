[TOC]

# 内存池



## pool

pool是最简单，最容易使用的内存池类，它可以返回一个简单数据类型(POD)。它位于名字空间boost,需要包含的头文件如下:

```C++
#include <boost/pool/pool.hpp>
using namespace boost;
```

### API

| 函数                 | 说明             |
| -------------------- | ---------------- |
| `get_requested_size` | 分配内存块的大小 |
| `malloc`             | 分配内存         |
| `ordered_malloc`     |                  |
| `ordered_malloc`     |                  |
| `is_from`            |                  |
| `free`               | 归还内存         |
| `ordered_free`       |                  |
| `free`               |                  |
| `ordered_free`       |                  |
| `release_memory`     | 释放内存         |
| `purge_memory`       |                  |

### 用法

```c++
int main()
{
    pool<> p1(sizeof(int)); // 一个可分配int的内存池

    int *p = static_cast<int*>(p1.malloc()); // 必须把void*转换成需要的类型
    assert(p1.is_from(p));

    p1.free(p); // 释放内存池分配的内存块
    for (int i = 0; i < 100; ++i) // 连续分配大量的内存
    { p1.ordered_malloc(10); }
} // 内存池对象析构，所有分配的内存都在这里被释放
```

pool在分配内存失败的时候不会抛出异常，所以实际编写代码时应该检查malloc()函数返回的指针，以防止空指针发生错误。例:

```c++
int *p = static_cast<int*>(p1.malloc());
if (p != nullptr) {...}
```



## object_pool

object_pool是用于类实例(对象)的内存池，他的功能与pool类似，但它会在析构时对所有已经分配的内存块调用析构函数，从而正确地释放资源。
object_pool位于名字空间boost,需要包含的头文件如下:

```c++
#include <boost/pool/object_pool.hpp>
using namespace boost;
```

### API

| 函数        | 说明     |
| ----------- | -------- |
| `malloc`    | 分配内存 |
| `free`      | 归还内存 |
| `is_from`   |          |
| `construct` | 创建对象 |
| `destroy`   | 销毁对象 |

### 用法

```c++
struct demo_class
{
public:
    int a,b,c;

    demo_class(int x = 1, int y = 2, int z= 3):
        a(x),b(y),c(z){}
};

int main()
{
    object_pool<demo_class> p1;  // 对象内存池

    auto p = p1.malloc();        // 分配一个原始内存块
    assert(p1.is_from(p));

    // p指向的内存未经过初始化
    assert(p->a != 1 || p->b != 2 || p->c != 3);

    p = p1.construct(7, 8, 9);   // 构造一个对象，可以传递参数
    assert(p->a == 7);
    object_pool<string> pls;     // 定义一个分配string对象的内存池
    for (int i = 0; i < 10; ++i) // 连续分配大量string对象
    {
        string *ps = pls.construct("hello object_pool");
        cout << *ps << endl;
    }
} // 所有创建的对象在这里都被正确析构并释放内存
```



## singleton_pool

`singleton_pool`与`pool`的接口完全一致，可以用它分配简单数据类型(POD)的内存指针，但它是一个“单件”。
`singleton_pool`位于名字空间`boost`,需要包含的头文件如下:

```c++
#include <boost/pool/singleton_pool.hpp>
using namespace boost;
```

### API

| 函数             | 说明     |
| ---------------- | -------- |
| `is_from`        |          |
| `malloc`         | 分配内存 |
| `ordered_malloc` |          |
| `free`           | 归还内存 |
| `ordered_free`   |          |
| `free`           |          |
| `ordered_free`   |          |
| `release_memory` |          |
| `purge_memory`   |          |

### 用法

singleton_pool主要有两个模板参数(其余的可以使用默认值)：第一个参数Tag仅仅用于标记不同的单件，可以是空类，甚至可以只进行声明；第二个参数RequestedSize等同于pool构造函数中的整数requested_size，可以指示pool分配的内存块的大小。

```c++
struct pool_tag{};                                 // 仅仅用于标记的空类
typedef singleton_pool<pool_tag, sizeof(int)> sp1; // 内存池定义
int main()
{
    int *p = (int *)sp1::malloc();                 // 分配一个整数内存块
    assert(sp1::is_from(p));
    sp1::release_memory();                         // 释放所有未被分配的内存
} // sp1的内存直到程序结束才完全释放，而不是退出作用域
```

