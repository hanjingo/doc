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

<div style="width: 50%; float:left;">unwieldy `/ʌnˈwiːldi/` 笨重的，笨手笨脚的，不灵巧的</div>
<div style="width: 50%; float:left;">intuitive `/ɪn'tjuːɪtɪv/` 直觉的</div>
<div style="width: 50%; float:left;">conclude `/kənˈkluːd/` 推断，断定，终止，结束</div>
<div style="width: 50%; float:left;">tentatively `/'tentətɪvli/` 试验性地，犹豫不决地，暂时地</div>
<div style="width: 50%; float:left;">conclusion `/kənˈkluː.ʒən/` 结尾，结局，结果</div>
<div style="width: 50%; float:left;">mention `/ˈmenʃn/` 提到，提及，说起</div>
<div style="width: 50%; float:left;">literal `/ˈlɪtərəl/` 常量，字面值，文学的，书面的，字面上的</div>
<div style="width: 50%; float:left;">overlook `/ˌəʊvəˈlʊk/` 忽略，忽视，俯视</div>
<div style="width: 50%; float:left;">participate `/pɑːˈtɪsɪpeɪt/` 参加，参与，分享</div>
<div style="width: 50%; float:left;">intricate `/'ɪntrɪkət/` 复杂的，难懂的</div>
<div style="width: 50%; float:left;">possibility `/ˌpɒsə'bɪləti/` 可能，可能性，潜在的价值</div>
<div style="width: 50%; float:left;">preferable `/ˈprefrəbl/` 更好的，较合适的，更可取的</div>
<div style="width: 50%; float:left;">trick `/trɪk/` 诡计，欺骗，把戏</div>
<div style="width: 50%; float:left;">candidate `/ˈkændɪdət/` 候选人，申请人，考生</div>
<div style="width: 50%; float:left;">sensitive `/'sensətɪv/` 敏感的，灵敏的，感光的，善解人意的</div>
<div style="width: 50%; float:left;">vocal `/'vəʊkl/` 声音的，口头的，声乐的，直言不讳的，元音，声乐作品</div>
<div style="width: 50%; float:left;">eliminate `/ɪˈlɪmɪneɪt/` 消灭，铲除，排除，淘汰</div>
<div style="width: 50%; float:left;">rumored `/'ruːmə/` 谣言，传闻，谣传</div>