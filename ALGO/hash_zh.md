中文版 | [English](hash.md)

# HASH算法

[TOC]




## HASH函数

`散列函数（hash function）` 将键映射到散列表中的适当单元（理想情况下它应该运算简单并且应该保证任何两个不同键映射到不同的单元）。

### 示例

```c++
// 一个好的散列函数
int hash(const string& key, int tableSize)
{
    int hashVal = 0;

    for (int i = 0; i < key.length(); i++)
        hashVal = 37 * hashVal + key[i];

    hashVal %= tableSize;
    if (hashVal < 0)
        hashVal += tableSize;

    return hashVal;
}
```



## HASH碰撞

### 线性探测

`线性探测（Linear probing）`：插入时，如果检测到有冲突，即向左/右移动一位再次检测冲突。

通过使用积分计算插入时间平均值的方法来估计平均值，得到：$I(\lambda) = \frac{1}{\lambda} \int^{\lambda}_{0} \frac{1}{1-x} dx = \frac{1}{\lambda} ln \frac{1}{1-\lambda}$

![linear_probing](res/linear_probing.png)

*对线性探测（虚线）和随机方法的装填因子画出的探测次数（S为成功查找，U为不成功查找，而I为插入）*

例:

| 0    | 1    | 2    | 3    | 4    | 5    | 6    | 7    | 8    | 9    |
| ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- |
| 49   | 18   | 29   |      |      |      |      |      | 38   | 79   |

```mermaid
graph LR
a(插入到0)-->b{是否冲突}
b-.是.->c(插入到1)-->b
b-.是.->e(插入到2)-->b
b-.是.->f(插入到3)-->b
b-.否.->d(结束)
```

### 二次探测

`二次探测/平方探测`：插入时发生碰撞向左/右移动$H+1^2$,$H+2^2$,$H+3^2$..个位置。

**定理5-1** 如果使用平方探测，且表的大小是素数，那么当表至少有一半是空的时候，总能够插入一个新的元素。

**证明** 令表的大小`TableSize`是一个大于3的（奇）素数。我们证明，前$\lceil TableSize/2 \rceil$个备选位置（包括初始位置$h_0(x)$）是互异的。其中的两个位置是$h(x) + i^2 (mod TableSize)$和$h(x) + j^2 (mod\ TableSize)$，其中$0 \leqslant i, j \leqslant \lfloor TableSize/2 \rfloor$。为推出矛盾，假设这两个位置相同，但$i \neq j$。有

$h(x) + i^2 = h(x) + j^2\ (mod\ TableSize)$

$i^2 = j^2\ (mod\ TableSize)$

$i^2 - j^2 = 0\ (mod\ TableSize)$

$(i-j)(i+j)=0 (mod TableSize)$

例：

| 0    | 1    | 2    | 3    | 4    | 5    | 6    | 7    | 8    | 9    |
| ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- |
| 49   | 18   | 29   |      |      |      |      |      | 38   | 79   |

```mermaid
graph LR
a(插入到0)-->b{是否冲突}
b-.是.->c(插入到1)-->b
b-.是.->e(插入到4)-->b
b-.否.->d(结束)
```

### 分离链接法

`分离链接法（separate chaining）` 将散列到同一个值的所有元素保留到一个链表中。

插入时发生碰撞，把发生碰撞的值存到链表中

例：

| 0    | 1    | 2    | 3    | 4    | 5    | 6    | 7    | 8    | 9    |
| ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- |
| 链表 | 链表 | 链表 |      |      |      |      |      | 链表 | 链表 |
| 49   | 18   | 29   |      |      |      |      |      | 38   | 79   |
|      |      |      |      |      |      |      |      |      |      |

插入 32到1，与18发生冲突

| 0    | 1    | 2    | 3    | 4    | 5    | 6    | 7    | 8    | 9    |
| ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- |
| 链表 | 链表 | 链表 |      |      |      |      |      | 链表 | 链表 |
| 49   | 18   | 29   |      |      |      |      |      | 38   | 79   |
|      | 32   |      |      |      |      |      |      |      |      |



## MurmurHash算法

**MurmurHash算法**，由Austin Appleby在2008年发明；目前(2021年)一共有`MurmurHash1`，`MurmurHash2`，`MurmurHash3`三个版本；与其他hash函数相比，对于规律性较强的key，MurMurHash的随机分布特征表现更良好，Redis，Memcached，Cassandra，HBase，Lucene中都使用到了这种hash算法。

### 原理

