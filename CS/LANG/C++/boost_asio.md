# Boost.Asio

[TOC]

asio不需要编译，但它依赖一些其他Boost库组件，最基本的是boost.system库，用来提供系统错误支持。与thread库不同的是asio默认使用标准库<chrono>提供的时间功能，如果要强制使用boost.chrono，可以定义宏BOOST_ASIO_DISABLE_STD_CHRONO。

asio使用之前需要包含以下头文件：

```c++
#include <boost/asio.hpp>
```

## API

### io_service

| API                                     | 参数               | 说明                       |
| --------------------------------------- | ------------------ | -------------------------- |
| `std::size_t run()`                     |                    | 阻塞执行事件循环           |
| `std::size_t run_once()`                |                    | 至少阻塞执行一个handler    |
| `std::size_t poll()`                    |                    | 非阻塞，执行ready的handler |
| `std::size_t poll_one()`                |                    | 至少执行一个ready的handler |
| `void stop()`                           |                    | 停止事件循环               |
| `bool stopped() const`                  |                    | 时间循环是否已经停止       |
| `bool reset() const`                    |                    | 重启时间循环               |
| `unspecified dispatch(Handler handler)` | - handler 回调函数 | 要求异步执行一个handler    |
| `unspecified post(Handler handler)`     | - handler 回调函数 | 要求异步执行一个handler    |

### timer

steady_timer, system_timer和high_resulution_timer是basic_waitable_timer的模板特化，其函数如下：

| API                                                         | 参数                       | 说明             |
| ----------------------------------------------------------- | -------------------------- | ---------------- |
| `time_point expires_at() const`                             |                            | 获取过期时间点   |
| `std::size_t expires_at(const time_point& expiry_time)`     | - expiry_time 过期时间     | 设置过期时间点   |
| `duration expires_from_now() const`                         |                            | 获得过期时间长度 |
| `std::size_t expires_from_now(const duration& expiry_time)` | - expire_time 过期时间长度 | 设置过期时间长度 |
| `void wait()`                                               |                            | 听不等待         |
| `void async_wait(WaitHandler handler)`                      |                            | 异步等待         |
| `std::size_t cancel()`                                      |                            | 取消所有handler  |
| `std::size_t cancel_one()`                                  |                            | 取消一个handler  |

### address

| API                                                          | 参数                     | 说明             |
| ------------------------------------------------------------ | ------------------------ | ---------------- |
| `bool is_v4() const`                                         |                          | 是否是ipv4地址   |
| `bool is_v6() const`                                         |                          | 是否是ipv6地址   |
| `bool is_loopback() const`                                   |                          | 是否是环回地址   |
| `ip::address_v4 to_v4() const`                               |                          | 转换为ipv4地址   |
| `ip::address_v6 to_v6() const`                               |                          | 转换为ipv6地址   |
| `string to_string() const`                                   |                          | 转换为字符串表示 |
| `static address from_string(const char* str)`                | - str 字符串             | 从字符串构造     |
| `static address from_string(const string& str)`              | - str 字符串             | 从字符串构造     |
| `friend bool operator==(const address& a1, const address& a2)` | - a1 地址1<br>- a2 地址2 | 比较地址是否一致 |

### endpoint

| API                                  | 参数              | 说明       |
| ------------------------------------ | ----------------- | ---------- |
| `protocol_type protocol() const`     |                   | 获取协议   |
| `unsigned short port() const`        |                   | 获取端口号 |
| `void port(unsigned short port_num)` | - port_num 端口号 | 设置端口号 |
| `ip::address address() const`        |                   | 获取地址   |
| `void address(ip::address& addr)`    | - addr 地址       | 设置地址   |

### socket

| API                                                          | 参数                                         | 说明               |
| ------------------------------------------------------------ | -------------------------------------------- | ------------------ |
| `void open(const protocol_type& protocol = protocol_type())` | - protocol 协议                              | 打开协议           |
| `bool is_open() const`                                       |                                              | 打开endpoint       |
| `void close()`                                               |                                              | 关闭endpoint       |
| `void shutdown(shutdown_type what)`                          | - what 关闭类型                              | 关闭endpoint       |
| `void cancel()`                                              |                                              | 取消               |
| `std::size_t available() const`                              |                                              | 获取可读取的字节数 |
| `void bind(const endpoint_type& endpoint)`                   | - endpoint 端点                              | 绑定endpoint       |
| `void connect(const endpoint_type& peer_endpoint)`           | - peer_endpoint 对方端点                     | 连接endpoint       |
| `void async_connect(const endpoint_type& peer, handler)`     | - peer 对方端点<br>- handler 回调函数        | 异步连接endpoint   |
| `void set_option(const SettableSocketOption& option)`        | - option 选项                                | 设置socket选项     |
| `void get_option(GettableSocketOption& option) const`        | - option 选项                                | 获得socket选项     |
| `bool non_blocking() const`                                  |                                              | 是否是非阻塞的     |
| `void non_blocking(bool mode)`                               | - mode 模式                                  | 是否是非阻塞的     |
| `endpoint_type local_endpoint() const`                       |                                              | 获取本地endpoint   |
| `endpoint_type remote_endpoint() const`                      |                                              | 获取远程endpoint   |
| `std::size_t send(const ConstBuffer& buffers)`               | - buffers 缓冲区                             | 发送数据           |
| `void async_send(const ConstBuffer& buffers, handler)`       | - buffers 缓冲区<br>- handler 回调函数       | 异步发送数据       |
| `std::size_t receive(const MutableBuffer& buffers)`          | - buffers 缓冲区                             | 接收数据           |
| `void async_receive(const MutableBuffer& buffers, handler)`  | - buffers 缓冲区<br>- handler 回调函数       | 异步接收数据       |
| `std::size_t write_some(const ConstBuffer& buffers)`         | - buffers 缓冲区                             | 写数据             |
| `void async_write_some(const ConstBuffer& buffers, handler)` | - ConstBuffer 缓冲区<br>- handler 回调函数   | 异步写数据         |
| `std::size_t read_some(const MutableBuffer& buffers)`        | - MutableBuffer 缓冲区                       | 读数据             |
| `void async_read_some(const MutableBuffer& buffers, handler)` | - MutableBuffer 缓冲区<br>- handler 回调函数 | 异步读数据         |

