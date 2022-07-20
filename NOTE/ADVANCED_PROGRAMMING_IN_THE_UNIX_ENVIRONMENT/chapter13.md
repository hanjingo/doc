# 第十三章 守护进程

[TOC]



## 13.1 引言



## 13.2 守护进程的特征



## 13.3 编程规则

1. 调用`umask`将文件模式创建屏蔽字设置为0，由继承得来的文件模式创建屏蔽字可能会拒绝设置某些权限；
2. 调用`fork`并且使父进程退出（`exit`）；
3. 调用`setsid`以创建一个新会话；
4. 将当前工作目录更改为根目录；
5. 关闭不再需要的文件描述符；
6. 打开`/dev/null`使其具有文件描述符0,1和2，从而屏蔽读标准输入，写标准输出或标准出错等操作。

例：

```c++
TODO
```

*初始化一个守护进程*



## 13.4 出错记录

![13_1](res/13_1.png)

*BSD syslog设施*

产生日志信息的三种方法：

1. 内核例程调用`log`函数；
2. 调用`syslog(3)`函数以产生日志消息；
3. 通过TCP/IP网络连接到此主机的其它主机上的一个用户进程可将日志消息发向UDP端口514。

```c++
#include <syslog.h>
void openlog(const char *ident, int option, int facility);
```

- `ident` 认证信息，一般为程序名

- `option` 选项

  ![t13_1](res/t13_1.png)

- `facility` 设施

  ![t13_2](res/t13_2.png)

- `返回值`

  前日志记录优先级屏蔽值

*打开日志（可选）*

```c++
#include <syslog.h>
void syslog(int priority, const char *format, ...);
```

- `priority` 优先级，由`facility`和`level`组合而成；

  ![t13_3](res/t13_3.png)

- `format` 格式化字符串

- `返回值`

  前日志记录优先级屏蔽值

*写日志*

```c++
#include <syslog.h>
void closelog(void);
```

- `返回值`

  前日志记录优先级屏蔽值

*关闭日志*

```c++
#include <syslog.h>
int setlogmask(int maskpri);
```

- `maskpri` 屏蔽字

- `返回值`

  前日志记录优先级屏蔽值

*设置进程的记录优先级屏蔽字*

例1：

```c++
openlog("lpd", LOG_PID, LOG_LPR);
syslog(LOG_ERR, "open error for %s: %m", filename);
```

例2：

```c++
syslog(LOG_ERR | LOG_LPR, "open error for %s: %m", filename); // 不使用openlog
```



## 13.5 单实例守护进程

例：

```c++
TODO
```

*保证只运行某个守护进程的一个副本*



## 13.6 守护进程的惯例

在UNIX系统中，守护进程遵循以下公共惯例：

1. 若守护进程使用锁文件，那么该文件通常存放在`/var/run`目录中；
2. 若守护进程支持配置选项，那么配置文件通常存放在`/etc`目录中；
3. 守护进程可用命令行启动，但通常它们是由系统初始化脚本之一（`/etc/rc*`或`/etc/init.d/*`）启动的；
4. 若一守护进程有一配置文件，那么当该守护进程启动时，它读文件，但在此之后一般就不会再查看它；若一管理员更改了配置文件，那么该守护进程可能需要被停止，然后再启动，以便使配置文件的更改生效。

例：

```c++
TODO
```

*守护进程重读配置文件*

例：

```c++
TODO
```

*守护进程重读配置文件的另一种实现*



## 13.7 客户进程-服务器进程模型



## 13.8 小结

