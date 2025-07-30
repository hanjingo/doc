# Chapter 13. Future Directions

[TOC]



The second typedef declaration is an error because the two closing angle brackets with no intervening blank space constitute a "right shift" (`>>`) operator, which makes no sense at that location in the source.

```c++
typedef std::vector<std::list<int> > a; // 正确
typedef std::vector<std::list<int>> b;  // 错误(以后可能会取消此限制)
```

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

it is possible to specify explicitly function template arguments that cannot be deduced. Hence, would be entirely natural to specify default values for those nondeducible template arguments.

```c++
template<typename T1 = int, typename T2>
class Bad;
Bad<int>* b; // int替换的是T1还是T2？
```

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

Class templates are often combined in relatively sophisticated ways to obtain other parameterized types. When such parameterized types appear repeatedly in source code, it is natural to want a shortcut for them, just as typedefs provide a shortcut for unparameterized types.

```c++
template<typename T>
typedef vector<list<T> > T1;

T1<int> li; // li的类型为：vector<lsit<int> >
```

in parctice there are a number of limitations:

- It is possible to specialize member templates of a class without changing the definition of that class. However, adding an overloaded member does require a change in the definition of a class. In many cases this is not an option because we may not own the rights to do so. Furthemore, the C++ standard does not currently allow us to add new templates to the `std` namespace, but it does allow us to specialize templates from that namespace.
- To overload function templates, their function parameters must differ in some material way. Consider a function template `R convert(T const&)` where `R` and `T` are template parameters. We may very well want to specialize this template for `R = void`, but this cannot be done using overloading.
- Code that is valid for a nonoverloaded function may no longer be valid when the function is overloaded. Specifically, given two function templates `f(T)` and `g(T)` (where `T` is a template parameter), the expression `g(&f<int>)` is valid only if `f` is not overloaded (otherwise, there is no way to decide which `f` is meant).
- Friend declarations refer to specific function tempalte or an instantiation of a specific function template. A overloaded version of a function template would not automatically have the privileges granted to the origin template.

Thd tyepof Operator:

```c++
template<typename T1, typename T2>
Array<???> operator+ (Array<T1> const& x, Array<T2> const& y);
```

Named Template Arguments:

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

Static Properties:

```c++
#include <iostream>
int main()
{
    std::cout << std::type<int>::is_bit_copyable << '\n';
    std::cout << std::type<int>::is_union << '\n';
}
```

Custom Instantiation Diagnostics:

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

It is entirely possible to imagine that class templates could be overloaded on their template parameters.

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

A need that shows up sometimes is the ability to pass a list of types as a single template argument. Usually, this list meant for one of two purpose: declaring a function with a parameterized number of parameters or defining a type struct with a parameterized list of members.

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

A fairly common template programming challenge is to declare an array of bytes that will be sufficiently large (but no excessively so) to hold an object of an as yet unknown type `T` -- in other words, a template parameter. One application of thist is the so-called discriminated unions (also called variant types or tagged unions):

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

Initializer Deduction:

```c++
template<typename T>
class Complex {
    public:
    	Complex(T const& re, T const& im);
};

Complex<> z(1.0, 3.0);
```

The idea here is that we can introduce a function expression with a special token `$` followed by parameter types in parentheses and a brace-enclosed body. Within such a construct, we can refer to the parameters with the special notation `$n`, when `n` is a constant indicating the number of the parameter.

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



## Glossary

