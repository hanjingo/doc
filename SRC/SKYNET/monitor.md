# skynet监视器
## 摘要
skynet监视器

## 详情
- skynet_monitor.h
- skynet_monitor.c

### 定义全局函数
```c++
//新建监视器
struct skynet_monitor * skynet_monitor_new();
//删除监视器
void skynet_monitor_delete(struct skynet_monitor *);
//触发监视器
void skynet_monitor_trigger(struct skynet_monitor *, uint32_t source, uint32_t destination);
//检查监视器
void skynet_monitor_check(struct skynet_monitor *);
```

### 定义类
```c++
//监视器
struct skynet_monitor {
	int version;            //版本
	int check_version;      //检查版本
	uint32_t source;        //源
	uint32_t destination;   //触发器
};
```