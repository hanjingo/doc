# IM系统构建

<!-- vim-markdown-toc GFM -->

* [1用户状态一致性](#1用户状态一致性)
    - [1.1拉模式](#11拉模式)
    - [1.2推模式](#12推模式)
    - [1.3小结](#13小结)
* [2可靠性](#2可靠性)
    - [2.1QoS机制](#21qos机制)
    - [2.2应用层确认](#22应用层确认)
    - [2.3个人观点](#23个人观点)
* [参考](#参考)

<!-- vim-markdown-toc -->



## 1用户状态一致性

用户状态的更新，有2种模型：

- 拉模式
- 推模式

### 1.1拉模式

```mermaid
graph LR
Client1--更新状态-->Server
Server--循环拉取-->Client2-->Server
```

1. Client1状态更新到Server
2. Client2循环拉取Client1的信息

**缺点:**

- Client1状态改变，Client2获取不实时
- Client1状态不改变，Client2会有大量无效轮询请求，占用服务器资源

### 1.2推模式

```mermaid
graph LR
Client1--更新状态-->Server
Server==推送==>Client2
Server==推送==>Client3
```

1. Client1状态更新到Server
2. Server推送到Client2，Client3

**缺点:**

- 当在线好友量很大时，任何一个用户状态的改变，会扩散成N(消息风暴扩散系数)个实时通知，此时非常恐怖。

### 1.3小结

需要根据不同的场景选用不同的模式：

- 好友状态：如果对实时性要求较高，可以采用推送的方式同步；如果实时性要求不高，可以采用轮询拉取的方式同步；
- 群友的状态：由于消息风暴扩散系数过大，可以采用按需拉取，延时拉取的方式同步；
- 系统消息/开屏广告等：对实时性要求不高的业务，可以采用拉取的方式获取消息；
- 消息风暴扩散系数：是指一个消息发出时，变成N个消息的扩散系数，这个系数与业务及数据相关，一定程度上它的大小决定了技术采用推送还是拉取。



## 2可靠性

消息的可靠性有以下基本要求：

1. 消息不丢失
2. 消息不重复

### 2.1QoS机制

QoS(Quality of Service，服务质量)，提供以下三种服务模型：

1. `Best-Effort Service(尽力而为服务模型)`：尽最大可能发送报文，对带宽，时延，抖动和可靠性等不提供任何保证；
2. `Differentiated Service(区分服务模型)`：根据服务要求对不同业务的数据进行分类，对保温按类进行优先级标记，然后有差别的提供服务；
3. `Integrated Service(综合服务模型)`：节点在发送报文前，需要向网络申请资源预留，确保网络能够满足数据流的特定服务要求；

### 2.2应用层确认

为了实现消息传递的可靠性，需要采用“应用层确认机制”；一次可靠投递需要使用6个报文，流程如下：

```mermaid
graph LR
ClientA--Req1-->ImServer--Rsp1-->ClientA
ImServer--Ntf1-->ClientB
ClientB--Req2-->ImServer--Rsp2-->ClientB
ImServer--Ntf2-->ClientA
```

- `Req` 请求消息(客户端->服务端)
- `Rsp` 返回消息()
- `Ntf` 通知消息(服务端->客户端)

1. 客户端A发送消息到服务器；
2. 服务器返回回执信息给客户端A；
3. 服务器转发信息到客户端B；
4. 客户端B返回回执信息给服务器；
5. 服务器返回回执信息给客户端B，内容为：已收到B的回执；
6. 服务器发送消息给客户端A，内容为：客户端B已收到A发送的消息

此时为了防止在客户端上述过程中的长时间等待，需要引入消息过期机制；

情景分析：

1. `Req1/Rsp1`丢失：经过一段时间，A还是没有收到`Rsp1`，A重新发送`Req1`；
2. `Ntf1/Req2`丢失：经过一段时间，服务器没有收到`Req2`，服务器重新发送`Ntf1`；
3. `Rsp2`丢失：经过一段时间，B没有收到`Rsp2`，B重新发送`Req2`；
4. `Ntf2`丢失：经过一段时间，A没有收到`Ntf2`，A重新发送`Req1`。

### 2.3个人观点

6步的QoS过于繁琐，如果为了时效性可以考虑牺牲一部分可靠性，则上述步骤中的第2步和第5步可以省略；流程如下：

```mermaid
graph LR
ClientA--Req1-->ImServer
ImServer--Ntf1-->ClientB
ClientB--Req2-->ImServer
ImServer--Ntf2-->ClientA
```



## 参考

- [IM单聊和群聊中的在线状态同步应该用“推”还是“拉”？](http://www.52im.net/thread-715-1-1.html)
- [IM消息送达保证机制实现(一)：保证在线实时消息的可靠投递](http://www.52im.net/thread-294-1-1.html)
- [QoS的基本原理](https://blog.csdn.net/c1194758555/article/details/78839184)
- [百度百科-QoS](https://baike.baidu.com/item/qos/404053?fr=aladdin)

