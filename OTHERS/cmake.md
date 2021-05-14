# cmake 教程



## cmake关键字

- cmake_minimum_require

    指定运行此配置文件所需的 CMake 的最低版本

- project

    指定项目名

- aux_source_directory

    搜集所有在指定路径下的源文件的文件名，将输出结果列表储存在指定的变量中

    ```cmake
    aux_source_directory(< dir > < variable >)
    ```

    

## 从cmake命令行传入参数

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

