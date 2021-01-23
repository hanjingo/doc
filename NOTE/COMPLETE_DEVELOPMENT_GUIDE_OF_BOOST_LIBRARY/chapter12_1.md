# atomic
atomic库需要编译才能使用，在jamfile里指定lib的语句如下:
```c++
lib boost_atomic;
```
atomic位于名字空间boost,需要包含的头文件如下:
```c++
#include <boost/atomic.hpp>
using namespace boost;
```

## 类摘要
atomic库定义了基本模板类atomic<T>,其摘要如下:
```c++
template< typename T >
class atomic : public atomics::detail::base_atomic<T>
{
public:
    atomic() = default;
    explicit atomic(T v);

    atomic(atomic const&) = delete;
    atomic& operator=(atomic const&) = delete;

public:
    bool is_lock_free();

    void store(T value);
    T load();

    T operator=(T v) volatile;
    operator T() volatile const;

    T exchange(T new_value);
    bool compare_exchange_weak(T & excepted, T desired);
    bool compare_exchange_strong(T & expected, T desired);

    T& storage();
    T const& storage() const;
};
```
atomic可以把对类型T的操作原子化，但不是任意的类型都可以原子化，类型T如下:
- 标量类型(scalar),如c++内建的算术类型，枚举，指针。
- 只有平凡(trivial)拷贝/转移构造，赋值和析构函数的类，并且可以使用memcmp执行比较操作-通常这样的类都是POD
atomic<T>还针对整数类型和指针类型进行了特化，增加了一些特殊的操作:
```c++
tempalte< >
class atomic < I > // 对整型类型特化
{
public:
    ...
public:
    T fetch_add(T v); // 加法，返回原值
    T fetch_sub(T v); // 减法，返回原值
    T fetch_and(T v); // 逻辑与，返回原值
    T fetch_or (T v); // 逻辑或，返回原值
    T fetch_xor(T v); // 逻辑异或，返回原值

    T operator++();   // 自增操作
    T operator--();   // 自减操作
    ...
};

template< typename T >
class atomic< T* >             // 对指针类型特化
{
public:
    ...
public:
    T* fetch_add(ptrdiff_t v); // 指针加偏移，返回原值
    T* fetch_sub(ptrdiff_t v); // 指针减偏移，返回原值
};
```

## 基本用法
可以用2种方法创建atomic对象：有参数的构造函数创建有初值的atomic;而无参数的默认构造函数创建一个初值不确定的atomic(这种方式很危险，我们应当尽量避免)。
```c++
atomic<int> a(10);  // 初始化原子整数值为10
assert(a == 10);    // 隐式类型转换

atomic<long> 1;     // 默认构造
cout << 1 << endl;  // 初值不确定，在并发环境里很危险
```
atomic最重要的2个成员函数是store()和load(),他们以原子的方式存取atomic内部的值，不会因为并发访问导致数据不一致。atomic还是用操作符重载简化了store()和load()的调用方式：赋值等价于store(),而隐式转换等价于load()。
```c++
atomic<bool> b{false};  // 原子化bool
assert(!b.load());      // 显式调用load取值

b.store(true);          // 显式调用store存值
assert(b);              // 隐式类型转换，等价于load
```
对于exchange()函数，顾名思义，它原子化地“交换”2个值，在存值之后返回内部原有的值:
```c++
atomic<int> n(100);             // 原子化int
assert(n.exchange(200) == 100); // 存值的同时返回原值
assert(n == 200);               // 隐式类型转化，等价于load
```