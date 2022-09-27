# cmake

[TOC]

## 基础

### 行为准则

1. 不要使用具有全局作用域的函数；如：`link_directories`, `include_libraries`等；
2. 不要添加非必要的PUBLIC要求；
3. 不要在file函数中添加GLOB文件；
4. 将库直接链接到需要构建的目标上；如果可以的话，总是显式地将库链接到目标上；
5. 当链接库文件时，不要省略PUBLIC或PRIVATE关键字；这将导致后续所有的链接都是缺省的。
6. 指令是大小写无关的，参数和变量时大小写相关的，**推荐变量使用大写指令，函数和宏使用小写**。

### 基本原理

1. 变量使用`${}`方式取值，但是在IF控制语句中是直接使用变量名；
2. 指令格式 `指令(参数1 参数2 ...)`；
4. make不支持make distclean；
5. 在CMake中，C++是默认的编程语言；如果要编译其他语言，使用`LANGUAGES`选项显式声明；
6. 使用cmake命令时，通过`-D`选项设置选项选项，通过`-G`;
7. 字符串比较使用`EQUAL`来进行。

### 条件控制

```cmake
if (PARAM)
    ...
else()
    ...
endif()
```

- 开 1/ON/YES/true/Y/非零数值
- 关 0/OFF/NO/false/N/IGNORE/NOTFOUND/空字符串/xxx-NOTFOUND

使用IF进行条件控制。

```cmake
set(ok 0)
set(ok OFF)
set(ok NO)
set(ok false)
set(ok N)
set(ok IGNORE)
set(ok NOTFOUND)
set(ok "")
set(ok xxx-NOTFOUND)

if (ok)
    message("do ok")
else()
    message("do fail")
endif()
```

### 项目结构

- `Makefile` make将运行指令来构建项目；
- `CMakefile` 包含临时文件的目录，CMake用于检测操作系统，编译器等；
- `cmake_install.cmake` 处理安装规则的CMake脚本，在项目安装时使用；
- `CMakeCache.txt` CMake缓存，在重新运行配置时使用这个文件。




## 函数

### ADD_CUSTOM_COMMAND

```cmake
add_custom_command(OUTPUT output1 [output2 ...]
                   COMMAND command1 [ARGS] [args1...]
                   [COMMAND command2 [ARGS] [args2...] ...]
                   [MAIN_DEPENDENCY depend]
                   [DEPENDS [depends...]]
                   [BYPRODUCTS [files...]]
                   [IMPLICIT_DEPENDS <lang1> depend1
                                    [<lang2> depend2] ...]
                   [WORKING_DIRECTORY dir]
                   [COMMENT comment]
                   [DEPFILE depfile]
                   [JOB_POOL job_pool]
                   [VERBATIM] [APPEND] [USES_TERMINAL]
                   [COMMAND_EXPAND_LISTS])
```

执行命令。

```cmake
add_custom_command(
    Setup ALL hello.exe /V1 hello.nsi
    COMMENT begin building...
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)
```

### ADD_EXECUTABLE

生成可执行文件。

```cmake
add_executable(hello 
    main.c
)
```

### ADD_LIBRARY

`add_library(TARGETS [STATIC|SHARED] ...)`

- STATIC 静态库；
- SHARED 动态库；
- OBJECT 目标文件；
- MODULE DSO组(用于动态加载，构建运行时插件；不链接到项目中的任何目标)；
- IMPORTED 不可变库（用于对现有依赖项进行构建）；
- INTERFACE 可变库（用于项目之外的目标构建使用）；
- ALIAS 别名（用于为项目中已存在的库目标定义别名）。

从源文件创建库（动态/静态/目标文件/...）。

```cmake
add_library(hello
    STATIC
        hello.h
        hello.cpp
)
```

### ADD_LINK_LIBRARY

在链接时将依赖文件(lib)与可执行文件(exe)链接起来。

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

### CMAKE_DEPENDENT_OPTION

定义依赖于其他选项的选项。

