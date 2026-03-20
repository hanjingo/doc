English | [中文版](cmd_zh.md)

# Redis Commands

[TOC]


## Key

| Command    | Description                                                                 | Options                                                                 | Complexity | Example                                                                 |
| ---------- | --------------------------------------------------------------------------- | ----------------------------------------------------------------------- | ---------- | ----------------------------------------------------------------------- |
| DEL        | Remove the specified one or more keys (non-existing keys are ignored); returns number of removed keys |                                                                         |            | `DEL name1 name2` removes keys `name1` and `name2`                      |
| DUMP       | Serialize the value stored at key and return it                             |                                                                         |            | `DUMP name`                                                              |
| EXISTS     | Check if a key exists (returns 1 if it exists)                              |                                                                         |            | `EXISTS name`                                                            |
| EXPIRE     | Set a key's time to live (precision: since 2.6, millisecond precision available) |                                                                         |            | `EXPIRE name 1` set `name` to expire in 1s                              |
| EXPIREAT   | Set the expiration for a key as a UNIX timestamp                            |                                                                         |            | `EXPIREAT name 1641213599`                                              |
| KEYS       | Find all keys matching pattern (use with caution — heavy; prefer incremental SCAN) |                                                                         |            | `KEYS *`, `KEYS h?llo`, `KEYS h*llo`, `KEYS h[ae]llo`                    |
| MIGRATE    | Atomically transfer a key to a different Redis instance                      | `COPY` keep source key; `REPLACE` replace target key if present         |            | `MIGRATE 127.0.0.1 7777 greeting 0 1000 COPY`                            |
| MOVE       | Move a key to a different database (fails if target DB already has the key)  |                                                                         |            | `MOVE name 1` move `name` to DB 1                                        |
| OBJECT     | Return internal metadata about a key                                         | `REFCOUNT`, `ENCODING`, `IDLETIME`                                      |            | `OBJECT REFCOUNT game`, `OBJECT IDLETIME game`, `OBJECT ENCODING game`  |
| PERSIST    | Remove the expiration from a key (make it persistent)                       |                                                                         |            | `PERSIST k`                                                              |
| PEXPIRE    | Set a key's TTL in milliseconds                                              |                                                                         |            | `PEXPIRE k 1500`                                                         |
| PEXPIREAT  | Set key expiration as UNIX timestamp in milliseconds                        |                                                                         |            | `PEXPIREAT k 1555555555005`                                              |
| PTTL       | Return remaining TTL in milliseconds                                        |                                                                         |            | `PTTL k`                                                                 |
| RANDOMKEY  | Return a random key from the current DB                                      |                                                                         |            | `RANDOMKEY`                                                               |
| RENAME     | Rename a key (overwrites the new key if it exists)                           |                                                                         |            | `RENAME a b`                                                             |
| RENAMENX   | Rename a key only if the new key does not exist                              |                                                                         |            | `RENAMENX a b`                                                            |
| RESTORE    | Deserialize and restore a key from serialized value                          |                                                                         |            | `RESTORE k 0 "\x00..."` or with TTL `RESTORE k 1500 "\x00..."`     |
| SORT       | Sort elements in a list/set or sorted set and return the result              | `ASC`, `DESC`, `ALPHA`, `LIMIT offset count`, `BY`, `GET`, `STORE`      |            | many advanced examples: see `SORT` docs                                  |
| TTL        | Return remaining TTL in seconds                                             |                                                                         |            | `TTL k`                                                                  |
| TYPE       | Return the type of the value stored at key                                   |                                                                         |            | `TYPE k`                                                                 |
| SCAN       | Incrementally iterate all keys in the DB (returns cursor; use instead of KEYS in production) | `COUNT` (hint), `MATCH` pattern                                      |            | `SCAN 0`, `SCAN 0 MATCH *11* COUNT 100`                                   |


## String

