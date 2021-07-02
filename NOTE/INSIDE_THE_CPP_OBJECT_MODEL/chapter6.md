# 第六章 执行期语意学

c++在执行期的一些变化

## 对象的构造和析构

一般而言，我们将object尽可能放置在使用它的那个程序区段附近，这样可以节省非必要的对象的构造和析构成本。

### 全局对象

已经初始化全局对象均存储在data segment(数据段)，未初始化的全局变量存储在BSS(block started by symbol)，但是c++中差异不大，如果全局对象没有显式初始化，那么该对象所配置到的内存内容为0.

munch方法：全局变量静态初始化方法。

1. 为每一个需要静态初始化的文件产生一个`__sti()`函数(sti: static initialization)，内含必要的constructor调用操作或者inline expansions。
2. 为每一个需要静态的内存释放操作产生`__std()`函数（std: static deallocation），内含必要的constructor调用操作或者inline expansions。
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

局部静态对象

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

对象数组

例：

```c++
Point knots[10];
```

假如Point定义了一个默认构造函数，在从cfront的策略中，产生一个`vec_new`函数（如果含有虚函数，产生`vec_vnew()`函数），用来构造数组：

```c++
void vec_new(
    void* array, // 数组的起始地址
    size_t elem_size, // 数组中每一个元素的大小
    int elem_count, // 数组中的元素个数
    void (*constructor)(void*), // 形参个数为0的默认构造函数指针
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
    void* array, // 数组的起始地址
    size_t elem_size, // 数组中每一个元素大小
    int elem_count, // 数组中元素的个数
    void (*destructor)(void*, char) // 析构函数指针
)
```

### Default Constructor和数组

如果一个类的构造函数有一个活一个以上的默认参数值，例：

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

### new和delete运算符

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

1. 操作符new的过程就是：先配置内存，再调用构造函数（内置类型直接赋值）。（如果配置内存失败，内存还是需要释放的）
2. 操作符delete的过程就是：先调用析构函数（内置类型没有这一步），再释放内存（）。

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

针对数组的new语意

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

Placement Operator new是一个预先定义好的重载的new运算符