```cmake
cmake_dependent_option(
    MAKE_STATIC_LIBRARY "compile static library" OFF # OFF依赖于USE_LIBRARY=ON
    "USE_LIBRARY" ON
)
```

```sh
cmake -DUSE_LIBRARY=ON .. # MAKE_STATIC_LIBRARY=OFF
```


### CMAKE_MINIMUM_REQUIRE

CMake最小版本要求。

```cmake
cmake_minimum_required()

cmake_minimum_required(VERSION 3.24.1)
```

### CONFIGURE_FILE

配置文件通过源码版本检查。

```cmake
configure_file(hello.h.in hello.h)
```

### EXECUTE_PROCESS

执行一条命令，并获得它的执行结果。

```cmake
find_package(GIT QUIET)

if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
    execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                    RESULT_VARIABLE GIT_SUBMOD_RESULT)
    if(NOT GIT_SUBMOD_RESULT EQUAL "0")
        message(FATAL_ERROR "git submodule update --init --recursive failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
    endif()
endif()
```

### FIND_PACKAGE

- TODO 库名称；
- TODO 库得最低版本；
- REQUIRED 告诉模块是必须的（如果失败，则找不到该模块）；
- COMPONENTS 要查找的库列表。

从`CMAKE_MODULE_PATH`中的文件夹列表中搜索格式为`Findxxx.cmake`的CMAKE模块。

```cmake
find_package(Boost 1.80.0 REQUIRED COMPONENTS filesystem system)
```

### FOREACH

遍历列表，一共4种使用方式：

- 使用`foreach(loop_var arg1 arg2 ...)`提供循环变量和显式项列表（如果项目列表位于变量中，则必须显式展开它，即`${sources_with_lower_optimization}`必须作为参数传递）。
- 通过指定一个范围，对整数进行循环
    ```cmake
    foreach(loop_var range total)

    foreach(loop_var range start stop [step])
    ```
- 对列表值变量的循环
    ```cmake
    foreach(loop_var IN LISTS [list1[...]])
    ```
- 对变量的循环
    ```cmake
    foreach(loop_var IN ITEMS [item1 [...]])
    ```

```cmake
list(
    APPEND hello_src
        hello.c
        hello_main.c
)

foreach(f IN LISTS hello_src)
    ...
endforeach()
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

### LIST

合成文件列表。

```cmake
list(
    APPEND hello_src
        hello.c
        hello_main.c
)
```

### MESSAGE

`MESSAGE([SEND_ERROR | STATUS | FATAL_ERROR] "message to display" ...)` 

- `SEND_ERROR` 产生错误，产生过程被跳过；
- `STATUS` 输出前缀为一的信息；
- `FATAL_ERROR` 立即终止所有cmake过程；

向终端输出信息。

### OPTION

`OPTION(<NAME> "MESSAGE" [VALUE])`

- `NAME` 选项的变量名；
- `MESSAGE` 选项的说明；
- `VALUE` 选项的默认值（ON/OFF）。

用于接受命令行传入的参数。

```cmake
option(hello "hello world" ON)
```

### PROJECT 

`PROJECT(target_name LANGUAGES language)`

- `LANGUAGES` 编程语言（默认C++）。

声明工程名。

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

设置[变量值](#变量 )。

```cmake
SET(SRC_LIST main.c t1.c t2.c)
```

### SET_TARGET_PROPERTIES

为生成目标设置属性。

```cmake
set_target_properties(hello
    PROPERTIES
        CXX_STANARD 14              # 使用c++14标准
        CXX_EXTENSIONS ON           # 启用ISO C++标准的编译器标志，不实用特定编译起的扩展
        CXX_STANDARD_REQUIRED ON    # 指定所选标准的版本，如果不可用，cmake将停止配置
        POSITION_INDEPENDENT_CODE 1 # 
)
```

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

### TARGET_COMPILE_OPTIONS

设置编译选项。

```c++
target_compile_options(hello PRIVATE ${hello_flags})
```

### TARGET_LINK_LIBRARIES

`TARGET_LINK_LIBRARIES[TARGETS SOURCE]` 

- `TARGETS` 要链接到的可执行目标；
- `SOURCE` 目标库。

将目标库链接到可执行目标。

```cmake
target_link_libraries(hello hello_lib)
```

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

- `UNIX`
- `WIN32`
- `MINGW`
- `APPLE`

### 编译变量

- `MSVC`

### 环境变量

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

### 外部标志

- `CMAKE_BUILD_TYPE` [构建类型](#构建类型)
- `CMAKE_C_FLAGS` c编译器标志；
- `CMAKE_CXX_COMPILER` 指定使用哪个c++编译器
    + `clang++` 使用clang；
- `CMAKE_CXX_FLAGS` c++编译器标志
    + `-std` 编译器版本；
- `CMAKE_CXX_STANDARD` c++标准库标志（从v3.1开始提供）；
- `CMAKE_LINKER_FLAGS` 链接器标志；

```cmake
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DEX2" CACHE STRING "Set C++ Compiler Flags" FORCE)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11") # 使用c++11版本

