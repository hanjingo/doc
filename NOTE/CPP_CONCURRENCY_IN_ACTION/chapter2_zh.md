# 第二章 管理线程

[TOC]



## 基本线程管理

创建线程时，所提供的函数对象被复制（copied）到属于新创建的执行线程的存储器中，并从那里调用。

**如何创建一个线程**；例：

```c++
// 例1
// 声明了函数my_thread，
// 它接受单个参数（参数类型是指向不接受参数同时返回
// background_task对象的函数的指针），并返回
// std::thread对象，而不是启动一个新线程
std::thread my_thread(background_task());

// 例2
// 额外的括号避免其解释为函数声明，从而让my_thread被声明
// 为std::thread类型的变量
std::thread my_thread((background_task()));

// 例3
// 使用新的统一初始化语法，用大括号而不是括号
std::thread my_thread{background_task()};
```

**如何处理：当线程函数持有局部变量的指针或引用，且当函数退出的时候线程尚未完成**；例：

```c++
struct func
{
  int& i;
  func(int& i_):i(i_){}
  
  void operator()()
  {
    for(unsigned j=0; j<1000000; ++j)
    {
      do_something(i); // 对悬空引用可能的访问
    }
  }
};
void oops()
{
  int some_local_state = 0;
  func my_func(some_local_state);
  std::thread my_thread(my_func);
  my_thread.detach();	// 不等待线程完成
}	// 新的线程可能仍在运行
```

一个常见的处理这种情况的方式是使线程函数自包含，并且把数据复制（copy）到该线程中而不是共享数据。

### 等待线程完成

调用`join()`等待线程完成，只能对一个给定的线程调用一次`join()`，一旦调用`join()`，此`std::thread`对象不再是可连接的，并且`joinable()`将返回`false`。

### 在异常环境下的等待

要确保在`std::thread`对象被销毁前已调用`join()`或`detach()`函数，如果在线程开始之后但在调用`join()`之前引发了异常，对`join()`的调用就容易被跳过。

要解决上面的问题，可以用以下方法：

1. 使用`try/catch`来处理异常，例：

   ```c++
   struct func;
   void f()
   {
     int some_local_state = 0;
     func my_func(some_local_state);
     std::thread t(my_func);
     try
     {
       do_something_in_current_thread();
     }
     catch(...)
     {
       t.join();
       throw;
     }
     t.join();
   }
   ```

