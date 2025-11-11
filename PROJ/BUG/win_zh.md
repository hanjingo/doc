# Windows错误

[TOC]



### 崩溃捕获不起作用

**问题**

在Windows下通过函数`SetUnhandledExceptionFilter`或breakpad设置崩溃捕获时，有时候不起作用。

**原因**

参考资料：

- [Windows上发生异常时抓取dump](https://blog.csdn.net/lgyxdn/article/details/109304356)
- [When Even Crashing Doesn’t Work](https://randomascii.wordpress.com/2012/07/05/when-even-crashing-doesnt-work/)
- [windows下捕获dump](https://www.cnblogs.com/cswuyg/p/3207576.html)
- [百度输入法吃了我的异常](https://zhuanlan.zhihu.com/p/440736811?utm_id=0)
- [Qt QML interferes with SetUnhandledExceptionFilter on Windows/64bit](https://bugreports.qt.io/browse/QTBUG-50061)
- [MiniDump不生成或者生成0字节](https://blog.csdn.net/witton/article/details/129715825)
- [SetUnhandledExceptionFilter拦不住的崩溃](https://blog.csdn.net/limiteee/article/details/8472179)

**解决**

1. 卸载其它可能捕获异常的软件比如：百度输入法，讯飞语音，...
2. 使用函数`AddVectoredExceptionHandler`替代`SetUnhandledExceptionFilter`；（可能会带来误捕获的问题）。
3. 阻止操作系统CRT的错误捕获，具体方法参考：[windows下捕获dump](https://www.cnblogs.com/cswuyg/p/3207576.html), [When Even Crashing Doesn’t Work](https://randomascii.wordpress.com/2012/07/05/when-even-crashing-doesnt-work/), 