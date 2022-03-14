# 第3章 在线程间共享数据



## 线程之间共享数据的问题

如果所有的共享数据都是只读的，就没有问题，因为一个线程所读取的数据不受另一个线程是否正在读取相同的数据而影响。

### 竞争条件

**竞争条件（racecondition）**：用来表示**有问题的（problematic）**竞争条件。

**数据竞争（datarace）**：表示因对单个对象的并发修改而产生的特定类型的竞争条件，数据竞争造成可怕的**未定义行为（undefined behavior）**

### 避免有问题的竞争条件

**无锁编程（lock-free programming）**：修改数据结构的设计及其不变量，从而令修改作为一系列不可分割的变更来完成，每个修改均保留其不变量。

**事务（transaction）**：所需的一系列数据修改和读取被存储在一个事务日志中，然后在单个步骤中进行提交。

**软件事务内存（software transactional memory, STM）**：事务步骤的提交因为数据结构已被另一个线程修改而无法进行，该事务将重新启动。



## 用互斥元保护共享数据

### 使用c++中的互斥元

```c++
#include <list>
#include <mutext>
#include <algorithm>

std::list<int> some_list;
std::mutex some_mutex;

void add_to_list(int new_value)
{
  std::lock_guard<std::mutex> guard(some_mutex);
  some_list.push_back(new_value);
}
bool list_contains(int value_to_find)
{
  std::lock_guard<std::mutex> guard(some_mutex);
  return std::find(some_list.begin(), some_list.end(), value_to_find) != some_list.end();
}
```

**能够访问（并可能修改）该指针或引用的任意代码现在可以访问受保护的数据而无需锁定该互斥元。**

### 为保护共享数据精心组织代码

意外地传出对受保护数据的引用

```c++
class some_data
{
  int a;
  std::string b;
public:
  void do_something();
};

class data_wrapper
{
private:
  some_data data;
  std::mutex m;
public:
  template<typename Function>
  void process_data(Function func)
  {
    std::lock_guard<std::mutex> l(m);
    func(data); // 传递“受保护的”数据到用户提供的函数
  }
};
some_data* unprotected;
void malicious_function(some_data& protected_data)
{
  unprotected=&protected_data;
}
data_wrapper x;
void foo()
{
  x.process_data(malicious_function);	// 传入一个恶意函数
  unprotected->do_something();	// 对受保护的数据进行未受保护的访问
}
```

**不要对受保护数据的指针和引用传递到锁的范围之外，无论是通过从函数中返回它们，将其存放在外部可见的内存中，还是作为参数传递给用户提供的函数。**

### 发现接口中固有的竞争条件

消除竞争条件的方法：

1. 选项1:传入引用

   第一个选项是把你希望接受出栈值的变量的引用，作为参数传递给对pop()的调用。

   ```c++
   std::vector<int> result;
   some_stack.pop(result);
   ```

2. 选项2:要求不引发异常的拷贝构造函数或移动构造函数

   在编译时使用`std::is_nothrow_copy_constructible`和`std::is_nothrow_move_constructible`类型特征来检测一个不引发异常的拷贝或移动构造函数的存在。

3. 选项3:返回指向出栈项的指针

4. 选项4:同时提供选项1以及2或3

一个线程安全栈的详细类定义：

```c++
#include <exception>
#include <memory>
#include <mutex>
#include <stack>
struct empty_stack: std::exception
{
  const char* what() const throw();
};
template<typename T>
class threadsafe_stack
{
private:
  std::stack<T> data;
  mutable std::mutex m;
public:
  threadsafe_stack(){}
  threadsafe_stack(const threadsafe_stack& other)
  {
    std::lock_guard<std::mutex> lock(other.m);
    data = other.data; // 在构造函数体中执行复制
  }
  threadsafe_stack& operator=(const threadsafe_stack&) = delete;
  void push(T new_value)
  {
    std::lock_guard<std::mutex> lock(m);
    data.push(new_value);
  }
  std::shared_ptr<T> pop()
  {
    std::lock_guard<std::mutex> lock(m);
    if(data.empty()) throw empty_stack(); // 在试着出栈值的时候检查是否为空
    std::shared_ptr<T> const res(std::make_shared<T>(data.top())); // 在修改栈之前分配返回值
    data.pop();
    return res;
  }
  void pop(T& value)
  {
    std::lock_guard<std::mutex> lock(m);
    if (data.empty()) throw empty_stack();
    value = data.top();
    data.pop();
  }
  bool empty() const
  {
    std::lock_guard<std::mutex> lock(m);
    return data.empty();
  }
};
```

