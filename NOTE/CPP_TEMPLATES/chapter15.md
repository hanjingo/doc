# Chapter 15. Traits and Policy Classes



Policy classes and traits (or traits templates) are C++ programming devices that greatly facilitate the management of the sort of extra parameters that come up in the design of industrial-strength templates. In this chapter we show a number of situations in which they prove useful and demonstrate various techniques that will enable you to write robust and powerful devices of your own.

## 15.1 An Example: Accumulating a Sequence

### 15.1.1 Fixed Traits

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

### 15.1.2 Value Traits

This is the key of the traits concept: Traits provide an avenue to configure concrete elements (mostly types) for generic computations.

### 15.1.3 Parameterized Traits



## Glossary

<div style="width: 50%; float:left;">decouple `/diː'kʌpl/` 分离，拆散</div>
<div style="width: 50%; float:left;">summed `/sʌmd/` 总计的，总数的</div>
<div style="width: 50%; float:left;">omit `/ə'mɪt/` 省略，遗漏，忘记，删去</div>
<div style="width: 50%; float:left;">bonnet `/'bɒnɪt/` 软帽，引擎罩，壁炉罩</div>
<div style="width: 50%; float:left;">revision `/rɪ'vɪʒn/` 修订本，校订，修正，复习</div>
<div style="width: 50%; float:left;">revise `/rɪ'vaɪz/` 校订，修正，校正</div>
<div style="width: 50%; float:left;">circumvent `/ˌsɜːkəm'vent/` 绕行，避开，围住</div>
<div style="width: 50%; float:left;"></div>
<div style="width: 50%; float:left;"></div>
<div style="width: 50%; float:left;"></div>
<div style="width: 50%; float:left;"></div>
<div style="width: 50%; float:left;"></div>
<div style="width: 50%; float:left;"></div>
<div style="width: 50%; float:left;"></div>
<div style="width: 50%; float:left;"></div>
<div style="width: 50%; float:left;"></div>
<div style="width: 50%; float:left;"></div>
<div style="width: 50%; float:left;"></div>
<div style="width: 50%; float:left;"></div>
<div style="width: 50%; float:left;"></div>
<div style="width: 50%; float:left;"></div>
<div style="width: 50%; float:left;"></div>
<div style="width: 50%; float:left;"></div>
<div style="width: 50%; float:left;"></div>
<div style="width: 50%; float:left;"></div>
<div style="width: 50%; float:left;"></div>
<div style="width: 50%; float:left;"></div>
<div style="width: 50%; float:left;"></div>
<div style="width: 50%; float:left;"></div>
<div style="width: 50%; float:left;"></div>
<div style="width: 50%; float:left;"></div>
<div style="width: 50%; float:left;"></div>
<div style="width: 50%; float:left;"></div>
<div style="width: 50%; float:left;"></div>
<div style="width: 50%; float:left;"></div>
<div style="width: 50%; float:left;"></div>
<div style="width: 50%; float:left;"></div>
<div style="width: 50%; float:left;"></div>
<div style="width: 50%; float:left;"></div>
<div style="width: 50%; float:left;"></div>
<div style="width: 50%; float:left;"></div>