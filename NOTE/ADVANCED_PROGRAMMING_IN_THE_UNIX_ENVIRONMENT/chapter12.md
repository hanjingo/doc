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

  | 名称        | 描述                                 | FreeBSD 5.2.1 | Linux 2.4.22 | Mac OS X 10.3 | Solaris 9 |
  | ----------- | ------------------------------------ | ------------- | ------------ | ------------- | --------- |
  | detachstate | 线程的分离状态属性                   | *             | *            | *             | *         |
  | guardsize   | 线程栈末尾的警戒缓冲区大小（字节数） |               | *            | *             | *         |
  | stackaddr   | 线程栈的最低地址                     | ob            | *            | *             | ob        |
  | stacksize   | 线程栈的最小长度（字节数）           | *             | *            | *             | *         |

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
#include "apue.h"
#include <pthread.h>
int 
makethread(void *(*fn)(void *), void *arg)
{
    int err;
    pthread_t tid;
    pthread_attr_t attr;
    err = pthread_attr_init(&attr);
    if (err != 0)
        return(err);
    err = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    if (err == 0)
        err = pthread_create(&tid, &attr, fn, arg);
    pthread_attr_destroy(&attr);
    return(err);
}
```

*以分离状态创建的线程*

```c++
#include <pthread.h>
int pthread_attr_getstack(const pthread_attr_t *restrict attr, void **restrict stackaddr, size_t *restrict stacksize);
int pthread_attr_setstack(const pthread_attr_t *attr, void *stackaddr, size_t *stacksize);
```

- `attr` 属性

- `stackaddr` 栈地址指针

- `stacksize` 栈默认大小

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

- `guardsize` 栈指针警戒线

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

### 12.4.1 互斥量属性

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
int pthread_mutexattr_getrobust(const pthread_mutexattr_t *restrict attr, int *restrict robust);
int pthread_mutexattr_setrobust(pthread_mutexattr_t *attr, int robust);
```

- `attr` 互斥量属性

- `robust` 健壮属性

- `返回值`

  成功：0

  失败：错误码

*获取/设置 健壮的互斥量属性*

```c++
#include <pthread.h>
int pthread_mutex_consistent(pthread_mutex_t *mutex);
```

- `mutex` 互斥量

- `返回值`

  成功：0

  失败：错误码

*设置互斥量一致（解除`ENOTRECOVERABLE`状态）*

```c++
#include <pthread.h>
int pthread_mutexattr_gettype(const pthread_mutexattr_t *restrict attr, int *restrict type);
int pthread_mutexattr_settype(pthread_mutexattr_t *attr, int type);
```

- `attr` 互斥量属性

- `type` 互斥量类型

  | 互斥量类型                 | 没有解锁时再次加锁？ | 不占用时解锁？ | 在已解锁时解锁 |
  | -------------------------- | -------------------- | -------------- | -------------- |
  | `PTHREAD_MUTEX_NORMAL`     | 死锁                 | 未定义         | 未定义         |
  | `PTHREAD_MUTEX_ERRORCHECK` | 返回错误             | 返回错误       | 返回错误       |
  | `PTHREAD_MUTEX_RECURSIVE`  | 允许                 | 返回错误       | 返回错误       |
  | `PTHREAD_MUTEX_DEFAULT`    | 未定义               | 未定义         | 未定义         |

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
#include "apue.h"
#include <pthread.h>
#include <time.h>
#include <sys/time.h>
extern int makethread(void *(*)(void *), void *);
struct to_info{
    void (*to_fn)(void *);
    void *to_arg;
    struct timespec to_wait;
};

#define SECTONSEC 1000000000

#if !defined(CLOCK_REALTIME) || define(BSD)
#define clock_nanosleep(ID, FL, REQ, REM) nanosleep((REQ), (REM))
#endif

#ifndef CLOCK_REALTIME
#define CLOCK_REALTIME 0
#define USECTONSEC 1000