<div style="width: 50%; float:left;">consistency `/kənˈsɪstənsi/` 一致性，连贯性，平滑度，坚实度，粘稠度</div>
<div style="width: 50%; float:left;">orthogonality `/ɔːθɒgə'nælɪtɪ/` 正交性，相互垂直</div>
<div style="width: 50%; float:left;">consecutive `/kənˈsekjətɪv/` 连续的，连续不断的</div>
<div style="width: 50%; float:left;">silent `/'saɪlənt/` 安静的，沉默的，无言的，不吵闹的</div>
<div style="width: 50%; float:left;">occurrence `/əˈkʌrəns/` 发生的事，存在情况</div>
<div style="width: 50%; float:left;">elaborate `/ɪˈlæbərət/` 精巧的，苦心经营的，详细描述的，详尽的，复杂的</div>
<div style="width: 50%; float:left;">extraneous `/ɪk'streɪniəs/` 外来的，无关的</div>
<div style="width: 50%; float:left;">trailing `/'treɪlɪŋ/` 蔓生的，拖尾</div>
<div style="width: 50%; float:left;">hindsight `/'haɪndsaɪt/` 事后聪明，后见之明，照门（枪的瞄准器）</div>
<div style="width: 50%; float:left;">literal `/ˈlɪtərəl/` 常量，字面值，文学的，书面的，字面上的</div>
<div style="width: 50%; float:left;">intuitive `/ɪn'tjuːɪtɪv/` 直觉的</div>
<div style="width: 50%; float:left;">awkward `/'ɔːkwəd/` 尴尬的，笨拙的，别扭的</div>
<div style="width: 50%; float:left;">feasible `/'fiːzəbl/` 可行的，可能的</div>
<div style="width: 50%; float:left;">commentator `/'kɒmənteɪtə(r)/` 评论员，解说员，注释者
</div>
<div style="width: 50%; float:left;">overwhelming `/ˌəʊvə'welmɪŋ/` 压倒性的，势不可挡的</div>
<div style="width: 50%; float:left;">wrinkle `/ˈrɪŋkl/` 皱纹，起皱，方法</div>
<div style="width: 50%; float:left;">uncommon `/ʌn'kɒmən/` 不寻常的，不常见的，极度的</div>
<div style="width: 50%; float:left;">exactly `/ɪɡ'zæktli/` 精确地，准确地，完全的，严密的
</div>
<div style="width: 50%; float:left;">respect `/rɪ'spekt/` 方面，关系，尊敬，尊重，遵守，问候，敬意</div>
<div style="width: 50%; float:left;">arguable `/'ɑːɡjuəbl/` 可辩论的，可论证的</div>
<div style="width: 50%; float:left;">sophisticate `/səˈfɪstɪkət/` 老练的，精密的，复杂的，老于世故的人，使...更精确</div>
<div style="width: 50%; float:left;">designer `/dɪ'zaɪnə(r)/` 设计者</div>
<div style="width: 50%; float:left;">concrete `/ˈkɒŋkriːt/` 具体的，实体的，混凝土，水泥，实质性的，凝结，结合</div>
<div style="width: 50%; float:left;">arbitrary `/ˈɑːbɪtrəri/` 任意的，武断的，随心所欲的，专制的</div>
<div style="width: 50%; float:left;">adequate `/'ædɪkwət/` 足够的，适当的，能够胜任的</div>
<div style="width: 50%; float:left;">differ `/ˈdɪfə/` 有区别，持不同看法</div>
<div style="width: 50%; float:left;">granted `/'ɡrɑːntɪd/` 的确，假定</div>
<div style="width: 50%; float:left;">syntax `/ˈsɪntæks/` 语法，句法</div>
<div style="width: 50%; float:left;">poster `/'pəʊstə(r)/` 海报，装饰画，广告</div>
<div style="width: 50%; float:left;">reminiscent `/ˌremɪ'nɪsnt/` 怀旧的，引人联想的，回忆着，回忆录作者</div>
<div style="width: 50%; float:left;">radical `/'rædɪkl/` 根本的，彻底的，激进的，激进分子</div>
<div style="width: 50%; float:left;">covariant `/kəʊ'veəriənt/` 协变的，协变式</div>
<div style="width: 50%; float:left;">promotion `/prə'məʊʃn/` 提升，促进，晋升，促销</div>
<div style="width: 50%; float:left;">propose `/prəˈpəʊz/` 提议，求婚，打算</div>
<div style="width: 50%; float:left;">sake `/seɪk/` 理由，缘故，目的，利益</div>
<div style="width: 50%; float:left;">syntactic `/sɪnˈtaktɪk/` 句法的</div>
<div style="width: 50%; float:left;">verbose `/vɜː'bəʊs/` 罗嗦的，冗长的</div>
<div style="width: 50%; float:left;">omit `/ə(ʊ)ˈmɪt/` 删掉，漏掉，省略，遗漏</div>
<div style="width: 50%; float:left;">categorize `/'kætəɡəraɪz/` 分类</div>
<div style="width: 50%; float:left;">optimal `/ˈɒptɪməl/` 最优的，最佳的</div>
<div style="width: 50%; float:left;">commonplace `/'kɒmənpleɪs/` 平凡的，普通的，老生常谈的</div>
<div style="width: 50%; float:left;">sought `/sɔːt/` 搜索</div>
<div style="width: 50%; float:left;">smooth `/smuːð/` 光滑的，平稳的，流畅的，圆滑的，可口的</div>
<div style="width: 50%; float:left;">opaque `/əʊˈpeɪk/` 不透明的，浑浊的，难懂，模糊，隐晦</div>
<div style="width: 50%; float:left;">envision `/ɪnˈvɪʒn/` 想象</div>
<div style="width: 50%; float:left;">feasible `/'fiːzəbl/` 可行的，可能的</div>
<div style="width: 50%; float:left;">dummy `/ˈdʌmi/` 假的，仿制品，笨蛋，傀儡</div>
<div style="width: 50%; float:left;">tentatively `/'tentətɪvli/` 试验性地，犹豫不决地，暂时地</div>
<div style="width: 50%; float:left;">furthermore `/ˌfɜːðəˈmɔː(r)/` 此外，而且，再者</div>
<div style="width: 50%; float:left;">precondition `/ˌpriːkən'dɪʃn/` 先决条件，前提</div>
<div style="width: 50%; float:left;">arbitrary `/ˈɑːbɪtrəri/` 任意的，武断的，随心所欲的，专制的</div>
<div style="width: 50%; float:left;">cause `/kɔːz/` 引起，原因，理由</div>
<div style="width: 50%; float:left;">recursion `/rɪ'kɜːʃn/` （计算机）递归，循环</div>
<div style="width: 50%; float:left;">fairly `/ˈfeəli/` 公平的</div>
<div style="width: 50%; float:left;">excessive `/ɪk'sesɪv/` 过分的，过多的</div>
<div style="width: 50%; float:left;">discriminate `/dɪ'skrɪmɪneɪt/` 区分，区别对待，辨别，差别对待</div>
<div style="width: 50%; float:left;">heuristic `/hju'rɪstɪk/` （教学）启发式的，探索的</div>
<div style="width: 50%; float:left;">impose `/ɪmˈpəʊz/` 强制执行，推行，强迫，利用</div>
<div style="width: 50%; float:left;">desire `/dɪˈzaɪər/` 渴望，愿望，性欲</div>
<div style="width: 50%; float:left;">compact `/ˈkɑːmpækt/` 小巧的，紧凑的，紧密的，合约，协定，压实，小型汽车</div>
<div style="width: 50%; float:left;">synonym `/ˈsɪnənɪm/` 同义词</div>
<div style="width: 50%; float:left;">redundant `/rɪˈdʌndənt/` 冗余的，多余的，不需要的</div>
<div style="width: 50%; float:left;">elegant `/'elɪɡənt/` 优雅的，雅致的</div>
<div style="width: 50%; float:left;">precise `/prɪˈsaɪs/` 准确的，精确的，明确的，细致的</div>
<div style="width: 50%; float:left;">concise `/kən'saɪs/` 简明的，简要的</div>
<div style="width: 50%; float:left;">brace `/breɪs/` 大括号，吊带，背带，支撑，绷紧，防备，支柱，支架，一对</div>
<div style="width: 50%; float:left;">proposal `/prəˈpəʊ.zə/` 建议，计划，提案，求婚</div>
<div style="width: 50%; float:left;">tackle `/ˈtækl/` 解决，应付，处理，阻断，阻截，渔具</div>
<div style="width: 50%; float:left;">conceivable `/kənˈsiːvəbl/` 可想到的</div>
<div style="width: 50%; float:left;">albeit `/ˌɔːl'biːɪt/` 虽然（即使）</div>
<div style="width: 50%; float:left;">premature `/ˈpremətʃə(r)/` 早产的，早熟的，仓促的</div>
<div style="width: 50%; float:left;">preliminary `/prɪˈlɪmɪnəri/` 初步的，预备的，开始的</div>
<div style="width: 50%; float:left;">embarrassment `/ɪm'bærəsmənt/` 困窘，尴尬，难堪</div>