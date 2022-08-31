# C++并发编程

[TOC]



## std::thread

### 创建线程

创建线程时，所提供的函数对象被复制（copied）到属于新创建的执行线程的存储器中，并从那里调用

```c++
// 老式的方法
std::thread my_thread(background_task());
// 新式创建线程的方法
std::thread my_thread{background_task()};
```

### 等待线程完成

调用`join()`等待线程完成，只能对一个给定的线程调用一次`join()`，一旦调用`join()`，此`std::thread`对象不再是可连接的，并且`joinable()`将返回`false`。

**注意：为了防止`std::thread`对象在线程开始之后，在调用`join()`之前引发异常，有2种方法预防这个问题：**

1. `try/catch`处理异常

   ```c++
   std::thread t(my_func);
   try
   {
   	...
   }
   catch(...)
   {
   	t.join();
   	throw;
   }
   t.join();
   ```

2. 用RAII语法

   ```c++
   class thread_guard
   {
     std::thread& t;
   public:
     explicit thread_guard(std::thread& t_) : t(t_) {}
     ~thread_guard()
     {
       if(t.joinable())
       {
         t.join();
       }
     }
     ...
   };
   std::thread t(...);
   thread_guard g(t);
   ```

### 线程分离

在`std::thread`对象上调用`detach()`会把线程丢在后台运行，也没有直接的方法与之通信。

```c++
std::thread t(...);
t.detach();
```

### 线程函数传参

参数会以默认的方式被复制（copied）到内部存储空间；当传递引用来作为参数时，会自行复制引用指向的值，有以下2个办法来避免：

1. 使用`std::ref`来包装被引用的参数

   ```c++
   void f(...);
   std::thread t(f, std::ref(...))
   ```

2. 使用智能指针`std::unique_ptr`来限制所有权，使用`std::move`来转移所有权

   ```c++
   void f(std::unique_ptr<...>);
   std::unique_ptr<...> p(new ...);
   std::thread t(f, std::move(p));
   ```

### 转移线程函数所有权

`std::thread`支持移动。意味着线程的所有权可以很容易的从一个函数中被转移出来。

```c++
void f(std::thread t);
std::thread t(...);
f(std::move(t));
```

### 在运行时选择线程数量

`std::thread::hardware_currency()`用来计算给定程序执行时能够真正并发运行的线程数量

```c++
unsigned long const hardware_threads = std::thread::hardware_concurrency();
```

### 标识线程

线程标识符是`std::thread::id`类型，有2种获取方式：

- 通过从与之相关联的`std::thread`对象中调用`get_id()`获得。
- 线程构建时返回。



## std::mutex

```c++
#include <mutext>
std::mutex m;
void f()
{
  std::lock_guard<std::mutex> guard(m);
  ...
}
```

### 如何避免死锁

- 使用相同的顺序锁定和解锁
- 尽量避免嵌套锁
- 使用锁层次
- 在持有锁时，避免调用用户提供的代码

### 转移锁的所有权

如果源为右值，则所有权转移是自动的，而对于左值，所有权转移必须是显式完成，以避免从变量中意外的转移了所有权。

```c++
std::unique_lock<std::mutex> get_lock()
{
  extern std::mutex m;
  std::unique_lock<std::mutex> lk(some_mutex);
  ...
  return lk;
}
void process_data()
{
  std::unique_lock<std::mutex> lk(get_lock());
  ...
}
```

### 使用`boost::share_mutex`保护很少更新的数据结构

```c++
#include <mutex>
#include <boost/thread/shared_mutex.hpp>

mutable boost::shared_mutex sm;
boost::shared_lock<boost::shared_mutex> lk(sm); // 提供共享，只读访问
```

### 递归锁

**不推荐使用递归锁。**



## std::atomic

| 操作类型                            | 分类                                                         |
| ----------------------------------- | ------------------------------------------------------------ |
| 存储（store）操作                   | memory_order_relaxed<br>memory_order_release<br>memory_order_seq_cst |
| 载入（load）操作                    | memory_order_relaxed<br>memory_order_consume<br>memory_order_acquire<br>memory_order_seq_cst |
| 读-修改-写（read-modify-write）操作 | memory_order_relaxed<br>memory_order_consume<br>memory_order_acquire<br>memory_order_release<br>memory_order_acq_rel<br>memory_order_seq_cst |

