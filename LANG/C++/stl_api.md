[TOC]
# STL速查手册

## vector(向量容器)

|函数|描述|
|:--|:--|
|assign |对vector中的元素赋值 |
|at |返回指定位置的元素 |
|back |返回最后一个元素 |
|begin |返回第一个元素的迭代器 |
|capacity |返回vector所能容纳的元素数量(再不重新分配内存的情况下) |
|clear |清空所有元素 |
|empty |判断vector是否为空 |
|end |返回最后一个元素的迭代器,此迭代器指向最后一个元素的下一个位置 |
|erase |删除指定元素 |
|front |返回第一个元素的引用 |
|get_allocator |返回vector的内存分配器 |
|insert |插入元素到vector中 |
|max_size |返回vector所能容纳元素的最大数量(上限) |
|pop_back |移除最后一个元素 |
|push_back |在vector最后添加一个元素 |
|rbegin |返回vector尾部的逆迭代器 |
|rend |返回vector起始的逆迭代器 |
|reserve |设置vector最小的元素容纳数量，为当前vector预留至少size个元素的空间 |
|resize |改变vector元素数量的大小 |
|size |返回vector元素数量的大小 |
|swap |交换两个vector |



## list(双向链表)

|函数|描述|
|:--|:--|
|assign |给list赋值 |
|back |返回最后一个元素的引用 |
|begin |返回指向第一个元素的迭代器 |
|clear |删除所有元素 |
|empty |如果list是空的则返回true |
|end |返回末尾的迭代器 |
|erase |删除一个元素 |
|front |返回第一个元素的引用 |
|get_allocator |返回list的配置器 |
|insert |插入一个元素到list中 |
|max_size |返回list能容纳的最大元素数量 |
|merge |合并2个list |
|pop_back |删除最后一个元素 |
|pop_front |删除第一个元素 |
|push_back |在list的末尾添加一个元素 |
|push_front |在list的头部添加一个元素 |
|rbegin |返回指向第一个元素的逆向迭代器 |
|remove |从list删除元素 |
|remove_if |按指定条件删除元素 |
|rend |指向list末尾的逆向迭代器 |
|resize |改变list的大小 |
|reverse |把list的元素倒转 |
|size |返回list中的元素个数 |
|sort |给list排序 |
|splice |合并2个list |
|swap |交换2个list |
|unique |删除list中重复的元素 |



## deque(双向队列)

|函数|描述|
|:--|:--|
|assign |设置双向队列的值 |
|at |返回指定的元素 |
|back |返回最后一个元素 |
|begin |返回指向第一个元素的迭代器 |
|clear |删除所有元素 |
|empty |双向队列是否为空 |
|end |返回指向尾部的迭代器 |
|erase |删除一个元素 |
|front |返回第一个元素的引用 |
|get_allocator |返回双向队列的配置器 |
|insert |插入一个元素到双向队列中 |
|max_size |返回双向队列能容纳的最大元素个数 |
|pop_back |删除尾部的元素 |
|pop_front |删除头部的元素 |
|push_back |在尾部加入一个元素 |
|push_front |在头部加入一个元素 |
|rbegin |返回指向尾部的逆向迭代器 |
|rend |返回指向头部的逆向迭代器 |
|resize |改变双向队列的大小 |
|size |返回双向队列中元素的个数 |
|swap |和另一个双向队列交换元素 |



## set & multisets

|函数|描述|
|:--|:--|
|begin |返回指向第一个元素的迭代器 |
|clear |清除所有元素 |
|count |返回某个值元素的个数 |
|empty |如果集合为空，返回true |
|end |返回指向最后一个元素的迭代器 |
|equal_range |返回第一个>=关键字的迭代器和>关键字的迭代器 |
|erase |删除集合中的元素 |
|find |返回一个指向被查找到元素的迭代器 |
|get_allocator |返回集合的分配器 |
|insert |插入元素 |
|lower_bound |返回指向大于或等于某个值的第一个元素的迭代器 |
|key_comp |返回一个用于元素间比较的函数 |
|max_size |返回集合能容纳的元素的最大数 |
|rbegin |返回指向集合中最后一个元素的方向迭代器 |
|rend |返回指向集合中第一个元素有的反向迭代器 |
|size |集合中元素的数目 |
|swap |交换两个集合变量 |
|upper_bound |返回大于某个值元素的迭代器 |
|value_comp |返回一个用于比较元素间的值的函数 |



