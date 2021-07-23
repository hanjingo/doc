[TOC]

# `std::move`和`std::forward`



## `std::move`

`std::move`实施的是无条件的向右值型别的强制型别转换。把对象的所有权从一个对象转移到另一个对象，只转移所有权而没有内存移动或拷贝。

### 用途

- 避免复制入参数据成员的过程产生的复制操作成本
- 有条件的进行强制类型转换

### 实现

- c++11

```c++
template<typename T>
typename remove_reference<T>::type&& move(T&& param)
{
    using ReturnType = typename remove_reference<T>::type&&; // 别名
    
    return static_cast<ReturnType>(param);
}
```

- c++14

```c++
template<typename T>
decltype(auto) move(T&& param)
{
    using ReturnType = remove_reference_t<T>&&;
    
    return static_cast<ReturnType>(param);
}
```



## `std::forward`

仅当传入的实参被绑定到右值时，`std::forward`才针对该实参实施向右值型别的强制型别转换。
