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

通过调用函数`pthread_rwlock_rdlock`在读模式下锁定读写锁，通过调用函数`pthread_rwlock_wrlock`在写模式下锁定读写锁，通过调用`pthread_rwlock_unlock`进行解锁：

```c
#include <pthread.h>
int pthread_rwlock_rdlock(pthread_rwlock_t *rwlock);
int pthread_rwlock_wrlock(pthread_rwlock_t *rwlock);
int pthread_rwlock_unlock(pthread_rwlock_t *rwlock);
```

- 返回值
  - 0：成功
  - 错误码：失败

```c
#include <pthread.h>
int pthread_rwlock_tryrdlock(pthread_rwlock_t *rwlock);
int pthread_rwlock_trywrlock(pthread_rwlock_t *rwlock);
```

- 返回值
  - 0：成功
  - 错误码：失败

例，使用读写锁：

```c
#include <stdlib.h>
#include <pthread.h>

struct job {
	struct job *j_next;
  struct job *j_prev;
  pthread_t j_id;
};

struct queue {
	struct job *q_head;
  struct job *q_tail;
  pthread_rwlock q_lock;
};

int 
queue_init(struct queue *qp)
{
	int err;
  
  qp->q_head = NULL;
  qp->q_tail = NULL;
  err = pthread_rwlock_init(&qp->q_lock, NULL);
  if (err != 0)
    return (err);
  return (0);
}

void 
job_insert(struct queue *qp, struct job *jp)
{
	pthread_rwlock_wrlock(&qp->q_lock);
  jp->j_next = qp->q_head;
  jp->j_prev = NULL;
  if (qp->q_head != NULL)
    qp->q_head->j_prev = jp;
  else
    qp->q_tail = jp;
  qp->q_head = jp;
  pthread_rwlock_unlock(&qp->q_lock);
}

void 
job_append(struct queue *qp, struct job *jp)
{
	pthread_rwlock_wrlock(&qp->q_lock);
  jp->j_next = NULL;
  jp->j_prev = NULL;
  if (qp->q_head != NULL)
    qp->q_tail->j_next = jp;
  else
    qp->q_head = jp;
  qp->q_tail = jp;
  pthread_rwlock_unlock(&qp->q_lock);
}

void 
job_remove(struct queue *qp, struct job *jp)
{
	pthread_rwlock_wrlock(&qp->q_lock);
  if(jp == qp->q_head) {
  	qp->q_head = jp->j_next;
    if (qp->q_tail == jp)
      qp->q_tail = NULL;
    else
      jp->j_next->j_prev = jp->j_prev;
  } else if (jp == qp->q_tail) {
  	qp->q_tail = jp->j_prev;
    jp->j_prev->j_next = jp->j_next;
  } else {
  	jp->j_prev->j_next = jp->j_next;
    jp->j_next->j_prev = jp->j_prev;
  }
  pthread_rwlock_unlock(&qp->q_lock);
}

struct job * 
job_find(struct queue *qp, pthrad_t id)
{
	struct jpb *jp;
  if (pthread_rwlock_rdlock(&qp->q_lock) != 0)
    return (NULL);
  for (jp = qp->q_head; jp != NULL; jp = jp->j_next)
    if (pthread_equal(jp->id, id))
      break;
  
  pthread_rwlock_unlock(&qp->q_lock);
  return (jp);
}
```

### 带有超时的读写锁

Single UNIX Specification提供了带有超时的读写锁加锁函数，使应用程序在获取读写锁时避免陷入永久阻塞状态：

```c
#include <pthread.h>
#include <time.h>
int pthread_rwlock_timedrdlock(pthread_rwlock_t *restrict rwlock, 
                               const struct timespec *restrict tsptr);
int pthread_rwlock_timedwrlock(pthread_rwlock_t *restrict rwlock,
                               const struct timespec *restrict tsptr);
```

- 返回值
  - 0：成功
  - 错误码：失败

### 条件变量

由pthread_cond_t数据类型表示的条件变量可以用两种方式进行初始化，可以把常量PTHREAD_COND_INITIALIZER赋给静态分配的条件变量，但是如果条件变量是动态分配的，则需要使用`pthread_cond_init`函数对它进行初始化；

