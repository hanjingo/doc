# Redis命令


<!-- vim-markdown-toc GFM -->

* [Key](#key)
* [String](#string)
* [Hash](#hash)
* [List](#list)
* [Set](#set)
* [Zset](#zset)
* [Pub/Sub](#pubsub)
* [Transaction](#transaction)
* [HyperLogLog](#hyperloglog)
* [Script](#script)
* [Server](#server)
* [其它](#其它)
* [参考](#参考)

<!-- vim-markdown-toc -->

## Key

| 命令      | 说明                                                         | 可选项                                                       | 时间复杂度 | 示例                                                         |
| --------- | ------------------------------------------------------------ | ------------------------------------------------------------ | ---------- | ------------------------------------------------------------ |
| DEL       | 删除给定的一个或多个key（不存在的key会被忽略），返回被删除的key的数量 |                                                              |            | - `del name1 name2` 删除key:name1和name2;                    |
| DUMP      | 序列化键对应的值，并返回被序列化的值                         |                                                              |            | - `dump name` 序列化键name对应的值;                          |
| EXISTS    | 检查给定键是否存在（如果存在，返回1）                        |                                                              |            | - `exists name` 检查键name是否存在;                          |
| EXPIRE    | 为给定键设置过期时长（精确度：版本2.6以后精确到1ms）         |                                                              |            | - `expire name 1` 设置键name的过期时长为1s;                  |
| EXPIREAT  | 为给定键设置过期时间（Unix时间戳）                           |                                                              |            | - `expireat name 1641213599` 设置键name的过期时间为 2022-01-03 20:39:59; |
| KEYS      | 以匹配模式查找所有符合条件的key（**慎用，有性能问题，推荐使用增量迭代命令**） |                                                              |            | - `keys *` 匹配数据库中所有key;<br>- `keys h?llo` 匹配hello, hallo;<br>- `keys h*llo` 匹配hllo, heeeello;<br>- `keys h[ae]llo` 匹配hello, hallo |
| MIGRATE   | 将key原子性的从当前实例传送到指定实例的数据库中              | - `COPY` 不移除源实例的key<br>- `REPLACE` 替换目标实例上已存在的key |            | - `MIGRATE 127.0.0.1 7777 greeting 0 1000 COPY` 传送greeting到服务器127.0.0.1:7777的0号数据库上，并保留当前数据库的key |
| MOVE      | 移动当前数据库的key到指定数据库中（如果目标数据库中也存在此key，移动失败） |                                                              |            | - `move name 1` 将name移动到1号数据库                        |
| OBJECT    | 返回键的信息                                                 | - `REFCOUNT` 返回给定key引用所存储的值的次数<br>- `ENCODING` 返回给定key存储的值所使用的内部表示<br>- `IDLETIME` 返回给定key自存储以来的空转时间（单位：s） |            | - `OBJECT REFCOUNT game` 返回键game的引用次数；<br>- `OBJECT IDLETIME game` 查看键game的空转时间<br>- `OBJECT ENCODING game` 返回键game在redis中存储的值的编码内容；<br/> |
| PERSIST   | 移除给定key的生存时间，将key转化为持久的key                  |                                                              |            | - `PERSIST k` 将临时的k转化为持久的k                         |
| PEXPIRE   | 以**ms**为单位设置key的生存时长                              |                                                              |            | - `PEXPIRE k 1500` 设置k在1.5s后失效                         |
| PEXPIREAT | 以**ms**为单位设置key的过期时间（unix时间戳）                |                                                              |            | - `PEXPIREAT k 1555555555005` 设置k的失效时间                |
| PTTL      | 返回key的剩余生存时长（**ms**）                              |                                                              |            | - `PTTL k` 返回k的剩余生存时长                               |
| RANDOMKEY | 从当前数据库中随机返回一个key                                |                                                              |            | - `RANDOMKEY` 随机返回一个key                                |
| RENAME    | 重命名一个key，如果new key已存在时覆盖它                     |                                                              |            | - `RENAME a b` 将a重命名为b                                  |
| RENAMENX  | 重命名一个key，如果new key已存在时返回失败                   |                                                              |            | - `RENAMENX a b` 将a重命名为b，如果b已存在就返回失败；       |
| RESTORE   | 反序列化给定的值，并将它与key绑定                            |                                                              |            | - `RESTORE k 0 "\x00\x15hello, dumping world!\x06\x00E\xa0Z\x82\xd8r\xc1\xde"` 反序列化给定的值并与k绑定，不设置生存时长；<br>- `RESTORE k 1500 "\x00\x15hello, dumping world!\x06\x00E\xa0Z\x82\xd8r\xc1\xde"` 反序列化给定的值并与k绑定，设置生存时长为1.5s； |
| SORT      | 取集合中的数据进行排序（默认按数字升序）并返回               | - `ASC` 升序；<br>- `DESC` 降序；<br>- `ALPHA` 按字符排序；<br>- `LIMIT [offset] [count]` 限制返回结果，offset指定要跳过的元素数量，count指定要返回的元素数量；<br>- `BY` 按照指定方式来排序；<br>- `GET` 根据排序的结果作为key来取出相应的值；<br>- `STORE` 保存排序结果； |            | - `SORT li` 取列表li的数据按数字进行升序排序并返回；<br>- `SORT li DESC` 取列表li的数据按数字进行降序排序并返回；<br>- `SORT li ALPHA` 取列表li的数据按字符进行升序排序并返回；<br>- `SORT li LIMIT  1 5` 取列表li的数据按数字进行升序排序，跳过排名第1的元素，返回第2～6的元素；<br>- `SORT uid BY lvl_*` 取uid的值与占位符`lvl_`组合成权重，用来对uid排序；<br>- `SORT uid GET name_*` 对uid进行排序，然后将排序结果与占位符`name_`组合成新的key，并取出key对应的值；<br>- `SORT uid BY lvl_* GET name_*` 按权重`lvl_{uid}`来对uid进行排序，然后取出`name_{uid}`对应的值；<br>- `SORT uid GET lvl_* GET name_*`分别获取`lvl_{uid}`和`name_{uid}`对应的值；<br>- `SORT uid GET # lvl_* GET name_*` 分别获取`{uid}`, `lvl_{uid}`, `name_{uid}`对应的值；<br>- `SORT uid BY not-exists-key GET # lvl_* GET name_*` 将一个不存在的键`not-exists-key`作为参数传给BY选项，实现在不排序的情况下，获取多个外部键（类似于数据库的join操作）；<br>- `SORT uid BY m*->lvl GET m*->name` 将哈希表m中lvl和name作为排序参数；<br>- `SORT numbers STORE sorted-numbers` 将numbers排序并将结果保存到sorted-numbers； |
| TTL       | 返回给定key的剩余生存时长（单位：s）                         |                                                              |            | - `TTL k` 返回k的剩余生存时长；                              |
| TYPE      | 返回键对应的值的类型                                         |                                                              |            | - `TYPE k` 返回k对应的值的类型                               |
| SCAN      | 增量迭代（分多次返回）当前数据库中的**所有**数据库键，当返回0时完成一次完整遍历；（每次返回不定数量的元素，推荐用于生产环节替换SMEMBERS，KEYS等命令） | - `COUNT` 对每次迭代返回的数量提供建议（即不保证此选项有效）；<br>- `MATCH` 对迭代出的元素进行模式匹配； |            | - `SCAN 0` 使用0作为游标，开始一次新的迭代；<br>- `SCAN 17` 使用17作为游标（起始位置），开始一次新的迭代； <br>- `SCAN 0 MATCH *11* COUNT 100` 使用0作为游标，开始一次新的迭代，对迭代出的元素进行模式匹配（a11b, b11, ...），并建议返回1000个元素； |



## String

| 命令        | 说明                                                         | 参数                                                         | 时间复杂度 | 示例                                                         |
| ----------- | ------------------------------------------------------------ | ------------------------------------------------------------ | ---------- | ------------------------------------------------------------ |
| APPEND      | 将value追加到key对应的值的末尾，如果key不存在，直接将key的值设置为value |                                                              |            | - `APPEND k ext` 在k对应的值后面添加ext；                    |
| BITCOUNT    | 统计给定字符串中，被设置为1的比特位的数量                    | - `start` 起始位置；<br>- `end` 终点位置                     |            | - `BITCOUNT b` 统计b中被设置为1的位的数量；<br><br>一些常见用途：<br>1. 统计第100~101天时用户xx的上线频率<br>- `SETBIT xx 100 1` 设置起始位置为100的字符串的比特位为1<br>- `SETBIT xx 101 1` 设置起始位置为101的字符串的比特位为1<br/>- `BITCOUNT xx` 返回xx上线的总天数 |
| BITOP       | 对一个或多个保存二进制位的字符串key进行位元操作，保存操作结果 | - `AND` 并操作<br>- `OR` 或操作<br>- `XOR` 异或<br>- `NOT` 非 |            | - `BITOP dst k1 k2` 对k1, k2进行位操作并保存到dst            |
| DECR        | 将key中存储的数字值-1<br>- 如果key不存在，先将key的值初始化为0再执行-1操作；<br>- 如果key中存储的不是数值，直接报错； |                                                              |            | - `DECR k` 将k中存储的数字值-1                               |
| DECRBY      | 将key所存储的值减去指定的值                                  |                                                              |            | - `DECRBY k 100 ` 将k中存储的数字减去100                     |
| GET         | 返回key所对应的字符串值                                      |                                                              |            | - `GET k` 返回k所对应的字符串值                              |
| GETBIT      | 返回key所对应的字符串值上指定偏移量上的位（bit）             |                                                              |            | - `GETBIT k 10086` 返回k所对应的字符串值上的偏移量           |
| GETRANGE    | 返回key所对应的字符串值的子字符串                            | - `start` 子字符串开始位置<br>- `end` 子字符串结束位置       |            | - `GETRANGE k 0 -1` 返回k所对应字符串的第1个字符到最后1个字符的内容<br>- `GETRANGE k 1 4` 返回k所对应字符串的第2到第4个字符的内容 |
| GETSET      | 将给定key的值设置为value，并返回key的old value               |                                                              |            | - 一个典型的原子操作：<br>  `INCR k` 对k自增1<br>  `GETSET k 0` 重置计时器 |
| INCR        | 将key对应的数字值+1，如果key不存在，将key的值初始化为0，再执行INCR操作；<br>用途：<br>+ 可以通过组合使用`INCR`和`EXPIRE`，来达到只在规定的生存时间内进行计数(counting)的目的。<br>+ 客户端可以通过使用`GESET`命令原子性的获取计数器的当前值并将计数器清零。<br>+ 使用其它自增/自减操作，比如`DECR`和`INCRBY`，用户可以通过执行不同的操作增加或减少计数器的值，比如在游戏中的记分器就可能用到这些命令。 |                                                              |            | - 限速器示例：<br>`FUNCTION LIMIT_API_CALL(ip)`<br>` ts = CURRENT_UNIX_TIME() `<br>`keyname = ip+":"+ts `<br>`current = GET(keyname)`<br><br>`IF current != NULL AND current > 10 THEN`<br>`     ERROR "too many requests per second"` <br>`END`  <br><br>`IF current == NULL THEN`<br>     `MULTI`<br>         `INCR(keyname, 1)`<br>         `EXPIRE(keyname, 1)`<br>     `EXEC`<br>`ELSE`<br>     `INCR(keyname, 1)`<br>`END`<br>`PERFORM_API_CALL()` |
| INCRBY      | 将key所存储的值加上增量；如果key不存在，现将key的值初始化为0，再执行命令；操作的值限制在64bit有符号数字内； |                                                              |            | - `INCRBY k 20` k的值+=20                                    |
| INCRBYFLOAT | 为key所存储的值加上浮点数增量（精度最高到小数点后**17位**）； |                                                              |            | - `INCRBYFLOAT k 10.5` k的值+=10.5<br>- `INCRBYFLOAT k 314e-2` k的值+=3.14 |
| MGET        | 返回多个key的值                                              |                                                              |            | - `MGET k1 k2` 返回k1, k2的值                                |
| MSET        | 同时设置多个key-value对（**如果key已经存在，覆盖旧的值**）   |                                                              |            | - `MSET k1 1 k2 2` 将k1的值设置为1, k2的值设置为2            |
| MSETNX      | 同时设置多个key-value对（**如果key已经存在，本次操作失败**） |                                                              |            | - `MSETNX k1 1 k2 2` 将k1的值设置为1, k2的值设置为2          |
| PSETEX      | 以**ms**为单位设置生存时间                                   |                                                              |            | - `PSETEX k 1000 "abc"` 设置k的值为"abc"且其过期时间为1000ms |
| SET         | 设置key的值（**默认：如果key已经存在，覆盖旧的值和过期时间**） | - `EX` 指定过期时长（s）<br>- `PX` 指定过期时长（ms）<br>- `NX` 只有在key不存在时，才对key进行设置<br>- `xx` 只有在key已经存在时，才对key进行设置 |            | - `SET k 1` 设置k的值为1<br>- `SET k "abc" EX 5` 设置k的值为“abc”，过期时长为5s<br>- `SET k "abc" PX 1000` 设置k的值为“abc”，过期时长为1000ms<br>- `SET k "abc" NX` 如果k不存在，设置k的值为“abc”<br>- `SET k "abc" XX` 如果k存在，设置k的值为“abc” |
| SETBIT      | 设置或清除key对应的字符串值上指定偏移量的bit（字符串会grown以确保它可以将value保存在指定的偏移量上，当字符串grown时，空白位置以0填充，偏移量取值范围$[0, 2^{32})$， **注意：偏移量过大可能会导致Redis阻塞，从而触发警告**） |                                                              |            | - `SETBIT b 10086 1` 设置b的偏移位置10086的值为1             |
| SETEX       | 将值关联到key，并设置key的生存时长（s）                      |                                                              |            | - `SETEX k 5 "abc"` 设置k的值为“abc”，并设置生存时长为5s     |
| SETNX       | 当key不存在时，设置key的值                                   |                                                              |            | - `SETNX k "abc"` 当k不存在时，设置k的值为“abc”              |
| SETRANGE    | 设置key对应的值的偏移范围（如果偏移量>值的长度，用零字节"\x00"填充） |                                                              |            | - `SETRANGE k 6 "ab"` 设置k的值，[6]=a, [7]=b                |
| STRLEN      | 返回key所对应的值的长度                                      |                                                              |            | - `STRLEN k` 返回k的值的长度                                 |



## Hash

| 命令         | 说明                                                         | 时间复杂度 | 示例                                                         |
| ------------ | ------------------------------------------------------------ | ---------- | ------------------------------------------------------------ |
| HDEL         | 删除哈希表中的一个或多个指定域，不存在的域将被忽略           |            | - `HDEL h a b` 删除哈希表h中的域a和域b                       |
| HEXISTS      | 查看哈希表中给定域field是否存在                              |            | - `HEXISTS h a` 查看哈希表h中域a是否存在                     |
| HGET         | 返回哈希表中给定域的值                                       |            | - `HGET h a` 返回哈希表h中域a的值                            |
| HGETALL      | 以列表形式返回哈希表中所有的域和值                           |            | - `HGETALL h` 返回哈希表h中所有的域和值                      |
| HINCRBY      | 为哈希表中指定域的值+指定的值（<64bit）                      |            | - `HINCRBY h a 200` 对h.a = h.a + 200<br>- `HINCRBY h a -200` 对h.a = h.a - 200 |
| HINCRBYFLOAT | 为哈希表中指定域的值+指定的浮点值；<br>注意：<br>  - **field的值必须为字符串类型；**<br>  - **field的字符串值必须可以被解析为双精度浮点数（double precision floating point number）；** |            | - `HINCRBYFLOAT h a 0.1 ` 对h.a = h.a + 0.1<br>- `HINCRBYFLOAT h a -0.1` 对h.1 = h.a - 0.1 |
| HKEYS        | 返回哈希表中所有域的key                                      |            | - `HKEYS h` 列出h的所有键                                    |
| HLEN         | 返回哈希表中所有key的数量                                    |            | - `HLEN h` 返回哈希表中h的所有key的数量                      |
| HMGET        | 返回哈希表中多个key的值                                      |            | - `HMGET h key1, key2` 返回哈希表h中的key1, key2的值         |
| HMSET        | 将多个field-value设置到哈希表中                              |            | - `HMSET h k1 v1 k2 v2` 设置哈希表h中k1的值为v1，k2的值为v2  |
| HSET         | 设置哈希表中指定key的值                                      |            | - `HSET h k1 v1` 设置哈希表h中k1的值为v1                     |
| HSETNX       | 当哈希表中指定key的值不存在时，设置key的值                   |            | - `HSETNX h k1 v1` 当h中k1不存在时，设置k1的值为v1           |
| HVALS        | 返回哈希表中所有key的值                                      |            | - `HVALS h` 返回哈希表h中所有key的值                         |
| HSCAN        | 增量迭代，参考**SCAN**命令                                   |            |                                                              |



## List

| 命令       | 说明                                                         | 参数                                  | 时间复杂度 | 示例                                                         |
| ---------- | ------------------------------------------------------------ | ------------------------------------- | ---------- | ------------------------------------------------------------ |
| BLPOP      | **阻塞式**移除并返回多个list的头元素；如果list不存在或包含空列表，`BLPOP`将阻塞至超时或另一个客户端执行`LPUSH`或`RPUSH`命令为止；<br>- 相同的key可以被多个客户端同时阻塞，按照first-BLPOP first-served（先阻塞先服务）的顺序执行`BLPOP`；<br>- 当BLPOP用于流水线时，不进行阻塞操作； |                                       |            | - `BLPOP li1 li2 li3` 移除并返回li1，li2，li3的头元素，如果li1，li2，li3有一个为空，无限期阻塞直到它非空；<br>- `BLPOP li1 li2 5` 移除并返回li1，li2的头元素，如果li1或li2为空，等待5s后结束阻塞；<br>- **非阻塞式**地移除并返回li1的头元素：<br>`MULTI`<br>`BLPOP li1 30`<br>`EXEC`<br>- 轮询示例：<br>消费者：<br>`LOOP forever`<br>    `WHILE SPOP(key) returns elements`<br>        `...`<br>    `END`<br>    `BRPOP helper_key`<br>`END`<br>生产者：<br>`MULTI`<br>    `SADD key element`<br>    `LPUSH helper_key x`<br>`EXEC` |
| BRPOP      | **阻塞式**移除并返回多个列表的最后一个元素                   |                                       |            | - `BRPOP li 30` 阻塞式移除并返回li的最后一个元素的key和value |
| BRPOPLPUSH | **阻塞式**在原子时间内弹出一个列表的最后一个元素并插入到另一个列表的头（如果最后的元素为nil，不执行操作）； |                                       |            | - `BRPOPLPUSH src dst 5` 将src的最后一个元素弹出并插入到dst的头，阻塞式等待5s |
| LINDEX     | 返回列表中指定位置元素的值                                   |                                       |            | - `LINDEX li 0` 返回列表li的第一个元素<br>- `LINDEX li -1` 返回列表li的最后一个元素 |
| LINSERT    | 将值插入列表中指定位置之前或之后（如果列表不存在或为空，不执行操作；如果指定位置不存在，不执行操作） | - `BEFORE` 位置前<br>- `AFTER` 位置后 |            | - `LINSERT h BEFORE "world" "he"` 将"he"插入到列表h的位置"world"的前面； |
| LLEN       | 返回列表的长度                                               |                                       |            | - `LLEN h` 返回列表h的长度                                   |
| LPOP       | 移除并返回列表的头元素                                       |                                       |            | - `LPOP li` 移除并返回列表li的头元素                         |
| LPUSH      | 将多个值（按从左到右）插入到列表的表头（**如果列表不存在，则创建之**） |                                       |            | - `LPUSH li a b c` 将a, b, c插入到列表li，插入之后li的顺序为c, b, a, ... |
| LPUSHX     | 将多个值（按从左到右）插入到列表的表头（**如果列表不存在，则什么也不做**） |                                       |            | - `LPUSHX li a b c` 将a, b, c插入到列表li，插入之后li的顺序为c, b, a, ... |
| LRANGE     | 返回列表中指定范围内的元素                                   |                                       |            | - `LRANGE li 0 0` 返回列表li的第1个元素<br>- `LRANGE li 0 1` 返回列表li范围内[0, 1]的值（即第1，2个元素） |
| LREM       | 移除列表中与指定值相等的n个元素；<br>`n > 0` 从表头开始向表尾搜索，移除n个与指定值相等的元素；<br>`n < 0` 从表尾开始向表头搜索，移除`-n`个与指定值相等的元素；<br>`n = 0` 移除表中所有与指定值相等的元素； |                                       |            | - `LREM li 2 abc` **从表头到表尾开始**，移除列表li中值为"abc"的2个元素<br>- `LREM li -2 abc` **从表尾到表头开始**，移除列表li中值为"abc"的2个元素<br>- `LREM li 0 abc` 移除列表中所有值为"abc"的元素 |
| LSET       | 设置列表中指定下标位置的值（当下表超出范围时，返回一个错误） |                                       |            | - `LSET li 3 "abc"` 设置列表li的3号位置的值为"abc"           |
| LTRIM      | 保留列表指定范围的元素，删除其它位置的元素（如果`起始位置`>`终止位置`或者`起始位置`>`列表的最大下标`，清空列表） |                                       |            | - `LTRIM li 1 -1` 保留列表li第2到最后一个元素，删除其它元素； |
| RPOP       | 移除并返回列表的最后一个元素                                 |                                       |            | - `RPOP li` 移除并返回列表li的最后一个元素                   |
| RPOPLPUSH  | 在原子时间内弹出一个列表的最后一个元素并插入到另一个列表的头（如果最后的元素为nil，不执行操作） |                                       |            | - `RPOPLPUSH src dst` 将src的最后一个元素弹出并插入到dst的头<br>- `RPOPLPUSH src src` 将src的最后一个元素弹出并插入到src的头 |
| RPUSH      | 将多个值（按从左到右的顺序）插入到列表的尾部（**如果列表不存在，创建之**） |                                       |            | - `RPUSH li a b c` 将a, b, c插入到列表li的尾部，插入之后li的内容为：..., a, b, c |
| RPUSHX     | 将多个值（按从左到右的顺序）插入到列表的尾部（**如果列表不存在，不做操作**） |                                       |            | - `RPUSHX li "abc"` 如果li存在，将"abc"插入到li的尾部        |



## Set

| 命令                                                     | 说明                                                         | 时间复杂度 | 示例                                                         |
| -------------------------------------------------------- | ------------------------------------------------------------ | ---------- | ------------------------------------------------------------ |
| SADD                                                     | 将多个元素加入到集合中，忽略已经存在的元素（如果集合不存在，创建之） |            | - `SADD s "abc" "def"` 将"abc", "def"加入到集合s中           |
| ZCARD                                                    | 返回集合中元素的数量                                         |            | - `ZCARD s` 返回集合s中元素的数量                            |
| SDIFF                                                    | 返回多个集合的**差集**                                       |            | - `SDIFF s1 s2` 返回集合s1与s2的差集                         |
| SDIFFSTORE                                               | 返回多个集合的**差集**，并将其保存到第1个集合                |            | - `SDIFFSTORE s1 s2 s3` 返回s2与s3的差集，并将它保存到s1     |
| SINTER                                                   | 返回多个集合的**交集**                                       |            | - `SINTER s1 s2` 返回s1与s2的交集                            |
| SINTERSTORE                                              | 返回多个集合的**交集**，并将其保存到第1个集合                |            | - `SINTERSTORE s1 s2 s3` 返回s2与s3的交集，并将它保存到s1    |
| SISMEMBER                                                | 判断给定元素是否存在于集合中                                 |            | - `SISMEMBER s1 "abc"` 判断"abc"是否存在于集合s1中           |
| SMEMBERS（**性能有问题，建议使用增量迭代系列命令SCAN**） | 返回集合包含的所有成员                                       |            | - `SMEMBERS s1` 返回集合s1中的所有成员                       |
| SMOVE                                                    | 将指定元素从一个集合移动到另一个集合（原子操作）             |            | - `SMOVE src dst "abc"` 将src中的元素“abc”移动到dst          |
| SPOP                                                     | 从集合中随机移除一个元素并返回                               |            | - `SPOP s1` 从s1中随机移除一个元素并返回                     |
| SRANDMEMBER                                              | 从集合中随机选取指定数量n的元素<br>1. 如果n为正数，且小于集合中元素数量，那么返回一个包含n个**各不相同**的元素的数组；<br>2. 如果n为负数，那么返回一个容量为`-n`的数组，数组中的元素可能会**重复多次**； |            | - `SRANDMEMBER s1 3` 从s1中随机返回3个元素                   |
| SREM                                                     | 移除集合中多个元素                                           |            | - `SREM s1 "a" "b" "c"` 移除集合s1中的三个元素"a", "b", "c"  |
| SUNION                                                   | 返回多个集合的**并集**                                       |            | - `SUNION s1 s1` 返回集合s1和s2的并集                        |
| SUNIONSTORE                                              | 返回多个集合的**并集**，并将结果存储到第1个集合              |            | - `SUNIONStORE s1 s2 s3` 返回集合s2和s3的并集，并将结果保存到s1 |
| SSCAN                                                    | 增量迭代，参考**SCAN**命令                                   |            |                                                              |



## Zset

| 命令             | 说明                                                        | 参数                                                         | 时间复杂度 | 示例                                                         |
| ---------------- | ----------------------------------------------------------- | ------------------------------------------------------------ | ---------- | ------------------------------------------------------------ |
| ZADD             | 将多个元素及分数加入到有序集中（如果元素已存在，更新其值）  |                                                              |            | - `ZADD z1 5 a 6 b` 将[a, 5], [b, 6]加入到有序集合z1         |
| ZCARD            | 返回有序集内的元素数量                                      |                                                              |            | - `ZCARD z1` 返回有序集合z1内的元素数量                      |
| ZCOUNT           | 返回有序集合内指定分数值范围内的元素                        |                                                              |            | - `ZCOUNT z1 2 5` 返回分数在[2, 5]之间的元素                 |
| ZINCRBY          | 为有序集合中指定元素加上增量（如果元素不存在，添加之）      |                                                              |            | - `ZSCORE z1 10 a` 将有序集合z1中的元素a的分值+10<br>- `ZSCORE z1 -10 a` 将有序集合z1中的元素a的分值-10 |
| ZRANGE           | 返回有序集合中指定索引范围的元素（按从小到大排列）          | - `WITHSCORES` 返回分数                                      |            | - `ZRANGE z1 0 -1 WITHSCORES` 返回整个有序集z1的成员<br>- `ZRANGE z1 1 2` 返回有序集z1的范围[1, 2]中的成员（不返回分数） |
| ZRANGEBYSCORE    | 返回有序集合中指定分值范围的元素                            | - `LIMIT` 指定返回的数量和区间<br>- `WITHSCORES` 返回分数<br>- `(` 使用开区间 |            | - `ZRANGEBYSCORE z1 1 5` 返回有序集合z1中分值<=1且<=5的成员<br>- `ZRANGEBYSCORE z1 (1 5` 返回有序集合z1中分值<1且<=5的成员<br>- `ZRANGEBYSCORE z1 -inf +inf` 返回有序集合z1中的所有成员<br>- `ZRANGEBYSCORE z1 -inf 5` 返回有序集合z1中分值<=5的成员 |
| ZRANK            | 返回有序集合中指定成员的排名（按从小到大）                  |                                                              |            | - `ZRANK z1 a` 返回有序集合z1中成员a的排名（从小到大）       |
| ZREM             | 移除有序集合中一个或多个成员                                |                                                              |            | - `ZREM z1 a b` 移除有序集合z1中的元素a, b                   |
| ZREMRANGEBYRANK  | 移除有序集合中指定排名区间内的成员                          |                                                              |            | - `ZREMRANGEBYRANK z1 0 1` 移除有序集合z1中排名第1，2的元素  |
| ZREMRANGEBYSCORE | 移除有序集合中指定分值范围的元素                            |                                                              |            | - `ZREMRANGEBYSCORE z1 3 5` 移除有序集合z1中分值在[3, 5]之间的元素 |
| ZREVRANGE        | 返回有序集合中指定索引区间内的成员（按从大到小排列）        |                                                              |            | - `ZREVRANGE z1 0 -1 WIthSCORES` 按从大到小的顺序，返回有序集合z1中的所有成员 |
| ZREVRANGEBYSCORE | 返回有序集合中指定分值区间内的成员（按从大到小排列）        |                                                              |            | - `ZREVRANGEBYSCORE z1 +inf -inf` 逆序排列有序集合z1中的成员<br>- `ZREVRANGEBYSCORE z1 3 5` 逆序排列有序集合z1中分值介于[3, 5]之间的成员 |
| ZREVRANK         | 返回有序集合中指定成员的排名（按从大到小）                  |                                                              |            | - `ZREVRANK z1 a` 返回有序集合z1中成员a的排名（从大到小）    |
| ZSCORE           | 返回有序集合中指定成员的分值                                |                                                              |            | - `ZSCORE z1 a` 返回有序集合z1中成员a的分值                  |
| ZUNIONSTORE      | 计算多个有序集中指定数量的**并集**，并将结果存储到第1个集合 | - `WEIGHTS` 指定乘法因子(multiplication factor)<br>- `AGGREGATE` 指定并集的结果集的聚合方式：<br>1. `SUM` （默认）将所有集合中某个成员的score值之和作为结果集中该成员的score值；<br>2. `MIN` 将所有集合中某个成员的最小score值作为结果集中该成员的score值；<br>3. `MAX` 将所有集合中某个成员的最大score值作为结果集中该成员的score值； |            | - `ZUNIONSTORE z1 2 z2 z3 WEIGHTS 1 3` 将z2的值x1，将z3的值x3，并将计算结果存储于z1 |
| ZINTERSTORE      | 计算指定数量的有序集的**交集**，并将结果存储到第1个集合     |                                                              |            | - `ZINTERSTORE z1 2 z2 z3` 计算z2与z3的交集，并将结果存储到z1 |
| ZSCAN            | 增量迭代，参考**SCAN**命令                                  |                                                              |            |                                                              |



## Pub/Sub

| 命令         | 说明                       | 时间复杂度 | 示例                                                         |
| ------------ | -------------------------- | ---------- | ------------------------------------------------------------ |
| PSUBSCRIBE   | 以模糊匹配的方式订阅频道   |            | - `PSUBSCRIBE AB*` 模糊匹配订阅以AB开头的频道                |
| PUBLISH      | 向频道发布消息             |            | - `PUBLISH ch "hello"` 向频道ch发送消息"hello"               |
| PUBSUB       | 查看发布订阅信息           |            | - `PUBSUB CHANNELS *.abc` 查看匹配频道<br>- `PUBSUB NUMSUM ch1 ch2` 查看ch1和ch2的订阅者数量<br>- `PUBSUB NUMPAT` 查看订阅模式的数量 |
| PUNSUBSCRIBE | 以模糊匹配方式取消订阅频道 |            | - `PUNSUBSCRIBE AB*` 取消模糊匹配以AB开头的频道              |
| SUBSCRIBE    | 订阅频道                   |            | - `SUBSCRIBE AB` 订阅频道AB                                  |
| UNSUBSCRIBE  | 取消订阅                   |            | - `UNSUBSCRIBE AB` 取消订阅频道AB                            |



## Transaction

| 命令    | 说明                                                         | 时间复杂度 | 示例                                  |
| ------- | ------------------------------------------------------------ | ---------- | ------------------------------------- |
| DISCARD | 取消事务的执行，放弃执行事务块内的所有命令                   |            | - `DISCARD` 取消事务的执行            |
| EXEC    | 执行所有事务块内的命令（如果事务中有key处于WATCH命令的监视下，EXEC命令只有在这些key没有被其它命令所改动的情况下才生效，否则该事务被打断(abort)） |            | - `MULTI`<br>  `SET a "xx"`<br>`EXEC` |
| MULTI   | 标记一个事务块的开始                                         |            |                                       |
| UNWATCH | 取消`WATCH`命令对所有key的监视                               |            |                                       |
| WATCH   | 监视一个或多个key，如果在事务执行前这些key被其它命名所改动，那么事务将被打断 |            | - `WATCH k1 k2` 监视键k1，k2          |



## HyperLogLog

| 命令    | 说明                                       | 时间复杂度 | 示例                           |
| ------- | ------------------------------------------ | ---------- | ------------------------------ |
| PFADD   | 增加计数                                   |            | - `PFADD k1 "k1"` 增加k1的计数 |
| PFCOUNT | 获取计数                                   |            | - `PFCOUNT k1` 获取k1的计数    |
| PFMERGE | 用于将多个pf计数值类加在一起形成一个新的pf |            |                                |



## Script

| 命令          | 说明                                   | 时间复杂度 | 示例                                                         |
| ------------- | -------------------------------------- | ---------- | ------------------------------------------------------------ |
| EVAL          | 传入参数，并执行LUA语句                |            | - `EVAL "return {KEYS[1],KEYS[2],ARGV[1]}" 2 key1 key2 first` 执行一段LUA语句，传入2个**键名参数**，以及附加参数first<br>- `EVAL "return redis.call('set',KEYS[1],'xx')" 1 foo` 执行一段LUA脚本，将foo的值设置为xx<br>- `EVAL "return {1, 2, {3, 'hello world'}}" 0` Lua表转Redis状态回复 |
| EVALSHA       | 传入参数，并执行指定SHA校验和的LUA语句 |            | - `EVALSHA 6b1bf486c81ceb7edf3c093f4c48582e38c0e791 0` 执行指定校验和的Lua语句 |
| SCRIPT EXISTS | 判断指定SHA校验和的脚本是否存在        |            | - `SCRIPT EXISTS 232fd51614574cf0867b83d384a5e898cfd24e5a` 判断指定校验和的Lua脚本是否存在 |
| SCRIPT FLUSH  | 清空所有脚本缓存                       |            | - `SCRIPT FLUSH` 清空所有LUA脚本缓存                         |
| SCRIPT KILL   | 终止当前正在运行的脚本                 |            | - `SCRIPT KILL` 杀死当前正在运行的LUA脚本                    |
| SCRIPT LOAD   | 将一个脚本载入缓存，但**不立即运行**   |            | - `SCROPT LOAD "return 'hello world'"` 载入Lua脚本           |



## Server

| 命令             | 说明                                                         | 时间复杂度 | 示例                                                         |
| ---------------- | ------------------------------------------------------------ | ---------- | ------------------------------------------------------------ |
| BGREWRITEAOF     | 手动触发AOF文件重写操作                                      |            | - `BGREWRITEAOF` 重写AOF文件                                 |
| BGSAVE           | 后台异步保存当前数据库的数据到磁盘                           |            | - `BGSAVE` 后台异步保存当前数据库的数据                      |
| CLIENT GETNAME   | 返回当前连接的别名                                           |            | - `CLIENT GETNAME` 返回当前连接的别名                        |
| CLIENT KILL      | 关闭指定地址的客户端                                         |            | - `CLIENT KILL 127.0.0.1:6379` 关闭与地址`127.0.0.1:6379`连接的客户端 |
| CLIENT LIST      | 返回所有连接到服务器的客户端信息和统计数据                   |            | - `CLIENt LIST` 列出所有客户端的信息                         |
| CLIENT SETNAME   | 为当前连接分配一个别名                                       |            | - `CLIENT SETNAME hello` 为当前连接设置别名hello             |
| CONFIG GET       | 获得运行中的Redis服务器的指定配置的参数                      |            | - `CONFIG GET s*` 返回所有以s开头的配置参数<br>- `CONFIG GET slowlog-max-len` 返回配置`slowlog-max-len`的值<br>- `CONFIG GET *` 列出所有的配置值 |
| CONFIG RESETSTAT | 重置以下统计数据：<br>- `Keyspace hits` 键空间命中次数<br>- `Keyspace misses` 键空间不命中次数<br>- `Number of commands processed` 执行命令的次数<br>- `Number of connections received` 连接服务器的次数<br>- `Number of expired keys` 过期key的数量<br>- `Number of rejected connections` 被拒绝的连接数量<br>- `Latest fork(2) time` 最后执行fork(2)的时间<br>- `The aof_delayed_fsync counter` aof_delayed_fsync计数器的值 |            | - `CONFIG RESETSTAT` 重置统计数据                            |
| CONFIG REWRITE   | 原子性地重写Redis服务器的配置文件`redis.conf`                |            | - 修改配置文件的appendonly选项：<br>`CONFIG SET appendonly yes`<br>`CONFIG REWRITE` |
| CONFIG SET       | 修改配置文件的参数                                           |            | - `CONFIG SET appendonly yes` 开启追加模式                   |
| DBSIZE           | 返回当前数据库的key的数量                                    |            | - `DBSIZE` 返回当前数据库的key的数量                         |
| DEBUG OBJECT     | （调试命令）返回某个对象的信息                               |            | - `DEBUG OBJECT obj` 返回对象obj的信息                       |
| DEBUG SEGFAULT   | （调试命令）模拟BUG，执行一个不合法的内存访问从而让Redis崩溃 |            | - `DEBUG SEGFAULT` 让Redis崩溃                               |
| FLUSHALL         | 清空整个Redis服务器的数据                                    |            | - `FLUSHALL` 清空**所有数据库**的**所有数据**                |
| FLUSHDB          | 清空当前数据库中的所有数据                                   |            | - `FLUSHDB` 清空当前数据库的所有数据                         |
| INFO             | 显示信息                                                     |            | - `INFO server` 服务器信息<br>- `INFO clients` 已连接客户端信息<br>- `INFO memory` 内存信息<br>- `INFO persistence` RDB和AOF相关信息<br>- `INFO stats` 一般统计信息<br>- `INFO replication` 主从复制信息<br>- `INFO cpu` CPU统计信息<br>- `INFO commandstats` 命令统计信息<br>- `INFO cluster` 集群信息<br>- `INFO keyspace` 数据库相关的统计信息 |
| LASTSAVE         | 返回最近一次Redis成功将数据保存到磁盘上的时间，以UNIX时间戳格式表示 |            | - `LASTSAVE` 返回最近一次数据保存时间                        |
| MONITOR          | （调试命令）实时打印出Redis服务器接收到的命令                |            | - `MONITOR` 实时打印出收到的Redis命令                        |
| PSYNC            | 部分重同步数据（新版）                                       |            | - `PSYNC ? -1` 主动请求主服务器进行完整重同步<br>- `PSYNC 53b9b28df8042fdc9ab5e3fcbbbabff1d5dce2b3 20000` 主动请求主服务器同步偏移量2000之后的数据 |
| SAVE             | 执行一个同步保存操作，将当前Redis实例的所有数据快照以RDB文件的形式保存到硬盘 |            | - `SAVE` 执行一个同步保存操作                                |
| SHUTDOWN         | 关闭Redis服务器                                              |            | - `SHUTDOWN` 关闭redis服务器                                 |
| SLAVEOF          | 设置当前服务器的主服务器                                     |            | - `SLAVEOF 127.0.0.1 6379` 设置当前服务器的主服务器为127.0.0.1:6379 |
| SLOWLOG          | 查看slow log日志                                             |            | - `SLOWLOG GET 10` 查看10条日志<br>- `SLOWLOG LEN` 返回日志的数量 |
| SYNC             | 重同步数据（**效率不佳**）                                   |            | - `SYNC` 重同步数据                                          |
| TIME             | 返回当前服务器的时间                                         |            | - `TIME` 返回当前服务器时间                                  |



## 其它

| 命令     | 说明                                     | 时间复杂度 | 示例                                                         |
| -------- | ---------------------------------------- | ---------- | ------------------------------------------------------------ |
| SENTINEL | 哨兵命令                                 |            | - `SENTINEL is-master-down-by-addr 127.0.0.1 6379 0 *` 询问其他哨兵，master(127.0.0.1:6379)是否已下线 |
| AUTH     | 检测给定的密码是否和配置文件中的密码一致 |            | - `AUTH hello` 检测配置的密码是不是hello                     |
| FLUSHALL | 删除所有数据库的所有key                  |            | - `FLUSHALL` 删除所有数据                                    |
| INCR     | 将key的值+1                              |            | - `INCR a` 将a对应的值+1                                     |
| REPLCONF | TODO                                     |            |                                                              |



## 参考

[1] 黄健宏.Redis设计与实现

[2] [Redis 命令参考](http://doc.redisfans.com/)
