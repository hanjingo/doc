# 信号

[TOC]

`信号（signal）`就是告知某个进程发生了某个事件的通知，有时也称为`软件中断（software interrupt）`，信号通常是异步发生的。



## 信号分类

| 信号     | 说明 |
| -------- | ---- |
| SIGCHILD | TODO |
| SIGPIPE  | TODO |
| SIGTERM  | TODO |
| SIGKILL  | TODO |



## 相关函数

### wait

TODO

### waitpid

TODO



## 信号处理

TODO

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
