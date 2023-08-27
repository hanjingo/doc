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





## Glossary

<div style="width: 50%; float:left;">corrupt `/kəˈrʌpt/` 贪污，腐败，不道德的，破坏，损坏</div>
<div style="width: 50%; float:left;">bullet `/'bʊlɪt/` 子弹，弹丸</div>
<div style="width: 50%; float:left;">surreptitiously</div>
<div style="width: 50%; float:left;">wiser</div>
<div style="width: 50%; float:left;">privacy</div>
<div style="width: 50%; float:left;">buggy</div>
<div style="width: 50%; float:left;">stalled</div>
<div style="width: 50%; float:left;">rogue</div>
<div style="width: 50%; float:left;">akin</div>
<div style="width: 50%; float:left;">insane</div>
<div style="width: 50%; float:left;">asylum</div>
<div style="width: 50%; float:left;">warden</div>
<div style="width: 50%; float:left;">inmate</div>
<div style="width: 50%; float:left;">straightjacket</div>
<div style="width: 50%; float:left;">dual</div>
<div style="width: 50%; float:left;">efficient</div>
<div style="width: 50%; float:left;">procedure</div>
<div style="width: 50%; float:left;">devote</div>
<div style="width: 50%; float:left;">immensely</div>
<div style="width: 50%; float:left;">prevent</div>
<div style="width: 50%; float:left;">hypothetical</div>
<div style="width: 50%; float:left;">crucial</div>
<div style="width: 50%; float:left;">fate</div>
<div style="width: 50%; float:left;">trapping</div>
<div style="width: 50%; float:left;">rogue</div>
<div style="width: 50%; float:left;">violations</div>
<div style="width: 50%; float:left;">instant</div>
<div style="width: 50%; float:left;">browse</div>
<div style="width: 50%; float:left;">attacker</div>
<div style="width: 50%; float:left;">extravagant</div>
<div style="width: 50%; float:left;">inadvertently</div>
<div style="width: 50%; float:left;">regain</div>
<div style="width: 50%; float:left;">inadvertently</div>
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