[TOC]

# 编码之坑



## 调试方法

#### [如何定位内存问题](mem_bug.md)

#### [如何定位CPU跑满问题](cpu_full.md)

#### [如何定位Core Dump问题](core_dump.md)

#### [如何定位丢包问题](package_lost.md)

#### [如何定位高并发问题](high_concurrency.md)



## 调试工具

#### [valgrind](valgrind.md)

#### [GDB](gdb.md)

#### [WireShark](wire_shark.md)

#### [telnet](telnet.md)

#### [linux系统日志](linux_sys_log.md)

#### [linux调试命令](linux_debug_cmd.md)



## C++

#### [c++不允许内部类前置声明](cpp.md)

#### [动态链接库链接不上](cpp.md)



## eos

#### [脏数据问题](eos.md)

#### [eos无法启动](eos.md)

#### [报`Error 3090003`错误](eos.md)

#### [报`fetching abi for undefined: unknown key (eosio::chain::name)`错误](eos.md)

#### [报`Error 3080004: Transaction exceeded the current CPU usage limit imposed on the transaction`错误](eos.md)

#### [eos合约被冲掉的问题](eos.md)



## go

#### [waitgroup的坑](golang.md)

#### [`time.Parse`时间转换的坑](golang.md)



## 网络

#### [大小端问题](net.md)

关键字：**大小端**，**数据存储模式**

不同架构的CPU可能采用的是不同的数据存储模式，不做转换可能会掉坑...

#### [Nagle算法的坑](net.md)

关键字：**Nagle**，**NoDelay**，**TCP**

如果使用TCP但不关闭Nagle算法(NoDelay选项)，TCP会把一些小的包汇聚到一起再发送，对于一些低延迟的程序来说，这一特性可能会造成一些不良影响...



## skynet

#### [lua模块引用时找不到文件](skynet.md)

关键字：**模块**，**require.lua**

用skynet调用模块时，报` lua loader error : ./lualib/skynet/require.lua:31: module 'xxx' not found:`错误...

#### [热更新时print函数无法打印](skynet.md)

关键字：**热更新**，**print**

热更新时，print函数失效...



## Mysql

#### [修改密码时提示不合法](mysql.md)

关键字：mysql，密码，不合法

修改MySQL的用户名和密码时，报`ERROR 1819 (HY000): Your password does not satisfy the current policy requirements;`错误...



## 其它

#### [eos-go报`action declares irrelevant authority`错误](eos-go.md)

#### [在执行sh文件时报`Syntax error: "(" unexpected`错误](linux.md)
