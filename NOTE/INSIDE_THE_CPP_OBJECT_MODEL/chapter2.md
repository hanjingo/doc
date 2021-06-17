# 第二章 构造函数语意学(The Semantics of Constructors)

**explicit**能够制止"单一参数的constructor"被当做一个conversion运算符。

## Deafult Constructor的构造操作

1. 对于`class X`，如果没有任何`user-declared constructor`，那么会有一个`default constructor`被隐式（implicitly）声明出来...一个被隐式声明出来的`default constructor`将是一个`trivial（无效的） constructor`

2. 把合成的`default constructor, copy constructor, destructor, assignment copy operator`都以`inline`方式完成。一个`inline`函数有静态链接`(static linkage)`，不会被文件以外者看到。如果函数太复杂，不适合做成`inline`，就会合成出一个`explicit non-inline static`实例。

3. 如果`class A`内含一个或一个以上的`member class objects`，那么`class A`的每一个`constructor`必须调用每一个`member classes`的`default constructor`。会扩张已存在的`constructors`，在其中安插一些代码，使得用户代码被执行之前，先调用必要的`default constructors`。

### 带有一个Virtual Function的Class
有2种情况需要合成出`default constructor`:

1. class声明（或继承）一个`virtual function`。

2. class派生自一个继承串链，其中有一个或更多的`virtual base classes`。

扩张行动，例：

```c++
class Widget {
    public:
        virtual void flip()b = 0;
        // ...
};

void flip( const Widget& widget) { widget.flip(); }

// 假设Bell和Whistle都派生自Widget
void foo()
{
    Bell b;
    Whistle w;

    flip(b);
    flip(w);
}
```

下面的扩张行动会在编译期发生：

1. 一个`virtual function table`（在cfront中被称为vtbl）会被编译器产生出来，内放class的`virtual functions`地址。

2. 在每一个`class object`中，一个额外的`pointer member`（也就是vptr）会被编译器合成出来，内含相关之`class vtbl`的地址。

此外，`widget.flip()`的虚拟调用操作(`virtual invocation`)会被重新改写，以使用`widget`的`vptr`和`vtbl`中的`flip()`条目：

```c++
// widget.flip()的虚拟调用操作（virtual invocation）的转变
(*widget.vptr[ 1 ])( &widget )
```

- 1表示`flip()`在`virtual table`中的固定索引；
- `&widget`代表要交给“被调用的某个flip()函数实例”的**this**指针；

`__vbcX`（或编译器所做出的某个什么东西）是在class object构造期间被完成的。对于class所定义的每一个`constructor`，编译期会安插那些“允许每一个virtual base class的执行期存取操作"的代码。如果class没有声明任何constructors，编译器必须为它合成一个default constructor。

有4种情况，会造成“编译器必须为未声明constructor的classes合成一个default constructor”。`implicit nontrivial default constructors`。被合成出来的`constructor`只能满足编译器（而非程序）的需要。

没有存在那4种情况而又没有声明任何`constructor`的`classes`，我们说它们拥有的是`implicit trivial default constructors`，它们实际上并不会被合成出来。

在合成的`default constructor`中，只有`base class subobjects`和`member class objects`会被初始化。所有其他的`nonstatic data member（如整数，整数指针，整数数组等等）都不会被初始化`。



## Copy Constructor的构造操作

### Default Memberwise Initialization

当`class object`以"相同class的另一个object"作为初始值,其内部是以所谓的`default memberwise initialization`手法完成的,也就是把每一个内建的或派生的`data member`(例如一个指针或数组)的值,从某个`object`拷贝一份到另一个object身上.不过它并不会拷贝其中的`member class object`,而是以递归的方式施行`memberwise initialization`.例:

```cpp
class String {
public:
    // ...没有explicit copy constructor
private:
    char *str;
    int len;
};
```

一个`String object`的`default memberwise initialization`发生在以下情况:

```cpp
String noun("book");
String verb = noun;
```

其完成方式就好像个别设定每一个members一样:

```cpp
// 语意相同
verb.str = noun.str;
verb.len = noun.len;
```

如果一个`String object`被声明为另一个`class`的member,如下所示:

```cpp
class Word {
public:
   // ...没有explicit copy constructor
private:
    int _occurs;
    String _word;
};
```

那么一个`Word object`的`default memberwise initialization`会拷贝其内建的member`_occurs`,然后再于String member object `_word`身上递归实施`memberwise initialization`.

具体实际操作如下:

1. 概念上而言,对于一个`class X`,这个操作时被一个`copy constructor`实现出来的...

2. 一个良好的编译器可以为大部分`class objects`产生`bitwise copies`,因为它们有`bitwise copy semantics`...

3. `Default constructors`和`copy constructors`在必要的时候才由编译器产生出来.

4. 一个`class object`可用两种方式复制得到,一种是被初始化(也就是我们这里锁关心的),另一种是被指定(assignment).从概念上而言,这两个操作分别是以`copy constructor`和`copy assignment operator`完成的.

如果class没有声明一个`copy constructor`,就会有隐式的声明(implicitly declared)或隐式的定义(implicitly defined)出现.

c++ Standard把`copy constructor`区分为`trival`和`notrivial`两种.只有`notrivial`的实例才会被合成于程序之中.决定一个`copy constructor`是否为`trivial`的标准在于class是否展现出所谓的"bitwise copy semantics".

