# Chapter 1 Introduction

An `operating system` is the layer of software that manages a computer's resources for its users and their applications.

Operating systems have three roles:

- Operating systems play referee -- they manage shared resources between different applications running on the same physical machine.
- Operating systems play illusionist -- they provide an abstraction physical hardware to simplify application design.
- Operation systems provide glue -- a set of common services between applications.

Sharing raises several challenges for an operating system:

- Resource Allocation.
- Isolation.
- Communication.

Virtualization provides an application with the illusion of resources that are not physically present.

Some operating systems virtualize the entire computer, to run the operating system as an application running on top of another operating system. This is called creating a `virtual machine`.

The operating system running in the virtual machine, called the `guest operating system`, thinks it is running on a real, physical machine, but this is an illusion presented by the true operating system running underneath.

The memory system in hardware ensures that any updates to the same memory word are `atomic`, that is, the value stored in memory is the last value stored by one of the processors, not a mixture of the updates of the different processors.

`Reliability` is that a system does exactly what it is designed to do. As the lowest level of software running on the system, errors in operating system code can have devastating and hidden effects.

`availability`, the percentage of time that the system is usable.

Availability is affected by two factors: 

- the frequency of failures, called the `mean time to failure`(MTTF)
- the time it takes to restore a system to a working state after a failure (for example, to reboot), the `mean time to repair`(MTTR).

Availability can be improved by increasing the MTTF or reducing the MTTR, and we will present operating systems techniques that do each.

`Security` is the property that the computer's operation cannot be compromised by a malicious attacker.

`Privacy` is a part of security that data stored on the computer is only accessible to authorized users.

A `computer virus` is a computer program that modifies an operating system or application to provide the attacker, rather than the user, control over the system's resources or data.

`Enforcement` is how the operating system ensures that only permitted actions are allowed.

The `security policy` defines what is permitted who is allowed to access what data and who can perform what operations.

A portable abstraction is one that does not change as the hardware changes.

The `abstract machine interface`(AMI) is the interface provided by operating systems to applications. A key part of the AMI is the `application programming interface`(API), the list of function calls the operating system provides to applications.

The `hardware abstraction layer`(HAL) is designed to hide unimportant hardware details.

One performance metric is the `efficiency` of the abstraction presented to applications. A related concept to efficiency is `overhead`, the added resource cost of implementing an abstraction.

`fairness`, between different users of the same machine, or between different applications running on that machine.

`Response` time, sometimes called `delay`, is how long it takes for a single specific task from when it starts until it completes.

`Throughput` is the rate at which a group of tasks can be completed. Throughput is a measure of efficiency for a group of tasks rather than a single one.

`predictability`, whether the system's response time or other metric is consistent over time.

The `network effect` occurs when the value of some technology depends not only on its intrinsic capabilities, but also on the number of other people who have adopted that technology.

A `proprietary` system is one under the control of a single company, so it can be changed at any time by its provider to meet the needs of its customers.

An `open system` is one where the system's source code is public, allowing anyone the ability to inspect the code and change it.

`batch operating systems`, one program can be using the processor while another is being loaded into memory.

While one job was running, the operating system would set up the I/O devices to do background transfers for the next/previous job using a process called `direct memory access`(DMA).

Batch operating systems were soon extended to run multiple applications at once, that is, `multitasking`, or what is also sometimes called `multiprogramming`.

Instead of running a test operating system directly on the hardware, with virtual machines an operating system can be run just like any another application. The true operating system, called a `virtual machine monitor`, exports an abstract machine interface (AMI) that is identical to the underlying hardware.

A `time-sharing` operating system, is one designed to support interactive use of the computer, rather than the batch mode processing of earlier systems.

Here are some examples of operating systems that the reader might have used recently:

- Desktop, laptop, and netbook operating systems.
- Smartphone operating systems.
- Embedded systems.
- Virtual machines.
- Server operating systems.
- Server clusters.



## Glossary

