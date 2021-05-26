# 第四章 同步并发操作

[TOC]



## 等待事件或其他条件

如果一个线程正等待着第二个线程完成一项任务，那么它有以下选择：

1. 一直检查共享数据（由互斥元保护）中的标识，并且让第二个线程在完成任务时设置该标识
2. 使用`std::this_thread::sleep_for()`，让等待中的线程在检查之间休眠一会
3. 使用c++标准库提供的工具来等待事件本身。

### 用条件变量等待条件

头文件`<condition_variable>`

- `std::condition_variable`

  仅限于和`std::mutex`一起工作

- `std::condition_variable_any`

  可以与复合成为类似互斥元的最低标准的任何东西一起工作，此函数更加普遍，但是有性能代价；除非必要，应该首选`std::condition_variable`

使用`std::condition_variable`等待数据：

```c++
std::mutex mut;
std::queue<data_chunk> data_queue; // 用来给线程间传递数据
std::condition_variable data_cond;
void data_preparation_thread()
{
  while(more_data_to_prepare())
  {
    data_chunk const data=prepare_data();
    std::lock_guard<std::mutex> lk(mut);
    data_queue.push(data);
    data_cond.notify_one();	// 通知等待中的线程
  }
}
void data_processing_thread()
{
  while(true)
  {
    std::unique_lock<std::mutex> lk(mut);
    data_cond.wait(lk, []{return !data_queue.empty();});
    data_chunk data=data_queue.front();
    data_queue.pop();
    lk.unlock();
    process(data);
    if (is_last_chunk(data))
      break;
  }
}
```

当等待线程重新获取互斥元并检查条件时，如果它并非直接响应另一个线程的通知，这就是所谓的伪唤醒(spurious wake)。

### 使用条件变量建立一个线程安全队列

使用条件变量的线程安全队列的完整类定义

```c++
#include <queue>
#include <memory>
#include <mutex>
#include <condition_variable>
template<typename T>
class threadsafe_queue
{
private:
  mutable std::mutex mut;
  std::queue<T> data_queue;
  std::condition_variable data_cond;
public:
  threadsafe_queue()
  {}
  threadsafe_queue(threadsafe_queue const& other)
  {
    std::lock_guard<std::mutex> lk(other.mut);
    data_queue=other.data_queue;
  }
  void push(T new_value)
  {
    std::lock_guard<std::mutex> lk(mut);
    data_queue.push(new_value);
    data_cond.notify_one();
  }
  void wait_and_pop(T& value)
  {
    std::unique_lock<std::mutex> lk(mut);
    data_cond.wait(lk, [this]{return !data_queue.empty();});
    value=data_queue.front();
    data_queue.pop();
  }
  std::shared_ptr<T> wait_and_pop()
  {
    std::unique_lock<std::mutex> lk(mut);
    data_cond.wait(lk, [this]{return !data_queue.empty();});
    std::shared_prt<T> res(std::make_shared<T>(data_queue.front()));
    data_queue.pop();
    return res;
  }
  bool try_pop(T& value)
  {
    std::lock_guard<std::mutex> lk(mut);
    if (data_queue.empty())
      return false;
    value=data_queue.front();
    data_queue.pop();
    return true;
  }
  std::shared_ptr<T> try_pop()
  {
    std::lock_guard<std::mutex> lk(mut);
    if (data_queue.empty())
      returnj std::shared_ptr<T>();
    std::shared_PTR<T> res(std::make_shared<T>(data_queue.front()));
    data_queue.pop();
    return res;
  }
  bool empty() const
  {
    std::lock_guard<std::mutex> lk(mut);
    return data_queue.empty();
  }
};
```

由于锁定互斥元是一种可变的操作，故互斥元对象必须标记为mutable。



## 使用future等地一次性事件

c++标准库中有两类future，是由`<future>`库的头文件中声明的两个类模板实现的：

- 唯一future(unique futures, std::future<>)
- 共享future(shared futures, std::shared_future<>)

### 从后台任务中返回值

使用std::future获取异步任务的返回值：

```c++
#include <future>
#include <iostream>
int find_the_answer_to_ltuae();
void do_other_stuff();
int main()
{
  std::future<int> the_answer=std::async(find_the_answer_to_ltuae);
  do_other_stuff();
  std::cout<<"The answer is "<<the_answer.get()<<std::endl;
}
```

使用std::async来将参数传递给函数：

