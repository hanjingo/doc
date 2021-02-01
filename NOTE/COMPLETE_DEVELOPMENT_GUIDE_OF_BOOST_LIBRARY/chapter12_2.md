# thread
thread库需要chrono库提供的时间概念来执行睡眠，等待操作，因此必须先编译chrono库，在jamfile里指定lib的语句如下:
```c++
lib boost_thread : boost_chrono : <name>boost_thread;
```
thread位于名字空间boost,需要包含头文件<boost/thread.hpp>,并定义BOOST_THREAD_VERSION宏:
```c++
#define BOOST_THREAD_VERSION 5
#include <boost/thread.hpp>
using namespace boost;
```

## mutex
互斥量(mutex)是一种用于线程同步的手段,它可以在多线程环境里防止多个线程同时操作共享资源。一旦一个线程锁定了互斥量，那么其他线程必须等待他解锁互斥量后才能访问共享资源。thread提供了6种互斥量类型:
- null_mutex: 无任何锁定功能的互斥量，它是空对象模式的应用。
- mutex: 独占式的互斥量，是最简单，最常用的互斥量类型。
- timed_mutex: 独占式的互斥量，但提供超时锁定功能。
- recursive_mutex: 递归式互斥量，可以多次锁定，相应地也需要多次解锁。
- recursive_timed_mutex: 递归式互斥量，同样增加了超时锁定功能。
- shared_mutex: multiple-reader/single-writer型的共享互斥量（又称读写锁）。
摘要:
```c++
class mutex : boost::noncopyable                    // 互斥量都不是可拷贝的
{
public:
    void lock();                                    // 锁定互斥量
    void unlock();                                  // 解锁互斥量

    bool try_lock();                                // 尝试锁定互斥量

    bool try_lock_for(const duration& rel_time);    // 限时尝试锁定
    bool try_lock_until(const time_point& t);       // 限时尝试锁定

    some_type native_handle();                      // 系统相关的handle
};
```
mutex对象在创建后就表示一个互斥量，成员函数lock()用于线程阻塞等待直至获得互斥量的所有权（锁定）；当线程使用完共享资源后应该及时使用unlock()解除对互斥量的锁定。

try_lock()尝试锁定互斥量，如果锁定成功则返回true,否则返回false,它是非阻塞的。

成员函数try_lock_for()和try_lock_until()只属于timed_mutex和recursive_timed_mutex,他们为try_lock()增加了时间等待的功能；阻塞等待一定的时间后视图锁定互斥量，如果到一定的时间后还未锁定互斥量则返回false。等待时间可以是从当前开始的相对时间（时间长度），也可以是一个绝对时间点。

### mutex用法
```c++
mutex mu;
try
{
    mu.lock();
    cout << "some operations" << endl;
    mu.unlock();
}
catch (...)
{
    mu.unlock();
}
```
直接使用mutex的成员函数来锁定互斥量不够方便，而且在发生异常导致退出作用域等情况下，很可能会导致未调用unlock(),所以通常要使用try-catch块保证解锁互斥量。

## time_mutex用法
如果不想因为mutex而阻塞线程，那么就可以使用timed_mutex,调用它的try_lock_for()或try_lock_until(),等待一个相对时间或绝对时间。在这段时间内如果获得了锁那么函数会立即返回true，否则超时返回false，表示未获得锁，线程此时就可以去做其他事情。
```c++
time_mutext mu;

auto flag = mu.try_lock_for(100_ms); // 等待100ms，使用自定义字面值
if (flag)                            // 检查是否成功锁定互斥量
{
    cout << "lock mutex">> << endl;  // 访问共享资源
    mu.unlock();                     // 解锁
}
```

