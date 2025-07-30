# Chapter 14. The Polymorphic Power of Templates

[TOC]



`abstract base class (ABC)`

Dynamic and static polymorphism provide support for different C++ programming idioms:

- Polymorphism implemented via inheritance is bounded and dynamic:
  - Bounded means that the interfaces of the types participating in the polymorphic behavior are predetermined by the design of the common base class (other terms for this concept are invasive)。
  - Dynamic means that the binding of the interfaces is done at run time (dynamically).
- Polymorphism implemented via templates is unbounded and static:
  - Unbounded means that the interfaces of the types participating in the polymorphic behavior are not predetermined (other terms for this concept are noninvasive or nonintrusive).
  - Static means that the binding of the interfaces is done at compile time (statically).

Dynamic polymorphism in C++ exhibits the following strengths:

- Heterogeneous collections are handled elegantly.
- The executable code size is potentially smaller (because only one polymorphic function is needed, whereas distinct template instances must be generated to handle different types).
- Code can be entirely compiled; hence, no implementation source must be published (distributing template libraries usually requires distribution of the source code of the template implementations).

In contrast, the following can be said about static polymorphism in C++:

- Collections of built-in types are easily implemented. More generally, the interface commonality need not be expressed through a common base class.
- Generated code is potentially faster (because no indirection through pointers is needed a priori, and non-virtual functions can be inlined much more often).
- Concrete types that provide only partial interfaces can still be used if only that part ends up being exercised by the application.

Generic programming is a subdiscipline of computer science that deals with finding abstract representations of efficient algorithms, data structures, and other software concepts, and with their systematic organization... Generic programming focuses on representing families of domain concepts.

National Institutes of Health Class Library (NIHCL)



## Glossary

<div style="width: 50%; float:left;">presentation `/ˌprezn'teɪʃn/` 介绍，陈述，赠送物，报告，讲课</div>
<div style="width: 50%; float:left;">polymorphic `/ˌpɒli'mɔːfɪk/` 多样性的</div>
<div style="width: 50%; float:left;">cornerstone `/ˈkɔːnəstəʊn/` 基础，奠基石</div>
<div style="width: 50%; float:left;">paradigm `/ˈparədʌɪm/` 范例，词形变化表</div>
<div style="width: 50%; float:left;">polymorphism `/ˌpɒlɪˈmɔːfɪzm/` （计算机）多态，多样性</div>
<div style="width: 50%; float:left;">plain `/pleɪn/` 朴素的，清晰的，平原，广阔的地区，完全的，存粹的</div>
<div style="width: 50%; float:left;">appropriate `/əˈprəʊpriət/`  合适的，恰当的，盗用，占用，侵吞，拨出（款项）</div>
<div style="width: 50%; float:left;">orthogonal `/ɔː'θɒgənl/` 直角的，正交的</div>
<div style="width: 50%; float:left;">invocation `/ˌɪnvə'keɪʃn/` （计算机）调用，祈祷，实施</div>
<div style="width: 50%; float:left;">sketch `/sketʃ/` 素描，速写，框架，概述，草图</div>
<div style="width: 50%; float:left;">dynamic `/daɪˈnæmɪk/` 动态，有活力的，动力学，力学</div>
<div style="width: 50%; float:left;">heterogeneous `/ˌhetərə'dʒiːniəs/` （计算机）非均匀的，异种的，异质的，由不同成分形成的</div>
<div style="width: 50%; float:left;">rely `/rɪˈlʌɪ/` 依靠，依赖</div>
<div style="width: 50%; float:left;">relevant `/ˈreləvənt/` 相关的，合适的，有意义的</div>
<div style="width: 50%; float:left;">concrete `/ˈkɒŋkriːt/` 具体的，实体的，混凝土，水泥，实质性的，凝结，结合</div>
<div style="width: 50%; float:left;">hood `/hʊd/` 头巾，兜帽，遮罩，引擎盖，覆盖</div>
<div style="width: 50%; float:left;">recode `/'riː'kəʊd/` 重新编码</div>
<div style="width: 50%; float:left;">hierarchy `/ˈhʌɪərɑːki/` 等级制度，统治集团</div>
<div style="width: 50%; float:left;">transparent `/trænsˈpærənt/` 透明的，清澈的，显而易见的，易懂的</div>
<div style="width: 50%; float:left;">terminology `/ˌtɜːmɪˈnɒlədʒi/` 术语，专门用语</div>
<div style="width: 50%; float:left;">idiom `/'ɪdiəm/` 方言，成语，惯用语，风格，特色</div>
<div style="width: 50%; float:left;">participate `/pɑːˈtɪsɪpeɪt/` 参加，参与，分享</div>
<div style="width: 50%; float:left;">invasive `/ɪn'veɪsɪv/` 侵入的，侵略性的，攻击性的</div>
<div style="width: 50%; float:left;">intrusive `/ɪnˈtruːsɪv/` 侵入的，插入的，添加的</div>
<div style="width: 50%; float:left;">parlance `/'pɑːləns/` 说法，用语，语调，辩论</div>
<div style="width: 50%; float:left;">elegant `/'elɪɡənt/` 优雅的，雅致的</div>
<div style="width: 50%; float:left;">grief `/ɡriːf/` 悲痛，忧伤</div>
<div style="width: 50%; float:left;">curious `/'kjʊəriəs/` 好奇的，奇特的</div>
<div style="width: 50%; float:left;">recur `/rɪˈkɜː(r)/` 重现，再次发生，反复出现</div>
<div style="width: 50%; float:left;">delegate `/ˈdelɪɡət /` 代理，授权，委托，代表</div>
<div style="width: 50%; float:left;">ingredient `/ɪnˈɡriːdɪənt/` 原料，因素</div>
<div style="width: 50%; float:left;">incorporate `/ɪn'kɔːpəreɪt/` 合并，组建公司，合成一体</div>
<div style="width: 50%; float:left;">essentially `/ɪ'senʃəli/` 本质上，本来</div>
<div style="width: 50%; float:left;">traverse `/trəˈvɜːs/` 横过，穿过，横渡，横木</div>
<div style="width: 50%; float:left;">glue `/ɡluː/` 胶水，粘贴</div>
<div style="width: 50%; float:left;">fulfill `/fʊl'fɪl/` 完成，履行，执行，满足</div>
<div style="width: 50%; float:left;">motivation `/ˌməʊtɪˈveɪʃn/` 动机，积极性，动力，刺激</div>
<div style="width: 50%; float:left;">dramatic `/drəˈmætɪk/` 戏剧性的，巨大的，突然的，令人吃惊的</div>
<div style="width: 50%; float:left;">sought `/sɔːt/` 搜索</div>
<div style="width: 50%; float:left;">solace `/'sɒləs/` 安慰，慰藉，使快乐，使安慰，使缓和</div>
<div style="width: 50%; float:left;">vein `/veɪn/` 静脉，纹理，叶脉，岩脉，使有脉络，用脉络装饰</div>
<div style="width: 50%; float:left;">homogeneous `/ˌhɒmə'dʒiːniəs/` 同质的，同种的</div>
<div style="width: 50%; float:left;">intimate `/'ɪntɪmət/` 亲密的，私人的，暗示，透露</div>
<div style="width: 50%; float:left;"></div>
<div style="width: 50%; float:left;"></div>
<div style="width: 50%; float:left;"></div>
<div style="width: 50%; float:left;"></div>
<div style="width: 50%; float:left;"></div>
<div style="width: 50%; float:left;"></div>
<div style="width: 50%; float:left;"></div>
<div style="width: 50%; float:left;"></div>