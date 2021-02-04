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
当io_service里注册的所有事件都完成时,它就会退出事件循环,我们并不希望这样，有时我们想让io_service继续运行，以处理将来可能发生的异步事件，这时就需要让io_service始终"有事可做"。他的功能很简单，在构造函数里启动了一个可用的“工作”，而在析构函数中停止“工作”，它像是一个guard,在work的生命周期里，io_service永远不会因其他异步事件完成而结束事件循环。work的类摘要如下:
```c++
class io_service::work
{
public:
    explicit work(io_service& io_service);  // 构造函数启动工作
    ~work();                                // 析构函数停止工作
    boost::asio::io_service& get_io_service(); 
};
```

### mutable_buffer和const_buffer
```c++
class mutable_buffer
{
public:
    mutable_buffer();
    mutable_buffer(void* data, std::size_t size);
private:
    void* data_; // 内部数据表示
    std::size_t size_;
};

class const_buffer
{
public:
    const_buffer();
    const_buffer(const void* data, std::size_t size);
    const_buffer(const mutable_buffer& b);
private:
    void* data_; // 内部数据表示
    std::size_t size_;
};
```
buffer()有多种重载形式:
```c++
unspecified buffer(void* data, std::size_t size_in_bytes);
unspecified buffer(std::vector& data);
```
asio库还提供了几个自由函数可以操作buffer。
- buffer_size() :获取缓冲区的长度。
- buffer_cast<T*>() :转换指针类型。
- buffer_copy() :拷贝缓冲区数据，类似memcpy。
这些函数的声明如下:
```c++
std::size_t buffer_size(const buffer_type& b);
T* buffer_cast(const buffer_type& b);
std::size_t buffer_copy(const mutable_buffer& target,
                        const const_buffer& source);
```

### 错误处理
asio库使用system库的error_code和system_error来表示程序运行时的错误。

### 跟踪日志
异步代码的执行是非线性的，运行异步代码时的流程很难调试。asio库为此特别提供了handler跟踪机制，只要头文件<boost/asio.hpp>前定义宏BOOST_ASIO_ENABLE_HANDLER_TRACKING,它就会向标准流cerr输出运行日志，使用操作系统的重定向功能也可以写入指定的日志文件。

跟踪日志以"|"分为4个字段，格式如下:
```c++
tag|timestamp|action|description
```
第一个字段是标记字符串，目前总是"@asio"。第二个字段是UNIX时间戳，精确到毫秒分辨率。最后2个字段很重要，他们记录了异步代码的具体动作，具体含义如下。
```sh
n   :n号handler正在执行某些操作。
>n  :进入n号handler，description表示入口参数。
<n  :离开n号handler,无description。
!n  :发生异常，离开n号handler。
~n  :n号handler未被调用就被销毁。
n*m :n号handler创建了一个新的m号handler。
```

## 信号
asio库提供了类signal_set,利用异步IO的方式很好地处理了UNIX信号。signal_set的类摘要如下:
```c++
class signal_set
{
public:
    explicit signal_set(io_service& io_service);
    signal_set(io_service& io_service, int number, ...);

    void add(int signal_number);            // 添加信号量
    void remove(int signal_number);         // 删除信号量
    void clear();                           // 清空信号量集合

    void cancel();                          // 取消所有异步操作

    void async_wait(SignalHandler handler); // 添加处理handler,非阻塞
};
```
成员函数async_wait()用于异步添加信号处理函数，也就是handler,它是非阻塞的，无须任何等待就会返回。handler的形式如下:
```c++
void handler(const system::error_code& ec,  // 操作的错误码
            int signal_number);             // 引发操作的信号值
```

### 用法
```c++
io_service io; // asio程序必须要有io_service对象

signal_set sig(io, SIGINT, SIGUSR1); // 捕获2个信号

// sig.add(SIGINT); // 等价于这2行add函数
// sig.add(SIGUSR1);

auto handler1 = 
    [](const error_code& ec, int n)
    {
        if (ec)
        {
            cout << ec.message() << endl;
            return;
        }
        if (n != SIGINT)
        { return; }
        cout << "handler1 recv = " << n << endl;
        cout << "do something" << endl;
    };

typedef void(handler_type)(     // 定义handler函数类型
    const error_code&, int);

function<handler_type> handler2 = 
    [](const error_code& ec, int n)
    {
        if (n != SIGUSR1)
        { return; }

        cout << "handler2 recv = " << n << endl;
    };

sig.async_wait(handler1);       // 异步添加处理handler
sig.async_wait(handler2);       // 异步添加处理handler

io.run();                       // 启动事件循环，阻塞等待信号事件
cout << "handler2 recv = " << n << endl;
```
一种循环捕获示例:
```c++
// handler2在处理完信号后再次调用了sig.async_wait(),所以io_service会持续等待信号事件的发生，直到被Ctrl+C中断
function<handler_type> handler2 = 
    [&](const error_code& ec, int n)
    {
        ...
        sig.async_wait(handler1);
        sig.async_wait(handler2);
    };
```

