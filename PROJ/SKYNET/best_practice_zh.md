# skynet最佳实践


<!-- vim-markdown-toc GFM -->

+ [1 节点间通信代价](#1-节点间通信代价)
+ [2 优先选用多核机器](#2-优先选用多核机器)
+ [3 保证消息顺序](#3-保证消息顺序)
+ [4 避免调度器失效](#4-避免调度器失效)
+ [5 排除内存隐患](#5-排除内存隐患)
+ [6 尽量避免单点服务](#6-尽量避免单点服务)

<!-- vim-markdown-toc -->


#### 1 节点间通信代价

节点间通信有较大的代价，具体如下：

- 节点间消息传递速度慢
- 安全性得不到保障

#### 2 优先选用多核机器

根据skynet的特性，如果CPU运算能力不足，选用多核机器比增加物理机性价比高（多节点通信性能损耗大）。

#### 3 保证消息顺序

Skynet服务重入问题：Skynet服务在收到消息时，会创建一个协程，在协程中会运行消息处理方法（即用``skynet.dispatch`设置的回调方法）。这意味着，如果在消息处理方法中调用阻塞API，服务不会被卡住（仅仅是处理消息的协程被卡住），执行效率得以提高，但程序的执行时序将得不到保证。

如何解决Skynet服务重入问题？

使用skynet提供的工具`skynet.queue`来将API重入调用转为顺序调用；

#### 4 避免调度器失效

Skynet使用全局队列保存了要调度的服务，调度算法是先来先服务。如果某个服务有新消息，就把这个服务驾到调度队列中，然后等待调度线程调度。而skynet服务的调度切换依赖于协程的挂起，如果当前调度的服务没有主动挂起或退出，就会一直执行，不调度其他服务，从而**导致其他服务饿死**。

如何解决其它服务饿死问题？

不推荐在skynet服务中使用使用死循环，如果一定要使用，要给循环加退出条件；最好给每个循环加一个`skynet.sleep`，让循环稍等片刻；

#### 5 排除内存隐患

skynet服务创建协程来处理请求，当请求数量过大时，创建过多的协程会耗费非常大的内存；

如何解决这个问题？

手动调用skynet的GC函数

#### 6 尽量避免单点服务

对于一些频繁调用的功能服务，尽量避免做成单点服务；如果有这项需求，可以前置一个代理服务，通过代理服务将消息转发到功能服务集群；
