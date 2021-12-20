# signals2

signals2库位于名字空间boost::signals2,需要包含的头文件如下：

```c++
#include <boost/signals2.hpp>
using namespace boost::signals2;
```

## 类摘要

```c++
template<typename Signature,	// Function type R (T1,..., TN)
	typename Combiner = boost::signals2::optional_last_value<R>,
  typename Group = int,
  typename GroupCompare = std::less<Group> >
class signal : public boost::signals2::signal_base
{
  public:
  	signal(const combiner_type& = combiner_type(),
           const group_compare_type& = group_compare_type());
  	~signal();
  
  	// 插槽连接管理
  	connection connect(const slot_type&, connect_position = at_back);
  	connection connect(const group_type&, const slot_type&,
                       connect_position = at_back);
  	void disconnect(const group_type&);
  	
  	template<typename S>
  	void disconnect(const S&);
  
  	void disconnect_all_slots();
  	bool empty() const;
  	std::size_t num_slots() const;
  
  	// 调用操作符
  	result_type operator(){...};
  
  	// 合并器
  	combiner_type combiner() const;
  	void set_combiner(const combiner_type&);
};
```

- 第一个模板参数Signature的含义与function的含义相同，它也是一个函数类型，表示可被signal调用的函数（插槽，事件处理handler）。例：

  ```c++
  signal<void(int, double)>
  ```

- 第二个模板参数Combiner是一个函数对象，它被称为“合并器”，用来组合所有插槽的调用结果，默认是optional_last_value<R>，它使用optional库返回最后一个被调用的插槽的返回值。

- 第三个模板参数Group是插槽编组的类型，默认使用int来记组号，也可以改为std::string等类型，但通常没有必要。

- 第四个模板参数GroupCompare与Group配合使用，用来确定编组的排序准则，默认是升序(std::less<Group>)，因此要求Group必须定义operator<。

signal是不可拷贝的。如果把signal作为自定义类的成员变量，那么自定义类也将是不可拷贝的，除非使用shared_ptr/ref来间接持有它。

## 用法

1. 基本用法

   ```c++
   void slots1()
   { cout << "slot1 called" << endl; }
   void slots2()
   { cout << "slot2 called" << endl; }
   signal<void()> sig;		// 指定插槽类型void(),其他模板参数使用默认值
   signal<void()> sig;		// 一个信号对象
   
   sig.connect(&slots1);	// 连接插槽1
   sig.connect(&slots2);	// 连接插槽2
   sig();                  // 调用operator()，产生信号(事件)，触发插槽调用
   ```

2. 使用组号

   - 各编组的调用顺序组号从小到大决定（也可以在signal的第四个模板参数中改变排序函数对象）。
   - 每个编组的插槽链表内部的插入顺序用at_back和at_front指定。
   - 如果未被编组的插槽的位置标志是at_front，它将在所有的编组之前被调用。
   - 如果未被编组的插槽的为指标值是at_back，它将在所在的编组之后被调用。

   例:

   ```c++
   template<int N>
   struct slots
   {
     void operator()()
     { cout << "slot" << N << " called" << endl; }
   };
   
   sig.connect(slots<1>(), at_back);       // 最后被调用
   sig.connect(slots<100>(), at_front);    // 第一个被调用
   
   sig.connect(5, slots<51>(), at_back);   // 组号5，该组最后一个
   sig.connect(5, slots<55>(), at_front); 	// 组号5，该组第一个
   
   sig.connect(3, slots<30>(), at_front);	// 组号3，该组第一个
   sig.connect(3, slots<33>(), at_back);   // 组号3，该组最后一个
   
   sig.connect(10, slots<10>());           // 组号10，该组仅有的一个
   ```

## 返回值

```c++
template<int N>
struct slots
{
  int operator()(int x)
  {
    cout << "slot" << N << " called" << endl;
    return x *N;
  }
};

signal<int(int)> sig;
sig.connect(slots<10>());
sig.connect(slots<20>());
sig.connect(slots<50>());
// signal将返回插槽链表末尾slots<50>()的计算结果，它是一个optional对向，必须用解引用操作符“*”来获得值
cout << *sig(2); // 输出100
```

## 合并器

signal允许用户自定义合并器来处理插槽的返回值，把多个插槽的返回值合并为一个结果返回给用户。合并器应该是一个函数对象（不是函数或函数指针），合并器的形式如下：

```c++
template<typename T>
class combiner // 自定义合并器
{
  public:
  	typedef T result_type; // 返回值类型定义
  	template<typename InputIterator>
  	result_type operator()(InputIterator, InputIterator) const;
};
```

编写一个自定义的合并器，它使用pair返回所有插槽的返回值之和以及其中的最大值：

