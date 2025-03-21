# STL

[TOC]



## 智能指针

### shared_ptr

shared_ptr与scoped_ptr一样包装了new操作符在堆上分配的动态对象，但它实现的是引用计数型的智能指针，
可以被自由地拷贝和赋值，当没有代码使用它时（引用计数为0），才删除被包装过的动态分配的对象。

**构造函数**

shared_ptr有多种形式的构造函数，可以应用于各种可能的情形：

- 无参的`shared_ptr()`: 创建一个持有空指针的`shared_ptr`。

- `shared_ptr(Y * p)`: 获得指向类型T的指针p的管理权，同时将引用计数量为1，这个构造函数要求Y类型必须能够转换为T类型。

  ```c++
  shared_ptr<int> sp(new int(10));
  ```

- `shared_ptr(shared_ptr const & r)`: 从另外一个`shared_ptr`获得指针的管理权，同时引用计数加1，结果是两个`shared_ptr`共享一个指针的管理权。

- `operator=`: 赋值操作符，可以从另外一个`shared_ptr`获得指针的管理权，其行为同拷贝构造函数。

  ```c++
  shared_ptr<int> sp(new int(10));
  shared_ptr<int> sp2 = sp;
  ```

- `shared_ptr(Y * p, D d)`: 其行为类似`shared_ptr(Y * p)`，但它使用参数d指定了析构时的定制删除器，而不是简单的`delete`。

- `aliasing`: 别名构造函数是不增加引用计数的特殊用法

| 成员函数                  | 描述                                                 |
| ------------------------- | ---------------------------------------------------- |
| get                       | 返回存储的指针。                                     |
| reset                     | 替换所管理的对象。                                   |
| swap                      | 交换所管理的对象。                                   |
| owner_before              | 提供基于拥有者的共享指针排序。                       |
| operator =                | 对 `shared_ptr` 赋值。                               |
| operator *<br>operator -> | 解引用存储的指针。                                   |
| use_count                 | 返回 `shared_ptr` 所指对象的引用计数。               |
| unique                    | 检查所管理对象是否仅由当前 `shared_ptr` 的实例管理。 |

```c++
#include <memory>
#include <string>

int main()
{
    std::shared_ptr<std::string> sp1;
    std::shared_ptr<std::string> sp2{NULL};
    std::shared_ptr<std::string> sp3{new std::string};
    std::shared_ptr<std::string> sp4{new std::string, [](auto ptr){ delete ptr; }};
    std::shared_ptr<std::string> sp5{sp3};
    std::shared_ptr<std::string> sp6{sp3, new std::string};
    std::shared_ptr<std::string> sp7{std::move(sp3), new std::string};
    std::shared_ptr<std::string> sp8{std::move(new std::string)};
    std::shared_ptr<std::string> sp9{std::move(sp6)};
    
    sp1 = std::make_shared<std::string>("abc");

    std::string *ret_get = sp1.get();        // *ret_get: abc

    sp1.reset();                             // *sp1: 
    sp1.reset(new std::string("def"), 
              [](auto p){ delete p; });      // *sp1: def

    sp1.swap(sp3);                           // *sp1: , *sp3: def

    bool ret_ob = sp1.owner_before(sp3);     // ret_ob: true
    ret_ob = sp1.owner_before(std::weak_ptr<std::string>(
        std::make_shared<std::string>()));   // ret_ob: true

    std::shared_ptr<std::string> sp10 = sp3; // *sp10: def

    std::string ret_op1 = *sp3;             // ret_op1: def
    std::string ret_op2 = sp3->c_str();     // ret_op2: def

    long ret_uc = sp1.use_count();          // ret_uc: 4

    bool ret_u = sp1.unique();              // ret_u: false
}
```

### weak_ptr

| 成员函数     | 描述                                     |
| ------------ | ---------------------------------------- |
| expired      | 检查被引用的对象是否已删除。             |
| lock         | 创建管理被引用的对象的`shared_ptr`。     |
| owner_before | 提供弱指针的基于拥有者顺序。             |
| reset        | 释放被管理对象的所有权。                 |
| swap         | 交换被管理对象。                         |
| use_count    | 返回管理该对象的 `shared_ptr` 对象数量。 |

```c++
#include <memory>
#include <string>

int main()
{
    std::weak_ptr<std::string> wp1{std::make_shared<std::string>("")};
    std::weak_ptr<std::string> wp2;
    std::weak_ptr<std::string> wp3{wp1};
    std::weak_ptr<std::string> wp4(std::move(wp3));

    bool ret_exp = wp1.expired();                     // ret_exp: true

    std::shared_ptr<std::string> ret_lk = wp1.lock(); // ret_lk: 0

    bool ret_ob = wp1.owner_before(wp2);              // ret_ob: false
    ret_ob = wp1.owner_before(wp3.lock());            // ret_ob: false

    wp1.reset();

    wp1.swap(wp3);

    long ret_uc = wp1.use_count();                    // ret_uc: 0
}
```

---



## 容器

### string

TODO

### array

```c++
// GCC-4.4 /libstdc++-v3/include/tr1_impl/array
template<typename _Tp, std::size_t _Nm>
    struct array
    {
      typedef _Tp 	    			      value_type;
      // Support for zero-sized arrays mandatory.
      value_type _M_instance[_Nm ? _Nm : 1]; // array数组
    };
```

| 函数成员   | 复杂度 | 描述                                                         |
| :--------- | ------ | :----------------------------------------------------------- |
| begin      | $O(1)$ | 返回第一个元素的随机访问迭代器，若容器为空，则返回的迭代器等于end()。<br>![array_begin](res/stl/array_begin.png) |
| end        | $O(1)$ | 返回最后一个元素**下一个位置**的随机访问迭代器。<br>![array_end](res/stl/array_end.png) |
| rbegin     | $O(1)$ | 返回指向逆向 `array` 首元素的逆向迭代器。若容器为空，返回的迭代器等于`rend()`。<br>![array_rbegin](res/stl/array_rbegin.png) |
| rend       | $O(1)$ | 返回指向逆向 `array` 末元素后一元素的逆向迭代器。它对应非逆向 `array` 首元素的前一元素。此元素表现为占位符，试图访问它导致未定义行为。<br>![array_rend](res/stl/array_rend.png) |
| cbegin     | $O(1)$ | 类似于`begin`，不过返回的是const类型的迭代器。               |
| cend       | $O(1)$ | 类似于`end`，不过返回的是const类型的迭代器。                 |
| crbegin    | $O(1)$ | 类似于`rbegin`，不过返回的是const类型的迭代器。              |
| crend      | $O(1)$ | 类似于`rend`，不过返回的是const类型的迭代器。                |
| operator=  | $O(1)$ | 复制同类型容器的元素，或者用初始化列表替换现有内容。         |
| size       | $O(1)$ | 返回元素的实际数量。                                         |
| max_size   | $O(1)$ | 返回元素个数的最大值（因为array是固定大小，所以max_size()==size()）。 |
| empty      | $O(1)$ | 判断容器是否为空。                                           |
| front      | $O(1)$ | 返回第一个元素的引用，如果容器是空，其结果未定义。           |
| back       | $O(1)$ | 返回最后一个元素的引用，如果容器是空，其结果未定义。         |
| operator[] | $O(1)$ | 访问指定位置的元素（不进行边界检查）。                       |
| at         | $O(1)$ | 访问指定位置的元素（进行边界检查）。                         |
| swap       | $O(n)$ | 与另一个长度相同的容器交换元素。                             |
| data       | $O(1)$ | 返回包含元素的内部数组的指针。                               |

```c++
#include <iostream>
#include <array>
#include <experimental/array>

int main()
{
	std::array<int, 10> a1{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::array<int, 10> a2; // 创建具有10个0的array
	std::array<int, 5>  a3 = std::experimental::make_array(1, 2, 3, 4, 5);

	std::array<int, 10>::iterator ret1 = a1.begin();   // *ret1: 1

	std::array<int, 10>::iterator ret2 = a1.end();     // *ret2: 未知变量

	std::array<int, 10>::reverse_iterator ret3 =       // *ret3: 10
        a1.rbegin();

	std::array<int, 10>::reverse_iterator ret4 =       // *ret4: 未知变量
        a1.rend();

	std::array<int, 10>::const_iterator ret5 =         // *ret5: 1
        a1.cbegin();

	std::array<int, 10>::const_iterator ret6 =         // *ret6: 未知变量
        a1.cend();

	std::array<int, 10>::const_reverse_iterator ret7 = // *ret7: 10
        a1.crbegin();

	std::array<int, 10>::const_reverse_iterator ret8 = // *ret8: 未知变量
        a1.crend();

	a2 = a1;                      // a2: [1,2,3,4,5,6,7,8,9,10]

	size_t ret9 = a1.size();      // ret9: 10

	size_t ret10 = a1.max_size(); // ret10: 10

	bool ret11 = a1.empty();      // ret11: false

	int ret12 = a1.front();       // ret12: 1

	int ret13 = a1.back();        // ret13: 10

	a1[0] = 2;                    // a1: [2,2,3,4,5,6,7,8,9,10]

	a1.at(1) = 3;                 // a1: [2,3,3,4,5,6,7,8,9,10]

	a1.swap(a2);                  // a1: [1,2,3,4,5,6,7,8,9,10]

	int* ret14 = a1.data();       // ret14: [1,2,3,4,5,6,7,8,9,10]
}
```

### vector

```c++
template <class _Tp, class _Alloc>
class _Vector_base {
...
protected:
  _Tp* _M_start;          // 头指针
  _Tp* _M_finish;         // 尾指针
  _Tp* _M_end_of_storage; // 分配的存储空间的尾部
}
```

|成员函数|复杂度|说明/示意图/代码|
|:--|---|---|
|assign |$O(n)$ | 对元素赋值。 |
|at |$O(1)$ | 返回指定位置的元素的引用（进行边界检查）。 |
|back |$O(1)$ | 返回最后一个元素的引用。 |
|begin |$O(1)$ | 返回一个指向第一个元素的迭代器。<br>![vector_begin](res/stl/vector_begin.png) |
|capacity |$O(1)$ | 返回vector所能容纳的元素数量（不重新分配内存的情况下）。 |
|clear |$O(n)$ | 擦除所有元素。 |
|emplace |$O(n)$ | （C++11）构造元素，并在指定位置之前插入。 |
|emplace_back |$O(1)$ | （C++11）构造元素，并添加到容器尾部。 |
|empty |$O(1)$ | 判断容器是否为空。 |
|end |$O(1)$ | 返回指向最后一个元素的下一个位置的迭代器。<br>![vector_end](res/stl/vector_end.png) |
|erase |$O(n)$ |擦除指定范围内的元素。<br>![vector_erase](res/stl/vector_erase.png) |
|front |$O(1)$ | 返回第一个元素的引用。 |
|get_allocator |$O(1)$ | 返回容器的内存分配器。 |
|insert |$O(n)$ |插入元素：<br>+ `备用空间 > 新增元素个数 且 插入点后方元素个数 > 新增元素个数`<br>![vector_insert1](res/stl/vector_insert1.png)<br>+ `备用空间 > 新增元素个数 且 插入点后方元素个数 ≤ 新增元素个数`<br>![vector_insert2](res/stl/vector_insert2.png)<br>+ `备用空间 < 新增元素个数`<br>![vector_insert3](res/stl/vector_insert3.png) |
|max_size |$O(1)$ | 返回根据系统或库实现限制的容器可保有的元素最大数量（限制条件上限）。 |
|pop_back |$O(1)$ | 移除尾部元素。 |
|push_back |$O(1)$ | 向尾部添加元素。 |
|rbegin |$O(1)$ | 返回指向逆向`vector`首元素的逆向迭代器。它对应非逆向`vector`的末元素。若`vector`为空，则返回的迭代器等于`rend()`。<br>![vector_rbegin](res/stl/vector_rbegin.png) |
|rend |$O(1)$ | 返回指向逆向 `vector` 末元素后一元素的逆向迭代器。它对应非逆向 `vector` 首元素的前一元素。此元素表现为占位符，试图访问它导致未定义行为。<br>![vector_rend](res/stl/vector_rend.png) |
|reserve |$O(n)$ | 增加容器容量，不改变当前元素的个数。<br>![vector_reserve](res/stl/vector_reserve.png) |
|resize |$O(n)$ | 改变元素数量。 |
|shrink_to_fit |$O(n)$ | 建议（非强制性）移除未使用的容量。 |
|size |$O(1)$ | 返回元素数量。 |
|swap |$O(1)$ | 交换两个vector（其实就是交换迭代器，不会移动元素）。 |

```c++
#include <iostream>
#include <vector>

int main()
{
	std::vector<int> v1(5);          // 初始化5个元素，其值为默认值
	std::vector<int> v2{ 5 };        // 初始化1个元素，其值为5
	std::vector<int> v3(5, 1);       // 初始化5个元素，其值都为1
	std::vector<int> v4{       
        std::begin(v3), 
        std::end(v3) 
	};                               // 复制一个容器的片段来初始化
	std::vector<int> v5(
		v1.get_allocator());         // 构造拥有给定分配器 alloc 的空容器
	std::vector<int> v6{
		std::begin(v3),
		std::end(v3),
		v3.get_allocator(),
	};                               // 复制一个容器的片段并提供分配器来初始化
	std::vector<int> v7{       
        std::make_move_iterator(std::begin(v4)),
        std::make_move_iterator(std::end(v4)) 
	};                               // 移动一个容器的片段来初始化
	std::vector<int> v8(v5);         // 用另一个容器来初始化
	std::vector<int> v9(v5, 
	    v6.get_allocator());         // 用另一个容器和分配器来初始化
	std::vector<int> v10({1, 2, 3}); // 用初始化列表来初始化
	std::vector<int> v11({1, 2, 3}, 
	    v6.get_allocator());         // 用初始化列表和分配器来初始化

	v1.assign({1, 2, 3, 4, 5});          // v1: [1,2,3,4,5]

	int ret1 = v1.at(0);                 // ret1: 1

	int ret2 = v1.back();                // ret2: 5

	std::vector<int>::iterator ret3 = 
        v1.begin();                      // *ret3: 1

	size_t ret4 = v1.capacity();         // ret4: 5

	v1.clear();                          // v1: []

	std::vector<int>::iterator ret5 = 
        v1.emplace(v1.end(), 11);        // v1: [11], *ret5: 11

	v1.emplace_back(12);                 // v1: [11,12]

	bool ret6 = v1.empty();              // ret6: false

	std::vector<int>::iterator ret7 = 
        v1.end();                        // *ret7: 3

	std::vector<int>::iterator ret8 =   // v1: [12], *ret8: 12
        v1.erase(v1.begin(), v1.begin() + 1);

	int ret9 = v1.front();              // ret9: 12

	std::vector<int>::allocator_type ret10 = 
        v1.get_allocator(); // ret10.max_size(): 4611686018427387903

	std::vector<int>::iterator ret11 = 
        v1.insert(++v1.begin(), 8);     // v1: [12,8], *ret11: 8
	std::vector<int>::iterator ret12 = 
        v1.insert(++v1.begin(), v2.begin(), 
                  v2.end());           // v1: [12,5,8], *ret12: 5
	std::vector<int>::iterator ret13 = // v1: [12,5,10,10,8], *ret13: 10
        v1.insert(v1.cend() - 1, 2, 10);
	std::vector<int>::iterator ret14 = // v1: [12,5,10,10,8,1,2,3], *ret14: 1
        v1.insert(v1.end(), { 1, 2, 3 });

	size_t ret15 = v1.max_size();      // ret15: 4611686018427387903

	v1.pop_back();                     // v1: [12,5,10,10,8,1,2]

	v1.push_back(1);                   // v1: [12,5,10,10,8,1,2,1]

	std::vector<int>::reverse_iterator ret16 = 
        v1.rbegin();                   // *ret16: 1

	std::vector<int>::reverse_iterator ret17 = 
        v1.rend();                     // *ret17: 0

	v1.reserve(10);                   // v1: [12,5,10,10,8,1,2,1]

	v1.resize(3);                     // v1: [12,5,10]

	v1.shrink_to_fit();               // 调用前, v1.capacity(): 10
                                      // 调用后: v1.capacity(): 3

	size_t ret18 = v1.size();         // ret18: 3

	v1.swap(v2);                      // v1: [5], v2:[12,5,10]
}
```

### list

```c++
// 双向链表节点
struct _List_node_base {
  _List_node_base* _M_next; // 指向下个节点
  _List_node_base* _M_prev;	// 指向上个节点
};
// list节点
template <class _Tp>
struct _List_node : public _List_node_base {
  _Tp _M_data;	// 节点存储的值
}
// list 基类
template <class _Tp, class _Alloc>
class _List_base
{
...
protected:
  // 只要一个指针，便可表示整个环状双向链表，空白节点  
  _List_node<_Tp>* _M_node;	
}
```

