# Chapter 9 Names in Templates


<!-- vim-markdown-toc GFM -->

<!-- vim-markdown-toc -->



| Classification         | Explanation and Notes                                        |
| ---------------------- | ------------------------------------------------------------ |
| Identifier             | A name that consists solely of an uninterrupted sequences of letters, underscores(`_`) and digits. It cannot start with a digit, and some identifiers are reserverd fro the implementation: You should not introduce them in your programs(as a rule of thumb, avoid leading underscores and double underscores). The concept of "letter" should be taken broadly and includes special universal character names (UCNs) that encode glyphs from nonalphabetical languages. |
| Operator-function-id   | The keyword `operator` followed by the symbol for an operator -- for example `operator new` and `operator []`. Many operators have alternative representations. For example, `operator &` can equivalently be written as `operator bit and` even when it denotes the unary address of operator. |
| Conversion-function-id | Used to denote user-defined implicit conversion operator -- for example `operator int &`, which could also be obfuscated as `operator int bit and`. |
| Template-id            | The name of a template followed by template arguments enclosed in angle brackets; for example, `List<T, int, 0>`(Strictly speaking, the C++ standard allows only simple identifiers for the template name of a template-id. However, this is probably an oversight and an operator-function-id should be allowed too; e.g. `operator+<X<int>>`.) |
| Unqualified-id         | The generalization of an identifier. It can be any of the above(identifier, operator-function-id, conversion-function-id or template-id) or a "destructor name"(for example, notations like `~Data` or `~List<T, T, N>`). |
| Qualified-id           | An unqualified-id that is qualified with the name of a class or namespace, or just with the global scope resolution operator. Note that such a name itself can be qualified. Examples are `::X`, `S::x`, `Array<T>::y`, and `::N::A<T>::z`. |
| Qualified name         | This term is not defined in the standard, but we use it to refer to names that undergo so-called `qualified lookup`. Specifically, this is a qualified-id or an unqualified-id that is used after an explicit member access operator (`.` or `->`). Examples are `S::x`, `this->f`, and `p->A::m`. However, just `class_mem` in a context that is implicitly equivalent to `this->class_mem` is not a qualified name: The member access must be explicit. |
| Unqualified name       | An unqualified-id that is not a qualified name. This is not a standard term but corresponds to names that undergo what the standard call `unqualified lookup`. |

*Table 9.1 Name Taxonomy(part one)*

| Classification    | Explanation and Notes                                        |
| ----------------- | ------------------------------------------------------------ |
| Name              | Either a qualified or an unqualified name.                   |
| Dependent name    | A name that depends in some way on a template parameter. Certainly any qualified or unqualified name that explicitly contains a template parameter is dependent. Furthermore, a qualified name that is qualified by a member access operator (`.` or `->`) is dependent if the type of the expression on the left of the access operator depends on a template parameter. In particular, `b` in `this->b` is a dependent name when it appears in a template. Finally, the identifier `ident` in a call of the form `ident(x, y, z)` is a dependent name if and only if any of the argument expressions has a type that depends on a template parameter. |
| Nondependent name | A name that is not a dependent name by the above description. |

*Table 9.2 Name Taxonomy(part two)*

A more recent twist to the lookup of unqualified names is that -- in addition to ordinary lookup -- they may sometimes undergo so-called argument-dependent lookup (ADL).

The precise definition of the set of associated namespaces and associated classes for a given type is determined by the following rules:

- For built-in types, this is the empty set.
- For pointer and array types, the set of associated namespaces and classes is that of the underlying type.
- For enumeration types, the associated namespace is the namespace in which the enumeration is declared. For class members, the enclosing class is the associated class.
- For class types (including union types) the set of associated classes is the type itself, the enclosing class, and any direct and indirect base classes. The set of associated namespaces is the namespaces in which the associated classes are declared. If the class is a class template instantiation, then they types of the template type arguments and the classes and namespaces in which the template arguments are declared are also included.
- For function types, the sets of associated namespaces and classes comprise the namespaces and classes associated with all the parameter types and those associated with the return type.
- For pointer-to-member-of-class-X types, the sets of associated namespaces and classes include those associated with `X` in addition to those associated with the type of the member. (If it is a pointer-to-member-function type, then the parameter and return types can contribute too.)

