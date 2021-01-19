# scoped_ptr
scpoed_ptr是一个与auto_ptr/unique_ptr很类似的智能指针，他包装了new操作符在堆上分配的动态对象，
能够保证动态创建的对象在任何时候都可以被正确地删除。但scoped_ptr的所有权更加严格，不能转让，
一旦scoped_ptr获取了对象的管理权，我们就无法再从它那里收回来。

## scoped_ptr类摘要
```c++
template<class T>
class scoped_ptr {
private:
    T * px;                                     // 原始指针
    scoped_ptr(scoped_ptr const &);             // 拷贝构造函数私有化
    scoped_ptr & operator=(scoped_ptr const &); // 赋值操作私有化

    void operator==( scoped_ptr const& ) const; // 相等操作私有化
    void operator!=( scoped_ptr const& ) const; // 不等操作私有化

public:
    explicit scoped_ptr(T * p = 0); // 显式构造函数
    ~scoped_ptr();                  // 析构函数
    void reset(T * p = 0);          // 重置智能指针

    T & operator*() const;  // 操作符重载
    T * operator->() const; // 操作符重载
    T * get() const;        // 获得原始指针

    explicit operator bool() const; // 显式bool值转型
    void swap(scoped_ptr & b);      // 交换指针
}；

template<class T> inline // 与空指针比较
bool operator==(scoped_ptr<T> const & p, boost::detail::sp_nullptr_t);
```

## 操作函数
成员函数get()返回scoped_ptr内部保存的原始指针，可以用在某些要求必须是原始指针的场景（如底层的c接口）。
但在使用函数get()时必须小心，这将使原始指针脱离scoped_ptr的控制，不能对这个指针进行delete操作，
否则scoped_ptr析构时会对已经删除的指针再次进行删除操作，发生未定义行为。

## 用法
在原本使用指针变量接受new表达式结果的地方改成用scoped_ptr对象接受new表达式结果，
然后去掉那些多余的try/catch和delete操作即可。例:
```c++
scoped_ptr<string> sp(new string("text")); // 构造一个scoped_ptr对象
assert(sp);                                // 使用显式bool转型
assert(sp != nullptr);                     // 空指针比较操作
```
不需要进行delete操作，scoped_ptr会自动帮我们释放资源。如果我们对scoped_ptr执行delete操作，会得到一个编译错误。
因为scoped_ptr是一个行为类似指针的对象实例，而不是指针，所以不允许对一个对象应用delete操作。

scoped_ptr把拷贝构造函数和赋值函数都声明为私有的，不允许拷贝或赋值，拒绝转让指针的所有权，
只能在scoped_ptr被声明的作用域内使用（除了scoped_ptr自己，其他任何人都无权访问被管理的的指针），
从而保证了指针的绝对安全。

只能在定义的作用域内使用，不可转让，这在代码后续的维护生命周期中很重要。

如果一个类持有scoped_ptr成员变量，那么他也会是不可拷贝和赋值的。例:
```c++
class ptr_owned final
{
    scoped_ptr<int> m_ptr; // scoped_ptr成员
};

ptr_owned p;               // 类的一个实例
ptr_owned p2(p);           // 编译错误，不能拷贝构造
```

另一个示例:
```c++
struct posix_file
{
    posix_file(const char * file_name) // 构造函数打开文件
    { cout << "open file:" << file_name << endl; }
    ~posix_file()
    { cout << "close file" << endl; }
};

int main()
{
    // 文件类的scoped_ptr,将在离开作用域时自动析构，从而关闭文件释放资源
    scoped_ptr<posix_file> fp(new posix_file("/tmp/a.txt"));

    scoped_ptr<int> p(new int); // 一个int指针的scoped_ptr

    if (p)
    {
        *p = 100;   // 可以像普通指针一样使用解引用操作符×
        cout << *p << endl;
    }

    p.reset();      // 置空scoped_ptr,仅仅是演示

    assert(p == 0); // 与0比较，p不持有任何指针
    if (!p)
    { cout << "scoped_ptr == nullptr" << endl; }
} // 在这里发生scoped_ptr的析构,p和fp管理的指针自动被删除
```

## unique_ptr
unique_ptr是在c++标准中定义的新的智能指针，用来取代曾经的auto_ptr。unique_ptr不仅能够代理new创建的单个对象，
也能够代理new[]创建的数组对象。c++标准中对unique_ptr的定义如下:
```c++
template <class T, class D = default_delete<T>> // 使用删除器
class unique_ptr {
public:
    typedef some_define pointer; // 内部类型定义
    typedef T element_type;

    constexpr unique_ptr() noexcept; // 构造函数
    explicit unique_ptr(pointer p) noexcept;

    ~unique_ptr();                                  // 析构函数
    unique_ptr& operator=(unique_ptr&& u) noexcept; // 转移语义赋值

    element_type & operator*() const;               // 操作符重载
    pointer operator->() const noexcept;
    pointer get() const noexcept;                   // 获得原始指针
    explicit operator bool() const noexcept;        // bool值转型

    pointer release() noexcept;                     // 释放指针的管理权
    void reset(pointer p) noexcept;                 // 重置智能指针
    void swap(unique_ptr& u) noexcept;              // 交换指针

    unique_ptr(const unique_ptr&) = delete;         // 使用delete禁用拷贝
    unique_ptr& operator=(const unique_ptr&) = delete;
};
bool operator==(const unique_ptr& x, const unique_ptr& y);
```
unique_ptr的基本能以与scoped_ptr相同，且比scoped_ptr有更多的功能：unique_ptr可以像原始指针一样进行比较，可以像shared_ptr一样定制删除器，也可以安全的放入标准容器。因此，如果读者使用的编译器支持c++11标准，
那么可以毫不犹豫地使用unique_ptr来替代scoped_ptr。