set(CMAKE_CXX_STANDARD 11) # 使用c++11标准库
```

```sh
cmake -DCMAKE_CXX_COMPILER=clang++ .. # 使用clang编译
```

### 编译器选项

TOD

### 从命令行传入参数

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



## 依赖处理

### 编译库引入
TODO

### FetchContent

CMake从3.11开始提供`FetchContent`模块，用于解决模块依赖问题。

`FetchContent_Declare()` 用于从URL，Git仓库等地方获取数据或者是软件包。

`FetchContent_GetProperties()` 用于获取软件包的信息。

`xxx_POPULATED` 用于判断变量是否被导出（内容被填充）。

`ExternalProject_Add()`用于在在构建时进行下载操作；使得构建可以立即进行，获取的主要项目和外部项目仅在第一次执行CMake时调用。

`ExternalProject_Add`提供以下选项，用于外部项目的配置和编译：

- Directory 用于调优源码的结构，并为外部项目构建目录。
- Download 外部项目的代码可能需要从在线存储库或资源处下载。
- Update和Patch 用于定义如何更新外部项目的源代码或如何应用布丁。
- Configure 如果外部项目是CMake项目，`ExternalProject_Add`将调用CMake可执行文件，并传递选项。
- Build 用于调整外部项目的实际编译。
- Install 用于配置应该如何安装外部项目。
- Test 为基于源代码构建的软件运行测试。
- URL 用来指定压缩包的HTTP地址。
- GIT_REPOSITORY 用来指定包含依赖项源的存储库的Git地址。
- GIT_TAG 检出的存储库分支。
- SVN_REPOSITORY 用来指定包含依赖项源的存储库的SVN地址。
- HG_REPOSITORY 用来指定包含依赖项源的存储库的Mercurial地址。
- TEST_AFTER_INSTALL 在安装步骤之后立即运行测试。
- TEST_BEFORE_INSTALL 在安装步骤之前运行测试套件。
- TEST_EXCLUDE_FROM_MAIN 从测试套件中删除对外部项目的主要目标的依赖。

```cmake
include(FetchContent) # 引入FetchContent模块

FetchContent_Declare( # 声明外部内容
    hello
    GIT_REPOSITORY https://github.com/hanjingo/doc.git
    GIT_TAG main
)

# CMake 3.14+
FetchContent_MakeAvailable(hello)

# CMake 3.14-
FetchContent_GetProperties(hello) # 查询内容是否已经被填充/获取
if(NOT hello_POPULATED)           # 内容没有填充
    FetchContent_Populate(hello)  # 获取内容

    add_subdirectory( # 配置子项目
        ${hello_SOURCE_DIR}
        ${hello_BINARY_DIR}
    )
