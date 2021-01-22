# skynet消息队列
## 摘要
消息队列

## 详情
- skynet_mq.h
- skynet_mq.c

### 定义全局变量
```c++
#define DEFAULT_QUEUE_SIZE 64  //默认队列尺寸
#define MAX_GLOBAL_MQ 0x10000  //
#define MQ_IN_GLOBAL 1         //全局队列定义
#define MQ_OVERLOAD 1024       //过载数量
#define MESSAGE_TYPE_MASK (SIZE_MAX >> 8)            //消息类型掩码
#define MESSAGE_TYPE_SHIFT ((sizeof(size_t)-1) * 8)  //掩码后面的值
 
static struct global_queue *Q = NULL;//全局队列单例
```

### 定义全局函数
```c++
//消息放入全局队列
void skynet_globalmq_push(struct message_queue * queue);
//从全局队列弹出头节点
struct message_queue * skynet_globalmq_pop();
//创建一个队列并指定一个回调
struct message_queue * skynet_mq_create(uint32_t handle);
//释放消息队列
void skynet_mq_mark_release(struct message_queue *q);
//摧毁消息
typedef void (*message_drop)(struct skynet_message *, void *);
//释放队列
void skynet_mq_release(struct message_queue *q, message_drop drop_func, void *ud);
//返回消息队列的回调
uint32_t skynet_mq_handle(struct message_queue *);
//出队列
int skynet_mq_pop(struct message_queue *q, struct skynet_message *message);
//消息入队
void skynet_mq_push(struct message_queue *q, struct skynet_message *message);
//返回消息队列的长度
int skynet_mq_length(struct message_queue *q);
//返回队列的过载并置零
int skynet_mq_overload(struct message_queue *q);
//初始化队列
void skynet_mq_init();
```

### 定义类
```c++
//定义消息队列
struct message_queue {
	struct spinlock lock;           //自选锁
	uint32_t handle;                //回调器
	int cap;                        //容量
	int head;                       //管道头
	int tail;                       //管道尾
	int release;                    //
	int in_global;                  //是否在全局消息队列；0:不在全局消息队列,1:在全局队列或在递送中
	int overload;                   //过载数量
	int overload_threshold;         //过载阀值
	struct skynet_message *queue;   //消息
	struct message_queue *next;     //指向下一个消息队列
};
 
//全局队列
struct global_queue {
	struct message_queue *head;    //队列头
	struct message_queue *tail;    //队列尾
	struct spinlock lock;          //自旋锁
};
```

### 定义函数
```c++
//释放消息队列
static void _release(struct message_queue *q)
//队列扩充 2倍
static void expand_queue(struct message_queue *q)
```