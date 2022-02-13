# Redis配置

[TOC]



Redis的配置文件在不同系统下有不同的路径，以下为以下常用的路径：

- ubuntu

  ```sh
  /etc/redis/redis.conf
  ```

  

## 配置说明

| 配置                                   | 说明                                                         |
| -------------------------------------- | ------------------------------------------------------------ |
| `daemonize <yes/no>`                   | 是否为后台守护模式                                           |
| `down-after-milliseconds <ms>`         | 哨兵判断实例进入主观下线所需的时间长度（单位：ms）           |
| `pidfile <file_path>`                  | 设置进程ID保存文件                                           |
| `port <num>`                           | 设置端口                                                     |
| `timeout <second>`                     | 客户端空闲超时时长（单位：s）                                |
| `loglevel <lvl>`                       | 设置日志等级；<br>  - debug<br>  - verbose<br>  - notice<br>  - warning |
| `logfile <file_path_name>`             | 设置日志文件                                                 |
| `databases <db_num>`                   | 设置数据库数量(默认0)                                        |
| `save <second> <mod_time>`             | 在多长时间(second)内，有所少次更新操作(mod_time)，就将数据同步到数据文件，可以多个条件配合 |
| `stop-write-on-bgsave-error <yes/no>`  | 最近一次save操作失败则停止写操作                             |
| `rdbcompression <yes/no>`              | RDB文件压缩                                                  |
| `rdbchecksum <yes/no>`                 | RDB文件启用CRC64校验码（对性能有影响）                       |
| `dbfilename <db_file_name>`            | 设置本地数据库文件名                                         |
| `dir <path>`                           | 设置本地数据库路径                                           |
| `requirepass <passwd>`                 | 有slave连接时需要提供的密码                                  |
| `appendonly <yes/no>`                  | 是否每次更新操作后进行日志记录                               |
| `appendfsync <no/always/everyusec>`    | 更新日志条件；<br>  - no 等操作系统进行数据缓存同步到磁盘（快）<br>  - always 每次更新操作后手动调到fsync()将数据写到磁盘（慢，安全）<br>  -`everysec` 每秒同步一次（默认） |
| `notify-keyspace-events <KEg$lshzXeA>` | 设置服务器所发送通知的类型；<br>  -`K` 键空间通知，所有通知以 `__keyspace@<db>__` 为前缀<br>  -`E` 键事件通知，所有通知以 `__keyevent@<db>__` 为前缀<br>  -`g` 类型无关的通用命令的通知<br>  -`$` 字符串命令通知<br>  -`l` 列表命令通知<br>  -`s` 集合命令通知<br>  -`h` 哈希命令通知<br>  -`z` 有序集合命令通知<br>  -`X` 过期事件（每当有过期键被删除时发送）<br>  -`e` 驱逐(evict)事件（每当有键因为 `maxmemory` 政策而被删除时发送）<br>  -`A` 参数 `g$lshzxe` 的别名<br>  -`AKE` 发送所有类型的键空间和键事件通知 |
| `repl-backlog-size`                    | 设置复制积压缓冲区大小；<br>（可不带单位，但同时支持单位：b, k, kb, m, mb, g, gb；单位不区分大小写，其中k, m, g的计算倍数是1000，而kb, mb和gb的计算倍数是1024） |
| `repl-backlog-ttl`                     | 复制积压缓冲区存活时长（当所有slaves不可用时，保留多长时间，单位：s） |
| `maxclients <cli_num>`                 | 同一时间内的最大clients连接数量                              |
| `maxmemory <bytes>`                    | 设置内存最大使用量；0：表示不限制；                          |
| `maxmemory-policy`                     | 设置内存置换策略；<br>  - `noeviction` 不要淘汰任何数据，大部分写操作会返回错误；<br>  - `allkeys-lru` 使用近似的LRU算法淘汰长时间没有使用的键<br>  - `volatile-lru` 使用近似的LRU淘汰数据，仅设置过期的键；<br>  - `allkeys-random` 删除随机键，任何键；<br>  - `volatile-random` 随机删除设置了过期时间的键；<br>  - `volatile-ttl` 删除最接近到期时间（较小的TTL）的键；<br>  -  `volatile-lfu` 在设置了过期时间的键中，使用近似的LFU算法淘汰使用频率比较低的键；<br>  - `allkeys-lfu` 使用近似的LFU算法淘汰整个数据库的键。 |

例：

```sh
#修改为守护模式
daemonize yes
#设置进程锁文件
pidfile /usr/local/redis-4.0.9/redis.pid
#端口
port 6379
#客户端超时时间
timeout 300
#日志级别
loglevel debug
#日志文件位置
logfile /usr/local/redis-4.0.9/log-redis.log
#设置数据库的数量，默认数据库为0，可以使用SELECT <dbid>命令在连接上指定数据库id
databases 16
##指定在多长时间内，有多少次更新操作，就将数据同步到数据文件，可以多个条件配合
#save <seconds> <changes>
#Redis默认配置文件中提供了三个条件：
save 900 1
save 300 10
save 60 10000
#指定存储至本地数据库时是否压缩数据，默认为yes，Redis采用LZF压缩，如果为了节省CPU时间，
#可以关闭该#选项，但会导致数据库文件变的巨大
rdbcompression yes
#指定本地数据库文件名
dbfilename dump.rdb
#指定本地数据库路径
dir /usr/local/redis-4.0.9/db/
#指定是否在每次更新操作后进行日志记录，Redis在默认情况下是异步的把数据写入磁盘，如果不开启，可能
#会在断电时导致一段时间内的数据丢失。因为 redis本身同步数据文件是按上面save条件来同步的，所以有
#的数据会在一段时间内只存在于内存中
appendonly no
#指定更新日志条件，共有3个可选值：
#no：表示等操作系统进行数据缓存同步到磁盘（快）
#always：表示每次更新操作后手动调用fsync()将数据写到磁盘（慢，安全）
#everysec：表示每秒同步一次（折衷，默认值）
appendfsync everysec
```



## 命令

### 获得配置项的值

```sh
CONFIG GET <配置项>
```

### 编辑配置项

```sh
CONFIG SET <配置项> <值>
```



## 源码

```c
```



