# 第五章 c++内存模型和原子类型上操作



## 内存模型基础

内存模型包括两个方面：

- 基本结构方面
- 并发方面

### 对象和内存位置

- 每个变量都是一个对象，包括其他对象的成员。
- 每个对象占据至少一个内存位置。
- 如int或char这样的基本类型的变量恰好一个内存位置，不论其大小，即便它们相邻或是数组的一部分。
- 相邻的位域是相同内存位置的一部分。

![5-1](res/5-1.png)

### 

## c++中的原子操作及类型

**原子操作（atomic operation）：**一个不可分割的操作。

### 标准原子类型

标准原子类型的替代名称和它们所对应的`std::atomic<>`特化：

| 原子类型        | 对应的特化                        |
| --------------- | --------------------------------- |
| atomic_bool     | `std::atomic<bool>`               |
| atomic_char     | `std::atomic<char>`               |
| atomic_schar    | `std::atomic<signed char>`        |
| atomic_uchar    | `std::atomic<unsigned char>`      |
| atomic_int      | `std::atomic<int>`                |
| atomic_uint     | `std::atomic<unsigned>`           |
| atomic_short    | `std::atomic<short>`              |
| atomic_ushort   | `std::atomic<unsigned short>`     |
| atomic_long     | `std::atomic<long>`               |
| atomic_ulong    | `std::atomic<unsigned long>`      |
| atomic_llong    | `std::atomic<long long>`          |
| atomic_ullong   | `std::atomic<unsigned long long>` |
| atomic_char16_t | `std::atomic<char16_t>`           |
| atomic_char32_t | `std::atomic<char32_t>`           |
| atomic_wchar_t  | `std::atomic<wchar_t>`            |

标准库原理类型定义以及对应的内置类型定义：

| 原子typedef           | 对应的标准库typedef |
| --------------------- | ------------------- |
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

三种类型运算：

- 存储（store）操作
  - memory_order_relaxed
  - memory_order_release
  - memory_order_seq_cst
- 载入（load）操作
  - memory_order_relaxed
  - memory_order_consume
  - memory_order_acquire
  - memory_order_seq_cst
- 读-修改-写（read-modify-write）操作
  - memory_order_relaxed
  - memory_order_consume
  - memory_order_acquire
  - memory_order_release
  - memory_order_acq_rel
  - memory_order_seq_cst

### std::atomic_flag上的操作

类型为`std::atomic_flag`的对象必须用ATOMIC_FLAG_INIT初始化。这会将该标志初始化为清除状态。在这里没有其他的选择，此标志总是以清除开始。

```c++
std::atomic_flag f=ATOMIC_FLAG_INIT;
```

一旦标识对象初始化完成，你只能对它做三件事：销毁，清除或设置并查询其先前的值。

使用`std::atomic_flag`的自旋锁互斥实现：

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

### 基于std::atomic<bool>的操作



