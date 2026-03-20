English | [中文版](log_zh.md)

# Redis Source Analysis - Slow Log

[TOC]


Redis slow log is used to record command requests whose execution time exceeds a configured threshold.

The server provides the following configuration options related to the slow log:

- `slowlog-log-slower-than`

  Specifies the execution time in nanoseconds above which a command will be recorded in the slow log.

- `slowlog-max-len`

  Specifies the maximum number of slow log entries the server keeps.


## Storage of slow log entries

```c
/** @brief redis server */
struct redisServer {
	...
	list *slowlog;                  /* slow log list */
	long long slowlog_entry_id;     /* next slow log ID */
	long long slowlog_log_slower_than; /* commands taking longer than this (ns) are logged (config: slowlog-log-slower-than) */
	unsigned long slowlog_max_len;     /* maximum number of log entries, FIFO (config: slowlog-max-len) */
	...
};
```

Slow log entry definition:

```c
/* slow log entry */
typedef struct slowlogEntry {
	robj **argv;        /* command arguments */
	int argc;           /* number of command arguments */
	long long id;       /* unique identifier */
	long long duration; /* command execution duration (ns) */
	time_t time;        /* command start time (Unix timestamp) */
} slowlogEntry;
```


## Viewing and clearing the slow log

Command to view slow log:

```sh
SLOWLOG GET
```

```c
/** @brief command: slowlog */
void slowlogCommand(redisClient *c) {
	if (c->argc == 2 && !strcasecmp(c->argv[1]->ptr,"reset")) { /* slowlog reset: reset the slow log */
		slowlogReset();
		addReply(c,shared.ok);
	} else if (c->argc == 2 && !strcasecmp(c->argv[1]->ptr,"len")) { /* slowlog len: get log length */
		addReplyLongLong(c,listLength(server.slowlog));
	} else if ((c->argc == 2 || c->argc == 3) &&
			   !strcasecmp(c->argv[1]->ptr,"get")) /* slowlog get: retrieve entries */
	{
		long count = 10, sent = 0; /* default 10 entries (can be specified by argument) */
		listIter li;
		void *totentries;
		listNode *ln;
		slowlogEntry *se;

		if (c->argc == 3 &&
			getLongFromObjectOrReply(c,c->argv[2],&count,NULL) != REDIS_OK)
			return;

		listRewind(server.slowlog,&li); /* acquire iterator */
		totentries = addDeferredMultiBulkLength(c);
		while(count-- && (ln = listNext(&li))) { /* iterate the list */
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


## Adding new entries

`slowlogPushEntryIfNeeded` behavior:

1. Check whether the command's execution duration exceeds the `slowlog-log-slower-than` configuration. If so, allocate a new slow log entry for the command and push it to the head of the `slowlog` list.
2. Check whether the slow log length exceeds the `slowlog-max-len` configuration. If it does, remove the oldest entries from the `slowlog` list to trim it to the configured maximum.
