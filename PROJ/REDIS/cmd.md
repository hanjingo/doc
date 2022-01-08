# Redis命令

[TOC]

## Key

| 命令      | 说明                                                         | 可选项                                                       | 示例                                                         |
| --------- | ------------------------------------------------------------ | ------------------------------------------------------------ | ------------------------------------------------------------ |
| DEL       | 删除给定的一个或多个key（不存在的key会被忽略），返回被删除的key的数量 |                                                              | - `del name1 name2` 删除key:name1和name2;                    |
| DUMP      | 序列化键对应的值，并返回被序列化的值                         |                                                              | - `dump name` 序列化键name对应的值;                          |
| EXISTS    | 检查给定键是否存在（如果存在，返回1）                        |                                                              | - `exists name` 检查键name是否存在;                          |
| EXPIRE    | 为给定键设置过期时长（精确度：版本2.6以后精确到1ms）         |                                                              | - `expire name 1` 设置键name的过期时长为1s;                  |
| EXPIREAT  | 为给定键设置过期时间（Unix时间戳）                           |                                                              | - `expireat name 1641213599` 设置键name的过期时间为 2022-01-03 20:39:59; |
| KEYS      | 以匹配模式查找所有符合条件的key（**慎用，有性能问题，推荐使用增量迭代命令**） |                                                              | - `keys *` 匹配数据库中所有key;<br>- `keys h?llo` 匹配hello, hallo;<br>- `keys h*llo` 匹配hllo, heeeello;<br>- `keys h[ae]llo` 匹配hello, hallo |
| MIGRATE   | 将key原子性的从当前实例传送到指定实例的数据库中              | - `COPY` 不移除源实例的key<br>- `REPLACE` 替换目标实例上已存在的key | - `MIGRATE 127.0.0.1 7777 greeting 0 1000 COPY` 传送greeting到服务器127.0.0.1:7777的0号数据库上，并保留当前数据库的key |
| MOVE      | 移动当前数据库的key到指定数据库中（如果目标数据库中也存在此key，移动失败） |                                                              | - `move name 1` 将name移动到1号数据库                        |
| OBJECT    | 返回键的信息                                                 | - `REFCOUNT` 返回给定key引用所存储的值的次数<br>- `ENCODING` 返回给定key存储的值所使用的内部表示<br>- `IDLETIME` 返回给定key自存储以来的空转时间（单位：s） | - `OBJECT REFCOUNT game` 返回键game的引用次数；<br>- `OBJECT IDLETIME game` 查看键game的空转时间<br>- `OBJECT ENCODING game` 返回键game在redis中存储的值的编码内容；<br/> |
| PERSIST   | 移除给定key的生存时间，将key转化为持久的key                  |                                                              | - `PERSIST k` 将临时的k转化为持久的k                         |
| PEXPIRE   | 以**ms**为单位设置key的生存时长                              |                                                              | - `PEXPIRE k 1500` 设置k在1.5s后失效                         |
| PEXPIREAT | 以**ms**为单位设置key的过期时间（unix时间戳）                |                                                              | - `PEXPIREAT k 1555555555005` 设置k的失效时间                |
| PTTL      | 返回key的剩余生存时长（ms）                                  |                                                              | - `PTTL k` 返回k的剩余生存时长（ms）                         |
| RANDOMKEY | 从当前数据库中随机返回一个key                                |                                                              | - `RANDOMKEY` 随机返回一个key                                |
| RENAME    | 重命名一个key，如果new key已存在时覆盖它                     |                                                              | - `RENAME a b` 将a重命名为b                                  |
| RENAMENX  | 重命名一个key，如果new key已存在时返回失败                   |                                                              | - `RENAMENX a b` 将a重命名为b，如果b已存在就返回失败；       |
| RESTORE   | 反序列化给定的值，并将它与key绑定                            |                                                              | - `RESTORE k 0 "\x00\x15hello, dumping world!\x06\x00E\xa0Z\x82\xd8r\xc1\xde"` 反序列化给定的值并与k绑定，不设置生存时长；<br>- `RESTORE k 1500 "\x00\x15hello, dumping world!\x06\x00E\xa0Z\x82\xd8r\xc1\xde"` 反序列化给定的值并与k绑定，设置生存时长为1.5s； |
| SORT      | 取集合中的数据进行排序（默认按数字升序）并返回               | - `ASC` 升序；<br>- `DESC` 降序；<br>- `ALPHA` 按字符排序；<br>- `LIMIT [offset] [count]` 限制返回结果，offset指定要跳过的元素数量，count指定要返回的元素数量；<br>- `BY` 按照指定方式来排序；<br>- `GET` 根据排序的结果作为key来取出相应的值；<br>- `STORE` 保存排序结果； | - `SORT li` 取列表li的数据按数字进行升序排序并返回；<br>- `SORT li DESC` 取列表li的数据按数字进行降序排序并返回；<br>- `SORT li ALPHA` 取列表li的数据按字符进行升序排序并返回；<br>- `SORT li LIMIT  1 5` 取列表li的数据按数字进行升序排序，跳过排名第1的元素，返回第2～6的元素；<br>- `SORT uid BY lvl_*` 取uid的值与占位符`lvl_`组合成权重，用来对uid排序；<br>- `SORT uid GET name_*` 对uid进行排序，然后将排序结果与占位符`name_`组合成新的key，并取出key对应的值；<br>- `SORT uid BY lvl_* GET name_*` 按权重`lvl_{uid}`来对uid进行排序，然后取出`name_{uid}`对应的值；<br>- `SORT uid GET lvl_* GET name_*`分别获取`lvl_{uid}`和`name_{uid}`对应的值；<br>- `SORT uid GET # lvl_* GET name_*` 分别获取`{uid}`, `lvl_{uid}`, `name_{uid}`对应的值；<br>- `SORT uid BY not-exists-key GET # lvl_* GET name_*` 将一个不存在的键`not-exists-key`作为参数传给BY选项，实现在不排序的情况下，获取多个外部键（类似于数据库的join操作）；<br>- `SORT uid BY m*->lvl GET m*->name` 将哈希表m中lvl和name作为排序参数；<br>- `SORT numbers STORE sorted-numbers` 将numbers排序并将结果保存到sorted-numbers； |
| TTL       | 返回给定key的剩余生存时长（单位：s）                         |                                                              | - `TTL k` 返回k的剩余生存时长；                              |
| TYPE      | 返回键对应的值的类型                                         |                                                              | - `TYPE k` 返回k对应的值的类型                               |
| SCAN      | 增量迭代（分多次返回）当前数据库中的**所有**数据库键，当返回0时完成一次完整遍历；（每次返回不定数量的元素，推荐用于生产环节替换SMEMBERS，KEYS等命令） | - `COUNT` 对每次迭代返回的数量提供建议（即不保证此选项有效）；<br>- `MATCH` 对迭代出的元素进行模式匹配； | - `SCAN 0` 使用0作为游标，开始一次新的迭代；<br>- `SCAN 17` 使用17作为游标（起始位置），开始一次新的迭代； <br>- `SCAN 0 MATCH *11* COUNT 100` 使用0作为游标，开始一次新的迭代，对迭代出的元素进行模式匹配（a11b, b11, ...），并建议返回1000个元素； |