```c++
template<typename T>
class combiner
{
  T v;
public:
  typedef std::pair<T, T> result_type;
  combiner(T t = T()):v(t){}   // 构造函数
  
  template<typename InputIterator>
  result_type operator()(InputIterator begin, InputIterator end) const
  {
    if (begin == end)          // 如果返回值链表为空，则返回0
    { return result_type(); }
    
    vector<T> vec(begin, end); // 使用容器保存插槽调用结果
    
    T sum = std::accumulate(vec.begin(), vec.end(), v);
    T max = *std::max_element(vec.begin(), vec.end());
    
    return result_type(sum, max);
  }
};

signal<int(int), combiner<int> > sig(combiner<int>());

sig.connect(slots<10>());
sig.connect(slots<20>());
sig.connect(slots<30>, at_front);   // 最大值，第一个调用

auto x = sig(2);                    // 用auto获得信号的返回值
cout << x.first << "," << x.second; // 输出"120,60"
```

## 管理信号连接

signal可以用成员函数disconnect()断开一个或一组插槽，或者使用成员函数disconnect_all_slots()断开所有插槽的连接，函数empty()和num_slots()用来检查信号上的当前插槽的连接状态。

示范插槽的连接和断开：

```c++
signal<int(int)> sig;
assert(sig.empty());            // 刚开始没有连接任何插槽

sig.connect(0, slots<10>());	// 连接2个组号为0的插槽
sig.connect(0, slots<20>());
sig.connect(1, slots<30>());	// 连接组号为1的插槽

assert(sig.num_slots() == 3);	// 目前有3个插槽
sig.disconnect(0);              // 断开组号为0的插槽，共两个
assert(sig.num_slots() == 1);
sig.disconnect(slots<30>());	// 断开一个插槽
assert(sig.empty());            // 信号不再连接任何插槽
```

## 更灵活地管理信号连接

每当signal使用connect()连接插槽时，他就会返回一个connection对象。connection对象就像是信号与插槽之间连接的一个句柄(handle)，可以管理连接。摘要如下：

```c++
class connection {
public:
  connection();                              // 构造函数与析构函数
  connection(const connection&);
  connection& operator=(const connection&);
  
  void disconnect() const;                  // 插槽连接管理
  bool connected() const;
  
  bool blocked() const;                     // 插槽是否被阻塞
  void swap(const connection&);             // 交换
  
  bool operator==(const connection&) const;	// 比较操作
  bool operator!=(const connection&) const;
  bool operator<(const connection&) const;
};
```

connection是可拷贝，可赋值的，它也重载了比较操作符，因此它可以被安全地放入标准序列容器或关联容器中，成员函数disconnection()和connected()分别用来与信号断开连接和检测连接状态。例：

```c++
signal<int(int)> sig;

connection c1 = sig.connect(0, slots<10>());
connection c2 = sig.connect(0, slots<20>());
connection c3 = sig.connect(1, slots<30>());

c1.disconnect();              // 断开第一个连接
assert(sig.num_slots() == 2); // sig现在连接两个插槽
assert(!c1.connected());      // c1不再连接信号
assert(c2.connected());       // c2仍然连接信号
```

scoped_connection，提供类似scoped_ptr的RAII功能：插槽与信号的连接仅在作用域内生效，当离开作用域时连接就会自动断开。

当需要临时连接信号，scoped_connection会非常有用。例：

```c++
signal<int(int) > sig;

sig.connect(0, slots<10>());
assert(sig.num_slots() == 1);
{	// 进入局部作用域，建立临时连接
  scoped_connection sc = sig.connect(0, slots<20>());
  assert(sig.num_slots() == 2);
} // 离开局部作用域，临时连接自动断开
assert(sig.num_slots() == 1);
```

示范连接阻塞用法：

```c++
signal<int(int) > sig;

connection c1 = sig.connect(0, slots<10>());
connection c2 = sig.connect(0, slots<20>());
assert(sig.num_slots() == 2); // 有两个插槽连接
sig(2);                       // 调用两个插槽

cout << "begin blocking..." << endl;
{
  shared_connection_block block(c1); // 阻塞c1连接
  assert(sig.num_slots() == 2);      // 仍然有两个连接
  assert(c1.blocked());              // c1被阻塞
  sig(2);                            // 只有一个插槽会被调用
}                                    // 离开作用与，阻塞自动解除

cout << "end blocking..." << endl;
assert(!c1.blocked());
sig(2); // 可以调用两个插槽
```

## 自动管理连接

如果插槽在与信号建立连接后被意外地销毁了，那么调用信号将发生未定义行为。例：

