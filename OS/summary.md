English | [中文版](summary_zh.md)

# OS Summary

[TOC]



The operating system has two primary purposes: (1) to protect the hardware from misuse by runaway applications and (2) to provide applications with simple and uniform mechanisms for manipulating complicated and often wildly different low-level hardware devices.

## Hardware Organization

![hardware_organization](res/hardware_organization.png)



## Control flow

![os_startup](res/os_startup.png)

### System Call

![os_system_call](res/os_system_call.png)



## Types

### Batch Operating System

![os_type_batch](res/os_type_batch.png)

### Multi-Programming Operating System

![os_type_multiprogramming](res/os_type_multiprogramming.png)

### Multi-tasking/Time-sharing Operating System

![os_type_multitasking](res/os_type_multitasking.png)

### Multi-Processing Operating System

![os_type_multiprocessing](res/os_type_multiprocessing.png)

### Distributed Operating System

![os_type_dcs](res/os_type_dcs.png)

### Network Operating System

![os_type_network](res/os_type_network.png)

### Real-Time Operating System

![os_type_realtime](res/os_type_realtime.png)

### Mobile Operating Systems

![os_type_mobile](res/os_type_mobile.png)



## Components

### Shell

Shell is the outermost layer of the Operating System and handles user interaction. It interprets input for the OS and handles the output from the OS.

### Kernel

![os_kernel](res/os_kernel.png)

Kernel is the core component of the operating system. The kernel is the primary interface between the Operating system and Hardware.

### Process Schedulers

Process Schedulers are fundamental components of operating systems responsible for deciding the order in which processes are executed by the CPU. Include:

1. Long-Term Scheduler(Job Scheduler)

2. Short-Term Scheduler(CPU Scheduler)

   ![short_term_scheduler](res/short_term_scheduler.png)

3. Medium-Term Scheduler

   ![medium_term_scheduler](res/medium_term_scheduler.png)

Comparison Among Scheduler:

| Long-Term Scheduler                                          | Short-Term Scheduler                                      | Medium-Term Scheduler                                        |
| ------------------------------------------------------------ | --------------------------------------------------------- | ------------------------------------------------------------ |
| It is a job scheduler                                        | It is a CPU scheduler                                     | It is a process-swapping scheduler                           |
| It is the slowest scheduler                                  | It is the fastest scheduler                               | It's speed lies between long-term and short-term schedulers  |
| It controls the degree of multiprogramming                   | It gives less control over the degree of multiprogramming | It reduces the degree of multiprogramming                    |
| It is barely present or nonexistent in time-sharing systems  | It is essential for time-sharing systems                  | It is a component of time-sharing systems                    |
| It selects processes from the job poll and loads them into memory | It selects ready processes for execution by the CPU       | It can re-introduce processes into memory and resume execution |



## Process

### States Transaction

![process_seven_state_model](res/process_seven_state_model.png)



## Summary

### Process vs Thread vs Coroutine

|             | Process                                                     | Thread                                                       | Coroutine                                                 |
| ----------- | ----------------------------------------------------------- | ------------------------------------------------------------ | --------------------------------------------------------- |
| Scheduling  | Runs independently.                                         | Basic unit of scheduling and dispatch; actually runs on CPU. | Fully controlled by user.                                 |
| Resources   | Has independent resources.                                  | All threads in a process share resources; more efficient.    | Has its own register context and stack.                   |
| Overhead    | Large overhead for creation/destruction and context switch. | Small overhead.                                              | Can save/restore state; switching has almost no overhead. |
| Concurrency | Processes run independently.                                | Preemptive multitasking; threads need locks; less robust.    | Cooperative multitasking; no locks needed; more robust.   |

### Dispatcher vs Scheduler

![os_dispatcher](res/os_dispatcher.png)

*OS Dispather*

![os_scheduler](res/os_scheduler.png)

*OS Scheduler*

| Scheduler                                            | Dispatcher                                                   |
| ---------------------------------------------------- | ------------------------------------------------------------ |
| Decides which process should be executed next.       | Transfers control of CPU to the process selected by the scheduler. |
| To select the process and determine execution order. | To start the execution of the selected process.              |
| Long-term, Medium-term and Short-term.               | No types; it's a single module.                              |
| Works independently.                                 | Dependent on the scheduler's decision.                       |
| Uses algorithms like FCFS, SJF, RR, Priority, etc.   | No specific algorithm used.                                  |
| Negligible and occurs less frequently.               | Time taken is known as Dispatch Latency.                     |
| Process selection and queue management.              | Context switching, mode change and process start.            |
| Works with the ready queue and dispatcher.           | Works with CPU and the selected process.                     |
| Takes longer than the dispatcher.                    | Executes in a very short time.                               |



## Reference

[1] Randal E. Bryant, David R. O'Hallaron . COMPUTER SYSTEMS: A PROGRAMMER'S PERSPECTIVE . 3ED

[2] [Operating System Tutorial](https://www.geeksforgeeks.org/blogs/operating-systems/)

[3] [Introduction to Operating System](https://www.geeksforgeeks.org/operating-systems/introduction-of-operating-system-set-1/)

[4] [Types of Operating Systems](https://www.geeksforgeeks.org/operating-systems/types-of-operating-systems/)

[5] [Kernel in Operating System](https://www.geeksforgeeks.org/operating-systems/kernel-in-operating-system/)

[6] [System Call](https://www.geeksforgeeks.org/operating-systems/introduction-of-system-call/)

[7] [Process Schedulers in Operating System](https://www.geeksforgeeks.org/operating-systems/process-schedulers-in-operating-system/)

[8] [Dispatcher vs Scheduler in OS](https://www.geeksforgeeks.org/operating-systems/difference-between-dispatcher-and-scheduler/)