# redis事务

## 摘要
Redis事务可以一次执行多个命令，提供以下保证：
- 批量操作在发送EXEC命令前被放入队列缓存
- 收到`EXEC`命令后进入事务执行，事务中任意命令执行失败，其余的命令依然被执行
- 在事务执行过程，其他客户端提交的命令请求不会插入到事务执行命令序列中

## 流程
- 开始事务
- 命令入队
- 执行事务

## 命令
- MULTI:开始新事务，一般与EXEC配合使用；

- EXEC:执行事务；

- WATCH:监视一个或多个键；

- UNWATCH:对监视进行重置；

- DISCARD:对连接进行重置；

说明:
* 使用MULTI和EXEC包裹命令式不会被其他客户端打扰；
* 使用流水线（pipline）可以提高redis的效率；
* 对redis性能影响较大的几个因素：
  - 3-1：没有使用流水线；
  - 3-2：对于每一个命令或每组命令都创建了新的连接，如果条件允许，可以重用已有的redis连接，不必每次用完就马上释放；

