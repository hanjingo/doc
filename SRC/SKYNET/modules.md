

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
	int count; // 模块类型id
	struct spinlock lock; // 自旋锁
	const char * path; // 模块集合的共有路径
	struct skynet_module m[MAX_MODULE_TYPE]; // 模块集合
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



## 上下文

skynet在创建完`module`实例并初始化后，同时创建了一个`skynet_context`，并将`module`实例和`skynet_context`关联起来，最后放置于`handle_storage`的`slot`里面，这样一个个独立的沙盒环境就这样被创建出来了。

`skynet_context`的定义如下：

```c
// skynet模块上下文
struct skynet_context {
	void * instance; 				// 由模块的create函数创建的实例指针
	struct skynet_module * mod; 	// module对象指针
	void * cb_ud;					// 传递给消息回调函数的userdata
	skynet_cb cb;					// 消息回调函数，由模块的init函数来指定
	struct message_queue *queue;	// 内部消息队列
	ATOM_POINTER logfile;			// 日志
	uint64_t cpu_cost;				// cpu耗费事件（ms）
	uint64_t cpu_start;				// cpu开始时间（ms）
	char result[32];				// 返回值
	uint32_t handle;				// 当前上下文的ID
	int session_id;					// 标识对应的请求
	ATOM_INT ref;					// 引用计数变量，为0表示可以背释放
	int message_count;				// 消息数量统计
	bool init;						// 是否已初始化
	bool endless;					// 消息是否堵住
	bool profile;

	CHECKCALLING_DECL
};
```

### 对消息的处理

1. 当消息到达`skynet_context`时，会调用`callback`
2. 在调用`callback`时传入以下参数：
   - `userdata` 一般是instance指针
   - `source` 发送方的服务id
   - `type` 消息类型
   - `msg` 数据
   - `sz` 数据大小
