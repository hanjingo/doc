# 第二章 空间配置器
## 文件结构：
allocator必须定义于:< memory >  
< memory > 包含以下头文件定义:
* < stl_construct.h >: 定义全局函数construct()和destroy()，负责对象的构造和析构
* < stl_alloc.h >: 定义一，二级allocator;配置器名为alloc
* < stl_uninitialized.h >: 定义了一些全局函数用来填充和赋值大块内存数据，实现STL标准规范：
    un_initialized_copy(), un_initialized_fill(), un_initialized_fill_n()

## 空间的配置与释放: std::alloc
一二级分配机制：
* 一级allocator: __malloc_alloc_template  
allocate()直接使用malloc(), dealloc()直接使用free(),模拟c++的set_new_handler()用来处理内存不足；
* 二级allocator: __default_alloc_template  
维护16个自由链表，负责16种小型区块的次配置能以；内存池以malloc()配置而得，如果内存不足，  
转而调用第一级配置器；如果需求区块>128bytes,转而调用第一级配置器；  

## 内存基本处理工具:
1. ForwardIterator uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator result):  
first:指向输入端的起始位置； last:指向输入端的结束位置； result:指向输出端；  
如果作为输出目的地的[result, result+(last-first))范围内的每一个迭代器都指向未初始化区域，  
则uninitialized_copy()会使用copy constructor,给身为输入来源之[first, last)范围内的每一个对象产生一份复制品，放进输出范围中；

2. void uninitialized_fill(ForwardIterator first, ForwardIterator last, const T& x):  
first:指向欲初始化空间的起始位置； last:指向欲初始化空间的结束处； x:初始化值
如果[first, last)范围内的每个迭代器都指向未初始化的内存，那么uninitialized_fill()会在该范围内产生x的复制品;

3. ForwardIterator uninitialized_fill_n(ForwardIterator first, Size n, const T& x);  
first:指向欲初始化空间的起始位置； n:欲初始化空间的大小； x:初始化值
如果[first, first+n)范围内的每一个迭代器都指向未初始化的内存，那么uninitialized_fill_n()会调用copy constructor,在该范围内产生x的复制品；