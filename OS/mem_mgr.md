[TOC]

# 内存管理函数



## malloc

```c
int* p = (int*)malloc(sizeof(int));
```

从堆里面获得空间，实际占用的内存比申请的大，超出的空间用来记录对这块内存的管理信息。



## free

```c
free(p);
```

释放空间时，先读取内存的管理信息，得到内存的实际大小，再释放它。



## new

```c++
int* p = new int(1);
```

流程：`operator new()->malloc()->constructor function->ptr`



## delete

```c++
delete p;
```

流程：`destructor function->operator delete()->free()`



## malloc/free与new/delete的区别

1. malloc开辟空间类型大小需要手动计算，new由编译器自己计算
2. malloc返回`void*`，需要强转为对应类型指针；new直接返回对应类型指针
3. free和delete都不需要指定空间大小