# cmake

[TOC]



## 函数

### ADD_EXECUTABLE

TODO

```cmake
add_executable(hello 
    main.c
)
```

### ADD_LIBRARY

`add_library(TARGETS [STATIC|SHARED] ...)`

- STATIC 静态库
- SHARED 共享库

从源文件创建库（动态/静态）

### ADD_LINK_LIBRARY

在链接时将依赖文件与可执行文件链接起来。

```cmake
target_link_libraries(hello
    PRIVATE
        hello_lib
)
```

### ADD_SUBDIRECTORY

`ADD_SUBDIRECTORY(source_dir [binary_dir] [EXCLUDE_FROM_ALL])` 

- `source_dir` 在源文件的子目录；
- `binary_dir` 编译输出（包含编译中间结果）路径；
- `EXCLUDE_FROM_ALL` 将这个目录从编译过程中排除；

向当前工程中添加存放源文件的子目录，并可以指定中间二进制和目标二进制存放的位置。

```cmake
ADD_SUBDIRECTORY(sub_dir)
```

### AUX_SOURCE_DIRECTORY 

搜集所有在指定路径下的源文件的文件名，将输出结果列表储存在指定的变量中。


### CMAKE_MINIMUM_REQUIRE

CMake最小版本要求。

```cmake
cmake_minimum_required(3.24.1)
```

### CONFIGURE_FILE

进行变量替换。

### FIND_PACKAGE

- TODO 库名称；
- TODO 库得最低版本；
- REQUIRED 告诉模块是必须的（如果失败，则找不到该模块）；
- COMPONENTS 要查找的库列表。

从`CMAKE_MODULE_PATH`中的文件夹列表中搜索格式为`Findxxx.cmake`的CMAKE模块。

```cmake
find_package(Boost 1.80.0 REQUIRED COMPONENTS filesystem system)
```

### INSTALL

`INSTALL(TARGETS targets ... [[ARCHIVE|LIBRARY|RUNTIME]] [DESTINATION <dir>] [PERMISSIONS permissions ...] [CONFIGURATIONS [Debug|Release|...]] [COMPONENT <component>] [OPTIONAL]])` 

- `PERMISSIONS`
- `OWNER_EXECUTE`
- `OWNER_WRITE`
- `OWNEr_READ`
- `GROUP_EXECUTE`
- `GROUP_READ`
- `CMAKE_INSTALL_PREFIX` 安装位置
- TODO

定义安装规则。

```cmake
INSTALL(TARGETS myrun mylib mystaticlib 
        RUNTIME DESTINATION bin       # 可执行程序myrun安装到${CMAKE_INSTALL_PREFIX}/bin
        LIBRARY DESTINATION lib       # 动态库libmylib安装到${CMAKE_INSTALL_PREFIX}/lib
        ARCHIVE DESTINATION libstatic # 静态库libmystaticlib安装到${CMAKE_INSTALL_PREFIX}/libstatic
)
```

### MESSAGE

`MESSAGE([SEND_ERROR | STATUS | FATAL_ERROR] "message to display" ...)` 

- `SEND_ERROR` 产生错误，产生过程被跳过；
- `STATUS` 输出前缀为一的信息；
- `FATAL_ERROR` 立即终止所有cmake过程；

向终端输出信息。

### PROJECT 

```cmake
project(HELLO)
```

指定项目名。

### PROJECT_BINARY_DIR

TODO

### PROJECT_SOURCE_DIR

TODO

### SET

`SET(VAR [VALUE] [CACHE TYPE DOCSTRING [FORCE]])`

```cmake
SET(SRC_LIST main.c t1.c t2.c)
```

设置变量值。
   
### SUBDIRS

`SUBDIRS(dir1 dir2 ...)` 

一次添加多个子目录（不推荐使用）。

### TARGET_COMPILE_DEFINITIONS

根据作用域将目标的编译标志传递到其他目标。

```cmake
target_compile_definitions(hello_flags
    PRIVATE EX3
)
```

### TARGET_COMPILE_FEATURES

设置C++标准。

```c++
target_compile_features(hello PUBLIC cxx_auto_type)
```

### TARGET_LINK_LIBRARIES

`TARGET_LINK_LIBRARIES[TARGETS SOURCE]` 

- `TARGETS` 要链接到的可执行目标；
- `SOURCE` 目标库。

