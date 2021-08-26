[TOC]

# Redis持久化



## RDB文件的创建与载入

有2条命令可以生成RDB文件：

- `SAVE` 创建RDB文件（阻塞）
- `BGSAVE` 后台创建RDB文件（派生出一个子进程来操作，非阻塞）

**注意：**

1. Redis会优先使用AOF文件来还原数据库，只有在AOF功能关闭的情况下，才使用RDB文件来还原数据库状态。
2. `BGSAVE`命令执行期间，客户端发送过来的`SAVE`和`BGSAVE`命令会被拒绝；`BGREWRITEAOF`命令会被延迟到`BGSAVE`命令执行完毕以后再执行。
3. `BGREWRITEAOF`命令执行期间，客户端发送过来的`BGSAVE`命令会被拒绝。

### 源码实现

#### 保存RDB

Redis使用函数`int rdbSave(char *filename)`或`int rdbSaveBackground(char *filename)`保存RDB文件到数据库。

```c
/** @brief 保存RDB文件到磁盘 @param filename RDB文件路径 */
int rdbSave(char *filename) {
    char tmpfile[256];
    FILE *fp;
    rio rdb;
    int error;

    snprintf(tmpfile,256,"temp-%d.rdb", (int) getpid());
    fp = fopen(tmpfile,"w"); /* 创建临时文件 temp-进程ID.rdb */
    if (!fp) {
        redisLog(REDIS_WARNING, "Failed opening .rdb for saving: %s",
            strerror(errno));
        return REDIS_ERR;
    }

    rioInitWithFile(&rdb,fp);
    if (rdbSaveRio(&rdb,&error) == REDIS_ERR) { /* 复制一份RDB副本并保存到临时文件 */
        errno = error;
        goto werr;
    }

    /* Make sure data will not remain on the OS's output buffers */
    if (fflush(fp) == EOF) goto werr;
    if (fsync(fileno(fp)) == -1) goto werr;
    if (fclose(fp) == EOF) goto werr;

    /* Use RENAME to make sure the DB file is changed atomically only
     * if the generate DB file is ok. */
    if (rename(tmpfile,filename) == -1) { /* 重命名临时文件 */
        redisLog(REDIS_WARNING,"Error moving temp DB file on the final destination: %s", strerror(errno));
        unlink(tmpfile);
        return REDIS_ERR;
    }
    redisLog(REDIS_NOTICE,"DB saved on disk");
    server.dirty = 0;
    server.lastsave = time(NULL);
    server.lastbgsave_status = REDIS_OK;
    return REDIS_OK;

werr:
    redisLog(REDIS_WARNING,"Write error saving DB on disk: %s", strerror(errno));
    fclose(fp);
    unlink(tmpfile);
    return REDIS_ERR;
}
```

#### 载入RDB

Redis使用函数`int rdbLoad(char *filename)`来载入RDB文件。

```c
/** @brief 载入RDB文件 @param filename 文件路径 */
int rdbLoad(char *filename) {
	...   
}
```



## 持久化策略

### save选项

用户通过`save`选项可以设置多个保存条件，只要其中任一个条件被满足，Redis就会执行`BGSAVE`命令；

源码如下：

```c
struct redisServer {
    struct saveparam *saveparams;   /* 配置“save”的参数 <秒数> <修改数> */
    int saveparamslen;              /* 配置“save”的条数 */
}
```

### dirty计数器和lastsave属性

- `dirty` 最后一次成功持久化后新增的修改数
- `lastsave` 最后一次成功持久化的时间

源码如下：

```c
struct redisServer {
    long long dirty;                /* 最后一次成功持久化后新增的修改数 */
    time_t lastsave;                /* 最后一次成功持久化的时间 */
}
```

### 保存条件检查函数

`serverCron`默认每隔100ms执行一次，用于检查`save`选项所设置的保存条件是否已经满足。

TODO

