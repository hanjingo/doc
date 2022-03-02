# 第一章 容器

[TOC]



## 第一条：慎重选择容器类型

- 标准STL序列容器：vector，string，deque和list；
- 标准STL关联容器：set，multiset，map和multimap；
- 非标准序列容器slit和rope；
- 非标准的关联容器hash_set，hash_multiset，hash_map和hash_multimap。
- vector<char>作为stringed替代；
- vector作为标准关联容器的替代；
- 几种标准的非STL容器，包括数组，bitset，valarray，stack，queue和priority_queue。

vector，list和deque为程序员提供了不同的复杂性，使用时要对此做出权衡。vector是默认应使用的序列类型；当需要频繁地在序列中做插入和删除操作时，应使用list；当大多数插入和删除操作发生在序列的头部和尾部时，deque是应考虑的数据结构。

1. 是否需要在容器的任意位置插入新元素
   - 需要：选择序列容器；
2. 是否关心容器中的元素是如何排序的
   - 不关心：选择哈希容器；
3. 选择的容器必须是标准C++的一部分吗
   - 是：排除哈希容器，slist和rope；
4. 需要哪种类型的迭代器
   - 随机访问迭代器：容器被限定为vector，deque和string，rope；
   - 双向迭代器：必须避免slist以及哈希容器的一个常见实现；
5. 当发生元素的插入或删除操作时，避免移动容器中原来的元素是否很重要
   - 是：避免连续内存的容器；
6. 容器中数据的布局是否需要和C兼容
   - 是：只能选择vector；
7. 元素的查找速度是否是关键的考虑因素
   - 是：考虑哈希容器，排序的vector和标准关联容器；
8. 是否介意容器内部使用了引用计数技术（reference counting）
   - 是：避免使用string，因为许多string的实现都使用了引用计数（考虑用vector<char>代替）。rope也需要避免，因为权威的rope实现是基于引用计数的。
9. 对插入和删除操作，是否需要事务语义（transaction semantics）
   - 是：使用基于节点的容器；如果对多个元素的插入操作需要事务语义，选择list；
10. 需要使迭代器，指针和引用变为无效的次数最少
    - 需要：使用基于节点的容器，因为对这类容器的插入和删除操作从来不会使迭代器，指针和引用变为无效（除非它们指向了一个正在审的元素）。
11. 如果序列容器的得带起是随机访问类型，而且只要没有删除操作发生，且插入操作只发生在容器的末尾，则指向数据的指针和引用就不会变为无效，这样的容器是有对你有帮助
    - 是：选择dque，当插入操作仅在容器末尾发生时，deque的迭代器有可能变为无效。deque是唯一的，迭代器可能变为无效而指针和引用不会变为无效的STL标准容器。



## 第二条：不要试图编写独立于容器类型的代码

1. 尽量使用封装（encapsulation）技术来将一种容器类型转换到另一种。

   错误示例：

   ```c++
   class Widget{...}
   vector<Widget> vw;
   Widget bestWidget;
   ...
   vector<Widget>::iterator i = find(vw.begin(), vw.end(), bestWidget);
   ```

   正确示例：

   ```c++
   class Widget {...};
   typedef vector<Widget> WidgetContainer;
   typedef WidgetContainer::iterator WCIterator;
   WidgetContainer cw;
   Widget bestWidget;
   ...
   WCIterator i = find(cw.begin(), cw.end(), bestWidget);
   ```

2. 把容器隐藏在一个类中，并尽量减少那些通过类接口（而使外部）可见的，与容器相关的信息，来减少在替换容器类型时所需要修改的代码。

   例：

   ```c++
   class CustomerList {
   private:
     typedef list<Customer> CustomerContainer;
     typedef CustumorContainer::iterator CCIterator;
     
     CustomerContainer customers;
   public:
     ...
   };
   ```



## 第三条：确保容器中的对象拷贝正确而高效

1. 向容器中填充对象，而对象的拷贝又很费时时，这一操作会成为程序的性能瓶颈；同时如果这些对象的拷贝有特殊含义，将它们放入容器时将不可避免地会产生错误；

