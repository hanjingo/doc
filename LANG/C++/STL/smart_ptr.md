[TOC]

# 智能指针

c++11开始提供三大智能指针：`scoped_ptr`，`shared_ptr`，`weak_ptr`

## scoped_ptr

TODO

## shared_ptr

shared_ptr与scoped_ptr一样包装了new操作符在堆上分配的动态对象，但它实现的是引用计数型的智能指针，
可以被自由地拷贝和赋值，当没有代码使用它时（引用计数为0），才删除被包装过的动态分配的对象。

### 构造函数

shared_ptr有多种形式的构造函数，可以应用于各种可能的情形：

- 无参的`shared_ptr()`: 创建一个持有空指针的`shared_ptr`。

- `shared_ptr(Y * p)`: 获得指向类型T的指针p的管理权，同时将引用计数量为1，这个构造函数要求Y类型必须能够转换为T类型。

  ```c++
  shared_ptr<int> sp(new int(10));
  ```

- `shared_ptr(shared_ptr const & r)`: 从另外一个`shared_ptr`获得指针的管理权，同时引用计数加1，结果是两个`shared_ptr`共享一个指针的管理权。

- `operator=`: 赋值操作符，可以从另外一个`shared_ptr`获得指针的管理权，其行为同拷贝构造函数。

  ```c++
  shared_ptr<int> sp(new int(10));
  shared_ptr<int> sp2 = sp;
  ```

- `shared_ptr(Y * p, D d)`: 其行为类似`shared_ptr(Y * p)`，但它使用参数d指定了析构时的定制删除器，而不是简单的`delete`。

- `aliasing`: 别名构造函数是不增加引用计数的特殊用法

### 工厂函数

### `get`函数

`get()`函数可以得到原始指针，并且没有提供指针算术操作，也不能管理`new[]`产生的动态数组指针。

例：

```c++
shared_ptr<int> spi(new int); // 一个int的shared_ptr
assert(spi); // 在bool语境中转换为bool值
*spi = 253; // 使用解引用操作符×

shared_ptr<string> sps(new string("smart")); // 一个string的shared_ptr
assert(sps->size() == 5); // 使用箭头操作符->

shared_ptr<int> dont_do_this(new int[10]); // 危险！不能正确释放内存
```

### reset函数

TODO

## weak_ptr

TODO
