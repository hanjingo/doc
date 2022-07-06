# C++日志库

[TOC]



## log4cplus

log4cplus是一个线程安全，灵活且任意粒度的开源日志库；地址：[log4cplus](https://github.com/log4cplus/log4cplus)

### 环境搭建

#### linux

1. 产生makefile

   ```sh
   ./configure --prefix=xx -enable-threads=xx
   ```

   - `--prefix` 指定安装路径
   - `-enable-threads` 是否启用多线程
     - yes 是
     - no 否

   例：

   ```sh
   ./configure --prefix=/usr/local -enable-threads=no
   ```

2. make构建

   ```sh
   make
   ```

3. 测试

   ```sh
   make check
   ```

4. 安装

   ```sh
   make installS
   ```

#### windows

1. 使用cmake构建项目

   新建build文件夹，使用"vs2015开发人员命令提示"工具切换到build目录，执行以下命令：

   ```sh
   cmake -A x64 .. # 生成64位的库
   ```

2. 编译生成dll/lib

   使用vs打开`msvc14/log4cplus.sln`编译dll/lib

### 基本类型

| **类**   | **功能**                                                     |
| -------- | ------------------------------------------------------------ |
| Logger   | 记录日志的句柄。                                             |
| Appender | 用于指定内容输出位置（如：控制台，文件、远程服务器等）。一个Logger可添加多个Appender，从而向多个位置输出日志。 |
| Layout   | 用于指定日志输出的格式。每个Appender需要设置一个Layout       |

### 示例

#### 1.vs集成log4cplus

点击`添加`-`现有项`，添加log4cplus的静态库。

添加以下代码：

```c++
#include <log4cplus/log4cplus.h>

int main()
{
	// 初始化
	log4cplus::Initializer initializer;
	// 获得一个Logger实例，设置等级
	log4cplus::Logger logger = log4cplus::Logger::getInstance(LOG4CPLUS_TEXT("test"));
	logger.setLogLevel(log4cplus::INFO_LOG_LEVEL);

	// 控制台Appender
	log4cplus::SharedAppenderPtr console(new log4cplus::ConsoleAppender());
	// 设置Appender的名称和格式
	console->setName(LOG4CPLUS_TEXT("console"));
	console->setLayout(std::unique_ptr<log4cplus::Layout>(new log4cplus::SimpleLayout));
	// 添加Appender到Logger实例
	logger.addAppender(console);

	// 文件Appender
	log4cplus::SharedAppenderPtr file(new log4cplus::FileAppender(
		LOG4CPLUS_TEXT("D:\\test\\007.log"),
		std::ios_base::app
	));
	// 设置Appender的名称和格式
	console->setName(LOG4CPLUS_TEXT("file"));
	file->setLayout(std::unique_ptr<log4cplus::Layout>(
		new log4cplus::PatternLayout(LOG4CPLUS_TEXT("%D{%m/%d/%y %H:%M:%S,%Q} [%t] %-5p %c - %m [%l]%n"))
	));
	// 添加Appender到Logger实例
	logger.addAppender(file);

	// 网络Appender
	log4cplus::SharedAppenderPtr net(new log4cplus::SocketAppender(LOG4CPLUS_TEXT("localhost"), 10086, LOG4CPLUS_TEXT("name")));
	// 设置Appender的名称和格式
	net->setName(LOG4CPLUS_TEXT("net"));
	// 添加Appender到Logger实例
	logger.addAppender(net);

	// 测试
	LOG4CPLUS_INFO(logger, LOG4CPLUS_TEXT("hello world"));
	system("pause");
}
```



## 参考

[1] [log4cplus之基本使用方法及示例](https://blog.csdn.net/u014695839/article/details/84937769)

[2] [Log4cplus使用指南](https://www.cnblogs.com/keepsimple/archive/2013/05/10/3071309.html)