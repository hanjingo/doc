# chapter16 Templates and Inheritance



Named Template Arguments Example:

```c++
#include <iostream>
#include <typeinfo>
using namespace std;

class DefaultPolicy1{};
class DefaultPolicy2{};
class DefaultPolicy3{};
class DefaultPolicy4{};

class DefaultPolicies {
    public:
        typedef DefaultPolicy1 P1;
        typedef DefaultPolicy2 P2;
        typedef DefaultPolicy3 P3;
        typedef DefaultPolicy4 P4;
};

class DefaultPolicyArgs : virtual public DefaultPolicies{};
template<typename Policy>
class Policy1_is : virtual public DefaultPolicies {
    public:
        typedef Policy P1;
};

template <typename Policy>
class Policy2_is : virtual public DefaultPolicies {
    public:
        typedef Policy P2;
};

template <typename Policy>
class Policy3_is : virtual public DefaultPolicies {
    public:
        typedef Policy P3;
};

template <typename Policy>
class Policy4_is : virtual public DefaultPolicies{
    public:
        typedef Policy P4;
};

template<typename Base, int D>
class CanMultiDerivedFromOneClass : public Base{};

template<typename Setter1, typename Setter2, typename Setter3, typename Setter4>
class PolicySelector : public CanMultiDerivedFromOneClass<Setter1, 1>,
    public CanMultiDerivedFromOneClass<Setter2, 2>,
    public CanMultiDerivedFromOneClass<Setter3, 3>,
    public CanMultiDerivedFromOneClass<Setter4, 4>
{};

template<typename PolicySet1 = DefaultPolicyArgs,
    typename PolicySet2 = DefaultPolicyArgs,
    typename PolicySet3 = DefaultPolicyArgs,
    typename PolicySet4 = DefaultPolicyArgs>
class MyClass{
    public:
        typedef PolicySelector<PolicySet1, PolicySet2, PolicySet3, PolicySet4> Policies;
};

int main(){
    typedef MyClass<Policy2_is<int>, Policy4_is<double> > MyClassDef;
    MyClassDef::Policies::P1 p1;
    MyClassDef::Policies::P2 p2;
    MyClassDef::Policies::P3 p3;
    MyClassDef::Policies::P4 p4;
    cout << typeid(p1).name() << endl;
    cout << typeid(p2).name() << endl;
    cout << typeid(p3).name() << endl;
    cout << typeid(p4).name() << endl;

    return 0;
}
```

The designers of C++ had various reasons to avoid zero-size classes.

However, even though there are no zero-size types in C++, the C++ standard does specify that when an empty class is used as a base class, no space needs to be allocated for it, provided that it does not cause it to be allocated to the same address as another object or subobject of the same type.

empty base class optimization (or EBCO) means in practice:

```c++
#include <iostream>

class Empty{
    typedef int Int; // typedef成员并不会使类成为非空
};

class EmptyToo : public Empty {
};

class EmptyThree : public EmptyToo {
};
```

![16_2](/res/16_2.png)

*Figure 16.2. Layout of EmptyThree by a compiler that implements the EBCO*

![16_3](/res/16_3.png)

*Figure 16.3. Layout of EmptyThree by a compiler that does not implement the EBCO Consider an example that runs into a constraint of empty base optimization*

![16_4](/res/16_4.png)

*Figure 16.4. Layout of NonEmpty by a compiler that implements the EBCO*

*Curiously Recurring Template Pattern (CRTP)*: This oddly named pattern refers to a general class of techniques that consists of passing a derived class as a template argument to one of its own base classes. In it's simplest form, C++ code for such a pattern looks as follows:

```c++
template <typename Derived>
class CuriousBase {
    ...
};

class Curious : public CuriousBase<Curious> {
    ...
};
```

C++ allows us to parameterize directly three kinds of entities through templates: types, constants("nontypes"), and templates. However, indirectly, it also allows us to parameterize other attributes such as the virtuality of a member function.



## Glossary

<div style="width: 50%; float:left;">intermediate `/ˌɪntə'miːdiət/` 调解，干涉，中间的，中级的，调解人，媒介物</div>
<div style="width: 50%; float:left;">discriminator `/dɪ'skrɪmɪneɪtə/` 鉴别器，鉴别者</div>
<div style="width: 50%; float:left;">setter `/'setə(r)/` 安装者，排字工人，作曲者，给定装置</div>
<div style="width: 50%; float:left;">developed `/dɪ'veləpt/` 发达的，成熟的</div>
<div style="width: 50%; float:left;">conceivable `/kən'siːvəbl/` 可能的，可想象的</div>
<div style="width: 50%; float:left;">rationale `/ˌræʃə'nɑːl/` 基本原理，基础理论</div>
<div style="width: 50%; float:left;">constraint `/kən'streɪnt/` 约束，限制，强制，虚情假意</div>
<div style="width: 50%; float:left;">stems `/stems/` 柄，茎，船首，起源于，阻止，遏制</div>
<div style="width: 50%; float:left;">suboptimal `/'sʌb'ɒptɪməl/` 不是最理想的，未达最佳水平的</div>
<div style="width: 50%; float:left;">fairly `/'feəli/` 公正的，相当地</div>
<div style="width: 50%; float:left;">substituted `/'sʌbstɪtjuːtɪd/` 取代的，代替的</div>
<div style="width: 50%; float:left;">potentially `/pə'tenʃəli/` 潜在的/div>
<div style="width: 50%; float:left;">verbose `/vɜː'bəʊs/` 啰嗦的，冗长的</div>
<div style="width: 50%; float:left;">encapsulated `/ɪn'kæpsjuleɪt/` 封装，装入胶囊，封进内部，压缩，概括</div>
<div style="width: 50%; float:left;">oddly `/'ɒdli/` 奇怪的，奇妙的</div>
<div style="width: 50%; float:left;">immune `/ɪ'mjuːn/` 免疫的，免除的</div>
<div style="width: 50%; float:left;">intrinsic `/ɪn'trɪnsɪk/` 内在的，固有的，本质的</div>
<div style="width: 50%; float:left;">stretch `/stretʃ/` 伸展，延伸，张开，夸大，弹性</div>
<div style="width: 50%; float:left;">formulation `/ˌfɔːmju'leɪʃn/` 格式化，公式化，规划，构想，配方</div>
<div style="width: 50%; float:left;">track `/træk/` 追踪，跟踪，轨道，跑道，踪迹，小路</div>
<div style="width: 50%; float:left;">tedious `/'tiːdiəs/` 单调乏味的，沉闷的</div>
<div style="width: 50%; float:left;">decrement `/'dekrɪmənt/` 减少，负增长，减量</div>

