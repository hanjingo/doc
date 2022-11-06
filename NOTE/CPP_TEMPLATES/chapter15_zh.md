# 第15章 trait和policy类



## 15.1 一个实例：累加一个序列

### 15.1.1 fixed traits

```c++
#ifndef ACCUM_HPP
#define ACCUM_HPP

#include "accumutraits2.hpp"

template<typename T>
inline 
typename AccumulationTraits<T>::Acct accum(T const* beg,
                                           T const* end)
{
    // 返回值的类型是一个元素类型的trait
    typedef typename AccumulationTraits<T>::Acct Acct;
    AccT total = AccT();
    while (beg != end) {
        total += *beg;
        ++beg;
    }
    return total;
}

#endif
```

### 15.1.2 value trait

### 15.1.3 参数化trait