| Command      | Description                                                                 | Params / Notes                                                                                                           | Example                                                                       |
|--------------|-----------------------------------------------------------------------------|--------------------------------------------------------------------------------------------------------------------------|-------------------------------------------------------------------------------|
| APPEND       | Append a value to a key (create the key if it does not exist)              |                                                                                                                          | `APPEND k ext`                                                                |
| BITCOUNT     | Count set bits in a string value                                           | `start`, `end`                                                                                                           | `BITCOUNT b` — e.g. track user daily activity with `SETBIT` + `BITCOUNT`     |
| BITOP        | Perform bitwise operations between strings and store result                | `AND`, `OR`, `XOR`, `NOT`                                                                                                 | `BITOP dst k1 k2`                                                             |
| DECR         | Decrement numeric value by 1 (initialize to 0 if missing)                  | errors if value is not numeric                                                                                            | `DECR k`                                                                      |
| DECRBY       | Decrement by given amount                                                   |                                                                                                                          | `DECRBY k 100`                                                                |
| GET          | Get the value of a key                                                      |                                                                                                                          | `GET k`                                                                       |
| GETBIT       | Return the bit value at offset                                              |                                                                                                                          | `GETBIT k 10086`                                                              |
| GETRANGE     | Get substring of the string value                                           | `start`, `end`                                                                                                           | `GETRANGE k 0 -1`, `GETRANGE k 1 4`                                           |
| GETSET       | Set the string value and return the old value (atomic)                      | useful for atomic resets                                                                                                  | `GETSET k 0`                                                                  |
| INCR         | Increment numeric value by 1 (init to 0 if missing)                        | common for rate limiting combined with `EXPIRE`                                                                           | example rate-limiter pattern in original doc                                 |
| INCRBY       | Increment by integer                                                        | 64-bit signed range                                                                                                       | `INCRBY k 20`                                                                 |
| INCRBYFLOAT  | Increment by floating point (up to 17 digits precision)                     |                                                                                                                          | `INCRBYFLOAT k 10.5`                                                          |
| MGET         | Get multiple keys                                                            |                                                                                                                          | `MGET k1 k2`                                                                  |
| MSET         | Set multiple keys (overwrites existing keys)                                |                                                                                                                          | `MSET k1 1 k2 2`                                                              |
| MSETNX       | Set multiple keys only if none of the keys exist                             |                                                                                                                          | `MSETNX k1 1 k2 2`                                                            |
| PSETEX       | Set value and TTL in milliseconds                                            |                                                                                                                          | `PSETEX k 1000 "abc"`                                                       |
| SET          | Set key to hold string value (options: `EX` seconds, `PX` ms, `NX`, `XX`)  | `NX` set only if not exists, `XX` set only if exists                                                                     | `SET k "abc" EX 5`, `SET k "abc" NX`                                      |
| SETBIT       | Set or clear bit at offset (string grows; offset in [0,2^32))               | large offsets can block server                                                                                           | `SETBIT b 10086 1`                                                            |
| SETEX        | Set value and TTL in seconds                                                 |                                                                                                                          | `SETEX k 5 "abc"`                                                           |
| SETNX        | Set if not exists                                                             |                                                                                                                          | `SETNX k "abc"`                                                             |
| SETRANGE     | Overwrite part of a string at specified offset                               | fills with `\x00` if offset beyond current length                                                                       | `SETRANGE k 6 "ab"`                                                         |
| STRLEN       | Return length of the string value                                            |                                                                                                                          | `STRLEN k`                                                                    |


## Hash

| Command    | Description                                                                 | Example                                                                    |
|------------|-----------------------------------------------------------------------------|----------------------------------------------------------------------------|
| HDEL       | Delete one or more hash fields (ignored if field does not exist)           | `HDEL h a b`                                                               |
| HEXISTS    | Determine if a hash field exists                                            | `HEXISTS h a`                                                              |
| HGET       | Get the value of a hash field                                               | `HGET h a`                                                                 |
| HGETALL    | Get all fields and values in a hash as a list                               | `HGETALL h`                                                                |
| HINCRBY    | Increment the integer value of a hash field by given amount                | `HINCRBY h a 200`                                                           |
| HINCRBYFLOAT| Increment a hash field by a floating point value                            | field must be string parseable as double                                 |
| HKEYS      | Get all field names in a hash                                                | `HKEYS h`                                                                  |
| HLEN       | Get number of fields in a hash                                              | `HLEN h`                                                                   |
| HMGET      | Get multiple hash fields                                                    | `HMGET h key1 key2`                                                         |
| HMSET      | Set multiple hash fields (deprecated in newer Redis in favor of HSET)       | `HMSET h k1 v1 k2 v2`                                                      |
| HSET       | Set the string value of a hash field                                        | `HSET h k1 v1`                                                             |
| HSETNX     | Set field only if it does not exist                                         | `HSETNX h k1 v1`                                                           |
| HVALS      | Get all values in a hash                                                     | `HVALS h`                                                                  |
| HSCAN      | Incrementally iterate hash fields (see `SCAN`)                              |                                                                            |


## List

| Command    | Description                                                                 | Params / Notes                                                                 | Example                                                                    |
|------------|-----------------------------------------------------------------------------|--------------------------------------------------------------------------------|----------------------------------------------------------------------------|
| BLPOP      | Blocking pop from left across multiple lists (blocks until element available or timeout) | multiple clients can block on same key; pipeline behavior differs; see examples | `BLPOP li1 li2 5`                                                           |
| BRPOP      | Blocking pop from right                                                      |                                                                                | `BRPOP li 30`                                                              |
| BRPOPLPUSH | Blocking pop from right and push to another list atomically                 |                                                                                | `BRPOPLPUSH src dst 5`                                                     |
| LINDEX     | Get element by index                                                          |                                                                                | `LINDEX li 0`, `LINDEX li -1`                                              |
| LINSERT    | Insert element before or after pivot element                                 | `BEFORE` or `AFTER`                                                            | `LINSERT h BEFORE "world" "he"`                                        |
| LLEN       | Get length of list                                                           |                                                                                | `LLEN h`                                                                   |
| LPOP       | Remove and return first element                                              |                                                                                | `LPOP li`                                                                  |
| LPUSH      | Prepend one or more values to a list (create if missing)                     | values inserted from left-to-right                                          | `LPUSH li a b c`                                                            |
| LPUSHX     | Prepend only if list exists                                                   |                                                                                | `LPUSHX li a b c`                                                           |
| LRANGE     | Get a range of elements from a list                                           |                                                                                | `LRANGE li 0 1`                                                             |
| LREM       | Remove elements equal to value (count >0: from head, <0: from tail, =0: all) |                                                                                | `LREM li 2 abc`                                                             |
| LSET       | Set list element at index                                                     | error if index out of range                                                     | `LSET li 3 "abc"`                                                         |
| LTRIM      | Trim a list to the specified range                                            | if start > end or out of range result is empty                                | `LTRIM li 1 -1`                                                             |
| RPOP       | Remove and return last element                                                |                                                                                | `RPOP li`                                                                  |
| RPOPLPUSH  | Pop last element and push to another list atomically                         |                                                                                | `RPOPLPUSH src dst`                                                         |
| RPUSH      | Append one or more values to a list (create if missing)                       |                                                                                | `RPUSH li a b c`                                                            |
| RPUSHX     | Append only if list exists                                                     |                                                                                | `RPUSHX li "abc"`                                                          |


