[TOC]

# 第一章 型别推导

## 条款1:理解模板型别推导
* 在模板型别推导过程中，具有引用型别的实参会被当成非引用型别来处理。换言之，其引用性会被忽略。
* 对万能引用形参进行推导时，左值实参会进行特殊处理
* 对按值传递的形参进行推导时，若实参型别中带有const或volatile，则他们还是会被当作不带const或volatile的型别来处理
* 在模板型别推导过程中，数组或函数型别的实参会退化成对应的指针，除非他们被用来初始化引用

### 情况1:ParamType是个指针或引用，但不是个万能引用
1. 若expr具有引用型别，先将引用部分忽略。
2. 对expr的型别和ParamType的型别执行模式匹配，来决定T的型别。

例1:

```c++
template<typename T>
void f(T& param);

int x = 27;
const int cx = x;
const int& rx = x;

// 在各次调用中，对param和T的型别推导结果如下:
f(x);   //T的型别是 int, param的型别是 int&
f(cx);  //T的型别是 const int, param的型别是 const int&
f(rx);  //T的型别是 const int, param的型别是 const int&
```

例2:

```c++
template<typename T>
void f(const T& param);

int x = 27;
const int cx = x;
const int& rx = x;

// 在各次调用中，对param和T的型别推导结果如下:
f(x);   //T的型别是 int, param的型别是 const int&
f(cx);  //T的型别是 int, param的型别是 const int&
f(rx);  //T的型别是 int, param的型别是 const int&
```

例3:

```c++
template<typename T>
void f(T* param);       //param是个指针

int x = 27;
const int *px = &x;     //px是指向x的指针，型别为 const int

f(&x);                  //T的型别是 int, param的型别是 int*

f(px);                  //T的型别是 const int, param的型别是 const int*
```

### 情况2:ParamType是个万能引用
* 如果expr是个左值，T和ParamType都会被推导为左值引用。这个结果具有双重的奇特之处:首先，这是在模板型别推导中，T被推导为引用型别的唯一情形。其次，尽管在声明时使用的是右值引用语法，他的型别推导结果却是左值引用。
* 如果expr是个右值，则应用“常规”（即情况1中的）规则。

例1:

```c++
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

### 情况3:ParamType即非指针也非引用
这意味着，无论传入的是什么，param都会是它的一个副本；
* 一如之前，若expr具有引用型别，则忽略其引用部分。
* 忽略expr的引用性后，若expr是个const对象，也忽略之。若其是个volatile对象，同忽略之(volatile对象不常用，他们一般仅用于实现设备驱动)。

例1:

```c++
int x = 27;
const int cx = x;
const int& rx = x;

f(x);   //T和param的型别都是int

f(cx);  //T和param的型别还都是int

f(rx);  //T和param的型别仍都是int
```

需要说明，const和volatile仅会在按值形参处被忽略

例2:

```c++
template<typename T>
void f(T param);

const char* const ptr = "abc";  //ptr是个指向const对象的const指针

f(ptr);                         //传递型别为const char* const的实参
```

### 函数实参:

例子:

```c++
void someFunc(int, double);

template<typename T>
void f1(T param);

template<typename T>
vid f2(T& param);

f1(someFunc);   //param被推导为函数指针，具体型别是 void(*)(int, double)

f2(someFunc);   //param被推导为函数引用，具体型别是 void(&)(int, double)
```



## 条款2:理解auto型别推导
- 在一般情况下，auto型别推导和模版型别推导是一模一样的，但是auto型别推导会假定用大括号括起来的初始化表达式代表一个`std::initializer_list`，但模版型别推导却不会。
- 在函数返回值或lambda式的形参中使用auto，意思是使用模版型别推导而非auto型别推导。

### 情况1:型别饰词是指针或引用，但不是万能引用

```c++
const auto& rx = x; // 情况1（rx是个引用，但不是万能引用）
```

### 情况2:型别饰词是万能引用

```c++
auto&& uref1 = x;   // x的型别是int，且是左值，
                    // 所以uref1的型别是int&

