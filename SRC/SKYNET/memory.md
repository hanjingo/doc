# skynet内存分配



## 前提
### `malloc`，`calloc`，`realloc`的区别

- `malloc`需要手动计算需要分配的空间大小，分配后不做初始化
-  `calloc`不需要手动计算，分配后初始化为0
- `realloc`重新分配已申请的空间，用来缩/扩容

### ssize_t和size_t的区别

- ssize_t 有符号
- size_t 无符号



## jemalloc



## 参考

