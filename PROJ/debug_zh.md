# 软件调试

[TOC]



## 定位内存问题

TODO



## 定位CPU跑满问题

TODO



## 定位Dump问题

核心转存（coredump），实际为进程运行过程中的一个内存快照；当进程crash时，操作系统接收到异常指令后，在进程crash之前，把进程做一个内存快照，保存进程的地址，寄存器，堆栈调用等信息，这个文件就叫coredump。

### Dump文件产生原因

Window下生成的是MiniDump。

Linux下CoreDump文件经由以下信号产生：

| 信号    | 说明                        |
| ------- | --------------------------- |
| SIGABRT | 异常终止（abort）           |
| SIGBUS  | 硬件故障                    |
| SIGEMT  | 硬件故障                    |
| SIGFPE  | 算术异常                    |
| SIGILL  | 非法硬件指令                |
| SIGIOT  | 硬件故障                    |
| SIGQUIT | 终端退出符                  |
| SIGSEGV | 无效存储访问                |
| SIGSYS  | 无效系统调用                |
| SIGTRAP | 硬件故障                    |
| SIGXCPU | 超出CPU限制(setrlimit)      |
| SIGXFSZ | 超过文件长度限制(setrlimit) |

造成程序dump的原因有很多，以下为一些常见的原因：

1. 内存访问越绝
2. 多线程程序使用了线程不安全的函数
3. 多线程读写数据未加锁保护
4. 非法指针
   - 空指针
   - 非法指针转换
5. 堆栈溢出

### 配置Dump捕获

#### 开启功能

linux默认不生成core文件，开启core文件生成功能有以下3种方法：

1. 将语句`ulimit -c unlimited`写入`/etc/profile`里，`source`之后永久生效

2. cd到程序目录，输入`ulimit -c unlimited`命令，在当前终端生效

3. 在代码里面使用`setrlimit`函数设置生成core文件，例：

   ```c++
   #include<sys/resource.h>
   ...
   struct rlimit limit;
   limit.rlim_cur = RLIM_INFINITY;
   limit.rlim_max = RLIM_INFINITY;
   setrlimit(RLIMIT_CORE, &limit);
   ...
   ```

#### 文件大小

使用以下命令来配置core文件属性：

- 查看core文件生成功能是否开启

  ```sh
  ulimit -c # 如果为0表示core文件生成功能已关闭
  ```

- 限制core文件大小

  ```sh
  ulimit -c fsize #fsize文件大小(单位：kbyte)
  ```

- 取消core文件大小限制

  ```sh
  ulimit -c unlimited
  ```

#### 命名

使用以下命令来设置core文件的生成目录和命名：

- linux

  ```sh
  echo "/xx/core.%e.%p" > /proc/sys/kernel/core_pattern #xx:core文件生成路径
  
  # 如果echo无效,使用以下命令
  sysctl -w "kernel.core_pattern=/xx/core.%e.%p" > /dev/null #xx:core文件生成路径
  ```

- macos

  ```sh
  echo "/path/core.%e.%p" >> /core/core.pid #path:core文件生成路径
  ```

`core.%e.%p`是core文件的命名规则，各参数说明如下：

| 参数 | 含义                       |
| ---- | -------------------------- |
| `%p` | 添加pid                    |
| `%u` | 添加当前uid                |
| `%g` | 添加当前gid                |
| `%s` | 添加导致产生core的信号     |
| `%t` | 添加core文件生成的unix时间 |
| `%h` | 添加主机名                 |
| `%e` | 添加命令名                 |

#### 测试

```sh
sleep 15

# 按下Ctrl + \
```

### dump捕获

linux/windows下都有各自的dump捕获函数，也可以通过使用跨平台崩溃捕获工具：[BreakPad](..\LANG\C++\OTHER\break_pad_zh.md), CrashPad来捕获。

### dump文件格式

linux下使用以下命令判断一个文件是否是dump文件：

- `readelf -h xx`

  例：

  ```sh
  TODO
  ```

Windows略。

### 调试Dump

#### 使用GDB

```sh
# 使用gdb打开
gdb test xx # xx:c
# 查看堆栈信息
bt
# 查看出错位置
where
# 切换堆栈信息
f(xx) # xx:堆栈层数(1:一般是main函数, ...)
```

#### 使用VisualStudio

TODO

#### 使用windbg

TODO



## 定位丢包问题

TODO



## 定位高并发问题

TODO



## 使用系统日志

### 日志分类

linux：

- `/var/log/message`：系统服务及日志，包括服务的信息，报错等
- `/var/log/secure`：系统登录日志（系统认证信息日志）
- `/var/log/cron`：定时任务日志
- `/var/log/maillog`：邮件日志
- `/var/log/boot.log`：系统启动日志
- `/var/log/wtmp`：永久记录每个用户登陆，注销及系统的启动，停机事件

windows：

略

### 日志类型

Linux：

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

windows：

略

### 日志级别

Linux：

- `debug`：调试信息
- `info`：一般信息
- `notice`：通知
- `warning`：警告级别
- `err`：错误级别
- `crit`：严重级别
- `alert`：需要立即修改的信息
- `emerg`：内核崩溃
- `none`：无

windows：

略

### 开启与关闭系统日志

系统日志的配置文件在：

- linux

  `/etc/rsyslog.conf`

- macos

  `/etc/syslog.conf`

#### 开启

- linux

  ```sh
  systemctl restart rsyslog
  ```
  
- Windows

  略

