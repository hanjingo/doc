# 第六章 执行期语意学

c++在执行期的一些变化



## 对象的构造和析构

一般而言，我们将object尽可能放置在使用它的那个程序区段附近，这样可以节省非必要的对象的构造和析构成本。

### 全局对象

已经初始化全局对象均存储在`data segment`(数据段)，未初始化的全局变量存储在BSS(block started by symbol)，但是c++中差异不大，如果全局对象没有显式初始化，那么该对象所配置到的内存内容为0.

munch方法：全局变量静态初始化方法。

1. 为每一个需要静态初始化的文件产生一个`__sti()`函数(`sti: static initialization`)，内含必要的constructor调用操作或者inline expansions。
2. 为每一个需要静态的内存释放操作产生`__std()`函数（`std: static deallocation`），内含必要的constructor调用操作或者inline expansions。
3. 提供一组running library munch函数：调用所有的`__sti()`一个`_main()`函数以及一个调用`__std()`函数的`exit()`函数。

例：

```c++
Matrix identity1, identity2;
main() {
  Matrix m1 = identity, m2 = identity2;
  ...
  return 0;
}
```

对应munch策略如下：

```c++
main() {
  _main();
  // _main()调用__sti_identity1()以及__sti_identity2();对所有的global做static_initialization操作
  exit();
  // exit()调用__std_identity1()以及__std_identity2();对所有的global做static deallocation操作
  exit();
  // exit()调用__std_identity1()以及__std_idenity2();对所有的global做static deallocation操作
  return 0;
}
```

#### 局部静态对象

静态对象存储在全局区/静态区，例如：

```c++
const Matrix&
identity() {
  static Matrix mat_identity;
  return mat_identity;
}
```

局部静态对象mat_identity满足什么语意？
1. mat_identity的构造函数只执行一次，即使identity函数调用多次。
2. mat_identity的析构函数也只执行一次，即使identity函数调用多次。

编译器的策略是无条件在程序起始处构造对象，这会导致所有的静态对象在程序起始时都初始化，即使调用他们的函数从来没有被调用过。新的规则要求编译单位中的局部静态对象必须被摧毁，以构造相反的顺序摧毁。

#### 对象数组

例：

```c++
Point knots[10];
```

假如Point定义了一个默认构造函数，在从cfront的策略中，产生一个`vec_new`函数（如果含有虚函数，产生`vec_vnew()`函数），用来构造数组：

```c++
void vec_new(
    void* array,                    // 数组的起始地址
    size_t elem_size,               // 数组中每一个元素的大小
    int elem_count,                 // 数组中的元素个数
    void (*constructor)(void*),     // 形参个数为0的默认构造函数指针
    void (*destructor)(void*, char) // 析构函数指针
)
```

则上述knots数组的调用操作为：

```c++
Point knots[10];
vec_new(&knots, sizeof(Point), 10, Point:Point, 0);
```

同样地，cfront的策略中，产生一个`vec_deletel`函数（如果含有虚函数，产生`vec_vdelete()`函数），用来析构数组：

```c++
void vec_new(
    void* array,                    // 数组的起始地址
    size_t elem_size,               // 数组中每一个元素大小
    int elem_count,                 // 数组中元素的个数
    void (*destructor)(void*, char) // 析构函数指针
)
```

### Default Constructor和数组

如果一个类的构造函数有一个或一个以上的默认参数值，例：

```c++
class complex {
    complex(double = 0.0, double = 0.0);
}
```

那么当我们写下`complex array[10];`时，编译器最终需要调用：

```c++
vec_nex(&array, sizeof(complex), 10, &complex::complex, 0);
```

这里的&complex::complex需要是无参的构造函数，那么应该怎么做？做法是：在`&complex::complex`中调用我们自己提供的constructor，并将default参数值显式指定过去，例：

```c++
complex::complex() {
    complex(0.0, 0.0); // 调用我们自己的构造函数
}
```



## new和delete运算符

```c++
int *pi = new int(5);
```

上述的new操作符可以看作两个步骤：

1. 通过`__next`配置所需要的内存：

```c++
int *pi = __nex(sizeof(int));
```

将配置来的对象设定初始值

```c++
*pi = 5;
```

或者更确切的说：

```c++
int *pi;
if (pi = __new(sizeof(int)))
    *pi = 5;
```

delete操作符：

```c++
delete pi; // 下面是编译器的实现
if(pi != 0) __delete(pi);
```

如果不是内置类型(int)，而是一个class呢？例：

```c++
Point3d *origin = new Point3d;
```

转换为：

```c++
Point3d *origin;
if(origin = __new(sizeof(Point3d)))
  origin->Point3d::Point3d(origin);
```

再加上异常处理：

```c++
Point3d *origin;
if(origin = __new(sizeof(Point3d)))
    try {
        origin->Point3d::Point3d(origin);
    }
    catch(...) {
        __delete(origin)
        throw;
    }
}
```

在这里，如果constructor抛出异常，配置的内存就会释放掉，然后异常被抛上去。

Destructor的应用也是类似的：

```c++
delete origin; // 下面是编译器的实现
if(origin != 0) {
    Point3d::~Point3d(origin);
    __delete(origin);
}
```

总结：

1. **操作符new的过程就是：先配置内存，再调用构造函数（内置类型直接赋值）。（如果配置内存失败，内存还是需要释放的）**
2. **操作符delete的过程就是：先调用析构函数（内置类型没有这一步），再释放内存（）。**

