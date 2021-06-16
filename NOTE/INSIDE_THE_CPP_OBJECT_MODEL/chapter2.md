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

