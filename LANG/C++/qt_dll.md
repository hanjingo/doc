# Qt动态链接库


<!-- vim-markdown-toc GFM -->

* [关键字](#关键字)
    - [Q_DECL_EXPORT和Q_DECL_IMPORT](#q_decl_export和q_decl_import)
* [调用](#调用)
    - [隐式调用](#隐式调用)
    - [显式调用](#显式调用)
* [示例](#示例)
    - [创建接口类](#创建接口类)
    - [创建动态链接库](#创建动态链接库)
    - [显式调用](#显式调用-1)
* [参考](#参考)

<!-- vim-markdown-toc -->



## 关键字

### Q_DECL_EXPORT和Q_DECL_IMPORT

Qt中每个共享库导出给用户使用的类，符号，函数等都需要用宏`Q_DECL_EXPORT`来定义导出。

Qt中每个使用共享库的应用程序都需要通过`Q_DECL_IMPORT`导入共享库里的可用对象。

示例：

```c++
#ifndef HELLO_GLOBAL_H
#define HELLO_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(HELLO_LIBRARY)
#  define HELLO_EXPORT Q_DECL_EXPORT
#else
#  define HELLO_EXPORT Q_DECL_IMPORT
#endif

#endif // HELLO_GLOBAL_H
```



## 调用

### 隐式调用

TODO

### 显式调用

QLibrary用于显式链接调用共享库，与平台无关，一个QLibrary对象只对一个共享库进行操作。



## 示例

### 创建接口类

1. 选择`Library/C++ Library`，创建工程并命名为`dll_class_interface`（接口工程建议以`interface`结尾）

2. 修改`.pro`文件

   ```txt
   DEFINES += DLL_CLASS_INTERFACE_LIB # xx_LIB用于标识启用Q_DECL_EXPORT
   ```

3. 创建抽象类作为接口

   ```c++
   class DLL_CLASS_INTERFACE_EXPORT dll_class_interface
   {
   public:
       virtual void say() = 0;
   };
   ```

4. 编译构建

### 创建动态链接库

1. 选择`Library/C++ Library`并创建工程`dll_class`

2. 修改`.pro`文件

   ```txt
   CONFIG(debug, debug|release) {
       LIBS += -L$$PWD/./ -ldll_class_interface # 导入接口工程的lib文件
   } else {
       LIBS +=  -L$$PWD/./ -ldll_class_interface
   }
   
   INCLUDEPATH += ../dll_class_interface # 导入接口工程目录
   
   HEADERS += ../dll_class_interface/dll_class_interface.h # 导入接口类头文件
   ```

3. 修改`dll_class.h`

   ```c++
   #include "dll_class_interface.h"
   
   class dll_class : public dll_class_interface
   {
   public:
       dll_class();
       ~dll_class();
   
   public:
       virtual void say(); // 实现接口
   };
   
   // 导出创建对象函数为C接口
   extern "C"
   {
       DLL_CLASS_INTERFACE_EXPORT dll_class_interface* create_dll_class();
       DLL_CLASS_INTERFACE_EXPORT void release_dll_class(dll_class_interface* obj);
   }
   
   // 定义类类型
   typedef dll_class_interface* (*create_dll_class_t)();
   typedef void(*release_dll_class_t)(dll_class_interface*);
   ```

4. 修改`dll_class.cpp`

   ```c++
   void dll_class::say()
   {
       qDebug() << "hello";
       qDebug() << "world";
   }
   
   dll_class_interface* create_dll_class()
   {
       return new dll_class();
   }
   
   void release_dll_class(dll_class_interface* obj)
   {
       delete obj;
   }
   ```

5. 编译构建

### 显式调用

1. 创建Qt应用程序`dll_test`

2. 修改`.pro`文件

   ```txt
   INCLUDEPATH += \
       ../dll_class_interface \
       ../dll_class
   
   HEADERS += \
       ../dll_class/dll_class.h \ # 导入头文件
       ../dll_class_interface/dll_class_interface.h # 导入头文件
   ```

3. 修改`main.cpp`

   ```c++
   #include <QCoreApplication>
   #include <QLibrary>
   
   #include "dll_class_interface.h"
   #include "dll_class.h"
   
   int main(int argc, char* argv[])
   {
       QCoreApplication a(argc, argv);
       QLibrary lib("./dll_class.dll"); // 加载dll
   
       if (lib.load()) {
           auto create = (create_dll_class_t)lib.resolve("create_dll_class");
           auto obj = create();
           obj->say();
       }
   
       return a.exec();
   }
   ```

   

   

   





## 参考

[1] [Qt中的动态链接库编程(Q_DECL_IMPORT、Q_DECL_EXPORT)](https://blog.csdn.net/weixin_39743893/article/details/81225240)

[2] [Qt 动态链接库的创建和使用](https://blog.csdn.net/qq_45147279/article/details/121516226)

[3] [Qt：56---QT创建和使用动态链接库（.dll）](https://blog.51cto.com/u_15346415/5172442)
