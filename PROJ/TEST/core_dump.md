[TOC]

# 如何定位Core Dump问题

（coredump，核心转存），实际为进程运行过程中的一个内存快照；当进程crash时，操作系统接收到异常指令后，在进程crash之前，把进程做一个内存快照，保存进程的地址，寄存器，堆栈调用等信息，这个文件就叫coredump。



## core文件产生原因

| 信号    | 说明 |
| ------- | ---- |
| SIGABRT |      |
| SIGBUS  |      |
| SIGEMT  |      |
| SIGFPE  |      |
| SIGILL  |      |
| SIGIOT  |      |
| SIGQUIT |      |
| SIGSEGV |      |
| SIGSYS  |      |
| SIGTRAP |      |
| SIGXCPU |      |
| SIGXFSZ |      |



## 配置

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
  echo /path/core.%e.%p> /proc/sys/kernel/core_pattern #path路径
  ```

- macos

  ```sh
  echo /path/core.%e.%p> /core/core.pid #path路径
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



## GDB调试

TODO



## 参考

- [core文件生成及使用gdb调试](https://blog.csdn.net/zhang_han666/article/details/80668002)
- [gdb调试coredump(原理篇)](https://blog.csdn.net/sunlin972913894/article/details/113001810)

