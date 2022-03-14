# cmake

[TOC]



## 关键字

- `ADD_EXECUTABLE` 。

    ```cmake
    ADD_EXECUTABLE(hello main.c)
    ```

- `ADD_LIBRARY(TARGETS [STATIC|SHARED] ...)` 生成必要的构建指令，将指定的源码编译到库中。

    - `TARGETS` 生成的目标名。
    
- `ADD_SUBDIRECTORY(source_dir [binary_dir] [EXCLUDE_FROM_ALL])` 向当前工程中添加存放源文件的子目录，并可以指定中间二进制和目标二进制存放的位置。

    - `source_dir` 在源文件的子目录；
    - `binary_dir` 编译输出（包含编译中间结果）路径；
    - `EXCLUDE_FROM_ALL` 将这个目录从编译过程中排除；

    ```cmake
    ADD_SUBDIRECTORY(src bin)
    ```

- `AUX_SOURCE_DIRECTORY` 搜集所有在指定路径下的源文件的文件名，将输出结果列表储存在指定的变量中。

- `CMAKE_MINIMUM_REQUIRE` 指定运行此配置文件所需的 CMake 的最低版本。

- `INSTALL(TARGETS targets ... [[ARCHIVE|LIBRARY|RUNTIME]] [DESTINATION <dir>] [PERMISSIONS permissions ...] [CONFIGURATIONS [Debug|Release|...]] [COMPONENT <component>] [OPTIONAL]])` 定义安装规则。

    ```cmake
    INSTALL(TARGETS myrun mylib mystaticlib 
        RUNTIME DESTINATION bin       # 可执行程序myrun安装到${CMAKE_INSTALL_PREFIX}/bin
        LIBRARY DESTINATION lib       # 动态库libmylib安装到${CMAKE_INSTALL_PREFIX}/lib
        ARCHIVE DESTINATION libstatic # 静态库libmystaticlib安装到${CMAKE_INSTALL_PREFIX}/libstatic
    )
    ```

    - `PERMISSIONS`
      - OWNER_EXECUTE
      - OWNER_WRITE
      - OWNEr_READ
      - GROUP_EXECUTE
      - GROUP_READ
    - TODO

- `MESSAGE([SEND_ERROR | STATUS | FATAL_ERROR] "message to display" ...)` 向终端输出信息。

    - `SEND_ERROR` 产生错误，产生过程被跳过；
    - `STATUS` 输出前缀为一的信息；
    - `FATAL_ERROR` 立即终止所有cmake过程；

- `PROJECT` 指定项目名。

    ```cmake
    PROJECT(HELLO)
    ```

- `PROJECT_BINARY_DIR`

- `PROJECT_SOURCE_DIR`

- `SET(VAR [VALUE] [CACHE TYPE DOCSTRING [FORCE]])` 设置变量值。

    ```cmake
    SET(SRC_LIST main.c t1.c t2.c)
    ```
    
- `SUBDIRS(dir1 dir2 ...)` 一次添加多个子目录（不推荐使用）。

- `TARGET_LINK_LIBRARIES[TARGETS SOURCE]` 将目标库链接到可执行目标。

    - `TARGETS` 要链接到的可执行目标；
    - `SOURCE` 目标库。



## 变量

- `EXECUTABLE_OUTPUT_PATH` 可执行二进制文件的生成路径；
- `LIBRARY_OUTPUT_PATH` 共享库的生成路径；
- `PROJECT_SOURCE_DIR`
- `PROJECT_BINARY_DIR`
- `CMAKE_INSTALL_PREFIX`



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



## 参考

[1] CMAKE教程

[2] Eric Noulard, Roberto Di Remigio.CMake-Cookbook

