[TOC]

# skynet线程模型



## 创建多线程

```flow
start=>start: skynet启动
create_thread=>operation: 创建多条线程
pop_msg=>operation: 线程pop出一个msg
callback=>operation: 线程对msg执行执行回调函数

start->create_thread->pop_msg->callback
```

1. skynet在启动时，会创建若干条（取决于skynet_config.thread的定义）条worker线程。
2. worker线程pop出一个消息msg（一个服务不能同时在多个worker线程中调用callback函数，从而保证了线程安全）。
3. worker线程对msg执行回调函数。



## 线程权重

权重决定了线程消费消息的能力，skynet在创建线程时会引入一张权重表，通过权重表的配置，决定了worker线程不同的消费能力。

### 权重表

权重表结构如下：

```c
	static int weight[] = { 
		-1, -1, -1, -1, 0, 0, 0, 0,
		1, 1, 1, 1, 1, 1, 1, 1, 
		2, 2, 2, 2, 2, 2, 2, 2, 
		3, 3, 3, 3, 3, 3, 3, 3, };
```

说明：

- 当权重<0

  一个线程一次消费一条消息

- 当权重==0

  一个线程一次消费完次级消息队列中的所有消息

- 当权重>0

  一个线程一次消费n条消息



## 线程消费

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

1. worker线程每次从global_mq中pop一个次级消息队列，如果次级消息队列为空，则该worker线程投入睡眠，timer线程每隔2.5ms会唤醒一条睡眠中的worker线程，并重新尝试从全局消息队列中pop一个次级消息队列出来，当次级消息队列不为空时，进入下一步。
2. 根据次级消息的handle，找出其所属的服务指针(skynet_context实例)；从次级消息队列中，pop出n条消息（n受权重影响），并将其作为参数，传给skynet_context的cb函数，并调用它。
3. 当完成callback函数调用时，就从global_mq中再pop一个次级消息队列中，供下一次使用，并将本次使用的次级消息队列push回global_mq的尾部。
4. 返回第一步



## 线程安全

skynet使用以下特性保证线程安全：

1. 同一时间，一个次级消息队列只会被一个线程拿到，用完之后再放回global_mq。
2. global_mq和次级消息队列在push/pop时都有加spinlock
3. 通过handle从handle_storage的slot里获取sky net_context时，加上了rowlock。

