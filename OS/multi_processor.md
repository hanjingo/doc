# Multi Processor

[TOC]



## Amdahl's Law

In computer architecture, Amdahl's law is a formula that shows how much faster a task can be completed when more resources are added to the system.

Amdahl's law can be formulated in the following way:

$Speedup_{overall}=\frac{1}{1 - time_{optimized} + \frac{time_{optimized}}{speedup_{optimized}}}$

- $Speedup_{overall}$ represents the total speedup of a program.
- $time_{optimized}$ represents the proportion of time spent on the portion of the code where improvements are made.
- $speedup_{optimized}$ represents the extent of the improvement.



## Reference

[1] Randal E. Bryant, David R. O'Hallaron . COMPUTER SYSTEMS: A PROGRAMMER'S PERSPECTIVE . 3ED

[2] [WIKIPEDIA/Amdahl's law](https://en.wikipedia.org/wiki/Amdahl%27s_law)
