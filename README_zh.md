[中文版](README_zh.md) | [English](README.md)

# 目录

## 快捷导航

[英汉词典](en_zh_dictionary.md) [面试笔记](interview.md) [Bug速查](BUG/README.md) [shell手册](LANG/shell.md) [git指南](OTHERS/git.md) [redis命令](DB/REDIS/cmd.md) [markdown手册](LANG/markdown.md) [sql语法手册](DB/sql.md) [STL](LANG/C++/stl.md) [vim快捷键](OTHERS/vim_shortcut.md)  [dot语法](LANG/dot.md)  [ASSIC码表](OTHERS/assic_table.md)  [Posix接口](OS/posix.md)  [Lua API](LANG/LUA/api.md)  [套接字编程](NET/socket.md)

---

## [算法](ALGO/README.md)

- [平衡树](ALGO/balance_tree.md)
- [大O计数法](ALGO/big_o_notation.md)
- [有限状态机](ALGO/fsm.md)
- [行为树](ALGO/behavior_tree.md)
- [二叉树](ALGO/binary_tree.md)
- [散列算法](ALGO/hash.md)
- [堆](ALGO/heap.md)
- [LRU算法](ALGO/lru.md)
- [最小生成树](ALGO/minimum_spanning_tree.md)
- [链表](ALGO/link_list.md)
- [MurmurHash算法](ALGO/murmur_hash.md)
- [队列](ALGO/queue.md)
- [红黑树](ALGO/rb_tree.md)
- [环形队列](ALGO/ring_buffer.md)
- [最短路径算法](ALGO/shortest_path_problem.md)
- [跳表](ALGO/skiplist.md)
- [排序算法总结](ALGO/sort.md)
- [栈](ALGO/stack.md)
- [树](ALGO/tree.md)

---

## [数据库](DB/README.md)

- [acid](DB/acid.md)
- [数据库设计](DB/design.md)
- [sql手册](DB/sql.md)

### [Mysql](DB/MYSQL/README.md)

- [总结](DB/MYSQL/summary.md)
- [命令](DB/MYSQL/cmd.md)
- [配置](DB/MYSQL/conf.md)
- [数据类型](DB/MYSQL/data_type.md)
- [驱动](DB/MYSQL/drive.md)
- [环境搭建](DB/MYSQL/env.md)
- [日志](DB/MYSQL/log.md)

### [Redis](DB/REDIS/README.md)

- [总结](DB/REDIS/summary.md)
- [命令](DB/REDIS/cmd.md)
- [环境搭建](DB/REDIS/env.md)
- [利用redis实现异步队列](DB/REDIS/async_queue.md)
- [利用redis实现分布式锁](DB/REDIS/dcs_lock.md)
- [利用redis实现延时队列](DB/REDIS/delay_queue.md)
- [利用redis实现消息队列](DB/REDIS/mq.md)
- [redis源码分析-二进制位数组](DB/REDIS/ansys_bit_array.md)
- [redis源码分析-客户端](DB/REDIS/ansys_cli.md)
- [redis源码分析-集群](DB/REDIS/ansys_cluster.md)
- [redis源码分析-命令行](DB/REDIS/ansys_cmd.md)
- [redis源码分析-数据库实现](DB/REDIS/ansys_db.md)
- [redis源码分析-事件](DB/REDIS/ansys_event.md)
- [redis源码分析-内存回收](DB/REDIS/ansys_gc.md)
- [redis源码分析-整数集合](DB/REDIS/ansys_intset.md)
- [redis源码分析-链表](DB/REDIS/ansys_linklist.md)
- [redis源码分析-Lua脚本](DB/REDIS/ansys_lua.md)
- [redis源码分析-字典](DB/REDIS/ansys_map.md)
- [redis源码分析-监视器](DB/REDIS/ansys_moniter.md)
- [redis源码分析-网络连接](DB/REDIS/ansys_network.md)
- [redis源码分析-数据类型](DB/REDIS/ansys_object.md)
- [redis源码分析-持久化](DB/REDIS/ansys_persistence.md)
- [redis源码分析-发布订阅](DB/REDIS/ansys_pub_sub.md)
- [redis源码分析-复制](DB/REDIS/ansys_replication.md)
- [redis源码分析-字符串](DB/REDIS/ansys_sds.md)
- [redis源码分析-哨兵](DB/REDIS/ansys_sentinel.md)
- [redis源码分析-服务端](DB/REDIS/ansys_server.md)
- [redis源码分析-跳表](DB/REDIS/ansys_skiplist.md)
- [redis源码分析-事务](DB/REDIS/ansys_transaction.md)
- [redis源码分析-压缩列表](DB/REDIS/ansys_ziplist.md)

