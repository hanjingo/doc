# 开发工具

[TOC]



## GCC

### GCC选项

| 选项               | 说明                                        |
| ------------------ | ------------------------------------------- |
| -fsanitize=address | 启用 AddressSanitizer，用于内存访问错误定位 |

### 使用LeakSanitizer定位内存访问错误

1. 编写带有内存泄漏的程序：

   ```c++
   #include <iostream>
   
   int main()
   {
       int* data = new int[10];
       return 0;
   }
   ```

2. 编译

   ```shell
   g++ -fsanitize=address -g main.cpp -o mem_leak
   ```

3. 运行报错

   ```sh
   ./mem_leak
   
   =================================================================
   ==2275==ERROR: LeakSanitizer: detected memory leaks
   
   Direct leak of 40 byte(s) in 1 object(s) allocated from:
       #0 0x7fb17b356357 in operator new[](unsigned long) ../../../../src/libsanitizer/asan/asan_new_delete.cpp:102
       #1 0x7fb17bce825e in main /mnt/c/work/example/mem_leak/main.cpp:5
       #2 0x7fb17ad59d8f in __libc_start_call_main ../sysdeps/nptl/libc_start_call_main.h:58
   
   SUMMARY: AddressSanitizer: 40 byte(s) leaked in 1 allocation(s).
   ```

---



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

---



## Valgrind

Valgrind 的内存检查将被测试程序运行在一个特殊的虚拟机中，该虚拟机会在程序的每一步操作时进行监视和记录，从而在运行时对程序进行动态分析，捕获和跟踪程序执行时的内存操作，并在必要时提供警告或报告。

### 环境搭建

#### 命令安装

- Ubuntu/Debian

  ```sh
  sudo apt-get install valgrind
  ```

- CentOS/Fedora

  ```sh
  sudo yum install balgrind
  ```

- macos

  ```sh
  brew install valgrind
  ```

#### 编译安装

```sh
./configure
make
make install
```

#### 测试

1. 编写带有内存泄漏的程序：

   ```c++
   #include <iostream>
   
   int main()
   {
       int* data = new int[10];
       return 0;
   }
   ```

2. 编译

   ```shell
   g++ -g main.cpp -o mem_leak
   ```

3. 使用valgrind检测

   ```sh
   valgrind --leak-check=full --show-reachable=yes --show-leak-kinds=all --track-origins=yes ./mem_leak
   ```

### 使用

valgrind的命令格式为：`valgrind [工具名(可选)] [工具选项(可选)] [要检测的程序名] [程序选项(可选)]`

**注意：valgrind 工具的待测程序在编译的时候需要添加"-g"编译参数，以保留程序调试信息。**

#### 命令选项

| 所属工具 | 选项                                                         |
| -------- | ------------------------------------------------------------ |
| 通用     | `-h` `--help` 帮助<br>`--version` 查看版本<br>`-q` `--quiet` 安静模式<br>`-v` `--verbose` 显示详细信息<br>`--trace-children=no|yes` 是否跟踪到子进程中<br>`--trace-children-skip=patt1,patt2,...`<br>`--trace-children-skip-by-arg=patt1,patt2,...`<br>`--child-silent-after-fork=no`<br>`--vgdb=no`<br><br><br><br><br><br><br><br><br><br><br><br><br><br>`--track-fds=[default: no]` 退出时打印打开的文件描述符列表<br>`--time-stamp= [default: no]` 开启时间戳<br>`--log-fd= [default: 2, stderr]` 日志输出路径<br>`--log-file=` 日志文件名<br>`--log-file-exactly=` 类似于`--log-file=`但是不加后缀<br>`--log-file-qualifier=` 通过环境变量`$VAR`来指定日志文件名<br>`--log-socket=` 输出日志到指定网络地址<br>`--xml= [default: no]`<br>`--tool= [default: memcheck]` 指定使用的工具<br/><br><br><br><br><br><br><br> |

示例：

```sh
TODO
```

#### memcheck工具

细粒度的的内存检查器。

#### cachegrind

缓冲模拟器，用于标出每一行执行的指令数和导致的缓冲不命中数；