|成员函数|复杂度|描述/示意图/代码|
|:--|:--|---|
|assign |$O(n)$ |替换容器的内容。 |
|back |$O(1)$ |返回容器中最后一个元素的引用。 |
|begin |$O(1)$ |返回指向 `list` 首元素的迭代器，若 `list` 为空，则返回的迭代器将等于`end()`。<br>![list_begin](res/stl/list_begin.png) |
|clear |$O(n)$ |从容器擦除所有元素。 |
|emplace |$O(1)$ |构造元素并在指定位置前插入，并返回插入元素的迭代器。 |
|emplace_back |$O(1)$ |构造元素并在容器尾部插入。 |
|emplace_front |$O(1)$ |构造元素并在容器头部插入。 |
|empty |$O(1)$ |检查容器是否为空。 |
|end |$O(1)$ |返回指向 `list` 末元素后一元素的迭代器，此元素表现为占位符；试图访问它导致未定义行为。<br>![list_end](res/stl/list_end.png) |
|erase |$O(n)$ |从容器擦除指定的元素/区间，并返回最后被移除元素的迭代器。 |
|front |$O(1)$ |返回容器首元素的引用，在空容器上对 `front` 的调用是未定义的。 |
|get_allocator |$O(1)$ |返回与容器关联的分配器。 |
|insert |$O(n)$ |插入元素到指定位置，返回插入位置的迭代器。<br>![list_insert](res/stl/list_insert.png) |
|max_size |$O(1)$ |返回根据系统或库实现限制的容器可保有的元素最大数量，即对于最大容器的`std::distance(begin(), end())`。 |
|merge |$O(n)$ |归并二个已排序链表为一个，链表以升序排序；操作后，第二个链表变为空。 |
|pop_back |$O(1)$ |移除容器的末元素，在空容器上调用 `pop_back` 导致未定义行为。 |
|pop_front |$O(1)$ |移除容器首元素。若容器中无元素，则行为未定义。 |
|push_back |$O(1)$ |添加一个元素到容器尾。 |
|push_front |$O(1)$ |添加一个元素到容器头。 |
|rbegin |$O(1)$ |返回指向逆向 `list` 首元素的逆向迭代器。它对应非逆向 `list` 的末元素。若 `list` 为空，则返回的迭代器等于`rend()`。<br>![list_rbegin](res/stl/list_rbegin.png) |
|remove |$O(n)$ |移除所有等于指定值的元素。 |
|remove_if |$O(n)$ |移除所有满足指定条件的元素。 |
|rend |$O(1)$ |返回指向逆向 `list` 末元素后一元素的逆向迭代器。它对应非逆向 `list` 首元素的前一元素。此元素表现为占位符，试图访问它导致未定义行为。<br>![list_rend](res/stl/list_rend.png) |
|resize |$O(n)$ |重设容器大小以容纳 `count` 个元素：<br>+ 若当前大小 > `count` ，则减小容器为其首 `count` 个元素；<br>+ 若当前大小 <  `count` ，插入`(count - 当前大小)`个默认值/指定值的元素。 |
|reverse |$O(n)$ |翻转容器中的元素。 |
|size |$O(n)$ |容器中的元素数量。 |
|sort |$O(n\ log\ n)$ |使用list自己的sort算法排序（STL的sort算法只接受`RamdonAccessIterator`），升序排序元素，保持相等元素的顺序。 |
|splice |$O(n)$ |将一个容器中的元素拆分出来，放到另一个容器（不复制或移动元素，仅移动链表节点的内部指针）。 |
|swap |$O(1)$ |交换2个容器的内容（不在单独的元素上调用任何移动、复制或交换操作）。 |
|unique |$O(n)$ |从容器移除所有*相继*的重复元素。只留下相等元素组中的第一个元素。若选择的比较器不建立等价关系则行为未定义。 |

```c++
#include <iostream>
#include <list>

int main()
{
	std::list<int> L1;                        // 创建空的容器
	std::list<int> L2{ 10 };                  // 构造包含1个元素(值为10)的容器
	std::list<int> L3(10, 1);                 // 构造包含10个元素(值为1)的容器
	std::list<int> L4{ L3 };                  // 创建L3的副本
    std::list<int> L5{ L3, 
                      L2.get_allocator() };   // 用另一个list和分配器来构造
	std::list<int> L6{ ++L3.cbegin(), 
                      --L3.cend() };          // 用一段元素来构造
    std::list<int> L7(L2.get_allocator());    // 提供分配器
    std::list<int> L8{ 
        std::make_move_iterator(L4.begin()), 
        std::make_move_iterator(L4.end())};   // 移动迭代器构造
    std::list<int> L9{
        std::make_move_iterator(L4.begin()), 
        std::make_move_iterator(L4.end()),
        L8.get_allocator()
    };                                        // 移动迭代器和提供分配器构造
    std::list<int> L10({1, 2, 3});            // 用初始化列表构造


	L1.assign(10, 1);                         // L1: [1,1,1,1,1,1,1,1,1,1]
	L1.assign(
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10});     // L1: [1,2,3,4,5,6,7,8,9,10]
	L1.assign(L3.cbegin(), L3.cend());        // L1: [1,1,1,1,1,1,1,1,1,1]

	int ret1 = L1.back();                     // ret1: 1

	std::list<int>::iterator ret2 = 
        L1.begin();                           // *ret2: 1

	L1.clear();                               // L1: []

	std::list<int>::iterator ret3 = 
        L1.emplace(L1.end(), 2);              // L1: [2], *ret3: 2

	L1.emplace_back(3);                       // L1: [2,3]

	L1.emplace_front(4);                      // L1: [4,2,3]

	bool ret4 = L1.empty();                   // ret4: false

	std::list<int>::iterator ret5 = L1.end(); // *ret5: 3

    std::list<int>::iterator ret6;
	ret6 = L1.erase(L1.begin());              // L1: [2,3], *ret6: 2
	ret6 = L1.erase(L1.begin(), L1.begin()++);// L1: [2,3], *ret6: 2

	int ret7 = L1.front();                    // ret7: 2

	std::list<int>::allocator_type ret8 = 
        L1.get_allocator();

	std::list<int>::iterator ret9;
    ret9 = L1.insert(L1.cbegin(), 1); // L1: [1,2,3], *ret9: 1
	ret9 = L1.insert(L1.cbegin(), 
                     2, 1);           // L1: [1,1,1,2,3], *ret9: 1
	ret9 = L1.insert(L1.cbegin(), 
                     { 2, 3 });       // L1: [2,3,1,1,1,2,3], *ret9: 2
	ret9 = L1.insert(L1.cbegin(), L2.begin(), 
        L2.end());                    // L1: [10,2,3,1,1,1,2,3], *ret9: 10

	size_t ret10 = L1.max_size();             // ret10: 76861433...

	L1.sort(); L2.sort(); L1.merge(L2);       // L1: [1,1,1,2,2,3,3,10,10]
                                              // L2: []

	L1.pop_back();                            // L1: [1,1,1,2,2,3,3,10]

	L1.pop_front();                           // L1: [1,1,2,2,3,3,10]

	L1.push_back(2);                          // L1: [1,1,2,2,3,3,10,2]

	L1.push_front(3);                         // L1: [3,1,1,2,2,3,3,10,2]

	std::list<int>::reverse_iterator ret11 = 
        L1.rbegin();                          // *ret10: 2

	L1.remove(1);                             // L1: [3,2,2,3,3,10,2]

	L1.remove_if([](int n) { 
        return n % 2 == 0; 
    });                                       // L1: [3,3,3]

	L1.resize(5);                             // L1: [3,3,3,0,0]
	L1.resize(7, 1);                          // L1: [3,3,3,0,0,1,1]

	L1.reverse();                             // L1: [1,1,0,0,3,3,3]

	size_t ret12 = L1.size();                 // ret12: 7

	L1.sort();                                // L1: [0,0,1,1,3,3,3]
	L1.sort(std::greater<int>());             // L1: [3,3,3,1,1,0,0]
    class my_greater { 
        public: 
        bool operator()(const int a, const int b) { return a > b; }; }; 
	L1.sort(my_greater());                    // L1: [3,3,3,1,1,0,0]

	L1.splice(L2.begin(), L1);                // L1: []
                                              // L2: [3,3,3,1,1,0,0]
	L1.splice(L1.begin(), L2, L2.begin());    // L1: [3]
                                              // L2: [3,3,1,1,0,0]        
	L1.splice(L1.begin()++, L2, L2.begin(), 
        L2.end());                            // L1: [3,3,1,1,0,0,3]
                                              // L2: []

	L1.swap(L2);                              // L1: []
                                              // L2: [3,3,1,1,0,0,3]

	L2.unique();                              // L2: [3,1,0,3]
	L2.unique(
        [](int x, int y) { 
            return x == y; 
        });                                   // L2: [3,1,0,3]
}
```

### deque

```c++
// deque迭代器
template <class _Tp, class _Ref, class _Ptr>
struct _Deque_iterator {
  typedef _Tp** _Map_pointer;

  _Tp* _M_curr;         // 指向节点的当前元素
  _Tp* _M_first;        // 指向节点的头
  _Tp* _M_last;         // 指向节点的尾部（含备用空间）
  _Map_pointer _M_node; // 指向所在的map
  ...
};

template <class _Tp, class _Alloc>
class _Deque_base {
...
protected:
  _Tp** _M_map;	        // map
  size_t _Map_map_size; // map的节点数量大小
  iterator _M_start;    // 指向第一个缓冲区的第一个元素
  iterator _M_finish;   // 指向最后一个缓冲区的最后一个元素
  ...
};
```

|成员函数|复杂度|描述/示意图/代码|
|:--|:--|---|
|assign |$O(n)$ |替换容器的内容。 |
|at |$O(1)$ |返回位于指定位置的元素的**引用**（带边界检查）。 |
|back |$O(1)$ |容器中最后一个元素的引用。 |
|begin |$O(1)$ |返回指向第一个元素的迭代器。<br>![deque_begin](res/stl/deque_begin.png) |
|cbegin |$O(1)$ |（c++11）返回指向第一个元素的const类型迭代器。<br>![deque_cbegin](res/stl/deque_cbegin.png) |
|clear |$O(n)$ |从容器擦除所有元素。 |
|crbegin |$O(1)$ |（C++11）返回指向逆向 `deque` 首元素的const类型的逆向迭代器。<br/>![deque_crbegin](res/stl/deque_crbegin.png) |
|crend |$O(1)$ |（C++11）返回指向逆向 `deque` 末元素后一元素的const类型的逆向迭代器。<br>![deque_crend](res/stl/deque_crend.png) |
|emplace |$O(n)$ |（C++11）在容器的指定位置**前**，置入元素。 |
|emplace_back |$O(1)$ |（C++11）在容器尾部置入元素。 |
|emplace_front |$O(1)$ |（C++11）在容器的头部置入元素。 |
|empty |$O(1)$ |检查容器是否无元素。 |
|end |$O(1)$ |返回指向容器末元素后一元素的迭代器。<br>![deque_end](res/stl/deque_end.png) |
|cend |$O(1)$ |（C++11）返回指向容器末元素后一元素的const类型的迭代器。<br/>![deque_cend](res/stl/deque_cend.png) |
|erase |$O(n)$ |从容器擦除指定的元素。 |
|front |$O(1)$ |返回容器首元素的**引用**。 |
|get_allocator |$O(1)$ |返回与容器关联的内存分配器。 |
|insert |$O(n)$ |插入元素到容器中的指定位置。 |
|max_size |$O(1)$ |返回容器能容纳的最大元素个数（取决于`std::numeric_limits<diference_type>::max()`的定义）。 |
|pop_back |$O(1)$ |移除容器尾部的元素。 |
|pop_front |$O(1)$ |移除头部的元素。 |
|push_back |$O(1)$ |在容器尾部加入元素。 |
|push_front |$O(1)$ |在头部加入元素。 |
|rbegin |$O(1)$ |返回指向逆向 `deque` 首元素的逆向迭代器。<br>![deque_rbegin](res/stl/deque_rbegin.png) |
|rend |$O(1)$ |返回指向逆向 `deque` 末元素后一元素的逆向迭代器。<br>![deque_rend](res/stl/deque_rend.png) |
|resize |$O(n)$ |重设容器大小以容纳指定个元素。 |
|shrink_to_fit |$O(n)$ |（C++11）移除未使用的容量（非强制性）。 |
|size |$O(1)$ |返回容器中元素的实际个数。 |
|swap |$O(1)$ |和另一个容器交换元素（不做移动，直接交换存储元素的容器地址）。 |

```c++
#include <iostream>
#include <deque>

int main()
{
    std::deque<int> d1;               // 构造空容器
    std::deque<int> d2(5);            // 构造带5个元素（默认值）的容器
    std::deque<int> d3(5, 1);         // 构造带5个元素（值为1）的容器
    std::deque<int> d4(5, 
        d2.get_allocator());          // 使用分配器构造带5个元素（默认值）的容器
    std::deque<int> d5(5, 1, 
        d3.get_allocator());          // 使用分配器构造带5个元素（值为1）的容器
    std::deque<int> d6{d3.begin(), 
        d3.end()};                    // 使用迭代器来构造容器
    std::deque<int> d7(d3);           // 使用容器的副本构造容器
    std::deque<int> d8(d3, 
        d2.get_allocator());          // 使用分配器和容器的副本构造容器
    std::deque<int> d9{1, 2, 3};      // 使用初始化列表构造容器
    std::deque<int> d10({1, 2, 3}, 
        d3.get_allocator());          // 使用初始化列表和分配器来构造容器

    d1.assign(5, 2);                  // d1: [2,2,2,2,2]
    d1.assign(d3.begin(), d3.end());  // d1: [1,1,1,1,1]
    d1.assign({1, 2, 3, 4, 5});       // d1: [1,2,3,4,5]

    int& ret1 = d1.at(1);             // ret1: 2

    int& ret2 = d1.back();            // ret2: 5

    std::deque<int>::iterator ret3 = 
        d1.begin();                   // *ret3: 1

    std::deque<int>::const_iterator ret4 = 
        d1.cbegin();                  // *ret4: 1

    d1.clear();                       // d1: []

    std::deque<int>::const_reverse_iterator ret5 = 
        d1.crbegin();                 // *ret5: 0

    std::deque<int>::const_reverse_iterator ret6 = 
        d1.crend();                   // *ret6: 0

    std::deque<int>::iterator ret7 = 
        d1.emplace(d1.begin(), 6);    // d1: [6], *ret7: 6

    d1.emplace_back(7);               // d1: [6,7]

    d1.emplace_front(8);              // d1: [8,6,7]

    bool ret8 = d1.empty();           // ret8: false

    std::deque<int>::iterator ret9 = 
        d1.end();                     // *ret9: 2

    std::deque<int>::const_iterator ret10 = 
        d1.cend();                    // *ret10: 2

    std::deque<int>::iterator ret11 = 
        d1.erase(d1.begin());         // d1: [6, 7], *ret11: 6

    int& ret12 = d1.front();          // ret12: 6

    std::deque<int>::allocator_type ret13 = d1.get_allocator();

    std::deque<int>::iterator ret14;
    ret14 = d1.insert(d1.begin(), 9); // d1: [9,6,7], *ret14: 9
    ret14 = d1.insert(d1.begin(), 2, 
        10);                          // d1: [10,10,9,6,7], *ret14: 10
    ret14 = d1.insert(d1.begin(), d3.begin(), 
        d3.begin() + 1);              // d1: [1,10,10,9,6,7], *ret14: 1 
    ret14 = d1.insert(d1.begin(), 
                      {1, 2});        // d1: [1,2,1,10,10,9,6,7], *ret14: 1

    size_t ret15 = d1.max_size();     // ret15: 4611686...

    d1.pop_back();                    // d1: [1,2,1,10,10,9,6]

    d1.pop_front();                   // d1: [2,1,10,10,9,6]

    d1.push_back(11);                 // d1: [2,1,10,10,9,6,11]

    d1.push_front(12);                // d1: [12,2,1,10,10,9,6,11]

    std::deque<int>::reverse_iterator ret16 = 
        d1.rbegin();                  // *ret16: 11

    std::deque<int>::reverse_iterator ret17 = 
        d1.rend();                    // *ret17: 0

    d1.resize(5);                     // d1: [12,2,1,10,10]
    d1.resize(7, 1);                  // d1: [12,2,1,10,10,1,1]

    d1.shrink_to_fit();               // d1: [12,2,1,10,10,1,1]

    size_t ret18 = d1.size();         // ret18: 7

    d1.swap(d3);                      // d1: [1,2,3,4,5]
                                      // d3: [12,2,1,10,10,1,1]
}
```

### set

```c++
// set & multiset底层机制为RB-tree。
// RB-tree节点
struct _Rb_tree_node_base
{  
  ...
  _Color_type _M_color;	// 节点颜色，非红即黑
  _Base_ptr _M_parent;	// 父节点
  _Base_ptr _M_left;    // 左节点（小）
  _Base_ptr _M_right;   // 右节点（大）
};

// RB-tree迭代器
struct _Rb_tree_base_iterator
{
  ...
  typedef _Rb_tree_node_base::_Base_ptr _Base_ptr;
  _Base_ptr _M_node;
}

// RB-tree
template <class _Value>
struct _Rb_tree_node : public _Rb_tree_node_base
{
  _Value _M_value_field;          // 节点的值
};

template <class _Tp, class _Alloc>
struct _Rb_tree_base
{
protected:
  _Rb_tree_node<_Tp>* _M_header; // 头节点
  ...
}

template <class _Key, class _Value, class _KeyOfValue, class _Compare, class _Alloc = __STL_DEFAULT_ALLOCATOR(_Value) >
class _Rb_tree : protected _Rb_tree_base<_Value, _Alloc> {
protected:
  size_type _M_node_count; // 节点数量
  _Compare _M_key_compare; // 节点的键比较函数
  ...
}
```

