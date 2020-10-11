# 第一章 型别推导
## 条款1:理解模板型别推导
要点:
* 在模板型别推导过程中，具有引用型别的实参会被当成非引用型别来处理。换言之，其引用性会被忽略。
* 对万能引用形参进行推导时，左值实参会进行特殊处理
* 对按值传递的形参进行推导时，若实参型别中带有const或volatile，则他们还是会被当作不带const或volatile的型别来处理
* 在模板型别推导过程中，数组或函数型别的实参会退化成对应的指针，除非他们被用来初始化引用

### 情况1: ParamType是个指针或引用，但不是个万能引用
1. 若expr具有引用型别,先将引用部分忽略.
2. 尔后，对expr的型别和ParamType的型别执行模式匹配，来决定T的型别。

例1:

```
template<typename T>
void f(T& param);

int x = 27;
const int cx = x;
const int& rx = x;

在各次调用中，对param和T的型别推导结果如下:
f(x);   //T的型别是 int, param的型别是 int&
f(cx);  //T的型别是 const int, param的型别是 const int&
f(rx);  //T的型别是 const int, param的型别是 const int&
```

例2:

```
template<typename T>
void f(const T& param);

int x = 27;
const int cx = x;
const int& rx = x;

在各次调用中，对param和T的型别推导结果如下:
f(x);   //T的型别是 int, param的型别是 const int&
f(cx);  //T的型别是 int, param的型别是 const int&
f(rx);  //T的型别是 int, param的型别是 const int&
```

例3:

```
template<typename T>
void f(T* param);       //param是个指针

int x = 27;
const int *px = &x;     //px是指向x的指针，型别为 const int

f(&x);                  //T的型别是 int, param的型别是 int*

f(px);                  //T的型别是 const int, param的型别是 const int*
```

### 情况2： ParamTYpe是个万能引用
* 如果expr是个左值，T和ParamType都会被推导为左值引用。这个结果具有双重的奇特之处:首先，这是在模板型别推导中，T被推导为引用型别的唯一情形。其次，尽管在声明时使用的是右值引用语法，他的型别推导结果却是左值引用。
* 如果expr是个右值，则应用“常规”（即情况1中的）规则。

例1:

```
template<typename T>
void f(T&& param);

int x = 27;
const int cx = x;
const int& rx = x;

f(x);   //x是个左值，所以T的型别是int&, param的型别也是int&

f(cx);  //cx是个左值，所以T的型别是const int&, param的型别也是 const int&

f(rx);  //rx是个左值，所以T的型别是const int&, param的型别也是 const int&

f(27);  //27是个右值，所以T的型别是int，这么一来，param的型别就成了 int&&
```

### 情况3： ParamType即非指针也非引用
这意味着，无论传入的是什么，param都会是它的一个副本；
* 一如之前，若expr具有引用型别，则忽略其引用部分。
* 忽略expr的引用性后，若expr是个const对象，也忽略之。若其是个volatile对象，同忽略之(volatile对象不常用，他们一般仅用于实现设备驱动)。

例1:

```
int x = 27;
const int cx = x;
const int& rx = x;

f(x);   //T和param的型别都是int

f(cx);  //T和param的型别还都是int

f(rx);  //T和param的型别仍都是int
```

需要说明，const和volatile仅会在按值形参处被忽略

例2:

```
template<typename T>
void f(T param);

const char* const ptr = "abc";  //ptr是个指向const对象的const指针

f(ptr);                         //传递型别为const char* const的实参
```

函数实参:

例子:

```
void someFunc(int, double);

template<typename T>
void f1(T param);

template<typename T>
vid f2(T& param);

f1(someFunc);   //param被推导为函数指针，具体型别是 void(*)(int, double)

f2(someFunc);   //param被推导为函数引用，具体型别是 void(&)(int, double)
```