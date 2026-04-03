English | [中文版](kernel_zh.md)

# OS Kernel

[TOC]



A kernel is the core part of an operating system. It acts as a bridge between software applications and the hardware of a computer.

![os_kernel](res/os_kernel.png)

## Types

- Monolithic
- Microkernel
- Hybrid kernel
- Nanokernel
- Exokernel



## Functions

![os_kernel_function](res/os_kernel_function.png)

The kernel is responsible for various critical functions that ensure the smooth operation of the computer system. These functions include:

- Process Management
- Memory Management
- Device Management
- File System Management
- Resource Management
- Security And Access Control
- Inter-Process Communication



## UNIX Kernel Structure

![unix_core_struct](/usr/local/src/github.com/hanjingo/doc/OS/res/unix_core_struct.png)

### Process State Transitions

![unix_core_progress_stat_transform](/usr/local/src/github.com/hanjingo/doc/OS/res/unix_core_progress_stat_transform.png)

### Process Priority

#### Calculation Formula

$Priority = (recent CPU time \div 2) + base user priority$

### Device Switch Table and Interface Between System Calls and Drivers

![unix_core_interrupt](/usr/local/src/github.com/hanjingo/doc/OS/res/unix_core_interrupt.png)



## Reference

[1] [Kernel in Operating System](https://www.geeksforgeeks.org/operating-systems/kernel-in-operating-system/)