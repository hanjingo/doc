# Chapter 2 The Kernel Abstraction



Protection is essential to achieving several of the goals we listed for operating systems:

- Reliability.
- Security.
- Privacy.
- Efficiency.

`operating system kernel`. The kernel is the lowest level of sofeware running on the system, with full access to all of the capabilities of the hardware.

A `process` is the abstraction for protection provided by the operating system kernel: the execution of an application program with restricted rights.

Protection raises several important questions:

- The process abstraction.
- Dual-mode operation.
- Safe control transfer: exceptions, interrupts, and system calls.
- Booting the kernel.

A compiler converts that code into a sequence of machine instructions, and stores those instructions into a file, called the `executable image` of the program.

most operating systems are designed to reuse memory wherever possible: they store only a single copy of a program's instructions when multiple copies of the program are executed at the same time.

The operating system keeps track of the various processes on the computer using a data structure called the `process control block`. The process control block stores all the information the operating system needs about a particular process.

`dual-mode operation`, represented by a single bit in the processor status register to signify which mode the processor is currently executing in. 

In `user-mode`, the processor checks each instruction before executing it to verify that the instruction is permitted to be performed by that process.

In `kernel-mode`, the operating system executes with protection checks turned off.

the hardware must support three things:

- `Privileged instructions`.
- `Memory protection`.
- `Timer interrupts`.

that processes can indirectly change their privilege level by executing a special instruction called a `system call` to transfer control into the kernel at a fixed location specified by the operating system.

Instructions available in kernel-mode, but not in user-mode, are called, naturally enough, `privileged instructions`.

A processor has two extra registers, called `base and bounds`. The base specifies the start of process's memory region, while the bound gives its length.

Although the base and bounds mechanism is sufficient for implementing protection, it is unable to provide some important features:

- Expandable heap and stack.
- Memory sharing.
- Non-relative memory addresses.
- Memory fragmentation.

Almost all computer systems include a device called a `hardware timer` which can be set to interrupt the processor after a specified delay, either in time or after some number of instructions have been executed.

There are three reasons for why the kernel will take control from a user process:

- Exceptions. A processor `exception` is any unexpected condition caused by user program behavior.
- Interrupts. An `interrupt` is an asynchronous signal to the processor that some external event has occurred that may require its attention.
- System calls. A `system call` is any procedure provided by the kernel that can be called from user-level.

There are several causes for transitions from kernel-mode to user-mode:

- New process.
- Resume after an exception, interrupt or system call.
- Switch to a different process.
- User-level upcall.

we need the processor to save its state and switch what it is doing, all while it continues to execute instructions that might alter the state that is in the process of saving.

most operating systems have a common sequence of instructions for entering the kernel, this common sequence must provide:

- Limited entry.
- Atomic changes to processor state.
- Transparent, restartable execution.

To identify the code to run on a context switch, the processor will include a special register that points to an area of kernel memory called the `interrupt vector`. The interrupt vector is an array of pointers, with each entry pointing to the first instruction of a different handler procedure in the kernel.

We use a separate kernel-level interrupt stack for two reasons:

-  First, having a dedicated stack is necessary for reliability.
- Second, having a protected stack is necessary for security.

![2_8](res/2_8.png)

*Kernel and user stacks for various states of a process*

1. If the process is running on the processor in user-mode, its kernel stack is empty, ready to be used for an interrupt.
2. If the process is running on the processor in kernel-mode, e.g., due to an interrupt, exception or system call trap, its kernel stack is in use, containing the saved registers from the suspended user-level computation, as well as the current state of the kernel handler.
3. If the process is available to run but is waiting for its turn on the processor, its kernel stack contains the registers and state to be restored when the process is resumed.
4. If the process is waiting for an I/O event to complete, its kernel stack contains the suspended computation to be resumed when the I/O finishes.

When a context switch occurs the x86 hardware:

- If in user-mode, pushes the interrupted process's stack pointer onto the kernel's exception stack, and switches to the kernel stack.
- Pushes the interrupted process's instruction pointer.
- Pushes the x86 `processor status word`.

x86 has complementary features for restoring state: a `popad` instruction to pop an array of integer register values off the stack into the registers and an `iret` (return from interrupt) instruction that loads a stack pointer, instruction pointer, and processor status word off of the stack into the appropriate processor registers.

The kernel should assume the parameters to each system call are intentionally designed to corrupt the kernel.

A `pair of stubs` are two short procedures that mediate between two environments.

The kernel stub has four tasks:

- Locate system call arguments.
- Validate parameters.
- Copy before check.
- Copy back any results.





## Glossary

