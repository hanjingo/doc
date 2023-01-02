# Chapter 13. Future Directions



## 13.1 The Angle Bracket Hack

The second typedef declaration is an error because the two closing angle brackets with no intervening blank space constitute a "right shift" (`>>`) operator, which makes no sense at that location in the source.

```c++
typedef std::vector<std::list<int> > a; // 正确
typedef std::vector<std::list<int>> b;  // 错误(以后可能会取消此限制)
```



## 13.2 Relaxed typename Rules

Some programmers and language designers find the rules for the use of `typename` too strict.

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



## 13.3 Default Function Template Arguments

it is possible to specify explicitly function template arguments that cannot be deduced. Hence, would be entirely natural to specify default values for those nondeducible template arguments.

```c++
template<typename T1 = int, typename T2>
class Bad;
Bad<int>* b; // int替换的是T1还是T2？
```



## 13.4 String Literal and Floating-Point Template Arguments

Among the restrictions on nontype template arguments, perhaps the most surprising to beginning and advanced template writers alike is the inability to provide a string literal as template argument.

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



## 13.5 Relaxed Matching of Template Template Parameters

A template used to substitute a template template parameter must match that parameter's list of template parameter exactly. This can sometimes have surprising consequences.

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



## 13.6 Typedef Tempaltes

Class templates are often combined in relatively sophisticated ways to obtain other parameterized types. When such parameterized types appear repeatedly in source code, it is natural to want a shortcut for them, just as typedefs provide a shortcut for unparameterized types.

```c++
template<typename T>
typedef vector<list<T> > T1;

T1<int> li; // li的类型为：vector<lsit<int> >
```



## 13.7 Partial Specialization of Function Templates

in parctice there are a number of limitations:

- It is possible to specialize member templates of a class without changing the definition of that class. However, adding an overloaded member does require a change in the definition of a class. In many cases this is not an option because we may not own the rights to do so. Furthemore, the C++ standard does not currently allow us to add new templates to the `std` namespace, but it does allow us to specialize templates from that namespace.
- To overload function templates, their function parameters must differ in some material way. Consider a function template `R convert(T const&)` where `R` and `T` are template parameters. We may very well want to specialize this template for `R = void`, but this cannot be done using overloading.
- Code that is valid for a nonoverloaded function may no longer be valid when the function is overloaded. Specifically, given two function templates `f(T)` and `g(T)` (where `T` is a template parameter), the expression `g(&f<int>)` is valid only if `f` is not overloaded (otherwise, there is no way to decide which `f` is meant).
- Friend declarations refer to specific function tempalte or an instantiation of a specific function template. A overloaded version of a function template would not automatically have the privileges granted to the origin template.



## 13.8 Thd tyepof Operator

```c++
template<typename T1, typename T2>
Array<???> operator+ (Array<T1> const& x, Array<T2> const& y);
```



## 13.9 Named Template Arguments

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



## 13.10 Static Properties

```c++
#include <iostream>
int main()
{
    std::cout << std::type<int>::is_bit_copyable << '\n';
    std::cout << std::type<int>::is_union << '\n';
}
```

