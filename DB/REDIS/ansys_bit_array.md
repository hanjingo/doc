# Redis源码分析-二进制位数组



<!-- vim-markdown-toc GFM -->

* [参考](#参考)

<!-- vim-markdown-toc -->

- `SETBIT` 为位数组指定偏移量上的二进制位设置值；
- `GETBIT` 用于获取数组指定偏移量上的二进制位的值；
- `BITCOUNT` 用于统计位数组里面值为1的二进制位的数量；



## 参考

[1] 黄健宏.Redis设计与实现