### [RocksDB](DB/ROCKSDB/README.md)


### [Sqlite](DB/SQLITE/README.md)

- [环境配置](DB/SQLITE/env.md)

---

## [分布式系统](DCS/README.md)

- [BitTorrent协议](DCS/bittorrent.md)
- [CAP理论](DCS/cap.md)
- [DHT(Distributed Hash Table, 分布式哈希表)](DCS/dht.md)
- [DTP(分布式事务)](DCS/dtp.md)
- [Kad算法](DCS/kad.md)
- [Merkle tree](DCS/merkle.md)
- [分布式存储](DCS/storage.md)

### [共识算法](#DCS/CONSENSUS/README.md)

- [零知识证明](DCS/CONSENSUS/zk-SNARK.md)
- [Raft-可靠，可复制，可冗余，可容错算法](DCS/CONSENSUS/raft.md)
- [Paxos](DCS/CONSENSUS/paxos.md)
- [pool-pool验证池](DCS/CONSENSUS/pool.md)
- [dbft-授权拜占庭容错](DCS/CONSENSUS/dbft.md)
- [pbft-实用拜占庭容错](DCS/CONSENSUS/pbft.md)
- [ripple-瑞波共识](DCS/CONSENSUS/ripple.md)
- [casper-投注共识](DCS/CONSENSUS/casper.md)
- [dpos-股份授权证明](DCS/CONSENSUS/dpos.md)
- [pos-权益证明](DCS/CONSENSUS/pos.md)
- [pow-工作量证明](DCS/CONSENSUS/pow.md)

其它

- [bancor协议](DCS/OTHER/bancor.md)

---

## [编程语言](LANG/README.md)

- [cmake](LANG/cmake.md)
- [dot](LANG/dot.md)
- [make](LANG/make.md)
- [markdown](LANG/markdown.md)
- [shell](LANG/shell.md)
- [solidity](LANG/solidity.md)

### [c/c++](LANG/C++/README.md)

- [c++环境搭建](LANG/C++/env.md)
- [最佳实践](LANG/C++/best_practice.md)
- [STL](LANG/C++/stl.md)
- [并发编程](LANG/C++/concurrency.md)
- [协程](LANG/C++/coroutine.md)
- [c++特性](LANG/C++/feature.md)
- [对象模型](LANG/C++/object.md)

Boost

- [asio](LANG/C++/Roost_asio.md)
- [optional](LANG/C++/boost_optional.md)
- [pool](LANG/C++/boost_pool.md)
- [statechart](LANG/C++/boost_statechart.md)
- [strand](LANG/C++/boost_strand.md)
- [test](LANG/C++/boost_test.md)

Qt

- [Qt总结](LANG/C++/qt_summary.md)
- [操作数据库](LANG/C++/qt_db.md)
- [信号槽](LANG/C++/qt_signals_slots.md)
- [元对象系统](LANG/C++/qt_obj.md)
- [多线程](LANG/C++/qt_multi_thread.md)
- [进程](LANG/C++/qt_progress.md)
- [套接字](LANG/C++/qt_socket.md)
- [单元测试](LANG/C++/qt_test.md)

### [go](LANG/GO/README.md)

- [总结](LANG/GO/summary.md)
- [协程](LANG/GO/coroutine.md)
- [环境配置](LANG/GO/env.md)
- [垃圾回收](LANG/GO/gc.md)
- [io函数](LANG/GO/io.md)

### [lua](LANG/LUA/README.md)