2. 当存在继承关系时，向基类容器的拷贝动作会剥离派生类的信息（拷贝指针时可以避免这个问题）；

   例，拷贝对象：

   ```C++
   vector<Widget> vw;
   class SpecialWidget : public Widget{...};
   SpecialWidget sw;
   vw.push_back(sw); // 派生类特有的部分在拷贝时被丢弃了
   ```

   例，拷贝指针：

   ```C++
   vector<Widget*> vw;
   class SpecialWidget : public Widget{...};
   SpecialWidget *sw;
   vw.push_back(sw);
   ```

3. 尽量避免不必要的拷贝；

   ```c++
   Widget w[n]; // 创建有n个Widget对象的数组，每个对象都使用默认构造函数来创建（浪费）
   
   vector<Widget> vw; // 创建了包含0个Widget对象的vector，当需要时它会增长（避免了拷贝）
   ```



## 第四条：调用empty而不是检查size()==0

empty对所有的标准容器的操作都是**常数时间**，且empty函数常常会被内联，而size对于一些list的操作是**线性时间**；



## 第五条：区间成员函数优先于与之对应的单元素成员函数

1. 当需要给容器一组全新的值时，使用assign而不是operator=；

   例：

   ```c++
   v1.assign(v2.begin() + v2.size() / 2, v2.end());
   ```

2. 区间成员函数（range member function）是指像STL算法一样，使用两个迭代器参数来确定该成员操作所执行的区间，其优于与之对应的单元素成员函数；

   原因如下：

   - 通过使用区间成员函数，通常可以少写一些代码；
   - 使用区间成员函数通常会得到意图清晰和更加直接的代码；
   - 使用单元素的成员函数比使用区间成员函数需要更多地调用内存分配子，更频繁地拷贝对象，且做了冗余操作。

   例，使用单元素成员函数进行复制：

   ```c++
   vector<Widget> v1, v2;
   ...
   v1.clear();
   for (vector<Widget>::conset_iterator ci = v2.begin() + v2.size() / 2; ci != v2.end(); ++ci)
       v1.push_back(*ci);
   ```

   例，使用区间成员函数进行复制：

   ```c++
   v1.clear();
   copy(v2.begin() + v2.size() / 2, v2.end(), back_inserter(v1));
   ```

   例，使用单元素成员函数进行插入：

   ```c++
   int data[numValues];
   vector<int> v;
   vector<int>::iterator insertLoc(v.begin());
   
   for (int i = 0; i < numValues; ++i) {
       insertLoc = v.insert(insertLoc, data[i]);
       ++insertLoc;
   }
   ```

   例，使用区间成员函数进行插入：

   ```c++
   int data[numValues];
   vector<int> v;
   
   v.insert(v.begin(), data, data + numValues); // 使用区间插入效率比单元素插入高得多
   ```

3. 通过利用插入迭代器的方式来限定目标区间的copy调用，几乎都应该被替换为对区间成员函数的调用；

4. 支持区间操作的成员函数：

   - 区间创建

     所有的标准容器都提供了如下的构造函数：

     ```c++
     container::container(InputIterator begin, InputIterator end);
     ```

   - 区间插入

     所有的序列容器都提供了如下形式的insert：

     ```c++
     void container::insert(iterator position, InputIterator begin, InputIterator end);
     ```

     关联容器利用比较函数来决定元素该插入何处，它们提供了一个省去position参数的函数原型：

     ```c++
     void container::insert(InputIterator begin, InputIterator end);
     ```

   - 区间删除

     所有的标准容器提供了区间形式的删除操作，但对于序列和关联容器，其返回值有所不同。序列容器提供了这样的形式：

     ```c++
     iterator container::erase(iterator begin, iterator end);
     ```

     关联容器提供了如下形式：

     ```c++
     void container::erase(iterator begin, iterator end);
     ```

   - 区间赋值

     所有的标准容器都提供了区间形式的assign：

     ```c++
     void container::assign(InputIterator begin, InputIterator end);
     ```



## 第六条：当心C++编译器最烦人的分析机制

