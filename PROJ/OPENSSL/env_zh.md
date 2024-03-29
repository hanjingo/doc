# openssl环境搭建

<!-- vim-markdown-toc GFM -->

* [1 编译安装](#1-编译安装)
    - [1.1 环境要求](#11-环境要求)
    - [1.2 配置环境](#12-配置环境)
        + [1.2.1 windows](#121-windows)
        + [1.2.2 Linux](#122-linux)
        + [1.2.3 MacOS](#123-macos)
    - [1.3 编译项目](#13-编译项目)
        + [1.3.1 执行Configure程序](#131-执行configure程序)
        + [1.3.2 编译](#132-编译)
    - [1.4 报错处理](#14-报错处理)
* [2 项目引用](#2-项目引用)
    - [2.1 Visual Studio](#21-visual-studio)
    - [2.2 CMake](#22-cmake)
* [参考](#参考)

<!-- vim-markdown-toc -->



## 1 编译安装

### 1.1 环境要求

（本文档在以下环境中测试通过，其它环境未经测试）

| 操作系统 | 环境                                    | 版本要求（最低）                     |
| -------- | --------------------------------------- | ------------------------------------ |
| Window   | VisualStudio<br>Perl<br>nasm<br>openssl | 2015<br>5.32.1.1<br>2.15.05<br>1.1.1 |
| linux    | gcc<br>openssl                          | 7.1<br>1.1.1                         |
| macos    | -                                       | -                                    |

### 1.2 配置环境

拉取项目：

```sh
git clone git@github.com:openssl/openssl.git

# 切换分支
git checkout remotes/origin/OpenSSL_1_1_1-stable # 你可以选择其他分支，注意不同分支的区别

# 拉取子模块
git submodule update --init --recursive
```

#### 1.2.1 windows

- 安装Perl
  1. 去https://strawberryperl.com/下载perl-5.32.1.1（或其它版本）并安装。

  2. 安装完成后自动注册了perl环境。
- 安装nasm（根据环境要求安装）
  1. 去https://www.nasm.us/pub/nasm/releasebuilds下载nasm-2.15.05（或其他版本）安装。
  2. 安装完成后，在环境变量中加入nasm的安装路径（尽量避免中文）。
- 配置nmake（根据环境要求配置）

  1. 找到nmake.exe的路径（一般在`...\Microsoft Visual Studio x\VC\bin`目录下）。

  2. 添加到环境变量中。

#### 1.2.2 Linux

- 配置编译环境

  ubuntu/debain

  ```sh
  sudo apt update
  sudo apt upgrade
  sudo apt install build-essential checkinstall zlib1g-dev
  ```

#### 1.2.3 MacOS

TODO

### 1.3 编译项目

#### 1.3.1 执行Configure程序

windows下打开 "VS201x 开发人员命令提示（32位系统）" 或 "VS201x x64 x86 兼容工具命令提示符"（64位系统），进入到openssl代码目录，执行Configure命令：

```sh
perl Configure [no-<cipher> ...] [enable-<cipher> ...] [-Dxxx] [-lxxx] [-Lxxx] [-fxxx] [-Kxxx] [no-hw-xxx|no-hw] [[no-]threads] [[no-]shared] [[no-]zlib|zlib-dynamic] [no-asm] [no-dso] [no-egd] [sctp] [386] [--prefix=DIR] [--openssldir=OPENSSLDIR] [--with-xxx[=vvv]] [--config=FILE] os/compiler[:flags]
```

macos/linux下打开终端，进入到openssl代码目录，执行Configure命令：

```sh
[sudo] ./config [no-<cipher> ...] [enable-<cipher> ...] [-Dxxx] [-lxxx] [-Lxxx] [-fxxx] [-Kxxx] [no-hw-xxx|no-hw] [[no-]threads] [[no-]shared] [[no-]zlib|zlib-dynamic] [no-asm] [no-dso] [no-egd] [sctp] [386] [--prefix=DIR] [--openssldir=OPENSSLDIR] [--with-xxx[=vvv]] [--config=FILE] os/compiler[:flags]
```

- `no-<cipher>` 停用某些加密算法(bf, cast, des, dh, dsa,hmac, md2, md5, mdc2, rc2, rc4, rc5, rsa, sha)

- `enable-<cipher>` 启用某些加密算法

- `[-Dxxx] [-lxxx] [-Lxxx] [-fxxx] [-Kxxx]` 预处理器参数设置

- `no-hw-xxx|no-hw`

- `[no-]threads` 是否启用多线程

- `[no-]shared` 编译静态/动态库

- `[no-]zlib|zlib-dynamic`

- `no-asm` 不使用汇编代码

- `no-dso`

- `no-egd`

- `sctp`

- `386`

- `--prefix` 编译完成后的安装路径

- `--openssldir` 编译完后的生成的配置文件的安装路径

- `os/compiler[:flags]` 目标平台

  主要的windows目标平台有以下几种：

  - `VC-WIN64A` 适用于amd x64处理器Release版。
  - `debug-VC-WIN64A` 适用于amd x64处理器Debug版。
  - `VC-WIN64I` 适用于intel x64处理器Release版。
  - `VC-WIN64-ARM` 适用于arm 64处理器Release版。
  - `VC-WIN32` 适用于x86架构处理器Release版。
  - ...

  主要的linux目标平台：

  - `linux-x86_64` 使用于64位linux。
  - ...
  
  主要的macos目标平台：
  
  TODO

例1，编译window 下32位程序：

```c++
perl Configure VC-WIN32 --prefix="C:\Program Files\openssl" --openssldir="C:\Program Files\openssl"
```

例2，让安装程序自动选择合适的平台：

```sh
perl Configure
```

例3，编译ubuntu18.04下64位程序：

```sh
./config linux-x86_64 --prefix=/usr/local/openssl --openssldir=/usr/local/openssl
```

#### 1.3.2 编译

- Window

  openssl版本<=1.1.0：

  ```sh
  # 用VC自带的构建程序构建一遍
  ms\do_nasm
  
  # 切换到VC目录`...\Microsoft Visual Studio x\VC\bin`并执行脚本
  vcvars32.bat
  
  # 切回openssl目录，使用nmake进行编译
  nmake -f ms\ntdll.mak # 生成动态库
  nmake -f ms\nt.mak # 生成静态库
  
  # 测试是否编译成功; 显示：`passed all tests`则表示编译成功
  nmake -f ms\ntdll.mak test # 动态库
  nmake -f ms\nt.mak test # 静态库
  
  # 安装
  nmake -f ms\ntdll.mak install # 动态库
  nmake -f ms\nt.mak install # 静态库
  ```

  openssl版本>1.1.0:

  ```sh
  nmake
  nmake test
  nmake install
  ```

- Linux

  编译：

  ```sh
  sudo make
  sudo make test
  ```
  
  编译安装：
  
  ```sh
  sudo make install
  ```
  
  建立链接：
  
  ```sh
  export OPENSSL_DIR="/usr/local/openssl" # 可以换成你想要安装的目录
  sudo ln -s ${OPENSSL_DIR}/bin/openssl /usr/bin/openssl
  sudo ln -s ${OPENSSL_DIR}/lib/libssl.so.1.1 /usr/lib/libssl.so.1.1
  sudo ln -s ${OPENSSL_DIR}/lib/libcrypto.so.1.1 /usr/lib/libcrypto.so.1.1
  
  # 确认
  openssl version
  ```

### 1.4 报错处理

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

   1. perl的相关模块与文件NOTES.PERL要求的对不上。

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

- 执行Configure时，提示生成目标已经定义

  **问题**

  ```sh
  Failure!  build file wasn't produced.
  Please read INSTALL.md and associated NOTES-* files.  You may also have to
  look over your available compiler tool chain or change your configuration.
  
  target already defined - VC-WIN32 (offending arg: Files\openssl\bin)
  ```

  **原因**

  1. 中文字符的问题；
  1. 路径没有打双引号。
  
  **解决**
  
  1. 去掉中文字符；
  
  1. 路径加上双引号
  
     ```sh
     # 错误做法
     perl Configure VC-WIN32 --prefix=C:\Program Files\openssl --openssldir=C:\Program Files\openssl
     
     # 正确做法
     perl Configure VC-WIN32 --prefix="C:\Program Files\openssl" --openssldir="C:\Program Files\openssl"
     ```
     
     
     

## 2 项目引用

### 2.1 Visual Studio

- 添加目录

  项目-属性-VC++目录-包含目录 添加：`openssl安装目录\include`。

  项目-属性-VC++目录-包含目录 添加：`openssl安装目录\lib`。

- 复制动态/静态链接库文件

  复制静态文件：`openssl安装目录\lib\libcrypto.lib`到VS项目根目录。

  复制静态文件：`openssl安装目录\lib\libssl.lib`到VS项目根目录。

- 在代码中引用

  ```c++
  // 静态引用
  
  #pragma comment(lib, "libcrypto.lib")
  #pragma comment(lib, "libssl.lib")
      
  // 动态引用
  ```

### 2.2 CMake

- 集成CMakeLists.txt

  ```cmake
  find_package(OpenSSL REQUIRED)
  
  # 设置openssl头文件
  set(OPENSSL_INCLUDE_DIRS ${OPENSSL_DIR}/include)
  # 设置openssl依赖库
  set(OPENSSL_SSL_LIBRARY ${OPENSSL_DIR}/lib/libssl.so.1.1)
  # 设置openssl工具库
  set(OPENSSL_CRYPTO_LIBRARY ${OPENSSL_DIR}/lib/libcrypto.so.1.1)
  # 设置openssl生成路径
  set(OPENSSL_INSTALL_PREFIX ${OPENSSL_DIR}/lib/libcrypto.so.1.1)
  
  target_link_libraries(${PROJECT_NAME} OpenSSL::SSL OpenSSL::Crypto)
  ```



## 参考

- [OpenSSL 中文手册](https://www.openssl.net.cn/)
- [Windows 下编译 OpenSSL](https://blog.csdn.net/liang19890820/article/details/51658574)
- [C/C++使用openssl进行摘要和加密解密（md5, sha256, des, rsa）](https://blog.csdn.net/u012234115/article/details/72762045)
- [Visual Studio 2015 中使用 OpenSSL](https://fenying.net/post/2015/12/02/using-openssl-with-vs2015/)
- [OpenSSL/GmSSL+VS2015环境配置](https://blog.csdn.net/apianmuse/article/details/107353574)
- [ActivePerl、dmake、nasm、nmake编译OpenSSL(1.1.0系列)](https://blog.csdn.net/ayang1986/article/details/77917297?locationNum=5&fps=1)
- [nmake下一些错误的解决办法](https://blog.csdn.net/hongqiang200/article/details/39210767)
- [VS2015编译Openssl-1.1.0f](https://blog.csdn.net/ljttianqin/article/details/72978612)
- [Windows下openssl的下载安装和使用](https://blog.csdn.net/houjixin/article/details/25806151)
- [CentOS6安装openssl-1.1.1版本可能遇到的问题及解决](https://blog.csdn.net/yxy369/article/details/104517168)





