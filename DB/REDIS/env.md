English | [中文版](env_zh.md)

# Redis Configuration

[TOC]


## Installation

### Ubuntu

- Install via package manager:

```sh
sudo apt-get install redis-server
# verify
service redis-server start
ps -aux | grep redis
```


## Configuration

Redis configuration file location varies by system. Common path on Ubuntu:

```sh
/etc/redis/redis.conf
```


### Configuration options

| Option                                  | Description                                                                 |
| --------------------------------------- | --------------------------------------------------------------------------- |
| `daemonize <yes/no>`                    | Run as a background daemon                                                   |
| `down-after-milliseconds <ms>`          | Time a Sentinel waits before marking an instance subjectively down (ms)     |
| `pidfile <file_path>`                   | Path to pidfile                                                              |
| `port <num>`                            | TCP port                                                                     |
| `timeout <seconds>`                     | Client idle timeout (seconds)                                                |
| `loglevel <lvl>`                        | Log verbosity: `debug`, `verbose`, `notice`, `warning`                      |
| `logfile <path>`                        | Log file path                                                                |
| `databases <db_num>`                    | Number of databases (default 16)                                             |
| `save <seconds> <changes>`              | Snapshotting conditions: save after `<changes>` writes within `<seconds>`   |
| `stop-write-on-bgsave-error <yes/no>`   | Stop accepting writes if last RDB save failed                                |
| `rdbcompression <yes/no>`               | Compress RDB files (LZF)                                                     |
| `rdbchecksum <yes/no>`                  | Enable CRC64 checksum for RDB (costs CPU)                                   |
| `dbfilename <file>`                     | RDB filename                                                                  |
| `dir <path>`                            | Working directory for DB files                                                |
| `requirepass <passwd>`                  | Password required by replicas when connecting                                |
| `appendonly <yes/no>`                   | Enable AOF append-only file                                                   |
| `appendfsync <no|always|everysec>`      | AOF fsync policy: `no` (OS manages), `always` (fsync every write), `everysec` (fsync once per second) |
| `notify-keyspace-events <flags>`        | Events notifications mask (K=keyspace, E=keyevent, g=$all, $=string, l=list, s=set, h=hash, z=zset, X=expired, e=evicted, A=all) |
| `repl-backlog-size`                     | Replication backlog size (supports units like b,k,m,g or kb,mb,gb)           |
| `repl-backlog-ttl`                      | Replication backlog TTL in seconds when no replicas are connected           |
| `maxclients <num>`                      | Maximum number of client connections                                         |
| `maxmemory <bytes>`                     | Maximum memory usage (0 = no limit)                                          |
| `maxmemory-policy`                      | Eviction policy: `noeviction`, `allkeys-lru`, `volatile-lru`, `allkeys-random`, `volatile-random`, `volatile-ttl`, `volatile-lfu`, `allkeys-lfu` |


Example configuration snippets:

```sh
# run as daemon
daemonize yes
# pidfile
pidfile /usr/local/redis-4.0.9/redis.pid
# port
port 6379
# client timeout (seconds)
timeout 300
# log level
loglevel debug
# log file
logfile /usr/local/redis-4.0.9/log-redis.log
# number of databases (default 16)
databases 16

## snapshotting rules: save <seconds> <changes>
save 900 1
save 300 10
save 60 10000

# compress RDB files
rdbcompression yes
# RDB filename and directory
dbfilename dump.rdb
dir /usr/local/redis-4.0.9/db/

# AOF
appendonly no
# appendfsync options: no, always, everysec
appendfsync everysec
```


### Commands

#### Get configuration value

```sh
CONFIG GET <pattern>
```

#### Set configuration value at runtime

```sh
CONFIG SET <option> <value>
```
