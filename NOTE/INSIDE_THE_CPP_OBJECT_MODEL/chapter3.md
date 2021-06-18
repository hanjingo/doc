# 第三章 Data语意学

一个空类的大小通常为1，是因为编译器为其安插了一个char，以便这个类的任意两个object能够在内存中配置独一无二的地址。

一个类的大小通常与机器和编译器有关，受以下三个因素的影响：

1. 语言本身的额外负担
2. 编译器对于特殊情况所提供的优化处理
3. Alignment的限制(对齐原则)
内存对齐使得它们能够更有效地在内存中存取，Alignment指将数值调整至某数的整数倍，一般32位机器Alignment为4bytes.

例：

```c++
class X{};                      // 1
class Y : public virtual X{};   // 8
class Z : public virtual X{};   // 8
class A : public Y, public Z{}; // 12
```

![3_1](res/3_1.png)

一个`virtual base class subobject`只会在`derived class`只存在一份实例，`class A`的大小由以下几点决定：

- 共享的虚基类X的实例，大小为1bytes；
- class Y的大小减去因配置`class X`的大小，结果是4bytes
