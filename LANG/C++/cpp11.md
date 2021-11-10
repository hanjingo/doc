# c++11 新特性

[TOC]

## enable_shared_from_this

若一个类T继承`std::enable_shared_from_this<T>`，则会为该类T提供成员函数：`shared_from_this`。当T类型对象t被一个名为pt的`std::shared_ptr<T>`类对象管理时，调用`T::shared_from_this`成员函数，将会返回一个新的`std::shared_ptr<T>`对象，它与pt共享t的所有权。

示例：

```c++
#include <memory>
#include <iostream>
struct Good : std::enable_shared_from_this<Good>
{
public:
    std::shared_ptr<Good> getptr() {
        return shared_from_this();
    }
    ~Good() { std::cout << "Good::~Good() called" << std::endl; }
};
int main()
{
    { // 限定作用域，确保智能指针在system("pause")之前析构
        std::shared_ptr<Good> gp1(new Good());
        std::shared_ptr<Good> gp2 = gp1->getptr();
        std::cout << gp1.use_count() << std::endl;
        std::cout << gp2.use_count() << std::endl;
    }
    system("pause");
}
```

---

## 列表初始化

TODO

---

## std::function

TODO

---



## 参考

- [C++11新特性之十：enable_shared_from_this](https://blog.csdn.net/caoshangpa/article/details/79392878)

