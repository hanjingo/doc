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
    - [5.2.4 Operations on std::atomic<T*>: pointer arithmetic](#524-operations-on-stdatomict-pointer-arithmetic)
    - [5.2.5 Operations on standard atomic integral types](#525-operations-on-standard-atomic-integral-types)
    - [5.2.6 The std::atomic<> primary class template](#526-the-stdatomic-primary-class-template)
    - [5.2.7 Free functions for atomic operations](#527-free-functions-for-atomic-operations)
* [5.3 Synchronizing operations and enforcing ordering](#53-synchronizing-operations-and-enforcing-ordering)
    - [5.3.1 The synchronizes-with relationship](#531-the-synchronizes-with-relationship)
    - [5.3.2 The happens-before relationship](#532-the-happens-before-relationship)
    - [5.3.3 Memory ordering for atomic operations](#533-memory-ordering-for-atomic-operations)

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

| 原子typedef           | 对应的标准库typedef |
|-----------------------|---------------------|
| atomic_int_least8_t   | int_least8_t        |
| atomic_uint_least8_t  | uint_least8_t       |
| atomic_int_least16_t  | int_least16_t       |
| atomic_uint_least16_t | uint_least16_t      |
| atomic_int_least32_t  | int_least32_t       |
| atomic_uint_least32_t | uint_least32_t      |
| atomic_int_least64_t  | int_least64_t       |
| atomic_uint_least64_t | uint_least64_t      |
| atomic_int_fast8_t    | int_fast8_t         |
| atomic_uint_fast8_t   | uint_fast8_t        |
| atomic_int_fast16_t   | int_fast16_t        |
| atomic_uint_fast16_t  | uint_fast16_t       |
| atomic_int_fast32_t   | int_fast32_t        |
| atomic_uint_fast32_t  | uint_fast32_t       |
| atomic_int_fast64_t   | int_fast64_t        |
| atomic_uint_fast64_t  | uint_fast64_t       |
| atomic_intptr_t       | intptr_t            |
| atomic_uintptr_t      | uintptr_t           |
| atomic_size_t         | size_t              |
| atomic_ptrdiff_t      | ptrdiff_t           |
| atomic_intmax_t       | intmax_t            |
| atomic_uintmax_t      | uintmax_t           |


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

The compare/exchange operation is the cornerstone of programming with atomic types; it compares the value of the atomic variable with a supplied expected value and stores the supplied desired value if they're equal. If the values aren't equal, the expected value and stores the supplied desired value if they're equal. If the values aren't equal, the expected value is updated with the actual value of the atomic variable. The return type of the compare/exchange functions is a `bool`, which is `true` if the store was performed and false otherwise.

Because `compare_exchange_weak()` can fail spuriously, it must typically be used in a loop:

```c++
bool expected=false;
extern atomic<bool> b; // 设置些什么
while(!b.compare_exchange_weak(expected,true) && !expected);
```

### 5.2.4 Operations on std::atomic<T*>: pointer arithmetic

Beacuse both `fetch_add()` and `fetch_sub()` are read-modify-write operations, they can have any of the memory-ordering tags and can participate in a `release wequence`. Specifying the ordering semantics isn't possible for the operator forms, because there's no way of providing the onformation: these forms therefore always have `memory_order_seq_cst` semantics.

```c++
class Foo{};
Foo some_array[5];
std::atomic<Foo*> p(some_array);
Foo* x=p.fetch_add(2);  // p加2，并返回原始值
assert(x==some_array);
assert(p.load()==&some_array[2]);
x=(p-=1);  // p减1，并返回原始值
assert(x==&some_array[1]);
assert(p.load()==&some_array[1]);
```

The function forms also allow the memory-ordering semantics to be specified as an additional function call argument:

```c++
p.fetch_add(3,std::memory_order_release);
```

### 5.2.5 Operations on standard atomic integral types

### 5.2.6 The std::atomic<> primary class template

In order to use `std::atomic<UDT>` for some user-defined type UDT, this type must have a `trivial` copy-assignment operator. This means that the type must not have any virtual functions or virtual base classes and must use the compiler-generated copy-assignment operator. Not only that, but every base class and non-static data member of a user-defined type must also have a trivial copy-assignment operator. This essentially permits the compiler to use `memcpy()` or an equivalent operation for assignment operations, because there's no user-written code to run.

Finally, the type must be `bitwise equality comparable`. This goes alongside the assign-ment requirements; not only must you be able to copy an object of type UDT using `memcpy()`, but you must be able to compare instances for equality using `memcmp()`. 

don't pass pointers and references to protected data outside the scope of the lock by passing them as arguments to user-suplied functions.

### 5.2.7 Free functions for atomic operations

*Table 5.3 The operations available on atomic types*

| 操作                                       | atomic_flag | `atomic<bool>` | `atomic<T*>` | `atomic<integral-type>` | `atomic<other-type>` |
|--------------------------------------------|-------------|----------------|--------------|-------------------------|----------------------|
| test_and_set                               | *           |                |              |                         |                      |
| clear                                      | *           |                |              |                         |                      |
| is_lock_free                               |             | *              | *            | *                       | *                    |
| load                                       |             | *              | *            | *                       | *                    |
| store                                      |             | *              | *            | *                       | *                    |
| exchange                                   |             | *              | *            | *                       | *                    |
| compare_exchange_weak,<br>compare_exchange |             | *              | *            | *                       | *                    |
| fetch_add, `+=`                            |             |                | *            | *                       | *                    |
| fetch_sub, `-=`                            |             |                | *            | *                       |                      |
| fetch_or, `                                | =`          |                |              |                         | *                    |  |
| fetch_and, `&=`                            |             |                |              | *                       |                      |
| fetch_xor, `^=`                            |             |                |              | *                       |                      |
| `++`, `--`                                 |             |                | *            | *                       |                      |

example:

```c++
std::shared_ptr<my_data> p;
void process_global_data()
{
  std::shared_ptr<my_data> local=std::atomic_load(&p);
  process_data(local);
}
void update_global_data()
{
  std::shared_ptr<my_data> local(new my_data);
  std::atomic_store(&p,local);
}
```

## 5.3 Synchronizing operations and enforcing ordering

```c++
#include <vector>
#include <atomic>
#include <iostream>

std::vector<int> data;
std::atomic<bool> data_ready(false);

void reader_thread()
{
  while(!data_ready.load())  // 1
  {
    std::this_thread::sleep(std::milliseconds(1));
  }
  std::cout<<"The answer="<<data[0]<<"\m";  // 2
}
void writer_thread()
{
  data.push_back(42);  // 3
  data_ready=true;  // 4
}

```

*Listing 5.2 Reading and writing variables from different threads*

![5_2](res/5_2.png) 

*Figure 5.2 Enforcing an ordering between nonatomic operations using atomic operations *

### 5.3.1 The synchronizes-with relationship

The synchronizes-With relationship is something that you can get only between operations on atomic types.

### 5.3.2 The happens-before relationship

```c++
#include <iostream>
void foo(int a,int b)
{
  std::cout<<a<<”,”<<b<<std::endl;
}
int get_num()
{
  static int i=0;
  return ++i;
}
int main()
{
  foo(get_num(),get_num());  // 无序调用get_num()
}
```

*Listing 5.3 Order of evaluation of arguments to a function call is unspecified*

### 5.3.3 Memory ordering for atomic operations

These distinct memory-ordering models can have varying costs on different CPU architectures.

The availability of the distinct memory-ordering models allows expert to take advantage of the increased performance of the more fine-grained ordering relation-ships where they're advantageous while allowing the use of the default sequentially consistent ordering(which is considerably easier to reason about than the others) for those cases that are less critical.

**SEQUENTIALLY CONSISTENT ORDERING**

The default ordering is named `sequentially consistent` because it implies that the vehavior of the program is consistent with a simple sequential view of the world. If all operations on instances of atomic types are sequentially consisten, the behavior of a multithreaded program is as if all these operations were performed in some particular sequence by a single thread.

This ease of understanding can come at a price, though. On a weakly ordered machine with many processors, it can impose a noticeable performance penalty, beacuse the overall sequence of operations must be kept consistent between the processors, possibly requiring extensive (and expensive!) synchronization operations between the processors.

```c++
#include <atomic>
#include <thread>
#include <assert.h>

std::atomic<bool> x,y;
std::atomic<int> z;

void write_x()
{
  x.store(true,std::memory_order_seq_cst);  // 1
}

void write_y()
{
  y.store(true,std::memory_order_seq_cst);  // 2
}
void read_x_then_y()
{
  while(!x.load(std::memory_order_seq_cst));
  if(y.load(std::memory_order_seq_cst))  // 3
    ++z;
}
void read_y_then_x()
{
  while(!y.load(std::memory_order_seq_cst));
  if(x.load(std::memory_order_seq_cst))  // 4
    ++z;
}
int main()
{
  x=false;
  y=false;
  z=0;
  std::thread a(write_x);
  std::thread b(write_y);
  std::thread c(read_x_then_y);
  std::thread d(read_y_then_x);
  a.join();
  b.join();
  c.join();
  d.join();
  assert(z.load()!=0);  // 5
}
```

*Listing 5.4 Sequential consistency implies a total ordering*

TODO
