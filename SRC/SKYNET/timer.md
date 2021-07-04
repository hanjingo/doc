# skynet计时器
## 摘要
计时器

## 详情
- skynet_timer.h
- skynet_timer.c

### 定义全局变量
```c++

#define TIME_NEAR_SHIFT 8
#define TIME_NEAR (1 << TIME_NEAR_SHIFT) 		//256
#define TIME_LEVEL_SHIFT 6
#define TIME_LEVEL (1 << TIME_LEVEL_SHIFT) 	//64
#define TIME_NEAR_MASK (TIME_NEAR-1) 				//255
#define TIME_LEVEL_MASK (TIME_LEVEL-1) 			//63
 
//全局计时器单例
static struct timer * TI = NULL;
 
#define NANOSEC 1000000000 	//纳秒

#define MICROSEC 1000000		//毫秒
```

### 定义全局函数
```c++
//超时处理 handle：回调函数 time：超时时间 session:连接
int skynet_timeout(uint32_t handle, int time, int session);
//更新时间
void skynet_updatetime(void);
//获得开始时间
uint32_t skynet_starttime(void);
//获得线程时间
uint64_t skynet_thread_time(void); // for profile, in micro second
//初始化
void skynet_timer_init(void);
```

### 定义函数
```c++
//清空计时器列表,用尾指针指头,并返回第二个节点
static inline struct timer_node *link_clear(struct link_list *list)
//在尾部添加节点
static inline void link(struct link_list *list,struct timer_node *node)
//添加节点,如果快过期放入过期队列，否则放入等级队列
static void add_node(struct timer *T,struct timer_node *node)
//添加计时器 T：计时器 arg:节点 sz:节点内容长度 time:时长
static void timer_add(struct timer *T,void *arg,size_t sz,int time)
//调整指定等级的链表 T：计时器 level：等级 idx：等级下的索引
static void move_list(struct timer *T, int level, int idx)
//走过一个时间单位 T：计时器
static void timer_shift(struct timer *T)
//从当前位置开始遍历， current:指定位置开始
static inline void dispatch_list(struct timer_node *current)
//执行计时器 T:计时器
static inline void timer_execute(struct timer *T)
//更新计时器 T：计时器
static void timer_update(struct timer *T) 
//创建计时器
static struct timer *timer_create_timer()
//获得秒数和厘苗(centisecond)，1厘秒=1/100秒； sec:秒， cs:厘秒
static void systime(uint32_t *sec, uint32_t *cs)
//获得当前时间，精确到厘秒
static uint64_t gettime()
//更新时间
void skynet_updatetime(void)
//获得开始时间
uint32_t skynet_starttime(void)
//获得当前时间
uint64_t skynet_now(void)
//计时器初始化
void skynet_timer_init(void)
//获得线程时间，精确到（ms）
uint64_t skynet_thread_time(void)
```

### 定义类
```c++

//计时器事件
struct timer_event {
    uint32_t handle; 	//回调句柄
    int session;	//连接
};
 
//计时器节点
struct timer_node {
    struct timer_node *next;	//指向下一个节点
    uint32_t expire;		//当前节点过期时长
};
 
//计时器链表
struct link_list {
    struct timer_node head;	//头节点
    struct timer_node *tail;	//尾节点
};
 
//计时器集合
struct timer {
    struct link_list near[TIME_NEAR];     //快到期的计时器集合 256条
    struct link_list t[4][TIME_LEVEL];    //根据到期时间等级组成计时器集合 等级 64条
    struct spinlock lock;                 //自旋锁
    uint32_t time;
    uint32_t starttime;                   //开始时间
    uint64_t current;		          //当前时间
    uint64_t current_point;

```