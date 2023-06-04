# Chapter 20. Smart Pointers

<!-- vim-markdown-toc GFM -->

<!-- vim-markdown-toc -->



In C++, smart pointers are classes that behave somewhat like ordinary pointers(in that they provide the dereferencing operators `->` and `*`) but in addition encapsulate some memory or resource management policy.


tow different ownership models:

- `exclusive`: Exclusive ownership can be enforced with little overhead, compared with handling raw pointers. Smart pointers that enforce such a policy are useful to deal with exceptions thrown while manipulating dynamically allocated objects.
- `shared`: Shared ownership can sometimes lead to excessively complicated object lifetime situations. In such cases, it may be advisable to move the burden of the lifetime decisions from the programmer to the program.

This section introduces two smart pointer types: a holder type to hold an object exclusively and a so-called rule to enable the transfer of ownership from one holder to another.

(resource acquisition is initialization, RAII)

`reference counting`: For each object that is pointed to, keep a count of the number of pointers to it, and when that count drops to zero, delete the object.

Built-in pointers are subject to several implicit conversions:

- Conversion to `void*`
- Conversion to pointer to a base subobject of the object pointed to
- Conversion to `bool`(`false` if the pointer is null, `true` otherwise)

Other drawbacks to implicit conversions to built-in pointer types include(assume `cp` is an counting pointer):

- `delete cp;` and `::delete cp;` become valid
- All sort of meaningless pointer arithmetic goes undiagnosed (for example, `cp[n], cp2 - cp1`, and so forth)



## Glossary

<div style="width: 50%; float:left;">encapsulate `/ɪn'kæpsjuleɪt/` 封装，压缩，概括</div>
<div style="width: 50%; float:left;">separated `/'sepəreɪtɪd/` 分开的</div>
<div style="width: 50%; float:left;">columnist `/'kɒləmnɪst/` 专栏作家</div>
<div style="width: 50%; float:left;">dominate `/'dɒmɪneɪt/` 支配，统治，控制，占优势</div>
<div style="width: 50%; float:left;">routine `/ruː'tiːn/` 例行公事，常规，无聊，乏味</div>
<div style="width: 50%; float:left;">significantly `/sɪɡ'nɪfɪkəntli/` 意味深长的，重要的</div>
<div style="width: 50%; float:left;">behave `/bɪ'heɪv/` 表现，行为，举止</div>
<div style="width: 50%; float:left;">minor `/'maɪnə(r)/` 次要的，轻微的，未成年人，辅修</div>
<div style="width: 50%; float:left;">inhibited `/ɪn'hɪbɪtɪd/` 羞怯的，抑制情感的</div>
<div style="width: 50%; float:left;">omit `/ə'mɪt/` 省略，遗漏，忘记，删去</div>
<div style="width: 50%; float:left;">acquisition `/ˌækwɪ'zɪʃn/` 获得，采集</div>
<div style="width: 50%; float:left;">recipient `/rɪ'sɪpiənt/` 接受者，收信人</div>
<div style="width: 50%; float:left;">appropriate `/ə'prəʊpriət /` 适当的，相称的，占用，拨款</div>
<div style="width: 50%; float:left;">ensues `/ɪn'sjuː/` 接着发生，继而，因而产生</div>
<div style="width: 50%; float:left;">inclined `/ɪn'klaɪnd/` 倾向于</div>
<div style="width: 50%; float:left;">counterpart `/'kaʊntəpɑːt/` 对应物，副本</div>
<div style="width: 50%; float:left;">subtle `/'sʌtl/` 微妙的，敏锐的，不明显的，精细的</div>
<div style="width: 50%; float:left;">callee `/kɔː'liː/` 被召唤者，被呼叫者</div>
<div style="width: 50%; float:left;">subsequent `/'sʌbsɪkwənt/` 随后的，后来的</div>
<div style="width: 50%; float:left;">prior `/'praɪə(r)/` 在前，居先，优先的，在前的，更重要的</div>
<div style="width: 50%; float:left;">nulling `/'nʌlɪŋ/` 清零，置零</div>
<div style="width: 50%; float:left;">intrinsically `/ɪn'trɪnzɪkli/` 内在的，固有的</div>
<div style="width: 50%; float:left;">affair `/ə'feə(r)/` 私通，事件，事务，事情</div>
<div style="width: 50%; float:left;">capsule `/'kæpsjuːl/` 胶囊，太空舱，概要，概括</div>
<div style="width: 50%; float:left;">thwart `/θwɔːt/` 反对，阻碍，座板，横过</div>
<div style="width: 50%; float:left;">unwound `/ˌʌn'waʊnd/` 展开</div>
<div style="width: 50%; float:left;">feasible `/'fiːzəbl/` 可行的，可能的</div>
<div style="width: 50%; float:left;">adhere `/əd'hɪə(r)/` 遵守，坚持，黏附</div>
<div style="width: 50%; float:left;">viable `/'vaɪəbl/` 可行的，能生存的</div>
<div style="width: 50%; float:left;">quasi `/'kweɪsaɪ/` 类似的，外表的</div>
<div style="width: 50%; float:left;">arbitrary `/'ɑːbɪtrəri/` 任意的，专制的，武断的，霸道的</div>
<div style="width: 50%; float:left;">simultaneous `/ˌsɪml'teɪniəs/` 同步的，同时发生的</div>
<div style="width: 50%; float:left;">presumably `/prɪ'zjuːməbli/` 大概，据推测，可能</div>
<div style="width: 50%; float:left;">anticipate `/æn'tɪsɪpeɪt/` 预期，预言，提前使用</div>
<div style="width: 50%; float:left;">incorporate `/ɪn'kɔːpəreɪt/` 合并，组成公司</div>
<div style="width: 50%; float:left;">brevity `/'brevəti/` 简短，简洁，短暂</div>
<div style="width: 50%; float:left;">premature `/'premətʃə(r)/` 早产的，过早的，早熟</div>
<div style="width: 50%; float:left;">noninvasive `/ˌnɒnɪn'veɪsɪv/` （计算机）非侵入性的，非侵害的</div>
<div style="width: 50%; float:left;">nonintrusive `/nɒnɪnt'ruːsɪv/` 无干扰的</div>
<div style="width: 50%; float:left;">pertinent `/'pɜːtɪnənt/` 中肯的，相关的，切题的</div>
<div style="width: 50%; float:left;">alongside `/əˌlɒŋ'saɪd/` 在旁边</div>
<div style="width: 50%; float:left;">invasive `/ɪn'veɪsɪv/` 侵入的，攻击性的</div>
<div style="width: 50%; float:left;">duality `/djuː'æləti/` 二重性，二元性</div>
<div style="width: 50%; float:left;">vein `/veɪn/` 静脉，纹理，叶脉</div>
<div style="width: 50%; float:left;">opaque `/əʊ'peɪk/` 晦涩的，难懂的，不透明的</div>
<div style="width: 50%; float:left;">accommodate `/ə'kɒmədeɪt/` 适应，调节，容纳，调解</div>
<div style="width: 50%; float:left;">nested `/nestɪd/` 嵌套的</div>
<div style="width: 50%; float:left;">comparison `/kəm'pærɪsn/` 比较，比喻</div>
<div style="width: 50%; float:left;">obvious `/'ɒbviəs/` 明显的，显然的</div>
<div style="width: 50%; float:left;">controversy `/'kɒntrəvɜːsɪ/` 争论，争议</div>