## Set

| Command    | Description                                                                 | Example                                                                    |
|------------|-----------------------------------------------------------------------------|----------------------------------------------------------------------------|
| SADD       | Add one or more members to a set (create if missing)                       | `SADD s "abc" "def"`                                                     |
| ZCARD      | Return set cardinality                                                       | `ZCARD s`                                                                   |
| SDIFF      | Return the difference between sets                                           | `SDIFF s1 s2`                                                               |
| SDIFFSTORE | Store the difference in destination set                                      | `SDIFFSTORE s1 s2 s3`                                                       |
| SINTER     | Return the intersection of sets                                              | `SINTER s1 s2`                                                              |
| SINTERSTORE| Store the intersection in destination set                                    | `SINTERSTORE s1 s2 s3`                                                      |
| SISMEMBER  | Determine if a given value is a member of a set                              | `SISMEMBER s1 "abc"`                                                      |
| SMEMBERS   | Return all members of the set (heavy — prefer `SSCAN`)                        | `SMEMBERS s1`                                                               |
| SMOVE      | Move a member from one set to another (atomic)                               | `SMOVE src dst "abc"`                                                     |
| SPOP       | Remove and return a random member                                             | `SPOP s1`                                                                   |
| SRANDMEMBER| Return one or more random members (positive n => unique elements; negative n => allow duplicates) | `SRANDMEMBER s1 3`                                                           |
| SREM       | Remove one or more members                                                    | `SREM s1 "a" "b" "c"`                                                 |
| SUNION     | Return the union of sets                                                      | `SUNION s1 s2`                                                              |
| SUNIONSTORE| Store the union in destination set                                            | `SUNIONSTORE s1 s2 s3`                                                      |
| SSCAN      | Incrementally iterate set members (see `SCAN`)                                |                                                                            |


## Zset (Sorted Set)

| Command    | Description                                                                 | Params / Notes                                                                 | Example                                                                    |
|------------|-----------------------------------------------------------------------------|--------------------------------------------------------------------------------|----------------------------------------------------------------------------|
| ZADD       | Add one or more members with scores to a sorted set (update if exists)     |                                                                                | `ZADD z1 5 a 6 b`                                                           |
| ZCARD      | Return number of elements in sorted set                                      |                                                                                | `ZCARD z1`                                                                  |
| ZCOUNT     | Count elements with scores within range                                      |                                                                                | `ZCOUNT z1 2 5`                                                             |
| ZINCRBY    | Increment member's score by given amount                                     |                                                                                | `ZINCRBY z1 10 a`                                                           |
| ZRANGE     | Return range by rank (ascending)                                              | `WITHSCORES`                                                                 | `ZRANGE z1 0 -1 WITHSCORES`                                                 |
| ZRANGEBYSCORE | Return elements with scores within range                                  | `LIMIT`, `WITHSCORES`, `(` for exclusive range                                 | `ZRANGEBYSCORE z1 1 5`                                                       |
| ZRANK      | Return the rank of a member (ascending)                                      |                                                                                | `ZRANK z1 a`                                                                |
| ZREM       | Remove one or more members                                                     | `ZREM z1 a b`                                                                |
| ZREMRANGEBYRANK | Remove elements by rank range                                              |                                                                                | `ZREMRANGEBYRANK z1 0 1`                                                     |
| ZREMRANGEBYSCORE | Remove elements by score range                                            |                                                                                | `ZREMRANGEBYSCORE z1 3 5`                                                    |
| ZREVRANGE  | Return range by rank (descending)                                            |                                                                                | `ZREVRANGE z1 0 -1 WITHSCORES`                                              |
| ZREVRANGEBYSCORE | Return elements by score in descending order                             |                                                                                | `ZREVRANGEBYSCORE z1 +inf -inf`                                             |
| ZREVRANK   | Return rank of a member (descending)                                         |                                                                                | `ZREVRANK z1 a`                                                              |
| ZSCORE     | Get the score associated with the member                                     |                                                                                | `ZSCORE z1 a`                                                                |
| ZUNIONSTORE| Compute union of sorted sets and store result                                 | `WEIGHTS`, `AGGREGATE (SUM|MIN|MAX)`                                          | `ZUNIONSTORE z1 2 z2 z3 WEIGHTS 1 3`                                        |
| ZINTERSTORE| Compute intersection and store result                                         |                                                                                | `ZINTERSTORE z1 2 z2 z3`                                                     |
| ZSCAN      | Incrementally iterate sorted set entries                                      |                                                                                |                                                                             |


## Pub/Sub

