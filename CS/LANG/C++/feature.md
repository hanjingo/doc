# C++特性(C98)

[TOC]




## C++ new关键字

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

---



## explicit关键字

C++中的explicit关键字只能用于修饰只有一个参数的类构造函数, 它的作用是表明该构造函数是显示的, 而非隐式的, 跟它相对应的另一个关键字是implicit, 意思是隐藏的,类构造函数默认情况下即声明为implicit(隐式).

那么，什么是“隐式转换”呢？ 上面这句话也说了，是从 构造函数形参类型 到 该类类型 的一个编译器的自动转换。
下面通过代码来看一看：

```c++
#include "stdafx.h"
#include <string>
#include <iostream>
using namespace std ;
class BOOK  //定义了一个书类
{
    private:
        string _bookISBN ;  //书的ISBN号
        float _price ;    //书的价格

    public:
        //定义了一个成员函数，这个函数即是那个“期待一个实参为类类型的函数”
        //这个函数用于比较两本书的ISBN号是否相同
        bool isSameISBN(const BOOK & other ){
            return other._bookISBN==_bookISBN;
                }

        //类的构造函数，即那个“能够用一个参数进行调用的构造函数”（虽然它有两个形参，但其中一个有默认实参，只用一个参数也能进行调用）
        BOOK(string ISBN,float price=0.0f):_bookISBN(ISBN),_price(price){}
};

int main()
{
    BOOK A("A-A-A");
    BOOK B("B-B-B");

    cout<<A.isSameISBN(B)<<endl;   //正经地进行比较，无需发生转换

    cout<<A.isSameISBN(string("A-A-A"))<<endl; //此处即发生一个隐式转换：string类型-->BOOK类型，借助BOOK的构造函数进行转换，以满足isSameISBN函数的参数期待。
    cout<<A.isSameISBN(BOOK("A-A-A"))<<endl;    //显式创建临时对象，也即是编译器干的事情。
    
    system("pause");
}
```

代码中可以看到，isSameISBN函数是期待一个BOOK类类型形参的，但我们却传递了一个string类型的给它，这不是它想要的啊！还好，BOOK类中有个构造函数，它使用一个string类型实参进行调用，编译器调用了这个构造函数，隐式地将stirng类型转换为BOOK类型（构造了一个BOOK临时对象），再传递给isSameISBN函数。
　　
隐式类类型转换还是会带来风险的，正如上面标记，隐式转换得到类的临时变量，完成操作后就消失了，我们构造了一个完成测试后被丢弃的对象。
　　
我们可以通过explicit声明来抑制这种转换:

```c++
explicit BOOK(string ISBN,float price=0.0f):_bookISBN(ISBN),_price(price){}
```

explicit关键字只能用于类内部的构造函数声明上.这样一来，BOOK类构造函数就不能用于隐式地创造对象了，编译上面的代码会出现这样的提示：

```sh
Error:不存在用户定义的从"std::string"到"const BOOK"的适当转换
...
```

现在用户只能进行显示类型转换，显式地创建临时对象。

### 显示声明的构造函数和隐式声明的有什么区别

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
    // 析构函数这里不讨论, 省略...  
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

上面的代码中, "CxString string2 = 10;" 这句为什么是可以的呢? 在C++中, 如果的构造函数只有一个参数时, 那么在编译的时候就会有一个缺省的转换操作:将该构造函数对应数据类型的数据转换为该类对象. 也就是说 "CxString string2 = 10;" 这段代码, 编译器自动将整型转换为CxString类对象, 实际上等同于下面的操作:

```c++
CxString string2(10);  
```

或

```c++ 
CxString temp(10);  
CxString string2 = temp;  
```

但是, 上面的代码中的_size代表的是字符串内存分配的大小, 那么调用的第二句 "CxString string2 = 10;" 和第六句 "CxString string6 = 'c';" 就显得不伦不类, 而且容易让人疑惑. 有什么办法阻止这种用法呢? 答案就是使用explicit关键字. 我们把上面的代码修改一下, 如下:

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