|成员函数|复杂度|描述|
|:--|:--|---|
|begin |$O(1)$ |返回指向第一个元素的迭代器。<br>![set_begin](res/stl/set_begin.png) |
|cbegin |$O(1)$ |（C++11）返回指向第一个元素的const类型的迭代器。<br/>![set_cbegin](res/stl/set_cbegin.png) |
|cend |$O(1)$ |（C++11）返回指向容器末元素后一元素的const类型的迭代器。<br/>![set_cend](res/stl/set_cend.png) |
|clear |$O(n)$ |从容器擦除所有元素。 |
|count |$O(log\ n)$ |返回某个值元素的个数（因为set不允许重复，所以返回值只可能为1或0）。 |
|crbegin |$O(1)$ |（C++11）返回指向逆向容器首元素的逆向迭代器。<br>![set_crbegin](res/stl/set_crbegin.png) |
|crend |$O(1)$ |（C++11）返回指向逆向容器末元素后一元素的逆向迭代器（即非逆向容器第一个元素的前一个位置）。<br>![set_crend](res/stl/set_crend.png) |
|emplace |$O(log\ n)$ |（C++11）置入元素到容器。 |
|emplace_hint |$O(log\ n)$ |（C++11）尽可能置入元素到指定位置之前。 |
|empty |$O(1)$ |如果容器是否为空。 |
|end |$O(1)$ |返回指向容器末元素后一元素的迭代器。<br>![set_end](res/stl/set_end.png) |
|equal_range |$O(log\ n)$ |返回容器中所有拥有给定范围的元素。 |
|erase |$O(log\ n) + O(n)$ |从容器移除指定的元素。 |
|find |$O(log\ n)$ |查找key与指定值相等的元素。 |
|get_allocator |$O(1)$ |返回与容器关联的分配器。 |
|insert |$O(log\ n)$ |如果容器中**不存在**该元素，则插入之，并返回插入元素的迭代器。 |
|lower_bound |$O(log\ n)$ |返回>=指定值的元素的迭代器。 |
|key_comp |$O(1)$ |返回用于比较元素key的函数。 |
|max_size |$O(1)$ |返回根据系统或库实现限制的容器可保有的元素最大数量（该值由`std::distance(begin(), end())`计算得出）。 |
|rbegin |$O(1)$ |返回指向逆向首元素的逆向迭代器（即，非逆向容器的最后一个元素）。<br>![set_rbegin](res/stl/set_rbegin.png) |
|rend |$O(1)$ |返回指向逆向容器末元素后一元素的逆向迭代器（即非逆向容器的第一个元素的前一位）。<br>![set_rend](res/stl/set_rend.png) |
|size |$O(1)$ |容器中的元素数量。 |
|swap |$O(1)$ |交换两个容器的所有元素（不移动元素，只交换存储元素的底层容器的指针）。 |
|upper_bound |$O(log\ n)$ |返回大于指定值的元素的迭代器。 |
|value_comp |$O(1)$ |返回用于比较元素value的函数。 |

```c++
#include <iostream>
#include <set>

int main()
{
    std::set<int> s1{1, 2, 3};              // 使用初始化列表构造
    std::set<int> s2({1, 2, 3});            // 通过初始化列表构造
    std::set<int> s3(s1.begin(), s1.end()); // 使用迭代器范围构造
    std::set<int> s4(s1.begin(), s1.end(), 
        s1.get_allocator());                // 使用迭代器范围和分配器构造
    std::set<int, std::greater<int> > s5{
        s1.begin(), s1.end() };             // 使用迭代器范围和函数对象构造
    std::set<int> s6(s1);                   // 使用另一个容器的副本构造
    std::set<int> s7(std::move(s6));        // 通过移动另一个容器来构造
    std::set<int> s8(s1.get_allocator());   // 使用分配器构造容器
    std::set<int> s9(s1, 
        s1.get_allocator());                // 使用另一个容器的副本和分配器构造
    std::set<int> s10({1, 2, 3}, 
        s2.get_allocator());                // 使用初始化列表和分配器构造

    std::set<int>::iterator ret1 = 
        s1.begin();               // s1:[1,2,3], *ret1:1

    std::set<int>::const_iterator ret2 = 
        s1.cbegin();              // s1:[1,2,3], *ret1:1

    std::set<int>::const_iterator ret3 = 
        s1.cend();                // s1:[1,2,3], *ret1:3

    s1.clear();                   // s1:[]

    s1 = s2; size_t ret4 = 
        s1.count(1);              // ret4:1

    std::set<int>::const_reverse_iterator ret5 = 
        s1.crbegin();             // *ret5:3 

    std::set<int>::const_reverse_iterator ret6 = 
        s1.crend();               // *ret6:3

    std::pair<std::set<int>::iterator, bool> ret7 = 
        s1.emplace(1);            // s1:[1,2,3]
                                  // <*ret7.first,ret7.second>:<1,false>

    std::set<int>::iterator ret8 = 
        s1.emplace_hint(
            s1.begin(), 2);       // s1:[1,2,3], *ret8:2

    bool ret9 = s1.empty();       // ret9:false

    std::set<int>::iterator ret10 = s1.end(); // *ret10: 3

    std::pair<std::set<int>::iterator, std::set<int>::iterator> ret11 = 
        s1.equal_range(1);        // <*ret11.first,*ret11.second>:<1,2>

    std::set<int>::iterator ret12;
    ret12 = s1.erase(
        s1.begin());              // s1:[2,3], *ret12:2
    ret12 = s1.erase(s1.begin(), 
        s1.end());                // s1:[], *ret12:0
    size_t ret12_1 = s2.erase(2); // s2:[1,3], ret12_1:1

    std::set<int>::iterator ret13 = 
        s1.find(1);               // *ret13:0

    std::set<int>::allocator_type ret14 = s1.get_allocator();

    std::pair<std::set<int>::iterator, bool> ret15 = 
        s1.insert(4);             // s1:[4]
                                  // <*ret15.first,ret15.second>:<4,1>
    std::set<int>::iterator ret15_1 = s1.insert(
        s1.begin(), 5);           // s1:[4,5], *ret15_1: 5
    s1.insert(s2.begin(), 
        s2.end());                // s1:[1,3,4,5]
    s1.insert({5, 6});            // s1:[1,3,4,5,6]

    std::set<int>::iterator ret16 = 
        s1.lower_bound(4);        // *ret16:4

    std::set<int>::key_compare ret17 = s1.key_comp();

    size_t ret18 = s1.max_size(); // ret18:461168...

    std::set<int>::reverse_iterator ret19 = 
        s1.rbegin();              // *ret19:6

    std::set<int>::reverse_iterator ret20 = 
        s1.rend();                // *ret20:5

    size_t ret21 = s1.size();     // ret21:5

    s1.swap(s2);                  // s1:[1,3]
                                  // s2:[1,3,4,5,6]

    std::set<int>::iterator ret22 = 
        s1.upper_bound(2);        // *ret22:3

    std::set<int>::value_compare ret22 = s1.value_comp();
}
```

### map

```c++
template <class _Key, class _Tp, class _Compare, class _Alloc>
class map {
private:
  typedef _Rb_tree<key_type, value_type, _Select1st<value_type>, key_compare, _Alloc> _Rep_type;
  _Rep_type _M_t;	// 底层实现为 RB-tree
  ...
}
```

|成员函数|复杂度|说明/示意图/代码|
|:--|:--|---|
|at|$O(log n)$|返回拥有等于`key`的关键的元素被映射值的引用，若无这种元素，则抛出`std::out_of_range`类型异常。|
|begin | $O(1)$ |返回指向首元素的迭代器。 |
|clear | $O(n)$ |删除所有元素。 |
|count | $O(log n)$ |返回指定元素出现的次数（因为map不允许重复，所以返回值只可能为0或1）。 |
|emplace | $O(log n)$ |（C++11）构造元素，如果容器中不存在该键，插入之；并返回元素的迭代器和是否插入成功bool值（用std::pair包裹）。 |
|emplace_hint | $O(1)$ |（C++11）构造元素，并插入到指定位置；并返回元素的迭代器。 |
|empty | $O(log n)$ |判断容器是否为空。 |
|end | $O(1)$ |返回指向末元素**后一位置**的迭代器，试图访问`end()`返回的值会导致未定义行为。 |
|equal_range | $O(log n)$ |返回2个迭代器（包裹在std::pair中）；一个迭代器指向的值>=参数值，另一个迭代器指向的值>参数值。 |
|erase | $O(log n)$ |擦除指定值/范围的元素，并返回删除的元素个数。 |
|find | $O(log n)$ |查找键值与指定值相等/等价的元素，返回该元素的迭代器。 |
|get_allocator | $O(1)$ |返回容器的配置器。 |
|insert | $O(log n)$ |插入元素，并返回元素的迭代器和是否插入成功bool值（用std::pair包裹）。 |
|key_comp | $O(1)$ |返回容器用来对比key的函数对象。 |
|lower_bound | $O(log n)$ |返回首个键>=给定值的元素的迭代器。 |
|max_size | $O(1)$ |返回根据系统或库实现限制的容器可保有的元素最大数量，即对于最大容器的`std::distance(begin(), end())`。 |
|operator[] | $O(log n)$ | 返回键等于指定值的元素的引用，如果不存在，先插入，再返回。 |
|rbegin | $O(1)$ |返回指向逆向 `map` 首元素的逆向迭代器。它对应非逆向 `map` 的末元素。若 `map` 为空，则返回的迭代器等于`rend()`。 |
|rend | $O(1)$ |返回指向逆向 `map` 末元素后一元素的逆向迭代器。它对应非逆向 `map` 首元素的前一元素。此元素表现为占位符，试图访问它导致未定义行为。 |
|size | $O(1)$ |返回容器中元素的个数。 |
|swap | $O(1)$ |交换2个容器的内容。 |
|upper_bound | $O(log n)$ |返回首个键>给定值的元素的迭代器。 |
|value_comp | $O(1)$ |返回容器用来对比value的函数对象。 |

```c++
#include <iostream>
#include <map>
#include <string>

int main()
{
	std::map<int, std::string> m1{ {1, "one"}, 
                                  {2, "two"} };    // 根据初始化列表构造
	std::map<int, std::string> m2{ 
        std::make_pair(1, "one"), 
        std::make_pair(2, "two")};                 // 根据初始化列表构造
	std::map<int, std::string> m3{ m1 };           // 构造一个map的副本
	std::map<int, std::string> m4{ std::begin(m1), 
                                   std::end(m1) }; // 构造指定范围的map

	std::string ret1 = m1.at(1);// ret1: one

	std::map<int, std::string>::iterator ret2 = 
        m1.begin();             // {ret2->first, ret2->second}: {1, one}

	m3.clear();                 // m3: {}

	size_t ret3 = m1.count(1);  // ret3: 1

	std::pair<std::map<int, std::string>::iterator, bool> ret4 = 
     m1.emplace(3, "three");    // {
                                //   {
                                //     (ret4.first)->first, : 3
                                //     (ret4.first)->second : three
                                //   },
                                //   ret4.second : true
                                // }

	std::map<int, std::string>::iterator ret5 = m1.emplace_hint(
        m1.begin(), 4, "four"); // {ret5->first, ret5->second}: {4, four}

	bool ret6 = m3.empty();     // ret6: true

	std::map<int, std::string>::iterator ret7 = m1.end(); // ret7: NULL

	std::pair<std::map<int, std::string>::iterator, 
        std::map<int, std::string>::iterator> ret8 =
        m1.equal_range(1);       // {
                                 //   {ret8.first->first, 
                                 //    ret8.first->second},  : {1, one}
                                 //   {ret8.second->first, 
                                 //    ret8.second->second} : {2, two}
                                 // }

	size_t ret9 = m1.erase(4);   // ret9: 1

	std::map<int, std::string>::iterator ret10 = 
        m1.find(1);              // {ret10->first, ret10->second}: {1, one}
	
	auto ret11 = m1.get_allocator();
	
	std::pair<std::map<int, std::string>::iterator, bool> ret12 = 
        m1.insert(std::make_pair(4, "four")); // m1: {
                                              //       {1,one}, 
                                              //       {2,two}, 
                                              //       {3,three}, 
                                              //       {4,four}
                                              //     }
	m2.insert(std::begin(m1), std::end(m1)); // m2: {
                                              //       {1,one}, 
                                              //       {2,two}, 
                                              //       {3,three}, 
                                              //       {4,four}
                                              //     }

	std::map<int, std::string>::key_compare ret13 = 
        m1.key_comp();            // ret13(1, 2): true

	std::map<int, std::string>::iterator ret14 = 
        m1.lower_bound(2);        // {ret14->first, ret14->second}: {2, two}

	size_t ret15 = m1.max_size(); // ret15: 25620...

	std::string ret16 = m1[1];    // ret16: one

	std::map<int, std::string>::reverse_iterator ret17 = 
        m1.rbegin();              // {ret17->first, ret17->second}: {4, four}

	std::map<int, std::string>::reverse_iterator ret18 = 
        m1.rend();                // {ret18->first, ret18->second}: {4, }

	size_t n = m1.size();         // n: 4
	
	m1.swap(m2); // m1: {{1,one}, {2,two}, {3,three}, {4,four}}
                 // m2: {{1,one}, {2,two}, {3,three}, {4,four}}

	std::map<int, std::string>::iterator ret19 = 
        m1.upper_bound(3);        // {ret19->first, ret19->second}: {4, four}

	std::map<int, std::string>::value_compare ret20 = 
        m1.value_comp();          // ret20({1, "one" }, {2, "tow"}): true
}
```

### stack

|成员函数|复杂度|描述/示意图/代码|
|:--|:--|---|
|emplace|$O(1)$|（C++11）构造元素并推入到栈顶。|
|empty |$O(1)$ |检查容器是否为空。 |
|pop |$O(1)$ |从栈顶移除元素。 |
|push |$O(1)$ |推入元素到栈顶。 |
|size | $O(1)$ |返回容器中元素数目。 |
|swap | $O(1)$ |（C++11）交换两个容器的内容。 |
|top | $O(1)$ |返回栈顶元素的引用。 |

```c++
#include <iostream>
#include <stack>
#include <list>

int main()
{
    std::list<int> values{1, 2, 3};

    std::stack<int> s1;                          // 创建容器
    std::stack<int> s2(s1);                      // 使用另一个容器来初始化
    std::stack<int, std::list<int> > s3(values); // 指定底层容器，用来初始化
    std::stack<int, std::list<int> > s4{values}; // 指定底层容器，用初始化列表来初始化
    std::stack<int, std::list<int> > s5(values, 
                        values.get_allocator()); // 指定底层容器和内存分配器来初始化
    std::stack<int, std::list<int> > s6(s3, 
                        values.get_allocator()); // 指定容器和内存分配器来初始化

    s1.emplace(4);           // s1: [4]

    bool ret1 = s1.empty();  // ret1: false

    s1.pop();                // s1: []

    s1.push(5);              // s1: [5]

    size_t ret2 = s1.size(); // ret2: 1

    s1.swap(s2);             // s1: [], s2: [5]

    int& ret3 = s1.top();    // s1: [], ret3: 未定义值
}
```

### queue

|成员函数|复杂度|描述|
|:--|:--|---|
|back |$O(1)$ |返回容器中最后一个元素的引用。 |
|emplace |$O(1)$ |（C++11）置入元素到容器尾部。 |
|empty |$O(1)$ |判断容器是否为空。 |
|front |$O(1)$ |返回第一个元素的引用。 |
|pop |$O(1)$ |移除第一个元素。 |
|push |$O(1)$ |添加元素到容器尾部。 |
|size |$O(1)$ |返回容器中元素的个数。 |
|swap |$O(1)$ |（C++11）交换两个容器的所有元素（不移动元素，只交换底层容器的指针）。 |

```c++
int main()
{
    int a[]{1, 2, 3};
    std::deque<int> values{1, 2, 3};
    std::queue<int> q1(values);                 // 使用构造容器初始化
    std::queue<int> q2(q1);                     // 复制构造初始化
    std::queue<int> q3(std::move(q2));          // 移动构造初始化
    std::queue<int> q4(values.get_allocator()); // 使用底层容器初始化
    std::queue<int> q5(values, 
        values.get_allocator());                // 使用指定的容器和内存分配器初始化
    std::queue<int> q6(std::move(values), 
        values.get_allocator());                // 移动指定的容器和内存分配器初始化
    std::queue<int> q7(q5, 
        values.get_allocator());                // 使用另一个容器和内存分配器初始化
    std::queue<int> q8(std::begin(a), 
        std::end(a));                           // 使用迭代器初始化
    std::queue<int> q9(std::begin(a), std::end(a), 
        values.get_allocator());                // 使用迭代器和内存分配器初始化
    

    int& ret1 = q1.back();  // ret1: 3

    q1.emplace(4);          // q1: [1,2,3,4]

    bool ret2 = q1.empty(); // ret2: false

    int& ret3 = q1.front(); // ret3: 1

    q1.pop();               // q1: [2,3,4]

    q1.push(5);             // q1: [2,3,4,5]

    size_t ret4 = q1.size();// ret4: 4

    q1.swap(q2);            // q1: [], q2: [2,3,4,5]
}
```

### priority queue

|成员函数|复杂度|描述|
|:--|:--|---|
|emplace|$O(log\ n)$|（C++11）置入新元素到容器。|
|empty |$O(1)$ |判断容器是否为空。 |
|pop |$O(log\ n)$ |移除第一个元素。 |
|push |$O(log\ n)$ |推入一个元素。 |
|size |$O(1)$ |返回容器中元素的个数。 |
|swap |$O(1)$ |（C++11）交换2个容器的元素。 |
|top |$O(1)$ |返回容器中第一个元素。 |

```c++
#include <iostream>
#include <queue>
#include <vector>

int main()
{
    int values[]{1, 2, 3};
    std::priority_queue<int> p1{                 // 使用迭代器初始化
        std::begin(values), std::end(values)};
    std::priority_queue<int> p2{p1};             // 使用另一个容器初始化
    std::priority_queue<int, std::vector<int>, std::greater<int> > p3 { 
        std::begin(values), std::end(values)};   // 使用迭代器和指定底层容器及比较函数初始化

    p1.emplace(4);           // p1: [4,3,2,1]

    bool ret1 = p1.empty();  // ret1: false

    p1.pop();                // p1: [3,2,1]

    p1.push(5);              // p1: [5,3,2,1]

    size_t ret2 = p1.size(); // ret2: 4

    p1.swap(p2);             // p1: [3,2,1], p2: [5,3,2,1]

    int ret3 = p1.top();     // ret3: 3
}
```

