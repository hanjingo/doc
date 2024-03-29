# C++插件系统


<!-- vim-markdown-toc GFM -->

* [设计思路](#设计思路)
    - [影响因素](#影响因素)
    - [插件通信机制](#插件通信机制)
    - [设计模式](#设计模式)
        + [访问者模式](#访问者模式)
        + [单例模式](#单例模式)
    - [接口设计](#接口设计)
    - [插件管理](#插件管理)
    - [版本控制](#版本控制)
    - [最佳实践](#最佳实践)
* [逆向工程](#逆向工程)
    - [常用工具](#常用工具)
* [x3py](#x3py)
    - [插件装/卸载](#插件装卸载)
    - [例1：vs编写插件示例](#例1vs编写插件示例)
* [CTK](#ctk)
    - [编译](#编译)
* [CppMicroServices](#cppmicroservices)
* [COM](#com)
* [自定义插件框架](#自定义插件框架)
    - [延伸 - 基于微服务实现](#延伸---基于微服务实现)
* [总结](#总结)
    - [对比](#对比)
* [参考](#参考)

<!-- vim-markdown-toc -->



C++由于其语言本身及历史问题，缺乏标准的ABI规范，其二进制兼容性较差（比C还要烂），用C++做插件化开发比较痛苦。同时由于插件化开发具有以下优点：

- 优化了团队协作，方便进行任务划分；
- 对大型项目进行解耦，降低项目复杂度；
- 提高代码重用度；
- 简化开发，发布及维护流程。

因此，本文主要用于讨论C++插件设计以及对市面上已有的C++插件方案和自定义插件框架的介绍，仅供参考。



## 设计思路

### 影响因素

设计插件时，以下这些因素会影响插件系统的架构模式：

1. 编程语言使用C还是C++。

   C++没有明确的定义ABI，不同编译器，甚至同一编译器的不同版本，生成的带啊吗可能无法做到二进制兼容。

   C代码的ABI有明确的定义，可以跨平台和跨编译器工作。

2. 版本控制。

   编写插件时，需要指定API版本的适用范围。

3. 插件的元数据（名字、版本等）使用内部还是外部的。

4. 安全性。

5. 静态库还是动态库。

### 插件通信机制

1. 基于虚拟服务总线

   每个插件都有自己的开放接口，这些接口会被注册到虚拟服务总线上，其它插件通过虚拟服务总线，获取到其他插件的接口服务。

   ![plugin_virtual_service_bus](res/plugin_virtual_service_bus.png)

   *虚拟服务总线示意图*

2. 插件间消息通信

   由插件开发者之间自行约定接口定义，调用及返回规则（契约），插件之间直接进行通信；插件通信一般基于SOA模型，服务=契约（接口）+实现（类）。

### 设计模式

#### 访问者模式

TODO

#### 单例模式

TODO

### 接口设计

根据C++语言特性，总结出以下接口设计方法：

1. `PIMPL（Pointer to Implementation）` 在接口类成员中包含一个指向实现类的指针，这样可以最大限度做到接口和实现分离。
2. `Object Interface` 采用C++的动态功能，实现类继承接口类，功能接口函数定义成虚函数。

**注意事项**

接口设计时需要遵循以下规则：

1. 单一功能原则

   一个class只提供单一的服务。如果一个class提供多种服务，那么就因该将它拆分；如果某个单一功能由多个class负责，则应将这几个class合并。

2. 开放/封闭原则

   对于扩充的动作支持，对于修改的动作封闭（即：可以加接口，尽量不要改接口）。

3. 最小惊讶原理

   在重载函数，或者子类实现父类虚函数时，应该基本维持函数原来所期望的功能。

4. 不要过度封装

   设计接口时，应该紧盯着下面3个问题：

   - 我们需要解决什么问题；
   - 问题的核心是什么；
   - 应该怎样设计，可以方便客户扩展。

5. 注意命名规范

   名字要简洁规范，达到望文生义的效果。

### 插件管理

插件管理器用于对插件的管理，需要处理以下任务：

1. 加载所有插件的元数据。
2. 插件加载时，初始化例程，提供对库中符号的访问能力。
3. 插件卸载时，调用其清理例程。

### 版本控制

设计插件API时，需要考虑向前及向后兼容。

### 最佳实践

- **使用抽象基类**。实现抽象基类的虚方法可以使插件与ABI问题隔离，因为虚方法调用通常是用类的虚函数表中的索引来表示（需要注意，不同编译器对重载的虚函数在虚函数表中的排序算法可能是不同的）。
- **使用C链接**，即`extern "C"`语法。
- **避免使用STL和异常**。STL的不同实现可能不是ABI兼容的，编写插件时应尽量避免使用这些容器。
- **不要混用内存分配器**。插件链接的内存分配器可能与用户的内存分配器不同，对于插件系统的设计而言，要么所有的对象由插件分配并回收，要么将控制权交给用户，由用户负责创建和销毁。
- **windows平台需要处理`__declspec(dllexport)和__declspec(dllimport)`修饰符**。



## 逆向工程

### 常用工具

windows：

- `tasklist.exe` 分析EXE文件所依赖的动态库。
- `depends.exe` 分析DLL文件的依赖关系。
- `dlister.exe` 列出计算机上安装的所有DLL文件。
- `dcomp.exe` 显示`dlister.exe`产生的两个DLL列表文件的不同之处。

linux：

- `libtool` 提供了一致的，可移植的接口，支持在不同的`*nix`平台上创建库。
- `nm` 显示目标文件或库中的符号名。
- `ldd` 显示可执行程序依赖的动态库列表。

## x3py

x3py是一款国人出品的C++插件式框架，支持Windows，Linux及Macos平台，其项目地址为：https://github.com/rhcad/x3py。

### 插件装/卸载

插件装载模式：

1. 装载多个插件
2. 装载单个插件
3. 滚动装载
4. 装载静态链接库插件
5. 扫描装载

x3py最多支持装载40个插件（具体看 `PLUGINS_MAXCOUNT` 相关定义）

### 例1：vs编写插件示例

1. 编译core/x3manager项目，得到x3manager.pln（这个是核心插件，其它所有插件都依赖于它）

2. 新建WIN32项目libtest`，并设置”应用程序类型“为静态库/动态库，同时对项目进行以下配置：

   在 `配置属性\常规\输出目录` 设置值：`你的输出目录\$(Configuration)\plugins\`。

   在 `配置属性\常规\中间目录` 设置值：`你的输出目录\$(Configuration)\obj\$(ProjectName)\`。

   在 `配置属性\c/c++\常规\附加包含目录` 中添加以下值：

   - `x3py源码目录\source\public`
   - `x3py源码目录\interface\core`

   在 `配置属性\C/C++\所有选项\预编译头` 中选择`不使用预编译头`。

3. 在`libtest`中新建以下文件：

   - `itest.h`

     ```c++
     #pragma once
     
     #include <objptr.h>
     
     const char* const clsidSimple = "94071767-ba6b-4769-9eb4-2ebf469289f3";
     class ITest : public x3::IObject
     {
     	X3DEFINE_IID(ITest);
     	virtual int add(int a, int b) const = 0;
     };
     ```

   - `libtest.h`

     ```c++
     #pragma once
     
     #include <module/classmacro.h>
     #include "itest.h"
     
     class CTestA : public ITest
     {
     	X3BEGIN_CLASS_DECLARE(CTestA, clsidSimple)
     		X3DEFINE_INTERFACE_ENTRY(ITest)
     	X3END_CLASS_DECLARE()
     protected:
     	CTestA();
     	virtual ~CTestA();
     private:
     	virtual int add(int a, int b) const;
     };
     ```

   - `libtest.cpp`

     ```c++
     #include <module/plugininc.h>
     #include "libtest.h"
     
     CTestA::CTestA() {}
     CTestA::~CTestA() {}
     int CTestA::add(int a, int b) const
     {
     	return a + b;
     }
     ```

   - `module.cpp`

     ```c++
     // lib版本
     #include <module/plugininc.h>
     #include <module/pluginimpl.h>
     #include <module/modulemacro.h>
     #include "libtest.h"
     
     XBEGIN_DEFINE_MODULE()
     XDEFINE_CLASSMAP_ENTRY(CTestA)
     XEND_DEFINE_MODULE_LIB(libtest)
     ```
     
     ```c++
     // pln版本
     #include <module/plugininc.h>
     #include <module/pluginimpl.h>
     #include <module/modulemacro.h>
     #include "libtest.h"
     
     XBEGIN_DEFINE_MODULE()
     XDEFINE_CLASSMAP_ENTRY(CTestA)
     XEND_DEFINE_MODULE_DLL()
     
     OUTAPI bool x3InitializePlugin() { return true; }
     OUTAPI void x3UninitializePlugin() {}
     ```
   
4. 新建Win32控制台应用程序空项目`test`，同时对项目进行以下配置：

   在 `配置属性\常规\输出目录` 设置值：`你的输出目录\$(Configuration)\`。

   在 `配置属性\常规\中间目录` 设置值：`你的输出目录\$(Configuration)\obj\$(ProjectName)\`。

   在 `配置属性\c/c++\常规\附加包含目录` 中添加以下值：

   - `x3py源码目录\source\public`
   - `x3py源码目录\interface\core`
   - `libtest目录`

   在 `配置属性\C/C++\所有选项\预编译头` 中选择`不使用预编译头`。

   （如果要生成指定后缀`.pln`的插件，需要额外做以下几步）：

   在 `配置属性\链接器\常规\输出文件` 中设置值：`$(OutDir)$(ProjectName).pln`。

5. 在VS中引入静态依赖库`libtest.lib`到当前项目（如果是动态类型的插件，如`xx.pln`的可跳过这步）。

6. 在`test`中新建以下文件：

   - `main.cpp`

     ```c++
     #include <portability/x3port.h>
     #include <module/pluginimpl.h>
     #define XUSE_LIB_PLUGIN
     #include <module/modulemacro.h>
     XDEFINE_EMPTY_MODULE()
     
     #include <iostream>
     #include "itest.h"
         
     #include <chrono>
     
     /* 加载lib类型插件 */
     #ifdef _MSC_VER
     #pragma comment(lib, "libtest.lib")
     #endif
     
     extern const x3::ClassEntry* const classes_libtest;
     
     const x3::ClassEntry* const x3::ClassEntry::classes[] = {
     	s_classes, classes_libtest, NULL
     };
     
     int main()
     {
         /* 自动加载pln类型插件 */
     	//const char* plugins[] = { "x3manager.pln", "libtest.pln", NULL};
     	//x3::AutoLoadPlugins autoload(plugins, "plugins");
         
     	x3::Object<ITest> p(clsidSimple);
     	if (p)
     		std::cout << "plugin:" << p->getInterfaceName() << " is loaded in:" << p->getClassName() << std::endl;
     	else
     	{
     		std::cout << "The plugin is not loaded." << std::endl;
     		return 1;
     	}
     
     	int sum = p->add(1, 2);
     	std::cout << "p->add(1, 2) = " << sum << std::endl;
         
         // 运行100000000次调用
     	auto times = 100000000;
     	auto start = std::chrono::system_clock::now();
     	std::cout << "bench start" << std::endl;
     	for (auto i = 0; i < times; i++)
     		p->add(1, 2);
     	auto dur = std::chrono::system_clock::now() - start;
     	std::cout << "bench end:" << times
     		<< " times cost: " << std::chrono::duration_cast<std::chrono::milliseconds>(dur).count() << "ms"
     		<< std::endl;
         
     	std::cin >> sum;
     	return 0;
     }
     ```
     



## CTK

CTK 为支持生物医学图像计算的公共开发包，其全称为 Common Toolkit，基于OSGi规范和Qt框架，主要包括以下功能：

- `DICOM` 用于从PACS和本地数据库中查询和检索。
- `DICOM Application Hosting` 用于创建主机和托管应用程序的基础设施。
- `Widgets` 用于生物医学成像应用的 Qt Widgets 集合。
- `Plugin Framework` **用于 C++ 的动态组件系统**。
- `Command Line Interfaces` 一种允许将算法编写为自包含可执行程序的技术，可以在多个终端用户应用程序环境中使用，而无需修改。

其地址为：https://github.com/commontk/CTK。

### 编译

1. 下载安装以下工具：

   - CMake：
   - QT 5.14.2：
   
2. 配置
   
   下载CTKData项目，其地址为：https://github.com/commontk/CTKData。
   
   - Windows + Cmake
   
     配置CTKData项目：
   
     ```cmake
     # CTK/CMakeExternals/CTKData.cmake
     set(CTKData_DIR "C:\\Work\\src\\CTKData") # 填CTKData项目地址
     ```
   
     开启PluginFramework编译：
   
     ```cmake
     # /CTK/CMakeLists.txt
     ctk_lib_option(PluginFramework
                    "Build the Plugin Framework" ON
                    CTK_ENABLE_PluginFramework)
     ```
   
     修改安装选项：
   
     ```cmake
     # /CTK/SuperBuild.cmake
     if(WIN32)
       set(_INSTALL_CMD nmake install)
     else()
       set(_INSTALL_CMD make install)
     endif()
     
     INSTALL_COMMAND ${_INSTALL_CMD}
     ```
   
     以管理员模式启动QtCreator，并打开`CTK/CMakeLists.txt`，构建项目。
   
     报错：
   
     1. TODO
   
   - linux
   



## CppMicroServices

TODO



## COM

TODO



## 自定义插件框架

基于pimpl与dll技术。

插件管理，版本管理。

### 延伸 - 基于微服务实现

TODO



## 总结

### 对比

| 方案            | 开源协议            | 优点                                                        | 缺点                                                         |
| --------------- | ------------------- | ----------------------------------------------------------- | ------------------------------------------------------------ |
| [x3py](#x3py)   | Apache License V2.0 | + 使用简单，容易上手。<br>+ 使用标准C++，与其它平台依赖少。 | - 文档非常少（真的少）。<br>- 项目长期未更新（最近一次更新是5年前）。<br>- 官方支持的vs版本比较低（vs2008，可以升级到vs2015）。<br>- 自定义插件后缀`.pln`的方式比较非主流。<br>- 装载的插件数量有限制（<40）。 |
| CTK             |                     | + 基于开放的OSGI协议。<br>+ 项目非常活跃。                  | - 与Qt平台深度绑定。                                         |
| CppMicroService |                     | +                                                           | -                                                            |
| COM             |                     | + 功能齐全                                                  | - 仅限于Windows平台，难以跨平台。                            |
| 自定义插件框架  |                     | + 可定制性强                                                | - 需要手动实现关于插件管理的几乎所有的功能，费事费力。       |

对各方案的加法函数（add函数，具体见示例代码）进行调用，其耗时结果如下：

| 方案            | 调用1,000,000次 | 调用10,000,000次 | 调用100,000,000次 |
| --------------- | --------------- | ---------------- | ----------------- |
| x3py            | 21ms            | 204ms            | 2104ms            |
| CTK             |                 |                  |                   |
| CppMicroService |                 |                  |                   |
| COM             |                 |                  |                   |
| 自定义插件框架  |                 |                  |                   |

- CPU：11th Gen Intel(R) Core(TM) i5-11500 @ 2.70GHz   
- 内存：16.0 GB
- 操作系统：Windows 10 专业版 19044.1645



## 参考

[] Unix环境高级编程

[] Windows核心编程

[] C++ API设计

[] [C++ 程序设计 - 插件框架分析](https://zhuanlan.zhihu.com/p/427795467)

[] [[转载]C/C++：构建你自己的插件框架](http://www.flyif.com/archives/257)

[] [有哪些成熟的C++跨平台插件管理系统实现?](https://www.zhihu.com/question/402162303)

[] [插件式可扩展架构设计心得](https://segmentfault.com/a/1190000040002834)

[] [CTK框架使用简明教程](http://www.uml.org.cn/c++/202103251.asp?artid=23787)

[] Martin Reddy, C++ API 设计, 1ED, P310-P334

