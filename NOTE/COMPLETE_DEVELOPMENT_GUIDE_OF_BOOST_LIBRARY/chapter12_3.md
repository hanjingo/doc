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

    void handler(const error_code&)
    {
        if (m_count++ >= m_count_max)           // 如果计数器到达上限则退出
        { return; }

        m_f();                                  // 调用function对象

        m_t.expires_from_now(200_ms);           // 设置定时器的终止时间为0.2秒之后

        m_t.async_wait(bind(                    // 再次启动定时器，异步等待
            &this_type::handler, this,
            boost::asio::placeholders::error));
    }
}; // timer_with_func定义结束

// timer_with_func的调用代码非常简单，只需要一个io_service对象即可
io_service io;                                  // io_service对象

timer_with_func t1(io, 5, 
    []{cout << "hello timer1" << endl;});

timer_with_func t2(io, 5, 
    []{cout << "hello timer2" << endl;});

io.run();                                       // io_service等待异步调用结束
```

### 使用lambda
```c++
private:
    typedef void(handler_type)(const error_code&);  // 定义handler类型

    function<handler_type> m_handler =              // 捕获引用，包括this
    [&](const error_code&)
    {
        ...
        m_t.expires_from_now(200_ms);               // 设置定时器的终止时间
        m_t.async_wait(m_handler);                  // 再次异步等待
    };

void init()
{
    m_t.async_wait(m_handler);                      // 异步等待，注册回调函数
}
```

## 网络通信
ip::tcp位于头文件<boost/asio/ip/tcp.hpp>,其摘要如下:
```c++
class tcp
{
public:
    typedef basic_endpoint<tcp>             endpoint;
    typedef basic_stream_socket<tcp>        socket;
    typedef basic_socket_acceptor<tcp>      acceptor;
    typedef basic_resolver<tcp>             resolver;
    typedef basic_resolver_query<tcp>       resolver_query;
    typedef basic_resolver_iterator<tcp>    resolver_iterator;
    typedef basic_socket_iostream<tcp>      iostream;

    int type() const;       // 获取协议类型
    int protocol() const;   // 获取协议标志
    int family() const;

    static tcp v4();        // 返回ipv4版tcp对象
    static tcp v6();        // 返回ipv6版tcp对象
}
```

### address
ip地址独立于TCP, UDP等通信协议之外，asio库使用类ip::address来表示IP地址，可以同时支持IPv4和IPv6两种地址，他的类摘要如下:
```c++
class address
{
public:
    address();
    address(const address& other);

    bool is_v4() const;                          // 是否是ipv4地址
    bool is_v6() const;                          // 是否是ipv6地址
    bool is_loopback() const;                    // 是否是环回地址

    ip::address_v4 to_v4() const;                // 转换为ipv4地址
    ip::address_v6 to_v6() const;                // 转换为ipv6地址

    string to_string() const;                    // 转换为字符串表示

    static address from_string(const char* str); // 从字符串构造
    static address from_string(const string& str);

    friend bool operator==(const address& a1, const address& a2);
    ... // 其他比较操作和流输出操作
private:
    enum { ipv4, ipv6 } type_;                  // ipv4地址和ipv6地址的枚举

    boost::asio::ip::address_v4 ipv4_address_;  // ipv4地址的内部实现
    boost::asio::ip::address_v6 ipv6_address_;  // ipv6地址的内部实现
};
```
例:
```c++
ip::address addr;

addr = addr.from_string("127.0.0.1");
assert(addr.is_v4());
cout << addr.to_string() << endl;

addr = addr.from_string("ab::12:34:56");
assert(addr.is_v6());
```

### endpoint
有了ip地址，再加上通信用的端口号就构成了一个socket端点，在asio库中用ip::tcp::endpoint来表示

endpoint是basic_endpoint的TCP协议特化，其类摘要如下:
```c++
template <typename InternetProtocol>
class basic_endpoint
{
public:
    typedef InternetProtocol protocol_type;

    basic_endpoint(const InternetProtocol& internet_protocol,
                    unsigned short port_num);
    basic_endpoint(const ip::address& addr, unsigned short port_num);

    basic_endpoint(basic_endpoint&& other);
    basic_endpoint& operator=(const basic_endpoint& other);

    protocol_type protocol() const;     // 获取协议

