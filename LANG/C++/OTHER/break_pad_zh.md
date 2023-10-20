# BreakPad

[TOC]



## 环境搭建

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
   
      

## 分析dump文件

### 通过VS分析dump文件

1. 直接将`*.exe`, `*.dmp`, `*.pdb`（如果有）放到同一目录下，使用vs打开dmp文件并调试

2. 对于`mingw`环境编译生成的可执行程序，需要设置源代码路径：

   依次点击：视图-解决方案管理器-属性-调试源文件；导入源文件所在目录。

### 通过breakpad工具分析dump文件

1. 导出dump文件信息

   ```sh
   dump_syms test.exe test.pdb > test.sym
   head -n1 test.sym > head.txt # 取第一行用于符号信息地址获取
   mkdir -p ./symbols/test
   mv test.sym ./symbols/test
   minidump_stackwalk ./xx.dmp ./symbols > test.txt
   ```

2. 使用address2line或其他工具定位错误。



## 报错

1. 在某些环境下无法生成dump文件

   你需要检查以下：

   - dump文件生成路径。
   - 权限不够。
   - 是否被其它程序捕获了异常，如：杀毒软件，输入法等。



## breakpad的继任者-crashpad

- [chromium/crashpad](https://github.com/chromium/crashpad)

TODO



## 参考

- [google/breakpad](https://github.com/google/breakpad)
- [buzzySmile/qBreakpad](https://github.com/buzzySmile/qBreakpad)
- [Qt Windows系统使用QBreakpad实战](https://blog.csdn.net/CLinuxF/article/details/122917770)
- [跨平台的Qt程序崩溃生成Dump文件Breakpad](https://blog.csdn.net/HeroGuo_JP/article/details/105387526)
- [Google Breakpad 在 windows下捕获程序崩溃报告](https://blog.csdn.net/goforwardtostep/article/details/56304285)
- [Google Breakpad 在 windows下捕获程序崩溃报告](https://blog.csdn.net/goforwardtostep/article/details/56304285)
- [window mingw qbreakpad 生成dump](https://blog.csdn.net/woquNOKIA/article/details/127860799)

