# static_assert

static_assert库把断言的诊断时刻由运行期提前到编译期，让编译器检查可能发生的错误，这样能够更好地增加程序的正确性，它模拟实现了c++标准里的static_assert关键字

为了使用static_assert组件，需要包含的头文件如下:

```c++
#include <boost/static_assert.hpp>
```

## 定义

与assert库类似，static_assert库定义了2个宏来进行编译期断言，具体如下:

```c++
BOOST_STATIC_ASSERT(expr)						// 编译期检查表达式
BOOST_STATIC_ASSERT_MSG(expr, msg)	// 编译期检查表达式，带字符串消息
```

如果编译器支持c++标准的新关键字static_assert,那么他们会直接使用static_assert,即:

```c++
#define BOOST_STATIC_ASSERT( B )					static_assert(B, #B)
#define BOOST_STATIC_ASSERT_MSG( B, Msg )	static_assert(B, Msg)
```

如果编译器不支持新关键字static_assert,那么BOOST_STATIC_ASSERT_MSG类似于BOOST_STATIC_ASSERT，字符串消息功能会失效:

```c++
#define BOOST_STATIC_ASSERT_MSG( B, Msg )	BOOST_STATIC_ASSERT( B )
```

## 用法

静态断言BOOST_STATIC_ASSERT的使用方法与BOOST_ASSERT类似。例:

```c++
template<typename T>
T my_min(T a, T b)
{
  BOOST_STATIC_ASSERT(sizeof(T) < sizeof(int));	// 静态断言
  return a < b ? a : b;
}
int main()
{
  cout << my_min((short)1, (short)3);						// ok
  cout << my_min(1L, 3L);												// 编译期错误
}
```

BOOST_STATIC_ASSERT在类域和名字空间域的使用方式与在函数域的使用方式相同，例:

```c++
namespace my_space
{
  class empty_class
  {
    // 在类域中静态断言，要求int至少4个字节
    BOOST_STATIC_ASSERT_MSG(sizeof(int)>=4, "for 32 bit");
  };
  
  // 名字空间域静态断言，是一个“空类”
  BOOST_STATIC_ASSERT(sizeof(empty_class) == 1);
}
```