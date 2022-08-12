# 第20章 数据库函数库

[TOC]



## 20.1 引言



## 20.2 历史

![t20_1](res/t20_1.png)

*多种平台支持的数据库函数库*



## 20.3 函数库

```c++
#include "apue_db.h"
DBHANDLE db_open(const char *pathname, int oflag, ...);
```

- `pathname` 数据库文件路径

- `oflag` 打开模式

- `...` 文件访问权限

- `返回值`

  成功：数据库句柄

  失败：NULL

*打开/创建数据库文件*

```c++
#include "apue_db.h"
void db_close(DBHANDLE db);
```

- `db` 数据库句柄

*关闭数据库*

```c++
#include "apue_db.h"
int db_store(DBHANDLE db, const char *key, const char *data, int flag);
```

- `db` 数据库句柄

- `key` 键

- `data` 数据

- `flag` 标志

  - DB_INSERT 加一条新纪录
  - DB_REPLACE 替换一条已有的记录
  - DB_STORE 加一条新纪录或替换一条已有记录

- `返回值`

  成功：0

  失败：非0

*向数据库添加记录*

```c++
#include "apue_db.h"
char *db_fetch(DBHANDLE db, const char *key);
```

- `db` 数据库句柄

- `key` 键

- `返回值`

  成功：指向数据的指针

  失败：NULL

*从数据库中取出一条记录*

```c++
#include "apue_hdb.h"
int db_delete(DBHANDLE db, const char *key);
```

- `db` 数据库句柄

- `key` 键

- `返回值`

  成功：0

  失败：-1

*从数据库删除一条记录*

```c++
#include "apue_db.h"
void db_rewind(DBHANDLE db);
```

- `db` 数据库句柄

- `key` 键

- `返回值`

  成功：指向数据的指针

  到达数据库结尾：NULL

*回滚到数据库的第一条记录*

```c++
#include "apue_db.h"
char *db_nextrec(DBHANDLE db, char *key);
```

- `db` 数据库句柄

- `key` 键

- `返回值`

  成功：指向数据的指针

  到达数据库结尾：NULL

*查找下一条记录*



## 20.4 实现概述

