[TOC]

# skynet消息机制



## 消息定义

skynet消息的定义如下：

```c
// 消息
struct skynet_message {
	uint32_t source;// 发送方地址
	int session;    // 消息id，用来找对应的协程
	void * data;    // 消息内容地址
	size_t sz;      // 消息大小
};
```



## 消息协议

### 请求协议(待确定)

协议规定超过32kbyte的数据包需要分成小包传输，小包依赖session来区隔；

| 包头  | type  | 其它 |
| ----- | ----- | ---- |
| 2byte | 1byte | 变长 |

- `type`

  用于区分这是一个完整的小包，还是大包的一部分，参数说明如下:

  - `0` 表示这是一个**不超过32kbyte的完整包**，其结构如下：

    | 包头  | type  | 目的地址（id） | session | 包内容     |
    | ----- | ----- | -------------- | ------- | ---------- |
    | 2byte | 1byte | 4byte          | 4byte   | 0～32kbyte |

    如果session为0，表示这是一个推送包，不需要回应

  - `1` 表示这是一个超过32kbyte的**请求**，包本身没有数据内容，内容在对应的`0x81`处。其结构如下：

    | 包头  | type  | 目的地址（id） | session | 包总长（小端） |
    | ----- | ----- | -------------- | ------- | -------------- |
    | 2byte | 1byte | 4byte          | 4byte   | 4byte          |

  - `2` 表示这是一个长消息的一部分，且**后续还有数据**，其结构如下：

    | 包头  | type  | session | 包内容 |
    | ----- | ----- | ------- | ------ |
    | 2byte | 1byte | 4byte   |        |

  - `3` 表示这是一个长消息的一部分，且**这是最后一个包**，其结构如下：

    | 包头  | type  | session | 包内容 |
    | ----- | ----- | ------- | ------ |
    | 2byte | 1byte | 4byte   |        |

  - `0x41` 表示这是一个超过32kbyte的**推送**，包本身没有数据内容，内容在对应的`0xc1`处。其结构如下：

    | 包头  | type  | 目的地址（id） | session | 包总长（小端） |
    | ----- | ----- | -------------- | ------- | -------------- |
    | 2byte | 1byte | 4byte          | 4byte   | 4byte          |

  - `0x80` 类似0，表示这是一个**不超过32kbyte的完整包**，结构如下：

    | 包头  | type  | 目的地址（字符串） | session | 包内容     |
    | ----- | ----- | ------------------ | ------- | ---------- |
    | 2byte | 1byte | 变长(0~255byte)    | 4byte   | 0～32kbyte |

  - `0x81` 对应1

  - `0xc1` 对应0x41

### 响应协议

TODO



## 消息类型

### 进程内消息

用于进程内部的消息通信，其结构为：

```c
// 进程内部的请求消息
struct request_package {
	uint8_t header[8];	// 6 bytes dummy
	union {
		char buffer[256];
		struct request_open open;
		struct request_send send;
		struct request_send_udp send_udp;
		struct request_close close;
		struct request_listen listen;
		struct request_bind bind;
		struct request_resumepause resumepause;
		struct request_setopt setopt;
		struct request_udp udp;
		struct request_setudp set_udp;
	} u;
	uint8_t dummy[256];
};
```

该请求消息包括以下类型：

- `request_open`
- `request_send`
- `request_send_udp`
- `request_close`
- `request_listen`
- `request_bind`
- `request_resumepause`
- `request_setopt`
- `request_udp`
- `request_setudp`

### 跨进程消息

TODO



## 消息队列

消息队列定义如下：

```c
// 消息队列
struct message_queue {
	struct spinlock lock; // 自旋锁
	uint32_t handle; 				// 回调器ID
	int cap; 						// 容量
	int head; 						// 管道头索引
	int tail; 						// 管道尾索引
	int release; 					// 是否能释放消息
	int in_global; 					// 是否在全局消息队列；0:不在全局消息队列,1:在全局队列或在递送中
	int overload; 					// 过载数量
	int overload_threshold; 		// 过载阀值
	struct skynet_message *queue; 	// 消息队列
	struct message_queue *next; 	// 指向下一个消息队列
};
```

### 消息队列扩充

在push消息时，如果`head==tail`，表示消息队列已满，需要扩充，源码如下：

```c
static void
expand_queue(struct message_queue *q) {
	struct skynet_message *new_queue = skynet_malloc(sizeof(struct skynet_message) * q->cap * 2);
	int i;
	for (i=0;i<q->cap;i++) {
		new_queue[i] = q->queue[(q->head + i) % q->cap];
	}
	q->head = 0;
	q->tail = q->cap;
	q->cap *= 2;
	
	skynet_free(q->queue);
	q->queue = new_queue;
}
```

1. 队列cap扩充2倍
2. 从头到尾重新赋值



## 消息流向

```mermaid
graph TD
subgraph 进入socket线程处理流程
thread_socket(skynet_socket_poll)--循环调用-->
thread_socket-->
socket_server_poll(socket_server_poll<br>处理socket事件,建立/监听/接收消息<br><br>forward_message<br>读一个消息)-->
skynet_context_push(skynet_context_push<br>将上下文推入消息队列)-->
skynet_mq_push(skynet_mq_push<br>将消息推入消息队列)
==> is_mq_full{消息队列是否已满}
is_mq_full -.yes<br>.-> expand_queue(expand_queue<br>扩充队列)-->skynet_globalmq_push
is_mq_full -.no.->
skynet_globalmq_push(skynet_globalmq_push<br>消息推入全局消息队列)
end

subgraph 进入全局消息队列处理流程
skynet_globalmq_push-->
thread_worker(thread_worker<br>循环工作线程)-->
skynet_context_message_dispatch(skynet_context_message_dispatch<br>分派消息上下文)-->
skynet_globalmq_pop(skynet_globalmq_pop<br>从全局消息队列pop出一个次级消息队列)
==> is_null{次级消息队列是否为NULL}
is_null -.yes.->
exit(退出工作线程)

is_null -.no.->
skynet_mq_handle(skynet_mq_handle<br>从次级消息队列获取回调器id)-->
skynet_handle_grab(skynet_handle_grab<br>根据回调器id拿上下文)

==> is_ctx_null{上下文是否为NULL}
is_ctx_null -.yes.->
drop_message(drop_message<br>丢掉消息)--继续循环-->
skynet_context_message_dispatch

is_ctx_null -.no.->
skynet_monitor_trigger(skynet_monitor_trigger<br>触发监视器)-->
dispatch_message(dispatch_message<br>派发消息传递给lua虚拟机)-->
lua_callback(进入回调)
end

subgraph 进入lua虚拟机处理流程
lua_callback-->lua_logic(业务逻辑)
end
```

## 参考

- [skynet源码赏析](https://manistein.github.io/blog/post/server/skynet/skynet%E6%BA%90%E7%A0%81%E8%B5%8F%E6%9E%90/)
- [云风的BLOG - skynet cluster 模块的设计与编码协议](https://blog.codingnow.com/2017/03/skynet_cluster.html)