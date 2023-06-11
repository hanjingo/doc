# 12 Concurrent Programming



Modern operating systems provide three basic approaches for building concurrent programs:

- `Processes`. With this approach, each logical control flow is a process that is scheduled and maintained by the kernel. Since processes have separate virtual address spaces, flows that want to communicate with each other must use some kind of explicit interprocess communication (IPC) mechanism.
- `I/O multiplexing`. This is a form of concurrent programming where applications explicitly schedule their own logical flows in the context of a single process. Logical flows are modeled as state machines that the main program explicitly transitions from state to state as a result of data arriving on file descriptors. Since the program is a single process, all flows share the same address space.
- `Threads`. Threads are logical flows that run in the context of a single process and are scheduled by the kernel. You can think of threads as a hybrid of the other two approaches, scheduled by the kernel-like process flows and sharing the same virtual address space like I/O multiplexing flows.

Pros and Cons of Processes:

- Having separate address spaces for processes is both an advantage and a disadvantage. It is impossible for one process to accidentally overwrite the virtual memory of another process, which eliminates a lot of confusing failures -- an obvious advantage.
- On the other hand, separate address spaces make it more difficult for processes to share state information. To share information, they must use explicit IPC(interprocess communications) mechanisms.
- Another disadvantage of process-based designs is that they tend to be slower because the overhead for process control and IPC is hight.

I/O multiplexing can be used as the basis for concurrent event-driven programs, where flows make progress as a result of cretain events.

The server uses the I/O multiplexing, courtesy of the select function, to detect the occurrence of input events. As each connected descriptor becomes ready for reading, the server executes the transition for the corresponding state machine.

Pros and Cons of I/O Multiplexing

- One advantage is that event-driven designs give programmers more control over the behavior of their programs than process-based designs.
- Another advantage is that an event-driven server based on I/O multiplexing runs in the context of a single process, and thus every logical flow has access to the entire address space of the process. This makes it easy to share data between flows.
- Finally, event-driven designs are often significantly more efficient than process-based designs because they do not require a process context switch to schedule a new flow.
- A significant disadvantage of event-driven designs is coding complexity.
- Another significant disadvantage of event-based designs is that they cannot fully utilize multi-core processors.

A thread is a logical flow that runs in the context of a process.

Thread execution differs from processes in some important ways:

- a thread context is much smaller than a process context.
- a thread context switch is faster than a process context switch.
- thread unlike processes, are not organized in a rigid parent-child hierarchy.

A thread terminates in one of the following ways:

- The thread terminates `implicitly` when its top-level thread routine returns.
- The thread terminates `explicitly` by calling the `pthread_exit` function.
- Some peer thread calls the Linux `exit` function, which terminates the process and all threads associated with the process.
- Another peer thread terminates the current thread by calling the `pthread_cancel` function with the ID of the current thread.

A joinable thread can be reaped and killed by other threads. Its memory resources (such as the stack) are not freed until it is reaped by another thread. In contrast, a detached thread cannot be reaped or killed by other threads. Its memory resources are freed automatically by the system when it terminates.

Thus, registers are never shared, whereas virtual memory is always shared.

Variables in threaded C programs are mapped to virtual memory according to their storage classes:

- `Global variables`. A global variable is any variable declared outside of a function. At run time, the read/write area of virtual memory contains exactly one instance of each global variable that can be referenced by any thread.
- `Local automatic variables`. A local automatic variable is one that is declared inside a function without the static attribute. At run time, each thread's stack contains its own instances of any local automatic variables. This is true even if multiple threads execute the same thread routine.
- `Local static variables`. A local static variable is one that is declared inside a function with the static attribute. As with global variables, the read/write area of virtual memory contains exactly one instance of each local static variable declared in a program.

We say that a variable `v` is shared if and only if one of its instances is referenced by more than one thread.

A progress graph models the execution of $n$ concurrent threads as a trajectory through an $n$-dimensional Cartesian space. Each axis $k$ corresponds to the progress of thread $k$. Each point $(I_1, I_2, ..., I_n)$ represents the state where thread $k(k = 1, ..., n)$ has completed instruction $I_k$. The origin of the graph corresponds to the initial state where none of the threads has yet completed an instruction.

