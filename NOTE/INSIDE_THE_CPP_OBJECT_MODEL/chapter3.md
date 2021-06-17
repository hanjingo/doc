# 第三章 Data语意学

一个空的`class object`其实并不是空的，它隐藏了一个1byte大小的char，用来唯一标识object在内存中的地址；

`class object`的大小受3个因素的影响：

1. 语言本身所造成的额外负担(overhead)当语言支持`virtual base classes`时，就会导致一些额外负担。

2. 
