# ref

一般情况下，传值语义都是可行的，但也有很多特殊情况：作为参数的函数对象拷贝代价过高（具有复杂的内部状态），不希望拷贝对象（内部状态不应该被改变），甚至拷贝是不可行的(noncopyable, singleton)。

boost.ref应用代理模式，引入对象引用的包装器概念解决了上述问题。它位于名字空间boost,需要包含的头文件如下：

```c++
#include <boost/ref.hpp>
using namespace boost;
```

## 类摘要

ref库定义了一个很小，很简单的引用类型的包装器，名字叫reference_wrapper,其类摘要如下:

```c++
template<class T>
class reference_wrapper
{
public:
  explicit reference_wrapper(T& t) : t_(&t) {}	// 构造函数
  
  operator T& () const { return *t_; }					// 隐式转型
  T& get() const { return *t_; }								// 访问被包装的对象
  T* get_pointer() const { return t_; }
private:
  T* t_;																				// 保存对象指针
};
```

## 基本用法

```c++
int x = 10;
reference_wrapper<int> rw(x);										// 包装int类型的引用
assert(x == rw);																// 隐式转换为int类型
(int &) rw = 100;																// 显式转换为int&类型
assert(x == 100);

reference_wrapper<int> rw2(rw);									// 拷贝构造
assert(rw2.get() == 100);

string str;
reference_wrapper<string> rws(str);							// 包装字符串的引用
*rws.get_pointer() = "test reference_wrapper";	// 指针操作
cout << rws.get().size() << endl;
```

## 工厂函数

reference_wrapper的名字过长，用它声明包装对象很不方便，因此ref库提供了2个便捷的工厂函数ref()和cref()，利用它们可以通过推导参数类型很容易地构造包装对象。

这2个函数的声明如下:

```c++
reference_wrapper<T> ref(T& t);
reference_wrapper<T const> cref(T const& t);
```

ref()和cref()会根据参数类型自动推导生成正确的reference_wrapper<T>对象，ref()产生的类型是T，而cref()产生的类型是T const。例：

```c++
double x = 2.71828;
auto rw = cref(x);					// 包装double const
std::cout << typeid(rw).name() << std::endl;

std::string str;
auto rws = boost::ref(str);	// 使用名字空间限定，避免ADL
std::cout << typeid(rws).name() << std::endl;
```

因为reference_wrapper支持拷贝，所以ref()和cref()可以直接用在需要拷贝语义的函数参数中，而不必专门使用一个reference_wrapper来暂存:

```c++
double x = 2.0;
cout << std::sqrt(ref(x)) << endl;
```

### 操作包装

ref库运用模板元编程技术提供两个特征类:is_reference_wrapper和unwrap_reference，用于检测reference_wrappter对象：

- is_reference_wrappter<T>:: value可以判断T是否被包装。
- unwrap_reference<T>::type 表明了T的真实类型（无论它是否经过包装）。

例:

```c++
vector<int> v(10, 2);
auto rw = boost::cref(v);

assert( is_reference_wrapper<decltype(rw)>::value );
assert( !is_reference_wrapper<decltype(v)>::value );

string str;
auto rws = boost::ref(str);
cout << typeid(unwrap_reference<decltype(rws)>::type).name() << endl;
cout << typeid(unwrap_reference<decltype(str)>::type).name() << endl;
```

自由函数unwrap_ref()为解开包装提供了简便的方法，它利用unwrap_reference<T>直接解开reference_wrapper的包装（如果有的话），返回被包装对象的引用。例：

```c++
set<int> s;
auto rw = boost::ref(s);					// 获得一个包装对象
unwrap_ref(rw).insert(12);				// 直接解开包装

string str("test");
auto rws = boost::cref(str);			// 获得一个常对象的包装
cout << unwrap_ref(rws) << endl;	// 解包装
```

直接对一个未包装的对象使用unwrap_ref()也是可以的，它将直接返回对象自身的引用：

```c++
cout << unwrap_ref(str) << endl;	// 对未包装的对象解包装
```

## 综合应用

```c++
class big_class							// 一个简化的例子
{
private:
  int x;										// 具有复杂的内部状态，这里从简
public:
  big_class():x(0){}				// 构造函数
  void print()							// 一个操作函数，改变内部状态
  { cout << "big_class " << ++x << endl; }
}

template<typename T>
void print(T a)
{
  for (int i = 0; i < 2; ++i)
    unwrap_ref(a).print();	// 解包装
}

big_class c;
auto rw = ref(c);
c.print();									// 输出1

print(c);										// 拷贝传参，输出2，3，内部状态不改变
print(rw);									// 引用传参，输出2，3，内部状态改变
print(c);										// 拷贝传参，输出4，5，内部状态不改变
c.print();									// 输出4
```

## 对比标准

c++标准里的std::reference_wrapper的摘要如下:

```c++
template <class T>
class reference_wrapper {
public:
  reference_wrapper(T&) noexcept;
  reference_wrapper(T&&) = delete;		// 不能包装右值（临时对象）
  
  reference_wrapper(const reference_wrapper<T>& x) noexcept;
  reference_wrapper& operator=(const reference_wrapper<T>& x) noexcept;
  
  operator T& () const noexcept;			// 隐式转型
  T& get() const noexcept;
  
  template <class... ArgTypes>
  typename result_of<T&(ArgTypes&&...)>::type
  operator() (ArgTypes&&...) const;		// 调用操作符
};
```

与boost.ref的区别是：std::reference_wrapper支持调用操作符-这使得我们可以包装一个函数对象的引用并将其传递给标准库算法。std::reference_wrapper的函数调用示例：

```c++
struct square
{
  typedef void result_type;									// 返回结果的类型定义，很重要
  void operator()(int& x)
  { x = x*x; }
}；
  
typedef double (*pfunc)(double);
pfunc pf = sqrt;
cout << std::ref(pf)(5.0);									// 包装函数指针

square sq;
int x = 5;
ref(sq)(x);																	// 包装函数对象
cout << x;

vector<int> v = {1,2,3,4,5};
for_each(v.begin(), v.end(), std::ref(sq));	// 传递给算法引用
```

