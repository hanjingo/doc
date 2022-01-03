# Redis命令

[TOC]

## Key

| 命令      | 子命令                           | 说明                                                         | 可选项                                                       | 示例                                                         |
| --------- | -------------------------------- | ------------------------------------------------------------ | ------------------------------------------------------------ | ------------------------------------------------------------ |
| DEL       |                                  | 删除给定的一个或多个key（不存在的key会被忽略），返回被删除的key的数量 |                                                              | -`del name1 name2` 删除key:name1和name2;                     |
| DUMP      |                                  | 序列化键对应的值，并返回被序列化的值                         |                                                              | - `dump name` 序列化键name对应的值;                          |
| EXISTS    |                                  | 检查给定键是否存在（如果存在，返回1）                        |                                                              | - `exists name` 检查键name是否存在;                          |
| EXPIRE    |                                  | 为给定键设置过期时长（精确度：版本2.6以后精确到1ms）         |                                                              | - `expire name 1` 设置键name的过期时长为1s;                  |
| EXPIREAT  |                                  | 为给定键设置过期时间（Unix时间戳）                           |                                                              | - `expireat name 1641213599` 设置键name的过期时间为 2022-01-03 20:39:59; |
| KEYS      |                                  | 以匹配模式查找所有符合条件的key（**慎用，可能有性能问题**）  |                                                              | - `keys *` 匹配数据库中所有key;<br>- `keys h?llo` 匹配hello, hallo;<br>- `keys h*llo` 匹配hllo, heeeello;<br>- `keys h[ae]llo` 匹配hello, hallo |
| MIGRATE   |                                  | 将key原子性的从当前实例传送到指定实例的数据库中              | - `COPY` 不移除源实例的key<br>- `REPLACE` 替换目标实例上已存在的key | - `MIGRATE 127.0.0.1 7777 greeting 0 1000 COPY` 传送greeting到服务器127.0.0.1:7777的0号数据库上，并保留当前数据库的key |
| MOVE      |                                  | 移动当前数据库的key到指定数据库中（如果目标数据库中也存在此key，移动失败） |                                                              | - `move name 1` 将name移动到1号数据库                        |
| OBJECT    | REFCOUNT<br>ENCODING<br>IDLETIME |                                                              |                                                              |                                                              |
| PERSIST   |                                  |                                                              |                                                              |                                                              |
| PEXPIRE   |                                  |                                                              |                                                              |                                                              |
| PEXPIREAT |                                  |                                                              |                                                              |                                                              |
| PTTL      |                                  |                                                              |                                                              |                                                              |
| RANDOMKEY |                                  |                                                              |                                                              |                                                              |
| RENAME    |                                  |                                                              |                                                              |                                                              |
| RENAMENX  |                                  |                                                              |                                                              |                                                              |
| RESTORE   |                                  |                                                              |                                                              |                                                              |
| SORT      |                                  |                                                              |                                                              |                                                              |
| TTL       |                                  |                                                              |                                                              |                                                              |
| TYPE      |                                  |                                                              |                                                              |                                                              |
| SCAN      |                                  |                                                              |                                                              |                                                              |



## String

| 命令        | 说明                                       | 参数 | 示例 |
| ----------- | ------------------------------------------ | ---- | ---- |
| INCR        | 将键存储的值自增1                          |      |      |
| DECR        | 将键存储的值自减1                          |      |      |
| INCRBY      | 将键存储的值加上此命令右侧的值             |      |      |
| DECRBY      | 将键存储的值减去此命令右侧的值             |      |      |
| INCRBYFLOAT | 将键存储的值加上此命令右侧的值，值为浮点数 |      |      |



## Hash

| 命令         | 说明     | 参数 | 示例 |
| ------------ | -------- | ---- | ---- |
| HDEL         | 删除     |      |      |
| HEXISTS      |          |      |      |
| HGET         | 获取     |      |      |
| HGETALL      | 获取所有 |      |      |
| HINCRBY      |          |      |      |
| HINCRBYFLOAT |          |      |      |
| HKEYS        |          |      |      |
| HLEN         |          |      |      |
| HMGET        |          |      |      |
| HMSET        |          |      |      |
| HSET         | 设置     |      |      |
| HSETNX       |          |      |      |
| HVALS        |          |      |      |
| HSCAN        |          |      |      |