## String

| 命令        | 说明                                                         | 参数 | 示例                                      |
| ----------- | ------------------------------------------------------------ | ---- | ----------------------------------------- |
| APPEND      | 将value追加到key对应的值的末尾，如果key不存在，直接将key的值设置为value |      | - `APPEND k ext` 在k对应的值后面添加ext； |
| BITCOUNT    | 计算给定字符串中，被设置为1的比特位的数量                    |      |                                           |
| BITOP       |                                                              |      |                                           |
| DECR        |                                                              |      |                                           |
| DECRBY      |                                                              |      |                                           |
| GET         |                                                              |      |                                           |
| GETBIT      |                                                              |      |                                           |
| GETRANGE    |                                                              |      |                                           |
| GETSET      |                                                              |      |                                           |
| INCR        |                                                              |      |                                           |
| INCRBY      |                                                              |      |                                           |
| INCRBYFLOAT |                                                              |      |                                           |
| MGET        |                                                              |      |                                           |
| MSET        |                                                              |      |                                           |
| MSETNX      |                                                              |      |                                           |
| PSETEX      |                                                              |      |                                           |
| SET         |                                                              |      |                                           |
| SETBIT      |                                                              |      |                                           |
| SETEX       |                                                              |      |                                           |
| SETNX       |                                                              |      |                                           |
| SETRANGE    |                                                              |      |                                           |
| STRLEN      |                                                              |      |                                           |



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

