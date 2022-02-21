# QT信号槽

[TOC]



## 信号槽的重载形式

### QT5

```c++
QMetaObject::Connection connect(const QObject *, const char *, const QObject *, const char *, Qt::ConnectionType);
QMetaObject::Connection connect(const QObject *, const QMetaMethod &,const QObject *, const QMetaMethod &, Qt::ConnectionType);
QMetaObject::Connection connect(const QObject *, const char *, const char *, Qt::ConnectionType) const;
QMetaObject::Connection connect(const QObject *, PointerToMemberFunction, const QObject *, PointerToMemberFunction, Qt::ConnectionType)
QMetaObject::Connection connect(const QObject *, PointerToMemberFunction, Functor);
```

### QT4

```c++
bool connect(const QObject *, const char *, const QObject *,const char *, Qt::ConnectionType );
bool connect(const QObject *, const QMetaMethod &, const QObject *, const QMetaMethod &, Qt::ConnectionType);
bool connect(const QObject *, const char *, const char *, Qt::ConnectionType) const
```



## 使用

### 规范

- 一个信号可以连接多个槽。
- 多个信号可以连接同一个槽。
- 一个信号可以连接另外一个信号。
- 信号与槽的参数个数和类型必须一致，否则会出现编译错误和运行错误。

### 多线程

Qt提供`Qt::ConnectionType`来控制信号槽执行时所在的线程：

- `Qt::AutoConnection` 

  默认，如果信号（发送者）与槽（接受者）在同一线程，等同于`Qt::DirectConnection`；如果不在同一线程，等同于队列连接`Qt::QueuedConnection`。

- `Qt::DirectConnection` 

  槽函数和信号**发送者**在同一线程（当信号发射时，槽函数立即直接调用；无论槽函数所属对象在哪个线程，槽函数总在发送者所在线程执行）。

- `Qt::QueuedConnection` 

  槽函数与信号**接受者**在同一线程（当控制权回到接受者所在线程的事件循环时，槽函数被调用；槽函数在接受者所在线程执行）。

- `Qt::BlockingQueuedConnection` 

  槽函数的调用时机与`Qt::QueuedConnection`一致，发送完信号后发送者所在的线程会阻塞，直到槽函数运行完。接受者与发送者不能再同一个线程，否则会造成死锁。

- `Qt::UniqueConnection`

  可以通过按位`|`与以上四个结合使用；当设置此参数时，可以避免重复连接。



## 优缺点

| 优点                                                     | 缺点                                                 |
| -------------------------------------------------------- | ---------------------------------------------------- |
| - 精简代码量（避免回调地狱）<br>- 类型安全<br>- 松散耦合 | - 运行速度慢（同回调相比）<br>- 使用时有一些限制<br> |





## 参考

[1] [C++ Qt常用面试题整理（不定时更新）](https://blog.csdn.net/qq_33462307/article/details/108998579)

[2] [Qt基础面试题 ](https://www.cnblogs.com/xiaokang01/p/12562704.html)