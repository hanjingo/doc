# Chapter 18. Expression Templates



`expression templates`: It was originally invented in support of numeric array classes, and that is also the context in which we introduce it here.

To justify the complexity of the expression template idea, we have already invoked greatly enhanced performance on arraywise operations.



## Glossary

<div style="width: 50%; float:left;">scalar `/'skeɪlə(r)/` 标量的，数量的，梯状的，分等级的</div>
<div style="width: 50%; float:left;">cruncher `/k'rʌntʃər/` （计算机）数字计算器</div>
<div style="width: 50%; float:left;">crucial `/'kruːʃl/` 关键的，决定性的</div>
<div style="width: 50%; float:left;">trivial `/'trɪviəl/` 不重要的，琐碎的</div>
<div style="width: 50%; float:left;">rescue `/'reskjuː/` 营救，救援</div>
<div style="width: 50%; float:left;">reminiscent `/ˌremɪ'nɪsnt/` 怀旧的，引人联想的，回忆录作者</div>
<div style="width: 50%; float:left;">complementary `/ˌkɒmplɪ'mentri/` 补充的，互补的</div>
<div style="width: 50%; float:left;">inefficient `/ˌɪnɪ'fɪʃnt/` 无效率的，无能的，不称职的</div>
<div style="width: 50%; float:left;">traversal `/traversal/` （计算机）遍历，横越，横断物</div>
<div style="width: 50%; float:left;">approximately `/ə'prɒksɪmətli/` 大约，近似地</div>
<div style="width: 50%; float:left;">creation `/kri'eɪʃn/` 创造，创作</div>
<div style="width: 50%; float:left;">realistic `/ˌriːə'lɪstɪk/` 现实主义的，现实的</div>
<div style="width: 50%; float:left;">clumsy `/'klʌmzi/` 笨拙的，笨重的</div>
<div style="width: 50%; float:left;">representation `/ˌreprɪzen'teɪʃn/` 陈述，表现，表示</div>
<div style="width: 50%; float:left;">operand `/'ɒpərænd/` （计算机）操作数，（计算机）操作对象</div>
<div style="width: 50%; float:left;">subscripting `/subscripting/` 加下标</div>
<div style="width: 50%; float:left;">handling `/'hændlɪŋ/` 操作，处理，管理，触摸，装卸</div>
<div style="width: 50%; float:left;">roughly `/'rʌfli/` 粗略地，粗糙地，大约</div>
<div style="width: 50%; float:left;">efficient `/ɪ'fɪʃnt/` 效率高的，胜任的</div>
<div style="width: 50%; float:left;">cumbersome `/'kʌmbəsəm/` 笨重的</div>
<div style="width: 50%; float:left;">unary `/'juːnəri/` 单项的，（数学）一元的</div>
<div style="width: 50%; float:left;">daunting `/dɔːntɪŋ/` 令人畏惧的</div>
<div style="width: 50%; float:left;">crystallize `/'krɪstəlaɪz/` 结晶，阐明，具体化</div>
<div style="width: 50%; float:left;">leftmost `/'leftməʊst/` 最左边的</div>
<div style="width: 50%; float:left;">elimination `/ɪˌlɪmɪ'neɪʃn/` 消去，消除，淘汰</div>
<div style="width: 50%; float:left;">problematic `/ˌprɒblə'mætɪk/` 有问题的，有疑问的</div>
<div style="width: 50%; float:left;">pioneer `/ˌpaɪə'nɪə(r)/` 先驱，先锋，开拓者，开辟</div>
<div style="width: 50%; float:left;">intriguing `/ɪn'triːɡɪŋ/` 吸引人的，有趣的</div>
<div style="width: 50%; float:left;">excerpt `/'eksɜːpt/` 摘录，引用</div>
<div style="width: 50%; float:left;">copier `/'kɒpiə(r)/` 复印机，抄写员</div>
<div style="width: 50%; float:left;">sketch `/sketʃ/` 素描，速写，概述，草图</div>
<div style="width: 50%; float:left;">impressive `/ɪm'presɪv/` 令人印象深刻的</div>
<div style="width: 50%; float:left;">precursor `/priː'kɜːsə(r)/` 前任，前兆，前驱</div>
<div style="width: 50%; float:left;">proposal `/prə'pəʊzl/` 建议，求婚，提议</div>
<div style="width: 50%; float:left;">bells `/bels/` 排钟</div>
<div style="width: 50%; float:left;">inspired `/ɪn'spaɪəd/` 有灵感的，有创见的，授意的</div>
<div style="width: 50%; float:left;">pseudo `/'sjuːdəʊ/` 假的，冒充的</div>
<div style="width: 50%; float:left;">rewrote `/ˌriː'rəʊt/` 再写</div>
<div style="width: 50%; float:left;">tweaks `/twiːk/` 拧，扭，拉，捏</div>
<div style="width: 50%; float:left;">exploitation `/ˌeksplɔɪ'teɪʃn/` 开采，开发，剥削，利用</div>
<div style="width: 50%; float:left;">elaborate `/ɪ'læbəreɪt/` 详尽的，复杂的，精美的，精心的</div>
<div style="width: 50%; float:left;">inspiration `/ˌɪnspə'reɪʃn/` 灵感，吸气</div>