#### callgrind

对cachegrind的补充，在cachegrind的基础上增加了调用追踪功能，可以生成函数调用图；

#### helgrind

发现条件竞争问题；

#### massif

堆剖析器，它测量你的程序使用了多少堆内存；

#### 生成可视化图像

生成可视化的图形需要下载gprof2dot：https://pypi.org/project/gprof2dot/#files

---



## WireShark

TODO

---



## BreakPad

### 环境搭建

1. 下载源码

   ```sh
   # qt环境(搭配qt使用建议使用qBreakpad)
   git clone git@github.com:buzzySmile/qBreakpad.git
   cd qBreakpad/third_party
   git clone git@github.com:google/breakpad.git
   git clone git@github.com:ithaibo/linux-syscall-support.git lss
   
   # vs环境(TODO)
   
   # *nix(TODO)
   ```

2. 编译

   ```sh
   # qt环境（直接使用qt creater打开，点击编译）
   
   # *nix环境
   ./configure
   make
   ```

3. 测试（qt+breakpad）

   1. 新建Qt Console工程，命名为test

   2. 复制以下内容到test.pro

      ```txt
      # qBreakPad需要用到的特性
      QT += network
      CONFIG += thread exceptions rtti stl
      
      # 配置qBreakPad头文件和链接库路径
      win32:CONFIG(release, debug|release): {
      LIBS += -L$$PWD/qbreakpadlib/lib/release/ -lqBreakpad
      DEPENDPATH += $$PWD/qbreakpadlib/lib/release
      }
      else:win32:CONFIG(debug, debug|release): {
      LIBS += -L$$PWD/qbreakpadlib/lib/debug/ -lqBreakpad
      DEPENDPATH += $$PWD/qbreakpadlib/lib/debug
      }
      
      INCLUDEPATH += $$PWD/qbreakpadlib/include
      
      # 设置release模式生成调试信息（MSVC:xx.pdb, *nix/mingw:带调试信息的exe）
      win32-msvc* {
          QMAKE_LFLAGS_RELEASE += /MAP
          QMAKE_CFLAGS_RELEASE += /Zi
          QMAKE_LFLAGS_RELEASE += /debug /opt:ref
      }
      
      * {
          QMAKE_CFLAGS_RELEASE += -g
          QMAKE_CXXFLAGS_RELEASE += -g
          QMAKE_CFLAGS_RELEASE -= -O2
          QMAKE_CXXFLAGS_RELEASE -= -O2
          QMAKE_LFLAGS_RELEASE = -mthreads -W
      }
      
      QMAKE_CXXFLAGS_RELEASE += $$QMAKE_CFLAGS_RELEASE_WITH_DEBUGINFO
      QMAKE_LFLAGS_RELEASE += $$QMAKE_LFLAGS_RELEASE_WITH_DEBUGINFO
      ```

   3. 复制以下信息到指定位置：

      ```sh
      # 以下指令需要根据不同平台，文件目录和release/debug模式修改
      mkdir -r test/qbreakpadlib/lib
      cp qBreakpad文件夹/handler/libqBreakpad.a test/qbreakpadlib/lib/release 
      cp qBreakpad文件夹/handler/QBreakpadHandler.h test/qbreakpadlib/include
      cp qBreakpad文件夹/handler/QBreakpadHandler.cpp test/qbreakpadlib/include
      cp qBreakpad文件夹/handler/QBreakpadHttpUploader.h test/qbreakpadlib/include
      cp qBreakpad文件夹/handler/QBreakpadHttpUploader.cpp test/qbreakpadlib/include
      cp -r qBreakpad文件夹/handler/singletone test/qbreakpadlib/include
      ```

   4. 修改main.cpp

      ```cpp
      #include <QCoreApplication>
      
      #include "QBreakpadHandler.h"
      
      int main(int argc, char *argv[])
      {
          QCoreApplication a(argc, argv);
      
          QBreakpadInstance.setDumpPath("./");
      
          int *i = nullptr;
          *i = 1;
      
          return a.exec();
      }
      ```

   5. 点击编译运行

      **注意：debug和release模式要用对应版本的qBreakpad依赖库，不可混用!!!**

