# ZMQ socket

<!-- vim-markdown-toc GFM -->

* [选项](#选项)
    - [socket选项](#socket选项)
        + [ZMQ_SNDHWM](#zmq_sndhwm)
        + [ZMQ_RCVHWM](#zmq_rcvhwm)
        + [ZMQ_AFFINITY](#zmq_affinity)
        + [ZMQ_SUBSCRIBE](#zmq_subscribe)
        + [ZMQ_UNSUBSCRIBE](#zmq_unsubscribe)
        + [ZMQ_IDENTITY](#zmq_identity)
        + [ZMQ_RATE](#zmq_rate)
        + [ZMQ_RECOVERY_IVL](#zmq_recovery_ivl)
        + [ZMQ_SNDBUF](#zmq_sndbuf)
        + [ZMQ_RCVBUF](#zmq_rcvbuf)
        + [ZMQ_RCVMORE](#zmq_rcvmore)
        + [ZMQ_FD](#zmq_fd)
        + [ZMQ_EVENTS](#zmq_events)
        + [ZMQ_TYPE](#zmq_type)
        + [ZMQ_LINGER](#zmq_linger)
        + [ZMQ_RECONNECT_IVL](#zmq_reconnect_ivl)
        + [ZMQ_BACKLOG](#zmq_backlog)
        + [ZMQ_RECONNECT_IVL_MAX](#zmq_reconnect_ivl_max)
        + [ZMQ_MAXMSGSIZE](#zmq_maxmsgsize)
        + [ZMQ_MULTICAST_HOPS](#zmq_multicast_hops)
        + [ZMQ_RCVTIMEO](#zmq_rcvtimeo)
        + [ZMQ_SNDTIMEO](#zmq_sndtimeo)
        + [ZMQ_LAST_ENDPOINT](#zmq_last_endpoint)
        + [ZMQ_ROUTER_MANDATORY](#zmq_router_mandatory)
        + [ZMQ_TCP_KEEPALIVE](#zmq_tcp_keepalive)
        + [ZMQ_TCP_KEEPALIVE_CNT](#zmq_tcp_keepalive_cnt)
        + [ZMQ_TCP_KEEPALIVE_INTVL](#zmq_tcp_keepalive_intvl)
        + [ZMQ_IMMEDIATE](#zmq_immediate)
        + [ZMQ_XPUB_VERBOSE](#zmq_xpub_verbose)
        + [ZMQ_ROUTER_RAW](#zmq_router_raw)
        + [ZMQ_IPV6](#zmq_ipv6)
        + [ZMQ_MECHANISM](#zmq_mechanism)
        + [ZMQ_PLAIN_SERVER](#zmq_plain_server)
        + [ZMQ_PLAIN_USERNAME](#zmq_plain_username)
        + [ZMQ_PLAIN_PASSWORD](#zmq_plain_password)
        + [ZMQ_CURVE_SERVER](#zmq_curve_server)
        + [ZMQ_CURVE_PUBLICKEY](#zmq_curve_publickey)
        + [ZMQ_CURVE_SECRETKEY](#zmq_curve_secretkey)
        + [ZMQ_CURVE_SERVERKEY](#zmq_curve_serverkey)
        + [ZMQ_PROBE_ROUTER](#zmq_probe_router)
        + [ZMQ_REQ_CORRELATE](#zmq_req_correlate)
        + [ZMQ_REQ_RELAXED](#zmq_req_relaxed)
        + [ZMQ_CONFLATE](#zmq_conflate)
        + [ZMQ_ZAP_DOMAIN](#zmq_zap_domain)
        + [ZMQ_ROUTER_HANDOVER](#zmq_router_handover)
        + [ZMQ_TOS](#zmq_tos)
        + [ZMQ_CONNECT_ROUTING_ID](#zmq_connect_routing_id)
        + [ZMQ_GSSAPI_SERVER](#zmq_gssapi_server)
        + [ZMQ_GSSAPI_PRINCIPAL](#zmq_gssapi_principal)
        + [ZMQ_GSSAPI_SERVICE_PRINCIPAL](#zmq_gssapi_service_principal)
        + [ZMQ_GSSAPI_PLAINTEXT](#zmq_gssapi_plaintext)
        + [ZMQ_HANDSHAKE_IVL](#zmq_handshake_ivl)
        + [ZMQ_SOCKS_PROXY](#zmq_socks_proxy)
        + [ZMQ_XPUB_NODROP](#zmq_xpub_nodrop)
        + [ZMQ_BLOCKY](#zmq_blocky)
        + [ZMQ_XPUB_MANUAL](#zmq_xpub_manual)
        + [ZMQ_XPUB_WELCOME_MSG](#zmq_xpub_welcome_msg)
        + [ZMQ_STREAM_NOTIFY](#zmq_stream_notify)
        + [ZMQ_INVERT_MATCHING](#zmq_invert_matching)
        + [ZMQ_HEARTBEAT_IVL](#zmq_heartbeat_ivl)
        + [ZMQ_HEARTBEAT_TTL](#zmq_heartbeat_ttl)
        + [ZMQ_HEARTBEAT_TIMEOUT](#zmq_heartbeat_timeout)
        + [ZMQ_XPUB_VERBOSER](#zmq_xpub_verboser)
        + [ZMQ_CONNECT_TIMEOUT](#zmq_connect_timeout)
        + [ZMQ_TCP_MAXRT](#zmq_tcp_maxrt)
        + [ZMQ_THREAD_SAFE](#zmq_thread_safe)
        + [ZMQ_MULTICAST_MAXTPDU](#zmq_multicast_maxtpdu)
        + [ZMQ_VMCI_BUFFER_SIZE](#zmq_vmci_buffer_size)
        + [ZMQ_VMCI_BUFFER_MIN_SIZE](#zmq_vmci_buffer_min_size)
        + [ZMQ_VMCI_BUFFER_MAX_SIZE](#zmq_vmci_buffer_max_size)
        + [ZMQ_VMCI_CONNECT_TIMEOUT](#zmq_vmci_connect_timeout)
        + [ZMQ_USE_FD](#zmq_use_fd)
        + [ZMQ_GSSAPI_PRINCIPAL_NAMETYPE](#zmq_gssapi_principal_nametype)
        + [ZMQ_GSSAPI_SERVICE_PRINCIPAL_NAMETYPE](#zmq_gssapi_service_principal_nametype)
        + [ZMQ_BINDTODEVICE](#zmq_bindtodevice)
    - [message选项](#message选项)
        + [ZMQ_MORE](#zmq_more)
        + [ZMQ_SHARED](#zmq_shared)
    - [send/recv 选项](#sendrecv-选项)
        + [ZMQ_DONTWAIT](#zmq_dontwait)
        + [ZMQ_SNDMORE](#zmq_sndmore)
    - [security mechainsms选项](#security-mechainsms选项)
        + [ZMQ_NULL](#zmq_null)
        + [ZMQ_PLAIN](#zmq_plain)
        + [ZMQ_CURVE](#zmq_curve)
        + [ZMQ_GSSAPI](#zmq_gssapi)
    - [RDDIO-DISH protocol选项](#rddio-dish-protocol选项)
        + [ZMQ_GROUP_MAX_LENGTH](#zmq_group_max_length)
    - [注意](#注意)
* [参考](#参考)

<!-- vim-markdown-toc -->



## 选项

### socket选项

#### ZMQ_SNDHWM

| 值类型   | int                                  |
| -------- | ------------------------------------ |
| 值       | 1000                                 |
| 特殊值   | 无限制：0                            |
| 应用场景 | 所有socket                           |
| 边界处理 | pub/sub：TODO<br>router/dealer：TODO |

发送消息高水位（最大发送缓冲区缓存量，这只是理论上的硬限制值，实际缓冲区最大容量只能达到高水位的6-~70%左右）。

#### ZMQ_RCVHWM

| 值类型   | int                                   |
| -------- | ------------------------------------- |
| 默认值   | 1000                                  |
| 特殊值   | 0：无限制                             |
| 应用场景 | 所有socket                            |
| 边界处理 | pub/sub：TODO<br/>router/dealer：TODO |

接收消息高水位（最大接收缓冲区缓存量，这只是理论上的硬限制值，实际缓冲区最大容量只能达到高水位的6-~70%左右）。

#### ZMQ_AFFINITY

| 值类型   | bitmap     |
| -------- | ---------- |
| 默认值   | 0          |
| 特殊值   | 0：无关联  |
| 应用场景 | 所有socket |
| 边界处理 |            |

设置I/O线程关联（指定socket新创建的链接与哪个线程关联），最低位对应线程，第2位对应线程2，以此类推。

#### ZMQ_SUBSCRIBE

| 值类型   | 二进制数据                        |
| -------- | --------------------------------- |
| 默认值   | N/A                               |
| 特殊值   | 长度为0的二进制数据：订阅所有主题 |
| 应用场景 | ZMQ_SUB                           |
| 边界处理 |                                   |

订阅主题（支持订阅多个相同主题）。

#### ZMQ_UNSUBSCRIBE

| 值类型   | 二进制数据                        |
| -------- | --------------------------------- |
| 默认值   | N/A                               |
| 特殊值   | 长度为0的二进制数据：订阅所有主题 |
| 应用场景 | ZMQ_SUB                           |
| 边界处理 |                                   |

取消订阅主题（如果订阅多个相同的主题，此操作指挥移除其中一个，其它可以继续使用）。

#### ZMQ_IDENTITY

| 值类型   | 二进制数据                               |
| -------- | ---------------------------------------- |
| 默认值   | NULL                                     |
| 特殊值   |                                          |
| 应用场景 | ZMQ_REQ, ZMQ_REP, ZMQ_ROUTER, ZMQ_DEALER |
| 边界处理 | 1. ID重名：TODO。                        |

设置socket身份ID（socket ID主要用于消息路由）。

#### ZMQ_RATE

| 值类型   | int (kbyte/s)                  |
| -------- | ------------------------------ |
| 默认值   | 100                            |
| 特殊值   |                                |
| 应用场景 | 多路广播时，所有socket都有效。 |
| 边界处理 |                                |

设置接收和发送广播数据的频率最大值。

#### ZMQ_RECOVERY_IVL

| 值类型   | int (ms)                       |
| -------- | ------------------------------ |
| 默认值   | 10000                          |
| 特殊值   |                                |
| 应用场景 | 多路广播时，所有socket都有效。 |
| 边界处理 |                                |

设置多路广播恢复时间（一个接收端从一个广播组退出后再连接上来之前，数据丢失导致数据不可恢复的最大时间间隔（ms）；当设置较大的恢复时间时，非常耗内存）。

#### ZMQ_SNDBUF

| 值类型   | int (Byte)           |
| -------- | -------------------- |
| 默认值   | 0                    |
| 特殊值   | 0：使用OS默认值；    |
| 应用场景 | 对所有socket都有效。 |
| 边界处理 |                      |

设置内核发送缓冲区大小。

#### ZMQ_RCVBUF

| 值类型   | int (Byte)           |
| -------- | -------------------- |
| 默认值   | 0                    |
| 特殊值   | 0：使用OS默认值；    |
| 应用场景 | 对所有socket都有效。 |
| 边界处理 |                      |

设置内核接收缓冲区大小。

#### ZMQ_RCVMORE

#### ZMQ_FD

#### ZMQ_EVENTS

#### ZMQ_TYPE

#### ZMQ_LINGER

| 值类型   | int (ms)                                          |
| -------- | ------------------------------------------------- |
| 默认值   | -1                                                |
| 特殊值   | -1：无限停留时间；0：不停留，直接丢弃未发送消息。 |
| 应用场景 | 对所有socket都有效。                              |
| 边界处理 |                                                   |

为socket关闭设置停留时间（为尚未发送完的消息发送腾出时间，当时间到时，所有未发送的消息都被丢弃）。

#### ZMQ_RECONNECT_IVL

| 值类型   | int (ms)                                         |
| -------- | ------------------------------------------------ |
| 默认值   | 100                                              |
| 特殊值   | -1：不进行重连                                   |
| 应用场景 | 当使用面向连接的传输方式时，对所有socket都有效。 |
| 边界处理 |                                                  |

重连间隔（当对端的连接断开后，初次尝试重新连接的时长；不建议设置过小，防止“重连风暴”）。

#### ZMQ_BACKLOG

#### ZMQ_RECONNECT_IVL_MAX

| 值类型   | int (ms)                                               |
| -------- | ------------------------------------------------------ |
| 默认值   | 0                                                      |
| 特殊值   | 0：只使用`ZMQ_RECONNECT_IVL`设置的值，不进行指数补偿； |
| 应用场景 | 当使用面向连接的传输方式时，对所有socket都有效。       |
| 边界处理 | `< ZMQ_RECONNECT_IVL`：忽略这个值。                    |

重连间隔最大值（与`ZMQ_RECONNECT_IVL`配合使用，使用指数补偿技术：每次重连都是上次时间间隔的2倍，直到`ZMQ_RECONNECT_IVL == ZMQ_RECONNECT_IVL_MAX`）。

#### ZMQ_MAXMSGSIZE

#### ZMQ_MULTICAST_HOPS

| 值类型   | int                                              |
| -------- | ------------------------------------------------ |
| 默认值   | 1                                                |
| 特殊值   | 1：多播数据包不能离开本地网路。                  |
| 应用场景 | 当使用面向连接的传输方式时，对所有socket都有效。 |
| 边界处理 |                                                  |

多播数据包的最大网络中继。

#### ZMQ_RCVTIMEO

| 值类型   | int (ms)                                                     |
| -------- | ------------------------------------------------------------ |
| 默认值   | -1                                                           |
| 特殊值   | -1：阻塞直到收到消息；<br>0：立即返回，如果没有收到任何消息，返回EAGAIN错误； |
| 应用场景 | 对所有socket都有效。                                         |
| 边界处理 |                                                              |

接收超时

#### ZMQ_SNDTIMEO

| 值类型   | int (ms)                                                     |
| -------- | ------------------------------------------------------------ |
| 默认值   | -1                                                           |
| 特殊值   | -1：阻塞直到收到消息；<br>0：立即返回，如果没有收到任何消息，返回EAGAIN错误； |
| 应用场景 | 对所有socket都有效。                                         |
| 边界处理 |                                                              |

发送超时

#### ZMQ_LAST_ENDPOINT

#### ZMQ_ROUTER_MANDATORY

#### ZMQ_TCP_KEEPALIVE

#### ZMQ_TCP_KEEPALIVE_CNT

#### ZMQ_TCP_KEEPALIVE_INTVL

#### ZMQ_IMMEDIATE

| 值类型   | int                                    |
| -------- | -------------------------------------- |
| 默认值   | 0                                      |
| 特殊值   | 0：false<br>1：true                    |
| 应用场景 | 当使用面向连接的时候，所有socket可用； |
| 边界处理 |                                        |

设置在连接在建立完成后进行发送（防止连接时丢包）。

#### ZMQ_XPUB_VERBOSE

| 值类型   | int                                                          |
| -------- | ------------------------------------------------------------ |
| 默认值   | 0                                                            |
| 特殊值   | 0：只允许新的订阅消息通过传输到上游；<br>1：允许所有的订阅消息传输到上游。 |
| 应用场景 | ZMQ_XPUB                                                     |
| 边界处理 |                                                              |

设置订阅行为。

#### ZMQ_ROUTER_RAW

#### ZMQ_IPV6

#### ZMQ_MECHANISM

#### ZMQ_PLAIN_SERVER

#### ZMQ_PLAIN_USERNAME

#### ZMQ_PLAIN_PASSWORD

#### ZMQ_CURVE_SERVER

#### ZMQ_CURVE_PUBLICKEY

#### ZMQ_CURVE_SECRETKEY

#### ZMQ_CURVE_SERVERKEY

#### ZMQ_PROBE_ROUTER

#### ZMQ_REQ_CORRELATE

#### ZMQ_REQ_RELAXED

#### ZMQ_CONFLATE

#### ZMQ_ZAP_DOMAIN

#### ZMQ_ROUTER_HANDOVER

| 值类型   | int                                        |
| -------- | ------------------------------------------ |
| 默认值   | 0                                          |
| 特殊值   | 0：不处理<br>1：遇到ID冲突时进行ID重新分配 |
| 应用场景 | ZMQ_ROUTER                                 |
| 边界处理 |                                            |

设置如何处理ROUTER socket的ID冲突。

#### ZMQ_TOS

#### ZMQ_CONNECT_ROUTING_ID

#### ZMQ_GSSAPI_SERVER

#### ZMQ_GSSAPI_PRINCIPAL

#### ZMQ_GSSAPI_SERVICE_PRINCIPAL

#### ZMQ_GSSAPI_PLAINTEXT

#### ZMQ_HANDSHAKE_IVL

#### ZMQ_SOCKS_PROXY

#### ZMQ_XPUB_NODROP

#### ZMQ_BLOCKY

#### ZMQ_XPUB_MANUAL

#### ZMQ_XPUB_WELCOME_MSG

#### ZMQ_STREAM_NOTIFY

#### ZMQ_INVERT_MATCHING

#### ZMQ_HEARTBEAT_IVL

#### ZMQ_HEARTBEAT_TTL

#### ZMQ_HEARTBEAT_TIMEOUT

#### ZMQ_XPUB_VERBOSER

#### ZMQ_CONNECT_TIMEOUT

#### ZMQ_TCP_MAXRT

#### ZMQ_THREAD_SAFE

#### ZMQ_MULTICAST_MAXTPDU

#### ZMQ_VMCI_BUFFER_SIZE

#### ZMQ_VMCI_BUFFER_MIN_SIZE

#### ZMQ_VMCI_BUFFER_MAX_SIZE

#### ZMQ_VMCI_CONNECT_TIMEOUT

#### ZMQ_USE_FD

#### ZMQ_GSSAPI_PRINCIPAL_NAMETYPE

#### ZMQ_GSSAPI_SERVICE_PRINCIPAL_NAMETYPE

#### ZMQ_BINDTODEVICE

### message选项

#### ZMQ_MORE

#### ZMQ_SHARED

### send/recv 选项

#### ZMQ_DONTWAIT

#### ZMQ_SNDMORE

### security mechainsms选项

#### ZMQ_NULL

#### ZMQ_PLAIN

#### ZMQ_CURVE

#### ZMQ_GSSAPI

### RDDIO-DISH protocol选项

#### ZMQ_GROUP_MAX_LENGTH

### 注意

一般的选项都需要在`bind/connect`之前设置（以下选项除外）：

- ZMQ_SUBSCRIBE
- ZMQ_UNSUBSCRIBE
- ZMQ_LINGER
- ZMQ_ROUTER_HANDOVER
- ZMQ_ROUTER_MANDATORY
- ZMQ_PROBE_ROUTE
- ZMQ_XPUB_VERBOSE
- ZMQ_REQ_CORRELATE
- ZMQ_REQ_RELAXED



## 参考

-  [ZeroMQ学习笔记(2)——套接字和模式](https://blog.csdn.net/lcynone/article/details/112448171)
-  [ZeroMQ 教程 002 : 高级技巧](https://www.cnblogs.com/neooelric/p/9020872.html)
-  [ZeroMQ源码阅读阶段性总结](https://www.icode9.com/content-1-120408.html#socket_base_t___343)
-  [源码分析-ZeroMQ连接的建立与重连机制](https://dymanzy.github.io/2017/08/11/%E6%BA%90%E7%A0%81%E5%88%86%E6%9E%90-ZeroMQ%E8%BF%9E%E6%8E%A5%E7%9A%84%E5%BB%BA%E7%AB%8B%E4%B8%8E%E9%87%8D%E8%BF%9E%E6%9C%BA%E5%88%B6/)
-  [ZMQ源码分析（五） --TCP通讯](https://blog.csdn.net/tbyzs/article/details/50577284)
-  [源码分析-ZeroMQ连接的建立与重连机制](https://dymanzy.github.io/2017/08/11/%E6%BA%90%E7%A0%81%E5%88%86%E6%9E%90-ZeroMQ%E8%BF%9E%E6%8E%A5%E7%9A%84%E5%BB%BA%E7%AB%8B%E4%B8%8E%E9%87%8D%E8%BF%9E%E6%9C%BA%E5%88%B6/)
-  [ZeroMQ接口函数之 ：zmq_setsockopt –设置ZMQ socket的属性](https://www.cnblogs.com/fengbohello/p/4398953.html)