### 死锁：问题和解决方案

为避免死锁，常见的建议是始终使用相同的顺序锁定这两个互斥元。

在交换操作中使用`std::lock()`和`std::lock_guard`：

```c++
class some_big_object;
void swap(some_big_object& lhs, some_big_object& rhs);
class x
{
private:
  some_big_object some_detail;
  std::mutex m;
public:
  x(some_big_object const& sd):some_detail(sd) {}
  friend void swap(X& lhs, X& rhs)
  {
    if (&lhs==&rhs)
      return;
    std::lock(lhs.m, rhs.m);
    // 提供参数std::adopt_lock给互斥元，告知std::lock_guard对象该互斥元已被锁定，
    // 并且它们只应沿用互斥元上已有锁的所有权，而不是试图在构造函数中锁定互斥元。
    std::lock_guard<std::mutex> lock_a(lhs.m, std::adopt_lock);
    std::lock_guard<std::mutex> lock_b(rhs.m, std::adopt_lock);
    swap(lhs.some_detail, rhs.some_detail);
  }
};
```

### 避免死锁的进一步指南

1. 避免嵌套锁

   如果已经持有一个锁，就别再获取锁。

2. 在持有锁时，避免调用用户提供的代码

3. 以固定顺序获取锁

4. 使用锁层次

   将应用程序分层，并且确认所有能够在任意给定的层级上被锁定的互斥元。当代码试图锁定一个互斥元时，如果它在较低层已经持有锁定，那么就不允许它锁定该互斥元。

   使用锁层次来避免死锁：

   ```c++
   hierarchical_mutex high_level_mutex(10000);
   hierarchical_mutex low_level_mutex(5000);
   int do_low_level_stuff();
   int low_level_func()
   {
     std::locak_guard<hierarchical_mutex> lk(low_level_mutex);
     return do_low_level_stuff();
   }
   void high_level_stuff(int some_param);
   void high_level_func()
   {
     std::lock_guard<hierarchical_mutex> lk(high_level_mutex);
     high_level_stuff(low_level_func());
   }
   void thread_a() // 遵守规则
   {
     high_level_func();
   }
   hierarchical_mutex other_mutex(100);
   void do_other_stuff();
   void other_stuff()
   {
     high_level_func();
     do_other_stuff();
   }
   void thread_b()	// 未遵守规则
   {
     std::lock_guard<hierarchical_mutex> lk(other_mutex);
     other_stuff();
   }
   ```

   简单的分层次互斥元：
   
   ```c++
   class hierarchical_mutex
   {
     std::mutex internal_mutex;
     unsigned long const hierarchy_value;
     unsigned long previous_hierarchy_value;
     static thread_local unsigned long this_thread_hierarchy_value;
     void check_for_hierarchy_violation()
     {
       if (this_thread_hierarchy_value <= hierarchy_value)
         throw std::logic_error("mutex hierarchy violated");
     }
     void update_hierarchy_value()
     {
       previous_hierarchy_value=this_thread_hierarchy_value;
       this_thread_hierarchy_value=hierarchy_value;
     }
   public:
     explicit hierarchical_mutex(unsigned long value) :
     	hierarchy_value(value),
     	previous_hierarchy_value(0)
     {}
     void lock()
     {
       check_for_hierarchy_violation();
       internal_mutex.lock();
       update_hierarchy_value();
     }
     void unlock()
     {
       this_thread_hierarchy_value=previous_hierarchy_value;
       internal_mutex.unlock();
     }
     bool try_lock()
     {
       check_for_hierarchy_violation();
       if (!internal_mutex.try_lock())
         return false;
       update_hierarchy_value();
       return true;
     }
   };
   thread_local unsigned long 
     hierarchical_mutex::this_thread_hierarchy_value(ULONG_MAX);
   ```
   
5. 将这些设计准则扩展到锁之外

### 用std::unique_lock灵活锁定

在交换操作中使用std::lock()和std::unique_lock：

```c++
class some_big_object;
void swap(some_big_object& lhs, some_big_object& rhs);
class x
{
private:
  some_big_object some_detail;
  std::mutex m;
public:
  x(some_big_object const& sd) : some_detail(sd) {}
  friend void swap(x& lhs, x& rhs)
  {
    if(&lhs==&rhs)
      return;
    // std::defer_lock保留互斥元为未锁定
    std::unique_lock<std::mutex> lock_a(lhs.m, std::defer_lock);
    std::unique_lock<std::mutex> lock_b(rhs.m, std::defer_lock);
    std::lock(lock_a, lock_b);	// 互斥元在这里被锁定
    swap(lhs.some_detail, rhs.some_detail);
  }
}
```

