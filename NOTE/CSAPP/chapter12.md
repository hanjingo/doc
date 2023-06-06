# 12 Concurrent Programming



Modern operating systems provide three basic approaches for building concurrent programs:

- `Processes`. With this approach, each logical control flow is a process that is scheduled and maintained by the kernel. Since processes have separate virtual address spaces, flows that want to communicate with each other must use some kind of explicit interprocess communication (IPC) mechanism.
- `I/O multiplexing`. This is a form of concurrent programming where applications explicitly schedule their own logical flows in the context of a single process. Logical flows are modeled as state machines that the main program explicitly transitions from state to state as a result of data arriving on file descriptors. Since the program is a single process, all flows share the same address space.
- `Threads`. Threads are logical flows that run in the context of a single process and are scheduled by the kernel. You can think of threads as a hybrid of the other two approaches, scheduled by the kernel-like process flows and sharing the same virtual address space like I/O multiplexing flows.

Pros and Cons of Processes:

- Having separate address spaces for processes is both an advantage and a disadvantage. It is impossible for one process to accidentally overwrite the virtual memory of another process, which eliminates a lot of confusing failures -- an obvious advantage.
- On the other hand, separate address spaces make it more difficult for processes to share state information. To share information, they must use explicit IPC(interprocess communications) mechanisms.
- Another disadvantage of process-based designs is that they tend to be slower because the overhead for process control and IPC is hight.





## Glossary

<div style="width: 50%; float:left;">bibliographic `/ˌbibliə'ɡræfik,-kəl/` 书籍解题的,著书目录的</div>
<div style="width: 50%; float:left;">phenomenon `/fəˈnɒmɪnən/` 现象，杰出的人，奇人，奇事</div>
<div style="width: 50%; float:left;">exploit `/ɪkˈsplɔɪt/` 剥削，压榨，利用，开发，功绩，英勇行为</div>
<div style="width: 50%; float:left;">coalesce `/ˌkəʊə'les/` 合并，联合，接合</div>
<div style="width: 50%; float:left;">soak `/səʊk/` 侵泡，渗透，渗入，吸入，使喝醉</div>

<div style="width: 50%; float:left;">uniprocessor</div>
<div style="width: 50%; float:left;">investigates</div>
<div style="width: 50%; float:left;">Pros</div>
<div style="width: 50%; float:left;">Cons</div>
<div style="width: 50%; float:left;">arbitrary `/ˈɑːbɪtrəri/` 任意的，武断的，随心所欲的，专制的</div>
<div style="width: 50%; float:left;">hodgepodge</div>
<div style="width: 50%; float:left;">dilemma `/dɪˈlemə/` 困境，进退两难的
</div>
<div style="width: 50%; float:left;">scenario /sɪˈnɑː.ri.əʊ/ 可能发生的事态，设想，剧本，情节，情况
</div>
<div style="width: 50%; float:left;"></div>
<div style="width: 50%; float:left;"></div>
<div style="width: 50%; float:left;"></div>
<div style="width: 50%; float:left;"></div>
<div style="width: 50%; float:left;"></div>
<div style="width: 50%; float:left;"></div>