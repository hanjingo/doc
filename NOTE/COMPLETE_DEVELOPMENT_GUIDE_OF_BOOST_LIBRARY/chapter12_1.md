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
compare_exchange_weak()和compare_exchange_strong()是exchange()的增强版本，也就是常说的CAS(compare-and-swap)操作。他们比较expected,如果相等则存值为desired,返回true/false表示原值是否被修改，但无论怎样，最后在expected变量里都会输出原值。两者的区别是compare_exchange_weak()的执行速度快，但使用它即使执行成功也可能会返回false；
```c++
atomic<long > l(100);

long v = 100;							// 设置变量expected,左值
if (l.compare_exchange_weak(v, 313))	// 比较并交换
{
	assert(l == 313 && v == 100);
}

v = 200;
auto b = l.compare_exchange_strong(v, 99);
assert(!b && v == 313);

l.compare_exchange_weak(v, 99);
assert(1 == 99 && v == 313);
```

## 整数用法
例：
```c++
atomic<int> n(100);

assert(n.fetch_add(10) == 100);
assert(n == 110);

assert(++n == 111);
assert(n++ == 111);
assert(n == 112);
assert((n -= 10) == 102);

atomic<int> b{BOOST_BINARY(0110)};

auto x = b.fetch_and(BOOST_BINARY(0110));
assert(x == BOOST_BINARY(1101) && 
				b == BOOST_BINARY(0100));
assert((b |= BOOST_BINARY(1001))
				== BOOST_BINARY(1101));
```

## 并发顺序一致性
atomic库在头文件<boost/memory_order.hpp>里定义了内存访问顺序的概念，它是一个简单的枚举类型，允许用户自己控制代码顺序的一致性:
```c++
enum memory_order
{
	memory_order_relaxed = 0,
	memory_order_consume = 1,
	memory_order_acquire = 2,
	memory_order_release = 4,
	memory_order_acq_rel = 6,
	memory_order_seq_cst = 14
}
```
实际上，atomic<T>的每个成员函数都有一个memory_order默认参数（操作符重载函数除外），他指定了院子操作的内存访问顺序要求:
```c++
template<typename T>
class atomic : public atomics::detail::base_atomic<T>
{
	public:
		T load(memory_order order = memory_order_seq_cst);
		void store(T value, memory_order order = momory_order_seq_cst);

		T exchange(T new_value, memory_order = momory_order_seq_cst);
		bool compare_exchange_weak(T & expected, T desired, memory_order);
        bool compare_exchange_strong(T & expected, T desired, memory_order);
}
```
例:
```c++
template<typename T>
class ref_count // 泛型的引用计数
{
private:
    typedef boost::atomic<int> atomic_type;
    mutable atomic_type m_count{0};                 // 初始化，注意是mutable
protected:
    ref_count(){}                                   // 这里不能使用default
    ~ref_count(){}
public:
    typedef boost::intrusive_ptr<T> counted_ptr;    // 定义intrusive_ptr

    void add_ref() const // 增加引用计数
    {
        m_count.fetch_add(
            1, boost::memory_order_relaxed);        // 不做任何顺序要求
    }

    void sub_ref() const // 减少引用计数
    {
        if (m_count.fetch_sub(
            1, boost::memory_order_release) == 1)
        {
            boost::atomic_thread_fence(
                boost::memory_order_acquire);
            delete static_cast<const T*>(this);
        }
    }

    decltype(m_count.load()) count() const          // 获取引用计数，注意decltype c++14里可以直接用auto推导取值，
                                                    // 也可以用隐式类型转换
    {
        return m_count.load();
    }
public:
    template<typename ... Args>                     // 可变参数模板
    static counted_ptr make_ptr(Args&& ... args)    // 工厂函数
    {
        return counted_ptr(new T(std::forward<Args>(args)...));
    }
private:
    friend void intrusive_ptr_add_ref(const T* p)
    {
        p->add_ref();
    }
    friend void intrusive_ptr_release(const T* p)
    {
        p->sub_ref();
    }
};

// ref_count的用法和intrusive_ref_counter一样，只要自定义类从它派生就会自动获得引用计数能力，能够被intrusive_ptr管理
class demo : public ref_count<demo>
{
public:
    demo () = default;
    ~demo () = default;
    int x;
};

int main()
{
    auto p = demo::make_ptr(); // 创建智能指针

    p->x = 10;
    assert(p->x == 10);
    assert(p->count() == 1); // 检查引用计数
}
```