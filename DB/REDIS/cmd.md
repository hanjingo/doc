# 常用命令
## 1.redis五种数据结构
- set
- sortset
- hash
- list
- string
- HyperLogLog(新增)



## 2.redis基本操作
- GET
- SET
- DEL



## 3.特殊操作

### 3_1.list操作命令
- RPUSH: 右插
- LPOP: 左出
- LRANGE: 获取列表指定范围的所有值
- LINDEX: 获取指定位置的单个元素

### 3_2.set操作命令
- SADD: 将给定元素添加到集合
- SMEMBERS: 返回集合包含的所有元素
- SISMEMBER: 检查给定元素是否存在于集合中
- SREM: 如果存在，删除之

### 3_3.hash操作命令
- HSET:设置
- HGET:获取
- HGETALL:获取所有
- HDEL:删除

### 3_4.sortset操作命令
- ZADD:添加给定分值的元素
- ZRANGE:获取指定索引范围的元素
- ZRANGEBYSCORE:获取指定分值范围的元素
- ZREM:如果存在，移除之

### 3_5.string操作
- INCR: 将键存储的值自增1
- DECR: 将键存储的值自减1
- INCRBY: 将键存储的值加上此命令右侧的值
- DECRBY: 将键存储的值减去此命令右侧的值
- INCRBYFLOAT: 将键存储的值加上此命令右侧的值，值为浮点数

### 10. HyperLogLog
- PFADD: 增加计数
- PFCOUNT: 获取计数
- PFMERGE: 用于将多个pf计数值类加在一起形成一个新的pf

```sh
127.0.0.1:6379> pfadd k1 "k1"
(integer) 1
127.0.0.1:6379> pfadd k1 "k2"
(integer) 1
127.0.0.1:6379> pfadd k1 "k3"
(integer) 1
127.0.0.1:6379> pfcount k1
(integer) 3
```



## 其他命令

### 1.阻塞式列表弹出命令&列表之间移动元素命令
-  BLPOP:从第一个非空列表中弹出位于最左端的元素；如果列表为空，则在指定时间内阻塞并等待可弹出的元素出现；
- BRPOP:从第一个非空列表中弹出位于最右端的元素；如果列表为空，则在指定内阻塞并等待可弹出的元素出现；
- RPOPLPUSH:从第一个列表最右端弹出一个元素并存入第二个列表最左端；
- BRPOPLPUSH:从第一个列表最右端弹出一个元素并存入第二个列表最左端；如果第一个列表为空，等待timeout秒；

### 2.集合常用的命令
- SADD:将一个或多个元素添加到集合里，并返回新增的元素数量；
- SREM:将一个或多个元素从集合里删除，并返回删除的元素数量；
- SISMEMBER:检查元素item是否存在与集合里；
- SCARD:返回集合包含的元素数量
- SMEMBERS:返回集合包含的所有元素；
- SRANDMEMBER:从集合里随机返回一个或多个元素；
- SPOP:随即删除集合中的一个元素并返回被删除的元素；
- SMOVE:从集合1中删除一个元素并添加到集合2中；

### 3.处理多个集合关系的命令
- SDIFF:返回存在于集合1，但不存在于集合2中的元素；
- SDIFFSTORE:将存在于集合1，但不存在于集合2中的元素返回并存储；
- SINTER:返回同时存在于所有集合中的元素；
- SINTERSTORE:将同时存在于所有集合中的元素返回并存储；
- SUNION:返回至少存在于一个集合中的元素；
- SUNIONSTORE:返回至少存在于一个集合中的元素并存储；

### 4.添加和删除键值对的散列操作
- HMGET:从散列中获取一个或多个键的值；
- HMSET:为散列中一个或多个键设置值；
- HDEL:删除散列里面一个或多个键值对，返回被删除的键值对数量；、
- HLEN:返回散列包含的键值对数量；
- HEXISTS:检出键是否在散列中；
- HKEYS:获取散列所有的键；
- HVALS:获取散列所有的值；
- HGETALL:获取散列所有的键值对；
- HINCRBY:将键key存储的值加上指定的整数；
- HINCRBYFLOAT:将键key存储的值加上指定的浮点数；

### 5.zset批量操作命令
- ZREVRANK:从大到小返回zset里元素排名；
- ZREVRANGE:从给定范围里从大到小返回zset里元素排名；
- ZRANGEBYSCORE:返回指定值范围里的元素;
- ZREVRANGEBYSCORE:返回指定值范围里的元素，并按照从大到小的顺序排列；
- ZREMRANGEBYRANK:移除指定排名范围里的元素；
- ZREMRANEBYSCORE:移除指定值范围里的元素；
- ZINTERSTORE:对集合进行交集运算；
- ZUNIONSTORE:对集合进行并集运算；

### 6. 发布与订阅命令
- SUBSCRIBE:订阅给定的一个或多个频道；
- UNSUBSCRIBE:退订给定的一个或多个频道；
- PUBLISH:向频道发送消息；
- PSUBSCRIBE:订阅符合条件的所有频道；
- PUNSUBSCRIBE:退订符合条件的所有频道；

### 7. 处理过期时间命令
- PERSIST:移除key的过期时间；
- TTL:查看key距离过期还有多少秒；
- EXPIRE:让key在指定秒数后过期；
- EXPOREAT:让key在指定时间过期；
- PTTL:查看key举了国企还有多少毫秒；
- PEXPIRE:让key在指定毫秒数后过期；
- PEXPIREAT:让key在指定时间过期（精度为毫秒级）；

### 8. 其他命令
- SORT:按给定条件排序；

### 9. 增量循环
- scan
增量循环，每次调用只会返回一小部分的元素；返回一个游标，从0开始遍历，到0结束遍历。注意如下特性：

1. 查询复杂度为`O(n)`，通过游标分步进行，不会阻塞线程
2. 提供limit参数，控制每次返回结果的最大条数。
3. 同keys一样，它也提供模式匹配功能
4. 返回的结果可能会重复，需要客户端去重
5. 遍历过程中，如果有数据修改，改动后的数据不一定能遍历到
6. 单次返回结果是空的并不意味着遍历结束，而是看返回的游标值是否为0

例：

```sh
[127.0.0.1:6379> scan 0 match key* count 10
1) "0"          # 游标
2) 1) "key5"
   2) "key6"
   3) "key4"
   4) "key2"
   5) "key3"
   6) "key1"
```


