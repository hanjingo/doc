[TOC]

# 整数集合-intset

## API

| 函数          | 作用                           | 时间复杂度                                                   |
| ------------- | ------------------------------ | ------------------------------------------------------------ |
| intsetNew     | 创建一个新的压缩列表           | $O(1)$                                                       |
| intsetAdd     | 将给定元素添加到整数集合里面   | $O(N)$                                                       |
| intsetRemove  | 从整数集合中移除给定元素       | $O(N)$                                                       |
| intsetFind    | 检查给定值是否存在于集合       | 因为底层数组有序，查找可以通过二分查找法来进行，所以复杂度为$O(logN)$ |
| intsetRandom  | 从整数集合中随机返回一个元素   | $O(1)$                                                       |
| intsetGet     | 取出底层数组在给定索引上的元素 | $O(1)$                                                       |
| intsetLen     | 返回整数集合包含的元素个数     | $O(1)$                                                       |
| intsetBlobLen | 返回整数集合占用的内存字节数   | $O(1)$                                                       |



## 定义

### 整数集合

```c
// 整数集合
typedef struct intset {
    uint32_t encoding; // 编码方式 INTSET_ENC_INT16,INTSET_ENC_INT32,INTSET_ENC_INT64
    uint32_t length;   // 集合包含的元素数量，contents的长度
    int8_t contents[]; // 保存元素的数组，从小到大排序，不包含重复项(item不一定为int8_t，取决于编码方式)
} intset;
```

### 编码方式

```c
#define INTSET_ENC_INT16 (sizeof(int16_t)) // 编码方式int16_t，[-32768, 32767]
#define INTSET_ENC_INT32 (sizeof(int32_t)) // 编码方式int32_t，[-2147483648, 2147483647]
#define INTSET_ENC_INT64 (sizeof(int64_t)) // 编码方式int64_t，[-9223372036854775808，9223372036854775807]
```

