# asio
asio不需要编译，但它依赖一些其他Boost库组件，最基本的是boost.system库，用来提供系统错误支持。与thread库不同的是asio默认使用标准库<chrono>提供的时间功能，如果要强制使用boost.chrono，可以定义宏BOOST_ASIO_DISABLE_STD_CHRONO。其他可选库还有coroutine, regex, thread和serialization, 如果需要支持SSL,还要额外安装OpenSSL。asio位于名字空间boost::asio,需要包含的头文件如下:
```c++
#define BOOST_ASIO_DISABLE_STD_CHRONO // 使用boost.chrono库的时间功能
#include <boost/asio.hpp>
using namespace boost::asio;
```

## 概述
### handler
在asio库里，handler主要有以下3种:
- 只有一个error_code参数，标志某个异步事件完成了，是最基本的handler。
- 有error_code和signal_number两个参数，标志发生了一个UNIX信号事件。
- 有error_code和bytes_transferred两个参数，标志某个读写操作完成了，可读写的数据字节数是bytes_transferred,通常用于socket回调。
上述3种handler的形式如下:
```c++
void handler(const error_code& ec);         // 操作的错误码

void handler(const error_code& ec,          // 操作的错误码
            int signal_number);             // 引发操作的信号量

void handler(const error_code& ec,          // 操作的错误码
            std::size_t bytes_transferred); // 传输的字节数
```
可以使用bind把任意函数适配为asio要求的handler形式，asio库在子名字空间boost::asio::placeholders里定义了几个新的占位符，这些新占位符比bind自己的_1,_2等占位符的含义更清晰。
- error             :表示error_code值。
- signal_number     :表示UNIX信号值。
- bytes_transferred :表示可读写的字节数。

### io_service
```c++
class io_service : private noncopyable // 不可拷贝
{
public:
    std::size_t run(); // 阻塞执行事件循环
    std::size_t run_once(); // 
}
```