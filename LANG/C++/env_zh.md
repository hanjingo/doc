# C++环境配置

<!-- vim-markdown-toc GFM -->

* [第三方库](#第三方库)
* [依赖环境](#依赖环境)
    - [ubuntu/debain](#ubuntudebain)
    - [macos](#macos)
    - [windows](#windows)
        + [vcpkg](#vcpkg)
* [GCC](#gcc)
    - [编译安装](#编译安装)
* [CMAKE](#cmake)
    - [脚本安装](#脚本安装)
    - [编译安装](#编译安装-1)
* [QT](#qt)
    - [二进制安装](#二进制安装)
    - [编译安装](#编译安装-2)
    - [报错解决](#报错解决)
* [QtCreator](#qtcreator)
    - [编译安装](#编译安装-3)
* [Clang](#clang)
    - [命令安装](#命令安装)
    - [编译安装](#编译安装-4)
* [Boost](#boost)
    - [Linux/Unix](#linuxunix)
    - [Windows](#windows-1)
* [folly](#folly)
    - [使用vcpkg](#使用vcpkg)
* [参考](#参考)

<!-- vim-markdown-toc -->



## 第三方库

| 组件             | boost | folly                          |
| ---------------- | ----- | ------------------------------ |
| 日志             |       |                                |
| 内存管理         |       | Arena.h<br>ThreadCachedArena.h |
| 线程管理         |       |                                |
| 线程安全数据结构 |       | AtomicHashMap                  |
| 压测工具         |       | Benchmark                      |
| 文件管理         |       |                                |



## 依赖环境

### ubuntu/debain

- 基本环境支持

  ```sh
  sudo apt-get install -y make bzip2 automake libbz2-dev libssl-dev doxygen graphviz libgmp3-dev \
      autotools-dev libicu-dev python2.7 python2.7-dev python3 python3-dev \
      autoconf libtool curl zlib1g-dev sudo ruby libusb-1.0-0-dev \
      libcurl4-gnutls-dev pkg-config patch llvm-7-dev clang-7 vim-common jq
  ```

### macos

- 基本环境支持

  ```sh
  xcode-select --install
  ```

- qt环境支持

  ```sh
  brew install pcre2 harfbuzz freetype cmake ninja python llvm
  ```

### windows

#### vcpkg

1. clone vcpkg项目

   ```sh
   git clone git@github.com:microsoft/vcpkg.git
   ```

2. 设置环境变量



## GCC

### 编译安装

```sh
./contrib/download_prerequisites
./configure --prefix=/usr/local/gcc  --enable-bootstrap  --enable-checking=release --enable-languages=c,c++ --disable-multilib
make -j 8
make install

# 配置环境
echo 'export PATH="/usr/local/gcc/bin:$PATH"\n' >> ~/.zshrc

# 库文件
echo "/usr/local/gcc/lib64" >> ~/.zshrc

# 配置头文件
ln -sv /usr/local/gcc/include/ /usr/include/gcc

# 确认版本
gcc -v
```



## CMAKE

### 脚本安装

```sh
wgets https://github.com/Kitware/CMake/releases/download/v3.19.2/cmake-3.19.2-Linux-x86_64.sh
sudo bash cmake-3.19.2-Linux-x86_64.sh --prefix=/usr/local --include-subdir --skip-license
CMAKE_DIR="/usr/local/cmake-3.19.2-Linux-x86_64"
export PATH=${CMAKE_DIR}/bin:$PATH
cmake --version
echo -e '\nCMAKE_DIR="/usr/local/cmake-3.19.2-Linux-x86_64"\nexport PATH=${CMAKE_DIR}/bin:$PATH' >> ~/.bashrc
```

### 编译安装

```sh
git clone git@github.com:hanjingo/CMake.git
./bootstrap --prefix=/usr/local/cmake
make
make install

# 设置环境
echo -e '\nCMAKE_DIR="/usr/local/cmake"\nexport PATH=${CMAKE_DIR}/bin:$PATH' >> ~/.bashrc

# 确认
cmake --version
```



## QT

### 二进制安装

1. 去网址`https://www.qt.io/download-qt-installer?hsCtaTracking=99d9dd4f-5681-48d2-b096-470725510d34%7C074ddad0-fdef-4e53-8aa8-5e8a876d6ab4`下载在线安装程序
2. 点击安装

### 编译安装

1. 拉取源码

   - 通过git下载

     ```sh
     git clone git://code.qt.io/qt/qt5.git
     cd qt5
     git checkout 5.15
     ```

   - 通过http下载（去到`https://download.qt.io/archive/qt/`选择自己想要的版本下载）

     ```sh
     wget https://download.qt.io/archive/qt/6.2/6.2.1/single/qt-everywhere-src-6.2.1.tar.xz
     tar -zxvf qt-everywhere-src-6.2.1.tar.xz
     cd qt-everywhere-src-6.2.1
     ```

2. 编译

   - Qt5

     Macos（Arm架构）：

     ```sh
     ./configure -release -prefix /Users/he/qt/5.15.2 -nomake examples -nomake tests QMAKE_APPLE_DEVICE_ARCHS=arm64 -opensource -confirm-license -skip qt3d -skip qtwebengine -skip virtualkeyboard # 安装到/Users/he/qt/5.15.2，根据实际情况设置
     
     make -j 8 # 这里8指CPU核心，根据机器的实际情况设置
     
     sudo make install
     ```

   - Qt6

     Macos（Arm架构）：
     
     TODO

   configure参数说明:
   
   | 参数                     | 说明                                                         |
   | ------------------------ | ------------------------------------------------------------ |
   | release                  | 编译release版本                                              |
   | prefix                   | 指定安装位置                                                 |
   | opensource               | 指定linces                                                   |
   | platform                 | 指定平台                                                     |
   | QMAKE_APPLE_DEVICE_ARCHS | 指定CPU架构                                                  |
   | no-sse2                  |                                                              |
   | no-penssl                |                                                              |
   | no-cups                  |                                                              |
   | no-glib                  |                                                              |
   | no-iconv                 |                                                              |
   | skip                     | 编译时跳过某些模块：<br>qtvirtualkeyboard <br>qt3d<br>qtcanvas3d<br>qtpurchasing |
   | nomake                   | 编译时跳过某些项目：<br>examples<br>tools                    |

​		**注意：configure默认安装所有的插件，有些插件在Arm下不支持，需要根据实际情况删减！**

3. 设置环境

   - zsh

     ```sh
     export "export QT_BIN=\"/Users/he/Qt/6.2.1/bin\"" >> ~/.zshrc # 指向Qt安装位置，根据实际情况设置
     export "export PATH = $QT_BIN:$PATH" >> ~/.zshrc
     source ~/.zshrc
     ```

### 报错解决

1. 模块`QtWebEngine`, `QtPdf`等无法被配置；

   **问题**

   ```sh
   Note: No wayland-egl support detected. Cross-toolkit compatibility disabled.
   
   Note: The following modules are not being compiled in this configuration:
       webenginecore
       webengine
       webenginewidgets
       pdf
       pdfwidgets
   
   WARNING: QtWebEngine requires at least version 10.0.0, but using Xcode version .
   
   WARNING: QtPdf requires at least version 10.0.0, but using Xcode version .
   
   WARNING: QtWebEngine will not be built.
   
   WARNING: QtPdf will not be built.
   ```

   **原因**

   1. 相关模块需要手动安装；

   **解决**

   ```sh
   TODO
   ```

1. clip2tri，clipper, poly2tri的依赖缺失

   **问题**

   ```sh
   qt library not found for -lqt_clip2tri
   ```

   **原因**

   1. 需要单独编译clip2tri，clipper, poly2tri

   **解决**

   ```sh
   cd ./qtlocation/src/3rdparty/clip2tri && make && cd -
   cd ./qtlocation/src/3rdparty/clipper && make && cd -
   cd ./qtlocation/src/3rdparty/poly2tri && make && cd -
   ```

1. lqmapboxgl依赖缺失

   **问题**

   ```sh
   ld: library not found for -lqmapboxgl
   
   clang: error: linker command failed with exit code 1 (use -v to see invocation)
   ```

   **原因**

   1. 需要单独编译lqmapboxgl

   **解决**

   ```sh
   cd ./qtlocation/src/3rdparty/mapbox-gl-native && make && cd -
   ```



## QtCreator

### 编译安装

1. 拉取源码
   
   ```sh
   TODO
   ```
2. 编译
   
   TODO



## Clang

### 命令安装

- Clang10

  ```sh
  # 安装clang10
  sudo apt-get install clang-10 libclang-10-dev llvm-10-dev libc++-10-dev libc++abi-10-dev clang-tidy clang-tidy-10
  # 注册版本，优先级是100
  sudo update-alternatives --install /usr/bin/clang clang /usr/bin/clang-10 100 --slave /usr/bin/clang++ clang++ /usr/bin/clang++-10
  # 检查版本号是否正确
  clang --version
  clang++ --version
  update-alternatives --display clang 
  # 如果其它版本的优先级更高，可以手工切换版本： sudo update-alternatives --config clang
  ```

- Clang11

  ```sh
  # 修改/etc/apt/sources.list添加源
  deb http://apt.llvm.org/bionic/ llvm-toolchain-bionic-11 main
  deb-src http://apt.llvm.org/bionic/ llvm-toolchain-bionic-11 main
  # 更新源
  wget -O - https://apt.llvm.org/llvm-snapshot.gpg.key|sudo apt-key add -
  sudo apt-get update
  sudo apt-get upgrade
  # 安装clang11
  sudo apt-get install clang-11 libclang-11-dev llvm-11-dev libc++-11-dev libc++abi-11-dev clang-tidy clang-tidy-11
  # 注册版本，优先级是110
  sudo update-alternatives --install /usr/bin/clang clang /usr/bin/clang-11 110 --slave /usr/bin/clang++ clang++ /usr/bin/clang++-11
  # 检查版本号是否正确
  clang --version
  clang++ --version
  update-alternatives --display clang 
  # 如果其它版本的优先级更高，可以手工切换版本： sudo update-alternatives --config clang
  ```

### 编译安装

```sh
TODO
```



## Boost

编译选项列表：

| 编译选项        | 说明                                                         |
| --------------- | ------------------------------------------------------------ |
| toolset         | 指定使用的编译工具：<br>`msvc-15.0` 使用vs2017<br>`msvc-14.0` 使用vs2015<br>`msvc-12.0` 使用vs2013<br>... |
| install         | 同时生成库文件和include文件（不推荐，很慢）                  |
| prefix          | 生成的库文件（静态/动态）和include文件存放路径               |
| stage           | 只生成库文件（推荐）                                         |
| stagedir        | 生成的库文件（静态/动态）存放路径（默认stage）               |
| builddir        | 中间文件（临时文件）存放路径                                 |
| link            | 生成动态/静态链接库：<br>`static` 静态链接<br>`shared` 动态链接 |
| runtime-link    | 使用动态/静态链接C++标准库：<br/>`static` 静态链接<br/>`shared` 动态链接 |
| build-type      | 是否编译所有库：<br>`minimal` 最小化<br>`complete` 编译所有库 |
| with            | 指定使用组件（组件信息请查看boost文档）                      |
| without         | 指定不使用组件（组件信息请查看boost文档）                    |
| show-libraries  | 显示需要编译的库名称（用于指定使用某些组件）                 |
| architecture    | CPU架构：<br>`x86` x86架构<br>`x64` x64架构<br>...           |
| address-model   | CPU位数（需要与architecture配合使用）：<br>`32` 32位寻址<br>`64` 64位寻址 |
| instruction-set | 指令集                                                       |
| threading       | 使用单线程/多线程：<br>`single` 单线程<br>`multi` 多线程     |
| variant         | 指定生成debug/release版本（默认两者都生成）<br>release<br>debug |

示例：

```sh
b2.exe stage --stagedir="../bins/lib" --with-log
```

### Linux/Unix

编译安装：

```sh
export BOOST_ROOT="/usr/local/boost-1.75"
echo -e '\nexport BOOST_ROOT="/usr/local/boost-1.75"' >> ~/.bashrc
sudo mkdir -p ${BOOST_ROOT}
mkdir -p ~/tmp
cd ~/tmp
wget -c https://dl.bintray.com/boostorg/release/1.75.0/source/boost_1_75_0.tar.bz2
tar -xjf boost_1_75_0.tar.bz2
cd boost_1_75_0
./bootstrap.sh --prefix=${BOOST_ROOT} 
sudo ./b2 --without-graph_parallel --without-mpi -q -j $(nproc) install
```

### Windows

编译安装：

1. 下载boost源码并解压。

2. 打开`VS2015开发人员命令提示`，执行`bootstrap.bat`，生成`b2.exe`/`bjam.exe`。

   ```sh
   bootstrap.bat
   ```

3. 执行`b2.exe`/`bjm.exe`执行编译。

   ```sh
   b2.exe stage --with-log
   ```

使用vcpkg：

TODO



## folly

### 使用vcpkg

- macos

  ```sh
  vcpkg install folly:x64-osx
  ```

- linux

  ```sh
  vcpkg install folly:x64-linux
  ```

- windows

  ```sh
  vcpkg install folly:x64-windows
  ```



## log4cplus

  ```sh
  cmake ../
  ```



## 参考

- [Qt Documentation/Qt WebEngine Platform Notes](https://doc.qt.io/qt-5/qtwebengine-platform-notes.html)
- [QtPDF Build Instructions](https://wiki.qt.io/QtPDF_Build_Instructions)
- [vcpkg](http://blog.fpliu.com/it/software/vcpkg)
- [folly](http://blog.fpliu.com/it/software/development/language/C++/library/folly)
- [github/facebook/folly/docs/Overview.md](https://github.com/facebook/folly/blob/main/folly/docs/Overview.md)
