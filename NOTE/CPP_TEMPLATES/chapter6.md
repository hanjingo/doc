# Chapter6 Using Template in Practice

<!-- vim-markdown-toc GFM -->

<!-- vim-markdown-toc -->



Most C and C++ programmers organize their nontemplate code largely as follows:

- Classes and other types are entirely placed in header files. Typically, this is a file with a `.hpp`(or `.H`, `.h`, `.hh`, `.hxx`)filename extension.
- For global variables and (noninline) functions, only a declaration is put in a header file, and the definition goes into a so-called dot-C file. Typically, this is a file with a `.cpp`(or `.C`, `.c`, `.cc`, or `.hxx`) filename extension.

inclusion model: We include the definitions of a template in the header file that declares that template.

Example of Explicit Instantiation:

```c++
template class Stack<int>;                      // 显式实例化类模板
template Stack<int>::Stack();                   // 显式实例化类模板的成员函数
template void PrintType<double>(double const&); // 显式实例化函数模板
```

In principle, it is quite simple to make use of the export facility: Define the template in just one file, and mark that definition and all its nondefining declarations with the keyword export.

However, note that the keyword export cannot be combined with inline and must always precede the keyword template.

Both function templates and inline functions can be defined in multiple translation units. This is usually achieved by placing the definition in a header file that is included by multiple dot-C files.

Debugging Templates:

- In this section, we deal mostly with the constraints that lead to compilation errors when violated, and we call these constraints `syntactic constraints`.
- The other kind of constraint we call `semantic constraints`, For example, we may require that there be a `<`operator defined on a template type parameter(which is a syntactic constraint), but usually we'll also require that the operator actually defines some sort of ordering on its domain(which is a semantic constraint).

Instantiated template code can result in very long symbols.

The organization of source code in header files and dot-C files is a practical consequence of various incarnations of the so-called one-definition rule or ODR.



## Summary

- Templates challenge the classic compiler-plus-linker model. Therefore there are different approaches to organize template code: the inclusion model, explicit instantiation, and the separation model.
- Usually, you should use the inclusion model (that is, put all template code in header files).
- By separating template code into different header files for declarations and definitions, you can ore easily switch between the inclusion model and explicit instantiation.
- The C++ standard defines a separate compilation model for templates(using the keyword export). It is not yet widely available, however.
- Debugging code with templates can be challenging.
- Template instances may have very long names.
- To take advantage of precompiled headers, be sure to keep the same order for `#include` directives.



## Glossary

