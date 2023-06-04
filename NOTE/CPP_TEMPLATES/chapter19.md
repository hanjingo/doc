# Chapter 19. Type Classification

<!-- vim-markdown-toc GFM -->

<!-- vim-markdown-toc -->



It is sometimes useful to be able to know whether a template parameter is a built-in type, a pointer type, or a class type, and so forth. 

Compound types are types constructed from other types. Simple compound types include plain types, pointer types, reference types, and even array types.

The problem with function types is that because of the arbitrary number of parameters, there isn't a finite syntactic construct using template parameters that describes them all:

- provide partial specializations for functions with a template argument list that is shorter than a chosen limimt

  ```c++
  template<typename R>
  class Compoud<R()>{...} // 类似的一系列特化
  
  template<typename R, typename P1>
  class Compoud<R(P1, ...)>{...} // 类似的一系列特化
  ```

- uses the SFINAE(substitution-failure-is-not-an-error) principle: An overloaded function template can be followed by explicit template arguments that are invalid for some of the templates:

  ```c++
  template<typename U> static char test(...);
  template<typename U> static int test(U(*)[1]);
  enum {Yes = sizeof(test<T>(0) == 1)};s
  ```

Overload resolution is the process that selects among various functions with a same based on the types of their arguments. As shown shortly, we can determine the outcome of a case of overload resolution without actually evaluating a function call. This is useful to test whether a particular implicit conversion exists. The implicit conversion that interests us particularly is the conversion from an enumeration type to an integral type: It allows us to identify enumeration types.

Another approach is to proceed by elimination: if a type is not a fundamental type, not an enumeration type, and not a compound type, it must be a class type. The following straightforward template implements this idea:

```c++
enum {
    Yes = IsFundaT<T>::No &&
        !CompoundT<T>::IsRefT &&
        !CompoundT<T>::IsPtrT && 
        !CompoundT<T>::IsPtrMemT &&
        sizeof(enum_check(ConsumeUDC<T>())) == 1
};
```



## Glossary

<div style="width: 50%; float:left;">sophisticated `/sophisticated/` 老练的，精密的，复杂的，久经世故的</div>
<div style="width: 50%; float:left;">fundamental `/ˌfʌndə'mentl/` 基础，基本原理，基本的，根本的</div>
<div style="width: 50%; float:left;">synonym `/'sɪnənɪm/` 近义词</div>
<div style="width: 50%; float:left;">ultimate `/'ʌltɪmət/` 根本的，最终的，极限的，极品</div>
<div style="width: 50%; float:left;">partial `/'pɑːʃl/` 部分的，偏袒的，偏爱的</div>
<div style="width: 50%; float:left;">watchful `/'wɒtʃfl/` 警惕的，注意的</div>
<div style="width: 50%; float:left;">finite `/finite/` 有限的</div>
<div style="width: 50%; float:left;">syntactic `/sɪn'tæktɪk/` 句法的</div>
<div style="width: 50%; float:left;">shortcoming `/'ʃɔːtkʌmɪŋ/` 缺点，短处</div>
<div style="width: 50%; float:left;">convertible `/kən'vɜːtəbl/` 可转变的，同意义的，敞篷车</div>
<div style="width: 50%; float:left;">integral `/'ɪntɪɡrəl/` （数学）积分，完整的</div>
<div style="width: 50%; float:left;">ellipsis `/ɪ'lɪpsɪs/` 省略，省略号</div>
<div style="width: 50%; float:left;">promotion `/prə'məʊʃn/` 提升，促进，促销</div>
<div style="width: 50%; float:left;">ally `/'ælaɪ/` 结盟，同盟国，伙伴</div>
<div style="width: 50%; float:left;">albeit `/ˌɔːl'biːɪt/` 虽然（即使）</div>
<div style="width: 50%; float:left;">suboptimal `/'sʌb'ɒptɪməl/` 不是最理想的，未达最佳标准的</div>
<div style="width: 50%; float:left;">notable `/'nəʊtəbl/` 显著的，著名的，名人</div>
<div style="width: 50%; float:left;">incorporated `/ɪn'kɔːpəreɪtɪd/` 合并，组建公司，合成一体</div>
<div style="width: 50%; float:left;">basis `/'beɪsɪs/` 基础，根据</div>