endif()
```

### CPM
TODO

### git submodule
TODO




## 编译构建

### 编译过程

- 内部编译
    
    1. TODO

- 外部编译
    
    1. 在目录中清除所有非CmakeLists.txt的中间文件，如：CMakeCache.txt等。
    2. 在目录中建立build文件夹。
    3. 进入build文件夹，执行命令`cmake ..`。
    4. 执行命令`make`，构建工程。

### 构建类型

`CMAKE_BUILD_TYPE`构建类型：

+ Debug: 用于在没有优化的情况下，使用带调试符号构建库或可执行文件；
+ Release: 用于构建的优化的库或可执行文件，不包含调试符号；
+ RelWithDebInfo: 用于构建较少的优化库或可执行文件，包含调试符号；
+ MinSizeRel: 用于不增加目标代码大小的优化方式，来构建库或可执行文件。

```cmake
set(CMAKE_BUILD_TYPE Release CACHE STRING "Build Type" FORCE)
```

### 构建规则

`cmake --build . --target <target-name>`

- `target`

    - `all` 在项目中构建所有目标（默认，在Visual Studio generator中为ALL_BUILD）;
    - `clean` 删除所有生成的文件；
    - `rebuild_cache` 将调用CMake为源文件生成依赖；
    - `edit_cache` 允许直接编辑缓存。
    - `test`
    - `install`
    - `package`

构建项目。

```cmake
TODO
```

### 交叉编译
TODO

### 打包

#### 集成NSIS

TODO



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

### 变量

通过以下**boost信息变量**来获取Boost的信息：
- Boost_FOUND：是否找到了所需的库；
- Boost_INCLUDE_DIRS：boost头文件搜索路径；
- Boost_LIBRARY_DIRS：boost库的链接路径；
- Boost_LIBRARIES：boost库名，用于链接到目标程序；
- Boost_VERSION：从boost/version.hpp文件获取的版本号；
- Boost_LIB_VERSION：某个子库的版本。

通过以下**boost选项**来控制相关行为：
- Boost_USE_STATIC_LIBS
- Boost_USE_MULTITHREADED
- Boost_USE_STATIC_RUNTIME

通过设置以下**系统环境变量**来帮助boost的的查找：
- BOOST_ROOT：首选的Boost安装路径；
- BOOST_INCLUDEDIR：首选的头文件搜索路径；
- BOOST_LIBRARYDIR：首选的库文件搜索路径。

### 单元测试

要使用Boost的单元测试，需要执行一下步骤：

1. 添加boost组件`unit_test_framework`；
2. 添加链接依赖`Boost::unit_test_framework`；
3. 定义编译选项`BOOST_TEST_DYN_LINK`；
4. 定义单元测试。

```cmake
find_package(Boost 1.80 REQUIRED COMPONENTS unit_test_framework)

target_link_libraries(hello
    PRIVATE
        Boost::unit_test_framework
)

target_compile_definitions(hello
    PRIVATE
        BOOST_TEST_DYN_LINK
)

