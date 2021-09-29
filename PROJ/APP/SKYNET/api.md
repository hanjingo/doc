[TOC]

# SKYNET API



## skynet

### abort

`skynet.abort()`

退出**进程**

### call

`skynet.call(addr, typename, ...)`

- `addr` 服务地址
- `typename` 服务类型

向服务发送消息(阻塞)

### dispatch

`skynet.dispatch(typename, func)`

- `typename` 服务名
- `func` 回调函数

把回调函数注册到服务

### exit

`skynet.exit()`

结束服务

### localname

`skynet.localname(name)`

- `name` 服务名

返回同一进程内，用register注册的具名服务的地址

### newservice

`skynet.newservice(name, ...)`

- `name` 服务名

启动一个名为name的新服务（可以在一个进程其启动多个服务）

### queryservice

`skynet.queryservice(name)`

- `name` 服务名

查询一个由uniqueservice启动的唯一服务的地址，若该服务尚未启动则等待

### response

`skynet.response(pack)`

- `pack` 打包函数

包装消息打包函数到闭包

### send

`skynet.send(addr, typename, ...)`

- `addr` 服务地址
- `typename` 服务类型

向服务发送消息

### timeout

`skynet.timeout(ti, func)`

- `ti` 时长（单位：0.01秒）
- `func` 回调函数

创建一个计时器，并设置回调

### uniqueservice

`skynet.uniqueservice(name, ...)`

- `name` 服务名

启动一个唯一服务（单例），如果该服务已经启动，则返回已启动的服务地址



## cluster

### call

`cluster.call(node, address, ...)` 

向一个节点上的一个服务提起一个请求，等待回应。

### open

`cluster.open(port)` 

让当前节点监听一个端口。

### proxy

`cluster.proxy(node, address)` 

为远程节点上的服务创建一个本地代理服务。

### query

`cluster.query(node, name)` 

在远程节点上查询一个名字对应的地址。

### reload

`cluster.reload([config])` 

重新加载当前节点的网络配置，通过config表来取代文件配置。

### register

`cluster.register(name, address)` 

在当前节点上为一个服务起一个字符串名字，之后可以用这个名字取代地址。

### send

`cluster.send(node, address, ...)`

向一个节点上的一个服务推送一条消息。

### snax

`cluster.snax(node, name, address)` 

向远程节点上的snax服务创建一个本地代理。

### wait

TODO



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

服务入口



## redis

使用redis模块需要先引用`require "skynet.db.redis"`

### connect

`redis.connect(db_conf)`

- `db_conf` redis连接配置

与Redis服务器建立连接

例：

```lua
local db = redis.connect({
        host="127.0.0.1",
        port=6379,
        db=0,
        --auth="xxx"
    })
```

### disconnect

`command:disconnect()`

断开与Redis服务器的连接

例：

```lua
local db = redis.connect({
        host="127.0.0.1",
        port=6379,
        db=0,
        --auth="xxx"
    })
db:disconnect()
```



## snax

### newservice

`snax.newservice(name, ...)`

- `name` 服务名

启动一个服务（同名服务可以同时启动多个，各自独立）

### uniqueservice

`snax.uniqueservice(name, ...)`

- `name` 服务名

启动一个唯一服务（同一个节点只能有一个同名服务，多次调用返回相同的对象）

### globalservice

`snax.globalservice(name, ...)`

- `name` 服务名

启动一个全局唯一服务（整个skynet网络中都只能有一个同名服务）

### queryservice

`snax.queryservice(name)`

- `name` 服务名

查询当前节点的服务（如果服务未启动，阻塞）

### queryglobal

`snax.queryglobal(name)`

- `name` 服务名

查询一个全局的服务（如果服务未启动，阻塞）

### self

`snax.self()`

获取当前的服务(注意是当前)

### exit

`snax.exit(...)`

退出当前服务

### kill

`snax.kill(obj, ...)`

- `obj` 服务对象

### hotfix

`snax.hotfix(obj, source, ...)`

- `obj` 服务对象
- `source` 代码块

热更新代码



  
