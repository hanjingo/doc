# 信号

[TOC]

`信号（signal）`就是告知某个进程发生了某个事件的通知，有时也称为`软件中断（software interrupt）`。信号通常是异步发生的，要使用信号相关函数，需包含以下头文件：

| 系统                         | 头文件                   |
| ---------------------------- | ------------------------ |
| FreeBSD 8.0，Mac OS X 10.6.8 | `<sys/signal.h>`         |
| Linux 3.2.0                  | `<bit/signum.h>`         |
| Solaris 10                   | `<sys/iso/signal_iso.h>` |



## 信号分类

### UNIX系统信号

| 名字       | 默认动作        | 说明                              | 触发条件                                                     |
| ---------- | --------------- | --------------------------------- | ------------------------------------------------------------ |
| SIGABRT    | 终止+core       | **异常终止（abort）**             | 1.调用abort函数时产生此信号，进程异常终止。                  |
| SIGALRM    | 终止            | **定时器超时（alarm）**           | 1.当用alarm函数设置的定时器超时时，产生此信号；<br>2.若由setitimer(2)函数设置的间隔时间已经超时时，也产生此信号。 |
| SIGBUS     | 终止+core       | **硬件故障**                      | 1.当出现某些类型的内存故障时，实现常常产生此种信号。         |
| SIGCANCEL  | 忽略            | **线程库内部使用**                |                                                              |
| SIGCHLD    | 忽略            | **子进程状态改变**                |                                                              |
| SIGCONT    | 继续/忽略       | **使暂停进程继续**                |                                                              |
| SIGEMT     | 终止+core       | **硬件故障**                      |                                                              |
| SIGFPE     | 终止+core       | **算术异常**                      | 1.此信号由算术运算异常产生，如除以0，浮点溢出等。            |
| SIGFREEZE  | 忽略            | **检查点冻结**                    |                                                              |
| SIGHUP     | 终止            | **连接断开**                      | 1.终端接口检测到一个连接断开且终端的CLOCAL标志**没有**设置。 |
| SIGILL     | 终止+core       | **非法硬件指令**                  | 1.执行非法硬件指令。                                         |
| SIGINFO    | 忽略            | **键盘状态请求**                  | 1.用户按状态键（一般采用Ctrl+T）。                           |
| SIGINT     | 终止            | **终端中断符**                    | 1.用户按中断键（一般采用Delete或Ctrl+C）。                   |
| SIGIO      | 终止/忽略       | **异步I/O**                       |                                                              |
| SIGIOT     | 终止+core       | **硬件故障**                      |                                                              |
| SIGJVM1    | 忽略            | **java虚拟机内部使用**            |                                                              |
| SIGJVM2    | 忽略            | **java虚拟机内部使用**            |                                                              |
| SIGKILL    | 终止            | **终止**                          | 1.用户发送此信号以杀死进程（无法捕获或忽略）。               |
| SIGLOST    | 终止            | **资源丢失**                      |                                                              |
| SIGLWP     | 终止/忽略       | **线程库内部使用**                |                                                              |
| SIGPIPE    | 终止            | **写至无读进程的管道**            | 1.管道的读进程已终止时写管道。                               |
| SIGPOLL    | 终止            | **可轮询时间（poll）**            | （已弃用）                                                   |
| SIGPROF    | 终止            | **梗概时间超时（setitimer）**     | （已弃用）                                                   |
| SIGPWR     | 终止/忽略       | **电源失效/重启动**               | 1.具有不间断电源（UPS）系统的设备电源失效。                  |
| SIGQUIT    | 终止+core       | **终端退出符**                    | 1.用户在终端上按退出键（一般采用Ctrl+\）。                   |
| SIGSEGV    | 终止+core       | **无效内存引用**                  | 1.进程进行了一次无效的内存引用。                             |
| SIGSTKFLT  | 终止            | **协处理器栈故障**                |                                                              |
| SIGSTOP    | 停止进程        | **停止**                          |                                                              |
| SIGSYS     | 终止+core       | **无效系统调用**                  | 1.无效的系统调用。                                           |
| SIGTERM    | 终止            | **终止**                          | 1.调用kill(1)命令。                                          |
| SIGTHAW    | 忽略            | **检查点解冻**                    | 1.恢复被挂起的系统。                                         |
| SIGTHR     | 忽略            | **线程库内部使用**                |                                                              |
| SIGTRAP    | 终止+core       | **硬件故障**                      | 1.硬件故障。                                                 |
| SIGTSTP    | 停止进程        | **终端停止符**                    | 1.用户在终端上按挂起键（一般采用Ctrl+Z）。                   |
| SIGTTIN    | 停止进程        | **后台读控制tty**                 | 1.一个后台进程组进程试图读其控制终端。                       |
| SIGTTOU    | 停止进程        | **后台写向控制tty**               | 1.一个后台进程组进程试图写其控制终端。                       |
| SIGURG     | 忽略            | **紧急情况（套接字）**            | 1.在网络连接上接到带外的数据。                               |
| SIGUSR1    | 终止            | **用户定义信号**                  | （用户定义）                                                 |
| SIGUSR2    | 终止            | **用户定义信号**                  | （用户定义）                                                 |
| SIGVTALRM  | 终止            | **虚拟时间闹钟（setitimer）**     | 1.由setitimer(2)函数设置的虚拟间隔时间超时。                 |
| SIGWAITING | 忽略            | **线程库内部使用**                |                                                              |
| SIGWINCH   | 忽略            | **终端窗口大小改变**              | 1.用ioctl命令更改了窗口大小。                                |
| SIGXCPU    | 终止或终止+core | **超过CPU限制（setrlimit）**      | 1.进程超过了其软CPU时间限制。                                |
| SIGXFSZ    | 终止或终止+core | **超过文件长度限制（setrlimit）** | 1.进程超过了其软文件长度限制。                               |
| SIGXRES    | 忽略            | **超过资源控制**                  |                                                              |



