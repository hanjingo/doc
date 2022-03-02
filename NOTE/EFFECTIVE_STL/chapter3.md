# 第三章 关联容器

[TOC]

## 第十九条：理解相等（equality）和等价（equivalence）的区别

TODO



## 第二十条：为包含指针的关联容器指定比较类型

1. 当创建包含指针的关联容器时，容器会按照**指针的值**而不是**指针指向的内容**进行排序；

   例，使用包含指针的关联容器**错误用法**：

   ```c++
   set<string*> ssp; // 等价于：set<string*, less<string*>, allocator<string*> > ssp;
   ssp.insert(new string("Anteater")); // insert指针
   ssp.insert(new string("Wombat"));
   ssp.insert(new string("Lemur"));
   ssp.insert(new string("Penguin"));
   
   // 普通方法打印
   for (set<string*>::const_iterator i = ssp.begin; i != ssp.end(); ++i)
       cout << **i << endl;
   
   // 使用copy算法打印
   copy(ssp.begin(), ssp.end(), ostream_iterator<string>(out, "\n"));
   ```

2. 每当创建包含指针的关联容器时，同时也要指定容器的比较类型；

   例，使用比较函数通用模板：

   ```c++
   struct DereferenceLess // 定义一个比较函数的通用模板
   {
       template<typename PtrType>
       bool operator()(PtrType pT1, PtrType pT2) const 
       {
           return *pT1 < *pT2;
       }
   }
   
   set<string*, DereferenceLess> ssp;
   
   // 普通方法打印
   for (StringPtrSet::const_iterator i = ssp.begin(); i != ssp.end(); ++i)
       cout << i << endl;
   
   // 使用for_each算法打印
   void print(const string *ps)
   {
       cout << *ps << endl;
   }
   for_each(ssp.begin(), ssp.end(), print);
   ```
   
   

## 第二十一条：总是让比较函数在等值情况下返回false

1. 对于关联容器排序的比较函数必须为它们所比较的对象定义一个“严格的弱序化”（strict weak ordering）；

2. `>=`对于关联容器来说不是一个合法的比较函数，相等的值从来不会有前后顺序关系；

   例，错误的做法：

   ```c++
   set<int, less_equal<int> > s;
   s.insert(10);
   
   struct StringPtrGreater : public binary_function<const string*, const string*, bool> 
   {
       bool operator()(const string *ps1, const string *ps2) const
       {
           return !(*ps1 < *ps2); // !(<)等价于>=；不能直接把比较结果取反来改变排列顺序，这对于关联容器不是一个合法的比较函数
       }
   };
   ```

   例，正确的做法：

   ```c++
   set<int, less_equal<int> > s;
   s.insert(10);
   
   struct StringPtrGreater : public binary_function<const string*, const string*, bool> 
   {
       bool operator()(const string *ps1, const string *ps2) const
       {
           return *ps2 > *ps1; // 正确
       }
   };
   ```



## 第二十二条：切勿直接修改set或multiset中的键

1. 对于map和multimap，键的类型是const，如果有程序试图修改容器中的键，会影响到容器的排序性，它将无法通过编译；

   ```c++
   map<int, string> m;
   m.begin()->first = 10; // 错误；map的键不能被修改
   
   multimap<int, string> mm;
   mm.begin()->first = 20; // 错误；multimap的键不能被修改
   ```

2. 对于set和multiset，修改元素的值这一行为具有不可移植性；

   - 修改set和multiset中元素的值时，如果不关心可移植性，并且STL支持这一操作，那么这一操作是可行的；
   - 如果重视可以执行，就要确保set和multiset中的元素不能被修改，至少不能未经强制转换（cast）就修改。
   
   例，修改set中元素的值示例：
   
   ```c++
   class Emplyee {
   public:
       const string& name() const;
       void setName(const string& name);
       const string& title() const;
       void setTitle(const string& title);
       int idNumber() const;
   };
   
   struct IDNumberLess : public binary_function<Employee, Employee, bool> {
       bool operator()(const Employee& lhs, const Employee& rhs) const {
           return lhs.idNumber() < rhs.idNumber();
       }
   };
   
   typedef set<Employee, IDNumberLess> EmpIDSet; // 按照ID号进行排序
   EmpIDSet se;
   Employee selectedID;
   
   EmpIDSet::iterator i = se.find(selectedID);
   
   // 可能会编译不通过
   if (i != se.end()) 
   {
       i->setTitle("Corporate Deity"); // 修改元素的值（有些STL实现会认定这个不合法）
   }
   
   // 编译必过的办法（不推荐）
   if (i != se.end())
   {
       const_cast<Employee&>(*i).setTitle("Corporate Deity"); // 强转并修改元素的值
   }
   
   // 最安全，可移植性最好的办法
   if (i != se.end()) 
   {
       Employee e(*i);                // 拷贝元素
       e.setTitle("Corporate Deity"); // 修改拷贝
       se.erase(i++);                 // 删除元素，递增迭代器以保证它的有效性
       se.insert(i, e);               // 插入新元素，提示它的位置和原来的相同
   }
   ```
   