异步读写函数async_xxx()可以使用2种形式的handler:

```c++
void handler(const error_code& ec,          // 操作的错误码
            std::size_t bytes_transferred); // 传输的字节数
void handler(const error_code& ec);         // 忽略传输的字节数
```

### acceptor

acceptor是basic_socket_acceptor的TCP协议特化，其函数如下：

| API                                                          | 参数                                                        | 说明                               |
| ------------------------------------------------------------ | ----------------------------------------------------------- | ---------------------------------- |
| `void open(const protocol_type& protocol = protocol_type())` | - protocol 协议类型                                         | 打开endpoint                       |
| `bool is_open() const`                                       |                                                             | 监听器是否打开                     |
| `void close()`                                               |                                                             | 关闭监听器                         |
| `void cancel()`                                              |                                                             | 取消监听                           |
| `void bind(const endpoint_type& endpoint)`                   | - endpoint 端点                                             | 绑定endpoint                       |
| `void listen(int backlog = socket_base::max_connections)`    | - backlog 最大连接数                                        | 监听绑定的endpoint，设置最大连接数 |
| `bool non_blocking() const`                                  |                                                             | 是否是非阻塞的                     |
| `void non_blocking(bool mode)`                               |                                                             | 是否是非阻塞的                     |
| `void set_option(const SettableSocketOption& option)`        | - option                                                    | 设置socket选项                     |
| `void get_option(GettableSocketOption& option)`              |                                                             | 获得socket选项                     |
| `endpoint_type local_endpoint() const`                       |                                                             | 获得本地endpoint                   |
| `void accept(socket& peer)`                                  |                                                             | 接收请求                           |
| `void async_accept(socket& peer, handler)`                   | - peer 套接字节点<br>- handler 回调函数                     | 异步接收请求                       |
| `void accept(socket& peer, endpoint_type& peer_endpoint)`    | - peer 套接字<br>- peer_endpoint 端点                       | 接收请求                           |
| `void async_accept(socket& peer, endpoint_type& peer_endpoint, handler)` | - peer 套接字<br>- peer_endpoint 端点<br>- handler 回调函数 | 异步接收请求                       |

### resolver

```c++
typedef basic_resolver_query<InternetProtocol>      query;
typedef basic_resolver_interator<InternetProtocol>  iterator;
```

| API                                                          | 参数                                 | 说明           |
| ------------------------------------------------------------ | ------------------------------------ | -------------- |
| `void cancel()`                                              |                                      | 取消解析       |
| `iterator resolve(const query& q)`                           | - q 解析查询类                       | 解析查询类     |
| `void async_resolve(const query& q, ResolveHandler handler)` | - q 解析查询类<br>- handler 回调函数 | 异步解析查询类 |
| `iterator resolve(const endpoint_type& e)`                   | - e 端点                             | 解析端点       |
| `iterator async_resolve(const endpoint_type& e, ResolveHandler handler)` | - e 端点<br>- handler 解析额回调函数 | 异步解析端点   |



## 辅助库

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

- error                     :表示error_code值。
- signal_number     :表示UNIX信号值。
- bytes_transferred :表示可读写的字节数。

### error_code

asio库使用system库的error_code和system_error来表示程序运行时的错误。

### io_service

TODO

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

steady_timer, system_timer和high_resulution_timer是basic_waitable_timer的模板特化typedef:

```c++
typedef basic_waitable_timer<steady_clock> steady_timer;
typedef basic_waitable_timer<system_clock> system_timer;
typedef basic_waitable_timer<high_resolution_clock> high_resolution_timer;
```

basic_waitable_timer的定义如下：

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
    ...
}
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

### ip::tcp

ip::tcp位于头文件<boost/asio/ip/tcp.hpp>，其摘要如下：

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

### resolver

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
...
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
...
}
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

- error                     :表示error_code值。
- signal_number     :表示UNIX信号值。
- bytes_transferred :表示可读写的字节数。