In other words, we want to ensure that each thread has `mutually exclusive access` to the shared variable while it is executing the instructions in its critical section. The phenomenon in general is known as `mutual exclusion`.

On the progress graph, the intersection of the two critical sections defines a region of the state space known as an `unsafe region`.

A semaphore, $s$ is a global variable with a nonnegative integer value that can only be manipulated by two special operations, called $P$ and $V$:

- $P(s)$: If $s$ is nonzero, then $P$ decrements $s$ and returns immediately. If $s$ is zero, then suspend the thread until $s$ becomes nonzero and the thread is restarted by a $V$ operation. After restarting, the $P$ operation decrements $s$ and returns control to the caller.
- $V(s)$: The $V$ operation increments $s$ by 1. If there are any threads blocked at a $P$ operation waiting for $s$ to become nonzero, then the $V$ operation restarts exactly one of these threads, which then completes its $P$ operation by decrementing $s$.

when several threads are waiting at a semaphore, you cannot predict which one will be restarted as a result of the $V$.

The definitions of $P$ and $V$ ensure that a running program can never enter a state where a properly initialized semaphore has a negative value. This property, known as the semaphore invariant, provides a powerful tool for controlling the trajectories of concurrent programs.

Semaphores provide a convenient way to ensure mutually exclusive access to shared variables. The basic idea is to associate a semaphore $s$, initially 1, with each shared variable (or related set of shared variables) and then surround the corresponding critical section with $P(s)$ and $V(s)$ operations.

A semaphore that is used in this way to protect shared variables is called a `binary semaphore` because its value is always 0 or 1.

Binary semaphores whose purpose is to provide mutual exclusion are often called `mutexes`.

Performing a $P$ operation on a mutex is called `locking` the mutex.

Performing the $V$ operation is called `unlocking` the mutex.

A thread that has locked but not yet unlocked a mutex is said to be `holding` the mutex.

A semaphore that is used as a counter for a set of available resources is called a `counting sempahore`.

**Synchronization overhead is expensive and should be avoided if possible. If it cannot be avoided, the overhead should be amortized by as much useful computation as possible.**



## Glossary

