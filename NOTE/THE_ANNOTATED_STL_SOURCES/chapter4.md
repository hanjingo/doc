# 第四章 序列式容器

序列式容器分类

- vector
- list

## vector

### vector数据结构:

```c++
template <class T, class Alloc *alloc>
class vector {
...
protected:  
  iterator start;						// 表示目前使用空间的头
  iterator finish;					// 表示目前使用空间的尾
  iterator end_of_storage;	// 表示目前可用空间的尾
  ...
}
```

### vector的指针(Random Access Iterators)

支持随机存取,支持以下操作:`operator*, operator->, operator++, operator--, operator+, operator-, operator+=, operator-=`

### 扩容算法

如果空间不够，则以原空间大小的2倍开辟一块新空间，然后将原内容拷贝过来，并释放原空间。

所以，一旦引起空间重新配置，会导致迭代器失效。

### 元素操作

- pop_back

  丢掉尾部元素

- erase

  删除指定范围的元素，后面的元素全部前移

  ![](res/vector_erase.jpg)

- clear

  删除某个位置的元素，后面的元素全部前移

- insert

  插入元素

  1. 备用空间 > 新增元素个数

  >  1.1. 插入点之后的现有元素个数 > 新增元素个数
  >  ![](res/vector_insert1.1.jpg)

  >  1.2. 插入点之后的现有元素个数 ≤ 新增元素个数
  >  ![](res/vector_insert1.2.jpg)

  2. 备用空间 < 新增元素个数
  >  ![](res/vector_insert2.1.jpg)

### 适用场景

随机访问的情况，不适宜插入，删除等操作频繁的操作

---

## list

STL list是一个环状双向链表(double linked-list), 插入(insert)和拼接(splice)都不会造成原有list迭代器失效。

遵循STL的前闭后开原则，默认有一个node指针可以置于尾部的一个空白节点。

### list node结构

```c++
// stl_list.h
// 双向链表
struct _List_node_base {
  _List_node_base* _M_next;
  _List_node_base* _M_prev;
};
// list节点
template <class _Tp>
struct _List_node : public _List_node_base {
  _Tp _M_data;	// 节点存储的值
}
```

### list的迭代器(Bidirectional Iterators)

具备:递增，递减，取值，成员取用，前移，后移等功能

```c++
// stl_list.h
// list迭代器基类
struct _List_iterator_base {
  typedef size_t 											size_type;
  typedef ptrdiff_t 									difference_type;
  typedef bidirectional_iterator_tag 	iterator_category; // 双向移动迭代器
  
  _List_node_base* _M_node;	// 指向节点的指针
  
  _List_iterator_base(_List_node_base* __x) : _M_node(__x) {}
  _List_iterator_base() {}
  
  void _M_incr() { _M_node = _M_node->_M_next; }	// 前移
  void _M_decr() { _M_code = _M_node->_M_prev; }	// 后退
  
  bool operator==(const _List_iterator_base& __x) const {
    return _M_node == __x._M_node;
  }
  bool operator!=(const _List_iterator_base& __x) const {
    return _M_node != __x._M_node;
  }
};
```

### list本身的结构

环状链表

![](res/list_ring.jpg)

```c++
// stl_list.h
// list 基类
template <class _Tp, class _Alloc>
class _List_base
{
public:
  typedef _Alloc allocator_type;
  allocator_type get_allocator() const { return allocator_type(); }
  
  _List_base(const allocator_type&) {
    _M_node = _M_get_node();
    _M_node->_M_next = _M_node;
    _M_node->_M_prev = _M_node;
  }
  ~_List_base() {
    clear();
    _M_put_node(_M_node);
  }
  
  void clear();
  
protected:
  // 专属空间配置器，每次配置一个节点大小
  typedef simple_alloc<_List_node<_Tp>, _Alloc> _Alloc_type;
  // 配置一个节点并返回
  _List_node<_Tp>* _M_get_node() { return _Alloc_type::allocate(1); }
  //  释放一个节点
  void _M_put_node(_List_node<_Tp>* __p) { _Alloc_type::deallocate(__p, 1); }
  
protected:
  _List_node<_Tp>* _M_node;	// 只要一个指针，便可表示整个环状双向链表，空白节点
}
```

### 元素操作

- insert

  插入元素

  ```c++
  iterator insert(iterator __position, const _Tp& __x) {
    _Node* __tmp = _M_create_node(__x);
    __tmp->_M_next = __position._M_node;
    __tmp->_M_prev = __position._M_node->_M_prev;
    __position._M_node->_M_prev->_M_next = __tmp;
    __position._M_node->_M_prev = __tmp;
    return __tmp;
  }
  ```

  ![](res/list_insert.jpg)

- push_front

  插入一个节点，作为头节点

  ```c++
  void push_front(const T& x) { insert(begin(), __x); }
  ```

- push_back

  插入一个节点，作为尾节点

  ```c++
  void push_back(const T& x) { insert(end(), x); }
  ```

