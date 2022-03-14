# weak_ptr
## 摘要
```c++
template<class T>
class weak_ptr
{
public:
    weak_ptr();
    template<class Y> weak_ptr(shared_ptr<Y> const & r);
    weak_ptr(weak_ptr const & r);
    ~weak_ptr();
    weak_ptr & operator=(weak_ptr const & r); 

    long use_count() const;     // 引用计数
    bool expired() const;       // 是否为失效指针
    bool empty() const;         // 是否为空指针，非标准
    shared_ptr<T> lock() const; // 获取shared_ptr

    void reset();               // 重置指针
    void swap(eak_ptr<T> & b);  // 交换指针
}
```

## 用法
```c++
shared_ptr<int> sp(new int(10));
assert(sp.use_count() == 1);

weak_ptr<int> wp(sp);                // 从shared_ptr创建weak_ptr
assert(wp.use_count() == 1);         // weak_ptr不影响引用计数
assert(!wp.empty());                 // weak_ptr此时非空指针

if (!wp.expired())                   // 判断weak_ptr观察的对象是否失效
{
    shared_ptr<int> sp2 = wp.lock(); // 获得一个shared_ptr
    *sp2 = 100;
    assert(wp.use_count() == 2);
}                                    // 退出作用域，sp2自动析构，引用计数器

assert(wp.use_count() == 1);
sp.reset();                          // shared_ptr失效
assert(wp.expired());
assert(!wp.lock());                  // weak_ptr将获得一个空指针
```

### 对象自我管理
weak_ptr的一个重要用途是获得this指针的shared_ptr,使对象自己能够生产shared_ptr管理自己：
对象使用weak_ptr观测this指针，这并不影响引用计数，在需要的时候调用lock()函数，返回一个符合要求的shared_ptr供外界使用。
这个解决方案是一种惯用法，在头文件<boost/enable_shared_from_this.hpp>里面定义一个助手类enable_shared_from_this<T>,
它的声明摘要如下:
```c++
template<class T>
class enable_shared_from_this
{
public:
    shared_ptr<T> shared_from_this(); // 工厂函数，产生this指针的shared_ptr
}
```

使用weak_ptr的时候只需要让想被shared_ptr管理的类继承它既可，成员函数shared_from_this()会返回this指针的shared_ptr。例:
```c++
class self_shared:
    public enable_shared_from_this<self_shared>
{
public:
    self_shared(int n):x(n){}
    int x;
    void print()
    { cout << "self_shared:" << x << endl; }
};

int main()
{
    auto sp = make_shared<self_shared>(313);
    sp->print();

    auto p = sp->shared_from_this();
    p->x = 1000;
    p->print();
}
```
注意:不要对一个普通对象(非shared_ptr管理的对象)使用shared_from_this()获取shared_ptr!!!

### 打破循环引用
```c++
class node
{
public:
    ...
    typedef weak_ptr<node> ptr_type; // 指针类型使用weak_ptr
    ptr_type next;                   // 后继指针
};
int main()
{
    auto p1 = make_shared<node>();   // 2个节点对象
    auto p2 = make_shared<node>();

    p1->next = p2;                   // 形成循环链表
    p2->next = p1;                   // 使用了weak_ptr，所以正常

    assert(p1.use_count() == 1);     // 每个shared_ptr的引用计数是1
    assert(p2.use_count() == 1);     // 没有了循环引用

    if (!p1->next.expired())         // 检查弱引用是否有效
    {
        auto p3 = p1->next.lock();   // 调用lock()获得"强"引用
    }                                // 退出作用域，shared_ptr正确析构
}
```