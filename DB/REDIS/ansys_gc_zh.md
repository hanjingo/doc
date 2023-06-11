# Redis源码分析-内存回收


<!-- vim-markdown-toc GFM -->

* [内存管理](#内存管理)
    - [置换策略](#置换策略)
        + [noeviction](#noeviction)
        + [allkeys-lru](#allkeys-lru)
        + [volatile-lru](#volatile-lru)
        + [allkeys-random](#allkeys-random)
        + [volatile-random](#volatile-random)
        + [volatile-ttl](#volatile-ttl)
* [参考](#参考)

<!-- vim-markdown-toc -->


## 内存管理

### 置换策略

#### noeviction

#### allkeys-lru

#### volatile-lru

#### allkeys-random

#### volatile-random

#### volatile-ttl



## 参考

[1] [Redis 缓存过期（maxmemory） 配置/算法 详解](https://www.cnblogs.com/52php/p/6171172.html)

[2] [redis 源码走读 maxmemory 数据淘汰策略](https://www.jianshu.com/p/0dd701d1442d)