## maps & multimaps

|函数|描述|
|:--|:--|
|begin |返回指向map头部的迭代器 |
|clear |删除所有元素 |
|count |返回指定元素出现的次数 |
|empty |如果map为空则返回true |
|end |返回指向map末尾的迭代器 |
|equal_range |返回特殊条目的迭代器对 |
|erase |删除一个元素 |
|find |查找一个元素 |
|get_allocator |返回map的配置器 |
|insert |插入元素 |
|key_comp |返回比较元素key的函数 |
|lower_bound |返回键值>=给定元素的第一个位置 |
|max_size |返回可以容纳的最大元素个数 |
|rbegin |返回一个指向map尾部的逆向迭代器 |
|rend |返回一个指向map头部的逆向迭代器 |
|size |返回map中元素的个数 |
|swap |交换2个map |
|upper_bound |返回键值>给定元素的第一个位置 |
|value_comp |返回比较元素value的函数 |



## stack

|函数|描述|
|:--|:--|
|empty |堆栈是否为空 |
|pop |移除栈顶元素 |
|push |在栈顶增加元素 |
|size |返回栈中元素数目 |
|top |返回栈顶元素 |



## queue

|函数|描述|
|:--|:--|
|back |返回一个引用，指向最后一个元素 |
|empty |如果队列空则返回真 |
|front |返回第一个元素 |
|pop |删除第一个元素 |
|push |在末尾加入一个元素 |
|size |返回队列中元素的个数 |



## priority queues

|函数|描述|
|:--|:--|
|empty |判断优先队列是否为空 |
|pop |删除第一个元素 |
|push |加入一个元素 |
|size |返回优先队列中拥有的元素个数 |
|top |返回优先队列中有最高优先级的元素 |



## 算法

|函数|描述|
|:--|:--|
|binary_search|二分查找法，应用于有序区间；试图在已排序的`[first,last)`中寻找元素value。如果`[first,last)`内有等同于value的元素，便返回true，否则返回false|
|copy|将输入区间`[first,last)`内的元素复制到输出区间`[result,result+(last-first))`内|
|for_each |对序列中每个元素执行操作 |
|find |在序列中找某个值的第一个出现 |
|lower_bound |二分查找(binary search)的一种版本，应用于有序区间；他会返回一个迭代器，指向第一个“不小于value”的元素。如果value大于`[first,last)`内的任何一个元素，则返回last |
|max |取两个对象中的较大值 |
|min |取两个对象中的较小值 |
|mismatch |用来平行比较两个序列，指出两者之间的第一个不匹配点，返回一对迭代器，分别指向两个序列中的不匹配点 |
| merge          | 将两个有序的集合合并起来，放置于另一段空间                   |
| random_shuffle | 将`[first,last)`的元素次序随机重排                           |
|reverse |将序列`[first,last)`的元素在原容器中颠倒重排 |
|remove |移除`[first,last)`之中所有与value相等的元素 |
|replace |将`[first,last)`区间内的所有old_value都以new_value取代 |
|rotate |将`[first,middle)`内的元素和`[middle,last)`内的元素互换。middle所指的元素会成为容器的一个元素 |
|search |在序列一`[first1,last1)`所涵盖的区间中，查找序列二`[first2,last2)`的首次出现点。如果序列一内不存在与序列二完全匹配的子序列，便返回迭代器last1 |
|sort |排序；数据量大时采用Quick Sort，分段式递归排序；数据量小于某个门槛时，为避免Quick Sort的递归调用带来过大的额外负担，就改用Insertion Sort；如果递归层次过深，还会改用Heap Sort。 |
|unique |移除(remove)重复的元素，事实上unique并不会改变`[first,last)`的元素个数，有一些残余数据会留下来 |
|upper_bound |二分查找(binary search)法的一个版本，“查找可插入value的最后一个合适位置” |
