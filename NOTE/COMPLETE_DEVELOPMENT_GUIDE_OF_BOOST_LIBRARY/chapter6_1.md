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