- [总结](LANG/LUA/summary.md)
- [API](LANG/LUA/api.md)
- [最佳实践](LANG/LUA/best_practice.md)
- [元表](LANG/LUA/metatable.md)
- [LUA模块](LANG/LUA/module.md)
- [面向对象](LANG/LUA/oop.md)
- [可变长参数](LANG/LUA/var_num_of_arg.md)
- [LUA源码分析-协程](LANG/LUA/ansys_coroutine.md)
- [LUA源码分析-数据类型](LANG/LUA/ansys_data_type.md)
- [LUA源码分析-GC](LANG/LUA/ansys_gc.md)

---

## [数学](MATH/README.md)

- [决策树](MATH/decision_table.md)

### [密码学](MATH/CRYPTO/README.md)

### [数学模型](MATH/MODEL/README.md)

### [概率论](MATH/PROBABILITY_THEORY/README.md)

### [统计学](MATH/STATISTICS/README.md)

---

## [多媒体](MEDIA/README.md)

- [FFmpeg](FFMPEG/README.md)
- [DTS和PTS](dts_pts.md)
- [I帧 P帧 B帧](frame.md)
- [GB/T 28181](gb28181.md)
- [ts协议](ts.md)

### [FFmpeg](MEDIA/README.md)

- [速查手册](ffmpeg_cmd.md)
- [安装](env.md)
- [常用的数据结构](ansys_data_struct.md)
- [init系列函数](ansys_init.md)
- [main函数](ansys_main.md)
- [注册系列函数](ansys_register.md)

---

## [计算机网络](NET/README.md)

- [总结](NET/summary.md)
- [ARP协议](NET/arp.md)
- [Bitswap协议](NET/bitswap.md)
- [DHCP协议](NET/dhcp.md)
- [DNS协议](NET/dns.md)
- [HLS协议](NET/hls.md)
- [HTTP协议](NET/http.md)
- [HTTP-FLV协议](NET/http_flv.md)
- [ICMP协议](NET/icmp.md)
- [网络I/O](NET/io.md)
- [IP](NET/ip.md)
- [MDNS协议](NET/mdns.md)
- [Protobuf编码](NET/protobuf.md)
- [QoS服务质量控制](NET/qos.md)
- [MessagePack编码](NET/msgpack.md)
- [Groupcast组播](NET/multicast.md)
- [NAT网络地址转换](NET/nat.md)
- [P2P协议](NET/p2p.md)
- [套接字](NET/socket.md)
- [TCP协议](NET/tcp.md)
- [UDP协议](NET/udp.md)
- [WIFI](NET/wifi.md)
- [Windows套接字编程](NET/winsock.md)

---

## [读书笔记](NOTE/README.md)

---

## [操作系统](OS/README.md)

- [COM技术](com.md)
- [编译与链接](compile_and_link.md)
- [守护进程](daemon.md)
- [驱动](drive.md)
- [动态链接](dynamic_link.md)
- [可执行程序](exe.md)
- [文件系统](file_system.md)
- [中断](interrupt.md)
- [文件I/O](io.md)
- [内存管理函数](mem_mgr.md)
- [多处理机系统](multi_processor.md)
- [流水线模型](pipeline.md)
- [posix接口](posix.md)
- [进程，线程和协程](progress_thread_coroutine.md)
- [系统安全](safe.md)
- [信号](signal.md)
- [静态链接](static_link.md)
- [存储器](storage.md)
- [unix系统内核结构](unix_core.md)
- [Windows API](winapi.md)

---

## [杂项](OTHERS/README.md)

- [ASSIC码表](OTHERS/assic_table.md)
- [astyle代码格式化工具](OTHERS/astyle.md)
- [emacs快捷键](OTHERS/emacs_shortcut.md)
- [git教程](OTHERS/git.md)
- [代理设置](OTHERS/proxy.md)
- [重新绑定键](OTHERS/rebind_key.md)
- [正则表达式](OTHERS/regular_expression.md)
- [优秀资源集合](OTHERS/resource_compile.md)
- [vim配置](OTHERS/vim_cfg.md)
- [vim快捷键](OTHERS/vim_shortcut.md)
- [vimium快捷键](OTHERS/vimium_shortcut.md)

