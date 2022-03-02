# 第五章 算法

[TOC]



## 第三十条：确保目标区间足够大

1. 如果所使用的算法需要指定一个目标区间，那么必须确保目标区间足够大，或者确保它会随着算法的运行而增大；

   ```c++
   vector<int> values;
   vector<int> results;
   if (result.size() < values.size()) // 确保results至少和values一样大
   {
       result.resize(values.size());
   }
   transform(values.begin(), values.end(), results.begin(), transmogrify);
   ```

2. 正确使用transform

   ```c++
   int transmogrify(int x); // 根据x生成一个新的值
   vector<int> values;
   ... // 往values中添加一些元素
   
   // 将函数transmogrify作用于values的每个元素上，并将返回值追加到results的末尾
   vector<int> results;
   transform(values.begin(), values.end(), back_inserter(results), transmogrify); 
   
   // 将函数transmogrify作用于values的每个元素上，并将返回值以 逆序 的方式插入到results1的头部
   list<int> results1;
   transform(values.begin(), values.end(), front_inserter(results1), transmogrify);
   
   // 将函数transmogrify作用于values的每个元素上，并将返回值以 顺序 的方式插入到results2的头部
   list<int> results2;
   transform(values.rbegin(), values.rend(), front_inserter(results2), transmogrify);
   
   // 将函数transmogrify作用于values的每个元素上，并将返回值插入到results3的指定位置
   vector<int> results3;
   results3.reserve(results3.size() + values.size()); // 预分配容量
   transform(values.begin(), values.end(), inserter(results3, results.begin() + results.size() / 2), transmogrify);
   ```



## 第三十一条：了解各种与排序有关的选择

1. 如果需要对vector，string，deque或者数组中的元素执行一次完全排序，那么可以使用sort或者stable_sort；
2. 如果有一个vector，string，deque或者数组，并且只需对等价性最前面的n个元素进行排序，那么可以使用partial_sort；
3. 如果有一个vector，string，deque或者数组，并且需要找到第n个位置上的元素，或者，需要找到等价性最前面的n个元素但又不必对这n个元素进行排序，那么nth_element正是你所需要的函数；
4. 如果需要将一个标准序列容器中的元素按照是否满足某个特定的条件区分开来，那么，partition和stable_partition可能正是你所需要的；
5. 如果你的数据在一个list中，那么你仍然可以直接调用partition和stable_partition算法；你可以用list::sort来替代sort和stable_sort算法。但是，如果你需要获得partial_sort或nth_element算法的效果，有一些间接的途径来完成这项任务。

```c++
bool qualityCompare(const Widget& lhs, const Widget& rhs); // 判断lhs > rhs

partial_sort(widgets.begin(), widgets.begin() + 20, widgets.end(), qualityCompare); // 对前20个进行排序

nth_element(widgets.begin(), widgets.begin() + 19, widgets.end(), qualityCompare); // 将最好的20个元素放在前面，不用排序

nth_element(widgets.begin(), widgets.begin() + widgets.size() / 2, widgets.end(), qualityCompare); // 找到中间的元素

nth_element(widgets.begin(), widgets.begin() + widgets.begin() + widgets.size() / 2, widgets.end(), qualityCompare); // 找到75%处的元素
```



## 第三十二条：如果确实需要删除元素，则需要在remove这一类算法之后调用erase

1. remove不是真正意义上的删除，用remove删除元素，它只是移动被删除的元素到容器**尾部**，而容器中的元素数目并不会减少；

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

2. 使用erase与remove合作，来真正删除元素；

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



## 第三十三条：对包含指针的容器使用remove这一类算法时要特别小心

1. 当容器中存放的是指向动态分配的对象的指针的时候，应该避免使用remove和类似的算法（remove_if，unique），因为这样会造成内存泄漏；

   例，错误的方法：

   ```c++
   class Widget {
   public:
       bool isCertified() const;
   };
   vector<Widget*> v;
   v.push_back(new Widget);
   
   v.erase(remove_if(v.begin(), v.end(), fun(&Widget::isCertified)), v.end()); // 内存泄漏
   ```

   例，正确的方法：

   ```c++
   void delAndNullifyUncertified(Widget*& pWidget) // 删除符合条件的指针并置空
   {
   	if (!pWidget->isCertified()) 
       {
           delete pWidget;
           pWidget = 0;
       }    
   }
   
   for_each(v.begin(), v.end(), delAndNullifyUncertified); // 遍历并处理符合条件的指针
   
   v.erase(remove(v.begin(), v.end(), static_cast<Widget*>(0)), v.end()); // 删除空指针（必须将0转换为一个指针，这样c++才能正确推断出remove的第三个参数的类型）
   ```

2. 对于带有引用计数功能的智能指针，直接使用erase-remove删除之，不用担心内存泄露；

   ```c++
   template<typename T>
   class RCSP{...};
   typedef RCSP<Widget> RCSPW;
   vector<RCSPW> v;
   
   v.push_back(RCSPW(new Widget)); // 将智能指针加入到vector中
   v.erase(remove_if(v.begin(), v.end(), fun(&Widget::isCertified)), v.end()); // 删除那些指向未被验证的Widgetd指针
   ```

   

