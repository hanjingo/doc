# openssl环境搭建

[TOC]



## 1 编译安装

### 1.1 环境要求

| 操作系统 | 环境                                    | 版本要求（最低）                     |
| -------- | --------------------------------------- | ------------------------------------ |
| Window   | VisualStudio<br>Perl<br>nasm<br>openssl | 2015<br>5.32.1.1<br>2.15.05<br>1.1.1 |
| linux    | gcc<br>openssl                          | 7.1<br>1.1.1                         |
| macos    |                                         |                                      |

### 1.2 配置环境

拉取项目：

```sh
git clone git@github.com:openssl/openssl.git

# 切换分支
git checkout OpenSSL_1_1_1

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

windows下打开 "VS2015 开发人员命令提示（32位系统）" 或 "VS2015 x64 x86 兼容工具命令提示符"（64位系统），进入到openssl代码目录，执行Configure命令：

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

- `[no-]shared` 编译动态/静态库

  - no-shared 静态库
  - shared 动态库

- `[no-]zlib|zlib-dynamic`

- `no-asm`

- `no-dso`

- `no-egd`

- `sctp`

- `386`

- `--prefix` 编译完成后的安装路径

- `--openssldir` 编译完后的生成的配置文件的安装路径

- `os/compiler[:flags]` 目标平台

  主要的windows目标平台有以下几种：

  - `VC-WIN64A` 适用于amd x64处理器Release版。
  - `debug-VC-WIN64A` 适用于amd x64处理器Release版。
  - `VC-WIN64I` 适用于intel x64处理器Release版。
  - `VC-WIN64-ARM` 适用于arm 64处理器Release版。
  - `VC-WIN32` 适用于x86架构处理器Release版。
  - ...

  主要的linux目标平台：

  TODO

  主要的macos目标平台：

  TODO

例1，编译window 下32位程序：

```c++
perl Configure VC-WIN32 --prefix=C:\Program Files\openssl\bin --openssldir=C:\Program Files\openssl\config
```

例2，让安装程序自动选择合适的平台：

```sh
perl Configure --prefix=C:\Program Files\openssl\bin --openssldir=C:\Program Files\openssl\config
```

例3，编译ubuntu18.04下64位程序：

```sh
./configure linux-x86_64 --prefix=/usr/local/ssl
```

#### 1.3.2 编译

- Window

  用VC自带的构建程序构建一遍：

  ```sh
  ms\do_nasm
  ```

  切换到VC目录`...\Microsoft Visual Studio x\VC\bin`并执行脚本：

  ```sh
  vcvars32.bat
  ```

  再切回openssl目录，使用nmake进行编译：

  ```sh
  # 生成动态库
  nmake -f ms\ntdll.mak
  
  # 生成静态库
  nmake -f ms\nt.mak
  ```

  编译完成之后，测试是否编译成功：

  ```sh
  # 动态库
  nmake -f ms\ntdll.mak test
  
  # 静态库
  nmake -f ms\nt.mak test
  ```

  显示：`passed all tests`则表示编译成功。

  编译安装：

  ```sh
  # 动态库
  nmake -f ms\ntdll.mak install
  
  # 静态库
  nmake -f ms\nt.mak 
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
  echo "/usr/local/ssl/lib" >> /etc/ld.so.conf.d/
  sudo ldconfig -v
  echo ":/usr/local/ssl/bin" >> /etc/environment
  source /etc/environment
  
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

  1. 以前执行过Configure程序；

  **解决**

  1. 在Configure命令中加入`no-asm`：

     ```sh
     perl Configure no-asm VC-WIN32 --prefix=C:\Program Files\openssl\bin --openssldir=C:\Program Files\openssl\config
     ```

     

     



## 2 项目引用

### 2.1 Visual Studio

TODO



## 参考

- [OpenSSL 中文手册](https://www.openssl.net.cn/)
- [Windows 下编译 OpenSSL](https://blog.csdn.net/liang19890820/article/details/51658574)
- [ActivePerl、dmake、nasm、nmake编译OpenSSL(1.1.0系列)](https://blog.csdn.net/ayang1986/article/details/77917297?locationNum=5&fps=1)
- [nmake下一些错误的解决办法](https://blog.csdn.net/hongqiang200/article/details/39210767)
- [VS2015编译Openssl-1.1.0f](https://blog.csdn.net/ljttianqin/article/details/72978612)
- [Windows下openssl的下载安装和使用](https://blog.csdn.net/houjixin/article/details/25806151)
- [CentOS6安装openssl-1.1.1版本可能遇到的问题及解决](https://blog.csdn.net/yxy369/article/details/104517168)





