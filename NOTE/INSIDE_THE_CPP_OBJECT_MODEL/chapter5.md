# 构造析构拷贝语意学

对于`abstract base class(抽象基类)`,class中的data member应该被初始化，并且**只在constructor中或者在其它member functions中指定初值。**

## 纯虚函数的存在

纯虚函数，虚函数在声明后加上`=0`，纯虚函数的意义在于只定义一个可继承的接口，并没有**实现**（虚函数意义在于定义一个可继承的接口并且有一份缺省实现，普通的成员函数意义在于定义一个可继承的接口并且有一份强制实现）。

纯虚函数不能经由虚拟机制调用，但是可以被静态调用`(invoked statically, AbsractClassName::pureFunction())`。

唯一的例外在于：对于`pure vitual destructor`，一定要定义它，因为每一个`derived class destructor`会被编译器加以扩张，**以静态调用的方式调用其“每一个virtual base class”以及"上一层base class"的destructor**，因此只要缺乏任何一个`base class destrctor`以及"上一层base class"的destructor**，因此只要缺乏任何一个base class destructor的定义，就会导致链接失败。一个较好的替代方案就是：**不要把virtual destructor声明成pure。**

## 纯虚函数的规格

一个函数几乎不会被后继的`derived class`改写，而且是inline函数，将其改写成`virtual function`是一个糟糕的选择。
