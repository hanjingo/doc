# 第18章 终端I/O

[TOC]



## 18.1 引言



## 18.2 综述

终端I/O有两种不同的工作模式：

1. `规范模式输入处理（Canonical mode input processing，默认）` 终端输入以行为单位进行处理。
2. `非规范模式输入处理（Noncanonical mode input processing）` 输入字符并不组成行。

![18_1](res/18_1.png)

*终端设备的输入，输出队列逻辑结构*

![18_2](res/18_2.png)

*终端行规程*

![t18_1](res/t18_1.png)

*c_cflag终端标志*

![t18_2a](res/t18_2a.png)

![t18_2b](res/t18_2b.png)

*c_iflag终端标志*

![t18_3](res/t18_3.png)

*c_lflag终端标志*

![t18_4a](res/t18_4a.png)

![t18_4b](res/t18_4b.png)

*c_oflag终端标志*

![t18_5](res/t18_5.png)

*终端I/O函数摘要*

![18_3](res/18_3.png)

*与终端有关的函数之间的关系*



## 18.3 特殊输入字符

![18_6](res/18_6.png)

*终端特殊输入字符*

例：

```c++
TODO
```

*禁用中断字符和更改文件结束字符*

| 特殊输入字符 | 说明 |
| ------------ | ---- |
| CR           |      |
| DISCARD      |      |
| DSUSP        |      |
| EOF          |      |
| EOL          |      |
| EOL2         |      |
| ERASE        |      |
| ERASE2       |      |
| INTR         |      |
| KILL         |      |
| LNEXT        |      |
| NL           |      |
| QUIT         |      |
| REPRINT      |      |
| START        |      |
| STATUS       |      |
| STOP         |      |
| SUSP         |      |
| WERASE       |      |



## 18.4 获得和设置终端属性

```c++
#include <termios.h>
int tcgetattr(int filedes, struct termios *termptr);
int tcsetattr(int filedes, int opt, const struct termios *termptr);
```

- `filedes` 终端设备

- `termptr` 返回的终端属性指针

- `opt` 选项

  - TCSANOW 更改立即发生；
  - TCSADRAIN 发送了所有输出后更改才发生（若更改输出参数则应使用此选项）；
  - TCSAFLUSH 发送了所有输出后更改才发生（更进一步，在更改发生时未读的所有输入数据都被删除（刷清））；

- `返回值`

  成功：0

  失败：-1

*获得/设置终端属性*



## 18.5 终端选项标志

例：

```c++
TODO
```

*tcgetattr和tcsetattr实例*

| 选项标志   | 说明 |
| ---------- | ---- |
| ALTWERASE  |      |
| BRKINT     |      |
| BSDLY      |      |
| CBAUDEXT   |      |
| CCAR_OFLOW |      |
| CCTS_OFLOW |      |
| CDSR_OFLOW |      |
| CDTR_IFLOW |      |
| CIBAUDEXT  |      |
| CIGNORE    |      |
| CLOCAL     |      |
| CMSPAR     |      |
| CRDLY      |      |
| CREAD      |      |
| CRTSCTS    |      |
| CRTS_IFLOW |      |
| CRTSXOFF   |      |
| CSIZE      |      |
| CSTOPB     |      |
| ECHO       |      |
| ECHOCTL    |      |
| ECHOE      |      |
| ECHOK      |      |
| ECHOKE     |      |
| ECHONL     |      |
| ECHOPRT    |      |
| EXTPROC    |      |
| FFDLY      |      |
| FLUSHO     |      |
| HUPCL      |      |
| ICANON     |      |
| ICRNL      |      |
| IEXTEN     |      |
| IGNBRK     |      |
| IGNCR      |      |
| IGNPAR     |      |
| IMAXBEL    |      |
| INLCR      |      |
| INPCK      |      |
| ISIG       |      |
| ISTRIP     |      |
| IUCLC      |      |
| IXANY      |      |
| IXOFF      |      |
| IXON       |      |
| MDMBUF     |      |
| NLDLY      |      |
| NOFLSH     |      |
| NOKERNINFO |      |
| OCRNL      |      |
| OFDEL      |      |
| OFILL      |      |
| OLCUC      |      |
| ONLCR      |      |
| ONLRET     |      |
| ONOCR      |      |
| ONOEOT     |      |
| OPOST      |      |
| OXTABS     |      |
| PARENB     |      |
| PAREXT     |      |
| PARMRK     |      |
| PARODD     |      |
| PENDIN     |      |
| TABDLY     |      |
| TOSTOP     |      |
| VTDLY      |      |
| XCASE      |      |



## 18.6 stty命令

显示终端的所有选项命令：