```c++
signal<int(int) > sig;

sig.connect(slots<10>()); // 正常连接

auto p = new slots<20>;   // 创建一个指针对象
sig.connect(ref(*p));     // 用ref包装，连接到引用

delete p; // 指针被销毁
sig(1);   // 信号调用将发生未定义行为
```

slot的类摘要如下：

```c++
template<typename Signature,
	typename SlotFunction = boost::function<R (T1, ..., TN)> >
class slot : public boost::signals2::slot_base
{
public:
  template<typename Slot> slot(const Slot &);
  tempalte<typename Func, typename Arg...>
  slot(const Func &, const Arg &...);
  
  result_type operator()(...);
  // 跟踪功能
  slot & track(const weak_ptr<void> &);
};
```

如果要使用自动管理连接的功能，那么在信号连接时我们就不能直接连接插槽，而是要用slot的构造函数包装插槽，然后用成员函数track()来跟踪插槽使用的资源。**注意，track()函数不支持c++标准里的std::weak_ptr，所以只能使用boost.weak_ptr。***

示范boost.weak_ptr：

```c++
typedef signal<int(int) >signal_t; // typedef用于简化类型声明
signal_t sig;

sig.connect(slots<10>());                 // 连接一个普通的slot
auto p = boost::make_shared<slots<20>>(); // 用boost::shared_ptr管理资源

// 注意slot_type的用法
sig.connect(signal_t::slot_type(ref(*p)).track(p));
p.reset();                    // 销毁插槽
assert(sig.num_slots() == 1); // 一个插槽被自动断开
sig(1);                       // 只有一个插槽被调用
```

示范slot用于bind和function的代码：

```c++
typedef signal<int(int) > signal_t;
typedef signal_t::slot_type slot_t;
signal_t sig;

// 声明两个shared_ptr
auto p1 = boost::make_shared<slots<10>>();
auto p2 = boost::make_shared<slots<20>>();

function<int(int)> func = ref(*p1);		// function存储引用
sig.connect(slot_t(func).track(p1));	// 直接跟踪function

// 使用bind语法，直接绑定
sig.connect(slot_t(&slots<20>::operator(), p2.get(), _1).track(p2));

p1.reset();                   // 销毁两个指针对象
p2.reset();
assert(sig.num_slots() == 0); // 此时已经自动断开了所有连接
sig(1);                       // 不发生任何插槽调用
```

## 应用于观察者模式

```c++
class ring
{
public:
  typedef signal<void()> signal_t; 		// 内部类型定义
  typedef signal_t::slot_type slot_t;
  connection connect(const slot_t& s)	// 连接插槽
  { return alarm.connect(s); }
  void press()
  {
    cout << "Ring alarms..." << endl;
    alarm();                            // 调用signal，发出信号，引发插槽调用
  }
private:
  signal_t alarm;                       // 信号对象
}

typedef variate_generator<rand48, uniform_smallint<> > bool_rand;
bool_rand g_rand(rand48(time(0)), uniform_smallint<>(0,100));

// 它使用了char const*作为护士的名字，因此实例化时必须将字符串声明为extern
extern char const nurse1[] = "Mary";
extern char const nurse2[] = "Kate";

template<char const *name>
class nurse
{
private:
  bool_rand &rand;       // 随机数发生器
public:
  nurse():rand(g_rand){} // 构造函数
  void action()
  {
    cout << name;
    if (rand() > 30) // 70%的概率惊醒
    { cout << " wakeup and open the door." << endl; }
    else // 30%的概率继续睡觉
    { cout << "is sleeping..." << endl; }
  }
};

// 婴儿类
extern char const baby1[] = "Tom";
extern char const baby2[] = "Jerry";

template<char const *name>
class baby
{
private:
  bool_rand &rand;
public:
  baby():rand(g_rand){}
  
  void action()
  {
    cout << "Baby " << name;
    if (rand() > 50) // 50%的概率惊醒并哭闹
    { cout << " wakeup and crying loudly..." << endl; }
    else // 50%的概率继续睡觉
    { cout << " is sleeping sweetly..." << endl; }
  }
};

// 访客类
class guest
{
public:
  void press(ring &r)
  {
    cout << "A guest presses the ring." << endl;
    r.press();
  }
};

// 使用
ring r;
nurse<nurse1> n1;
nurse<nurse2> n2;
baby<baby1> b1;
baby<baby2> b2;
guest g;

r.connect(bind(&nurse<nurse1>::action, n1));
r.connect(bind(&nurse<nurse2>::action, n2));
r.connect(bind(&baby<baby1>::action, b1));
r.connect(bind(&baby<baby2>::action, b2));

g.press(r);
```

## 高级议题

