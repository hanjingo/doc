# Accustoming Yourself to C++

[TOC]

## 条款01 视C++为一个语言联邦

C++是个多重范型编程语言（multiparadigm programming language），同时支持以下形式：

- procedural 过程形式
- object-oriented 面向对象形式
- functional 函数形式
- generic 泛型形式
- metaprogramming 元编程形式

C++包含以下几种次语言：

- C
- Object-Oriented C++
- Template C++
- STL



## 条款02 尽量以const, enum, inline替换#define

宁可以编译器替换预处理器，因为预处理的名称可能并为进入记号表(symbol table)；例：

```c++
#define ASPECT_RATIO 1.653 // 大写名称通常用于宏
```

会给调试带来困难，可以修改成：

```c++
const double AspectRatio = 1.653;
```

旧式编译器(取决于版本，我在gcc 8.4.0没遇到)不允许在class声明中初始化static类型变量；例：

```c++
// t.h
class C1 {
private:
    static const int n = 5; // 不建议这样写
};
```

可以修改为以下形式：

```c++
// t.h
class C1 {
private:
    static const int n;
};
```

```c++
// t.cpp
const int C1::n = 5;
```

总结：

- 对于单纯常量，最好以const对象或enums替换`#define`；
- 对于形似函数的宏（macros），最好改用inline函数替换`#defines`；



## 条款03 尽可能使用const

`void f1(const Widget* pw)`与`void f2(Widget cont* pw)`等效；

两个成员函数如果只是常量性(constness)不同，也可以被重载；例：

```c++
class TextBlock {
public:
    const char& operator[](std::size_t position) const // const
    { return text[position]; }
    char& operator[](std::size_t postion) // 非const
    { return text[position]; }
private:
    std::string text;
}

TextBlock tb("Hello");
std::cout << tb[0]; // 调用 非const[]
const TextBlock ctb("World");
std::cout << ctb[0]; // 调用 const[]
```

const函数的约束：

- `bitwise constness(physical constness)`

  (由编译器强制实施)，成员函数只有在不更改对象的任何成员变量(static除外)时，才可以说是const;

- `logical constness`

  在客户端侦测不出的情况下，一个const成员函数可以修改它所处理的对象内的某些bits；

常量性转除(casting away constness)：

1. 使用`mutable`释放掉non-static成员变量的`bitwise constness`约束；

   ```c++
   class CTextBlock {
   public:
       std::size_t length() const;
   private:
       char* pText;
       mutable std::size_t textLength; // 即使在const成员函数内，此变量也可被更改
       mutable bool lengthIsValid;
   };
   std::size_t CTextBlock::length() const
   {
       if (!lengthIsValid) {
           textLength = std::strlen(pText); // 被更改了
           lengthIsValid = true;
       }
       return textLength;
   };
   ```
   
2. 使用`const_cast`去掉const性质；

   ```c++
   class TextBlock {
   public:
       const char& operator[](std::size_t position) const {};
       char& operator[](std::size_t position)
       {
           return const_cast<char&>(static_cast<const TextBlock&>(*this)[position]);
       };
   }
   ```

总结：

- 将某些东西声明为const可帮助编译器侦测出错误用法；const可被施加于任何作用域内的对象，函数参数，函数返回类型，成员函数本体；
- 编译器强制实施bitwise constness，但编写程序时应该使用“概念上的常量性”(conceptual constness)；
- 当const和non-const成员函数有着实质等价的实现时，令non-const版本调用const版本可避免代码重复；




## 条款04 确定对象被使用前已先被初始化

读取未初始化的值会导致不明确的行为，**永远在使用对象之前先将它初始化**；

C++规定：对象的成员变量的初始化动作发生在进入构造函数本体之前；

由于C++赋值前，会先进行一次默认构造操作；所以推荐使用成员初始化列表(member initialization list)的方式来构造，可以避免一次多余的默认构造操作；

成员初始化顺序为：基类早于派生类被初始化，同一class内的成员变量总是以其声明次序被初始化；

C++对定义于不同编译单元内的`non-local static`对象的初始化次序并无明确定义，多个编译单元内的`non-local static`对象经由“模版隐式具现化(implicit template instantiations)”形成；例：

```c++
class FileSystem {
public:
  std::size_t numDisks() const;
};
extern FileSystem tfs;
```

```c++
class Directory {
public:
  Directory(params);
};
Directory::Directory( params )
{
	std::size_t disks = tfs.numDisks(); // 使用tfs对象
};
Directory tempDir( params );
```

优化为：

```c++
class FileSystem { ... };
FileSystem& tfs()
{
  static FileSystem fs;
  return fs;
}
```

```c++
class Directory { ... };
Directory::Directory( params )
{
	std::size_t disks = tfs().numDisks();
}
Directory& tempDir()
{
	static Directory td;
  return td;
}
```

在程序的单线程启动阶段（single-threaded startup portion）手工调用所有`reference-returning`函数，这可消除与初始化有关的“竞速形势(race conditions)”。

总结：

- 为内置型别对象进行手工初始化，因为C++不保证初始化它们；
- 构造函数最好使用成员初值列（member initialization list），而不要在构造函数本体内使用赋值操作（assignment）；初值列列出的成员变量，其排列次序应该和它们在class中的声明次序相同；
- 为免除“跨编译单元之初始化次序”问题，请以`local static`对象替换`non-local static`对象。
