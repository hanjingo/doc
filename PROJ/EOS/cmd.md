# eos命令行

[TOC]



## 查询
|用途|实现|
|:--|:--|
|查看钱包列表|cleos wallet list|
|查看钱包密钥列表|cleos wallet keys|
|查看合约部署情况|cleos get table eosio eosio abihash|
|查看节点信息|cleos get table 部署者账号 scope(默认部署者账号) producers|
|查看节点调度信息|cleos get schedule -j|
|查看账号token信息|cleos get currency balance eosio.token 账号名|



## 合约部署&执行

|用途|实现|
|:--|:--|
|发布合约|cleos set contract 账号 dapp地址 -p 账号@active|
|清除合约|cleos set contract 合约部署者账号 -c|
|抵押net,cpu,内存|cli-baz system delegatebw 给钱的人 受益人 "用来买net而抵押的钱" "用来买cpu而抵押的钱" --transfer --buyram "要买的内存"|



## 钱包&账号

|用途|实现|
|:--|:--|
|创建钱包|cleos wallet create --to-console -n 钱包名字|
|打开钱包|cleos wallet open -n 钱包名字|
|解锁钱包|cleos wallet unlock -n 钱包名字|
|将私钥导入钱包|cleos wallet import -n 钱包名字 --private-key 私钥|
|创建公钥|cleos create key --to-console|
|创建账号|cleos create account 创建者账号 账号 公钥|