# skynet配置



## 定义

```c
// skynet配置
struct skynet_config {
	int thread;								// 可创建的最大线程数量
	int harbor;								// 
	int profile;							// 是否做简略的消息统计
	const char * daemon;			// 记录进程id的文件路径
	const char * module_path;	// 模块路径
	const char * bootstrap;		// 初始化参数
	const char * logger;			// 日志路径
	const char * logservice;	// 日志模块名
};
```



## 用例

```
include "config.path"

-- preload = "./examples/preload.lua"	-- run preload.lua before every lua service run
thread = 8
logger = nil
logpath = "."
harbor = 1
address = "127.0.0.1:2526"
master = "127.0.0.1:2013"
start = "main"	-- main script
bootstrap = "snlua bootstrap"	-- The service for bootstrap
standalone = "0.0.0.0:2013"
-- snax_interface_g = "snax_g"
cpath = root.."cservice/?.so"
-- daemon = "./skynet.pid"
```

