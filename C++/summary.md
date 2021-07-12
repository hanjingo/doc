# c++总结

[TOC]

## 智能指针



## 对象模型

1. new函数：先分配内存，再调用构造函数；delete函数：先调用析构函数，再释放内存；
2. 只有`nonstatic data member`是在object内部的，其他的都在外面
3. 每个类只要声明了`virtual function`就会存在一个虚表（多重继承和虚继承可能会有多个虚表），虚表保存了这个类`virtual function`的地址，这个类的每一个对象都有一个指向该虚表的指针(vptr)，vptr在`constructor`时被赋值。
4. 继承关系也可以被指定为virtual（共享），例：`class istream : virtual public ios { ... };`；在此情况下，基类不管在继承链中被派生多少次，它都永远只存在一个实例。
5. 虚拟继承会影响效率。
6. 一个`class object`的内存大小 = `nonstatic data member`的大小总和 + 由于`alignment`而填充的空间 + `virtual`产生的额外负担。
7. cast无法改变一个指针所指向的真正地址，只影响该地址的“解释方式”。
8. 用`base class object`给`drived class object`赋值，初始化或用类型转换将`base class`转化为`drived class`都是**非法的**；
9. 用`drived class object`给`base class object`赋值，初始化或用类型转换将`drived class object`转化为`base class object`是**可以的**；但是会发生切割。
10. `base class object pointer`**可以**指向`drived class object`；`drived class object point`**不可以**指向`base class object`，这是实现多态的基础条件。
11. 使用**类型转化**将`drived class object`转化为`base class object`**不会发生切割**；
12. explicit能够防止"单一参数的`constructor`"被当做一个`conversion`运算符。
13. 在编译器生成默认构造函数时，**不会**初始化类中的其他成员。
14. 一个`empty class object`的大小不为0，编译器会为其安插一个`char`，用来给这个类的任意两个`object`能够在内存中配置一个独一无二的地址；如果有`virtual function`，还会添加一个vptr来指向`virtual table`；
15. 一般越晚声明的`member`就在`class object`中越后（高）的位置，为了兼容c，`vptr`一般放在`class object`的后面。
16. `static member`放在`data segment`而**不在**`class object`中。
17. `virtual destructor`的作用是将基类的析构函数作为共享，防止内存泄漏。
18. 不要把`virtual destructor`声明为`pure virtual destructor`。
19. 在以下3种情况，编译器会调用复制构造函数：
    - 一个对象以值传递的方式传入函数体
    - 一个对象以值传递的方式从函数返回
    - 一个对象需要通过另一个对象进行初始化



## 继承关系

1. protected继承会将public的member转化为protected
2. private继承会将public和protected的member转化为private
3. 面向对象的三大特征：多态(Polymorphism), 封装(Encapsulation)和继承(Inheritance)
4. 多态：同一操作作用于不同的对象，产生不同的结果。有以下分类：
   	- 编译时多态（重载）
   	- 运行时多态（虚函数）



## stl



## 并发编程

1. 用`join()`来加入线程（等待），用`detach()`来分离线程（不等）。

2. 要确保`std::thread`对象被销毁前已经调用`join()`或`detach()`，如果在线程开始之后在调用`join()`之前引发一场，对`join()`的调用就容易被跳过。

3. 可以使用以下方法来给线程函数传递参数：

   - 使用`std::ref`包装
   - 使用`std::move`来转移所有权

4. 通过一下方法来获取线程标识符`std::thread::id`:

   - 通过从与之相关联的`std::thread`对象中调用`get_id()`获得。
   - 线程构建时返回。

5. 互斥元用法：`std::lock_guard<std::mutex> guard(mutex_obj)`

6. 可以通过以下方法来等待其他线程完成：

   - 使用条件变量`std::condition_variable`和`std::condition_variable_any`

7. 使用`std::future`来从线程中返回参数

8. 常用的原子操作：

   - load
   - store
   - exchange
   - compare
   - exchange

9. 无锁编程准则：

   - 使用`std::memory_order_seq_cst`作为原型
   - 使用无锁内存回收模式
   - 当心ABA问题
   - 识别忙于等待的循环以及辅助其它线程
   
10. **阿姆达尔定律(Amdahl's law)：**$P=\frac{1}{f_s + \frac{1 - f_s}{N}}$

    - $P$: 性能
    - $f_s$: "串行部分"
    - $N$: 处理器个数


   

