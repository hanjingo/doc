# 第六章 函数子，函数子类，函数及其他

[TOC]



## 第三十八条：遵循按值传递的原则来设计函数子类

1. 函数指针和函数对象在函数之间按值传递（用class/struct包裹的函数例外）；

   例，将函数用class包裹时，强制按引用传递：

   ```c++
   class DoSomething : public unary_function<int, void> {
   public:
       void operator()(int x) {...}
   };
   
   typedef deque<int>::iterator DequeIntIter;
   deque<int> di;
   DoSomething d; // 创建一个函数对象
   // 用类型参数DequeIntIter和DoSomething&来调用for_each，这将强制d按引用传递并返回
   for_each<DequeIntIter, DoSomething&>(di.begin(), di.end(), d); 
   ```



## 第三十九条：确保判别式是“纯函数”

1. 术语

   - `判别式（predicate）` 是一个返回值为bool类型（或者可以隐式地转换为bool类型）的函数。
   - `纯函数（pure function）` 返回值仅仅依赖于其参数的函数。
   - `判别式类（predicate class）` 一个函数子类，它的operator()函数是一个判别式，也就是说，它的operator()返回true或者false。

2. 判别式函数必须是纯函数；

   例，错误示例：

   ```c++
   class BadPredicate : public unary_function<Widget, bool> {
   public:
       BadPredicate() : timesCalled(0) {}
       bool operator()(const Widget&)
       {
           return ++timesCalled == 3; // 判断是否是第3个元素
       }
   private:
       size_t timesCalled;
   };
   
   vector<Widget> vw;
   vw.erase(remove_if(vw.begin(), vw.end(), BadPredicate()), vw.end()); // 本意是，删除第3个元素；实际，删除了第3和第6个元素
   
   // STL中remove_if的源码
   template<typename FwdIterator, typename Prediate>
   FwdIterator remove_if(FwdIterator begin, FwdIterator end, Predicate p)
   {
       begin = find_if(begin, end, p); // p第一次传值
       if (begin == end) return begin;
       else {
           FwdIterator next = begin;
           return remove_copy_if(++next, end, begin, p); // p第二次传值
       }
   }
   ```



## 第四十条：若一个类是函数子，则应使它可配接

```c++
lsit<Widget*> widgetPtrs;
bool isInteresting(const Widget* pw);

list<Widget*>::iterator i = find_if(widgetPtrs.begin(), widgetPtrs.end(), isInteresting);
if (i != widgetPtrs.end()) { // 第一个指向“有趣”的Widget的指针
    ...
}

list<Widget*>::iterator i = find_if(WidgetPtrs.begin(), widgetPtrs.end(), not1(ptr_fun(isInteresting)));
if (i != widgetPtrs.end()) { // 第一个指向“无趣”的Widget的指针
    ...
}
```

```c++
template<typename T>
class MeetsThreshold : public std::unary_function<Widget, bool> {
private:
    const T threshold;
public:
    MeetsThreshold(const T& threshold);
    bool operator()(const Widget&) const;
    ...
};

struct WidgetNameCompare : public std::binary_function<Widget, Widget, bool> {
    bool operator()(const Widget& lhs, const Widget& rhs) const;
}
```



## 第四十一条：理解ptr_fun, mem_fun和mem_fun_ref的来由

1. 函数或者函数对象在被调用时，总是使用非成员函数的语法形式。
2. mem_fun和mem_fun_ref被用来调整成员函数，使之能够通过非成员函数被调用。

```c++
f(x);   // ptr_fun
x.f();  // mem_fun
p->f(); // mem_fun_ref
```



## 第四十二条：确保less<T>与operator<具有相同的语义

1. 尽量避免修改less的行为，因为这样做很可能会误导其他程序员；如果使用了less，无论是显式还是隐式地，你都需要确保它与operator<具有相同的意义；

2. 对std名字空间的组件进行修改是被禁止的（通常这样会导致未定义的行为），但是在特定情况下，对std名字空间的修补是允许的；

   例，针对自定义类的std::less特化：

   ```c++
   class Widget {
   public:
       size_t weight() const;
       size_t maxSpeed() const;
       
       bool operator<(const Widget& lhs, const Widget& rhs)
       {
           return lhs.weight() < rhs.weight();
       }
   };
   
   template<> 
   struct std::less<Widget> : public std::binary_function<Widget, Widget, bool> {
       bool operator()(const Widget& lhs, const Widget& rhs) const
       {
           return lhs.maxSpeed() < rhs.maxSpeed();
       }
   };
   ```

   例，针对智能指针类的std::less特化：

   ```c++
   namespace std {
       // 针对boost::shared_ptr<T>的std::less特化（boost是名字空间）
       template<typename T>
       struct less<boost::shared_ptr<T> > : public binary_function<boost::shared_ptr<T>, 
           boost::shared_ptr<T>, bool> 
       {
           bool operator()(const boost::shared_ptr<T>& a, const boost::shared_ptr<T>& b) const
           {
               return less<T*>()(a.get(), b.get()); // shared_ptr::get返回shared_ptr对象的内置指针
           }
       }
   }
   ```

   