void 
clock_getttime(itn id, struct timespec *tsp)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    tsp->tv_sec = tv.tv_sec;
    tsp->tv_nsec = tv.tv_usec * USECTONSEC;
}
#endif

void * 
timeout_helper(void *arg)
{
    struct to_info *tip;
    tip = (struct to_info *)arg;
    clock_nanosleep(CLOCK_REALTIME, 0, &tip->to_wait, NULL);
    (*tip->to_fn)(tip->to_arg);
    free(arg);
    return(0);
}

void 
timeout(const struct timespec *when, void (*func)(void *), void *arg)
{
    struct timespec now;
    struct to_info *tip;
    int err;
    
    clock_gettime(CLOCK_REALTIME, &now);
    if ((when->tv_sec > now.tv_sec) ||
        (when->tv_sec == now.tv_sec && when->tv_nsec > now.tv_nsec)) {
        tip = malloc(sizeof(struct to_info));
        if (tip != NULL) {
            tip->to_fn = func;
            tip->to_arg = arg;
            tip->to_wait.tv_sec = when->tv_sec - now.tv_sec;
            if (when->tv_nsec >= now.tv_nsec) {
                tip->to_wait.tv_nsec = when->tv_nsec - now.tv_nsec;
            } else {
                tip->to_wait.tv_sec--;
                tip->to_wait.tv_nsec = SECTONSEC - now.tv_nsec + when->tv_nsec;
            }
            err = makethread(timeout_helper, (void *)tip);
            if (err == 0)
                return;
            else
                free(tip);
        }
    }
    (*func)(arg);
}

pthread_mutexattr_t attr;
pthread_mutex_t mutex;

void 
retry(void *arg)
{
    pthread_mutex_lock(&mutex);
    pthread_mutex_unlock(&mutex);
}

int 
main(void)
{
    int err, condition, arg;
    struct timespec when;
    if ((err = pthread_mutexattr_init(&attr)) != 0)
        err_exit(err, "pthread_mutexattr_init failed");
    if ((err = pthread_mutex_init(&mutex, &attr)) != 0)
        err_exit(err, "can't create recursive mutex");
    pthread_mutex_lock(&mutex);
    
    if(condition) {
        clock_gettime(CLOCK_REALTIME, &when);
        when.tv_sec += 10;
        timeout(&when, retry, (void *)((unsigned long)arg));
    }
    pthread_mutex_unlock(&mutex);
    exit(0);
}
```

*使用递归互斥量*

### 12.4.2 读写锁属性

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

### 12.4.3 条件变量属性

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

- `attr` 线程条件属性

- `pshared` 进程共享属性值

- `返回值`

  成功：0

  失败：错误码

*获取/设置进程共享属性*

```c++
#include <pthread.h>
int pthread_condattr_getclock(const pthread_condattr_t *restrict attr, clockid_t *restrict clock_id);
int pthread_condattr_setclock(pthread_condattr_t *attr, clockid_t clock_id);
```

- `attr` 条件变量属性

- `clock_id` 时钟id

- `返回值`

  成功：0

  失败：错误编号

*获取/设置 条件变量时钟*

### 12.4.4 屏障属性

```c++
#include <pthread.h>
int pthread_barrierattr_init(pthread_barrierattr_t *attr);
int pthread_barrierattr_destroy(pthread_barrierattr_t *attr);
```

- `attr` 屏障属性

- `返回值`

  成功：0

  失败：错误码

*初始化/反初始化 屏障属性*

```c++
#include <pthread.h>
int pthread_barrierattr_getpshared(const pthread_barrierattr_t *restrict attr, int *restrict pshared);
int pthread_barrierattr_setpshared(pthread_barrierattr_t *attr, int pshared);
```

- `attr` 屏障属性

- `pshared` 进程共享属性

- `返回值`

  成功：0

  失败：错误码

*获取/设置 屏障属性*



## 12.5 重入

![t12_5](res/t12_5.png)

*POSIX.1中不能保证线程安全的函数*

![t12_6](res/t12_6.png)

*替代的线程安全函数*

```c++
#include <stdio.h>
int ftrylockfile(FILE *fp);
void flockfile(FILE *fp);
void funlockfile(FILE *fp);
```

- `fp` 文件描述符

- `返回值`

  成功：0

  失败：非0

*加/解锁文件对象（线程安全）*

```c++
#include <stdio.h>
int getchar_unlocked(void);
int getc_unlocked(FILE *fp);
```

- `fp` 文件描述符

- `返回值`

  成功：下一个字符

  已到达文件尾或出错：EOF

*读一个字符（不加锁，不建议使用）*

```c++
#include <stdio.h>
int putchar_unlocked(int c);
int putc_unlocked(int c, FILE *fp);
```

- `c` 字符

- `fp` 文件描述符

- `返回值`

  成功：c

  失败：EOF

*写一个字符（不加锁，不建议使用）*

例：

```c++
#include <limits.h>
#include <string.h>