| Command      | Description                                 | Example                              |
|--------------|---------------------------------------------|--------------------------------------|
| PSUBSCRIBE   | Subscribe to channels by pattern            | `PSUBSCRIBE AB*`                     |
| PUBLISH      | Post a message to a channel                  | `PUBLISH ch "hello"`               |
| PUBSUB       | Inspect pub/sub state                        | `PUBSUB CHANNELS *.abc`, `PUBSUB NUMSUB ch1 ch2`, `PUBSUB NUMPAT` |
| PUNSUBSCRIBE | Unsubscribe from pattern subscriptions       | `PUNSUBSCRIBE AB*`                   |
| SUBSCRIBE    | Subscribe to channels                        | `SUBSCRIBE AB`                       |
| UNSUBSCRIBE  | Unsubscribe from channels                    | `UNSUBSCRIBE AB`                     |


## Transaction

| Command  | Description                                                                 | Example                                    |
|----------|-----------------------------------------------------------------------------|--------------------------------------------|
| DISCARD  | Discard a transaction — abandon all queued commands                         | `DISCARD`                                  |
| EXEC     | Execute all queued commands (fails if WATCHed keys were modified)           | `MULTI` / `SET a "xx"` / `EXEC`          |
| MULTI    | Start a transaction block                                                    |                                            |
| UNWATCH  | Unwatch all keys                                                              |                                            |
| WATCH    | Watch one or more keys for conditional execution                             | `WATCH k1 k2`                              |


## HyperLogLog

| Command  | Description                         | Example                |
|----------|-------------------------------------|------------------------|
| PFADD    | Add elements to HyperLogLog         | `PFADD k1 "k1"`      |
| PFCOUNT  | Return approximated cardinality     | `PFCOUNT k1`           |
| PFMERGE  | Merge multiple HyperLogLogs         |                        |


## Script

| Command       | Description                                                  | Example                                                                 |
|---------------|--------------------------------------------------------------|-------------------------------------------------------------------------|
| EVAL          | Evaluate Lua script with provided keys and args              | `EVAL "return {KEYS[1],KEYS[2],ARGV[1]}" 2 key1 key2 first`           |
| EVALSHA       | Evaluate script by SHA1                                      | `EVALSHA <sha1> 0`                                                      |
| SCRIPT EXISTS | Check whether script(s) exist by SHA1                         | `SCRIPT EXISTS <sha1>`                                                  |
| SCRIPT FLUSH  | Remove all scripts from script cache                         | `SCRIPT FLUSH`                                                           |
| SCRIPT KILL   | Kill the script currently running                             | `SCRIPT KILL`                                                            |
| SCRIPT LOAD   | Load a script into the script cache (does not execute it)    | `SCRIPT LOAD "return 'hello'"`                                         |


## Server

| Command           | Description                                                           | Example                                                  |
|-------------------|-----------------------------------------------------------------------|----------------------------------------------------------|
| BGREWRITEAOF      | Manually trigger AOF rewrite                                           | `BGREWRITEAOF`                                           |
| BGSAVE            | Asynchronously save the dataset to disk                                 | `BGSAVE`                                                 |
| CLIENT GETNAME    | Get the current connection's name                                       | `CLIENT GETNAME`                                         |
| CLIENT KILL       | Kill connection by address                                               | `CLIENT KILL 127.0.0.1:6379`                             |
| CLIENT LIST       | Return information and statistics about client connections              | `CLIENT LIST`                                            |
| CLIENT SETNAME    | Set the current connection's name                                      | `CLIENT SETNAME hello`                                   |
| CONFIG GET        | Get runtime configuration parameters                                   | `CONFIG GET s*`, `CONFIG GET slowlog-max-len`            |
| CONFIG RESETSTAT  | Reset various statistics (keyspace hits/misses, commands processed, etc.) | `CONFIG RESETSTAT`                                      |
| CONFIG REWRITE    | Rewrite redis.conf atomically                                           | `CONFIG SET appendonly yes` then `CONFIG REWRITE`        |
| CONFIG SET        | Set runtime configuration parameter                                     | `CONFIG SET appendonly yes`                              |
| DBSIZE            | Return number of keys in the current DB                                 | `DBSIZE`                                                 |
| DEBUG OBJECT      | (debug) Return internal representation info for an object              | `DEBUG OBJECT obj`                                       |

[TOC]


## Key

