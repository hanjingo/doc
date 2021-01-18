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