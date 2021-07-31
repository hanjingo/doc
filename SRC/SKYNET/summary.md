[TOC]

# Skynet总结



## 目录结构

- `3rd`
    
    第三方库，包括：
    
    - `lua` 语言支持
    - `lpeg `
    - `jemalloc` 内存管理
    - `lua-md5` md5加密
    
- `lualib`

    - lua的辅助函数

- `lualib-src`

    lua调C提供C层级的API调用，包括：

    - socket模块API
    - skynet消息发送，注册回调函数API

- `service`

    lua层服务，依附于snlua这个c服务，涵盖skynet lua层级的一些基本服务，包括：

    - lua层级服务的bootstrap服务
    - gate服务
    - 供lua层创建新服务的launcher服务

- `service-src`

    依附于skynet核心模块的c服务，包括：

    - 日志
    - snlua

- `skynet-src`

    包含skynet最核心机制的模块，包括：
    
    - 逻辑入口
    - skynet_module模块
    - skynet_context模块
    - 消息队列
    - 定时器
    - socket



## 架构

![constructor](res/constructor.jpeg)

1. 每一个`socket`对应一个`lua vm`和一个`per client mq`
2. 有一个`socket thread`轮询所有的`socket`，收到信息后，打包发送到`per client mq`中
3. 将`per client mq`挂到`global message queue`的尾部
4. `worker threads`从`global message queue`头部开始，获取每个`client`对应的消息队列
5. 处理获取到的消息队列，用完放回`global message queue`



## 多线程

```flow
start=>start: 消费开始
sleep=>operation: 线程睡眠2.5ms
wakeup=>operation: 唤醒线程
pop=>operation: 从global_mq中pop一个次级消息队列
bempty=>condition: 次级消息队列是否为空?
pop=>operation: 从次级消息队列pop出n条消息，并将其传递给callback函数
callback=>operation: callback函数回调消息
pushback=>operation: 将用完的次级消息队列push回global_mq

start->sleep->wakeup->bempty
bempty(yes)->sleep
bempty(no)->pop->callback->pushback(right)->sleep
```

线程从次级消息队列`pop`出消息时，消息的条数取决于线程的权重w：

- `w<0`

  一个线程一次消费一条消息

- `w==0`

  一个线程一次消费完次级消息队列中的所有消息

- `w>0`

  一个线程一次消费w条消息



## 任务调度

![job_dispatch](res/job_dispatch.jpg)

1. 每个`OS thread`会创建一个`lua vm`
2. 每个`lua vm`会创建海量的`coroutine`

**注意：**

- 不支持任务跨`lua vm`迁移，coroutine是`lua vm`内部的数据结构，两个`lua vm`之间的coroutine无法通用。



## 消息




## 集群



## 参考

- [skynet的总体架构以及任务调度分析](https://zhuanlan.zhihu.com/p/339599579)
- [skynet简介](https://blog.csdn.net/o8413897/article/details/79044437)
- [Skynet 设计综述](https://blog.codingnow.com/2012/09/the_design_of_skynet.html)
- [skynet源码赏析](https://manistein.github.io/blog/post/server/skynet/skynet%E6%BA%90%E7%A0%81%E8%B5%8F%E6%9E%90/)

