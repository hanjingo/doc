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
class io_service : private noncopyable      // 不可拷贝
{
public:
    std::size_t run();                      // 阻塞执行事件循环
    std::size_t run_once();                 // 至少阻塞执行一个handler

    std::size_t poll();                     // 非阻塞，执行ready的handler
    std::size_t poll_one();                 // 至少执行一个ready的handler

    void stop();                            // 停止事件循环
    bool stopped() const;                   // 时间循环是否已经停止
    bool reset() const;                     // 重启事件循环

    unspecified dispatch(Handler handler);  // 要求异步执行一个handler
    unspecified post(Handler handler);      // 要求异步执行一个handler

    class strand;                           // 内部的线程类
    class work;                             // 表示有工作在进行
};
```

### strand
asio库基于操作系统的异步IO模型，不直接使用系统线程，而是定义了一个自己的线程概念:strand, strand可以序列化异步操作，保证异步代码在多线程的环境中可以正确执行，无需使用互斥量。strand的类摘要如下:
```c++
class io_service::strand
{
public:
    explicit strand(io_service& io);        // 构造函数，要求io_service

    io_service& get_io_service();           // 获取引用的io_service

    unspecified dispatch(Handler handler);  // 要求异步执行一个handler
    unspecified post(Handler handler);      // 要求异步执行一个handler
    unspecified wrap(Handler handler);      // 包装一个handler

    bool running_in_this_thread() const;
};
```

### work
当io_service里注册的所有事件都完成时,它就会退出事件循环,