### bitset

TODO

---



## 算法

### 生成/填充

| 算法             | 复杂度   | 描述/示意图/代码                                             |
| ---------------- | -------- | ------------------------------------------------------------ |
| fill             | $O(n)$   | 将指定值保存到序列中的每一个元素。                           |
| fill_n           | $O(n)$   | 将指定值保存到序列中的前n个元素。                            |
| is_permutation   | $O(n^2)$ | 判断一个序列是否是另一个序列的一个排列。                     |
| generate         | $O(n)$   | 将指定函数生成的值保存到序列中的每一个元素。                 |
| generate_n       | $O(n)$   | 将指定函数生成的值保存到序列中的前n个元素。                  |
| next_permutation | $O(n)$   | 按字典序的升序来生成元素的下一个排列，如果下一个排列存在，返回true；否则，元素被排为序列的第一排列，返回false；<br>![algo_next_permutation](res/stl/algo_next_permutation.png) |
| prev_permutation | $O(n)$   | 按字典序的升序来生成元素的前一个排列，如果前一个排列存在，返回true；否则，元素被排为序列中的最后一个排列，返回false。 |

```c++
#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    std::vector<int> f{1, 2, 3, 4, 5};
    std::fill(f.begin(), f.end(), 2);                     // f:  [2,2,2,2,2]

    std::vector<int> fn{1, 2, 3, 4, 5};
    std::fill_n(fn.begin(), 3, 2);                        // fn: [2,2,2,4,5]

    std::vector<int> ip1{1, 2, 3, 4, 5};
    std::vector<int> ip2{3, 5, 4, 1, 2};
    std::vector<int> ip3{3, 5, 4, 1, 1};
    bool ret_ip;
    ret_ip = std::is_permutation(ip1.begin(), ip1.end(), 
                                 ip2.begin());            // ret_ip: true
    ret_ip = std::is_permutation(ip1.begin(), ip2.end(), ip2.begin(), 
                                 ip2.begin() + 3);        // ret_ip: false
    ret_ip = std::is_permutation(ip1.begin(), ip1.end(), ip2.begin(), 
        [](int n1, int n2){ return n1 < n2; });           // ret_ip: false
    ret_ip = std::is_permutation(ip1.begin(), ip1.end(), ip2.begin(), 
        ip2.begin() + 3, 
        [](int n1, int n2){
            return n1 < n2; 
        });                                               // ret_ip: false
    ret_ip = std::is_permutation(ip1.begin(), ip1.end(), 
                                 ip3.begin());            // ret_ip: false

    std::vector<int> g1{1, 2, 3, 4, 5};
    int n = 1;
    std::generate(g1.begin(), g1.end(), 
                  [&n](){ return n * 2; });               // g1: [2,2,2,2,2]

    std::vector<int> gn1{1, 2, 3, 4, 5};
    std::generate_n(gn1.begin(), gn1.size() / 2, 
                    [&n](){ return ++n; });               // gn1: [2,3,3,4,5]

    std::vector<int> np{1, 2, 3, 3, 6, 5, 4};
    bool ret_np;
    ret_np = std::next_permutation(np.begin(), np.end()); // ret_np: true
    ret_np = std::next_permutation(np.begin(), np.end(), 
        [](int n1, int n2){ return n1 < n2; });           // ret_np: true

    std::vector<int> pp{1, 2, 3, 4, 6, 5, 4};
    bool ret_pp;
    ret_pp = std::prev_permutation(pp.begin(), pp.end()); // ret_pp: true
    ret_pp = std::prev_permutation(pp.begin(), pp.end(), 
        [](int n1, int n2){ return n1 < n2; });           // ret_pp: true
}
```

### 排序

| 算法            | 复杂度               | 描述/示意图/代码                                             |
| --------------- | -------------------- | ------------------------------------------------------------ |
| is_sorted       | $O(n)$               | 判断指定范围内的元素是否以不降序的方式排列。                 |
| is_sorted_until | $O(n)$               | 判断指定范围内的元素是否有序，并返回一个指向这段元素中升序序列上边界元素的迭代器。 |
| nth_element     | $O(n)$               | 提供指定值对指定范围的元素进行分区排序，并使得指定值左边的所有元素 <= 指定值右边的所有元素；<br>![algo_nth_element](res/stl/algo_nth_element.png) |
| partial_sort    | $O(n \times log(m))$ | 对指定范围内的元素进行部分排序；<br>![algo_partial_sort](res/stl/algo_partial_sort.png) |
| sort            | $O(n \times log(n))$ | 以不降序的方式排序指定范围内的元素，不保证维持相等元素的顺序。 |
| stable_sort     | $O(n \times log(n))$ | 以不降序的方式排序指定范围内的元素。                         |

```c++
#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    std::vector<int> is1{1, 2, 3, 3, 4};
    bool ret_is;
    ret_is = std::is_sorted(is1.begin(), is1.end()); // ret_is: true
    ret_is = std::is_sorted(is1.begin(), is1.end(), 
        std::greater<>());                           // ret_is: false
    ret_is = std::is_sorted(is1.begin(), is1.end(), 
        [](int n1, int n2){ 
            return n1 < n2; 
        });                                          // ret_is: true

    std::vector<int> isu1{1, 2, 3, 3, 6, 5, 4};
    std::vector<int>::iterator ret_isu;
    ret_isu = std::is_sorted_until(isu1.begin(), 
        isu1.end());                                 // *ret_isu: 5
    ret_isu = std::is_sorted_until(isu1.begin(), isu1.end(), 
        std::greater<>());                           // *ret_isu: 2
    ret_isu = std::is_sorted_until(isu1.begin(), isu1.end(), 
        [](int n1, int n2){ return n1 < n2; });      // *ret_isu: 5

    std::vector<int> ne{4, 3, 2, 1, 5, 7, 6, 8};
    std::nth_element(ne.begin(), ne.begin() + ne.size() / 2, 
        ne.end());                                   // ne: [3,1,2,4,5,7,6,8]
    std::nth_element(ne.begin(), ne.begin() + ne.size() / 2, ne.end(), 
        std::greater<>());                           // ne: [5,8,6,7,4,3,2,1]
    std::nth_element(ne.begin(), ne.begin() + ne.size() / 2, ne.end(), 
        [](int n1, int n2){ return n1 < n2; });      // ne: [4,1,2,3,5,6,7,8]

    std::vector<int> ps1{3, 4, 2, 1, 5};
    std::partial_sort(ps1.begin(), ps1.begin() + 3, 
        ps1.end());                                  // ps1: [1,2,3,4,5]
    std::partial_sort(ps1.begin(), ps1.begin() + 3, ps1.end(), 
        [](int n1, int n2){ 
            return n1 < n2; 
        });                                          // ps1: [1,2,3,4,5]

    std::vector<int> s1{3, 4, 2, 1, 5};
    std::vector<int> s2{s1};
    std::vector<int> s3{s1};
    std::sort(s1.begin(), s1.end());                 // s1: [1,2,3,4,5]
    std::sort(s2.begin(), s2.end(), 
        [](int n1, int n2){ 
            return n1 < n2 && n2 % 2 != 0; 
        });                                          // s2: [2,3,4,1,5]
    std::sort(s3.begin(), s3.end(), 
        std::greater<>());                           // s3: [5,4,3,2,1]

    std::vector<int> ss1{3, 4, 2, 1, 5};
    std::vector<int> ss2{ss1};
    std::vector<int> ss3{ss1};
    std::stable_sort(ss1.begin(), ss1.end());        // ss1: [1,2,3,4,5]
    std::stable_sort(ss2.begin(), ss2.end(), 
        [](int n1, int n2){ 
            return n2 % 2 == 0 && n1 < n2; 
        });                                         // ss2: [3,1,2,4,5]
    std::stable_sort(ss3.begin(), ss3.end(), 
        std::greater<>());                          // ss3: [5,4,3,2,1]
}
```

### 合并

| 算法          | 复杂度               | 描述/示意图/代码                                             |
| ------------- | -------------------- | ------------------------------------------------------------ |
| inplace_merge | $O(n \times log(n))$ | 合并同一个序列中两个**连续有序**的元素序列;<br>![inplace_merge](res/stl/inplace_merge.png) |
| merge         | $O(n + m)$           | 合并两个**有序**的容器到一个新的容器；<br>![algo_merge](res/stl/algo_merge.png) |

```c++
#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    std::vector<int> v1{1, 2, 3};
    std::vector<int> v2{7, 8, 9};

    std::merge(v1.begin(), v1.end(), v2.begin(), 
               v2.end(), v1.begin());                  // v1: [1, 2, 3]

    std::vector<int> v3(6);
    std::merge(v1.begin(), v1.end(), v2.begin(), 
               v2.end(), v3.begin());                  // v3: [1,2,3,7,8,9]

    std::vector<int> v4(6);
    std::merge(v1.begin(), v1.end(), v2.begin(), v2.end(), 
               v4.begin(), std::greater<>());          // v4: [7,8,9,1,2,3]

    std::vector<int> v5(6);
    std::merge(v1.begin(), v1.end(), v2.begin(), v2.end(), v5.begin(), 
               [](int n1, int n2){ return n1 < n2; }); // v5: [1,2,3,7,8,9]

    
    std::vector<int> v6{5, 17, 19, 20, 24, 30, 9, 13, 19, 25, 29, 31, 40, 41};
    std::inplace_merge(v6.begin(), v6.begin() + 6, 
        v6.end()); // v6: [5,9,13,17,19,19,20,24,25,29,30,31,40,41]

    std::vector<int> v7{5, 17, 19, 20, 24, 30, 9, 13, 19, 25, 29, 31, 40, 41};
    std::inplace_merge(v7.begin(), v7.begin() + 6, v7.end(),
        [](int n1, int n2){ 
            return n1 < n2; 
        });        // v7: [5,9,13,17,19,19,20,24,25,29,30,31,40,41]
}
```

### 搜索

| 算法          | 复杂度                    | 描述/示意图/代码                                             |
| ------------- | ------------------------- | ------------------------------------------------------------ |
| adjacent_find | $O(n)$                    | 搜索序列中两个连续相等的元素。                               |
| binary_search | $O(log_2{n})$             | 二分查找指定值，如果找到就返回true；<br>![algo_binary_search](res/stl/algo_binary_search.png) |
| find          | $O(n)$                    | 在指定范围内搜索指定值，并返回该值的迭代器。                 |
| find_end      | $O(s \times (n - s + 1))$ | 在指定范围内搜索最后一个和其他序列匹配的项；<br>![algo_find_end](res/stl/algo_find_end.png) |
| find_first_of | $O(s \times n)$           | 在指定范围内搜索第一个和其他序列匹配的项目；<br>![algo_find_first_of](res/stl/algo_find_first_of.png) |
| find_if       | $O(n)$                    | 在指定范围内搜索满足条件的元素。                             |
| find_if_not   | $O(n)$                    | 在指定范围内搜索**不满足**条件的元素。                       |
| lower_bound   | $O(log_2n)$               | 在指定范围内搜索>=指定值的元素；<br>![algo_lower_bound](res/stl/algo_lower_bound.png) |
| search        | $O(s \times n)$           | 在指定范围内搜索第一个和其他序列匹配的项目。                 |
| search_n      | $O(n)$                    | 在指定范围内搜索连续出现n次的序列。                          |
| upper_bound   |                           |                                                              |

```c++
#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    std::vector<int> af{1, 2, 3, 4, 5, 5, 6, 7, 8};
    std::vector<int>::iterator ret_af;
    ret_af = std::adjacent_find(af.begin(), af.end());    // *ret_af: 5
    ret_af = std::adjacent_find(af.begin(), af.end(),
        std::greater<int>());                             // *ret_af: 0
    ret_af = std::adjacent_find(af.begin(), af.end(), 
        [](int n1, int n2){ return n1 == n2; });          // *ret_af: 5

    std::vector<int> bs{1, 2, 3, 3, 4};
    bool ret_bs;
    ret_bs = std::binary_search(bs.begin(), bs.end(), 3); // ret_bs: true
    ret_bs = std::binary_search(bs.begin(), bs.end(), 3,
        [](int n1, int n2){ return n1 == n2; });          // ret_bs: true

    std::vector<int> f{1, 2, 3, 3, 4};
    std::vector<int>::iterator ret_f;
    ret_f = std::find(f.begin(), f.end(), 3);             // *ret_f: 3

    std::vector<int> fe1{1, 2, 3, 1, 2, 4};
    std::vector<int> fe2{1, 2};
    std::vector<int>::iterator ret_fe;
    ret_fe = std::find_end(fe1.begin(), fe1.end(), 
        fe2.begin(), fe2.end());                          // *ret_fe: 1
    ret_fe = std::find_end(fe1.begin(), fe1.end(), 
        fe2.begin(), fe2.end(), 
        [](int n1, int n2){ return n1 == n2; });          // *ret_fe: 1

    std::vector<int> ffo1{1, 2, 3, 4, 2, 3, 5};
    std::vector<int> ffo2{2, 3};
    std::vector<int>::iterator ret_ffo;
    ret_ffo = std::find_first_of(ffo1.begin(), ffo1.end(), 
        ffo2.begin(), ffo2.end());                        // *ret_ffo: 2
    ret_ffo = std::find_first_of(ffo1.begin(), ffo1.end(), 
        ffo2.begin(), ffo2.end(), 
        [](int n1, int n2){ return n1 == n2; });          // *ret_ffo: 2

    std::vector<int> fi{1, 2, 3, 4, 5};
    std::vector<int>::iterator ret_fi;
    ret_fi = std::find_if(fi.begin(), fi.end(), 
        [](int n){ return n % 2 == 0; });                 // *ret_fi: 2

    std::vector<int> fin{1, 2, 3, 4, 5};
    std::vector<int>::iterator ret_fin;
    ret_fin = std::find_if_not(fin.begin(), fin.end(),
        [](int n){ return n % 2 == 0; });                 // *ret_fin: 1

    std::vector<int> lb{1, 2, 3, 4, 5};
    std::vector<int>::iterator ret_lb;
    ret_lb = std::lower_bound(lb.begin(), lb.end(), 3);   // *ret_lb: 3
    ret_lb = std::lower_bound(lb.begin(), lb.end(), 3, 
        [](int n1, int n2){ return n1 < n2; });           // *ret_lb: 3

    std::vector<int> mm1{1, 2, 3, 4, 5};
    std::vector<int> mm2{1, 2, 4, 5};
    std::pair<std::vector<int>::iterator, std::vector<int>::iterator> ret_mm;
    ret_mm = std::mismatch(mm1.begin(), mm1.end(), 
        mm2.begin());   // <*(ret_mm.first), *(ret_mm.second)>: <3, 4>
    ret_mm = std::mismatch(mm1.begin(), mm1.end(), mm2.begin(), 
        [](int n1, int n2){ 
            return n1 == n2; 
        });             // <*(ret_mm.first), *(ret_mm.second)>: <3, 4> 
    ret_mm = std::mismatch(mm1.begin(), mm1.end(), mm2.begin(), 
        mm2.end());     // <*(ret_mm.first), *(ret_mm.second)>: <3, 4>
    ret_mm = std::mismatch(mm1.begin(), mm1.end(), mm2.begin(), mm2.end(), 
        [](int n1, int n2){ 
            return n1 == n2; 
        });             // <*(ret_mm.first), *(ret_mm.second)>: <3, 4>

    std::vector<int> s1{1, 2, 3, 4, 5};
    std::vector<int> s2{2, 3};
    std::vector<int>::iterator ret_s;
    ret_s = std::search(s1.begin(), s1.end(), 
        s2.begin(), s2.end());                            // *ret_s: 2
    ret_s = std::search(s1.begin(), s1.end(), 
        s2.begin(), s2.end(), 
        [](int n1, int n2){ return n1 < n2; });           // *ret_s: 1

    std::vector<int> sn1{1, 2, 3, 3, 4, 5};
    std::vector<int>::iterator ret_sn;
    ret_sn = std::search_n(sn1.begin(), sn1.end(), 2, 3); // *ret_sn: 3
    ret_sn = std::search_n(sn1.begin(), sn1.end(), 2, 3, 
        [](int n1, int n2){ return n1 == n2; });          // *ret_sn: 3
}
```

### 分区

| 算法             | 复杂度       | 描述/示意图/代码                                             |
| ---------------- | ------------ | ------------------------------------------------------------ |
| is_partitioned   | $O(n)$       | 判断序列是否分区完毕。                                       |
| partition        | $O(nlog(n))$ | 根据条件对序列进行分区（**不保证**原始元素序列的相对顺序），并返回**第二个分区的首元素迭代器**。 |
| partition_point  | $O(n)$       | 返回已分区序列中，**第一个分区的结束迭代器**。               |
| stable_partition | $O(nlog(n))$ | 根据条件对序列进行分区（**保证**原始元素序列的相对顺序），并返回**第二个分区的首元素迭代器**。 |

```c++
#include <vector>
#include <iostream>
#include <algorithm>

int main()
{
    std::vector<int> ip1{1, 4, 6, 4, 5, 3};
    bool ret_ip;
    ret_ip = std::is_partitioned(ip1.begin(), ip1.end(), 
        [](int n){ return n <= 4; }); // ret_ip: false

    std::vector<int> p1{1, 4, 6, 4, 5, 3};
    std::vector<int>::iterator ret_p;
    ret_p = std::partition(p1.begin(), p1.end(), 
        [](int n){ return n < 4; }); // *ret_p: 6, p1:[1,3,6,4,5,4]

    std::vector<int> pp1{1, 4, 6, 4, 5, 3};
    std::vector<int>::iterator ret_pp;
    ret_pp = std::partition_point(pp1.begin(), pp1.end(), 
        [](int n){ return n < 4; }); // *ret_pp:4 pp1:[1,4,6,4,5,3]

    std::vector<int> sp1{1, 4, 6, 4, 5, 3};
    std::vector<int>::iterator ret_sp;
    ret_sp = std::stable_partition(sp1.begin(), sp1.end(),
        [](int n){ return n < 4; }); // *ret_sp:4 sp1:[1,3,4,6,4,5]
}
```

