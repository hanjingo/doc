# noncopyable

noncopyable允许程序轻松地实现一个禁止拷贝的类。

noncopyable位于名字空间boost，需要包含的头文件如下:

```c++
#include <boost/noncopyable.hpp>
```

### 原理

在c++中定义一个类时，如果不明确定义拷贝构造函数和拷贝赋值操作符，编译器会为我们自动生成这2个函数，为了禁止这种操作，我们需要noncopyable；

### 用法

noncopyable为实现不可拷贝的类提供了简单清晰的解决方案：从boost::noncopyable派生即可。

例:

```c++
class do_not_copy: boost::noncopyable	// 注意这里，使用默认的私有继承是允许的
{...};
```

只要有可能，就使用boost::noncopyable，它明确无误地表达了类设计者的意图，对用户更加友好，而且与其他Boost库也配合得很好。

### 实现

旧版:

```c++
class noncopyable
{
  protected:
  	noncopyable() {}	// 默认的构造和析构是保护的，可继承
  	~noncopyable() {}
  private:
  	noncopyable( const noncopyable& ); // 私有化拷贝构造和拷贝赋值
  	const noncopyable& operator=( const noncopyable& );
};
```

新版:

```c++
class noncopyable
{
  protected:
  	noncopyable() = default;	// 默认的构造和析构是保护的
  	~noncopyable() = default;	// 使用默认实现
  	// 使用delete关键字禁用拷贝构造和拷贝赋值
  	noncopyable( const noncopyable& ) = delete;
  	const noncopyable& operator=( const noncopyable& ) = delete;
};
```