以下源码参考自[smasher](https://github.com/aappleby/smhasher)

x86平台32位:

```c++
void MurmurHash3_x86_32 ( const void * key, int len,
                          uint32_t seed, void * out )
{
  const uint8_t * data = (const uint8_t*)key;
  const int nblocks = len / 4;

  uint32_t h1 = seed;

  const uint32_t c1 = 0xcc9e2d51;
  const uint32_t c2 = 0x1b873593;

  //----------
  // body

  const uint32_t * blocks = (const uint32_t *)(data + nblocks*4);

  for(int i = -nblocks; i; i++)
  {
    uint32_t k1 = getblock32(blocks,i);

    k1 *= c1;
    k1 = ROTL32(k1,15);
    k1 *= c2;
    
    h1 ^= k1;
    h1 = ROTL32(h1,13); 
    h1 = h1*5+0xe6546b64;
  }

  //----------
  // tail

  const uint8_t * tail = (const uint8_t*)(data + nblocks*4);

  uint32_t k1 = 0;

  switch(len & 3)
  {
  case 3: k1 ^= tail[2] << 16;
  case 2: k1 ^= tail[1] << 8;
  case 1: k1 ^= tail[0];
          k1 *= c1; k1 = ROTL32(k1,15); k1 *= c2; h1 ^= k1;
  };

  //----------
  // finalization

  h1 ^= len;

  h1 = fmix32(h1);

  *(uint32_t*)out = h1;
}
```

x64平台128位:

```c++
void MurmurHash3_x64_128 ( const void * key, const int len,
                           const uint32_t seed, void * out )
{
  const uint8_t * data = (const uint8_t*)key;
  const int nblocks = len / 16;

  uint64_t h1 = seed;
  uint64_t h2 = seed;

  const uint64_t c1 = BIG_CONSTANT(0x87c37b91114253d5);
  const uint64_t c2 = BIG_CONSTANT(0x4cf5ad432745937f);

  //----------
  // body

  const uint64_t * blocks = (const uint64_t *)(data);

  for(int i = 0; i < nblocks; i++)
  {
    uint64_t k1 = getblock64(blocks,i*2+0);
    uint64_t k2 = getblock64(blocks,i*2+1);

    k1 *= c1; k1  = ROTL64(k1,31); k1 *= c2; h1 ^= k1;

    h1 = ROTL64(h1,27); h1 += h2; h1 = h1*5+0x52dce729;

    k2 *= c2; k2  = ROTL64(k2,33); k2 *= c1; h2 ^= k2;

    h2 = ROTL64(h2,31); h2 += h1; h2 = h2*5+0x38495ab5;
  }

  //----------
  // tail

  const uint8_t * tail = (const uint8_t*)(data + nblocks*16);

  uint64_t k1 = 0;
  uint64_t k2 = 0;

  switch(len & 15)
  {
  case 15: k2 ^= ((uint64_t)tail[14]) << 48;
  case 14: k2 ^= ((uint64_t)tail[13]) << 40;
  case 13: k2 ^= ((uint64_t)tail[12]) << 32;
  case 12: k2 ^= ((uint64_t)tail[11]) << 24;
  case 11: k2 ^= ((uint64_t)tail[10]) << 16;
  case 10: k2 ^= ((uint64_t)tail[ 9]) << 8;
  case  9: k2 ^= ((uint64_t)tail[ 8]) << 0;
           k2 *= c2; k2  = ROTL64(k2,33); k2 *= c1; h2 ^= k2;

  case  8: k1 ^= ((uint64_t)tail[ 7]) << 56;
  case  7: k1 ^= ((uint64_t)tail[ 6]) << 48;
  case  6: k1 ^= ((uint64_t)tail[ 5]) << 40;
  case  5: k1 ^= ((uint64_t)tail[ 4]) << 32;
  case  4: k1 ^= ((uint64_t)tail[ 3]) << 24;
  case  3: k1 ^= ((uint64_t)tail[ 2]) << 16;
  case  2: k1 ^= ((uint64_t)tail[ 1]) << 8;
  case  1: k1 ^= ((uint64_t)tail[ 0]) << 0;
           k1 *= c1; k1  = ROTL64(k1,31); k1 *= c2; h1 ^= k1;
  };

  //----------
  // finalization

  h1 ^= len; h2 ^= len;

  h1 += h2;
  h2 += h1;

  h1 = fmix64(h1);
  h2 = fmix64(h2);

  h1 += h2;
  h2 += h1;

  ((uint64_t*)out)[0] = h1;
  ((uint64_t*)out)[1] = h2;
}
```



## 参考

[1] [MurmurHash3_最详细的介绍](https://blog.csdn.net/freda1997/article/details/105199265)
