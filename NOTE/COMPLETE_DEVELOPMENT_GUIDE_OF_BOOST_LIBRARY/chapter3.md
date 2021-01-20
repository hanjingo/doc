# 内存管理
## smart_ptr库概述
### RAII机制
为了管理内存等资源，c++程序员通常采用RAII机制(Resource Acquisition Is Initialization,
资源获取即初始化)，在类的构造函数里申请资源，然后使用资源，最终在析构函数中释放资源。

### 智能指针
boost.smart_ptr库提供了很多种智能指针，常用的有scoped_ptr,shared_ptr,weak_ptr和intrusive_ptr。
它们是轻量级的对象，其速度与原始指针相差无几，都是异常安全的(exception safe)，
而且对于所指向的类型T也仅有一个很小且很合理的要求：类型T的析构函数不能抛出异常。
这些智能指针都位于名字空间boost，需要包含的头文件如下：
```c++
#include <boost/smart_ptr.hpp>
using namespace boost;
```

## 总结
1. smart_ptr库提供了数种新型智能指针，非常接近c++标准的定义，可以有效地清除new和delete的显式使用，减少甚至杜绝代码资源泄漏。
2. scoped_ptr是smart_ptr库中最容易学习和使用的一个，他的行为类似unique_ptr,但其所有权更明确，因此这种智能指针只能在声明的作用域中使用，不能转让，任何对他的复制都会失败，此特点对代码的后期维护工作非常有用。
3. shared_ptr是非常有用的智能指针，也是这些智能指针中最“智能”的一个，它不仅可以管理内存，也可以管理其他系统资源，能够应用于许多场合。它可以自动地计算指针的引用计数，其行为最接近原始指针。shared_ptr几乎可以用在任何可以使用原始指针的地方，并且不用承担资源泄漏的风险。shared_ptr不仅可以保存指针，它还可以通过配置删除器自动释放指针关联的资源。除基础用法外，我们还讨论了shared_ptr的很多其他用法，如实现pimpl惯用法，应用于工厂模式，别名构造，持有任意对象的指针等，这些用法进一步展示shared_ptr的强大功能。
4. 为了方便使用智能指针，smart_ptr库还提供了工厂函数make_unique()和make_shared(),进一步消除代码的new操作符。
5. smart_ptr库里的weak_ptr是一个弱引用，weak_ptr能够“静态地观察”shared_ptr而不影响引用计数，intrusive_ptr则为自行实现引用计数智能指针提供了通用计数方案。
6. pool库实现了高效的内存池，可用于管理内存资源，pool库是boost程序库在内存管理方面的另一个非常有用的工具。
7. pool库提供了pool，object_pool，singleton_pool等内存池，适用于各种情形。完全可以把他们当作一个小型的垃圾回收机制，因此可以在内存池中随意地动态创建对象，完全不关心他的回收问题，也无须对原有类做任何形式的修改。尤其是object_pool,它可以统一管理各种对象的创建与销毁，能够很好地应用在各种规模的弥香对象的软件系统中。
8. pool库还提供了一个底层的实现类simple_segregated_storage,它实现了简单分隔存储的管理机制，是pool库中其他类的基础。simple_segregated_storeage不适合大多数库用户使用，但它可以作为自行实现内存池类的一个很好的起点。