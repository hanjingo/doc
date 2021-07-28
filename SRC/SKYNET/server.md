# skynet服务
`pthread_getpecific`和`pthread_setspecific`提供了在同一个线程中不同函数间共享数据即线程存储的一种方法。具体用法为：

1. 调用`pthread_key_create()`来创建一个类型为`pthread_key_t`类型的变量

   该函数有两个参数，第一个参数就是声明的`pthread_key_t`变量，第二个参数是一个清理函数，用来在线程释放该线程存储的时候被调用。该函数指针可以设成`NULL`，这样系统将调用默认的清理函数。

2. 调用`pthread_setspcific()`

   当线程中需要存储特殊值的时候调用该函数，该函数有两个参数，第一个为前面声明的`pthread_key_t`变量，第二个为`void*`变量，用来存储任何类型的值。

3. 如果需要取出所存储的值，调用`pthread_getspecific()`

   该函数的参数为前面提到的`pthread_key_t`变量，该函数返回`void*`类型的值。

