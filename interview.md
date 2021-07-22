[TOC]

# 面试笔记



## 算法

### 如何判断链表是否有环

[返回顶部](#面试笔记)



## 系统

### 简述进程，线程和协程以及它们的区别

具体见：[进程，线程和协程#区别](OS/progress_thread_coroutine.md)

### epoll详解

具体见：[epoll](NET/epoll.md)

### 可执行程序的结构

具体见：[可执行程序](OS/exe.md)

### 如何提升memcpy的效率

具体见：[POSIX接口#memcpy](OS/posix.md)

### TCP状态转移图

具体见：[TCP](NET/tcp.md)

### 进程状态图

具体见：[进程，线程和协程#进程状态转移图](OS/progress_thread_coroutine.md)

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

### 缓存穿透

缓存和数据库中都没有的数据，用户还是源源不断的发起请求，导致每次请求都会到数据库，从而压垮数据库

解决方案：

1. 业务层校验
2. 对于查找不到的数据，在redis中将其值设置为NULL，并设置较短的过期时间
3. 布隆过滤器

### 缓存击穿

redis中一个热点key在失效的同时，大量的请求过来，这些请求全部到达数据库，压垮数据库

解决方案：

1. 设置热点数据永不过期
2. 定时更新过期时间（续命）
3. 分布式锁

### 缓存雪崩

redis中混存的数据大面积失效或者redis宕机，导致大量请求直接到数据库，压垮数据库。

解决方案：

1. 数据过期时间不要太密集
2. 数据预热
3. 做集群

[返回顶部](#面试笔记)



## c++

### 描述下c++中四种`cast`以及他们的使用场景

具体见：[c++转换函数](C++/cast.md)

### 为什么要用`virtual destructor`？为什么没有`virtual constructor`?

具体见：[c++的虚函数](C++/vfunc.md)

### 哪些函数不能是虚函数？

具体见：[c++的虚函数](C++/vfunc.md)

### 指针和引用的用途和区别

具体见：[指针和引用](C++/ptr_ref.md)

### `malloc/free`，`new/delete`的区别

具体见：[内存管理函数](OS/mem_mgr.md)

[返回顶部](#面试笔记)



## lua

### lua有哪些数据类型

- number
- string
- boolean
- function
- table
- userdata
- thread
- nil

[返回顶部](#面试笔记)



## skynet

### 定时器

### actor模型

### 集群

### lua虚拟机

### 负载均衡

### 热更新

[返回顶部](#面试笔记)



## redis

### 同步机制

### 为什么redis用跳表不用rbtree

1. skiplist比较简单
2. rbtree的rebalance需要消耗比较多的性能，skiplist不需要

### redis如何实现延时队列

利用`zset`，用时间戳做score，消息内容做key；生产者使用zadd产生消息，消费者使用`zrangebyscore`轮询消息。

### redis持久化

- 追加（增量持久化）
- 快照

[返回顶部](#面试笔记)



## mysql

### innedb的底层数据结构

[返回顶部](#面试笔记)



## kafka

### kafka原理

[返回顶部](#面试笔记)

