# CONST用法
const主要是为了程序的健壮型,减少程序出错.



## 最基本的用法:

```c++
const int a=100; b的内容不变,b只能是100也就是声明一个int类型的常量(#define b =100)
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

### 一、const 和引用联合使用的时候要注意 
```c++
const int a = 1; 
const int& ref1 = a;
const int& ref2 = 1; 
```
ref1 和 ref2 都是正确的，但是他们引用的内容和一般的引用不同;对 const int& ref1 = a; 而言，其实这个 ref1 已经和 a 没有任何关系了,ref1 实际上是对一个临时量的引用。同理 const int& ref2 = 1; 也是对一个临时量做的引用。当引用临时量是 C++ 的隐式类型转换可以起作用。临时量的生存期和引用量的生存期相同。 

### 二、强传const对象可能导致无定义行为 
对于优化做的比较好的编译器，代码 const int i = 1;当后面用到变量 i 的时候，编译器会优化掉对 i 的存取，而直接使用立即数 1 
```c++
const int i = 1; 
*(const_cast<int*>(&i)) = 2;
cout << *(int*)&i << endl;
cout << i << endl; 
```
所以，对 const 对象做 const_cast(标准转化) 可能导致无定义行为
目前我就遇到这些问题，那位还有补充的吗 



## Thinking again in C++（一）常量性原理 cphj（原作） 

有些地方很受启发:
### 1.不能将const修饰的任何对象、引用和指针作为赋值表达式的左值。
```c++
const int cx=100;
const int & rcx=cx;
const int * pcx=&cx;
cx=200; //error
rcx=200; //error
*pcx=200; //error 
```

### 2.const类型的对象不能直接被non-const类型的别名所引用。
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

### 3.可以使用const类型别名引用non-const对象。此时通过const引用不能修改对象，但对象可以通过non-const引用被修改。
```c++
int x=100;
int & rx=x;
const int & rcx=x; //ok
x=200;
rx=200;
rcx=200; //error 
```

### 4.指针的属性有两个：指针的类型和指针本身的常量性。其中，指向const对象与指向non-const对象，是不同的指针类型。
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

### 5.可以将相同类型（包括常量性）的const指针值赋给non-const指针。
```c++
int x=100;
int * px;
const int * pcx=&x;
px=pcx; //error
int * const cpx=&x;
px=cpx; //ok 
```

### 6.若函数的返回值为内建类型或是指针，则该返回值自动成为const性质。但自定义类型则为non-const性质。
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



## 补充

### 一、const 和引用联合使用的时候要注意 
```c++
const int a = 1; 
const int& ref1 = a;
const int& ref2 = 1; 
```
ref1 和 ref2 都是正确的，但是他们引用的内容和一般的引用不同;对 const int& ref1 = a; 而言，其实这个 ref1 已经和 a 没有任何关系了;ref1 实际上是对一个临时量的引用。同理 const int& ref2 = 1; 也是对一个临时量做的引用。当引用临时量是 C++ 的隐式类型转换可以起作用。临时量的生存期和引用量的生存期相同。 

### 二、强传const对象可能导致无定义行为 
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