    unsigned short port() const;        // 获取端口号
    void port(unsigned short port_num); // 设置端口号

    ip::address address() const;        // 获取地址
    void address(ip::address& addr);    // 设置地址
};
```
例:
```c++
ip::address addr;                       // ip地址对象
addr = addr.from_string("127.0.0.1");   // 一个ipv4地址

ip::tcp::endpoint ep(addr, 6688);       // 创建端点对象，端口号为6688
assert(ep.address() == addr);
assert(ep.port() == 6688);
```

### socket
socket类是TCP通信的基本类,它是basic_stream_socket的TCP协议特化，其摘要如下:
```c++
tempate <typename Protocol, ...>
class basic_stream_socket
{
public:
    typedef Protocol protocol_type;
    typedef typename Protocol::endpoint endpoint_type;

    // 构造函数
    explicit basic_stream_socket(io_service& io_service);
    basic_stream_socket(io_service& io_service,
                        const protocol_type& protocol);
    basic_stream_socket(io_service& io_service,
                        const endpoint_type& endpoint);

    // 转移构造函数
    basic_stream_socket(basic_stream_socket&& other);
    basic_stream_socket& operator=(basic_stream_socket&& other);

    // 打开关闭端口，取消操作
    void open(const protocol_type& protocol = protocol_type());
    bool is_open() const;
    void close();
    void shutdown(shutdown_type what);
    void cancel();

    // 可读取的字节数
    std::size_t available() const;

    // 绑定endpoint
    void bind(const endpoint_type& endpoint);
    // 连接endpoint
    void connect(const endpoint_type& peer_endpoint);
    void async_connect(const endpoint_type& peer, handler);

    // 设置socket选项
    void set_option(const SettableSocketOption& option);
    void get_option(GettableSocketOption& option) const;

    // 是否是非阻塞的
    bool non_blocking() const;
    void non_blocking(bool mode);

    // 本地endpoint和远端endpoint
    endpoint_type local_endpoint() const;
    endpoint_type remote_endpoint() const;

    // 发送数据
    std::size_t send(const ConstBuffer& buffers);
    void async_send(const ConstBuffer& buffers, handler);

    // 接收数据
    std::size_t receive(const MutableBuffer& buffers);
    void async_receive(const MutableBuffer& buffers, handler);

    // 发送数据
    std::size_t write_some(const ConstBuffer& buffers);
    void async_write_some(const ConstBuffer& buffers, handler);

    // 接收数据
    std::size_t read_some(const MutableBuffer& buffers);
    void async_read_some(const MutableBuffer& buffers, handler);
};
```
异步读写函数async_xxx()可以使用2种形式的handler:
```c++
void handler(const error_code& ec,          // 操作的错误码
            std::size_t bytes_transferred); // 传输的字节数
void handler(const error_code& ec);         // 忽略传输的字节数
```

### acceptor
acceptor类对应Socket API的accept()函数功能，它用于服务器端，在指定的端口号接收连接，acceptor必须配合socket类才能完成通信。

acceptor是basic_socket_acceptor的TCP协议特化，其摘要如下:
```c++
template <typename Protocol, ...>
class basic_socket_acceptor
{
public:
    typedef Protocol protocol_type;
    typedef typename Protocol::endpoint endpoint_type;

    // 构造函数
    explicit basic_socket_acceptor(io_service& io_service);

