# 第5章 Posix消息队列



## 5.1 概述

![5_1](res/5_1.png)



## 5.2 mq_open, mq_close和mq_unlink函数

```c++
#include <mqueue.h>
mqd_t mq_open(const char *name, int oflag, ...);
```

- `name` 消息队列名

- `oflag` 标记，由`O_RDONLY, O_WRONLY或O_RDWR`按位组合。

- `返回值`

  成功：消息队列描述符

  失败：-1

*创建一个新的消息队列或打开一个已存在的消息队列*

```c++
#include <mqueue.h>
int mq_close(mqd_t mqdes);
```

- `mqdes` 消息队列描述符

- `返回值`

  成功：0

  失败：-1

关闭消息队列。

```c++
#include <mqueue.h>
int mq_unlink(const char *name);
```

- `name` 消息队列名

- `返回值`

  成功：0

  失败：-1

解绑消息队列（引用计数-1）。

### 5.2.1 例子：mqcreatel程序

```c++
TODO
```

*指定排他性创建标志，创建一个消息队列*

### 5.2.2 例子：mqunlink程序

```c++
TODO
```

*mq_unlink一个消息队列*



## 5.3 mq_getattr和mq_setattr函数

```c++
struct mq_attr {
    long mq_flags;
    long mq_maxmsg;
    long mq_msgsize;
    long mq_curmsgs;
};
```

```c++
#include <mqueue.h>
int mq_getattr(mqd_t mqdes, struct mq_attr *attr);
```

- `mqdes` 消息队列标识

- `attr` 返回属性

- `返回值`

  成功：0

  失败：-1

返回消息队列属性。

```c++
#include <mqueue.h>
int mq_setattr(mqd_t mqdes, const struct mq_attr *attr, struct mq_attr *oattr);
```

- `mqdes` 消息队列标识

- `attr` 

- `oattr`

- `返回值`

  成功：0

  失败：-1

设置消息队列属性。