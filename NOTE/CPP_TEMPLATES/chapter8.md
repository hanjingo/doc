# Chapter8 Fundamentals in Depth

<!-- vim-markdown-toc GFM -->

<!-- vim-markdown-toc -->



C++ currently supports two fundamental kinds of templates: class templates and function templates.

All three correspond to definitions of members of class templates:

1. Definitions of member functions of class templates
2. Definitions of nested class members of class templates
3. Definitions of static data members of class templates

Member function templates cannot be declared virtual. This constraint is imposed because the usual implementation of the virtual function call mechanism uses a fixed-size table with one entry per virtual function. However, the number of instantiations of a member function template is not fixed until the entire program has been translated.

Every template must have a name and that name must be unique within its scope, except that function templates can be overloaded. Note especially that, unlike class types, class templates cannot share a name with a different kind of entity:

```c++
int c;
class c; // 正确：类名称和非类名称位于不同的名字空间

int x;
template <typename T>
class x; // 错误：与变量x冲突

struct s;
template <typename T>
class s; // 错误：与struct s冲突
```

Template names have linkage, but they cannot have C linkage.

Normal declarations of templates declare so-called primary templates. Such template declarations are declared without adding template arguments in angle brackets after the template name:

```c++
template <typename T> class Box;    // 正确

template <typename T> class Box<T>; // 错误

template <typename T> void translate(T*);    // 正确

template <typename T> void translate<T>(T*); // 错误
```

There are three kinds of template parameters:

1. Type parameters(these are by far the most common)
2. Nontype parameters
3. Template template parameters

Type parameters are introduced with either the keyword `typename` or the keyword `class`: The two are entirely equivalent. The keyword must be followed by a simple identifier and that identifier must be followed by a comma to denote the start of the next parameter declaration, a closing angle bracket (>) to denote the end of the parameterization clause, or an equal sign (=) to denote the beginning of a default template argument.

Nontype template parameters stand for constant values that can be determined at compile or link time. The type of such a parameter(in other words, the type of the value for which it stands) must be one of the following:

- An integer type or an enumeration type
- A pointer type(including regular object pointer types, function pointer types, and pointer-to-member types)
- A reference type(both references to objects and references to functions are acceptable)

Perhaps surprisingly, the declaration of a nontype template parameter can in some cases also start with the keyword `typename`:

```c++
template <typename T,                  // 类型参数
         typename T::Allocator *alloc> // 非类型参数
class List;
```

**Nontype template parameters are declared much like variables, but they cannot have nontype specifiers like `static`, `mutable`, and so forth. They can have `const` and `volatile` qualifiers, buf if such a qualifier appears at the outermost level of the parameter type, it is simply ignored.**

**nontype parameters are always rvalues: Their address cannot be taken, and they cannot be assigned to.**

Template template parameters are placeholders for class templates. They are declared much like class templates, but the keywords `struct` and `union` cannot be used.

Template arguments are the "values" that are substituted for template parameters when instantiating a template. These values can be determined using several different mechanisms:

- Explicit template arguments: A template name can be followed bny explicit template argument values enclosed in angle brackets. The resulting name is called a template-id.
- Injected class name: Within the scope of a class template `X` with template parameters `P1`, `P2`, ..., the name of that template(`X`) can be equivalent to the template-id `X<P1, P2, ...>`. 
- Default template arguments: Explicit template arguments can be omitted from class template instances if default template arguments are available. However, even if all template parameters have a default value, the (possibly empty) angle brackets must be provided.
- Argument deduction: Function template arguments that are not explicitly specified may be deduced from the tyes of the function call arguments in a call.

Template arguments for a function template can be specified explicitly or deduced from the way the template is used.

```c++
template <typename Func, typename T>
void apply(Func f, T x) {
    f(x);
}

template <typename T> void multi(T t) {
    cout << 1 << ": " << t << endl;
}

template <typename T> void multi(T *t) {
    cout << 2 << ": " << *t << endl;
}

int i = 3;
apply(&multi<int>, i); // 这里应该产生二义性
```

