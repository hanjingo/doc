# 面试笔记

[TOC]



## 算法

### 树

#### B树的应用场景与特点

具体见：[平衡树](MATH/ALGO/balance_tree.md)

#### B+树的应用场景与特点

Mysql的INNODB引擎，具体见：[平衡树](MATH/ALGO/balance_tree.md)

#### B树与B+树的区别

TODO

#### 求二叉树最远叶子结点的距离

TODO

#### 层级遍历二叉树并计算每一层节点之和

TODO

### 链表

#### 如何判断链表是否有环

TODO

#### 如何逆转链表

从头到尾遍历并插入前面，例：`|1|2|3|`->`|2|1|3|`->`|3|2|1|`

### 其他

#### LRU缓存实现

一般用双向链表，具体见：[LRU算法](MATH/ALGO/lru.md)

[返回顶部](#面试笔记)

---



## 系统

### 简述进程，线程和协程以及它们的区别

具体见：[进程，线程和协程#区别](OS/progress_thread_coroutine.md)

### 可执行程序的结构

具体见：[可执行程序](OS/exe.md)

### 不同线程之间是否可以共享套接字

TODO

### 如何提升memcpy的效率

具体见：[POSIX接口#memcpy](posix.md)

### 进程状态图

具体见：[进程，线程和协程#进程状态转移图](OS/progress_thread_coroutine.md)

[返回顶部](#面试笔记)

---



## 分布式

### 描述下Raft协议和Paxos协议，以及它们的区别

具体见：[Raft协议](DCS/CONSENSUS/raft.md)， [Paxos协议](DCS/CONSENSUS/paxos.md)

### 如何实现分布式锁

具体见：[利用redis实现分布式锁](PROJ/REDIS/dcs_lock.md)

[返回顶部](#面试笔记)

---



## 网络

### 说说TCP的三次握手和四次挥手

具体见：[TCP](NET/tcp.md)

### TCP状态转移图

具体见：[TCP#状态转移](NET/tcp.md)

### 说说Epoll的原理以及它的用法

红黑树+链表；具体见：[网络I/O#Epoll](NET/io.md)

### DNS原理

具体见：[DNS协议](NET/dns.md)

### 讲述下RESTFUL API，以及PUT和GET的区别

TODO

### 为什么不建议使用TCP自带的`keepalive`选项来做心跳

1. `keepalive`对服务区负载压力大
2. socks代理不支持`keepalive`
3. 复杂情况下`keepalive`会失效（如：网线被拔掉，路由器挂掉...）

[返回顶部](#面试笔记)

---



## 项目

### 架构

#### 游戏服务器的架构

具体见：[游戏服务器开发#总体架构](PROJ/game_server_develop.md)

#### 热更新的用途

具体见：[游戏服务器开发#热更新](PROJ/game_server_develop.md)

### 消息协议

#### Protobuf的底层实现

varint+zigzag，具体见：[Protobuf编码](NET/protobuf.md)

#### 使用UDP的理由

TODO

#### 怎么处理粘包问题

在包头标记包长，具体见：[粘包处理](PROJ/anti_sticky.md)

### 缓存系统

#### 如何解决缓存与数据库的数据一致性问题

具体见：[数据库设计](PROJ/db.md)

#### 如何避免缓存穿透，缓存击穿和缓存雪崩

- 缓存穿透：缓存和数据库中都没有数据，直接压跨数据库
- 缓存击穿：缓存中一个热点key失效，同时大量请求过来，压垮数据库
- 缓存雪崩：缓存中的大量key同时失效，同时大量请求过来，压垮数据库

具体见：[数据库设计#通用缓存系统](PROJ/db.md)

### 信息安全

#### 描述下Cookie以及Session

TODO

#### 如何对API接口限流

TODO

#### Token机制应该怎么设计

TODO

### 调试

#### linux如何开启系统日志

命令`systemctl restart rsyslog`，具体见：[调试工具#linux系统日志](PROJ/test_tool.md)

#### linux如何开启core文件生成

命令`ulimit -c unlimited`，具体见：[软件调试方法#如何定位Core Dump问题](PROJ/testway.md)

#### CPU100%的调试方法

具体见：[软件调试方法#如何定位CPU跑满问题](PROJ/testway.md)

#### CoreDump的调试方法

用GDB，具体见：[软件调试方法#如何定位CoreDump问题](PROJ/testway.md)

[返回顶部](#面试笔记)

---



## C/C++

### 基本语法

#### 1 指针和数组的区别

- 数组要么在全局数据区被创建，要么在栈上被创建；指针可以随时指向任意类型的内存块；
- 在对数组赋值时使用`[]`；
- 对数组变量做sizeof运算得到的是数组占用内存的总大小（如果数组变量被传入函数中做sizeof运算，则结果与对指针做sizeof运算一致）；

#### 2 指针和引用的用途和区别

区别如下：

- 初始化：引用在创建时必须初始化；
- 可修改性：引用一旦被初始化就无法被修改；
- NULL：引用不能为NULL；
- 效率：使用引用之前不需要测试它的合法性而指针需要，引用的效率要高于指针；

具体见：TODO

#### 3 C语言参数压栈顺序

从右到左，栈是向下生长的，从高地址向低地址方向分配内存；

#### 4 重载和覆盖的区别

重载（overriding）的特征：

- 方法名必须相同；
- 参数列表必须不相同，与参数列表的顺序无关；
- 返回值类型可以不相同；

覆盖（overloading）的特征：

- 只有虚方法和抽象方法才能够被覆写；
- 相同的函数名；
- 相同的参数列表；
- 相同的返回值类型；

#### 5 C++中四种`cast`以及他们的使用场景

`static_cast`,`dynamic_cast`,`reinterprent_cast`,`const_cast`具体见：TODO

#### 6 static的作用

- 在函数内，static变量在函数被调用的过程中维持其值不变；
- 在函数外模块内，static变量可以被模块内的所有函数访问，但不能被模块外的其他函数访问，它是一个本地变量；
- 在模块内，static函数只能被模块内的其他函数调用；

#### 7 const的作用

- 定义常量：编译器可以对其进行数据静态类型安全检查；
- 修饰函数行参：限制形参的可修改性；
- 修饰函数返回值：给函数返回值加const，则返回值不能被直接修改，且该返回值只能被赋值给const修饰的同类型指针；
- 修饰类成员函数：不会修改数据成员的函数都应该用const修饰，当不小心修改了数据成员或调用非const成员函数时，编译器会报错；

#### 8 空指针和悬垂指针的区别

TODO

### 面向对象

#### 1 实现运行时多态有哪些方式

1.接口；2.虚函数；3.抽象类；具体见：TODO

#### 2 为什么要用`virtual destructor`？为什么没有`virtual constructor`?

- 防止内存泄漏

具体见：TODO

#### 3 哪些函数不能是虚函数？

具体见：TODO

#### 4 虚函数和纯虚函数的区别

- 虚函数是实现的，纯虚函数只是一个接口（函数声明）；
- 虚函数在子类可以不重载，纯虚函数必须在子类中实现；
- 带纯虚函数的类叫做虚基类（抽象类），不能直接生成对象，只能被继承；

具体见：TODO

#### 5 构造函数和析构函数可以调用虚函数吗？

可以但是不建议，具体见：TODO

#### 6 什么是私有继承

私有继承的特性：

- 如果两个类之间的继承关系为私有，编译器一般不会将派生类对象转换为基类对象
- 从私有基类继承而来的成员都成为了派生类的私有成员

私有继承时派生类与基类不是“is a”的关系，而是“Is-Implement-In-Terms-Of”的关系；

#### 7 C++中空类默认产生哪些成员函数/变量

TODO

#### 8 explicit构造函数的作用

- explicit构造函数只能被显式调用，普通构造函数能够被隐式调用；

#### 9 虚析构函数的作用

只有当一个类被用来作为基类的时候，才会把析构函数写成虚函数；

#### 10 复制构造函数的作用，与赋值函数的区别是什么

TODO

#### 11 抽象基类与纯虚函数的作用

- 方便使用多态；
- 用来定义接口；

#### 12 const与#define的区别

- const和#define都可以定义常量，但是const用途更广；
- const常量有数据类型，#define没有；
- #define不方便调试；

### STL

#### 1 STL的allocator

TODO

#### 2 `std::move`

具体见：TODO

#### 3 迭代器失效怎么解决

失效操作后返回一个有效的迭代器

#### 4 如何在两个线程之间共享套接字

TODO

#### 5 智能指针的内存泄漏如何解决

TODO

#### 6 STL中map的实现

TODO

#### 7 STL的内存优化策略

TODO

### 编译原理

#### 1 `malloc/free`，`new/delete`的区别

- malloc/free是C/C++标准库函数，new/delete是C++运算符；
- malloc/free无法满足动态对象的要求，对象在创建的同时要自动执行构造函数，在消亡之前要自动执行析构函数；
- malloc开辟空间类型大小需要手动计算，new由编译器自己计算；
- malloc返回`void*`，需要强转为对应类型指针；new直接返回对应类型指针
- free和delete都不需要指定空间大小

具体见：[内存管理函数](OS/mem_mgr.md)

#### 2 字节对齐的规则

- 结构体变量的首地址能够被其最宽基本类型成员的大小所整除；
- 结构体每个成员相对于结构体首地址的偏移量（offset）都是成员大小的整数倍；
- 结构体的总大小为结构体最宽基本类型成员大小的整数倍；
- 联合体的大小取决于它的成员中占用空间最大的一个成员的大小；

#### 3 sizeof小结

特性：

- sizeof不计算static变量占有的内存；

- 各类型使用sizeof得出占用的内存大小：

  | 类型               | 大小（字节）                                                 |
  | ------------------ | ------------------------------------------------------------ |
  | char               | 4                                                            |
  | int                | 4                                                            |
  | short int          | 2                                                            |
  | long int           | 4                                                            |
  | float              | 4                                                            |
  | double             | 8                                                            |
  | string             | 4                                                            |
  | 空类               | 1                                                            |
  | 单一继承空类       | 1                                                            |
  | 虚继承涉及到虚指针 | 4                                                            |
  | 数组               | + 如果指定了数组长度：$数组长度\times sizeof(元素类型)$<br>+ 如果没有指定长度：按实际元素个数来计算<br>+ 如果是字符数组：要考虑末尾的空字符 |
  | 结构体对象         | ？                                                           |
  | unsigned           | unsigned修饰的数据类型长度不变                               |
  | 函数               | 对函数使用sizeof，在编译阶段会被函数的返回值的类型代替       |
  | 自定义类型         | 等于自定义类型的原型取sizeof                                 |

用途：

- 与存储分配和I/O系统那样的例程进行通信；
- 查看某个类型的对象在内存中所占的单元字节；
- 在动态分配对象时，可以让系统知道要分配多少内存；
- 便于一些类型的扩充；
- 由于操作数的字节数在实现时可能出现变化，建议在涉及操作数字节大小时用sizeof来代替常量计算；
- 如果操作数是函数中的数组行参活函数类型的行参，则sizeof给出其指针的大小；

#### 4 `#pragma pack(x)`的作用

- `#pragma pack(x)`可以改变编译器的对齐方式，设置对齐的大小；

#### 5 extern "C"的作用

- 解决由于C++支持函数重载导致的名字匹配问题，实现C++与C的混合编程；

### 模版

TODO

[返回顶部](#面试笔记)

---



## Lua

### Lua有哪些数据类型

具体见：[LUA数据类型](LANG/LUA/data_type.md)

### 谈谈Lua的GC

具体见：[Lua GC](SRC/LUA/gc.md)

### 谈谈Lua的元表

具体见：[Lua数据类型](SRC/LUA/data_type.md)

[返回顶部](#面试笔记)

---



## GO

### GO的不足

具体见：[Golang总结#优缺点](LANG/GO/summary.md)

### GO的协程原理

TODO

[返回顶部](#面试笔记)

---



## Skynet

#### 谈谈Skynet的定时器

具体见：[skynet计时器](SRC/SKYNET/timer.md)

#### 谈谈Skynet的actor模型

TODO

#### Skynet的集群方案有哪些

`master/slaver`模式，`cluster`模式；具体见：[skynet集群](PROJ/SKYNET/cluster.md)

#### Skynet有哪些热更新方案

`clearcache`命令，`inject`命令，`云风制作的热更新工具-skynet-reload`，`snax框架的hotfix`，`利用lua的require机制`；具体见：[skynet热更新](PROJ/SKYNET/hotpatch.md)

[返回顶部](#面试笔记)

---



## Redis

### 使用

#### 1 Redis为什么是单线程的

TODO

#### 2 Redis的性能为什么这么高

TODO

#### 3 客户端是怎么接入Redis哨兵系统的

TODO

### 实现

#### 1 为什么Redis用跳表不用RBtree

1.简单，2.并发效率，3.范围查找效率；

#### 2 Redis如何实现延时队列

具体见：[利用redis实现延时队列](PROJ/REDIS/delay_queue.md)

#### 3 Redis持久化

具体见：[Redis持久化](SRC/REDIS/persistence.md)

#### 4 Redis线程模型

TODO

#### 5 Redis的过期机制

TODO

#### 6 谈谈Redis的布隆过滤器

TODO

#### 7 谈谈Redis的持久化机制

TODO

#### 8 Redis的主从同步是怎么实现的

TODO

#### 9 Redis哨兵的实现

TODO

#### 10 Redis哨兵系统是怎么实现自动故障转移的

TODO

#### 11 Redis集群是怎么实现数据分片的

TODO

#### 12 Redis集群是怎么做故障转移和发现的

TODO

[返回顶部](#面试笔记)

---



## Mysql

### 使用

#### 1 Mysql有哪些优化措施

TODO

#### 2 说说数据库索引的使用及其原理

TODO

#### 3 mysql事物

TODO

#### 4 脏页是什么

TODO

#### 5 Mysql的隔离级别是怎么样的

TODO

#### 6 Mysql中由哪些锁

TODO

#### 7 Mysql如何解决幻读问题

TODO

#### 8 主键，唯一性索引，普通索引的区别是什么

TODO

#### 9 什么是分表分库

TODO

#### 10 如何实现跨库分页查询

TODO

#### 11 Checkpoint是什么

TODO

#### 12 undo log, redo log, bin log是什么

TODO

### 实现

#### 1 InnoDb的底层数据结构

TODO

#### 2 磁盘结构分析与数据存储原理

TODO

#### 3 一条MySql更新语句的执行过程是怎么样的

TODO

[返回顶部](#面试笔记)

---



## Ceph

### 谈谈Ceph的整体架构

TODO

### 谈谈Ceph的纠删码原理

TODO

[返回顶部](#面试笔记)

---



## NGINX

### 谈谈Nginx线程模型

TODO

[返回顶部](#面试笔记)

---



## 参考

- [Github-interviewGuide](https://github.com/NotFound9/interviewGuide)

