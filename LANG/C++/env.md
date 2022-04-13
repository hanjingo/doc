# C++环境配置

[TOC]

## ubuntu/debain

### 依赖包
```sh
sudo apt-get install -y make bzip2 automake libbz2-dev libssl-dev doxygen graphviz libgmp3-dev \
    autotools-dev libicu-dev python2.7 python2.7-dev python3 python3-dev \
    autoconf libtool curl zlib1g-dev sudo ruby libusb-1.0-0-dev \
    libcurl4-gnutls-dev pkg-config patch llvm-7-dev clang-7 vim-common jq
```

### clang

#### clang10

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
#### clang11

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

### cmake

#### cmake-3.19.2

```sh
wget https://github.com/Kitware/CMake/releases/download/v3.19.2/cmake-3.19.2-Linux-x86_64.sh
sudo bash cmake-3.19.2-Linux-x86_64.sh --prefix=/usr/local --include-subdir --skip-license
CMAKE_DIR="/usr/local/cmake-3.19.2-Linux-x86_64"
export PATH=${CMAKE_DIR}/bin:$PATH
cmake --version
echo -e '\nCMAKE_DIR="/usr/local/cmake-3.19.2-Linux-x86_64"\nexport PATH=${CMAKE_DIR}/bin:$PATH' >> ~/.bashrc
```

### boost

#### boost_1_75_0

```sh
export BOOST_ROOT="/usr/local/boost-1.75"
echo -e '\nexport BOOST_ROOT="/usr/local/boost-1.75"' >> ~/.bashrc
sudo mkdir -p ${BOOST_ROOT}
mkdir -p ~/tmp
cd ~/tmp
wget -c https://dl.bintray.com/boostorg/release/1.75.0/source/boost_1_75_0.tar.bz2
tar -xjf boost_1_75_0.tar.bz2
cd boost_1_75_0
./bootstrap.sh --with-toolset=clang --prefix=${BOOST_ROOT} 
sudo ./b2 toolset=clang --without-graph_parallel --without-mpi -q -j $(nproc) install
```



### QT

#### 通过二进制安装

1. 去网址`https://www.qt.io/download-qt-installer?hsCtaTracking=99d9dd4f-5681-48d2-b096-470725510d34%7C074ddad0-fdef-4e53-8aa8-5e8a876d6ab4`下载在线安装程序
2. 点击安装

#### 编译安装

设置编译环境：

- Macos

  ```sh
  brew install pcre2 harfbuzz freetype cmake ninja python llvm
  ```

- Ubuntu/Debain

  ```sh
  TODO
  ```

编译并设置Qt环境：

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

     - Macos（Arm架构）

       ```sh
       ./configure -release -prefix /Users/he/qt/5.15.2 -nomake examples -nomake tests QMAKE_APPLE_DEVICE_ARCHS=arm64 -opensource -confirm-license -skip qt3d -skip qtwebengine -skip virtualkeyboard # 安装到/Users/he/qt/5.15.2，根据实际情况设置
       
       make -j 8 # 这里8指CPU核心，根据机器的实际情况设置
       
       sudo make install
       ```

   - Qt6

     - Macos（Arm架构）

   configure参数说明:

   | 参数                     | 说明               |
   | ------------------------ | ------------------ |
   | release                  | 编译release版本    |
   | prefix                   | 指定安装位置       |
   | nomake                   | 编译时跳过某些项目 |
   | QMAKE_APPLE_DEVICE_ARCHS | 指定CPU架构        |
   | opensource               | 指定linces         |
   | skip                     | 编译时跳过某些模块 |

​		**注意：configure默认安装所有的插件，有些插件在Arm下不支持，需要根据实际情况删减！**

3. 设置环境

   - zsh

     ```sh
     export "export QT_BIN=\"/Users/he/Qt/6.2.1/bin\"" >> ~/.zshrc # 指向Qt安装位置，根据实际情况设置
     export "export PATH = $QT_BIN:$PATH" >> ~/.zshrc
     source ~/.zshrc
     ```

#### 安装QtCreator

1. 拉取源码
   - 通过git下载
   - 通过http下载
2. 编译
   - Qt5
   - Qt6

#### 报错解决

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



## 参考

- [Qt Documentation/Qt WebEngine Platform Notes](https://doc.qt.io/qt-5/qtwebengine-platform-notes.html)
- [QtPDF Build Instructions](https://wiki.qt.io/QtPDF_Build_Instructions)
