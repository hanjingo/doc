[TOC]

# SKYNET API



## cluster

### call

`cluster.call(node, address, ...)` 

向一个节点上的一个服务提起一个请求，等待回应。

### send

`cluster.send(node, address, ...)`

向一个节点上的一个服务推送一条消息。

### open

`cluster.open(port)` 

让当前节点监听一个端口。

### reload

`cluster.reload([config])` 

重新加载当前节点的网络配置，通过config表来取代文件配置。

### proxy

`cluster.proxy(node, address)` 

为远程节点上的服务创建一个本地代理服务。

### snax

`cluster.snax(node, name, address)` 

向远程节点上的snax服务创建一个本地代理。

### wait

TODO

### register

`cluster.register(name, address)` 

在当前节点上为一个服务起一个字符串名字，之后可以用这个名字取代地址。

### query

`cluster.query(node, name)` 

在远程节点上查询一个名字对应的地址。



## gateway

### openclient

`gateserver.openclient(fd)`

- `fd`

允许fd接收消息，给消息放行

### closeclient

`gateserver.closeclient(fd)`

- `fd`

关闭fd，踢掉一个连接

### start

`gateserver.start(handler)`

- `handler`

入口



## service

### newservice

`skynet.newservice(name, ...)`

- `name` 服务名

启动一个名为name的新服务（可以在一个进程其启动多个服务）

### uniqueservice

`skynet.uniqueservice(name, ...)`

- `name` 服务名

启动一个唯一服务（单例），如果该服务已经启动，则返回已启动的服务地址

### queryservice

`skynet.queryservice(name)`

- `name` 服务名

查询一个由uniqueservice启动的唯一服务的地址，若该服务尚未启动则等待

### localname

`skynet.localname(name)`

- `name` 服务名

返回同一进程内，用register注册的具名服务的地址
