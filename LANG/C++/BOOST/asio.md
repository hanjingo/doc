# Boost.Asio

[TOC]

asio不需要编译，但它依赖一些其他Boost库组件，最基本的是boost.system库，用来提供系统错误支持。与thread库不同的是asio默认使用标准库<chrono>提供的时间功能，如果要强制使用boost.chrono，可以定义宏BOOST_ASIO_DISABLE_STD_CHRONO。

asio使用之前需要包含以下头文件：

```c++
#include <boost/asio.hpp>
```



## 辅助库

### error_code

asio库使用system库的error_code和system_error来表示程序运行时的错误。

### io_service

#### io_service::work

当io_service里注册的所有事件都完成时,它就会退出事件循环，使用io_service::work可以避免因其他异步事件完成而结束事件循环；其在boost中的定义如下：

```c++
class io_service::work
{
public:
    explicit work(io_service& io_service);  // 构造函数启动工作
    ~work();                                // 析构函数停止工作
    boost::asio::io_service& get_io_service(); 
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

### buffer

asio提供了以下操作buffer工具：

- `buffer_size()` :获取缓冲区的长度。
- `buffer_cast<T*>()` :转换指针类型。
- `buffer_copy() `:拷贝缓冲区数据，类似memcpy。
  这些函数的声明如下:

#### mutable_buffer

```c++
class mutable_buffer
{
public:
    mutable_buffer();
    mutable_buffer(void* data, std::size_t size);
    ...
};
```

#### const_buffer

```c++
class const_buffer
{
public:
    const_buffer();
    const_buffer(const void* data, std::size_t size);
    const_buffer(const mutable_buffer& b);
    ...
};
```

### timer

asio库提供了4个定时器，分别是：

- deadline_timer

- steady_timer

- system_timer

- high_resolution_timer

  其所在头文件如下：

```c++
#include <boost/asio/steady_timer.hpp>
#include <boost/asio/system_timer.hpp>
#include <boost/asio/high_resolution_timer.hpp>
```

#### 同步定时器

下面的代码示范了steady_timer的同步用法:

```c++
io_service io;                          // 必须是io_service对象
steady_timer t(io, 500_ms);             // 定时器，500ms后定时器终止

cout << t.expires_at() << endl;         // 查看终止的时间点，单位是纳秒
cout << t.expires_from_now() << endl;   // 查看终止的时间长度，单位是纳秒
t.wait();                               // 调用wait()同步等待
cout << "hello asio" << endl;
```

#### 异步定时器

下面的代码示范了steady_timer的异步用法:

```c++
io_service io;                          // io_service对象
steady_timer t(io, 500_ms);             // 定时器，500ms后过期

t.async_wait(                           // 异步等待，传入回调函数
    [](const error_code& ec) {          // lambda表达式,接收错误码参数
        cout << "hello asio" << endl;   // 忽略错误码
    });
io.run();                               // 启动事件循环，等待定时器事件
```

#### timer配合bind和lambda使用

下面代码示范了steady_timer配合bind与lambda的用法：

```c++
class timer_with_func
{
public:
    template<typename F>
    timer_with_func(io_service& io, int x, F f):
    	mt(io, 200_ms)
    {
        init();
    }
private:
    steady_timer mt;
    typedef void(handler_type)(const error_code&); // 定义hadnler类型
    function<handler_type> h = [&](const error_code&) { ... };
    void init() { mt.async_wait(h); };
};

io_service io;
timer_with_func t1(io, 5, []{cout << "hello timer1" << endl;});
```



## 网络通信

### address

ip地址独立于TCP, UDP等通信协议之外，asio库使用类ip::address来表示IP地址，可以同时支持IPv4和IPv6两种地址；其定义如下：

```c++
class address
{
public:
    address();
    address(const address& other);
    ... 
};
```

使用示例：

```c++
ip::address addr;

addr = addr.from_string("127.0.0.1");
assert(addr.is_v4());
cout << addr.to_string() << endl;

addr = addr.from_string("ab::12:34:56");
assert(addr.is_v6());
```

### endpoint

有了address，再加上通信用的端口号就构成了一个socket端点，在asio库中用`ip::tcp::endpoint`来表示；endpoint是basic_endpoint的TCP协议特化，basic_endpoint类摘要如下：

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
    ...
};
```

使用示例：

```c++
ip::address addr;                       // ip地址对象
addr = addr.from_string("127.0.0.1");   // 一个ipv4地址

ip::tcp::endpoint ep(addr, 6688);       // 创建端点对象，端口号为6688
assert(ep.address() == addr);
assert(ep.port() == 6688);
```

### socket

socket类是TCP通信的基本类,它是basic_stream_socket的TCP协议特化，basic_stream_socket类摘要如下:

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
    ...
};
```

### acceptor

acceptor用于服务器端，在指定的端口号接收连接，acceptor必须配合socket类才能完成通信；acceptor是basic_socket_acceptor的TCP协议特化，basic_socket_acceptor定义如下:

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
    ...
};
```



## 示例

### 同步通信

#### 服务端

```c++
int main() {
	try{
		typedef ip::tcp::acceptor acc_typ;
  	typedef ip::tcp::endpoint ep_typ;
  	typedef ip::tcp::socket   sock_typ;
    
    cout << "server start." << endl;
    io_service io;
    acc_typ acceptor(io, ep_typ(ip::tcp::v4(), 6688)); // 创建监听器
    for(;;)
    {
    	sock_typ sock(io);            // 创建套接字
      acceptor.accept(sock);           // 阻塞等待socket连接
      sock.send(buffer("hello asio")); // 发送数据
    }
	} catch (std::exception& e) {
  	cout << e.what() << endl;
  }
}
```

#### 客户端

```c++
int main() {
	try {
  	typedef ip::tcp::endpoint ep_typ;
    typedef ip::tcp::socket   sock_typ;
    typedef ip::address       addr_typ;
    
    cout << "client start." << endl;
    io_service io;
    sock_typ sock(io);
    ep_typ ep(addr_typ::from_string("127.0.0.1"), 6688);
    sock.connect(ep);
    vector<char> str(sock.available() + 1, 0);
    sock.receive(buffer(str));
    cout << &str[0] << endl;
  } catch (std::exception& e) {
  	cout << e.what() << endl;
  }
}
```

### 异步通信

#### 服务端

```c++
class server {
	typedef server this_type;
  typedef ip::tcp::acceptor acceptor_type;
  typedef ip::tcp::endpoint endpoint_type;
  typedef ip::tcp::socket   socket_type;
  typedef shared_ptr<socket_type> sock_ptr;
  
private:
  io_service m_io;
  acceptor_type m_acceptor;
  
public:
  server() : m_acceptor(m_io, endpoint_type(ip::tcp::v4(), 6688)) { accept(); }
  void run() { m_io.run(); }
  void accept() {
  	sock_ptr sock(new socket_type(m_io));
    acceptor.async_accept(*sock, bind)
  }
}
```



# 参考

### 文献

[1] Boost程序库完全开发指南-深入c++"准"标准库

### 外链

- 

