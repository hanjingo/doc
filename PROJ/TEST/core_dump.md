[TOC]

# 如何定位Core Dump问题

核心转存（coredump），实际为进程运行过程中的一个内存快照；当进程crash时，操作系统接收到异常指令后，在进程crash之前，把进程做一个内存快照，保存进程的地址，寄存器，堆栈调用等信息，这个文件就叫coredump。



## Core文件产生原因

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



## 配置CoreDump

### 开启功能

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

### 文件大小

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

### 命名

使用以下命令来设置core文件的生成目录和命名：

- linux

  ```sh
  echo /xx/core.%e.%p> /proc/sys/kernel/core_pattern #xx:core文件生成路径
  
  # 如果echo无效,使用以下命令
  sysctl -w "kernel.core_pattern=/xx/core.%e.%p" > /dev/null #xx:core文件生成路径
  ```

- macos

  ```sh
  echo /path/core.%e.%p> /core/core.pid #path:core文件生成路径
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

### 测试

```sh
sleep 15

# 按下Ctrl + \
```



## Core格式

使用以下命令判断一个文件是否是core文件：

- `readelf -h xx`

  例：

  ```sh
  TODO
  ```



## GDB调试

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



## 参考

- [core文件生成及使用gdb调试](https://blog.csdn.net/zhang_han666/article/details/80668002)
- [gdb调试coredump(原理篇)](https://blog.csdn.net/sunlin972913894/article/details/113001810)

