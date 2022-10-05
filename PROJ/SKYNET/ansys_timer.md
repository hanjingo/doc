# skynet源码分析-计时器

<!-- vim-markdown-toc GFM -->

* [原理](#原理)
    - [定义](#定义)
* [API](#api)
* [计时器溢出](#计时器溢出)
* [参考](#参考)

<!-- vim-markdown-toc -->



skynet提供了一个简单的计时器实现，可以设置一个超时时间，时间到达后给对应的服务发送消息。

## 原理

skynet计时器设计思想参考自**Linux内核动态定时器机制**；

skynet没有使用signal信号的方式来实现计时器，而是程序自身进行计时并处理计时器事件。skynet中将时间由近到远划分为5个level，时间精度是**0.01**秒（1滴答=0.01秒），每个定时器设置一个到期的滴答数，与当前系统的滴答数比较差值。

### 定义

```c
#define TIME_NEAR_SHIFT 8
#define TIME_NEAR (1 << TIME_NEAR_SHIFT)
#define TIME_LEVEL_SHIFT 6
#define TIME_LEVEL (1 << TIME_LEVEL_SHIFT)
#define TIME_NEAR_MASK (TIME_NEAR-1)
#define TIME_LEVEL_MASK (TIME_LEVEL-1)
// 计时器事件
struct timer_event {
	uint32_t handle; // 回调句柄
	int session;     // 连接
};
// 计时器节点
struct timer_node {
	struct timer_node *next; 	 // 指向下一个节点
	uint32_t expire;			// 当前节点的过期时长
};
// 计时器链表（单链表）
struct link_list {
	struct timer_node head;		// 头节点
	struct timer_node *tail;	// 尾节点
};
// 计时器集合
struct timer {
	struct link_list near[TIME_NEAR];	// 快到期的计时器集合（最大256条）
	struct link_list t[4][TIME_LEVEL];  // 根据到期事件等级组成计时器集合（最大64级）
	struct spinlock lock;			   // 自旋锁
	uint32_t time;                      // 计时器初始化之后计时器触发的次数(每百分之一秒更新一次)
	uint32_t starttime;				   // 开始时间
	uint64_t current;                   // 当前时间
	uint64_t current_point;             // b
};

static struct timer * TI = NULL; // 全局计时器单例
```



## API

- `void skynet_timer_init(void)`

  初始化计时器

- `int skynet_timeout(uint32_t handle, int time, int session)`

  - `handle` 回调器id
  - `time` 超时时间
  - `session`

  设置超时时间和回调

- `void skynet_updatetime(void) `

  更新全局计时器时间



## 计时器溢出

`timer.time`存储的是计时器初始化之后计时器的触发次数（每百分之一秒更新一次），如果程序运行时间比较长，会发生**计时器溢出**的现象；



## 参考

- [skynet API](https://github.com/cloudwu/skynet/wiki/APIList)
- [skynet源码分析之定时器skynet_timer.c](https://www.cnblogs.com/RainRill/p/8516430.html)
- [skynet源码解析：计时器](https://blog.csdn.net/suzuiyue/article/details/72713875)

