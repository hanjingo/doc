# 第一章 STL介绍

[TOC]



## 摘要
stl库介绍



## 详情
### stl概念库
* 

### 知识点
1. 

### 容器
* 
  容器在堆上存放对象，并且自动管理它们所占用的内存；

### 迭代器
* 输入迭代器（input iterators）：提供对对象的只读访问，没有减量运算
* 输出迭代器（output iterators）：提供对对象的只写访问，没有减量运算
* 正向迭代器（forward iterators）：结合输入输出迭代器功能，可以随意多次用它进行读或写操作
* 双向迭代器（bidirectional iterators）：具有和正向迭代器同样的功能，但允许进行前向和后向遍历
* 随机访问迭代器（random access iterators）:提供了和双向迭代器同样的功能，但是支持对元素的随机访问

### 迭代器适配器
1. 反向迭代器（reverse iterators）：

2. 插入迭代器（insert iterators）：

   - 后向插入迭代器（back_insert_iterator）

     vector, list, deque都有push_back(),将一个新的元素添加到容器尾部 

   - 向前插入迭代器(front_insert_iterator）

     list, forward_list, deque都有push_front(),将一个新的元素添加到容器的头部 

   - 插入迭代器（insert_iterator）

     用insert()插入新的元素  

3. 移动迭代器（move iterators）

   指向一定范围内的元素，将某个范围内的类对象移动到目标范围，而不需要通过拷贝去移动

### 迭代器运算
* advance()

  将迭代器移动n个位置，例：std::advance(iter, 3)

* distance()

  返回迭代器之间的距离, 例：std::distance(iter1, iter2)

* next()

  获得距离迭代器n个位置的迭代器,例：std::next(iter, 3)

* prev()

  获得迭代器反向偏移n个位置之后所指向的迭代器，例：std::prev(iter, 3)

### 智能指针
智能指针只能用来保存堆上分配的内存的地址 
不能像对原生指针那样，对智能指针进行一些自增或自减这样的操作  

1. `unique_ptr<T>`:唯一指针

   - 不可能有其他的`unique_ptr<T>`指向同一地址; 
   - 不能以传值的方式将一个`unique_ptr<T>`对象传入函数中，因为他们不支持拷贝，必须使用引用的方式；
   - 可以通过交换2个`unique_ptr<T>`指针的方式来交换2个对象;  
2. `shared_ptr<T>`:共享指针

   - 允许共享一个对象的所有权；
   - 只能通过拷贝构造函数或赋值运算符去赋值一个shared_ptr<T>对象;
3. `weak_ptr<T>`:弱引用指针
   - 只能从`shared_ptr<T>`对象创建;
   - 不会增加`shared_ptr<T>`对象的引用机制，当最后一个`shared_ptr<T>`引用被释放或指向一个不同的地址时，他们所指向的对象的内存被释放，即使相关的`weak_ptr<T>`可能仍然存在

### 算法
* 非变化序列运算（不改变值）

  find(), count(), mismatch(), search(), equal()

* 可变序列运算（改变值）

  swap(), copy(), transform(), replace(), remove(), reverse(), rotate(), fill(), shuffle()

* 改变顺序运算（改变顺序）

  sort(), stable_sort(), binry_search(), merge(), min(), max()

### lambda表达式
`【捕获列表】（参数列表）mutable -> 返回类型 { 主体 }  `

```
捕获列表：列出了在闭合区域不活的变量，变量可以通过值引用或引用的方式捕获  
参数列表：确定在lambda被调用时，传给它的值得类型和个数。可以指定默认参数值，参数列表可以为空  
mutable：可选，说明不活的变量的副本是否可以修改
返回类型：可选，当省略时，默认是返回值得类型。如果没有任何返回值，返回类型是void
主体：函数实现
```
如果想用引用的方式捕获，需要在每一个名字的前面加上一个 & 前缀；

### 总结
* stl定义类模板，作为其他对象的容器
* stl定义迭代器，一种行为像指针的对象
* 反向其实迭代器指向序列的最后一个元素，方向结束迭代器指向第一个元素的前一个位置
* iterator头文件定义了一些全局函数，可以从容器，数组，任何支持迭代器的独享得到一些迭代器
* 可以使用流迭代器转换流对象中给定类型的数据
* stl定义了一些实现了算法的函数模板，可以运用到由迭代器指定的一段元素上
* 智能指针是一种表现有些像指针的对象
* lambda表达式定义了一个匿名函数
* 能够用定义在functional头文件中的std::function<>模板类型，去指定任意种类的，有给定函数签名的可调用实体