enable_testing()
add_test(
    NAME boost_test
    COMMAND $<TARGET_FILE:hello>
)
```

```c++
#define BOOST_TEST_MODULE xxx
#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(xxx)
BOOST_AUTO_TEST_CASE(xx)
{
    BOOST_CHECK(...)
}
BOOST_AUTO_TEST_SUITE_END()
```



## 集成git

TODO


## 集成Visual Studio

### 构建VS项目

microsoft在VS2017开始支持CMake，因此构建不同版本的VS项目，需要使用不同的方法：

- VS2017及以上

    1. TODO

- VS2017以下

    1. TODO



## 集成Qt

### 变量

普通变量：
- CMAKE_AUTOMOC：是否处理.moc文件；
- CMAKE_AUTORCC：是否处理.qrc文件（资源文件）；
- CMAKE_AUTOUIC：是否处理.ui文件（界面文件）；
- CMAKE_INCLUDE_CURRENT_DIR：moc文件查找目录。

模块变量：
- Qt5Widgets_COMPILE_DEFINITIONS：编译选项；
- Qt5Widgets_DEFINITIONS：依赖选项；
- Qt5Widgets_EXECUTABLE_COMPILE_FLAGS：执行选项；
- Qt5Widgets_FOUND：是否发现了Widgets模块；
- Qt5Widgets_INCLUDE_DIRS：Qt widgets目录（QtCore和QtGui需要依赖此目录）；
- Qt5Widgets_LIBRARIES：Qt widgets依赖目录；
- QtWidgets_PRIVATE_INCLUDE_DIRS：Qt Widgets私有目录；
- QtWidgets_VERSION_STRING：模块版本；
- Qt5Declarative_INCLUDE_DIRS：Qt Declarative目录 ；
- Qt5Declarative_LIBRARIES：Qt Declarative依赖目录。

安装变量：
- QT_DEFAULT_MAJOR_VERSIO：默认的主版本（Qt5/Qt6）；
- QT_LIBINFIX：依赖的中缀名；
- QT_NO_CREATE_VERSIONLESS_FUNCTIONS：解决函数带版本的兼容性问题(从Qt5.15开始，qt函数不带版本，如`qt5_`变为`qt_`)；
- QT_NO_CREATE_VERSIONLESS_TARGETS：解决模块带版本的兼容性问题（从Qt5.15开始，qt模块不带版本，如`Qt5::`变为`Qt::`）；
- QT_VISIBILITY_AVAILABLE：是否导出符号。

### 函数

Qt5::Core：
- qt5/qt_add_big_resources 添加大资源文件
- qt5/qt_add_binary_resources 从qt资源文件创建RCC文件
- qt5/qt_add_resources 添加二进制资源文件
- qt5/qt_generate_moc 调用输入的.moc文件
- qt5/qt_import_plugins 添加qt静态插件
- qt5/qt_wrap_cpp 从源码创建.moc文件

Qt5::DBus
- qt_add_dbus_adaptor
- qt_add_dbus_interface
- qt_add_dbus_interfaces
- qt_generate_dbus_interface

Qt5::LinguistTools
- qt5_add_translation 编译`Linguist.ts`文件到`.qm`文件
- qt5_create_translation 设置轻量级的翻译工具

Qt5::RemoteObjects
- qt5_generate_repc 从qt远程对象.rep文件创建c++类

Qt5::Widgets
- qt5/qt_wrap_ui 从.ui文件创建源码

### 命令

- `-debug`

    等价于：
    ```cmake
    set_target_properties(Qt5::Core PROPERTIES MAP_IMPORTED_CONFIG_COVERAGE "DEBUG")
    ```
- `-release`

    等价于：
    ```cmake
    set_target_properties(Qt5::Core PROPERTIES MAP_IMPORTED_CONFIG_COVERAGE "RELEASE")
    ```
- `-debug-and-release`

### 示例

```cmake
cmake_minimum_required(2.8.8)
project(hello)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_definitions(${Qt5Widgets_DEFINITIONS}) # -DQT_WIDGETS_LIB

# cmake2.8.8开始支持，等价于在.pro中：
#   TARGET = hello
#   QT += widgets declarative
qt5_use_modules(hello Widgets Declarative)

add_executable(${PROJECT_NAME} 
    hello.h 
    hello.cpp 
    hello.qrc 
    hello.qml
    hello.ui
)

target_link_libraries(hello Qt5::Widgets)
```



## 集成Zeromq

TODO



## 参考

[1] [CMake Tutorial](https://cmake.org/cmake/help/latest/guide/tutorial/index.html)

[2] Eric Noulard, Roberto Di Remigio.CMake-Cookbook

[3] [Modern CMake 简体中文版](https://github.com/Modern-CMake-CN/Modern-CMake-zh_CN)

[4] [An Introduction to Modern CMake](https://cliutils.gitlab.io/modern-cmake/)

[5] [CMake基础教程](https://www.cnblogs.com/juzaizai/category/1993745.html)

[6] [Linux下使用CMake进行编译的时候寻找Boost库](https://www.jianshu.com/p/1827cd86d576)

[7] [Using CMake with Qt 5](https://www.kdab.com/using-cmake-with-qt-5/)

[8] [Build with CMake](https://doc.qt.io/qt-5/cmake-manual.html)
