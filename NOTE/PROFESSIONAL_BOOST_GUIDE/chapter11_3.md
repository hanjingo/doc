# function

function可以配合bind/lambda使用，以存储bind/lambda表达式的结果，使bind/lambda能够被多次调用。

function位于名字空间boost，需要包含的头文件如下：

```c++
#include <boost/function.hpp>
using namespace boost;
```

## 类摘要

function可以容纳0到10个参数的函数，摘要如下：

```c++
template< typename Signature >
class function : public functionN <R, T1, T2, ..., TN>
{
 public:
  typedef R result_type; 												// 内部类型定义
  typedef TN argN_type;
  
  static const int arity = N;
  
  function();																		// 构造函数
  template<typename F> function(F);
  
  void swap(const function&);
  void clear();
  bool empty() const;
  bool safe_bool() const;
  bool operator!() const;
  
  template<typename Functor> Functor* target(); // 访问内部元素
  template<typename Functor> bool contains(const Functor&) const;
  const std::type_info& target_type() const;
  
  result_type operator()(arg1_type, ...) const;	// 调用操作符
};
```

## 声明形式

function的函数类型声明也可以像真的函数类型声明那样带有参数名，如下面的写法：

```c++
function<int (int a, int b, int c)> func2;
```

与

```c++
function<int (int, int, int)> func2;
```

完全等价

我们可以用关键字decltype来直接获取函数类型，例：

```c++
int f(int a, int b){...}
function<decltype(f)> func;	// 使用decltype推导函数类型
```

## 操作函数

function的其他成员函数的功能如下：

- clear()可以直接将function对象置空，它与直接赋值0具有同样的效果。
- 模板成员函数target()可以返回function对象内部持有的可调用物Functor的指针，如果function为空则返回空指针nullptr。
- contains()可以检测function是否持有一个Functor对象。
- function提供了operator()，它把传入的参数转交给内部保存的可调用物，完成真正的函数调用。

## 用法

与原始的函数指针相比，function对象的体积要稍微大一些（3个指针大小），速度要稍微慢一些（10%左右的性能差距），但这些缺点与它带给程序的巨大好处相比微不足道。

示范function基本用法如下：

```c++
int f(int a, int b)
{ return a + b; }

int main()
{
  function<int(int, int)> func;		// 无参构造一个function对象
  assert(!func);									// 此时function不持有任何对象
  
  func = f;												// func存储函数f
  assert(func.contains(&f));			// 验证已经存储函数f
  
  if (func)												// function可以转换为bool值
  { cout << func(10, 20); }				// 调用function的operator()
  
  func = 0;												// function清空，相当于clear()
  assert(func.empty());
}
```

只要函数签名式一致，function也可以存储成员函数和函数对象，还可以存储bind/lambda表达式。例：

```c++
struct demo_class
{
  int add(int a, int b)
  { return a + b; }
  int operator()(int x) const	// 重载operator()
  { return x * x; }
}
```

存储成员函数时可以直接在function声明的函数签名式中指定类的类型，然后用bind绑定成员函数：

```c++
function<int(demo_class&, int, int)> func1;

func1 = bind(&demo_class::add, _1, _2, _3);

demo_class sc;
cout << func1(sc, 10, 20);
```

我们也可以在函数类型中仅写出成员函数的签名，在bind时直接绑定类的实例：

```c++
function<int(int, int)> func2;

func2 = bind(&demo_class::add,&sc,_1,_2);
cout << func2(10, 20);
```

## 使用ref库

```c++
template<typename T>
struct summary
{
  typedef void result_type;
  T sum;
  
  summary(T v = T()):sum(v){}
  void operator()(T const &x)
  { sum += x; }
};

vector<int> v= {1, 3, 5, 7, 9};

summary<int> s;														// 有状态的函数对象
function<void(int const&)> func(ref(s)); 	// function包装引用

std::for_each(v.begin(), v.end(), func); 	// 使用标准库算法
cout << s.sum << endl; 										// 函数对象的状态被改变
```

## 用户回调

