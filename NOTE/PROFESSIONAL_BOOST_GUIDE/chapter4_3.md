# optional

optional位于名字空间boost，需要包含头文件<boost/optional.hpp>：

```c++
#include <boost/optional.hpp>
using namespace boost;
```

## 类摘要

optional库首先定义了常量boost::none，表示未初始化，明确了无效值：

```c++
class none_t{};						// 定义类型none_t，具体形式依据条件编译不同而不同
const none_t none = ...; 	// 定义常量none, 具体形式依据条件编译不同而不同
```

optional库的核心类是optional，它很像是个仅能存放一个元素的容器，实现了未初始化的概念：如果元素未初始化，那么容器就是空的，否则，容器内的值就是有效的，已经初始化的值。

optional的类摘要如下：

```c++
template<class T>
class optional
{
public:
  optional();													// 构造函数
  optional( none_t );
  optional(T const& v);
  optional(bool condition, T v);
  
  optional& operator=(T const& rhs);	// 赋值操作符
  template<class... Args>
  void emplace(Args...&& args);				// 就地创建
  
  T* operator->();
  T& operator*();
  T& get();
  T* get_ptr();
  T& value();
  T const& value_or(T const& default) const;
  template<typename F>
  T value_or_eval(F f) const;
  
  explicit operator bool() const;			// 显式bool转型
  bool operator!() const;							// bool测试
}；
```

## 操作函数

有很多方式可以创建optional对象，具体如下：

- 用无参的optional()或optional(boost::none)构造一个未初始化对象。
- optional(v)构造一个已初始化的optional对象，内部拷贝v的值。如果模板类型为T&，那么optional内部持有对引用的包装。
- optional(condition, v)根据条件condition来构造optional对象，如果条件成立(true)，则初始化为v，否则为未初始化。
- optional支持拷贝构造和赋值操作，可以从另一个optional对象构造。
- emplace()是一个特殊的赋值函数，它可以使用参数就地创建对象，避免了构造后在拷贝的代价。
- 想让一个optional对象重新恢复到未初始化状态，可以向对象赋none值。

optional另外提供了三个value()系列成员函数，它们更加安全。

- value()同样可以访问元素，如果optional未初始化，会抛出bad_optional_access异常。
- value_or(default)可以保证返回一个有效值，如果optional已初始化，那么返回内部的元素，否则返回default。
- value_or_eval(f)类似value_or()，但它的参数是一个可调用的函数或函数对象，如果optional未初始化，则返回f的执行结果，即f()。

## 用法

示范optional基本用法的代码如下：

```c++
optional<int> op0;									// 一个未初始化的optional对象
optional<int> op1(none);						// 同上，使用none赋予其未初始化值
assert(!op0);												// bool测试
assert(op0 == op1);									// 比价两个optional对象

assert(op1.value_or(253) == 253);		// 获取默认值
cout << op1.value_or_eval(					// 使用函数对象
				[](){return 874;}) << endl;	// 用lambda表达式定义函数对象

optional<string> ops("test");				// 初始化为字符串test
cout << *ops << endl;								// 用解引用操作符获取值

ops.emplace("monado", 3);						// 就地创建一个字符串，没有拷贝代价
assert(*ops == "mon");							// 只使用了前三个字符

vector<int> v(10);
optional<vector<int>& > opv(v);			// 容纳一个容器的引用
assert(opv);												// bool转型

opv->push_back(5);									// 使用箭头操作符操作容器
assert(opv->size() == 1);

opv = none;													// 置为未初始化状态
assert(!opv);												// 此时为无效值
```

下列代码使用optional作为函数的返回值：

```c++
optional<double> calc(int x)
{
  return optional<double>(x != 0, 1.0 / x);
}

optional<double> sqrt_op(double x)
{
  return optional<double>(x >= 0, sqrt(x));
}

optional<double> d = calc(10);

if (d)
{ cout << *d << endl; }

d = sqrt_op(-10);
if (!d)
{ cout << "no result" << endl; }
```

## 工厂函数

```c++
optional<T> make_optional(T const& v);
optional<T> make_optional(bool condition, T const& v);
```

make_optional()无法推导出T引用类型的optional对象，如果需要一个optional<T&>的对象就不能使用make_optional()函数。

make_optional()也不支持emplace的用法，可能存在值的拷贝代价。

示范make_optional()函数用法的代码如下：

```c++
auto x = make_optional(5);											// 使用auto关键字自动推导类型
assert(*x == 5);

auto y = make_optional<double>((*x > 10), 1.0); // 使用木板夹参数明确类型
assert(!y);
```

