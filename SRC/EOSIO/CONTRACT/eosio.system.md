# eosin.system合约



# 摘要

eos的投票以及资产购买,抵押,竞拍,出租,等等; 
购买机制使用的[bancor算法](../../DCS/bancor_protocol.md); 
执行action需要ram,cpu和net，cpu和net需要抵押获得，ram需要购买;用来抵押的物品为eos token; 
ram会消耗;cpu和net用完会退押金; 



# 详情

[eosio.system.hpp](https://github.com/hanjingo/eosio.contracts/blob/master/contracts/eosio.system/include/eosio.system/eosio.system.hpp) 
[exchange_state.hpp](https://github.com/hanjingo/eosio.contracts/blob/master/contracts/eosio.system/include/eosio.system/exchange_state.hpp) 
[native.hpp](https://github.com/hanjingo/eosio.contracts/blob/master/contracts/eosio.system/include/eosio.system/native.hpp) 
[rex.results.hpp](https://github.com/hanjingo/eosio.contracts/blob/master/contracts/eosio.system/include/eosio.system/rex.results.hpp) 
[delegate_bandwidth.cpp](https://github.com/hanjingo/eosio.contracts/blob/master/contracts/eosio.system/src/delegate_bandwidth.cpp) 
[eosio.system.cpp](https://github.com/hanjingo/eosio.contracts/blob/master/contracts/eosio.system/src/eosio.system.cpp) 
[exchange_state.cpp](https://github.com/hanjingo/eosio.contracts/blob/master/contracts/eosio.system/src/exchange_state.cpp) 
[name_bindding.cpp](https://github.com/hanjingo/eosio.contracts/blob/master/contracts/eosio.system/src/name_bidding.cpp) 
[native.cpp](https://github.com/hanjingo/eosio.contracts/blob/master/contracts/eosio.system/src/native.cpp) 
[producer_pay.cpp](https://github.com/hanjingo/eosio.contracts/blob/master/contracts/eosio.system/src/producer_pay.cpp) 
[rex.cpp](https://github.com/hanjingo/eosio.contracts/blob/master/contracts/eosio.system/src/rex.cpp) 
[rex.results.cpp](https://github.com/hanjingo/eosio.contracts/blob/master/contracts/eosio.system/src/rex.results.cpp) 
[voting.cpp](https://github.com/hanjingo/eosio.contracts/blob/master/contracts/eosio.system/src/voting.cpp)  

## 知识点
* `std::enable_if_t`是c++14支持的写法，c++11为`std::enable_if`；当`enable_if`的条件为true时，优先匹配`enable_if`后面的模板；`enable_if_t`是`enable_if`的type；
* `std::optional`类似于智能指针接口,可以显示转化为bool类标识`std::optional`是否有一个值;
* `std::is_same` 判断类型是否一致，位于头文件`<type_traits>`中，两个一样的类型会返回true;
* `1000'000ll` 表示把int型的1000000转为`long long`型;
## 投票
1. 投票前需要抵押eos换取cpu和net,调用`delegatebw`抵押eos;
2. 账号需要调用`regproducer`注册成为生产者节点候选人，别的账号才能给他投票;
3. 账号可以调用`voteproducer`给其他账号投票；
4. 如果不想投票，调用`undelegatebw`取消抵押，但是要3天才能到帐；
5. 投票计分,账号的投票权重与抵押的eos数量正相关；具体的规则看代码; 
***抵押与投票权重转换规则***:$$权重=抵押的资金\times(2^{(自2000年来的周数)\div52})$$

## 购买/出售资源
1. 内存无法抵押获得，只能购买获得;
2. 购买(buyram)或出售(sellram)内存需要收取:0.5%的小费，也就是说完成一次交易需要买卖双方总共需要支付1%的小费;

## 交易所规则
* 外部转交易所: $$实际可购买数量=预定数量\times[(1+支付金额\div供应量)^{小费} -1]$$
* 交易所转外部: $$实际可购买数量=预定数量\times[\sqrt[小费]{1+支付金额\div供应量}-1]$$
## 名字竞拍
竞拍规则:
1. 如果没人抢，直接给竞拍者;
2. 如果有人抢, 出钱多的放到竞拍表,出钱少的放到竞拍退钱表里；

## 生产块
1. 每分钟更新块生产者一次;
2. 在生产区块时，如果出现冲突，先找到全局变量表`eosio_global_state`的`last_producer_schedule_update`(最后一个块生成时间)做比对;

## 领奖
1. 出块有奖励，限制一天只能领取一次；
2. 出块资金分成两部分:一部分给节点，另一部分给eosio.saving；
3. 具体规则看代码

## 名字规则
1. 账号格式:12个字符长,包含:`.`， `1到9`， `a到z`。
2. 如果名字中间含有`.`，则`.`后面必须为创建者名字；比如 abc.def 的创建者是 def。

## 定义内联函数
```c++
//域是否存在, 如果标记F是无符号整型 且 域E是枚举无符号整型
template<typename ER, typename F>
static inline auto has_field( F flag, E field ) -> std::enable_if_t< std::is_integral_v<F> && std::is_unsigned_v<F> &&
					 std::is_enum_v<E> && std::is_same_v< F, std::underlying_type_t<E> >, bool >
{
	return ( (flags & static_cast<F>(field)) != 0 );//静态转换ok
}
//设置域(bool)
template<typename E, typename F>
static inline auto set_field( F flags, E field, bool value = true ) -> std::enable_if_t< std::is_integral_v<F> && std::is_unsigned_v<F> &&
					 std::is_enum_v<E> && std::is_same_v< F, std::underlying_type_t<E> >, F >
{
	if( value )
		return ( flags | static_cast<F>(field) ); 
	else
		return ( flags & ~static_cast<F>(field) );
}
```

## 定义全局变量
|名字|类型|说明|
|:---|:---|:---|
|seconds_per_year|static constexpr uint32_t|`52*7*24*3600`, 每一年的秒数|
|seconds_per_day|static constexpr uint32_t|`24*3600`, 每天的秒数|
|seconds_per_hour|static constexpr uint32_t|3600, 每小时的秒数|
|useconds_per_year|static constexpr int64_t|`int64_t(seconds_per_year) * 1000' 000ll`, 每年的微秒数|
|useconds_per_day|static constexpr int64_t|`int64_t(seconds_per_day) * 1000' 000ll`, 每天的微秒数|
|useconds_per_hour|static constexpr int64_t|`int64_t(seconds_per_hour) * 1000' 000ll`, 每小时的微秒数|
|blocks_per_day|static constexpr uint32_t|`2*seconds_per_day`, 1秒钟产生2个块|
|min_activated_stake|static constexpr int64_t|`150'000'000'0000`， 最小活跃抵押,更新投票时用|
|ram_gift_bytes|static constexpr int64_t|`1400`, 内存数据包大小|
|min_pervote_daily_pay|static constexpr int64_t|`100'0000`, 最小日级平均投票|
|refund_delay_sec|static constexpr uint32_t |`3 * seconds_per_day`, 资金返还延时，3天|
|inflation_percision| static constexpr int64_t|`100`, 通胀系数,2个小数点|
|default_annual_rate|static constexpr int64_t|`500`, 默认年利率|
|pay_factor_percision| static constexpr int64_t|`10000`, ?|
|default_inflation_pay_factor|static constexpr int64_t|`50000`,  默认通胀倍数|
|default_votepay_factor| static constexpr int64_t|`40000`, 默认投票倍数|

## 定义action
|接口|参数|说明|
|:-----|:------|:----|
|init|- `unsigned_init` 版本<br>- `const symbol&` 系统货币|初始化|
|onblock|`ignore<block_header>` 块头|更新块|
|setalimits|- `const name&` 账号<br>- int64_t 内存字节大小<br>- int64_t 网络资源<br>- int64_t cpu资源|设置账号资源限制|
|setacctram|- `const name&` 账号<br>- `const std::optional<int64_t>&` 内存限制|设置内存限制|
|setacctnet|- `const name&` 账号<br>- `const std::optional<int64_t>&` 网络限制|设置网络限制|
|setacctcpu|- `const name&` 账号<br>- `const std::optional<int64_t>&` cpu限制|设置cpu限制|
|activate|`const eosio::checksum256&` 特征摘要|激活协议|
|delegatebw|- `const name&` 抵押者<br>- `const name&:token` 接收者<br>- `const asset&` 获得的网络<br>- `const asset&` 获得的cpu<br>- `bool` 是否发生交易|抵押token，获取net和cpu|
|setrex|`const asset&` 数量|设置资源代币数量|
|deposit|- `const name&` 用户<br>- `const asset&` 数量|交定金|
|withdraw|- `const name&` 资金拥有者<br>- `const asset&` 资金数量|从资金池撤回资产|
|buyrex|- `const name&` 购买者<br>- `const asset&` 资金数量|购买资源代币|
|unstaketorex|- `const name&` 退货人<br>- `const name&` 接受者<br>- `const asset&` 网络<br>- `const asset&` cpu|取消抵押资源代币并退钱|
|sellrex|- `const name&` 出售者<br>- `const asset&` 资金数量|出售资源代币|
|cnclrexorder|`const name&` 调用人|取消资源代币订单|
|rentcpu|- `const name&` 出租者<br>- `const name&` 接收者<br>- `const asset&` 出租花费<br>- `const asset&` 出租退费|出租cpu|
|rentnet|- `const name&` 出租者<br>- `const name&` 接收者<br>- `const asset&` 出租花费<br>- `const asset&` 出租退费|出租网络|
|fundcpuloan|- `const name&` 出租者<br>- `uint64_t` 出租数量<br>- `const asset&` 花费|cpu出租打钱|
|fundnetloan|- `const name&` 出租者<br>- `uint64_t` 出租数量<br>- `const asset&` 花费|net出租打钱|
|defcpuloan|const name& 出租者, uint64_t 出租数量, const asset& 价格|定义cpu出租价格|
|defnetloan|const name& 出租者, uint64_t 出租数量, const asset& 价格|定义net出租价格|
|updaterex|const name& 用户|更新用户资源代币|
|rexexec|const name& 用户, uint16_t 最大订单数|处理cpu,net,rex出租订单|
|consolidate|const name& 收款人|应付款到期合并|
|mvtosavings|const name& 收款人, const asset& 金额|删除应付款|
|mvfrsavings|const name& 收款人, const asset& 金额|添加应付款|
|closerex|const name& 持有人|删除代币|
|undelegatebw|const name& 押金持有人, const name& 押金抵押者, const asset& 抵押的net, const asset& 抵押的cpu|取消抵押|
|buyram|const name& 买家, const name& 卖家, const asset& 内存数量|购买内存|
|buyrambytes|const name& 买家, const name& 卖家, uint32_t 字节数|购买指定大小内存,使用的bancor算法,内存与资金的兑换比率浮动变化;收0.5%的小费|
|sellram|const name& 卖家, int64_t 内存大小|出售内存,需要0.5%的小费|
|refund|const name& 收款人|退款,有3天的延时|
|regproducer|const name& 节点, const public_key& 节点公钥, const std::string& 节点地址, uint16_t 所属国家	|注册节点|
|regproducer2|const name& 节点, const eosio::block_signing_authority& 权限, const std::string& 地址, uint16_t 所属国家|注册节点2|
|unregprod|const name& 生产者名字|取消注册生产者|
|setram|uint64_t 内存大小|设置提供的内存大小|
|setramrate|uint16_t 每个块的内存大小|设置每个块内存增长速率,影响内存供应|
|voteproducer|const name& 投票人, const name& 账户代理人, const std::vector<name>& 节点集合|投票生产者节点，可以投给多人|
|regproxy|const name& 代理人, bool 是否使用了代理|注册代理人，已经使用了代理的投票者不能注册未投票代理|
|setparams|const eosio::blockchain_parameters& 参数|设置系统参数|
|claimrewards|const name& 节点|节点领奖|
|setpriv|const name& 账号, uint8_t 是否开启特权|设置特权开启,0不开,>0开启|
|rmvproducer|const name& 节点|让一节点失效|
|updtrevision|uint8_t 新的版本|更新版本|
|bidname|const name& 竞拍者, const name& 新名字, const asset& 竞拍资金|竞拍抢名字|
|bidrefund|const name& 竞拍者, const name& 新名字|竞拍退款|
|newaccount|const name& 创建者, const name& 要创建的名字, ignore<authority> owner权限, ignore<authority> active权限|新建账号；1.账号格式:12个字符长,不包含"."; 2.新账号创建时必须购买一个最小单位的内存|
|updateauth|ignore<name> 账号, ignore<name> 权限, ignore<name> 账号的父账号，调用次action的人, ignore<authorith> 此action的调用权限|更新账号的权限|
|deleteauth|ignore<name> 账号, ignore<name> 权限|删除权限|
|linkauth|ignore<name> 调用者账号, ignore<name> 被授权人, ignore<name> 被赋值的action, ignore<name>权限|给一个action赋予权限,有5个action: updateauth, deleteauth, linkauth, unlinkauth, canceldelay;不能被赋权|
|unlinkauth|ignore<name> 调用者账号, ignore<name> 被授权人, ignore<name>|被取消的action	取消授权|
|canceldelay|ignore<permission_level> 权限, ignore<checksum256> 传输id|取消延时传输|
|onerror|ignore<uint128_t> 发送者, ignore<std::vector<char>> 传输id|报错|
|setabi|const name& 账号, const std::vector<char>& abi|设置合约abi|
|setcode|const name& 部署者, uint8_t 虚拟机类型, uint8_t 虚拟机版本, const std::vector<char>& 合约内容|设置合约|
|setinflation|int64_t 年率, int64_t 通胀系数, int64_t 投票系数|设置通胀率|

## 定义私有函数
|函数|参数|说明|
|:-----|:---|:---|
|static symbol **get_core_symbol**|const rammarket& rm:交易所|返回ram交易所的货币类型|
|static eosio_global_state **get_default_parameters**|-|返回默认的全局变量表|
|static eosio_blobal_state4 **get_default_inflation_parameters**|-|返回默认的全局变量表4的信息|
|symbol **core_symbol**()const|-|返回货币类型|
|void **update_ram_supply**|-|更新ram供应量|
|void **runrex**|uint16_t max:3种资源的最大数量(net, cpu, 代币出售订单|执行代币动作(买net,买cpu,出售代币...)|
|void **update_rex_pool**|-|更新代币池|
|void **update_resource_limits**|const name& from: 记账人, const name& receiver:需要变更者, int64_t delta_net:net资源, int64_t delta_cpu:cpu资源 |更新账号资源限制|
|void **check_voting_requirement**|const name& owner:代币持有者, const char* error_msg:返回错误|是否可以买代币,只有生产者大于21个或它是一个代理才可以买代币; |
|rex_order_outcome **fill_rex_order**|const rex_balance_table::const_iterator& bitr:迭代器, const asset& rex:代币|撮合代币订单|
|asset **update_rex_account**|const name& owner:账号, const asset& proceeds:转到个人代币表的数量, const asset& delta_stake 抵押的数目(用来增加权重), bool force_vote_update:是否强制更新投票权)|更新账号代币|
|void **channel_to_rex**|const name& from:转账者, const asset& amount 数量|代币渠道转账|
|void **channel_namebid_to_rex**|const int64_t highest_bid:最高出价|账号竞拍代币转账|
|template <typename T> int64_t **rent_rex**|T& table 记录表, const name& from 出租人, const name& receiver 购买者, const asset& loan_payment 小费, const asset& loan_fund 出租的代币资产|出租代币|
|template <typename T> void **fund_rex_loan**|T& table 记录表, const name& from 借出人, uint64_t loan_num 借出数目, const asset& payment 小费|出借代币|
|void **defund_rex_loan**|T& table 记录表, const name& from 借款人, uint64_t loan_num 借出资金数目, const asset& amount 借出的资金|收回借出的代币|
|void **transfer_from_fund**|const name& owner 拥有者, const asset& amount 资金|从代币资金表转资金出来|
|void **transfer_to_fund**| const name& owner 拥有者, const asset& amount 资金|将资金转入代币资金表|
|bool **rex_loans_available**()const|-|是否可以借贷代币,如果代币池有效且没有订单或订单已结束，返回true|
|bool **rex_system_initialized**()const { return _rexpool.begin() != _rexpool.end(); }|-|代币系统是否已经初始化|
|bool **rex_available**()const { return rex_system_initialized() && _rexpool.begin()->total_rex.amount > 0; }|-|代币池是否有代币|
|static time_point_sec **get_rex_maturity**|-|计算购买代币4天后到期时间的秒数|
|asset **add_to_rex_balance**|const name& owner 代币所有者, const asset& payment 小费, const asset& rex_received 购买的代币|添加代币到代币现金表,返回所有抵押的代币数量|
|asset **add_to_rex_pool**|const asset& payment 代币|添加代币到代币池,比率:10000, 代币池代币总额为:200000000|
|void **add_to_rex_return_pool**|const asset& fee 代币|添加代币到代币返还表|
|void **process_rex_maturities**|const rex_balance_table::const_iterator& bitr 迭代器|更新代币已到期的桶|
|void **consolidate_rex_balance**|`const rex_balance_table::const_iterator& bitr` 桶迭代器<br>const asset& rex_in_sell_order 正在出售的代币订单|把所有代币到期桶合并到一个桶(排除掉正在出售的代币)|
|int64_t **read_rex_savings**|`const rex_balance_table::const_iterator& bitr` 代币桶迭代器|取一个正在存储的桶|
|void **put_rex_savings**|`const rex_balance_table::const_iterator& bitr` 迭代器<br>int64_t rex 待添加的代币数量|放一个详细的代币数量到过期桶里面去|
|void **update_rex_stake**|`const name& voter` 投票人|更新投票人代币抵押|
|void **add_loan_to_rex_pool**|`const asset& payment` 本次借贷的小费<br>`int64_t rented_tokens` 借贷人抵押的token<br>`bool new_loan` 是否是新的订单|创建新的借贷或激活旧的订单|
|void **remove_loan_from_rex_pool**| `const rex_loan& loan` 借贷记录 |从代币池表移除指定借贷记录|
|template <typename Index, typename Iterator> int64_t **update_renewed_loan**|`Index& idx` 索引<br>`const Iterator&` itr 迭代器<br>`int64_t rented_tokens` 出租的token|更新订单|
|void **changebw**|`name from` 变更者<br>`const name& receiver` 接收者<br>`const asset& stake_net_quantity` 抵押的net数量<br>`const asset& stake_cpu_quantity` 抵押的cpu数量<br>`bool transfer` |变更带宽|
|void **update_voting_power**|`const name& voter` 投票人<br>`const asset& total_update` 投票权变更值|更新投票权|
|void **register_producer**|`const name& producer` 生产者<br>`const eosio::block_signing_authority& producer_authority` 生产者签名验证<br>`const std::string& url` 生产者地址<br>uint16_t location 生产者所属国家|注册成为生产者|
|void **update_elected_producers**|`const block_timestamp& timestamp `更新的时间|更新生产者选举|
|void **update_votes**|`const name& voter` 投票人<br>`const name& proxy` 代理人<br>`const std::vector<name>& producers` 生产者<br>bool voting 是否在投票中|更新投票信息|
|void **propagate_weight_change**|`const voter_info& voter` 投票人|传播投票变更|
|double **update_producer_votepay_share**|`const producers_table2::const_iterator& prod_itr , const time_point& ct , double shares_rate , bool reset_to_zero` |更新生产者投票股份|
|double **update_total_votepay_share**|`const time_point& ct, double additional_shares_delta , double shares_rate_delta` |更新总投票股份|

## 定义table
#### name_bid 名字竞拍表
|类型|名字|注释|
|:---|:---|:---|
|name|newname|新的名字|
|name|high_bidder|最高出价者|
|int64_t|high_bid|价格|
|time_point|last_bid_time|最后一次出价时间|
|func|primary_key|主键|
|func|by_high_bid|分索引|

#### bid_refund 竞拍退款表
|类型|名字|注释|
|:---|:---|:---|
|name|bidder|竞拍者|
|asset|amount|资产|

#### eosio_global_state 全局变量表
|类型|名字|注释|
|:---|:---|:---|
|uint64_t|max_ram_size|最大内存大小 64GB|
|uint64_t|total_ram_bytes_reserved = 0|可用内存大小|
|int64_t|total_ram_stake = 0|总内存抵押大小|
|block_timestamp|last_producer_schedule_update|最后一个块生成时间|
|time_point|last_pervote_bucket_fill|最后一次投入桶时间|
|int64_t|pervote_bucket = 0|每次投票的奖励|
|int64_t|perblock_bucket = 0|每次出块的奖励|
|uint32_t|total_unpaid_blocks = 0|总未支付的块|
|int64_t|total_activated_stake = 0|总有效的抵押|
|time_point|thresh_activated_stake_time|上次更新抵押的时间|
|uint16_t|last_producer_schedule_size|上一个生产者调度任务大小|
|double|total_producer_vote_weight|生产者的投票权重|
|block_timestamp|last_name_close|上次出块时间|
|func|`uint64_t free_ram()const {  return max_ram_size - total_ram_bytes_reserved; }`|释放内存|

#### eosio_global_state2 全局变量表2
|类型|名字|注释|
|:---|:---|:---|
|uint16_t|new_ram_per_block= 0|每个块分配内存|
|block_timestamp|last_ram_increase|上一次内存增长时间|
|block_timestamp|last_block_num|上次出块时间(不建议使用)|
|double|total_producer_votepay_share = 0|总生产者投票股份|
|uint8_t|revision = 0|修订后的版本号, 最大256|

#### eosio_global_state3 全局变量表3
|类型|名字|注释|
|:---|:---|:---|
|time_point|last_vpay_state_update|上一次投票状态更新时间|
|double|total_vpay_share_change_rate = 0|总投票权重变更速率|

#### eosio_global_state4 全局变量表4
|类型|名字|注释|
|:---|:---|:---|
|double|continuous_rate|持续率|
|int64_t|inflation_pay_factor|通胀倍数|
|int64_t|votepay_factor|投票倍数|

#### producer_info 生产者信息表
|类型|名字|注释|
|:---|:---|:---|
|name|owner|生产者名字|
|double|total_votes = 0|总投票数|
|eosio::public_key|producer_key|生产者key|
|bool|is_active = true|是否活跃|
|std::string|url|网址|
|uint32_t|unpaid_blocks = 0|未支付的块数量|
|time_point|last_claim_time|上一次领取时间|
|uint16_t|location = 0|所属地区|
|`eosio::binary_extension<eosio::block_signing_authority>`|producer_authority|生产者权限验证|

#### producer_info2 生产者信息表2
|类型|名字|注释|
|:---|:---|:---|
|name|owner|生产者名字|
|double|votepay_share = 0|投票股份|
|time_point|last_votepay_share_update|上一次投票股份变更时间|
|func|`uint64_t primary_key()const { return owner.value }`|主键|

#### voter_info 投票者信息表
|类型|名字|注释|
|:---|:---|:---|
|name|owner|投票人|
|name|proxy|代理人|
|std::vector<name>|producers|生产者集合|
|int64_t|staked = 0|抵押的token数量|
|double|last_vote_weight = 0|上一次投票资产|
|double|proxied_vote_weight = 0|代理人投票区资产|
|bool|is_proxy = 0|是否是代理人|
|uint32_t|flags1 = 0|标记 ram:1 net:2 cpu:4|
|uint32_t|reserved2 = 0|(无用)|
|eosio:asset|reserved3|(无用)|

#### user_resources 用户资源表
|类型|名字|注释|
|:---|:---|:---|
|name|owner|拥有者|
|asset|net_weight|网络资产|
|asset|cpu_weight|cpu资产|
|int64_t|ram_bytes|内存大小|
|func|`bool is_empty()const {  return net_weight.amount == 0 && cpu_weight.amount == 0 && ram_bytes == 0; }`|net,cpu和ram是否都为空|
|func|`uint64_t primary_key()const { return owner.value; }`|主键|

#### delegated_bandwidth 带宽委托表
|类型|名字|注释|
|:---|:---|:---|
|name|from|发起者|
|name|to|接收者|
|asset|net_weight|net资产|
|asset|cpu_weight|cpu资产|
|func|`bool is_empty()const { return net_weight.amount == 0 && cpu_weight.amount == 0; }`|是否网络和cpu资源为空|
|func|`uint64_t primary_key()const { return to.value; }`|主键|

#### refund_request 请求退款表
|类型|名字|注释|
|:---|:---|:---|
|name|owner|拥有者名字|
|time_point_sec|request_time|请求时间|
|`eosio::asset`|net_amount|网络资产|
|`eosio::asset`|cpu_amount|cpu资产|

#### rex_pool 代币池表
|类型|名字|注释|
|:---|:---|:---|
|uint8_t|version|版本|
|asset|total_lent|所有已借出资产|
|asset|total_unlent|所有未借出资产|
|asset|total_rent|租金|
|asset|total_lendable|所有代币,已借出资产+未借出资产|
|asset|total_rex|rex总额|
|asset|namebid_proceeds|名字竞拍者出资|
|uint64_t|loan_num|贷款数量|

#### rex_return_pool 代币退还池表
|类型|名字|注释|
|:---|:---|:---|
|uint8_t|version|版本|
|time_point_sec|last_dist_time|最后一次返还资金时间|
|time_point_sec|pending_bucket_time|0xffffffff 秒,12小时,资金返还桶装满时间|
|time_point_sec|oldest_bucket_time|0, 12小时,最老的资金返还桶时间|
|int64_t|pending_bucket_proceeds|0,等待处理的桶子数|
|int64_t|current_rate_of_increase|0, 过期速率|
|int64_t|proceeds|0, 已处理|
|static constexpr uint32_t|total_intervals|30 * 144 = 30天，最大时长|
|static constexpr uint32_t|dist_interval|10 * 60, 10分钟|
|static constexpr uint8_t|hours_per_bucket|12, 每个桶子的时长|

#### rex_fund 代币资金表
|类型|名字|注释|
|:---|:---|:---|
|uint8_t|version|版本|
|name|owner|代币拥有者|
|asset|balance|代币数量|
|func|`uint64_t primary_key()const { return owner.value; }`|主键|

#### rex_return_buckets 代币进项积累表
|类型|名字|注释|
|:---|:---|:---|
|uint8_t|version|版本|
|`std::map<time_point_sec, int64_t>`|return_buckets|12小时内进项桶|
|func|`uint64_t primary_key()const{return 0;}`|主键|

#### rex_balance 代币现金表
|类型|名字|注释|
|:---|:---|:---|
|uint8_t|version|0, 版本|
|name|owner|rex现金持有者|
|asset|vote_stake|投票股份|
|asset|rex_balance|REX现金数量|
|int64_t|matured_rex|可出售的rex|
|`std::deque<std::pair<time_point_sec, int64_t>>`|rex_maturities|代币每天出售的桶队列|
|func|`uint64_t primary_key()const { return owner.value; }`|主键|

#### rex_loan 代币出租表 
|类型|名字|注释|
|:---|:---|:---|
|uint8_t|version|0， 版本|
|name|from|出租者|
|name|receiver|租户|
|asset|payment|支付的SYS tokens|
|asset|balance|可用来续租的SYS tokens|
|asset|total_staked|押金|
|uint64_t|loan_num|出租的rex数量|
|eosio::time_point|expiration|交易过期时间|
|func|uint64_t primary_key()cosnt { return loan_num; }|主键|
|func|uint64_t by_expr()const { return expiration.elapsed.count(); }|分索引1|
|func|uint64_t by_owner()const { return from.value }|分索引2|

#### rex_order 代币订单表
|类型|名字|注释|
|:---|:---|:---|
|uint8_t|version|0, 版本|
|name|owner|持有者|
|asset|rex_requested|请求的代币数量|
|asset|proceeds|订单数量|
|asset|stake_change|押金数量|
|eosio::time_point|order_time|	订单创建时间|
|bool|is_open|true, 订单是否有效|
|func|`void close() {is_open = false;}`|关闭订单|
|func|`uint64_t primary_key() const {return owner.value}`|主键|
|func|`uint64_t by_time()const {return is_open ? order_time.elapsed.count() : std::numeric_limits<uint64_t>::max();}`|分索引|
```c++
//代币订单处理结果
struct rex_order_outcome {
	bool success; 		//是否成功
	asset proceeds; 	//处理的数量
	asset stake_change; //抵押变更
};
```

#### abi_hash abi表
|类型|名字|注释|
|:---|:---|:---|
|name|owner|拥有者|
|checksum256|hash|hash|

#### exchange_state 交易所
```c++
struct connector {
    asset balance,      //储备金余额
    double weight = 5,  //小费
}
```
|类型|名字|注释|
|:---|:---|:---|
|asset|supply|供应量|
|connector|base|原价|
|connector|quote|出价|
|func|`uint64_t primary_key()const {  return supply.symbol.raw(); }`|主键|
|func|`asset convert_to_exchange( connector& reserve, const asset& payment)`|reserve:预定量，payment:支付金额,; 转成交易所价格; $$实际可购买数量=预定数量\times[(1+支付金额\div供应量)^{小费} -1]$$|
|func|`asset convert_from_exchange(  connector& reserve, const asset& tokens )`|reserve:预定量，payment:支付金额；从交易所价格转回实际价格  $$实际可购买数量=预定数量\times[\sqrt[小费]{1+支付金额\div供应量}-1]$$|
|func|`asset covert(  const asset& from, const symbol& to )`|汇率转换,流程:1.convert_to_exchange到交易所，2.convert_from_exchange从交易所转回来|
|func|`asset direct_convert( const asset& from, const symbol& to )`|用 [bancor算法](https://blog.csdn.net/qq_27304213/article/details/107299373) 计算价格，并设置实时价格|
|func|`static int64_t get_bancor_output( int64_t inp_reserve, int64_t out_reserve, int64_t inp)`|获得bancor输出|
|func|`static int64_t get_bancor_input(int64_t out_reserve, int64_t inp_reserve, int64_t out)`|获得bancor输入|

## 定义类
#### permission_level_weight 等级权限
|类型|名字|注释|
|:---|:---|:---|
|permission_level|permission|等级|
|uint16_t|weight|权重|

#### key_weight 键权重
|类型|名字|注释|
|:---|:---|:---|
|`eosio::public_key`|key|键|
|uint16_t|weight|权重|

#### wait_weight 等待时间权重
|类型|名字|注释|
|:---|:---|:---|
|uint32_t|wait_sec|等待秒数|
|uint16_t|weight|权重|

#### authority 权限验证
|类型|名字|注释|
|:---|:---|:---|
|uint32_t|threshold|0, 起点|
|`std::vector<key_weight>`|keys|key权重|
|`std::vector<permission_level_weight>`|accounts|权限等级权重|
|`std::vector<wait_weight>`|waits|等待权重|

#### block_header 块头
|类型|名字|注释|
|:---|:---|:---|
|uint32_t|timestamp|时间戳|
|name|producer|块头生产者|
|checksum256|previous|上一个块|
|checksum256|transaction_mroot|只想transaction根节点|
|checksum256|action_mroot|指向action根节点|
|uint32_t|schedule_version|0, 调度器版本|
|`std::optional<eosio::producer_schedule>`|new_producers|新的生产者|

## rex.results合约
```c++
//购买结果
void buyresult( const asset& rex_received )
//出售结果
void sellresult( const asset& proceeds )
//预订结果
void orderresult( const name& owner, const asset& proceeds )
//出租结果
void rentresult( const asset& rented_tokens )
```