The name of a class is "injected" inside the scope of that class itself and is therefore accessible as an unqualified name in that scope.(However, it is not accessible as qualified name because this is the notation used to denote the constructors.

This is a consequence of the so-called `maximum munch` tokenization principle: A C++ implementation must collect as many consecutive characters as possible into a token.

The typename prefix to a name is reuired when the name:

1. Appears in template
2. Is qualified
3. Is not used as in a l;ist of base class specifications or in a list of member initializers introducing a constructor definition
4. Is dependent on a template parameter

A problem very similar to the one encountered in the previouse section occurs when a name of a template is dependent. In general, a C++ compiler is required to treat a `<` following the name of the name of a template as the beginning of a template argument list; otherwise, it is a "less than" operator. As is the case with type names, a compiler has to assume that a dependent name does not refer to a template unless the programmer provides extra information using the keyword `template`:

```c++
template <typename T>
class Shell {
public:
    template <int N>
    class In {
    public:
        template<int M>
        class Deep{
        public:
            virtual void f();
        };
    };
};

template<typename T, int N>
class Weird {
public:
    void case1(typename Shell<T>::template In<N>::template Deep<N>* p) {
        p->template Deep<6>::f(); // 抑制virtual call
    }
    void case2(typename Shell<T>::template In<N>::template Deep<N>& p) {
        p.template Deep<8>::f(); // 同上，且Deep<8>并不要求依赖于模板参数N
    }
};
```

Dependent Names in Using-Declarations:

```c++
template <typename T>
class BXT {
    public:
        typedef T Mystery;

        template<typename U>
        struct Magic;
};
```

ADL and Explicit Template Arguments:

```c++
template <typename T>
class DXTT : private BXT<T> {
    public:
        using BXT<T>::Mystery;      // 不必再写typename了
        using BXT<T>::Magic;        // 统一了using-declaration写法
        typename BXT<T>::Mystery m; // 使用typename很合情理，BXT<T>是依赖名称
        typename BXT<T>::template Magic<T> *plink; // 用::template显式的表示Magic是一个模板
};
```

In a class template, a nondependent base class is one with a complete type that can be determined without knowing the template arguments.

```c++
template <typename X>
class Base {
    public:
        int basefield;
        typedef int T;
};

template <typename T>
class D2 : public Base<double> {
    public:
        void f() {
            basefield = 7;
        }
        T strange; // 永远都是Base<double>::T即int类型
};

int main() {
    D2<char> d;
    cout << typeid(d.strange).name() << endl; // 永远输出int类型
}
```



## Glossary

<div style="width: 50%; float:left;">respect `/rɪ'spekt/` 方面，关系，尊敬，尊重，遵守，问候，敬意</div>
<div style="width: 50%; float:left;">sensitive `/'sensətɪv/` 敏感的，灵敏的，感光的，善解人意的</div>
<div style="width: 50%; float:left;">taxonomy `/tæk'sɒnəmi/` 分类，分类学</div>
<div style="width: 50%; float:left;">scope-resolution `//` （计算机）作用域解析运算符（::）</div>
<div style="width: 50%; float:left;">underscore `/ˌʌndəˈskɔː(r) /` 下划线，底线，强调</div>
<div style="width: 50%; float:left;">broadly `/'brɔːdli/` 概括地，大体上，广泛地，明白地，无礼貌地</div>
<div style="width: 50%; float:left;">glyph `/ɡlɪf/` 雕刻的文字，雕像，竖沟</div>
<div style="width: 50%; float:left;">obfuscate `/'ɒbfʌskeɪt/` 弄暗，使模糊，使困惑</div>
<div style="width: 50%; float:left;">enclose `/ɪnˈkləʊz/` 围住，圈起，附上，装入信封</div>
<div style="width: 50%; float:left;">intuitive `/ɪn'tjuːɪtɪv/` 直觉的</div>
<div style="width: 50%; float:left;">pathological `/ˌpæθə'lɒdʒɪkl/` 病理学的</div>
<div style="width: 50%; float:left;">twist `/twɪst/` 扭曲，弯曲，转动，旋转</div>
<div style="width: 50%; float:left;">motivate `/ˈməʊtɪveɪt/` 动机，激励，激发，原因</div>
<div style="width: 50%; float:left;">perennial `/pə'reniəl/` 永久的，反复出现的，多年生的
</div>
<div style="width: 50%; float:left;">unaware `/ˌʌnə'weə(r)/` 没有发觉的，不知道的</div>
<div style="width: 50%; float:left;">inhibited `/ɪn'hɪbɪtɪd/` 羞怯的，抑制情感的</div>
<div style="width: 50%; float:left;">precise `/prɪˈsaɪs/` 准确的，精确的，明确的，细致的</div>
<div style="width: 50%; float:left;">intuitive `/ɪn'tjuːɪtɪv/` 直觉的</div>
<div style="width: 50%; float:left;">comprise `/kəmˈpraɪz/` 包含，包括，构成，组成</div>
<div style="width: 50%; float:left;">injection `/ɪn'dʒekʃn/` 注入，注射，数学函数</div>
<div style="width: 50%; float:left;">controversial `/ˌkɒntrəˈvɜːʃl/` 有争议的</div>
<div style="width: 50%; float:left;">technique `/tɛkˈniːk/` 方法，技巧</div>
<div style="width: 50%; float:left;">notation `/nəʊ'teɪʃn/` 标记，表示法，记号</div>
<div style="width: 50%; float:left;">scope `/skəʊp/` （考试，活动）范围，机会，能力，仔细看，彻底检查</div>
<div style="width: 50%; float:left;">interprete `/ɪn'tɜːprɪt/` 口译，解释，翻译，诠释</div>
<div style="width: 50%; float:left;">perplex `/pəˈpleks/` 困惑，迷惑</div>
<div style="width: 50%; float:left;">diagnostic `/ˌdʌɪəɡˈnɒstɪk/` 症状，诊断程序，诊断法，诊断的</div>
<div style="width: 50%; float:left;">lexical `/'leksɪkl/` 词汇的，词典的</div>
<div style="width: 50%; float:left;">validly `/'vælɪdli/` 正当地，妥当地</div>
<div style="width: 50%; float:left;">gist `/dʒɪst/` 要点，主旨</div>
<div style="width: 50%; float:left;">delimit `/di'lɪmɪt/` 界定，划界</div>
<div style="width: 50%; float:left;">syntactic `/sɪnˈtaktɪk/` 句法的</div>
<div style="width: 50%; float:left;">spare `/speə(r)/` 备用的，闲置的，多余的，空闲的</div>
<div style="width: 50%; float:left;">caution `/'kɔːʃn/` 警告，劝告，戒备，慎重，吸引眼球地人或物</div>
<div style="width: 50%; float:left;">stumble `/ˈstʌmbl/` 绊倒，跌倒，失足，结结巴巴的</div>
<div style="width: 50%; float:left;">revision `/rɪ'vɪʒn/` 校订，修订本，修正，复习</div>
<div style="width: 50%; float:left;">munch `/mʌntʃ/`  用力咀嚼</div>
<div style="width: 50%; float:left;">digraph `/'daɪɡrɑːf/` 两字一音，合体字母</div>
<div style="width: 50%; float:left;">lack `/læk/` 缺乏，不足</div>
<div style="width: 50%; float:left;">corrupt `/kəˈrʌpt/` 贪污，腐败，不道德的，破坏，损坏</div>
<div style="width: 50%; float:left;">promote `/prə'məʊt/` 提升，促进，促销</div>
<div style="width: 50%; float:left;">precede `/prɪ'siːd/` 在...之前，先于，领先</div>
<div style="width: 50%; float:left;">intricate `/'ɪntrɪkət/` 复杂的，难懂的</div>
<div style="width: 50%; float:left;">sprinkle `/'sprɪŋkl/` 洒，撒，下稀疏小雨，少量散布的屑状物</div>
<div style="width: 50%; float:left;">symbolic `/sɪm'bɒlɪk/` 象征的，符号的，代号</div>
<div style="width: 50%; float:left;">nominate `/'nɒmɪneɪt/` 提名，指派</div>
<div style="width: 50%; float:left;">perceive `/pə'siːv/` 注意到，觉察到，认为，理解</div>
<div style="width: 50%; float:left;">snippet `/ˈsnɪpɪt/` 小部分，片段，一则（新闻），一小段（谈话），一小条（消息）</div>
<div style="width: 50%; float:left;">conversely `/'kɒnvɜːsli/` 相反地</div>
<div style="width: 50%; float:left;">scenario `/sɪˈnɑː.ri.əʊ/` 可能发生的事态，设想，剧本，情节，情况</div>
<div style="width: 50%; float:left;">counterintuitive `/kaʊntərɪn'tjuːɪtɪv/` 违反直觉的</div>
<div style="width: 50%; float:left;">eagerly `/ˈiːɡəli/` 热切的，渴望地，急切的，兴奋的</div>
<div style="width: 50%; float:left;">circumvent `/ˌsɜːkəm'vent/` 绕行，避开，围住</div>
<div style="width: 50%; float:left;">clutter `/'klʌtə(r)/` 弄乱，混乱，杂乱</div>
<div style="width: 50%; float:left;">advocate `/'ædvəkeɪt/` 提倡，主张，拥护者，提倡者，律师，辩护者</div>
<div style="width: 50%; float:left;">perception `/pə'sepʃn/` 观念，洞察力，认识能力</div>
<div style="width: 50%; float:left;">parenthesis `/pə'renθəsɪs/` 圆括号，插入语</div>
<div style="width: 50%; float:left;">brace `/breɪs/` 大括号，吊带，背带，支撑，绷紧，防备，支柱，支架，一对</div>
<div style="width: 50%; float:left;">proposal `/prəˈpəʊ.zə/` 建议，计划，提案，求婚</div>
<div style="width: 50%; float:left;">nontrivial `/'nɒn'trɪvɪəl/` 非平凡的，重要的</div>
<div style="width: 50%; float:left;">incorporate `/ɪn'kɔːpəreɪt/` 合并，组建公司，合成一体
</div>
<div style="width: 50%; float:left;">transition `/træn'zɪʃn/` 转换，转变</div>
<div style="width: 50%; float:left;">reattempt `/'riːə'tempt/` 再尝试，重新尝试</div>
<div style="width: 50%; float:left;">ironically `/aɪ'rɒnɪkli/` 讽刺地，说反话地</div>
<div style="width: 50%; float:left;">wise `/waɪz/` 明智的，英明的，有见识的</div>
<div style="width: 50%; float:left;">primary `/'praɪməri/` 主要的，首要的，初级的，要素</div>
<div style="width: 50%; float:left;">esthetic `/es'θetɪk/` 审美观，审美的，美学，美学的</div>
<div style="width: 50%; float:left;">awkward `/'ɔːkwəd/` 尴尬的，笨拙的，别扭的</div>
<div style="width: 50%; float:left;">unwieldy `/ʌnˈwiːldi/` 笨重的，笨手笨脚的，不灵巧的</div>
<div style="width: 50%; float:left;">accommodate `/əˈkɒmədeɪt/` 容纳，住宿，调解，向..提供，随和，乐于助人，顾及的
</div>