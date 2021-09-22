[TOC]

# 调试工具-linux系统日志



## 分类

### 系统日志分类

- `/var/log/message`：系统服务及日志，包括服务的信息，报错等
- `/var/log/secure`：系统登录日志（系统认证信息日志）
- `/var/log/cron`：定时任务日志
- `/var/log/maillog`：邮件日志
- `/var/log/boot.log`：系统启动日志
- `/var/log/wtmp`：永久记录每个用户登陆，注销及系统的启动，停机事件

### 日志类型

- `auth`：pam产生的日志
- `authpriv`：ssh，ftp等登陆信息验证信息
- `cron`：时间任务相关
- `kern`：内核
- `lpr`：打印
- `mail`：邮件
- `mark(syslog)-rsyslog`：服务内部的信息，时间标识
- `news`：新闻组
- `user`：用户程序产生的相关信息
- `uucp`：`unix to unix copy`，unix主机之间相关的通讯
- `local 1~7`：自定义的日志设备

### 日志级别

- `debug`：调试信息
- `info`：一般信息
- `notice`：通知
- `warning`：警告级别
- `err`：错误级别
- `crit`：严重级别
- `alert`：需要立即修改的信息
- `emerg`：内核崩溃
- `none`：无



## 开启与关闭系统日志

系统日志的配置文件在：

- linux

  `/etc/rsyslog.conf`

- macos

  `/etc/syslog.conf`

### 开启

- linux

  ```sh
  systemctl restart rsyslog
  ```

  

## 参考

- [Linux下的系统日志管理](https://blog.csdn.net/j_1282937574/article/details/81258153)