This "substitution-failure-is-not-an-error"(SFINAE) principle is clearly an important ingredient to make the overloading of function templates practical. However, it also enables remarkable compile-time techniques.

Template type arguments are the "values" specified for template type parameters. Most commonly used types can be used as template arguments, but there are two exceptions:

- Local classes and enumerations(in other words, types declared in a function definition) cannot be involved in template type arguments.
- Types that involve unnamed class types or unnamed enumeration types cannot be template type arguments(unnamed classes or enumerations that are given a name through a typedef declaration are OK).

Nontype template arguments are the values substituted for nontype parameters. Such a value must be one of the following things:

- Another nontype template parameter that has the right type
- A compile-time constant value of integer(or enumeration) type. This is acceptable only if the corresponding parameter has a type that matches that of the value, or a type to which the value can be implicitly converted(for example, a `char` can be provided for an `int` parameter).
- The name of an external variable or function precede3d by the built-in unary `&` ("address of") operator. For functions and array variables, `&` can be left out. Such template arguments match nontype parameters of a pointer type.
- The previoous kind of argument but without a leading `&` operator is a valid argument for a nontype parameter of reference type.
- A pointer-to-member constant; in other words, an expression of the form `&C::m` where `C` is a class type and `m` is a nonstatic member (data or function). This matches nontype parameters of pointer-to-member type only.

there are some constant values that are, perhaps surprisingly, not currently valid:

- Null pointer constants
- Floating-point numbers
- String literals

Two sets of template arguments are equivalent when values of the arguments are identical one-for-one.

This has two important consequences for class members:

1. A function generated from a member function template never overrides a virtual function.
2. A constructor generated from a constructor template is never a default copy constructor.(Similarly, an assignment generated from an assignment template is never a copy-assignment operator. However, this is less prone to problems because unlike copy constructors, assignment operators are never called implicitly.)

Friends:

1. A friend declaration may be the only declaration of an entity.
2. A friend function declaration can be definition.

If the name is not followed by angle brackets, there are two possibilities:

1. If the name isn't qualified (in other words, it doesn't contain a double colon), it never refers to a template instance. If no matching nontemplate function is visible at the point of the friend declaration, the friend declaration is the first declaration of that function. The declaration could also be a definition.
2. If the name is qualified (it contains `::`), the name must refer to a previously declared function or function template. A matching function is preferred over a matching function template. However, such a friend declaration cannot be a definition.

```c++
void multiply(void*); // 普通函数
template<typename T>  // 函数模板
void multiply(T);
class Comrades {
   friend void multiply(int){}    // 定义了一个新函数::multiply(int)
   friend void ::multiply(void*); // 受限名称，则是引用先前定义的普通函数
   friend void ::multiply(int);   // 引用template的一个实体
   friend void ::multiply<double*>(double*); // 带尖括号，一定是一个模板的实例，而且此时编译器必须见到了此template
   friend void ::error(){} // ERROR：受限的名称，一定是对已经存在的名称的引用
};
```

two different instantiations create two identical definitions-a direct violation of the ODR。

Friend Templates:

```c++
class Manager{
    template<typename T>
    friend int ticket(){}
};
```



## Glossary

