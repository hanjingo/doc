# system
system库使用轻量级的对象封装了操作系统底层的错误代码和错误信息，使调用操作系统功能的程序可以被很容易地移植到其他操作系统。
system库位于名字空间boost::system,需要包含的头文件如下:
```c++
#include <boost/system/error_code.hpp>
using namespace boost::system;
```

## 错误值
system库在名字空间boost::system::errc里定义了一个很大的枚举类errc_t,它定义了通用的可移植的错误代码。
```c++
namespace errc
{
    enum errc_t                         // c++标准定义为enum class
    {
        success = 0,
        address_family_not_supported,   // EAFNOSUPPORT
        address_in_use,                 // EADDRINUSE
        address_not_available,          // EADDRNOTAVAIL
        already_connected,              // EISCONN
        ...
    }
}
```
system库还在头文件<boost/system/linux_error.hpp>和<boost/system/windows_error.hpp>里分别定义了linux和windows操作系统特定的错误值枚举，分别位于名字空间boost::system::linux_error和boost::system::windows_error。

## 错误类别
system库的核心类是error_catagory,error_code和error_condition。

error_category是一个抽象基类，用于标识错误代码的类别，摘要如下:
```c++
class error_category : public noncopyable
{
public:
    virtual const char* name() const BOOST_SYSTEM_NOEXCEPT = 0;
    virtual string message( error_code::value_type ev ) const = 0；
    virtual error_condition default_error_condition( int ev ) const;

    virtual bool equivalent( int code, const error_condition & condition ) const;
    virtual bool equivalent( const error_code & code, int condition ) const;
}
```
error_category的核心函数共有以下4个:
- 成员函数name()可以获得类别的名称。
- message()可以获得错误代码ev对应的描述信息。
- default_error_condition()是一个工厂方法，它由错误代码ev产生一个error_condition对象。
- equivalent()用于比较2个错误代码是否相等。

不能直接使用error_category,必须使用继承的方式生成他的子类。

如果我们需要建立一个新的错误类别，则可以从error_category派生一个新类。新类只有name()和message()是必须实现的，
因为他们是纯虚函数，其余的函数可以使用error_category的默认实现。例:
```c++
class my_category : public error_category
{
public:
    virtual const char* name() const BOOST_SYSTEM_NOEXCEPT
    { return "myapp_category"; }

    virtual string message(int ev) const
    {
        string msg;
        switch(ev)
        {
        case 0:
            msg = "ok"; break;
        default:
            msg = "some error"; break;
        }
        return msg;
    }
};
```

## 错误代码
error_code和error_condition都用于表示错误代码,error_code更接近操作系统和底层API，而error_condition则更偏重于可移植。两者的声明类似，但error_code多了一个default_error_condition()的方法,可以把error_code转换成error_condition。

error_code的类摘要如下:
```c++
class error_code
{
public:
    error_code();
    error_code( int val, const error_category& cat );
    void assign( int val, cosnt error_category& cat );
    void clear();

    int value() const;
    string message() const;
    const error_category& category() const;
    // 转换为error_condition
    error_condition default_error_condition() const;

    explicit operator bool() const;
    bool operator==(const error_code& lhs, const error_code& rhs);
    bool operator!=(const error_code& lhs, const error_code& rhs);
    bool operator<(const error_code& lhs, const error_code& rhs);
};
```

不同的错误类别决定了error_code的含义，相同的错误代码如果属于不同的类别，那么将具有不同的含义。
```c++
my_category my_cat;
error_code ec(10, my_cat);              // 错误码10,自定义类别
count << ec.value() << ec.message() << endl;
ec = error_code(10, system_category()); // 系统错误类别
cout << ec.value() << ec.message() << endl;

// 注意：在使用自定义错误类别的时候，我们不能向error_code传递临时对象构造
error_code ec(10, my_categorty())       // 错误
```
例:
```c++
count << system_category().name() << endl;  // 输出类别名称

error_code ec;                              // 默认构造一个错误代码对象
assert(ec.value() == errc::success);        // 默认无错误
assert(!ec);                                // 默认无错误，可bool转换
assert(ec.category() == system_category());

ec.assign(3L, system_category());           // 错误值为3
auto econd = ec.default_error_condition();  // 产生一个可移植的错误代码
assert(econd == ec);                        // 比较操作

// 也可以直接用system_category产生可移植的错误代码
assert(econd == system_category().default_error_condition(3L));

count << ec.message() << endl;              // 输出错误描述信息
count << econd.message() << endl;
count << econd.value() << endl;             // 输出可移植的错误代码
```
在编写跨平台的程序时应尽量使用error_condition,并且使用不依赖于具体错误值的errc_t枚举。

## 错误异常
system库还提供一个异常类system_error，它是std::runtime_error的子类，是对error_code的一个适配，可以把error_code应用到c++的异常处理机制之中。

system_error位于名字空间boost::system,使用它时需要另外包含头文件
```c++
#include <boost/system/system_error.hpp>
using namespace boost::system;
```
其类摘要如下:
```c++
class system_error : public std::runtime_error
{
public:
    system_error{ error_code ec };
    system_error{ error_code ec, const char * what_arg };

    const error_code & code() const;
    const char * what() const;
};
```
使用示例:
```c++
try
{
    throw system_error( // 抛出system_error异常
        error_code(5, system_category()));
}
catch (system_error& e)
{
    cout << e.what();
}
```