| Command   | Description                                                                 | Options                                                                 | Time Complexity | Example                                                                 |
| --------- | --------------------------------------------------------------------------- | ----------------------------------------------------------------------- | --------------- | ----------------------------------------------------------------------- |
| DEL       | Delete one or more given keys (non-existing keys are ignored); returns number of deleted keys |                                                                         |                 | `DEL name1 name2` delete keys name1 and name2                           |
| DUMP      | Serialize the value stored at key and return the serialized value           |                                                                         |                 | `DUMP name` serialize value at key name                                  |
| EXISTS    | Check if a key exists (returns 1 if it does)                               |                                                                         |                 | `EXISTS name`                                                            |
| EXPIRE    | Set a timeout on a key (precision: since Redis 2.6 ms precision)            |                                                                         |                 | `EXPIRE name 1` set key name to expire in 1s                             |
| EXPIREAT  | Set expiration as Unix timestamp                                            |                                                                         |                 | `EXPIREAT name 1641213599`                                               |
| KEYS      | Find all keys matching a pattern (use with caution — may be slow; prefer incremental iteration commands) |                                                                         |                 | `KEYS *`, `KEYS h?llo`, `KEYS h*llo`, `KEYS h[ae]llo`                    |
| MIGRATE   | Atomically migrate a key from this instance to another instance's DB       | `COPY` (do not remove from source)<br>`REPLACE` (replace existing target) |                 | `MIGRATE 127.0.0.1 7777 greeting 0 1000 COPY`                             |
| MOVE      | Move a key to another database on the same instance (fails if target db has key) |                                                                         |                 | `MOVE name 1`                                                             |
| OBJECT    | Return metadata about a key                                                  | `REFCOUNT`, `ENCODING`, `IDLETIME`                                      |                 | `OBJECT REFCOUNT game`, `OBJECT IDLETIME game`, `OBJECT ENCODING game`   |
| PERSIST   | Remove the existing timeout on a key (make it persistent)                  |                                                                         |                 | `PERSIST k`                                                               |
| PEXPIRE   | Set key expiration in milliseconds                                         |                                                                         |                 | `PEXPIRE k 1500`                                                          |
| PEXPIREAT | Set expiration as Unix timestamp in milliseconds                           |                                                                         |                 | `PEXPIREAT k 1555555555005`                                               |
| PTTL      | Return remaining TTL of a key in milliseconds                               |                                                                         |                 | `PTTL k`                                                                  |
| RANDOMKEY | Return a random key from the currently selected database                    |                                                                         |                 | `RANDOMKEY`                                                               |
| RENAME    | Rename a key (overwrites the new key if it exists)                         |                                                                         |                 | `RENAME a b`                                                              |
| RENAMENX  | Rename a key only if the new key does not exist                             |                                                                         |                 | `RENAMENX a b`                                                             |
| RESTORE   | Deserialize a value and create the key                                      |                                                                         |                 | `RESTORE k 0 "..."` or `RESTORE k 1500 "..."`                         |
| SORT      | Sort elements in a list, set or sorted set and return the sorted result     | `ASC` / `DESC`, `ALPHA`, `LIMIT [offset] [count]`, `BY`, `GET`, `STORE`  |                 | many options — see examples in source file                                |
| TTL       | Return remaining TTL of a key in seconds                                    |                                                                         |                 | `TTL k`                                                                   |
| TYPE      | Return the type of the value stored at key                                  |                                                                         |                 | `TYPE k`                                                                  |
| SCAN      | Incrementally iterate all keys in the database (returns a cursor; 0 means finished) — preferred over `KEYS` in production | `COUNT` (hint), `MATCH` (pattern)                                       |                 | `SCAN 0`, `SCAN 0 MATCH *11* COUNT 100`                                   |


## String

| Command       | Description                                                                 | Params / Notes                                                                                                                                                                                                                  | Time Complexity | Example                                                                 |
| ------------- | --------------------------------------------------------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | --------------- | ----------------------------------------------------------------------- |
| APPEND        | Append value to the string at key (create key if not exists)                |                                                                                                                                                                                                                                 |                 | `APPEND k ext`                                                           |
| BITCOUNT      | Count set bits (1s) in a string                                             | `start`, `end` offsets                                                                                                                                                                                                          |                 | `BITCOUNT b`                                                             |
| BITOP         | Perform bitwise operations between strings and store result                  | `AND`, `OR`, `XOR`, `NOT`                                                                                                                                                                                                       |                 | `BITOP dst k1 k2`                                                         |
| DECR          | Decrement numeric value by 1 (create key as 0 if missing)                   | Error if value is not numeric                                                                                                                                                                                                   |                 | `DECR k`                                                                  |
| DECRBY        | Decrement numeric value by given amount                                     |                                                                                                                                                                                                                                 |                 | `DECRBY k 100`                                                            |
| GET           | Get the value of a key                                                       |                                                                                                                                                                                                                                 |                 | `GET k`                                                                   |
| GETBIT        | Return bit value at offset in string                                         |                                                                                                                                                                                                                                 |                 | `GETBIT k 10086`                                                          |
| GETRANGE      | Get substring of the string value                                           | `start`, `end` indexes                                                                                                                                                                                                          |                 | `GETRANGE k 0 -1`, `GETRANGE k 1 4`                                       |
| GETSET        | Atomically set key to value and return old value                            | Useful for atomic swaps / resets                                                                                                                                                                                                |                 | `GETSET k 0`                                                              |
| INCR          | Increment numeric value by 1 (create 0 if missing)                          | Useful for counters combined with `EXPIRE` for rate limiting                                                                                                                                                                   |                 | rate limiter example in source file                                       |
| INCRBY        | Increment by given integer (64-bit signed)                                  |                                                                                                                                                                                                                                 |                 | `INCRBY k 20`                                                             |
| INCRBYFLOAT   | Increment by given float (up to 17 decimal digits)                          |                                                                                                                                                                                                                                 |                 | `INCRBYFLOAT k 10.5`                                                      |
| MGET          | Get values of multiple keys                                                  |                                                                                                                                                                                                                                 |                 | `MGET k1 k2`                                                              |
| MSET          | Set multiple keys to multiple values (overwrite existing keys)              |                                                                                                                                                                                                                                 |                 | `MSET k1 1 k2 2`                                                           |
| MSETNX        | Set multiple keys, only if none of the keys exist                           |                                                                                                                                                                                                                                 |                 | `MSETNX k1 1 k2 2`                                                         |
| PSETEX        | Set the value and expiration in milliseconds                                |                                                                                                                                                                                                                                 |                 | `PSETEX k 1000 "abc"`                                                   |
| SET           | Set key to hold the string value                                            | `EX` seconds, `PX` milliseconds, `NX` set if not exists, `XX` set only if exists                                                                                                                                                |                 | `SET k 1`, `SET k "abc" EX 5`, `SET k "abc" NX`                        |
| SETBIT        | Set or clear bit at offset (string grows with zeros)                         | Offset range [0, 2^32) — large offsets may block Redis                                                                                                                               |                 | `SETBIT b 10086 1`                                                        |
| SETEX         | Set value and expiration in seconds                                         |                                                                                                                                                                                                                                 |                 | `SETEX k 5 "abc"`                                                        |
| SETNX         | Set key if it does not already exist                                        |                                                                                                                                                                                                                                 |                 | `SETNX k "abc"`                                                          |
| SETRANGE      | Overwrite part of the string at key starting at the specified offset        | Fills with zero bytes if offset is beyond current length                                                                                                                                                                      |                 | `SETRANGE k 6 "ab"`                                                      |
| STRLEN        | Return the length of the string value                                       |                                                                                                                                                                                                                                 |                 | `STRLEN k`                                                                |