1. C++的一条普遍规律，编译器会尽可能地解释为函数声明；

   例：

   ```c++
   // 分析错误
   list<int> data(istream_iterator<int>(dataFile), // 参数名为dataFile，参数类型是istream_iterator<int>，dataFile两边的括号是多余的，会被忽略
                  istream_iterator<int>());        // 参数没有名称，类型是指向不带参数的函数的指针，该函数返回一个istream_iterator<int>
   
   // 分析正确
   istream_iterator<int> dataBegin(dataFile);
   istream_iterator<int> dataEnd;
   list<int> data(dataBegin, dataEnd);
   ```
   
   例：
   
   ```c++
   class Widget{...};
   Widget w(); // 这里没有声明名为w的Widget，而是声明了一个名为w的函数，该函数不带任何参数，且返回一个Widget
   ```



## 第七条：如果容器中包含了通过new操作创建的指针，切记在容器对象析构前将指针delete掉

1. 指针容器在自己被析构时会析构所包含的每个元素，但对指针的析构函数不做处理，也不会调用delete；

   例，错误的做法：

   ```c++
   void doSomething()
   {
       vector<Widget*> vwp;
       for (int i = 0; i < SOME_MAGIC_NUMBER; ++i)
           vwp.push_back(new Widget); // 使用了new创建指针
   }
   ... // 发生内存泄漏！！！当vwp的作用域结束时，它的元素全部被析构，但是通过new创建的对象没有被删除；
   ```

   例，正确的做法：

   ```c++
   void doSomething()
   {
       vector<Widget*> vwp;
       for (int i = 0; i < SOME_MAGIC_NUMBER; ++i)
           vwp.push_back(new Widget); // 使用了new创建指针
       
       // 手动释放
       for (vector<Widget*>::iterator i = vwp.begin(); i != vwp.end(); ++i)
           delete *i;
   }
   ```

   例，更优秀的做法（简化代码，考虑异常安全）：

   ```c++
   struct DeleteObject {
       template<typename T>
       void operator()(const T* ptr) const { delete ptr; }
   };
   
   void doSomething()
   {
       typedef boost::shared_ptr<Widget> SPW;
       vector<SPW> vwp;
       for (int i = 0; i < SOME_MAGIC_NUMBER; ++i)
           vwp.push_back(SPW(new Widget)); // 建议用make_shared
       ... // 不需要手动释放了
   }
   ```



## 第八条：切勿创建包含auto_ptr的容器对象

COAP（auto_ptr的容器）

1. COAP不可移植；

2. 拷贝一个auto_ptr意味着改变它的值；

   例：

   ```c++
   auto_ptr<Widget> pw1(new Widget); // pw1指向一个Widget。
   auto_ptr<Widget> pw2(pw1);        // pw2指向pw1的Widget；pw1被置为NULL（Widget的所有权从pw1转移到了pw2）。
   pw1 = pw2;                        // pw1指向Widget，pw2被置为NULL。
   ```

   例：

   ```c++
   bool widgetAPCompare(const auto_ptr<Widget>& lhs,
                        const auto_ptr<Widget>& rhs)
   {
       return *lhs < *rhs;
   }
   
   vector<auto_ptr<Widget> > widgets; // 创建一个vector并用指向Widget的auto_ptr填满它（这里不应该通过编译！！！）。
   sort(widgets.begin(), widgets.end(), widgetAPCompare); // 排序（排序算法的 ElementType pivotValue(*i) 会转移auto_ptr的所有权，当sort调用结束时，vector中的元素被置为NULL，错误！！！）
   ```



## 第九条：慎重选择删除元素的方法

- 要删除容器中有特定值的所有对象：

  如果容器是vector，string或deque，则使用erase-remove习惯用法。

  如果容器是stl，则使用list::remove。

  如果容器是一个标准关联容器，则使用它的erase成员函数。

- 要删除容器中满足特定判别式（条件）的所有对象：

  如果容器是vector，string或deque，则使用remove_copy_if和swap，或者写一个循环来遍历容器中的元素，记住当把迭代器传给erase时，要对它进行后缀递增。