explicit关键字的作用就是防止类构造函数的隐式自动转换.

上面也已经说过了, explicit关键字只对有一个参数的类构造函数有效, 如果类构造函数参数大于或等于两个时, 是不会产生隐式转换的, 所以explicit关键字也就无效了. 例如: 

```c++
class CxString  // explicit关键字在类构造函数参数大于或等于两个时无效  
{  
public:  
    char *_pstr;  
    int _age;  
    int _size;  
    explicit CxString(int age, int size)  
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
  
// 这个时候有没有explicit关键字都是一样的  
```

但是, 也有一个例外, 就是当除了第一个参数以外的其他参数都有默认值的时候, explicit关键字依然有效, 此时, 当调用构造函数时只传入一个参数, 等效于只有一个参数的类构造函数, 例子如下:

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

### 总结

1. 可以使用一个实参进行调用，不是指构造函数只能有一个形参。
2. 隐式类类型转换容易引起错误，除非你有明确理由使用隐式类类型转换，否则，将可以用一个实参进行调用的构造函数都声明为explicit。
3. explicit只能用于类内部构造函数的声明。它虽然能避免隐式类型转换带来的问题，但需要用户能够显式创建临时对象（对用户提出了要求）。

---



## const关键字

const主要是为了程序的健壮型,减少程序出错.

### 最基本的用法

```c++
const int a=100; //b的内容不变,b只能是100也就是声明一个int类型的常量(#define b =100)
int const b=100; //和上面作用一样 
```

const指针和引用一般用在函数的参数中

```c++
int* m = &a; //出错,常量只能用常指针
int c= 1;const int*pc = &c;//常指针可指向常量 

const int* pa = &a; //指针指向的内容为常量(就是b的值不变)
int const *a = &b; //指针指向的内容为常量(就是b的值不变)*p=3//error
int* const a = &b; //指针为常量,不能更改指针了如 a++但可以改值*p=3; 
```

从这可以看出const放在*左侧修饰的是指针的内容,const放在*右侧修饰的是指针本身. 

const引用的用法和指针一样

```c++
int const & a=b; 和指针一样
const int& a=b; 和指针一样
```

但没有 int& const a=b 的用法因为引用不能做移位运算，但只是出个warning 

```c++
const int* const a = &b; //综合应用,一般用来传递多维的数组
```

类如：

```c++
char* init[] = {"Paris","in the","Spring"};
void fun(const int* const a){}
fun(init)//保护参数不被修改 

int A(int)const; //是常函数，只能用在类中，调用它的对象不能改变成员值
const int A(); //返回的是常量,所以必须这么调用 cosnt int a=A();
int A(const int); //参数不能改值,可用在任意函数
int A(const int*);
....
int height() const;//常函数只能由常函数调用
int max(int,int) const;
int Max = max(height(),height()); 

const int* pHeap = new int;
delete pHeap;
p = NULL;//出错
```

我的解决办法是强制类型转换

```c++
const int* pHeap = new int(1);
delete (int*)pHeap;
pHeap = NULL; 
```

一、const 和引用联合使用的时候要注意 

```c++
const int a = 1; 
const int& ref1 = a;
const int& ref2 = 1; 
```

ref1 和 ref2 都是正确的，但是他们引用的内容和一般的引用不同;对 const int& ref1 = a; 而言，其实这个 ref1 已经和 a 没有任何关系了,ref1 实际上是对一个临时量的引用。同理 const int& ref2 = 1; 也是对一个临时量做的引用。当引用临时量是 C++ 的隐式类型转换可以起作用。临时量的生存期和引用量的生存期相同。 

二、强传const对象可能导致无定义行为 

对于优化做的比较好的编译器，代码 const int i = 1;当后面用到变量 i 的时候，编译器会优化掉对 i 的存取，而直接使用立即数 1 