## Hash

| Command    | Description                                                                            | Time Complexity | Example                                  |
| ---------- | -------------------------------------------------------------------------------------- | --------------- | ---------------------------------------- |
| HDEL       | Remove one or more specified fields from a hash (non-existing fields ignored)         |                 | `HDEL h a b`                              |
| HEXISTS    | Determine if a field exists in a hash                                                   |                 | `HEXISTS h a`                             |
| HGET       | Get the value of a hash field                                                          |                 | `HGET h a`                                |
| HGETALL    | Return all fields and values of the hash as a list                                     |                 | `HGETALL h`                               |
| HINCRBY    | Increment the integer value of a hash field by the given amount (64-bit)             |                 | `HINCRBY h a 200`                          |
| HINCRBYFLOAT | Increment the float value of a hash field                                            | Field value must be a string parseable as double                                                                                                                               |                 | `HINCRBYFLOAT h a 0.1`                     |
| HKEYS      | Get all field names in a hash                                                          |                 | `HKEYS h`                                 |
| HLEN       | Get the number of fields in a hash                                                     |                 | `HLEN h`                                  |
| HMGET      | Get the values of multiple hash fields                                                 |                 | `HMGET h key1 key2`                        |
| HMSET      | Set multiple fields in a hash (deprecated in newer Redis in favor of HSET with multiple pairs) |                 | `HMSET h k1 v1 k2 v2`                      |
| HSET       | Set the string value of a hash field                                                   |                 | `HSET h k1 v1`                             |
| HSETNX     | Set the value of a hash field, only if the field does not exist                       |                 | `HSETNX h k1 v1`                           |
| HVALS      | Get all values in a hash                                                               |                 | `HVALS h`                                  |
| HSCAN      | Incremental iteration over hash fields (see `SCAN`)                                   |                 |                                            |


## List

| Command     | Description                                                                 | Params / Notes                                                                                                                                                                                                 | Time Complexity | Example                                                                 |
| ----------- | --------------------------------------------------------------------------- | -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | --------------- | ----------------------------------------------------------------------- |
| BLPOP       | Blocking pop from multiple lists' heads (blocks until timeout or pushed)    | Multiple clients can block on the same keys; first-BLPOP-first-served ordering; in pipelining BLPOP does not block                                                                                                |                 | `BLPOP li1 li2 li3` or `BLPOP li1 li2 5`                                |
| BRPOP       | Blocking pop from multiple lists' tails                                    |                                                                                                                                                                                                                |                 | `BRPOP li 30`                                                            |
| BRPOPLPUSH  | Blocking pop from tail of source and push to head of destination (atomic)   |                                                                                                                                                                                                                |                 | `BRPOPLPUSH src dst 5`                                                   |
| LINDEX      | Get element at index                                                         |                                                                                                                                                                                                                |                 | `LINDEX li 0`, `LINDEX li -1`                                            |
| LINSERT     | Insert value before or after pivot element                                  | `BEFORE` / `AFTER`                                                                                                                                                                                             |                 | `LINSERT h BEFORE "world" "he"`                                       |
| LLEN        | Get list length                                                              |                                                                                                                                                                                                                |                 | `LLEN h`                                                                  |
| LPOP        | Remove and return the first element                                          |                                                                                                                                                                                                                |                 | `LPOP li`                                                                 |
| LPUSH       | Push values to the head (left) — creates list if not exists                 | Values are inserted from left to right (resulting order: last argument becomes head)                                                                                                                           |                 | `LPUSH li a b c`                                                          |
| LPUSHX      | Push to head only if list exists                                             |                                                                                                                                                                                                                |                 | `LPUSHX li a b c`                                                         |
| LRANGE      | Return a range of elements                                                   |                                                                                                                                                                                                                |                 | `LRANGE li 0 0`, `LRANGE li 0 1`                                         |
| LREM        | Remove elements equal to value — n>0 from head, n<0 from tail, n=0 all      |                                                                                                                                                                                                                |                 | `LREM li 2 abc`, `LREM li -2 abc`, `LREM li 0 abc`                        |
| LSET        | Set list element at index (error if out of range)                           |                                                                                                                                                                                                                |                 | `LSET li 3 "abc"`                                                       |
| LTRIM       | Trim list to specified range (clear list if start>stop)                     |                                                                                                                                                                                                                |                 | `LTRIM li 1 -1`                                                           |
| RPOP        | Remove and return the last element                                           |                                                                                                                                                                                                                |                 | `RPOP li`                                                                 |
| RPOPLPUSH   | Atomically pop from tail and push to another list's head                    | Can be used with same source and destination                                                                                                                                                                   |                 | `RPOPLPUSH src dst`                                                       |
| RPUSH       | Push values to the tail (right) — creates list if not exists               |                                                                                                                                                                                                                |                 | `RPUSH li a b c`                                                          |
| RPUSHX      | Push to tail only if list exists                                             |                                                                                                                                                                                                                |                 | `RPUSHX li "abc"`                                                       |


