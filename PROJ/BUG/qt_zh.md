# Qt错误

[TOC]



### Qt的信号槽被卡住

**问题**

使用Qt信号槽时，如果在槽函数中执行非常耗时的操作，有可能会卡住整个信号槽机制，导致其它信号无响应。

**原因**

槽函数中执行非常耗时的操作，有可能会卡住整个信号槽机制，导致其它信号无响应。

**解决**

1. 在耗时的槽函数中执行QCoreApplication的processEvents以防止信号槽被卡住。



### Qt的readyRead信号粘包问题

**问题**

使用Qt Tcp套接字进行通信时，根据readyRead信号来读数据，可能会出现多个数据包只触发一次readyRead信号，会导致粘包问题。

**原因**

根据readyRead信号来读数据，可能会出现多个数据包只触发一次readyRead信号；具体见：https://blog.csdn.net/whiskey_wei/article/details/80790428。

**解决**

收到readyRead信号后，手动拆包。

