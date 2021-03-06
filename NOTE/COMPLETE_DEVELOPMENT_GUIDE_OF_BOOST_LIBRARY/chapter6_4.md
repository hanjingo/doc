# test

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

## 测试断言

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

## 测试主体

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

   测试套件是测试用例的容器，它包含一个或多个测试用例，可以将繁多的测试用铝分组管理，共享安装/清理代码，更好地组织测试用例。

   测试套件可以嵌套，并且没有嵌套层数的限制。

   测试套件同样有手动和自动2种使用方式，自动方式使用BOOST_AUTO_TEST_SUITE和BOOST_AUTO_TEST_SUITE_END2个宏，它们的定义如下:

   ```c++
   #define BOOST_AUTO_TEST_SUITE( suite_name )
   #define BOOST_AUTO_TEST_SUITE_END()
   ```
```
   
   这两个宏必须成对使用
   
   例:
   
   ```c++
   BOOST_AUTO_TEST_SUITE(s_suite1)		// 测试套件开始
     
   BOOST_AUTO_TEST_CASE(t_case1)			// 测试用例1
   {
     BOOST_CHECK_EQUAL(1, 1);
     ...															// 其他测试断言
   }
   
   BOOST_AUTO_TEST_CASE(t_case2)			// 测试用例2
   {
     BOOST_CHECK_EQUAL(5, 10/2);
     ...
   }  
   
   BOOST_AUTO_TEST_SUITE_END()				// 测试套件结束
```

3. 主测试套件

   任何UTF单元测试程序都必须存在唯一一个主测试套件，它是整个测试树的根节点，其他的测试套件都是他的子节点。

   主测试套件的定义可以使用宏BOOST_TEST_MAIN或BOOST_TEST_MODULE，它们必须出现在<boost/test/unit_test.hpp>之前

## 测试实例

测试套件的声明如下:

```c++
BOOST_AUTO_TEST_SUITE(s_smart_ptr)	// 测试套件开始
BOOST_AUTO_TEST_SUITE_END()					// 测试套件结束
```

测试用例针对scoped_ptr和shared_ptr，具体如下:

```c++
BOOST_AUTO_TEST_CASE(t_scoped_ptr)
{
  ...
}
```

完整的单元测试程序如下:

```c++
#define BOOST_TEST_MAIN									// 必须定义测试套件
#include <boost/test/unit_test.hpp>			// test库的头文件
#include <boost/smart_ptr.hpp>

BOOST_AUTO_TEST_SUITE(s_smart_ptr)			// 开始测试套件 s_smart_ptr
  
BOOST_AUTO_TEST_CASE(t_scoped_ptr)			// 测试用例1: t_scoped_ptr
{
  scoped_ptr<int> p(new int(874));
  BOOST_CHECK(p);												// p不是空指针
  BOOST_CHECK_EQUAL(*p, 874);						// 测试解引用的值
  
  p.reset();														// scoped_ptr复位
  BOOST_CHECK(p == 0);									// 为空指针
}

BOOST_AUTO_TEST_CASE(t_shared_ptr)			// 测试用例2: t_shared_ptr
{
  shared_ptr<int> p(new int(1000));
  
  BOOST_CHECK(p);												// p不是空指针
  BOOST_CHECK_EQUAL(*p, 100);						// 测试解引用的值
  BOOST_CHECK_EUQAL(p.use_count(), 1);	// 引用计数为1
  
  shared_ptr<int> p2 = p;								// 拷贝构造另一个shared_ptr
  BOOST_CHECK_EQUAL(p, p2);							// 两个shread_ptr必定相等
  BOOST_CHECK_EQUAL(p2.use_count(), 2);	// 引用计数为2
  
  *p = 255;															// 改变第二个shared_ptr所指的内容
  BOOST_CHECK_EQUAL(*p, 255);						// 第一个所指的内容也同时改变
  BOOST_CHECK_GT(*p, 200);
}

BOOST_AUTO_TEST_SUITE_END()							// 结束测试套件
```

我们也可以采用另一种方式来组织我们的测试树：在一个单独的源文件里定义空的主测试套件，然后再其他的源文件里分别实现具体的测试套件，这样的组织结构更加清晰：

```c++
//test_main.cpp
#define BOOST_TEST_MAIN		// 定义主测试套件，是测试main函数入口
#include <boost/test/uint_test.hpp>

