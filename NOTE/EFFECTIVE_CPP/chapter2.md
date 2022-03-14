# 2 Constructor,Destructors,and Assignment Operators

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

总结：

- 编译器可以暗自为class创建default构造函数，copy构造函数，copy assignment操作符，以及析构函数；



## 条款06 若不想使用编译器自动生成的函数，就该明确拒绝

将成员函数声明为private而且不实现它们，可以阻止人们调用它；例：

```c++
class HomeForSale {
public:
  ...
private:
  ...
  HomeForSale(const HomeForSale&); // 只声明不实现
  HomeForSale& operator=(const HomeForSale&); // 只声明不实现
}
```

总结：

- 为驳回编译器自动提供的机能，可将相应的成员函数声明为private并且不予实现；



## 条款07 为多态基类声明virtual析构函数

给基类一个virtual析构函数，删除派生类对象会销毁所有派生成分；任何class只要带有virtual函数几乎确定应该也有一个virtual析构函数；例：

```c++
class TimeKeeper {
public:
  TimeKeeper();
  virtual ~TimeKeeper();
  ...
};
TimeKeeper* ptk = getTimeKeeper();
delete ptk; // 行为正确
```

如果class不含virtual函数，通常表示它并不意图被用作一个基类，令其析构函数为virtual往往是个馊主意；例：

```c++
class Point {
public:
  Point(int xCoord, int yCoord);
  ~Point();
private:
  int x, y;
};
```

纯虚析构函数可以被定义；例：

```c++
class AWOV { // 抽象类
public:
  virtual ~AWOV() = 0; // 纯虚析构函数
};
AWOV::~AWOV() { }; // 纯虚析构函数的定义
```

总结：

- polymorphic（带多态性质的）base classes应该声明一个virtual析构函数；如果class带有任何virtual函数，它就应该拥有一个virtual析构函数；
- Classes的设计目的如果不是作为base classes使用，或不是为了具备多态性（polymorphically），就不该声明virtual析构函数；



## 条款08 别让异常逃离析构函数

C++不禁止析构函数抛出异常，但是应该尽量避免它，析构函数抛出异常总会带来风险；

如果某个操作可能在失败时抛出异常，而又存在某种需要必须处理该异常，那么这个异常必须来自析构函数以外的某个函数；

总结：

- 析构函数绝对不要吐出异常，如果一个被析构函数调用的函数可能抛出异常，析构函数应该捕捉任何异常，然后吞下它们（不传播）或结束程序；
- 如果客户需要对某个操作函数运行期间抛出异常做出反应，那么class应该提供一个普通函数（而非在析构函数中）执行该操作。



## 条款09 绝不在构造和析构过程中调用virtual函数

在base class构造期间，使用对象内部尚未初始化的部分非常危险；由于base class构造函数的执行更早与derived class构造函数，当base class构造函数执行时derived class的成员变量尚未初始化；例：

```c++
class Transaction {
public:
  Transaction()
  { init(); }
  virtual void logTransaction() const = 0;
private:
  void init()
  {
  	logTransaction(); // 这里调用了virtual function
  }
};
```

上述代码会报错，可以修改为以下代码：

```c++
class Transaction {
public:
  explicit Transaction(const std::string& logInfo);
  void logTransaction(const std::string& logInfo) const;
};
Transaction::Transaction(const std::string& logInfo)
{
	logTransaction(logInfo);
}

class BuyTransaction : public Transaction {
public:
  BuyTransaction(parameters) : Transaction( createLogString(parameters) ) {}
private:
  static std::string createLogString(parameters);
};
```

总结：

- 在构造和析构期间不要调用virtual函数，因为这类调用从不下降至derived class(比起当前执行构造函数和析构函数的那层)；



## 条款10 令operator=返回一个reference to *this

为classes实现赋值操作符时应该遵守的规矩：赋值操作必须返回一个reference指向操作符的左侧实参；例：

```c++
class Widget {
public:
  Widget& operator=(const Widget& rhs) // 返回类型是个reference，指向当前对象
  {
  	return* this; // 返回左侧对象
  }
  Widget& operator+=(const Widget& rhs) // 适用于+=, -=, *=等等
  {
  	return *this;
  }
  Widget& operator=(int rhs)
  {
  	return *this;
  }
};
```

总结：

- 令赋值（assignment）操作符返回一个reference to *this；



## 条款11 在operator=中处理“自我赋值”

自我赋值的情况：

```c++
w = w; // 自我赋值
a[i] = a[j]; // 当i==j时，自我赋值
*px = *py; // 当px和py指向同一个对象时，自我赋值
```

避免自我赋值有以下方法：

```c++
// 不具备自我赋值安全性和异常安全性
class Bitmap {};
class Widget {
private:
  Bitmap* pb;
};
Widget& Widget::operator=(const Widget& rhs) // 不安全的operator=实现版本
{
	delete pb;
  pb = new Bitmap(*rhs.pb);
  return *this;
}
```

```c++
// 还是不够安全
Widget& Widget::operator=(const Widget& rhs)
{
	if (this == &rhs) return *this; // 证同测试(identity test)
  delete pb;
  pb = new Bitmap(*rhs.pb); // 这里有可能抛出异常
  return *this;
}
```

```c++
// 比较安全
Widget& Widget::operator=(const Widget& rhs)
{
	Widget temp(rhs); // 制作副本
  swap(temp);       // 交换数据
  return *this;
}
```

总结：

- 确保当对象自我赋值时operator=有良好行为，其中技术包括比较“来源对象”和“目标对象”的地址，精心周到的语句顺序，以及copy-and-swap；
- 确定任何函数如果操作一个以上的对象，而其中多个对象是同一个对象时，其行为仍然正确。



## 条款12 复制对象时勿忘其每一个成分

如果为class添加一个成员变量，必须同时修改copying函数，所有构造函数以及任何非标准形式的operator=；例：

```c++
class PriorityCustomer : public Customer {
public:
  PriorityCustomer(const PriorityCustomer& rhs);
  PriorityCustomer& operator=(const PriorityCustomer& rhs);
private:
  int priority;
};
PriorityCustomer::PriorityCustomer(const PriorityCustomer& rhs)
  : Customer(rhs),
    priority(rhs.priority)
{
  logCall("PriorityCustomer copy constructor");    
}
PriorityCustomer& PriorityCustomer::operator=(const PriorityCustomer& rhs)
{
	logCal("PriorityCustomer copy assignment operator");
  Customer::operator=(rhs);
  priority = rhs.priority;
  return *this;
}
```

总结：

- Copying函数应该确保复制“对象内的所有成员变量”及“所有base class成分”；
- 不要尝试以某个copying函数实现另一个copying函数，应该将共同机能放进第三个函数中，并由两个coping函数共同调用。