### `std::atomic_flag`

`std::atomic_flag`的对象类型必须用`ATOMIC_FLAG_INIT`初始化，一旦标识初始化完成，你只能对它做三件事：

- 销毁
- 清除（clear）
- 设置并查询其先前的值（test_and_set）

```c++
// 使用std::atomic_flag的自旋锁互斥实现：
class spinlock_mutex
{
  std::atomic_flag flag;
public:
  spinlock_mutex():
  	flag(ATOMIC_FLAG_INIT)
  {}
  void lock()
  {
    while(flag.test_and_set(std::memory_order_acquire));
  }
  void unlock()
  {
    flag.clear(std::memory_order_release);
  }
};
```

### `std::atomic`

`std::atomic`不能拷贝构造和拷贝赋值。

#### CAS

compare and swap，当前值与预期值一致时，存储新值，否则返回false

- compare_excahge_weak

  能更好的避免一个双重循环的执行

  ```c++
  bool expected=false;
  extern atomic<bool> b;
  auto result = b.compare_exchange_weak(expected, true)
  ```

- compare_exchange_strong

#### 指针运算

`std::atomic<T*>`提供`fetch_add()`和`fetch_sub()`操作，它们都是读-改-写操作，它们可以拥有任意的内存顺序标签，以及加入到一个释放序列中。指定的语序不可能是操作符的形式，因为没办法提供必要的信息：这些形式都具有memory_order_seq_cst语义。

```c++
class F{};
F f[5];
std::atomic<F*> p(f);
F* x=p.fetch_add(2); // p加2，并返回原始值
assert(p.load()==&f[2]);
```

### 原子操作的内存顺序

- memory_order_seq_cst
- memory_order_consume
- memory_order_acquire
- memory_order_release（获得-释放顺序）
- memory_order_acq_rel
- memory_order_relaxed（松散顺序）

### 栅栏

栅栏可以让自由操作变得有序

```c++
#include <atomic>
#include <thread>

std::atomic<bool> x, y;
std::atomic<int> z;
void write_x_then_y()
{
    x.store(true, std::memory_order_relaxed);
    std::atomic_thread_fence(std::memory_order_release); // 释放栅栏
    y.store(true, std::memory_order_relaxed);
}
void read_y_then_x()
{
    while(!y.load(std::memory_order_relaxed));
    std::atomic_thread_fence(std::memory_order_acquire); // 获取栅栏
    if (x.load(std::memory_order_relaxed))
        ++z;
}
int main()
{
    x=false;
    y=false;
    z=0;
    std::thread a(write_x_then_y);
    std::thread b(read_y_then_x);
    a.join();
    b.join();
    assert(z.load() != 0);
}
```



## std::future

类模板`std::future`提供访问异步操作结果的机制，所引用的共享状态不能与任何其它异步返回的对象共享：

1. 通过异步操作（`std::async`, `std::packaged_task`或`std::promise`）返回一个`std::future`对象。
2. 当异步操作完成后，通过`std::future`获取异步操作返回的值。

```c++
#include <iostream>
#include <future>
#include <thread>

int main(int argc, char* argv[])
{
    // 通过promise-future通道，返回future
    std::promise<int> p;
    std::future<int> f1 = p.get_future();
    std::thread([&p] {p.set_value_at_thread_exit(1);}).detach();
    f1.wait();
    std::cout << "wait for promise:" << f1.get() << std::endl;

    // 通过async返回future
    std::future<int> f2 = std::async(std::launch::async, []() {
        return 2;
    });
    f2.wait();
    std::cout << "wait for async:" << f2.get() << std::endl;

    // 通过package_task返回future
    std::packaged_task<int()> task([]() {
        return 3;
    }); // 包装
    std::future<int> f3 = task.get_future();
    std::thread(std::move(task)).detach();
    f3.wait();
    std::cout << "wait for packaged_task:" << f3.get() << std::endl;
}

```

### std::async

函数模板`std::async`异步运行函数，并返回最终保有该函数调用结果的`std::future`。

若使用`std::async`需要引用头文件`#include <future>`。

#### 调用策略

`std::launch`提供`std::async`的函数调用策略：

