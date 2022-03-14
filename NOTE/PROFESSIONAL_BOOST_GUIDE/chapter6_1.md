# assert
boost.assert提供的主要工具是BOOST_ASSERT宏，它类似于c标准中的assert,提供运行时的断言，但其功能有所增强。为了使用boost.assert,需要包含的头文件如下:
```c++
#include <boost/assert.hpp>
```

## 基本用法
assert库定义了2个断言宏:
```c++
#define BOOST_ASSERT(expr)          assert(expr)
#define BOOST_ASSERT_MSG(expr, msg) assert((expr)&&(msg))
```
第一种形式的BOOST_ASSERT等同于assert宏，断言表达式为真。第二种形式则允许断言失败时输出描述字符串，有助于排错。例:
```c++
BOOST_ASSERT(16 == 0x10);           // 断言成立
BOOST_ASSERT(string().size() == 1); // 断言失败，抛出异常
```
BOOST_ASSERT宏会在debug模式下生效，在release模式下不会进行编译，不会影响到运行效率，所以可以放心大胆的在代码中使用BOOST_ASSERT断言。

```c++
double func(int x)															// 取倒数的函数
{
  BOOST_ASSERT_MSG(x != 0, "divided by zero"); 	// 断言参数非0
  return 1.0 / x;
}
```

### 禁用断言

BOOST_ASSERT是标准断言宏assert的增强版，因此它有更强的灵活性。

如果在头文件<boost/assert.hpp>之前定义了宏BOOST_DISABLE_ASSERTS,那么BOOST_ASSERT将会定义为"((void)0)",自动失效。但标准的assert宏并不会受影响，这可以让程序员有选择的关闭BOOST_ASSERT。

```c++
#define BOOST_DISABLE_ASSERTS // 注意这里
#include <cassert> 						// 标准断言宏的头文件
#incldue <boost/assert.hpp>		// boost断言宏的头文件

double func(int x)
{
  BOOST_ASSERT(x != 0 && "divided by zero");	// 失效
  cout << "after BOOST_ASSERT" << endl;
  
  assert(x != 0 && "divided by zero");				// 有效
  cout << "after assert" << endl;
  
  return 1.0 / x;
}
```

### 扩展用法

如果在头文件<boost/assert.hpp>之前定义了宏BOOST_ENABLE_ASSERT_HANDLER,将导致BOOST_ASSERT的行为发生改变；它将不再等同于assert宏，断言的表达式无论是在debug模式下还是在release模式下，都将被求值。如果断言失败，会发生一个断言失败的函数调用boost::assertion_failed()或assertion_failed_msg()这相当于提供了一个错误处理handler。

上述2个函数声明在boost名字空间里，但他们特意被设计为没有具体实现，其声明如下:

```c++
namespace boost
{
  void assertion_failed(char const * expr, char const * function, 
                        char const * file, long line);
  void assertion_failed_msg(char const * expr, char const * msg,
                           char const * function, char const * file, long line);
}
```

assertion_failed()函数用法示例:

```c++
namespace boost {
  void assertion_failed(char const *, char const *, char const*, long) {}
  void assertion_failed_msg(char const * expr, char const * msg,
                           char const * function, char const * file, long line)
  {
    boost::format fmt("Assertion failed!\nExpression: %s\n"
                     "Function: %s\nFile: %s\nLine: %ld\n"
                     "Msg: %s\n\n");
    fmt % expr% function% file% line %msg;
    cout << fmt;
  }
}

#define BOOST_ENABLE_ASSERT_HANDLER // 启用handler
#include <boost/assert.hpp>

double func(int x) {...}

int main()
{
  func(0);
}
```

