# cmake

<!-- vim-markdown-toc GFM -->

* [基础](#基础)
    - [行为准则](#行为准则)
    - [基本原理](#基本原理)
    - [条件控制](#条件控制)
        + [IF...ELSE...ENDIF](#ifelseendif)
        + [WHILE](#while)
        + [FOREACH](#foreach)
    - [项目结构](#项目结构)
* [函数](#函数)
    - [CMake函数](#cmake函数)
    - [自定义函数](#自定义函数)
        + [function](#function)
        + [隐式参数](#隐式参数)
* [变量](#变量)
    - [系统变量](#系统变量)
    - [编译变量](#编译变量)
    - [环境变量](#环境变量)
    - [外部标志](#外部标志)
    - [编译器选项](#编译器选项)
    - [从命令行传入参数](#从命令行传入参数)
    - [示例](#示例)
* [依赖处理](#依赖处理)
    - [编译库引入](#编译库引入)
    - [FetchContent](#fetchcontent)
    - [CPM](#cpm)
    - [git submodule](#git-submodule)
* [单元测试](#单元测试)
    - [CTest](#ctest)
    - [其它](#其它)
* [编译构建](#编译构建)
    - [编译过程](#编译过程)
    - [构建类型](#构建类型)
    - [构建规则](#构建规则)
    - [交叉编译](#交叉编译)
    - [打包](#打包)
        + [变量](#变量-1)
        + [工具](#工具)
        + [示例](#示例-1)
* [可移植性](#可移植性)
* [集成Protobuf](#集成protobuf)
    - [变量](#变量-2)
    - [生成源代码](#生成源代码)
* [集成Boost](#集成boost)
    - [变量](#变量-3)
    - [单元测试](#单元测试-1)
* [集成git](#集成git)
* [集成Visual Studio](#集成visual-studio)
    - [构建VS项目](#构建vs项目)
* [集成Qt](#集成qt)
    - [变量](#变量-4)
    - [函数](#函数-1)
    - [命令](#命令)
    - [示例](#示例-2)
* [集成Zeromq](#集成zeromq)
    - [变量](#变量-5)
    - [zmqpp](#zmqpp)
* [集成Valgrind](#集成valgrind)
* [参考](#参考)

<!-- vim-markdown-toc -->

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
2. 系统变量使用`ENV{变量名}`访问；
3. 指令格式 `指令(参数1 参数2 ...)`；
4. make不支持make distclean；
5. 在CMake中，C++是默认的编程语言；如果要编译其他语言，使用`LANGUAGES`选项显式声明；
6. 使用cmake命令时，通过`-D`选项设置选项选项，通过`-G`;
7. 字符串比较使用`EQUAL`来进行。

### 条件控制

#### IF...ELSE...ENDIF

```cmake
if(<condition>)
  <commands>
elseif(<condition>) 
  <commands>
else()
  <commands>
endif()
```

condition有以下几类：

- 基本表达式

    | condition                                                                      | 说明  |
    |--------------------------------------------------------------------------------|-------|
    | 1<br>ON<br>YES<br>true<br>Y<br>非零数值                                        | true  |
    | 0<br>OFF<br>NO<br>false<br>N<br>IGNORE<br>NOTFOUND<br>空字符串<br>xxx-NOTFOUND | false |

- 逻辑表达式

    | condition | 说明   |
    |-----------|--------|
    | NOT       | 非运算 |
    | AND       | 与运算 |
    | OR        | 或运算 |

- 扩充检查

    | condition     | 说明                                                                                                                                  |
    |---------------|---------------------------------------------------------------------------------------------------------------------------------------|
    | COMMAND       | 如果给定的名称是一个可以调用的命令、宏或函数,则为真                                                                                   |
    | POLICY        | 如果给定名称是现有策略（格式为 CMP<NNNN> ），则为True                                                                                 |
    | TARGET        | 如果给定名称是通过调用（在任何目录中） `add_executable()`，`add_library()`或`add_custom_target()`命令创建的现有逻辑目标名称，则为true |
    | TEST          | 如果给定名称是由 add_test() 命令创建的现有测试名称，则为true（3.3版新增）                                                             |
    | DEFINED<name> | 具有给定`<name>`的变量，则为true                                                                                                      |
    | CACHE{<name>} | 具有给定`<name>`的缓存变量，则为true                                                                                                  |
    | ENV{<name>}   | 具有给定`<name>`的环境变量 ，则为true                                                                                                 |
    | IN_LIST       | 如果给定的元素包含在命名的列表变量中,则为真(3.3版新增)                                                                                |

- 文件操作

    | condition     | 说明                                                   |
    |---------------|--------------------------------------------------------|
    | EXISTS        | 如果指定的文件或目录存在，则为True                     |
    | IS_NEWER_THAN | 如果 file1 比 file2 更新或两个文件之一不存在，则为true |
    | IS_DIRECTORY  | 如果给定的名称是一个目录,则为真                        |
    | IS_SYMLINK    | 如果给定的名称是一个符号链接,则为真                    |
    | IS_ABSOLUTE   | 如果给定的路径是一个绝对路径,则为真。                  |

    注意：
    1. 对于`IS_ABSOLUTE`有以下情况：
        + 空 path 评估为假。
        + 在 Windows 主机上，任何以驱动器号和冒号（例如 C: ）、正斜杠或反斜杠开头的 path 都将评估为真。这意味着像`C:no\base\dir`这样的路径将评估为真，即使路径的非驱动器部分是相对的。
        + 在非 Windows 主机上，任何以波浪号 ( ~ )开头的 path 计算结果为 true。

使用IF进行条件控制。

例：

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

#### WHILE

```cmake
while(<condition>)
  <commands>
endwhile()
```

当条件为真时，循环执行命令。

#### FOREACH

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

例：

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

### 项目结构

- `Makefile` make将运行指令来构建项目；
- `CMakefile` 包含临时文件的目录，CMake用于检测操作系统，编译器等；
- `cmake_install.cmake` 处理安装规则的CMake脚本，在项目安装时使用；
- `CMakeCache.txt` CMake缓存，在重新运行配置时使用这个文件。

---



## 函数

###  CMake函数

**ADD_COMPILE_DEFINITIONS**

TODO

**ADD_COMPILE_OPTIONS**

TODO

**ADD_CUSTOM_COMMAND**

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

例：

```cmake
add_custom_command(
    Setup ALL hello.exe /V1 hello.nsi
    COMMENT begin building...
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)
```

**ADD_CUSTOM_TARGET**

TODO

**ADD_DEFINITIONS**

```cmake
add_definitions(-DFOO -DBAR ...)
```

添加编译器命令行定义（由`-D`定义的标志）。

```cmake
add_definitions(-DABC -DHELLO)
```

```c++
#ifdef ABC
    ...
#endif

#ifdef HELLO
    ...
#endif
```

**ADD_DEPENDENCIES**

```cmake
add_dependencies(<target> [<target-dependency>]...)
```

- `target` 顶层目标；
- `target-dependency` 依赖关系。

在顶层目标之间增加一个依赖关系。

```cmake
add_subdirectory(lib1)

add_dependencies(hello lib1)
```

**ADD_EXECUTABLE**

```cmake
add_executable(<name> [WIN32] [MACOSX_BUNDLE]
               [EXCLUDE_FROM_ALL]
               [source1] [source2 ...]) 
```

生成可执行文件。

```cmake
add_executable(<name> IMPORTED [GLOBAL])
```
导入可执行文件。

```cmake
add_executable(<name> ALIAS <target>)
```
为可执行文件命别名。

例：

```cmake
add_executable(hello 
    main.c
)
```

**ADD_LIBRARY**

```cmake
add_library(<name> [STATIC | SHARED | MODULE]
            [EXCLUDE_FROM_ALL]
            [<source>...])
```

- STATIC 静态库；
- SHARED 动态库；
- OBJECT 目标文件；
- MODULE DSO组(用于动态加载，构建运行时插件；不链接到项目中的任何目标)；
- IMPORTED 不可变库（用于对现有依赖项进行构建）；
- INTERFACE 可变库（用于项目之外的目标构建使用）；
- ALIAS 别名（用于为项目中已存在的库目标定义别名）。

创建库（动态/静态/目标文件/...）。

```cmake
add_library(<name> OBJECT [<source>...])
```

创建obj文件的依赖库。

```cmake
add_library(<name> OBJECT [<source>...])
```

创建接口依赖。

```camke
add_library(<name> <type> IMPORTED [GLOBAL])
```

导入依赖。

例：

```cmake
# 创建hello.lib
add_library(hello
    STATIC
        hello.h
        hello.cpp
)
```

**ADD_LINK_LIBRARY**

```cmake
link_libraries([item1 [item2 [...]]]
               [[debug|optimized|general] <item>] ...)
```

在链接时将依赖文件(lib)与可执行文件(exe)链接起来。

```cmake
target_link_libraries(hello
    PRIVATE
        hello_lib
)
```

**ADD_LINK_OPTIONS**

```cmake
add_link_options(<option> ...)
```

在链接步骤中添加当前目录及以下的可执行文件、共享库或模块库目标的选项。

**ADD_SUBDIRECTORY**

`ADD_SUBDIRECTORY(source_dir [binary_dir] [EXCLUDE_FROM_ALL])` 

- `source_dir` 在源文件的子目录；
- `binary_dir` 编译输出（包含编译中间结果）路径；
- `EXCLUDE_FROM_ALL` 将这个目录从编译过程中排除；

向当前工程中添加存放源文件的子目录，并可以指定中间二进制和目标二进制存放的位置。

```cmake
ADD_SUBDIRECTORY(sub_dir)
```

**ADD_TEST**

```cmake
add_test(NAME <name> COMMAND <command> [<arg>...]
         [CONFIGURATIONS <config>...]
         [WORKING_DIRECTORY <dir>]
         [COMMAND_EXPAND_LISTS])
```

- `COMMAND` 命令行
- `CONFIGURATIONS` 配置
- `WORKING_DIRECTORY` 工作目录
- `COMMAND_EXPAND_LISTS` 对COMMAND参数扩展（3.16版本中新增的功能）

添加测试（具体见[CTest](#CTest)）。

**AUX_SOURCE_DIRECTORY**

```cmake
aux_source_directory(<dir> <variable>)
```

搜集所有在指定路径下的源文件的文件名，将输出结果列表储存在指定的变量中。

```cmake
aux_source_directory(. HELLO_SRC) # 查找当前目录下所有源文件并保存到HELLO_SRC
```

**CMAKE_DEPENDENT_OPTION**

```cmake
cmake_dependent_option(<option> "<help_text>" <value> <depends> <force>)
```

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


**CMAKE_MINIMUM_REQUIRE**

```cmake
cmake_minimum_required(VERSION <min>[...<policy_max>] [FATAL_ERROR])
```

CMake最小版本要求。

```cmake
cmake_minimum_required()

cmake_minimum_required(VERSION 3.24.1)
```

**CONFIGURE_FILE**

配置文件通过源码版本检查。

```cmake
configure_file(hello.h.in hello.h)
```

**ENABLE_TESTING**

```cmake
configure_file(<input> <output>
               [NO_SOURCE_PERMISSIONS | USE_SOURCE_PERMISSIONS |
                FILE_PERMISSIONS <permissions>...]
               [COPYONLY] [ESCAPE_QUOTES] [@ONLY]
               [NEWLINE_STYLE [UNIX|DOS|WIN32|LF|CRLF] ])
```

启用当前目录及以下目录的测试。

**EXEC_PROGRAM**

```cmake
exec_program(Executable [directory in which to run]
             [ARGS <arguments to executable>]
             [OUTPUT_VARIABLE <var>]
             [RETURN_VALUE <var>])
```

是否构建 test 目标,涉及工程所有目录。

**EXECUTE_PROCESS**

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

**FILE**

```cmake
Reading
  file(READ <filename> <out-var> [...])
  file(STRINGS <filename> <out-var> [...])
  file(<HASH> <filename> <out-var>)
  file(TIMESTAMP <filename> <out-var> [...])
  file(GET_RUNTIME_DEPENDENCIES [...])

Writing
  file({WRITE | APPEND} <filename> <content>...)
  file({TOUCH | TOUCH_NOCREATE} [<file>...])
  file(GENERATE OUTPUT <output-file> [...])
  file(CONFIGURE OUTPUT <output-file> CONTENT <content> [...])

Filesystem
  file({GLOB | GLOB_RECURSE} <out-var> [...] [<globbing-expr>...])
  file(RENAME <oldname> <newname> [...])
  file(COPY_FILE <oldname> <newname> [...])
  file({REMOVE | REMOVE_RECURSE } [<files>...])
  file(MAKE_DIRECTORY [<dir>...])
  file({COPY | INSTALL} <file>... DESTINATION <dir> [...])
  file(SIZE <filename> <out-var>)
  file(READ_SYMLINK <linkname> <out-var>)
  file(CREATE_LINK <original> <linkname> [...])
  file(CHMOD <files>... <directories>... PERMISSIONS <permissions>... [...])
  file(CHMOD_RECURSE <files>... <directories>... PERMISSIONS <permissions>... [...])

Path Conversion
  file(REAL_PATH <path> <out-var> [BASE_DIRECTORY <dir>] [EXPAND_TILDE])
  file(RELATIVE_PATH <out-var> <directory> <file>)
  file({TO_CMAKE_PATH | TO_NATIVE_PATH} <path> <out-var>)

Transfer
  file(DOWNLOAD <url> [<file>] [...])
  file(UPLOAD <file> <url> [...])

Locking
  file(LOCK <path> [...])

Archiving
  file(ARCHIVE_CREATE OUTPUT <archive> PATHS <paths>... [...])
  file(ARCHIVE_EXTRACT INPUT <archive> [...])
```

文件操作命令。

**FIND_PACKAGE**

- TODO 库名称；
- TODO 库得最低版本；
- REQUIRED 告诉模块是必须的（如果失败，则找不到该模块）；
- COMPONENTS 要查找的库列表。

从`CMAKE_MODULE_PATH`中的文件夹列表中搜索格式为`Findxxx.cmake`的CMAKE模块。

```cmake
find_package(Boost 1.80.0 REQUIRED COMPONENTS filesystem system)
```

**FIND_PATH**

```cmake
find_path (
          <VAR>
          name | NAMES name1 [name2 ...]
          [HINTS [path | ENV var]... ]
          [PATHS [path | ENV var]... ]
          [REGISTRY_VIEW (64|32|64_32|32_64|HOST|TARGET|BOTH)]
          [PATH_SUFFIXES suffix1 [suffix2 ...]]
          [DOC "cache documentation string"]
          [NO_CACHE]
          [REQUIRED]
          [NO_DEFAULT_PATH]
          [NO_PACKAGE_ROOT_PATH]
          [NO_CMAKE_PATH]
          [NO_CMAKE_ENVIRONMENT_PATH]
          [NO_SYSTEM_ENVIRONMENT_PATH]
          [NO_CMAKE_SYSTEM_PATH]
          [NO_CMAKE_INSTALL_PREFIX]
          [CMAKE_FIND_ROOT_PATH_BOTH |
           ONLY_CMAKE_FIND_ROOT_PATH |
           NO_CMAKE_FIND_ROOT_PATH]
         )
```

- `NAMES` 为目录中的文件指定一个或多个可能的名称；
- `HINTS, PATHS` 搜索的目录;
- `PATH_SUFFIXES` 在每个目录位置下面指定额外的子目录进行检查,否则视为无效；
- `DOC` 指定`<VAR>`缓存条目的文档字符串；
- `NO_CACHE` 搜索的结果将被存储在一个普通的变量中,而不是缓存条目（3.21版新增）；
- `REQUIRED` 如果没有找到任何东西,则停止处理并发出错误信息,否则在下一次用相同的变量调用find_path时,将再次尝试搜索（3.18版本新增）；
- `CMAKE_FIND_ROOT_PATH_BOTH` 按上述顺序搜索；
- `NO_CMAKE_FIND_ROOT_PATH` 不要使用`CMAKE_FIND_ROOT_PATH`变量；
- `ONLY_CMAKE_FIND_ROOT_PATH` 仅搜索重新rooted目录和`CMAKE_STAGING_PREFIX`下的目录。

查找包含命名文件的目录。

**FIND_LIBRARY**

```cmake
find_library (
          <VAR>
          name | NAMES name1 [name2 ...] [NAMES_PER_DIR]
          [HINTS [path | ENV var]... ]
          [PATHS [path | ENV var]... ]
          [PATH_SUFFIXES suffix1 [suffix2 ...]]
          [DOC "cache documentation string"]
          [NO_CACHE]
          [REQUIRED]
          [NO_DEFAULT_PATH]
          [NO_PACKAGE_ROOT_PATH]
          [NO_CMAKE_PATH]
          [NO_CMAKE_ENVIRONMENT_PATH]
          [NO_SYSTEM_ENVIRONMENT_PATH]
          [NO_CMAKE_SYSTEM_PATH]
          [CMAKE_FIND_ROOT_PATH_BOTH |
           ONLY_CMAKE_FIND_ROOT_PATH |
           NO_CMAKE_FIND_ROOT_PATH]
         )
```

此命令用于查找库。

**INCLUDE**

```cmake
include(<file|module> [OPTIONAL] [RESULT_VARIABLE <var>]
                      [NO_POLICY_SCOPE])
```

从文件或模块加载并运行CMake代码。

**INSTALL**

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

**LIST**

合成文件列表。

```cmake
list(
    APPEND hello_src
        hello.c
        hello_main.c
)
```

**MACRO**

```cmake
macro(<name> [<arg1> ...])
  <commands>
endmacro()
```

开始记录一个宏,以便以后以命令的形式调用（调用不区分大小写）。

例：

```cmake
macro(hello)
    ...
endmacro()

Hello()
```

**MESSAGE**

`MESSAGE([SEND_ERROR | STATUS | FATAL_ERROR] "message to display" ...)` 

- `SEND_ERROR` 产生错误，产生过程被跳过；
- `STATUS` 输出前缀为一的信息；
- `FATAL_ERROR` 立即终止所有cmake过程；

向终端输出信息。

**OPTION**

`OPTION(<NAME> "MESSAGE" [VALUE])`

- `NAME` 选项的变量名；
- `MESSAGE` 选项的说明；
- `VALUE` 选项的默认值（ON/OFF）。

用于接受命令行传入的参数。

```cmake
option(hello "hello world" ON)
```

**PROJECT**

`PROJECT(target_name LANGUAGES language)`

- `LANGUAGES` 编程语言（默认C++）。

声明工程名。

```cmake
project(HELLO)
```

指定项目名。

**SET**

`SET(VAR [VALUE] [CACHE TYPE DOCSTRING [FORCE]])`

设置[变量值](#变量)。

```cmake
SET(SRC_LIST main.c t1.c t2.c)
```

**SET_TARGET_PROPERTIES**

```cmake
set_target_properties(target1 target2 ...
                      PROPERTIES prop1 value1
                      prop2 value2 ...)
```

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

**SET_TESTS_PROPERTES**

```cmake
set_tests_properties(test1 [test2...] PROPERTIES prop1 value1 prop2 value2)
```

- `prop*` 键

    + TIMEOUT 

设置测试参数。

```cmake
set_tests_properties(helo PROPERTIES TIMEOUT 10) # 设置测试超时
```

**SUBDIRS**

`SUBDIRS(dir1 dir2 ...)` 

一次添加多个子目录（不推荐使用）。

**TARGET_COMPILE_DEFINITIONS**

根据作用域将目标的编译标志传递到其他目标。

```cmake
target_compile_definitions(hello_flags
    PRIVATE EX3
)
```

**TARGET_COMPILE_FEATURES**

设置C++标准。

```c++
target_compile_features(hello PUBLIC cxx_auto_type)
```

**TARGET_COMPILE_OPTIONS**

设置编译选项。

```c++
target_compile_options(hello PRIVATE ${hello_flags})
```

**TARGET_LINK_LIBRARIES**

`TARGET_LINK_LIBRARIES[TARGETS SOURCE]` 

- `TARGETS` 要链接到的可执行目标；
- `SOURCE` 目标库。

将目标库链接到可执行目标。

```cmake
target_link_libraries(hello hello_lib)
```

**TARGET_INCLUDE_DIRECTORIES**

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

**TARGETS**

生成的目标名。


### 自定义函数

#### function

cmake提供`function`，用于自定义函数。

```cmake
function(<name> [arg1 [arg2 [arg3 ...]]])
  COMMAND1(ARGS ...)
  COMMAND2(ARGS ...)
  ...
endfunction(<name>)
```

- `<𝑛𝑎𝑚𝑒>` 为函数名字
- `arg1、arg2...` 为函数参数

例：

```cmake
set(x "ABC")
set(y "DEF")

function(F1 arg)
  message(arg "abc" PARENT_SCOPE)
endfunction()

function(F2 arg)
  message(${arg} "def" PARENT_SCOPE) 
endfunction()

Foo(${x}) # 传值
Foo(y)    # 传引用
```

#### 隐式参数

cmake针对`functiion`定义了一些隐含参数：

| 隐式参数 | 说明                                                             |
|----------|------------------------------------------------------------------|
| ARGC     | 函数实参的个数                                                   |
| ARGV     | 所有实参列表                                                     |
| ARGN     | 所有额外实参列表, 即ARGV去掉函数声明时显示指定的实参，剩余的实参 |
| ARGV0    | 函数第1个实参                                                    |
| ARGV1    | 函数第2个实参                                                    |
| ARGV2    | 函数第3个实参                                                    |
| ...      | ...                                                              |

例：

```cmake
function(print_list arg)
    message("======= args count : ${ARGC} ======= ")    # 实际实参个数

    message("======= all args ======= ")                # 打印所有参数
    foreach(v IN LISTS ARGV)
        message(${v})
    endforeach()


    message("======= all extra args ======= ")          # 打印所有额外参数
    foreach(v IN LISTS ARGN)
        message(${v})
    endforeach()

    message("======= print content of ARGV0 ======= ")  # 打印第一个参数里的所有内容
    foreach(v IN LISTS ARGV0)
        message(${v})
    endforeach()
endfunction()

set(arg hello world) 

message("------------ calling with qutoes -----------")     # 使用引号来调用
print_list("${arg}")

message("------------ calling without qutoes -----------")  # 不使用引号调用
print_list(${arg})
```

---



## 变量

### 系统变量

- `CMAKE_MAJOR_VERSION` 主版本号
- `CMAKE_MINOR_VERSION` 次版本号
- `CMAKE_PATCH_VERSION` 补丁等级
- `CMAKE_SYSTEM` 系统名称
    + `APPLE` macos系统
    + `UNIX` unix系统
    + `WIN32` windows系统
    + `MINGW` mingw环境
- `CMAKE_SYSTEM_NAME` 不包含版本的系统名
- `CMAKE_SYSTEM_VERSION` 系统版本
- `CMAKE_SYSTEM_PROCESSOR` 处理器名称
- `HOME`

### 编译变量

- `MSVC`

### 环境变量

- `CMAKE_BINARY_DIR` 二进制文件生成目录；
- `CMAKE_RUNTIME_OUTPUT_DIRECTORY` 可执行文件存放路径
- `CMAKE_CURRENT_BINARY_DIR` 当前所在的生成目录；
- `CMAKE_CURRENT_LIST_FILE` 当前正在处理的列表文件的完整路径；
- `CMAKE_CURRENT_LIST_LINE`当前正在处理的文件的行号；
- `CMAKE_CURRENT_SOURCE_DIR` 当前源目录；
- `CMAKE_INCLUDE_CURRENT_DIR` 是否将当前的源代码和构建目录添加到include路径中；
- `CMAKE_INCLUDE_DIRECTORIES_PROJECT_BEFORE` 是否强制预置项目包含目;
- `CMAKE_INCLUDE_PATH` 
- `CMAKE_LIBRARY_PATH`
- `CMAKE_MODULE_PATH`
- `CMAKE_PROJECT_NAME` 由`project()`命令设置的第一个项目（顶级项目）的名称；
- `CMAKE_SOURCE_DIR` 根源目录；
- `EXECUTABLE_OUTPUT_PATH` 可执行二进制文件的生成路径；
- `LIBRARY_OUTPUT_PATH` 共享库（动态/静态库）的生成路径（当默认路径不设置时，才生效）；
- `CMAKE_ARCHIVE_OUTPUT_DIRECTORY` 静态库默认存放路径。
- `CMAKE_LIBRARY_OUTPUT_DIRECTORY` 动态库默认存放路径。
- `PROJECT_BINARY_DIR` 当前项目的生成目录；
- `PROJECT_NAME` 项目名；
- `PROJECT_SOURCE_DIR` 当前cmake项目的源目录；
- `xxx_SOURCE_DIR` xxx项目的源目录；
- `xxx_BINARY_DIR` xxx项目的二进制目录。

### 外部标志

- `BUILD_SHARED_LIBS` 控制默认的库编译方式(默认编译生成的库都是静态库)；
- `CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS` 用于控制if else语句的书写方式；
- `CMAKE_BUILD_TYPE` [构建类型](#构建类型)；
- `CMAKE_C_FLAGS` c编译器标志；
- `CMAKE_CXX_COMPILER` 指定使用哪个c++编译器；
    + `clang++` 使用clang；
- `CMAKE_CXX_FLAGS` c++编译器标志；
    + `-std` 编译器版本；
- `CMAKE_CXX_STANDARD` c++标准库标志（从v3.1开始提供）；
- `CMAKE_LINKER_FLAGS` 链接器标志；

### 编译器选项

TODO

### 缓存变量

TODO

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
### 示例

```cmake
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DEX2" CACHE STRING "Set C++ Compiler Flags" FORCE)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11") # 使用c++11版本

set(CMAKE_CXX_STANDARD 11) # 使用c++11标准库
```

```sh
cmake -DCMAKE_CXX_COMPILER=clang++ .. # 使用clang编译
```

---



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

FetchContent_Populate( # 声明外部内容
  firmware
  URL        https://mycompany.com/assets/firmware-1.23-arm.tar.gz
  URL_HASH   MD5=68247684da89b608d466253762b0ff11
  SOURCE_DIR firmware
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

---



## 单元测试

### CTest

CMake从3.5开始提供了测试工具CTest，用于单元测试。

CTest遵循的标准约定是：返回零意味着成功，非零返回意味着失败；可以返回零或非零的脚本，都可以做测试用例。

使用以下选项可以从CTest获得更详细的测试输出：

- `--output-on-failure` 将测试程序生成的任何内容打印到屏幕上，以免测试失败；
- `-v` 将启用测试的详细输出；
- `-vv` 启用更详细的输出;
- `--rerun-failed` 是否重新运行以前失败的测试。

例：

```cmake
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(hello_test LANGUAGES CXX)

find_package(PythonInterp REQUIRED)
find_program(BASH_EXECUTABLE NAMES bash REQUIRED)

add_executable(hello_test test.cpp)
```

```python
enable_testing() # 测试这个目录和目录下的所有子文件夹

# 设置测试环境变量
set_tests_properties(python_test
    PROTERTIES
        ENVIRONMENT
            HELLO_MODULE_PATH=${CMAKE_CURRENT_SOURCE_DIR}
            HELLO_HEADER_FILE=${CMAKE_CURRENT_SOURCE_DIR}/test.hpp)
            HELLO_LIBRARY_FILE=$<TARGET_FILE:hello_test>
            ${PYTHON_EXECUTABLE}
            ${CMAKE_CURRENT_SOURCE_DIR}/test.py
)

# 定义一个新的测试，
add_test(
    NAME hello_test # 设置测试名称
    COMMAND $<TARGET_FILE:hello_test> # 使用生成器表达式运行命令
)

# 设置测试时长
set_tests_properties(hello PROPERTIES TIMEOUT 10)
```

```sh
ctest
```

### 其它

CMake同时支持以下其它单元测试工具：

- [boost test](#集成Boost)

---



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

CPack用于生成包程序包，在CMakeCPack.cmake中列出了CPack指令，用于生成`CPackConfig.cmake`，当运行以`package`或`package_source`目标的CMake命令时，CPack会自动调用。

#### 变量

- CPACK_PACKAGE_NAME 名称
- CPACK_PACKAGE_VENDOR 供应商
- CPACK_PACKAGE_DESCRIPTION_FILE 描述文件
- CPACK_PACKAGE_DESCRIPTION_SUMMARY 包描述
- CPACK_RESOURCE_FILE_LICENSE 许可证文件
- CPACK_PACKAGING_INSTALL_PREFIX 安装路径
- CPACK_PACKAGE_VERSION_MAJOR 主要版本
- CPACK_PACKAGE_VERSION_MINOR 次要版本
- CPACK_PACKAGE_VERSION_PATCH 布丁版本
- CPACK_SOURCE_IGNORE_FILES 忽略文件/目录
- CPACK_SOURCE_GENERATOR 归档格式
- CPACK_GENERATOR 打包工具
- CPACK_DEBIAN_PACKAGE_MAINTAINER
- CPACK_DEBIAN_PACKAGE_SECTION
- CPACK_NSIS_CONTACT
- CPACK_NSIS_ENABLE_UNINSTALL_BEFORE_INSTALL 是否在安装之前先卸载
- CPACK_BUNDLE_NAME bundle打包名
- CPACK_BUNDLE_PLIST `*.plist`文件
- CPACK_BUNDLE_ICON 图标

#### 工具

- linux

    TODO

- macos

    macos使用以下工具打包`.dmg`文件：
    
    1. Bundle

- windows

    windows提供以下工具打包`.exe`文件：

    1. NSIS

#### 示例

```cmake
# 声明包的名称
set(CPACK_PACKAGE_NAME "${PROJECT_NAME}")

# 声明包的供应商
set(CPACK_PACKAGE_VENDOR "hello")

# 打包描述文件
set(CPACK_PACKAGE_DESCRIPTION_FILE "${PROJECT_SOURCE_DIR}/INSTALL.md")

# 添加包描述
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "hello")

# 添加许可证文件
set(CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/LICENSE")

# 设置文件安装路径到 /usr/local/hello
set(CPACK_PACKAGING_INSTALL_PREFIX "/usr/local/${PROJECT_NAME}")

# 设置 主要，次要和补丁版本
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

# 设置在包装时需要忽略的文件列表和目录
set(CPACK_SOURCE_IGNORE_FILES "${PROJECT_BINARY_DIR};/.git/;.gitignore")

# 设置归档格式
set(CPACK_SOURCE_GENERATOR "ZIP;TGZ")

# 设置二进制存档生成器
set(CPACK_GENERATOR "ZIP;TGZ")

# 声明linux平台原生二进制安装程序
if(UNIX)
    if(CMAKE_SYSTEM_NAME MATCHES Linux) 
        list(APPEND CPACK_GENERATOR "DEB") # .deb
        set(CPACK_DEBIAN_PACKAGE_MAINTAINER "master")
        set(CPACK_DEBIAN_PACKAGE_SECTION "devel")
        set(CPACK_DEBIAN_PACKAGE_DEPENDS "uuid-dev")

        list(APPEND CPACK_GENERATOR "RPM") # .rpm
        set(CPACK_RPM_PACKAGE_RELEASE "1")
        set(CPACK_RPM_PACKAGE_LICENSE "MIT")
        set(CPACK_RPM_PACKAGE_REQUIRES "UUID-DEVEL")
    endif()
endif()

# 声明windows平台原生二进制安装程序
if(WIN32 OR MINGW)
   list(APPEND CPACK_GENERATOR "NSIS") # nsis安装程序
   set(CPACK_NSIS_PACKAGE_NAME "hello")
   set(CPACK_NSIS_CONTACT "master")
   set(CPACK_NSIS_ENABLE_UNINSTALL_BEFORE_INSTALL ON)
endif()

# 声明windows平台原生二进制安装程序
if(APPLE)
    list(APPEND CPACK_GENERATOR "Bundle") # bundle
    set(CPACK_BUNDLE_NAME "hello")
    configure_file(${PROJECT_SOURCE_DIR}/cmake/Info.plist.in Info.plist @ONLY)
    set(CPACK_BUNDLE_PLIST ${CMAKE_CURRENT_BINARY_DIR}/Info.plist)
    set(CPACK_BUNDLE_ICON ${PROJECT_SOURCE_DIR}/cmake/coffee.icns)
endif()

# 打印信息
message(STATUS "CPack genertors: ${CPACK_GENERATOR}")

include(CPack)
```

---



## 可移植性

---



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

---



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

### Boost单元测试

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

---



## 集成git

TODO

---



## 集成Visual Studio

microsoft在VS2017开始支持CMake，如果需要启用Visual Studio 对CMake的支持，需要安装VS的C++ CMake工具“C++ CMake tools for Windows”。

### 构建VS项目

因此构建不同版本的VS项目，需要在构建时指定VS生成器和架构：

```sh
cmake -G "<platform>" -A <architecture>
```

- `platform` VS生成器
    + "Visual Studio 6"
    + "Visual Studio 7"
    + "Visual Studio 7 .NET 2003"
    + "Visual Studio 8 2005"
    + "Visual Studio 9 2008"
    + "Visual Studio 10 2010"
    + "Visual Studio 11 2012"
    + "Visual Studio 12 2013"
    + "Visual Studio 14 2015"
    + "Visual Studio 15 2017"
    + "Visual Studio 16 2019"
    + "Visual Studio 17 2022"
    + ...
- `architecture` 架构
    + Win32
    + x64
    + ARM
    + ARM64
    + ...

选择编译环境。

例：

```sh
cmake -G "Visual Studio 17 2022" -A x64
```

---



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

---



## 集成Zeromq

zeromq是一个开源的第三方网络库，cmake提供相关方式集成zeromq。

### 变量

- `ZMQ_BUILD_TESTS` 构建test示例
- `BUILD_SHARED` 构建动态库
- `BUILD_STATIC` 构建静态库

例：

```sh
cmake .. -DZMQ_BUILD_TESTS=OFF -DBUILD_STATIC=ON -DBUILD_SHARED=ON
```

### zmqpp

zmqpp是一个优秀的zeromq C++版本封装库，使用Cmake可以集成zmqpp工程，以下是常用变量：

- `ZMQ_BUILD_TESTS` 是否开启test
- `ZMQPP_BUILD_STATIC` 是否编译静态库（默认开启）
- `ZMQPP_BUILD_SHARED` 是否编译动态库（默认开启）
- `ZMQPP_LIBZMQ_NAME_STATIC` zeromq的静态库
- `ZMQPP_LIBZMQ_NAME_SHARED` zeromq的动态库
- `ZEROMQ_LIB_DIR` zeromq的的关的查找路径
- `ZEROMQ_INCLUDE_DIR` zeromq相头文件目录

例：

```cmake
cmake .. -G "Visual Studio 14 2015 Win64" -DZMQ_BUILD_TESTS=OFF
```
---



## 集成Valgrind

Valgrind是一个通用的工具，用于检测内存缺陷和内存泄漏，CMake支持集成Valgrind。

例：

```c++
// main.cpp
#include <iostream>

int main() {
    auto m = new double[1000]; // 没有释放
}
```

```cmake
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(hello LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(hello_test main.cpp)

# 查找valgrind，并设置绝对路径MEMORYCHECK_COMMAND
find_program(MEMORYCHECK_COMMAND NAMES valgrind)

# 设置valgrind参数（创建日志文件，用于记录内存缺陷信息）
set(MEMORYCHECK_COMMAND_OPTIONS "--trace-children=yes --leak-check=full")

include(CTest)
enable_testing()

add_test(
    NAME hello_test
    COMMAND $<TARGET_FILE:hello_test>
)
```

```sh
ctest -T memcheck
```

---




## 参考

[1] [CMake Tutorial](https://cmake.org/cmake/help/latest/guide/tutorial/index.html)

[2] Eric Noulard, Roberto Di Remigio.CMake-Cookbook

[3] [Modern CMake 简体中文版](https://github.com/Modern-CMake-CN/Modern-CMake-zh_CN)

[4] [An Introduction to Modern CMake](https://cliutils.gitlab.io/modern-cmake/)

[5] [CMake基础教程](https://www.cnblogs.com/juzaizai/category/1993745.html)

[6] [Linux下使用CMake进行编译的时候寻找Boost库](https://www.jianshu.com/p/1827cd86d576)

[7] [Using CMake with Qt 5](https://www.kdab.com/using-cmake-with-qt-5/)

[8] [Build with CMake](https://doc.qt.io/qt-5/cmake-manual.html)

[9] [CMake 3.21 [中文]](https://runebook.dev/zh-CN/docs/cmake/-index-#Commands)

[10] [Visual Studio 中的 CMake 项目](https://learn.microsoft.com/zh-cn/cpp/build/cmake-projects-in-visual-studio?view=msvc-170)

[11] [Visual Studio 17 2022](https://cmake.org/cmake/help/latest/generator/Visual%20Studio%2017%202022.html)

[12] [CMake语法—缓存变量（Cache Variable）](https://www.cnblogs.com/Braveliu/p/15614013.html)