<div style="width: 50%; float:left;">oversimplification `/ˌəʊvəˌsɪmplɪfɪ'keɪʃn/` 过度简化</div>
<div style="width: 50%; float:left;">practicality `/ˌpræktɪ'kæləti/` 实用，实际，可行性</div>
<div style="width: 50%; float:left;">delving `/delv/` 探究，挖掘，搜索</div>
<div style="width: 50%; float:left;">underlie `/ˌʌndə'laɪ/` 位于...之下，成为...的基础</div>
<div style="width: 50%; float:left;">inclusion `/ɪn'kluːʒn/` 包含</div>
<div style="width: 50%; float:left;">erroneous `/ɪ'rəʊniəs/` 错误的，不正确的</div>
<div style="width: 50%; float:left;">auxiliary `/ɔːɡ'zɪliəri/` 辅助的，附加的，助动词</div>
<div style="width: 50%; float:left;">indication `/ˌɪndɪ'keɪʃn/` 指示，表示，迹象</div>
<div style="width: 50%; float:left;">deficiencies `/dɪ'fɪʃnsi/` 缺乏，不足，缺陷，缺点</div>
<div style="width: 50%; float:left;">aspects `/'æspekts/` 方面，方位，外观</div>
<div style="width: 50%; float:left;">accommodate `/ə'kɒmədeɪt/` 适应，调节，调解，提供住宿，容纳</div>
<div style="width: 50%; float:left;">regret `/rɪ'ɡret/` 后悔，惋惜，抱歉</div>
<div style="width: 50%; float:left;">tuned `/tjuːnd/` （收音机）调谐的，调好台的</div>
<div style="width: 50%; float:left;">wise `/waɪz/` 聪明的，有智慧的，明智的</div>
<div style="width: 50%; float:left;">guards `/'gɑrd/` 警卫，看守，护卫队</div>
<div style="width: 50%; float:left;">separation `/ˌsepə'reɪʃn/` 分离，分居，间隔</div>
<div style="width: 50%; float:left;">advocated `/'ædvəkeɪt/` 提倡，主张，拥护者，律师，辩护者</div>
<div style="width: 50%; float:left;">triggering `/'trɪgərɪŋ/` 触发</div>
<div style="width: 50%; float:left;">widespread `/'waɪdspred/` 分布广泛的，普遍的</div>
<div style="width: 50%; float:left;">misgivings `/mɪs'ɡɪvɪŋz/` 怀疑，不安</div>
<div style="width: 50%; float:left;">neatly `/niːtli/` 整洁的，熟练地</div>
<div style="width: 50%; float:left;">decoupled `/diː'kʌpl/` 分离，拆散</div>
<div style="width: 50%; float:left;">coupling `/'kʌplɪŋ/` （计算机）耦合，联结，结合</div>
<div style="width: 50%; float:left;">bookkeeping `/'bʊkkiːpɪŋ/` 记账</div>
<div style="width: 50%; float:left;">semantic `/sɪ'mæntɪk/` 语义的</div>
<div style="width: 50%; float:left;">misconception `/ˌmɪskən'sepʃn/` 误解，错误想法</div>
<div style="width: 50%; float:left;">feasible `/'fiːzəbl/` 可行的</div>
<div style="width: 50%; float:left;">reiterate `/ri'ɪtəreɪt/` 重申</div>
<div style="width: 50%; float:left;">sake `/seɪk/` 理由，缘故，目的，利益</div>
<div style="width: 50%; float:left;">magnitude `/'mæɡnɪtjuːd/` 大小，重要，（地震）等级</div>
<div style="width: 50%; float:left;">comprehensive `/ˌkɒmprɪ'hensɪv/` 全面的，广泛的，综合的</div>
<div style="width: 50%; float:left;">attractive `/ə'træktɪv/` 有吸引力的</div>
<div style="width: 50%; float:left;">mechanically `/mə'kænɪkli/` 机械的，呆板的，无意识的</div>
<div style="width: 50%; float:left;">hierarchy `/'haɪərɑːki/` 等级制度，统治集团</div>
<div style="width: 50%; float:left;">bidirectional `/ˌbaɪdə'rekʃənl/` 双向的</div>
<div style="width: 50%; float:left;">terminology `/ˌtɜːmɪ'nɒlədʒi/` 术语</div>
<div style="width: 50%; float:left;">succinct `/sək'sɪŋkt/` 简洁的</div>
<div style="width: 50%; float:left;">novel `/'nɒvl/` 小说，新奇的</div>
<div style="width: 50%; float:left;">diagnostic `/ˌdaɪəɡ'nɒstɪk/` 诊断的，特征的</div>
<div style="width: 50%; float:left;">candidate `/'kændɪdət/` 候选人，应试者</div>
<div style="width: 50%; float:left;">decomposing `/ˌdiːkəm'pəʊz/` 分解，拆分，拆解，腐烂</div>
<div style="width: 50%; float:left;">overwhelming `/ˌəʊvə'welmɪŋ/` 势不可挡的，压倒的，无法抗拒的</div>
<div style="width: 50%; float:left;">shallow `/'ʃæləʊ/` 浅的，薄的，浅滩</div>
<div style="width: 50%; float:left;">layering `/'leɪərɪŋ/` 分层，压条法</div>
<div style="width: 50%; float:left;">unwieldy `/ʌn'wiːldi/` 笨重的，笨拙的，庞大的</div>
<div style="width: 50%; float:left;">inhibit `/ɪn'hɪbɪt/` 抑制，阻止</div>
<div style="width: 50%; float:left;">snippet `/'snɪpɪt/` 小片，小部分，片段</div>
<div style="width: 50%; float:left;">substitution `/ˌsʌbstɪ'tjuːʃn/` 代替，替代，交换</div>
<div style="width: 50%; float:left;">alleviate `/ə'liːvieɪt/` 减轻，缓和</div>
<div style="width: 50%; float:left;">associative `/ə'səʊʃiətɪv/` 联合的，组成的，联想的</div>
<div style="width: 50%; float:left;">archetype `/'ɑːkitaɪp/` （计算机）原型</div>
<div style="width: 50%; float:left;">syntactic `/sɪn'tæktɪk/` 句法的</div>
<div style="width: 50%; float:left;">incarnation `/ˌɪnkɑː'neɪʃn/` 赋予肉体，化身，（生活中的）特殊阶段</div>
<div style="width: 50%; float:left;">pragmatic `/præɡ'mætɪk/` 实用主义的，实际的</div>
<div style="width: 50%; float:left;">garnered `/'ɡɑːnə(r)/` 贮藏，收集，得到，谷仓</div>
<div style="width: 50%; float:left;">theoretical `/ˌθɪə'retɪkl/` 理论上的</div>
<div style="width: 50%; float:left;">obstacle `/'ɒbstəkl/` 障碍，绊脚石</div>