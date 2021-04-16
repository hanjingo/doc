# 第一章 STL概论

[返回目录](README.md)

- [stl六大组件](#stl六大组件)



## stl六大组件

1. 容器（containers）:各种数据结构，如vector, list, deque, set, map, 用来存放数据。
2. 算法（algorithm）:各种常用算法如sort, search, copy, erase...。
3. 迭代器（iterators）:扮演容器与算法之间的胶着剂，共有5中类型。
4. 仿函数（functors）:行为类似函式，可作为算法的某种策略(policy)。
5. 适配器（adapters）:用来修饰容器(containers)或仿函数(functors)或迭代器(iterators)接口的东西。
6. 配置器（allocators）:负责空间配置与管理，配置器是一个实现了动态空间配置，空间管理，空间释放的class template。