模板文件
    
- [测试计划模版](OTHERS/tmpl/benchmark_plan.md)
- [游戏服务器压测报告模版](OTHERS/res/game_server_benchmark_report.md)
- [调研报告模板](OTHERS/tmpl/investigation_research.md)
- [论文模板](OTHERS/tmpl/paper.md)
- [需求文档模板](OTHERS/tmpl/requirements.md)
- [简历模版](OTHERS/tmpl/resume.md)
- [软件测试报告模板](OTHERS/tmpl/soft_test.md)
- [工作日志模版](OTHERS/tmpl/work_note.md)
- [vim配置文件模板](OTHERS/tmpl/.vimrc)
- [别名配置文件](OTHERS/tmpl/.aliases)

---

## [工程实践](PROJ/README.md)

- [软件调试](PROJ/debug.md)
- [运维技巧](PROJ/dev_ops.md)
- [唯一ID的生成](PROJ/id.md)
- [IM系统构建](PROJ/im.md)
- [服务端图形引擎](PROJ/server_graphic_engine.md)
- [软件开发流程](PROJ/software_dev_flow.md)
- [软件测试](PROJ/software_test.md)
- [Token机制](PROJ/token.md)
- [生物科技](PROJ/BIOTECH/README.md)
- [游戏开发](PROJ/GAME/README.md)

### [PBC](PROJ/PBC/README.md)

- [总结](PROJ/PBC/summary.md)

### [OpenSSL](PROJ/OPENSSL/README.md)

- [DES使用示例](PROJ/OPENSSL/ecb.md)
- [环境搭建](PROJ/OPENSSL/env.md)

### [Grpc](PROJ/GRPC/README.md)


### [IPFS](PROJ/IPFS/README.md)

- [总结](PROJ/IPFS/summary.md)
- [命令](PROJ/IPFS/cmd.md)
- [环境配置](PROJ/IPFS/env.md)

源码分析

- [assets](PROJ/IPFS/ansys_assets.md)
- [blocks](PROJ/IPFS/ansys_blocks.md)
- [merkle_dag](PROJ/IPFS/ansys_merkle_dag.md)
- [swarm_key](PROJ/IPFS/ansys_swarm_key.md)

### [Filecoin](PROJ/FILECOIN/README.md)

- [总结](PROJ/FILECOIN/summary.md)
- [fil](PROJ/FILECOIN/fil.md)
- [Lotus安装手册](PROJ/FILECOIN/lotus.md)
- [PDP](PROJ/FILECOIN/pdp.md)
- [PoRep](PROJ/FILECOIN/porep.md)
- [PoRet](PROJ/FILECOIN/poret.md)
- [PoS](PROJ/FILECOIN/pos.md)
- [PoSpace](PROJ/FILECOIN/pospace.md)
- [PoSt](PROJ/FILECOIN/post.md)

### [Ethereum](PROJ/ETH/README.md)

- [总结](PROJ/ETH/summary.md)
- [挖矿难度](PROJ/ETH/difficulty.md)
- [环境搭建](PROJ/ETH/env.md)
- [挖矿可行性分析](PROJ/ETH/mine_analysis.md)
- [挖矿教程](PROJ/ETH/miner.md)

### [Ceph](PROJ/CEPH/READE.md)

- [总结](PROJ/CEPH/summary.md)
- [环境搭建](PROJ/CEPH/env.md)

### [Docker](PROJ/DOCKER/README.md)

- [Docker环境](PROJ/DOCKER/env.md)

### [EOS](PROJ/EOSIO/README.md)

- [常用命令](PROJ/EOSIO/cmd.md)
- [环境配置](PROJ/EOSIO/env.md)
- [EOS合约](PROJ/EOSIO/eos_contract_guide.md)
- [权限](PROJ/EOSIO/permission.md)
- [侧链与搭建](PROJ/EOSIO/side_chain.md)
- [EOS钱包](PROJ/EOSIO/wallet.md)