```c++
#include <string>
#include <future>
struct X
{
  void foo(int,std::string const&);
  std::string bar(std::string const&);
};
X x;
auto f1=std::async(&X::foo, &x, 42, "hello"); // 调用p->foo(42,"hello"),其中p是&x
auto f2=std::async(&X::bar, x, "goodbye"); // 调用tmpx.bar("goodbye"),其中tmpx是x的副本
struct Y
{
  double operator(){double};
};
Y y;
auto f3=std::async(Y{},3.14); // 调用tmpy(3.141),其中tmpy是从Y()移动构造的
auto f4=std::async(std::ref(y),2.718); // 调用y(2.718)
X baz(X&);
std::async(baz, std::ref(x)); // 调用baz(x)
class move_only
{
public:
  move_only();
  move_only(move_only&&);
  move_only(move_only const&) = delete;
  move_only& operator=(move_only&&);
  move_only& operator=(move_only const&) = delete;
  
  void operator()();
};
auto f5=std::async(move_only()); // 调用tmp(),其中tmp是从std::move(move_only())构造的
```

### 将任务与future相关联

std::packaged_task<>将一个future绑定到一个函数或可调用对象上。当std::packaged_task<>对象被调用时，他就调用相关联的函数或可调用对象，并且让future就绪，将返回值作为关联数据存储。

std::packaged_task<>特化的部分类定义：

```c++
template<>
class packaged_task<std::string(std::vector<char>*, int)>
{
public:
  template<typename Callable>
  explicit packaged_task(Callable&& f);
  std::future<std::string> get_future();
  void operator()(std::vector<char>*, int);
}
```

使用std::packaged_task在GUI线程上运行代码：

```c++
#include <deque>
#include <mutex>
#include <future>
#include <thread>
#include <utility>
std::mutex m;
std::deque<std::packaged_task<void()> > tasks;
bool gui_shutdown_message_received();
void get_and_process_gui_message();
void gui_thread()
{
  while(!gui_shutdown_message_received())
  {
    get_and_process_gui_message();
    std::packaged_task<void()> task;
    {
      std::lock_guard<std::mutex> lk(m);
      if (tasks.empty())
        continue;
      task=std::move(tasks.front());
      tasks.pop_front();
    }
    task();
  }
}
std::thread gui_bg_thread(gui_thread);
template<typename Func>
std::future<void> post_task_for_gui_thread(Func f)
{
  std::packaged_task<void()> task(f); // 新建任务
  std::future<void> res=task.get_future(); // 从任务中获取future
  std::lock_guard<std::mutex> lk(m);
  tasks.push_back(std::move(task));
  return res;
}
```

### 生成std::promise

`std::promise<T>`提供一种设置值（类型T）方式，它可以在这之后通过相关联的`std::future<T>`对象进行读取。等待中的线程可以阻塞future，同时提供数据的线程可以使用配对中的promise项，来设置相关的值并使future就绪。

使用promise在单个线程中处理多个连接：

```c++
#include <future>
void process_connections(connection_set& connections)
{
  while(!done(connections))
  {
    for(connection_iterator connection=connections.begin(), end=connections.end();
        connection != end;
        ++connection)
    {
      if(connection->has_incoming_data())
      {
        data_packet data=connection->incoming();
        std::promise<payload_type>& p=connection->get_promise(data.id);
        p.set_value(data.payload);
      }
      if(connection->has_outgoing_data())
      {
        outgoing_packet data=connection->top_of_outgoing_queue();
        connection->send(data.payload);
        data.promise.set_value(true); // 传输成功
      }
    }
  }
}
```

### 为future保存异常

如果作为std::async一部分的函数调用引发了异常，该异常会被存储在future中，代替所存储的值，future变成就绪，并且对get()的调用会重新引发所存储的异常。

将异常存储置future的方式：

- 将函数封装入`std::packaged_task`的时候，当任务被调用时，如果封装的函数引发异常，该异常代替结果存入future，准备在调用get()时引发。
- 销毁与future关联的std::promise或std::packaged_task,而无需在promise上调用设置函数或是调用打包任务。在任何一种情况下，如果future尚未就绪，`std::promise`或`std::packaged_task`的析构函数会将具有`std::future_errc::broken_promise`错误代码的`std::future_error`异常存储在相关联的状态中。

### 等待自多个线程

`std::future`是**仅可移动的**，所以所有权可以在实例间转移，但是一次只有一个实例指向特定的异步结果。

`std::shared_future`实例是**可复制的**，因此可以有多个对象引用同一个相关状态。

![4-1]()



## 有时间限制的等待