```sh
stty -a
```



## 18.7 波特率函数

```c++
#include <termios.h>
speed_t cfgetispeed(const struct termios *termptr);
speed_t cfgetospeed(const struct termios *termptr);
```

- `termptr` 终端
- `返回值` 波特率

*获取波特率*

```c++
#include <termios.h>
int cfsetispeed(struct termios *termptr, speed_t speed);
int cfsetospeed(struct termios *termptr, speed_t speed);
```

- `termptr` 终端

- `speed` 波特率

- `返回值`

  成功：0

  失败：-1

*设置波特率*



## 18.8 行控制函数

```c++
#include <termios.h>
int tcdrain(int filedes);
```

- `filedes` 终端设备

- `返回值`

  成功：0

  失败：-1

*等待所有输出都被发送*

```c++
#include <termios.h>
int tcflow(int filedes, int action);
```

- `filedes` 终端设备

- `action` 控制动作

  - TCOOFF 输出被挂起；
  - TCOON 重新启动以前被挂起的输出；
  - TCIOFF 系统发送一个STOP字符（这将使终端设备暂停发送数据）；
  - TCION 系统发送一个START字符（这将使终端恢复发送数据）。

- `返回值`

  成功：0

  失败：-1

*对输入和输出流的控制命令进行控制*

```c++
#include <termios.h>
int tcflush(int filedes, int queue);
```

- `filedes` 终端设备

- `queue` 控制动作

  - TCIFLUSH 刷清输入队列
  - TCOFLUSH 刷清输出队列
  - TCIOFLUSH 刷清输入，输出队列

- `返回值`

  成功：0

  失败：-1

*刷清（抛弃）输入/输出缓冲区*

```c++
#include <termios.h>
int tcsendbreak(int filedes, int duration);
```

- `filedes` 终端设备

- `duration` 时长（值为0时，此种发送延续0.25至0.5之间）

- `返回值`

  成功：0

  失败：-1

*在一个指定的时间区间内发送连续的0位流*



## 18.9 终端标识

```c++
#include <stdio.h>
char *ctermid(char *ptr);
```

- `ptr` 控制终端名

- `返回值`

  成功：返回指向控制终端名的指针

  失败：返回指向空字符串的指针

*设置控制终端名*

例：

```c++
TODO
```

*POSIX.1 ctermid函数的实现*

```c++
#include <unistd.h>
int isatty(int filedes);
```

- `filedes` 终端

- `返回值`

  是终端设备：1

  不是终端设备：0

*判断是否为终端设备*

```c++
#include <unistd.h>
char *ttyname(int filedes);
```

- `filedes` 终端

- `返回值`

  成功：指向终端路径名的指针

  失败：NULL

*返回在文件描述符上打开的终端设备的路径名*

例：

```c++
TODO
```

*POSIX.1 isatty函数的实现*

例：

```c++
TODO
```

*测试isatty函数*

例：

```c++
TODO
```

*POSIX.1 ttyname函数的实现*

例：

```c++
TODO
```

*测试ttyname函数*



## 18.10 规范模式

以下几个条件都会导致规范模式下读返回：

- 所要求的字节数已读到时，读返回；
- 当读到一个行定界符时，读返回；
- 如果捕捉到信号且该函数并不自动重启动，则读返回。

例：

```c++
TODO
```

*getpass函数的实现*

例：

```c++
TODO
```

*调用getpass函数*



## 18.11 非规范模式

![t18_7](res/t18_7.png)

*非规范输入的四种情形*

例：

```c++
TODO
```

*将终端模式设置为原始或chreak模式*

例：

```c++
TODO
```

*测试原始终端模式和cbreak终端模式*



## 18.12 终端的窗口大小

```c++
struct winsize {
    unsigned short ws_row;
    unsigned short ws_col;
    unsigned short ws_xpixel;
    unsigned short ws_ypixel;
};
```

*内核为每个终端和伪终端保存一个winsize结构*

winsize结构作用如下：

- 用ioctl的TIOCGWINSZ命令可以取此结构的当前值；
- 用ioctl的TIOCSWINSZ命令可以将此结构的新值存放到内核中；如果此新值与存放在内核中的当前值不同，则向前台进程组发送SIGWINCH信号；
- 除了存放结构的当前值以及在此值改变时产生一个信号以外，内核对该结构不进行任何其它操作；
- 提供这种功能的目的是，当窗口大小发生变化时通知应用程序；应用程序接到此信号后，他可以取窗口大小的新值，然后重绘屏幕。

例：

```c++
TODO
```

*打印窗口大小*



## 18.13 termcap, terminfo和curses



## 18.14 小结

