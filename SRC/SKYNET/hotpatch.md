[TOC]

# skynet热更新

skynet实现热更新的两种方式：

- clearcache
- inject



## skynet控制台

控制台是skynet提供的一个控制工具，需要启动debug_console服务`skynet.newservice("debug_console", ip, port)`，指定一个地址；

skynet启动后，用telnet或nc命令就可以进入控制台发送控制命令；

### 源码

- `service/debug_console.lua`
- `service/debug_console.lua`



## skynet缓存机制

skynet修改了Lua的官方实现（可选），让多个Lua VM共享相同的函数原型；

skynet改写了lua的辅助API（`luaL_loadfilex`），代码缓存采用永久保存机制；即一旦加载过一份脚本，那么到进程结束前，它占据的内存永远不会释放（也不会被加载多次）。

skynet提供了以下lua接口用来处理缓存：

- `clear`

  ```lua
  local cache = require "skynet.codecache"
  cache.clear()
  ```

  新建一个新的缓存，不会释放旧的缓存（**注意：所以它的内存是不断增长的，慎用这个函数**）。

- `mode`

  ```lua
  cache.mode(mode)
  ```

  - `mode` 当mode为空时，返回当前的mode，默认为"ON

    | mode  | 说明                                                         |
    | ----- | ------------------------------------------------------------ |
    | ON    | （默认）缓存加载的lua代码文件的                              |
    | OFF   | 禁止lua代码文件复用，即使在别的服务中曾经加载过同名文件      |
    | EXIST | - 如果自己或其他服务或加载过同名文件，复用之前的lua代码文件拷贝；<br>- 如果是新加载的文件则不进行缓存 |

  修改缓存模式

### 源码

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

### 源码

- `service/debug_console.lua`

```c
-- debug命令
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

1. 修改lua启动文件`examples/main.lua`，开启console(如果已有就忽略)

   ```lua
   skynet.start(function()
   	...
   	skynet.newservice("debug_console",8000)
   	...
   end)
   ```

2. 启动skynet（配置文件使用`examples/config`）

   ```sh
   ./skynet examples/config
   ```

3. 使用telnet登录控制台

   ```sh
   he@SD-20210816HMLO:~$ telnet 127.0.0.1 8000
   Trying 127.0.0.1...
   Connected to 127.0.0.1.
   Escape character is '^]'.
   Welcome to skynet console
   list
   :01000004       snlua cmaster
   :01000005       snlua cslave
   :01000007       snlua datacenterd
   :01000008       snlua service_mgr
   :0100000a       snlua protoloader
   :0100000b       snlua console
   :0100000c       snlua debug_console 8000
   :0100000d       snlua simpledb
   :0100000e       snlua watchdog
   :0100000f       snlua gate
   ```

4. 在控制台输入`clearcache`

   ```sh
   clearcache
   <CMD OK>
   ```

5. 修改lua文件

**注意：clearcache只能用于新服务的热更新，对已有服务不能更新；**



## inject

inject(注入更新)，将新代码注入到已有的服务里，让服务执行新的代码，**可以热更已开启的服务**

### 源码：

- `lualib/skynet/inject.lua`

### 用例

1. 启动控制台
2. 在控制台输入`inject 3 examples/injectlaunch.lua`



## 参考

- [云风-DebugConsole](https://github.com/cloudwu/skynet/wiki/DebugConsole)
- [云风-在不同的 lua vm 间共享 Proto](https://blog.codingnow.com/2014/03/lua_shared_proto.html)
- [云风-CodeCache](https://github.com/cloudwu/skynet/wiki/CodeCache)
- [skynet源码分析之热更新](https://www.cnblogs.com/RainRill/p/8940673.html)

