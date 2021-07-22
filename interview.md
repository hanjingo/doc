[TOC]

# 面试笔记



## 算法

### 如何判断链表是否有环

TODO

### B+树的应用场景与实用特点

TODO

### LRU缓存实现

TODO

### 求二叉树最远叶子结点的距离

TODO

[返回顶部](#面试笔记)



## 系统

### 简述进程，线程和协程以及它们的区别

具体见：[进程，线程和协程#区别](OS/progress_thread_coroutine.md)

### 可执行程序的结构

具体见：[可执行程序](OS/exe.md)

### 如何提升memcpy的效率

具体见：[POSIX接口#memcpy](OS/posix.md)

### 进程状态图

具体见：[进程，线程和协程#进程状态转移图](OS/progress_thread_coroutine.md)

[返回顶部](#面试笔记)



## 分布式

### 描述下Raft协议和Paxos协议，以及它们的区别

具体见：[Raft协议](DCS/CONSENSUS/raft.md)， [Paxos协议](DCS/CONSENSUS/paxos.md)

### 如何实现分布式锁

具体见：[利用redis实现分布式锁](DB/REDIS/dcs_lock.md)

[返回顶部](#面试笔记)



## 网络

### TCP状态转移图

具体见：[TCP](NET/tcp.md)

### epoll详解

具体见：[epoll](NET/epoll.md)

### DNS原理

TODO

### 讲述下RESTFUL API，以及PUT和GET的区别

TODO

[返回顶部](#面试笔记)



## 项目

### 游戏服务器的架构

具体见：[游戏服务器架构](PROJ/game_server_construct.md)

### 热更新的用途

具体见：[热更新](PROJ/hot_patch.md)

### protobuf的底层实现

TODO

### 使用UDP的理由

TODO

### 如何避免缓存穿透，缓存击穿和缓存雪崩

具体见：[缓存系统](PROJ/cache.md)

### 描述下Cookie以及Session

TODO

### 如何对API接口限流

TODO

[返回顶部](#面试笔记)



## c++

### 描述下c++中四种`cast`以及他们的使用场景

具体见：[c++转换函数](LANG/C++/cast.md)

### 为什么要用`virtual destructor`？为什么没有`virtual constructor`?

具体见：[c++的虚函数](LANG/C++/vfunc.md)

### 哪些函数不能是虚函数？

具体见：[c++的虚函数](LANG/C++/vfunc.md)

### 指针和引用的用途和区别

具体见：[指针和引用](LANG/C++/ptr_ref.md)

### `malloc/free`，`new/delete`的区别

具体见：[内存管理函数](OS/mem_mgr.md)

### 谈谈`std::move`

TODO

[返回顶部](#面试笔记)



## Lua

### Lua有哪些数据类型

具体见：[LUA数据类型](LANG/LUA/data_type.md)

[返回顶部](#面试笔记)



## Skynet

### 定时器

### actor模型

### 集群

### lua虚拟机

### 负载均衡

### 热更新

[返回顶部](#面试笔记)



## Redis

### 为什么Redis用跳表不用RBtree

具体见：[redis跳表](DB/REDIS/skip_list.md)

### Redis如何实现延时队列

具体见：[利用redis实现延时队列](DB/REDIS/delay_queue.md)

### Redis持久化

具体见：[Redis持久化](DB/REDIS/persistence.md)

### Redis线程模型

TODO

[返回顶部](#面试笔记)



## Mysql

### innedb的底层数据结构

TODO

### 磁盘结构分析与数据存储原理

TODO

### 说说数据库索引的使用及其原理

TODO

[返回顶部](#面试笔记)



## ZeroMQ

[返回顶部](#面试笔记)



## HBase

[返回顶部](#面试笔记)



## NGINX

### Nginx线程模型

TODO

[返回顶部](#面试笔记)
