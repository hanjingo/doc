# 第一章 STL介绍

[TOC]

## 1.1基本思想

* `容器库（Containers Library）` 定义管理和存储数据的容器；
* `迭代器库（Itrators Library）` 定义迭代器，迭代器类似于指针的对象，通常被用于引用容器类的对象序列；
* `算法库（Algorithms Library）` 定义一些使用比较广泛的通用算法，可以运用到容器中的一组元素；
* `数值库（Numerics Library）` 定义一些通用的数学函数和一些对容器元素进行数值处理操作；



## 1.2模板

`size_t`定义在cstddef头文件中，表示无符号整形。

`size()`在类模板中默认以内联的方式实现，所以不再需要外部定义。



## 1.3容器

* `序列容器（Sequence Containers）` 以线性组织的方式存储对象，和数组类似，但是不需要拦蓄的存储空间；
* `关联容器（Associative Containers）` 存储了一些和键关联的对象；
* `容器适配器（Container Adapters）` 提供了替换机制的适配类模板，可以用来访问基础的序列容器或关联容器。