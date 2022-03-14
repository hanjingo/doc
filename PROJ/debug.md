

[TOC]



# 软件调试方法

## 1如何定位内存问题

TODO



## 2如何定位CPU跑满问题

TODO



## 3如何定位Core Dump问题

核心转存（coredump），实际为进程运行过程中的一个内存快照；当进程crash时，操作系统接收到异常指令后，在进程crash之前，把进程做一个内存快照，保存进程的地址，寄存器，堆栈调用等信息，这个文件就叫coredump。

### 3.1Core文件产生原因

Core文件经由以下信号产生：

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

造成程序coredump的原因有很多，以下为一些常见的原因：

1. 内存访问越绝
2. 多线程程序使用了线程不安全的函数
3. 多线程读写数据未加锁保护
4. 非法指针
   - 空指针
   - 非法指针转换
5. 堆栈溢出

### 3.2配置CoreDump

#### 3.2.1开启功能

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

#### 3.2.2文件大小

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

#### 3.2.3命名

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

#### 3.2.4测试

```sh
sleep 15

# 按下Ctrl + \
```

### 3.3Core格式

使用以下命令判断一个文件是否是core文件：

- `readelf -h xx`

  例：

  ```sh
  TODO
  ```

### 3.4使用GDB调试CoreDump

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



## 4如何定位丢包问题

TODO



## 5如何定位高并发问题

TODO

---



# 调试工具

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
- [core文件生成及使用gdb调试](https://blog.csdn.net/zhang_han666/article/details/80668002)
- [gdb调试coredump(原理篇)](https://blog.csdn.net/sunlin972913894/article/details/113001810)
- [性能测试入门——LoadRunner使用初探](https://www.admin5.com/article/20161114/695706.shtml)

