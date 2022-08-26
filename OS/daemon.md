# 守护进程

[TOC]



## 系统日志

### 复制日志

```c++
#include <syslog.h>
void syslog(int priority, const char *message, ...);
```

- `priority`优先级

  由level和faility组合而成：

  | level       | 值   | 说明                         |
  | ----------- | ---- | ---------------------------- |
  | LOG_EMERG   | 0    | 系统不可用（最高优先级）     |
  | LOG_ALERT   | 1    | 必须立即采取行动             |
  | LOG_CRIT    | 2    | 临界信息                     |
  | LOG_ERR     | 3    | 出错条件                     |
  | LOG_WARNING | 4    | 警告条件                     |
  | LOG_NOTICE  | 5    | 正常然而重要的条件（默认值） |
  | LOG_INFO    | 6    | 通告消息                     |
  | LOG_DEBUG   | 7    | 调试级消息（最低优先级）     |

  | facility     | 说明                     |
  | ------------ | ------------------------ |
  | LOG_AUTH     | 安全/授权消息            |
  | LOG_AUTHPRIV | 安全/授权消息（私用）    |
  | LOG_CRON     | cron守护进程             |
  | LOG_DAEMON   | 系统守护进程             |
  | LOG_FTP      | FTP守护进程              |
  | LOG_KERN     | 内核消息                 |
  | LOG_LOCAL0   | 本地使用                 |
  | LOG_LOCAL1   | 本地使用                 |
  | LOG_LOCAL2   | 本地使用                 |
  | LOG_LOCAL3   | 本地使用                 |
  | LOG_LOCAL4   | 本地使用                 |
  | LOG_LOCAL5   | 本地使用                 |
  | LOG_LOCAL6   | 本地使用                 |
  | LOG_LOCAL7   | 本地使用                 |
  | LOG_LPR      | 行式打印机系统           |
  | LOG_MAIL     | 邮件系统                 |
  | LOG_NEWS     | 网络新闻系统             |
  | LOG_SYSLOG   | 由syslogd内部产生的消息  |
  | LOG_USER     | 任意的用户级消息（默认） |
  | LOG_UUCP     | UUCP系统                 |

- `message`格式化字符串；

从守护进程中登记（复制读）消息。

### 打开/关闭日志

```c++
#include <syslog.h>
void openlog(const char *ident, int options, int facility);
void closelog(void);
```

- ident`由syslog冠于每个日志消息之前的字符串（通常是程序名）；

- `options`可选项

  | options    | 说明                                            |
  | ---------- | ----------------------------------------------- |
  | LOG_CONS   | 若无法发送到syslogd守护进程则登记到控制台。     |
  | LOG_NDELAY | 不延迟打开，立即创建套接字。                    |
  | LOG_PERROR | 既发送到syslogd守护进程，又登记到标准错误输出。 |
  | LOG_PID    | 随每个日志消息登记进程ID。                      |

- `facility`

打开/关闭日志（调用openlog时，默认不会立即创建Unix域套接字，在首次调用syslog时才创建，通过设置LOG_NDELAY可以修改此操作）。



## 参考

[1] (美)W.Richard Stevens,(美)Bill Fenner,(美)Andrew M Rudoff . Unix网络编程 卷一:套接字联网api . 3ED