| 命令                                                     | 说明                         | 参数 | 示例 |
| -------------------------------------------------------- | ---------------------------- | ---- | ---- |
| SADD                                                     | 将给定元素添加到集合         |      |      |
| ZCARD                                                    |                              |      |      |
| SDIFF                                                    |                              |      |      |
| SDIFFSTORE                                               |                              |      |      |
| SINTER                                                   |                              |      |      |
| SINTERSTORE                                              |                              |      |      |
| SISMEMBER                                                | 检查给定元素是否存在于集合中 |      |      |
| SMEMBERS（**性能有问题，建议使用增量迭代系列命令SCAN**） | 返回集合包含的所有元素       |      |      |
| SMOVE                                                    |                              |      |      |
| SPOP                                                     |                              |      |      |
| SRANDMEMBER                                              |                              |      |      |
| SREM                                                     | 如果元素存在，则删除         |      |      |
| SUNION                                                   |                              |      |      |
| SUNIONSTORE                                              |                              |      |      |
| SSCAN                                                    |                              |      |      |



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

| 命令    | 说明 | 参数 | 示例 |
| ------- | ---- | ---- | ---- |
| DISCARD |      |      |      |
| EXEC    |      |      |      |
| MULTI   |      |      |      |
| UNWATCH |      |      |      |
| WATCH   |      |      |      |



## HyperLogLog

| 命令    | 说明                                       | 参数 | 示例 |
| ------- | ------------------------------------------ | ---- | ---- |
| PFADD   | 增加计数                                   |      |      |
| PFCOUNT | 获取计数                                   |      |      |
| PFMERGE | 用于将多个pf计数值类加在一起形成一个新的pf |      |      |



## Script

| 命令          | 说明 | 参数 | 示例 |
| ------------- | ---- | ---- | ---- |
| EVAL          |      |      |      |
| EVALSHA       |      |      |      |
| SCRIPT EXISTS |      |      |      |
| SCRIPT FLUSH  |      |      |      |
| SCRIPT KILL   |      |      |      |
| SCRIPT LOAD   |      |      |      |



## Server

| 命令             | 说明                       | 参数                                                         | 示例                                                         |
| ---------------- | -------------------------- | ------------------------------------------------------------ | ------------------------------------------------------------ |
| BGREWRITEAOF     |                            |                                                              |                                                              |
| BGSAVE           |                            |                                                              |                                                              |
| CLIENT GETNAME   |                            |                                                              |                                                              |
| CLIENT KILL      |                            |                                                              |                                                              |
| CLIENT LIST      |                            |                                                              |                                                              |
| CLIENT SETNAME   |                            |                                                              |                                                              |
| CONFIG GET       |                            |                                                              |                                                              |
| CONFIG RESETSTAT |                            |                                                              |                                                              |
| CONFIG REWRITE   |                            |                                                              |                                                              |
| CONFIG SET       |                            |                                                              |                                                              |
| DBSIZE           |                            |                                                              |                                                              |
| DEBUG OBJECT     |                            |                                                              |                                                              |
| DEBUG SEGFAULT   |                            |                                                              |                                                              |
| FLUSHALL         |                            |                                                              |                                                              |
| FLUSHDB          |                            |                                                              |                                                              |
| INFO             | 显示信息                   | - `server`<br>- `clients`<br>- ` memory`<br>- `persistence`<br>- `stats`<br>- `replication`<br>- `cpu`<br>- `commandstats`<br>- `cluster`<br>- `keyspace` | - `INFO server` 服务器信息<br>- `INFO clients` 已连接客户端信息<br>- `INFO memory` 内存信息<br>- `INFO persistence` RDB和AOF相关信息<br>- `INFO stats` 一般统计信息<br>- `INFO replication` 主从复制信息<br>- `INFO cpu` CPU统计信息<br>- `INFO commandstats` 命令统计信息<br>- `INFO cluster` 集群信息<br>- `INFO keyspace` 数据库相关的统计信息 |
| LASTSAVE         |                            |                                                              |                                                              |
| MONITOR          |                            |                                                              |                                                              |
| PSYNC            |                            |                                                              |                                                              |
| SAVE             |                            |                                                              |                                                              |
| SHUTDOWN         |                            |                                                              |                                                              |
| SLAVEOF          | 设置当前服务器的主服务器   | - `<IP> <PORT>`                                              | - `SLAVEOF 127.0.0.1 6379` 设置当前服务器的主服务器为127.0.0.1:6379 |
| SLOWLOG          |                            |                                                              |                                                              |
| SYNC             | 重同步数据（**效率不佳**） |                                                              |                                                              |
| TIME             |                            |                                                              |                                                              |



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