2. 使用标准的**资源获取即初始化(RAII)**惯用语法，并提供一个类，在它的析构函数中进行`join()`，例：

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
     thread_guard(thread_guard const&) = delete;
     thread_guard& operator=(thread_guard const&) = delete;
   };
   struct func;
   void f()
   {
     int some_local_state = 0;
     func my_func(some_local_state);
     std::thread t(my_func);
     thread_guard g(t);
     
     do_something_in_current_thread();
   }
   ```
   
   ### 在后台运行线程
   
   在`std::thread`对象上调用`detach()`会把线程丢在后台运行，也没有直接的方法与之通信。例：
   
   ```c++
   void edit_document(std::string const& filename)
   {
     open_document_and_display_gui(filename);
     while (!done_editing())
     {
       user_command cmd = get_user_input();
       if (cmd.type == open_new_document)
       {
         std::string const new_name = get_filename_from_user();
         std::thread t(edit_document, new_name);
         t.detach();
       }
       else
       {
         process_user_input(cmd);
       }
     }
   }
   ```
   
   
   
   ## 传递参数给线程函数
   
   参数会以默认的方式被复制（copied）到内部存储空间。
   
   **如何解决：当传递引用来作为参数时，会自行复制引用指向的值**？
   
   1. 使用`std::ref`来包装被引用的参数，例：
   
      ```c++
      void update_data_for_widget(widget_id w, widget_data& data);
      void oops_again(widget_id w)
      {
        widget_data data;
        std::thread t(update_data_for_widget, w, std::ref(data));
        display_status();
        t.join();
        process_widget_data(data);
      }
      ```
   
   2. 使用智能指针`std::unique_ptr`来限制所有权，使用`std::move`来转移所有权，例：
   
      ```c++
      void process_big_object(std::unique_ptr<big_object>);
      
      std::unique_ptr<big_object> p(new big_object);
      p->prepare_data(42);
      std::thread t(process_big_object, std::move(p));
      ```



## 转移线程的所有权

`std::thread`支持移动。意味着线程的所有权可以很容易的从一个函数中被转移出来，例：

```c++
std::thread f()
{
  void some_function();
  return std::thread(some_function);
}
std::thread g()
{
  void some_other_function(int);
  std::thread t(some_other_function, 42);
  return t;
}
```

如果要把所有权转移到函数中，它只能以值形式接受`std::thread`的实例作为其中一个参数，例：

```c++
void f(std::thread t);
void g()
{
  void some_function();
  f(std::thread(some_function));
  
  std::thread t(some_function);
  f(std::move(t));
}
```

支持移动的好处是：可以避免`thread_guard`对象在引用它的线程结束后继续存在所造成的不良影响，同时也意味着一旦所有权转移到了该位置，那么其他对象都不可以结合或分离该线程。

如何确保在退出一个作用域之前线程都已完成，例：

```c++
class scoped_thread
{
  std::thread t;
public:
  explicit scoped_thread(std::thread t_) : 
  	t(std::move(t_))
  {
    if (!t.joinable())
      throw std::logic_error("No thread");
  }
  ~scoped_thread();
  {
    t.join();
  }
  scoped_thread(scoped_thread const&) = delete;
  scoped_thread& operator=(scoped_thread const&) = delete;
};
struct func;
void f()
{
  int some_local_state;
  scoped_thread t(std::thread(func(some_local_state)));
  do_something_in_current_thread();
}
```

如何生成一批线程并等待它们完成，例：

```c++
void do_work(unsigned id);
void f()
{
  std::vector<std::thread> threads;
  for (unsigned i = 0; i < 20; ++i)
  {
    threads.push_back(std::thread(do_work, i));
  }
  std::for_each(threads.begin(), threads.end(),
                std::mem_fn(&std::thread::join));
}
```



## 在运行时选择线程数量

`std::thread::hardware_currency()`:返回一个对于给定程序执行时能够真正并发运行的线程数量的指示

例：std::accumulate的简单的并行版本：

```c++
template<typename Iterator, typename T>
struct accumulate_block
{
  void operator()(Iterator first, Iterator last, T& result)
  {
    result = std::accumulate(first, last, result);
  }
};

template<typename Iterator, typename T>
T parallel_accumulate(Iterator first, Iterator last, T init)
{
  unsigned long const length = std::distance(first, last);
  if (!length)
    return init;
  unsigned long const min_per_thread = 25;
  unsigned long const max_threads = 
    (length + min_per_thread - 1) / min_per_thread;
  
  unsigned long const hardware_threads = 
    std::thread::hardware_concurrency();
  
  // 要运行的线程数 = min(计算出的最大值, 硬件线程数量)
  unsigned long const num_threads = 
    std::min(hardware_threads != 0 ? hardward_threads : 2,
             max_threads);
  unsigned long const block_size = length / num_threads;
  std::vector<T> results(num_threads);
  std::vector<std::thread> threads(num_threads - 1);
  
  Iterator block_start = first;
  for (unsigned long i = 0; i < (num_threads - 1); ++i)
  {
    Iterator block_end = block_start;
    std::advance(block_end, block_size);
    threads[i] = std::thread(
      accumulate_block<Iterator, T>(),
    	block_start, block_end, std::ref(results[i]));
    block_start = block_end;
  }
  accumulate_block<Iterator, T>()(
  	block_start, last, results[num_threads - 1]);
  std::for_each(threads.begin(), threads.end(),
                std::mem_fn(&std::thread::join));
  return std::accumulate(results.begin(), results.end(), init);
}
```

超额订阅（oversubscription）：运行比硬件所能支持的更多的线程。



## 标识线程

线程标识符是`std::thread::id`类型，有2种获取方式：

- 通过从与之相关联的`std::thread`对象中调用`get_id()`获得。
- 线程构建时返回。

