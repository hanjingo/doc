# Constructor,Destructors,and Assignment Operators

[TOC]

## 条款05 了解C++默默编写并调用哪些函数

编译器会自动为一个空类，声明一个copy构造函数，一个copy assignment操作符和一个析构函数；例：

```c++
class Empty {};
```

自动转化为：

```c++
class Empty {
public:
  Empty() { ... }                 // default构造函数
  Empty(const Empty& rhs) { ... } // copy构造函数
  ~Empty() { ... }                // 析构函数
  Empty& operator=(const Empty& rhs) { ... } // copy assignment操作符
};
```

