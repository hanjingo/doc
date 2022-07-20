# 第十二章

[TOC]



## 12.1 引言



## 12.2 线程限制

![t12_1](res/t12_1.png)

*线程限制和sysconf的name参数*

![t12_2](res/t12_2.png)

*线程配置限制的例子*



## 12.3 线程属性

```c++
#include <pthread.h>
int pthread_attr_init(pthread_attr_t *attr);
int pthread_attr_destroy(pthread_attr_t *attr);
```

- `attr` 线程属性

  ![t12_3](res/t12_3.png)

- `返回值`

  成功：0

  失败：错误码

*初始化/反初始化线程*

```c++
#include <pthread.h>
int pthread_attr_getdetachstate(const pthread_attr_t *restrict attr, int *detachstate);
int pthread_attr_setdetachstate(pthread_attr_t *attr, int detachstate);
```

- `attr` 属性

- `detachstate` 分离状态

- `返回值`

  成功：0

  失败：错误码

*获取/设置线程分离状态*

例：

```c++
TODO
```

*以分离状态创建的线程*

```c++
#include <pthread.h>
int pthread_attr_getstack(const pthread_attr_t *restrict attr, void **restrict stackaddr, size_t *restrict stacksize);
int pthread_attr_setstack(const pthread_attr_t *attr, void *stackaddr, size_t *stacksize);
```

- `attr` 属性

- `stackaddr` 值

- `stacksize` 值

- `返回值`

  成功：0

  失败：错误码

*获取/设置线程属性stackaddr（栈地址）和stacksize（栈默认大小）*

```c++
#include <pthread.h>
int pthread_attr_getstacksize(const pthread_attr_t *restrict attr, size_t *restrict stacksize);
int pthread_attr_setstackszie(pthread_attr_t *attr, size_t stacksize);
```

- `attr` 属性

- `stacksize` 值

- `返回值`

  成功：0

  失败：错误码

*获取/设置线程属性stacksize（栈默认大小）*

```c++
#include <pthread.h>
int pthread_attr_getguardsize(const pthread_attr_t *restrict attr, size_t *restrict guardsize);
int pthread_attr_setguardsize(pthread_attr_t *attr, size_t guardsize);
```

- `attr` 属性

- `guardsize` 值

- `返回值`

  成功：0

  失败：错误码

*获取/设置线程属性guardsize（栈指针警戒线，栈溢出时可以通过信号接受到出错信息）*

```c++
#include <pthread.h>
int pthread_getconcurrency(void);
int pthread_setconcurrency(int level);
```

- `level` 并发度

- `返回值`

  成功：0

  失败：错误码

*获取/设置线程并发度（影响性能）*



## 12.4 同步属性

```c++
#include <pthread.h>
int pthread_mutexattr_init(pthread_mutexattr_t *attr);
int pthread_mutexattr_destroy(pthread_mutexattr_t *attr);
```

- `attr` 属性

- `返回值`

  成功：0

  失败：错误码

*初始化/回收互斥量属性*

```c++
#include <pthread.h>
int pthread_mutexattr_getpshared(const pthread_mutexattr_t *restrict attr, int *restrict pshared);
int pthread_mutexattr_setpshared(pthread_mutexattr_t *attr, int pshared);
```

- `attr` 互斥量属性

- `pshared` 进程共享属性值

- `返回值`

  成功：0

  失败：错误码

*获取/设置进程共享属性*

```c++
#include <pthread.h>
int pthread_mutexattr_gettype(const pthread_mutexattr_t *restrict attr, int *restrict type);
int pthread_mutexattr_settype(pthread_mutexattr_t *attr, int type);
```

- `attr` 互斥量属性

- `type` 互斥量类型

  ![t12_4](res/t12_4.png)

- `返回值`

  成功：0

  失败：错误码

*获取/设置互斥量类型*

![12_1](res/12_1.png)

*使用递归锁的情况*

![12_2](res/12_2.png)

*避免使用递归锁的情况*

例：

```c++
TODO
```

*使用递归互斥量*

```c++
#include <pthread.h>
int pthread_rwlockattr_init(pthread_rwlockattr_t *attr);
int pthread_rwlockattr_destroy(pthread_rwlockattr_t *attr);
```

- `attr` 读写锁属性

- `返回值`

  成功：0

  失败：错误码

*初始化/回收读写锁属性*

```c++
#include <pthread.h>
int pthread_rwlockattr_getpshared(const pthread_rwlockattr_t *restrict attr, int *rstrict pshared);
int pthread_rwlockattr_setpshared(pthread_rwlockattr_t *attr, int pshared);
```

- `attr`读写锁属性

- `pshared` 进程共享属性值

- `返回值`

  成功：0

  失败：错误码

*获取/设置读写锁进程共享属性*

```c++
#include <pthread.h>
int pthread_condattr_init(pthread_condattr_t *attr);
int pthread_condattr_destroy(pthread_condattr_t *attr);
```

- `attr` 条件变量属性

- `返回值`

  成功：0

  失败：错误码

*初始化/回收条件变量属性*

```c++
#include <pthread.h>
int pthread_condattr_getpshared(const pthread_condattr_t *restrict attr, int *restrict pshared);
int pthread_condattr_setpshared(pthread_condattr_t *attr, int pshared);
```

- `attr`

- `pshared`

- `返回值`

  成功：0

  失败：错误码

*获取/设置进程共享属性*



## 12.5 重入

![t12_5](res/t12_5.png)

*POSIX.1中不能保证线程安全的函数*

![t12_6](res/t12_6.png)

*替代的线程安全函数*

