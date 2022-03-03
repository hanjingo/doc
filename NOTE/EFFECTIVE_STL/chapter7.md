# 第七章 在程序中使用STL

[TOC]



## 第四十三条：算法调用优先于手写的循环

1. STL算法调用优先于手写的循环；

   理由如下：

   - 效率，算法通常比程序员自己写的循环效率更高。
   - 正确性，自己写循环比使用算法更容易出错。
   - 可维护性，使用算法的代码通常比手写循环的代码更加简洁明了。

   例，使用循环：

   ```c++
   double data[maxNumDoubles];
   deque<double> d;
   
   deque<double>::iterator insertLocation = d.begin();
   for (size_t i = 0; i < numDoubles; ++i)
   {
       // 每次insert被调用之后都更新insertLocation，以便保持迭代器有效，然后递增迭代器
       insertLocation = d.insert(insertLocation, data[i] + 41); 
       ++insertLocation;
   }
   ```

   例，使用STL算法：

   ```c++
   double data[maxNumDoubles];
   deque<double> d;
   transform(data, data + numDoubles, inserter(d, d.begin()), bind2nd(plus<double>(), 41));
   ```



## 第四十四条：容器的成员函数优先于同名的算法

1. 容器的成员函数优先于同名的算法；

   理由如下：

   - 成员函数往往速度快；
   - 成员函数通常与容器（特别是关联容器）结合得更加紧密。

   例：

   ```c++
   set<int> s;
   
   set<int>::iterator i = s.find(727); // 使用find成员函数，速度更快
   if (i != s.end())
       ...
       
   set<int>::iterator i = find(s.begin(), s.end(), 727); // 使用find算法，速度慢
   if (i != s.end())
       ...
   ```



## 第四十五条：正确区分count，find，binary_search，lower_bound，upper_bound和equal_range

| 目的                                                 | 对未排序的区间使用算法 | 对排序的区间使用算法    | 对set或map使用成员函数 | 对multiset或multimap使用成员函数 |
| ---------------------------------------------------- | ---------------------- | ----------------------- | ---------------------- | -------------------------------- |
| 特定值存在吗？                                       | find                   | binary_earch            | count                  | find                             |
| 特定值存在吗？如果存在，那第一个有该值的对象在哪里？ | find                   | equal_range             | find                   | find或lower_bound                |
| 第一个不超过特定值的对象在哪里？                     | find_if                | lower_bound             | lower_bound            | lower_bound                      |
| 第一个在某个特定值之后的对象在哪里？                 | find_if                | upper_bound             | upper_bound            | upper_bound                      |
| 具有特定值的对象有多少个？                           | count                  | equal_range然后distance | count                  | count                            |
| 具有特定值的对象都在哪里？                           | 反复调用find           | equal_range             | equal_range            | equal_range                      |



## 第四十六条：考虑使用函数对象而不是函数作为STL算法的参数

1. 将函数对象（即可以被伪装成函数的对象）传递给STL算法往往比传递实际的函数更加高效；

   例：

   ```c++
   vector<double> v;
   
   sort(v.begin(), v.end(), greater<double>()); // 使用函数对象做参数（高效）
   
   inline bool doubleGreater(double d1, double d2) { return d1 > d2; }
   sort(v.begin(), v.end(), doubleGreater); // 使用函数做参数（低效）
   ```

2. 由于编译器或STL的问题，有时候用函数做参数可能会编译不过；

   例：

   ```c++
   set<string> s;
   
   // 用函数做参数，可能无法通过编译
   transform(s.begin(), s.end(), ostream_iterator<string::size_type>(count, "\n"), mem_fun_ref(&string::size));
   
   // 用函数对象做参数
   struct StringSize : public unary_function<string, string::size_type> {
       string::size_type operator()(const string& s) const
       {
           return s.size();
       }
   };
   transform(s.begin(), s.end(), ostream_iterator<string::size_type>(count, "\n"), StringSize());
   ```

