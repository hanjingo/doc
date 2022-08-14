# 第21章 与网络打印机通信

[TOC]



## 21.1 引言

`网络打印协议（Internet Printing Protocol，IPP）`



## 21.2 网络打印协议

![21_1](res/21_1.png)

*IPP报文结构*

![21_2](res/21_2.png)

*IPP首部结构*

![21_3](res/21_3.png)

*IPP属性编码示例*

![t21_1](res/t21_1.png)

*打印作业请求的属性*

![t21_2](res/t21_2.png)

*主要的IPP RFC*



## 21.3 超文本传输协议



## 21.4 打印假脱机技术

![21_4](res/21_4.png)

*打印假脱机组件*



## 21.5 源代码

```c++
TODO
```

*ipp.h*

```c++
TODO
```

*print.h*

```c++
TODO
```

*util.c*

```c++
TODO
```

*print.c*

```c++
TODO
```

*printd.c*

```c++
#include <fcntl.h>
int getopt(int argc, const *const argv[], const char *options);
extern int optind, opterr, optopt;
extern char *optarg;
```

- `argc` 参数数量

- `argv` 参数数组

- `options` 命令支持的选项字符

- `返回值`

  成功：下一个选项字符

  全部选项处理完毕：-1

*按照一致的方式来处理命令行选项*



## 21.6 小结

