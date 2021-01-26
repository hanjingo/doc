# cmake 教程
## cmake_minimum_require
指定运行此配置文件所需的 CMake 的最低版本

## project
指定项目名

## aux_source_directory
搜集所有在指定路径下的源文件的文件名，将输出结果列表储存在指定的变量中
```txt
aux_source_directory(< dir > < variable >)
```