在释放条件变量底层的内存空间之前，可以使用`pthread_cond_destroy`函数对条件变量进行反初始化（deinitialize）：

```c
#include <pthread.h>
int pthread_cond_init(pthread_cond_t *restrict cond,
                      const pthread_condattr_t *restrict attr);
int pthread_cond_destroy(pthread_cond_t *cond);
```

- 返回值
  - 0：成功
  - 错误码：失败

```c
#include <pthread.h>
int pthread_cond_wait(pthread_cond_t *restrict cond, 
                      pthread_mutex_t *restrict mutex);
int pthread_cond_timewait(pthread_cond_t *restrict cond,
                          pthread_mutex_t *restrict mutex,
                          const struct timespec *restrict tsptr);
```

- 返回值
  - 0：成功
  - 错误码：失败

有两个函数可以用于通知线程条件已经满足，`pthread_cond_signal`函数至少能唤醒一个等待该条件的线程，而`pthread_cond_braodcast`函数则能唤醒等待该条件的所有线程：

```c
#include <pthread.h>
int pthread_cond_signal(pthread_cond_t *cond);
int pthread_cond_broadcast(pthread_cond_t *cond);
```

- 返回值
  - 0：成功
  - 错误码：失败

例，使用条件变量和互斥量对线程进行同步：

```c
#include <pthread.h>

struct msg {
	struct msg *m_next;
};

struct msg *workq;

pthread_cond_t qready = PTHREAD_COND_INITIALIZER;
pthread_mutex_t qlock = PTHREAD_MUTEX_INITIALIZER;

void 
process_msg(void)
{
	struct msg *mp;
  for (;;) {
  	pthread_mutex_lock(&qlock);
    while(work1 = NULL)
      pthread_cond_wait(&qready, &qlock);
    
    mp = workq;
    workq = mp->m_next;
    pthread_mutex_unlock(&qlock);
  }
}

void 
enqueue_msg(struct msg *mp)
{
	pthread_mutex_lock(&qlock);
  mp->m_next = workq;
  workq = mp;
  pthread_mutex_unlock(&qlock);
  pthread_cond_signal(&qready);
}
```

### 自旋锁

自旋锁在获取锁之前一直处于自旋（忙等）阻塞状态，此时CPU不能做其他的事情；自旋锁适用于以下特定情况：锁被持有的时间短，而且线程并不希望在重新调度上花费太多的成本；

当自旋锁用在非抢占式内核中是非常有用的：除了提供互斥机制以外，它们会阻塞中断，这样中断处理程序就不会让系统陷入死锁状态，因为它需要获取已被加锁的自旋锁（把中断想成是另一种抢占）；在这种类型的内核中，中断处理程序不能休眠，因此它们能用的同步原语只能是自旋锁；

运行在分时调度类中的用户层线程在2种情况下可以背取消调度：当它们的时间片到期时，或者具有更高调度优先级的线程就绪变成可运行时；在这些情况下，如果线程拥有自旋锁，他就会进入休眠状态，阻塞在锁上的其它线程自旋的时间可能会比预期的时间更长；

调用`pthread_spin_init`函数对自旋锁进行初始化，调用`pthread_spin_destroy`函数进行自旋锁的反初始化：

```c
#include <pthread.h>
int pthread_spin_init(pthread_spinlock_t *lock, int pshared);
int pthread_spin_destroy(pthread_spinlock_t *lock);
```

- 返回值
  - 0：成功
  - 错误码：失败

调用`pthred_spin_lock`或`pthread_spin_trylock`（无法自旋）对自旋锁进行加锁，调用`pthread_spin_unlock`解锁：

```c
#include <pthread.h>
int pthread_spin_lock(pthread_spinlock_t *lock);
int pthread_spin_trylock(pthread_spinlock_t *lock);
int pthread_spin_unlock(pthread_spinlock_t *lock);
```

- 返回值
  - 0：成功
  - 错误码：失败

**注意：不要调用在持有自旋锁情况下可能会进入休眠状态的函数，如果调用了这些函数，会浪费CPU资源，因为其它线程需要获取自旋锁需要等待的时间就延长了。**

### 屏障

