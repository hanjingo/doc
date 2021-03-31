# 算法
## 算法概观
### 算法分析与复杂度表示O()
算法分析(algorithm analysis)

> 分析算法所耗用的空间和时间资源

大O标记法

> 如果有任何正值常数c和$N_0$时，使得当$N \geq N_0$时，$T(N) \leq cF(N)$，那么我们便可将T(N)的复杂度表示为$O(F(N))^3$


### STL算法总览
|算法名称|算法用途|mutating|所在文件|
|:--|:--|:--|:--|
|accumulate|元素累计|N|<stl_numeric.h>|
|adjacent_difference|相邻元素的差|Y if in-place|<stl_numeric.h>|
|adjacent_find|查找相邻而重复（或符合某条件）的元素|N|<stl_algo.h>|
|binary_search|二分查找|N|<stl_algo.h>|
|Copy|复制|Y if in-place|<stl_algobase.h>|
|Copy_backward|逆向复制|Y if in-place|<stl_algobase.h>|
|Copy_n *|复制n个元素|Y if in-place|<stl_algobase.h>|
|count|计数|N|<stl_algo.h>|
|count_if|在特定条件下计数|N|<stl_algo.h>|
|equal|判断两个区间相等与否|N|<stl_alogbase.h>|
|equal_range|试图在有序区间中寻找某值(返回一个上下限区间)|N|<stl_algo.h>|
|fill|改填元素值|Y|<stl_algobase.h>|
|fill_n|改填元素值，n次|Y|<stl_algobase.h>|
|find|循序查找|N|<stl_algo.h>|
|find_if|循序查找符合特定条件者|N|<stl_algo.h>|
|find_end|查找某个子序列的最后一次出现点|N|<stl_algo.h>|
|find_first_of|查找某些元素的首次出现点|N|<stl_algo.h>|
|for_each|对区间内的每个元素施行某操作|N|<stl_algo.h>|
|generate|以特定操作之运算结果填充特定区间内的元素|Y|<stl_algo.h>|
|generate_n|以特定操作之运算结果填充特n个元素内容|Y|<stl_algo.h>|
|includes|是否涵盖于某序列之中|N|<stl_algo.h>|
|inner_product|内积|N|<stl_numeric.h>|
|inplace_merge|合并并就地替换(覆写上去)|Y|<stl_algo.h>|
|Iota*|在某区间填入某指定值的递增序列|Y|<stl_numeric.h>|
|is_heap*|判断某区间是否为一个heap|N|<stl_algo.h>|
|is_sorted*|判断某区间是否已排序|N|<stl_algo.h>|
|iter_swap|元素互换|Y|<stl_algobase.h>|
|lexicographical_compare|以字典顺序进行比较|N|<stl_numeric.h>|
|lower_bound|将指定元素插入区间之内而不影响区间之原本排序的最低位置|N|<stl_algo.h>|
|max|最大值|N|<stl_algobase.h>|
|max_element|最大值所在位置|N|<stl_algo.h>|
|merge|合并两个序列|Y if in-place|<stl_algo.h>|
|min|最小值|N|<stl_algobase.h>|
|min_element|最小值所在位置|N|<stl_algo.h>|
|mismatch|找出不匹配点|N|<stl_algobase.h>|
|next_permutation|获得的下一个排列组合|Y|<stl_algo.h>|
|nth_element|重新安排序列中的第n个元素的左右两端|Y|<stl_algo.h>|
|partial_sort|局部排序|Y|<stl_algo.h>|
|partial_sort_copy|局部排序并复制到他处|Y if in-place|<stl_algo.h>|
|partial_sum|局部求和|Y if in-place|<stl_numeric.h>|
|partition|分割|Y|<stl_algo.h>|
|prev_permutation|获得前一个排列组合|Y|<stl_algo.h>|
|power*|幂次方。表达式可指定|N|<stl_numeric.h>|
|random_shuffle|随机重排元素|Y|<stl_algo.h>|
|random_sample*|随机取样|Y if in-place|<stl_algo.h>|
|random_sample_n*|随机取样|Y if in-place|<stl_algo.h>|
|remove|删除某类元素|Y|<stl_algo.h>|
|remove_copy|删除某类元素并将结果复制到另一个容器|Y|<stl_algo.h>|
|remove_if|有条件地删除某类元素|Y|<stl_algo.h>|
|remove_copy_if|有条件地删除某类元素并将结果复制到另一个容器|Y|<stl_algo.h>|
|replace|替换某类元素|Y|<stl_algo.h>|
|replace_copy|替换某类元素,并将结果复制到另一个容器|Y|<stl_algo.h>|
|replace_if|有条件地替换|Y|<stl_algo.h>|
|replace_copy_if|有条件地替换，并将结果复制到另一个容器|Y|<stl_algo.h>|
|reverse|反转元素次序|Y|<stl_algo.h>|
|reverse_copy|反转元素次序并将结果复制到另一个容器|Y|<stl_algo.h>|
|rotate|旋转|Y|<stl_algo.h>|
|rotate_copy|旋转，并将结果复制到另一个容器|Y|<stl_algo.h>|
|search|查找某个子序列|N|<stl_algo.h>|
|search_n|查找“连续发生n次”的子序列|N|<stl_algo.h>|
|set_difference|差集|Y if in-place|<stl_algo.h>|
|set_intersection|交集|Y if in-place|<stl_algo.h>|
|set_symmetric_difference|对称差集|Y if in-place|<stl_algo.h>|
|set_union|并集|Y if in-place|<stl_algo.h>|
|sort|排序|Y|<stl_algo.h>|
|stable_partition|分割并保持元素的相对次序|Y|<stl_algo.h>|
|stable_sort|排序并保持等值元素的相对次序|Y|<stl_algo.h>|
|swap|交换（对调）|Y|<stl_algobase.h>|
|swap_range|交换（指定区间）|Y|<stl_algo.h>|
|transform|以两个序列为基础，交互作用产生第三个序列|Y|<stl_algo.h>|
|unique|将重复的元素折叠缩编，变成唯一|Y|<stl_algo.h>|
|unique_copy|将重复的元素折叠缩编，变成唯一，并复制到他处|Y if in-place|<stl_algo.h>|
|upper_bound|将指定元素插入区间之内而不影响区间之原本排序的最高位置|N|<stl_algo.h>|
|make_heap|制造一个heap|Y|<stl_heap.h>|
|pop_heap|从heap取出一个元素|Y|<stl_heap.h>|
|push_heap|将一个元素推进heap内|Y|<stl_heap.h>|
|sort_heap|对heap排序|Y|<stl_heap.h>|

mutating: 质变，会改变其操作对象之内容

### 质变算法mutating algorithms-会改变操作对象的值