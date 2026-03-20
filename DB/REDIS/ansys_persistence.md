English | [中文版](ansys_persistence_zh.md)

# Redis Source Code Analysis - Persistence

[TOC]


## Persistence strategies

### `save` option

Users can configure multiple `save` conditions; when any condition is met Redis triggers a `BGSAVE`.

Source schema:

```c
struct redisServer {
		struct saveparam *saveparams;   /* configured "save" parameters: <seconds> <changes> */
		int saveparamslen;              /* number of save parameter entries */
}
```

### `dirty` counter and `lastsave`

- `dirty`: number of changes since the last successful persistence
- `lastsave`: time of the last successful persistence

Source:

```c
struct redisServer {
		long long dirty;                /* changes since last successful persistence */
		time_t lastsave;                /* time of last successful persistence */
}
```

### Save-condition check

The `serverCron` runs by default every 100ms to check whether any `save` condition is satisfied.

Source:

```c
TODO
```


## RDB file creation and loading

Two commands can generate an RDB file:

- `SAVE` — create RDB file synchronously (blocking)
- `BGSAVE` — create RDB file in background (forks a child, non-blocking)

Notes:

1. Redis prefers AOF for restoring the dataset; RDB is used only when AOF is disabled.
2. While `BGSAVE` runs, incoming `SAVE` and `BGSAVE` commands are rejected; `BGREWRITEAOF` is delayed until `BGSAVE` completes.
3. While `BGREWRITEAOF` runs, incoming `BGSAVE` commands are rejected.

### Source implementation

#### Saving RDB

Redis saves RDB via `int rdbSave(char *filename)` or `int rdbSaveBackground(char *filename)`.

```c
/** @brief save RDB to disk @param filename RDB path */
int rdbSave(char *filename) {
		char tmpfile[256];
		FILE *fp;
		rio rdb;
		int error;

		snprintf(tmpfile,256,"temp-%d.rdb", (int) getpid());
		fp = fopen(tmpfile,"w"); /* create temporary file temp-<pid>.rdb */
		if (!fp) {
				redisLog(REDIS_WARNING, "Failed opening .rdb for saving: %s",
						strerror(errno));
				return REDIS_ERR;
		}

		rioInitWithFile(&rdb,fp);
		if (rdbSaveRio(&rdb,&error) == REDIS_ERR) { /* write RDB to temp file */
				errno = error;
				goto werr;
		}

		/* flush and sync */
		if (fflush(fp) == EOF) goto werr;
		if (fsync(fileno(fp)) == -1) goto werr;
		if (fclose(fp) == EOF) goto werr;

		/* atomic rename */
		if (rename(tmpfile,filename) == -1) {
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

#### Loading RDB

Redis loads RDB using `int rdbLoad(char *filename)`.

```c
/** @brief load RDB file @param filename path */
int rdbLoad(char *filename) {
		...
}
```

Server startup load flow:

```flow
a=>operation: server start
load=>operation: run loading routine
isAOFEnable=>condition: is AOF enabled?
loadAOF=>operation: load AOF file
loadRDB=>operation: load RDB file