    basic_socket_acceptor(io_service& io_service,
                            const protocol_type& protocol;
    basic_socket_acceptor(io_service& io_service,
                            const endpoint_type& endpoint,
                            bool reuse_addr = true);

    // 转移构造函数
    basic_socket_acceptor(basic_socket_acceptor&& other);
    basic_socket_acceptor& operator=(basic_socket_acceptor&& other);

    // 打开关闭端口,取消操作
    void open(const protocol_type& protocol = protocol_type());
    bool is_open() const;
    void close();
    void cancel();

    // 绑定endpoint,监听端口
    void bind(const endpoint_type& endpoint);
    void listen(int backlog = socket_base::max_connections);

    // 是否是非阻塞的
    bool non_blocking() const;
    void non_blocking(bool mode);

    // 设置socket选项
    void set_option(const SettableSocketOption& option);
    void get_option(GettableSocketOption& option);

    // 本地endpoint
    endpoint_type local_endpoint() const;

    // 接收请求
    void accept(socket& peer);
    void async_accept(socket& peer, handler);
    void accept(socket& peer, endpoint_type& peer_endpoint);
    void async_accept(socket& peer, endpoint_type& peer_endpoint, handler);
};
```

## 同步通信
服务端:
```c++
int main()
try
{
    typedef ip::tcp::acceptor   acceptor_type;
    typedef ip::tcp::endpoint   endpoint_type;
    typedef ip::tcp::socket     socket_type;

    cout << "server start." << endl;
    io_service io;                              // asio程序必需的io_service对象

    acceptor_type acceptor(io,                  // 创建acceptor对象，ipv4
        endpoint_type(ip::tcp::v4(), 6688));    // 接收6688端口，开始监听

    cout << acceptor.local_endpoint().address() << endl;

    for(;;) // 循环执行服务
    {
        socket_type sock(io);                   // 一个socket对象

        acceptor.accept(sock);                  // 阻塞等待socket连接

        cout << "client:";
        cout << sock.remote_endpoint().address() << endl;

        sock.send(buffer("hello asio"));        // 发送数据，使用buffer()
    }
}
catch (std::exception& e)                       // 捕获可能发生的异常
{
    cout << e.what() << endl;
}
```
客户端:
```c++
int main()
try
{
    typedef ip::tcp::endpoint   endpoint_type;  // 简化类型定义
    typedef ip::tcp::socket     socket_type;
    typedef ip::address         address_type;

    cout << "client start." << endl;

    io_service io;                              // io_service对象
    
    socket_type sock(io);                       // 创建socket对象

    endpoint_type ep(
        address_type::from_string("127.0.0.1"), 6688);

    sock.connect(ep);                           // socket连接到端点
    cout << sock.available() << endl;           // 获取可读取的字节数

    vector<char> str(sock.available()+1, 0);    // 定义一个vector缓冲区
    sock.receive(buffer(str));                  // 使用buffer()包装缓冲区，接收数据

    cout << "receive from " << sock.remote_endpoint().address();
    cout << &str[0] << endl;
}
catch (std::exception& e)
{
    cout << e.what() << endl;
}
```
在接受数据时，我们使用了vector<char>作为接收缓冲区，它可以分配大于sock.available()的内存，一次性接收所有数据，否则就要循环接收，直到返回错误码(或者捕获异常):
```c++
vector<char> str(5, 0); // 缓冲区长度5
error_code ec;

for(;;)
{
    sock.read_some(buffer(str), ec); // 使用read_some()的错误码形式
    if (ec)
    { break; }
    cout << &str[0];
}
```

## 异步通信
服务器端：
```c++
class server
{
    typedef server this_type;
    typedef ip::tcp::acceptor acceptor_type;
    typedef ip::tcp::endpoint endpoint_type;
    typedef ip::tcp::socket socket_type;
    typedef shared_ptr<socket_type> sock_ptr;

private:
    io_service m_io;
    acceptor_type m_acceptor;

    /*
    server类必需的成员变量是io_service对象和一个acceptor对象,他们是TCP通信的必备要素，
    我们还定义了一个智能指针的typedef,它指向socket对象，用来在回调函数中传递.
    */
public:
    server() : m_acceptor(m_io, endpoint_type(ip::tcp::v4(), 6688))
    { accept(); }

    void run()
    { m_io.run(); }

    /*
    server的构造函数使用io_service, TCP协议和端口初始化acceptor对象，并用accept()函数立即启动异步服务
    */
    void accept()
    {
        sock_ptr sock(new socket_type(m_io));
        acceptor.async_accept(*sock,
            bind(&this_type::accept_handler, this,
                boost::asio::placeholders::error, sock));
    }

    /*
    accept()函数用于启动异步，接收连接，它需要调用acceptor的async_accept()函数。
    为了能够让socket对象能够被异步调用后还能继续使用，我们可以使用shared_ptr来创建socket对象的智能指针，
    它可以在程序的整个生命周期中存在，直到没有人使用它为止。
    当有TCP链接发生时，server::accept_handler()函数将被调用，它使用socket对象发送数据。
    */
    void accept_handler(const error_code& ec, sock_ptr sock)
    {
        if (ec)
        { return; }

        cout << "client:";
        cout << sock->remote_endpoint().address() << endl;
        sock->async_write_some(buffer("hello asio"),
            bind(&this_type::write_handler, this,
            boost::asio::placeholders::error));
        accept();
    }