| std::launch             | 说明                                                         |
| ----------------------- | ------------------------------------------------------------ |
| `std::launch::asnyc`    | 异步求值，启动一个新的线程调用函数，该函数由新线程异步调用，并且将其返回值与共享状态的访问点同步。 |
| `std::launch::deferred` | 延迟求值，在访问共享状态时该函数才被调用，对函数的调用将推迟到返回的`std::future`的共享状态被访问时触发。 |

例：

```c++
#include <iostream>
#include <future>

int main(int argc, char* argv[])
{
    int i = 1;
    auto f1 = std::async([](int& n)->int {
        std::cout << "n = " << n << std::endl;
        return n * 2; // n = 2
    }, std::ref(i));
    i++;
    f1.wait();
    i++;
    std::cout << "i:" << i << ", f1:" << f1.get() << std::endl;

    i = 1;
    auto f2 = std::async(std::launch::deferred, [](int& n)->int{
        std::cout << "n = " << n << std::endl;
        return n * 2; // n = 3
    }, std::ref(i));
    i++;
    f2.wait();
    i++;
    std::cout << "i:" << i << ", f2:" << f2.get() << std::endl;

    i = 1;
    auto f3 = std::async(std::launch::async, [](int& n)->int{
        std::cout << "n = " << n << std::endl;
        return n * 2; // n = 2
    }, std::ref(i));
    i++;
    f3.wait();
    i++;
    std::cout << "i:" << i << ", f3:" << f3.get() << std::endl;
}
```

### std::promise

C++11中的模板类`std::promise`提供对值或异常的存储，通过与`std::future`配合，在线程之间传递值。

每个promise与共享状态关联，共享状态含有一些状态信息和可能仍未求值的结果，promise可以对共享状态做以下事情：

- 使就绪：promise存储结果或异常于共享状态。标记共享状态为就绪，并解除阻塞任何等待于该共享状态关联的future上的线程。
- 释放：promise放弃其对共享状态的引用。
- 抛弃：promise存储以`std::future_errc::broken_promise`为`error_code`的`std::future_error`类型异常，令共享状态为就绪，然后释放它。

**注意1：`std::promise`只应当使用一次。**

例：

```c++
#include <iostream>
#include <future>
#include <chrono>

int main(int argc, char* argv[])
{
    // 产生值
    std::promise<int> p;
    std::future<int> f = p.get_future();
    std::thread t1(std::bind([](std::promise<int>& p) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        p.set_value(1);
        //        p.set_value(2); // 报错，std::promise只能用一次
    }, std::move(p)));

    // 接收值
    std::thread t2(std::bind([](std::future<int>& f) {
        std::cout << "recv :" << f.get();
        //        std::cout << "recv :" << f.get(); // 报错，std::promise只能用一次
    }, std::move(f)));

    t1.join();
    t2.join();

    t1.join();
    t2.join();
}
```

### std::packaged_task

类模板`std::packaged_task`包装任何可调用目标（函数，lambda，bind表达式或其它函数对象），使能异步调用它。其返回值或所抛异常被存储于能通过`std::future`对象访问的共享状态中。

`std::packaged_task`将一个`future`绑定到一个函数或可调用对象上。当`std::packaged_task`对象被调用时，他就调用相关联的函数或可调用对象，并且让`future`就绪，将返回值作为关联数据存储。

**注意：如果需要开启异步任务，推荐使用async而不是package_task。**

例：

```c++
#include <iostream>
#include <future>

int fn(int a)
{
    return a + 2;
}

int main(int argc, char* argv[])
{
    // lambda
    std::packaged_task<int(int)>task1([](int a)->int {
        return a + 1;
    });
    auto f1 = task1.get_future();
    task1(1);
    std::cout << "lambda :" << f1.get() << std::endl;

    // bind
    std::packaged_task<int(int)>task2(std::bind(fn, std::placeholders::_1));
    auto f2 = task2.get_future();
    task2(1);
    std::cout << "bind :" << f2.get() << std::endl;

    // thread
    std::packaged_task<int(int)>task3(fn);
    auto f3 = task3.get_future();
    std::thread t(std::move(task3), 2);
    t.join();
    std::cout << "thread :" << f3.get() << std::endl;

    return a.exec();
}
```



