
# Multi-Processor Systems

[TOC]

This note summarizes fundamental ideas about parallelism and multiprocessing from a programmer's perspective, inspired by CS:APP and common systems literature. It explains how to reason about speedup and scalability (Amdahl's and Gustafson's laws), sources of overhead in parallel programs, synchronization and memory-coherence issues, and practical techniques for achieving scalable performance.

## Key concepts: speedup, efficiency, and scalability

- Speedup S(p): how much faster a program runs on p processors compared to 1 processor.
	S(p) = T(1) / T(p)
- Efficiency E(p): the speedup per processor, E(p) = S(p) / p. Efficiency measures how well parallel resources are utilized.
- Strong scaling: keep total problem size fixed and increase p. Measures how well a fixed-size problem accelerates with more processors.
- Weak scaling: increase problem size proportionally to p. Measures whether per-processor workload stays constant as the system grows.

## Amdahl's Law (limits to parallel speedup)

Amdahl's law formalizes the limit of speedup when only a fraction f of the work is parallelizable:

S(p) = \\frac{1}{(1 - f) + \\frac{f}{p}}

As p → ∞, the maximum speedup approaches 1/(1 - f). This shows that even a small serial fraction can cap overall speedup.

Notes:

- Amdahl's law assumes a fixed total workload (strong scaling).
- It highlights diminishing returns: beyond some p, adding processors yields little benefit if the serial fraction remains.

## Gustafson's Law (scalable workloads)

Gustafson observed that for many practical problems the total work scales with p. If the parallel portion grows with problem size, the effective speedup can be much higher. Gustafson's law uses scaled speedup:

S_{G}(p) = p - (p - 1) * (1 - f)

Gustafson emphasizes weak scaling and shows that large problems can better exploit many processors.

## Sources of overhead in parallel programs

- Parallelization overhead: spawning threads/processes, task dispatch, and joining/synchronization.
- Communication and synchronization: message passing or shared-memory synchronization cost (locks, barriers, atomic ops).
- Load imbalance: uneven work distribution leaves some processors idle.
- Memory contention: shared data structures, cache-line contention, and access to the same memory locations.
- False sharing: independent data on the same cache line cause unnecessary coherence traffic.
- I/O and OS-related overheads: page faults, context switches, and system calls can serialize parts of the program.

## Synchronization and correctness

Common synchronization primitives:

- Mutexes/locks: protect critical sections; easy to reason about but can block and cause contention.
- Condition variables: coordinate threads for producer/consumer patterns.
- Barriers: ensure all threads reach a synchronization point before any proceed.
- Atomic operations and lock-free algorithms: offer finer-grained concurrency and lower overhead in some scenarios (compare-and-swap, fetch-and-add).

Design tips:

- Minimize the size of critical sections and the frequency of lock acquisitions.
- Prefer per-thread or sharded data structures to reduce contention.
- Use read-mostly synchronization (read-copy-update, versioning) where possible.

## Memory consistency and cache coherence

In shared-memory systems, CPUs maintain caches that must stay coherent. Hardware coherence protocols (MESI and variants) ensure that caches agree, but they incur traffic:

- True sharing: threads communicate through the same memory locations intentionally.
- False sharing: independent variables placed in the same cache line cause extra coherence messages when different threads write nearby data.

Reduce coherence overhead by aligning frequently written variables to separate cache lines or padding structures.

Memory consistency models determine when stores from one processor become visible to others (sequential consistency, relaxed models). Many architectures provide weaker consistency for performance; use memory fences or atomic operations with appropriate ordering when needed.

## Granularity and task decomposition

- Fine-grained parallelism: many small tasks — reduces per-task work and increases scheduling/communication overhead.
- Coarse-grained parallelism: fewer larger tasks — lower overhead but may hurt load balance.

Choose granularity to balance scheduling cost and parallel work. Work-stealing schedulers (e.g., Cilk, Intel TBB) help by dynamically balancing tasks between workers.

## Load balancing strategies

- Static partitioning: simple and low-overhead, but vulnerable to imbalance.
- Dynamic scheduling: task queues, work-stealing — adapt to runtime variability.
- Data partitioning: block, cyclic, or blocked-cyclic distributions for arrays and loops.

## NUMA and memory placement

On NUMA (non-uniform memory access) machines, memory access latency depends on which NUMA node owns the memory relative to the CPU core. Practical guidance:

- Prefer first-touch allocation: allocate and initialize memory on the thread that will use it.
- Use NUMA-aware allocators or explicit mbind/mempolicy calls when necessary.
- Place threads and data together (affinity) to reduce remote memory access.

## Performance measurement and benchmarking

- Use both microbenchmarks (to isolate primitives like atomics, memory bandwidth, latency) and application benchmarks.
- Distinguish strong vs weak scaling when reporting results.
- Measure wall-clock time, throughput, and per-processor utilization; report median/percentiles for latency-sensitive workloads.

Useful tools: perf, top/htop, vmstat, numactl, Intel VTune, and architecture-specific counters.

## Practical tips and common pitfalls

- Profile first: optimize the real bottleneck, not an assumed hotspot.
- Reduce synchronization frequency and scope.
- Avoid false sharing by aligning or padding hot per-thread data.
- Batch small tasks where syscall or scheduling cost dominates.
- Use efficient concurrent data structures (lock-free queues or sharded maps) when contention is high.
- Prefer algorithms with locality-friendly access patterns to reduce cache misses.

## Summary

Parallel performance depends on algorithmic parallelism (f), overheads, workload scaling, and architecture (NUMA, cache-coherence). Amdahl's law provides an upper bound under fixed-work assumptions; Gustafson's law shows why larger problems can scale better. Combine careful decomposition, low-overhead synchronization, and NUMA-aware placement to build scalable systems.

## References

- Randal E. Bryant and David R. O'Hallaron, Computer Systems: A Programmer's Perspective (CS:APP), 3rd ed.
- Amdahl's law — https://en.wikipedia.org/wiki/Amdahl%27s_law

