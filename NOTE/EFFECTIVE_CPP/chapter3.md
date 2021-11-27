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