    /*
    发送数据的回调函数write_handler()很简单，因为我们不需要做更多的工作，可以直接实现一个空函数，
    在这里我们简单地输出一条消息，表示异步发送数据完成。
    */
    void write_handler(const system::error_code&) // 忽略字节数
    { cout << "send msg complete." << endl; }
    void write_handler2(const error_code&, std::size_t n)
    { cout << "send msg " << n << endl; }
}

int main()
try
{
    cout << "server start." << endl;
    server srv; // 构造server对象
    srv.run();  // 启动异步调用事件处理循环
}
catch (std::exception& e)
{
    cout << e.what() << endl;
}
```
客户端:
```c++
class client
{
    typedef client                  this_type;
    typedef ip::tcp::endpoint       endpoint_type;
    typedef ip::address             address_type;
    typedef ip::tcp::socket         socket_type;
    typedef shared_ptr<socket_type> sock_ptr;
    typedef vector<char>            buffer_type;
private:
    io_service      m_io;  // io_service对象
    buffer_type     m_buf; // 接收缓冲区
    endpoint_type   m_ep;  // TCP端点

    client():
        m_buf(100, 0),
            m_ep(address_type::from_string("127.0.0.1"), 6688)
    {
        start();
    }

    void run()
    { m_io.run(); }

    void start()
    {
        sock_ptr sock(new socket_type(m_io));   // 创建socket对象
        sock->async_connect(m_ep,               // 异步链接
            bin(&this_type::conn_handler, this,
                boost::asio::placeholders::error, sock));
    }

    void conn_handler(const error_code& ec, sock_ptr sock)
    {
        if (ec)                                 // 处理错误代码
        { return; }
        cout << "recive from " << sock->remote_endpoint().address();

        sock->async_read_some(buffer(m_buf),    // 异步读取数据
            bind(&client::read_handler, this,
                boost::asio::placeholders::error));
    }

    void read_handler(const error_code& ec)
    {
        if (ec)
        { return; }
        cout << &m_buf[0] << endl;
    }

    void conn_handler(const error_code& ec, sock_ptr sock)
    {
        ...
        sock->async_read_some(buffer(m_buf),
            bind(&client::read_handler, this,
                boost::asio::placeholders::error, sock));   // 绑定sock传递
    }

    void read_handler(const error_code& ec, sock_ptr sock)
    {
        ...
        sock->async_read_some(buffer(m_buf),                // 继续异步读取数据
            bind(&client::read_handler, this,
                boost::asio::placeholders::error, sock));
    }
}

int main()
try
{
    cout << "client start." << endl;
    client cl;
    cl.run();
}
catch (std::exception& e)
{ cout << e.what() << endl; }
```

### 使用lambda
服务端使用lambda:
```c++
void accept()
{
    sock_ptr sock(new socket_type(m_io));   // 智能指针

    m_acceptor.async_accept(*sock,          // 异步监听服务
        [this, sock](const error_code& ec){
            if (ec)
            { return; }

            sock->async_send(               // 异步发送数据
                buffer("hello asio"),
                [](const error_code&, std::size_t)
                { cout << "send msg complate." << endl; });

            accept();                       // 再次启动异步接收连接
        });
}
```
客户端使用lambda:
```c++
void start()
{
    sock_ptr sock(new socket_type(m_io));                           // 智能指针

    sock->async_connect(m_ep,                                       // 启动异步链接
        [this, sock](const error_code& ec){                         // 捕获this和sock对象
            if (ec)
            { return; }                                             // 检查错误码

            sock->async_read_some(buffer(m_buf),                    // 启动异步读取
                [this, sock](const error_code& ec, std::size_t){    // lambda表达式
                    read_handler(ec, sock);                         // 调用read_handler
                });
        });
}
```

## 域名解析
### 类摘要
resolver是basic_resolver的TCP协议特化，其类摘要如下:
```c++
template <typename InternetProtocol,...>
class basic_resolver
{
public:
    typedef InternetProtocol                            protocol_type;
    typedef typename InternetProtocol::endpoint         endpoint_type;
    typedef basic_resolver_query<InternetProtocol>      query;
    typedef basic_resolver_interator<InternetProtocol>  iterator;

