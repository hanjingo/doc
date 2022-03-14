# Redis源码分析-慢查询日志

[TOC]

Redis慢查询日志用于记录执行时间超过给定时长的命令请求；

服务器配置以下与慢查询日志相关的选项：

- slowlog-log-slower-than

  指定执行时间超过多少ns的命令请求会被记录到日志上

- slowlog-max-len

  指定服务器最多保存多少条慢查询日志；



## 慢查询记录的保存

```c
/** @brief redis服务端 */
struct redisServer {
    ...
    list *slowlog;                  /* 慢查询日志列表 */
    long long slowlog_entry_id;     /* 下一条慢查询日志ID */
    long long slowlog_log_slower_than; /* 执行时间超过此值的命令会被记录到日志（配置选项slowlog-log-slower-than）*/
    unsigned long slowlog_max_len;     /* 日志的最大条数，日志先进先出（配置选项slowlog-max-len） */
    ...
};
```

慢查询日志定义：

```c
/* 慢查询日志 */
typedef struct slowlogEntry {
    robj **argv;        /* 命令参数 */
    int argc;           /* 命令参数数量 */
    long long id;       /* 唯一标识符 */
    long long duration; /* 命令执行的时长(ns) */
    time_t time;        /* 命令开始执行的时间（Unix时间戳） */
} slowlogEntry;
```



## 慢查询日志的阅览和删除

日志查看命令：

```sh
SLOWLOG GET
```

```c
/** @brief 命令:slowlog 
 *  */
void slowlogCommand(redisClient *c) {
    if (c->argc == 2 && !strcasecmp(c->argv[1]->ptr,"reset")) { /* slowlog reset 重置日志 */
        slowlogReset();
        addReply(c,shared.ok);
    } else if (c->argc == 2 && !strcasecmp(c->argv[1]->ptr,"len")) { /* slowlog len 获得日志长度 */
        addReplyLongLong(c,listLength(server.slowlog));
    } else if ((c->argc == 2 || c->argc == 3) &&
               !strcasecmp(c->argv[1]->ptr,"get")) /* slowlog get 获取日志 */
    {
        long count = 10, sent = 0; /* 默认查询10（值可以通过参数指定） */
        listIter li;
        void *totentries;
        listNode *ln;
        slowlogEntry *se;

        if (c->argc == 3 &&
            getLongFromObjectOrReply(c,c->argv[2],&count,NULL) != REDIS_OK)
            return;

        listRewind(server.slowlog,&li); /* 获取迭代器 */
        totentries = addDeferredMultiBulkLength(c);
        while(count-- && (ln = listNext(&li))) { /* 遍历日志list */
            int j;

            se = ln->value;
            addReplyMultiBulkLen(c,4);
            addReplyLongLong(c,se->id);
            addReplyLongLong(c,se->time);
            addReplyLongLong(c,se->duration);
            addReplyMultiBulkLen(c,se->argc);
            for (j = 0; j < se->argc; j++)
                addReplyBulk(c,se->argv[j]);
            sent++;
        }
        setDeferredMultiBulkLength(c,totentries,sent);
    } else {
        addReplyError(c,
            "Unknown SLOWLOG subcommand or wrong # of args. Try GET, RESET, LEN.");
    }
}
```



## 添加新日志

slowlogPushEntryIfNeeded函数：

1. 检查命令的执行时长是否超过`slowlog-log-slower-than`选项所设置的时间，如果是的话，就为命令创建一个新的日志，并将新日志添加到slowlog链表的表头；
2. 检查慢查询日志的长度是否超过`slowlog-max-len`选项所设置的长度，如果是的话，那么将多出来的日志从slowlog链表中删除掉；