**注意：std::unique_lock占用更多空间且使用起来比std::lock_guard略慢**

### 在作用域之间转移锁的所有权

如果源为右值，则所有权转移是自动的，而对于左值，所有权转移必须是显式完成，以避免从变量中意外的转移了所有权。

例：

```c++
std::unique_lock<std::mutex> get_lock()
{
  extern std::mutex some_mutex;
  std::unique_lock<std::mutex> lk(some_mutex);
  prepare_data();
  return lk;	// 函数内声明的变量可以直接返回，而无需调用
}
void process_data()
{
  std::unique_lock<std::mutex> lk(get_lock());
  do_something();
}
```

### 锁定在恰当的粒度

```c++
void get_and_process_data()
{
  std::unique_lock<std::mutex> my_lock(the_mutex);
  some_class data_to_process=get_next_data_chunk();
  my_lock.unlock();	// 在对process()的调用中不需要锁定互斥元
  result_type result=process(data_to_process);
  my_lock.lock();	// 重新锁定互斥元以回写结果
  write_result(data_to_process, result);
}
```

**一般情况下，只应该以执行要求的操作所需的最小可能时间而去持有锁**

在比较运算符中每次锁定一个互斥元:

```c++
class Y
{
private:
  int some_detail;
  mutable std::mutex m;
  int get_detail() const
  {
    std::lock_guard<std::mutex> lock_a(m);
    return some_detail;
  }
public:
  Y(int sd):some_detail(sd){}
  friend bool operator==(Y const& lhs, Y const& rhs)
  {
    if (&lhs==&rhs)
      return true;
    int const lhs_value=lhs.get_detail();
    int const rhs_value=rhs.get_detail();
    return lhs_value==rhs_value;
  }
};
```

**如果你不能在操作的整个持续时间中持有所需的锁，你就把自己暴露在竞争条件中。**



## 用于共享数据保护的替代工具

### 在初始化时保护共享数据

使用互斥元进行线程安全的延迟初始化：

```c++
std::shared_ptr<some_resource> resource_ptr;
std::mutex resource_mutex;
void foo()
{
  std::unique_lock<std::mutex> lk(resource_mutex);	// 所有的线程在这里被序列化
  if (!resource_ptr)
  {
    resource_ptr.reset(new some_resource);	// 只有初始化需要被保护
  }
  lk.unlock();
  resource_ptr->do_something();
}
```

使用`std::call_once`的线程安全的类成员延迟初始化：

```c++
class x
{
private:
  connection_info connection_details;
  connection_handle connection;
  std::once_flag connection_init_flag;
  void open_connection()
  {
    connection=connection_manager.open(connection_details);
  }
public:
  x(connection_info const& connection_details_):
  	connection_details(connection_details_)
  {}
  void send_data(data_packet const& data) // 初始化
  {
    std::call_once(connection_init_flag, &x::open_connection, this);
    connection.send_data(data);
  }
  data_packet receive_data()
  {
    std::call_once(connection_init_flag, &x::open_connection, this);
    return connection.receive_data();
  }
};
```

### 保护很少更新的数据结构

使用`boost::share_mutex`保护数据结构：

```c++
#include <map>
#include <string>
#include <mutex>
#include <boost/thread/shared_mutex.hpp>
class dns_entry;
class dns_cache
{
  std::map<std::string, dns_entry> entries;
  mutable boost::shared_mutex entry_mutex;
public:
  dns_entry find_entry(std::string const& domain) const
  {
    boost::shared_lock<boost::shared_mutex> lk(entry_mutex); // 使用boost::share_lock<>来提供共享，只读访问
    std::map<std::string,dns_entry>::const_iterator const it=
      entries.find(domain);
    return (it==entries.end())?dns_entry():it->second;
  }
  void update_or_add_entry(std::string const& domain,
                           dns_entry const& dns_details)
  {
    std::lock_guard<boost::shared_mutex> lk(entry_mutex); // 表被更新时提供独占访问
    entries[domain]=dns_details;
  }
}
```

### 递归锁

在使用`std::mutex`的情况下，一个线程试图锁定其已经拥有的互斥元是错误的，将导致**未定义行为(undefined behavior)。**

**不推荐使用递归锁。**

