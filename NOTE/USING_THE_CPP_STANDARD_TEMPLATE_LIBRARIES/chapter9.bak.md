# 第九章 流操作
# 摘要
* 流迭代器提供了哪些成员函数
* 如何用流迭代器读写单独的数据项
* 什么是刘缓冲区迭代器流及其与迭代器的差别
* 如何使用流缓冲区迭代器读写文件
* 如何用流迭代器读写文件
* 什么是字符串流以及STL定义的不同类型的字符串流
* 如何对字符串流使用流迭代器和流缓冲区迭代器
# 详情
## 流迭代器
#### 输入流迭代器
* 
```c++
#include <iostream>
#include <iterator>
int main()
{

}
```
#### 输出流迭代器
* 
```c++
#include <iostream>
#include <iterator>
```
## 对文件使用流迭代器
* 
```c++
todo
```
**用流迭代器来反复读文件:**
```c++
todo
```
**用流迭代器输出文件:**
```c++
todo
```
## string流，流，以及流缓冲区迭代器
string流是表示内存中字符缓冲区中的I/O对象，是定义在sstream头文件中的3个模板中的一个模板实例：
* basic_istringstream：支持从内存中的字符缓冲区去读数据
* basic_ostringstream：支持写数据到内存中的字符缓冲区
* basic_stringstream：支持字符缓冲区上的输入和输出操作