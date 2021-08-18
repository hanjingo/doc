# skynet配置



## 定义

```c
// skynet配置
struct skynet_config {
	int thread;					// 可创建的最大线程数量(key:thread)
	int harbor;					// 节点id(key:harbor)
	int profile;				// 是否做简略的消息统计(key:profile)
	const char * daemon;		// 记录进程id的文件路径(key:daemon)
	const char * module_path;	// 模块路径(key:cpath)
	const char * bootstrap;		// 初始化参数(key:bootstrap)
	const char * logger;		// 日志路径(key:logger)
	const char * logservice;	// 日志模块名(key:logservice)
};
```



## 配置说明

### 常规配置

| 键         | 默认值            | 说明                                                         |
| ---------- | ----------------- | ------------------------------------------------------------ |
| address    | -                 | （可选）当前节点的ip和端口                                   |
| bootstrap  | `snlua bootstrap` | 启动的第一个服务以及其启动参数                               |
| cpath      | `./cservice/?.so` | 用c编写的服务模块的位置，以`;`作为分割。                     |
| enablessl  | NULL              | 如果需要通过ltls模块支持https，设置为true                    |
| harbor     | `1`               | 当前节点id，取值范围[1,255]；（0表示这是一个单节点，此时`master`, `address`和`standalone`都不必设置）。 |
| logger     | `NULL`            | 函数`skynet_error`输出到的文件路径                           |
| logservice | `logger`          | log定制参数（时间戳...）                                     |
| logpanth   | -                 | ？                                                           |
| master     | -                 | （可选）当前集群中的master节点的ip和端口                     |
| profile    | `1`               | 是否启用统计模式（对性能有点影响）                           |
| standalone | -                 | （可选）当前节点的master服务监听的地址，用于协调slave组网；配置格式为：`ip:端口` |
| start      | `main`            | 指定要启动的skynet主程序，默认main.lua                       |
| thread     | `8`               | 启动多少个工作线程，通常不要将它配置超过实际拥有的cpu核心数  |
| -- daemon  | `NULL`            | 后台模式，如果配置成`daemon="./skynet.pid"`就可以以后台模式启动 |

### lua配置

| 键         | 默认值              | 说明                               |
| ---------- | ------------------- | ---------------------------------- |
| lualoader  | `lualib/loader.lua` | 指定用哪个lua文件来加载lua服务     |
| luaservice | -                   | lua服务代码所在的位置，以`;`分割。 |
| snax       | -                   | 用snax框架编写的服务的查找路径     |
| lua_cpath  | -                   | TODO                               |
| lua_path   | -                   | TODO                               |
| preload    | -                   | TODO                               |

### 集群

cluster模式参考示例：`examples/clustername.lua`

`master/slave`模式参考示例：`examples/config.c1`，`examples/config.c2`



## 配置的加载

```c
int
main(int argc, char *argv[]) {
  ...
  config.thread =  optint("thread",8);
	config.module_path = optstring("cpath","./cservice/?.so");
	config.harbor = optint("harbor", 1);
	config.bootstrap = optstring("bootstrap","snlua bootstrap");
	config.daemon = optstring("daemon", NULL);
	config.logger = optstring("logger", NULL);
	config.logservice = optstring("logservice", "logger");
	config.profile = optboolean("profile", 1);
  ...
}
```



## 用例

```
root = "./"
thread = 8
logger = nil
harbor = 2
address = "127.0.0.1:2527"
master = "127.0.0.1:2013"
start = "testmulticast2"	-- main script
bootstrap = "snlua bootstrap"	-- The service for bootstrap
--standalone = "0.0.0.0:2013"
luaservice = root.."service/?.lua;"..root.."test/?.lua;"..root.."examples/?.lua"
lualoader = "lualib/loader.lua"
-- preload = "./examples/preload.lua"	-- run preload.lua before every lua service run
snax = root.."examples/?.lua;"..root.."test/?.lua"
cpath = root.."cservice/?.so"
```



## 参考

- [Github-Config](https://github.com/cloudwu/skynet/wiki/Config)