## Set

| Command    | Description                                                                 | Time Complexity | Example                                  |
| ---------- | --------------------------------------------------------------------------- | --------------- | ---------------------------------------- |
| SADD       | Add one or more members to a set (create set if not exists)                 |                 | `SADD s "abc" "def"`                  |
| SCARD      | Return set cardinality                                                       |                 | `ZCARD s` (note: for sorted sets use ZCARD) |
| SDIFF      | Subtract multiple sets                                                      |                 | `SDIFF s1 s2`                             |
| SDIFFSTORE | Subtract and store result in destination set                                 |                 | `SDIFFSTORE s1 s2 s3`                     |
| SINTER     | Intersect multiple sets                                                      |                 | `SINTER s1 s2`                            |
| SINTERSTORE| Intersect and store result                                                   |                 | `SINTERSTORE s1 s2 s3`                    |
| SISMEMBER  | Test membership                                                              |                 | `SISMEMBER s1 "abc"`                    |
| SMEMBERS   | Return all members (use SCAN for production to avoid performance issues)     |                 | `SMEMBERS s1`                             |
| SMOVE      | Move a member from one set to another (atomic)                              |                 | `SMOVE src dst "abc"`                   |
| SPOP       | Remove and return a random member                                            |                 | `SPOP s1`                                 |
| SRANDMEMBER| Return random members (unique if positive count less than size; may repeat if negative count) |                 | `SRANDMEMBER s1 3`                        |
| SREM       | Remove one or more members from a set                                        |                 | `SREM s1 "a" "b" "c"`               |
| SUNION     | Return union of sets                                                          |                 | `SUNION s1 s2`                            |
| SUNIONSTORE| Union and store result                                                       |                 | `SUNIONSTORE s1 s2 s3`                    |
| SSCAN      | Incremental iteration over set members (see `SCAN`)                          |                 |                                            |


## Sorted Set (Zset)

| Command        | Description                                                                 | Params / Notes                                                                 | Time Complexity | Example                                                                 |
| -------------- | --------------------------------------------------------------------------- | ------------------------------------------------------------------------------ | --------------- | ----------------------------------------------------------------------- |
| ZADD           | Add one or more members with scores (update if exists)                      |                                                                                |                 | `ZADD z1 5 a 6 b`                                                        |
| ZCARD          | Return number of elements in sorted set                                     |                                                                                |                 | `ZCARD z1`                                                               |
| ZCOUNT         | Count elements with score within range                                      |                                                                                |                 | `ZCOUNT z1 2 5`                                                          |
| ZINCRBY        | Increment score of member by given amount                                   |                                                                                |                 | `ZINCRBY z1 10 a`                                                        |
| ZRANGE         | Return elements in range by rank (ascending)                                | `WITHSCORES` option to return scores                                            |                 | `ZRANGE z1 0 -1 WITHSCORES`                                              |
| ZRANGEBYSCORE  | Return elements in score range                                               | `LIMIT`, `WITHSCORES`, use `(` for exclusive range                              |                 | `ZRANGEBYSCORE z1 1 5`                                                    |
| ZRANK          | Determine rank of member (ascending)                                         |                                                                                |                 | `ZRANK z1 a`                                                             |
| ZREM           | Remove one or more members                                                    |                                                                                |                 | `ZREM z1 a b`                                                             |
| ZREMRANGEBYRANK| Remove elements by rank range                                                 |                                                                                |                 | `ZREMRANGEBYRANK z1 0 1`                                                  |
| ZREMRANGEBYSCORE| Remove elements by score range                                               |                                                                                |                 | `ZREMRANGEBYSCORE z1 3 5`                                                 |
| ZREVRANGE      | Return range in reverse order (descending)                                   | `WITHSCORES` available                                                          |                 | `ZREVRANGE z1 0 -1 WITHSCORES`                                           |
| ZREVRANGEBYSCORE| Return elements by score in reverse order                                   |                                                                                |                 | `ZREVRANGEBYSCORE z1 +inf -inf`                                          |
| ZREVRANK       | Return rank of member (descending)                                           |                                                                                |                 | `ZREVRANK z1 a`                                                           |
| ZSCORE         | Return the score of a member                                                  |                                                                                |                 | `ZSCORE z1 a`                                                             |
| ZUNIONSTORE    | Union multiple zsets into destination with optional `WEIGHTS` and `AGGREGATE` | `AGGREGATE` can be `SUM` (default), `MIN`, `MAX`                                |                 | `ZUNIONSTORE z1 2 z2 z3 WEIGHTS 1 3`                                     |
| ZINTERSTORE    | Intersect multiple zsets into destination                                    |                                                                                |                 | `ZINTERSTORE z1 2 z2 z3`                                                  |
| ZSCAN          | Incremental iteration over sorted set                                         |                                                                                |                 |                                                                            |


