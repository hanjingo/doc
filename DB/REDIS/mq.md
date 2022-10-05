# 利用redis实现消息队列


<!-- vim-markdown-toc GFM -->

* [发布订阅](#发布订阅)
    - [缺点](#缺点)
* [stream模式](#stream模式)
* [参考](#参考)

<!-- vim-markdown-toc -->



## 发布订阅

1. 消费者订阅一个队列（此时阻塞等待）

   ```sh
   127.0.0.1:6379> SUBSCRIBE chat
   Reading messages... (press Ctrl-C to quit)
   1) "subscribe"
   2) "chat"
   3) (integer) 1
   ```

2. 生产者发布一条消息到此队列

   ```sh
   127.0.0.1:6379> PUBLISH chat fuck
   (integer) 2
   ```

3.  消费者收到发布的消息，然后继续阻塞等待

   ```sh
   127.0.0.1:6379> SUBSCRIBE chat
   Reading messages... (press Ctrl-C to quit)
   1) "subscribe"
   2) "chat"
   3) (integer) 1
   1) "message"
   2) "chat"
   3) "fuck"
   ```

以上过程利用Redis的发布/订阅机制实现了一个阻塞式拉取消息的消息队列，满足多组消费者消费同一批数据的业务需求。

### 缺点

这个方案最大的问题就是：**丢数据**，在以下场景中，很容易发生数据丢失：

1. 消费者（订阅者）下线

   如果一个消费者异常挂掉了，在下线期间生产者发布的消息因为找不到消费者，都会被丢弃掉；它再重新上线后，只能接收新的消息。

2. Redis宕机

   PUB/SUB操作不会写入到RDB和AOF中，当Redis宕机重启时，PUB/SUB的数据也会丢失。

3. 消息堆积

   PUB/SUB有一个特性，Redis会为每一个消费者创建一个缓冲区，当消息积压导致Redis缓冲区超过配置`client-output-buffer-limit`的阈值时，Redis会把消费者踢下线。



## stream模式

TODO



## 参考

[1] [Redis真的合适做消息队列吗？](https://mp.weixin.qq.com/s/KQcydvhkHMjuIekJ-DxIZw)

