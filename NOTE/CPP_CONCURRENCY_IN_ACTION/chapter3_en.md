# Chapter3 Sharing data between threads


<!-- vim-markdown-toc GFM -->

* [3.1 Problems with sharing data between threads](#31-problems-with-sharing-data-between-threads)
    - [3.1.1 Race condtions](#311-race-condtions)
    - [3.1.2 Avoiding problematic race conditions](#312-avoiding-problematic-race-conditions)
* [3.2 Protecting shared data with mutexes](#32-protecting-shared-data-with-mutexes)
    - [3.2.1 Using mutexes in C++](#321-using-mutexes-in-c)
    - [3.2.2 Structing code for protecting shared data](#322-structing-code-for-protecting-shared-data)
    - [3.2.3 Spotting race conditions inherent in interfaces](#323-spotting-race-conditions-inherent-in-interfaces)
    - [3.2.4 Deadlock: the problem and a solution](#324-deadlock-the-problem-and-a-solution)
    - [3.2.5 Further guidelines for avoiding deadlock](#325-further-guidelines-for-avoiding-deadlock)
    - [3.2.6 Flexible locking with std::unique_lock](#326-flexible-locking-with-stdunique_lock)
    - [3.2.7 Transferring mutex ownership between scopes](#327-transferring-mutex-ownership-between-scopes)
    - [3.2.8 Locking at an appropriate granularity](#328-locking-at-an-appropriate-granularity)
* [3.3 Alternative facilities for protecting shared data](#33-alternative-facilities-for-protecting-shared-data)
    - [3.3.1 Protecting shared data during initialization](#331-protecting-shared-data-during-initialization)
    - [3.3.2 Protecting rarely updated data structures](#332-protecting-rarely-updated-data-structures)
    - [3.3 Recursive locking](#33-recursive-locking)
* [3.4 Summary](#34-summary)

<!-- vim-markdown-toc -->

## 3.1 Problems with sharing data between threads

If all shared data is read-only, there's no problem, because the data read by one thread is unaffected by whether or not another thread is reading the same data.

### 3.1.1 Race condtions

data races cause the dreaded undefined behavior.

### 3.1.2 Avoiding problematic race conditions

Another option is to modify the design of your data structure and its invariants so that modifications are done as a series of inedivisible changes, each of which preserves the invariants. This is generally referred to as `lock-free programming` and is difficult to get right.



## 3.2 Protecting shared data with mutexes

### 3.2.1 Using mutexes in C++

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

*Listing 3.1 Protecting a list with a mutex*

Any code that has access to that pointer or reference can now access(and potentially modify) the protected data without locking the mutex.

### 3.2.2 Structing code for protecting shared data

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
            func(data);
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
    x.process_data(malicious_function);
    unprotected->do_something();
}
```

*Listing 3.2 Accidentally passing out a reference to protected data*

Don't pass pointers and references to protected data outside the scope of the lock, whether by returning them from a function, storing them in externally visible memory, or passing them as arguments to user-supplied functions.

### 3.2.3 Spotting race conditions inherent in interfaces

- OPTION 1: PASS IN A FEFERENCE
- OPTION 2: REQUIRE A NO-THROW COPY CONSTRUCTOR OR MOVE CONSTRUCTOR
- OPTION 3: RETURN A POINTER TO THE POPPED ITEM
- OPTION 4: PROVIDE BOTH OPTION 1 AND EITHER OPTION 2 OR 3

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

*Listing 3.5 A fleshed-out class definition for a thread-safe stack*

### 3.2.4 Deadlock: the problem and a solution

This is almost the opposite of a race dondition: rather than two threads racing to be first, each one is waiting for the other, so neither makes any progress.
.
all it takes is for two threads to try to exchange data between the same two instances with the parameters swapped, and you have deadlock!

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

*Listing 3.6 Using std::lock() and std::lock_guard in a swap operationa*

### 3.2.5 Further guidelines for avoiding deadlock

- AVOID NESTED LOCKS

    don't acquire a lock if you already hold one.

- AVOID CALLING USER-SUPPLIED CODE WHILE HOLDING A LOCK

    TODO

- ACQUIRE LOCKS IN A FIXED ORDER

    if two threds tried to traverse the list in reverse order using hand-over-hand locking, they could deadlock with each other in the middle of the list.    

- USE A LOCK HIERARCHY
    
    you divide your application into layers and identify all the mutexes that may be locked in any given layer. When code tries to lock a mutex, it isn't permitted to lock that mutex if it already holds a lock from a lower layer.

- EXTENDING THESE GUIDELINES BEYOND LOCKS

### 3.2.6 Flexible locking with std::unique_lock

`std::unique_lock` takes more space and is a fraction slower to use than `std::lock_guard`.

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

*Listing 3.9 Using std::lock() and std::unique_lock in a swap operation*

### 3.2.7 Transferring mutex ownership between scopes

`lvalue`: a real variable or reference to one.

`rvalue`: a temporary of some kind.

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

### 3.2.8 Locking at an appropriate granularity

The same applies to threads: if multiple threads are waiting for the same resource, then if any thread holds the lock for longer than necessary, it will increase the total time spent waiting(don't wait until you've reached the checkout to start looking for the cranberry sauce).

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

*Listing 3.10 Locking one mutex at a time in a comparison operator*

if you don't hold the required locks for the entire duration of an operation, you're exposing yourself to race conditions.



## 3.3 Alternative facilities for protecting shared data

### 3.3.1 Protecting shared data during initialization

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

*Listing 3.12 Thread-safe lazy initialization of a class member using std::call_once*

### 3.3.2 Protecting rarely updated data structures

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

*Listing 3.13 Protecting a data structure with a boost::shared_mutex*

### 3.3 Recursive locking

with `std::mutex` it's an error for a thread to try to lock a mutex it already owns, and attempting to do so will result in `undefined behavior`.



## 3.4 Summary