    explicit basic_resolver(io_service& io_service);
    void cancel();
    iterator resolve(const query& q);
    void async_resolve(const query& q, ResolveHandler handler);
    iterator resolve(const endpoint_type& e);
    void async_resolve(const endpoint_type& e, ResolveHandler handler);
};

template <typename InternetProtocol>
class basic_resolver_query
{
public:
    typedef InternetProtocol protocol_type;

    basic_resolver_query(const std::string& service,
        flags resolve_flags = passive | address_configured);

    basic_resolver_query(const protocol_type& protocol,
        const std::string& service,
        flags resolve_flags = passive | address_configured);

    basic_resolver_query(const std::string& host,
        const std::string& service,
        flags resolve_flags = address_configured);

    std::string host_name() const;
    std::string service_name() const;
}
```

### 用法
```c++
void resolve_connect(io_service &io,    // io_service对象
    ip::tcp::socket &sock,              // socket对象
    const char* name, int port)         // 网址和端口号
{
    ip::tcp::resolver r(io);            // 创建resolver对象

    ip::tcp::resolver::query q(         // 创建query对象
        name, lexical_cast<string>(port));

    auto iter = r.resolve(q);           // 使用resolve()迭代端点
    decltype(iter) end;                 // 尾部迭代器
    error_code ec = error::host_not_found;

    for (;ec && iter != end; ++iter)
    {
        sock.close();
        sock.connect(*iter, ec);        // 尝试连接
    }
    if (ec)
    {
        cout << "can't connect." << endl;
        throw system_error(ec);
    }
}

int main()
try
{
    io_service io;
    ip::tcp::socket sock(io);

    resolve_connect(io, sock, "www.baidu.com", 80);
    cout << sock.remote_endpoint() << endl;
}
catch (std::exception& e)
{
    cout << e.what() << endl;
};
```
resolver不仅能解析域名，它也支持使用IP地址和服务名:
```c++
ip::tcp::resolver::query q("127.0.0.1", "http");
```

## 使用协程
使用协程功能需要包含头文件<boost/asio/spawn.hpp>,并连接libboost_context.a, libboost_coroutine.a和libboost_thread.a。
### 摘要
asio的协程功能主要使用类yield_context,它是basic_yield_context的typedef,其类摘要如下:
```c++
template <typename Handler>
class basic_yield_context                   // 包装协程相关对象
{
public:
    basic_yield_context(
        const detail::weak_ptr<callee_type>& coro,
        caller_type& ca, Handler& handler);

    basic_yield_context operator[](boost::system::error_code& ec) const;

    detail::weak_ptr<callee_type> coro_;    // 协程
    caller_type& ca_;                       // 协程
    Handler& handler_;                      // 完成回调函数
    boost::system::error_code& ec_;         // 错误码
};

typedef basic_yield_context<                // 类型定义
    detail::wrapped_handler<
        io_service::strand, void(*)(),
        detail::is_continuation_if_running> > yield_context;
```
通常我们不直接创建yield_context对象，而是使用函数spawn()创建yield_context对象。它产生yield_context对象，再将其传递给使用yield_context对象的函数。spawn()有多个重载形式，常用的是以下2种:
```c++
void spawn(strand s, Function function);        // 使用strand创建协程
void spawn(io_service io, Function function);   // 使用io_service创建协程
```
其中的function必须符合以下函数签名:
```c++
void func(boost::asio::yield_context yield);    // 使用yield_context参数
```

### 用法
```c++
int main()
{
    typedef ip::tcp::acceptor   acceptor_type;
    typedef ip::tcp::endpoint   endpoint_type;
    typedef ip::tcp::socket     socket_type;

    io_service io; // 必需的io_service对象

    spawn(io, [&](yield_context yield){ // 使用spawn函数产生协程
        acceptor_type acceptor(io, endpoint_type(ip::tcp::v4(), 6688));

        for(;;)
        {
            socket_type sock(io);
            error_code ec;

            acceptor.async_accept(sock, yield[ec]);

            if (ec)
            { return; }

            auto len = sock.async_write_some(
                buffer("hello coroutine"), yield);
            cout << "send " << len << "bytes" << endl;
        }
    });
}
```