### 跟踪日志
使用宏BOOST_ASIO_ENABLE_HANDLER_TRACKING可以启用asio的跟踪日志:
```c++
#define BOOST_ASIO_ENABLE_HANDLER_TRACKING // 启用跟踪日志
#include <boost/asio.hpp>
```
我们用输出重定向把跟踪日志写入文件，注意它输出的是cerr，所以要用数字2,shell命令如下:
```c++
signal_set 2>out.log // 注意重定向标准错误流
```

## 定时器
asio库提供了4个定时器，分别是deadline_timer, steady_timer, system_timer和high_resolution_timer。
```c++
#include <boost/asio/steady_timer.hpp>
#include <boost/asio/system_timer.hpp>
#include <boost/asio/high_resolution_timer.hpp>
```
### 类摘要
模板类basic_waitable_timer是定时器的真正实现，它的类摘要如下:
```c++
template <typename Clock>                   // chrono的时钟类型
class basic_waitable_timer
{
public:
    typedef Clock clock_type;               // 类型定义
    typedef typename clock_type::duration duration;
    typedef typename clock_type::time_point time_point;

    explicit basic_waitable_timer(io_service& io_service);
    basic_waitable_timer(io_service&, const time_point& expiry_time);
    basic_waitable_timer(io_service&, const duration& expiry_time);

    time_point expires_at() const;          // 获得过期时间点
    std::size_t expires_at(                 // 设置过期时间点
        const time_point& expiry_time);
    duration expires_from_now() const;      // 获得过期时间长度
    std::size_t expires_from_now(           // 设置过期时间长度
        const duration& expiry_time);

    void wait();                            // 同步等待
    void async_wait(WaitHandlr handler);    // 异步等待
    std::size_t cancel();                   // 取消所有handler
    std::size_t cancel_one();               // 取消一个handler
};
```
steady_timer, system_timer和high_resulution_timer是basic_waitable_timer的模板特化typedef:
```c++
typedef basic_waitable_timer<steady_clock> steady_timer;
typedef basic_waitable_timer<system_clock> system_timer;
typedef basic_waitable_timer<high_resolution_clock> high_resolution_timer;
```
async_wait()异步等待的handler要求形式如下:
```c++
void handler(const error_code& ec);
```
定时器也有cancel()函数，可以传递error::operation_aborted错误码通知所有异步操作取消，返回已经取消的handler数量。cancel_one()的功能与cancel()相同，但它一次只取消一个handler。

### 同步定时器
下面的代码示范了steady_timer的同步用法:
```c++
io_service io;                          // 必须是io_service对象
steady_timer t(io, 500_ms);             // 定时器，500ms后定时器终止

cout << t.expires_at() << endl;         // 查看终止的时间点，单位是纳秒
cout << t.expires_from_now() << endl;   // 查看终止的时间长度，单位是纳秒
t.wait();                               // 调用wait()同步等待
cout << "hello asio" << endl;
```
与thread库的sleep()函数对比:thread库的sleep()使用了互斥量和条件变量，在线程中等待，而asio则调用了操作系统的异步机制，如epoll,kqueue等，没有多线程的竞争。

### 异步定时器
```c++
io_service io;                          // io_service对象
steady_timer t(io, 500_ms);             // 定时器，500ms后过期

t.async_wait(                           // 异步等待，传入回调函数
    [](const error_code& ec) {          // lambda表达式,接收错误码参数
        cout << "hello asio" << endl;   // 忽略错误码
    });
io.run();                               // 启动事件循环，等待定时器事件
```

### 使用bind
定时器非常有用，我们可以用它增加回调函数的参数，使它能够做更多的事情。虽然async_wait()接收的回调函数类型是固定的，但可以使用bind配合占位符placeholders::error来绑定参数来适配bind的接口。
```c++
class timer_with_func
{
private:
    int m_count = 0;                            // 计数器成员变量
    int m_count_max = 0;                        // 计数器上限
    function<void()> m_f;                       // function对象，持有无参，无返回的可调用物
    steady_timer m_t;                           // asio定时器对象
    
    // timer_with_func的构造函数初始化成员变量，将计数器清零，设置计数器的上限，拷贝存储回调函数，并立即启动定时器。
    // 之所以要立即启动定时器，是因为我们必须保证在io_service.run()之前至少有一个异步操作在执行，
    // 否则io_service.run()会因为没有事件处理而立即结束:
public:
    template<typename F>                        // 模板类型，可以接收任意可调用物
    timer_with_func(io_service& io, int x, F func):
        m_count_max(x),                         // 初始化计数器
        m_f(func),                              // 初始化回调函数
        m_t(io, 200_ms)                         // 启动计时器
    {
        init();                                 // 异步等待计时器，注册回调函数
    }
private:
    typedef timer_with_func this_type;          // 定义自身的别名，方便使用

    void init()
    {
        m_t.async_wait(bind(                    // 使用bind绑定成员函数
            &this_type::handler, this,          // 传递this指针
            boost::asio::placeholders::error)); // 使用error占位符传递错误码
    }

    void handler(const error_)
}
```