### 分析dump文件

#### 通过Windbg分析dump文件

1. 对于`mingw`环境编译生成的可执行程序，需要先使用工具[cv2pdb](https://github.com/rainers/cv2pdb)生产pdb文件（如已有pdb文件，可跳过）；
2. 选择`“File”`->`“Symbol File Path…”`，导入符号文件(*.pdb)；
3. 选择`“File”`->`“Source File Path…”`，导入源代码；
4. 选择`“File”`->`“Open Crash Dump…”`，导入dump文件；
5. 输入：!analyze -v 开始进行分析。

注意：有时候会报`ntdll.wrong.symbols.dll`这类错误，输入以下命令即可：

```cmd
TODO
```

#### 通过VS分析dump文件

1. 直接将`*.exe`, `*.dmp`, `*.pdb`（如果有）放到同一目录下，使用vs打开dump文件并调试

2. 对于`mingw`环境编译生成的可执行程序，需要先使用工具[cv2pdb](https://github.com/rainers/cv2pdb)生产pdb文件，并设置源代码路径：

   依次点击：视图-解决方案管理器-属性-调试源文件；导入源文件所在目录。

#### 通过breakpad工具分析dump文件

1. 导出dump文件信息

   ```sh
   dump_syms test.exe test.pdb > test.sym
   head -n1 test.sym > head.txt # 取第一行用于符号信息地址获取
   mkdir -p ./symbols/test
   mv test.sym ./symbols/test
   minidump_stackwalk ./xx.dmp ./symbols > test.txt
   ```

2. 使用address2line或其他工具定位错误。

### 报错

1. 在某些环境下无法生成dump文件

   你需要检查以下：

   - dump文件生成路径。
   - 权限不够。
   - 是否被其它程序捕获了异常，如：杀毒软件，输入法等。

### breakpad的继任者-crashpad

- [chromium/crashpad](https://github.com/chromium/crashpad)

---



## 参考

- [Valgrind学习总结](https://blog.csdn.net/andylauren/article/details/93189740)
- [实操学会使用内存分析工具Valgrind、LeakSanitizer，帮助检测和定位内存泄漏（C++）](https://blog.csdn.net/weixin_44046545/article/details/138417524)
- [一文学会使用 valgrind 工具进行程序内存检查](https://xie.infoq.cn/article/4e903f97fda10366f714d8266)
- [Debugging Under Unix: `gdb` Tutorial](https://www.cs.cmu.edu/~gilpin/tutorial/)
- [CMake生成可用gdb调试的可执行文件](https://blog.csdn.net/lemonaha/article/details/72837561)
- [Linux下的系统日志管理](https://blog.csdn.net/j_1282937574/article/details/81258153)
- [core文件生成及使用gdb调试](https://blog.csdn.net/zhang_han666/article/details/80668002)
- [gdb调试coredump(原理篇)](https://blog.csdn.net/sunlin972913894/article/details/113001810)
- [性能测试入门——LoadRunner使用初探](https://www.admin5.com/article/20161114/695706.shtml)
- [google/breakpad](https://github.com/google/breakpad)
- [buzzySmile/qBreakpad](https://github.com/buzzySmile/qBreakpad)
- [Qt-mingw 生成dump文件并使用vs调试定位错误代码](https://blog.csdn.net/LiHong333/article/details/129798322)
- [Qt Windows系统使用QBreakpad实战](https://blog.csdn.net/CLinuxF/article/details/122917770)
- [跨平台的Qt程序崩溃生成Dump文件Breakpad](https://blog.csdn.net/HeroGuo_JP/article/details/105387526)
- [Google Breakpad 在 windows下捕获程序崩溃报告](https://blog.csdn.net/goforwardtostep/article/details/56304285)
- [Google Breakpad 在 windows下捕获程序崩溃报告](https://blog.csdn.net/goforwardtostep/article/details/56304285)
- [window mingw qbreakpad 生成dump](https://blog.csdn.net/woquNOKIA/article/details/127860799)

