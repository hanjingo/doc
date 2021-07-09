# 摘要
插件功能：
1. 负责端点的连接与断开，状态管理；
2. 请求块，验证块，处理块；

# 详情
[net_plugin.hpp](https://github.com/hanjingo/eos/blob/master/plugins/net_plugin/include/eosio/net_plugin/net_plugin.hpp)
[net_plugin.cpp](https://github.com/hanjingo/eos/blob/master/plugins/net_plugin/net_plugin.cpp)
[protocol.hpp](https://github.com/hanjingo/eos/blob/master/plugins/net_plugin/include/eosio/net_plugin/protocol.hpp)  

## 定义类
#### net_plugin 网络插件类
|类型|名称|注释|
|:---|:---|:---|
|func|string connect( const string& endpoint )|连接端点 endpoint|
|func|string disconnect( const string& endpoint )|断开与endpoint的连接|
|func|optional< connection_status > status( const string& endpoint ) const|返回与endpoint的状态|
|func|vector< connection_status > connections() const|返回所有的连接|

#### sync_manager 同步管理类
|类型|名称|注释|
|:---|:---|:---|
|func|constexpr static auto stage_str( stages s )|返回状态string|
|func|void set_state( stages s )|设置状态|
|func|bool is_sync_required( uint32_t fork_head_block_num )|头块号是否是同步请求的|
|func|void request_next_chunk( std::unique_lock< std::mutex > g_sync, const connection_ptr& conn = connection_ptr() )|请求下一个块; 1.如果当前块不存在：使用传进来的conn 2.如果当前连接数为0:重置同步源 3.如果找不到同步源对应的连接:拿连接集合中的第一个 4.如果上一个请求的块号！=已知请求的块号（说明同步不一致）:请求同步块|
|func|start_sync( const connection_ptr& c, uint32_t target )|开启同步|
|func|verify_catchup( const connection_ptr& c, uint32_t num, const block_id_type& id )|发送握手|
|func|bool syncing_with_peer() const { return sync_state == lib_catchup; }|同步peer|
|func|void sync_reset_lib_num( const connection_ptr& conn )|同步重置块号(如果上一个确定的块号 > 已知同步的块号,赋值给已知同步的块号)|
|func|void sync_reassign_fetch( const connection_ptr& c, go_away_reason reason )|同步重新指定fetch|
|func|void rejected_block( const connection_ptr& c, uint32_t blk_num )|拒绝块(如果拒绝的数目超过最大块数限制,重置同步源)|
|func|void sync_recv_block( const connection_ptr& c, const block_id_type& blk_id, uint32_t blk_num, bool blk_applied )|同步接收块|
|func|void sync_update_expected( const connection_ptr& c, const block_id_type& blk_id, uint32_t blk_num, bool blk_applied )|同步更新指定块(如果指定的块号不是默认下一个要请求的块号，就赋值给它)|
|func|void recv_handshake( const connection_ptr& c, const handshake_message& msg )|接收握手消息|
|func|void sync_recv_notice( const connection_ptr& c, const notice_message& msg )|同步接收通知消息|

#### dispatch_manager 递送管理器
|类型|名称|注释|
|:---|:---|:---|
|boost::asio::io_context::strand|strand|确定多线程执行顺序|
|func|void bcast_transaction( const packed_transaction& trx )|广播传输块|
|func|rejected_transaction( const packed_transaction_ptr& trx, uint32_t head_blk_num )|拒绝传输块|
|func|void bcast_block( const signed_block_ptr& b, const block_id_type& id )|广播块(线程安全，先看看块id存不存在，不存在就广播)|
|func|void bcast_notice( const block_id_type& id )|广播通知|
|func|void rejected_block( const block_id_type& id )|拒绝块|
|func|void recv_block( const connection_ptr& conn, const block_id_type& msg, uint32_t bnum )|接受块|
|func|void expire_blocks( uint32_t bnum )|传输过期块(删掉到目前为止已过期的传输块)|

#### net_plugin_impl 网络插件实现类
|类型|名称|注释|
|:---|:---|:---|
|func|void update_chain_info()|更新链信息(只由主程序线程调用)|
|std::tuple< uint32_t, uint32_t, uint32_t, block_id_type, block_id_type, block_id_type > get_chain_info() const|获得链信息|
|func|void start_listen_loop()|开始监听|
|func|void on_accepted_block( const block_state_ptr& bs )|接受块|
|func|void on_pre_accepted_block( const signed_block_ptr& bs )|预接受块|
|func|void transaction_ack( const std::pair< fc::exception_ptr, transaction_metadata_ptr >& blk )|固定块，调用update_chain_info|
|func|void start_conn_timer(boost::asio::steady_timer::duration du, std::weak_ptr< connection > from_connection )|开启连接计时器|
|func|void start_expire_timer()|开启过期计时器(线程安全)|
|func|void start_monitors()|开启监视器|
|func|void expire()|过期|
|func|connection_monitor( std::weak_ptr<connection> from_connection, bool reschedule )|连接管理器(1ms检查一次，如果连接不可用，删除它)|
|func|void ticker()|节点心跳滴答|
|func|bool authenticate_peer( const handshake_message& msg ) const|验证握手信息，判定是否可以连接|
|func|chain::public_key_type get_authentication_key() const|获得公钥|
|func|chain::signature_type sign_compact( const chain::public_key_type& signer, const fc::sha256& digest ) const|合约签名(签名器，签名摘要)|
|func|constexpr uint16_t to_protocol_version( uint16_t v )|
|func|connection_ptr find_connection( const string& host ) const|根据host找到连接|

## 定义协议 net_message
|协议名|注释|
|:----_|:---|
|handshake_message|握手信息|
|chain_size_message|链大小信息|
|go_away_message|离开消息|
|time_message|时间信息|
|notice_message|通知消息|
|request_message|请求消息|
|sync_request_message|同步请求消息|
|signed_block|已签名块消息|
|packed_transaction|已打包的传输消息|

## 定义表
#### node_transaction_index 传输表
#### peer_block_state_index 节点块表