3. 使用函数对象做参数有助于避免一些语言本身的缺陷；

   例，语法上没问题，但是STL不支持：

   ```c++
   template<typename FPType>
   FPType average(FPType val1, FPType val2)
   {
       return (val1 + val2) / 2;
   }
   template<typename InputIter1, typename InputIter2>
   void writeAverages(InputIter1 begin1, InputIter1 end1, InputIter2 begin2, ostream& s)
   {
       transform(begin1, end1, begin2, 
                 ostream_iterator<typename iterator_traits<InputIter1>::value_type(s, "\n")>,
                 average<typename iterator_traits<InputIter1>::value_type>); // STL标准不支持，因为它觉得有二义性
   }
   ```

   修改为使用函数对象：

   ```c++
   template<typename FPType>
   struct Average : public binary_function<FPType, FPType, FPType>
   {
       FPType operator()(FPType val1, FPType val2) const
       {
           return average(val1, val2);
       }
   };
   
   template<typename InputIter1, typename InputIter2>
   void writeAverages(InputIter1 begin1, InputIter1 end1, InputIter2 begin2, ostream& s)
   {
       transform(begin1, end1, begin2, 
                 ostream_iterator<typename iterator_traits<InputIter1>::value_type(s, "\n")>,
                 Average<typename iterator_traits<InputIter1>::value_type>());
   }
   ```



## 第四十七条：避免产生“直写型”（write-only）的代码

1. 直写型代码虽然很容易编写，但是难以阅读和理解；

   例，典型的直写型代码：

   ```c++
   vector<int> v;
   int x, y;
   v.erase(remove_if(find_if(v.rbegin(), v.read(), bind2nd(greater_equal<int>(), y)).base(), 
                     v.end(), 
                     bind2nd(less<int>(), x)),
          v.end());
   ```

   优化为：

   ```c++
   typedef vector<int>::iterator VecIntIter;
   VecIntIter rangeBegin = find_if(v.rbegin(), v.rend(), bind2nd(greater_equal<int>(), y)).base();
   v.erase(remove_if(rangeBegin, v.end(), bind2nd(less<int>(), x)), v.end());
   ```



## 第四十八条：总是包含（#include）正确的头文件

1. 几乎所有的标准STL容器都被声明再与之同名的头文件中；
2. 除`accumulate`, `inner_product`, `adjacent_difference`和`partial_sum`以外，其他所有的算法都被声明在<algorithm>中；
3. 特殊类型的迭代器，包括`istream_iterator`和`istreambuf_iterator`被声明在<iterator>中；
4. 标准的函数子（比如less<T>）和函数子配接器（比如not1，bind2nd）被声明在头文件<functional>中。



## 第四十九条：学会分析与STL相关的编译器诊断信息

1. C++中所有与`string`类似的类型实际上都是`basic_string`模板的实例，可以用全程替换的办法，将`basic_string`长长的类型名替换为文本“string”；
2. 使用标准关联容器的源代码通常会导致在诊断信息中提及某个内部使用的树模板，可以先尝试着将所有传递给`_Tree`模板的内容统统替换成`SOMETHING`；
3. `vector`和`string`的迭代器通常就是指针，所以当错误地使用了iterator地时候，编译器地诊断信息中可能会引用到指针类型；
4. 如果诊断信息中提到了`back_insert_iterator`, `front_insert_iterator`或者`inert_iterator`，则几乎总是意味着你错误地调用了`back_inserter`, `front_inserter`或者`inserter`；
5. 类似的，如果诊断信息中提到了`binder1st`或者`binder2nd`，那么你可能是错误地使用了`bind1st`和`bind2nd`；
6. 输出迭代器（如`ostream_iterator`, `ostreambuf_iterator`，以及那些由`back_inserter`, `front_inserter`和`inserter`函数返回的迭代器）在赋值操作符内部完成其输出或者插入工作，在使用这些迭代器时犯错，那么你所看到的错误消息中可能会提到与赋值操作符有关的内容；
7. 如果你得到地错误消息来源于某一个STL算法的内部时间（例如，引起错误的源代码在<algorithm>中），那也许是你在调用算法的时候使用了错误的类型；
8. 如果你正在使用一个很常见的STL组件，比如`vector`，`string`或者`for_each`算法，但是从错误消息来看，编译器好像对此一无所知，那么可能是你没有包含相应的头文件。



## 第五十条：熟悉与STL相关的Web站点

- SGI STL站点：http://www.sgi.com/tech/stl/
- STL port站点：http://www.stlport.org
- Boost站点：http://www.boost.org