1. 让signal支持拷贝

   signal是noncopyable的子类，这意味着它不能被拷贝或赋值；如果处于某种理由，确实需要在多个对象之间共享signal对象，那么可以考虑使用shared_ptr<signal>作为类的成员，shared_ptr可以很好管理signal的共享定义。例：

   ```c++
   class demo_class
   {
   public:
     typedef signal<void()> signal_t; // 类型定义方便使用
     shared_ptr<signal_t> sig;        // shared_ptr of signal
     
     int x;
     demo_class():sig(new signal_t), x(10){} // 构造函数
   };
   
   void print() // 一个插槽函数
   { cout << "hello sig." << endl; }
   
   int main()
   {
     demo_class obj;
     assert(obj.sig.use_count() == 1);
     demo_class obj2(obj); // 拷贝构造
     assert(obj.sig.use_count() == 2);
     
     obj.sig->connect(&print); // obj链接插槽
     (*obj2.sig)();            // obj2可以调用共享的信号
   }
   ```

2. 插槽调度

   下面的合并器当得到一个大于100的返回值就停止调用插槽：

   ```c++
   class combiner
   {
   public:
     typedef bool result_type;
     template<typename InputIterator>
     result_type operator()(InputIterator begin, InputIterator end) const
     {
       for(;begin != end; ++begin)
       {
         if(*begin > 100)
           return true;
       }
       return false;
     }
   };
   ```

3. 线程安全

   signal模板参数列表的最后一个类型参数是互斥量Mutex，默认值是signals2::mutex，它会自动检测编译器的线程支持程度，根据操作系统自动决定要使用的互斥量对象。通常mutex都工作得很好，我们不需要改变它。

   signal对象在创建时会自动创建一个mutex保护内部状态，每一个插槽连接时也会创建一个新的mutex，当信号或插槽被调用时mutex会自动锁定，因此signal可以很好地工作于多线程环境。

   同样的，connection/shared_connection_block也是线程安全的，但用于自动连接管理的slot类不是线程安全的。

4. 让插槽自己管理连接

   signals2库提供了connect_extended()函数和extended_slot_type类型定义，可以让插槽接受一个额外的connection对象以管理连接。为了使用这个功能，需要修改插槽的声明，使他能够接收connection对象。例：

   ```c++
   template<int N>
   struct slots
   {
     int operator()(const connection &conn, int x)	// 检查连接状态
     {
       cout << "cout=" << conn.connected() << endl;
       return x * N;
     }
   };
   ```

   在连接插槽时必须使用extended_slot_type的类bind语法，用占位符“_1”向插槽传递connection对象。例：

   ```c++
   typedef signal<int(int)> signal_t;
   typedef signal_t::extended_slot_type slot_t;
   signal_t sig;
   
   // _1是connection对象，_2是插槽实际使用的参数
   sig.connect_extended(slot_t(&slots<10>::operator(), slots<10>(), _1, _2));
   sig.connect_extended(slot_t(&slots<20>::operator(), slots<20>(), _1, _2));
   sig(5);	// 整数5将作为_2的实际参数传递给插槽
   ```

5. 对比function

   signal内部使用function来存储可调用物，它的声明与function很像，它也提供了operator()。在signal只连接了一个插槽的时候，他基本上与function等价。例：

   ```c++
   void f()
   { cout << "func called" << endl; }
   
   // 下面的两种function和signal的调用代码在功能上是等价的
   function<void()> func;	// function对象
   func = f; // 存储一个可调用物
   func();   // 调用函数
   
   signal<void()> sig; // signal对象
   sig.connect(&f);    // 连接一个插槽
   sig();              // 触发事件，产生信号，调用插槽
   ```

**需要注意它们的返回值，function对象直接返回被包装函数的返回值，而signal则使用optional对象作为返回值，signal真正的返回值需要使用解引用操作符 "星号"才能取得**

signal用于回调的灵活性比function强，但也使得signal的用法比较复杂，较难掌握。

6. 扩展实现operator+=

   ```c++
   template<typename Signature>
   class sig_ex
   {
   public:
     typedef signal<Signature> 							signal_type;
     typedef typename signal_type::slot_type slot_type;
     
     connection connect(const slot_type& s)    // 连接插槽
     { return sig.connect(s); }
     connection operator++(const slot_type& s) // 操作符+=重载连接
     { return connect(s); }
     
     template<typename... Args> // c++11可变参数模板
     typename signal_type::result_type
     operator()(Args&&... args)
     { return sig(std::forward<Args>(args)...); } // 完美转发
     
   private:
     signal_type sig;
   };
   
   sig_ex<int(int)> sig; // 使用类似c#的语法连接插槽
   sig += slots<10>();
   sig += slots<5>();
   sig(2);               // 信号调用
   ```

   