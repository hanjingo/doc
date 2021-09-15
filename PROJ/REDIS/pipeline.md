# redis管道

## 摘要
客户端允许将多个请求依次发送给服务器，过程而不需要等待请求的回复，在最后再一并读取结果即可。主要作用在于提高吞吐量

![redis_pipeline](res/redis_pipeline.png)




## 缺点
1. pipeline机制可以优化吞吐量，但无法提供原子性/事务保障，而这个可以通过Redis-Multi等命令实现。
2. 部分读写操作存在相关以来，无法使用pipeline实现。

