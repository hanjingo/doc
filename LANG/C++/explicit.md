# C++ explicit关键字详解
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



## 显示声明的构造函数和隐式声明的有什么区别

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



## 总结

1. 可以使用一个实参进行调用，不是指构造函数只能有一个形参。
2. 隐式类类型转换容易引起错误，除非你有明确理由使用隐式类类型转换，否则，将可以用一个实参进行调用的构造函数都声明为explicit。
3. explicit只能用于类内部构造函数的声明。它虽然能避免隐式类型转换带来的问题，但需要用户能够显式创建临时对象（对用户提出了要求）。