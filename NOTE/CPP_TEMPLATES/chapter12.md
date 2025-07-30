# Chapter 12. Specialization and Overloading

[TOC]



In the previous section, we saw that two function templates with the same name can coexist, even though they may be instantiated so that both have identical parameter types.

Two functions can coexist in a program if they have distinct signatures. We define the signature of a function as the following information:

1. The unqualified name of the function (or the name of the function template from which it was generated).
2. The class or namespace scope of that name and, if the name has internal linkage, the translation unit in which the name is declared.
3. The `const`, `volatile`, or `const volatile` qualification of the function(if it is a member function with such a qualifier).
4. The types of the function parameters (before template parameters are substituted if the function is generated from a function template).
5. Its return type, if the function is generated from a function template.
6. The template parameters and the template arguments, if the function is generated from a function template.

This means that the following templates and their instantiations could, in principle, coexist in the same program:

```c++
template<typename T1, typename T2>
void f1(T1, T2);

template<typename T1, typename T2>
void f1(T2, T1);

template<typename T>
long f2(T);

template<typename T>
char f2(T);
```

We then synthesize two artificial lists of argument types (or for conversion function templates, a return type) by substituting every template parameter as follows:

1. Replace each template type parameter with a unique "made-up" type.
2. Replace each template parameter with a unique "made-up" class template.
3. Replace each nontype template parameter with a unique "made up" value of the appropriate type.

Function templates can be overloaded with nontemplate functions. All else being equal, the nontemplate function is preferred in selecting the actual function being called.

A full specialization is introduced with a sequence of three tokens: `template`, `<` and `>`. In addition, the class name declarator is followed by the template arguments for which the specialization is declared.

The syntax and principles behind (explicit) full function template specialization are much the same as those for full class template specialization, but overloading and argument deduction come into play.

The full specialization declaration can omit explicit template arguments when the template being specialized can be determined via argument deduction (using as argument types the parameter types provided in the declaration) and partial ordering.

A full function template specialization cannot include default argument values. However, any default arguments that were specified for the template being specialized remain applicable to the explicit specialization.

A full specialization is in many ways similar to a normal declaration (or rather, a normal redeclaration). In particular, it does not declare a template, and therefore, only one definition of a non-inline full function template specialization should appear in a program. However, we must still ensure that a declaration of the full specialization follows the template to prevent attempts at using the function generated from the template. The declarations for template `g` in the previous example would therefore typically be organized in two files.

Not only member templates, but also ordinary static data members and member functions of class templates, can be fully specialized. The syntax requires `template<>` prefix for every enclosing class template. If a member template is being specialized, a `template<>` must also be added to denote that it is being specialized.

```c++
template<>
class Outer<bool>::Inner<wchar_t>{
    public:
    	enum{count = 2};
};
```

There exists a number of limitations on the parameter and argument lists of partial specialization declarations. Some of them are as follows:

1. The arguments of the partial specialization must match in kind (type, nontype, or template) the corresponding parameters of the primary template.
2. The parameter list of the partial specialization cannot have default arguments; the default arguments of the primary class template are used instead.
3. The nontype arguments of the partial specialization should either be nondependent values or plain nontype template parameters. They cannot be more complex dependent expressions like `2*N` (where `N` is a template parameter).
4. The list of template arguments of the partial specialization should not be identical (ignoring renaming) to the list of parameters of the primary template.

```c++
template<typename T, int I = 3>
class S;           // 基本模板

template<typename T>
class S<int, T>;   // 错误；参数类型不匹配

template<typename T = int>
class S<T, 10>;    // 错误；不能具有缺省实参

template<int I>
class S<int, I*2>; // 错误；不能有非类型的表达式

template<typename U, int K>
class S<U, K>;     // 错误；局部特化和基本模板之间没有本质的区别
```

`template metaprogramming:` Using the template instantiation mechanism to perform nontrivial computations at compile time.



## Glossary

