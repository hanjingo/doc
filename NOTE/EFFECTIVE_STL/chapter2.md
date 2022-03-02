# 第二章 vector和string

[TOC]

## 第十三条：vector和string优先于动态分配的数组

1. 大多数情况下，推荐使用vector和string替换动态分配的数组；
2. 在多线程环境中，推荐使用内置数组代替含有引用计数的string（多线程下，为保证string的引用计数的安全性而采取的措施，会影响效率）。



## 第十四条：使用reserve来避免不必要的重新分配

1. 尽早使用reserve，把容器的容量设置为足够大，以避免重新分配；

   例：

   ```c++
   vector<int> v;
   v.reserve(1000); // 预先分配容量，防止push_back的过程中进行扩容
   for (int i = 1; i <= 1000; ++i)
       v.push_back(i);
   ```

2. 预留足够大的空间，当把所有数据都加入后，再去除多余的容量，也可以避免重新分配；



## 第十五条：注意string实现的多样性

1. string的值可能会被引用计数，也可能不会；只有当字符串被频繁拷贝时，引用计数才有意义；
2. string对象大小的范围可以是一个`char*`指针的大小的1倍到7倍；
3. 创建一个新的字符串值可能需要0次，1次或2次动态分配内存；
4. string对象可能共享，也可能不共享其大小和容量信息；
5. string可能支持，也可能不支持针对单个对象的allocator；
6. 不同的实现对字符内存的最小分配单位有不同的策略。



## 第十六条：了解如何把vector和string数据传给旧的API

```c++
size_t fillArray(double* pArray, size_t arraySize);
vector<double> vd(maxNumDoubles);
vd.resize(fillArray(&vd[0], vd.size())) // 利用vector和数组的内存布局兼容性，通过C API来初始化vector

size_t fillString(char* pArray, size_t arraySize);
vector<char> vc(maxNumChars);
size_t charsWriten = fillString(&vc[0], vc.size(0));
string s(vc.begin(), vc.begin() + charsWritten); // 通过区间构造函数，把数据从vc拷贝到s中

size_t fillArray(double *pArray, size_t arraySize);
vector<double> vd(maxNumDoubles);
vd.resize(fillArray(&vd[0], vd.size()));
deque<double> d(vd.begin(), vd.end());
list<double> l(vd.begin(), vd.end());
set<double> s(vd.begin(), vd.end());
```



## 第十七条：使用“swap技巧”除去多余的容量

```c++
class Contestant {...}
vector<Contestant> contestants;
vector<Contestant>(contestants).swap(contestants); // 对contestants做shrink-to-fit，缩小容量

string s;
string(s).swap(s); // 对s做shrink-to-fit，缩小容量
```



## 第十八条：避免使用`vector<bool>`

1. `vector<bool>`是一个假的容器，为了节省空间，它并不真的存储bool，而是使用类似1个字节存储8个bool的位域（bitfield）方式来存放；
2. 代替`vector<bool>`的方法：
   - 使用`deque<bool>`；
   - 使用bitset。
