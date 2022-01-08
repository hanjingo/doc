# 第11章 线程

[TOC]



## 线程概念

- 通过为美中事件类型分配单独的处理线程，可以简化处理异步事件的代码；
- 多个进程必须使用操作系统提供的复杂机制才能实现内存和文件描述符的共享，而多个线程自动地可以访问相同的存储地址空间和文件描述符；
- 对问题进行分解可以提高整个程序的吞吐量；
- 交互的程序同样可以通过使用多线程来改善响应时间，多线程可以把程序中处理用户输入输出的部分与其他部分分开；



## 线程标识

进程ID在整个系统中是唯一的，线程ID只有在它所属进程上下文中才有意义；

使用`pthread_equal`函数对两个线程ID进行比较：

```c
#include <pthread.h>
int pthread_equal(pthread_t tid1, pthread_t tid2);
```

- 返回值
  - 非0：相等
  - 0：不相等

使用`pthread_self`函数获得自身的线程ID：

```c
#include <pthread.h>
pthread_t pthread_self(void);
```

- 返回值
  - 调用线程的线程ID



## 线程创建

使用`pthread_create`函数创建一条线程：

```c
#include <pthread.h>
int pthread_create(pthread_t *restrict tidp, 
                   const pthread_attr_t *restrict attr, 
                   void *(*start_rtn)(void *),
                   void *restrict arg);
```

- 返回值
  - 0：成功
  - 错误码：失败

注意：线程创建时并不能保证哪个线程会先运行；

例，打印进程，新线程以及初始线程ID：

```c
#include "apue.h"
#include <pthread.h>

pthread_t ntid;

void
printids(const char* s)
{
	pid_t     pid;
  pthread_t tid;
  
  pid = getpid();
  tid = pthread_self();
  printf("%s pid %1u tid %1u (0x%1x)\n", s, (unsigned long)pid, (unsigned long)tid, (unsigned long)tid);
}

void
thr_fn(void *arg)
{
	printids("new thread: ");
  return((void *)0);
}

int
main(void)
{
	int err;
  err = pthread_create(&ntid, NULL, thr_fn, NULL);
  if (err != 0)
    err_exit(err, "can't create thread");
  printids("main thread:");
  sleep(1);
  exit(0);
}
```



## 线程终止

单个线程可以通过以下方式退出：

- 线程可以简单地从启动例程中返回，返回值是线程的退出码；
- 线程可以被同一进程中的其它线程取消；
- 线程调用`pthread_exit`函数；

调用`pthread_exit`函数退出线程：

```c
#include <pthread.h>
void pthread_exit(void *rval_ptr);
```

- `rval_ptr` 一个无类型指针，与传给启动例程的单个参数类似；

调用`pthread_join`函数分离线程，恢复资源：

```c
#include <pthread.h>
int pthread_join(pthread_t thread, void **rval_ptr);
```

- 返回值
  - 0：成功
  - 错误码：失败

例，获取已终止的线程的退出码：

```c
#include "apue.h"
#include <pthread.h>

void *
thr_fn1(void *arg)
{
	printf("thread 1 returning\n");
  return((void *)1);
}

void *
thr_fn2(void *arg)
{
	printf("thread 2 exiting\n");
  pthread_exit((void *)2);
}

int
main(void)
{
	int err;
  pthread_t tid1, tid2;
  void *tret;
  err = pthread_create(&tid1, NULL, thr_fn1, NULL);
  if (err != 0)
    err_exit(err, "can't create thread 1");
  err = pthread_create(&tid2, NULL, thr_fn2, NULL);
  if (err != 0)
    err_exit(err, "can't create thread 2");
  err = pthread_join(tid1, &tret);
  if (err != 0)
    err_exit(err, "can't create thread 2");
  printf("thread 1 exit code %1d\n", (long)tret);
  err = pthread_join(tid2, &tret);
  if (err != 0)
    err_exit(err, "can't join with thread 2");
  printf("thread 2 exit code %1d\n", (long)tret);
  exit(0);
}
```

例，pthread_exit参数的不正确使用：

