# 构造析构拷贝语意学

对于`abstract base class(抽象基类)`,class中的data member应该被初始化，并且**只在constructor中或者在其它member functions中指定初值。**

## 纯虚函数的存在

纯虚函数，虚函数在声明后加上`=0`，纯虚函数的意义在于只定义一个可继承的接口，并没有**实现**（虚函数意义在于定义一个可继承的接口并且有一份缺省实现，普通的成员函数意义在于定义一个可继承的接口并且有一份强制实现）。

纯虚函数不能经由虚拟机制调用，但是可以被静态调用`(invoked statically, AbsractClassName::pureFunction())`。

唯一的例外在于：对于`pure vitual destructor`，一定要定义它，因为每一个`derived class destructor`会被编译器加以扩张，**以静态调用的方式调用其“每一个virtual base class”以及"上一层base class"的destructor**，因此只要缺乏任何一个`base class destrctor`以及"上一层base class"的destructor，因此只要缺乏任何一个base class destructor的定义，就会导致链接失败。一个较好的替代方案就是：**不要把virtual destructor声明成pure。**

## 纯虚函数的规格

一个函数几乎不会被后继的`derived class`改写，而且是inline函数，将其改写成`virtual function`是一个糟糕的选择。

一般而言，把所有的成员都声明为虚函数，然后再经过编译器优化把非必要的`virtual invocation`去除，并不是好的设计理念。

## 虚拟规格中const存在

可以先将虚函数声明了const,如果后继有`derived instance`必须修改`data member`,再将const去掉就好了。

## 重新考虑class的声明

原来的声明如下：

```c++
class Abstract_base {
public:
    virtual ~Abstract_base()=0;
    virtual void interface() const = 0;
    virtual const char* mumble() const { return _mumble; }
private:
    char* _mumble;
}
```

重新声明如下：

```c++
class Abastract_base {
public:
    virtual ~Abstract_base(); // 不再是纯虚函数
    virtual void interface() = 0; // 不再是cosnt
    const char* //不再是虚函数
        mumble() const { return _mumble; }
private:
    Abstact_base(char *pc = 0); // 新增一个带有唯一参数的constructor
    char* _mumble;
}
```

重新声明如下：

```c++
class Abstract_base {
public:
    virtual ~Abstract_base(); // 不再是纯虚函数
    virtual void interface() = 0; // 不再是const
    const char* // 不再是虚函数
        mumble() const { return _mumble; }
private:
    Abstact_base(char *pc = 0); // 新增一个带有唯一参数的constructor
    char* _mumble;
}
```

一. 无继承的情况下的对象构造

考虑下面的这个调用片段

```c++
Point global;
Point foobar() {
    Point local;
    Point *heap = new Point;
    *heap = local;
    delete heap;
    return local;
}
```

三种对象产生方式：global内存配置，local内存配置和heap内存配置。

Point定义如下：

```c++
typedef struct { float x, y, z; }Point;
```

POD类型：plain Old Data，c风格的strcut结构体定义的数据结构。

以c++来编译这段代码的话，编译器会为Point声明：trival默认构造函数，trival析构函数，trival拷贝构造函数，trival拷贝赋值运算符。

第一行代码`Point global;`，会在程序启始时调用Point的constructor，然后在系统产生的`exit()`之前调用destructor。

在c语言中，global被视为一个“临时性对象”，没有显式初始化，被存放在`data segment`中的BSS区段（Block Start By Symbol，放置没有初始化的全局变量），但是在C++中，全局对象都是以“初始过的数据”来对待，因此置于`data segment`。

第三行代码`Point local;`这个局部变量没有经过初始化，可能成为一个潜在的问题。

第四行代码`Point *heap = new Point;`声明一个堆上的对象，其中new运算符会被转化为：

```c++
Point *heap = __new(sizeof(Point));
```

此时并没有`default constructor`施行于`*heap objectl`。

第五行代码`heap = local;`由于local没有初始化，因此会产生编译警告`local is used before being initaalized`。

接着`delete heap;`会被转化为`__delete(heap);`这样会触发heap的`trival destructor`。

最后函数已传值的方式将local当作返回值传回，这样会触发`trival copy constructor`，不过由于该对象是个POD类型，所以return操作只是一个简单的`bitwise copy`。

### 抽象数据类型

将`Point`不在声明为POD，提供private数据，但是没有virtual function:

```c++
class Point {
public:
    Point(float x = 0.0, float y = 0.0, float z = 0.0) :
        _x(x), _y(y), _z(z) {}
private:
    float _x, _y, _z;
};
```

对于global实例：

```c++
Point global;
```

现在有了默认构造函数作用在其身上，由于global定义在全局范畴，其初始化操作会延迟到程序启动（startup）时才开始。（统一构造一个_main()函数，该函数内调用所有global对象的默认构造函数）

例：

```c++
void mumble {
    Point local1 = {1.0, 1.0, 1.0};
    Point local2;
    local2._x = 1.0;
    local2._y = 1.0;
    local2._z = 1.0;
}
```

`explicit initalization list`会比较有效率。

考虑`Point *heap = new Point;`与之前不同在于，Point有自己的notrival默认构造函数，所以会显式调用这个默认构造函数如下：

```c++
Point *heap = __new(sizeof(Point));
if (heap != 0)
    heap->Point:Point();
```

其它的操作和之前一致。

为继承做准备：

限制对z的存取操作

```c++
class Point {
public:
    Point(float x = 0.0, float y = 0.0) : _x(x), _y(y) {}
    virtual float z();
private:
    float _x, _y;
};
```

增加了虚函数之后，所定义的constructor被附加了一些代码，用来初始化vptr:

```c++
Point::Point(Point *this, float x, float y) : _x(x), _y(y) {
    this->__vptr_Point = __vbtl_Point; // 设定虚表
    this->_x = x; // 扩展初值列表
    this->_y = y;
    return this; // 返回this
}
```

合成一个`copy constructor`和一个`copy assignment operator`，其操作是nontrival，但是implicit destructor仍然是trival。如果以一个子类对象初始化父类对象，且是以位运算为基础，那么vptr的设定有可能是非法的。

```c++
inline Point*
Point::Point(Point *this, const Point& rhs) {
    this->__vptr_Point = __vbtl_Point;
    // 将rhs坐标的连续位拷贝到this对象
    return this;
}
```


