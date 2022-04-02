# openssl环境搭建

[TOC]

## 编译安装

拉取项目：

```sh

```

### windows

#### 环境要求

- VisualStudio 2015
- Perl-5.32.1.1
- nasm-2.15.05
- openssl-1.1.0

#### 安装perl

1. 去https://strawberryperl.com/下载perl-5.32.1.1（或其它版本）并安装。
2. 安装完成后自动注册了perl环境。

#### 安装nasm

1. 去https://www.nasm.us/pub/nasm/releasebuilds下载nasm-2.15.05（或其他版本）安装。
2. 安装完成后，在环境变量中加入nasm的安装路径（尽量避免中文）。

#### 配置nmake

1. 找到nmake.exe的路径（一般在`...\Microsoft Visual Studio x\VC\bin`目录下）。
2. 添加到环境变量中。

#### 编译项目

1. 配置环境

   打开 "VS2015 开发人员命令提示"（64位打开 "VS2015 x64 x86 兼容工具命令提示符"），进入到openssl代码目录，执行Configure命令：
   
   ```sh
   perl Configure [no-<cipher> ...] [enable-<cipher> ...] [-Dxxx] [-lxxx] [-Lxxx] [-fxxx] [-Kxxx] [no-hw-xxx|no-hw] [[no-]threads] [[no-]shared] [[no-]zlib|zlib-dynamic] [no-asm] [no-dso] [no-egd] [sctp] [386] [--prefix=DIR] [--openssldir=OPENSSLDIR] [--with-xxx[=vvv]] [--config=FILE] os/compiler[:flags]
   ```
   
   - `--prefix` 编译完成后的安装路径
   
   - `--openssldir` 编译完后的生成的配置文件的安装路径
   
   - `[no-]shared` 编译动态/静态库
   
     - no-shared 静态库
     - shared 动态库

   - `os/compiler[:flags]` 目标平台

     主要的windows目标平台有以下几种：
   
     - `VC-WIN64A` 适用于64位下的amd处理器。
     - `VC-WIN64I` 适用于64位下的intel处理器。
     - `VC-WIN64-ARM` 适用于64位下的arm处理器。
     - `VC-WIN32` 适用于32位下x86架构处理器。
   
   例1，编译window 下amd x64程序：
   
   ```c++
   perl Configure VC-WIN64A
   ```
   
   例2，让安装程序自动选择合适的平台：
   
   ```sh
   perl Configure
   ```
   
2. nmake编译

   ```sh
   nmake
   
   # 确认编译成功
   nmake test
   ```
   
3. 编译安装

   ```sh
   nmake install
   ```

#### 报错处理

- 提示无法打开包括文件`c1.EXE`；

   **问题**

   ```sh
   fatal error C1083: 无法打开包括文件: “limits.h”: No such file or directoryNMAKE : fatal error U1077: “"C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\bin\cl.EXE"”: 返回代码“0x2”
   Stop.
   NMAKE : fatal error U1077: “"C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\bin\nmake.exe"”: 返回代码“0x2”
   ```

   **原因**

   1. 在安装visual studio的时候没有勾选注册环境变量。
   2. vs版本不够。

   **解决**

   1. 在系统环境变量中加入visual studio的以下路径：
      - bin路径：`...\Microsoft Visual Studio x\VC\bin`。
      - IDE路径：`...\Microsoft Visual Studio x\Common7\IDE`。
   2. 升级vs版本。
   
- 提示模块计算机类型“X86”与目标计算机类型“x64”冲突

   **问题**

   ```sh
   crypto\aes\aes_cfb.obj : fatal error LNK1112: 模块计算机类型“X86”与目标计算机类型“x64”冲突
   NMAKE : fatal error U1077: “link”: 返回代码“0x1”
   Stop.
   NMAKE : fatal error U1077: “"C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\BIN\amd64\nmake.exe"”: 返回代码“0x2”
   Stop.
   ```

   **原因**

   1. 计算机操作系统/编译器位数与生成的目标程序平台不一致。

   **解决**

   1. 调整生成的目标程序平台。
   
- 在验证编译成功时报错

   **问题**

   ```sh
   Test Summary Report
   -------------------
   test\recipes\90-test_fuzz.t           (Wstat: 65280 Tests: 0 Failed: 0)
     Non-zero exit status: 255
     Parse errors: No plan found in TAP output
   Files=100, Tests=552, 135 wallclock secs ( 0.58 usr +  0.14 sys =  0.72 CPU)
   Result: FAIL
   NMAKE : fatal error U1077: “C:\Strawberry\perl\bin\perl.exe”: 返回代码“0x1”
   Stop.
   NMAKE : fatal error U1077: “"C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\BIN\nmake.exe"”: 返回代码“0x2”
   Stop.
   ```

   **原因**

   1. perl的相关模块与NOTES.PERL要求的对不上。

   **解决**

   1. 检查并安装相关模块；

      进入perl CPAN：

      ```sh
      perl -MCPAN -e shell
      ```

      检查模块：

      ```sh
      i Test::More
      i Text::Template
      ```

      安装模块：

      ```sh
      install Test::More
      install Text::Template
      ```

### linux

#### 环境要求

- gcc
- openssl-1.1.0

#### 安装gcc

TODO

#### 编译安装

1. 

### macos

TODO



## 项目引用

### Visual Studio

TODO



## 参考

- [OpenSSL 中文手册](https://www.openssl.net.cn/)
- [ActivePerl、dmake、nasm、nmake编译OpenSSL(1.1.0系列)](https://blog.csdn.net/ayang1986/article/details/77917297?locationNum=5&fps=1)
- [nmake下一些错误的解决办法](https://blog.csdn.net/hongqiang200/article/details/39210767)
- [VS2015编译Openssl-1.1.0f](https://blog.csdn.net/ljttianqin/article/details/72978612)
- [Windows下openssl的下载安装和使用](https://blog.csdn.net/houjixin/article/details/25806151)
- [CentOS6安装openssl-1.1.1版本可能遇到的问题及解决](https://blog.csdn.net/yxy369/article/details/104517168)