### 比较

| 算法                    | 复杂度         | 描述/示意图/代码                                             |
| ----------------------- | -------------- | ------------------------------------------------------------ |
| equal                   | $O(min(m, n))$ | 判断两个序列的所有元素是否相等；<br>**此算法对于以下容器不可用：**<br>- `std::unordered_set`<br>- `std::unordered_multiset`<br>- `std::unordered_map`<br>- `std::unordered_multimap` |
| equal_range             | $O(log_2(n))$  | 查找序列中所有元素都与指定值相等的片段；<br>![algo_equal_range](res/stl/algo_equal_range.png) |
| lexicographical_compare | $O(min(m, n))$ | 判断一个序列是否按字典序小于第二个序列。                     |
| mismatch                | $O(min(m, n))$ | 搜索两个序列中，不匹配对出现的位置，并返回不匹配位置的迭代器对；<br>![algo_mismatch](res/stl/algo_mismatch.png) |

```c++
#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    std::vector<int> e1{1, 2, 3, 4, 5};
    std::vector<int> e2{1, 2, 3, 4};
    bool ret_e;
    ret_e = std::equal(e1.begin(), e1.end(), e2.begin());  // ret_e: false
    ret_e = std::equal(e1.begin(), e1.end(), e2.begin(), 
        [](int n1, int n2){ return n1 == n2; });           // ret_e: false
    ret_e = std::equal(e1.begin(), e1.end(), e2.begin(), 
        e2.end());                                         // ret_e: false
    ret_e = std::equal(e1.begin(), e1.end(), e2.begin(), 
        e2.end(), [](int n1, int n2){ return n1 == n2; }); // ret_e: false

    std::vector<int> er{1, 2, 3, 3, 5};
    std::pair<std::vector<int>::iterator, std::vector<int>::iterator> ret_er;
    ret_er = std::equal_range(er.begin(), 
        er.end(), 3);           // <*ret_er.first, *ret_er.second>: <3, 5>
    ret_er = std::equal_range(er.begin(), er.end(), 3, 
        [](int n1, int n2){ 
            return n1 == n2; 
        });                     // <*ret_er.first, *ret_er.second>: <5, 0>

    std::vector<int> lc1{1, 2, 3, 4};
    std::vector<int> lc2{2, 3, 4, 5};
    bool ret_lc;
    ret_lc = std::lexicographical_compare(lc1.begin(), lc1.end(), 
        lc2.begin(), lc2.end());                           // ret_lc: true
    ret_lc = std::lexicographical_compare(lc1.begin(), lc1.end(), lc2.begin(), 
        lc2.end(), [](int n1, int n2){ return n1 < n2; }); // ret_lc: true

    std::vector<int> mm1{1, 2, 3, 4, 5};
    std::vector<int> mm2{1, 2, 4, 5};
    std::pair<std::vector<int>::iterator, std::vector<int>::iterator> ret_mm;
    ret_mm = std::mismatch(mm1.begin(), mm1.end(), 
        mm2.begin());        // <*(ret_mm.first), *(ret_mm.second)>: <3, 4>
    ret_mm = std::mismatch(mm1.begin(), mm1.end(), mm2.begin(), 
        [](int n1, int n2){ 
            return n1 == n2; 
        });                  // <*(ret_mm.first), *(ret_mm.second)>: <3, 4> 
    ret_mm = std::mismatch(mm1.begin(), mm1.end(), mm2.begin(), 
        mm2.end());          // <*(ret_mm.first), *(ret_mm.second)>: <3, 4>
    ret_mm = std::mismatch(mm1.begin(), mm1.end(), mm2.begin(), mm2.end(), 
        [](int n1, int n2){ 
            return n1 == n2; 
        });                  // <*(ret_mm.first), *(ret_mm.second)>: <3, 4>
}
```

### 复制

| 算法            | 复杂度 | 描述/示意图/代码                                             |
| --------------- | ------ | ------------------------------------------------------------ |
| copy            | $O(n)$ | 将序列指定范围内元素复制到另一个序列的指定位置，返回最后复制元素的下一个位置；<br>![algo_copy](res/stl/algo_copy.png) |
| copy_backward   | $O(n)$ | 将序列复制到另一个序列的末尾，返回最后复制元素的迭代器；<br>![algo_copy_backward](res/stl/algo_copy_backward.png) |
| copy_if         | $O(n)$ | 将序列指定范围内符合条件的元素，复制到另一个序列的指定位置，返回最后复制元素的下一个位置的迭代器。 |
| copy_n          | $O(n)$ | 将指定范围内的元素，复制前n个元素到另一个序列的指定位置，返回最后复制元素的下一个位置的迭代器。 |
| partition_copy  | $O(n)$ | 将序列分区的结果复制到另两个序列（不改变原序列的内容），并返回这两个序列最后复制元素的迭代器pair。 |
| remove_copy     | $O(n)$ | 将指定范围内的元素复制到指定位置，并跳过等于指定值的元素，返回最后被复制元素的迭代器。 |
| remove_copy_if  | $O(n)$ | 将指定范围内的元素复制到指定位置，并跳过符合条件的元素，返回最后被复制元素的迭代器。 |
| replace_copy    | $O(n)$ | 将指定范围内的元素复制到指定位置，并用新元素替换等于指定值的旧元素，返回最后一个元素的下一个位置的迭代器。 |
| replace_copy_if | $O(n)$ | 将指定范围内的元素复制到指定位置，并用新元素替换符合条件的旧元素，返回最后一个元素的下一个位置的迭代器。 |
| reverse_copy    | $O(n)$ | 反向的将指定范围内的元素复制到指定位置，并返回指向被复制到目的位置的最后一个元素的下一个位置的迭代器。 |
| rotate_copy     | $O(n)$ | 将序列中指定范围的元素按照指定位置翻转，并将结果复制到指定位置，返回目的序列中的最后一个元素的下一个位置的迭代器。 |
| unique_copy     | $O(n)$ | 将指定范围内的元素复制到指定位置，忽略重复的元素，并返回被复制到目的位置的最后一个元素的下一个位置的迭代器。 |

```c++
#include <iostream>
#include <algorithm>
#include <vector>

int main()
{
    std::vector<int> c1{1, 2, 3, 4, 5};
    std::vector<int> c2(5);
    std::vector<int>::iterator ret_c;
    ret_c = std::copy(c1.begin(), c1.end(), 
        c2.begin());     // *ret_c: 0, c1:[1,2,3,4,5], c2:[1,2,3,4,5]

    std::vector<int> cb1{1, 2, 3, 4, 5};
    std::vector<int> cb2(5);
    std::vector<int>::iterator ret_cb;
    ret_cb = std::copy_backward(cb1.begin(), cb1.end(), 
        cb2.end());      // *ret_cb:1, cb1:[1,2,3,4,5], cb2:[1,2,3,4,5]

    std::vector<int> ci1{1, 2, 3, 4, 5};
    std::vector<int> ci2(2);
    std::vector<int>::iterator ret_ci;
    ret_ci = std::copy_if(ci1.begin(), ci1.end(), ci2.begin(), 
        [](int n){ return n % 2 == 0; }); 
                         // *ret_ci:0, ci1:[1,2,3,4,5], ci2:[2,4]

    std::vector<int> cn1{1, 2, 3, 4, 5};
    std::vector<int> cn2(2);
    std::vector<int>::iterator ret_cn;
    ret_cn = std::copy_n(cn1.begin(), 2, 
        cn2.begin());    // ret_cn:0, cn1:[1,2,3,4,5], cn2:[1,2]

    std::vector<int> pc1{1, 2, 3, 4, 5};
    std::vector<int> pc2(3);
    std::vector<int> pc3(3);
    std::pair<std::vector<int>::iterator, std::vector<int>::iterator> ret_pc;
    ret_pc = std::partition_copy(pc1.begin(), pc1.end(), pc2.begin(), pc3.begin(), 
        [](int n){ return n < 5; }); 
                         // <*ret_pc.first, *ret_pc.second>: <0, 0>
                         // pc2:[1,2,3,4,5], pc3:[1,2,3]

    std::vector<int> rc1{1, 2, 3, 4, 5};
    std::vector<int> rc2(4);
    std::vector<int>::iterator ret_rc;
    ret_rc = std::remove_copy(rc1.begin(), rc1.end(), 
        rc2.begin(), 3); // *ret_rc:0, rc1:[1,2,3,4,5], rc2:[1,2,4,5]

    std::vector<int> rci1{1, 2, 3, 4, 5};
    std::vector<int> rci2(4);
    std::vector<int>::iterator ret_rci;
    ret_rci = std::remove_copy_if(rci1.begin(), rci2.end(), rci2.begin(), 
        [](int n){ return n == 3; }); 
                         // *ret_rci:0, rci1:[1,2,3,4,5], rci2:[1,2,4,5]

    std::vector<int> rpc1{1, 2, 3, 4, 5};
    std::vector<int> rpc2{6, 7, 8};
    std::vector<int>::iterator ret_rpc;
    ret_rpc = std::replace_copy(rpc1.begin(), rpc1.end(), 
        rpc2.begin(), 2, 9); 
                         // *ret_rpc:0, rpc1:[1,2,3,4,5], rpc2:[1,9,3]

    std::vector<int> rpci1{1, 2, 3, 4, 5};
    std::vector<int> rpci2{6, 7, 8};
    std::vector<int>::iterator ret_rpci;
    ret_rpci = std::replace_copy_if(rpci1.begin(), rpci1.end(), rpci2.begin(), 
        [](int n){ return n == 2; }, 9); 
                         // *ret_rpci:0, rpci1:[1,2,3,4,5], rpci2:[1,9,3]

    std::vector<int> rvc1{1, 2, 3, 4, 5};
    std::vector<int> rvc2(5);
    std::vector<int>::iterator ret_rvc;
    ret_rvc = std::reverse_copy(rvc1.begin(), rvc1.end(), 
        rvc2.begin());   // *ret_rvc:0, rvc1:[1,2,3,4,5], rvc2:[5,4,3,2,1]

    std::vector<int> rtc1{1, 2, 3, 4, 5};
    std::vector<int> rtc2(5);
    std::vector<int>::iterator ret_rtc;
    ret_rtc = std::rotate_copy(rtc1.begin(), rtc1.begin() + 3, rtc1.end(), 
        rtc2.begin());   // *ret_rtc:0, rtc1:[1,2,3,4,5], rtc2:[4,5,1,2,3]

    std::vector<int> uc1{1, 2, 2, 3, 4, 5};
    std::vector<int> uc2(6);
    std::vector<int>::iterator ret_uc;
    ret_uc = std::unique_copy(uc1.begin(), uc1.end(), 
        uc2.begin());   // *ret_uc:0, uc1:[1,2,2,3,4,5], uc2:[1,2,3,4,5,0]
    ret_uc = std::unique_copy(uc1.begin(), uc1.end(), uc2.begin(), 
        [](int n1, int n2){ return n1 == n2; });
                        // *ret_uc:0, uc1:[1,2,2,3,4,5], uc2:[1,2,3,4,5,0]
}
```

### 交换/反转/删除/替换/旋转/移动/转换/去重

| 算法          | 复杂度   | 描述/示意图/代码                                             |
| ------------- | -------- | ------------------------------------------------------------ |
| iter_swap     | $O(1)$   | 交换两个迭代器指向的元素。                                   |
| reverse       | $O(n/2)$ | 逆转指定范围中的元素。                                       |
| remove        | $O(n)$   | 移除指定范围中，等于指定值的元素，并返回最后一个移除元素的下一个位置的迭代器；<br>![algo_remove](res/stl/algo_remove.png) |
| remove_if     | $O(n)$   | 移除指定范围中，符合指定条件的元素，并返回最后一个移除元素的下一个位置的迭代器。 |
| replace       | $O(n)$   | 用新元素替换指定范围中，等于指定值的元素。                   |
| replace_if    | $O(n)$   | 用新元素替换指定范围中，符合指定条件的元素。                 |
| rotate        | $O(n)$   | 按照逆时针方向旋转指定范围中的元素，并返回**原始序列**中首元素的迭代器；<br>![algo_rotate](res/stl/algo_rotate.png) |
| move          | $O(n)$   | 移动序列元素到指定位置，并返回最后移动元素的下一位置的迭代器。 |
| move_backward | $O(n)$   | 将序列元素以逆序移动（保持元素之间仍然保持原有的顺序）到另一个序列的尾部，并返回最后被移动元素的迭代器。 |
| swap          | $O(n)$   | 交换两个相同长度的序列。                                     |
| swap_ranges   | $O(n)$   | 将指定范围内的元素与另一个序列的指定位置开始的片段，进行交换，并返回第二个序列中最后被交换位置的下一位置的迭代器。 |
| transform     | $O(n)$   | 将指定范围内的元素传递给函数对象，并将操作结果保存到指定位置。 |
| unique        | $O(n)$   | 对指定范围内的元素去重，并返回去重后新范围的最后一个元素的迭代器；<br>![algo_unique](res/stl/algo_unique.png) |

```c++
#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    std::vector<int> is1{1, 2, 3, 4, 5};
    std::iter_swap(is1.begin(), 
                   is1.end() - 1);             // is1: [5,2,3,4,1]

    std::vector<int> r1{1, 2, 3, 4, 5};
    std::reverse(r1.begin(), r1.end());        // r1:  [5,4,3,2,1]
    
    std::vector<int> rm1{1, 2, 3, 4, 5};
    std::vector<int>::iterator ret_rm;
    ret_rm = std::remove(rm1.begin(), rm1.end(), 
                         3);                   // *ret_rm: 5
                                               // rm1: [1,2,4,5,5]
    
    std::vector<int> rmi1{1, 2, 3, 4, 5};
    std::vector<int>::iterator ret_rmi;
    ret_rmi = std::remove_if(rmi1.begin(), rmi1.end(), 
        [](int n){ return n == 3; });         // *ret_rmi: 5
                                              // rmi1: [1,2,4,5,5]
    
    std::vector<int> rp1{1, 2, 3, 4, 5};
    std::replace(rp1.begin(), rp1.end(), 
                 3, 6);                       // rp1: [1,2,6,4,5]
    
    std::vector<int> rpi1{1, 2, 3, 4, 5};
    std::replace_if(rpi1.begin(), rpi1.end(), 
        [](int n){ return n == 3; }, 6);      // rpi1: [1,2,6,4,5]

    std::vector<int> rt1{1, 2, 3, 4, 5};
    std::vector<int>::iterator ret_rt;
    ret_rt = std::rotate(rt1.begin(), rt1.begin() + 3, 
                         rt1.end());          // *ret_rt:1
                                              // rt1: [4,5,1,2,3]
    
    std::vector<int> mv1{1, 2, 3, 4, 5};
    std::vector<int> mv2(5);
    std::vector<int>::iterator ret_mv;
    ret_mv = std::move(mv1.begin(), mv1.end(), 
                       mv2.begin());          // *ret_mv:0
                                              // mv1: [1,2,3,4,5]
                                              // mv2: [1,2,3,4,5]

    std::vector<int> mvb1{1, 2, 3, 4, 5};
    std::vector<int> mvb2(5);
    std::vector<int>::iterator ret_mvb;
    ret_mvb = std::move_backward(mvb1.begin(), mvb1.end(), 
                                 mvb2.end()); // *ret_mvb:1
                                              // mvb2: [1,2,3,4,5]

    std::vector<int> sw1{1, 2, 3, 4, 5};
    std::vector<int> sw2{6, 7, 8, 9, 10};
    std::swap(sw1, sw2);                      // sw1: [6,7,8,9,10]
                                              // sw2: [1,2,3,4,5]
    
    std::vector<int> swr1{1, 2, 3, 4, 5};
    std::vector<int> swr2{6, 7, 8, 9, 10};
    std::vector<int>::iterator ret_swr;
    ret_swr = std::swap_ranges(swr1.begin(), swr1.begin() + 2, 
                               swr2.begin()); // *ret_swr:8
                                              // swr1: [6,7,3,4,5]
                                              // swr2: [1,2,8,9,10]
    
    std::vector<int> tsf1{1, 2, 3, 4, 5};
    std::vector<int>::iterator ret_tsf;
    ret_tsf = std::transform(tsf1.begin(), tsf1.begin() + 2, tsf1.begin(),
                             [](int n){ 
                                 return ++n; 
                             });               // ret_tsf:3
                                               // tsf1: [2,3,3,4,5]

    std::vector<int> u1{1, 2, 2, 3};
    std::vector<int>::iterator ret_u;
    ret_u = std::unique(u1.begin(), u1.end()); // *ret_u:3
                                               // u1: [1,2,3,3]
}
```

### 堆操作

| 算法          | 复杂度       | 描述/示意图/代码                                         |
| ------------- | ------------ | -------------------------------------------------------- |
| is_heap       | $O(n)$       | 检查范围中的元素是否为最大堆。                           |
| is_heap_until | $O(n)$       | 查找能成为最大堆的最大子范围，并返回最大堆的最末迭代器。 |
| make_heap     | $O(log\ n)$  | 在范围中构造最大堆。                                     |
| push_heap     | $O(log\ n)$  | 将一个元素加入到一个最大堆。                             |
| pop_heap      | $O(2log\ n)$ | 从最大堆中移除最大元素。                                 |
| sort_heap     | $O(2log\ n)$ | 将一个最大堆变成一个按升序排序的元素范围。               |

