# Redis源码分析-排序


<!-- vim-markdown-toc GFM -->

* [定义](#定义)
    - [redisSortObject](#redissortobject)
* [SORT命令的实现](#sort命令的实现)
* [ALPHA选项的实现](#alpha选项的实现)
* [ASC选项和DESC选项的实现](#asc选项和desc选项的实现)
* [BY选项的实现](#by选项的实现)
* [带有ALPHA选项的BY选项的实现](#带有alpha选项的by选项的实现)
* [LIMIT选项的实现](#limit选项的实现)
* [GET选项的实现](#get选项的实现)
* [STORE选项的实现](#store选项的实现)
* [多个选项的执行顺序](#多个选项的执行顺序)
    - [选项的执行顺序](#选项的执行顺序)
    - [选项的摆放顺序](#选项的摆放顺序)
* [参考](#参考)
    - [文献](#文献)

<!-- vim-markdown-toc -->



Redis的SORT命令可以对列表键，集合键或者有序集合键的值进行排序；



## 定义

### redisSortObject

```c
typedef struct _redisSortObject {
    robj *obj; // 被排序键的值
    union {
        double score; // 排序数字值时使用
        robj *cmpobj; // 排序带有BY选项的字符串值时使用
    } u;
} redisSortObject;
```



## SORT命令的实现

对一个包含数字值的键key进行排序的命令：

```sh
SORT <key>
```

服务器执行SORT numbers命令的步骤如下：

```mermaid

```

1. 创建一个和numbers列表长度相同的数组，该数组的每一个项都是一个`redis.h/redisSortObject`结构；
2. 遍历数组，将各个数组项的obj指针分别指向numbers列表的各个项，构成obj指针和列表项之间的一对一关系；
3. 遍历数组，将各个obj指针所指向的列表项转换成一个double类型的浮点数，并将这个浮点数保存在相应数组项的`u.score`属性里面；
4. 根据数组项`u.score`属性的值，对数组进行数字值排序，排序后的数组项按`u.score`属性的值从小到大排序；
5. 遍历数组，将各个数组项的obj指针所指向的列表项作为排序结果返回客户端；



## ALPHA选项的实现

通过使用ALPHA选项，SORT命令可以对包含字符串值的键进行排序：

```sh
SORT <key> ALPHA
```

服务器执行`SORT xx ALPHA`命令的步骤如下：

```mermaid

```

1. 创建一个`redisSortObject`结构数组，数组长度等于`xx`集合的大小；
2. 遍历数组，将各个数组项的obj指针分别指向`xx`集合的各个元素；
3. 根据obj指针所指向的集合元素，对数组进行字符串排序，排序后的数组按集合元素的字符串值从小到大排序；
4. 遍历数组，依次将数组项的obj指针所指向的元素返回给客户端；



## ASC选项和DESC选项的实现

SORT命令默认执行升序排序，使用ASC选项也可以达到相同的效果（以下2条命令等价）：

```sh
SORT <key>
SORT <key> ASC
```

使用DESC选项让SORT命令执行降序排序：

```sh
SORT <key> DESC
```



## BY选项的实现

SORT默认使用被排序键包含的元素作为排序的权重，通过使用BY选项可以指定某些域(field)来作为排序的权重：

```sh
SORT xx BY xxx
```

例：

```sh
MSET apple-price 8 banana-price 5.5 cherry-price 7
SORT fruits BY *-price
```

服务器执行`SORT xx BY xxx`命令的步骤如下：

```mermaid

```

1. 创建一个redisSortObject结构数组，数组的长度等于`xx`集合的小；
2. 遍历数组，将各个数组项的obj指针分别指向`xx`集合的各个元素；
3. 遍历数组，根据各个数组项的obj指针所指向的集合元素，以及BY选项所给定的模式`xxx`，查找相应的权重值；
4. 将各个权重键的值转换成一个double类型的浮点数，然后保存在相应数组项的`u.score`属性里面；
5. 以数组项`u.score`属性的值为权重，对数组进行排序，得到一个按`u.score`属性的值排序的数组；
6. 遍历数组，依次将数组项的obj指针所指向的集合元素返回给客户端；



## 带有ALPHA选项的BY选项的实现

BY选项默认假设权重键保存的值为数字值，如果权重键保存的是字符串值的话，那么就需要在使用BY选项的同时，配合使用ALPHA选项：

```sh
SORT xx BY xxx ALPHA
```

例：

```sh
SADD fruits "apple" "banana" "cherry"
MSET apple-id "FRUIT-25" banana-id "FRUIT-79" cherry-id "FRUIT-13"
SORT fruits BY *-id ALPHA
```

服务器执行`SORT xx BY xxx ALPHA`命令的步骤如下：

```mermaid
```

1. 创建一个`redisSortObject`结构数组，数组的长度等于fruits集合的大小；
2. 遍历数组，将各个数组项的obj指针分别指向fruits集合的各个元素；
3. 遍历数组，根据各个数组项的obj指针所指向的集合元素，以及BY选项所给定的模式`xxx`，查找相应的权重键；
4. 将各个数组项的`u.cmpobj`指针分别指向相应的权重键；
5. 以各个数组项的权重键的值为权重，对数组执行字符串排序；
6. 遍历数组，依次将数组项的obj指针所指向的集合元素返回给客户端；



## LIMIT选项的实现

LIMIT选项让SORT命令只返回其中一部分已排序的元素；LIMIT选项的格式为：

```sh
LIMIT <offset> <count>
```

- `offset` 要跳过的已排序元素数量；
- `count` 跳过给定数量的已排序元素之后，要返回的已排序元素数量；

例：

```sh
SADD alphabet a b c d e f
SORT alphabet ALPHA LIMIT 2 3
```

服务器执行`SORT xx ALPHA LIMIT m n`命令的步骤如下：

```mermaid

```

1. 创建一个`redisSortObject`结构数组，数组的长度等于`xx`集合的大小；
2. 遍历数组，将各个数组项的obj指针分别指向alphabet集合的各个元素；
3. 根据obj指针所指向的集合元素，对数组进行字符串排序；
4. 根据选项`LIMIT m n`，将指针移动到数组的索引m上面，然后依次访问`xx[m]`，`xx[m+1]`，...，`xx[n]`，并将数组项的obj指针所指向的元素返回给客户端；



## GET选项的实现

GET选项让SORT命令在对键进行排序之后，根据被排序的元素以及GET选项所指定的模式，查找并返回某些键的值；GET选项的格式为：

```sh
SORT xx ALPHA GET xxx
```

服务器执行`SORT xx ALPHA GET xxx`命令的步骤如下：

```mermaid
```

1. 创建一个`redisSortObject`结构数组，数组的长度等于xx集合的大小；
2. 遍历数组，将各个数组项的obj指针分别指向xx集合的各个元素；
3. 根据obj指针所指向的集合元素，对数组进行字符串排序；
4. 遍历数组，根据数组项obj指针所指向的集合元素，以及GET选项所给定的XXX模式，查找相应的键；
5. 遍历查找程序返回的三个键，并向客户端返回它们的值；



## STORE选项的实现

STORE选项将排序结果保存在指定的键里面，并在有需要时重用这个排序结果；STORE选项的格式为：

```sh
SORT xx ALPHA STORE xxx
```

服务器执行`SORT xx ALPHA STORE xxx`命令的步骤如下：

1. 创建一个`redisSortObject`结构数组，数组的长度等于xx集合的大小；
2. 遍历数组，将各个数组的obj指针分别指向xx集合的各个元素；
3. 根据obj指针所指向的集合元素，对数组进行字符串排序；
4. 检查xxx键是否存在，如果存在的话，删除该键；
5. 设置xxx为空白的列表键；
6. 遍历数组，将排序后的元素依次推入xxx列表的末尾；
7. 遍历数组，向客户端返回元素；



## 多个选项的执行顺序

### 选项的执行顺序

一个SORT命令的执行过程分为以下几步：

1. 排序

   命令使用ALPHA，ASC或DESC，BY这几个选项，对输入键进行排序，并得到一个排序结果集；

2. 限制排序结果集的长度

   命令使用LIMIT选项，对排序结果集的长度进行限制，只有LIMIT选项指定的元素会被保留在排序结果集中；

3. 获取外部键

   命令使用GET选项，根据排序结果集中的元素，以及GET选项指定的模式，查找并获取指定键的值，并用这些值来作为新的排序结果集；

4. 保存排序结果集

   命令使用STORE选项，将排序结果集保存到指定键上面；

5. 向客户端返回排序结果集

   命令遍历排序结果集并依次向客户端返回排序结果集中的元素；

例：

```sh
SORT <key> ALPHA DESC BY <by-pattern> LIMIT <offset> <count> GET <get-pattern> STORE <store_key>
```

执行1：

```sh
SORT <key> ALPHA DESC BY <by-pattern>
```

执行2:

```sh
LIMIT <offset> <count>
```

执行3:

```sh
GET <get-pattern>
```

执行4:

```sh
STORE <store_key>
```

### 选项的摆放顺序

调用SORT命令时，除了GET选项之外，改变选项的摆放顺序并不影响SORT命令执行这些选项的顺序；

例：

```sh
SORT <key> ALPHA DESC BY <by-pattern> LIMIT <offset> <count> GET <get-pattern> STORE <store_key>
```

等价于

```sh
SORT <key> LIMIT <offset> <count> BY <by-pattern> ALPHA GET <get-pattern> STORE <store_key> DESC
```

如果命令包含了多个GET选项，那么在调整选项的位置时，必须保证多个GET选项的摆放顺序不变，这样才可以让排序结果集保持不变；

例：

```sh
SORT <key> GET <pattern-a> GET <pattern-b> STORE <store_key>
```

与

```sh
SORT <key> STORE <store_key> GET <pattern-b> GET <pattern-a>
```

产生的排序结果集不同；



## 参考

### 文献

[1] 黄健宏.Redis设计与实现
