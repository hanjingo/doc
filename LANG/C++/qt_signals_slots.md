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

- 一个信号可以连接多个槽；
- 多个信号可以连接同一个槽；
- 一个信号可以连接另外一个信号；
- 连接可以被移除；
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

| 优点                                                     | 缺点                                             |
| -------------------------------------------------------- | ------------------------------------------------ |
| + 精简代码量（避免回调地狱）<br>+ 类型安全<br>+ 松散耦合 | - 运行速度慢（同回调相比）<br>- 使用时有一些限制 |



## 示例

- `selfdef_str.h`

  ```c++
  #ifndef SELFDEF_STR_H
  #define SELFDEF_STR_H
  
  #include<QObject>
  #include<QString>
  
  class Str : public QObject
  {
      Q_OBJECT // defined for signal-slots
  
  public:
      Str(){ _value = "null"; }
      QString Value() const { return _value; }
  
  public slots:
      void setValue(QString v);
  
      signals: // auto expand by moc
      void valueChanged(QString chg); // do not impliment it
  
  private:
      QString _value;
  };
  
  #endif // SELFDEF_STR_H
  ```

- `selfdef_str.cpp`

  ```c++
  #include "selfdef_str.h"
  
  void Str::setValue(QString value)
  {
      if (_value != value)
      {
          _value = value;
          emit valueChanged(value);
      }
  }
  ```

- `main.cpp`

  ```c++
  #include "mainwindow.h"
  #include "selfdef_str.h"
  
  #include <QApplication>
  #include <QLabel>
  #include <QDebug>
  
  void print(QString str) 
  {
      QLabel *l = new QLabel;
      l->setText(y.Value());
      l->show();
  }
  
  int main(int argc, char *argv[])
  {
      QApplication a(argc, argv);
  
      // signals:slots = 1:1
      Str x{};
      Str y{};
      QObject::connect(&x, SIGNAL(valueChanged(QString)),
                       &y, SLOT(setValue(QString)));
      x.setValue("1:1>> x commit\n");
      print(y.Value());
  
      // signals:slots = 1:n
      Str x1{};
      Str y1{};
      Str z1{};
      QObject::connect(&x1, SIGNAL(valueChanged(QString)),
                       &y1, SLOT(setValue(QString)));
      QObject::connect(&x1, SIGNAL(valueChanged(QString)),
                       &z1, SLOT(setValue(QString)));
      x1.setValue("1:n>> x1 commit\n");
      print(y1.Value() + z1.Value());
  
      // signals:slots = n:1
      Str x2{};
      Str y2{};
      Str z2{};
      QObject::connect(&x2, SIGNAL(valueChanged(QString)),
                       &z2, SLOT(setValue(QString)));
      QObject::connect(&y2, SIGNAL(valueChanged(QString)),
                       &z2, SLOT(setValue(QString)));
      x2.setValue("n:1>> x2 commit\n");
      y2.setValue("n:1>> y2 commit\n");
      l2->print(z2.Value());
  
      // signal:slots -- signal:slots
      Str x3{};
      Str y3{};
      Str z3{};
      QObject::connect(&x3, SIGNAL(valueChanged(QString)),
                       &y3, SLOT(setValue(QString)));
      QObject::connect(&y3, SIGNAL(valueChanged(QString)),
                       &z3, SLOT(setValue(QString)));
      x3.setValue("signal:slots -- signal:slots>> x3 commit\n");
      l3->print(y3.Value() + z3.Value());
  
      // remove connection
      Str x4{};
      Str y4{};
      QObject::connect(&x4, SIGNAL(valueChanged(QString)),
                       &y4, SLOT(setValue(QString)));
      QObject::disconnect(&x4, SIGNAL(valueChanged(QString)),
                          &y4, SLOT(setValue(QString)));
      x.setValue("connection remove>> x commit\n");
  
      l4->print(y4.Value());
  
      return a.exec();
  }
  ```



## 参考

[1] [C++ Qt常用面试题整理（不定时更新）](https://blog.csdn.net/qq_33462307/article/details/108998579)

[2] [Qt基础面试题 ](https://www.cnblogs.com/xiaokang01/p/12562704.html)

[3] [QT信号槽机制](https://www.cnblogs.com/QG-whz/p/4995938.html)