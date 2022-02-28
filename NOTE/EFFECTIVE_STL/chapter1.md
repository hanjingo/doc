# 容器

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



