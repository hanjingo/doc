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

- copy(拷贝)
- swap(交换)
- replace(替换)
- fill(填充)
- remove(删除)
- permutation(排列组合)
- partition(分割)
- random shuffling(随机重排)
- sort(排序)
- ...

### 非质变算法non mutating algorithms-不改变操作对象的值

- find(查找)
- search(匹配)
- count(计算)
- for_each(巡访)
- equal, mismatch(比较)
- max, min(寻找极值)
- ...

### STL算法的一般形式

所有泛型算法的前两个参数都是一对迭代器，STL 习惯使用前闭后开的区间，`[first, last)`。

最后一个元素的下一位置，称为 end()。

---

## 数值算法 <stl_numeric.h>

STL 将数值算法的内部实现放在 <stl_numeric.h> 中，用户调用数值算法的接口，需要包含 <numeric> 头文件。

- accumulate

计算 init 和 `[first, last)`内所有元素的总和。

- adjacent_difference

计算`[first, last)`中相邻元素的差值，将 `*first` 赋值给 `*result` 并针对`[first+1, last)`内的每个迭代器i，将`*i-*(i-1)`之值赋值给`*(result+(i-first))`。

- inner_product

计算`[first1, last1)`和`[first2, first2 + (last1 - first1))`的一般内积。

- partial_sum

计算局部总和，将`*first`赋值给`*result`，将`*first`和`*(first+1)`之和赋值给`*(result+1)`。

- power

SGI专属，并不在STL标准之列。计算某数的n幂次方。

- itoa

SGI专属，并不在STL标准之列。用来设定某个区间的内容，使其内的每个元素从指定的value值开始，呈现递增状态。



---

## 基本算法 <stl_algobase.h>

- equal

如果两个序列在`[first,last)`区间内相等，equal()返回true。

**注意：如果第二序列的元素比较多，多出来的元素不予考虑。**

- fill

将`[first, last)`内的所有元素改填新值。

- fill_n

将`[first, last)`内的前n个元素改填新值，返回的迭代器指向被填入的最后一个元素的下一个位置。

- iter_swap

将两个 ForwardIterators 所指的对象对调，如图：

![](res/iter_swap.png)

- Lexicographical_compare

以“字典排列方式”对两个序列`[first1,last1)`和`[first2,last2)`进行比较。

- max

取两个对象中的较大值。

- min

取两个对象中的较小值。

- mismatch

用来平行比较两个序列，指出两者之间的第一个不匹配点，返回一对迭代器，分别指向两个序列中的不匹配点，如图：

![](res/mismatch.png)

- copy

将输入区间[first,last)内的元素复制到输出区间[result,result+(last-first))内.

![6-2](res/6-2.png)

- copy_backward

将`[first,last)`区间内的每一个元素，以逆行的方向复制到以result-1为起点，方向亦为逆行的区间上。

![6-4](res/6-4.png)



---

## set相关算法

### set_union

构造两个集合的并集，是一种稳定操作，输入区间内的每个元素的相对顺序都不会改变。

![6-5a](res/6-5a.png)

### set_intersection

构造两个集合的交集，是一种稳定操作，输出区间内的每个元素的相对顺序都和s1内的相对顺序相同。

![](res/6-5b.png)

### set_difference

构造两个集合的差集，是一种稳定操作，输出区间内的每个元素的相对顺序都和s1内的相对顺序相同。

![](res/6-5c.png)

### set_symmetric_difference

构造两个集合的差集，输入区间内的元素相对顺序不会被改变。

![](res/6-5d.png)

---

## heap算法

<stl_heap.h>

- make_heap 

建堆

- pop_heap

从堆中取出一个元素