## List

| 命令       | 说明                       | 参数 | 示例 |
| ---------- | -------------------------- | ---- | ---- |
| BLPOP      |                            |      |      |
| BRPOP      |                            |      |      |
| BRPOPLPUSH |                            |      |      |
| LINDEX     | 获取指定位置的单个元素     |      |      |
| LINSERT    |                            |      |      |
| LLEN       |                            |      |      |
| LPOP       | 向左推出                   |      |      |
| LPUSH      |                            |      |      |
| LPUSHX     |                            |      |      |
| LRANGE     | 获取列表指定范围内的所有值 |      |      |
| LREM       |                            |      |      |
| LSET       |                            |      |      |
| LTRIM      |                            |      |      |
| RPOP       |                            |      |      |
| RPOPLPUSH  |                            |      |      |
| RPUSH      | 向右插入                   |      |      |
| RPUSHX     |                            |      |      |



## Set

| 命令        | 说明                         | 参数 | 示例 |
| ----------- | ---------------------------- | ---- | ---- |
| SADD        | 将给定元素添加到集合         |      |      |
| ZCARD       |                              |      |      |
| SDIFF       |                              |      |      |
| SDIFFSTORE  |                              |      |      |
| SINTER      |                              |      |      |
| SINTERSTORE |                              |      |      |
| SISMEMBER   | 检查给定元素是否存在于集合中 |      |      |
| SMEMBERS    | 返回集合包含的所有元素       |      |      |
| SMOVE       |                              |      |      |
| SPOP        |                              |      |      |
| SRANDMEMBER |                              |      |      |
| SREM        | 如果元素存在，则删除         |      |      |
| SUNION      |                              |      |      |
| SUNIONSTORE |                              |      |      |
| SSCAN       |                              |      |      |



## Zset

| 命令             | 说明                   | 参数 | 示例 |
| ---------------- | ---------------------- | ---- | ---- |
| ZADD             | 添加给定分值的元素     |      |      |
| ZCARD            |                        |      |      |
| ZCOUNT           |                        |      |      |
| ZINCRBY          |                        |      |      |
| ZRANGE           | 获取指定索引范围的元素 |      |      |
| ZRANGEBYSCORE    | 获取指定分值范围的元素 |      |      |
| ZRANK            |                        |      |      |
| ZREM             | 如果存在，则删除       |      |      |
| ZREMRANGEBYRANK  |                        |      |      |
| ZREMRANGEBYSCORE |                        |      |      |
| ZREVRANGE        |                        |      |      |
| ZREVRANGEBYSCORE |                        |      |      |
| ZREVRANK         |                        |      |      |
| ZSCORE           |                        |      |      |
| ZUNIONSTORE      |                        |      |      |
| ZINTERSTORE      |                        |      |      |
| ZSCAN            |                        |      |      |



## HyperLogLog

| 命令    | 说明                                       | 参数 | 示例 |
| ------- | ------------------------------------------ | ---- | ---- |
| PFADD   | 增加计数                                   |      |      |
| PFCOUNT | 获取计数                                   |      |      |
| PFMERGE | 用于将多个pf计数值类加在一起形成一个新的pf |      |      |



## Pub/Sub

