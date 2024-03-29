# 第17章 TCP保活机制

[TOC]



## 引言

保活机制是一种在不影响数据流内容的情况下探测对方的方式。它是由一个`保活计时器`实现的。当计时器被激发，连接一段将发送一个`保活探测`（简称保活）报文，另一端接收报文的同时会发送一个ACK作为响应。



## 描述

保活功能在默认情况下是关闭的，TCP连接的任何一端都可以请求打开这一功能；开启该功能的一端会发现对方处于**以下状态之一**：

1. 对方主机仍在工作，并且可以到达。
2. 对方主机已经崩溃，包括已经关闭或者正在重新启动。
3. 客户主机崩溃并且已重启。
4. 对方主机仍在工作，但是由于某些原因不能到达请求端。



## 与TCP保活机制相关的攻击

ssh中含有一种应用层的保活机制，称为`服务器保活报文和客户端保活报文`。与TCP保活报文的区别在于，它们是在应用层通过一条加密的链路传输的，而且这些报文中包含数据。TCP保活报文中不包含任何用户数据，所以它最多只进行有限的加密。