# 开发工具

[TOC]



## GDB

### GDB命令

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

### 生成调试文件设置

#### CMAKE

```cmake
SET(CMAKE_BUILD_TYPE "Debug")
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")
SET(CMAKE_CXX_FLAGS_RELEASE "$EN{CXXFLAGS} -O3 -Wall")
```

#### MAKE

TODO

### 调试可执行文件

TODO

### 调试进程

使用以下命令来调试正在运行的进程：

```sh
gdb pfile PID #pfile为进程文件，PID为进程ID
```

### 调试core文件

使用以下命令来调试core文件：

```sh
gdb core #core:core文件绝对路径
```



## valgrind

TODO



## WireShark

TODO



## BreakPad

参考：[BreakPad](..\LANG\C++\OTHER\break_pad_zh.md)



## 参考

- [Valgrind学习总结](https://blog.csdn.net/andylauren/article/details/93189740)
- [Debugging Under Unix: `gdb` Tutorial](https://www.cs.cmu.edu/~gilpin/tutorial/)
- [CMake生成可用gdb调试的可执行文件](https://blog.csdn.net/lemonaha/article/details/72837561)
- [Linux下的系统日志管理](https://blog.csdn.net/j_1282937574/article/details/81258153)
- [core文件生成及使用gdb调试](https://blog.csdn.net/zhang_han666/article/details/80668002)
- [gdb调试coredump(原理篇)](https://blog.csdn.net/sunlin972913894/article/details/113001810)
- [性能测试入门——LoadRunner使用初探](https://www.admin5.com/article/20161114/695706.shtml)

