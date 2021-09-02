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
    fp = fopen(tmpfile,"w"); /* 创建临时文件 temp-进程ID.rdb */
    ...
    if (rdbSaveRio(&rdb,&error) == REDIS_ERR) { /* 复制一份RDB副本并保存到临时文件 */
    ...
    if (rename(tmpfile,filename) == -1) { /* 重命名临时文件 */
    ...
}
```

服务器载入文件时的判断流程：

```flow
a=>operation: 服务器启动
load=>operation: 执行载入程序
isAOFEnable=>condition: 已开启AOF持久化功能？
loadAOF=>operation: 载入AOF文件
loadRDB=>operation: 载入RDB文件

a->load->isAOFEnable
isAOFEnable(yes)->loadAOF
isAOFEnable(no)->loadRDB
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

源码如下：

```c
TODO
```



## RDB文件结构

一个完整的RDB文件结构：

| REDIS | db_version | databases | EOF   | check_sum |
| ----- | ---------- | --------- | ----- | --------- |
| 5byte | 4byte      | 变长      | 1byte | 8字节     |

- `REDIS`：即'R''E''D''I''S'这五个字符，用于标识这是一个Redis的RDB文件。

- `db_version`：字符串形式的整数，记录了RDB文件的版本号。

- `databases`：包含着0或任意多个数据库以及各数据库中间的键值对数据；结构如下：

  | SELECTDB | db_number | key_value_pairs |
  | -------- | --------- | --------------- |
  | 1byte    | 1/2/5byte | 变长            |

  - `SELECTDB`：标识接下来要读的是一个数据库的ID；

  - `db_number`：数据库ID，根据ID的大小可以为1/2/5字节；

  - `key_value_pairs`：键值对数据；可以分为以下几类：

    - 不带过期时间的键值对

      | TYPE  | key  | value |
      | ----- | ---- | ----- |
      | 1byte | 变长 | 变长  |

      - `TYPE`：记录了value的类型，格式为REDIS_RDB_TYPE_XXX；
      - `key`：键值对的键，字符串类型；
      - `value`：键值对的值，它的编码方式说明[在这里](#value的编码)

    - 带过期时间的键值对

      | EXPIRETIME_MS | ms    | TYPE  | key  | value |
      | ------------- | ----- | ----- | ---- | ----- |
      | 1byte         | 8byte | 1byte | 变长 | 变长  |

      - `EXPIRETIME_MS`：告知读入程序，接下来要读入的是一个以毫秒为单位的过期时间；
      - `ms`：带符号整数，记录键值对的过期时间(ms)；
      - `TYPE`：同上
      - `key`：同上
      - `value`：同上

- `EOF`：标志着RDB文件正文内容已结束；

- `check_sum`：无符号整数，保存一个校验和（通过计算REDIS, db_version, databases, EOF得出）。

### value的编码

RDB文件中键值对的value可以为以下任何类型：

- 字符串对象

  字符串对象(REDIS_RDB_TYPE_STRING)的编码方式有以下2种：

  - `REDIS_ENCODING_INT`
  - `REDIS_ENCODING_RAW`

  对于不同长度的字符串，**开启文件压缩功能时**，其保存方式不一样

  - 如果字符串的长度小于等于20字节，这个字符串会直接被原样保存；
  - 如果字符串的长度大于20字节，这个字符串会被压缩(LZF压缩算法)之后再保存。

  如果关闭文件压缩功能，那么不管字符串长度，都是原样保存；

- 列表对象

  列表对象(REDIS_RDB_TYPE_LIST)采用`REDIS_ENCODING_LINKEDLIST`编码，其格式如下：

  `|list_length|item1|item2|...|itemN|`

  例：

  `|3|5|"hello"|5|"world"|1|"!"|`

- 集合对象

  集合对象(REDIS_RDB_TYPE_SET)采用`REDIS_ENCODING_HT`编码，其格式如下：

  `|set_size|elem1|elem2|...|elemN|`

  例：

  `|4|5|"apple"|6|"banana"|3|"cat"|3|"dog"|`

- 哈希表对象

  哈希表对象(REDIS_RDB_TYPE_HASH)采用`REDIS_ENCODING_HT`编码，其格式如下：

  `|hash_size|key_value_pair1|key_value_pair2|...|key_value_pairN|`

  - `hash_size` 记录了哈希表的大小，即这个哈希表保存了多少键值对；
  - `key_value_pairXXX` 代表了哈希表中的键值对，键值对的键和值都是字符串对象，所以程序会以处理字符串对象的方式来保存和读入键值对。 

  例：

  `|2|1|"a"|5|"apple"|1|"b"|6|"banana"|`

- 有序集合对象

  有序集合对象(REDIS_RDB_TYPE_ZSET)采用`REDIS_ENCODING_SKIPLIST`编码，格式如下：

  `|sorted_set_size|element1|element2|...|elementN|`

  - `sorted_set_size` 有序集合大小
  - `elementxxx`
    - `member` 成员
    - `score` 分值
  
  例：`|2|2|"pi"|4|"3.14"|1|"e"|3|"2.7"|`
  
  第1格标识集合有2个元素，第2格表示"pi"的长度为2，第3格表示"pi"，第4格表示"3.14"的长度为4，第5格表示"e"的长度为1，第6格表示"e"，第7格表示"2.7"的长度为3，第8格表示"2.7"。
  
- 整数集合对象
  
  整数集合对象(REDIS_RDB_TYPE_SET_INTSET)
  
  

