# Redis实现异步队列


<!-- vim-markdown-toc GFM -->

* [摘要](#摘要)

<!-- vim-markdown-toc -->



## 摘要

通过使用redis的`zset`,`list`，发布订阅等数据结构和功能，可以实现一个异步队列。

用`zset`实现延迟队列，`list`实现队列内容存储，发布订阅机制实现消息推送