### Bitwise Copy Semantics(位逐次拷贝)

### 不要Bitwise Copy Semantics

有以下4种情况不展现出`bitwise copy semantics`:

1. 当class内含一个`member object`而后者的class声明有一个`copy constructor`时。
2. 当class继承自一个`base class`而后者存在一个`copy constructor`时。
3. 当class声明了一个或多个`virtual functions`时。
4. 当class派生自一个继承串链，其中有一个或多个`virtual base classes`时。

### 重新设定Virtual Table的指针

一个class声明了一个或多个`virtual functions`会产生以下扩张操作：
- 增加一个`virtual function table(vtbl)`，内含每一个有作用的`virtual function`的地址。
- 一个指向`virtual function table`的指针（vptr），安插在每一个`class object`内。

### 处理Virtual Base Class Subobject

一个`virtual base class`的存在会使`bitwise copy semantics`无效。

`default copy constructor`如果未被声明的话，会被视为`nontrivial`。



## 程序转化语意学(Program Transformation Semantics)

### 显式的初始化操作(Explicit Initialization)

必要的程序转化有两个阶段：

1. 重写每一个定义，其中的初始化操作会被剥除以。
2. class的`copy constructor`调用操作会被安插进去。

### 参数的初始化(Argument Initialization)

将一个`class object`当做参数传给一个函数时，有2种策略：

1. 导入所谓的临时性`object`，并调用`copy constructor`将它初始化，然后将此临时性object交给函数。
2. 以“拷贝构造(copy construct)”的方式把实际参数直接构建在其应该的位置上，此位置视函数活动范围的不同，记录于程序堆栈中。在函数返回之前，局部对象`(local object)`的`destructor`(如果有定义的话)会被执行。

### 返回值的初始化(Return Value Initialization)

例，函数的转化：

```c++
X bar()
{
    X xx;
    // 处理xxx ...
    return xx;
}
```

转化为：

```c++
// c++伪代码
void
bar(X& __result)
{
    X xx;
    
    // 编译器所产生的default constructor调用操作
    xx.X::X();

    // ...处理xx

    // 编译器所产生的copy constructor调用操作
    __result.X::XX(xx);

    return;
}
```

函数的转化流程：

1. 首先加上一个额外参数，类型是`class object`的一个reference。这个将用来放置被“拷贝构建(copy constructed)”而得的返回值。
2. 在`return`指令之前安插一个`copy constructor`调用操作，以便将欲传回之object的内容当作上述新增参数的初值。

### 在使用者层面做优化(Optimization at the User Level)

### 在编译器层面做优化(Optimization at the Compiler Level)

例，编译器`Named Return Value(NRV)`优化：

```c++
X bar()
{
    X xx;
    // ...处理xx
    return xx;
}
```

优化为:

```c++
void
bar( X &__result )
{
    // default constructor被调用
    // c++伪代码
    __result.X::X();

    // ...直接处理 __result
    return;
}
```

虽然`NRV优化`提供了重要的效率改善，但其依然饱受批评，原因如下：

1. 优化由编译器默默完成，而它是否真的被完成，并不十分清楚（因为很少有编译器会说明其实现程度，或是否实现）
2. 一旦函数变得比较复杂，优化也就变得比较难以施行。
3. 优化会打破程序的对称性。

### Copy Constructor: 要还是不要?

不管使用`memcpy()`还是`memset()`，都只有在"classes不含任何由编译器产生的内部members"时才能有效运行。如果声明一个或一个以上的`virtual functions`，或内含一个`virtual base class`，那么使用上述函数将会导致那些“被编译器产生的内部members”的初值被改写。

### 摘要

`copy constructor`的应用，迫使编译器多多少少对你的代码做部分转化。尤其是当一个函数以传值(by value)的方式传回一个`class object`，而该class有一个`copy constructor(不论是显式定义出来的，或是合成的)`时。这将导致深奥的程序转化-不论在函数的定义上还是在使用上。此外，编译器也将`copy constructor`的调用操作优化，以一个额外的第一参数（数值被直接存放于其中）取代`NRV`。程序员如果了解那些转换，以及`copy constructor`优化后的可能状态，就比较能控制其程序的执行效率。



## 成员们的初始化队伍(Member Initialization List)

在下列情况下，为了让你的程序能够被顺利编译，你必须使用`member initialization list`：

1. 当初始化一个`reference member`时；
2. 当初始化一个`const member`时；
3. 当调用一个base class的`constructor`，而它拥有一组参数时；
4. 当调用一个member class的`constructor`，而它拥有一组参数时；

编译器会一一操作`initialization list`，以适当顺序在`constructor`之内安插初始化操作，并且在任何`explicit user code`之前。

**注意：list中的项目顺序是由class中的members声明顺序决定的，不是由`initialization list`中的排序顺序决定的。**

`initialization list`被放在`explicit user code`之前。

**忠告：请使用"存在于constructor”体内的一个member"，而不要使用“存在于member initialization list中的member“，来位另一个member设定初值。**

简略地说，编译器会对`initialization list`一一处理并可能重新排列，以反映出members的声明顺序。它会安插一些代码到constructor体内，并置于任何`explicit user code`之前。
