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
<div style="width: 50%; float:left;">preemptive</div>
<div style="width: 50%; float:left;">drawback</div>
<div style="width: 50%; float:left;">recourse</div>
<div style="width: 50%; float:left;">cursor</div>
<div style="width: 50%; float:left;">transition</div>
<div style="width: 50%; float:left;">intentionally</div>
<div style="width: 50%; float:left;">inadvertently</div>
<div style="width: 50%; float:left;">benign</div>
<div style="width: 50%; float:left;">transparently</div>
<div style="width: 50%; float:left;">descriptors</div>
<div style="width: 50%; float:left;">forth</div>
<div style="width: 50%; float:left;">decouples</div>
<div style="width: 50%; float:left;">arbitrary</div>
<div style="width: 50%; float:left;">gnarly</div>
<div style="width: 50%; float:left;">wiser</div>
<div style="width: 50%; float:left;">incremented</div>
<div style="width: 50%; float:left;">dedicated</div>
<div style="width: 50%; float:left;">bottleneck</div>
<div style="width: 50%; float:left;">contention</div>
<div style="width: 50%; float:left;">perspective</div>
<div style="width: 50%; float:left;">demultiplex</div>
<div style="width: 50%; float:left;">accomplish</div>
<div style="width: 50%; float:left;">suspend</div>
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