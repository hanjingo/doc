[TOC]

# 第十章 信号



## 信号概念

每个信号名字都以`SIG`开头，定义在内核头文件`<signal.h>`中，用户级头文件若要使用这些信号，需要包含以下头文件：

| 系统                         | 头文件                   |
| ---------------------------- | ------------------------ |
| FreeBSD 8.0，Mac OS X 10.6.8 | `<sys/signal.h>`         |
| Linux 3.2.0                  | `<bit/signum.h>`         |
| Solaris 10                   | `<sys/iso/signal_iso.h>` |

### 产生信号的方式

- 用户按某些终端键
- 硬件异常
- 进程调用kill(2)函数
- 进程调用kill(1)函数
- 当检测到某种软件条件

### 处理信号的方式

- 忽略信号
- 捕捉信号
- 执行系统默认动作

### UNIX系统信号

| 名字       | 说明                          | 默认动作        |
| ---------- | ----------------------------- | --------------- |
| SIGABRT    | 异常终止（abort）             | 终止+core       |
| SIGALRM    | 定时器超时（alarm）           | 终止            |
| SIGBUS     | 硬件故障                      | 终止+core       |
| SIGCANCEL  | 线程库内部使用                | 忽略            |
| SIGCHLD    | 子进程状态改变                | 忽略            |
| SIGCONT    | 使暂停进程继续                | 继续/忽略       |
| SIGEMT     | 硬件故障                      | 终止+core       |
| SIGFPE     | 算术异常                      | 终止+core       |
| SIGFREEZE  | 检查点冻结                    | 忽略            |
| SIGHUP     | 连接断开                      | 终止            |
| SIGILL     | 非法硬件指令                  | 终止+core       |
| SIGINFO    | 键盘状态请求                  | 忽略            |
| SIGINT     | 终端中断符                    | 终止            |
| SIGIO      | 异步I/O                       | 终止/忽略       |
| SIGIOT     | 硬件故障                      | 终止+core       |
| SIGJVM1    | java虚拟机内部使用            | 忽略            |
| SIGJVM2    | java虚拟机内部使用            | 忽略            |
| SIGKILL    | 终止                          | 终止            |
| SIGLOST    | 资源丢失                      | 终止            |
| SIGLWP     | 线程库内部使用                | 终止/忽略       |
| SIGPIPE    | 写至无读进程的管道            | 终止            |
| SIGPOLL    | 可轮询时间（poll）            | 终止            |
| SIGPROF    | 梗概时间超时（setitimer）     | 终止            |
| SIGPWR     | 电源失效/重启动               | 终止/忽略       |
| SIGQUIT    | 终端退出符                    | 终止+core       |
| SIGSEGV    | 无效内存引用                  | 终止+core       |
| SIGSTKFLT  | 协处理器栈故障                | 终止            |
| SIGSTOP    | 停止                          | 停止进程        |
| SIGSYS     | 无效系统调用                  | 终止+core       |
| SIGTERM    | 终止                          | 终止            |
| SIGTHAW    | 检查点解冻                    | 忽略            |
| SIGTHR     | 线程库内部使用                | 忽略            |
| SIGTRAP    | 硬件故障                      | 终止+core       |
| SIGTSTP    | 终端停止符                    | 停止进程        |
| SIGTTIN    | 后台读控制tty                 | 停止进程        |
| SIGTTOU    | 后台写向控制tty               | 停止进程        |
| SIGURG     | 紧急情况（套接字）            | 忽略            |
| SIGUSR1    | 用户定义信号                  | 终止            |
| SIGUSR2    | 用户定义信号                  | 终止            |
| SIGVTALRM  | 虚拟时间闹钟（setitimer）     | 终止            |
| SIGWAITING | 线程库内部使用                | 忽略            |
| SIGWINCH   | 终端窗口大小改变              | 忽略            |
| SIGXCPU    | 超过CPU限制（setrlimit）      | 终止或终止+core |
| SIGXFSZ    | 超过文件长度限制（setrlimit） | 终止或终止+core |
| SIGXRES    | 超过资源控制                  | 忽略            |