<div style="width: 50%; float:left;">corrupt `/kəˈrʌpt/` 贪污，腐败，不道德的，破坏，损坏</div>
<div style="width: 50%; float:left;">bullet `/'bʊlɪt/` 子弹，弹丸</div>
<div style="width: 50%; float:left;">surreptitiously `/ˌsʌrəp'tɪʃəsli/` 偷偷摸摸地，暗中地</div>
<div style="width: 50%; float:left;">wise `/waɪz/` 明智的，英明的，有见识的</div>
<div style="width: 50%; float:left;">privacy `/ˈprɪvəsi/` 隐私，自由，独处，私生活</div>
<div style="width: 50%; float:left;">buggy `/ˈbʌɡi/` 婴儿车，折叠式童车，轻便马车，专用小车</div>
<div style="width: 50%; float:left;">stalled `/stɔːld/` 被困住的</div>
<div style="width: 50%; float:left;">rogue `/rəʊɡ/` 流氓，游手好闲，欺诈，离群野兽</div>
<div style="width: 50%; float:left;">akin `/əˈkɪn/` 类似的</div>
<div style="width: 50%; float:left;">insane `/ɪn'seɪn/` 疯狂的，精神错乱的，荒唐的</div>
<div style="width: 50%; float:left;">asylum `/ə'saɪləm/` 收容所，避难所，精神病院，（政治）庇护</div>
<div style="width: 50%; float:left;">warden `/'wɔːdn/` 看守人，典狱长</div>
<div style="width: 50%; float:left;">inmate `/'ɪnmeɪt/` 同住者，犯人，居民</div>
<div style="width: 50%; float:left;">straightjacket `/ˈstreɪtdʒækɪt/` 紧身衣，束缚</div>
<div style="width: 50%; float:left;">dual `/ˈdjuːəl/` 两部分，双重的</div>
<div style="width: 50%; float:left;">efficient `/ɪˈfɪʃnt/` 高效的，有能力的</div>
<div style="width: 50%; float:left;">procedure `/prəˈsiːdʒə/` 程序</div>
<div style="width: 50%; float:left;">devote `/dɪˈvəʊt/` 致力于，奉献，投入时间，专注于</div>
<div style="width: 50%; float:left;">immense `/ɪˈmens/` 巨大的，极大的</div>
<div style="width: 50%; float:left;">prevent `/prɪˈvent/` 阻止，阻挠，阻碍，预防</div>
<div style="width: 50%; float:left;">hypothetical `/ˌhaɪpə'θetɪkl/` 假定的，假设的</div>
<div style="width: 50%; float:left;">crucial `/'kruːʃl/` 决定性的，关键的</div>
<div style="width: 50%; float:left;">fate `/feɪt/` 命运，宿命</div>
<div style="width: 50%; float:left;">trapping `/'træpɪŋ/` 装饰物，象征的符号</div>
<div style="width: 50%; float:left;">rogue `/rəʊɡ/` 流氓，游手好闲，欺诈，离群野兽</div>
<div style="width: 50%; float:left;">violation `/ˌvaɪə'leɪʃn/` 违反，违背，妨碍</div>
<div style="width: 50%; float:left;">instant `/ˈɪnstənt/` 立即，立刻</div>
<div style="width: 50%; float:left;">browse `/braʊz/` 浏览，随意观看，吃草，嫩叶</div>
<div style="width: 50%; float:left;">attacker `/ə'tækə(r)/` 攻击者，抨击者</div>
<div style="width: 50%; float:left;">extravagant `/ɪk'strævəɡənt/` 奢侈的，浪费的，过度的，大量的</div>
<div style="width: 50%; float:left;">inadvertently `/ˌɪnəd'vɜːtəntli/` 不注意地，疏忽地，非故意地</div>
<div style="width: 50%; float:left;">regain `/rɪ'ɡeɪn/` 恢复，重回</div>
<div style="width: 50%; float:left;">preemptive `/prɪ'emptɪv/` adj. 优先购买的；先发制人的</div>
<div style="width: 50%; float:left;">recourse `/rɪ'kɔːs/` n. 依赖；求助；追索权</div>
<div style="width: 50%; float:left;">transition `/træn'zɪʃn/` n. 转变；过渡</div>
<div style="width: 50%; float:left;">intentional `/ɪn'tenʃənl/` adj. 存心的；故意的</div>
<div style="width: 50%; float:left;">inadvertently `/ˌɪnəd'vɜːtəntli/` adv. 不注意地；疏忽地；非故意地</div>
<div style="width: 50%; float:left;">benign `/bɪˈnaɪn/` adj. 仁慈的；温和的；良性的</div>
<div style="width: 50%; float:left;">transparent `/trænsˈpærənt/` adj. 透明的；明显的；清晰的</div>
<div style="width: 50%; float:left;">descriptor `/dɪ'skrɪptə(r)/` n. 描述符</div>
<div style="width: 50%; float:left;">forth `/fɔːθ/` adv. 向前；向外；露出</div>
<div style="width: 50%; float:left;">decouple `/diːˈkʌpl/` vt. 分离；拆散；解耦</div>
<div style="width: 50%; float:left;">arbitrary `/ˈɑːbɪtrəri/` adj. 任意的；专制的；武断的；霸道的</div>
<div style="width: 50%; float:left;">gnarly `/'nɑːli/` adj. 扭曲的；粗糙的；多瘤节的</div>
<div style="width: 50%; float:left;">wise `/waɪz/` adj. 聪明的；有智慧的；明智的；有见识的</div>
<div style="width: 50%; float:left;">increment `/'ɪŋkrəmənt/` n. 增量；增加；增值；增额</div>
<div style="width: 50%; float:left;">dedicate `/'dedɪkeɪt/` vt. 致力于；献出；提献辞</div>
<div style="width: 50%; float:left;">contention `/kən'tenʃn/` n. 争论；争辩；争夺；论点</div>
<div style="width: 50%; float:left;">perspective `/pə'spektɪv/` n. 远景；看法；透视；adj. 透视的</div>
<div style="width: 50%; float:left;">demultiplex `/dɪmʌltɪp'leks/` n. （计算机）多路处理，多路化，多路分解</div>
<div style="width: 50%; float:left;">accomplish `/əˈkʌmplɪʃ/` vt. 完成；实现</div>
<div style="width: 50%; float:left;">suspend `/sə'spend/` v. 暂停；悬浮；中止；勒令停职</div>
<div style="width: 50%; float:left;">obliterate `/ə'blɪtəreɪt/` v. 涂去；擦去；删除；盖销（邮票等）</div>
<div style="width: 50%; float:left;">misnomer `/ˌmɪs'nəʊmə(r)/` n. 误称；用词不当</div>
<div style="width: 50%; float:left;">premium `/'priːmiəm/` n. 额外费用；奖金；保险费；n. (商)溢价；adj. 高价的；优质的</div>
<div style="width: 50%; float:left;">freeze `/friːz/` v. 冻结；冷冻；僵硬；凝固；n. 严寒；冻结</div>
<div style="width: 50%; float:left;">invocation `/ˌɪnvə'keɪʃn/` n. （计算机）调用；祈祷；实施</div>
<div style="width: 50%; float:left;">halves `/hɑːvz/` n. 一半（half的复数形式）</div>
<div style="width: 50%; float:left;">terminology `/ˌtɜːmɪˈnɒlədʒi/` n. 术语；术语学</div>
<div style="width: 50%; float:left;">dummy `/ˈdʌmi/` n. 傀儡；假人；仿制品；笨蛋；哑巴；adj. 假的；仿造的；vt. 保密</div>
<div style="width: 50%; float:left;">trap `/træp/` n. 圈套；陷阱；困境；双轮轻便马车；U（或S）型管道；防臭瓣；v. 设圈套；陷入（困境）</div>
<div style="width: 50%; float:left;">stub `/stʌb/` n. 烟蒂；残段；票根；v. 碰到某物；捻灭(香烟)</div>
<div style="width: 50%; float:left;">oblivious `/ə'blɪviəs/` adj. 没注意到；健忘的</div>
<div style="width: 50%; float:left;"></div>
<div style="width: 50%; float:left;"></div>
<div style="width: 50%; float:left;"></div>
<div style="width: 50%; float:left;"></div>
<div style="width: 50%; float:left;"></div>
<div style="width: 50%; float:left;"></div>
<div style="width: 50%; float:left;"></div>
<div style="width: 50%; float:left;"></div>
<div style="width: 50%; float:left;"></div>
<div style="width: 50%; float:left;"></div>
<div style="width: 50%; float:left;"></div>
<div style="width: 50%; float:left;"></div>
<div style="width: 50%; float:left;"></div>
<div style="width: 50%; float:left;"></div>
<div style="width: 50%; float:left;"></div>
<div style="width: 50%; float:left;"></div>
<div style="width: 50%; float:left;"></div>
<div style="width: 50%; float:left;"></div>
<div style="width: 50%; float:left;"></div>
<div style="width: 50%; float:left;"></div>
<div style="width: 50%; float:left;"></div>
<div style="width: 50%; float:left;"></div>
<div style="width: 50%; float:left;"></div>
<div style="width: 50%; float:left;"></div>
<div style="width: 50%; float:left;"></div>
<div style="width: 50%; float:left;"></div>