## Pub/Sub

| Command      | Description                                 | Time Complexity | Example                                                 |
| ------------ | ------------------------------------------- | --------------- | ------------------------------------------------------- |
| PSUBSCRIBE   | Subscribe to channels matching a pattern     |                 | `PSUBSCRIBE AB*`                                         |
| PUBLISH      | Publish a message to a channel               |                 | `PUBLISH ch "hello"`                                   |
| PUBSUB       | Inspect the Pub/Sub system                   |                 | `PUBSUB CHANNELS *.abc`, `PUBSUB NUMSUB ch1 ch2`, `PUBSUB NUMPAT` |
| PUNSUBSCRIBE | Unsubscribe from pattern subscriptions       |                 | `PUNSUBSCRIBE AB*`                                       |
| SUBSCRIBE    | Subscribe to channels                        |                 | `SUBSCRIBE AB`                                           |
| UNSUBSCRIBE  | Unsubscribe from channels                    |                 | `UNSUBSCRIBE AB`                                         |


## Transaction

| Command | Description                                                                                                       | Example                    |
| ------- | ----------------------------------------------------------------------------------------------------------------- | -------------------------- |
| DISCARD | Discard the queued commands in a transaction                                                                      | `DISCARD`                  |
| EXEC    | Execute all queued commands (aborts if watched keys were modified)                                                | `MULTI` / `SET a "xx"` / `EXEC` |
| MULTI   | Mark the start of a transaction block                                                                             |                            |
| UNWATCH | Forget all watched keys                                                                                            |                            |
| WATCH   | Watch one or more keys for conditional execution at `EXEC`                                                         | `WATCH k1 k2`              |


## HyperLogLog

| Command | Description                      | Example               |
| ------- | -------------------------------- | --------------------- |
| PFADD   | Add elements to HyperLogLog      | `PFADD k1 "k1"`     |
| PFCOUNT | Return approximate cardinality   | `PFCOUNT k1`          |
| PFMERGE | Merge multiple HyperLogLogs      |                       |


## Scripting

| Command        | Description                                     | Example                                                                 |
| -------------- | ----------------------------------------------- | ----------------------------------------------------------------------- |
| EVAL           | Execute a Lua script with given keys and args   | `EVAL "return {KEYS[1],KEYS[2],ARGV[1]}" 2 key1 key2 first`           |
| EVALSHA        | Execute a cached script by SHA1                 | `EVALSHA <sha1> 0`                                                     |
| SCRIPT EXISTS  | Check if script SHA exists                      | `SCRIPT EXISTS <sha1>`                                                 |
| SCRIPT FLUSH   | Remove all scripts from script cache            | `SCRIPT FLUSH`                                                          |
| SCRIPT KILL    | Kill the currently running script               | `SCRIPT KILL`                                                           |
| SCRIPT LOAD    | Load a script into the script cache (do not run) | `SCRIPT LOAD "return 'hello'"`                                        |


## Server

| Command           | Description                                                                 | Example                                              |
| ----------------- | --------------------------------------------------------------------------- | ---------------------------------------------------- |
| BGREWRITEAOF      | Manually trigger AOF rewrite                                                  | `BGREWRITEAOF`                                        |
| BGSAVE            | Asynchronously save dataset to disk (background)                              | `BGSAVE`                                              |
| CLIENT GETNAME    | Return the current connection's name                                         | `CLIENT GETNAME`                                      |
| CLIENT KILL       | Kill the connection for a given address                                      | `CLIENT KILL 127.0.0.1:6379`                          |
| CLIENT LIST       | List client connections and statistics                                       | `CLIENT LIST`                                         |
| CLIENT SETNAME    | Set the current connection's name                                            | `CLIENT SETNAME hello`                                |
| CONFIG GET        | Get runtime configuration parameters                                         | `CONFIG GET s*`, `CONFIG GET slowlog-max-len`        |
| CONFIG RESETSTAT  | Reset various statistics (keyspace hits/misses, commands processed, etc.)     | `CONFIG RESETSTAT`                                    |
| CONFIG REWRITE    | Atomically rewrite redis.conf with current config                             | `CONFIG SET appendonly yes` / `CONFIG REWRITE`        |
| CONFIG SET        | Set a configuration parameter at runtime                                     | `CONFIG SET appendonly yes`                           |
| DBSIZE            | Return the number of keys in the selected database                            | `DBSIZE`                                              |
| DEBUG OBJECT      | Debugging command — return internal object info                               | `DEBUG OBJECT obj`                                    |
