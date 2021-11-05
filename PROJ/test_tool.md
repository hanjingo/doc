# 调试工具

[TOC]

## 1GDB

### 1.1命令

| 命令                  | 简写 | 说明                                                         |
| --------------------- | ---- | ------------------------------------------------------------ |
| `run`                 | r    | 重新开始运行文件                                             |
| `start`               | -    | 单步执行，运行程序，停在第一执行语句                         |
| `quit`                | q    | 退出GDB                                                      |
| `list`                | l    | 查看源码（l+n，从第n行开始查看；l+函数名，查看具体函数）     |
| `set`                 | -    | 设置变量的值                                                 |
| `display`             | -    | 追踪查看具体变量值（display+变量名，追踪查看一个变量，每次都停下来显示它的值；） |
| `undisplay`           | -    | 取消追踪观察变量                                             |
| `watch`               | -    | 设置观察点                                                   |
| `i watch`             | -    | 显示观察点                                                   |
| `break`               | b    | 设置断点（b+n，在第n行设置断点；b+函数名，在函数开头设置断点；break...if...，设置条件断点） |
| `delete`              | d    | 删除断点（d+n，删除第n个断点）                               |
| `enable breakpoints`  | -    | 启用断点                                                     |
| `disable breakpoints` | -    | 禁用断点                                                     |
| `info breakpoints`    | -    | 查看当前设置的所有断点                                       |
| `next`                | n    | 单步调试（不进入函数）                                       |
| `step`                | s    | 单步调试（进入函数）                                         |
| `continue`            | c    | 继续运行                                                     |
| `finish`              | -    | 结束当前函数，返回到函数调用点                               |
| `backtrace`           | bt   | 查看函数的调用栈帧和层级关系                                 |
| `frame`               | f    | 切换函数的栈帧                                               |
| `info`                | i    | 查看函数内部局部变量的数值                                   |
| `print`               | p    | 打印值以及地址                                               |
| `x`                   | -    | 查看内存                                                     |

更多的信息使用GDB的`help`命令查看；

### 1.2生成调试文件

#### 1.2.1CMAKE

```cmake
SET(CMAKE_BUILD_TYPE "Debug")
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")
SET(CMAKE_CXX_FLAGS_RELEASE "$EN{CXXFLAGS} -O3 -Wall")
```

#### 1.2.2MAKE

TODO

### 1.3调试可执行文件

TODO

### 1.4调试进程

使用以下命令来调试正在运行的进程：

```sh
gdb pfile PID #pfile为进程文件，PID为进程ID
```

### 1.5调试core文件

使用以下命令来调试core文件：

```sh
gdb core #core:core文件绝对路径
```



## 2valgrind

TODO



## 3WireShark

TODO



## 4linux系统日志

### 4.1系统日志分类

- `/var/log/message`：系统服务及日志，包括服务的信息，报错等
- `/var/log/secure`：系统登录日志（系统认证信息日志）
- `/var/log/cron`：定时任务日志
- `/var/log/maillog`：邮件日志
- `/var/log/boot.log`：系统启动日志
- `/var/log/wtmp`：永久记录每个用户登陆，注销及系统的启动，停机事件

### 4.2日志类型

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

### 4.3日志级别

- `debug`：调试信息
- `info`：一般信息
- `notice`：通知
- `warning`：警告级别
- `err`：错误级别
- `crit`：严重级别
- `alert`：需要立即修改的信息
- `emerg`：内核崩溃
- `none`：无

### 4.4开启与关闭系统日志

系统日志的配置文件在：

- linux

  `/etc/rsyslog.conf`

- macos

  `/etc/syslog.conf`

#### 4.4.1开启

- linux

  ```sh
  systemctl restart rsyslog
  ```




## 5linux命令

1. file

   用来查看文件的类型

   例：

   ```sh
   he@he bin % file lua
   lua: Mach-O 64-bit executable x86_64 
   #lua:类型    位数    可执行文件  架构
   ```

2. ldd

   TODO

3. nm

   TODO

4. strings

   TODO

5. size

   TODO

6. readelf

   TODO

7. objdump

   TODO

8. netstat

   TODO

9. ps

   TODO

10. top

    TODO

11. ulimit

    TODO

12. addr2line

    TODO



## 参考

- [Valgrind学习总结](https://blog.csdn.net/andylauren/article/details/93189740)
- [Debugging Under Unix: `gdb` Tutorial](https://www.cs.cmu.edu/~gilpin/tutorial/)
- [CMake生成可用gdb调试的可执行文件](https://blog.csdn.net/lemonaha/article/details/72837561)
- [Linux下的系统日志管理](https://blog.csdn.net/j_1282937574/article/details/81258153)

