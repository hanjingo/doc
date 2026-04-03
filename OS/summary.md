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



## Process vs Thread vs Coroutine

|             | Process                                                     | Thread                                                       | Coroutine                                                 |
| ----------- | ----------------------------------------------------------- | ------------------------------------------------------------ | --------------------------------------------------------- |
| Scheduling  | Runs independently.                                         | Basic unit of scheduling and dispatch; actually runs on CPU. | Fully controlled by user.                                 |
| Resources   | Has independent resources.                                  | All threads in a process share resources; more efficient.    | Has its own register context and stack.                   |
| Overhead    | Large overhead for creation/destruction and context switch. | Small overhead.                                              | Can save/restore state; switching has almost no overhead. |
| Concurrency | Processes run independently.                                | Preemptive multitasking; threads need locks; less robust.    | Cooperative multitasking; no locks needed; more robust.   |



## Reference

[1] Randal E. Bryant, David R. O'Hallaron . COMPUTER SYSTEMS: A PROGRAMMER'S PERSPECTIVE . 3ED

[2] [Operating System Tutorial](https://www.geeksforgeeks.org/blogs/operating-systems/)

[3] [Introduction to Operating System](https://www.geeksforgeeks.org/operating-systems/introduction-of-operating-system-set-1/)

[4] [Types of Operating Systems](https://www.geeksforgeeks.org/operating-systems/types-of-operating-systems/)

[5] [Kernel in Operating System](https://www.geeksforgeeks.org/operating-systems/kernel-in-operating-system/)

[6] [System Call](https://www.geeksforgeeks.org/operating-systems/introduction-of-system-call/)