## std::condition_variable

### 与`std::mutex`合作

```c++
#include <mutex>
#include <condition_variable>

// 由于锁定互斥元是一种可变的操作，故互斥元对象必须标记为mutable
mutable std::mutex m;
std::condition_variable cond;
void f1()
{
  std::lock_guard<std::mutex> lk(m);
  ...
  cond.notify_one();
}
void f2()
{
  std::lock_guard<std::mutex> lk(m);
  ...
  cond.wait(lk, []{ ... });
}
```

### 超时条件变量

```c++
#include <condition_variable>
#include <mutex>
#include <chrono>

std::condtion_variable cv;
std::mutex m;

auto const timeout=std::chrono::steady_clock::now()+std::chrono::milliseconds(500);
std::unique_lock<std::mutex> lk(m);
if(cv.wait_until(lk, timeout)==std::cv_status::timeout)
	break;
```

### 与std::future合作

```c++
TODO
```

### 与std::packaged_task合作

`std::packaged_task<>`将一个`future`绑定到一个函数或可调用对象上。当`std::packaged_task<>`对象被调用时，他就调用相关联的函数或可调用对象，并且让`future`就绪，将返回值作为关联数据存储。

```c++
#include <mutex>
#include <future>
#include <thread>

std::mutex m;
std::deque<std::packaged_task<void()> > tasks;
std::packaged_task<void()> task;

void f1()
{
  while (1) {
  	std::lock_guard<std::mutex> lk(m);
		task=std::move(tasks.front());
		tasks.pop_front();
		task();
  }
}
f1();

template<typename Func>
std::future<void> f2(Func f)
{
  std::packaged_task<void()> task(f); 		 // 新建任务
  std::future<void> res=task.get_future(); // 从任务中获取future
  std::lock_guard<std::mutex> lk(m);
  tasks.push_back(std::move(task));
  return res;
}
```

### std::condition_variable_any

可以与复合成为类似互斥元的最低标准的任何东西一起工作，此函数更加普遍，但是有性能代价；除非必要，应该首选`std::condition_variable`。



## 有锁并发

### 意义

- 多个线程可以并发的访问这个数据结构，线程可以对这个数据结构做相同或不同的操作，并且每一个线程都能在自己的自治域中看到该数据结构。
- 在多线程环境下，无数据丢失和损毁，所有的数据需要维持原样，且无条件竞争。

### 准则

在设计数据结构时，需要自行考虑以下问题：

- 锁的范围中的操作，是否允许在锁外执行
- 数据结构中不同的区域是否能被不同的互斥量所保护
- 所有操作都需要同级互斥量保护
- 能否对数据结构进行简单的修改，以增加并发访问的概率，且不影响操作语义

如何保证数据结构是线程安全的：

- 确保无线程能够看到，数据结构的“不变量”破坏时的状态。
- 小心那些会引起条件竞争的接口，提供完整操作的函数，而非操作步骤。
- 注意数据结构的行为是否会产生异常，从而确保“不变量”的状态稳定。
- 将死锁的概率降到最低。使用数据结构时，需要限制锁的范围，且避免嵌套锁的存在。



## 无锁并发

### 意义

- 为了实现最大程度的并发
- 健壮性

### 准则

- 使用`std::memory_order_seq_cst`作为原型
- 使用无锁内存回收模式
- 当心ABA问题
- 识别忙于等待的循环以及辅助其它线程



## 并发代码性能分析

- 处理器数量

  linux下可以使用`std::thread::hardwarre_concurrency()`来获取硬件支持的最大同时运行的线程数量

- 数据竞争

  - **高竞争(high contention)：**一个处理器已经准备好更新这个值，但是另一个处理器已经在做了，这就要等待另一个处理器更新，并且这个改动已经传播完成。
  - **低竞争(low contention)：**处理器很少需要互相等待。
  - **乒乓缓存(cacheping-pong)：**数据在各处理器的缓存间来回传递，如果处理器因为需要等待缓存而被挂起，在这个时间里处理器无法工作，严重影响程序的性能。

