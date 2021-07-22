# 利用redis实现延时队列

利用`zset`，用时间戳做score，消息内容做key；生产者使用zadd产生消息，消费者使用`zrangebyscore`轮询消息。