<div style="width: 50%; float:left;">bibliographic `/ˌbibliə'ɡræfik,-kəl/` 书籍解题的,著书目录的</div>
<div style="width: 50%; float:left;">phenomenon `/fəˈnɒmɪnən/` 现象，杰出的人，奇人，奇事</div>
<div style="width: 50%; float:left;">exploit `/ɪkˈsplɔɪt/` 剥削，压榨，利用，开发，功绩，英勇行为</div>
<div style="width: 50%; float:left;">coalesce `/ˌkəʊə'les/` 合并，联合，接合</div>
<div style="width: 50%; float:left;">soak `/səʊk/` 侵泡，渗透，渗入，吸入，使喝醉</div>
<div style="width: 50%; float:left;">uniprocessor `/'juːnɪprəʊsesər/` （计算机）单处理器（单机）</div>
<div style="width: 50%; float:left;">investigate `/ɪn'vestɪɡeɪt/` 调查，研究</div>
<div style="width: 50%; float:left;">Pros `/prəʊ/` 正面，正面的，能手，行家，专业的</div>
<div style="width: 50%; float:left;">Cons `/kɔn/` 反面，发面的，骗局，精读，记诵</div>
<div style="width: 50%; float:left;">arbitrary `/ˈɑːbɪtrəri/` 任意的，武断的，随心所欲的，专制的</div>
<div style="width: 50%; float:left;">hodgepodge `/'hɒdʒpɒdʒ/` 混煮，杂烩菜</div>
<div style="width: 50%; float:left;">dilemma `/dɪˈlemə/` 困境，进退两难的
</div>
<div style="width: 50%; float:left;">scenario /sɪˈnɑː.ri.əʊ/ 可能发生的事态，设想，剧本，情节，情况
</div>
<div style="width: 50%; float:left;">courtesy `/'kɜːtəsi/` 礼貌，好意</div>
<div style="width: 50%; float:left;">granularity `/grænjʊ'lærɪtɪ/` 颗粒度，粒度</div>
<div style="width: 50%; float:left;">maxi `/'mæksi/` 长裙，最大，最长</div>
<div style="width: 50%; float:left;">complexity `/kəm'pleksəti/` 复杂性，复杂度</div>
<div style="width: 50%; float:left;">vulnerable `/'vʌlnərəbl/` 易受伤害的，有弱点的，脆弱的</div>
<div style="width: 50%; float:left;">malicious `/məˈlɪʃəs/` 恶毒的，蓄意的，怀有恶意的</div>
<div style="width: 50%; float:left;">adopt `/ə'dɒpt/` 采用，收养，接受</div>
<div style="width: 50%; float:left;">dissect `/dɪ'sekt/` 解剖，切细，仔细研究，详细分析</div>
<div style="width: 50%; float:left;">encapsulate `/ɪnˈkæpsjuleɪt/` 概括，压缩，简述，装入胶囊，包装
</div>
<div style="width: 50%; float:left;">reap `/riːp/` 收割，获得，收获</div>
<div style="width: 50%; float:left;">arbitrary `/ˈɑːbɪtrəri/` 任意的，武断的，随心所欲的，专制的</div>
<div style="width: 50%; float:left;">intuitive `/ɪn'tjuːɪtɪv/` 直觉的</div>
<div style="width: 50%; float:left;">specification `/ˌspesɪfɪ'keɪʃn/` 规格，详述</div>
<div style="width: 50%; float:left;">overall `/ˌəʊvərˈɔːl/` 全面的，全部的，总体的，总计</div>
<div style="width: 50%; float:left;">perspective `/pə'spektɪv/` 远景，看法，透视</div>
<div style="width: 50%; float:left;">aspect `/ˈæspekt/`  外表，面貌，方面，层面，方位</div>
<div style="width: 50%; float:left;">nonetheless `/ˌnʌnðə'les/` 尽管如此(仍然)</div>
<div style="width: 50%; float:left;">reside `/rɪ'zaɪd/` 居住，属于，存在</div>
<div style="width: 50%; float:left;">denote `/dɪˈnəʊt/` 标志，象征，表示，预示</div>
<div style="width: 50%; float:left;">niters</div>
<div style="width: 50%; float:left;">trajectory `/trə'dʒektəri/` 轨道，弹道，轨迹</div>
<div style="width: 50%; float:left;">cartesian `/kɑː'tiːziən/` （数学）笛卡尔的</div>
<div style="width: 50%; float:left;">correspond `/kɒrɪˈspɒnd/` 通信，相符，符合</div>
<div style="width: 50%; float:left;">diagonal `/daɪˈæɡənl/` 斜线，对角线</div>
<div style="width: 50%; float:left;">critical `/ˈkrɪtɪkl/` 关键的，严重的，致命的</div>
<div style="width: 50%; float:left;">mutually `/'mjuːtʃuəli/` 相互的，彼此的</div>
<div style="width: 50%; float:left;">abuts `/ə'bʌt/` 邻接，毗连</div>
<div style="width: 50%; float:left;">perimeter `/pə'rɪmɪtə(r)/` 周长，周界，边缘</div>
<div style="width: 50%; float:left;">skirt `/skɜːt/` 裙子，下摆，边缘，教区，挡板，绕开</div>
<div style="width: 50%; float:left;">infeasible `/ɪn'fiːzəbl/` 行不通的，不可实行的</div>
<div style="width: 50%; float:left;">crucial `/'kruːʃl/` 决定性的，关键的</div>
<div style="width: 50%; float:left;">trajectory `/trə'dʒektəri/` 轨道，弹道，轨迹</div>
<div style="width: 50%; float:left;">visualize `/'vɪʒuəlaɪz/` 看得见，形象化，设想</div>
<div style="width: 50%; float:left;">scenario `/sɪˈnɑː.ri.əʊ/` 可能发生的事态，设想，剧本，情节，情况</div>
<div style="width: 50%; float:left;">bound `/baʊnd/` 约束，捆绑，界限，必然的，注定的，跳跃
</div>
<div style="width: 50%; float:left;">exclusive `/ɪkˈskluːsɪv/` 专有的，独占的，专有的，排外的，独家</div>
<div style="width: 50%; float:left;">jitter `/'dʒɪtə/` 振动，紧张</div>
<div style="width: 50%; float:left;">reservoir `/ˈrezəvwɑː(r)/` 水库，储水池，储存器</div>
<div style="width: 50%; float:left;">prethreading `//` （计算机）预分配线程</div>
<div style="width: 50%; float:left;">indicate `/ˈɪndɪkeɪt/` 指示，说明，象征，显示，预示</div>
<div style="width: 50%; float:left;">symmetric `/sɪ'metrɪk/` 对称的</div>
<div style="width: 50%; float:left;">denote `/dɪˈnəʊt/` 标志，象征，表示，预示</div>
<div style="width: 50%; float:left;">scenario `/sɪˈnɑː.ri.əʊ/` 可能发生的事态，设想，剧本，情节，情况</div>
<div style="width: 50%; float:left;">interaction `/ˌɪntər'ækʃn/` 相互作用，相互影响</div>
<div style="width: 50%; float:left;">inspect `/ɪnˈspekt/` 检查，审查，查看，视察</div>
<div style="width: 50%; float:left;">favor `/'feɪvə/` 偏爱，好意，特权，赞成，给予，支持，关心</div>
<div style="width: 50%; float:left;">granted `/'ɡrɑːntɪd/` 的确，假定</div>
<div style="width: 50%; float:left;">deceptive `/dɪ'septɪv/` 骗人的，虚伪的，欺诈的</div>
<div style="width: 50%; float:left;">unimpeded `/ˌʌnɪm'piːdɪd/` 未受阻的，畅通无阻的</div>
<div style="width: 50%; float:left;">starvation `/stɑː'veɪʃn/` 饿死，饥饿</div>
<div style="width: 50%; float:left;">incur `/ɪnˈkɜːr/` 招致，引起，遭受，带来</div>
<div style="width: 50%; float:left;">nontrivial `/'nɒn'trɪvɪəl/` 非平凡的，重要的</div>
<div style="width: 50%; float:left;">mutual `/ˈmjuːtʃʊəl/` 相互的，关系对等的，共用的，互助的</div>
<div style="width: 50%; float:left;">exclusion `/ɪk'skluːʒn/` 排除，除外，逐出</div>
<div style="width: 50%; float:left;">cumulative `/'kjuːmjələtɪv/` 累积的，累计的，渐增的</div>
<div style="width: 50%; float:left;">sequential `/sɪ'kwenʃl/` 连续的</div>
<div style="width: 50%; float:left;">exploit `/ɪkˈsplɔɪt/` 剥削，压榨，利用，开发，功绩，英勇行为</div>
<div style="width: 50%; float:left;">mainstream `/'meɪnstriːm/` 主流</div>
<div style="width: 50%; float:left;">spreadsheet `/'spredʃiːt/` 电子制表软件，电子表格，试算表</div>
<div style="width: 50%; float:left;">disjoint `/dɪs'dʒɔɪnt/` 脱节，解体</div>
<div style="width: 50%; float:left;">treatment `/ˈtriːtm(ə)nt/` 对待，论述，探讨，治疗，处理</div>
<div style="width: 50%; float:left;">concise `/kən'saɪs/` 简明的，简要的</div>
<div style="width: 50%; float:left;">nasty `/'nɑːsti/` 下流的，严重的</div>
<div style="width: 50%; float:left;">extremely `/ɪk'striːmli/` 非常，极其</div>
<div style="width: 50%; float:left;">magnitude `/ˈmæɡnɪtjuːd/` 巨大，重大，重要性，地震等级</div>
<div style="width: 50%; float:left;">lesson `/'lesn/` 课程，榜样，典范，训斥，告诫</div>
<div style="width: 50%; float:left;">amortize `/ə'mɔːtaɪz/` 分期偿还，摊还</div>
<div style="width: 50%; float:left;">partial `/ˈpɑːʃl/` 部分，不完全的，偏爱</div>
<div style="width: 50%; float:left;">magnitude `/ˈmæɡnɪtjuːd/` 巨大，重大，重要性，地震等级</div>
<div style="width: 50%; float:left;">eliminate `/ɪˈlɪmɪneɪt/` 消灭，铲除，排除，淘汰</div>
<div style="width: 50%; float:left;">summing `/'sʌmɪŋ/` 求和，合计，概述</div>
<div style="width: 50%; float:left;">elapse `/əˈlaps/` 逝去（时间），过去</div>
<div style="width: 50%; float:left;">tricky `/'trɪki/` 棘手的，狡猾的，巧妙的</div>
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