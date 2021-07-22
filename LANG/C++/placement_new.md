# placement new 关键字



## new

new operator就是new操作符，不能被重载，假如A是一个类，那么A * a=new A;实际上执行如下3个过程。 
（1）调用operator new分配内存，operator new (sizeof(A)) 
（2）调用构造函数生成类对象，A::A() 
（3）返回相应指针 
事实上，分配内存这一操作就是由operator new(size_t)来完成的，如果类A重载了operator new，那么将调用A::operator new(size_t )，否则调用全局::operator new(size_t )，后者由C++默认提供。 



## operator new

operator new是函数，分为三种形式（前2种不调用构造函数，这点区别于new operator）： 
void* operator new (std::size_t size) throw (std::bad_alloc); 
void* operator new (std::size_t size, const std::nothrow_t& nothrow_constant) throw(); 
void* operator new (std::size_t size, void* ptr) throw(); 
第一种分配size个字节的存储空间，并将对象类型进行内存对齐。如果成功，返回一个非空的指针指向首地址。失败抛出bad_alloc异常。 
第二种在分配失败时不抛出异常，它返回一个NULL指针。 
第三种是placement new版本，它本质上是对operator new的重载，定义于#include <new>中。它不分配内存，调用合适的构造函数在ptr所指的地方构造一个对象，之后返回实参指针ptr。 
第一、第二个版本可以被用户重载，定义自己的版本，第三种placement new不可重载。 

```c++
A* a = new A; 							//调用第一种 
A* a = new(std::nothrow) A; //调用第二种 
new (p)A(); 								//调用第三种 

// new (p)A()调用placement new之后，还会在p上调用A::A()，这里的p可以是堆中动态分配的内存，也可以是栈中缓冲。 
```



## placement new

new和delete操作符我们应该都用过，它们是对堆中的内存进行申请和释放，而这两个都是不能被重载的。要实现不同的内存分配行为，需要重载operator new，而不是new和delete。

operator new就像operator+一样，是可以重载的，但是不能在全局对原型为void operator new(size_t size)这个原型进行重载，一般只能在类中进行重载。如果类中没有重载operator new，那么调用的就是全局的::operator new来完成堆的分配。同理，operator new[]、operator delete、operator delete[]也是可以重载的，一般你重载了其中一个，那么最好把其余三个都重载一遍。

placement new是operator new的一个重载版本，只是我们很少用到它。如果你想在已经分配的内存中创建一个对象，使用new是不行的。也就是说placement new允许你在一个已经分配好的内存中（栈或堆中）构造一个新的对象。原型中void*p实际上就是指向一个已经分配好的内存缓冲区的的首地址。

我们知道使用new操作符分配内存需要在堆中查找足够大的剩余空间，这个操作速度是很慢的，而且有可能出现无法分配内存的异常（空间不够）。placement new就可以解决这个问题。我们构造对象都是在一个预先准备好了的内存缓冲区中进行，不需要查找内存，内存分配的时间是常数；而且不会出现在程序运行中途出现内存不足的异常。所以，placement new非常适合那些对时间要求比较高，长时间运行不希望被打断的应用程序。

使用方法如下：

1. 缓冲区提前分配
	```c++
	// 可以使用堆的空间，也可以使用栈的空间，所以分配方式有如下两种：

 	class MyClass {…};
 	char *buf=new char[N*sizeof(MyClass)+ sizeof(int) ] ; 或者char buf[N*sizeof(MyClass)+ sizeof(int) ];
 	```
2. 对象的构造
   ```c++
   MyClass * pClass=new(buf) MyClass;
   ```

3. 对象的销毁
   一旦这个对象使用完毕，你必须显式的调用类的析构函数进行销毁对象。但此时内存空间不会被释放，以便其他的对象的构造。
   ```c++
   pClass->~MyClass();
   ```

4. 内存的释放
   如果缓冲区在堆中，那么调用delete[] buf;进行内存的释放；如果在栈中，那么在其作用域内有效，跳出作用域，内存自动释放。

**注意：**

- 在C++标准中，对于`placement operator new []`有如下的说明：` placement operator new[] needs implementation-defined amount of additional storage to save a size of array.` 所以我们必须申请比原始对象大小多出`sizeof(int)`个字节来存放对象的个数，或者说数组的大小。
- 使用方法第二步中的new才是placement new，其实是没有申请内存的，只是调用了构造函数，返回一个指向已经分配好的内存的一个指针，所以对象销毁的时候不需要调用delete释放空间，但必须调用析构函数销毁对象。
- 使用placement new之前需要包含文件` new.h`

