# bind

bind是对c++标准中函数适配器bind1st/bind2nd的泛化和增强，可以适配任意的可调用对象，包括函数指针，函数引用，成员函数指针，函数对象和lambda表达式.

bind位于名字空间boost，需要包含的头文件如下：

```c++
#include <boost/bind.hpp>
using namespace boost;
```

## 工作原理

bind的基本形式如下：

```c++
template<class R, class F> 						bind(F f);
template<class R, class F, class A1> 	bind(F f, A1 a1);

namespace	// 匿名名字空间
{
  boost::arg<1> _1;
  boost::arg<2> _2;
  boost::arg<3> _3;
  ...
}
```

绑定完成后，bind会返回一个函数对象，它内部保存了f的拷贝，具有operator()，返回值类型被自动推导为f的返回值类型。在发生调用时，这个函数对象把之前存储的参数转发给f完成调用。

## 操作普通函数

bind可以绑定普通函数，使用函数名或函数指针，假设我们有如下的函数定义：

```c++
int f(int a, int b)
{ return a + b; }

int g(int a, int b, int c)
{ return a + b * c; }
```

那么，bind(f, 1, 2)将返回一个无参调用的函数对象，等价于f(1, 2)。bind(g, 1, 2, 3)同样返回一个无参调用的函数对象，等价于g(1,2,3)。这两个绑定表达式没有使用占位符，而是给出了全部的具体参数，代码如下：

```c++
cout << bind(f,1,2)() << endl;
cout << bind(g,1,2,3)() << endl;
```

相当于：

```c++
cout << f(1,2) << endl;
cout << g(1,2,3) << endl;
```

bind完全可以代替标准库中的bind1st和bind2nd，即使用bind(f, N, _1)和bind(f, _1, N)。

bind同样可以绑定函数指针，例：

```c++
typedef decltype(&f) f_type;
typedef decltype(&g) g_type;

f_type pf = f;
g_type pg = g;

int x = 1, y = 2, z = 3;
cout << bind(pf, _1, 9)(x) << endl;							// (*pf)(x,9)
cout << bind(pg, _3, _2, _2)(x, y, z) << endl;	// (*pg)(z,y,y)
```

## 操作成员函数

bind也可以绑定类的成员函数,例:

```c++
struct demo
{
  int f(int a, int b)
  { return a + b; }
};

demo a, &ra = a;	// 类的实例对象和引用
demo *p = &a;			// 指针

cout << bind(&demo::f, a, _1, 20)(10) << endl;
cout << bind(&demo::f, ra, _2, _1)(10, 20) << endl;
cout << bind(&demo::f, p, _1, _2)(10, 20) << endl;
```

下面的代码使用bind搭配标准算法for_each用来调用容器中所有对象的print()函数，例：

```c++
struct point
{
  int x, y;
  point(int a = 0, int b = 0):x(a),y(b){}
  void print()
  { cout << "(" << x << "," << y << ")\n"; }
};

vector<point> v(10);
for_each(v.begin(), v.end(), bind(&point::print, _1));
```

bind同样支持绑定虚拟成员函数，其用法与非虚拟函数相同，虚函数的行为将由实际调用发生时的实例来决定。

## 操作成员变量

bind的另一个对类的操作是它可以绑定public成员变量，他就像是一个选择器，其用法与绑定成员函数类似，只需要像使用一个成员函数一样去使用成员变量名。例:

```c++
vector<point> v(10);
vector<int> v2(10);

transform(v.begin(), v.end(), v2.begin(), bind(&point::x, _1));

for(auto x : v2)
{ cout << x << ","; }
```

代码中的bind(&point::x, _1)取出point对象的成员变量x，transform算法调用bind表达式操作容器v，逐个把成员变量填入v2中。

使用bind，可以实现SGISTL/STLport中非标准函数适配器select1st和select2nd的功能，直接选择出pair对象的first和second成员。例：

```c++
typedef pair<int, string> pair_t;
pair_t p(123, "string");

cout << bind(&pair_t::first, p)() << endl;
cout << bind(&pair_t::secodn, p)() << endl;
```

## 操作函数对象

如果函数对象有内部类型定义result_type，那么bind可以自动推导出返回值类型，其用法与绑定普通函数一样。但如果函数对象没有定义result_type，则需要在绑定形式上进行改动，用模板参数指明返回类型，例:

```c++
bind<result_type>(functor, ...);	// 注意模板参数
```

对于自定义函数对象，如果没有result_type类型定义。例：

```c++
struct func
{
  int operator()(int a, int b)
  { return a + b; }
};
```

那么，我们必须在模板参数里指明bind的返回值类型，像这样：

```c++
cout << bind<int>(func(), _1, _2)(10, 20) << endl;
```

## 对比标准

std::bind的用法与boost::bind完全相同。但为了避免冲突，标准占位符位于std::placeholder名字空间，其代码里需要用"std::placeholders::_1"的形式，略微不太方便。例：

