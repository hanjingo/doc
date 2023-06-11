# skynet源码分析-启动

<!-- vim-markdown-toc GFM -->

* [流程](#流程)
    - [1.读取配置](#1读取配置)
    - [2.启动skynet](#2启动skynet)

<!-- vim-markdown-toc -->



## 流程

### 1.读取配置

```c
// skynet main函数，所有服务的入口
int
main(int argc, char *argv[]) {
	const char * config_file = NULL ;
	if (argc > 1) {
		config_file = argv[1]; // 通过第一个参数来获取配置文件地址
	} else {
		fprintf(stderr, "Need a config file. Please read skynet wiki : https://github.com/cloudwu/skynet/wiki/Config\n"
			"usage: skynet configfilename\n");
		return 1;
	}

	skynet_globalinit();
	skynet_env_init();

	sigign();

	struct skynet_config config;

#ifdef LUA_CACHELIB
	// init the lock of code cache
	luaL_initcodecache();
#endif
	// 新建lua虚拟机并引入依赖
	struct lua_State *L = luaL_newstate();
	luaL_openlibs(L);	// link lua lib

	int err =  luaL_loadbufferx(L, load_config, strlen(load_config), "=[skynet config]", "t");
	assert(err == LUA_OK);
	lua_pushstring(L, config_file);

	err = lua_pcall(L, 1, 1, 0);
	if (err) {
		fprintf(stderr,"%s\n",lua_tostring(L,-1));
		lua_close(L);
		return 1;
	}
	_init_env(L);

	config.thread =  optint("thread",8);
	config.module_path = optstring("cpath","./cservice/?.so");
	config.harbor = optint("harbor", 1);
	config.bootstrap = optstring("bootstrap","snlua bootstrap");
	config.daemon = optstring("daemon", NULL);
	config.logger = optstring("logger", NULL);
	config.logservice = optstring("logservice", "logger");
	config.profile = optboolean("profile", 1);

	lua_close(L);

	skynet_start(&config); // 进入start方法，开始启动start
	skynet_globalexit();

	return 0;
}
```

1. 新建虚拟机
2. 读取配置文件
3. 进入`skynet_start`方法，启动skynet

### 2.启动skynet

`skynet_start.c`

```c
// 启动skynet节点
void 
skynet_start(struct skynet_config * config) {
	// register SIGHUP for log file reopen
	struct sigaction sa;
	sa.sa_handler = &handle_hup;
	sa.sa_flags = SA_RESTART;
	sigfillset(&sa.sa_mask);
	sigaction(SIGHUP, &sa, NULL);

	if (config->daemon) {
		if (daemon_init(config->daemon)) {
			exit(1);
		}
	}
	skynet_harbor_init(config->harbor);
	skynet_handle_init(config->harbor);
	skynet_mq_init();
	skynet_module_init(config->module_path);
	skynet_timer_init();
	skynet_socket_init();
	skynet_profile_enable(config->profile);
	// 创建日志服务，传递日志路径参数
	struct skynet_context *ctx = skynet_context_new(config->logservice, config->logger);
	if (ctx == NULL) {
		fprintf(stderr, "Can't launch %s service\n", config->logservice);
		exit(1);
	}

	skynet_handle_namehandle(skynet_context_handle(ctx), "logger");
	// 启动bootstrap服务
	bootstrap(ctx, config->bootstrap);
	// 创建指定的线程数量
	start(config->thread);

	// harbor_exit may call socket send, so it should exit before socket_free
	skynet_harbor_exit();
	skynet_socket_free();
	if (config->daemon) {
		daemon_exit(config->daemon);
	}
}
```

1. 启动日志服务
2. 启动bootstrap配置的服务（默认为：[snlua服务](server.md)）
3. 创建配置的线程数量

具体的启动原理请看[skynet服务#初始化#lua服务](server.md)

