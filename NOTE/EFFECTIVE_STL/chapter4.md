# 第四章 迭代器

[TOC]



## 第二十六条：iterator优先于const_iterator，reverse_iterator以及const_reverse_iterator

1. 尽量使用iterator而不是const或reverse型的迭代器，可以使容器的使用更为简单而有效，并且可以避免潜在的问题，原因如下：

   - 有些版本的insert和erase函数要求使用iterator。如果你需要调用这些函数，那你就必须使用iterator。const和reverse型的迭代器不能满足这些函数的要求。
   - 要想隐式地将一个const_iterator转换成iterator是不可能的。
   - 从reverse_iterator转换而来的iterator在使用之前可能需要相应的调整。

2. 避免混用不同类型的迭代器；

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



## 第二十七条：使用distance和advance将容器的const_iterator转换成iterator

1. 无法通过隐式或强制转化，将const_iterator转化为iterator；

   例：

   ```c++
   typedef deque<int> IntDeque;
   typedef IntDeque::iterator Iter;
   typedef IntDeque::const_iterator ConstIter;
   ConstIter ci;
   
   Iter i(ci);                   // 编译错误！从const_iterator到iterator没有隐式转换途径
   Iter i(const_cast<Iter>(ci)); // 编译错误！不能将const_iterator强制转换为iterator
   ```

2. 可以通过distance和advance将const_iterator转换成iterator；

   - distance 用于取得两个迭代器之间的距离；
   - advance 用于将一个迭代器移动指定的距离。

   例：

   ```c++
   typedef deque<int> IntDeque;
   typedef IntDeque::iterator Iter;
   typedef IntDeque::const_iterator ConstIter;
   
   IntDeque d;
   ConstIter ci;
   Iter i(d.begin());
   advance(i, distance<ConstIter>(i, ci)); // 移动i，使它指向ci的位置
   ```

3. 使用distance和advance方案转换const_iterator，需要消耗线性时间，并且需要访问const_iterator所属容器，使用时应慎重考虑；



## 第二十八条：正确理解由reverse_iterator的base()成员函数所产生的iterator的用法

1. 如果要在一个`reverse_iterator ri`指定的位置上插入新元素，则只需在`ri.base()`位置处插入元素即可。对于插入操作而言，`ri`和`ri.base()`是等价的，`ri.base()`是真正与`ri`对应的iterator；

2. 如果要在一个`reverse_iterator ri`指定的位置上删除一个元素，则需要在`ri.base()`前面的位置上执行删除操作。对于删除操作而言，`ri`和`ri.base()`是不等价的，`ri.base()`不是与`ri`对应的iterator；

   ```c++
   vector<int> v;
   vector<int>::reverse_iterator ri = find(v.rbegin(), v.rend(), 3);
   
   // 错误
   v.erase(--ri.base()); // 编译不过；试图删除ri.base()前面位置上的元素；对于vector和string
   
   // 正确
   v.erase((++ri).base()); // 删除ri所指向的元素
   ```



## 第二十九条：对于逐个字符的输入请考虑使用istreambuf_iterator

1. istream_iterator内部执行了格式化输入（构造析构对象，流标志检查，错误检查，...），导致其效率不佳；

   ```c++
   ifstream inputFile("interestingData.txt");
   inputFile.unsetf(ios::skipws); // 禁止忽略空格
   string fileData((istream_iterator<char>(inputFile)), istream_iterator<char>()); // 将inputFile读入fileData
   ```

2. istreambuf_iterator从流读取单个字符，从流的缓冲区读取下一个字符，效率更佳；

   ```c++
   ifstream inputFile("interestingData.txt");
   string fileData((istreambuf_iterator<char>(inputFile)), istreambuf_iterator<char>()); // istreambuf_iterator不会跳过任何字符（包括空格）
   ```