- 假共享

  处理器缓存的最小单位通常不是一个内存地址，而是一小块称为**缓存线(cacheline)**的内存。这些内存块一般大小为`32~64`字节，取决于具体的处理器。缓存只能处理缓存线大小的内存块，相邻地址的数据会被载入同一个缓存线。有时这是好事，线程访问的数据在同一个缓存线比分布在多个缓存线更好。但是如果缓存线内有不相关但需要被别的线程访问的数据，会导致严重的性能问题。

  **假共享(false sharing)：**一个线程在更改其访问的数据时，缓存线的所有权需要转移到其所在的处理器，而另一个线程所需的数据可能也在这个缓存线上，当它访问时缓存线又要再次转移。这个缓存线是两者共享的，然而其中的数据并不共享。通俗地说就是是一个线程访问的数据与另一个线程的靠的太近而导致的问题。

- 过度订阅和过多的任务切换

  频繁地切换任务会导致性能损失



## 定位并发错误

### 阅读源码

- 并发访问时，那些数据需要保护？
- 如何确定访问数据受到了保护？
- 是否会有多个线程同时访问这段代码？
- 这个线程获取了哪个互斥量？
- 其他线程可能获取哪些互斥量?
- 两个线程间的操作是否有依赖关系？如何满足这种关系？
- 这个线程加载的数据还是合法数据吗？数据是否被其他线程修改过？
- 当假设其他线程可以对数据进行修改，这将意味着什么？并且，怎么确保这样的事情不会发生？

### 测试

- 使用单线程调用`push()`或`pop()`，来去顶在一般情况下队列是否正常工作
- 其他线程调用`pop()`时，使用另一线程在空队列上调用`push()`
- 在空队列上，以多线程的方式调用`push()`
- 在满载队列上，以多线程的方式调用`push()`
- 在空队列上，以多个线程的方式调用`pop()`
- 在满载队列上，以多线程的方式调用`pop()`
- 在非满载队列上（任务数量小于线程数量），以多线程的方式调用`pop()`
- 当一线程在空队列上调用`pop()`的同时，以多线程的方式调用`push()`
- 当一线程在满载队列上调用`pop()`的同时，以多线程的方式调用`push()`
- 当多线程在空队列上调用`pop()`的同时，以多线程方式调用`push()`
- 当多线程在满载队列上调用`pop()`的同时，以多线程方式调用`push()`
- “多线程”是有多少线程（3个，4个，还是1024个？）
- 系统中是否有足够的处理器，能让每个线程运行在属于自己的处理器上
- 测试需要运行在哪种处理器架构上
- 在测试中如何对“同时”进行合理的安排



## 线程池的设计

job与thread分离

TODO



## 总结

1. 用`join()`来加入线程（等待），用`detach()`来分离线程（不等）。

2. 要确保`std::thread`对象被销毁前已经调用`join()`或`detach()`，如果在线程开始之后在调用`join()`之前引发异常，对`join()`的调用就容易被跳过。

3. 可以使用以下方法来给线程函数传递参数：

   - 使用`std::ref`包装
   - 使用`std::move`来转移所有权

4. 通过一下方法来获取线程标识符`std::thread::id`:

   - 通过从与之相关联的`std::thread`对象中调用`get_id()`获得。
   - 线程构建时返回。

5. 互斥元用法：`std::lock_guard<std::mutex> guard(mutex_obj)`

6. 可以通过以下方法来等待其他线程完成：

   - 使用条件变量`std::condition_variable`和`std::condition_variable_any`

7. 使用`std::future`来从线程中返回参数

8. 常用的原子操作：

   - load
   - store
   - exchange
   - compare
   - exchange

9. 无锁编程准则：

   - 使用`std::memory_order_seq_cst`作为原型
   - 使用无锁内存回收模式
   - 当心ABA问题
   - 识别忙于等待的循环以及辅助其它线程

10. **阿姆达尔定律(Amdahl's law)：**$P=\frac{1}{f_s + \frac{1 - f_s}{N}}$

    - $P$: 性能
    - $f_s$: "串行部分"
    - $N$: 处理器个数



## 参考

[1] Anthony Williams.C++并发编程实战

[2] [C++ Concurrency In Action](http://shouce.jb51.net/cpp_concurrency_in_action/)

[3] [cppreference.com](https://zh.cppreference.com/)

[4] [面试题 -- 如何设计一个线程池](https://segmentfault.com/a/1190000040631931)