## 示例

### 1. 同步通信

```c++
// 服务端
int main() {
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
}
```

```c++
// 客户端
int main() {
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
}
```

### 2. 异步通信

```c++
// 服务端
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
    acceptor.async_accept(*sock, [this, sock](const error_code& ec){
    	if (ec) { return; }
      sock->async_send(
      	buffer("hello asio"),
      	[](const error_code&, std::size_t){ cout << "send msg complete." << endl; });
      accept();
    });
  }
  void accept_handler(const error_code& ec, sock_ptr sock) {
  	if (ec) { return; }
    sock -> async_write_some(buffer("hello asio"), 
      bind(&this_type::write_handler, this, boost::asio::placeholders::error));
    accept();
  }
  void write_handler(const system::error_code&) 
  { cout << "send msg complete." << endl; }
  void write_handler2(const error_code&, std::size_t n)
  { cout << "send msg" << n << endl; }
}

int main() {
	server src;
  serv.run();
}
```

```c++
// 客户端
class client
{
	typedef client                  this_type;
  typedef ip::tcp::endpoint       endpoint_type;
  typedef ip::address             address_type;
  typedef ip::tcp::socket         socket_type;
  typedef shared_ptr<socket_type> sock_ptr;
  typedef vector<char>            buffer_type;
private:
  io_service    m_io;  // io_service对象
  buffer_type   m_buf; // 接收缓冲区
  endpoint_type m_ep;  // TCP端点
  
  client() : m_buf(100, 0), m_ep(address_type::from_string("127.01.0.1"), 6688)
  {
  	start();
  }
  
  void run()
  { m_io.run(); }
  
  void start()
  {
  	sock_ptr sock(new socket_type(m_io));
    sock->async_connect(m_ep, [this, sock](const error_code& ec){
    	if (ec) { return; }
      sock->async_read_some(buffer(m_buf), [this, sock](const error_code& ec, std::size_t){
      	read_handler(ec, sock);
      });
    });
  }
  
  void conn_handler(const error_code& ec, sock_ptr sock)
  {
  	if (ec)
    { return; }
    cout << "receive from" << sock->remote_endpoint().address();
    
    sock->async_read_some(buffer(m_buf),
    	bind(&client::read_handler, this, boost::asio::placeholders::error));
  }
  
  void read_handler(const error_code& ec)
  {
  	if (ec) { return; }
    cout << &m_buf[0] << endl;
  }
  
  void conn_handler(const error_code& ec, sock_ptr sock)
  {
  	...
    sock->async_read_some(buffer(m_buf),
    	bind(&client::read_handler, this, boost::asio::placeholders::error, sock));
  }
  
  void read_handler(const error_code& ec, sock_ptr sock)
  {
  	...
    sock->async_read_some(buffer(m_buf),
    	bind(&client::read_handler, this, boost::asio::placeholders::error, sock));
  }
}

int main() 
{
	cout << "client start." << endl;
  client c1;
  c1.run();
}
```

### 域名解析

```c++
void resolve_connect(io_service &io, ip::tcp::socket &sock, const char* name, int port)
{
	ip::tcp::resolver r(io);
  ip::tcp::resolver::query q(name, lexical_cast<string>(port));
  auto iter = r.resolve(q); // 使用resolver()迭代端点
  decltype(iter) end;       // 尾部迭代器
  error_code ec = error::host_not_found;
  
  for (; ec && iter != end; ++iter)
  {
  	sock.close();
    sock.connect(*iter, ec); // 尝试连接
  }
  if (ec)
  {
  	cout << "can't connect." << endl;
    throw system_error(ec);
  }
}

int main() 
{
	io_service io;
  ip::tcp::socket sock(io);
  
  resolve_connect(io, sock, "www.baidu.com", 80);
  cout << sock.remote_endpoint() << endl;
}
```

### UDP协议通信

```c++
// 服务端
int main()
{
	io_service io;
  ip::udp::socket sock(io, ip::udp::endpoint(ip::udp::v4(), 6699));
  for (;;)
  {
  	char buf[1];
    ip::udp::endpoint ep;
    error_code ec;
    sock.receive_from(buffer(buf), ep, 0, ec); // 阻塞接收
    
    if (ec && ec != error::message_size) { throw system_error(ec); }
    cout << "send to" << ep.address() << endl;
    sock.send_to(buffer("hello asio udp"), ep);
  }
}
```

```c++
// 客户端
int main()
{
	io_service io;
  ip::udp::endpoint send_ep(ip::address::from_string("127.0.0.1"), 6699);
  ip::udp::socket sock(io); // 创建UDP socket对象
  sock.open(ip::udp::v4());
  
  char buf[1];
  sock.send_to(buffer[buf], send_ep); // 发送数据
  
  vector<char> v(100, 0);
  ip::udp::endpoint recv_ep;
  sock.receive_from(buffer(v), recv_ep); // 接收数据
  cout << "recv from" << recv_ep.address() << " ";
  cout << &v[0] << endl;
}
```

# 参考

[1] 罗剑锋.Boost程序库完全开发指南-深入c++"准"标准库