源码分析

* [action](PROJ/EOSIO/ansys_action.md)
* [contract](PROJ/EOSIO/ansys_contract.md)
* [datastream](PROJ/EOSIO/ansys_datastream.md)
* [eosio.bios合约](PROJ/EOSIO/ansys_eosio.bios.md)
* [eosio.msig合约](PROJ/EOSIO/ansys_eosio.msig.md)
* [eosio.system合约](PROJ/EOSIO/ansys_eosio.system.md)
* [eosio.token合约](PROJ/EOSIO/ansys_eosio.token.md)
* [fc](PROJ/EOSIO/ansys_fc.md)
* [history_api_plugin](PROJ/EOSIO/ansys_history_api_plugin.md)
* [history_plugin](PROJ/EOSIO/ansys_history_plugin.md)
* [name](PROJ/EOSIO/ansys_name.md)
* [net_plugin](PROJ/EOSIO/ansys_net_plugin.md)
* [permission](PROJ/EOSIO/ansys_permission.md)
* [producer_schedule](PROJ/EOSIO/ansys_producer_schedule.md)

### [ZeroMQ](PROJ/ZEROMQ/README.md)

- [总结](PROJ/ZEROMQ/summary.md)
- [libzmq环境配置](PROJ/ZEROMQ/env.md)
- [发布订阅模式](PROJ/ZEROMQ/pub_sub.md)
- [套接字](PROJ/ZEROMQ/socket.md)
- [zmqpp库](PROJ/ZEROMQ/zmqpp.md)
- [ZeroMQ源码分析-mailbox](PROJ/ZEROMQ/ansys_mailbox.md)
- [ZeroMQ源码分析-message](PROJ/ZEROMQ/ansys_message.md)
- [ZeroMQ源码分析-multi_thread](PROJ/ZEROMQ/ansys_multi_thread.md)
- [ZeroMQ源码分析-poller_t](PROJ/ZEROMQ/ansys_poller.md)
- [ZeroMQ源码分析-socket](PROJ/ZEROMQ/ansys_socket.md)
- [ZeroMQ源码分析-ypipe](PROJ/ZEROMQ/ansys_ypipe.md)

### [skynet](PROJ/SKYNET/README.md)

- [总结](PROJ/SKYNET/summary.md)
- [API](PROJ/SKYNET/api.md)
- [最佳实践](PROJ/SKYNET/best_practice.md)
- [集群](PROJ/SKYNET/cluster.md)
- [配置](PROJ/SKYNET/config.md)
- [控制台](PROJ/SKYNET/console.md)
- [环境搭建](PROJ/SKYNET/env.md)
- [GM工具](PROJ/SKYNET/gm.md)
- [热更新](PROJ/SKYNET/hotpatch.md)
- [日志](PROJ/SKYNET/log.md)
- [登录](PROJ/SKYNET/login.md)
- [过载保护](PROJ/SKYNET/overload_protection.md)
- [服务重入](PROJ/SKYNET/reentry.md)
- [序列化](PROJ/SKYNET/serialize.md)
- [snax框架的使用](PROJ/SKYNET/snax.md)
- [SKYNET源码分析-actor模型](PROJ/SKYNET/ansys_actor.md)
- [SKYNET源码分析-数据库](PROJ/SKYNET/ansys_db.md)
- [SKYNET源码分析-网关](PROJ/SKYNET/ansys_gateway.md)
- [SKYNET源码分析-锁](PROJ/SKYNET/ansys_lock.md)
- [SKYNET源码分析-模块机制](PROJ/SKYNET/ansys_modules.md)
- [SKYNET源码分析-消息机制](PROJ/SKYNET/ansys_msg.md)
- [SKYNET源码分析-网络模块](PROJ/SKYNET/ansys_net.md)
- [SKYNET源码分析-服务](PROJ/SKYNET/ansys_server.md)
- [SKYNET源码分析-线程模型](PROJ/SKYNET/ansys_thread.md)
- [SKYNET源码分析-计时器](PROJ/SKYNET/ansys_timer.md)
