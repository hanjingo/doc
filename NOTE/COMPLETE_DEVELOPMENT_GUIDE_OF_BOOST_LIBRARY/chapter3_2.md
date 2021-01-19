# shared_ptr
shared_ptr与scoped_ptr一样包装了new操作符在堆上分配的动态对象，但它实现的是引用计数型的智能指针，
可以被自由地拷贝和赋值，当没有代码使用它时（引用计数为0），才删除被包装过的动态分配的对象。

## 类摘要
```c++
template<class T>
class shared_ptr
{
public:
    typedef T element_type;                       // 内部类型定义
    shared_ptr();                                 // 构造函数
    template<class Y> explicit shared_ptr(Y * p);
    template<class Y, class D> shared_ptr(Y * p, D d);
    ~shared_ptr();                                // 析构函数  
    shared_ptr(shared_ptr const & r);             // 拷贝构造
    shared_ptr & operator=(shared_ptr const & r); // 赋值操作
    template<class Y> shared_ptr & operator=(shared_ptr<Y> const & r);

    void                            reset();      // 重置智能指针
    template<class Y> void          reset(Y * p);
    template<class Y, class D> void reset(Y * p, D d);

    T & operator*() const;                        // 操作符重载
    T * operator->() const;                       // 操作符重载
    T * get() const;                              // 获得原始指针

    bool unique() const;                          // 是否唯一
    long use_count() const;                       // 引用计数

    explicit operator bool() const;               // 显式bool值转型
    void swap(shared_ptr & b);                    // 交换指针
}
```

## 操作函数
get()函数可以得到原始指针，并且没有提供指针算术操作，也不能管理new[]产生的动态数组指针。例:
```c++
shared_ptr<int> spi(new int);                // 一个int的shared_ptr
assert(spi);                                 // 在bool语境中转换为bool值
*spi = 253;                                  // 使用解引用操作符×

shared_ptr<string> sps(new string("smart")); // 一个string的shared_ptr
assert(sps->size() == 5);                    // 使用箭头操作符->

shared_ptr<int> dont_do_this(new int[10]);   // 危险！不能正确释放内存
```
shared_ptr有多种形式的构造函数，可以应用于各种可能的情形，示例如下:
- 无参的shared_ptr(): 创建一个持有空指针的shared_ptr。
- shared_ptr(Y * p): 获得指向类型T的指针p的管理权，同时将引用计数量为1，这个构造函数要求Y类型必须能够转换为T类型。
- shared_ptr(shared_ptr const & r): 从另外一个shared_ptr获得指针的管理权，同时引用计数加1，结果是两个shared_ptr共享一个指针的管理权。
- operator=: 赋值操作符，可以从另外一个shared_ptr获得指针的管理权，其行为同拷贝构造函数。
- shared_ptr(Y * p, D d): 其行为类似shared_ptr(Y * p)，但它使用参数d指定了析构时的定制删除器，而不是简单的delete。
- aliasing: 别名构造函数是不增加引用计数的特殊用法

## 用法
例1:
```c++
shared_ptr<int> sp(new int(10)); // 一个指向整数的shared_ptr
assert(sp.unique());             // 现在shared_ptr是指针的唯一持有者

shared_ptr<int> sp2 = sp;        // 第二个shared_ptr，拷贝构造函数

assert(sp == sp2 &&              // 2个shared_ptr相等
        sp.use_count() == 2);    // 指向同一个对象，引用计数为2

*sp2 = 100;                      // 使用解引用操作符修改被指对象
assert(*sp == 100);              // 另一个share_ptr也被修改

sp.reset();                      // 停止shared_ptr的使用
assert(!sp);                     // sp不再持有任何指针(空指针)
```

例2:
```c++
class shared                            // 一个拥有shared_ptr的类
{
private:
    shared_ptr<int> p;                  // shared_ptr成员变量
public:
    shared(shared_ptr<int> p_):p(p_){}  // 构造函数初始化shared_ptr
    void print()                        // 输出shared_ptr的引用计数和指向的值
    {
        cout << "count:" << p.use_count() 
            << " v=">> << *p << endl;
    }
};
void print_func(shared_ptr<int> p)      // 使用shared_ptr作为函数参数
{                                       // 同样输出引用计数和指向的之
    cout << "count:" << p.use_count()
        << " v=" << *p << endl;
}
int main()
{
    shared_ptr<int> p(new int(100));    // shared_ptr持有整数指针
    shared s1(p), s2(p);                // 构造2个自定义类

    s1.print();
    s2.print();

    *p = 20;
    print_func(p);                      // 修改shared_ptr所指向的值

    s1.print();
}
```

## 工厂函数
smart_ptr库提供了一个工厂函数make_shared()来消除显式的new调用；make_shared()代码摘要：
```c++
template<class T, class... Args>                 // c++可变参数模板
typename boost::detail::sp_if_not_array<T>::type // 模板元计算类型
make_shared( Args && ... args );                 // c++的右值引用
```
例:
```c++
auto sp = make_shared<string>("make_shared"); // 创建string的共享指针
auto spv = make_shared<vector<int> >(10, 2);  // 创建vector的共享指针
assert(spv->size() == 10);
```

## 应用于标准容器
1. 将容器作为shared_ptr的管理对象，如shared_ptr<list<T>>,使容器可以被安全地共享，其用法与普通的shared_ptr没有区别
2. 将shared_ptr作为容器的元素，如vector<shared_ptr<T>>,因为shared_ptr支持拷贝语义和比较操作，符合标准容器对元素的要求，所以可以在容器中安全地容纳元素的指针，而不是拷贝

注意:标准容器不能容纳scoped_ptr,因为scoped_ptr不能拷贝和赋值。

## 应用于桥接模式
桥接模式是一种结构性设计模式，它把类的具体实现细节对用户隐藏起来，以达到类之间的最小耦合关系。例:
```c++
class sample
{
private:
    class impl;                // 不完整的内部类声明
    shared_ptr<impl> p;        // shared_ptr成员变量
public:
    sample();                  // 构造函数
    void print();              // 提供给外界的接口
};

class sample::impl             // 内部类的实现
{
public:
    void print()
    { cout << "impl print" << endl; }
};
sample::sample():p(new impl){} // 构造函数初始化shared_ptr

void sample::print()           // 调用pimpl实现print()
{ p->print(); }
sample s;
s.print();
```

## 应用于工厂模式
```c++
class abstract                     // 接口类定义
{
public:
    virtual void f() = 0;
    virtual void g() = 0;
protected:
    virtual ~abstract() = default; // 注意这里
}

// 注意abstract的析构函数，如果他被定义为保护的，则意味着除了它自己和他的子类，任何其他对象都无权调用delete来删除它。

class impl : public abstract
{
public:
    impl() = default;
    virtual ~impl() = default;
public:
    virtual void f()
    { cout << "class impl f" << endl; }
    virtual void g()
    { cout << "class impl g" << endl; }
};

shared_ptr<abstract> create()
{ return make_shared<impl>(); }

int main()
{
    auto p = create(); // 工厂函数创建对象
    p->f();            // 可以像普通指针一样使用
    p->g();            // 不必担心资源泄漏，shared_ptr会自动管理指针
}
```