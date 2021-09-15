# Redis命令

| 命令         | 说明                                                         | 参数                           | 示例                                                         |
| ------------ | ------------------------------------------------------------ | ------------------------------ | ------------------------------------------------------------ |
| AUTH         | 检测给定的密码是否和配置文件中的密码一致                     | - 密码值                       | - `AUTH hello` 检测配置的密码是不是hello                     |
| INFO         | - `server`<br>- `clients`<br>- ` memory`<br>- `persistence`<br>- `stats`<br>- `replication`<br>- `cpu`<br>- `commandstats`<br>- `cluster`<br>- `keyspace` |                                | - `INFO server` 服务器信息<br>- `INFO clients` 已连接客户端信息<br>- `INFO memory` 内存信息<br>- `INFO persistence` RDB和AOF相关信息<br>- `INFO stats` 一般统计信息<br>- `INFO replication` 主从复制信息<br>- `INFO cpu` CPU统计信息<br>- `INFO commandstats` 命令统计信息<br>- `INFO cluster` 集群信息<br>- `INFO keyspace` 数据库相关的统计信息 |
| PSUBSCRIBE   | 模糊匹配订阅频道                                             | - 模式名                       | - `PSUBSCRIBE AB*` 模糊匹配订阅以AB开头的频道                |
| PUNSUBSCRIBE | 取消模糊匹配订阅频道                                         | - 模式名                       | - `PUNSUBSCRIBE AB*` 取消模糊匹配以AB开头的频道              |
| PSYNC        | 部分重同步数据（新版）                                       | - 服务器运行ID<br>- 复制偏移量 | - `PSYNC ? -1` 主动请求主服务器进行完整重同步<br>- `PSYNC 53b9b28df8042fdc9ab5e3fcbbbabff1d5dce2b3 20000` 主动请求主服务器同步偏移量2000之后的数据 |
| PUBLISH      | 向频道发布消息                                               | - 频道/模式名<br>- 消息        | - `PUBLISH ch hello` 向频道ch发送消息hello                   |
| PUBSUB       | - `CHANNELS [pattern]`<br>- `NUMSUB [ch1 ... chN]`<br>- `NUMPAT` |                                | - `PUBSUB CHANNELS *.abc` 查看匹配频道<br>- `PUBSUB NUMSUM ch1 ch2` 查看ch1和ch2的订阅者数量<br>- `PUBSUB NUMPAT` 查看订阅模式的数量 |
| REPLCONF     | - `ACK <replication_offset>`                                 |                                |                                                              |
| SUBSCRIBE    | 订阅频道                                                     | - 频道名                       | - `SUBSCRIBE AB` 订阅频道AB                                  |
| UNSUBSCRIBE  | 取消订阅                                                     | - 频道名                       | - `UNSUBSCRIBE AB` 取消订阅频道AB                            |
| SYNC         | 重同步数据（效率不佳）                                       |                                |                                                              |
| SLAVEOF      | 设置当前服务器的主服务器                                     | - IP<br>- 端口                 | - `SLAVEOF 127.0.0.1 6379` 设置当前服务器的主服务器为127.0.0.1:6379 |

