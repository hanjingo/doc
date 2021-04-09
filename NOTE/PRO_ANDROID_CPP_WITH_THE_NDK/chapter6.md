# 第六章 Bionic API入门

摘要:

- [回顾标准库](#回顾标准库)
- [还有另一个C库](#还有另一个C库)
  - [二进制兼容性](#二进制兼容性)
  - [提供了什么](#提供了什么)
  - [缺什么](#缺什么)
- [内存管理](#内存管理)
  - [内存分配](#内存分配)
  - [c语言的动态内存管理](#c语言的动态内存管理)
  - [c++的动态内存管理](#c++的动态内存管理)
- [标准文件I/O](#标准文件I/O)
  - [标准流](#标准流)
  - [使用流I/O](#使用流I/O)
  - [打开流](#打开流)
  - [写入流](#写入流)
  - [流的读取](#流的读取)
  - [搜索位置](#搜索位置)
  - [错误检查](#错误检查)
  - [关闭流](#关闭流)
- [与进程交互](#与进程交互)
  - [执行shell命令](#执行shell命令)
  - [与子进程通信](#与子进程通信)
- [系统配置](#系统配置)
  - [通过名称获取系统属性值](#通过名称获取系统属性值)
  - [通过名称获取系统属性](#通过名称获取系统属性)
- [用户和组](#用户和组)
  - [获取应用程序用户和组ID](#获取应用程序用户和组ID)
  - [获取应用程序用户名](#获取应用程序用户名)
- [进程间通信](#进程间通信)
- [小结](#小结)



## 回顾标准库

java平台的标准库是Java Class Library(JCL)



## 还有另一个C库

### 二进制兼容性

Bionic不与其它C库二进制兼容。

### 提供了什么

- 内存管理
- 文件输入输出
- 字符串操作
- 数学
- 日期和时间
- 进程控制
- 信号处理
- 网络套接字
- 多线程
- 用户和组
- 系统配置
- 命名服务切换

### 缺什么

具体去ndk的c头文件查看



## 内存管理

### 内存分配

c/c++程序语言支持三种内存分配方式：

- 静态分配: 在代码中定义的每个静态和全局变量，静态分配在应用程序启动时自动发生。
- 自动分配: 在包含声明的复合语句被输入时发生；退出复合语句时所分配的内存被自动释放。
- 动态分配: 在运行时分配，内存大小和范围无法在编译期确定。

### c语言的动态内存管理

1. 用malloc进行动态内存分配

```c++
#include <stdlib.h>
int* dynamicIntArray = (int*)malloc(sizeof(int) * 16);
if (NULL == dynamicIntArray) {
  ...
} else {
  // 通过整型指针使用内存
  *dynamicIntArray = 0;
  dynamicIntArray[8] = 8;
  ...
  // 释放分配的内存
  free(dynamicIntArray);
  dynamicIntArray = NULL;
}
```

2. 用free释放动态内存

```c++
int* dynamicIntArray = (int*) malloc(sizeof(int) * 16);
// 使用分配的内存
free(dynamicIntArray);
dynamicIntArray = NULL;
```

3. 用realloc重新分配已分配的动态内存

```c++
int* newDynamicIntArray = (int*) realloc(
  dynamicIntArray, sizeof(int) * 32);
if (NULL = newDynamicIntArray) {
  ...
} else {
  // 更新内存指针
  dynamicIntArray = newDynamicIntArray;
}
```

### c++的动态内存管理

1. 多个元素的动态内存分配

```c++
int* dynamicIntArray = new int[16];
if (NULL == dynamicIntArray) {
  ...
} else {
  // 使用已分配的内存
  dynamicIntArray[8] = 8;
}
```

2. 使用delete[]释放数组动态内存

```c++
delete[] dynamicIntArray;
dynamicIntArray = 0;
```



## 标准文件I/O

标准C库提供了两种文件I/O:

- 低级I/O: 原始的I/O函数，有更完善的数据源控制等级。
- 流I/O: 更高级别的，可缓冲的I/O函数，更适合处理数据流。

### 标准流

- stdin: 应用程序标准输入流。
- stdout: 应用程序标准输出流。
- stderr: 应用程序标准错误流。

### 使用流I/O

包含标准I/O头文件以使用I/O流

```c++
#include <stdio.h>
```

### 打开流

使用 `FILE* fopen(const char* filename, const char* opentype)` 来打开文件流。

opentype标识打开流的方式:

- r: 只读打开。
- w: 只写打开。如果该文件已经存在，它会被截断，截断后文件长度为0。
- a: 以附加方式打开。保存文件内容，新输出的内容附加到文件结尾处。如果该文件不存在，将会打开一个新的文件。
- r+: 在读写模式下打开文件。
- w+: 在读写模式下打开文件。如果该文件已经存在，它会被截断，截断后文件长度为0。
- a+: 打开文件进行读取和附加。在读取时，初始文件的位置被设定在开头，而附加时被设定在文件结尾。

以只写模式打开一个流:

```c++
#include <stdio.h>
...
FILE* stream = fopen("/data/data/com.example.hellojni/test/txt", "w");
```

### 写入流

- `size_t fwrite(const void* data, size_t size, size_t count, FILE* stream)` 向流中写入数据块。

```c++
char data[] = {'h', 'e', 'l', 'l', 'o', '\n'};
size_t count = sizeof(data) / sizeof(data[0]);

// 向流中写数据
if (count != fwrite(data, sizeof(char), count, stream)) { ... }
```

- `int fputs(const char* data, FILE* stream)` 向流中写入以null结尾的字符序列。

```c++
// 向流中写字符序列
if (EOF == fputs("hello\n", stream)) { ... }
```

- `int fputc(int c, FILE* stream)` 向流中写入一个单字符或字节。

```c++
char c = 'c';
// 向流中写一个单字符
if (c != fputc(c, stream)) { ... }
```

- `int fprintf(FILE* stream, const char* format, ...)` 在给定的流中格式化并输出可变数量的参数。

>  格式参数:
>
>  - %d, %i: 将整数参数格式化为有符号十进制数
>
>  - %u: 将无符号整数格式化为无符号十进制数
>
>  - %o: 将无符号整数参数格式化为八进制
>
>  - %x: 将无符号整数参数格式化为十六进制
>
>  - %c: 将整数参数格式化为单个字符
>
>  - %f: 将双精度参数格式化为浮点数
>
>  - %e: 将双精度参数格式化为固定格式
>
>  - %s: 打印给出的NULL结尾字符数组
>
>  - %p: 打印给出的指针作为内存地址
>
>  - %%: 写入一个%字符
>
>    
>
>    向流中写带格式的数据

```c++
// 写带格式的数据
if (0 > fprintf(stream, "The %s is %d.", "number", 2)) { ... }
```

>  在以下情况下，缓冲区会自动刷新
>
> - 应用程序正常终止
>
> - 在行缓冲时写入新行
>
> - 当缓冲区已满
>
> - 当流被关闭
>
>   
>
> 也可以使用 `int fflush(FILE* stream)` 来手动刷新缓冲区

```c++
char data[] = { 'h', 'e', 'l', 'l', 'o', '\n' };
size_t count = sizeof(data) / sizeof(data[0]);
// 向流中写数据
fwrite(data, sizeof(char), count, stream);
// 刷新输出缓冲区
if (EOF == fflush(stream)) { ... }
```

 ### 流的读取

- `size_t fread(void* data, size_t size, size_t count, FILE* stream)` 从流中读取数据块。

```c++
char buffer[5];
size_t count = 4;
// 从流中读取4个字符
if (count != fread(buffer, sizeof(char), count, stream))
{
  ...
} else {
  // 以空结尾
  buffer[4] = NULL;
  // 输出缓冲区
  MY_LOG_INFO("read: %s", buffer);
}
```

- `char* fgets(char* buffer, int count, FILE* stream)` 从给定的流中读取以换行符结尾的字符序列。

```c++
char buffer[1024];
// 从流中读取换行符结尾的字符序列
if (NULL == fgets(buffer, 1024, stream))
{
  ...
} else {
  MY_LOG_INFO("read: %s", buffer);
}
```

- `int fgetc(FILE* stream)` 从流中读取单个无符号字符。

```c++
unsigned char ch;
int result;
// 从流中读取单个字符
result = fgetc(stream);
if (EOF == result)
{
  ...
} else {
  // 获取实际字符
  ch = (unsigned char) result;
}
```

- `int fscanf(FILE* stream, const char* format, ...)` 从流中读取格式数据。

>  格式参数:
>
> - %d, %i: 读取一个有符号十进制数
> - %u: 读取一个无符号十进制数
> - %o: 读取一个八进制数无符号整数
> - %x: 读取一个十六进制数无符号整数
> - %c: 读取单个字符
> - %f: 读取一个浮点数
> - %e: 读取一个固定格式的浮点数
> - %s: 扫描一个字符串
> - %%: 转义%字符

```c++
char s[5];
int i;
// 读带格式的数据
if (2 != fscanf(stream, "The %s is %d", s, &i)) { ... }
```

- `int feof(FILE* stream)` 检查文件结尾

```c++
char buffer[1024];
// 直到文件尾
while (0 == feof(stream))
{
  // 读取并输出字符串
  fgets(buffer, 1024, stream);
  MY_LOG_INFO("read: %s", buffer);
}
```

### 搜索位置

- `int fseek(FILE* stream, long offset, int whence)` 修改流中的位置。
  - stream: 流指针
  - offset: 偏移量
  - whence: 偏移量参照点
    - SEEK_SET: 偏移量相对于流的开头
    - SEEK_CUR: 偏移量相对于当前位置
    - SEEK_END: 偏移量相对于流结尾

```c++
// 写入流中
fputs("abcd", stream);
// 倒回4字节
fseek(stream, -4, SEEK_CUR);
// 用efgh重写abcd
fputs("efgh", stream);
```

### 错误检查

```c++
// 检查错误
if (0 != ferror(stream)) { ... }
```

### 关闭流

- `int fclose(FILE* stream)` 关闭流

```c++
if (0 != fclose(stream)) { ... }
```



## 与进程交互

### 执行shell命令

可以使用system函数向shell传递命令，应该先包含stdlib.h头文件

```c++
#include <stdlib.h>
int result;
// 指向shell命令
result = system("mkdir /data/data/com.example.hellojni/temp");
if (-1 == result || 127 == result) { ... }
```

### 与子进程通信

- `FILE *popen(const char* command, const char* type)` 在父进程和子进程之间打开一个双向通道。

- `int pclose(FILE* stream)` 将流关闭。

```c++
#include <stdio.h>
FILE* stream;

// 向ls命令打开一个只读通道
stream = popen("ls", "r");
if (NULL == stream)
{
  MY_LOG_ERROR("Unable to execute the command.");
}
else
{
  char buffer[1024];
  int status;
  
  // 从命令输出中读取每一行
  while (NULL != fgets(buffer, 1024, stream))
  {
    MY_LOG_INFO("read: %s", buffer);
  }
  // 关闭通道并获取其状态
  status = pclose(stream);
  MY_LOG_INFO("process exited with status %d", status);
}
```



## 系统配置

Android以简单的键-值对的方式保存系统属性。先包含系统属性头文件 `#include <sys/system_properties.h>` 来调用函数查询系统属性。

属性名不超过 `PROP_NAME_MAX` 个字符,属性值不超过 `PROP_VALUE_MAX` 个字符。

### 通过名称获取系统属性值

- `int __system_property_get(const char* name, char* value)` 根据名字查看系统属性

```c++
char value[PROP_VALUE_MAX];
// 获取product model系统属性
if (0 == __system_property_get("ro.product.model", value)) { ... }
```

### 通过名称获取系统属性

- `const prop_info* __system_property_find(const char* name)` 搜索系统属性。

- `int __system_property_read(const prop_info* pi, char* name, char* value)` 读取属性值。

```c++
const prop_info* property;
// 获取product model系统属性
property = __system_property_find("ro.product.model");
if (NULL == property)
{
  ...
} else {
  char name[PROP_NAME_MAX];
  char value[PROP_VALUE_MAX];
  // 获取系统属性名称和值
  if (0 == __system_property_read(property, name, value)) { ... }
}
```



## 用户和组

- Android在虚拟机沙箱里运行应用程序，且在系统上将它们当作不同的用户对待。通过单纯地依赖基于用户的权限模型，Android可以通过阻止应用程序访问其它应用程序的数据和内存来达到保证系统安全的目的。
- 服务和硬件资源也是通过基于用户的权限模型来保护的。每个资源都有自己的保护组。在应用程序部署的过程中，应用程序请求访问这些资源。如果应用程序不是正确的资源组成员，它就不能访问任何额外的资源。

为了使用以上函数，应该先包含头文件 `unistd.h`。

### 获取应用程序用户和组ID

每个程序的用户ID和组ID从10000开始

```c++
uid_t uid;
gid_t gid;
// 获取应用程序的用户ID
uid = getuid();
// 获取应用程序的组ID
gid = getgid();
```

### 获取应用程序用户名

每个程序的用户名以`"app_"` 开头，后接应用程序号。

```c++
char* username;
// 获取应用程序的用户名
username = getlogin();
MY_LOG_INFO("Application user name is %s", username);
```



## 进程间通信

Android应用程序通过Binder接口与系统，服务以及其它应用间进行交互。到目前为止，Bionic不提供任何可以使原生应用程序与Binder接口交互的官方API。



## 小结