屏障（barrier）是用户协调多个线程并行工作的同步机制，屏障允许每个线程等待，直到所有的合作线程都到达某一点，然后从该点继续执行；

调用`pthread_barrier_init`函数对屏障进行初始化，调用`thread_barrier_destroy`函数反初始化：

```c
#include <pthread.h>
int pthread_barrier_init(pthread_barrier_t *restrict barrier,
                         const pthread_barrierattr_t *restrict attr,
                         unsigned int count);
int pthread_barrier_destroy(pthread_barrier_t *barrier);
```

- 返回值
  - 0：成功
  - 错误码：失败

初始化屏障时，可以使用count参数指定，在允许所有线程继续运行之前，必须到达屏障的线程数目；

调用`pthread_barrier_wait`函数来表明线程已完成工作：

```c
#include <pthread.h>
int pthread_barrier_wait(pthread_barrier_t *barrier);
```

- 返回值
  - 0或PTHREAD_BARRIER_SERIAL_THREAD：成功
  - 错误码：失败

对于一个任意线程，`pthread_barrier_wait`函数返回了`PTHREAD_BARRIER_SERIAL_THREAD`；剩下的线程看到的返回值是0，这使得一个线程可以作为主线程，它可以工作在其它所有线程已完成的工作结果上；

一旦达到屏障计数值，而且线程处于非阻塞状态，屏障就可以被重用；但是除非在调用了`pthread_barrier_destroy`函数之后，又调用了`pthread_barrier_init`函数对计数用另外的数进行初始化，否则屏障计数不会改变；

例，在一个任务上合作的多个线程之间如何用屏障进行同步；

```c
#include "apue.h"
#include <pthread.h>
#include <limits.h>
#include <sys/time.h>

#define NTHR 8
#define NUMNUM 8000000L
#define TNUM (NUMNUM/NTHR)

long nums[NUMNUM];
long snums[NUMNUM];

pthread_barrier_t b;

#ifdef SOLARIS
#define heapsort qsort
#else
extern int heapsort(void *, size_t, size_t,
                    int (*)(const void *, const void *));
#endif

int 
complong(const void *arg1, const void *args)
{
	long l1 = *(long *)arg1;
  long l2 = *(long *)arg2;
  
  if (l1 == l2)
    return 0;
  else if (l1 < l2)
    return -1;
  else
    return 1;
}

void * 
thr_fn(void *arg)
{
	long idx = (long)arg;
  heapsort(&nums[idx], TNUM, sizeof(long), complong);
  pthread_barrier_wait(&b);
  return ((void *)0);
}

void 
merge()
{
	long idx[NTHR];
  long i, minidx, sidx, num;
  
  for (i = 0; i < NTHR; i++)
    idx[i] = i * TNUM;
  for (sidx = 0; sidx < NUMNUM; sidx++) {
  	num = LONG_MAX;
    for (i = 0; i < NTHR; i++) {
    	if ((idx[i] < (i+1)*TNUM) && (nums[idx[i]] < num)) {
      	num = nums[idx[i]];
        minidx = i;
      }
    }
    snums[sidx] = nums[idx[minidx]];
    idx[minidx]++;
  }
}

int 
main()
{
	unsigned long i;
  struct timeval start, end;
  long long startusec, endusec;
  double elapsed;
  int err;
  pthread_t tid;
  
  srandom(1);
  for (i = 0; i < NUMNUM; i++)
    nums[i] = random();
  
  gettimeofday(&start, NULL);
  pthread_barrier_init(&b, NULL, NTHR + 1);
  for (i = 0; i < NTHR; i++) {
  	err = pthread_create(&tid, NULL, thr_fn, (void *)(i * TNUM));
    if (err != 0)
      err_exit(err, "can't create thread");
  }
  pthread_barrier_wait(&b);
  merge();
  gettimeofday(&end, NULL);
  
  startusec = start.tv_sec * 1000000 + start.tv_usec;
  endusec = end.tv_sec * 1000000 + end.tv_usec;
  elapsed = (double)(endusec - startusec) / 1000000.0;
  printf("sort took %.4f seconds\n", elapsed);
  for (i = 0; i < NUMNUM; i++)
    printf("%1d\n", snums[i]);
  exit(0);
}
```



