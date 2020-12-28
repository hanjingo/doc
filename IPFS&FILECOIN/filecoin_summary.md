# filecoin总结
## 参考
* [filecoin技术架构分析之一：filecoin概念](https://blog.csdn.net/qq_21393091/article/details/88072946)
* [filecoin技术架构分析之二：filecoin通用语言理解](https://blog.csdn.net/qq_21393091/article/details/88073022)
* [filecoin技术架构分析之三：filecoin开发网络使用](https://blog.csdn.net/qq_21393091/article/details/88073071)
* [filecoin技术架构分析之四：filecoin源码顶层架构分析](https://blog.csdn.net/qq_21393091/article/details/88073352)
* [filecoin技术架构分析之五：filecoin源码分析之协议层心跳协议](https://blog.csdn.net/qq_21393091/article/details/88139537)

## 架构
### 消息流程
```sequence
participant Network
participant Commands
participant Protocols
participant Internal Api
participant Core

Network->Protocols:storege protocol
Network->Protocols:mining protocol
Network->Protocols:retrieval protocol
Network->Protocols:heart protocol
Commands->Protocols:cmd
Protocols->Internal Api:Core Api
Protocols->Internal Api:Porcelain
Protocols->Internal Api:Plumbing
Internal Api->Core:Message Pool
Internal Api->Core:Chain Store
Internal Api->Core:Processor
Internal Api->Core:Block Service
Internal Api->Core:Wallet
```

Network:

* libp2p

Commands:

* HTTP REST / API

Protocols:

* 挖矿协议(mining protocol)
* 存储协议(storege protocol)
* 检索协议(retrival protocol)
* 心跳协议(heartbeat protocol)