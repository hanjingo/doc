# STL 常用函数
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
|