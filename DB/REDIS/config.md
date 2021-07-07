# redis配置



## 摘要

简述redis的配置情况



## 详细配置

| 配置           | 参数1                                                        | 参数2 | 说明                                                         |
| -------------- | ------------------------------------------------------------ | ----- | ------------------------------------------------------------ |
| daemonize      | - yes<br>- no                                                |       | 是否为守护模式                                               |
| pidfile        | 路径                                                         |       | 设置进程锁文件                                               |
| port           | 默认6379                                                     |       | 端口                                                         |
| timeout        |                                                              |       | 客户端超时时间（s）                                          |
| loglevel       | - debug<br>-                                                 |       | 日志等级                                                     |
| logfile        | 路径                                                         |       | 日志文件位置                                                 |
| databases      | 默认0                                                        |       | 数据库的数量                                                 |
| save           | 秒数                                                         | 次数  | 在多长时间内，有所少次更新操作，就将数据同步到数据文件，可以多个条件配合 |
| rdbcompression | - yes<br>- no                                                |       |                                                              |
| dbfilename     | 数据库文件名                                                 |       | 本地数据库文件名                                             |
| dir            | 路径                                                         |       | 本地数据库路径                                               |
| appendonly     | - yes<br>- no                                                |       | 是否每次更新操作后进行日志记录                               |
| appendfsync    | - no 等操作系统进行数据缓存同步到磁盘（快）<br>- always 每次更新操作后手动调到fsync()将数据写到磁盘（慢，安全）<br>- everysec 每秒同步一次（默认） |       | 更新日志条件                                                 |

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

