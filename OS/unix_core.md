English | [中文版](unix_core_zh.md)

# UNIX Kernel

[TOC]

## UNIX Kernel Structure

![unix_core_struct](res/unix_core_struct.png)


## Process State Transitions

![unix_core_progress_stat_transform](res/unix_core_progress_stat_transform.png)


## Process Priority

### Calculation Formula

$Priority = (recent CPU time \div 2) + base user priority$


## Device Switch Table and Interface Between System Calls and Drivers

![unix_core_interrupt](res/unix_core_interrupt.png)

