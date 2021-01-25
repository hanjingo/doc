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
如果