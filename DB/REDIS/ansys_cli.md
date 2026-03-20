English | [中文版](ansys_cli_zh.md)

# Redis Source Code Analysis - Client

[TOC]



## Client Properties

```c
TODO
```

- `fd` The client's socket descriptor
	- `>-1` Normal client, commands come from the network
	- `-1` Fake client, commands come from AOF file or LUA script, not from the network
  
- `name` Client name

- `flags` Client role flags, can be a single flag or a bitwise OR of multiple flags;

	| Role                        | Description                                                  |
	| --------------------------- | ------------------------------------------------------------ |
	| `REDIS_SLAVE`               | Slave server                                                 |
	| `REDIS_MASTER`              | Client represents a master server                            |
	| `REDIS_MONITOR`             | Monitor                                                      |
	| `REDIS_MULTI`               | Executing a transaction                                      |
	| `REDIS_BLOCKED`             | Client is waiting for a blocking operation                   |
	| `REDIS_DIRTY_CAS`           | Key watched by WATCH command has been modified               |
	| `REDIS_CLOSE_AFTER_REPLY`   | Client output buffer size exceeds server's allowed range      |
	| `REDIS_UNBLOCKED`           | No longer blocked                                            |
	| `REDIS_LUA_CLIENT`          | Fake client for handling Redis commands in Lua scripts        |
	| `REDIS_ASKING`              | Sent ASKING command to a cluster node (in cluster mode)       |
	| `REDIS_CLOSE_ASAP`          | Output buffer exceeded limit, client will be closed on next serverCron |
	| `REDIS_UNIX_SOCKET`         | Client connected via Unix domain socket                      |
	| `REDIS_DIRTY_EXEC`          | Execution failed during queuing                              |
	| `REDIS_MASTER_FORCE_REPLY`  | Force master reply queue                                     |
	| `REDIS_FORCE_AOF`           | Force current command to be written to AOF file              |
	| `REDIS_FORCE_REPL`          | Force current command to be replicated to all slaves         |
	| `REDIS_PRE_PSYNC`           | Slave server with Redis version lower than 2.8               |
	| `REDIS_READONLY`            | Cluster client in read-only state                            |
	| `REDIS_PUBSUB`              | Client in publish/subscribe mode                             |

- `argv` Command to execute (argv[0]) and its arguments

- `argc` Length of argv

- `cmd` Command currently being executed

- `lastcmd` Last command to be executed

- `buf` Small reply buffer (16k)

- `bufpos` Number of bytes currently used in buf

- `reply` Variable size buffer

- `authenticated` Authentication flag
	- 0 Not authenticated
	- 1 Authenticated
  
- `ctime` Creation time

- `lastinteraction` Time of last communication with the server

- `obuf_soft_limit_reached_time` Time when output buffer size exceeded soft limit



## Client Creation and Closing

Reasons for client closure:

- Client process exits or is killed
- Client sends a command request with an invalid protocol format
- Client is the target of the CLIENT KILL command
- Client idle time exceeds the value set by the `timeout` option (exceptions: 1. Blocked by BLPOP command; 2. Executing SUBSCRIBE, PSUBSCRIBE, etc.)
- Size of the command request sent by the client exceeds the input buffer limit (default 1GB)
- Size of the command reply sent to the client exceeds the output buffer limit

The server uses two modes to limit the size of the client output buffer:

- Hard limit: If the output buffer size exceeds the hard limit, the server immediately closes the client.
- Soft limit: If the output buffer size exceeds the soft limit but not the hard limit, the server records the start time when the client reaches the soft limit using the `obuf_soft_limit_reached_time` property; the server continues to monitor the client, and if the output buffer size remains above the soft limit for longer than the configured duration, the server closes the client.

The `client-output-buffer-limit` option can be used to set different soft and hard limits for normal clients, slave clients, and clients using publish/subscribe. The format is:

`client-output-buffer-limit <class> <hard limit> <soft limit> <soft seconds>`

- `class` Category
	- `norm` Normal client
	- `slave` Slave client
	- `pubsub` Publish/subscribe client
- `hard limit` Hard limit
- `soft limit` Soft limit
- `soft seconds` Soft limit duration (s)



## References

[1] Huang Jianhong. Redis Design and Implementation

[2] [Redis Source Code Analysis (3) - Request Processing](https://blog.csdn.net/chosen0ne/article/details/43053915?utm_source=blogkpcl14)
