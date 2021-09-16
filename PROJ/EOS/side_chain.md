# EOS侧链
eos的侧链搭建，账号设置;



## 锚定模式

* 单一托管模式：通过一个中心化第三方完成交互，资产托管给第三方，第三方再来操作侧链；
* 联盟模式：使用公证人联盟取代单一的第三方；
* spv模式：将资产放在主链某一位置，创建一个spv证明法送到侧链；侧链验证资产已锁定，然后在侧链打开具有相同价值的另一种资产；
* 驱动链模式：类似于spv，只不过资产不是放在主链的某一位置，而是发送给资产所属的矿工，由矿工来联系侧链；
* 混合模式：主链和侧链使用不同的解锁方法，比如主链spv模式，侧链驱动链模式；



## 搭建方案`(基于EOSVR/sidechain)`

1. 运行 `"npm i"`;
2. 将` "config_example.js" `复制为 `"config.js" `并将` "config.js" `修改为你的设置；
3. 运行` "node linker.js"` ，就可以两边互相传输了；
注意：连接者在两边都要抵押足够的 CPU 和一点RAM 来维持操作，并且两边都要有足够 EVD。



## 前提

* 连接者(linker)：主链和侧链的交点，在2条链上都有此账号并且共用同一个公钥；



## 主侧链交互

1. 主链到侧链:从主链利用连接者账号发送一个transfer，指明侧链的chain_id（可以通过get info获得chain_id）, 例:

   ```sh
   cleos push action eoslocktoken transfer '{"from":"eoslinker111", "to":"eoslocktoken","quantity":"1000.0000 EVD","memo":"b6a3a2e75f6fc47e7ef8b413ae4ee6eb3a8fefcd01c0b0ecdf688563cfa5f493"}' -p eoslinker111
   ```

2. 侧链到主链:类似主链到侧链，不再赘述；

   

## 针对`eosio.bios, eosio.system`的改造
todo...



## 链接

* [`EOSVR/sidechain`](https://github.com/EOSVR/sidechain)
* [eos侧链开发设计](https://blog.csdn.net/weixin_39842528/article/details/83313374)



## 参考

[1] eos区块链应用开发指南

[2] 深入理解eos-原理解析与开发实战

