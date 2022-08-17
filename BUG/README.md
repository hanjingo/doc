[TOC]

# BUG速览



## linux

#### [ubuntu的dash问题](linux.md)

关键词：**ubuntu**, **dash**

在执行sh文件时报错：`Syntax error: "(" unexpected`...

#### [wsl环境下git clone报错](linux.md)

关键词：**wsl**, **git**, **config.lock**

在wsl环境下的windows文件夹中执行`git clone xx`报错：`xx/.git/config.lock failed: Operation not permitted`...

#### [shell脚本文件编码格式问题](linux.md)

关键词：**shell脚本**，**编码格式**

在linux下执行shell脚本时报错：`Syntax error: "elif" unexpected (expecting "then")`...



## C++

#### [c++不允许内部类前置声明](cpp.md)

关键词：**C++**，**前置声明**

#### [动态链接库链接不上](cpp.md)

关键词：**C++**，**动态链接库**

#### [Lambda引用捕获的悬挂引用问题](cpp.md)

关键词：**C++**，**lambda**，**引用捕获**，**悬挂引用**

Lambda引用捕获局部变量时，由于离开作用域导致局部变量释放，从而导致“悬挂引用”问题...




## eos

#### [脏数据问题](eos.md)

关键词：**eos**，**脏数据**

通过错误的方式关闭正在运行的eos系统，在eos下次启动时会报错...

#### [eos无法启动](eos.md)

关键词：**eos**，**无法启动**

eos无法启动...

#### [没有导入系统私钥](eos.md)

关键词：**eos**，**系统私钥**, **Error 3090003**

创建账户时报Error 3090003错误：`Provided keys, permissions, and delays do not satisfy declared authorizations...`

#### [abi错误](eos.md)

关键词：**eos**，**abi**

调用接口时报错：`Error: fetching abi for undefined: unknown key...`

#### [执行命令超时](eos.md)

关键词：**eos**，**Error 3080004**, **超时**

由于eos系统的限制，执行时间过长的的命令会报错：`Transaction exceeded the current CPU usage limit imposed on the transaction...`

#### [eos合约被冲掉的问题](eos.md)

关键词：**eos**，**合约**

一个eos账号只能部署一个合约...



## Eos-GO

#### [权限异常](eos-go.md)

关键词：**eos-go**

权限异常导致报错`action declares irrelevant authority...`



## Golang

#### [waitgroup的坑](golang.md)

关键词：**go**，**golang**, **waitgroup**

因为WaitGroup作用范围导致的Add操作失效...

#### [time.Parse时间转换的坑](golang.md)

关键词：**go**，**golang**, **time.Parse**

使用`time.Parse`转换字符串为utc时间...



## 网络

#### [大小端问题](net.md)

关键词：**大小端**，**数据存储模式**

不同架构的CPU可能采用的是不同的数据存储模式，不做转换可能会掉坑...

#### [Nagle算法的坑](net.md)

关键词：**Nagle**，**NoDelay**，**TCP**

如果使用TCP但不关闭Nagle算法(NoDelay选项)，TCP会把一些小的包汇聚到一起再发送，对于一些低延迟的程序来说，这一特性可能会造成一些不良影响...

#### [Time wait问题](net.md)

关键词：**TCP**，**Timewait**

主动发起方频繁建立/断开连接，会导致系统之存在大量的timewait连接，从而导致没法建立新的连接...

#### [linux端口访问不了](net.md)

关键词：**telnet**， **ufw**， **防火墙**

telnet端口不通，但是防火墙已关闭，可能是由于linux默认禁止端口访问...



## skynet

#### [lua模块引用时找不到文件](skynet.md)

关键词：**模块**，**require.lua**

用skynet调用模块时，报` lua loader error : ./lualib/skynet/require.lua:31: module 'xxx' not found:...`

#### [热更新时print函数无法打印](skynet.md)

关键词：**热更新**，**print**

热更新时，print函数失效...

#### [调用snax.exit时报错，提示对象为空](skynet.md)

关键词：**skynet**, **snax.exit()**

当调用`snax.exit()`时，报`[:00000008] init service failed: ./lualib/snax/interface.lua:82:...`

#### [pbc的lua版本不对](skynet.md)

关键词：**pbc**, **protobuf**, **protobuf.c**, **lua**

当调用第三方库`pbc`时，报`lua: ./protobuf.lua:1: module 'protobuf.c' not found:...`



## Mysql

#### [修改密码时提示不合法](mysql.md)

关键词：**mysql**，**密码**，**不合法**

修改MySQL的用户名和密码时，报`ERROR 1819 (HY000): Your password does not satisfy the current policy requirements;...`



## ZeroMQ

#### [慢启动问题](zeromq.md)

关键词：**ZeroMQ**，**pub/sub**

TODO

#### [高水位问题](zeromq.md)

关键词：**ZeroMQ**，**HWN**，**高水位**

TODO



## 其它

#### [eos-go报`action declares irrelevant authority`错误](eos-go.md)

