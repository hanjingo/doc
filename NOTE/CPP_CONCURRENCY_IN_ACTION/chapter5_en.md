# Chapter - 5 The C++ memory model and operations on atomic types

<!-- vim-markdown-toc GFM -->

* [5.1 Memory model basics](#51-memory-model-basics)
    - [5.1.1 Objects and memory locations](#511-objects-and-memory-locations)
    - [5.1.2 Objects, memory locations, and concurrency](#512-objects-memory-locations-and-concurrency)
    - [5.1.3 Modification orders](#513-modification-orders)
* [5.2 Atomic operations and types in C++](#52-atomic-operations-and-types-in-c)
    - [5.2.1 The standard atomic types](#521-the-standard-atomic-types)
    - [5.2.2 Operations on std::atomic_flag](#522-operations-on-stdatomic_flag)
    - [5.2.3 Operations on std::atomic<bool>](#523-operations-on-stdatomicbool)

<!-- vim-markdown-toc -->



## 5.1 Memory model basics

### 5.1.1 Objects and memory locations

![5_1](res/5_1.png)

*Figure 5.1 The division of a struct into objects and memory locations*

 There are four important things to take away from this:

 - Every variable is an object, including those that are members of other objects.
 - Every object occupies *at least one* memory location.
 - Variables of fundamental type such as `int` or `char` are `exactly one` memory location, whatever their size, even if they're adjacent or part of an array.
 - Adjacent bit fields are part of the same memory location.

### 5.1.2 Objects, memory locations, and concurrency

In order to avoid the race condition, there has to be an enforced ordering between the accesses in the two threads. One way to ensure there's a defined ordering is to use mutexes as described in chapter3; if the same mutex is locked prior to both accesses, only one thread can access the memory location at a time, so one must happen before the other. The other way is to use the synchronization properties of `atomic` operations(see section 5.2 for the definition of atomic operations) either on the same or other memory locations to enforce an ordering between the accesses in the two threads. The use of atomic operations to enforce an ordering is described in section 5.3. If more than two threads access the same memory location, each pair of accesses must have a defined ordering.

If there's no enforced ordering between two accesses to single memory location from separate threads, one or both of those accesses is not atomic, and one or both is write, then this is a data race and causes undefined behavior.

### 5.1.3 Modification orders



## 5.2 Atomic operations and types in C++

An `atomic` operation is an indivisible operation. You can't observe such an operation half-done from any thread in the system; it's either done or not done. If the load operation that reads the value of an object is `atomic`, and all modifications to that object are also `atomic`, that load will retrieve either the initial value of the object or the value stored by one of the modifications.

### 5.2.1 The standard atomic types

*Table 5.1 The alternative  names for the standard atomic types and their corresponding `std::atomic<>` specializations*

| Atomic type     | Corresponding specialization    |
|-----------------|---------------------------------|
| atomic_bool     | std::atomic<bool>               |
| atomic_char     | std::atomic<char>               |
| atomic_schar    | std::atomic<signed char>        |
| atomic_uchar    | std::atomic<unsigned char>      |
| atomic_int      | std::atomic<int>                |
| atomic_uint     | std::atomic<unsigned>           |
| atomic_short    | std::atomic<short>              |
| atomic_ushort   | std::atomic<unsigned short>     |
| atomic_long     | std::atomic<long>               |
| atomic_ulong    | std::atomic<unsigned long>      |
| atomic_llong    | std::atomic<long long>          |
| atomic_ullong   | std::atomic<unsigned long long> |
| atomic_char16_t | std::atomic<char16_t>           |
| atomic_char32_t | std::atomic<char32_t>           |
| atomic_wchar_t  | std::atomic<wchar_t>            |

*Table 5.2 The standard atomic typedefs and their corresponding built-in typedefs*

| Atomic typedef | Corresponding Standard Library typedef |
|----------------|----------------------------------------|
TODO

it suffices to know that the operations are divided into three categories:

- Store operations, which can have `memory_order_relaxed`, `memory_order_release`, or `memory_order_seq_cst` ordering;
- Load operations, which can have `memory_order_relaxed`, `memory_order_sonsume`, `memory_order_acquire`, or `memory_order_seq_cst` ordering;
- Read-modify-write operations, which can have `memory_order_relaxed`, `memory_order_consume`, `memory_order_acquire`, `memory_order_release`, `memory_order_acq_rel`, or `memory_order_seq_cst` ordering.

### 5.2.2 Operations on std::atomic_flag

```c++
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

*Listing 5.1 Implementation of a spinlock mutex using std::atomic_flag*

### 5.2.3 Operations on std::atomic<bool>