- push_heap(
    
将一个元素推进堆内

- sort_heap

对堆排序

---

## 其它算法

<stl_algo.h>

- adjacent_find

找出第一组满足条件的相邻元素。

- count

运用equality操作符，将[first,last)区间内的每一个元素拿来和指定值value比较，并返回与value相等的元素个数。

- count_if

将指定操作（一个仿函数）pred实施于`[first,last)`区间内的每一个元素身上，并将使pred的计算结果为true的所有元素的个数返回。

- find

根据equality操作符，循序查找`[first,last)`内的所有元素，找出第一个匹配"等同(equality)条件"者。如果找到，就返回一个InputIterator指向该元素，否则返回迭代器last。

- find_if

根据指定的pred运算条件(以仿函数表示)，循序查找`[first,last)`内的所有元素，找出第一个令pred运算结果为true者。如果找到就返回一个InputIterator指向该元素，否则返回迭代器last。

- find_end

在序列一`[first1,last1)`所涵盖的区间中，查找序列二`[first2,last2)`的最后一次出现点。如果序列一之内不存在“完全匹配序列二”的子序列，便返回迭代器last1。

![6-6a](res/6-6a.png)

- find_first_of

以`[first2,last2)`区间内的某些元素作为查找目标，寻找它们在`[first1,last1)`区间内的第一次出现地点。

- for_each

将仿函数f施行与`[first,last)`区间内的每一个元素身上。f不可以改变元素内容，因为first和last都是InputIterators，不保证接受赋值行为(assignment)。

- generate

将仿函数gen的运算结果填写在`[first,alst)`区间内的所有元素身上。所谓填写，用的是迭代器所指元素之assignment操作符。

- generate_n

将仿函数gen的运算结果填写在从迭代器first开始的n个元素身上。所谓填写，用的是迭代器所指元素的assignment操作符。

- includes

判断序列二s2是否包含于序列一s1。s1和s2都必须是有序集合，其中的元素都可以重复（不必唯一）。

!![6-6b]()

- max_element

返回一个迭代器，指向序列中数值最大的元素。

- merge(应用于有序区间)

将两个经过排序的集合s1和s2，合并起来置于另一段空间。所得结果也是一个有序(sorted)序列。返回一个迭代器，指向最后结果序列的最后一个元素的的下一个位置。

![6-6c]()

- min_element

返回一个迭代器，指向序列之中数值最小的元素。

- partition

将区间`[first,last)`中的元素重新排列。所有被一元条件运算pred判定为true的元素，都会被放在区间的前段，被判定为false的元素，都会被放在区间的后段。

![6-6d]()

- remove

移除`[first,last)`之中所有与value相等的元素。

这一算法并不真正从容器中删除那些元素（换句话说容器大小并未改变），而是将每一个不予value相等（也就是我们并不打算移除）的元素轮番赋值给first之后的空间。

**注意，array不适合使用remove()和remove_if(), 因为array无法缩小尺寸，导致残余数据永远存在。对array而言，较受欢迎的算法是remove_copy()和remove_copy_if()。**

![6-6e]()

- remove_copy

移除`[frist,last)`区间内所有与value相等的元素。

它并不真正从容器中删除那些元素（换句话说，原容器没有任何改变），而是将结果复制到一个以result标示起始位置的容器身上。

- remove_if

移除`[first,last)`区间内所有被仿函数pred确定为true的元素。

![6-6f]()

- remove_copy_if

移除`[first,last)`区间内所有被仿函数pred评估为true的元素。

它并不真正从容器中删除那些元素（换句话说，原容器没有任何改变），而是将结果复制到一个以result标示起始位置的容器身上。

- replace

将`[first,last)`区间内的所有old_value都以new_value取代。

- replace_copy

行为与replace()类似，唯一不同的是新序列会被复制到result所指的容器中。返回值OutputIterator指向被复制的最后一个元素的下一位置。原序列没有任何改变

- replace_if

将`[first,last)`区间内所有被pred评估为true的元素，都以new_value取而代之。

- replace_copy_if

行为与replace_if()类似，但是新序列会被复制到result所指的区间内。返回值OutputIterator指向被复制的最后一个元素的下一个位置。

- reverse

将序列`[first,last)`的元素在原容器中颠倒重排。

- reverse_copy

行为类似reverse()，但产生出来的新序列会被置于

---

