# 第6章 系统数据文件和信息

[TOC]



## 6.1 引言



## 6.2 口令文件

![t6_1](res/t6_1.png)

*/etc/passwd文件中的字段*

```c++
#include <pwd.h>
struct passwd *getpwuid(uid_t uid);
struct passwd *getpwnam(const char *name);
```

- `uid` 用户ID

- `name` 用户登陆名

- `返回值`

  成功：passwd指针

  失败：NULL

*获取口令文件项*

```c++
#include <pwd.h>
struct passwd *getpwent(void);
void setpwent(void);
void endpwent(void);
```

- `返回值`

  成功：passwd指针

  失败或到达文件结尾：NULL

*获得/设置/关闭 口令文件内容*

例：

```c++
TODO
```

*getpwnam函数*



## 6.3 阴影口令