## lock_guard
在构造时锁定互斥量，在析构时自动解锁，从而保证了互斥量的正确操作，避免遗忘解锁,它就像一个智能指针。摘要如下:
```c++
template<typename Mutex>                        // 模板参数可以是互斥量
class lock_guard : boost::noncopyable           // 不可拷贝
{
private:
    Mutex& m;                                   // 内部持有引用
public:
    explicit lock_guard(Mutex& m_);             // 构造锁定mutex
    lock_guard(Mutex& m_, boost::adopt_lock_t); // 不执行锁定但会解锁

    ~lock_guard();                              // 析构结果mutex
}
```
thread库还提供一个便捷函数with_lock_guard(),它可以使用lock_guard锁定互斥量执行一个函数，简化lock_guard的调用，其声明如下:
```c++
template <class Lockable, class Function, class... Args>
auto with_lock_guard(Lockable& m, Function& func, Args&&... args);
```
with_lock_guard()相当于:
```c++
{
    lock_guard<Lockable> g(m);
    return func(args...);
}
```

## unique_lock
lock_guard接口比较简单，thread库里还有一个用法更加复杂的unique_lock,他的类摘要如下:
```c++
template <typename Mutex>
class unique_lock
{
private:
    Mutex* m;
    bool is_locked;

public:
    unique_lock();
    ~unique_lock();

    unique_lock(Mutex& m);                          // 锁定互斥量
    unique_lock(Mutex& m, boost::adopt_lock_t);     // 不锁定互斥量，但会解锁
    unique_lock(Mutex& m, boost::defer_lock_t);     // 不锁定互斥量
    unique_lock(Mutex& m, boost::try_to_lock_t);    // 尝试锁定互斥量

    unique_lock(Mutex& m, const time_point& t);     // 超时锁定
    unique_lock(Mutex& m, const duration& t);       // 超时锁定

    void lock();                                    // 锁定互斥量
    void unlock();                                  // 解锁互斥量
    bool try_lock();                                // 尝试锁定互斥量
    bool try_lock_for(const duration& d);           // 限时尝试锁定
    bool try_lock_until(const time_point& t);       // 限时尝试锁定

    bool owns_lock() const;                         // 是否锁定了互斥量
    explicit operator bool() const;                 // 等价于owns_lock()

    Mutex* mutex() const noexcept;                  // 获取锁定的互斥量
    Mutex* release();                               // 不再管理互斥量
}
```

### 锁定选项
- defer_lock: is_locked=false,不执行锁定操作。
- try_to_lock: is_locked+false,执行try_lock。
- adopt_lock: is_locked=true,不执行锁定操作。

### 工厂函数
```c++
// 4种不同的工厂函数对应不同的构造函数
unique_lock<Lockable> make_unique_lock(Lockable& mtx);
unique_lock<Lockable> make_unique_lock(Lockable& mtx, adopt_lock_t);
unique_lock<Lockable> make_unique_lock(Lockable& mtx, defer_lock_t);
unique_lock<Lockable> make_unique_lock(Lockable& mtx, try_to_lock_t);

// 一次性产生多个unique_lock,以std::tuple返回
std::tuple<unique_lock<Lockable> ...>
make_unique_locks(Lockable& ...mtx);
```
例:
```c++
template <typename Lockable, typename D>
unique_lock<Lockable> my_make_lock(Lockable& mtx, D d)
{
    return unique_lock<Lockable>(mtx, d);
}
```

### 用法
```c++
mutex mu;
{
    auto g = make_unique_lock(mu);              // 工厂函数锁定互斥量
    assert(g.owns_lock());                      // 断言已经锁定
    cout << "some operations" << endl;
}

{
    auto g = make_unique_lock(mu, defer_lock);  // 暂不锁定互斥量
    assert(!g);                                 // 断言没有锁定

    assert(g.try_lock());                       // 尝试锁定
    assert(g);                                  // 断言已经锁定

    cout << "some operations" << endl;
}
timed_mutex tm;
{
    auto g = my_make_lock(tm, 100_ms);          // 限时100毫秒尝试锁定
    if (g)                                      // 检查是否成功锁定
    {
        cout << "lock timed mutex" << endl;
    }
}

auto g = make_unique_locks(mu, tm);             // 同时锁定多个互斥量
assert(std::tuple_size<decltype(g)>::value == 2);
```