a->load->isAOFEnable
isAOFEnable(yes)->loadAOF
isAOFEnable(no)->loadRDB
```


## RDB file format

An RDB file layout:

| REDIS | db_version | databases | EOF   | check_sum |
| ----- | ---------- | --------- | ----- | --------- |
| 5byte | 4byte      | variable  | 1byte | 8bytes    |

- `REDIS`: "REDIS" magic header (5 bytes)
- `db_version`: version string (4 bytes)
- `databases`: zero or more databases and their key-value pairs (variable length)
- `EOF`: end-of-file marker
- `check_sum`: 8-byte checksum

`databases` structure (repeated per DB):

| SELECTDB | db_number | key_value_pairs |
| -------- | --------- | --------------- |
| 1byte    | 1/2/5byte | variable        |

- `SELECTDB`: marker indicating a DB section follows
- `db_number`: DB id (1,2 or 5 bytes depending on size)
- `key_value_pairs`: one or more key/value entries

Key/value entry without expiration:

| TYPE  | key  | value |
| ----- | ---- | ----- |
| 1byte | var  | var   |

- `TYPE`: REDIS_RDB_TYPE_XXX
- `key`: string
- `value`: encoded per type (see below)

Key/value with expiration (ms):

| EXPIRETIME_MS | ms    | TYPE  | key  | value |
| ------------- | ----- | ----- | ---- | ----- |
| 1byte         | 8byte | 1byte | var  | var   |

- `EXPIRETIME_MS`: marker indicating next field is an expiration in ms
- `ms`: signed integer expiration (ms)


### Value encodings

RDB `value` may be any Redis type:

- String (REDIS_RDB_TYPE_STRING)

	Two encodings: `REDIS_ENCODING_INT` or `REDIS_ENCODING_RAW`.

	When file compression is enabled:
	- strings <= 20 bytes are saved as-is;
	- strings > 20 bytes are compressed with LZF before saving.

	When compression is disabled, strings are always stored raw.

- List (REDIS_RDB_TYPE_LIST)

	When encoded as `REDIS_ENCODING_LINKEDLIST` the format is:

	`|list_length|item1|item2|...|itemN|`

- Set (REDIS_RDB_TYPE_SET)

	When encoded as `REDIS_ENCODING_HT` the format is:

	`|set_size|elem1|elem2|...|elemN|`

- Hash (REDIS_RDB_TYPE_HASH)

	When encoded as `REDIS_ENCODING_HT` the format is:

	`|hash_size|key_value_pair1|...|key_value_pairN|`

- Sorted set (REDIS_RDB_TYPE_ZSET)

	When encoded as `REDIS_ENCODING_SKIPLIST` the format is:

	`|sorted_set_size|element1|element2|...|elementN|`

- Intset (REDIS_RDB_TYPE_SET_INTSET)

	The intset is converted to a string object and stored as a string.

- Ziplist encodings (list/hash/zset ziplist types)

	Ziplist objects are converted to a string object; when reading, the string is parsed back and converted to the appropriate ziplist type indicated by `TYPE`.


### RDB analysis

An empty RDB file contains the four parts: header, version, EOF and checksum as described above.

When a DB is saved it includes the SELECTDB marker, DB number and its key/value entries; keys with expiration include the expire marker and ms value.


## AOF persistence

AOF persistence records write commands executed by the server to reconstruct the dataset:

```mermaid
graph LR
Client--write command-->Server--append executed command-->AOF file
```

### AOF implementation steps

1. Append command to AOF buffer
2. Write buffer to AOF file
3. Sync file to disk

#### `appendfsync` modes

| appendfsync | behavior of `flushAppendOnlyFile` |
| ----------- | --------------------------------- |
| always      | write and fsync all `aof_buf` data each loop (safest, slowest) |
| everysec    | write `aof_buf` each loop; if last fsync > 1s spawn a thread to fsync (good balance) |
| no          | write `aof_buf` to file but do not fsync (rely on OS), fastest but least safe |

#### AOF durability vs performance

- `always`: slowest but safest — at worst only one event loop of commands is lost on crash.
- `everysec`: writes every loop and fsyncs at most once per second in a background thread; typically loses at most one second of commands on crash.
- `no`: fastest writes but relies on OS flush; accumulated data may cause long sync times when OS flush occurs.


### AOF loading and dataset restoration

RDB loads by replaying commands from AOF as follows:

```flow
load=>operation: server startup load routine
create_cli=>operation: create pseudo-client
read_wcmd=>operation: parse and read a write command from AOF
exec_wcmd=>operation: execute the write command using pseudo-client
exec_fin=>condition: all AOF commands processed?
load_fin=>operation: finished loading

load->create_cli->read_wcmd->exec_fin
exec_fin(yes)->load_fin
exec_fin(no)->read_wcmd
```

1. Create a fake client without a network socket.
2. Parse and read one write command from the AOF.
3. Use the fake client to execute the command.
4. Repeat until all commands are processed.


### AOF rewrite

Redis can rewrite the AOF in the background to produce a compact equivalent AOF without redundant commands.

#### Background AOF rewrite

The rewrite runs in a child process so the parent can continue serving clients without locks.

To keep the child consistent with the parent's ongoing writes, Redis uses an AOF rewrite buffer that records commands executed after the fork. The parent appends each write to both the normal AOF buffer and the rewrite buffer.

```mermaid
graph LR
Client --send command--> serv
subgraph Server
serv(command processor) --append command--> AOF buffer
serv(command processor) --append command--> AOF rewrite buffer
end
```

When rewrite completes:

1. Append the rewrite buffer contents to the new AOF so it reflects the current DB state.
2. Atomically rename the new AOF over the old one.


## References

[1] Huang Jianhong. Redis Design and Implementation