function可以容纳任意符合函数签名式的可调用物，因此它非常适合代替函数指针，存储用于回调的函数，而且它的强大功能会使代码更灵活，更富有弹性。例：

```c++
class demo_class
{
 private:
  typedef function<void(int)> func_t;	// function类型定义
  func_t func;												// function对象
  int n;
 public:
  demo_class(int i):n(i){}						// 构造函数
  
  template<typename CallBack>
	void accept(CallBack f)
	{ func = f; } 											// 存储回调函数
  
  void run()
  { func(n); }
};

void callback_func(int i)
{
  cout << "call_back_func:";
  cout << i * 2 << endl;
}

demo_class dc(10);
dc.accept(call_back_func);						// 接收回调函数
dc.run();															// 调用回调函数，输出“call_back_func:20”
```

使用普通函数进行回调并不能提现function的喊出，我们来编写一个带状态的函数对象，并使用ref库传递引用：

```c++
class call_back_obj
{
  private:
  	int x;
  public:
  	call_back_obj(int i):x(i) {}
  	void operator()(int i)
    {
      cout << "call_back_obj:";
      cout << i * x++ << endl;
    }
};

demo_class dc(10);
call_back_obj cbo(2);
dc.accpet(ref(cbo));
dc.run();
dc.run();
```

function还可以搭配bind库，把bind表达式作为回调函数，可以接收类成员函数，或者把不符合函数签名式的函数bind转为可接收的形式。例：

```c++
class call_back_factory
{
public:
  void call_back_func1(int i)
  {
    cout << "call_back_factory1:";
    cout << i * 2 << endl;
  }
  void call_back_func2(int i, int j)
  {
    cout << "call_back_factory2:";
    cout << i*j*2 << endl;
  }
};

demo_class dc(10);
call_back_factory cbf;

dc.accept(bind(&call_back_factory::call_back_func1, cbf, _1));
dc.run();
dc.accept(bind(&call_back_factory::call_back_func2, cbf, _1, 5));
dc.run();
```

通过以上实例代码我们可以看到function用于回调的好处，它无须改变回调的接口就可以解耦客户代码，使客户代码不必绑死在一种回调形式上，进而可以持续演化，而function始终能够保证与客户代码进行正确沟通。

### 对比标准

有些时候，关键字auto可以取代function。例：

```c++
auto func = &f;
cout << func(10, 20) << endl;

demo_class sc;
auto func2 = bind(&demo_class::add, &sc, _1, _2);	// 存储一个bind表达式
cout << func2(10, 20) << endl;
```

但auto和function的实现有很大的不同。function类似一个容器，可以容纳任意有operator()的类型（函数指针，函数对象，lambda表达式），它是运行时的，可以任意拷贝，赋值，存储其他可调用物。而auto仅是在编译期推导出的一个静态类型变量，很难再赋予它其他值，它也无法容纳其他的类型，不能用于泛型编程。

当需要存储一个可调用物用于回调的时候，最好使用function，它具有更强的灵活性，特别是把回调作为类的一个成员的时候我们只能使用function。

auto也有它的有点，他的类型是在编译期推导的，运行时没有“开销”，它在效率上要比function略高一点。但auto声明的变量不能存储其他类型的可调用物，灵活性较差，只能用于有限范围的延后回调。

c++标准定义了std::function,其声明摘要如下：

```c++
template<class R, class... ArgTypes>
class function<R(ArgTypes...)> {
 public:
  function() noexcept;											// 构造函数
  template<class F> function(F);
  
  void swap(function&) noexcept;						// 交换函数
  
  template<class F, class A>
  void assign(F&&, const A&);								// 赋值
  
  explicit operator bool() const noexcept; 	// 显式bool转型
  
  R operator()(ArgTypes...) const;					// operator()
  
  const std::type_info& target_type() const noexcept;
  template <typename T> T* target() noexcept;
};
```

std::function与boost::function基本相同，它们只有少量的区别：

- 没有clear()和empty()成员函数。
- 提供assign()成员函数。
- explicit显式bool转型。

所以，同shared_ptr一样，std::function在函数返回值或函数参数等语境里转型bool需要使用static_cast<bool>(f)或!!f的形式。