```c
#include "apue.h"
#include <pthread.h>

struct foo {
	int a, b, c, d;
};

void printfoo(const char *s, const struct foo *fp)
{
	printf("%s", s);
  printf(" structure at 0x%1x\n", (unsigned long)fp);
  printf(" foo.a = %d\n", fp->a);
  printf(" foo.b = %d\n", fp->b);
  printf(" foo.c = %d\n", fp->c);
  printf(" foo.d = %d\n", fp->d);
}

void *
thr_fn1(void *arg)
{
	struct foo foo = {1, 2, 3, 4};
  printfoo("thread 1:\n", &foo);
  pthread_exit((void *)&foo);
}

void *
thr_fn2(void *arg)
{
	printf("thread 2: ID is %1u\n", (unsigned long)pthread_self());
  pthread_exit((void *)0);
}

int main(void)
{
	int err;
  pthread_t tid1, tid2;
  struct foo *fp;
  
  err = ptherad_create(&tid1, NULL, thr_fn1, NULL);
  if (err != 0)
    err_exit(err, "can't create thread 1");
  err = pthread_join(tid1, (void *)&fp);
  if (err != 0)
    err_exit(err, "can't join with thread 1");
  sleep(1);
  printf("parent starting second thread\n");
  err = pthread_create(&tid2, NULL, thr_fn2, NULL);
  if (err != 0)
    err_exit(err, "can't create thread 2");
  sleep(1);
  printfoo("parent:\n", fp);
  exit(0);
}
```

线程可以通过调用`pthread_cancel`函数来请求取消同一进程中的其它线程：

```c
#include <pthread.h>
int pthread_cancel(pthread_t tid);
```

- 返回值
  - 0：成功
  - 错误码：失败

线程可以通过调用`thread_cleanup_xx`函数来指定退出时需要执行的操作：

```c
#include <pthread.h>
void pthread_cleanup_push(void(*rtn)(void *), void *arg);
void pthread_cleanup_pop(int execute);
```

当线程执行以下动作：

- 调用pthread_exit时；
- 响应取消请求时；
- 用非零execute参数调用pthread_cleanup_pop时；

清理函数rtn是由`pthread_cleanup_push`函数调度的，调用时只有一个参数arg；

例，使用线程清理处理程序：

```c
#include "apue.h"
#include <pthread.h>

void
cleanup(void *arg)
{
	printf("cleanup:%s\n", (char *)arg);
}

void *
thr_fn1(void *arg)
{
	printf("thread 1 start\n");
  pthread_cleanup_push(cleanup, "thread 1 first handler");
  pthread_cleanup_push(cleanup, "thread 1 second handler");
  print("thread 1 push complete\n");
  if (arg)
    return ((void *)1);
  pthread_cleanup_pop(0);
  pthread_cleanup_pop(0);
  return ((void *)1);
}

void *
thr_fn2(void *arg)
{
	printf("thread 2 start\n");
  pthread_cleanup_push(cleanup, "thread 2 first handler");
  pthread_cleanup_push(cleanup, "thread 2 second handler");
  printf("thread 2 push complete\n");
  if (arg)
    pthread_exit((void *)2);
  pthread_cleanup_pop(0);
  pthread_cleanup_pop(0);
  pthread_exit((void *)2);
}

int
main(void)
{
	int err;
  pthread_t tid1, tid2;
  void *tret;
  
  err = pthread_create(&tid1, NULL, thr_fn1, (void *)1);
  if (err != 0)
    err_exit(err, "can't create thread 1");
  err = pthread_create(&tid2, NULL, thr_fn2, (void *)1);
  if (err != 0)
    err_exit(err, "can't create thread 2");
  err = pthread_join(tid1, &tret);
  if (err != 0)
    err_exit(err, "can't join with thread 1");
  printf("thread 1 exit code %1d\n", (long)tret);
  err = pthread_join(tid2, &tret);
  if (err != 0)
    err_exit(err, "can't join with thread 2");
  printf("thread 2 exit code %1d\n", (long)tret);
  exit(0);
}
```

进程和线程函数比较：

