[TOC]

# GDB调试工具



## 命令

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

更具体的内容使用GDB的`help`命令查看；



## 生成GDB调试文件

### gcc

### CMAKE



## 参考

- [Debugging Under Unix: `gdb` Tutorial](https://www.cs.cmu.edu/~gilpin/tutorial/)

