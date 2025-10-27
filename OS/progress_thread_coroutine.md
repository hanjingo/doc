# Processes, Threads, and Coroutines

[TOC]

This note compares processes, threads, and coroutines from a programmer's perspective. It clarifies their semantics, trade-offs, common pitfalls (signals, synchronization, deadlocks, races), and when to prefer one model over another. Diagrams in `res/` illustrate context switch and signal handling.

## Concurrency models — short overview

Modern systems commonly use three approaches to structure concurrent programs:

- Processes: each logical flow runs in its own OS process with an independent virtual address space.
- Threads: multiple lightweight flows (threads) share a process address space and are scheduled by the kernel (or sometimes in user space).
- Coroutines: cooperative, user-space routines that explicitly yield control; they are lightweight and enable event-driven designs without kernel scheduling overhead.

Each model trades isolation, performance, and programming complexity differently. Processes provide strong isolation but higher IPC overhead; threads share memory and are easier for shared-state programs but require careful synchronization; coroutines give fine-grained control with minimal scheduling cost but move complexity to the application.

## Processes

A process is the OS abstraction for a running program. From a programmer's perspective, concurrency between processes means their instructions interleave on the CPU(s).

Pros:

- Strong isolation: separate address spaces prevent accidental memory corruption across processes.
- Fault containment: a crashed process usually does not corrupt other processes.

Cons:

- IPC overhead: communication requires explicit mechanisms (pipes, sockets, shared memory, etc.).
- Higher creation and context-switch cost compared to threads.

### Context switching

The kernel stores a process's context (registers, program counter, kernel stack, page table pointer, and other OS structures) and restores it to resume execution. Context switches may be triggered by interrupts, blocking syscalls, or preemption.

See `res/proc_ctx_switch.png` for a conceptual diagram.

### Process states and lifecycle

Typical states: running, runnable (ready), blocked (waiting), stopped, and terminated. Special behaviors include orphan adoption by `init` (PID 1) and zombie processes when children exit before being reaped.

### Signals

Signals are asynchronous notifications delivered by the kernel to processes to indicate events (e.g., SIGSEGV, SIGCHLD). Delivery has two phases: the kernel marks a signal pending for a process, and when the process next executes, the kernel arranges to deliver it (default action, ignore, or call a user-installed handler).

Key points:

- Signals are coarsely multiplexed: multiple deliveries of the same signal type may be merged into a single pending event.
- Applications can block signals (sigprocmask), handle them (sigaction), or ignore them.
- Signal handlers run asynchronously and must be careful about reentrancy and the limited-safe-list of functions they can call.

See `res/sig_handle.png` for an illustration.

## Threads

Threads are multiple flows of control within a single process. Threads share the same virtual address space and most OS resources; each thread has its own registers, stack, and thread-local storage.

Advantages:

- Lower creation/context-switch cost than processes.
- Easier sharing of in-process state (no IPC required).

Challenges:

- Synchronization: shared memory requires locks, atomics, or other coordination.
- Safety: data races and deadlocks are common pitfalls.

### Thread termination and joining

- A thread returns from its top-level routine or calls pthread_exit to terminate.
- Threads can be joinable (allowing another thread to wait and reap resources) or detached (resources freed automatically).
- The process `exit` terminates all threads in the process.

### Thread safety and reentrancy

- A function is thread-safe if it behaves correctly when invoked concurrently.
- Reentrant functions neither use nor mutate shared state and are safe to call from signal handlers or recursively.
- Common sources of thread-unsafety: global state, static buffers, and functions that return pointers to internal static storage.

Illustration: `res/reentrant.png` shows relationships between reentrant, thread-safe, and thread-unsafe routines.

### Synchronization primitives

- Mutexes and condition variables (pthread mutex/cond): standard blocking primitives for mutual exclusion and coordination.
- Semaphores: counting semaphores provide signaling and resource counting semantics (P and V operations).
- Atomics and lock-free algorithms: use hardware atomic instructions (compare-and-swap) for low-latency synchronization.

Deadlock: occurs when a cycle of threads waits on resources held by each other. Visual reasoning (progress graphs) helps understand possible deadlocks — see `res/progress_graph_deadlock.png`.

Design tips:

- Keep critical sections small and avoid holding locks during blocking operations.
- Use try-locks, lock ordering, or higher-level concurrency patterns to avoid deadlocks.

## Coroutines

Coroutines (also called fibers, green threads, or user-space threads in some contexts) are cooperatively scheduled routines that yield control explicitly. They are implemented in user space and do not require kernel scheduling for each switch.

Types and terminology:

- Stackful coroutines (fibers): maintain their own stack and can suspend from deep call stacks.
- Stackless coroutines: rely on the language/compiler to transform code into state machines (async/await, generators).
- Green threads: user-space threads that the runtime schedules onto kernel threads.

Advantages:

- Extremely lightweight: thousands or millions of coroutines are feasible because switching is cheap.
- Deterministic switching points: because yields are explicit, reasoning about control flow can be easier than preemptive threading.

Limitations:

- Cooperative scheduling: a misbehaving coroutine that never yields can starve others.
- Blocking syscalls: a blocking syscall in a coroutine will block the underlying kernel thread unless the runtime arranges nonblocking operations (or the syscall is proxied).

Common implementations and APIs:

- C/C++: Boost.Context/Boost.Fiber, libco, custom assembly contexts.
- Languages with built-in support: Go goroutines (M:N scheduler in runtime), Python asyncio (stackless coroutines with async/await), Kotlin coroutines, Rust async/await (futures + executor).
- User-space runtimes often combine coroutines with an event loop or IO scheduler to handle blocking I/O via nonblocking primitives.

Coroutine scheduling models:

- Single-threaded event loop: coroutines run on one thread and use nonblocking I/O (common in Node.js, asyncio).
- Work-stealing or M:N runtimes: schedule many coroutines over a pool of worker threads (Go, some coroutine libraries).

Programming patterns and best practices:

- Keep coroutine entry/exit simple; prefer libraries that integrate with the platform's nonblocking I/O.
- Avoid long-running CPU work in coroutines; offload to worker threads or thread pools.
- Use structured concurrency where available (scopes that ensure coroutines are cancelled/joined cleanly).

Examples (conceptual):

- Async I/O pattern: await read() -> process -> await write(). The runtime drives readiness notifications and resumes coroutines on completion.
- Producer/consumer: coroutines push items to an async queue; consumers await on the queue.

## Choosing a model

- Use processes for isolation, fault containment, and when components are loosely coupled.
- Use threads when you need true parallel CPU work and shared-memory communication.
- Use coroutines for high-concurrency I/O-bound systems where cheap context switches and low memory overhead matter.

Hybrid approaches are common: e.g., a pool of kernel threads each running many coroutines to combine parallelism with massive concurrency.

## References

- Randal E. Bryant and David R. O'Hallaron, Computer Systems: A Programmer's Perspective (CS:APP), 3rd ed.