| 进程函数 | 线程函数            | 描述                         |
| -------- | ------------------- | ---------------------------- |
| fork     | pthread_create      | 创建新的控制流               |
| exit     | pthread_exit        | 从现有的控制流中退出         |
| waitpid  | pthread_join        | 从控制流中得到退出状态       |
| atexit   | pthread_cancel_push | 注册在退出控制流时调用的函数 |
| getpid   | pthread_self        | 获取控制流的ID               |
| abort    | pthread_cancel      | 请求控制流的非正常退出       |

线程调用`pthread_detach`分离线程：

```c
#include <pthread.h>
int pthread_detach(pthread_t tid);
```

- 返回值
  - 0：成功
  - 错误码：失败



## 线程同步

### 互斥量

互斥量（mutex）从本质上说是一把锁，在访问共享资源前对互斥量进行加锁，在访问完成后解锁；

线程通过`pthread_mutex_init`进行初始化，通过`pthread_mutex_destroy`释放内存：

```c
#include <pthread.h>
int pthread_mutex_init(pthread_mutex_t *restrict mutex,
                       const pthread_mutexattr_t *restrict attr);
int pthread_mutex_destroy(pthread_mutex_t *mutex);
```

- 返回值
  - 0：成功
  - 错误码：失败

线程通过`pthread_mutex_lock`对互斥量进行加锁，通过`pthread_mutex_unlock`对互斥量进行解锁，通过`pthread_mutex_trylock`尝试对互斥量进行加锁：

```c
#include <pthread.h>
int pthread_mutex_lock(pthread_mutex_t *mutex);
int pthread_mutex_trylock(pthread_mutex_t *mutex);
int pthread_mutex_unlock(pthread_mutex_t *mutex);
```

- 返回值
  - 0：成功
  - 错误码：失败

例，使用互斥量保护数据结构：

```c
#include <stdlib.h>
#include <pthread.h>

struct foo {
	int f_count;
  pthread_mutex_t f_lock;
  int f_id;
};

struct foo *
foo_alloc(int id)
{
	struct foo *fp;
  if ((fp = malloc(sizeof(struct foo))) != NULL) {
  	fp->f_count = 1;
    fp->f_id = id;
    if (pthread_mutex_init(&fp->f_lock, NULL) != 0) {
    	free(fp);
      return (NULL);
    }
  }
  return (fp);
}

void
foo_hold(struct foo *fp)
{
	pthread_mutex_lock(&fp->f_lock);
  fp->f_count++;
  pthread_mutex_unlock(&fp->f_lock);
}

void
foo_rele(struct foo *fp)
{
	pthread_mutex_lock(&fp->f_lock);
  if (--fp->f_count == 0) {
  	pthread_mutex_unlock(&fp->f_lock);
    pthread_mutex_destroy(&fp->f_lock);
    free(fp);
  } else {
  	pthread_mutex_unlock(&fp->f_lock);
  }
}
```

### 避免死锁

例，使用`pthread_mutex_trylock`接口避免死锁：