<div style="width: 50%; float:left;">essential `/ɪˈsenʃl/` 本质的，要素，必需品</div>
<div style="width: 50%; float:left;">grocer `/'ɡrəʊsə(r)/` 食品杂货商，杂货店</div>
<div style="width: 50%; float:left;">analogue `/'ænəlɒɡ/` 类似物，模拟计算机的</div>
<div style="width: 50%; float:left;">toaster `/'təʊstə(r)/` 烤面包机</div>
<div style="width: 50%; float:left;">console `/kən'səʊl/` （计算机）操控台，仪表盘，(游戏)平台，安慰，慰藉</div>
<div style="width: 50%; float:left;">broad `/brɔːd/` 宽广的，广泛的，明显的，粗野的</div>
<div style="width: 50%; float:left;">literal `/ˈlɪtərəl/` 常量，字面值，文学的，书面的，字面上的</div>
<div style="width: 50%; float:left;">individual `/ɪndɪˈvɪdʒʊ(ə)l/` 单独的，独特的，个人主义，个人，个体</div>
<div style="width: 50%; float:left;">juggle `/'dʒʌɡl/` 玩杂耍，篡改，花招</div>
<div style="width: 50%; float:left;">animate `/'ænɪmeɪt/` 赋予生命，鼓励，有生命力的</div>
<div style="width: 50%; float:left;">compromise `/ˈkɒmprəmaɪz/` 妥协，折中，和解</div>
<div style="width: 50%; float:left;">surreptitiously `/ˌsʌrəp'tɪʃəsli/` 偷偷摸摸地，暗中地</div>
<div style="width: 50%; float:left;">dangling `/'dæŋɡl/` （计算机）悬垂，摇晃，挂着，追求</div>
<div style="width: 50%; float:left;">mishmash `/'mɪʃmæʃ/` 混杂物，杂乱的一堆</div>
<div style="width: 50%; float:left;">decouple `/diːˈkʌpl/` 分离，隔断，解耦</div>
<div style="width: 50%; float:left;">sphere `/sfɪə(r)/` 范围，领域，球体，包围</div>
<div style="width: 50%; float:left;">primitive `/'prɪmətɪv/` 原始的，简陋的，原始人</div>
<div style="width: 50%; float:left;">
sophisticate `/səˈfɪstɪkət/` 老练的，精密的，复杂的，老于世故的人，使...更精确</div>
<div style="width: 50%; float:left;">mediate `/'miːdieɪt/` 调停，斡旋，居间的，间接的</div>
<div style="width: 50%; float:left;">referee `/ˌrefə'riː/` 裁判，仲裁，裁判员，鉴定人</div>
<div style="width: 50%; float:left;">corrupt `/kəˈrʌpt/` 贪污，腐败，不道德的，破坏，损坏</div>
<div style="width: 50%; float:left;">malicious `/məˈlɪʃəs/` 恶毒的，蓄意的，怀有恶意的</div>
<div style="width: 50%; float:left;">illusionist `/ɪ'luːʒənɪst/` 魔术师，幻术家，幻觉论者</div>
<div style="width: 50%; float:left;">podcast `/'pɒdkɑːst/` 播客，发表博客</div>
<div style="width: 50%; float:left;">rest `/rest/` 剩余，休息，支撑，依赖，搁置，埋葬</div>
<div style="width: 50%; float:left;">finite `/'faɪnaɪt/` 有限的</div>
<div style="width: 50%; float:left;">trivial `/'trɪviəl/` 琐碎的，不重要的</div>
<div style="width: 50%; float:left;">perceive `/pə'siːv/` 注意到，觉察到，认为，理解</div>
<div style="width: 50%; float:left;">multiplex `/'mʌltɪpleks/` 多路传输，多样的，多元的</div>
<div style="width: 50%; float:left;">unimpeded `/ˌʌnɪm'piːdɪd/` 未受阻的，畅通无阻的</div>
<div style="width: 50%; float:left;">introductory `/ˌɪntrə'dʌktəri/` 介绍的，前言的，序文的</div>
<div style="width: 50%; float:left;">vastly `/'vɑːstli/` 极大地，广大地</div>
<div style="width: 50%; float:left;">spyware `/'spaɪweə/` 间谍软件</div>
<div style="width: 50%; float:left;">keystroke `/'kiːstrəʊk/` 按键，键盘输入</div>
<div style="width: 50%; float:left;">irretrievably `/ˌɪrɪ'triːvəbli/` 不可挽回地，无法弥补地，不能恢复地</div>
<div style="width: 50%; float:left;">erroneous `/ɪˈrəʊnɪəs/` 错误的</div>
<div style="width: 50%; float:left;">malignant `/mə'lɪɡnənt/` 有恶意的，恶性的，有害的</div>
<div style="width: 50%; float:left;">havoc `/'hævək/` 破坏，混乱</div>
<div style="width: 50%; float:left;">flip `/flɪp/` 轻弹，弹，掷，反转，空翻，无礼的，冒失的，轻率的</div>
<div style="width: 50%; float:left;">advertisement `/əd'vɜːtɪsmənt/` 广告</div>
<div style="width: 50%; float:left;">prevent `/prɪˈvent/` 阻止，阻挠，阻碍，预防</div>
<div style="width: 50%; float:left;">akin `/əˈkɪn/` 类似的</div>
<div style="width: 50%; float:left;">patient `/'peɪʃnt/` 病人，能忍耐的，有耐心的</div>
<div style="width: 50%; float:left;">kindergarten `/'kɪndəɡɑːtn/` 幼儿园</div>
<div style="width: 50%; float:left;">hog `/hɒɡ/` 猪，贪婪者，独占</div>
<div style="width: 50%; float:left;">buggy `/ˈbʌɡi/` 婴儿车，折叠式童车，轻便马车，专用小车</div>
<div style="width: 50%; float:left;">justify `/'dʒʌstɪfaɪ/` 替...辩护，证明...正当，调整版面</div>
<div style="width: 50%; float:left;">access `/'ækses/` （计算机）存取，入口，通道，使用权</div>
<div style="width: 50%; float:left;">spam `/spæm/` 垃圾电子邮件，兜售信息</div>
<div style="width: 50%; float:left;">present `/ˈpreznt/` 目前，提出，出席</div>
<div style="width: 50%; float:left;">dedicate `/'dedɪkeɪt/` 致力于，献出</div>
<div style="width: 50%; float:left;">roughly `/'rʌfli/` 粗略地，粗糙地，大约</div>
<div style="width: 50%; float:left;">persistent `/pə'sɪstənt/` 坚持的，连续的，固执的</div>
<div style="width: 50%; float:left;">puzzle `/ˈpʌzl/` 迷惑，困惑，拼图，智力游戏</div>
<div style="width: 50%; float:left;">blizzard `/'blɪzəd/` 暴雪，大量</div>
<div style="width: 50%; float:left;">coordinate `/kəʊˈɔːdɪnət/` 协调，坐标，套装</div>
<div style="width: 50%; float:left;">pose `/pəʊz/` 姿态，姿势，造成，提出，假装</div>
<div style="width: 50%; float:left;">intensive `/ɪnˈtensɪv/`  密集的，加强器</div>
<div style="width: 50%; float:left;">tolerance `/ˈtɒlərəns/`  容错，公差，容量</div>
<div style="width: 50%; float:left;">cart `/kɑːt/` 手推车，运货马车，运送，拖</div>
<div style="width: 50%; float:left;">transparent `/trænsˈpærənt/` 透明的，清澈的，显而易见的，易懂的</div>
<div style="width: 50%; float:left;">purchase `/'pɜːtʃəs/` 购买</div>
<div style="width: 50%; float:left;">simultaneous `/ˌsɪml'teɪniəs/` 同步的，同时发生的</div>
<div style="width: 50%; float:left;">interpose `/ˌɪntə'pəʊz/` （计算机）打桩，插入，介入，插嘴，调停</div>
<div style="width: 50%; float:left;">contention `/kən'tenʃn/` 争论，争辩，争夺，论点</div>
<div style="width: 50%; float:left;">rife `/raɪf/` 非常多的，盛传的，流行的</div>
<div style="width: 50%; float:left;">legitimate `/lɪ'dʒɪtɪmət/` 合法的，世袭的，婚生的，正当的，合理的，授权，宣布...合法</div>
<div style="width: 50%; float:left;">phishing `/'fɪʃɪŋ/` 网络钓鱼</div>
<div style="width: 50%; float:left;">discrete `/dɪˈskriːt/` 分散，分离，离散</div>
<div style="width: 50%; float:left;">garble `/'gɑːbl/` 断章取义，曲解，混淆</div>
<div style="width: 50%; float:left;">interoperability `/'ɪntərɒpərə'bɪlətɪ/` 互操作性，互用性</div>
<div style="width: 50%; float:left;">versa `/versa/` 反，反的</div>
<div style="width: 50%; float:left;">thinly `/'θɪnli/` 薄薄的，细细的，稀疏的</div>
<div style="width: 50%; float:left;">grapple `/'ɡræpl/` 抓钩，抓住，扭打，搏斗</div>
<div style="width: 50%; float:left;">misuse `/ˌmɪsˈjuːz/` 误用，错用，滥用，虐待</div>
<div style="width: 50%; float:left;">foster `/ˈfɒstə(r)/` 收养的，代养，照料，促进，培养</div>
<div style="width: 50%; float:left;">criteria `/kraɪ'tɪəriə/` 标准，尺度，准则</div>
<div style="width: 50%; float:left;">inevitable `/ɪn'evɪtəbl/` 不可避免的，必然(发生)的</div>
<div style="width: 50%; float:left;">devastate `/ˈdevəsteɪt/` 毁灭，摧毁，彻底破坏，震惊</div>
<div style="width: 50%; float:left;">hostile `/ˈhɒstaɪl/` 敌对的，敌意的，虐待的，坚决否定，不利的</div>
<div style="width: 50%; float:left;">exploit `/ɪkˈsplɔɪt/` 剥削，压榨，利用，开发，功绩，英勇行为</div>
<div style="width: 50%; float:left;">vulnerability `/ˌvʌlnərə'bɪləti/` （计算机）漏洞，易受攻击，弱点</div>
<div style="width: 50%; float:left;">subvert `/səb'vɜːt/` 推翻，颠覆，毁灭，使败坏</div>
<div style="width: 50%; float:left;">rigid `/'rɪdʒɪd/` 坚硬的，死板的，僵硬的</div>
<div style="width: 50%; float:left;">formulaic `/ˌfɔːmju'leɪɪk/` 公式的，俗套的，刻板的</div>
<div style="width: 50%; float:left;">ultra `/'ʌltrə/` 过激的，极端的，超级</div>
<div style="width: 50%; float:left;">alas `/ə'læs/` 唉，哎呀(表示悲伤、忧愁、恐惧等)</div>
<div style="width: 50%; float:left;">innocuous `/ɪ'nɒkjuəs/` 无害的，无毒的，无关痛痒的</div>
<div style="width: 50%; float:left;">tamper `/'tæmpə(r)/` 干预，玩弄，贿赂，篡改</div>
<div style="width: 50%; float:left;">untrustworthy `/ʌn'trʌstwɜːði/` 靠不住的，不能信赖的</div>
<div style="width: 50%; float:left;">vulnerability `/ˌvʌlnərə'bɪləti/` （计算机）漏洞，易受攻击，弱点</div>
<div style="width: 50%; float:left;">saver `/'seɪvə(r)/` 救助者，节约器，储蓄者</div>
<div style="width: 50%; float:left;">surreptitiously `/ˌsʌrəp'tɪʃəsli/` 偷偷摸摸地，暗中地</div>
<div style="width: 50%; float:left;">insecure `/ˌɪnsɪ'kjʊə(r)/` 不安全的，不稳固的，不可靠的</div>
<div style="width: 50%; float:left;">assurance `/ə'ʃʊərəns/` 保证，担保，确信，自信，保险</div>
<div style="width: 50%; float:left;">attachment `/əˈtætʃ.mənt/` 附件，附加设备</div>
<div style="width: 50%; float:left;">suspicious `/sə'spɪʃəs/` 可疑的，多疑的</div>
<div style="width: 50%; float:left;">complicate `/'kɒmplɪkeɪt/` 使复杂化，使难懂</div>
<div style="width: 50%; float:left;">impractical `/ɪmˈpræktɪkl/` 不明智的，不现实的，无用的</div>
<div style="width: 50%; float:left;">anomaly `/əˈnɒməli/` 异常，反常</div>
<div style="width: 50%; float:left;">retrospect `/'retrəspekt/` 回顾，回想，追溯</div>
<div style="width: 50%; float:left;">insulate `/'ɪnsjuleɪt/` 使绝缘，隔离</div>
<div style="width: 50%; float:left;">optical `/'ɒptɪkl/` 光学的，视觉的</div>
<div style="width: 50%; float:left;">procedural `/prə'siːdʒərəl/` 程序的</div>
<div style="width: 50%; float:left;">apparent `/ə'pærənt/` 明显的，表面上</div>
<div style="width: 50%; float:left;">associate `/ə'səʊʃieɪt/` 关联，联想，交往，同伴</div>
<div style="width: 50%; float:left;">perceive `/pə'siːv/` 注意到，觉察到，认为，理解</div>
<div style="width: 50%; float:left;">mediate `/'miːdieɪt/` 调停，斡旋，居间的，间接的</div>
<div style="width: 50%; float:left;">degree `/dɪ'ɡriː/` 程度，度数，学位</div>
<div style="width: 50%; float:left;">impede `/ɪmˈpiːd/` 阻碍，妨碍，阻止</div>
<div style="width: 50%; float:left;">perceive `/pə'siːv/` 注意到，觉察到，认为，理解</div>
<div style="width: 50%; float:left;">instant `/ˈɪnstənt/` 立即，立刻</div>
<div style="width: 50%; float:left;">instantaneous `/ˌɪnstən'teɪniəs/` 瞬间的，即刻的</div>
<div style="width: 50%; float:left;">pedestrian `/pə'destriən/` 徒步的，缺乏想像的，行人</div>
<div style="width: 50%; float:left;">congest `/kən'dʒest/` 拥挤</div>
<div style="width: 50%; float:left;">carpool `/'kɑːpuːl/` 拼车，合伙使用汽车</div>
<div style="width: 50%; float:left;">lane `/leɪn/` 小路，小巷，行车道，跑道，航道</div>
<div style="width: 50%; float:left;">arguable `/'ɑːɡjuəbl/` 可辩论的，可论证的</div>
<div style="width: 50%; float:left;">adoption `/ə'dɒpʃn/` 采用，采纳，收养</div>
<div style="width: 50%; float:left;">alleged `/ə'ledʒd/` 声称的，可疑的，靠不住的</div>
<div style="width: 50%; float:left;">circular `/'sɜːkjələ(r)/` 循环的，传单，通报</div>
<div style="width: 50%; float:left;">virtuous `/virtuous/` 有品德的，贞洁的</div>
<div style="width: 50%; float:left;">accommodate `/əˈkɒmədeɪt/` 容纳，住宿，调解，向..提供，随和，乐于助人，顾及的</div>
<div style="width: 50%; float:left;">adherence `/əd'hɪərəns/` 坚持，固守，黏附</div>
<div style="width: 50%; float:left;">assurance `/ə'ʃʊərəns/` 保证，担保，确信，自信，保险</div>
<div style="width: 50%; float:left;">fragmentation `/ˌfræɡmen'teɪʃn/` 分裂，破碎</div>
<div style="width: 50%; float:left;">impair `/ɪm'peə(r)/` （计算机）损伤，损害，削弱</div>
<div style="width: 50%; float:left;">purveyor `/pə'veɪə(r)/` 粮食供应者，承办者，散播者</div>
<div style="width: 50%; float:left;">interoperability `/'ɪntərɒpərə'bɪlətɪ/` 互操作性，互用性</div>
<div style="width: 50%; float:left;">idiosyncratic `/ˌɪdiəsɪŋ'krætɪk/` 特质的，与众不同的</div>
<div style="width: 50%; float:left;">chaotic `/keɪ'ɒtɪk/` 混乱的</div>
<div style="width: 50%; float:left;">vet `/vet/` 诊疗，审查，老兵，兽医</div>
<div style="width: 50%; float:left;">practice `/ˈpræktɪs/` 习惯，习俗，实践，练习，实习</div>
<div style="width: 50%; float:left;">telemarketing `/'telimɑːkɪtɪŋ/` 电话销售，电话推销</div>
<div style="width: 50%; float:left;">tweak `/twiːk/` 拧，扭，拉，微调</div>
<div style="width: 50%; float:left;">incidence `/'ɪnsɪdəns/` 发生（率），入射</div>
<div style="width: 50%; float:left;">shave `/ʃeɪv/` 刮，剃，修剪，剃刀</div>
<div style="width: 50%; float:left;">painstaking `/'peɪnzteɪkɪŋ/` 辛苦，苦心，工夫，辛苦的，勤勉的，十分小心的</div>
<div style="width: 50%; float:left;">factor `/ˈfæktə(r)/` （数学）商，因素，因子，要素</div>
<div style="width: 50%; float:left;">prioritize `/praɪ'ɒrətaɪz/` 把...区分优先次序</div>
<div style="width: 50%; float:left;">transistor `/træn'zɪstə(r)/` 晶体管</div>
<div style="width: 50%; float:left;">density `/ˈdensəti/` 密度，浓度，稠密，密集</div>
<div style="width: 50%; float:left;">exponential `/ˌekspə'nenʃl/` （数学）指数性的，成倍的，幂的</div>
<div style="width: 50%; float:left;">trajectory `/trə'dʒektəri/` 轨道，弹道，轨迹</div>
<div style="width: 50%; float:left;">radical `/'rædɪkl/` 根本的，彻底的，激进的，激进分子</div>
<div style="width: 50%; float:left;">incredible `/ɪn'kredəbl/` 难以置信的，惊人的</div>
<div style="width: 50%; float:left;">patient `/'peɪʃnt/` 病人，能忍耐的，有耐心的</div>
<div style="width: 50%; float:left;">synthesize `/'sɪnθəsaɪz/` 合成，综合</div>
<div style="width: 50%; float:left;">fraction `/ˈfrækʃn/` 部分，分数，小数，片段</div>
<div style="width: 50%; float:left;">progression `/prə'ɡreʃn/` 前进，进展，连续</div>
<div style="width: 50%; float:left;">conceptual `/kən'septʃuəl/` 概念的</div>
<div style="width: 50%; float:left;">tremendously `/trə'mendəsli/` 惊人地，非常，十分</div>
<div style="width: 50%; float:left;">warehouse `/ˈweəhaʊs/` 仓库，存入仓库</div>
<div style="width: 50%; float:left;">pore `/pɔː(r)/` 毛孔，小孔，熟读，钻研，沉思</div>
<div style="width: 50%; float:left;">likelihood `/'laɪklihʊd/` 可能性</div>
<div style="width: 50%; float:left;">batch `/bætʃ/` 一批，批处理</div>
<div style="width: 50%; float:left;">spare `/speə(r)/` 备用的，闲置的，多余的，空闲的</div>
<div style="width: 50%; float:left;">burst `/bɜːst/`  爆裂，胀开，暴涨</div>
<div style="width: 50%; float:left;">sustain `/səˈsteɪn/` 维持，持久，遭受，蒙受</div>
<div style="width: 50%; float:left;">dedicate `/'dedɪkeɪt/` 致力于，献出</div>
<div style="width: 50%; float:left;">paramount `/ˈpærəmaʊnt/` 元首，至尊的，权力最大的</div>
<div style="width: 50%; float:left;">surreptitiously `/ˌsʌrəp'tɪʃəsli/` 偷偷摸摸地，暗中地</div>
<div style="width: 50%; float:left;">misbehavior `/'mɪsbɪ'heɪvjə/` 粗鲁行为，品行不端</div>
<div style="width: 50%; float:left;">integrate `/'ɪntɪɡreɪt/` （数学）求积分，整合，结合，取消隔离，完整的，组合的</div>
<div style="width: 50%; float:left;">oven `/'ʌvn/` 烤箱，烤炉</div>
<div style="width: 50%; float:left;">intravenous `/ˌɪntrə'viːnəs/` 静脉的，静脉注射的</div>
<div style="width: 50%; float:left;">titration `/tɪ'treɪʃn/` （一种定量分析的手段）滴定</div>
<div style="width: 50%; float:left;">bundle `/'bʌndl/` 捆，束，包，大笔钱</div>
<div style="width: 50%; float:left;">merit `/ˈmerɪt/` 优点，价值，功绩，值得</div>
<div style="width: 50%; float:left;">devastate `/ˈdevəsteɪt/` 毁灭，摧毁，彻底破坏，震惊</div>
<div style="width: 50%; float:left;">paradigm `/ˈparədʌɪm/` 范例，词形变化表</div>
<div style="width: 50%; float:left;">tolerance `/ˈtɒlərəns/`  容错，公差，容量</div>
<div style="width: 50%; float:left;">accommodate `/əˈkɒmədeɪt/` 容纳，住宿，调解，向..提供，随和，乐于助人，顾及的</div>
<div style="width: 50%; float:left;">resist `/rɪˈzɪst/` 抵制，反抗，回击，抵挡</div>
<div style="width: 50%; float:left;">ubiquitous `/juː'bɪkwɪtəs/` 到处存在的</div>
<div style="width: 50%; float:left;">untether `/ʌn'teðə/` 解下(拴牛马的)绳，链</div>
<div style="width: 50%; float:left;">heterogeneous `/ˌhetərə'dʒiːniəs/` （计算机）非均匀的，异种的，异质的，由不同成分形成的</div>
<div style="width: 50%; float:left;">refrigerator `/rɪ'frɪdʒəreɪtə(r)/` 冰箱</div>