# Redis持久化



## 摘要

持久化的2种方式

- RDB

  snapshotting，快照模式；把当前内存中的数据集快照写入磁盘

- AOF

  append-only-file，追加模式；保存redis所执行的写命令来记录数据库状态



## RDB

### 触发方式

- 自动触发

  默认方式，可以通过设置配置文件的以下参数来设置自动触发：

  - save

- 手动触发

  可以使用以下命令来触发持久化：

  - save
  - bgsave

### 源码

```c++
struct redisServer {
      long long dirty;                /* Changes to DB from the last save */
    long long dirty_before_bgsave;  /* Used to restore dirty on failed BGSAVE */
    pid_t rdb_child_pid;            /* PID of RDB saving child */
    struct saveparam *saveparams;   /* Save points array for RDB */
    int saveparamslen;              /* Number of saving points */
    char *rdb_filename;             /* Name of RDB file */
    int rdb_compression;            /* Use compression in RDB? */
    int rdb_checksum;               /* Use RDB checksum? */
    time_t lastsave;                /* Unix time of last successful save */
    time_t lastbgsave_try;          /* Unix time of last attempted bgsave */
    time_t rdb_save_time_last;      /* Time used by last RDB save run. */
    time_t rdb_save_time_start;     /* Current RDB save start time. */
    int rdb_child_type;             /* Type of save by active child. */
    int lastbgsave_status;          /* REDIS_OK or REDIS_ERR */
    int stop_writes_on_bgsave_err;  /* Don't allow writes if can't BGSAVE */
    int rdb_pipe_write_result_to_parent; /* RDB pipes used to return the state */
    int rdb_pipe_read_result_from_child; /* of each slave in diskless SYNC. */
}
```



## AOF

### 触发方式

配置`appendonly`为`yes`可以触发追加保存模式