- 要在循环内部做某些（除了删除对象之外的）操作：

  如果容器是一个标准序列容器，则写一个循环来遍历容器中的元素，记住每次调用erase时，要用它的返回值更新迭代器。

  如果容器是一个标准关联容器，则写一个循环来遍历容器中的元素，记住当把迭代器传给erase时，要对迭代器做后缀递增。



## 第十条：了解allocator的约定和限制

1. allocator是一个模板，模板参数T代表你为它分配内存的对象的类型；
2. 提供类型定义pointer和reference，但是始终让pointer为`T*`，reference为`T&`；
3. 千万别让你的allocator拥有随对象而不同的状态（per-object state）；通常，allocator不应该有非静态的数据成员；
4. 传给allocator的allocate成员函数的是那些要求内存的对象的个数，而不是所需的字节数；同时，这些函数返回`T*`指针（通过pointer类型定义），即使尚未有T对象被构造出来；
5. 一定要提供嵌套的rebind模板，因为标准容器依赖该模板。



## 第十一条：理解自定义allocator的合理用法

例：

```c++
void* mallocShared(size_t bytesNeeded);
void* freeShared(void* ptr);

template<typename T>
class SharedMemoryAllocator {
public:
    ...
    pointer allocate<size_type numObjects, const void *localityHint = 0>
    {
        return static_cast<pointer>(mallocShared(numObjects *sizeof(T)));
    }
    void deallocate(pointer ptrToMemory, size_type numObjects)
    {
        freeShared(ptrToMemory);
    }
    ...
}

typedef vector<double, SharedMemoryAllocator<double> > SharedDoubleVec;

{
    SharedDoubleVec v; // 创建一个vector，其元素位于共享内存中
    void*pVectorMemory = mallocShared(sizeof(SharedDoubleVec)); // 为SharedDoubleVec对象分配足够的内存
    SharedDoubleVec *pv = new (pVectorMemory)SharedDoubleVec;   // 使用"placement new"在内存中创建一个SharedDoubleVec对象
    
    pv->~SharedDoubleVec();    // 析构共享内存中的对象
    freeShared(pVectorMemory); // 释放最初分配的那一块共享内存
}
```

例，自定义堆的allocator：

```c++
class Heap1 {
public:
    ...
    static void *alloc(size_t numBytes, const void *memoryBlockToBeNear);
    static void dealloc(void *ptr);
    ...
};
class Heap2 {
public:
    ...
    static void *alloc(size_t numBytes, const void *memoryBlockToBeNear);
    static void dealloc(void *ptr);
    ...
};

template<typename T, typename Heap>
class SpecificHeapAllocator {
public:
    ...
    pointer allocate(size_type numObjects, const void *localityHint = 0)
    {
        return static_cast<pointer>(Heap::alloc(numObjects * sizeof(T), localityHint));
    }
    void deallocate(pointer ptrToMemory, size_type numObjects)
    {
        Heap::dealloc(ptrToMemory);
    }
    ...
}

vector<int, SpecificHeapAllocator<int, Heap1> > v;
set<int, SpecificHeapAllocator<int, Heap1> > s;
list<Widget, SpecificHeapAllocator<Widget, Heap2> > L;
map<int, string, less<int>, SpecificHeapAllocator<pair<const int, string>, Heap2> >m;
```



## 第十二条：切勿对STL容器的线程安全性有不切实际的依赖

1. STL提供的一些基本特性；

   - **多个线程读是安全的**，多个线程可以同时读同一个容器的内容，并且保证是正确的；在度的过程中，不能对容器有任何写入操作；
   - **多个线程对不同的容器做写入操作是安全的**，多个线程可以同时对不同的容器做写入操作。

2. 建议使用RAII（Resource Acquisition Is Initialization）的方式来手动控制同步；

   ```c++
   template<typename Container>
   class Lock {
   public:
       Lock(const Container& container) : c(container)
       {
           getMutexFor(c); // 在构造函数中获取互斥体
       }
       ~Lock()
       {
           releaseMutexFor(c)
       }
   private:
       cosnt Continer& c;
   }
   
   vector v;
   Lock<vector<int> > lock(v);
   vector<int>::iterator first5(find(v.begin(), v.end(), 5));
   if (first5 != v.end()) {
       *
   }
   ```

   







