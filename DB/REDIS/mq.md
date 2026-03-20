English | [中文版](mq_zh.md)

# Implementing a Message Queue with Redis

[TOC]


## Publish/Subscribe

1. A consumer subscribes to a channel (blocks waiting):

   ```sh
   127.0.0.1:6379> SUBSCRIBE chat
   Reading messages... (press Ctrl-C to quit)
   1) "subscribe"
   2) "chat"
   3) (integer) 1
   ```

2. A producer publishes a message to the channel:

   ```sh
   127.0.0.1:6379> PUBLISH chat hello
   (integer) 2
   ```

3. The consumer receives the published message and continues waiting:

   ```sh
   127.0.0.1:6379> SUBSCRIBE chat
   Reading messages... (press Ctrl-C to quit)
   1) "subscribe"
   2) "chat"
   3) (integer) 1
   1) "message"
   2) "chat"
   3) "hello"
   ```

The above uses Redis PUB/SUB to build a blocking pull-style message queue, suitable when multiple consumer groups need to consume the same batch of messages.

### Drawbacks

The main problem with this approach is data loss. Data loss can easily occur in these scenarios:

1. Consumer goes offline

   If a consumer (subscriber) crashes or disconnects, messages published while it is offline are dropped; when it comes back online it only receives new messages.

2. Redis crash

   PUB/SUB messages are not written to RDB or AOF. If Redis crashes and restarts, published messages are lost.

3. Message backlog

   Redis allocates an output buffer per consumer. If messages pile up and the consumer's output buffer exceeds `client-output-buffer-limit`, Redis will disconnect the consumer.


## Stream mode

TODO


## References

[1] "Is Redis Really Suitable as a Message Queue?" — https://mp.weixin.qq.com/s/KQcydvhkHMjuIekJ-DxIZw
