# Chapter6 Designing lock-based concurrent data structures


<!-- vim-markdown-toc GFM -->

* [6.1 What does it mean to design for concurrency?](#61-what-does-it-mean-to-design-for-concurrency)
    - [6.1.1 Guidelines for designing data structures for concurrency](#611-guidelines-for-designing-data-structures-for-concurrency)
* [6.2 Lock-based concurrent data structures](#62-lock-based-concurrent-data-structures)
    - [6.2.1 A thread-safe stack using locks](#621-a-thread-safe-stack-using-locks)

<!-- vim-markdown-toc -->



## 6.1 What does it mean to design for concurrency?

No data will be lost or corrupted, all invariants will be upheld, and there'll be no problematic race conditions. Such a data structure is said to be `thread-safe`.

`serialization` threads take turns accessing the data protected by the mutex; they must access it serially rather than concurrently.

### 6.1.1 Guidelines for designing data structures for concurrency

you have two aspects to consider when designing data structures for concurrent access: ensuring that the accesses are safe and enabling genuine concurrent access:

- Ensure that no thread can see a state where the invariants of the data structure have been broken by the actions of another thread.
- Take care to avoid race conditions inherent in the interface to the data structure by providing functions for complete operations rather than for operation steps.
- Pay attention to how the data structure behaves in the presence of exceptions to ensure that the invariants are not broken.
- Minimize the opportunities for deadlock when using the data structure by restricting the scope of locks and avoiding nested locks where possible.

here's a list of questions to ask yourself as the data structure designer:

- Can the scope of locks be restricted to allow some parts of an operation to be performed outside the lock?
- Can different parts of the data structure be protected with different mutexes?
- Do all operations require the same level of protection?
- Can a simple change to the data structure improve the opportunities for concurrency without affecting the operational semantics?



## 6.2 Lock-based concurrent data structures

### 6.2.1 A thread-safe stack using locks

```c++
#include <exception>

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
    data=other.data;
  }

  threadsafe_stack& operator=(const threadsafe_stack&) = delete;

  void push(T new_value)
  {
    std::lock_guard<std::mutex> lock(m);
    data.push(std::move(new_value));  // 1
  }
  std::shared_ptr<T> pop()
  {
    std::lock_guard<std::mutex> lock(m);
    if(data.empty()) throw empty_stack();  // 2
    std::shared_ptr<T> const res(
      std::make_shared<T>(std::move(data.top())));  // 3
    data.pop();  // 4
    return res;
  }
  void pop(T& value)
  {
    std::lock_guard<std::mutex> lock(m);
    if(data.empty()) throw empty_stack();
    value=std::move(data.top());  // 5
    data.pop();  // 6
  }
  bool empty() const
  {
    std::lock_guard<std::mutex> lock(m);
    return data.empty();
  }
};
```

*Listing 6.1 A class definition for a thread-safe stack*


