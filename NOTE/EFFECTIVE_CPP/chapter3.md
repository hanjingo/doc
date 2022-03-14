# 3 Resource Management

[TOC]

## 条款13 以对象管理资源

资源在构造期间获得，在析构期间释放（Resource Acquisition Is Initialization, RAII）；

- 获得资源后立刻放进管理对象（managing object）内；
- 管理对象（managing object）运用析构函数确保资源被释放。

```c++
// 使用auto_ptr以避免函数潜在的资源泄漏的可能性：
void f()
{
	std::auto_ptr<Investment> pInv(createInvestment());
}
```

auto_ptr的替代方案是“引用计数型智能指针”(reference-counting smart pointer, RCSP)，RCSP提供的行为类似垃圾回收（garbage collection），不同的是RCSP无法打破环状引用（cycles of references）；例：

```c++
void f()
{
	std::tr1::shared_ptr<Investment>
  pInv(createInvestment());
}
```

总结：

- 为防止资源泄漏，请使用RAII对象，它们在构造函数中获得资源并在析构函数中释放资源；
- 两个常被使用的RAII classes分别是`tr1::shared_ptr`和`auto_ptr`，前者通常是较佳选择，因为其copy行为比较直观，若选择auto_ptr，复制动作会使被复制物指向null。



## 条款14 在资源管理类中小心coping行为

```c++
class Lock {
public:
  explicit Lock(Mutex* pm) : mutexPtr(pm) { lock(mutexPtr); } // 获得资源
  ~Lock() { unlock(mutexPtr); } // 释放资源
private:
  std::tr1::shared_ptr<Mutex> mutexPtr;
};
```

应对RAII对象被复制的方法：

- 禁止RAII对象被复制；
- 对底层资源祭出“引用计数法”(reference-count)；

总结：

- 复制RAII对象必须一并复制它所管理的资源，所以资源的copying行为决定RAII对象的copying行为；
- 普遍而常见的RAII class copying行为是：抑制copying，施行引用计数（reference counting），不过其他行为也都可能被实现。



## 条款15 在资源管理类中提供对原始资源的访问

总结：

- APIs往往要求访问原始资源（raw resources），所以每一个RAII class应该提供一个“取得其所管理之资源”的办法；
- 对原始资源的访问可能经由显式转换或隐式转换，一般而言显式转换比较安全，但隐式转换对客户比较方便。



## 条款16 成对使用new和delete时要采取相同形式

使用typedef时必须要说清楚，当以new创建该种typedef类型对象时，应该以哪种delete方式删除；例：

```c++
typedef std::string AddressLines[4];
std::string* pal = new AddressLines;

delete pal; // 行为未定义
delete [ ] pal; // 很好
```

**最好不要对数组形式做typedefs动作；**

总结：

- 如果你在new表达式中使用`[]`，必须要在相应的delete表达式中使用`[]`；如果你在new表达式中不使用`[]`，一定不要在相应的delete表达式中使用`[]`；



## 条款17 以独立语句将newed对象置入智能指针

```c++
processWidget(std::shared_ptr<Widget>(new Widget), priorty());
```

由于C++的函数参数计算不是有序的，有可能`priorty()`先运行，此时可能会对赋值产生影响；最好是分离语句如下：

```c++
std::shared_ptr<Widget> pw(new Widget);
processWidget(pw, priority());
```

总结：

- 以独立语句将newed对象存储于（置入）智能指针内，如果不这样做，一旦异常被抛出，有可能导致难以察觉的资源泄漏。
