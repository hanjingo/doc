# Chapter 11. Template Argument Deduction



We still need to explore how argument-parameter matching proceeds. We describe it in terms of matching a type A (derived from the argument type) to a parameterized type P (derived from the parameter declaration). If the parameter is declared with a reference declarator, P is taken to be the type referenced, and A is the type of the argument. Otherwise, however, P is the declared parameter type, and A is obtained from the type of the argument by `decaying` array and function types to pointer types, ignoring top-level `const` and `volatile` qualifiers.

However, a few constructs are not deduced contexts:

- Qualified type names. A type name like `Q<T>::X` will never be used to deduce a template parameter `T`.
- Nontype expressions that are not just a nontype parameter. A type name like `S<I+1>` will never be used to deduce `I`.

There are two situations in which the pair `(A, P)` used for deduction is not obtained from the arguments to a function call and the parameters of a function template:

- The First situation occurs when the address of a function template is taken:

  ```c++
  template<typename T>
  void f(T, T);
  void (*pf)(char, char) = &f;
  ```

- The other special situation occurs with conversion operator templates:

  ```c++
  struct S {
      public:
          template<typename T, int N> operator T[N]&(){...}
  };
  
  void f(int (&)[20]){...}
  void g(S s) {
      f(s);
  }
  ```

Normally, template deduction attempts to find a substitution of the function template parameters that make the parameterized type `P` identical to type `A`. However, when this is not possible, the following differences are tolerable:

- If the original parameter was declared with a reference declarator, the substituted `P` type may be more `const/volatile` qualified than the `A` type.
- If the `A` type is a pointer or pointer-to-member type, it may be convertible to the substituted `P` type by a qualification conversion (int other words, a conversion that adds `const` and/or `volatile` qualifiers).
- Unless deduction occurs for a conversion operator template, the substituted `P` type may be a base class type of the `A` type, or a pointer to a base class type of the class type for which `A` is a pointer type.

Template argument deduction applies exclusively to function and member function templates. In particular, the arguments for a class template are not deduced from the arguments to a call of one of its constructors. For example:

```c++
template<typename T>
class S {
    public:
    	S(T b) : a(b) {}
    private:
    	T a;
};

S x(12); // 错误：不能从构造函数的调用实参12演绎类模板参数T
```

Even when a default call argument is not dependent, it cannot be used to deduce template arguments. This means that the following is invalid C++:

```c++
template<typename T>
void f(T x = 42){...}
int main()
{
    f<int>(); // 正确；T=int
    f();      // 错误；不能根据缺省调用实参42来演绎T
}
```

The Barton-Nackman Trick:

```c++
template<typename T>
class Array{
    public:
    	...
        friend bool operator==(Array<T> const &a, Array<T> const &b) {...}
}
```



## Glossary

<div style="width: 50%; float:left;"></div>
<div style="width: 50%; float:left;"></div>
<div style="width: 50%; float:left;"></div>
<div style="width: 50%; float:left;"></div>
<div style="width: 50%; float:left;"></div>
<div style="width: 50%; float:left;"></div>
<div style="width: 50%; float:left;"></div>
<div style="width: 50%; float:left;"></div>
<div style="width: 50%; float:left;"></div>