```c++
const int i = 1; 
*(const_cast<int*>(&i)) = 2;
cout << *(int*)&i << endl;
cout << i << endl; 
```

所以，对 const 对象做 const_cast(标准转化) 可能导致无定义行为
目前我就遇到这些问题，那位还有补充的吗 

### Thinking again in C++（一）常量性原理 cphj（原作） 

有些地方很受启发:

1. 不能将const修饰的任何对象、引用和指针作为赋值表达式的左值。

```c++
const int cx=100;
const int & rcx=cx;
const int * pcx=&cx;
cx=200; //error
rcx=200; //error
*pcx=200; //error 
```

2. const类型的对象不能直接被non-const类型的别名所引用。

(1)不能将const类型的对象传递给non-const类型的引用。

```c++
const int cx=100;
int & rx=cx; //error
```

(2)不能将const类型的实参传递给形参为non-const类型引用的函数。

```c++
void f(int a)
{
}
void g(int & ra)
{
}
const int cx=100;
f(cx); //ok
g(cx); //error
```

(3)不能将const类型的对象作为non-const类型引用的函数返回值。

```c++
int & f(const int & rca)
{
return rca; //error
}
int x=100;
f(x); 
```

3. 可以使用const类型别名引用non-const对象。此时通过const引用不能修改对象，但对象可以通过non-const引用被修改。

```c++
int x=100;
int & rx=x;
const int & rcx=x; //ok
x=200;
rx=200;
rcx=200; //error 
```

4. 指针的属性有两个：指针的类型和指针本身的常量性。其中，指向const对象与指向non-const对象，是不同的指针类型。

```
int x=100;
const int * pcx=&x; //[1]
int * px=&x; //[2]
int y=100;
int * const cpy=&y; //[3]
int * py=&y; //[4]
```

[1][2]两个指针的类型不同；[3][4]两个指针的常量性不同。

对象与指向对象的指针的规则类似于对象与引用。即，const类型的对象不能直接被non-const类型的指针所指示（同2）；可以使用const类型的指针指向non-const对象（同3）。 

5. 可以将相同类型（包括常量性）的const指针值赋给non-const指针。

```c++
int x=100;
int * px;
const int * pcx=&x;
px=pcx; //error
int * const cpx=&x;
px=cpx; //ok 
```

6. 若函数的返回值为内建类型或是指针，则该返回值自动成为const性质。但自定义类型则为non-const性质。

```c++
int f() //相当于返回const int
{
return 100;
}
int * g(int & ra) //相当于返回int * const
{
return &ra;
}
class CTest
{
int n;
public:
CTest(int n){this->n=n;}
};
CTest h() //返回的就是CTest
{
return CTest(200);
} 

f()=200; //error 

int x=100;
int y=200;
int * px=&x;
g(y)=px; //error
*g(y)=x; //ok，从这点可以看出g()返回的不是const int * 

CTest t(100);
h()=t; //ok，但却是完全错误的、危险的做法
//所以h()的正确写法是返回const CTest
```

const int b=100; b的内容不变,b只能是100

int const b=100; b必须为int型,不能为其他类型?

这2句话的意思应该是一样的吧 ， THINKING IN C++是这样说的

const int a=100; a的内容不变,a只能是100（同样不能类型转换）。

int const b=100; b必须为int型,不能为其他类型?（同样在使用中不能修改）。

所以a和b是一样的，称为整型常数，在使用中不能被修改，当然都不能转为其他类型了。 

```c++
#include <iostream> 

using namespace std; 

int main()
{
　　const int a = 100;
　　int const b = 100; 

　 a = 100; //这四条语句编译时都会出现“Cannot modify a const object 
b = 100; //in function main()”的错误提示，也就是说，任何企图修改　　 a = 100.0;　//a和b（其实是一样的）的行为都会出现“灾难”，在语法上讲就　　b = 100.0; //是a和b都不能出现在赋值语句的左边！ 

　　cout<<'\n'<<a<<'\n'<<b<<endl; 

　　return 0;
}
```

