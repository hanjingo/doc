## redis持久化方式：
- 快照：将某一时刻的所有数据写入硬盘；
- 追加：只修改变化的部分；

## AOF与快照文件：
- AOF:对redis进行的写操作命令存储在硬盘的文件；
- 快照：某一时刻redis的所有数据；

## AOF持久化
### 1.appendfsync选项
- always：每个redis写命令都要将数据同步到硬盘；
- everysec：每秒执行一次同步；
- no：让操作系统决定何时同步；

### 2.auto-aof-rewrite-percentage
在AOF文件大于指定百分比时将数据同步到硬盘；

### 3.auto-aof-rewrite-min-size:
在AOF文件大于指定大小时将数据同步到硬盘；

## redis复制
主从服务器；

## 验证和修复快照文件
redis在修复时，通过计算快照文件的SHA1散列值和SHA256散列值来对内容进行验证；如果文件有错，目前暂无方法对其进行修正；

检查AOF文件使用redis-check-aof程序。

检查快照文件使用redis-check-dump程序。