<div style="width: 50%; float:left;">optimal `/ˈɒptɪməl/` 最优的，最佳的</div>
<div style="width: 50%; float:left;">transparent `/trænsˈpærənt/` 透明的，清澈的，显而易见的，易懂的</div>
<div style="width: 50%; float:left;">facility `/fəˈsɪləti/` 特色，设备，设施，天才，天赋</div>
<div style="width: 50%; float:left;">pragmatic `/præɡ'mætɪk/` 实用主义的，实际的</div>
<div style="width: 50%; float:left;">deviation `/ˌdiːvi'eɪʃn/` 偏差，偏离，出轨，背离</div>
<div style="width: 50%; float:left;">presumably `/prɪ'zjuːməbli/` 大概，据推测，可能</div>
<div style="width: 50%; float:left;">discriminate `/dɪ'skrɪmɪneɪt/` 区分，区别对待，辨别，差别对待
</div>
<div style="width: 50%; float:left;">transparent `/trænsˈpærənt/` 透明的，清澈的，显而易见的，易懂的</div>
<div style="width: 50%; float:left;">transparency `/træns'pærənsi/` 透明度，幻灯片</div>
<div style="width: 50%; float:left;">dramatic `/drəˈmætɪk/` 戏剧性的，巨大的，突然的，令人吃惊的</div>
<div style="width: 50%; float:left;">coexist `/ˌkəʊɪɡˈzɪst/` 共存，和平共处</div>
<div style="width: 50%; float:left;">indicate `/ˈɪndɪkeɪt/` 指示，说明，象征，显示，预示</div>
<div style="width: 50%; float:left;">substitute `/'sʌbstɪtjuːt/` 代替，替代品，替补队员</div>
<div style="width: 50%; float:left;">trivial `/'trɪviəl/` 琐碎的，不重要的</div>
<div style="width: 50%; float:left;">criterion `/kraɪ'tɪəriən/` 标准，准则</div>
<div style="width: 50%; float:left;">formal `/'fɔːml/` 正式的，正规的，形式的，拘谨的</div>
<div style="width: 50%; float:left;">accommodate `/əˈkɒmədeɪt/` 容纳，住宿，调解，向..提供，随和，乐于助人，顾及的</div>
<div style="width: 50%; float:left;">intuitive `/ɪn'tjuːɪtɪv/` 直觉的</div>
<div style="width: 50%; float:left;">ellipsis `/ɪ'lɪpsɪs/` 省略，省略号</div>
<div style="width: 50%; float:left;">synthesize `/'sɪnθəsaɪz/` 合成，综合</div>
<div style="width: 50%; float:left;">artificial `/ˌɑːtɪ'fɪʃl/` 人造的，虚伪的，武断的</div>
<div style="width: 50%; float:left;">versa `/versa/` 反，反的</div>
<div style="width: 50%; float:left;">intricate `/'ɪntrɪkət/` 复杂的，难懂的</div>
<div style="width: 50%; float:left;">tune `/tjuːn/` 曲调，曲子，（收音机）调谐</div>
<div style="width: 50%; float:left;">transparent `/trænsˈpærənt/` 透明的，清澈的，显而易见的，易懂的
</div>
<div style="width: 50%; float:left;">disambiguate `/ˌdɪsamˈbɪɡjʊeɪt/` 消除...的歧义</div>
<div style="width: 50%; float:left;">reinforce `/ˌriːɪnˈfɔːs/` 加强，加固，增援，支持</div>
<div style="width: 50%; float:left;">notion `/'nəʊʃn/` 观念，概念，想法，主张</div>
<div style="width: 50%; float:left;">via `/ˈvaɪə/` 通过，经由，凭借，经过（某一地方）</div>
<div style="width: 50%; float:left;">applicable `/ə'plɪkəbl/` 合适的，适用的，可应用的</div>
<div style="width: 50%; float:left;">prevent `/prɪˈvent/` 阻止，阻挠，阻碍，预防</div>
<div style="width: 50%; float:left;">attentive `/ə'tentɪv/` 注意的，留意的</div>
<div style="width: 50%; float:left;">contrast `/'kɒntrɑːst/` 对比，差别，对照，反差</div>
<div style="width: 50%; float:left;">combat `/'kɒmbæt/` 战斗，试图解决，与...斗争</div>
<div style="width: 50%; float:left;">bloat `/bləʊt/` 膨胀，肿胀的，自傲</div>
<div style="width: 50%; float:left;">legitimate `/lɪ'dʒɪtɪmət/` 合法的，世袭的，婚生的，正当的，合理的，授权，宣布...合法</div>
<div style="width: 50%; float:left;">brought `/brɔːt/` 拿来，带来</div>
<div style="width: 50%; float:left;">likelihood `/'laɪklihʊd/` 可能性</div>