| 命令         | 说明                 | 参数                                                         | 示例                                                         |
| ------------ | -------------------- | ------------------------------------------------------------ | ------------------------------------------------------------ |
| PSUBSCRIBE   | 模糊匹配订阅频道     | - `<pattern>`                                                | - `PSUBSCRIBE AB*` 模糊匹配订阅以AB开头的频道                |
| PUBLISH      | 向频道发布消息       | - `<channel/pattern> <msg>`                                  | - `PUBLISH ch hello` 向频道ch发送消息hello                   |
| PUBSUB       | 查看发布订阅消息     | - `CHANNELS <pattern>`<br>- `NUMSUB <ch1 ... chN>`<br>- `NUMPAT` | - `PUBSUB CHANNELS *.abc` 查看匹配频道<br>- `PUBSUB NUMSUM ch1 ch2` 查看ch1和ch2的订阅者数量<br>- `PUBSUB NUMPAT` 查看订阅模式的数量 |
| PUNSUBSCRIBE | 取消模糊匹配订阅频道 | - `<pattern>`                                                | - `PUNSUBSCRIBE AB*` 取消模糊匹配以AB开头的频道              |
| SUBSCRIBE    | 订阅频道             | - `<channel>`                                                | - `SUBSCRIBE AB` 订阅频道AB                                  |
| UNSUBSCRIBE  | 取消订阅             | - `<channel>`                                                | - `UNSUBSCRIBE AB` 取消订阅频道AB                            |



## Transaction

| 命令 | 说明 | 参数 | 示例 |
| ---- | ---- | ---- | ---- |
|      |      |      |      |
|      |      |      |      |
|      |      |      |      |
|      |      |      |      |
|      |      |      |      |



## Server

| 命令    | 说明                     | 参数                                                         | 示例                                                         |
| ------- | ------------------------ | ------------------------------------------------------------ | ------------------------------------------------------------ |
|         |                          |                                                              |                                                              |
| INFO    | 显示信息                 | - `server`<br>- `clients`<br>- ` memory`<br>- `persistence`<br>- `stats`<br>- `replication`<br>- `cpu`<br>- `commandstats`<br>- `cluster`<br>- `keyspace` | - `INFO server` 服务器信息<br>- `INFO clients` 已连接客户端信息<br>- `INFO memory` 内存信息<br>- `INFO persistence` RDB和AOF相关信息<br>- `INFO stats` 一般统计信息<br>- `INFO replication` 主从复制信息<br>- `INFO cpu` CPU统计信息<br>- `INFO commandstats` 命令统计信息<br>- `INFO cluster` 集群信息<br>- `INFO keyspace` 数据库相关的统计信息 |
|         |                          |                                                              |                                                              |
| SLAVEOF | 设置当前服务器的主服务器 | - `<IP> <PORT>`                                              | - `SLAVEOF 127.0.0.1 6379` 设置当前服务器的主服务器为127.0.0.1:6379 |
| SYNC    | 重同步数据（效率不佳）   |                                                              |                                                              |



## 其它

| 命令     | 说明                                     | 参数                                                         | 示例                                                         |
| -------- | ---------------------------------------- | ------------------------------------------------------------ | ------------------------------------------------------------ |
| SENTINEL | 哨兵命令                                 | - `is-master-down-by-addr <ip> <port> <current_epoch> <runid>` | - `SENTINEL is-master-down-by-addr 127.0.0.1 6379 0 *` 询问其他哨兵，master(127.0.0.1:6379)是否已下线 |
| AUTH     | 检测给定的密码是否和配置文件中的密码一致 | - `<passwd>`                                                 | - `AUTH hello` 检测配置的密码是不是hello                     |
| FLUSHALL | 删除所有数据库的所有key                  |                                                              | - `FLUSHALL` 删除所有数据                                    |
| INCR     | 将key的值+1                              | - `<key>`                                                    | - `INCR a` 将a对应的值+1                                     |
| PSYNC    | 部分重同步数据（新版）                   | - `<runid> <offset>`                                         | - `PSYNC ? -1` 主动请求主服务器进行完整重同步<br>- `PSYNC 53b9b28df8042fdc9ab5e3fcbbbabff1d5dce2b3 20000` 主动请求主服务器同步偏移量2000之后的数据 |
| REPLCONF |                                          |                                                              | - `ACK <replication_offset>`                                 |



## 参考

### 参考文献

[1] 黄健宏.Redis设计与实现

### 外部链接

- [Redis 命令参考](http://doc.redisfans.com/)
