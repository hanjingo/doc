# 4 Designs and Declarations

[toc]

## 条款18 让接口容易被正确使用，不易被误用

`std::shred_ptr`会自动使用自定义删除器，从而消除“cross-DLL problem”的问题；例：

```c++
std::shared_ptr<Investment> createInvestment()
{
    return std::shared_ptr<Investment>(new Stock);
}
```

总结：

- 好的接口很容易被正确使用，不容易被误用，你应该在你的所有接口中努力达成这些性质；
- “促进正确使用"的办法包括接口的一致性，以及与内置类型的行为兼容；
- “阻止误用"的办法包括建立新类型，限制类型上的操作，束缚对象值，以及消除客户的资源管理责任；
- `shared_ptr`支持定制删除器（custom deleter），这可防范DLL问题，可被用来自动解除互斥锁（mutex）；


## 条款19 设计class犹如设计type

设计高效的class需要考虑以下问题：

1. 新type的对象应该如何被创建和销毁？

2. 对象的初始化和对象的赋值该有什么样的差别？

3. 新type的对象如果被passed by value（以值传递），意味着什么？

4. 什么是新type的“合法值”？

5. 你的新type需要配合某个继承图系（inheritance graph）吗？

6. 你的新type需要什么样的转换？

7. 什么样的操作符和函数对此新type而言是否合理的？

8. 什么样的标准函数应该驳回？

9. 谁该取用新type的成员？

10. 什么是新type的“未声明接口”（undeclared interface）?

11. 你的新type有多么一般化？

12. 你真的需要一个新type吗？

总结：

- Class的设计就是type的设计，在定义一个新type之前，请确定你已经考虑过本条款覆盖的所有讨论主题；


## 条款20 宁以pass-by-reference-to-const替换pass-by-value

`pass by reference`的方式比`pass by value`的方式效率高得多，因为没有任何构造函数或析构函数被调用；同时`by reference`方式也可以避免`slicing（对象切割）`问题；例：

```c++
void printNameAndDisplay(Window w) // 传值
{
    std::cout << w.name();
    w.display();
}
WindowWithScrollBars wwsb;
printNameAndDisplay(wwsb);

void printNameAndDisplay(const Window& w) // 传引用
{
    std::cout << w.name();
    w.display();
}

```

对于内置类型（int, ...），`pass by value`往往比`pass by reference`效率高些；

总结：

- 尽量以`pass-by-reference-to-const`替换`pass-by-value`，前者通常比较高效，并可避免切割问题（slicing problem）；
- 以上规则并不适用于内置类型，以及STL的迭代器和函数对象；对它们而言，`pass-by-value`往往比较恰当。


## 条款21 必须返回对象时，别妄想返回其reference

一个必须返回新对象的正确写法；例：

```c++
inline const Rational operator * (const Rational& lhs, const Rational& rhs)
{
    return Rational(lhs.n * rhs.n, lhs.d * rhs.d);
}
```

总结：

- 绝不要返回pointer或reference指向一个local stack对象，或返回reference指向一个heap-allocated对象，或返回pointer或reference指向一个local static对象而有可能同时需要多个这样的对象；条款4已经为“在单线程环境中合理返回reference指向一个local static对象”提供了一份设计实例；


## 条款22 将成员变量声明为private

总结：

- 切记将成员变量声明为private，这可赋予客户访问数据的一致性，可细微划分访问控制，允诺约束条件获得保证，并提供class作者以充分的实现弹性；
- protected并不比public更具有封装性；

## 条款23 宁以non-member,non-friend替换member函数

namespace和classes不同，前者可跨越多个源码文件而后者不能；尽量以`non-member`函数替换`member`函数；例：

```c++
class WebBrowser {
public:
    void clearEverything();
}
```

优化为：

```c++
namespace WebBrowserStuff {
    class WebBrowser { ... };
    void clearBrowser(WebBrowser& wb);
};
```

总结：

- 宁可拿`non-member`, `non-friend`函数替换`member`函数，这样做可以增加封装性，包裹弹性（packaging flexibility）和机能扩充性；

## 条款24 若所有参数皆需类型转换，请为此采用non-member函数

```c++
class Rational {
    ...
};
const Rational operator*(const Rational& lhs,
                         const Rational& rhs)
{
    return Rational(lhs.numerator() * rhs.numerator(),
                    lhs.denominator() * rhs.denominator());
}
Rational oneFourth(1, 4);
Rational result;
result = oneFourth * 2;
result = 2 * oneFourth;
```

无论何时如果可以避免friend函数就该避免；

总结：

- 如果你需要为某个函数的所有参数（包括被this指针所指的那个隐喻参数）进行类型转换，那么这个函数必须是个non-member；

## 条款25 考虑写出一个不抛出异常的swap函数

```c++
namespace WidgetStuff {
    ...
    template<typename T>
    class Widget {...};
    ...
    template<typename T>
    void swap(Widget<T& a, // non-member swap函数，这里并不属于std命名空间；
              Widget<T>& b)
    {
        a.swap(b);
    }
}
```

**成员版swap绝不可抛出异常；**

如果缺省的swap实现效率不足，可以考虑以下方法：

1. 提供一个public swap成员函数，让它高效地置换你的类型的两个对象值；
2. 在你的class或template所在的命名空间提供一个non-member swap，并令它调用上述swap成员函数；
3. 如果你正在编写一个class（而非class template），为你的class特化`std::swap`，并令它调用你的swap成员函数；

总结：

- 当`std::swap`对你的类型效率不高时，提供一个swap成员函数，并确定这个函数不抛出异常；
- 如果你提供一个member swap，也该提供一个non-member swap用来调用前者，对于classes(而非templates)，也请特化`std::swap`；
- 调用swap时应针对`std::swap`使用using声明式，然后调用swap并且不带任何“命名空间资格修饰”；
- 为“用户定义类型”进行std templates全特化是好的，但千万不要尝试在std内加入某些对std而言全新的东西；
