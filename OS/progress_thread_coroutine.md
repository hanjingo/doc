# Process, Thread And Coroutine

[TOC]



## Process

A `process` is the operating system's abstraction for a running program. By `concurrently`, we mean that the instructions of one process are interleaved with the instructions of another process.

### Process Context Switch

The operating system kernel implements multitasking using a higher-level form of exceptional control flow known as a `context switch`.

![proc_ctx_switch](res/proc_ctx_switch.png)

The kernel maintains a `context` for each process. The context is the state that the kernel needs to restart a preempted process. It consists of the values of objects such as the general-purpose registers, the floating-point registers, the program counter, user's stack, status registers, kernel's stack, and various kernel data structures such as a `page table` that characterizes the address space, a `process table` that contains information about the current process, and a `file table` that contains information about the files that the process has opened.

A context switch can occur while the kernel is executing a system call on behalf of the user.

A context switch can also occur as a result of an interrupt.

### Process States

From a programmer's perspective, we can think of a process as being in one of three states:

- `Running`. The process is either executing on the CPU or waiting to be executed and will eventually be scheduled by the kernel.
- `Stopped`. The execution of the process is suspended and will not be scheduled. A process stops as a result of receiving a SIGSTOP, SIGTSTP, SIGTTIN, or SIGTTOU signal, and it remains stopped until it receives a SIGCONT signal, and it remains stopped until it receives a SIGCONT signal, at which point it becomes running again.
- `Terminated`. The process is stopped permanently. A process becomes terminated for one of three reasons: (1) receiving a signal whose default action is to terminate the process, (2) returning from the main routine, or (3) calling the `exit` function.

When a parent process terminates, the kernel arranges for the `init` process to become the adopted parent of any orphaned children. The `init` process, which has a PID of 1, is created by the kernel during system start-up, never terminates, and is the ancestor of every process. If a parent process terminates without reaping its zombie children, then the kernel arranges for the init process to reap them. 

### Signal

A signal is a small message that notifies a process that an event of some type has occurred in the system.

Each signal type corresponds to some kind of system event. Low-level hardware exceptions are processed by the kernel's exception handlers and would not normally be visible to user processes. Signals provide a mechanism for exposing the occurrence of such exceptions to user processes.

The transfer of a signal to a destination process occurs in two distinct steps:

1. `Sending a signal`. The kernel sends (delivers) a signal to a destination process by updating some state in the context of the destination process. The signal is delivered for one of two reasons: (1) The kernel has detected a system event such as a divide-by-zero error or the termination of a child process. (2) A process has invoked the `kill` function (discussed in the next section) to explicitly request the kernel to send a signal to the destination process. A process can send a signal to itself.

2. `Receiving a signal`. A destination process `receives` a signal when it is forced by the kernel to react in some way to the delivery of the signal. The process can either ignore the signal, terminate, or catch the signal by executing a user-level function called a `signal handler`.

![sig_handle](res/sig_handle.png)

A signal that has been sent but not yet received is called a `pending signal`. At any point in time, there can be at most one pending signal of a particular type. If a process has a pending signal of type $k$, then any subsequent signals of type $k$ sent to that process are not queued; they are simply discarded. A process can selectively `block` the receipt of certain signals. When a signal is blocked, it can be delivered, but the resulting pending signal will not be received until the process unblocks the signal.

A pending signal is received at most once. For each process, the kernel maintains the set of pending signals in the pending bit vector, and the set of blocked signals in the blocked bit vector. The kernel sets bit $k$ in pending whenever a signal of type $k$ is delivered and clears bit $k$ in pending whenever a signal of type $k$ is received.

Each signal type has a predefined `default` action, which is one of the following:

- The process terminates.
- The process terminates and dumps core.
- The process stops (suspends) until restarted by a SIGCONT signal.
- The process ignores the signal.

Linux provides implicit and explicit mechanisms for blocking signals:

- `Implicit blocking mechanism`. By default, the kernel blocks any pending signals of the type currently being processed by a handler.
- `Explicit blocking mechanism`. Applications can explicitly block and unblock selected signals using the `sigprocmask` function and its helpers.

---



## Thread

---



## Coroutine

---



## Reference

[1] Randal E. Bryant, David R. O'Hallaron . COMPUTER SYSTEMS: A PROGRAMMER'S PERSPECTIVE . 3ED