<div style="width: 50%; float:left;">majority `/mə'dʒɒrəti/` 大多数，多数派</div>
<div style="width: 50%; float:left;">concise `/kən'saɪs/` 简明的，简要的</div>
<div style="width: 50%; float:left;">artificial `/ˌɑːtɪ'fɪʃl/` 人造的，虚伪的，武断的</div>
<div style="width: 50%; float:left;">stray `/streɪ/` 走失，漫不经心地移动，偏离正题，有外遇，流浪的</div>
<div style="width: 50%; float:left;">instantiation `/ɪnstænʃɪ'eɪʃən/` 示例</div>
<div style="width: 50%; float:left;">clause `/klɔːz/` 条款，从句，子句</div>
<div style="width: 50%; float:left;">outermost `/'aʊtəməʊst/` 最外方的，离中心最远的</div>
<div style="width: 50%; float:left;">nested `/nestɪd/` 嵌套的</div>
<div style="width: 50%; float:left;">contrast `/'kɒntrɑːst/` 对比，差别，对照，反差</div>
<div style="width: 50%; float:left;">linkage `/'lɪŋkɪdʒ/` 链接，联系，链接，结合</div>
<div style="width: 50%; float:left;">introductory `/ˌɪntrə'dʌktəri/` 介绍的，前言的，序文的</div>
<div style="width: 50%; float:left;">refer `/rɪ'fɜː(r)/` 参考，归类，归因</div>
<div style="width: 50%; float:left;">comma `/ˈkɒmə/` 逗号，停顿，间歇</div>
<div style="width: 50%; float:left;">denote `/dɪˈnəʊt/` 标志，象征，表示，预示</div>
<div style="width: 50%; float:left;">imply `/ɪmˈplaɪ/` 含有...的意思，暗示，暗指，说明，表明，使必要</div>
<div style="width: 50%; float:left;">elaborate `/ɪˈlæbərət/` 精巧的，苦心经营的，详细描述的，详尽的，复杂的</div>
<div style="width: 50%; float:left;">mechanism `/'mekənɪzəm/`  机制，原理，结构，机构</div>
<div style="width: 50%; float:left;">colon `/'kəʊlən/` 冒号，结肠</div>
<div style="width: 50%; float:left;">subsequent `/ˈsʌbsɪkwənt/` 随后的，后来的，之后的</div>
<div style="width: 50%; float:left;">omitted `/əʊ'mɪtɪd/` 省略了的</div>
<div style="width: 50%; float:left;">unambiguous `/ˌʌnæm'bɪɡjuəs/` 不含糊的，清楚的</div>
<div style="width: 50%; float:left;">convenient `/kənˈviːnɪənt/` 实用的，方便的，公共设施</div>
<div style="width: 50%; float:left;">ellipsis `/ɪ'lɪpsɪs/` 省略，省略号</div>
<div style="width: 50%; float:left;">precede `/prɪ'siːd/` 在...之前，先于，领先</div>
<div style="width: 50%; float:left;">unary `/ˈjuːnəri/` 一元（数学名词），单项的</div>
<div style="width: 50%; float:left;">leading `/'liːdɪŋ/` 领导的，指导的，主要的，在前的</div>
<div style="width: 50%; float:left;">compatible `/kəmˈpatɪb(ə)l/` 兼容的，一致的</div>
<div style="width: 50%; float:left;">notion `/'nəʊʃn/` 观念，概念，想法，主张</div>
<div style="width: 50%; float:left;">cumbersome `/ˈkʌmbəs(ə)m/` 笨重的，累赘的</div>
<div style="width: 50%; float:left;">substitute `/'sʌbstɪtjuːt/` 代替，替代品，替补队员</div>
<div style="width: 50%; float:left;">satisfactory `/ˌsætɪs'fæktəri/` 令人满意的</div>
<div style="width: 50%; float:left;">syntactical `/sɪn'tæktɪkəl/` 依照句法的</div>
<div style="width: 50%; float:left;">observation `/ˌɒbzə'veɪʃn/` 观察力，注意，评论</div>
<div style="width: 50%; float:left;">prone `/prəʊn/` 易于...的，有...倾向的，俯卧的</div>
<div style="width: 50%; float:left;">ability `/ə'bɪləti/` 能力，才能</div>
<div style="width: 50%; float:left;">hence `/hens/` 因此，从此以后</div>
<div style="width: 50%; float:left;">participate `/pɑːˈtɪsɪpeɪt/` 参加，参与，分享</div>
<div style="width: 50%; float:left;">violation `/ˌvaɪə'leɪʃn/` 违反，违背，妨碍</div>
<div style="width: 50%; float:left;">ordinary `/ˈɔːdnri/` 法官，普通的，一般的，平常的</div>
<div style="width: 50%; float:left;">nonetheless `/ˌnʌnðə'les/` 尽管如此(仍然)</div>
<div style="width: 50%; float:left;">facility `/fəˈsɪləti/` 特色，设备，设施，天才，天赋</div>