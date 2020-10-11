# STL常用算法
* generate(Fwd_Iter beg, Fwd_Iter end, Fun_Object gen_fun)会将gen_fun返回的值保存到序列[beg,end)的每一个元素中。gen_fun必须是无参数的，并且必须能够返回一个可以保存到序列中的值。
* copy(Input_Iter beg1, Input_Iter end1, Output_Iter beg2) *会将序列[beg1, end1)复制到序列beg2的开始处。它返回的迭代器指向最后一个被复制到目的位置的元素的下一个位置。

# STL常用数据结构及其函数

## array

## vector

## deque

## list

## forward_list
在指定位置的后面插入一条或多个元素:

insert_after