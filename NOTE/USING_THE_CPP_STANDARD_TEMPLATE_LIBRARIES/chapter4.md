# 第四章 map容器
## 摘要

## 详情
map容器的比较函数在相等时不能返回true

### map类型
* map<K, T>容器保存的是pair<const K, T>类型的元素。
* multimap<K, T>容器和map<K, T>容器类似，允许使用重复的键。
* unordered_map<K, T>中pair<const K, T>元素的顺序并不是直接由键值确定的，而是由键值的哈希值决定的。
* unordered_multimap<K, T>也可以通过键值生成的哈希值来确定对象的位置，但它允许有重复的键。

### pair
pair的成员变量second也是一个迭代器，它指向键值大于参数的第一个参数

### map类函数
|函数成员|说明|
|:--|:--|
|begin()|头迭代器|
|end()|尾迭代器|
|insert()|插入键值对|
|emplace()|构造新元素|
|emplace_hint()|在迭代器后面构造新元素|
|operator[]()|索引|
|at()|根据key找alue|
|equal_range()|遍历查找key|
|upper_bound()|-|
|lower_bound()|-|
|erase()|删除元素|
|lower_bound()|返回一个迭代器，指向键值和参数相等或大于参数的第一个元素，或指向结束迭代器|
|upper_bound()|返回一个迭代器，指向键值大于函数参数的第一个元素，如果这样的元素不出现的话，他就是一个结束迭代器|
|rehash()|设置格子数量|
|clear()|移除所有元素|
|empty()|是否为空|
|bucket_count()|返回格子个数|
|bucket_size()|返回指定格子中元素的个数|

## 总结
* pair<T1, T2>对象封装了一个任意类型的对象
* tuple<>模板类型的实例可以封装任意个数不同类型的对象
* map容器是以pair<const K, T>对象的形式来保存键/对像对元素的
* map<K,T>容器保存的元素有唯一的键值，默认使用<运算符来对键进行排序，所以键类型必须支持<运算，除非自己提供一个比较函数
* multimap<K,T>包含的元素和map一样，都是有序的，但允许有重复的键
* 有序关联容器用等价来决定两个键什么时候是相同的。通常只用<或>来比较键，生成比较结果。当键相等时，比较函数会返回true，从而阻止容器正常工作
* 哈希是从对象生成名为哈希值的相对唯一整数的过程。
* 使用键生成的哈希值将元素保存在unordered_map<K,T>容器中
* unordered_multimap容器和unordered_map相似
* 无序map容器默认使用equal_to<K>来比较键是否相等，所以键类型必须支持==比较和键对象的哈希