- `SIGABRT` 调用abort函数时产生此信号，进程异常终止。
- `SIGALRM` 当用alarm函数设置的定时器超时时，产生此信号；若由setitimer(2)函数设置的间隔时间已经超时时，也产生此信号。
- `SIGBUS` 指示一个实现定义的硬件故障；当出现某些类型的内存故障时，实现常常产生此种信号。
- `SIGCANCEL` 这是Solaris线程库内部使用的信号，不适用于一般应用。
- `SIGCHLD` 在一个进程终止或停止时，SIGCHLD信号被送给其父进程；按系统默认，将忽略此信号。
- `SIGCONT` 此作业控制信号发送给需要继续运行，但当前处于停止状态的进程；如果接收到此信号的进程处于停止状态，则系统默认动作是使该进程继续运行，否则默认动作是忽略此信号。
- `SIGEMT` 指示一个实现定义的硬件故障。
- `SIGFPE` 此信号表示一个算术运算异常，如除以0，浮点溢出等。
- `SIGFREEZE` 此信号仅由Solaris定义，它用于通知进程在冻结系统状态之前需要采取特定动作。
- `SIGHUP` 如果终端接口检测到一个连接断开，则将此信号送给与该终端相关的控制进程（会话首进程）；此信号被送给session结构中s_leader字段所指向的进程；仅当终端的CLOCAL标志**没有**设置时，在上述条件下才产生此信号。
- `SIGILL` 此信号表示进程已执行一条非法硬件指令。
- `SIGINFO` 这是一种BSD信号，当用户按状态键（一般采用Ctrl+T）时，终端驱动程序产生此信号并发送至前台进程组中的每一个进程；此信号通常造成在终端上显示前台进程组中各进程的状态信息。
- `SIGINT` 当用户按中断键（一般采用Delete或Ctrl+C）时，终端驱动程序产生此信号并发送至前台进程组中的每一个进程；当一个进程在运行时失控，特别是它正在屏幕上产生大量不需要的输出时，常用此信号终止它。
- `SIGIO` 此信号指示一个异步I/O事件。
- `SIGIOT` 这指示一个实现定义的硬件故障。
- `SIGJVM1` Solaris上为Java虚拟机预留的一个信号。
- `SIGJVM2` Solaris上为Java虚拟机预留的另一个信号。
- `SIGKILL` 这是两个不能被捕捉或忽略信号中的一个；它向系统管理员提供了一种可以杀死任一进程的可靠方法。
- `SIGLOST` 运行在Solaris NFSv4客户端系统中的进程，恢复阶段不能重新获得锁，此时将由这个信号通知该进程。
- `SIGLWP` 此信号由Solaris线程库内部使用，并不做一半使用。
- `SIGPIPE` 如果在管道的读进程已终止时写管道，则产生此信号。
- `SIGPOLL` 这个信号在SUSv4中已被标记为弃用，将来的标准可能会将此信号移除。
- `SIGPROF` 这个信号在SUSv4中已被标记为弃用，将来的标准可能会将此信号移除。
- `SIGPWR` 这是一种依赖于系统的信号；它主要用于具有不间断电源（UPS）的系统，如果电源失效，则UPS起作用，而且通常软件会接到通知。
- `SIGQUIT` 当用户在终端上按退出键（一般采用Ctrl+\）时，中断驱动程序产生此信号，并发送给前台进程组中的所有进程；此信号不仅终止前台进程组（如SIGINT所做的那样），同时产生一个core文件。
- `SIGSEGV`
- `SIGSTKFLT`
- `SIGSTOP`
- `SIGSYS`
- `SIGTERM`
- `SIGTHAW`
- `SIGTHR`
- `SIGTRAP`
- `SIGTSTP`
- `SIGTTIN`
- `SIGTTOU`
- `SIGURG`
- `SIGUSR1`
- `SIGUSR2`
- `SIGVTALRM`
- `SIGWAITING`
- `SIGWINCH`
- `SIGXCPU`
- `SIGXFSZ`
- `SIGXRES`

### 不产生core文件的情况

- 进程是设置用户ID的，而且当前用户并非程序文件的所有者。
- 进程是设置组ID的，而且当前用户并非该程序文件的组所有者。
- 用户没有写当前工作目录的权限。
- 文件已存在且用户对该文件设有写权限。
- 文件太大超过了`RLIMIT_CORE`限制。