```c++
#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    std::vector<int> v{1, 2, 3, 4};

    bool ret_ih = std::is_heap(v.begin(), v.end());    // ret_ih: 0

    std::vector<int>::iterator ret_ihu = 
        std::is_heap_until(v.begin(), v.end());        // *ret_ihu: 2

    std::make_heap(v.begin(), v.end());                // v: [4,2,3,1]
    std::make_heap(v.begin(), v.end(), 
                   [](int a, int b){ return a > b; }); // v: [1,2,3,4]

    std::push_heap(v.begin(), v.end());                // v: [4,1,3,2]
    std::push_heap(v.begin(), v.end(), 
                   [](int a, int b){ return a > b; }); // v: [4,1,3,2]

    std::pop_heap(v.begin(), v.end());                 // v: [3,1,2,4]
    std::pop_heap(v.begin(), v.end(), 
                  [](int a, int b){ return a > b; });  // v: [1,4,2,3]

    std::sort_heap(v.begin(), v.end());                // v: [2,3,4,1]
    std::sort_heap(v.begin(), v.end(), 
                   [](int a, int b){ return a < b; }); // v: [1,3,4,2]
}
```

### 数值计算

| 算法                | 头文件    | 复杂度            | 描述/示意图/代码                                             |
| ------------------- | --------- | ----------------- | ------------------------------------------------------------ |
| accumulate          | numeric   | $O(n)$            | 根据提供的和的初始值，计算指定范围内元素之和并返回。         |
| adjacent_difference | numeric   | $O(n)$            | 计算指定范围内，相邻元素的差，保存到指定位置，并返回最后被写入元素后一位置的迭代器。 |
| inner_product       | numeric   | ？                | 根据提供的内积的初始值，计算两个序列的内积并返回；<br>![algo_inner_product](res/stl/algo_inner_product.png) |
| iota                | numeric   | $O(n)$            | 根据提供的初始值，生成一个连续递增的序列，并存放到指定位置。 |
| max                 | algorithm | $O(n)$            | 返回给定值中的最大值。                                       |
| max_element         | algorithm | $O(n)$            | 返回给定值中的最大值的迭代器。                               |
| min                 | algorithm | $O(n)$            | 返回给定值中的最小值。                                       |
| min_element         | algorithm | $O(n)$            | 返回给定值中的最小值的迭代器。                               |
| minmax              | algorithm | $O(\frac{3n}{2})$ | 返回给定值中的最小值和最大值的pair。                         |
| minmax_element      | algorithm | $O(\frac{3n}{2})$ | 返回给定值中的最小值和最大值的迭代器pair。                   |
| partial_sum         | numeric   | $O(n)$            | 对指定范围中的元素部分求和，将结果保存到指定位置，并返回最后被写入元素的后一位置的迭代器。 |

```c++
#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

int main()
{
    std::vector<int> a1{1, 2, 3, 4};
    int ret_a = 0;
    ret_a = std::accumulate(a1.begin(), a1.end(), 
                            1);                 // ret_a: 11
    ret_a = std::accumulate(a1.begin(), a1.end(), 1, 
        [](int n1, int n2){ return n2 - n1; }); // ret_a: 3
    
    std::vector<int> ad1{1, 2, 3, 4};
    std::vector<int> ad2(2);
    std::vector<int>::iterator ret_ad;
    ret_ad = std::adjacent_difference(ad1.begin(), ad1.end(), 
        ad2.begin());                           // *ret_ad: 0, ad2: [1,1]
    ret_ad = std::adjacent_difference(ad1.begin(), ad1.end(), ad2.begin(), 
        [](int n1, int n2){ return n1 + n2; }); // *ret_ad: 0, ad2: [1,3]

    std::vector<int> ip1{0, 1, 2, 3, 4};
    std::vector<int> ip2{5, 4, 2, 3, 1};
    int ret_ip = 0;
    ret_ip = std::inner_product(ip1.begin(), ip1.end(), ip2.begin(), 
                                0);             // *ret_ip: 21
    ret_ip = std::inner_product(ip1.begin(), ip1.end(), ip2.begin(), 0, 
      std::plus<>(),
      std::equal_to<>());                       // *ret_ip: 2

    std::vector<int> i1(5);
    std::iota(i1.begin(), i1.end(), 2);         // i1: [2,3,4,5,6]
    
    int ret_max = 0;
    ret_max = std::max(1, 2);                   // ret_max: 2
    ret_max = std::max(1, 2, 
        [](int n1, int n2){ return n1 > n2; }); // ret_max: 1
    ret_max = std::max({1, 2, 3, 4, 5});        // ret_max: 5
    ret_max = std::max({1, 2, 3, 4, 5}, [](int n1, int n2){ 
        return n1 < n2 && n2 % 2 == 0; 
    });                                         // ret_max: 4
    
    std::vector<int> max_e1{1, 2, 3, 4, 5};
    std::vector<int>::iterator ret_max_e;
    ret_max_e = std::max_element(max_e1.begin(), 
                                 max_e1.end()); // *ret_max_e: 5
    ret_max_e = std::max_element(max_e1.begin(), max_e1.end(), 
                                 [](int n1, int n2){ 
                                     return n1 < n2; 
                                 });            // *ret_max_e: 5
    
    int ret_min = 0;
    ret_min = std::min(1, 2);                   // ret_min: 1
    ret_min = std::min(1, 2, [](int n1, int n2){ 
        return n1 > n2; 
    });                                         // ret_min: 2
    ret_min = std::min({5, 4, 3, 2, 1});        // ret_min: 1
    ret_min = std::min({5, 4, 3, 2, 1}, [](int n1, int n2){ 
        return n1 < n2 && n1 % 2 == 0; 
    });                                         // ret_min: 2

    std::vector<int> min_e1{1, 2, 3, 4, 5};
    std::vector<int>::iterator ret_min_e;
    ret_min_e = std::min_element(min_e1.begin(), 
                                 min_e1.end()); // *ret_min_e: 1
    ret_min_e = std::min_element(min_e1.begin(), min_e1.end(), 
                                 [](int n1, int n2){ 
                                     return n1 < n2; 
                                 });            // *ret_min_e: 1
    
    std::pair<int, int> ret_mm;
    ret_mm = std::minmax(1, 2); // <ret_mm.first, ret_mm.second>: <1, 2>
    ret_mm = std::minmax(1, 2, [](int n1, int n2){ 
        return n1 < n2; 
    });                         // <ret_mm.first, ret_mm.second>: <1, 2>
    ret_mm = std::minmax(
        {1, 2, 3, 4, 5}
    );                          // <ret_mm.first, ret_mm.second>: <1, 5>
    ret_mm = std::minmax({1, 2, 3, 4, 5}, [](int n1, int n2){ 
        return n1 < n2; 
    });                         // <ret_mm.first, ret_mm.second>: <1, 5>

    std::vector<int> mme1{1, 2, 3, 4, 5};
    std::pair<std::vector<int>::iterator, std::vector<int>::iterator> ret_mme;
    ret_mme = std::minmax_element(mme1.begin(), 
        mme1.end());           // <*ret_mme.first, *ret_mme.second>: <1, 5>
    ret_mme = std::minmax_element(mme1.begin(), mme1.end(), 
        [](int n1, int n2){ 
            return n1 < n2; 
        });                    // <*ret_mme.first, *ret_mme.second>: <1, 5>

    std::vector<int> ps1{1, 2, 3, 4, 5};
    std::vector<int> ps2(5);
    std::vector<int>::iterator ret_ps;
    ret_ps = std::partial_sum(ps1.begin(), ps1.end(), 
        ps2.begin());            // *ret_ps: 0, ps2: [1,3,6,10,15]
    ret_ps = std::partial_sum(ps1.begin(), ps1.end(), ps2.begin(), 
        std::multiplies<int>()); // *ret_ps: 0, ps2: [1,2,6,24,120]
}
```

### 函数对象

| 算法          | 头文件     | 描述/示意图/代码 |
| ------------- | ---------- | ---------------- |
| bit_and       | functional | `x & y`          |
| bit_not       | functional | `~x`             |
| bit_or        | functional | `x | y`          |
| bit_xor       | functional | `x ^ y`          |
| divides       | functional | `x / y`          |
| equal_to      | functional | `x == y`         |
| greater       | functional | `x > y`          |
| greater_equal | functional | `x >= y`         |
| less          | functional | `x < y`          |
| less_equal    | functional | `x <= y`         |
| logical_and   | functional | `x && y`         |
| logical_not   | functional | `!x`             |
| logical_or    | functional | `x || y`         |
| minus         | functional | `x - y`          |
| modulus       | functional | `x % y`          |
| multiplies    | functional | `x * y`          |
| negate        | functional | `-x`             |
| not_equal_to  | functional | `x != y`         |
| plus          | functional | `x + y`          |

```c++
#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>

int main()
{
    std::vector<int> v1{0x1, 0x0, 0x0};
    std::vector<int> v2{0x1, 0x1, 0x1};
    std::vector<int> v3(3);
    
    std::fill(v3.begin(), v3.end(), 0);
    std::transform(std::begin(v1), std::end(v1), std::begin(v2), 
                   std::begin(v3), std::bit_and<int>());  // v3: [1,0,0]

    std::fill(v3.begin(), v3.end(), 0);
    std::transform(std::begin(v1), std::end(v1), std::begin(v3), 
                   std::bit_not<int>());                  // v3: [-2,-1,-1]

    std::fill(v3.begin(), v3.end(), 0);
    std::transform(std::begin(v1), std::end(v1), std::begin(v2), 
                   std::begin(v3), std::bit_or<int>());   // v3: [1,1,1]
    
    std::fill(v3.begin(), v3.end(), 0);
    std::transform(std::begin(v1), std::end(v1), std::begin(v2), 
                   std::begin(v3), std::bit_xor<int>());  // v3: [0,1,1]

    std::fill(v3.begin(), v3.end(), 0);
    std::transform(std::begin(v1), std::end(v1), std::begin(v2), 
                   std::begin(v3), std::divides<int>());  // v3: [1,0,0]

    std::fill(v3.begin(), v3.end(), 0);
    std::transform(std::begin(v1), std::end(v1), std::begin(v2), 
                   std::begin(v3), std::equal_to<int>()); // v3: [1,0,0]

    std::fill(v3.begin(), v3.end(), 0);
    std::transform(std::begin(v1), std::end(v1), std::begin(v2), 
                   std::begin(v3), std::greater<int>());  // v3: [0,0,0]

    std::fill(v3.begin(), v3.end(), 0);
    std::transform(std::begin(v1), std::end(v1), std::begin(v2), 
        std::begin(v3), std::greater_equal<int>());       // v3: [1,0,0]

    std::fill(v3.begin(), v3.end(), 0);
    std::transform(std::begin(v1), std::end(v1), std::begin(v2), 
                   std::begin(v3), std::less<int>());     // v3: [0,1,1]

    std::fill(v3.begin(), v3.end(), 0);
    std::transform(std::begin(v1), std::end(v1), std::begin(v2), 
        std::begin(v3), std::less_equal<int>());          // v3: [1,1,1]

    std::fill(v3.begin(), v3.end(), 0);
    std::transform(std::begin(v1), std::end(v1), std::begin(v2), 
        std::begin(v3), std::logical_and<int>());         // v3: [1,0,0]

    std::fill(v3.begin(), v3.end(), 0);
    std::transform(std::begin(v1), std::end(v1), std::begin(v3), 
                   std::logical_not<int>());              // v3: [0,1,1]

    std::fill(v3.begin(), v3.end(), 0);
    std::transform(std::begin(v1), std::end(v1), std::begin(v2), 
        std::begin(v3), std::logical_or<int>());          // v3: [1,1,1]

    std::fill(v3.begin(), v3.end(), 0);
    std::transform(std::begin(v1), std::end(v1), std::begin(v2), 
                   std::begin(v3), std::minus<int>());    // v3: [0,-1,-1]

    std::fill(v3.begin(), v3.end(), 0);
    std::transform(std::begin(v1), std::end(v1), std::begin(v2), 
                   std::begin(v3), std::modulus<int>());  // v3: [0,0,0]

    std::fill(v3.begin(), v3.end(), 0);
    std::transform(std::begin(v1), std::end(v1), std::begin(v2), 
        std::begin(v3), std::multiplies<int>());          // v3: [1,0,0]

    std::fill(v3.begin(), v3.end(), 0);
    std::transform(std::begin(v1), std::end(v1), std::begin(v3), 
                   std::negate<int>());                   // v3: [-1,0,0]

    std::fill(v3.begin(), v3.end(), 0);
    std::transform(std::begin(v1), std::end(v1), std::begin(v2), 
        std::begin(v3), std::not_equal_to<int>());        // v3: [0,1,1]

    std::fill(v3.begin(), v3.end(), 0);
    std::transform(std::begin(v1), std::end(v1), std::begin(v2), 
                   std::begin(v3), std::plus<int>());     // v3: [2,1,1]
}
```

### 其它

| 算法     | 复杂度 | 描述/示意图/代码                               |
| -------- | ------ | ---------------------------------------------- |
| for_each | $O(n)$ | 使用函数遍历指定范围内的元素。                 |
| count    | $O(n)$ | 统计指定范围内与指定值相等的元素的个数并返回。 |
| count_if | $O(n)$ | 统计指定范围内满足要求的元素个数并返回。       |

```c++
#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    std::vector<int> fe1{1, 2, 3, 4, 5};
    std::for_each(fe1.begin(), fe1.end(), 
                  [](int &n){ n++; }); // fe1: [2,3,4,5,6]
    
    std::vector<int> ct1{1, 2, 3, 4, 5};
    size_t ret_ct = std::count(ct1.begin(), ct1.end(), 
                               3);     // ret_ct: 1
    
    std::vector<int> cti1{1, 2, 3, 4, 5};
    size_t ret_cti = std::count_if(cti1.begin(), cti1.end(), 
                                   [](int n){ 
                                       return n % 2 == 0; 
                                   }); // ret_cti: 2
}
```

---



## I/O流

![io_inheritance](res/stl/io_inheritance.png)

### ios_base

| 成员函数          | 描述                                                         |
| ----------------- | ------------------------------------------------------------ |
| flags             | 设置当前格式化标志，并返回前一个格式化标志；<br>  - `std::ios_base::dec` 为整数I/O使用十进制底；<br>  - `std::ios_base::oct` 为整数I/O使用八进制底；<br>  - `std::ios_base::hex` 为整数I/O使用十六进制底；<br>  - `std::ios_base::basefield` 用于掩码运算（`dec|oct|hex`）；<br>  - `std::ios_base::left` 左校正（添加填充字符到右）；<br>  - `std::ios_base::right` 右校正（添加填充字符到左）；<br>  - `std::ios_base::internal` 内部校正（添加填充字符到内部选定点）<br>  - `std::ios_base::adjustfield` 用于掩码运算（`left|right|internal`）；<br>  - `std::ios_base::scientific` 用科学记数法生成浮点类型，若与fixed组合则用十六进制记法；<br>  - `std::ios_base::fixed` 用定点生成浮点类型，若与scientific组合则用十六进制记法；<br>  - `std::ios_base::floatfield` 用于掩码运算（`scientific|fixed`）；<br>  - `std::ios_base::boolalpha` 以字符数字格式插入并释出bool类型；<br>  - `std::ios_base::showbase` 生成为整数输出指示数字基底的前缀，货币I/O中要求现金指示器；<br>  - `std::ios_base::showpoint` 无条件为浮点数输出生成小数点字符；<br>  - `std::ios_base::showpos` 为非负数值输出生成+字符；<br>  - `std::ios_base::skipws` 在具体输入操作前跳过前导空白符；<br>  - `std::ios_base::unitbuf` 在每次输出操作后冲入输出；<br>  - `std::ios_base::uppercase` 在具体输出的输出操作中以大写等价替换小写字符。 |
| getloc            | 返回当前与流关联的 locale。                                  |
| imbue             | 设置本地环境。                                               |
| init              | 初始化标准流对象。                                           |
| iword             | 尽可能地分配或重置私有存储，并访问指定的下标的**long**类型元素。 |
| precision         | 设置/返回当前浮点数精度。                                    |
| pword             | 尽可能地分配或重置私有存储，并访问指定的下标的**void * **类型元素。 |
| register_callback | 注册事件回调函数（调用时以注册顺序的逆序回调，类似于栈）；<br>回调函数格式：`(*void)(std::ios_base::event, std::ios_base&, int)` |
| setf              | 设置特定格式标志及组合（同flags）。                          |
| sync_with_stdio   | 设置C++和C的IO库是否可以互操作。                             |
| unsetf            | 清除特定格式的标志。                                         |
| width             | 管理/返回当前域的宽度。                                      |
| xalloc            | 返回能安全用作 pword() 和 iword() 下标的程序范围内独有的整数。 |

### basic_ios

| 成员函数   | 描述                                                         |
| ---------- | ------------------------------------------------------------ |
| good       | 检查是否**未发生**错误。                                     |
| eof        | 判断是否到达了文件末尾。                                     |
| fail       | 判断是否发生了可恢复的错误。                                 |
| bad        | 判断是否已发生不可恢复的错误。                               |
| rdstate    | 返回当前错误状态。                                           |
| setstate   | 设置错误状态标志；<br>  - `std::ios_base::goodbit`无错误；<br>  - `std::ios_base::badbit`不可恢复的流错误；<br>  - `std::ios_base::failbit`输入/输出操作失败（格式化或提取错误）；<br>  - `std::ios_base::eofbit`关联的输出序列已抵达文件尾； |
| clear      | 修改状态标志。                                               |
| copyfmt    | 复制另一个流的格式化信息（除rdstate和rdbuf外的所有内容）。   |
| fill       | 设置填充字符，并返回前一个填充字符。                         |
| exceptions | 获取和设置流的异常掩码（参考错误状态标识）。                 |
| rdbuf      | 设置/返回关联的流缓冲。                                      |
| tie        | 设置/返回绑定的联系流（输出流）。                            |
| narrow     | 窄化指定字符（将其从`char_type`转换到`char`），成功即返回窄化后的值，若窄化失败则返回指定值。 |
| widen      | 拓宽字符，转换字符到其在当前本地环境的等价物，并返回。       |
| set_rdbuf  | 替换 `rdbuf` 而不清除其错误状态。                            |

