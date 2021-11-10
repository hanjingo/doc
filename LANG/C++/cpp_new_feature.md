# c++ 新特性

[TOC]

## enable_shared_from_this

若一个类T继承`std::enable_shared_from_this<T>`，则会为该类T提供成员函数：`shared_from_this`。当T类型对象t被一个名为pt的`std::shared_ptr<T>`类对象管理时，调用`T::shared_from_this`成员函数，将会返回一个新的`std::shared_ptr<T>`对象，它与pt共享t的所有权。

例：

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

## lambda

C++11的一大亮点就是引入了Lambda表达式，利用Lambda表达式，可以方便的定义和创建匿名函数；Lambda表达式完整的声明格式如下：

```c++
[捕获的外部变量] (形参) 是否可以修改捕获的变量值 异常-> return 返回类型{ ... }
```

**值捕获**

类似于值传递，被捕获的变量在Lambda表达式创建时通过值拷贝的方式传入，Lambda对传入值的修改**不影响**外部的值；例：

```c++
int main()
{
  int a = 123;
  auto f = [a]{ cout << a << endl; };
  f();
}
```

**引用捕获**

类似于引用传递，在被捕获的变量前加一个引用说明符`&`，Lambda对传入值的修改**会影响**外部的值；例：

```c++
int main()
{
  int a = 123;
  auto f = [&a] { cout << a << endl; }
  f();
}
```

**隐式捕获**

编译器根据函数体中的代码来推断需要捕获的变量，这种方式称之为隐式捕获；隐式捕获有2种方式：

- `[=]` 表示以值捕获的方式捕获外部变量
- `[&]` 表示以引用捕获的方式捕获外部变量

例：

```c++
int main()
{
  int a = 123;
  auto f1 = [=] { cout << a << endl; }; // 值捕获
  a = 456;
  auto f2 = [&] { cout << a << endl; }; // 引用捕获
  a = 789;
  f1(); // 输出123
  f2(); // 输出789
}
```

**混合方式**

Lambda支持多种捕获方式组合使用，捕获形式表：

| 捕获形式        | 说明                                                         |
| --------------- | ------------------------------------------------------------ |
| `[]`            | 不捕获任何外部变量                                           |
| `[变量名, ...]` | 默认以值的形式捕获指定的多个外部变量（用逗号分隔），如果引用捕获，需要显示声明（使用`&`说明符） |
| `[this]`        | 以值的形式捕获this指针                                       |
| `[=]`           | 以值的形式捕获所有外部变量                                   |
| `[&]`           | 以引用形式捕获所有外部变量                                   |
| `[=, &x]`       | 变量x以引用形式捕获，其余变量以传值形式捕获                  |
| `[&, x]`        | 变量x以值的形式捕获，其余变量以引用形式捕获                  |

**mutable**

在Lambda中，如果以传值方式捕获外部变量，则函数体中不能修改该外部变量，否则会引发编译错误；使用mutable可以避免编译错误，并且使Lambda修改值捕获的外部变量；例：

```c++
int main()
{
  int a = 123;
  auto f = [a]() mutable { cout << ++a; };
  cout << a << endl; // 输出：123
  f(); // 输出：124
}
```

**形参限制**

1. 参数列表中不能有默认参数
2. 不支持可变参数
3. 所有参数必须有参数名

---

## list-initialization

初始化类成员有2种方式：

- 初始化列表
- 构造函数赋值
  1. 初始化阶段
  2. 计算阶段

使用初始化列表的主要是基于性能考虑，初始化列表减少了一次调用默认构造函数的过程，对于数据密集型类，加速效果显著；

以下场合必须使用初始化列表：

- `常量成员` 因为常量只能初始化不能赋值，所以必须放在初始化列表里面；
- `引用类型` 引用必须在定义的时候初始化，并且不能重新赋值，所以也要写在初始化列表里面；
- `没有默认构造函数的类类型` 因为引用初始化列表可以不必调用默认构造函数来初始化，而是直接调用拷贝构造函数初始化；

成员变量的初始化顺序：

成员是按照它们在**类中出现**的顺序进行初始化，而不是按照它们在**初始化列表中出现**的顺序初始化；例：

```c++
struct foo
{
  int i;
  int j;
  foo(int x) : j(x), i(j) // i未定义
};
```

虽然j在初始化列表里面出现在i前面，但是i先于j定义，所以先初始化i，而此时j未初始化，导致i未定义；

---

## std::bind和std::function

`std::function`

可调用对象包装器，通过`std::function`对c++中各种可调用实体的封装，形成一个新的可调用对象；因为它可以延迟执行函数，所以比普通函数指针更加灵活和便利。

`std::bind`

把参数绑定到可调用对象，绑定后的结果以`std::function`保存。

- 绑定普通函数

  例：

  ```c++
  double my_divide(double x, double y) {return x/y;}
  auto fn_half = std::bind(my_divide, _1, 5);
  cout << fn_half(10) << '\n'; // 输出5
  ```

- 绑定类成员函数

  绑定类成员函数方法：`std::bind(成员函数指针, 对象地址, ...)`。

  例：

  ```c++
  struct Foo { 
    void print_sum(int n1, int n2){ cout << n1 + n2 << '\n'; }; 
    int data = 10;
  };
  int main() { 
    Foo foo; 
    auto f = std::bind(&Foo::print_sum, &foo, 95, std::placeholders::_1);
  	f(5); // 100
  }
  ```

- 绑定引用参数

  绑定引用参数方法：`std::bind(函数指针, ref(对象), ...)`。

  例：

  ```c++
  ostream & print(ostream &os, const string& s, char c) { os << s << c; return os; }
  int main() {
    vector<string> words{"hello", "world", "this", "is", "C++11"};
    char c = ' ';
    ostringstream os1;
    for_each(words.begin(), words.end(), bind(print, ref(os1), _1, c));
    cout << os1.str() << endl;
  }
  ```

---

## std::move和&&

`&&`

`&&`叫万能引用(或引用折叠)，右值经过`&&`传递之后，保持不变，依然为右值；

`std::move`

c++使用`std::move`把左值转换为右值，配合`&&`可以进行高效的参数传递；

在左值被转移之后，其值为空；例：

```c++
string str = "hello";
vector<std::string> v;
cout << "before:" << "\"" << str << "\"" << endl; // 输出"hello"
v.push_bak(std::move(str));
cout << "after:" << "\"" << str << "\"" << endl; // 输出""
```

---



## 参考

- [C++11新特性之十：enable_shared_from_this](https://blog.csdn.net/caoshangpa/article/details/79392878)
- [C++ 11 Lambda表达式](https://www.cnblogs.com/DswCnblog/p/5629165.html)
- [C++11新特性之六：list-initialization](https://blog.csdn.net/caoshangpa/article/details/79169930)
- [C++11新特性之七：bind和function](https://blog.csdn.net/caoshangpa/article/details/79173351)
- [cppreference.com-std::move](https://en.cppreference.com/w/cpp/utility/move)