## lock adapter
lock_guard和unique_lock大多数情况下需要搭配mutex使用，用于锁定互斥量，但因为他们是模板类，所以只要是符合Lockable概念-也就是有lock/unlock/try_lock接口的类（不一定是互斥量），都可以用于lock_guard和unique_lock,这样就能够很容易地锁定整个对象，实现原子性的事务操作。

thread库定义了几个lockable适配器类，方便我们实现Lockable概念。
- basic_lockable_adapter: 最简单的接口，提供lock/unlock。
- lockable_adapter: 基本的接口，增加try_lock功能。
- timed_lockable_adapter: 增加try_lock_for/try_lock_until。
这些适配器的声明如下:
```c++
template <typename BasicLockable>
class basic_lockable_adapter
{
public:
    void lock() const;
    void unlock() const;
};

template <typename Lockable>
class lockable_adapter: public basic_lockable_adapter<Lockable>
{
public:
    bool try_lock() const;
};

template <typename TimedLock>
class timed_lockable_adapter: public lockable_adapter<TimedLock>
{
public:
    bool try_lock_for(duration const& rel_time) const;
    bool try_lock_until(time_point const& abs_time) const;
};
```
例:
```c++
class account final : public lockable_adapter<mutex> // 使用mutex适配
{
private:
    atomic<int> m_money{0};

public:
    int sum() const 
    { return m_money; }

    void withdraw(int x)
    { m_money -= x; }

    void deposit(int x)
    { m_money += x; }
};

account a;
{
    auto g = make_unique_lock(a); // 无须其它mutex,自身即可锁定
    a.deposit(100);
    a.withdraw(20);
    assert(a.sum() == 80);
}

{
    auto b = make_unique_lock(a, try_to_lock);
    if (b)
    {
        a.withdraw(a.sum());
        assert(a.sum() == 0);
    }
}
```

## 线程对象
```c++
class thread
{
public:
    thread();
    explicit thread(F f);
    thread(F f, A1 a1, A2 a2,...);                  // 传递可调用对象及参数

    thread(thread&&) noexcept;                      // 转移构造函数
    thread& operator=(thread&&) noexcept;           // 转移赋值函数

    bool joinable() const;                          // 是否可join
    void join();                                    // 等待线程

    void detach();                                  // 分离线程

    bool try_join_for(const duration& rel_time);    // 超时等待，非c++标准
    bool try_join_until(const time_point& t);       // 超时等待，非c++标准

    void interrupt();                               // 中断线程，非c++标准
    bool interruption_requested() const;            // 是否被中断，非c++标准

    class id;                                       // 内部类线程id
    id get_id() const;                              // 获得线程id对象
    native_handle_type native_handle();             // 获得系统相关的操作handle

    static unsigned hardware_concurrency();         // 静态成员，获得可并发的核心数 
    static unsigned physical_concurrency();         // 静态成员，获得真实CPU的核心数
};

namespace this_thread {                             // 子名字空间 this_thread
    thread::id get_id();                            // 获得线程id对象
    void yield();                                   // 允许重调度线程
    void sleep_until(const time_point& t);          // 睡眠等待
    void sleep_for(const duration& d);              // 睡眠等待
}
```
thread对象是不可拷贝，不可比较的，但它支持转移(move)语义，有转移构造函数和转移赋值函数

还有一些其他函数:
- get_id(): 与thread同名的函数，用来获得thread::id。
- yield(): 指示当前线程放弃时间片，允许其他的线程运行。
- sleep_for(): 线程睡眠等待一小段时间。
- sleep_until(): 线程睡眠等待一个时间点。
其用法如下:
```c++
thie_thread::sleep_for(2_s);    // 睡眠2秒钟
cout << this_thread::get_id();  // 允许当前线程的id
this_thread::yield();           // 允许CPU调度让出线程执行权
```

## 使用线程