常函数的调用是这样的：常量对象只能调用常成员函数，非常量对象即可以调常成员函数，也可以调一般成员函数，但当某个函数有const和非const两个版本时，const对象调const版本，非const对象调非const版本,例：

```c++
class A
{
public:
int & GetData(){return data;}
const int & GetData()const {return data;}
private:
int data;
} 
A a;
a.GetData();//调用int & GetData(){return data;}
//但如果没有这个函数，也可以调用const int & GetData()const 
const A const_a;
const_a.GetData();//调用const int & GetData()const {return data;}
```

常函数只能调常函数，也是由于这个原因

### 补充

1. const 和引用联合使用的时候要注意 

```c++
const int a = 1; 
const int& ref1 = a;
const int& ref2 = 1; 
```

ref1 和 ref2 都是正确的，但是他们引用的内容和一般的引用不同;对 const int& ref1 = a; 而言，其实这个 ref1 已经和 a 没有任何关系了;ref1 实际上是对一个临时量的引用。同理 const int& ref2 = 1; 也是对一个临时量做的引用。当引用临时量是 C++ 的隐式类型转换可以起作用。临时量的生存期和引用量的生存期相同。 

2. 强传const对象可能导致无定义行为 

对于优化做的比较好的编译器，代码 const int i = 1;当后面用到变量 i 的时候，编译器会优化掉对 i 的存取，而直接使用立即数 1 

```c++
const int i = 1; 

*(const_cast<int*>(&i)) = 2;
cout << *(int*)&i << endl;
cout << i << endl; 
```

所以，对 const 对象做 const_cast 可能导致无定义行为

```c++
#include <iostream.h>
void fun(char b){cout <<"void"<<endl;}
int fun(int const b){cout <<"int"<<endl;} 
int main()
{
fun(1.0);//详细看看重载函数吧 
fun(4); //想一想调用哪一个 

return 0;
}
```

我试了一下，会出错? vc说：'fun':ambiguous call to overloaded function 

补充的好啊，这个一般不会注意的

```c++
const int i = 1;
*(const_cast<int*>(&i)) = 2;
cout << *(int*)&i << endl;
cout << i << endl;
```

这个可真有意思，调试时两个都是2，可编译就是2，1了;const的永远都是const,这样能更改就不错了，不然就自相矛盾了
奇怪的是 pi 和 &i地址一样啊，就像楼上说的这是编译时的优化处理

```c++
const int i = 1;
int* pi=const_cast<int*>(&i);
*pi=2;
cout << *pi << endl;
cout << i << endl; 
```

那个主要是隐式转换;你可依次把两个函数注掉看看调用

```c++
#include <iostream.h>
//void fun(char b){cout <<"void"<<endl;}
void fun(int b){cout <<"int"<<endl;}
int main()
{
fun('a');
fun(4); 
return 0;
}
```

---



## volatile关键字

volatile 关键字是一种类型修饰符，用它声明的类型变量表示可以被某些编译器未知的因素更改，比如：操作系统、硬件或者其它线程等。遇到这个关键字声明的变量，编译器对访问该变量的代码就不再进行优化，从而可以提供对特殊地址的稳定访问。

当要求使用 volatile 声明的变量的值的时候，系统总是重新从它所在的内存读取数据，即使它前面的指令刚刚从该处读取过数据。而且读取的数据立刻被保存。例如：

```c++
volatile int i=10;
int a = i;
...
// 其他代码，并未明确告诉编译器，对 i 进行过操作
int b = i;
```

volatile 指出 i 是随时可能发生变化的，每次使用它的时候必须从 i的地址中读取，因而编译器生成的汇编代码会重新从i的地址读取数据放在 b 中。

### volatile指针