```c++
cout << std::bind(f, std::placeholders::_1, 20)(10) << endl;
```

## 高级议题

1. 为占位符更名

   bind库默认使用_1, _2作为占位符的名称，例:为原占位符创建别名：

   ```c++
   boost::arg<1> &_x = _1;
   boost::arg<2> &_y = _2;
   boost::arg<1> &arg1 = _1;
   boost::arg<2> &arg2 = _2;
   ```

   定义别名也可以使用auto或decltype，这样就无须关心占位符的真实类型，可以把类型推导的工作交给编译器，有利于编写可移植代码：

   ```c++
   auto& 				_x = _1;
   decltype(_2)& _y = _2;
   ```

   改名后的占位符的用法与原占位符的用法完全相同。例如：

   ```c++
   assert(typeid(_x) == typeid(arg1));
   
   cout << bind(f, _x, _y)(10, 20) << endl;
   cout << bind(g, arg1, 2, arg2)(1, 2) << endl;
   ```

2. 存储bind表达式

   ```c++
   auto x = bind(greater<int>(), _1, _2);
   cout << x(10, 20) << endl;
   ```

3. 使用ref库

   bind采用拷贝的方式存储绑定函数对象和参数，bind库可以搭配ref库使用，让bind存储对象引用的拷贝，从而降低拷贝的代价。示例：

   ```c++
   int x = 10;
   cout << bind(g,_1,cref(x),ref(x))(10) << endl;
   
   func af;
   cout << bind<int>(ref(af), _1, _2)(10, 20) << endl;
   ```

   下面的代码因为引用失效引发了未定义行为：

   ```c++
   int x = 10;
   auto r = ref(x);											// r包装x的引用
   {
     int *y = new int(20);
     r = ref(*y);												// r包装*y
     
     cout << r << endl;
     cout << bind(g, r, 1, 1)() << endl;	// 工作正常
     delete y;														// 引用的对象被销毁
   }
   cout << bind(g, r, 1, 1)() << endl;		// 危险！未定义行为
   ```

4. 嵌套绑定

   bind可以嵌套，一个bind表达式生成的函数对象可以被另一个bind再次绑定，从而实现类似f(g(x))的形式：

   ```c++
   bind(f, bind(g, _1))(x)
   ```

5. 操作符重载

   ```c++
   typedef rational<int> ri;
   vector<ri> v = {ri(1,2,ri(3,4),ri(5,6))};
   
   // 删除所有分子为1的有理数
   remove_if(v.begin(), v.end(), bind(&ri::numerator, _1) == 1);
   assert(v[0].numerator() == 3);
   
   // 使用find_if算法查找分子是1的有理数，不存在
   assert(find_if(v.begin(), v.end(), bind(&ri.numerator, _1) == 1) == v.end());
   
   // 查找分子大于3且分母小于8的有理数
   auto pos = find_if(v.begin(), v.end(), 
                      bind(&ri::numerator, _1) > 3 && bind(&ri::denominator, _1) < 8);
   cout << *pos << endl;
   ```

   上面的find_if算法使用的bind表达式就等于下面的lambda表达式：

   ```c++
   auto pos = find_if(v.begin(), v.end(),
                     [](ri &r){
                       return r.numerator() > 3 && r.denomianator() < 8;
                     });
   ```

   显然，lambda表达式在实现复杂逻辑时更有优势。

6. 绑定重载函数

   直接使用函数名的绑定方式存在一点局限，如果程序里有若干个同名的重载函数，那么bind就无法确定要绑定的具体函数，导致编译错误。例：

   ```c++
   int f(double a, double b)
   { return a * b; }
   std::cout << bind(f,1,2)() << std::endl;	// bind失败，无法确定绑定函数
   ```

   解决方案一:用typedef定义函数指针类型，再使用函数指针变量明确要绑定的函数：

   ```c++
   typedef int (*f_type1)(int, int);
   typedef int (*f_type2)(double, double);
   
   f_type1 pf1 = f;
   f_type2 pf2 = f;
   
   cout << bind(pf1,1,2)() << endl;
   cout << bind(pf2,1,2)() << endl;
   ```

   解决方案二:使用lambda表达式来变通地“绑定”:

   ```c++
   [](const string& x)						// lambda表达式，x是占位符
   { return contains(x, "a"); } 	// 绑定contains函数
   ```

7. 绑定非标准函数

   bind库大大增强了c++标准库中的函数绑定器，可以适配任何c++中的函数。但标准形式bind(f,...)不是100%适用于所有情况，有些非标准函数是无法自动推导出返回值类型的，例:

   ```c++
   bind<int>(printf, "%d+%d=%d\n", _1, 1, _2)(6, 7);
   ```

   bind的标准形式也不能支持使用了不同的调用方式的函数，通用bind把他们看作函数对象，需要显式指定bind的返回值类型才能绑定。

