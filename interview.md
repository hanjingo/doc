[TOC]

# 面试笔记



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

一般用双向链表，具体见：[LRU算法](ALGO/lru.md)

[返回顶部](#面试笔记)



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



## 分布式

### 描述下Raft协议和Paxos协议，以及它们的区别

具体见：[Raft协议](DCS/CONSENSUS/raft.md)， [Paxos协议](DCS/CONSENSUS/paxos.md)

### 如何实现分布式锁

具体见：[利用redis实现分布式锁](PROJ/REDIS/dcs_lock.md)

[返回顶部](#面试笔记)



## 网络

### 说说TCP的三次握手和四次挥手

具体见：[TCP](NET/tcp.md)

### TCP状态转移图

具体见：[TCP#状态转移](NET/tcp.md)

### 说说Epoll的原理以及它的用法

红黑树+链表；具体见：[网络I/O#Epoll](net/io.md)

### DNS原理

具体见：[DNS协议](NET/dns.md)

### 讲述下RESTFUL API，以及PUT和GET的区别

TODO

### 为什么不建议使用TCP自带的`keepalive`选项来做心跳

1. `keepalive`对服务区负载压力大
2. socks代理不支持`keepalive`
3. 复杂情况下`keepalive`会失效（如：网线被拔掉，路由器挂掉...）

[返回顶部](#面试笔记)



## 项目

### 架构

#### 游戏服务器的架构

具体见：[游戏服务器架构](PROJ/game_server_construct.md)

#### 热更新的用途

具体见：[热更新](PROJ/hot_patch.md)

### 消息协议

#### Protobuf的底层实现

varint+zigzag，具体见：[Protobuf编码](NET/protobuf.md)

#### 使用UDP的理由

TODO

#### 怎么处理粘包问题

在包头标记包长，具体见：[粘包处理](PROJ/anti_sticky.md)

### 缓存系统

#### 如何解决缓存与数据库的数据一致性问题

TODO

#### 如何避免缓存穿透，缓存击穿和缓存雪崩

- 缓存穿透：缓存和数据库中都没有数据，直接压跨数据库
- 缓存击穿：缓存中一个热点key失效，同时大量请求过来，压垮数据库
- 缓存雪崩：缓存中的大量key同时失效，同时大量请求过来，压垮数据库

具体见：[缓存系统](PROJ/cache.md)

### 信息安全

#### 描述下Cookie以及Session

TODO

#### 如何对API接口限流

TODO

### 调试

#### linux如何开启系统日志

命令`systemctl restart rsyslog`，具体见：[linux系统日志](BUG/linux_sys_log.md)

#### linux如何开启core文件生成

命令`ulimit -c unlimited`，具体见：[如何定位Core Dump问题](BUG/core_dump.md)

#### CPU100%的调试方法

TODO

#### CoreDump的调试方法

用GDB，具体见：[如何定位Core Dump问题](BUG/core_dump.md)

[返回顶部](#面试笔记)



## c++

### 实现运行时多态有哪些方式

1.接口；2.虚函数；3.抽象类；具体见：[c++的虚函数#纯虚函数](LANG/C++/vfunc.md)

### 描述下c++中四种`cast`以及他们的使用场景

`static_cast`,`dynamic_cast`,`reinterprent_cast`,`const_cast`具体见：[c++转换函数](LANG/C++/cast.md)

### 为什么要用`virtual destructor`？为什么没有`virtual constructor`?

防止内存泄漏，具体见：[c++的虚函数#虚析构函数](LANG/C++/vfunc.md)

### 哪些函数不能是虚函数？

具体见：[c++的虚函数#哪些函数不能是虚函数](LANG/C++/vfunc.md)

### 谈谈虚函数和纯虚函数的区别

具体见：[c++的虚函数#纯虚函数](LANG/C++/vfunc.md)

### 构造函数和析构函数可以调用虚函数吗？

可以但是不建议，具体见：[c++的虚函数#纯虚函数](LANG/C++/vfunc.md)

### 指针和引用的用途和区别

具体见：[指针和引用](LANG/C++/ptr_ref.md)

### `malloc/free`，`new/delete`的区别

具体见：[内存管理函数](OS/mem_mgr.md)

### 谈谈`std::move`

具体见：[std::move和std::forward](LANG/C++/STL/move_forward.md)

### 迭代器失效怎么解决

失效操作后返回一个有效的迭代器

### 如何在两个线程之间共享套接字

TODO

[返回顶部](#面试笔记)



## Lua

### Lua有哪些数据类型

具体见：[LUA数据类型](LANG/LUA/data_type.md)

### 谈谈Lua的GC

具体见：[Lua GC](SRC/LUA/gc.md)

### 谈谈Lua的元表

具体见：[Lua数据类型](SRC/LUA/data_type.md)

[返回顶部](#面试笔记)



## GO

### GO的不足

具体见：[Golang总结#优缺点](LANG/GO/summary.md)

### GO的协程原理

TODO

[返回顶部](#面试笔记)



## Skynet

#### 谈谈Skynet的定时器

具体见：[skynet计时器](SRC/SKYNET/timer.md)

#### 谈谈Skynet的actor模型

TODO

#### Skynet的集群方案有哪些

`master/slaver`模式，`cluster`模式；具体见：[skynet集群](SRC/SKYNET/cluster.md)

#### Skynet有哪些热更新方案

`clearcache`命令，`inject`命令，`云风制作的热更新工具-skynet-reload`，`snax框架的hotfix`，`利用lua的require机制`；具体见：[skynet热更新](SRC/SKYNET/hotpatch.md)

[返回顶部](#面试笔记)



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

1.简单，2.并发效率，3.范围查找效率；具体见：[redis跳表](PROJ/REDIS/skip_list.md)

#### 2 Redis如何实现延时队列

具体见：[利用redis实现延时队列](PROJ/REDIS/delay_queue.md)

#### 3 Redis持久化

具体见：[Redis持久化](PROJ/REDIS/persistence.md)

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



## ZeroMQ

[返回顶部](#面试笔记)



## Ceph

### 谈谈Ceph的整体架构

TODO

### 谈谈Ceph的纠删码原理

TODO

[返回顶部](#面试笔记)



## NGINX

### 谈谈Nginx线程模型

TODO

[返回顶部](#面试笔记)



## 参考

- [Github-interviewGuide](https://github.com/NotFound9/interviewGuide)

