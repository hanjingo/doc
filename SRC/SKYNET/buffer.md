# skynet 缓冲区



## 分类

```c
#define SOCKET_BUFFER_MEMORY 0 			// 内存缓冲区
#define SOCKET_BUFFER_OBJECT 1 			// 对象缓冲区
#define SOCKET_BUFFER_RAWPOINTER 2 	// Raw指针缓冲区
```

- 内存缓冲区
- 对象缓冲区
- Raw指针缓冲区



## 定义

```C
struct socket_sendbuffer { // 套接字发送缓冲区
	int id; 						// id
	int type; 					// 类型
	const void *buffer; // 数据区
	size_t sz;					// 缓冲区大小
};
```

