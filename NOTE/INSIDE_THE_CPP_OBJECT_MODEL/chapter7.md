# 第七章 站在对象模型的尖端（On the Cusp of the ObjectModel）

[TOC]

## 7.1 Template

### Template的“实例化”行为(Template Instantiation)

编译器在看到一个模版的声明时没有任何反应，即使模版内部有明显的语法错误，编译器也不会报错，编译器对模版的所有操作都会延迟到Template实例化时进行；

### Template的错误报告(Error Reporting within a Template)

声明一个模版类型的指针是不会引起模版的具现化操作，因为仅仅声明指针不需要知道class的时机内存布局；只有在某个`member function`真正被使用时，它才会被真正的具现化出来，这样的延迟具现化有2个好处：

1. 空间和时间上的效率；
2. 如果使用的类型并不完全支持所有的函数，但是只需要不去用那些不支持函数，这样的部分具现化就能得以通过编译；

### Template中的名称决议法(Name Resolution within a Template)

Template中的名称决议方式有2种：

- 定义模版的地方(scope of the template definition)

  ```c++
  extern double foo( double );
  template <class type>
  class ScopeRules
  {
  public:
    void invariant() { _member = foo(_val); }
    type type_dependent() { return foo(_member); }
    ...
  private:
    int _val;
    type _member;
  };
  ```

- 具现出模版实体的地方(scope of the template instantiation)

  ```c++
  extern int foo(int);
  ...
  ScopeRules< int > sr0;
  ```

### Member Function的实例化行为(Member Function Instantiation)

template function的实例化(instantiation)提供了以下策略：

- 编译时期策略，程序代码必须在program text file中备妥可用；
- 链接时期策略，有些meta-compilation工具可以导引编译器的实例化行为(instantiation)；

编译器维持了2个scope contexts：

- scope of template declaration：用以专注一般的template class;
- scope of template instantiation：用以专注于特定的实体；

如果vtable被具现出来，那么每一个virtual function也都必须被具现；



## 7.2 异常处理(Exception Handling)

### Exception Handling快速检阅

以值类型抛出异常，以引用类型进行捕获；被抛出的一场类型，一定会被先复制一份，真正被抛出的实际上是这份复制数据；

对于每一个被丢出的exception，编译器必须产生一个类型描述器，对exception类型进行编码；如果那是一个derived type，则编码内容还必须包括其所有base class的类型信息；

### 对Exception Handling的支持

当一个exception被丢出时，exception object会被产生出来并通常放置在相同形式的exception数据堆栈种。从throw端传染给catch子句的是exception object的地址，类型描述器（或是一个函数指针，该函数会返回给exception type有关的类型描述器对象）以及可能会有的exception object的溪谷函数的地址（如果有人定义它的话）。

**与其它语言特征相比较，C++编译器支持EH机制所付出的代价最大（代价：空间10%, 时间5%）。**



## 7.3 执行期类型识别(Runtime Type Identification, RTTI)

### Type-Safe Downcast(保证安全的向下转换操作)

在C++种，一个具备多态性质的class，就是指内含virtual functions的类（直接声明或着继承而来的）。

### Type-Safe Dynamic Cast(保证安全的动态转换)

### References并不是Pointers

### Typeid运算符



## 7.4 效率有了，弹性呢

### 动态共享函数库(Dynamic Shared Libraries)

### 共享内存(Shared Memory)