#define MAXSTRINGSZ 4096
static char envbuf[MAXSTRINGSZ];
extern char **environ;

char * 
getenv(const char *name)
{
    int i, len;
    len = strlen(name);
    if (i = 0; environ[i] != NULL; i++) {
        if ((strncmp(name, environ[i], len) == 0) && 
            (environ[i][len] == '=')) {
            	strncpy(envbuf, &environ[i][len+1], MAXSTRINGSZ - 1);
            	return(envbuf);
        }
    }
    return(NULL);
}
```

*getenv的非可重入版本*

例：

```c++
#include <string.h>
#include <errno.h>
#include <pthread.h>
#include <stdlib.h>

extern char **environ;
pthread_mutex_t env_mutex;
static pthread_once_t init_done = PTHREAD_ONCE_INIT;

static void 
thread_init(void)
{
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
    pthread_mutex_init(&env_mutex, &attr);
    pthread_mutexattr_destroy(&attr);
}

int 
getenv_r(const char *name, char *buf, int buflen)
{
    int i, len, olen;
    pthread_once(&init_done, thread_init);
    len = strlen(name);
    pthread_mutex_lock(&env_mutex);
    for (i = 0; environ[i] != NULL; i++) {
        if ((strncmp(name, environ[i], len) == 0) &&
            (environ[i][len] == '=')) {
            olen = strlen(&environ[i][len+1]);
            if (olen >= buflen) {
                pthread_mutex_unlock(&env_mutex);
                return(ENOSEC);
            }
            strcpy(buf, &environ[i][len + 1]);
            pthread_mutex_unlock(&env_mutex);
            return(0);
        }
    }
    pthread_mutex_unlock(&env_mutex);
    return(ENOENT);
}
```

*getenv的可重入（线程安全）版本*



## 12.6 线程私有数据

```c++
#include <pthread.h>
int pthread_key_create(pthread_key_t *keyp, void (*destructor)(void *));
```

- `keyp` 键

- `destructor` 析构函数

- `返回值`

  成功：0

  失败：错误码

*创建与线程数据关联的键（用于获取对线程私有数据的访问权）*

```c++
#include <pthread.h>
int pthread_key_delete(pthread_key_t *key);
```

- `key` 键

- `返回值`

  成功：0

  失败：错误码

*取消键与线程数据的关联*

```c++
#include <pthread.h>
pthread_once_t initflag = PTHREAD_ONCE_INIT;
int pthread_once(pthread_once_t *initflag, void (*initfn)(void));
```

- `initflag` 标志（全局变量或静态变量）

- `initfn` 只执行一次的函数

- `返回值`

  成功：0

  失败：错误码

*让函数只执行一次*

例：

```c++
void destructor(void *);
pthread_key_t key;
pthread_once_t init_done = PTHREAD_ONCE_INIT;
void 
thread_init(void)
{
    err = pthread_key_create(&key, destructor);
}
int 
threadfunc(void *arg)
{
    pthread_once(&init_done, thread_init);
    ...
}
```

```c++
#include <pthread.h>
void *pthread_getspecific(pthread_key_t key);
```

- `key` 键

- `返回值`

  成功：线程私有数据

  失败：NULL

*返回与键关联的线程私有数据*

```c++
#include <pthread.h>
int pthread_setspecific(pthread_key_t key, const void *value);
```

- `key` 键

- `value` 值

- `返回值`

  成功：0

  失败：错误码

*设置键与关联的线程私有数据*

例：

```c++
#include <limits.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>