将目标库链接到可执行目标。

### TARGET_INCLUDE_DIRECTORIES

- `PRIVATE` 将目录添加到此目标的include目录中；
- `INTERFACE` 将该目录添加到任何连接到此库的目标的include目录中（不包括自己）；
- `PUBLIC` 包含在此库中，也包含在链接此库的任何目标中。

添加头文件目录到编译器，在以下位置使用：

1. 在编译该库时；
2. 在编译链接至该库的任何其他目标时。

```cmake
target_include_directories(hello
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)
```

### TARGETS

生成的目标名。



## 变量

### 系统变量

- `CMAKE_BINARY_DIR` 二进制文件生成目录；
- `CMAKE_CURRENT_SOURCE_DIR` 当前源目录；
- `CMAKE_CURRENT_BINARY_DIR` 当前所在的生成目录；
- `CMAKE_PROJECT_NAME` 由`project()`命令设置的第一个项目（顶级项目）的名称；
- `CMAKE_SOURCE_DIR` 根源目录；
- `EXECUTABLE_OUTPUT_PATH` 可执行二进制文件的生成路径；
- `LIBRARY_OUTPUT_PATH` 共享库的生成路径；
- `PROJECT_SOURCE_DIR` 当前cmake项目的源目录；
- `PROJECT_BINARY_DIR` 当前项目的生成目录；
- `PROJECT_NAME` 项目名；
- `xxx_SOURCE_DIR` xxx项目的源目录；
- `xxx_BINARY_DIR` xxx项目的二进制目录。

### 编译标志

- `CMAKE_C_FLAGS` c编译器标志；
- `CMAKE_CXX_FLAGS` c++编译器标志；
    - `-std` 编译器版本；
- `CMAKE_CXX_STANDARD` c++标准库标志（从v3.1开始提供）；
- `CMAKE_LINKER_FLAGS` 链接器标志；

```cmake
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DEX2" CACHE STRING "Set C++ Compiler Flags" FORCE)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11") # 使用c++11版本

set(CMAKE_CXX_STANDARD 11) # 使用c++11标准库
```



## 基本语法

1. 变量使用`${}`方式取值，但是在IF控制语句中是直接使用变量名。
2. 指令格式 `指令(参数1 参数2 ...)`。
3. 指令是大小写无关的，参数和变量时大小写相关的，**推荐全部使用大些指令**。
4. make不支持make distclean。



## 静/动态链接库

TODO



## 编译步骤

### 内部编译过程

TODO

### 外部编译过程

1. 在目录中清除所有非CmakeLists.txt的中间文件，如：CMakeCache.txt等。
2. 在目录中建立build文件夹。
3. 进入build文件夹，执行命令`cmake ..`。
4. 执行命令`make`，构建工程。



## 从命令行传入参数

在CMakeLists.txt文件中定义一个option来接受命令行传入的参数,

然后把这个参数传给c++文件

```cmake
# 定义option
option(LOG_TABLE "select to use log table" OFF)

# 传给c++文件
if(LOG_TABLE)
   add_definitions(-DLOG_TABLE=on)
endif(LOG_TABLE)
```

命令行修改为

```cmake
cmake -DLOG_TABLE=ON ..
```



## 集成Protobuf

### 变量

- `PROTOBUF_FOUND` 是否安装了protobuf库；
- `PROTOBUF_INCLUDE_DIRS` protobuf库的头文件目录；
- `PROTOBUF_LIBRARIES` protobuf库依赖文件目录。

### 生成源代码

`PROTOBUF_GENERATE_CPP(SRCS HDRS *.proto)`

- `SRCS` 存储`.pb.cc`文件名称集合；
- `HDRS` 存储`.pb.h`文件名称集合；
- `*.proto` proto文件。

```cmake
if(PROTOBUF_FOUND) # 是否安装了protobuf
    ...    
endif()

PROTOBUF_GENERATE_CPP(hello hello  hello.proto)
```



## 集成Boost

TODO



## 集成git

TODO



## 打包deb文件
TODO



## 参考

[1] [CMake Tutorial](https://cmake.org/cmake/help/latest/guide/tutorial/index.html)

[2] Eric Noulard, Roberto Di Remigio.CMake-Cookbook

[3] [CMake基础教程](https://www.cnblogs.com/juzaizai/category/1993745.html)

