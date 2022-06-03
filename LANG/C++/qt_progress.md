# Qt进程

[TOC]



## 打包可执行程序

1. 使用`Release`模式编译项目；

2. 启动`Qt 5.9.9 (MSV 2015 64-bit)`控制台程序（其它版本和平台请相应变更），并切换到Release目录

3. 执行以下命令进行打包

   - 对于QWidget：

     ```shell
     windeployqt xx.exe
     ```

   - 对于Qt-quick：

     ```shell
     windeployqt xx.exe –qmldir xxx # xx.exe：可执行程序名，xxx：qml路径
     ```



## 参考

- [QT可执行文件编译打包，生成用来发给别人执行的文件](https://blog.51cto.com/u_6043682/3706089)
- [Qt 之启动外部程序](https://blog.csdn.net/liang19890820/article/details/50478833?utm_medium=distribute.pc_relevant.none-task-blog-2~default~baidujs_baidulandingword~default-0-50478833-blog-8289144.pc_relevant_default&spm=1001.2101.3001.4242.1&utm_relevant_index=3)