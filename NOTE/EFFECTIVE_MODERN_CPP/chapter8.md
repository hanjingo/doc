[TOC]

# 第八章 微调

## 条款41:针对可复制的形参，在移动成本低并且一定会被复制的前提下，考虑将其按值传递
- 对于可复制的，在移动成本低廉的并且一定会被复制的形参而言，按值传递可能会和按引用传递的具备相近的效率，并可能生成更少量的目标代码。
- 经由构造复制形参的成本可能比经由赋值复制形参高出很多。
- 按值传递肯定会导致切片问题，所以基类型别特别不适用于按值传递。



## 条款42:考虑置入而非插入
- 从原理上说，置入函数应该有时比对应的插入函数高效，而且不应该有更低效的可能。
- 从实践上说，置入函数在以下几个前提成立时，极有可能会运行的更快：1.待添加的值是以构造h而非赋值方式加入容器；2.传递的实参型别与容器持有之物的型别不同；3.容器不会由于存在重复值而拒绝待添加的值。
- 置入函数可能会执行在插入函数中会被拒绝的型别转换。