### istream

| 成员函数 | 描述                                                         |
| -------- | ------------------------------------------------------------ |
| gcount   | 最近的无格式输入操作所提取的字符数。                         |
| get      | 从流中读并取走一个字符。                                     |
| getline  | 一直读并取走字符，直到找到给定字符。                         |
| ignore   | 读并取走并舍弃指定数量的字符，直至发现给定值（默认eof）。    |
| read     | 读并取走指定数量的字符块。                                   |
| readsome | 读并取走指定数量的已经可用的字符块。                         |
| peek     | 仅读出但不取走1个字符。                                      |
| putback  | 往输入流中退回一个字符。                                     |
| seekg    | 设置输入位置指示器；<br>- `std::istream::beg`流的开始；<br>- `std::istream::end`流的结尾；<br>- `std::istream::cur`流位置指示器的当前位置； |
| sync     | 同步数据到底层设备。                                         |
| tellg    | 返回当前输入位置指示器。                                     |
| unget    | 插销get操作。                                                |

```c++
#include <iostream>
#include <sstream>

void cb(std::ios_base::event evt, std::ios_base& str, int idx) {str.pword(idx);}

int main()
{
    std::istringstream ss1{
        "1234567\n"
        "abcdefg\n"
        "ABCDEFG"
    };
    std::istringstream ss2{"1234567"};
    std::istream i1{ss1.rdbuf()};         // i1: [
                                          //   1234567
                                          //   abcdefg
                                          //   ABCDEFG
                                          // ]
    std::istream i2{ss2.rdbuf()};         // i2: [1234567]

    bool ret_b = i1.bad();                // ret_b: false

    i1.clear();                           // i1: [
                                          //   1234567
                                          //   abcdefg
                                          //   ABCDEFG
                                          // ]

    i1.copyfmt(i2);                       // i1: [
                                          //   1234567
                                          //   abcdefg
                                          //   ABCDEFG
                                          // ]

    bool ret_eof = i1.eof();              // ret_eof: false

    std::ios_base::iostate ret_exp = 
        i1.exceptions();                  // ret_exp: NULL
    i1.exceptions(ret_exp);               // ret_exp: NULL

    bool ret_f = i1.fail();               // ret_f: false

    char ret_fill = i1.fill();            // ret_fill: 
    ret_fill = i1.fill('0');              // ret_fill: 
    
    std::ios_base::fmtflags ret_flg = 
        i1.flags();                       // ret_flg(二进制): 1000000000010
    ret_flg = 
        i1.flags(std::ios_base::hex);     // ret_flg(二进制): 1000000000010
    ret_flg = 
        i1.flags(std::ios_base::skipws);  // ret_flg(二进制): 0000000001000

    std::streamsize ret_gc = i1.gcount(); // ret_gc: 0

    char ret_g1;
    char ret_g2[2];
    std::istringstream ret_g3{};
    i1.get(ret_g1);                       // i1: [
                                          //   234567
                                          //   abcdefg
                                          //   ABCDEFG
                                          // ]
    i1.get(ret_g2, 2);                    // i1: [
                                          //   34567
                                          //   abcdefg
                                          //   ABCDEFG
                                          // ]
    i1.get(ret_g2, 3, '5');               // i1: [
                                          //   567
                                          //   abcdefg
                                          //   ABCDEFG
                                          // ]
    i1.get(*ret_g3.rdbuf(), '6');         // i1: []
    i1.get(*ret_g3.rdbuf());              // i1: []

    char ret_gl[10];
    i2.getline(ret_gl, 10);               // i2: []， ret_gl: [123456]
    i2.getline(ret_gl, 10, 'C');          // i2: []， ret_gl: []

    std::locale ret_lc = i1.getloc();

    bool ret_g = i1.good();               // ret_g: false

    i1.ignore(1);                         // i1: []
    i1.ignore(2, 'E');                    // i1: []

    i1.imbue(ret_lc);

    long ret_iw = i1.iword(1);            // ret_iw: 0

    char ret_c = i1.narrow('G', 'N');     // ret_c: G

    char ret_r[7];
    i1.read(ret_r, 1);                    // ret_r: 

    char ret_rs[7];
    i1.readsome(ret_rs, 7);               // ret_rs: 

    i1.register_callback(cb, 1);

    std::streambuf *ret_rd;
    ret_rd = i1.rdbuf();
    ret_rd = i1.rdbuf(ret_g3.rdbuf());

    std::ios_base::iostate ret_rds = 
        i1.rdstate();                     // ret_rds: 0

    char ret_p = i1.peek();               // ret_p: 

    std::streamsize ret_pr = i1.precision();
    i1.precision(2);

    i1.putback('G');                      // i1: []

    void* ret_pw = i1.pword(1);

    i1.seekg(0);
    i1.seekg(1, std::istream::beg);

    i2.setf(std::ios_base::dec);
    i2.setf(std::ios_base::dec, std::ios_base::showpos);

    // i2.set_rdbuf(i1.rdbuf());

    i2.setstate(std::ios_base::goodbit);

    i1.sync();

    i1.sync_with_stdio(true);

    std::streampos ret_tg = i1.tellg();

    std::ostream *ret_tie;
    ret_tie = i1.tie();
    ret_tie = i1.tie(&std::cout);

    i1.unget();

    i1.unsetf(std::ios_base::dec);

    char ret_wd = i1.widen('c');

    std::streamsize ret_w;
    ret_w = i1.width();
    ret_w = i1.width(8);

    int ret_x = i1.xalloc();
}
```

### ostream

| 成员函数 | 描述                     |
| -------- | ------------------------ |
| flush    | 与底层存储设备同步。     |
| put      | 插入字符。               |
| seekp    | 设置输出位置指示器。     |
| tellp    | 返回当前输出位置指示器。 |
| write    | 插入字符块。             |

```c++
#include <iostream>
#include <sstream>

void cb(std::ios_base::event evt, std::ios_base& str, int idx) {str.pword(idx);}

int main()
{
    std::istringstream ss1{
        "1234567\n"
        "abcdefg\n"
        "ABCDEFG"
    };
    std::ostream os1{ss1.rdbuf()};

    bool ret_b = os1.bad(); // ret_b:

    os1.clear(); // os1: 

    os1.copyfmt(os1);

    bool ret_eof = os1.eof();

    std::ios_base::iostate ret_exp = os1.exceptions(); // ret_exp: NULL
    os1.exceptions(ret_exp);                           // ret_exp: NULL

    bool ret_f = os1.fail(); // ret_f: 

    char ret_fill = os1.fill(); // ret_fill: 
    ret_fill = os1.fill('0'); // ret_fill: 

    std::ios_base::fmtflags ret_flg = os1.flags();
    ret_flg = os1.flags(std::ios_base::hex);
    ret_flg = os1.flags(std::ios_base::skipws);

    os1.flush();

    std::locale ret_lc = os1.getloc();

    bool ret_g = os1.good();

    os1.imbue(ret_lc);

    long ret_iw = os1.iword(1);

    char ret_n = os1.narrow('G', 'N'); // ret_n: 

    std::streamsize ret_pr = os1.precision();
    os1.precision(2);

    void* ret_pw = os1.pword(1);

    os1.register_callback(cb, 1);

    std::streambuf *ret_rd;
    ret_rd = os1.rdbuf();
    ret_rd = os1.rdbuf(ss1.rdbuf());

    std::ios_base::iostate ret_rds = os1.rdstate(); // ret_rds:

    os1.seekp(1);
    os1.seekp(0, std::ios_base::beg);

    os1.setf(std::ios_base::dec);
    os1.setf(std::ios_base::dec, std::ios_base::showpos);

    // os1.set_rdbuf(os1.rdbuf());

    os1.setstate(std::ios_base::goodbit);

    os1.sync_with_stdio(true);

    std::streampos ret_tp = os1.tellp();

    std::ostream *ret_tie;
    ret_tie = os1.tie();
    ret_tie = os1.tie(&std::cout);

    os1.unsetf(std::ios_base::dec);

    char ret_wd = os1.widen('c');

    std::streamsize ret_w;
    ret_w = os1.width();
    ret_w = os1.width(8);

    char cs[5] = {'h', 'e', 'l', 'l', 'o'};
    os1.write(cs, 5);

    int ret_x = os1.xalloc();
}
```

### ifstream

| 成员函数 | 描述                                                         |
| -------- | ------------------------------------------------------------ |
| close    | 关闭关联文件。                                               |
| is_open  | 检查流是否有关联文件。                                       |
| open     | 打开文件，并将它与流关联；<br>打开模式：<br>  - `std::ios::app` 每次写入前寻位到流结尾；<br>  - `std::ios::binary` 以二进制模式打开；<br>  - `std::ios::in` 以读打开；<br>  - `std::ios::out` 为写打开；<br>  - `std::ios::trunc` 在打开时舍弃流的内容；<br>  - `std::ios::ate` 打开后立即寻位到流结尾； |

```c++
#include <fstream>
#include <iostream>

int main()
{
    std::ifstream f1;
    std::ifstream f2{std::move(f1)};

    f1.open("007.txt", std::ios_base::in);
    
    bool ret_iop = f1.is_open();

    f1.close();
}
```

### ofstream

| 成员函数 | 描述                       |
| -------- | -------------------------- |
| close    | 关闭关联文件。             |
| is_open  | 检查流是否有关联文件。     |
| open     | 打开文件，并将它与流关联。 |

```c++
#include <fstream>

int main()
{
    std::ofstream of1{};
    std::ofstream of2{std::move(of1)};

    of1.open("/mnt/c/Work/src/test/007.txt", std::ios::out);

    bool ret_iop = of1.is_open();

    of1.close();
}
```

---



## 时间

### duration

| 成员函数 | 描述                       |
| -------- | -------------------------- |
| count    | 返回计次的计数。           |
| min      | 返回拥有最低可能值的时长。 |
| max      | 返回拥有最大可能值的时长。 |
| zero     | （静态）返回零长度时长。   |

```c++
#include <chrono>

std::chrono::hours operator"" _h(unsigned long long n) { 
    return std::chrono::hours(n); };
std::chrono::seconds operator"" _s(unsigned long long n) { 
    return std::chrono::seconds(n); };

int main()
{
    std::chrono::duration<int> d1{60};
    std::chrono::duration<int, std::milli> d2{1500};
    std::chrono::duration<double, std::ratio<60> > d3{60};
    std::chrono::duration<double, std::ratio<1, 30> > d4{3.5};
    std::chrono::milliseconds d5{1000}; 

    int ret_ct = d1.count();                            // ret_ct: 60

    std::chrono::duration<int, std::milli> ret_zero = 
        std::chrono::duration<int, std::milli>::zero(); // ret_zero.count: 0 

    std::chrono::duration<int, std::milli> ret_min = 
        d2.min();                                       // ret_min.count: -21474...

    std::chrono::duration<int, std::milli> ret_max = 
        d2.max();                                       // ret_max.count: 21474...

    std::chrono::seconds ret_sec = std::chrono::duration_cast<
        std::chrono::seconds>(d2);                      // ret_sec.count(): 1

    std::chrono::hours h = 5_h;                         // h.count(): 5
    std::chrono::seconds s = 30_s;                      // s.count(): 30
}
```

### time_point

- `system_clock` 当前真实时钟时间。
- `steady_clock` 适合记录时间间隔的时钟。
- `high_resolution_clock` 具有当前系统所能使用的最小时钟周期的时钟。

| 成员函数/变量     | 描述                                |
| ----------------- | ----------------------------------- |
| from_time_t       | （静态）转换`std::time_t`位时间点。 |
| max               | 返回对应最小时长的时间点。          |
| min               | 返回对应最大时长的时间点。          |
| now               | （静态）返回当前时间点。            |
| time_point_cast   | （静态）时间点转换。                |
| time_sinc_epoch() | 从其时钟起点开始的时间点。          |
| to_time_t         | （静态）转换时间点为`std::time_t`   |

```c++
#include <chrono>

using SysTimePoint = std::chrono::time_point<std::chrono::system_clock>;
using SteadyTimePoint = std::chrono::time_point<std::chrono::steady_clock>;
using HTimePoint = std::chrono::time_point<std::chrono::high_resolution_clock>;

int main()
{
    SysTimePoint tp1{std::chrono::minutes(1)};
    SysTimePoint tp2{std::chrono::duration<int>(20)};
    SteadyTimePoint tp3{std::chrono::minutes(1)};
    SteadyTimePoint tp4{std::chrono::duration<int>(20)};
    HTimePoint tp5{std::chrono::minutes(1)};
    HTimePoint tp6{std::chrono::duration<int>(20)};

    std::chrono::system_clock::duration ret_tse1 = tp1.time_since_epoch();
    std::chrono::steady_clock::duration ret_tse2 = tp3.time_since_epoch();
    std::chrono::high_resolution_clock::duration ret_tse3 = tp5.time_since_epoch();

    std::chrono::duration<double> ret_dc1 = 
        std::chrono::duration_cast<std::chrono::duration<double> >(
            std::chrono::duration<int>(20)
    );

    std::chrono::time_point<std::chrono::system_clock, std::chrono::seconds> tp_sec = 
        std::chrono::time_point_cast<std::chrono::seconds>(tp1);

    std::chrono::system_clock::time_point ret_now1 = 
        std::chrono::system_clock::now();
    std::chrono::steady_clock::time_point ret_now2 = 
        std::chrono::steady_clock::now();
    std::chrono::high_resolution_clock::time_point ret_now3 = 
        std::chrono::high_resolution_clock::now();

    std::time_t t1 = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::time_t t3 = std::chrono::high_resolution_clock::to_time_t(std::chrono::high_resolution_clock::now());

    tm *tm4 = std::localtime(&t1);
}
```

### put_time

TODO


---



## 其它

### function,bind和ref

（C++11）`std::function`可调用对象包装器，通过对c++中各种可调用实体的封装，同时通过`std::bind`把参数绑定到可调用对象，形成一个新的可调用对象。

```c++
#include <iostream>
#include <functional>

int f1(int x, int &y, int z = 1) { 
    std::cout << "x:" << x << ",y:" << y << ",z:" << z << std::endl; };
struct Foo { 
    int f2(int x, int &y, int z = 1) { 
        std::cout << "x:" << x << ",y:" << y << ",z:" << z << std::endl; }; 
};
auto f3 = [](int x, int &y, int z = 1) { 
    std::cout << "x:" << x << ",y:" << y << ",z:" << z << std::endl; };

int main()
{
    int y = 2;
    // 绑定普通函数
    auto fun1 = std::bind(f1, 
                          std::placeholders::_1,  // 占用第1个参数位
                          std::ref(y),            // 给第  2个参数传引用
                          std::placeholders::_2); // 占用第3个参数位
    fun1(1, 3); // x:1,y:2,z:3

    // 绑定类函数
    Foo foo{};
    auto fun2 = std::bind(&Foo::f2, &foo, 
                          std::placeholders::_1, 
                          std::ref(y), 
                          std::placeholders::_2); 
    fun2(1, 3); // x:1,y:2,z:3

    // 绑定lambda
    auto fun3 = std::bind(f3, 
                          std::placeholders::_1, 
                          std::ref(y), 
                          std::placeholders::_2);
    fun3(1, 3); // x:1,y:2,z:3
}
```

### optional

(C++17)`std::optional`可以接受对象或者`nullopt`(表示为空值)

有以下几种方式创建optional：

- 直接创建或者用nullopt赋值

  ```c++
  std::optional<int> empty;
  std::optional<int> opt = std::nullopt;
  ```

- 使用对象初始化

  ```c++
  std::optional<int> opt = 1;
  Some s;
  std::optional<Some> opt = s;
  ```

- 使用`std::make_optional`构造（类似于`std::make_shared`），可以传递参数

  ```c++
  optional<Some> opt = std::make_optional<Some>(1);
  ```

- 使用`std::in_place`构造

  ```c++
  optional<Some> opt = std::in_place<Some>(1);
  ```

```c++
#include <iostream>
#include <optional>
using namespace std;

int main()
{
  std::optional<int> pp = 1;
  if (pp) { cout << *pp << endl; } // 1
  pp = nullopt;
  if (pp) { cout << *pp << endl; } // 不输出
}
```

### &&和move

`&&`叫万能引用(或引用折叠)，右值经过`&&`传递之后，保持不变，依然为右值。

（C++11）`std::move`实施的是无条件的向右值型别的强制型别转换；把对象的所有权从一个对象转移到另一个对象，只转移所有权而没有内存移动或拷贝。

c++使用`std::move`把左值转换为右值，配合`&&`可以进行高效的参数传递。

用途：

- 避免复制入参数据成员的过程产生的复制操作成本；
- 有条件的进行强制类型转换。

```c++
#include <iostream>
#include <string>

int main()
{
    std::string x{"hello"};
    std::string y{};
    y = std::move(x);
    std::cout << "x:" << x << ", y:" << y << std::endl; // x:, y:hello
}
```

### enable_shared_from_this

若一个类T继承`std::enable_shared_from_this<T>`，则会为该类T提供成员函数：`shared_from_this`。当T类型对象t被一个名为pt的`std::shared_ptr<T>`类对象管理时，调用`T::shared_from_this`成员函数，将会返回一个新的`std::shared_ptr<T>`对象，它与pt共享t的所有权。

