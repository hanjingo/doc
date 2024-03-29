# 游戏服务器压测报告模版



| 编号 | 文档版本 | 修订章节 | 修订原因 | 修订日期 | 修订人 | 审核人 |
| ---- | -------- | -------- | -------- | -------- | ------ | ------ |
| 1    | 0.0.1    |          |          |          |        |        |
| 2    |          |          |          |          |        |        |



[TOC]



## 1 项目概述

（填写项目和文档介绍）



## 2 测试结论

本次测试内容为：

- （填写测试内容）

测试结论：（填写测试结论：高/中/低/无风险）

### 2.1 测试结果

| 测试策略         | 性能基线                                                     | 实测结果        |
| ---------------- | ------------------------------------------------------------ | --------------- |
| 单机容量测试     | （例：5w用户在线时，使用特定游戏模型90%响应时间<1秒，成功率>99.9%） | （达标/不达标） |
| 24小时稳定性测试 | （例：使用特定游戏模型压测24小时，服务无重启，内存无泄漏，各事务成功率>99.9%） | （达标/不达标） |

| 单场景                          | 每秒请求人数           | 关键事务成功率     | 关键事务90%响应时间 |
| ------------------------------- | ---------------------- | ------------------ | ------------------- |
| （填场景名：注册/登录/副本...） | （填写分配的用户数量） | （填写事务成功率） | （填写响应时间）    |

注：

1. （填写详细说明）



## 3 测试环境

### 3.1 硬件环境

| 测试环境   | 参数                   |
| ---------- | ---------------------- |
| 服务器型号 | （填写服务器型号信息） |
| CPU        | （填写CPU信息）        |
| 内存       | （填写内存信息）       |
| 网络       | （填写网络信息）       |

### 3.2 软件环境

| 测试环境 | 参数                 |
| -------- | -------------------- |
| 操作系统 | （填写操作系统信息） |
| 数据库   | （填写数据库信息）   |

### 3.3 测试工具

| 测试项目         | 测试工具         | 监控工具                 |
| ---------------- | ---------------- | ------------------------ |
| （填写测试项目） | （填写测试工具） | （填写测试指标监控工具） |



## 4 测试规模及限制

测试系统的数据规模如下：

| 序号 | 类型                   | 数量         |
| ---- | ---------------------- | ------------ |
| 1    | （填写需要测试的类型） | （填写数量） |



## 5 测试过程

### 5.1 测试模型

为了使性能测试尽量准确，测试必须要符合以下流程：

(填玩家模拟操作流程图)

从上述测试模型中，抽取出需要关注的性能指标如下：

| 序号 | 性能指标           | 说明         |
| ---- | ------------------ | ------------ |
| 1    | 同时在线数量（CU） | （填写说明） |
| 2    | 吞吐量（TPS）      | （填写说明） |
| 3    | 事务成功率         | （填写说明） |
| 4    | 平均响应时间       | （填写说明） |
| 5    | 平均收包率         | （填写说明） |
| 6    | 平均发包率         | （填写说明） |
| 7    | 发送流量           | （填写说明） |
| 8    | 接收流量           | （填写说明） |

### 5.2 测试案例

根据测试模型，选取以下典型案例/场景进行测试：

| 序号 | 案例名称           | 案例配比（%）      | 测试程序               |
| ---- | ------------------ | ------------------ | ---------------------- |
| 1    | （填写测试的案例） | （填写机器人配比） | （填写用到的测试程序） |

### 5.3 测试场景

为了使测试过程和测试结果能尽可能准确地反映出现实的生产系统场景，本次测试过程选取了具有代表性的几项业务操作；另外，根据初步分析，在每种并发用户数条件下，为各项业务操作分配了一定数量配比关系的虚拟用户，详见下表：

| 序号 | 业务操作               | 用户配比（配置的虚拟用户数/虚拟用户总数） |
| ---- | ---------------------- | ----------------------------------------- |
| 1    | （填写需要测试的业务） | （填写虚拟用户配比）                      |



## 6 测试结果

### 6.1 响应时间

### 6.1.1 平均响应时间

| 序号 | 业务操作                   | 配置用户数             | 响应时间(ms)       |
| ---- | -------------------------- | ---------------------- | ------------------ |
| 1    | （填写业务）               | （填写配置的用户数）   | （填写响应时间）   |
| 合计 | （填写业务数量）项业务操作 | （填写配置的用户总数） | （填写总响应时间） |

（在这里画折线图）

### 6.2 事务成功率

| 序号 | 业务操作         | 成功数     | 失败数     | 成功率     |
| ---- | ---------------- | ---------- | ---------- | ---------- |
| 1    | （填写业务操作） | （成功数） | （失败数） | （成功率） |

（在这里画柱状图/饼图）

### 6.3 CPU占用率

| 配置用户数               | CPU占用率（%）  |
| ------------------------ | --------------- |
| （填写配置的虚拟用户数） | （填写CPU占比） |

### 6.4 吞吐量(TPS)

TODO

### 6.5 同时在线数量(CU)

TODO

## 7 总结

（填写总结）



## 参考

- [网页游戏评测报告模板](http://www.fanwen118.com/c/219427.html)
- [测试报告模板](http://www.fanwen118.com/info_20/fw_3383676.html)
- [系统测试报告模板(绝对实用)](http://www.fanwen118.com/info_10/fw_2381079.html)
- [性能测试报告模板](http://www.fanwen118.com/info_10/fw_2343544.html)
- [WeTest服务器性能专项测试报告](https://www.doc88.com/p-0893169138362.html)





