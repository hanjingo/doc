# lightweight_test

为了使用lightweight_test库，需要包含的头文件如下:

```c++
#include <boost/core/lightweight_test.hpp>
```

## 测试断言

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

## 用法

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

## 测试元编程

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