例：

```c++
#include <memory>
#include <iostream>
struct Good : std::enable_shared_from_this<Good>
{
public:
    std::shared_ptr<Good> getptr() {
        return shared_from_this();
    }
    ~Good() { std::cout << "Good::~Good() called" << std::endl; }
};
int main()
{
    { // 限定作用域，确保智能指针在system("pause")之前析构
        std::shared_ptr<Good> gp1(new Good());
        std::shared_ptr<Good> gp2 = gp1->getptr();
        std::cout << gp1.use_count() << std::endl;
        std::cout << gp2.use_count() << std::endl;
    }
    system("pause");
}
```


---



## 并发编程

TODO

---



## 最佳实践

### 1.选择合适的算法

排序算法：

| 需求                                                         | sort | stable_sort | partial | stable_partition | nth_element |
| ------------------------------------------------------------ | ---- | ----------- | ------- | ---------------- | ----------- |
| 需要对vector，string，deque或者数组中的元素执行一次完全排序  | *    | *           |         |                  |             |
| 有一个vector，string，deque或者数组，并且只需对等价性最前面的n个元素进行排序 |      |             | *       |                  |             |
| 有一个vector，string，deque或者数组，并且需要找到第n个位置上的元素，或者，需要找到等价性最前面的n个元素但又不必对这n个元素进行排序 |      |             |         |                  | *           |
| 需要将一个标准序列容器中的元素按照是否满足某个特定的条件区分开来 |      |             | *       | *                |             |
| 需要对list中的数据排序                                       |      |             | *       | *                |             |

[TOP](#STL)



### 2.选择合适的容器

| 需求                                                         | vector | list | deque | set<br>multiset | map<br>multimap | stack | queue<br>priority queues |
| ------------------------------------------------------------ | ------ | ---- | ----- | --------------- | --------------- | ----- | ------------------------ |
| 在容器的任意位置插入新元素                                   | *      | *    | *     |                 |                 |       |                          |
| 不关心容器中的元素是如何排序的                               |        |      |       |                 |                 |       |                          |
| 随机访问迭代器                                               | *      |      | *     |                 |                 |       |                          |
| 当发生元素的插入或删除操作时，避免移动容器中原来的元素       |        | *    |       | *               | *               |       |                          |
| 数据的布局需要和C兼容                                        | *      |      |       |                 |                 |       |                          |
| 对元素的查找速度敏感                                         | *      |      |       | *               | *               |       |                          |
| 使迭代器，指针或引用变为无效的次数最少                       |        | *    |       |                 |                 |       |                          |
| 使用随机访问迭代器，没有删除操作，且插入操作只发生在容器尾部 |        |      | *     |                 |                 |       |                          |

[TOP](#STL)



### 3.尽量使用empty函数判空而不是检查size()==0

- empty对所有的标准容器的操作都是**常数时间**，且empty函数常常会被内联，而size对于一些list的操作是**线性时间**；

[TOP](#STL)



### 4.区间成员函数优先于与之对应的单元素成员函数

- 通过使用区间成员函数，通常可以少写一些代码；
- 使用区间成员函数通常会得到意图清晰和更加直接的代码；
- 使用单元素的成员函数比使用区间成员函数需要更多地调用内存分配子，更频繁地拷贝对象，且做了冗余操作；
- 当需要给容器一组全新的值时，使用assign而不是operator=；

使用单元素成员函数进行插入：

```c++
int data[numValues];
vector<int> v;
vector<int>::iterator insertLoc(v.begin());
for (int i = 0; i < numValues; ++i) {
    insertLoc = v.insert(insertLoc, data[i]);
    ++insertLoc;
}
```

使用区间成员函数进行插入：

```c++
int data[numValues];
vector<int> v;
v.insert(v.begin(), data, data + numValues); // 使用区间插入效率比单元素插入高得多
```

[TOP](#STL)



### 5.小心C++编译器的分析机制-尽可能地将代码解释为函数声明

错误的做法：

```c++
list<int> data(istream_iterator<int>(dataFile), 
               istream_iterator<int>()); // 参数没有名称，类型是指向不带参数的函数的指针，该函数返回一个istream_iterator<int>
```

正确的做法：

```c++
istream_iterator<int> dataBegin(dataFile);
istream_iterator<int> dataEnd;
list<int> data(dataBegin, dataEnd);
```

[TOP](#STL)



### 6.如果容器中包含了通过new操作创建的指针，切记在容器对象析构前将指针delete掉

- 指针容器在自己被析构时会析构所包含的每个元素，但对指针的析构函数不做处理，也不会调用delete；

  错误的做法：

  ```c++
  void doSomething()
  {
      vector<Widget*> vwp;
      for (int i = 0; i < SOME_MAGIC_NUMBER; ++i)
          vwp.push_back(new Widget); // 使用了new创建指针
  }
  ... // 发生内存泄漏！！！当vwp的作用域结束时，它的元素全部被析构，但是通过new创建的对象没有被删除；
  ```

  正确的做法：

  ```c++
  void doSomething()
  {
      vector<Widget*> vwp;
      for (int i = 0; i < SOME_MAGIC_NUMBER; ++i)
          vwp.push_back(new Widget); // 使用了new创建指针
      
      // 手动释放
      for (vector<Widget*>::iterator i = vwp.begin(); i != vwp.end(); ++i)
          delete *i;
  }
  ```

[TOP](#STL)



### 7.禁止创建包含auto_ptr的容器对象

- COAP（auto_ptr的容器）不可移植；

- 拷贝一个auto_ptr意味着改变它的值；

  ```c++
  auto_ptr<Widget> pw1(new Widget); // pw1指向一个Widget。
  auto_ptr<Widget> pw2(pw1);        // pw2指向pw1的Widget；pw1被置为NULL（Widget的所有权从pw1转移到了pw2）。
  pw1 = pw2;                        // pw1指向Widget，pw2被置为NULL。
  ```

[TOP](#STL)



### 8.STL容器的线程安全性不够

- **多个线程读是安全的**，多个线程可以同时读同一个容器的内容，并且保证是正确的；在读的过程中，不能对容器有任何写入操作；

- **多个线程对不同的容器做写入操作是安全的**，多个线程可以同时对不同的容器做写入操作；

- 建议使用RAII（Resource Acquisition Is Initialization）的方式来手动控制同步；

  ```c++
  TODO
  ```

[TOP](#STL)



### 9.推荐使用vector和string而不是动态分配的数组

- 大多数情况下，推荐使用vector和string替换动态分配的数组；
- 在多线程环境中，推荐使用内置数组代替含有引用计数的string；多线程下，为保证string的引用计数的安全性而采取的措施，会影响效率；

[TOP](#STL)



### 10.使用reserve来避免不必要的重新分配

- 尽早使用reserve，把容器的容量设置为足够大，以避免重新分配；

  ```c++
  vector<int> v;
  v.reserve(1000); // 预先分配容量，防止push_back的过程中进行扩容
  for (int i = 1; i <= 1000; ++i)
      v.push_back(i);
  ```

[TOP](#STL)



### 11.避免使用`vector<bool>`

- `vector<bool>`是一个假的容器，为了节省空间，它并不真的存储bool，而是使用类似1个字节存储8个bool的位域（bitfield）方式来存放；

[TOP](#STL)



### 12.包含指针的关联容器指定比较类型

- 当创建包含指针的关联容器时，容器会按照**指针的值**而不是**指针指向的内容**进行排序；

- 每当创建包含指针的关联容器时，同时也要指定容器的比较类型；

  创建比较函数通用模版：

  ```c++
  struct DereferenceLess // 定义一个比较函数的通用模板
  {
      template<typename PtrType>
      bool operator()(PtrType pT1, PtrType pT2) const 
      {
          return *pT1 < *pT2;
      }
  }
  
  set<string*, DereferenceLess> ssp;
  
  // 普通方法打印
  for (StringPtrSet::const_iterator i = ssp.begin(); i != ssp.end(); ++i)
      cout << i << endl;
  
  // 使用for_each算法打印
  void print(const string *ps)
  {
      cout << *ps << endl;
  }
  for_each(ssp.begin(), ssp.end(), print);
  ```

- `>=`对于关联容器来说不是一个合法的比较函数，相等的值从来不会有前后顺序关系；

  ```c++
  set<int, less_equal<int> > s;
  s.insert(10);
  
  struct StringPtrGreater : public binary_function<const string*, const string*, bool> 
  {
      bool operator()(const string *ps1, const string *ps2) const
      {
          return !(*ps1 < *ps2); // !(<)等价于>=；不能直接把比较结果取反来改变排列顺序，这对于关联容器不是一个合法的比较函数
      }
  };
  ```

[TOP](#STL)



### 13.禁止直接修改set或multiset中的键

- 对于map和multimap，键的类型是const，如果有程序试图修改容器中的键，会影响到容器的排序性，它将无法通过编译；

  ```c++
  map<int, string> m;
  m.begin()->first = 10; // 错误；map的键不能被修改
  
  multimap<int, string> mm;
  mm.begin()->first = 20; // 错误；multimap的键不能被修改
  ```

- 对于set和multiset，修改元素的值这一行为具有不可移植性；

[TOP](#STL)



### 14.当效率至关重要时，根据不同情况选择map::operator[]或map::insert

- 当向映射表中添加元素时，要优先选用insert，而不是operator[]；

  ```c++
  class Widget {
  public:
      Widget();
      Widget(double weight);
      Widget& operator=(double weight);
      ...
  };
  
  map<int, Widget> m;
  // 低效
  m[1] = 1.50; // 效率低，先判断存不存在，存在就更新，不存在就插入（空的map，键1肯定不存在）
  // 高效
  m.insert(IntWidgetMap::value_type(1, 1.50)); // 效率高，不判断直接插入
  ```

- 当更新已经在映射表中的元素的值时，要优先选择operator[]；

[TOP](#STL)



### 15.避免混用不同类型的迭代器，优先使用iterator而不是其它类型的迭代器

- 尽量使用iterator而不是const或reverse型的迭代器，可以使容器的使用更为简单而有效，并且可以避免潜在的问题，原因如下：

  - 有些版本的insert和erase函数要求使用iterator。如果你需要调用这些函数，那你就必须使用iterator。const和reverse型的迭代器不能满足这些函数的要求。
  - 要想隐式地将一个const_iterator转换成iterator是不可能的。
  - 从reverse_iterator转换而来的iterator在使用之前可能需要相应的调整。

- 避免混用不同类型的迭代器；

  ```c++
  typedef deque<int> IntDeque;
  typedef IntDeque::iterator Iter;
  typedef IntDeque::const_iterator ConstIter;
  Iter i;
  ConstIter ci;
  ...
  if (i == ci) // 比较一个iterator和一个const_iterator（iterator在比较前会被隐式转化为const_iterator）
      ...
  ```

[TOP](#STL)



### 16.对于逐个字符的输入考虑使用istreambuf_iterator

- istream_iterator内部执行了格式化输入（构造析构对象，流标志检查，错误检查，...），导致其效率不佳；

  ```c++
  ifstream inputFile("interestingData.txt");
  inputFile.unsetf(ios::skipws); // 禁止忽略空格
  string fileData((istream_iterator<char>(inputFile)), istream_iterator<char>()); // 将inputFile读入fileData
  ```

- istreambuf_iterator从流读取单个字符，从流的缓冲区读取下一个字符，效率更佳；

  ```c++
  ifstream inputFile("interestingData.txt");
  string fileData((istreambuf_iterator<char>(inputFile)), istreambuf_iterator<char>()); // istreambuf_iterator不会跳过任何字符（包括空格）
  ```

[TOP](#STL)



### 17.尽量使用封装技术

- 尽量使用封装（encapsulation）技术来将一种容器类型转换到另一种;

  ```c++
  class Widget {...};
  typedef vector<Widget> WidgetContainer;
  typedef WidgetContainer::iterator WCIterator; // 封装
  WidgetContainer cw;
  Widget bestWidget;
  ...
  WCIterator i = find(cw.begin(), cw.end(), bestWidget);
  ```

- 把容器隐藏在一个类中，并尽量减少那些通过类接口（而使外部）可见的，与容器相关的信息，来减少在替换容器类型时所需要修改的代码；

  ```c++
  class CustomerList {
  private:
    typedef list<Customer> CustomerContainer;
    typedef CustumorContainer::iterator CCIterator;
    
    CustomerContainer customers; // 隐藏容器，通过对外接口访问
  public:
    ...
  };
  ```

[TOP](#STL)



### 18.使用erase-remove方法完全删除元素

- remove不是真正意义上的删除，用remove删除元素，它只是移动被删除的元素到容器**尾部**，而容器中的元素数目并不会减少；

  ```c++
  vector<int> v;
  v.reserve(10);
  for (int i = 1; i <= 10; ++i)
      v.push_back(i);
  
  cout << v.size();               // 输出10
  v[3] = v[5] = v[9] = 99;
  remove(v.begin(), v.end(), 99); // 删除所有值等于99的元素
  cout << v.size();               // 依然输出10
  ```

- 当容器中存放的是指向动态分配的对象的指针的时候，应该避免使用remove和类似的算法（remove_if，unique），因为这样会造成内存泄漏；

  ```c++
  class Widget {
  public:
      bool isCertified() const;
  };
  vector<Widget*> v;
  v.push_back(new Widget);
  
  v.erase(remove_if(v.begin(), v.end(), fun(&Widget::isCertified)), v.end()); // 内存泄漏
  ```

- 推荐使用erase与remove合作（erase-remove）来真正删除元素；

  ```c++
  vector<int> v;
  v.reserve(10);
  for (int i = 1; i <= 10; ++i)
      v.push_back(i);
  
  cout << v.size();                        // 输出10
  v[3] = v[5] = v[9] = 99;
  v.erase(remove(v.begin(), v.end(), 99)); // 删除remove函数返回的迭代器所指向的元素
  cout << v.size();                        // 输出7
  ```

[TOP](#STL)



### 19.使用函数对象而不是函数作为STL算法的参数

- 将函数对象（即可以被伪装成函数的对象）传递给STL算法往往比传递实际的函数更加高效；

  ```c++
  vector<double> v;
  
  sort(v.begin(), v.end(), greater<double>()); // 使用函数对象做参数（高效）
  
  inline bool doubleGreater(double d1, double d2) { return d1 > d2; }
  sort(v.begin(), v.end(), doubleGreater); // 使用函数做参数（低效）
  ```

- 由于编译器或STL的问题，有时候用函数做参数可能会编译不过；

  ```c++
  set<string> s;
  
  // 用函数做参数，可能无法通过编译
  transform(s.begin(), s.end(), ostream_iterator<string::size_type>(count, "\n"), mem_fun_ref(&string::size));
  
  // 用函数对象做参数
  struct StringSize : public unary_function<string, string::size_type> {
      string::size_type operator()(const string& s) const
      {
          return s.size();
      }
  };
  transform(s.begin(), s.end(), ostream_iterator<string::size_type>(count, "\n"), StringSize());
  ```

- 使用函数对象做参数有助于避免一些语言本身的缺陷;

  用函数做参数在语法上没问题，但是有些情况下STL不支持：

  ```c++
  template<typename FPType>
  FPType average(FPType val1, FPType val2)
  {
      return (val1 + val2) / 2;
  }
  template<typename InputIter1, typename InputIter2>
  void writeAverages(InputIter1 begin1, InputIter1 end1, InputIter2 begin2, ostream& s)
  {
      transform(begin1, end1, begin2, 
                ostream_iterator<typename iterator_traits<InputIter1>::value_type(s, "\n")>,
                average<typename iterator_traits<InputIter1>::value_type>); // STL标准不支持，因为它觉得有二义性
  }
  ```

- 函数指针和函数对象在函数之间按值传递（用class/struct包裹的函数例外）；

  ```c++
  // 将函数用class包裹时，强制按引用传递
  class DoSomething : public unary_function<int, void> {
  public:
      void operator()(int x) {...}
  };
  
  typedef deque<int>::iterator DequeIntIter;
  deque<int> di;
  DoSomething d; // 创建一个函数对象
  // 用类型参数DequeIntIter和DoSomething&来调用for_each，这将强制d按引用传递并返回
  for_each<DequeIntIter, DoSomething&>(di.begin(), di.end(), d); 
  ```

[TOP](#STL)



### 20.容器的成员函数优先于同名的算法

- 成员函数往往速度快；
- 成员函数通常与容器（特别是关联容器）结合得更加紧密。

```c++
set<int> s;

set<int>::iterator i = s.find(727); // 使用find成员函数，速度更快
if (i != s.end())
    ...
    
set<int>::iterator i = find(s.begin(), s.end(), 727); // 使用find算法，速度慢
if (i != s.end())
    ...
```

[TOP](#STL)



### 21.确保容器中的对象拷贝正确而高效

- 向容器中填充对象，而对象的拷贝又很费时时，这一操作会成为程序的性能瓶颈；

- 当存在继承关系时，向基类容器的拷贝动作会剥离派生类的信息（拷贝指针时可以避免这个问题）；

  ```c++
  vector<Widget> vw;
  class SpecialWidget : public Widget{...};
  SpecialWidget sw;
  vw.push_back(sw); // 派生类特有的部分在拷贝时被丢弃了
  ```

- 尽量避免不必要的拷贝；

  ```c++
  Widget w[n]; // 创建有n个Widget对象的数组，每个对象都使用默认构造函数来创建（浪费）
  vector<Widget> vw; // 创建了包含0个Widget对象的vector，当需要时它会增长（避免了拷贝）
  ```

[TOP](#STL)

---



## 参考

[1] 侯捷.STL源码剖析.1th Edition

[2] [C++参考手册](https://zh.cppreference.com/w/%e9%a6%96%e9%a1%b5)

[3] [美]Scott Meyers.Effective STL.1th Edition
