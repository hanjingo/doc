# skynet源码分析-数据库

<!-- vim-markdown-toc GFM -->

* [Redis](#redis)
    - [连接](#连接)
    - [示例](#示例)
* [Mysql](#mysql)
    - [连接](#连接-1)

<!-- vim-markdown-toc -->



## Redis

Skynet使用Redis需要引入Redis模块`require "skynet.db.redis"`；

### 连接

Skynet提供接口`redis.connect(db_conf)`用于与Redis建立连接，db_conf为配置，其格式如下：

```lua
{
	host="127.0.0.1", -- redis IP
	port=6379, -- redis 端口
	db=0, -- 数据库id
    auth=xxx, -- 鉴权
}
```

Skynet提供接口`command:disconnect()`用于与Redis断开连接

### 示例

```lua
local redis = require "skynet.db.redis"

skynet.start(function ()
    local db = redis.connect({
        host="127.0.0.1",
        port=6379,
        db=0,
    })

    if not db then
        print("connect redis fail")
        return
    end

    print("test set \"a\" 1 with result=", db:set("a", 1))
    print("test get \"a\" with result=", db:get("a"))
    print("test exists \"a\" with result=", db:exists("a"))
    print("test del \"a\" with reuslt=", db:del "a", "and \"a\" = ", db:get("a"))
    print("test sadd myset \"b\" with result=", db:sadd("myset", "b"))
    print("test ismember myset \"b\" with result=", db:sismember("myset", "b"))
    print("test hset \"c\" c1 123 with result=", db:hset("c", "c1", 123))
    print("test hget \"c\" c1 with result=", db:hget("c", "c1"))

    db:disconnect()
end)
```



## Mysql

Skynet使用Mysql需要引入Mysql模块`require "skynet.db.mysql"`；

### 连接

Skynet提供接口`mysql.connect(db_conf)`用于与mysql建立连接，db_conf为配置，其格式如下：

```lua
game_db[1] = {
    host = "localhost", 	       -- mysql IP
    port = 3306,			      -- mysql Port
    user = "root",			      -- 用户名 
    password = "123456",	       -- 密码
    database = "test",	           -- 数据库
    charset  = "utf8mb4",	       -- 编码格式
    max_packet_size = 1024 * 1024, -- 最大数据包大小
}
```

Skynet提供接口`command:disconnect()`用于与mysql断开连接

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

    local sql = string.format("SELECT id, name FROM tb WHERE id = %d LIMIT 1",)
    print("test sql:", sql, " with result=", db:query(sql))
    db:disconnect()
end)
```



