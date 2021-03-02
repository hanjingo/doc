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

## static_assert

static_assert库把断言的诊断时刻由运行期提前到编译期，让编译器检查可能发生的错误，这样能够更好地增加程序的正确性，它模拟实现了c++标准里的static_assert关键字

为了使用static_assert组件，需要包含的头文件如下:

```c++
#include <boost/static_assert.hpp>
```

### 定义

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

### 用法

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

## lightweight_test

为了使用lightweight_test库，需要包含的头文件如下:

```c++
#include <boost/core/lightweight_test.hpp>
```

### 测试断言

lightweight_test只提供最基本的单元测试功能，不支持测试用例，测试套件的概念，但因为它简单小巧，所以它适用于要求不高或快速的测试工作。

lightweight_test定义了数个测试断言，以下列出比较常用的几个:

- BOOST_TEST(e): 断言表达式成立。
- BOOST_TEST_NOT(e): 断言表达式不成立。
- BOOST_ERROR(s): 直接断言失败，输出错误消息s。
- BOOST_TEST_EQ(e1, e2): 断言2个表达式相等。
- BOOST_TEST_NE(e1, e2): 断言2个表达式不等。
- BOOST_TEST_CSTR_EQ(e1, e2): 断言2个c字符串相等。
- BOOST_TEST_CSTR_NE(e1, e2): 断言2个c字符串不相等。
- BOOST_TEST_THROWS(e, ex): 断言表达式e抛出异常ex。

### 用法

lightweight_test用法示例:

```c++
#include <boost/smart_prt.hpp>								// 测试智能指针
#include <boost/core/lightweight_test.hpp>		// 轻量级测试框架

int main()
{
  auto p = make_shared<int>(10);							// 智能指针
  
  BOOST_TEST(*p == 10);												// 测试解引用
  BOOST_TEST(p.unique()); 										// 测试唯一性
  BOOST_TEST_NOT(!p);													// 测试指针是否为空
  
  BOOST_TEST_EQ(p.use_count(), 1);						// 相等测试
  BOOST_TEST_NE(*p, 20);											// 不等测试
  
  p.reset();
  BOOST_TEST(!p);
  
  BOOST_TEST_THROWS(*p, std::runtime_error); 	// 测试抛出异常，失败
  BOOST_ERROR("error accured!!"); 						// 输出错误信息
  
  return boost::report_errors(); 							// 输出测试报告
}
```

### 测试元编程

lightweight_test库也提供了对元编程测试的有限支持，在头文件<boost/core/lightweight_test_trait.hpp>里定义了两个编译期的断言:

```c++
#define BOOST_TEST_TRAIT_TRUE((type))
#define BOOST_TEST_TRAIT_FALSE((type))
```

**注意:由于内部实现的原因，type必须要使用圆括号包围（宏展开为一个模板函数的参数）。**

下面的代码使用type_traits库里的traits元函数示范了元编程测试的用法:

```c++
#include <type_traits>
#include <boost/core/lightweight_test_trait.hpp>

int main()
{
  BOOST_TEST_TRAIT_TRUE((is_integral<int>));	// int是整数，注意圆括号
  BOOST_TEST_TRAIT_FALSE((is_function<int>)); // int不是函数
  
  return boost::report_errors();							// 输出测试报告
}
```

## test

test库提供了一个用于单元测试，基于命令行界面的测试套件:Unit Test Framework(简称UTF)，它比其他的单元测试库更强大，更方便，更好用。

test库包含2个库文件，需要编译才能使用，在jamfile里指定lib的语句如下:

```c++
lib boost_unit_test_framework;	// 单元测试框架库
lib boost_test_exec_monitor;		// 程序执行监视库
```

为了使用test库，需要包含的头文件如下:

```c++
#include <boost/test/unit_test.hpp>
```

### 测试断言

test库提供了4个最基本的测试断言:

- BOOST_CHECK(e): 断言测试通过，如不通过也不影响程序执行。
- BOOST_REQUIRE(e): 要求测试必须通过，否则程序停止执行。
- BOOST_ERROR(s): 给出一个错误信息，程序继续执行。
- BOOST_FAIL(s): 给出一个错误信息，程序运行终止。

我们应当尽量少使用他们

test库其他测试断言形式是BOOST_LVL_XXX,如BOOST_CHECK_EQUAL,BOOST_WARN_GT,详细的命名规则如下:

- BOOST:遵循Boost库的命名规则，宏一律以大写的BOOST开头。
- LVL:断言的级别。WARN是警告级，不影响程序运行，也不增加错误数量；CHECK是检查级别，如果断言失败则增加错误数量，但不影响程序运行；REQUIRE是最高的级别，如果断言失败将增加错误数量并终止程序运行。最常用的断言级别是CHECK,WARN可以用于不涉及程序关键功能的测试，只有当断言失败会导致程序无法继续进行测试时才能使用REQUIRE。
- XXX:各种具体的测试断言，如断言相等/不等，抛出/不抛出异常，大于/小于等。

test库中常用的几个测试断言如下:

- BOOST_LVL_EQUAL(l, r):检测 l==r,当测试失败时会给出详细的信息。他不能用于浮点数的比较，浮点数的相等比较应使用BOOST_LVL_CLOSE。
- BOOST_LVL_GE(l, r):检测l >= r,与GT(1>r),LT(l<r),LE(l<=r)和NE(l!=r)相同，他们勇于测试各种不等性。
- BOOST_LVL_THROW(e, ex):检测表达式e,抛出指定的ex异常。
- BOOST_LVL_NO_THROW(e):检测表达式e,不抛出任何异常。
- BOOST_LVL_MESSAGE(e,msg):它与不带MESSAGE后缀的断言功能，但测试失败时，他会给出指定的信息。
- BOOST_TEST_MESSAGE(msg):它仅输出通知消息，不含有任何警告或错误信息，默认情况不会显示。

### 测试主体

test库将测试程序定义为一个测试模块，由测试安装，测试主体，测试清理和测试运行器四部分组成。测试主体是测试模块的实际运行部分，由测试用例如测试套件组织成测试数的形式。

1. 测试用例

   测试用例是一个包含多个测试断言的函数，它是可以被独立执行测试的最小单位，各个测试用例之间是无关的，发生的错误不会影响其他测试用例。

   向UTF注册，可以采用手动或自动2中形式添加测试用例。我们使用宏BOOST_AUTO_TEST_CASE像声明函数一样创建测试用例，它的定义如下:

   ```c++
   #define BOOST_AUTO_TEST_CASE( test_name )
   ```

   宏的参数test_name是测试用例的名字，本书一律以t开头，表明整个名字是一个测试用例。例:

   ```c++
   BOOST_AUTO_TEST_CASE(t_case1)	// 测试用例声明
   {
     BOOST_CHECK_EQUAL(1, 1);		// 测试1==1
     ...
   }
   ```

2. 测试套件

   测试套件是测试用例的容器，

