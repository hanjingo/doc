# C++特性


<!-- vim-markdown-toc GFM -->

* [new](#new)
    - [new operator](#new-operator)
    - [operator new](#operator-new)
    - [placement new](#placement-new)
* [explicit](#explicit)
    - [显示和隐式声明](#显示和隐式声明)
    - [注意事项](#注意事项)
* [const](#const)
    - [最基本的用法](#最基本的用法)
    - [注意事项](#注意事项-1)
* [volatile](#volatile)
    - [多线程下的volatile](#多线程下的volatile)
    - [注意事项](#注意事项-2)
* [virtual](#virtual)
    - [虚函数](#虚函数)
    - [纯虚函数](#纯虚函数)
    - [抽象类](#抽象类)
    - [注意事项](#注意事项-3)
* [static](#static)
    - [作用](#作用)
    - [注意事项](#注意事项-4)
* [namespace](#namespace)
    - [用法](#用法)
    - [注意事项](#注意事项-5)
* [union](#union)
* [C++指针](#c指针)
    - [常量指针](#常量指针)
    - [指针常量](#指针常量)
    - [指向常量的指针常量](#指向常量的指针常量)
    - [指针与引用的区别](#指针与引用的区别)
* [lambda](#lambda)
    - [值捕获](#值捕获)
    - [引用捕获](#引用捕获)
    - [隐式捕获](#隐式捕获)
    - [混合方式](#混合方式)
    - [mutable](#mutable)
    - [形参限制](#形参限制)
* [list-initialization](#list-initialization)
    - [初始化顺序](#初始化顺序)
* [override](#override)
* [final](#final)
* [=default和=delete](#default和delete)
* [pragma](#pragma)
* [decltype](#decltype)
* [mutable](#mutable-1)
* [参考](#参考)

<!-- vim-markdown-toc -->



## new

### new operator

new operator是**操作符**，**不能被重载**，假如A是一个类，那么`A * a=new A`;实际上执行如下3个过程。 

1. 调用operator new分配足够的内存，等价于`operator new(sizeof(A)) `；

2. 调用构造函数生成类对象，`A::A() `；

3. 返回相应指针 。

事实上，分配内存这一操作就是由`operator new(size_t)`来完成的，如果类A重载了operator new，那么将调用`A::operator new(size_t )`，否则调用全局`::operator new(size_t )`，后者由C++默认提供。 

### operator new

operator new是**函数**，分为三种形式（前2种只分配空间，不调用构造函数，这点区别于new operator）： 

- `void* operator new (std::size_t size) throw (std::bad_alloc); `

  （可以被重载）；分配size个字节的存储空间，并将对象类型进行内存对齐；如果成功，返回一个非空的指针指向首地址；失败抛出bad_alloc异常。

- `void* operator new (std::size_t size, const std::nothrow_t& nothrow_constant) throw(); `

  （可以被重载）；在分配失败时不抛出异常，它返回一个NULL指针。 

- `void* operator new (std::size_t size, void* ptr) throw(); `

  （不可以被重载）；placement new版本，它本质上是对operator new的重载，定义于`#include <new>`中。它不分配内存，调用合。

```c++
A* a = new A; 							//调用第一种 
A* a = new(std::nothrow) A; //调用第二种 
new (p)A(); 								//调用第三种 

// new (p)A()调用placement new之后，还会在p上调用A::A()，这里的p可以是堆中动态分配的内存，也可以是栈中缓冲。 
```

### placement new

placement new是operator new的一个重载版本，placement new允许在一个已经分配好的内存中（栈或堆中）构造一个新的对象。

使用new operator分配内存需要在堆中查找足够大的剩余空间，这个操作速度是很慢的，而且有可能出现无法分配内存的异常（空间不够）；placement new可以解决这个问题，构造对象都是在一个预先准备好了的内存缓冲区中进行，不需要查找内存，内存分配的时间是常数；而且不会出现在程序运行中途出现内存不足的异常；

placement new的好处：

- 适用于对时间要求比较高，长时间运行不希望被打断的应用程序；
- 已分配好的内存可以反复利用，有效避免内存碎片问题。

使用方法如下：

1. 缓冲区提前分配

   ````c++
   // 可以使用堆的空间，也可以使用栈的空间，所以分配方式有如下两种：
   class MyClass {…};
   char *buf=new char[N*sizeof(MyClass)+ sizeof(int) ] ; 或者char buf[N*sizeof(MyClass)+ sizeof(int) ];
   ````
   
2. 对象的构造

   ```c++
   MyClass * pClass=new(buf) MyClass;
   ```

3. 对象的销毁
   一旦这个对象使用完毕，你必须显式的调用类的析构函数进行销毁对象。但此时内存空间不会被释放，以便其他的对象的构造。

   ```c++
   pClass->~MyClass();
   ```

4. 内存的释放
   如果缓冲区在堆中，那么调用`delete[] buf`进行内存的释放；如果在栈中，那么在其作用域内有效，跳出作用域，内存自动释放。

**注意：**

- 在C++标准中，对于`placement operator new []`有如下的说明：` placement operator new[] needs implementation-defined amount of additional storage to save a size of array.` 所以我们必须申请比原始对象大小多出`sizeof(int)`个字节来存放对象的个数，或者说数组的大小。
- 使用方法第二步中的new才是placement new，其实是没有申请内存的，只是调用了构造函数，返回一个指向已经分配好的内存的一个指针，所以对象销毁的时候不需要调用delete释放空间，但必须调用析构函数销毁对象。
- 使用placement new之前需要包含文件` new.h`

[返回顶部](#C++特性)

---



## explicit

C++中的explicit关键字只能用于修饰只有一个参数的类构造函数, 它的作用是表明该构造函数是显示的, 而非隐式的。

例，自动类型转换：

```c++
#include "stdafx.h"
#include <string>
#include <iostream>
using namespace std ;
class BOOK
{
private:
    string _bookISBN;
    float _price;

public:
    bool isSameISBN(const BOOK& other ) {
      return other._bookISBN==_bookISBN;
    }

    BOOK(string ISBN, float price=0.0f)
      :_bookISBN(ISBN),_price(price){}
};

int main()
{
    BOOK A("A-A-A");
    BOOK B("B-B-B");
  
    // 正经地进行比较，无需发生转换
    cout << A.isSameISBN(B) << endl; 

    // 此处即发生一个隐式转换：string类型-->BOOK类型，借助BOOK的构造函数进行转换，以满足isSameISBN函数的参数期待。
    cout << A.isSameISBN(string("A-A-A")) << endl;
  
    // 显式创建临时对象，也即是编译器干的事情。
    cout << A.isSameISBN(BOOK("A-A-A")) << endl;
}
```

隐式类类型转换会带来风险，隐式转换得到类的临时变量，完成操作后就消失了，我们构造了一个完成测试后被丢弃的对象。

我们可以通过explicit声明来抑制这种转换:

```c++
explicit BOOK(string ISBN, float price=0.0f)
  :_bookISBN(ISBN), _price(price){}
```

explicit关键字只能用于类内部的构造函数声明上；这样一来，BOOK类构造函数就不能用于隐式地创造对象了，编译上面的代码会出现这样的提示：

```sh
Error:不存在用户定义的从"std::string"到"const BOOK"的适当转换
...
```

### 显示和隐式声明

隐式声明：

```c++
class CxString  // 没有使用explicit关键字的类声明, 即默认为隐式声明  
{  
public:
  char *_pstr;
  int _size;
  CxString(int size)
  {  
    _size = size;                // string的预设大小
    _pstr = malloc(size + 1);    // 分配string的内存  
    memset(_pstr, 0, size + 1);  
  }  
  CxString(const char *p)  
  {  
    int size = strlen(p);  
    _pstr = malloc(size + 1);    // 分配string的内存  
    strcpy(_pstr, p);            // 复制字符串  
    _size = strlen(_pstr);  
  }
};  
  
  // 下面是调用:  
  CxString string1(24);     // 这样是OK的, 为CxString预分配24字节的大小的内存  
  CxString string2 = 10;    // 这样是OK的, 为CxString预分配10字节的大小的内存  
  CxString string3;         // 这样是不行的, 因为没有默认构造函数, 错误为: “CxString”: 没有合适的默认构造函数可用  
  CxString string4("aaaa"); // 这样是OK的  
  CxString string5 = "bbb"; // 这样也是OK的, 调用的是CxString(const char *p)  
  CxString string6 = 'c';   // 这样也是OK的, 其实调用的是CxString(int size), 且size等于'c'的ascii码  
  string1 = 2;              // 这样也是OK的, 为CxString预分配2字节的大小的内存  
  string2 = 3;              // 这样也是OK的, 为CxString预分配3字节的大小的内存  
  string3 = string1;        // 这样也是OK的, 至少编译是没问题的, 但是如果析构函数里用free释放_pstr内存指针的时候可能会报错, 完整的代码必须重载运算符"=", 并在其中处理内存释放  
```

在C++中, 如果的构造函数只有一个参数时，那么在编译的时候就会有一个缺省的转换操作：将该构造函数对应数据类型的数据转换为该类对象。在上述代码中`CxString string2 = 10;`，编译器自动将整型转换为CxString类对象，实际上等同于下面的操作:

```c++
CxString string2(10);  
```

或

```c++ 
CxString temp(10);  
CxString string2 = temp;  
```

使用explicit关键字，我们把上面的代码修改一下，如下:

```c++
class CxString  // 使用关键字explicit的类声明, 显示转换  
{  
public:  
  char *_pstr;  
  int _size;  
  explicit CxString(int size)  
  {
    _size = size;
    // 代码同上, 省略...  
  }
  CxString(const char *p)
  {
    // 代码同上, 省略...
  }  
};  
  
  // 下面是调用:  
  CxString string1(24);     // 这样是OK的  
  CxString string2 = 10;    // 这样是不行的, 因为explicit关键字取消了隐式转换  
  CxString string3;         // 这样是不行的, 因为没有默认构造函数  
  CxString string4("aaaa"); // 这样是OK的  
  CxString string5 = "bbb"; // 这样也是OK的, 调用的是CxString(const char *p)  
  CxString string6 = 'c';   // 这样是不行的, 其实调用的是CxString(int size), 且size等于'c'的ascii码, 但explicit关键字取消了隐式转换  
  string1 = 2;              // 这样也是不行的, 因为取消了隐式转换  
  string2 = 3;              // 这样也是不行的, 因为取消了隐式转换  
  string3 = string1;        // 这样也是不行的, 因为取消了隐式转换, 除非类实现操作符"="的重载
```

explicit关键字只对有一个参数的类构造函数有效，如果类构造函数参数大于或等于两个时，不会产生隐式转换（有一个例外，当除了第一个参数以外的其他参数都有默认值的时候，explicit关键字依然有效；此时，当调用构造函数时只传入一个参数，等效于只有一个参数的类构造函数）。

例如: 

```c++
class CxString  // 使用关键字explicit声明  
{  
public:  
    int _age;  
    int _size;  
    explicit CxString(int age, int size = 0)  
    {  
        _age = age;  
        _size = size;  
        // 代码同上, 省略...  
    }  
    CxString(const char *p)  
    {  
        // 代码同上, 省略...  
    }  
};  
  
    // 下面是调用:  
  
    CxString string1(24);     // 这样是OK的  
    CxString string2 = 10;    // 这样是不行的, 因为explicit关键字取消了隐式转换  
    CxString string3;         // 这样是不行的, 因为没有默认构造函数  
    string1 = 2;              // 这样也是不行的, 因为取消了隐式转换  
    string2 = 3;              // 这样也是不行的, 因为取消了隐式转换  
    string3 = string1;        // 这样也是不行的, 因为取消了隐式转换, 除非类实现操作符"="的重载 
```

### 注意事项

1. 可以使用一个实参进行调用，不是指构造函数只能有一个形参。
2. 隐式类类型转换容易引起错误，除非你有明确理由使用隐式类类型转换，否则，将可以用一个实参进行调用的构造函数都声明为explicit。
3. explicit只能用于类内部构造函数的声明。它虽然能避免隐式类型转换带来的问题，但需要用户能够显式创建临时对象（对用户提出了要求）。

[返回顶部](#C++特性)

---



## const

const主要是为了程序的健壮型，减少程序出错。

### 最基本的用法

```c++
const int a=100; // b的内容不变,b只能是100也就是声明一个int类型的常量(#define b =100)
int const b=100; // 和上面作用一样 
```

const指针和引用一般用在函数的参数中：

```c++
int* m = &a;                // 出错,常量只能用常指针
int c= 1;const int*pc = &c; // 常指针可指向常量 
const int* pa = &a;         // 指针指向的内容为常量(就是b的值不变)
int const *a = &b;          // 指针指向的内容为常量(就是b的值不变)*p=3//error
int* const a = &b;          // 指针为常量,不能更改指针了如 a++但可以改值*p=3; 
```

从这可以看出const放在左侧修饰的是指针的内容，const放在右侧修饰的是指针本身.。

const引用的用法和指针一样：

```c++
int const & a=b; // 和指针一样
const int& a=b;  // 和指针一样
```

但没有`int& const a=b`的用法，因为引用不能做移位运算；但硬要这么用，编译器只是出个warning：

```c++
const int* const a = &b; // 综合应用,一般用来传递多维的数组
```

const使用示例：

```c++
const int* pHeap = new int;
delete pHeap;
p = NULL; // 出错
```

我的解决办法是强制类型转换

```c++
const int* pHeap = new int(1);
delete (int*)pHeap;
pHeap = NULL; 
```

### 注意事项

1. const 和引用联合使用的时候要注意 

   ```c++
   const int a = 1; 
   const int& ref1 = a; // ref1是一个临时量的引用
   const int& ref2 = 1; // ref2是一个临时量的引用
   ```

   当引用临时量时C++的隐式类型转换可以起作用，临时量的生存期和引用量的生存期相同。 

2. 强转const对象可能导致无定义行为

   ```c++
   const int i = 1;
   *(const_cast<int*>(&i)) = 2;
   cout << *(int*)&i << endl;
   cout << i << endl; 
   ```

   对于优化做的比较好的编译器，代码`const int i = 1;`当后面用到变量i的时候，编译器会优化掉对i的存取，而直接使用立即数1；所以，对 const 对象做const_cast(标准转化)可能导致无定义行为。

3. 不能将const修饰的任何对象、引用和指针作为赋值表达式的**左值**

   ```c++
   const int cx = 100;
   const int &rcx = cx;
   const int *pcx = &cx;
   cx   = 200; // 错误
   rcx  = 200; // 错误
   *pcx = 200; // 错误
   ```

4. const类型的对象不能直接被non const类型的别名所引用

   不能将const类型的对象传递给non const类型的引用：

   ```c++
   const int cx = 100;
   int &rx = cx; // 错误
   ```

   不能将const类型的实参传递给形参为non const类型引用的函数：

   ```c++
   void f(int a) { }
   void g(int &ra) { }
   const int cx = 100;
   f(cx); // 正确
   g(cx); // 错误
   ```

   不能将const类型的对象作为non const类型引用的函数返回值：

   ```c++
   int& f(const int& rca)
   {
   	return rca; // 错误
   }
   int x = 100;
   f(x); 
   ```

5. 可以使用const类型别名引用non const对象，此时通过const引用不能修改对象，但对象可以通过non const引用被修改

   ```c++
   int  x  = 100;
   int& rx = x;
   const int& rcx = x; // 正确
   x   = 200;
   rx  = 200;
   rcx = 200; // 错误
   ```

6. 指向const对象与指向non const对象的指针，是不同的指针类型

   ```c++
   int x = 100;
   const int* pcx = &x; // 1
   int* px = &x;        // 2
   int y = 100;
   int* const cpy = &y; // 3
   int* py = &y;        // 4
   int* pz = pcx;       // 5
   ```

   `1`， `2`两个指针的类型不同；`3`，`4`两个指针的常量性不同。

   const类型的对象不能直接被non const类型的指针所指向（见5）。

   可以使用const类型的指针指向non const对象（见3）。

7. 可以将相同类型（包括常量性）的const指针值赋给non const指针

   ```c++
   int x = 100;
   int* px;
   const int* pcx = &x;
   px = pcx; // 错误
   int* const cpx = &x;
   px = cpx; // 正确
   ```
   
8. 若函数的返回值为内建类型或是指针，则该返回值自动成为const性质，但自定义类型则为non const性质
   
   ```c++
   int f() // 相当于返回const int
   {
       return 100;
   }
   int* g(int& ra) // 相当于返回int* const
   {
       return &ra;
   }
   class CTest
   {
       int n;
   public:
       CTest(int n) { this->n = n; }
   };
   CTest h() // 返回的就是CTest
   {
       return CTest(200);
   }
   
   f() = 200;     // 错误
   int x   = 100;
   int y   = 200;
   int* px = &x;
   g(y)    = px;  // 错误
   *g(y)   = x;   // 正确，从这点可以看出g()返回的不是const int*
   CTest t(100);
   h()     = t;   // 正确，但却是非常危险的做法，h()的正确写法是返回const CTest
   ```
   
9. 常量对象只能调用常成员函数，非常量对象即可以调常成员函数，也可以调一般成员函数；但当某个函数有const和非const两个版本时，const对象调const版本，非const对象调非const版本
   
   ```c++
   class A
   {
   public:
       int& GetData() { return data; }
       const int& GetData() const { return data; }
   private:
       int data;
   };
   
   A a;
   a.GetData();       // 调用int& GetData() { return data; }
   const A const_a;
   const_a.GetData(); // 调用const int& GetData() const { return data; }
   ```

[返回顶部](#C++特性)

---



## volatile

volatile关键字是一种类型修饰符，用它声明的类型变量表示可以被某些编译器未知的因素更改，比如：操作系统、硬件或者其它线程等。遇到这个关键字声明的变量，编译器对访问该变量的代码就不再进行优化，从而可以提供对特殊地址的稳定访问。

当要求使用volatile声明的变量的值的时候，系统总是**重新从它所在的内存读取数据**，即使它前面的指令刚刚从该处读取过数据，而且读取的数据立刻被保存。例如：

```c++
volatile int i=10;
int a = i;
...
// 其他代码，并未明确告诉编译器，对 i 进行过操作
int b = i;
```

volatile指出i是随时可能发生变化的，每次使用它的时候必须从i的地址中读取，因而编译器生成的汇编代码会重新从i的地址读取数据放在b中。

可以使用const或volatile修饰由指针指向的对象：

```c++
const char* cpch;
volatile char* vpch;
```

### 多线程下的volatile

当两个线程都要用到某一个变量且该变量的值会被改变时，应该用 volatile 声明，该关键字的作用是防止优化编译器把变量从内存装入 CPU 寄存器中。

如果变量被装入寄存器，那么两个线程有可能一个使用内存中的变量，一个使用寄存器中的变量，这会造成程序的错误执行；volatile 的意思是让编译器每次操作该变量时一定要从内存中真正取出，而不是使用已经存在寄存器中的值；如下：

```c++
volatile BOOL bStop = FALSE;
```

在一个线程中：

```c++
while(!bStop) {  ...  }
bStop = FALSE;
return;
```

在另外一个线程中，要终止上面的线程循环：

```c++
bStop = TRUE;
// 等待上面的线程终止，如果bStop不使用volatile申明，那么这个循环将是一个死循环，因为bStop已经读取到了寄存器中，寄存器中bStop的值永远不会变成FALSE，加上volatile，程序在执行时，每次均从内存中读出bStop的值，就不会死循环了。
while(bStop);
```

这个关键字是用来设定某个对象的存储位置在内存中，而不是寄存器中（一般的对象编译器可能会将其的拷贝放在寄存器中，用以加快指令的执行速度）。

### 注意事项

1. 可以把一个**非volatile int**赋给**volatile int**，但是不能把**非volatile对象**赋给一个**volatile对象**。
2. 除了基本类型外，对用户定义类型也可以用volatile类型进行修饰。
3. C++中一个有volatile标识符的类只能访问它接口的子集，一个由类的实现者控制的子集；用户只能用const_cast来获得对类型接口的完全访问；此外，volatile向const一样会从类传递到它的成员。

[返回顶部](#C++特性)

---



## virtual

### 虚函数

虚函数的默认参数：

```c++
#include <iostream>
using namespace std;
class Base
{
public:
  // 默认参数不包含在函数签名内
  virtual void fun(int x = 0){cout << "Base::fun(), x = " << x << endl; }
};
class Derived : public Base
{
public:
  // 这里virtual可以省略，因为只要函数在基类被声明位虚函数，子类就默认是虚函数
  virtual void fun(int x){cout << "Derived::fun(), x = " << x << endl;}
};
int main(void) {
  Derived d1;
  Base* bp = &d1;
  bp->fun();
  return 0;
}
```

运行结果：

```sh
Derived::fun(), x = 0
```

### 纯虚函数

纯虚函数是在基类中声明的虚函数，它在基类中没有定义，但要求任何派生类都要定义自己的实现方法：

```c++
virtual func() = 0;
```

用途：

1. 必须在继承中重新声明该函数，否则编译无法通过，使用纯虚函数可以规范接口形式。
1. 声明纯虚函数的基类无法实例化对象，方便多态。

### 抽象类

含有纯虚函数的类被称为抽象类，抽象类可以拥有构造函数；例：

```c++
class Base {
protected:
    int x;
public:
    virtual void fun() = 0;
    Base(int i) { x = i; } // 抽象类也可以拥有构造函数
    virtual ~Base() = 0;   // 纯虚析构函数
};
Base::~Base() { cout << "~Base()" << endl; }

// 继承并重写基类声明的纯虚函数，如果没有重写，则该继承类也为抽象类
class Derived : public Base {
    int y;
public:
    Derived(int i, int j) : Base(i) { y = j; }
    ~Derived() { cout << "~Derived()" << endl; }
    void fun() { cout << "x = " << x << ", y = " << y << endl; }
};

int main(void) {
    Derived d(4, 5);
    d.fun();
    return 0;
}
```

运行结果：

```sh
x = 4, y = 5
~Derived()
~Base()
```

### 注意事项

1. 从语法上讲，构造函数和析构函数都可以调用虚函数，但是**不建议**，原因如下：

   - 如果构造函数中有虚函数，此时子类还没有构造，所以此时的对象还是父类，不会触发多态。
   - 子类先进行析构，如果有虚函数的话，由于子类已经被析构了，所以会执行父类的虚函数。

2. 以下函数不能是虚函数：

   - `构造函数` 构造时，基类指针无法知道子类的具体类型。
   - `内联成员函数` 内联函数是在编译期展开，虚函数是运行时绑定**（内联可以修饰虚函数，但是当虚函数表现多态性的时候不能内联）**。
   - `静态成员函数` 静态成员函数不属于任何实例，加上virtual没有意义；静态成员函数是编译期确定的，不支持多态。
   - `友元函数` 不属于类成员函数，不能被继承。
   - `普通函数` 普通函数无法被继承。

3. 当一个类有可能被其他类所继承，需要删除一个指向派生类的基类指针（用来防止内存泄漏）时，就应该声明虚析构函数。

   ```c++
   class base {
   public:
       base() { cout << "Constructing base \n"; }
       virtual ~base() { cout << "Destructing base \n"; }
   };
   class derived : public base {
   public:
       derived() { cout << "Constructing drvived \n"; }
       ~derived() { cout << "Destructing derived \n"; }
   };
   
   int main(void) {
       derived *d = new derived();
       base *b = d;
       delete b;
       return 0;
   }
   ```

   运行结构如下：

   ```sh
   Constructing base 
   Constructing drvived 
   Destructing base
   ```

4. 虚函数可以被私有化，但是main函数必须声明为基类的friend，否则编译失败。

   ```c++
   // 编译失败
   class Derived;
   class Base {
   private:
       virtual void fun() { cout << "Base Fun" << endl; }
   };
   class Derived : public Base {
   private:
       void fun() { cout << "Derived Fun" << endl; }
   };
   
   int main() {
       Base *ptr = new Derived;
       ptr->fun();
       return 0;
   }
   ```

   声明Base类的main函数：

   ```c++
   // 编译成功
   class Base {
   private:
       virtual void fun() { cout << "Base Fun" << endl; }
   		friend int main(); // 注意这里，声明main为friend
   };
   ...
   ```

[返回顶部](#C++特性)


---



## static

static 是 C/C++ 中很常用的修饰符，它被用来控制变量的存储方式和可见性。

static 被引入以告知编译器，将变量存储在程序的静态存储区而非栈上空间，静态数据成员按定义出现的先后顺序依次初始化（消除时的顺序是初始化的反顺序），注意静态成员嵌套时，要保证所嵌套的成员已经初始化了。

在 C++ 中 static 的内部实现机制：静态数据成员要在程序一开始运行时就必须存在；因为函数在程序运行中被调用，所以静态数据成员不能在任何函数内分配空间和初始化。

如果 static 要修饰一个类，说明这个类是一个静态内部类（注意static只能修饰一个内部类），也就是匿名内部类。

### 作用

- `修饰变量` static修饰的静态局部变量只执行初始化一次（节省内存），而且延长了局部变量的生命周期，直到程序运行结束以后才释放。
- `修饰全局变量` 这个全局变量只能在本文件中访问，不能在其它文件中访问，即便是 extern 外部声明也不可以（保障数据安全性）。
- `修饰函数` 则这个函数的只能在本文件中调用，不能被其他文件调用。

### 注意事项

- **不能在类声明中定义静态数据成员**，类声明不进行实际的内存分配，静态数据成员要实际地分配空间。

- **不能在头文件中类声明的外部定义静态数据成员**，因为那会造成在多个使用该类的源文件中，对其重复定义。

- **不能通过类名来调用类的非静态成员函数**。

  ```c++
  class Point
  {
  public:
      void init() {}
      static void output(){}
  };
  
  int main()
  {
      Point::init();   // 错误；不能通过类名调用类的非静态成员函数
      Point::output(); // 正确；
  
      Point pt;
      pt.init();       // 正确；
      pt.output();     // 正确；
  }
  ```

- **不能在静态成员函数中引用非静态成员**，但是可以在类的非静态成员函数中调用静态成员函数。

  ```C++
  class Point
  {
  public:
      void init() { output(); }          // 正确；可以在类的非静态成员函数中调用静态成员函数
      static void output() { 
          std::cout << m_x << std::endl; // 错误；静态成员函数属于整个类，在实例化之前就已经分配空间了
      } 
  private:
      int m_x;
  };
  
  void main() {
      Point pt;
      pt.output();
  }
  ```

- 类的静态成员变量必须先初始化再使用

  ```c++
  class Point
  {
  public:
      static void output() { 
          std::cout << m_x << std::endl; // 错误；必须要初始化m_x才能使用
      } 
  private:
      static int m_x;
  };
  
  // int Point::m_x = 0; // 初始化m_x（类的静态成员变量必须先初始化再使用）
  int main() {
      Point pt;
      pt.output();
  }
  ```


[返回顶部](#C++特性)

---



## namespace

命名空间提供了一种在大项目中避免名字冲突的方法：在命名空间块内声明的符号被放入一个具名的作用域中，避免这些符号被误认为其他作用域中的同名符号。

### 用法

1. 具名命名空间

   ```c++
   namespace Q {
   	...
   }
   ```

2. 内联命名空间（C++11）

   ```c++
   inline namespace Q {
   	...
   }
   ```

   命名空间内的声明将在它的外围命名空间可见。

3. 无名命名空间

   ```c++
   namespace { int i; } // ::(独有)::i
   void f() { i++; }
   namespace A 
   {
       namespace { int i; int j; } // ::(独有)::i, ::(独有)::j
       void g() { i++; }
   }
   using namespace A; // 从A引入所有名称到全局命名空间
   void h() 
   {
       i++;    // 错误；::(独有)::i 与 ::A::(独有)::i 均在作用域中
       A::i++; // 成功
       j++;    // 成功
   }
   ```

4. 命名空间别名

   ```c++
   namespace foo {
       namespace bar {
           namespace baz {
               int qux = 42;
           }
       }
   }
   namespace fbz = foo::bar::baz; // 定义别名
   ```
   
4. 定义不同命名空间的同名类

   ```c++
   #include <vector>
   namespace vec
   {
       template<typename T>
       class vector {};
   }
   int main()
   {
       std::vector<int> v1; // std库的vector
       vec::vector<int> v2; // 用户自定义vector
       v1 = v2; // 错误；v1和v2是不同类型的对象
       {
           using namespace std;
           vector<int> v3;  // std::vector
           v1 = v3;         // 正确
       }
       {
           using vec::vector;
           vector<int> v4; // vec::vector
           v2 = v4;        // 正确
       }
   }
   ```

### 注意事项

1. 不要在头文件的全局作用域中写`using namespace`，这可能导致不合预期的名字冲突。

[返回顶部](#C++特性)

---



## union

联合体是特殊的类类型，它在同一个时刻只能保有其一个**非静态**数据成员；各成员共享一段内存空间， 一个联合变量的长度等于各成员中最长的长度；具有以下特征：

1. 默认访问控制符为public；
2. 可以拥有成员函数（包括构造函数，析构函数）；
3. 不能含有引用类型的成员；
4. 不能继承自其它类，不能作为基类；
5. 不能含有虚函数；
6. 匿名union在定义所在作用域可直接访问union成员；
7. 匿名union不能包含protected成员或private成员；
8. 全局匿名联合必须是static的。

使用示例：

```c++
union u {
    u() : i(1), s("abc") {};
    int i;
    string s;
}; // 普通的union

static union {
    int i;
    string s;
}; // 匿名union
```

[返回顶部](#C++特性)

---



## C++指针

### 常量指针

常量指针：指针指向的对象是常量，那么指针所指的对象不能被更改，但是指针可以指向别处。

在C/C++中，常量指针是这样声明的：

```c++
const int *p;
int const *p;
```

**注意：指针指向的对象不能通过这个指针来修改，可是仍然可以通过原来的声明修改，也就是说常量指针可以被赋值为变量的地址。**

例：

```c++
int a = 5;
const int b = 8;
const int *c = &a; // 这是合法的，非法的是对c的使用
*c = 6;            // 非法，但可以这样修改c指向的对象的值：a = 6;
const int *d = &b; // b是常量，d可以指向b，d被赋值为b的地址是合法的
```

### 指针常量

指针常量：指针是一个常量，这个指针无法指向别处，但是其指向的值可以改变。

在C/C++中，指针常量这样声明：

```c++
int a;
int *const b = &a; //const放在指针声明操作符的右侧
```

**注意：因为指针常量是一个常量，在声明的时候一定要给它赋初始值。一旦赋值，以后这个常量再也不能指向别的地址。**

例：

```c++
char *a = "abcde1234";
char *b = "bcde";
char *const c = &a;
a[0] = 'x';  // 合法，我们并没有限制a为常量指针（指向常量的指针）
*c[0] = 'x'; // 合法，与上面的操作一致
```

### 指向常量的指针常量

指向常量的指针常量：一个指针常量，指向的对象也是一个常量；

在C/C++中，指向常量的指针常量这样声明：

```c++
const int a = 25;
const int * const b = &a;
```

例：

```c++
char *a = "abcde1234";
const char *b = "bcde";
char *const c = &a;
const char *const d = &b;

```

### 指针与引用的区别

- 指针是一个指向地址的变量，引用是地址的别名；
- 引用使用时无需解引用`(*)`，指针需要解引用；
- 引用只能在定义时被初始化一次，之后不可变；指针可以改变指向的地址；
- 引用不能为空，指针可以为空；
- `sizeof(引用)`：所指向对象的大小；`sizeof(指针)`：指针本身的大小；
- 指针可以有多级`(**指针)`，引用只能是一级；
- 指针需要分配内存区域，引用不需要；
- `++`,`--`等操作的意义不一样。

### 智能指针

具体见：[STL#智能指针](stl.md)

[返回顶部](#C++特性)

---



## lambda

C++11的一大亮点就是引入了Lambda表达式，利用Lambda表达式，可以方便的定义和创建匿名函数；Lambda表达式完整的声明格式如下：

```c++
[捕获的外部变量] (形参) 是否可以修改捕获的变量值 异常-> return 返回类型{ ... }
```

### 值捕获

类似于值传递，被捕获的变量在Lambda表达式创建时通过值拷贝的方式传入，Lambda对传入值的修改**不影响**外部的值；例：

```c++
int main()
{
  int a = 123;
  auto f = [a]{ cout << a << endl; };
  f();
}
```

### 引用捕获

类似于引用传递，在被捕获的变量前加一个引用说明符`&`，Lambda对传入值的修改**会影响**外部的值；例：

```c++
int main()
{
  int a = 123;
  auto f = [&a] { cout << a << endl; }
  f();
}
```

### 隐式捕获

编译器根据函数体中的代码来推断需要捕获的变量，这种方式称之为隐式捕获；隐式捕获有2种方式：

- `[=]` 表示以值捕获的方式捕获外部变量
- `[&]` 表示以引用捕获的方式捕获外部变量

例：

```c++
int main()
{
  int a = 123;
  auto f1 = [=] { cout << a << endl; }; // 值捕获
  a = 456;
  auto f2 = [&] { cout << a << endl; }; // 引用捕获
  a = 789;
  f1(); // 输出123
  f2(); // 输出789
}
```

### 混合方式

Lambda支持多种捕获方式组合使用，捕获形式表：

| 捕获形式        | 说明                                                         |
| --------------- | ------------------------------------------------------------ |
| `[]`            | 不捕获任何外部变量                                           |
| `[变量名, ...]` | 默认以值的形式捕获指定的多个外部变量（用逗号分隔），如果引用捕获，需要显示声明（使用`&`说明符） |
| `[this]`        | 以值的形式捕获this指针                                       |
| `[=]`           | 以值的形式捕获所有外部变量                                   |
| `[&]`           | 以引用形式捕获所有外部变量                                   |
| `[=, &x]`       | 变量x以引用形式捕获，其余变量以传值形式捕获                  |
| `[&, x]`        | 变量x以值的形式捕获，其余变量以引用形式捕获                  |

### mutable

在Lambda中，如果以传值方式捕获外部变量，则函数体中不能修改该外部变量，否则会引发编译错误；使用mutable可以避免编译错误，并且使Lambda修改值捕获的外部变量；例：

```c++
int main()
{
  int a = 123;
  auto f = [a]() mutable { cout << ++a; };
  cout << a << endl; // 输出：123
  f(); // 输出：124
}
```

### 形参限制

1. 参数列表中不能有默认参数
2. 不支持可变参数
3. 所有参数必须有参数名

[返回顶部](#C++特性)

---



## list-initialization

初始化类成员有2种方式：

- 初始化列表(list-initialization)
- 构造函数赋值
  1. 初始化阶段
  2. 计算阶段

使用初始化列表的主要是基于性能考虑，初始化列表减少了一次调用默认构造函数的过程，对于数据密集型类，加速效果显著；

以下场合必须使用初始化列表：

- `常量成员` 因为常量只能初始化不能赋值，所以必须放在初始化列表里面；
- `引用类型` 引用必须在定义的时候初始化，并且不能重新赋值，所以也要写在初始化列表里面；
- `没有默认构造函数的类类型` 因为引用初始化列表可以不必调用默认构造函数来初始化，而是直接调用拷贝构造函数初始化；

### 初始化顺序

成员是按照它们在**类中出现**的顺序进行初始化，而不是按照它们在**初始化列表中出现**的顺序初始化；例：

```c++
struct foo
{
  int i;
  int j;
  foo(int x) : j(x), i(j) // i未定义
};
```

虽然j在初始化列表里面出现在i前面，但是i先于j定义，所以先初始化i，而此时j未初始化，导致i未定义；

[返回顶部](#C++特性)

---



## override

如果派生类在虚函数声明时使用了`override`描述符，那么该函数必须重载其基类中的同名函数，否则代码将无法通过编译，提高了编译器检查的安全性。

示例：

```c++
struct Base 
{
    virtual void VNeumann(int g) = 0;
    virtual void DKnuth() const;
    void Print();
};
struct DerivedMid: public Base 
{
};
struct DerivedTop : public DerivedMid 
{
    void VNeumann(double g) override; // 无法通过编译，参数不一致，并非重载    
		void DKnuth() override;           // 无法通过编译，常量性不一致，并非重载
		void Print() override;            // 无法通过编译，非虚函数重载
};
```

[返回顶部](#C++特性)

---



## final

用途：

1. 禁用继承

   在父类中使用final修饰，意味着子类无法继承它

   ```c++
   class Base final
   {
   };
    
   // 错误，Derive不能从Base派生。
   class Derive
           : public Base
   {
   };
   ```

2. 禁用重写

   将父类的成员函数标记为final，意味着子类无法重写该函数

   ```c++
   class Super
   {
     public:
       Supe();
       virtual void SomeMethod() final;
   };
   ```

[返回顶部](#C++特性)

---



## =default和=delete

如果在一个类中自己定义了一个构造函数，那么编译器将不会再给你一个默认构造函数；如果强制加上`=default`，就可以重新获得默认构造函数。

`=delete`的用途：

1. 显式的禁用某个函数；
2. 禁用类的转换构造函数，避免不期望的类型转换；
3. 禁用用户的自定义类的new操作符，避免在自由存储区创建类的对象。

从任何函数都可以`=delete`，包括非成员函数和模板实现；例：

```c++
// 删除函数delete
template <class charT, class traits = char_traits<charT> >
class basic_ios : public ios_base {
public: // 习惯把delete函数声明为public
    basic_ios(const basic_ios&) = delete;
    basic_ios& operator=(const basic_ios&) = delete;
}
```

```c++
// c++11 删除函数delete
class Widget {
public:
    template<typename T>
    void processPointer(T* ptr) { ... }
};
template<>
void Widget::processPointer<void>(void*) = delete; // 仍然具备public访问权限，但被删除了
```

[返回顶部](#C++特性)

---



## pragma

TODO

[返回顶部](#C++特性)

---



## decltype

TODO

[返回顶部](#C++特性)

---



## mutable

TODO

[返回顶部](#C++特性)

---



## 可变参数

TODO

[返回顶部](#C++特性)

---



## execution_character_set

TODO

[返回顶部](#C++特性)

---



## sizeof

TODO

[返回顶部](#C++特性)

---



## 可变参数

### va_list

TODO

### 初始化列表

TODO

### 模板展开

std::index_sequence

TODO

[返回顶部](#C++特性)

---



## 数据类型

### POD

TODO

---



## 参考

[1] [C++参考手册](https://zh.cppreference.com/w/%E9%A6%96%E9%A1%B5)

[2] [C++11新特性之十：enable_shared_from_this](https://blog.csdn.net/caoshangpa/article/details/79392878)

[3] [C++ 11 Lambda表达式](https://www.cnblogs.com/DswCnblog/p/5629165.html)

[4] [C++11新特性之六：list-initialization](https://blog.csdn.net/caoshangpa/article/details/79169930)

[5] [C++11新特性之七：bind和function](https://blog.csdn.net/caoshangpa/article/details/79173351)

[6] [cppreference.com-std::move](https://en.cppreference.com/w/cpp/utility/move)

[7] [局部静态变量Static详解](https://blog.csdn.net/zkangaroo/article/details/61202533)

[8] [C++ virtual关键字](https://blog.csdn.net/shuzfan/article/details/77165474)

[9] [C/C++ 中 static 的用法全局变量与局部变量](https://www.runoob.com/w3cnote/cpp-static-usage.html)

[10] [cppreference.com/Implementation defined behavior control](https://en.cppreference.com/w/cpp/preprocessor/impl)

[11] [C++ Core Guidelines](http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines?utm_source=wechat_session&utm_medium=social&utm_oi=974639756117843968#f7-for-general-use-take-t-or-t-arguments-rather-than-smart-pointers)

[12] [cppreference.com-联合体声明](https://zh.cppreference.com/w/cpp/language/union)

[13] [JOINT STRIKE FIGHTER AIR VEHICLE C++ CONDING STANDARDS](res/JSF-AV-rules.pdf)

[14] [c语言宏定义唯一匿名变量,C语言宏定义技巧](https://blog.csdn.net/weixin_32473663/article/details/117090245)

[15] [C++可变参数函数](https://blog.csdn.net/qq_32534441/article/details/103495144)