//test_suite1.cpp
#include <boost/test/uint_test.hpp>
...
```

## 测试夹具

UTF中定义了”测试夹具“的概念，它实现了自动的测试安装和测试清理，就像是一个夹在测试用例/测试套件两端的”夹子“。测试夹具不仅可以用于测试用例，也可以用于测试套件和单元测试全局。

使用测试夹具时，必须要定义一个测试夹具类，它只有构造函数和析构函数，用于执行测试安装和测试清理，基本形式如下：

```c++
struct test_fixture_name	// 测试夹具类
{
  test_fixture_name(){}		// 测试安装工作
  ~test_fixture_name(){}	// 测试清理工作
};
```

指定测试用例和测试套件的测试夹具类需要使用另外2个宏：

```c++
#define BOOST_FIXTURE_TEST_SUITE( suite_name, fixture_name )
#define BOOST_FIXTURE_TEST_CASE	( test_name,  fixture_name )
```

示范测试夹具用法的代码如下，测试对象是assign库:

```c++
#include <boost/test/uint_test.hpp>
#include <boost/assign.hpp>

// 全局测试夹具类
struct global_fixture
{
  global_fixture(){cout << ("global setup\n");}
  ~global_fixture(){cout << ("global teardown\n");}
};

// 定义全局测试夹具
BOOST_TEST_GLOBAL_FIXTURE(global_fixture);

// 测试套件夹具类
struct assign_fixture
{
  assign_fixture()
  {cout << ("suit setup\n");}
  ~assign_fixture()
  {cout << ("suit teardown\n");}
  
  vector<int> v;									// 所有测试用例都可用的成员变量
};

// 定义测试套件级别的夹具
BOOST_FIXTURE_TEST_SUITE(s_assign, assign_fixture)
  
BOOST_AUTO_TEST_CASE(t_assign1)		// 测试"+="操作符
{
  using namespace boost::assign;
  
  v += 1, 2, 3, 4;
  BOOST_CHECK_EQUAL(v.size(), 4);
  BOOST_CHECK_EQUAL(v[2], 3);
}
BOOST_AUTO_TEST_CASE(t_assign2)		// 测试push_back函数
{
  using namespace boost::assign;
  
  push_back(v)(10)(20)(30);
  BOOST_CHECK_EQUAL(v.empty(), false);
  BOOST_CHECK_LT(v[0], v[1]);
}