和 const 修饰词类似，const 有常量指针和指针常量的说法，volatile 也有相应的概念：
修饰由指针指向的对象、数据是 const 或 volatile 的：

```c++
const char* cpch;
volatile char* vpch;
```

注意:

- 可以把一个非volatile int赋给volatile int，但是不能把非volatile对象赋给一个volatile对象。
- 除了基本类型外，对用户定义类型也可以用volatile类型进行修饰。
- C++中一个有volatile标识符的类只能访问它接口的子集，一个由类的实现者控制的子集。用户只能用const_cast来获得对类型接口的完全访问。此外，volatile向const一样会从类传递到它的成员。

### 多线程下的volatile

有些变量是用 volatile 关键字声明的。当两个线程都要用到某一个变量且该变量的值会被改变时，应该用 volatile 声明，该关键字的作用是防止优化编译器把变量从内存装入 CPU 寄存器中。

如果变量被装入寄存器，那么两个线程有可能一个使用内存中的变量，一个使用寄存器中的变量，这会造成程序的错误执行。

volatile 的意思是让编译器每次操作该变量时一定要从内存中真正取出，而不是使用已经存在寄存器中的值，如下：

```c++
volatile  BOOL  bStop  =  FALSE;
```

在一个线程中：

```c++
while(  !bStop  )  {  ...  }  
bStop  =  FALSE;  
return;    
```

在另外一个线程中，要终止上面的线程循环：

```c++
bStop  =  TRUE;  
while(  bStop  );  //等待上面的线程终止，如果bStop不使用volatile申明，那么这个循环将是一个死循环，因为bStop已经读取到了寄存器中，寄存器中bStop的值永远不会变成FALSE，加上volatile，程序在执行时，每次均从内存中读出bStop的值，就不会死循环了。
```

这个关键字是用来设定某个对象的存储位置在内存中，而不是寄存器中。因为一般的对象编译器可能会将其的拷贝放在寄存器中用以加快指令的执行速度,再举个例子:

```c++
...  
int  nMyCounter  =  0;  
for(;  nMyCounter<100;nMyCounter++)  
{  
...  
}  
...
```

在此段代码中，nMyCounter 的拷贝可能存放到某个寄存器中（循环中，对 nMyCounter 的测试及操作总是对此寄存器中的值进行），但是另外又有段代码执行了这样的操作：nMyCounter -= 1; 这个操作中，对 nMyCounter 的改变是对内存中的 nMyCounter 进行操作，于是出现了这样一个现象：nMyCounter 的改变不同步。

---



## virtual关键字

### 虚函数

从语法上讲，构造函数和析构函数都可以调用虚函数，但是`<<effective c++>>`**不建议**，因为往往达不到目的。

1. 如果构造函数中有虚函数，此时子类还没有构造，所以此时的对象还是父类，不会触发多态。
2. 子类先进行析构，如果有虚函数的话，由于子类已经被析构了，所以会执行父类的虚函数。

哪些函数不能是虚函数:

- 构造函数：构造时，基类指针无法知道子类的具体类型；
- 内联成员函数：内联函数是在编译期展开，虚函数式运行时绑定**（内联可以修饰虚函数，但是当虚函数表现多态性的时候不能内联）**；
- 静态成员函数：静态成员函数是编译期确定的，不支持多态；
- 友元函数：不属于类成员函数，不能被继承；
- 普通函数：普通函数无法被继承；

### 虚析构函数

用途：

- 防止内存泄漏

### 纯虚函数

纯虚函数是在基类中声明的虚函数，它在基类中没有定义，但要求任何派生类都要定义自己的实现方法。

```c++
virtual func() = 0;
```

用途：

1. 方便多态
2. 不允许基类生成对象

---



## static关键字

TODO

---



## namespace关键字

TODO

---



## 参考

[1] [局部静态变量Static详解](https://blog.csdn.net/zkangaroo/article/details/61202533)