#define MAXSTRINGSZ 4096
static pthread_key_t key;
static pthread_once_t init_done = PTHREAD_ONCE_INIT;
pthread_mutex_t env_mutex = PTHREAD_MUTEX_INITIALIZER;

extern char **environ;

static void 
thread_init(void)
{
    pthread_key_create(&key, free);
}

char * 
getenv(const char *name)
{
    int i, len;
    char *envbuf;
    
    pthread_once(&init_done, thread_init);
    pthread_mutex_lock(&env_mutex);
    envbuf = (char *)pthread_getspecific(key);
    if (envbuf == NULL) {
        envbuf = malloc(MAXSTRINGSZ);
        if (envbuf == NULL) {
            pthread_mutex_unlock(&env_mutex);
            return(NULL);
        }
        pthread_setspecific(key, envbuf);
    }
    len = strlen(name);
    for (i = 0; environ[i] != NULL; i++) {
        if ((strncmp(name, environ[i], len) == 0) &&
            (environ[i][len] == '=')) {
            strncpy(envbuf, &environ[i][len+1], MAXSTRINGSZ-1);
            pthread_mutex_unlock(&env_mutex);
            return(envbuf);
        }
    }
    pthread_mutex_unlock(&env_mutex);
    return(NULL);
}
```

*线程安全的getenv的兼容版本*



## 12.7 取消选项

```c++
#include <pthread.h>
int pthread_setcancelstate(int state, int *oldstate);
```

- `state` 可取消状态

- `oldstate` 旧状态

- `返回值`

  成功：0

  失败：错误码

*设置可取消状态（线程启动时默认为PTHREAD_CANCEL_ENABLE）*

![12_7](res/12_7.png)

*POSIX.1定义的取消点*

```c++
#include <pthread.h>
void pthread_testcancel(void);
```

*添加自定义取消点*

```c++
#include <pthread.h>
int pthread_setcanceltype(int type, int *oldtype);
```

- `type` 新取消类型

- `oldtype` 旧取消类型

- `返回值`

  成功：0

  失败：错误码

*修改取消类型*

![12_8](res/12_8.png)

*POSIX.1 定义的可选取消点*



## 12.8 线程和信号

```c++
#include <signal.h>
int pthread_sigmask(int how, const sigset_t *restrict set, sigset_t *restrict oset);
```

- `how` 动作

  SIG_BLOCK：把信号添加到线程信号屏蔽字中

  SIG_SETMASK：用信号集替换线程的信号屏蔽字

  SIG_UNBLOCK：从线程信号屏蔽字中移除信号集

- `set` 新信号集

- `oset` 旧信号集

- `返回值`

  成功：0

  失败：错误码

*阻止信号发送*

```c++
#include <signal.h>
int sigwait(const sigset_t *restrict set, int *restrict signop);
```

- `set` 信号集

- `signop` 返回发送信号的数量

- `返回值`

  成功：0

  失败：错误码

*等待一个或多个信号发生*

```c++
#include <signal.h>
int pthread_kill(pthread_t thread, int signo);
```

- `thread` 线程

- `signo` 信号

- `返回值`

  成功：0

  失败：错误码

*把信号发送到线程*

例：

```c++
#include "apue.h"
#include <pthread.h>

int quitflag;
sigset_t mask;

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t waitloc = PTHREAD_COND_INITIALIZER;

