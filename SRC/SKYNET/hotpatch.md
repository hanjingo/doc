[TOC]

# skynet热更新

**首先提出个人观点：热更新不应该作为常规的版本更新手段，只应该作为bug fix的一种临时措施。**

skynet实现热更新有以下方式：

- [控制台clearcache命令](#clearcache)
- [控制台inject命令](#inject)
- [云风制作的热更新工具-skynet-reload](#skynet-reload)
- [snax框架的hotfix](#snax.hotfix)
- [利用lua的require机制](#lua-require)
- ...



## 前提

### 1. upvalue

upvalue其实是lua中的一种隐式类型，例：

```lua
local a = {}
function foo()
    return a
end
```

a是foo的一个upvalue，（个人理解，upvalue更像是一个get函数指向的instance）。

lua提供了以下函数来修改upvalue:

- `debug.upvalueid`
- `debug.upvaluejoin`

### 2. skynet缓存机制

skynet改写了lua的辅助API（`luaL_loadfilex`），代码缓存改为永久保存机制：

一旦加载过一份脚本，那么到进程结束前，它占据的内存永远不会释放（也不会被加载多次）。

skynet提供了以下lua接口用来处理缓存：

- `clear`

  ```lua
  local cache = require "skynet.codecache"
  cache.clear()
  ```

  新建一个新的缓存，不会释放旧的缓存（**注意：它的内存是不断增长的，因为没有释放老的内存，慎用这个函数**）。

- `mode`

  ```lua
  cache.mode(mode)
  ```

  - `mode` 当mode为空时，返回当前的mode，默认为"ON"

    | mode  | 说明                                                         |
    | ----- | ------------------------------------------------------------ |
    | ON    | （默认）缓存加载的lua代码文件的                              |
    | OFF   | 禁止lua代码文件复用，即使在别的服务中曾经加载过同名文件      |
    | EXIST | - 如果自己或其他服务或加载过同名文件，复用之前的lua代码文件拷贝；<br>- 如果是新加载的文件则不进行缓存 |

  修改缓存模式

#### 源码实现

- `3rd/lua/lauxlib.c`

```c
#define CACHE_OFF 0   // 缓存关闭（直接加载）
#define CACHE_EXIST 1 // 缓存已存在（更新旧缓存）
#define CACHE_ON 2    // 缓存开启（替换虚拟机）

// 全局静态变量，定义了缓存模式
static int cache_key = 0;

// 设置缓存模式
static int cache_mode(lua_State *L) {
	static const char * lst[] = {
		"OFF",
		"EXIST",
		"ON",
		NULL,
	};
	if (lua_isnoneornil(L,1)) {
		int t = lua_rawgetp(L, LUA_REGISTRYINDEX, &cache_key); // 读取lua的缓存模式定义值
		int r = lua_tointeger(L, -1);
		if (t == LUA_TNUMBER) {
			if (r < 0  || r >= CACHE_ON) {
				r = CACHE_ON;
			}
		} else {
			r = CACHE_ON;
		}
		lua_pushstring(L, lst[r]);
		return 1;
	}
	int t = luaL_checkoption(L, 1, "OFF" , lst);
	lua_pushinteger(L, t);
	lua_rawsetp(L, LUA_REGISTRYINDEX, &cache_key); // 设置缓存模式
	return 0;
}

// 加载文件；L:lua虚拟机, filename:文件地址, mode:文件格式(bin/text)
LUALIB_API int luaL_loadfilex (lua_State *L, const char *filename,
                                             const char *mode) {
  int level = cache_level(L);
  if (level == CACHE_OFF) {         // OFF，直接加载，禁止复用
    return luaL_loadfilex_(L, filename, mode);
  }
  const void * proto = load(filename);
  if (proto) {
    lua_clonefunction(L, proto); // 复用
    return LUA_OK;
  }
  if (level == CACHE_EXIST) {       // EXIST，如果以前加载过，复用它；如果是新文件，直接加载，并且不缓存；
    return luaL_loadfilex_(L, filename, mode);
  }
  lua_State * eL = luaL_newstate(); // ON，遇到新文件，直接新建虚拟机，并缓存文件
  if (eL == NULL) {
    lua_pushliteral(L, "New state failed");
    return LUA_ERRMEM;
  }
  int err = luaL_loadfilex_(eL, filename, mode);
  if (err != LUA_OK) {
    size_t sz = 0;
    const char * msg = lua_tolstring(eL, -1, &sz);
    lua_pushlstring(L, msg, sz);
    lua_close(eL);
    return err;
  }
  lua_sharefunction(eL, -1); // 把加载过的函数共享出去
  proto = lua_topointer(eL, -1);
  const void * oldv = save(filename, proto);
  if (oldv) { // 如果已经有老的同名函数，为了防止覆盖已有的代码，关闭当前lua虚拟机
    lua_close(eL);
    lua_clonefunction(L, oldv);
  } else { // 这一份新加载的缓存会一直保留到进程结束
    lua_clonefunction(L, proto);
    /* Never close it. notice: memory leak */
  }

  return LUA_OK;
}

// 清空缓存(旧的内存并没被清掉，只是用新的替换它)
static void
clearcache() {
	if (CC.L == NULL)
		return;
	SPIN_LOCK(&CC)
		lua_close(CC.L);
		CC.L = luaL_newstate();
	SPIN_UNLOCK(&CC)
}

// 提供给lua的接口
LUAMOD_API int luaopen_cache(lua_State *L) {
	luaL_Reg l[] = {
		{ "clear", cache_clear }, // 清空缓存
		{ "mode", cache_mode },   // 修改缓存模式
		{ NULL, NULL },
	};
	luaL_newlib(L,l);
	lua_getglobal(L, "loadfile");
	lua_setfield(L, -2, "loadfile");
	return 1;
}
```

### 优点

- 当在同一个skynet进程中开启了大量lua VM时，缓存机制可以节省不少内存，并且提高了VM启动速度。



## clearcache

每个snlua服务会启动一个单独的lua VM，对于同一份lua文件，N个服务就要加载N次到内存。

skynet对此做了优化，每个lua文件只加载一次到内存，保存`lua文件--内存映射表`，下一个服务加载的时候copy一份内存即可，提高了VM的启动速度。

**注意：clearcache只能用于新服务的更新，对已有服务不能更新；新服务用新代码，旧服务用旧代码。**

### 源码实现

- `service/debug_console.lua`

```lua
-- 控制台命令函数
function COMMAND.help()
	return {
    	 ...
		clearcache = "clear lua code cache", -- 清理缓存
         ...
	}
end
-- 清空缓存命令
function COMMAND.clearcache()
	codecache.clear() -- 调用的是:3rd/lua/lauxlib.c的clearcache函数
end
```

### 用例

下面介绍如何利用`clearcache`命令来更新服务：

1. 新建热更新代码文件`examples/hot.lua`和`examples/main_hot.lua`

   ```lua
   -- main_hot.lua
   package.path = "./examples/?.lua;" .. package.path
   local skynet = require "skynet"
   skynet.start(function()
       skynet.newservice("debug_console",8000)
       print("test hotpatch...")
       while true do
           skynet.newservice("hot")
           skynet.sleep(300)
       end
   end)
   ```

   ```lua
   -- hot.lua
   local skynet = require "skynet"
   skynet.start(function()
       print("hello")
   end)
   ```

2. 新建配置文件`examples/config.hot`

   ```txt
   thread = 8
   logger = nil
   harbor = 0
   start = "main_hot"
   luaservice ="./service/?.lua;./test/?.lua;./examples/?.lua"
   ```

3. 启动skynet

   ```sh
   he@SD-20210816HMLO:/mnt/e/skynet$ ./skynet examples/config.hot
   [:00000002] LAUNCH snlua bootstrap
   [:00000003] LAUNCH snlua launcher
   [:00000004] LAUNCH snlua cdummy
   [:00000005] LAUNCH harbor 0 4
   [:00000006] LAUNCH snlua datacenterd
   [:00000007] LAUNCH snlua service_mgr
   [:00000008] LAUNCH snlua main_hot
   [:00000009] LAUNCH snlua debug_console 8000
   [:00000009] Start debug console at 127.0.0.1:8000
   test hotpatch...
   [:0000000a] LAUNCH snlua hot
   hello
   ```

4. 修改lua文件`examples/hot.lua`为以下内容

   ```lua
   -- hot.lua
   local skynet = require "skynet"
   skynet.start(function()
       print("world") -- 修改了这里
   end)
   ```

5. 使用telnet登录控制台

   ```sh
   he@SD-20210816HMLO:/mnt/e/skynet$ telnet 127.0.0.1 8000
   Trying 127.0.0.1...
   Connected to 127.0.0.1.
   Escape character is '^]'.
   Welcome to skynet console
   ```

6. 在控制台输入`clearcache`

   ```sh
   clearcache
   <CMD OK>
   ```

7. 控制台输出如下

   ```sh
   [:00000015] LAUNCH snlua hot
   hello
   [:00000016] LAUNCH snlua hot
   world
   ```



## inject

inject(注入更新)，将新代码注入到已有的服务里，让老服务执行新的代码，**可以更新旧服务**。

由于skynet修改了lua的缓存机制，所以lua的`require`热更新方法不再适用。

inject的实现原理（个人理解）：其实就是把老代码片段和新代码片段合并在一起，从而替换掉**一部分代码**，让老的get函数去关联新的upvalue。

lua代码中与inject相关的全局变量：

| LUA全局变量 | 说明                        |
| ----------- | --------------------------- |
| `_P`        | 消息分发函数...             |
| `_U`        | 自定义接口函数, 全局变量... |

### 热更代码编写规范

1. 如果要使用全局变量`_P`，热更的代码至少需要自己手动实现消息派发功能，模板如下：

   ```lua
   skynet.start(function()
   	...
       skynet.dispatch("lua", function(session, address, cmd, ...)
          -- 消息派发逻辑
          ...
       end)
   end)
   ```

2. 如果要使用全变量`_U`，则把需要热更的函数定义为全局函数；

### 源码实现

- `service/debug_console.lua`

  ```lua
  -- debug命令
  function COMMAND.help()
  	return {
  		...
  		inject = "inject address luascript.lua", -- 注入新代码
  		...
  	}
  end -- 跳到COMMAND.inject
  
  -- 注入新代码的命令
  function COMMAND.inject(address, filename, ...)
  	address = adjust_address(address)
  	local f = io.open(filename, "rb")
  	if not f then
  		return "Can't open " .. filename
  	end
  	local source = f:read "*a"
  	f:close()
  	local ok, output = skynet.call(address, "debug", "RUN", source, filename, ...)
  	if ok == false then
  		error(output)
  	end
  	return output
  end -- 跳到lualib/skynet/debug.lua/dbgcmd.RUN
  ```

- `lualib/skynet/debug.lua`

  ```lua
  		-- 注入代码
  		function dbgcmd.RUN(source, filename, ...)
  			local inject = require "skynet.inject"
  			local args = table.pack(...)
  			local ok, output = inject(skynet, source, filename, args, export.dispatch, skynet.register_protocol) -- 跳到 lualib/skynet/inject.lua/inject函数
  			collectgarbage "collect"
  			skynet.ret(skynet.pack(ok, table.concat(output, "\n")))
  		end
  ```

- `lualib/skynet/inject.lua`

  ```lua
  -- inject函数，加载新的lua代码并注入; skynet:skynet库, source:代码块, filename:lua文件地址, args:参数
  return function(skynet, source, filename, args, ...)
  	if filename then
  		filename = "@" .. filename
  	else
  		filename = "=(load)"
  	end
  	local output = {}
  
  	local function print(...)
  		local value = { ... }
  		for k,v in ipairs(value) do
  			value[k] = tostring(v)
  		end
  		table.insert(output, table.concat(value, "\t"))
  	end
  	local u = {}
  	local unique = {}
  	local funcs = { ... }
  	for k, func in ipairs(funcs) do -- 获取接口的函数原型
  		getupvaluetable(u, func, unique)
  	end
  	local p = {}
  	local proto = u.proto -- 遍历所有的消息分发函数
  	if proto then
  		for k,v in pairs(proto) do
  			local name, dispatch = v.name, v.dispatch
  			if name and dispatch and not p[name] then
  				local pp = {}
  				p[name] = pp
  				getupvaluetable(pp, dispatch, unique)
  			end
  		end
  	end
  	local env = setmetatable( { print = print , _U = u, _P = p}, { __index = _ENV })
  	local func, err = load(source, filename, "bt", env) -- 加载新的lua代码
  	if not func then
  		return false, { err }
  	end
  	local ok, err = skynet.pcall(func, table.unpack(args, 1, args.n))
  	if not ok then
  		table.insert(output, err)
  		return false, output
  	end
  
  	return true, output
  end
  
  ```

1. 通过控制台输入`inject`命令，触发`COMMAND.inject`函数
2. `COMMAND.inject`调用`dbgcmd.RUN`函数跳转到lua脚本`lualib/skynet/inject.lua`里面

### 用例

- **通过dispatch函数热更**

  1. 新建热更新文件`examples/main_hot_inject.lua`和`examples/hot_inject.lua`

     ```lua
     -- examples/main_hot_inject.lua
     package.path = "./examples/?.lua;" .. package.path
     
     local skynet = require "skynet"
     local myclass = {}
     local function hello()
         print("hello")
     end
     
     function myclass.dispatch()
         -- todo
     end
     function myclass.say()
         hello()
     end
     
     skynet.start(function()
         skynet.newservice("debug_console",8000)
         skynet.dispatch("lua", function(session, address, cmd, ...)
             myclass.dispatch()
         end)
     
         while true do
             myclass.say()
             skynet.sleep(100)
         end
     end)
     ```

     ```lua
     -- examples/hot_inject.lua
     print ("hot inject start")
     
     if not _P then
         print("hotfix fail, no _P define")
         return
     end
     
     local function get_up(f)
         local u = {}
         if not f then
             return u
         end
         local i = 1
         while true do
             local name, value = debug.getupvalue(f, i)
             if name == nil then
                 return u
             end
             u[name] = value
             i = i + 1
         end
         return u
     end
     
     local myclass = _P.lua.myclass
     local up = get_up(myclass.say)
     local hello = up.hello
     
     myclass.say = function()
         print("world")
     end
     
     print ("hot inject end")
     ```

   2. 新建配置文件`examples/config.hot_inject`
  
     ```txt
     thread = 8
     logger = nil
     harbor = 0
     start = "main_hot_inject"
     luaservice ="./service/?.lua;./test/?.lua;./examples/?.lua"
     ```

   3. 启动skynet
  
     ```sh
     he@SD-20210816HMLO:/mnt/e/skynet$ ./skynet examples/config.hot_inject
     [:00000002] LAUNCH snlua bootstrap
     [:00000003] LAUNCH snlua launcher
     [:00000004] LAUNCH snlua cdummy
     [:00000005] LAUNCH harbor 0 4
     [:00000006] LAUNCH snlua datacenterd
     [:00000007] LAUNCH snlua service_mgr
     [:00000008] LAUNCH snlua main_hot_inject
     [:00000009] LAUNCH snlua debug_console 8000
     [:00000009] Start debug console at 127.0.0.1:8000
     hello
     ```
  
  4. 启动控制台并注入lua脚本
  
     ```sh
     he@SD-20210816HMLO:/mnt/e/skynet$ telnet 127.0.0.1 8000
     Trying 127.0.0.1...
     Connected to 127.0.0.1.
     Escape character is '^]'.
     Welcome to skynet console
     list
     :00000004       snlua cdummy
     :00000006       snlua datacenterd
     :00000007       snlua service_mgr
     :00000008       snlua main_hot_inject
     :00000009       snlua debug_console 8000
     <CMD OK>
     inject 8 ./examples/hot_inject.lua
     hot inject start
     hot inject end
     <CMD OK>
     ```

  5. 观察主服务窗口

     ```sh
     [:00000009] 127.0.0.1:65254 connected
     world
     ```
  
- **通过全局函数**

  1. 新建热更新文件`examples/main_hot_inject.lua`和`examples/hot_inject.lua`

     ```lua
     -- examples/main_hot_inject.lua
     package.path = "./examples/?.lua;" .. package.path
     
     local skynet = require "skynet"
     local myclass = {}
     function hello() -- 注意这里是全局变量，不是local
         print("hello")
     end
     
     function myclass.dispatch()
         -- todo
     end
     function myclass.say()
         hello()
     end
     
     skynet.start(function ()
         skynet.newservice("debug_console",8000)
         while true do
             myclass.say()
             skynet.sleep(100)
         end
     end)
     ```

     ```lua
     -- examples/hot_inject.lua
     print ("hot inject start")
     
     if not _U then
         return
     end
     
     _U._ENV.hello = function ()
         _G.print("u world")
     end
     print ("hot inject end")
     ```
  
  2. 新建配置文件`examples/config.hot_inject`
  
     ```lua
     thread = 8
     logger = nil
     harbor = 0
     start = "main_hot_inject"
     luaservice ="./service/?.lua;./test/?.lua;./examples/?.lua"
     ```
  
  3. 启动skynet

     ```sh
     he@SD-20210816HMLO:/mnt/e/skynet$ ./skynet examples/config.hot_inject
     [:00000002] LAUNCH snlua bootstrap
     [:00000003] LAUNCH snlua launcher
     [:00000004] LAUNCH snlua cdummy
     [:00000005] LAUNCH harbor 0 4
     [:00000006] LAUNCH snlua datacenterd
     [:00000007] LAUNCH snlua service_mgr
     [:00000008] LAUNCH snlua main_hot_inject
     [:00000009] LAUNCH snlua debug_console 8000
     [:00000009] Start debug console at 127.0.0.1:8000
     hello
     ```

  4. 启动控制台并注入lua脚本

     ```sh
     he@SD-20210816HMLO:/mnt/e/skynet$ telnet 127.0.0.1 8000
     Trying 127.0.0.1...
     Connected to 127.0.0.1.
     Escape character is '^]'.
     Welcome to skynet console
     inject 8 ./examples/hot_inject.lua
     hot inject start
     hot inject end
     <CMD OK>
     ```
  
  5. 观察主服务窗口
  
     ```sh
     [:00000009] 127.0.0.1:52042 connected
     hello
     hello
     u world
     ```
  
     

## snax.hotfix

TODO



## skynet-reload

TODO



## lua-require

skynet的缓存机制是可以关闭的，当关闭skynet缓存机制之后，就可以利用lua本身的特性来实现热更新。

**注意：关闭skynet缓存机制意味着性能可能会下降，慎重选择**

### 原理

TODO



## 参考

- [云风-如何让 lua 做尽量正确的热更新](https://blog.codingnow.com/2016/11/lua_update.html)
- [云风-DebugConsole](https://github.com/cloudwu/skynet/wiki/DebugConsole)
- [云风-在不同的 lua vm 间共享 Proto](https://blog.codingnow.com/2014/03/lua_shared_proto.html)
- [云风-CodeCache](https://github.com/cloudwu/skynet/wiki/CodeCache)
- [云风-重载一个 skynet 中的 lua 服务](https://blog.codingnow.com/2016/03/skynet_reload.html)
- [github-热更工具](https://github.com/cloudwu/skynet-reload)
- [skynet源码分析之热更新](https://www.cnblogs.com/RainRill/p/8940673.html)
- [skynet 热更新 lua 代码](https://blog.csdn.net/mycwq/article/details/53943890)
- [snax](https://github.com/cloudwu/skynet/wiki/Snax)

