English | [中文版](coroutine_zh.md)

# Coroutine

[TOC]



**A coroutine is a lightweight user-space thread.** Coroutines are at the language level, while threads are at the system level. Coroutine scheduling is fully controlled by the user. Coroutines have their own register context and stack. When switching, the register context and stack are saved elsewhere and restored when switching back. Context switching has almost no overhead.



## References

[1] Tang Xiaodan, Liang Hongbing, Zhe Fengping, Tang Ziying. Computer Operating System. 3rd Edition. P32 - P115

[2] [Wikipedia - Coroutine](https://en.wikipedia.org/wiki/Coroutine)