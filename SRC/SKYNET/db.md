# Skynet数据库



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

TODO

