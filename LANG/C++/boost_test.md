# boost 单元测试

[TOC]


## 语法

使用boost单元测试功能之前，需要引入头文件：

```c++
#include <boost/test/included/unit_test.hpp>
```

- BOOST_AUTO_TEST_SUITE 测试套件开始

- BOOST_AUTO_TEST_CASE 测试语句，用于包裹需要测试的代码

- BOOST_WARN 警告提示

- BOOST_CHECK 即使断言失败，测试仍将继续

- BOOST_REQUIRE 断言失败，视作严重错误，立即停止测试

- BOOST_AUTO_TEST_SUITE_END 测试套件结束

例：

```c++
#define BOOST_TEST_MODULE stringtest
#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(s1)

BOOST_AUTO_TEST_CAST (t1)
{
    BOOST_WARN(...);
    BOOST_CHECK(...);
    BOOST_REQUIRE(...);
}

BOOST_AUTO_TEST_CAST (t2)
{
    ...
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(s2)
...
BOOST_AUTO_TEST_SUITE_END()
```


## 参考

[1] [boost 单元测试 范例_了解Boost单元测试框架](https://blog.csdn.net/cusi77914/article/details/107114529)