## 第二十三条：考虑用排序的vector替代关联容器

1. 对于具有以下特征的场景，使用**排序后的vector**可能比关联容器性能更好；

   - 设置阶段：创建一个新的数据结构，并插入大量元素；在这个阶段，几乎所有的操作都是插入和删除操作；很少或几乎没有查找操作；
   - 查找阶段：查询该数据结构以找到特定的信息；在这个阶段，几乎所有的操作都是查找操作，很少或几乎没有插入和删除操作；
   - 重组阶段：改变该数据结构的内容，或许是删除所有的当前数据，再插入新的数据；再行为上，这个阶段与第1阶段类似；当这个阶段结束以后，应用程序又回到第二阶段。

2. 再排序的vector中存储数据可能比在标准关联容器中存储同样的数据要耗费更少的内存，考虑到页面错误的因素，通过二分搜索法查找一个排序的vector可能比查找一个标准关联容器要更快；

   例，使用vector做查找：
   
   ```c++
   typedef pair<string, int> Data;
   
   class DataCompare {
   public:
       bool operator()(const Data& lhs, const Data& rhs) const
       {
           return keyLess(lhs.first, rhs.first);
       }
       bool operator()(const Data& lhs, const Data::first_type& k) const
       {
           return keyLess(lhs.first, k);
       }
       bool operator()(const Data::first_type& k, const Data& rhs) const
       {
           return keyLess(k, rhs.first);
       }
   private:
       bool keyLess(const Data::first_type& k1, const Data::first_type& k2) const
       {
           return k1 < k2;
       }
   };
   
   vector<Data> vd;
   sort(vd.begin(), vd.end());
   string s;
   
   // 通过binary_search查找
   if (binary_search(vd.begin(), vd.end(), s, DataCompare())) 
       ...
   
   // 通过lower_bound查找
   vector<Data>::iterator i = lower_bound(vd.begin(), vd.end(), s, DataCompare()); 
   if (i != vd.end() && !DataCompare()(s, *i))
       ...
       
   // 通过equal_range查找
   pair<vector<Data>::iterator, vector<Data>::iterator> range = equal_range(vd.begin(), vd.end(), s, DataCompare());
   equal_range(vd.begin(), vd.end(), s, DataCompare()); 
   if (range.first != range.second)
       ...
   ```
   
   
   
## 第二十四条：当效率至关重要时，请在map::operator[]与map::insert之间谨慎做出选择

1. 当向映射表中添加元素时，要优先选用insert，而不是operator[]；

   ```c++
   class Widget {
   public:
       Widget();
       Widget(double weight);
       Widget& operator=(double weight);
       ...
   };
   
   map<int, Widget> m;
   // 低效
   m[1] = 1.50; // 效率低，先判断存不存在，存在就更新，不存在就插入（空的map，键1肯定不存在）
   // 高效
   m.insert(IntWidgetMap::value_type(1, 1.50)); // 效率高，不判断直接插入
   ```

2. 当更新已经在映射表中的元素的值时，要优先选择operator[]；

   例，同时进行高效的添加和更新：

   ```c++
   template<typename MapType, typename KeyArgType, typename ValueArgType>
   typename MapType::iterator efficientAddOrUpdate(MapType& m, const keyArgType& k, const ValueArgType& v)
   {
       typename MapType::iterator lb = m.lower_bound(k); // 确定k的位置
       
       if (lb != m.end() && !(m.key_comp()(k, lb->first))) // 如果lb已存在，更新它
       {
       	lb->second = v;
           return lb;
       }
       else // 否则插入
       {
           typedef typename MapType::value_type MVT;
           return m.insert(lb, MVT(k, v));
       }
   }
   
   class Widget {
   public:
       Widget();
       Widget(double weight);
       Widget& operator=(double weight);
       ...
   };
   
   map<int, Widget> m;
   efficientAddOrUpdate(m, 10, 1.5);
   ```
   



## 第二十五条：熟悉非标准的哈希容器

TODO
