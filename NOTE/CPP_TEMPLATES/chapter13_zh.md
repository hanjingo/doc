# 第13章 未来的方向



## 13.1 尖括号Hack

多层模板使用空格分开（`> >`），此限制可能会在以后取消。

```c++
typedef std::vector<std::list<int> > a; // 正确
typedef std::vector<std::list<int>> b;  // 错误(以后可能会取消此限制)
```



## 13.2 放松typename的原则

对于任何前面又有使用关键字`struct`, `class`, `union`或者`enum`之一的受限类型名称，都可以在前面加上关键字`tyepname`。

```c++
template<typename T>
class Array{
    public:
	    typedef T Element;
    	...
};

template<typename T>
void clear(typename Array<T>::Element T& p); // 正确

template<>
void clear(typename Array<int>::Element T& p); // 错误
```



## 13.3 缺省函数模板实参

如果模板参数具有一个缺省实参值，那么位于该参数后面的每个参数都必须具有缺省模板实参，这个约束也同样适用于类模板（因为如果类模板不遵循这个约束的话，那么通常情况下都不能指定应该匹配后面的哪个实参）。

```c++
template<typename T1 = int, typename T2>
class Bad;
Bad<int>* b; // int替换的是T1还是T2？
```



## 13.4 字符串文字和浮点型模板实参

不能让字符串文字作为模板实参。

```c++
template <char const* msg>
class C {
    public:
    	void print();
};

int main()
{
    C<"hello">().print();
}
```



## 13.5 放松模板的模板参数的匹配

用于替换模板的模板参数的模板必须能够和模板参数的参数列表精确地匹配。

```c++
#include <list>

template<typename T1,
		 typename T2,
		 template<typename> class Container>
class C {
    public:
    	...
    private:
    	Container<T1> dom1;
    	Container<T2> dom2;
};

int main()
{
    C<int, double, std::list> c; // 错误：std::list的参数多于一个
}
```



## 13.6 typedef模板

typedef模板：通过组合类模板来获得其它的参数化类型。

```c++
template<typename T>
typedef vector<list<T> > T1;

T1<int> li; // li的类型为：vector<lsit<int> >
```



## 13.7 函数模板的局部特化

重载的函数模板存在以下约束：

- 在不改变类定义的前提下，我们就可以特化类中的某个成员模板。如果要给类增加一个重载函数，就不得不改变这个类的定义。
- 为了重载函数模板，多个重载函数之间的参数必须有本质上的区别。
- 那些针对某个非重载函数的合法代码，在对这个函数进行重载之后，就可能会变成不合法的代码。
- 针对引用“特定函数模板或者特定函数模板的实例化体”的友元声明，函数模板的重载版本并不能自动获得（原来赋给）原始模板的特权（即友元关系）。



### 13.8 typeof运算符

```c++
template<typename T1, typename T2>
Array<???> operator+ (Array<T1> const& x, Array<T2> const& y);
```



## 13.9 命名模板实参

```c++
template<typename T,
		 Move: typename M = defaultMove<T>,
		 Copy: typename C = defaultCopy<T>,
         Swap: typename S = defaultSwap<T>,
         Init: typeanme I = defaultInit<T>,
         Kill: typename K = defaultKill<T> >
class Mutator {...}
void test(MatrixList ml)
{
    mySort(ml, Mutator<Matrix, Swap: matrixSwap>);
}
```



## 13.10 静态属性

```c++
#include <iostream>
int main()
{
    std::cout << std::type<int>::is_bit_copyable << '\n';
    std::cout << std::type<int>::is_union << '\n';
}
```



## 13.11 客户端的实例化诊断信息

```c++
template<typename T>
void shell(T const& env)
{
    template try {
        typename T::Index p;
        *p = 0;
    } catch "T::Index must be a pointer=like type";
    typename T::Index i;
    middle(i);
}
```



## 13.12 重载类模板

基于模板参数之间的差异对类模板进行重载是完全可能的。同时重载并不受限于模板参数的个数，也可以借助于参数的不同种类进行重载。

```c++
template<typename T1>
class Tuple{
    // 单个
};

template<typename T1, typename T2>
class Tuple{
    // 一对
};

template<typename T1, typename T2>
class Pair{
    // 一对泛型的类型域
};

template<int I1, int I2>
class Pair{
    // 一对常整数值
};

template<typename T1, typename T2, typename T3>
class Tuple{
    // 3元组
};
```



## 13.13 List参数

为了声明一个参数个数不固定的函数，或者定义一种具有成员个数不固定的类型结构。可以把具有几个类型的列表看成一个单一的模板实参，并用这个单实参进行传递。

```c++
#include <iostream>

template<typename T, ... list>
T const& max(T const&, T const&, list const&);

template<typename T>
class ListProps {
    public:
    	enum{length = 1};
};

template<... list>
class ListProps {
    public:
    	enum{length = 1 + ListProps<list[1 ...]>::length};
}

int main()
{
    std::cout << max(1, 2, 3, 4) << std::endl;
}
```



## 13.14 布局控制

声明一个足够（但不能超过太多）容纳“一个未知类型T的对象”的字节数组。

```c++
template<typename T>
class Alignment {
    public:
    	enum{max = alignof(T)};
};

template <... list>
class Alignment {
    public:
    	enum{max = alignof(list[0]) > Alignment<list[1 ...]>::max
            ? alignof(list[0])
            : Alignment<list[1 ...]>::max}
};

template<... list>
class Variant {
    public:
    	char buffer[Size<list>::max] alignof(Alignment<list>::max);
}
```



## 13.15 初始化器的演绎

```c++
template<typename T>
class Complex {
    public:
    	Complex(T const& re, T const& im);
};

Complex<> z(1.0, 3.0);
```



## 13.16 函数表达式

引入一个函数表达式，使用一个特殊符号`$`，在该符号后面紧跟圆括号中的参数类型和花括号里面的实体。在构造的内部，通过符号`$n`来引用每个参数。

```c++
class BigValue {
    public:
    	void init();
};
void compute(std::vecotr<BigValue>& vec)
{
    std::for_each(vec.begin(), vec.end(),
                 $(BigValue&){$1.init();});
}
```



## 13.17 本章后记