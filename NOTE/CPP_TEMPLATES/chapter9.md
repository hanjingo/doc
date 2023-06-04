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

<div style="width: 50%; float:left;"></div>
<div style="width: 50%; float:left;"></div>
<div style="width: 50%; float:left;"></div>
<div style="width: 50%; float:left;"></div>
<div style="width: 50%; float:left;"></div>
<div style="width: 50%; float:left;"></div>
<div style="width: 50%; float:left;"></div>
<div style="width: 50%; float:left;"></div>
<div style="width: 50%; float:left;"></div>