下面给出不考虑异常的new的实现（实际是以malloc()函数完成）：

```c++
extern void*
operator new(size_t size) {
    if(size == 0) size = 1;
    void *last_alloc;
    while(!(last_alloc = malloc(size))) {
        if(_new_handler) (*_new_handler) ();
        else return 0;
    }
    return last_alloc;
}
```

令size = 1的原因是每一次对new的调用都必须传回一个独一无二的指针，传回一个指针指向默认为1byte的内存区块。

delete函数也是以free()函数为基础完成的：

```c++
extern void
operator delete(void* ptr) {
    if(ptr)
        free((char*) ptr);
}
```

#### 针对数组的new语意

当我们这么写`int* p_array = new int[5];`时，由于int是内置类型，并没有默认构造函数，所以`vec_new()`不会被调用，倒是new运算符函数会被调用：

```c++
int* p_array = (int *) __new(5 * sizeof(int));
```

同样的，当我们写下：

```c++
simple_aggr* p_aggr = new simple_aggr[5];
```

`vec_new()`也不会被调用，因为simple_aggr没有定义构造函数或者析构函数。

针对数组的delete,通常的写法是`delete []p_array;`或者`delete [5] p_array;`第一种是最常见的。但是如果使用这样的写法：`delete p_array;`那么只有第一个元素被析构，其他的元素依然存在，虽然相关的内存已经被归还了。

### Placement Operator new的语意

Placement Operator new是一个预先定义好的重载的new运算符，原型如下：

```c++
void* operator new(size_t, void* p) { return p; }
```

Placement Operator new的用法：

```c++
Point2w* ptw2 = new(arena) Point2w;
```

其中arena是指向内存中的一个区块，用来放置新产生的Point2w object。那么上述和这句有什么区别呢？

```c++
Point2w* ptw1 = (Point2w*) arena;
```

这句只是做了强制隐式类型转换，而Placement Operator new还**将Point2w的constructor自动施行于arena的地址上**，Placement Operator new的语句等价于：

```c++
Point2w* ptw2 = (Point2w*) arena;
ptw2->~Point2w();
if(ptw2 != 0) ptw2->Point2w::Point2w();
```

编译系统保证了constructor会施行。

一般而言，Placement Operator new不支持多态，如果derived class比base class大的多，那么derived class的构造函数将会导致严重的破坏：

```c++
Point2w *p2w = new(arena)Point3w; // Point3w继承自Point2w
```



## 临时性对象

加入有一个函数，形式如下：

```c++
T operator+(const T&, const T&);
T a, b;
T c = a + b;
```

最后一行a+b的调用，编译器会产生一个临时性对象来放置a+b的结果，然后再使用T的`copy constructor`把临时性对象当作c的初值，或者以拷贝构造的方式将a+b的值放到c中。如果考虑NRV优化，则避免了copy constructor以及临时对象的destructor。

但是，如果是assignment statement，如下：

```c++
T c;
c = a + b;
```

则不能忽略临时对象，实际结果如下：

```c++
T c;
T temp;
temp.operator+(a, b);
c.operator=(temp);
temp.T::~T();
```

因此`T c = a + b;`总比`T c; c = a + b;`更有效率。

第三种运算形式：`a + b;`没有出现目标对象，也有必要产生一个临时对象存储运算后的结果。

#### 临时对象的生命周期

临时对象被摧毁，应该是**对完整表达式（full-expression）求值过程中的最后一个步骤。**

什么是完整表达式？例：

```c++
((objA > 1024) && (objB > 1024))
    ? objA + objB : foo(objA, objB);
```

一共五个式子:
- `objA > 1024`
- `objB > 1024`
- `(objA > 1024) && (objB > 1024)`
- `objA + objB`
- `foo(objA, objB)`

包含在`?:`完整表达式中，每一个公式的临时对象都应该在这个完整表达式被求值之后才能销毁。

临时对象的生命规则有两个意外：

1. 凡事有表达式执行结果的临时性对象，应该保存到object的初始化操作完成为止。

```c++
string proNameVersion = !verbose ? 0 : proName + progVersion;
//proName和progVersion均是string类型
```

`proName + progVersion`产生的临时对象本应该在`?:`表达式求值之后立即销毁，但是`proNameVersion` objecrt初始化需要用到该临时对象，因此应该保存到object的初始化操作完成为止。

2. 如果**一个临时性对象绑定于一个reference**，对象将残留，直到被初始化之reference的生命结束，或者知道临时对象的生命范畴结束，视哪种情况先到达。

```c++
const String& space = " ";
```

会产生这样的代码：

```c++
string temp;
temp.String::String(" ");
const String& space = temp;
```

如果临时对象现在就被销毁，那么引用也就没有什么用处了。

#### 临时对象的迷思

例如，复数类complex定义了如下操作符重载：

```c++
friend complex operator+(complex, complex);
```

测试程序是这样的：

```c++
void func(complex* a, const complex* b, const complex* c, int N) {
    for(int i = 0; i < N; ++i) {
        a[i] = b[i] + c[i] - b[i] * c[i];
    }
}
```

上述测试程序会产生5个临时对象：

1. 一个临时对象，放置`b[i] + c[i]`;
2. 一个临时对象，放置`b[i] * c[i]`;
3. 一个临时对象，放置上述两个临时对象的相减的结果；
4. 两个临时对象，为了放置上述第一个和第二个临时对象，为的是完成第三个临时对象。

