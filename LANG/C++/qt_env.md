# Qt环境搭建

[TOC]



## 编译安装

### 设置编译环境

- Macos

  ```sh
  brew install pcre2 harfbuzz freetype cmake ninja python llvm
  ```

- Ubuntu/Debain

  ```sh
  TODO
  ```

### 安装Qt环境

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

### 安装QtCreator

1. 拉取源码
   - 通过git下载
   - 通过http下载
2. 编译
   - Qt5
   - Qt6



## 二进制安装

1. 去网址`https://www.qt.io/download-qt-installer?hsCtaTracking=99d9dd4f-5681-48d2-b096-470725510d34%7C074ddad0-fdef-4e53-8aa8-5e8a876d6ab4`下载在线安装程序
2. 点击安装



## 报错解决

1. 

```sh
qt library not found for -lqt_clip2tri
```

需要单独编译clip2tri，clipper, poly2tri

```sh
cd ./qtlocation/src/3rdparty/clip2tri && make && cd -
cd ./qtlocation/src/3rdparty/clipper && make && cd -
cd ./qtlocation/src/3rdparty/poly2tri && make && cd -
```

2. 

```sh
ld: library not found for -lqmapboxgl

clang: error: linker command failed with exit code 1 (use -v to see invocation)
```

需要单独编译lqmapboxgl

```sh
cd ./qtlocation/src/3rdparty/mapbox-gl-native && make && cd -
```