BOOST_AUTO_TEST_SUITE_END()				// 测试套件结束
```

## 测试日志

日志级别如下:

- all: 输出所有的测试日志。
- success: 相当于all。
- test_suite: 仅允许运行测试套件的信息。
- message: 仅允许输出用户测试信息（BOOST_TEST_MESSAGE）。
- warning: 仅允许输出警告断言信息（BOOST_WARN_XXX）。
- error: 仅允许输出CHECK, REQURE断言信息（BOOST_CHECK_XXX）。
- cpp_exception: 仅允许输出未被捕获的c++异常信息。
- system_error: 仅允许输出非致命的系统错误。
- fatal_error: 仅允许输出致命的系统错误。
- nothing: 禁止任何信息输出。

默认情况下，UTF的日志级别是warning；

### 运行参数

基于UTF的单元测试程序在编译完成后可以独立运行，test库提供了许多运行时的命令行参数，常用的命令行参数如下：

- run_test: 可以指定要运行的测试用例或测试套件，用斜杠(/)来访问测试树里的任意节点，支持使用通配符"*"。
- build_info: 单元测试时输出编译器，STL，Boost等系统信息，取值为yes/no。
- output_format: 指定输出信息的格式，取值为HRF/XML。
- log_format: 指定日志信息的格式，取值为HRF/XML/JUNIT。
- list_content: 列出所有的测试套件和测试用例，并不运行。
- color_output: 使用彩色输出测试结果，更直观醒目。
- log_level: 允许输出的日志级别，取值为success等，默认是warning。
- show_progress: 显示测试的进度，值为yes/no。UTF不能显示测试用例内部的进度，只能显示已经完成的测试用例与测试用例总数的比例。

例：

```sh
--build_info=yes --run_test=s_assign/* --output_format=XML
```

## 高级议题

1. 不链接库使用

   > 头文件<boost/test/included/unit_test.hpp>里包含了test库的所有实现代码，因此我们可以在项目中加入cpp文件:
   >
   > ```c++
   > //test_main.cpp
   > #define BOOST_TEST_MAIN			// 定义主测试套件，测试main函数入口
   > #include <boost/test/included/uint_test.hpp>
   > ```
   >
   > 这样将导致把test库的所有实现代码编译进测试程序
   >
   > 其他测试套件的源代码文件仍然需要包含<boost/test/uint_test.hpp>，但前面应加入宏定义BOOST_TEST_INCLUDED，告诉test库我们使用嵌入源码的使用方式，即:
   >
   > ```c++
   > //test suite1.cpp
   > #define BOOST_TEST_INCLUDED	// 不链接库文件，直接使用头文件
   > #include <boost/test/unit_test.hpp>
   > ```

2. 期望测试失败

   > 通常情况下，所有的测试断言都应当通过，但有些时候需要特定的测试失败，允许有少量的断言失败。这时我们可以使用宏BOOST_AUTO_TEST_CASE_EXPECTED_FAILURES，它的声明如下:
   >
   > ```c++
   > #define BOOST_AUTO_TEST_CASE_EXPECTED_FAILURES( test_name, n )
   > ```
   >
   > 在测试套间内部使用这个宏，指定测试用例名和允许失败的断言的数量。例:
   >
   > ```c++
   > BOOST_FIXTURE_TEST_SUITE(test_suit, fixture)
   >   
   > // 允许出现2个断言失败
   > BOOST_AUTO_TEST_CASE_EXPECTED_FAILURES(t_case1, 2)
   > BOOST_AUTO_TEST_CASE(t_case1)
   > {...}
   > BOOST_AUTO_TEST_SUITE_END()
   > ```

3. 测试装饰器

   > 下面的代码定义了一个测试套件，里面有三个测试用例。测试套件添加了标签decorator，测试用例使用了两个标签low和high，注意装饰器前必须有"*"：
   >
   > ```c++
   > namespace urt = boost::unit_test;					// 简化名字空间的使用
   > BOOST_AUTO_TEST_SUITE(s_decorator,
   >                       * utf::label("decorator"))
   > BOOST_AUTO_TEST_CASE(t_case1,
   >                      * utr::label("low")	// 为测试用例添加标签和描述信息
   >                      * utf::description("a normal test case"))
   > {...}
   > BOOST_AUTO_TEST_CASE(t_case2,
   >                      * utf::label("low"))	// 为测试用例添加标签
   > {...}
   > BOOST_TEST_DECORATOR(*utr::label("high"))	// 使用宏为测试用例添加标签
   > BOOST_AUTO_TEST_CASE(t_case3)
   > {...}
   > BOOST_AUTO_TEST_SUITE_END()								// 测试套件结束
   > ```
   >
   > 之后可以在命令行参数里用--run_test=@label的方式指定运行打了标签的测试用例，或者用--list_content列出测试用例的详细描述信息。

4. 手工注册测试用例

   手动注册需要使用宏BOOST_TEST_CASE和BOOST_PARAM_TEST_CASE生成测试用例类，并调用framework::xxx_test_suite().add()方法

5. 测试泛型代码

   > UTF也能测试模板函数和模板类，如果采样自动测试方式，可使用BOOST_AUTO_TEST_CASE_TEMPLATE，它需要使用模板元编程库mpl，其声明如下：
   >
   > ```c++
   > #define BOOST_AUTO_TEST_CASE_TEMPLATE( test_name, type_name, TL )
   > ```
   >
   > 例:
   >
   > ```c++
   > #include <boost/test/uint_test.hpp>
   > #include <boost/lexical_cast.hpp>
   > #include <boost/mpl/list.hpp>
   > using namespace boost;
   > BOOST_AUTO_TEST_SUITE(s_lexical_cast)
   > typedef mpl::list<short, int, long> types;		// 模板元编程类型的容器
   > 
   > BOOST_AUTO_TEST_CASE_TEMPLATE(t_lexical_cast, T, types)
   > {
   >   T n(20);
   >   BOOST_CHECK_EQUAL(lexical_cast<string>(n), "20");
   > }
   > BOOST_AUTO_TEST_SUITE_END()
   > ```


