# PBC源码分析-总结

[TOC]



## 数据类型

### 分类

- `integer`
- `string`
- `real`



## API

### 分类

- `pbc_rmessage_xxx` 编码类API
- `pbc_wmessage_xxx` 解码类API
- `pbc_pattern_xxx`   适配类API

### 常用API

| API                  | 功能                                                         |
| -------------------- | ------------------------------------------------------------ |
| pbc_rmessage_new     |                                                              |
| pbc_rmessage_delete  |                                                              |
| pbc_rmessage_integer |                                                              |
| pbc_rmessage_real    |                                                              |
| pbc_rmessage_string  |                                                              |
| pbc_rmessage_message |                                                              |
| pbc_rmessage_size    | 查询message中的field被重复了多少次；                         |
| pbc_wmessage_new     |                                                              |
| pbc_wmessage_delete  |                                                              |
| pbc_wmessage_integer | 压入负数时，记得将高位传-1，因为接口一律把传入的参数当成是无符号的整数； |
| pbc_wmessage_real    |                                                              |
| pbc_wmessage_string  |                                                              |
| pbc_wmessage_message |                                                              |
| pbc_wmessage_buffer  |                                                              |
| pbc_pattern_new      |                                                              |
| pbc_pattern_delete   |                                                              |
| pbc_pattern_pack     |                                                              |
| pbc_pattern_unpack   |                                                              |



## 架构

TODO



## 源码路径

- `alloc.h/.c` 统一管理内存分配，支持堆内分配优化
- `array.h/.c` 



## 最佳实践

1. 建议所有的 string 都在末尾加上 \0 。因为，这样在解码的时候，可以将字符串指针直接指向数据包内，而不需要额外复制一份出来。
2. Pattern API 可以得到更高的性能。更快的速度和更少的内存占用量。更重要的是，对于比较小的消息包，如果你使用得当，使用 pattern api 甚至不会触发哪怕一次堆上的内存分配操作。api 工作时的所有的临时内存都在栈上。



## 参考

### 外链

- [云风的 BLOG](https://blog.codingnow.com/)
- [pbc实现分析](https://www.zhyingkun.com/markdown/pbcanalysis/)