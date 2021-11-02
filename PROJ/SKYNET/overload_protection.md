# skynet服务过载保护

[TOC]

当某个服务成为热点时，一旦外部请求的消息超过其处理能力，会导致其消息队列过长，从而报`May overload, message queue length = xxx`的错误(xxx为队列长度)。



## 源码分析

- `skynet_mq.c`

  ```c
  #define MQ_OVERLOAD 1024	// 过载数量
  // 消息队列
  struct message_queue {
      ...
  	int overload;                 // 过载数量
  	int overload_threshold;       // 过载阀值
      ...
  };
  
  // 创建消息队列
  struct message_queue * 
  skynet_mq_create(uint32_t handle) {
      ...
  	q->overload_threshold = MQ_OVERLOAD; // 赋予过载阈值
      ...
  }
  
  // 弹出消息
  int
  skynet_mq_pop(struct message_queue *q, struct skynet_message *message) {
      ...
  	if (q->head != q->tail) {
          ...
  		while (length > q->overload_threshold) {
  			q->overload = length;
  			q->overload_threshold *= 2; // 过载阈值*2
  		}
  	} else {
  		// reset overload_threshold when queue is empty
  		q->overload_threshold = MQ_OVERLOAD; // 重置过载阈值
  	}
      ...
  }
  ```

  1. 创建消息队列时，赋予默认过载阈值（1024）；
  2. 弹出消息时：
     - 如果消息队列长度超出了过载阈值：则过载阈值翻倍
     - 如果消息队列长度为空：重置过载阈值



## 解决方案

### 1 前置一个代理服务

TODO

### 2 拆分服务

TODO



## 参考

- [代理服务和过载保护](https://blog.codingnow.com/2016/05/skynet_proxy.html)
- [skynet 服务的过载保护](https://blog.codingnow.com/2014/10/skynet_overload.html)
- [skynet 消息分发及服务调度的新设计](https://blog.codingnow.com/2016/01/skynet2.html)

