# skynet服务
## 摘要
skynet服务

## 详情
- skynet_server.h
- skynet_server.c

## 知识点
pthread_getpecific和pthread_setspecific提供了在同一个线程中不同函数间共享数据即线程存储的一种方法。具体用法为：
1. 调用pthread_key_create()来创建一个类型为pthread_key_t类型的变量
> 该函数有两个参数，第一个参数就是声明的pthread_key_t变量，第二个参数是一个清理函数，用来在线程释放该线程存储的时候被调用。该函数指针可以设成NULL，这样系统将调用默认的清理函数。

2. 调用pthread_setspcific()
> 当线程中需要存储特殊值的时候调用该函数，该函数有两个参数，第一个为前面声明的pthread_key_t变量，第二个为void*变量，用来存储任何类型的值。

3. 如果需要取出所存储的值，调用pthread_getspecific()
> 该函数的参数为前面提到的pthread_key_t变量，该函数返回void*类型的值。

### 定义全局函数