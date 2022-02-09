# SKYNET API

[TOC]



## skynet

### abort

`skynet.abort()`

退出**进程**

### call

`skynet.call(addr, typename, ...)`

- `addr` 服务地址
- `typename` 服务类型

向服务发送消息（并等待对方响应）

### dispatch

`skynet.dispatch(typename, func)`

- `typename` 服务名
- `func` 回调函数

把回调函数注册到服务；

### exit

`skynet.exit()`

结束当前服务

### forward_type

`skynet.forward_type(map, start_func)`

- `map`
- `start_func`

转换消息

### localname

`skynet.localname(name)`

- `name` 服务名

返回同一进程内，用register注册的具名服务的地址

### newservice

`skynet.newservice(name, ...)`

- `name` 服务名

启动一个名为name的新服务（可以在一个进程其启动多个服务），返回新服务的地址；

### queryservice

`skynet.queryservice(name)`

- `name` 服务名

查询一个由uniqueservice启动的唯一服务的地址，若该服务尚未启动则等待

### queue

`skynet.queue()`

创建一个队列（锁），用于规避skynet服务重入问题；

例：

```lua
local skynet = require "skynet"
local queue  = require "skynet.queue"
require "skynet.manager"

local lock = queue() -- lock函数
local CMD  = {}

function CMD.work()
lock(function () -- 锁住
    skynet.error("work")
end)
end
skynet.start(.)
```

### rawcall

`function skynet.rawcall(addr, typename, msg, sz)`

- `addr`        地址
- `typename` 消息类型
- `msg`          消息
- `sz`            消息长度

向addr发送已经打包好的消息并等待响应

### rawsend

`function skynet.rawsend(addr, typename, msg, sz)`

- `addr`        地址
- `typename` 消息类型
- `msg`          消息
- `sz`            消息长度

向addr发送一个打包好的消息（对方无需响应）

### redirect

`skynet.redirect = function(dest,source,typename,...)`

- `dest`        目的地址
- `source`     发送地址
- `typename` 消息类型

与`skynet.send`类似，但是可以指定发送地址`source`和发送的`session`；可以用来伪造其他服务的消息。

### response

`skynet.response(pack)`

- `pack` 打包函数

包装消息打包函数到闭包

### self

`skynet.self()`

返回当前服务的地址

### send

`skynet.send(addr, typename, ...)`

- `addr`        服务地址
- `typename` 消息类型

向addr发送一个未打包好的消息（对方无需响应），该函数自动将`...`打包并发送；

### start

`skynet.start(start_func)`

- `start_func` 初始化服务函数

用函数`start_func`初始化

### timeout

`skynet.timeout(ti, func)`

- `ti`     时长（单位：0.01秒）
- `func` 回调函数

创建一个计时器，并设置回调（注意：此计时器只会调用一次，如果需要定期调用函数，需要将回调函数递归，在回调函数运行结束后重新设置skynet.timeout）；

例：

```sh
local function f()
	print("hello")
	skyent.timeout(1, f)
end
```

### tostring

c语言提供的字符串转换函数

例：

```lua
skynet.tostring(msg, sz)
```

### trash

c语言提供的内存释放函数；

例：

```lua
skynet.trash(msg,sz)
```

### uniqueservice

`skynet.uniqueservice(name, ...)`

- `name` 服务名

启动一个唯一服务（单例），如果该服务已经启动，则返回已启动的服务地址

---

## cluster

### call

`cluster.call(node, address, ...)` 

- `node`      节点名
- `address` 请求地址
- `...`

向一个节点上的一个服务提起一个请求，等待回应(阻塞)。

### open

`cluster.open(port)`

- `port` 端口

让当前节点监听一个端口。

### proxy

`cluster.proxy(node, address)`

- `node`      节点
- `address` 代理名

为远程节点上的服务创建一个本地代理服务，返回代理对象。

### query

`cluster.query(node, name)` 

在远程节点上查询一个名字对应的地址。

### reload

`cluster.reload(config)`

- `config` 节点配置表

重新加载其他节点的配置

### register

`cluster.register(name, address)`

- `name`      字符串名字
- `address` 服务地址

在当前节点上为一个服务起一个字符串名字，之后可以用这个名字取代地址。

### send

`cluster.send(node, address, ...)`

- `node`      节点名
- `address` 请求地址
- `...`

向一个节点上的一个服务发送一条消息(非阻塞)。

### snax

`cluster.snax(node, name, address)` 

向远程节点上的snax服务创建一个本地代理。

### wait

TODO

---

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

---

## mysql

使用mysql模块需要先引用`require "skynet.db.mysql"`

### connect

`mysql.connect(opts)`

- `opts` 连接参数

连接mysql数据库

例:

```lua
local mysql = require "skynet.db.mysql"

skynet.start(function ()
    local db = mysql.connect({
        host="localhost",
        port=3306,
        user="root",
        password="abc",
        database = "test",
        charset = "utf8mb4",
        max_packet_size = 1024 * 1024,
    })

    if not db then
        print("connect redis fail")
        return
    end

    db:query("SELECT id, name FROM tb WHERE id = 1 LIMIT 1")
    ...
end)
```

---

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

---

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

终止服务

### hotfix

`snax.hotfix(obj, source, ...)`

- `obj`      服务对象
- `source` 代码块

热更新代码

---

  ## socket

### listen

`socket.listen(host, port, backlog)`

- `host` IP地址
- `port` 端口
- `backlog` ？

监听套接字

### start

socket.start(id, func)

- `id`    套接字
- `func` 接收回调函数

让套接字开始接收数据

### read

`socket.read(id, sz)`

- `id` 套接字
- `sz` 需要读取的数据长度

从socket读数据（阻塞）

### close

`socket.close(id)`

- `id` 套接字

关闭socket（阻塞）

---