## 相关函数

### wait

```c++
#include <sys/wait.h>
pid_t wait(int *statloc);
```

- `statloc`用于返回子进程的终止状态（一个整数）

- `返回值`

  成功：进程ID

  失败：0或-1

*处理已终止的子进程，并返回其进程ID；如果没有已终止的子进程，但是有一个或多个子进程仍在执行，那么阻塞到现有子进程第一个终止为止。（阻塞）*

### waitpid

```c++
#include <sys/wait.h>
pid_t waitpid(pid_t pid, int *statloc, int options);
```

- `pid` 想要等待的进程ID（-1表示等待第一个终止的子进程）

- `statloc`用于返回子进程的终止状态（一个整数）

- `options` 附加选项

- `返回值`

  成功：进程ID

  失败：0或-1

*处理已终止的子进程，并返回其进程ID。*

### signal

```c++
#include <signal.h>
void(*signal(int signo, void(*func)(int)))(int);
```

- `signo` 信号量

- `func` 信号处理动作，默认SIG_IGN

- 返回值

  成功：返回以前的信号处理配置

  出错：返回SIG_ERR

*信号处理函数*

### kill

```c++
#include <signal.h>
int kill(pid_t pid, int signo);
```

- `pid` 进程ID

  - `pid>0` 将该信号发送给进程ID为pid的进程
  - `pid==0` 将该信号发送给与发送进程属于同一进程组的所有进程（这些进程的进程组ID等于发送进程的进程组ID），而且发送进程具有权限向这些进程发送信号。
  - `pid<0` 将该信号发送给其他进程组ID等于pid绝对值，而且发送进程具有权限向其发送信号的所有进程。
  - `pid==-1` 将该信号发送给发送进程有权向向他们发送信号的所有进程。

- `signo` 信号

- 返回值

  成功：0

  失败：-1

*将信号发送给进程或进程组*

### raise

```c++
#include <signal.h>
int raise(int signo);
```

- `signo` 信号

- 返回值

  成功：0

  失败：-1

*允许进程向自身发送信号*

### alarm

```c++
#include <unistd.h>
unsigned int alarm(unsigned int seconds);
```

- `seconds` 时长（秒）
- 返回值：0或以前设置的闹钟时间的余留秒数

*设置一个定时器，当定时器超时时，产生SIGALRM信号*

### pause

```c++
#include <unistd.h>
int pause(void);
```

- 返回值：-1，errno设置为EINTR

*使进程挂起直至捕捉到一个信号（阻塞）*

### 信号集

```c++
#include <signal.h>
int sigemptyset(sigset_t *set);          // 初始化信号集，清除其中所有信号
int sigfillset(sigset_t *set);           // 初始化由set指向的信号集，使其包括所有信号
int sigaddset(sigset_t *set, int signo); // 添加信号
int sigdelset(sigset_t *set, int signo); // 删除信号
int sigismember(const sigset_t *set, int signo); // 判断信号是否是信号集中的成员
```

- `set` 信号集

- `signo` 信号

- `返回值`

  成功：0

  失败：-1

### sigprocmask

```c++
#include <signal.h>
int sigprocmask(int how, const sigset_t *restrict set, sigset_t *restrict oset);
```

- `how` 操作

  | how         | 说明                                                         |
  | ----------- | ------------------------------------------------------------ |
  | SIG_BLOCK   | 该进程新的信号屏蔽字是其当前信号屏蔽字和set指向信号集的并集。set包含了希望阻塞的附加信号 |
  | SIG_UNBLOCK | 该进程新的信号屏蔽字是其当前信号屏蔽字和set所指向信号集补集的交集。set包含了希望解除阻塞的信号 |
  | SIG_SETMASK | 该进程新的信号屏蔽是set指向的值                              |

- `set` 如果非空，则指示需要修改修改的当前信号屏蔽字

