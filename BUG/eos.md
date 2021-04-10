# eos开发常见错误



## 脏数据问题  

database dirty flag set (likely due to unclean shutdown) replay or resync required  

解决方法:

在nodeos启动时添加选项--hard-replay-blockchain或者--delete-all-blocks参数  



## eos无法启动:  

eos无法启动

解决方法:

把启动选项--producer-name eosio的eosio改成自己账号名，不然会启动不了  



## Error 3090003:

创建账户时报错:Provided keys, permissions, and delays do not satisfy declared authorizations  

解决方法:  

系统私钥在 2个位置都可以找到：

> 1. 启动选项: --signature-provider EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV=KEY:5KQwrPbwdL6PhXujxW37FSSQZ1JiwsST4cqQzDeyXtP79zkvFD3 这里 =KEY:的后面那一段
>
> 2. 在nodeos的配置文件（ubuntu默认路径：~/.local/share/eosio/nodeos/config/config.ini）=KEY:的后面那一段   

找到后将私钥导入钱包：cleos wallet import -n 钱包名  --private-key 5KQwrPbwdL6PhXujxW37FSSQZ1JiwsST4cqQzDeyXtP79zkvFD3



## fetching abi for undefined: unknown key (eosio::chain::name):

```shell
6|app  | 11-24 11:25:31: Error: fetching abi for undefined: unknown key (eosio::chain::name):
6|app  | 11-24 11:25:31:     at new RpcError (/data/api_server/node_modules/eosjs/dist/eosjs-rpcerror.js:26:28)
6|app  | 11-24 11:25:31:     at JsonRpc.<anonymous> (/data/api_server/node_modules/eosjs/dist/eosjs-jsonrpc.js:118:35)
6|app  | 11-24 11:25:31:     at step (/data/api_server/node_modules/eosjs/dist/eosjs-jsonrpc.js:36:23)
6|app  | 11-24 11:25:31:     at Object.next (/data/api_server/node_modules/eosjs/dist/eosjs-jsonrpc.js:17:53)
6|app  | 11-24 11:25:31:     at fulfilled (/data/api_server/node_modules/eosjs/dist/eosjs-jsonrpc.js:8:58)
6|app  | 11-24 11:25:31:     at process._tickCallback (internal/process/next_tick.js:68:7)
```

eosjs调用接口时，报错;因为多打了一个 } 囧

原来的代码:
```typescript
let actions = {
            actions: [{
                account: eosConfig.CONTRACT_DEPLOYER,
                name: 'adddevice',
                authorization: [{
                    actor:acc,
                    permission: 'active',
                }],
                data:{
                    carrier: operators, //运营商
                    account: acc, //设备名字
                    telephone: phone, //电话
                    longitude: longitude, //经度
                    latitude: latitude, //纬度
                    place_name: place, //小区名
                    address: addr, //地址
                    is_enable: enable, //是否启用
                    id: id
                }
            }]
        }
        const result = await api.transact({ actions: [ actions ]}, {
            blocksBehind: 3,
            expireSeconds: 30,
        });
```

修改后:
```typescript
let actions = {
            actions: [{
                account: "collection",
                name: 'adddevice',
                authorization: [{
                    actor:'carrier1',
                    permission: 'active',
                }],
                data:{
                    carrier: 'carrier1', //运营商
                    account: 'carrier1', //设备名字
                    telephone: '123456', //电话
                    longitude: longitude, //经度
                    latitude: latitude, //纬度
                    place_name: place, //小区名
                    address: addr, //地址
                    is_enable: enable, //是否启用
                    id: id
                }
            }]
        }
        const result = await api.transact( actions, {
            blocksBehind: 3,
            expireSeconds: 30,
        });

```



## Error 3080004: Transaction exceeded the current CPU usage limit imposed on the transaction

命令执行超时了，在命令行后面加上 +x n(任意<=3600的正数，表示秒数) 就可以了,例: 

```sh
cleos push action eosio fuck '' -p eosio +x 100
```



## eos合约被冲掉的问题

一个eos账号只能部署一个合约，先部署合约a，再部署合约b；会导致合约a被合约b替换掉,嗦嗨!!!