# C++指针

[TOC]

## 常量指针和指针常量

### 常量指针

常量指针：指针指向的对象是常量，那么指针所指的对象不能被更改，但是指针可以指向别处。

在C/C++中，常量指针是这样声明的：

```c++
const int *p;
int const *p;
```

**注意：指针指向的对象不能通过这个指针来修改，可是仍然可以通过原来的声明修改，也就是说常量指针可以被赋值为变量的地址。**

例：

```c++
int a = 5;
const int b = 8;
const int *c = &a; // 这是合法的，非法的是对c的使用
*c = 6;            // 非法，但可以这样修改c指向的对象的值：a = 6;
const int *d = &b; // b是常量，d可以指向b，d被赋值为b的地址是合法的
```

### 指针常量

指针常量：指针是一个常量，这个指针无法指向别处，但是其指向的值可以改变。

在C/C++中，指针常量这样声明：

```c++
int a;
int *const b = &a; //const放在指针声明操作符的右侧
```

**注意：因为指针常量是一个常量，在声明的时候一定要给它赋初始值。一旦赋值，以后这个常量再也不能指向别的地址。**

例：

```c++
char *a = "abcde1234";
char *b = "bcde";
char *const c = &a;
a[0] = 'x';  // 合法，我们并没有限制a为常量指针（指向常量的指针）
*c[0] = 'x'; // 合法，与上面的操作一致
```

### 指向常量的指针常量

指向常量的指针常量：一个指针常量，指向的对象也是一个常量；

在C/C++中，指向常量的指针常量这样声明：

```c++
const int a = 25;
const int * const b = &a;
```

例：

```c++
char *a = "abcde1234";
const char *b = "bcde";
char *const c = &a;
const char *const d = &b;

```



## 指针与引用的区别

- 指针是一个指向地址的变量，引用是地址的别名
- 引用使用时无需解引用`(*)`，指针需要解引用
- 引用只能在定义时被初始化一次，之后不可变；指针可以改变指向的地址
- 引用不能为空，指针可以为空
- `sizeof(引用)`：所指向对象的大小；`sizeof(指针)`：指针本身的大小
- 指针可以有多级`(**指针)`，引用只能是一级
- 指针需要分配内存区域，引用不需要
- `++`,`--`等操作的意义不一样



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

### get函数

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