- `oset` 如果非空，用来返回进程的当前信号屏蔽字

- 返回值：

  - 成功：0
  - 失败：-1

*检测/更改进程的信号屏蔽字*（**注意：sigprocmask是仅为单线程进程定义的，处理多线程进程中信号的屏蔽使用其它函数**）

### sigpending

```c++
#include <signal.h>
int sigpending(sigset_t *set);
```

- `set` 返回的信号集

- 返回值

  成功：0

  失败：-1

*返回当前进程的阻塞且不可递送的信号集合*

### sigaction

```c++
#include <signal.h>
struct sigaction {
  void (*sa_handler)(int);
  sigset_t sa_mask;
  int sa_flags;
  void (*sa_sigaction)(int, siginfo_t *, void *);
};

int sigaction(int signo, const struct sigaction *restrict act, struct sigaction *restrict oact);
```

- `signo` 要检查/修改的信号编号

- `act` 非空，则修改其动作

  | 选项         | SUS  | FreeBSD 8.0 | Linux 3.2.0 | Mac OS X 10.6.8 | Solaris 10 | 说明                                                         |
  | ------------ | ---- | ----------- | ----------- | --------------- | ---------- | ------------------------------------------------------------ |
  | SA_INTERRUPT |      |             | *           |                 |            | 由此信号中断的系统调用不自动重启动（XSI对于sigaction的默认处理方式） |
  | SA_NOCLDSTOP | *    | *           | *           | *               | *          | 若signo是SIGCHLD，当子进程停止（作业控制），不产生此信号。当子进程终止时，仍旧产生此信号（但请参阅下面说明的SA_NOCLDWAIT选项）。若已设置此标志，则当停止的进程继续运行时，作为XSI扩展，不产生SIGCHLD信号 |
  | SA_NOCLDWAIT | *    | *           | *           | *               | *          | 若signo是SIGCHLD，则当调用进程的子进程终止时，不创建僵死进程。若调用进程所后调用wait，则阻塞到它所有子进程都终止，此时返回-1，errno设置为ECHILD。 |
  | SA_NODEFER   | *    | *           | *           | *               | *          | 当捕捉到此信号时，在执行其信号捕捉函数时，系统不自动阻塞此信号（除非sa_mask包括了此信号）。注意，此种类型的操作对应于早期的不可靠信号。 |
  | SA_ONSTACK   | XSI  | *           | *           | *               | *          | 若用sigaltstack(2)已声明了一个替换栈，则此信号地送给替换栈上的进程 |
  | SA_RESETHAND | *    | *           | *           | *               | *          | 在此信号捕捉函数的入口处，将此信号的处理方式重置为SIG_DFL，并清除SA_SIGINFO标志。注意，此种类型的信号对应于早期的不可靠信号。但是，不能自动重置SIGILL和SIGTRAP这两个信号的配置。设置此标志使sigaction的行为如同设置了SA_NODEFER标志 |
  | SA_RESTART   | *    | *           | *           | *               | *          | 由此信号中断的系统调用自动重启动                             |
  | SA_SIGINFO   | *    | *           | *           | *               | *          | 此选项对信号处理程序提供了附加信息：一个指向siginfo结构的指针以及一个指向进程上下文标识符的指针 |

- `oact` 非空，则返回该信号的上一个动作

- 返回值

  成功：0

  失败：-1

*检查/修改指定信号相关联的处理动作*（**注意：一旦对给定的信号设置了一个动作，那么在调用sigaction显式地改变它之前，该设置就一直有效。**）



## 信号处理

### 信号产生

信号通过以下方式产生：

- 用户按某些终端键
- 硬件异常
- 进程调用kill(2)函数
- 进程调用kill(1)函数
- 当检测到某种软件条件

### 信号处理

通过以下方式处理信号：

- 忽略信号
- 捕捉信号
- 执行系统默认动作

### 示例

```c++
// 调用POSIX sigaction函数的signal函数
#include "unp.h"
Sigfunc *signal(int signo, Sigfunc *func)
{
    struct sigaction act, oact;
    act.sa_handler = func;     // 设置回调函数
    sigemptyset(&act.sa_mask); // 设置处理函数的信号掩码
    // 设置SA_RESTART标志，由相应信号中的系统调用将由内核自动重启
    act.sa_flags = 0;
    if (signo == SIGALRM) {
#ifdef SA_INTERRUPT
    	act.sa_flags |= SA_INTERRUPT; /* SunOS 4.x */
#endif
    } else {
#ifdef SA_RESTART
    	act.sa_flags |= SA_RESTART; /* SVR4, 4.4BSD */
# endif
    }
    if (sigaction(signo, &act, &oact) < 0)
        return (SIG_ERR);
    return (oact.sa_handler);
}
```



## 参考

[1] [美]W.Richard Stevens, [美]Bill Fenner, [美]Andrew M Rudoff . Unix网络编程 卷一:套接字联网api
