# Chapter2 Function Templates



Function templates provide a functional behavior that can be called for different types.

The following is a function template that returns the maximum of two values:

```c++
template<typename T>
inline T const& max(T const& a, T const& b)
{
    return a < b ? b : a;
}
```

Thus Follow example, templates are compiled twice:

```c++
std::complex<float> c1, c2; // doesn't provide operator <
...
max(c1, c2); // ERROR at compile time
```

1. Without instantiation, the template code itself is checked for correct syntax. Syntax errors are discovered, such as missing semicolons.

2. At he time of instantiation, the template code is checked to ensure that all calls are valid. Invalid calls are discovered, such as unsupported function calls.

Function templates have two kinds of parameters:

1. Template parameters, which are declared in angle brackets before the function template name:

   ```c++
   template<typename T>
   ```

2. Call parameters, which are declared in parentheses after the function template name:

   ```c++
   max(T const& a, T const& b)
   ```

specify the template argument list explicitly:

1. in function templates(unlike class templates) no default template arguments can be specified.

   ```c++
   template <typename T1, typename T2, typename RT>
   inline RT max(T1 const& a, T2 const& b);
   max<int, double, double>(4, 4, 2);
   ```

2. instantiate a template explicitly for certain types:

   ```c++
   template<typename RT, typename T1, typename T2>
   inline RT max(T1 const& a, T2 const& b);
   max<double>(4, 4.2);
   ```

Like ordinary functions, function templates can be overloaded. That is, you can have different function definitions with the dame function name so that when that name is used in a function call, a C++ compiler must decide which one of the various candidates to call:

```c++
inline int const& max(int const& a, int const& b)
{
    return a < b ? b : a;
}

template <typename T>
inline T const& max(T const& a, T const& b)
{
    return a < b ? b : a;
}

template <typename T>
inline T const& max(T const& a, T const& b, T const& c)
{
    return ::max(::max(a, b), c);
}
```



## Summary

- Template functions define a family of functions for different template arguments.
- When you pass template arguments, function templates are instantiated for these argument types.
- You can explicitly qualify the template parameters.
- You can overload function templates.
- When you overload function templates, limit your changes to specifying template parameters explicitly.
- Make sure you see all overloaded versions of function templates before you call them.



## Glossary

<div style="width: 50%; float:left;">undetermined `/'ʌndɪ'tɜːmɪnd/` 待定的，缺乏判断力的</div>
<div style="width: 50%; float:left;">comma `/'kɒmə/` 逗号，停顿，间歇</div>
<div style="width: 50%; float:left;">bracket `/'brækɪt/` 括号，档次，支架，支撑，放入括号内</div>
<div style="width: 50%; float:left;">convention `/kən'venʃn/` 大会，协定，惯例，公约</div>
<div style="width: 50%; float:left;">arbitrary `/'ɑːbɪtrəri/` 任意的，专制的，武断的，霸道的</div>
<div style="width: 50%; float:left;">prior `/'praɪə(r)/` 优先的，更重要的，在前</div>
<div style="width: 50%; float:left;">semantically `/sɪ'mæntɪkli/` 语义上的</div>
<div style="width: 50%; float:left;">misleading `/ˌmɪs'liːdɪŋ/` 令人误解的</div>
<div style="width: 50%; float:left;">ambiguity `/ˌæmbɪ'ɡjuːəti/` 摸棱两可，含糊不清</div>
<div style="width: 50%; float:left;">conceivable `/kən'siːvəbl/` 想得到的，可想像的</div>
<div style="width: 50%; float:left;">parentheses `/pə'renθəsiːz/` 圆括号</div>
<div style="width: 50%; float:left;">glitch `/ɡlɪtʃ/` 小故障，小失误</div>
<div style="width: 50%; float:left;">hindrances `/'hɪndrəns/` 起妨碍作用的（人/物）</div>
<div style="width: 50%; float:left;">tricky `/'trɪki/` 棘手的，狡猾的，巧妙的</div>
<div style="width: 50%; float:left;">ordinary `/'ɔːdnri/` 平凡的，普通的，平淡的</div>
<div style="width: 50%; float:left;">approach `/ə'prəʊtʃ/` 靠近，途径，方法，接洽，要求，达到，动手处理</div>
<div style="width: 50%; float:left;">coexist `/ˌkəʊɪɡ'zɪst/` 共存，共处</div>
<div style="width: 50%; float:left;">visible `/'vɪzəbl/` 可见的，显而易见的</div>
<div style="width: 50%; float:left;">thumb `/θʌm/` 拇指，搭便车手势，翻阅</div>