auto&& uref2 = cx;  // cx的型别是const int, 且是左值，
                    // 所以uref2的型别是const int&

auto&& uref3 = 27;  // 27的型别是int，且是右值，
                    // 所以uref3的型别是int&&
```

### 情况3:型别饰词既非指针也非引用

```c++
auto x = 27;        // 情况3（x既非指针也非引用）

const auto cx = x;  // 情况3（cx同样即非指针也非引用）
```

对于大括号初始化表达式的处理方法，是auto型别推导和模版推导的唯一不同之处。

例：

```c++
auto x = { 11, 23, 9 }; // x的型别是 std::initializer_list<int>

template<typename T>    // 带有形参的模版
void f(T param);        // 与x的声明等价的声明式

f({ 11, 23, 9 });       // 错误！无法推导T的型别
```

c++14允许使用auto来说明函数返回值需要推导，而且c++14中lambda式也会在形参声明中用到auto。然而，这些auto用法是在使用模版型别推导而非auto型别推导。所以，带有auto返回值的函数若要返回一个大括号括起来的初始化表达式是通过不过编译的。例：

```c++
auto createInitList()
{
    return { 1, 2, 3 }; // 错误：无法为{ 1, 2, 3 }完成型别推导
}
```

用auto来指定lambda式的形参型别时，也不能使用大括号括起来的初始化表达式：

```c++
std::vector<int> v;

...
auto resetV = [&v](const auto& newValue) { v = newValue; }; // c++14
...

resetV({ 1, 2, 3 });    // 错误！无法为{ 1, 2, 3 }完成型别推导
```



## 条款3:理解decltype
- 绝大多数情况下，`decltype`会得出变量或表达式的型别而不做任何修改
- 对于型别为T的左值表达式，除非该表达式仅有一个名字，`decltype`总是得出型别`T&`
- c++14支持`decltype(auto)`，和auto一样，它会从其初始化表达式出发来推导型别，但是它的型别推导使用的是`decltype`的规则

例：

```c++
const int i = 0; // decltype(i)是const int

bool f(const Widget& w); // decltype(w)是const Widget&
                         // decltype(f)是bool(const Widget&)

struct Point {
    int x, y;        // decltype(Point::x)是int
};                   // decltype(Point::y)是int

Widget w;            // decltype(w)是Widget

if (f(w)) ...        // decltype(f(w))是bool

template<typename T> // std::vector的简化版
class vector {
public:
    ...
    T& operator[](std::size_t index);
    ...
};

vector<int> v;      // decltype(v)是vector<int>
...
if (v[0] == 0) ...  // decltype(v[0])是int&
```

使用c++11中的返回值型别尾序语法(trailing return type syntax，函数的返回值型别将在行参列表之后)，来计算返回值类型，例：

```c++
template<typename Container, typename Index> // 能运作，但是可以改进
auto authAndAccess(Container& c, Index i) -> decltype(c[i])
{
    authenticateUser();
    return c[i];
}
```

改进的版本：

- c++14版

```c++
template<typename Container, typename Index>
decltype(auto)
authAndAccess(Container&& c, Index i)
{
    authenticateUser();
    return std::forward<Container>(c)[i];
}
```
- c++11版

```c++
teplate<typename Container, typename Index>
auto
authAndAccess(Container&& c, Index i)
-> decltype(std::forward<Container>(c)[i])
{
    authenticateUser();
    return std::forward<Container>(c)[i];
}
```

decltype推导规则，例：

```c++
decltype(auto) f1()
{
    int x = 0;
    ...
    return x;   // decltype(x)是int,所以f1返回的是int
}

decltype(auto) f2()
{
    int x = 0;
    ...
    return (x); // decltype(x)是int&，所以f2返回的是int&
}
```



## 条款4:掌握查看型别推导结果的方法
- 利用IDE编辑器，编译器错误消息和Boost.TypeIndex库常常能够查看到推导而得的型别
- 游戏工具产生的结果可能会无用，或者不准确。所以，理解c++型别推导规则是必要的。

几种查看型别推导结果的方法：
- IDE编辑器
- 编译器诊断信息
- 运行时输出
