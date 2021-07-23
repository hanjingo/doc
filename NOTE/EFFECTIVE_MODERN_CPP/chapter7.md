[TOC]

# 第七章 并发API

## 条款35: 优先选用基于任务而非基于线程的程序设计
- `std::thread`的API未提供直接获取异步运行函数返回值的途径，而且如果那些函数抛出异常，程序就会终止。
- 基于线程的程序设计要求手动管理线程耗尽，超订，负载均衡，以及新平台适配。
- 经由应用了默认启动策略的`std::async`进行基于任务的程序设计，大部分这类问题都能找到解决之道。

优先选用基于任务的程序设计，但是以下情况基于线程比较好：

- 需要访问底层线程实现的API
- 需要且有能力为应用优化线程用法
- 需要时心啊超越c++并发API的线程技术



## 条款36: 如果异步是必要的，则指定`std::launch::async`
- `std::launch::async` 启动策略意味着函数f必须以异步方式运行，亦即，在另一线程之上执行。
- `std::launch::deferred` 启动策略意味着函数f只会在`std::async`所返回的期值的get或wait得到调用时才运行。
- `std::async` 的默认启动策略既允许任务以异步方式执行，也允许任务以同步方式执行。
- 如此的弹性会导致使用`thread_local`变量时的不确定性，隐含着任务可能永远不会执行，还会影响运用了基于超时的wait调用的程序逻辑。
- 如果异步是必要的，则指定`std::launch::async`。

例：

```c++
template<typename F, typename... Ts>
inline
auto
reallyAsync(F&& f, Ts&&... params)
{
    return std::async(std::launch::async,
                      std::forward<F>(f),
                      std::forward<Ts>(params)...);
}
```



## 条款37: 使`std::thread`型别对象在所有路径皆不可联结
- 使`std::thread`型别对象在所有路径皆不可联结
- 在析构时调用join可能导致难以调试的性能异常
- 在析构时调用detach可能导致难以调试的未定义行为
- 在成员列表的最后声明`std::thread`型别对象

可联结：
- `std::thread`型别对象对应的底层线程处于阻塞或等待调度。
- `std::thread`型别对象对应的底层线程已运行至结束。

不可联结：
- 默认构造的`std::thread`。
- 已移动的`std::thread`。
- 已联结的`std::thread`。
- 已分离的`std::thread`。

例：

```c++
class ThreadRAII {
public:
    enum class DtorAction { join, detach };

    ThreadRAII(std::thread&& t, DtorAction a)
    : action(a), t(std::move(t)) {}

    ~ThreadRAII()
    { ... }

    ThreadRAII(ThreadRAII&&) = default;
    ThreadRAII& operator=(ThreadRAII&&) = default; // 移动操作
}
```



## 条款38：对变化多端的线程句柄析构函数行为保持关注
- 期值的析构函数在常规情况下，仅会析构期值的成员变量
- 指涉到经由`std::async`启动的未推迟任务的共享状态的最后一个期值会保持阻塞，直至该任务结束

期值析构函数的行为由与其关联的共享状态决定：

- 指涉到经由`std::async`启动的未推迟任务的共享状态的最后一个期值会保持阻塞，直到该任务结束。
- 其他所有值对象的析构函数只仅仅将期值对象析构就结束了。

只有在期值满足一下全部条件时才发挥作用：

- 期值所指涉的共享状态是由于调用了`std::async`才创建的。
- 该任务的启动策略是`std::launch::async`
- 该期值是指涉到该共享状态的最后一个期值



## 条款39：考虑针对一次性事件通信使用以void为模板型别实参的期值
- 如果仅为了实现平凡事件通信，基于条件变量的设计会要求多余的互斥量，这会给相互关联的检测和反应任务带来约束，并要求反应任务校验事件确已发生
- 使用标志位的设计可以避免上述问题，但这一设计基于轮询而非阻塞
- 条件变量和标志位可以一起使用，但这样的通信机制设计结果不甚自然
- 使用`std::promise`型别对象和期值就可以回避这些问题，但是一来这个途径为了共享状态需要使用堆内存，而且仅限于一次性通信

让反应任务等待检测任务的期值，例：

```c++
std::promise<void> p;

void detect()                               // 现在可以处理多个反应任务了
{
    auto sf = p.get_future().share();       // sf的型别是std::shared_future<void>

    std::vector<std::thread> vt;            // 反应任务的容器

    for (int i = 0; i < threadsToRun; ++i ) {
        vt.emplace_back([sf]{ sf.wait();    // sf局部副本之上的wait
                              react(); });
    }

    ...                                     // 若此处抛出异常，则detect会失去响应

    p.set_value();                          // 让所有线程取消暂停

    ...

    for (auto& t : vt) {                    // 把所有线程设置为不可联结状态
        t.join();
    }
}
```



## 条款40：对并发使用std::atomic,对特种内存使用volatile
- std::atomic用于多线程访问的数据，且不用互斥量。他是撰写并发软件的工具。
- volatile用于读写操作不可以被优化掉的内存。它是在面对特种内存时使用的工具。



