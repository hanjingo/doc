# UNIX内核

[TOC]



## UNIX系统的内核结构

![unix_core_struct](res/unix_core_struct.png)



## 进程状态转换

![unix_core_progress_stat_transform](res/unix_core_progress_stat_transform.png)



## 进程优先数

### 计算公式

$优先数=(最近使用cpu的时间\div2) + 基本用户优先数$



## 设备开关表以及系统调用和驱动程序间的接口

![unix_core_interrupt](res/unix_core_interrupt.png)

