# 第三章 迭代器(iterators)概念与traits编程技法

[返回目录](README.md)

- [迭代器设计思维_STL关键所在](#迭代器设计思维_STL关键所在)
- [迭代器iterator是一种smart_pointer](#迭代器iterator是一种smart_pointer)
- [迭代器相应型别associated_types](#迭代器相应型别associated_types)
- [Traits编程技法](#Traits编程技法)
  - [模板偏特化template_partial_specialization](#模板偏特化template_partial_specialization)
  - [迭代器相应型别之一value_type](#迭代器相应型别之一value_type)
  - [迭代器相应型别之二difference_type](迭代器相应型别之二difference_type)
  - [迭代器相应型别之三reference_type](#迭代器相应型别之三reference_type)
  - [迭代器相应型别之四pointer_type](#迭代器相应型别之四pointer_type)
  - [迭代器相应型别之五iterator_category](#迭代器相应型别之五iterator_category)
- [std::iterator的保证](#std::iterator的保证)
- [总结](#总结)



## 迭代器设计思维_STL关键所在

迭代器：扮演容器与算法之间的桥梁，是所谓的 “泛型指针”，共有五种类型，以及其它衍生变化。从实现的角度来看，迭代器是一种将 `operator*`，`operator->`，`operator++`，`operator--` 等指针相关操作予以重载的 class template。 所有 STL 容器都附带有自己专属的迭代器。 native pointer 也是一种迭代器。



## 迭代器iterator是一种smart_pointer

迭代器是一种行为类似指针的对象，而指针的各种行为中最常见的用途是 dereference 和 member access。迭代器最重要的就是对 `operator*` 和 `operator->`进行重载工作。

auto_ptr：用来包装原生指针(native pointer)的对象，在头文件 中定义。

为什么每一种 STL 容器都提供有专属迭代器的缘故。

主要是暴露太多细节，所以把迭代器的开发工作交给容器去完成，这样所有实现细节可以得到封装，不被使用者看到。



## 迭代器相应型别associated_types

迭代器所指对象的类型。

利用 function template 的参数推导机制，只能推导出参数的类型，无法推导出函数返回值类型。

迭代器常用类型有五种：

- value type
- difference type
- pointer
- reference
- iterator category



## Traits编程技法

### 模板偏特化template_partial_specialization

traits 意为 “特性”，扮演 “特性萃取机” 角色，萃取各个迭代器的特性(相应类型)。

template partial specialization 模板偏特化：针对 template 参数更进一步的条件限制所设计出来的一个特化版本，本身仍然是 template。

```cpp
template <class I>
struct iterator_traits {
  typedef typename I::iterator_category	iterator_category;
  typedef typename I::value_type	value_type;
  typedef typename I::difference_type	difference_type;
  typedef typename I::pointer	pointer;
  typedef typename I::reference	reference;
};
```

### 迭代器相应型别之一value_type

迭代器所指对象的类型

### 迭代器相应型别之二difference_type

用来表示两个迭代器之间的距离

```c++
template <class I, class T>
// 这一整行是函数返回类型
typename iterator_traits<I>::difference_type 
count(I first, I last, const T& value) {
  typename iterator_traits<I>::difference_type n = 0;
  for (; first != last; ++first)
    if (*first == value)
      ++n;
  return n;
}
```

### 迭代器相应型别之三reference_type

在c++中，函数如果要传回左值，都是以by reference的方式进行，所以如果p是一个迭代器，他的value type是T，那么`*p`应该是T&(即reference type)

### 迭代器相应型别之四pointer_type

指向迭代器所指对象的指针

```c++
Item* operator->() const { return ptr; }
Iter& operator*() const { return *ptr; }
```

### 迭代器相应型别之五iterator_category

根据移动特性与施星操作，迭代器被分为五类：

- 输入迭代器（Input Iterator） 能从所指向元素读取的迭代器(Iterator)。仅保证单趟算法的合法性。
- 输出迭代器（Output Iterator）能写入所指元素的迭代器。
- 向前迭代器（Forward Iterator）能从所指元素读取数据的迭代器。
- 双向迭代器（Bidirectional Iterator）能啥UN个向移动（即自增与自减）的向前迭代器。
- 随机访问迭代器（Random Access Iterator）能在常数时间内移动到指向任何元素的双向迭代器。

迭代器的分类与从属关系

```sh
Input Iterator--->Forward Iterator->Bidirectional Iterator->Random Access Iterator
Output Iterator--->Forward Iterator...
```



## std::iterator的保证

为了符合规范，任何迭代器都应该提供五个内嵌相应型别，以利于traits萃取。

STL提供了一个iterators class，如果每个新设计的迭代器都继承自它，即可满足规范：

```c++
template <class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
struct iterator {
  typedef Category	iterator_category;
  typedef T	value_type;
  typedef Distance	difference_type;
  typedef Pointer	pointer;
  typedef Reference	reference;
};
```



## 总结

traits 本质是什么？  

多一层间接性，换来灵活性。

iterator_traits 负责萃取迭代器的特性，__type_traits 负责萃取类型的特性。



