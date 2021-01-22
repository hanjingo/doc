# c++ final关键字
final的用途如下:
1. 禁用继承
> 在父类中使用final修饰，意味着子类无法继承它
```c++
class Base final
{
};
 
// 错误，Derive不能从Base派生。
class Derive
        : public Base
{
};
```

2. 禁用重写
> 将父类的成员函数标记为final，意味着子类无法重写该函数
```c++
class Super
{
  public:
    Supe();
    virtual void SomeMethod() final;
};
```
