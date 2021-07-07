# redis源码总结

## 数据结构
- 内存分配
    - zmalloc.h
    - zmalloc.c
- 动态字符串
    - sds.h
    - sds.c
- 双端链表
    - adlist.h
    - adlist.c
- 字典
    - dict.h
    - dict.c
- 跳表
    - server.h
    - t_zset.c
- 日志
    - hyperloglog.c

## 数据类型
- 对象系统
    - object.c
- string
    - t_string.c
- list
    - t_list.c
- hash
    - t_hash.c
- set
    - t_set.c
- zset
    - t_zset.c

## 编码
- 整数集合数据结构
    - intset.h
    - intset.c
- 压缩列表数据结构
    - ziplist.h
    - ziplist.c

## 数据库功能实现
- 基本数据库功能
    - redis.h
    - db.c
- 通知功能
    - notify.c
- RDB持久化
    - rdb.c
- AOF持久化
    - aof.c
- 发布订阅
    - redis.h
    - pubsub.c
- 事务
    - redis.h
    - multi.c

## 客户端和服务端
- 事件处理
    - ae.c
    - ae_epoll.c
    - ae_evport.c
    - ae_kqueue.c
    - ae_select.c
- 网络连接库
    - anet.c
    - networking.c
- 服务端
    - redis.c
- 客户端
    - redis-cli.c

## 集群
- 复制功能
    - replication.c
- 集群
    - cluster.c

## 独立模块
- lua
    - scripting.c
- 慢查询
    - slowlog.c
- 监视
    - monitor.c

## 其他

