

[TOC]

# skynet模块机制



## 模块定义

```c
// skynet模块
struct skynet_module {
	const char * name;			// 模块名字
	void * module;				// 模块的句柄，通过dlopen函数获得
	skynet_dl_create create;	// 创建函数
	skynet_dl_init init;		// 初始化函数
	skynet_dl_release release;	// 释放函数
	skynet_dl_signal signal;	// 处理信号函数
};
```



## 模块实现

一个模块本质就是一个动态链接库文件，它必须要实现以下接口(xxx为动态链接库文件名)：

### xxx_create

`typedef void * (*skynet_dl_create)(void) `

### xxx_init

`typedef int (*skynet_dl_init)(void * inst, struct skynet_context *, const char * parm)`

- `inst` 当前module实例
- `skynet_context` 上下文
- `parm` 参数

初始化模块，指定消息的回调函数；

### xxx_release

`typedef void (*skynet_dl_release)(void * inst)`

释放模块

### xxx_signal

TODO



## 模块管理

skynet限制了最大模块数量：

```c
#define MAX_MODULE_TYPE 32 // 最大模块数量
```

skynet 通过modules来管理模块，其定义如下：

```c
// 模块集合
struct modules {
	int count; 									// 模块类型id
	struct spinlock lock; 						// 自旋锁
	const char * path; 							// 模块集合的共有路径
	struct skynet_module m[MAX_MODULE_TYPE]; 	// 模块集合
};
static struct modules * M = NULL; // 模块集合单例
```

### 模块文件加载

```c
void *dlopen(const char *filename, int flags)
```

类unix系统提供了函数`dlopen`来加载动态链接库文件，它会按照相应的逻辑来搜索文件。

具体参考本项目的：操作系统#动态链接库

### 模块文件解析

```c
void *dlsym(void *handle, const char *symbol)
```

类unix系统提供了函数`dlsym`来解析动态链接库符号，返回符号对应的地址。

具体参考本项目的：操作系统#动态链接库

### 模块文件释放

```c
int dlclose(void *handle)
```

类unix系统提供了函数`dlclose`来关闭指定句柄的动态链接库；**注意：只有当此动态链接库的使用计数为0时，才会真正被系统卸载。**

具体参考本项目的：操作系统#动态链接库



## 服务上下文

skynet在创建完`module`实例并初始化后，同时创建了一个`skynet_context`，并将`module`实例和`skynet_context`关联起来，最后放置于`handle_storage`的`slot`里面，这样一个个独立的沙盒环境就这样被创建出来了。

详情请看:[skynet服务](server.md)



## 回调

### C服务回调

```c
typedef int (*skynet_cb)(struct skynet_context * context, void *ud, int type, int session, uint32_t source , const void * msg, size_t sz)
```

- `context` 上下文
- `ud` 一般是instance指针
- `type` 消息类型
- `session` 凭证
- `source` 发送方的服务id
- `msg` 数据
- `sz` 数据大小

当消息到达`skynet_context`时，会调用`skynet_cb`

### LUA服务回调

TODO



## 参考

- [skynet源码分析（10）--消息机制之注册和回调](https://blog.csdn.net/119365374/article/details/77460685)
- [Skynet服务器框架（八） 任务和消息调度机制](https://blog.csdn.net/linshuhe1/article/details/73854411)

