# libzmq环境搭建

[TOC]



## 二进制安装

### windows

1. 去github：https://github.com/zeromq/libzmq/releases 下载官方编译好的zeromq；
2. 解压文件；
2. 添加解压后的文件目录到环境变量；
2. 完成。



## 源码安装

### windows

1. 安装cmake与VisualStudio；

2. 下载libsodium源码（zeromq依赖于这个库）；

   ```sh
   git clone git://github.com/jedisct1/libsodium.git
   ```

3. 用vs打开`libsodium\builds\msvc\vs2015\libsodium.sln`，并编译libsodium的动态/静态链接库；

4. 下载libzmq源码

   ```sh
   git clone git@github.com:zeromq/libzmq.git
   ```

5. 编译libzmq的动态/静态链接库；

   打开`VS2015开发人员命令提示`工具（其他版本的VS用其自带工具），进入编译目录，执行命令：

   ```sh
   cmake .. -G "编译器" -D参数
   ```

   | 编译器                      | 说明              |
   | --------------------------- | ----------------- |
   | Visual Studio 14 2015 Win64 | vs2015 64位编译器 |
   | Visual Studio 14 2015 Win32 | vs2015 32位编译器 |
   | ...                         |                   |
   
   | 参数            | 说明         |
   | --------------- | ------------ |
   | ZMQ_BUILD_TESTS | 构建test示例 |
   | BUILD_SHARED    | 构建动态库   |
   | BUILD_STATIC    | 构建静态库   |
   | ...             |              |

   例子：
   
   ```sh
   cmake .. -DZMQ_BUILD_TESTS=OFF -DBUILD_STATIC=ON -DBUILD_SHARED=ON
   ```
   
   使用VS2015（或其它版本），打开预编译后的`ZeroMQ.sln`文件，进行编译构建。
   
6. 完成。

### linux

1. 新建build文件夹，并构建cmake

   ```sh
   mkdir build
   cd build
   cmake .. -DZMQ_BUILD_TESTS=OFF -DBUILD_STATIC=ON -DBUILD_SHARED=ON
   ```

2. make构建

   ```sh
   make
   ```



## 测试

### qt+zeromq静态库示例

1. 新建qt console项目；

2. 复制`zmq.h`, `libzmq-v140-mt-4_3_4.dll`, `libsodium.dll`, `libzmq-v140-mt-4_3_4.lib`文件到我们的项目；

3. 修改`*.pro`文件，添加下面内容：

   ```txt
   LIBS += -L$$PWD/./ -llibzmq-v140-mt-4_3_4
   
   HEADERS += \
       zmq.h
   ```

4. 修改main.cpp为以下内容：

   ```c++
   #include <QCoreApplication>
   #include <iostream>
   #include "zmq.h"
   
   int main(int argc, char *argv[])
   {
       QCoreApplication a(argc, argv);
   
       std::cout << "qt+zmq" << std::endl;
       int x, y, z;
       zmq_version(&x, &y, &z);
       std::cout << "version:" << x << "-" << y << "-" << z;
   
       return a.exec();
   }
   ```

5. 输出

   ```sh
   qt+zmq
   version:4-3-4
   ```

   

## 参考

- [在QT中添加zeromq库，zeromq的下载编译](https://www.365seal.com/y/7evolozRVA.html)
- [ZMQ第三方通讯库的编译与使用](https://blog.songjiahao.com/archives/357)
- [在cmake工程中使用ZeroMQ](http://t.zoukankan.com/y4247464-p-14241876.html)
- [在QT中添加zeromq库，zeromq的下载编译](http://t.zoukankan.com/h2zZhou-p-13271933.html)
- [C/C++编程：ZeroMQ安装以及使用（windows+centos）_OceanStar的博客-程序员宅基地](https://www.cxyzjd.com/article/zhizhengguan/114626114#windows__vs2019__cmake__cppzmq_255)