- erase

  移除迭代器position所指节点

  ```c++
  iterator erase(iterator __position) {
    _List_node_base* __next_node = __position._M_node->_M_next;
    _List_node_base* __prev_node = __position._M_node->_M_prev;
    _Node* __n = (_Node*) __position._M_node;
    __prev_node->_M_next = __next_node;
    __next_node->_M_prev = __prev_node;
    _Destroy(&__n->_M_data);
    _M_put_node(__n);
    return iterator((_Node*) __next_node);
  }
  ```

- pop_front

  移除头节点

  ```c++
  void pop_front() { erase(begin()); }
  ```

- pop_back

  移除尾节点

  ```c++
  void pop_back() {
    iterator __tmp = end();
    erase(--__tmp);
  }
  ```

- clear

  清除所有节点(整个链表)

  ```c++
  template <class _Tp, class _Alloc>
  void
  _List_base<_Tp, _Alloc>::clear()
  {
    _List_node<_Tp>* __cur = (_List_node<_Tp>*) _M_node->_M_next; // 头节点
    while (__cur != _M_node) {	// 遍历环链表
      _List_node<_Tp>* __tmp = __cur;
      __cur = (_List_node<_Tp>*) __cur->_M_next;
      _Destroy(&__tmp->_M_data);
      _M_put_node(__tmp);
    }
    _M_node->_M_next = _M_node;
    _M_node->_M_prev = _M_node;
  }
  ```

- remove

  将数值为value的所有元素移除

  ```c++
  template <class _Tp, class _Alloc>
  void list<_Tp, _Alloc>::remove(const _Tp& __value)
  {
    iterator __first = begin();
    iterator __last = end();
    while (__first != __last) {
      iterator __next = __first;
      ++__next;
      if (*__first == __value) erase(__first);	// 符合条件就删除
      __first = __next;
    }
  }
  ```

- unique

  移除数值相同的连续元素，保持每个元素的唯一性。

  ```c++
  template <class _Tp, class _Alloc>
  void list<_Tp, _Alloc>::unique()
  {
    iterator __first = begin();
    iterator __last = end();
    if (__first == __last) return;
    iterator __next = __first;
    while (++__next != __last) {
      if (*__first == *__next)
        erase(__next);
      else
        __first = __next;
      __next = __first;
    }
  }
  ```

- splice

  拆分list

  ```c++
  void transfer(iterator __position, iterator __first, iterator __last) {
    if (__position != __last) {
      // 从__position位置移除[first, last)
      __last._M_node->_M_prev->_M_next 			= __position._M_node;
      __first._M_node->_M_prev->_M_next 		= __last._M_node;
      __position._M_node->_M_prev->_M_next 	= __first._M_node;
      
      // 插入[first, last)到新位置
      _List_node_base* __tmp 			= __position._M_node->_M_prev;
      __position._M_node->_M_prev = __last._M_node->_M_prev;
      __last._M_node->_M_prev 		= __first._M_node->_M_prev;
      __first._M_node->_M_prev 		= __tmp;
    }
  }
  void splice(iterator __position, list&, iterator __first, iterator __last) {
    if (__first != __last)
      this->transfer(__position, __first, __last);
  }
  ```

- merge

  合并2个list

  ```c++
  template <class _Tp, class _Alloc>
  void list<_Tp, _Alloc>::merge(list<_Tp, _Alloc>& __x)
  {
    iterator __first1 = begin();
    iterator __last1 = end();
    iterator __first2 = __x.begin();
    iterator __last2 = __x.end();
    while (__first1 != __last1 && __first2 != __last2)
      if (*__first2 < *__first1) {
        iterator __next = __first2;
        transfer(__first1, __first2, ++__next);
        __first2 = __next;
      } 
    	else
        ++__first1;
    if (__first2 != __last2) transfer(__last1, __first2, __last2);
  }
  ```

- reverse

  翻转list

  ```c++
  inline void __List_base_reverse(_List_node_base* __p)
  {
    _List_node_base* __tmp = __p;
    do {
      __STD::swap(__tmp->_M_next, __tmp->_M_prev);
      __tmp = __tmp->_M_prev;
    } while (__tmp != __p);
  }
  
  template <class _Tp, class _Alloc>
  inline void list<_Tp, _Alloc>::reverse()
  {
    __List_base_reverse(this->_M_node);
  }
  ```

- sort

  对list进行排序

  list不能使用STL算法sort()，必须使用自己的sort()；因为STL算法sort()只接受RamdonAccessIterator

  ```c++
  template <class _Tp, class _Alloc>
  void list<_Tp, _Alloc>::sort()
  {
    if (_M_node->_M_next != _M_node && _M_node->_M_next->_M_next != _M_node) {
      list<_Tp, _Alloc> __carry;
      list<_Tp, _Alloc> __counter[64];
      int __file = 0;
      while (!empty()) {
        __carry.splice(__carry.begin(), *this, begin());
        int __i = 0;
        while (__i < __fill && !__counter[__i].empty()) {
          __counter[__i].merge(__carry);
          __carry.swap(__counter[__i++]);
        }
        __carry.swap(__counter[__i]);
        if (__i == __fill) ++_fill;
      }
      
      for (int __i = 1; __i < __fill; ++__i)
        __counter[__i].merge(__counter[__i-1]);
      swap(__counter[__fill-1]);
    }
  }
  ```

  