void *
thr_fn(void *arg)
{
    int err, signo;
    for (;;) {
        err = sigwait(&mask, &signo);
        if (err != 0)
            err_exit(err, "sigwait failed");
        switch(signo) {
            case SIGINT:
                printf("\ninterrupt\n");
                break;
                
            case SIGQUIT:
                pthread_mutex_lock(&lock);
                quitflag = 1;
                pthread_mutex_unlock(&lock);
                pthread_cond_signal(&waitloc);
                return(0);
                
            default:
                printf("unexpected signal %d\n", signo);
                exit(1);
        }
    }
}

int 
main(void)
{
    int err;
    sigset_t oldmask;
    pthread_t tid;
    
    sigemptyset(&mask);
    sigaddset(&mask, SIGINT);
    sigaddset(&mask, SIGQUIT);
    if ((err = pthread_sigmask(SIG_BLOCK, &mask, &oldmask)) != 0)
        err_exit(err, "SIG_BLOCK error");
    
    err = pthread_create(&tid, NULL, thr_fn, 0);
    if (err != 0)
        err_exit(err, "can't create thread");
    
    pthread_mutex_lock(&lock);
    while (quitflag == 0)
        pthread_cond_wait(&waitloc, &lock);
    pthread_mutex_unlock(&lock);
    
    quitflag = 0;
    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
        err_sys("SIG_SETMASK error");
    exit(0);
}
```

*同步信号处理*



## 12.9 线程和fork

```c++
#include <pthread.h>
int pthread_atfork(void (*prepare)(void), void (*parernt)(void), void (*child)(void));
```

- `prepare` 获取父进程定义的所有锁（在创建子进程前调用）

- `parent` 对prepare获得的所有锁进行解锁（在创建子进程后，fork返回之前的父进程调用）

- `child` 释放prepare获得的所有锁（在fork返回之前调用，fork返回之前的子进程调用）

- `返回值`

  成功：0

  失败：错误码

*清除锁状态*

例：

```c++
#include "apue.h"
#include <pthread.h>

pthread_mutex_t lock1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lock2 = PTHREAD_MUTEX_INITIALIZER;

void 
prepare(void)
{
    int err;
    printf("preparing locks...\n");
    if ((err = pthread_mutex_lock(&lock1)) != 0)
        err_cont(err, "can't lock lock1 in prepare handler");
    if ((err = pthread_mutex_lock(&lock2)) != 0)
        err_cont(err, "can't lock lock2 in prepare handler");
}

void 
parent(void)
{
    int err;
    printf("parent unlocking locks...\n");
    if ((err = pthread_mutex_lunlock(&lock1)) != 0)
        err_cont(err, "can't unlock lock1 in parent handler");
    if ((err = pthread_mutex_unlock(&lock2)) != 0)
        err_cont(err, "can't unlock lock2 in parent handler");
}

void 
child(void)
{
    int err;
    printf("child unlocking locks...\n");
    if ((err = pthread_mutex_unlock(&lock1)) != 0)
        err_cont(err, "can't unlock lock1 in child handler");
    if ((err = pthread_mutex_unlock(&lock2)) != 0)
        err_cont(err, "can't unlock lock2 in child handler");
}

void *
thr_fn(void *arg)
{
    printf("thread started...\n");
    pause();
    return(0);
}

int 
main(void)
{
    int err;
    pid_t pid;
    pthread_t tid;
    
    if ((err = pthread_atfork(prepare, parent, child)) != 0)
        err_exit(err, "can't install fork handlers");
    if ((err = pthread_create(&tid, NULL, thr_fn, 0)) != 0)
        err_exit(err, "can't create thread");
    
    sleep(2);
    printf("parent about to fork...\n");
    if ((pid = fork()) < 0)
        err_quit("fork failed");
    else if (pid == 0)
        printf("child returned from fork\n");
    else
        printf("parent returned from fork\n");
    exit(0);
}
```

*pthread_atfork实例*



## 12.10 线程和I/O

使用`pread`可以使偏移量的设定和数据的读取成为一个原子操作。



## 12.11 小结