```c
#include <stdlib.h>
#include <pthread.h>

#define NHASH 29
#define HASH(id) (((unsigned long)id)%NHASH)

struct foo *fh[NHASH];
pthread_mutex_t hashlock = PTHREAD_MUTEX_INITIALIZER:

struct foo {
	int             f_count;
  pthread_mutex_t f_lock;
  int             f_id;
  struct foo     *f_next;
};

struct foo* 
foo_alloc(int id)
{
	struct foo *fp;
  int        idx;
  
  if ((fp = malloc(sizeof(struct foo))) != NULL) {
  	fp->f_count = 1;
    fp->f_id = id;
    if (pthread_mutex_init(&fp->f_lock, NULL) != 0) {
    	free(fp);
      return (NULL);
    }
    idx = HASH(id);
    pthread_mutex_lock(&hashlock);
    fp->f_next = fh[idx];
    fh[idx] = fp;
    pthread_mutex_lock(&fp->f_lock);
    pthread_mutex_unlock(&hashlock);
    pthread_mutex_unlock(&fp->f_lock);
  }
  return (fp);
}

void 
foo_hold(struct foo *fp)
{
	pthread_mutex_lock(&hashlock);
  fp->f_count++;
  pthread_mutex_unlock(&hashlock);
}

struct foo * 
foo_find(int id)
{
	struct foo *fp;
  pthread_mutex_lock(&hashlock);
  for (fp = fh[HASH(id)]; fp != NULL; fp = fp->f_next) {
  	if (fp->f_id == id) {
    	foo_hold(fp);
      break;
    }
  }
  pthread_mutex_unlock(&hashlock);
  return (fp);
}

void 
foo_rele(struct foo *fp)
{
	struct foo *tfp;
  int        idx;
  
  pthread_mutex_lock(&hashlock);
  if (fp->f_count == 1) {
    idx = HASH(fp->f_id);
    tfp = fh[idx];
    if (tfp == fp) {
    	fh[idx] = fp->f_next;
    } else {
    	while (tfp->f_next != fp)
        tfp = tfp->f_next;
      tfp->f_next = fp->f_next;
    }
    pthread_mutex_unlock(&hashlock);
    pthread_mutex_destroy(&fp->f_lock);
    free(fp);
  } else {
    pthread_mutex_unlock(&hashlock);
  }
}
```

**注意：如果锁的粒度太粗，就会出现很多线程阻塞等待相同的锁，这可能并不能改善并发性；如果锁的粒度太细，那么过多的锁开销会使系统性能收到影响，而且代码变得复杂；**

### 函数pthread_mutex_timelock

线程使用`pthread_mutex_timelock`互斥量绑定线程阻塞时间，在达到超时时间时不会对互斥量进行加锁，而是返回错误码`ETIMEDOUT`；

```c
#include <pthread.h>
#include <time.h>
int pthread_mutex_timedlock(pthread_mutex_t *restrict mutex,
                            const struct timespec *restrict tsptr);
```

- 返回值

  - 0：成功
  - 错误码：失败

例，用`pthread_mutex_timedlock`避免永久阻塞：

```c
#include "apue.h"
#include <pthread.h>

int 
main(void)
{
	int err;
  struct timespec tout;
  struct tm *tmp;
  char buf[64];
  pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
  
  pthread_mutex_lock(&lock);
  printf("mutex is locked\n");
  clock_gettime(CLOCK_REALTIME, &tout);
  tmp = localtime(&tout.tv_sec);
  strftime(buf, sizeof(buf), "%r", tmp);
  printf("current time is %s\n", buf);
  tout.tv_sec += 10;
  err = pthread_mutex_timedlock(&lock, &tout);
  clock_gettime(CLOCK_REALTIME, &tout);
  tmp = localtime(&tout.tv_sec);
  strftime(buf, sizeof(buf), "%r", tmp);
  printf("the time is now %s\n", buf);
  if (err == 0)
    printf("mutex locked again!\n");
  else
    printf("can't lock mutex again:%s\n", strerror(err));
  exit(0);
}
```

### 读写锁

读写锁（共享互斥锁，shared-exclusive lock）非常适合于读的次数远大于写的情况，读写锁的3种状态：

- 写加锁

  在这个锁被解锁前，所有试图对这个锁加锁的线程都会被阻塞；

- 读加锁

  所有试图以读模式对它进行加锁的线程都可以得到访问权，但是任何希望以写模式对此锁进行加锁的线程都会阻塞，直到所有的线程释放它们的读锁为止；

  如果有一个线程试图以写模式获取锁时，读写锁通常会阻塞随后的读模式锁请求，这样可以避免读模式锁长期占用，而等待的写模式锁请求一直得不到满足；

- 不加锁

读写锁通过调用函数`pthread_rwlock_init`进行初始化，通过调用函数`pthread_rwlock_destroy`做清理工作：

```c
#include <pthread.h>
int pthread_rwlock_init(pthread_rwlock_t *restrict rwlock,
                        const pthread_rwlockattr_t *restrict attr);
int pthread_rwlock_destroy(pthread_rwlock_t *rwlock);
```

- 返回值
  - 0：成功
  - 错误码：失败

读写锁通过调用函数`pthread_rwlock_rdlock`



