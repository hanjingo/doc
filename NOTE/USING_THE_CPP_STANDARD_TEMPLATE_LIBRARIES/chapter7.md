# 第七章 更多的算法

## 摘要
* 检查序列中元素的属性的算法
* 计算序列中有指定书香的元素个数的算法
* 比较两个序列中元素的算法
* 用来复制或移动序列的算法
* 设置或改变序列中元素的算法
  
## 详情
#### 在序列中找出具有指定属性的元素的个数
* **all_of(Input_Iter beg, Input_Iter end, Unary_Predicate p)** 返回true, 如果p对[beg, end)中的全部元素都返回true.
* **any_of(Input_Iter beg, Input_Iter end, Unary_Predicate p)** 返回true，如果p对[beg,end)中的任意一个元素返回true.
* **none_of(Input_Iter beg, Input_Iter end, Unary_Predicate p)** 返回true, 如果p对[beg,end)中的所有元素都返回false;
* **count(Input_Iter beg, Input_Iter end, const T& obj)** 返回[beg,end)中等于obj的元素的个数;
* **count_if(Input_Iter beg, Input_Iter end, Unary_Predicate p)** 返回[beg, end)中使p返回true的元素个数
#### 比较序列
* **equal(Input_Iter1 beg1, Input_Iter1 end1, Input_Iter2 beg2)** 返回true, 如果序列[beg1,end1)同beg2开始处对应的元素相等。
* **equal(Input_Iter1 beg1, Input_Iter1 end1, Input_Iter2 beg2, Input_Iter2 end2)** 返回true, 如果序列[beg1, end1)中的元素和序列[beg2, end2)中对应的元素相等。
* **equal(Input_Iter1 beg2, Input_Iter1 end1, Input_Iter2 beg2, Binary_Predicate p)** 返回true，如果p为序列[beg2, end1)和序列beg2开始处对应的元素返回true。
* **equal(Input_Iter1 beg1, Input_Iter1 end1, Input_Iter2 beg2, Input_Iter2 end2, Binary_Predicate p)** 返回true，如果p为[beg1, end1)和[beg2, end2)中对应的元素返回true。
* **mismatch(Input_Iter1 beg1, Input_Iter1 end1, Input_Iter2 beg2)** 返回一个pair<Input_Iter1, Input_Iter2>对象，它包含第一对不相等元素的迭代器。
* **mismatch(Input_Iter1 beg1, Input_Iter1 end1, Input_Iter2 beg2, Input_Iter2 end2)** 的返回和值上一个版本相同。
* **mismatch(Input_Iter1 beg1, Input_Iter1 end1, Input_Iter2 beg2, Binary_Predicate p)** 返回一个pair<Input_Iter1, Input_Iter2>对象，它包含第一对使p返回false的元素的迭代器。
* **mismatch(Input_Iter1 beg1, Input_Iter1 end1, Input_Iter2 beg2, Input_Iter2 end2, Binary_Predicate p)** 的返回值和上一个版本相同。
* **lexicographical_compare(Input_Iter1 beg1, Input_Iter1 end1, Input_Iter2 beg2, Input_Iter2 end2)** 返回true1, 如果这两个序列包含的元素个数相同，并且对应元素相等；否则返回false。
* **lexicographical_compare(Input_Iter1 beg1, Input_Iter1 end1, Input_Iter2 beg2, Input_Iter2 end2, Binary_Predicate p)** 返回true，如果这2个序列包含的元素个数相同，并且为所有对应的元素对p都返回true；否则返回false；
#### 排列元素序列
* **next_permutation(Bi_Iter beg, Bi_Iter end)** 会按字典序的升序来生成元素的下一个排列，并返回true，如果存在下一个排列的话。否则，元素会被排为序列的第一排列，算法会返回false。
* **next_permutation(Bi_Iter beg, Bi_Iter end, Compare compare)** 会基于元素的比较函数compare，按照字典序生成元素的下一个排列，并返回true。如果不存在下一个排列，元素会被排为基于compare的第一个序列，算法返回false。
* **prev_permutation(Bi_Iter beg, Bi_Iter end)** 会按字典序的升序生成元素的前一个排列，并返回true，如果存在前一个排列的话。否则，元素会被排为序列中的最后一个排列，算法返回false。
* **prev_permutation(Bi_Iter beg, Bi_Iter end, Compare compare)** 会基于元素的比较函数compare，按照字典序生成元素的前一个排列，并返回true。如果不存在前一个排列，元素会被排为基于compare的序列的最后一个排列，否则返回false。它用==来比较元素。
* **is_permutation(Fwd_Iter1 beg2, Fwd_Iter1 end1, Fwd_Iter2 beg2)** 返回true，如果从beg2开始的元素序列(end1, beg1)是序列[beg1, end1)的一个排列，否则返回false。它用==来比较元素。
* **is_permutation(Fwd_Iter1 beg1, Fwd_Iter1 end1, Fwd_Iter2 beg2, Binary_Predicate p)** 和前一个版本相同，除了它是用p来比较元素是否相等之外。
* **is_permutation(Fwd_Iter1 beg1, Fwd_Iter1 end1, Fwd_Iter2 beg2, Fwd_Iter2 end2)** 返回true，如果[beg2, end2)是序列[beg1, end1)的一个排列，否则返回false。它用==来比较元素。
* **is_permutation(Fwd_Iter1 beg1, Fwd_Iter1 end1, Fwd_Iter2 beg2, Fwd_Iter2 end2, Binary_Predicate p)** 和前一个版本相同，除了他是用p来比较元素是否相等之外。
#### 从序列中复制元素
* **copy(Input_Iter beg1, Input_Iter end1, Output_Iter beg2)** *会将序列[beg1, end1)复制到序列beg2的开始处。它返回的迭代器指向最后一个被复制到目的位置的元素的下一个位置。
* **copy_n(Input_Iter beg1, Int_Type n, Output_Iter beg2)** 会从序列[beg1, end1)复制n个元素到beg2的开始位置。它返回的迭代器指向最后一个被复制到目的位置的元素的下一个位置。
* **copy_if(Input_Iter beg1, Input_Iter end1, Output_Iter beg2, Unary_Predicate p)** 会从序列beg1的开始位置复制使p返回true的元素到beg2的开始位置。它返回的迭代器指向最后一个呗复制到目的位置的元素的下一个位置。
* **copy_backward(Bi_Iter1, Input_Iter1 end1, Bi_Iter2 end2)** 会将序列[beg1, end1)复制到序列end2的末尾。这个操作会从end1-1指向的元素开始反向复制元素。算法会返回一个地带器iter，它指向被复制到目的位置的最后一个元素，因此在这个操作之后目的序列为[iter, end2)。
* **reverse_copy(Bi_Iter beg1, Bi_Iter end1, Output_Iter beg2)** 会反向的将[beg1, end1)复制到目的序列beg2的开始位置，并返回一个迭代器iter,它指向被复制到目的位置的最后一个元素的下一个位置。因此，[beg2, iter)会以逆序包含[beg1, end1)中的元素。
* **reverse(Bi_Iter beg, Bi_Iter end)** 会反转序列[beg, end)中元素的顺序。
* **unique_copy(Input_Iter beg1, Input_Iter end1, Output_Iter beg2)** 会忽略持续的重复元素，将序列[beg1, end1)复制到序列beg2的开始位置。他是用==来比较元素的，它返回一个指向被复制到目的位置的最后一个元素的下一个位置的迭代器。
* **unique_copy(Input_Iter beg1, Input_Iter end1, Output_Iter beg2, Binary_Predicate p)** 所做的事和上一个版本相同，除了他是用p来比较元素之外。
* **unique(Fwd_Iter beg, Fwd_Iter end, Binary_Predicate p)** 和前一个算法做相同的事情，除了用p来比较元素之外。
#### 移动序列
* move(Input_Iter beg1, Input_Iter end1, Output_Iter beg2)会将序列[beg1, end1)移到序列beg2的开始位置。他会返回一个指向最后一个被移到目的位置的元素的下一个位置的迭代器。beg2不能在[beg1, end1)之内。
* move_backward(Bi_Iter1 beg1, Bi_Tter1 end1, Bi_Iter2 end2)会将序列[beg1, end1)移到序列end2的末尾，并且元素是以逆序移动的。算法会返回一个指向最后一个被移到目的位置的元素的迭代器。end2不能再[beg1, end1)之内。
#### 旋转元素的序列
* rotate(Fwd_Iter beg, Fwd_Iter new_beg, Fwd_Iter end)会按逆时针旋转[beg, end)中的元素，从而使new_beg成为序列的第一个元素。算法会返回一个指向序列原始的第一个元素的迭代器。
* rotate_copy(Fwd_Iter beg1, Fwd_Iter new_beg1, Fwd_Iter end1, Output_Iter beg2)会将[beg1, end1)中所有元素都复制到序列beg2的开始位置，从而使new_beg1指向的元素成为目的序列的第一个元素。算法会返回一个指向目的序列中的最后一个元素的下一个位置的迭代器。
#### 从序列中移除元素
* remove(Fwd_Iter beg, Fwd_Iter end, const T& obj)可以从[beg, end)中移除等于obj的元素，并返回一个迭代器，它指向结果序列中最后一个元素的下一个位置。
* remove_if(Fwd_Iter beg, Fwd_Iter end, Unary_Predicate p)可以从[beg, end)中移除使p为true的元素，并返回一个迭代器，它指向结果序列中最后一个元素的下一个位置。
* remove_coy(Input_Iter beg1, Input_Iter end1, Output_Iter beg2, const T& obj)会将[beg1, end1)中的元素复制到beg2的开始位置，它会跳过等于obj的元素，并返回一个迭代器，它指向目的位置最后一个元素的下一个位置。
* remove_copy_if(Input_Iter beg1, Input_Iter end1, Outpu_Iter beg2, Unary_Predicate p)会将[beg1, end1)中的元素复制到beg2的开始位置，它它会跳过使p返回true的元素，并返回一个迭代器，它指向目的位置最后一个元素的下一个位置。
#### 替换序列中的元素
* replace(Fwd_Iter beg, Fwd_Iter end, const T& obj, const T& new_obj)会用new_obj替换[beg, end)中等于obj的元素。
* replace_if(Fwd_Iter beg, Fwd_Iter end, Unary_Predicate p, const T& new_obj)会用new_obj替换[beg, end)中使p返回true的元素。
* replace_copy(Input_Iter beg1, Input_Iter end1, Output_Iter beg2, const T& obj, const T& new_obj)会将[beg1, end1)中的元素复制到序列beg2的开始位置，并用new_obj替换等于obj的元素。该算法返回一个迭代器，它指向目的位置最后一个元素的下一个位置。序列不能是重叠的。
* replace_copy_if(Input_Iter beg1, Input_Iter end1, Output_Iter beg2, Unary_Predicate p, const T& new_obj)会将[beg1, end1)中的元素复制到序列beg2的开始位置，并用new_obj替换使p返回true的元素。该算法返回一个迭代器，它指向目的位置的最后一个元素的下一个位置。序列不能是重叠的。
#### 修改序列中的元素
* fill(Fwd_Iter beg, Fwd_Iter end, const T& obj)会将obj保存到序列[beg, end)的每一个元素中。
* fill_n(Output_Iter begg, Int_Type n, const T& obj)会将obj保存到序列beg开始的前n个元素中。
* generate(Fwd_Iter beg, Fwd_Iter end, Fun_Object gen_fun)会将gen_fun返回的值保存到序列[beg,end)的每一个元素中。gen_fun必须是无参数的，并且必须能够返回一个可以保存到序列中的值。
* generate_n(Output_Iter beg, Int_Type n, Fun_Object gen_fun)会将gen_fun返回的值保存到序列beg开始的前n个元素中。算法会返回一个指向最后一个被保存元素的下一个位置的迭代器。
* transform(Input_Iter beg1, Input_Iter end1, Output_Iter beg2, Unary_Op op)会将op应用到序列[beg1, end1)的每一个元素上，并将这些元素返回的对应值保存到从beg2开始的序列中。
* transform(Input_Iter1 beg1, Input_Iter1 end1, Input_Iter2 beg2, Output_Iter beg3, Binary_Op op)会将op应用到序列[beg1, end1)中与从beg2开始的序列所对应的元素对上，并将这些元素返回的对应值保存到从beg3开始的序列中。
#### 交换算法
* swap(T& obj1, T& obj2)会交换obj1和obj2的值。第二个版本的swap可以交换2个同类型的数组，它们的长度必须相同。
* iter_swap(Fwd_Iter iter1, Fwd_Iter iter2)交换iter1和iter2指向的值。
* swap_ranges(Fwd_Iter1 beg1, Fwd_Iter1 end1, Fwd_Iter2 beg2)会交换序列[beg1, end1)和从beg2开始的序列的对应元素。该算法返回的迭代器指向从beg2开始的序列的最后一个元素。
