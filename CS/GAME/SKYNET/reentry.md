# skynet服务重入问题

[TOC]

Skynet服务在收到消息时，会创建一个**协程**，在协程中会运行消息处理方法（即用``skynet.dispatch`设置的回调方法）。这意味着，如果在消息处理方法中调用阻塞API，服务不会被卡住（仅仅是处理消息的协程被卡住），执行效率得以提高，但程序的执行时序将得不到保证；对于一些必须保证执行顺序的高并发场景（注册->登录，定时任务开启），上述机制可能会有问题。

## 源码分析

```lua
-- 真正的dispatch_message逻辑；
local function raw_dispatch_message(prototype, msg, sz, session, source)
		...

		local f = p.dispatch -- skynet.dispatch注册的消息回调函数
		if f then
			local co = co_create(f)                -- 创建协程
			session_coroutine_id[co] = session     -- 绑定session到协程
			session_coroutine_address[co] = source -- 绑定source到协程
			...
			suspend(co, coroutine_resume(co, session,source, p.unpack(msg,sz))) -- 执行协程
        ...
		end
	end
end
```

1. 每到一个消息就创建一个协程，避免了阻塞调用造成卡顿；

### 重入示例

- `config.reentry`

  ```lua
  thread = 8
  logger = nil
  harbor = 0
  start = "main_reentry"
  luaservice ="./service/?.lua;./test/?.lua;./examples/?.lua"
  ```

- `main_reentry.lua`

  ```lua
  local skynet = require "skynet"
  require "skynet.manager"
  
  skynet.start(function()
      local s = skynet.newservice("reentry")
  
      skynet.fork(function() -- 模拟并发场景
          skynet.call(s, "lua", "hello")
      end)
  
      skynet.fork(function() -- 模拟并发场景
          skynet.call(s, "lua", "work")
      end)
  end)
  ```

- `reentry.lua`

  ```sh
  local skynet = require "skynet"
  require "skynet.manager"
  
  local CMD = {}
  
  function CMD.hello()
      skynet.sleep(10)
      skynet.error("hello")
  end
  
  function CMD.work()
      skynet.error("work")
  end
  
  local function main()
      skynet.dispatch("lua", function(session, _, cmd, ...)
          local f = assert(CMD[cmd])
          if session > 0 then
              skynet.ret(skynet.pack(f(...)))
          else
              f(...)
          end
      end)
  end
  skynet.start(main)
  ```

运行结果：

```sh
he@SD-20210816HMLO:/mnt/e/skynet$ ./skynet examples/config.reentry
[:00000002] LAUNCH snlua bootstrap
[:00000003] LAUNCH snlua launcher
[:00000004] LAUNCH snlua cdummy
[:00000005] LAUNCH harbor 0 4
[:00000006] LAUNCH snlua datacenterd
[:00000007] LAUNCH snlua service_mgr
[:00000008] LAUNCH snlua main_reentry
[:00000009] LAUNCH snlua reentry
[:00000002] KILL self
[:00000009] work  # 先执行的work
[:00000009] hello # 后执行的hello
```



## skynet.queue

skynet.queue可以用于保持消息处理的顺序性，其源码如下：

```lua
local skynet = require "skynet"
local coroutine = coroutine
local xpcall = xpcall
local traceback = debug.traceback
local table = table

function skynet.queue()
	local current_thread    -- 当前处理的线程
	local ref = 0           -- 线程的引用计数器
	local thread_queue = {} -- 线程队列

	local function xpcall_ret(ok, ...)
		ref = ref - 1
		if ref == 0 then
			current_thread = table.remove(thread_queue,1) -- 这里使用table来做queue，其性能可能会有问题
			if current_thread then
				skynet.wakeup(current_thread)             -- 唤醒当前线程
			end
		end
		assert(ok, (...))
		return ...
	end
	-- 返回一个封装的线程包裹函数
	return function(f, ...)
		local thread = coroutine.running()
		if current_thread and current_thread ~= thread then -- 有其它异步操作未被包裹进来
			table.insert(thread_queue, thread)              -- 加入线程队列
			skynet.wait()                                   -- 等待其它异步操作让出执行权
			assert(ref == 0)	-- current_thread == thread
		end
		current_thread = thread

		ref = ref + 1
		return xpcall_ret(xpcall(f, traceback, ...))
	end
end

return skynet.queue

```

### 例

将前面示例的`reentry.lua`修改如下：

```lua
local skynet = require "skynet"
local queue  = require "skynet.queue"
require "skynet.manager"

local lock = queue() -- lock函数

local CMD = {}

function CMD.hello()
lock(function () -- 注意这里
    skynet.sleep(10)
    skynet.error("hello")
end)
end

function CMD.work()
lock(function () -- 注意这里
    skynet.error("work")
end)
end

local function main()
    skynet.dispatch("lua", function(session, _, cmd, ...)
        local f = assert(CMD[cmd])
        if session > 0 then
            skynet.ret(skynet.pack(f(...)))
        else
            f(...)
        end
    end)
end
skynet.start(main)
```

运行结果：

```sh
he@SD-20210816HMLO:/mnt/e/skynet$ ./skynet examples/config.reentry
[:00000002] LAUNCH snlua bootstrap
[:00000003] LAUNCH snlua launcher
[:00000004] LAUNCH snlua cdummy
[:00000005] LAUNCH harbor 0 4
[:00000006] LAUNCH snlua datacenterd
[:00000007] LAUNCH snlua service_mgr
[:00000008] LAUNCH snlua main_reentry
[:00000009] LAUNCH snlua reentry
[:00000002] KILL self
[:00000009] hello # 先执行的hello
[:00000009] work  # 后执行的work
```

### 注意

`skynet.queue`对性能造成的影响不大，例：

- 加lock版本：

  ```lua
  function CMD.work()
  lock(function ()
      local a = 1
      a = a + 1
  end)
  end
  ```

- 不加lock版本

  ```lua
  function CMD.work()
  -- lock(function ()
      local a = 1
      a = a + 1
  -- end)
  end
  
  ```

- 分别调用若干次

  ```lua
  local times = 1000000
  skynet.fork(function() -- 模拟并发场景
          local start_tm = skynet.time()
          for i = 1, times do
              skynet.call(s, "lua", "work")
          end
          local end_tm = skynet.time()
          skynet.error("call work ", " times with timeout:", times, 1000 * (end_tm - start_tm), " ms")
      end)
  ```

测试结果如下：

| times    | 加lock耗时(ms)  | 不加lock耗时(ms) | 加lock与不加lock的耗时百分比(%) |
| -------- | --------------- | ---------------- | ------------------------------- |
| 100000   | 679.99982833862 | 670.00007629395  | 101.4925                        |
| 1000000  | 7029.9999713898 | 6640.0001049042  | 105.873492                      |
| 10000000 | 72640.000104904 | 68679.999828339  | 105.765871                      |

加lock相对未加lock大概有5%的性能损失，可以接受



## 参考

- [记一次 skynet 中使用 skynet.queue 给消息加锁时的问题](https://blog.csdn.net/weixin_34345753/article/details/91947260)
- [skynet：服务重入问题](https://blog.csdn.net/u010601662/article/details/105832961)
- [skynet: queue](https://blog.csdn.net/u010601662/article/details/105862137)

