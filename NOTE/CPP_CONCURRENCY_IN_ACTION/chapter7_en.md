# Chapter7 - Designing lock-free concurrent data structures

[TOC]



## 7.1 Definitions and consequences

Algorithms and data structures that use mutexes, condition variables, and futures to synchronize the data are called `blocking`。

Data structures and algorighms that don't use blocking library functions are said to be `nonblocking`。

### 7.1.1 Types of nonblocking data structures

```c++
class spinlock_mutex
{
    std::atomic_flag flag;
public:
    spinlock_mutex() : 
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

*Listing 7.1 Implementation of spin-lock mutex using std::atomic_flag*

### 7.1.2 Lock-free data structures

