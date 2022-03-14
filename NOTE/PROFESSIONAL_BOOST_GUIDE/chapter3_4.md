# intrusive_ptr
intrusive_ptr也是一种引用计数型智能指针，摘要如下:
```c++
template<class T>
class intrusive_ptr {
public:
    typedef T element_type; // 被代理的对象

    intrusive_ptr();        // 构造函数
    intrusive_ptr(T *p, bool add_ref = true);

    intrusive_ptr(intrusive_ptr const & r);
    template<class Y> intrusive_ptr(intrusive_ptr<Y> const & r);

    ~intrusive_ptr();

    intrusive_ptr & operator=(intrusive_ptr const & r);
    template<class Y> intrusive_ptr & operator=(intrusive_ptr<Y> const & r);
    intrusive_ptr & operator=(T * r);

    void reset();           // 重置指针
    void reset(T * r);
    void reset(T * r, bool add_ref);

    T & operator*() const;
    T * operator->() const; // 操作符重载
    explicit operator bool() const;

    T * get() const;
    T * detach();
    void swap(intrusive_ptr & b);
};
```
intrusive_ptr自己不管理引用计数，而是调用以下两个函数来间接管理引用计数:
```c++
void intrusive_ptr_add_ref(T * p); // 增加引用计数
void intrusive_ptr_release(T * p); // 减少引用计数
```

## 用法
```c++
struct counted_date
{
    int m_count = 0;
};

void intrusive_ptr_add_ref(counted_date* p)
{
    ++p->m_count;
}
void intrusive_ptr_release(counted_date* p)
{
    if (--p->m_count == 0)
    {
        delete p;
    }
}

int main()
{
    typedef intrusive_ptr<counted_date> counted_ptr; // 类型定义
    counted_ptr p(new counted_date);                 // 创建智能指针
    assert(p);                                       // bool转型
    assert(p->m_count == 1);

    counted_ptr p2(p);                               // 指针拷贝构造
    assert(p->m_count == 2);                         // 引用计数增加

    counted_ptr weak_p(p.get(), false);              // 弱引用
    assert(weak_p->m_count == 2);                    // 引用计数不增加

    p2.reset();                                      // 复位指针
    assert(!p2);                                     // p2不持有指针
    assert(p->m_count == 1);                         // 引用计数减少
}                                                    // 对象被正确析构
```

## 引用计数器
为了进一步简化实现引用计数的工作，intrusive_ptr在头文件<boost/smart_ptr/intrusive_ref_counter.hpp>里定义了一个辅助类intrusive_ref_counter:
```c++
template<typename DerivedT,
         typename CounterPolicyT = thread_safe_counter>
class intrusive_ref_counter
{
private:
    typedef typename CounterPolicyT::type counter_type;
    mutable counter_type m_ref_counter;
public:
    intrusive_ref_counter();
    unsigned int use_count() const;
protected:
    ~intrusive_ref_counter() = default;
    friend void intrusive_ptr_add_ref(const intrusive_ref_counter* p);
    friend void intrusive_ptr_release(const intrusive_ref_counter* p);
};
```
intrusive_ref_counter内部定义了一个计数器变量m_ref_counter,使用模板参数配置策略实现了引用计数的增减，默认的策略是线程安全的thread_safe_counter。