# 6 Inheritance and Object-Oriented Design

[toc]

## 条款32 确定你的public继承塑模出is-a关系

总结：

- "public继承"意味着is-a，适用于base classes身上的每一件事情一定也适用于derived classes身上，因为每一个derived class对象也都是一个base class对象；


## 条款33 避免遮掩继承而来的名称

转交函数（forwarding function）示例：

```c++
class Base {
public:
	virtual void mf1() = 0;
	virtual void mf1(int);
};
class Derived: private Base {
public:
	virtual void mf1() { Base::mf1(); } // 转交函数，暗自成为inline
};
Derived d;
int x;
d.mf1();  // 正确，调用的事Derived::mf1
d.mf1(x); // 错误，Base::mf1()被遮掩了
```

总结：

- derived classes内的名称会遮掩base classes内的名称，在public继承下从来没有人希望如此；
- 为了让被遮掩的名称再见天日，可使用using声明式或转交函数（forwarding functions）；


## 条款34 区分接口继承和实现继承

1. 成员函数的接口总是会被继承；
2. 声明一个pure virtual函数（纯虚函数）的目的是为了让derived classes只继承函数接口；
```c++
class Shape{
public:
    virtual void draw() const = 0;
}
```
3. 声明简朴的impure virtual函数（非纯虚函数）的目的是让derived classes继承该函数的接口和缺省实现；
```c++
class Shape{
public:
    virtual void error(const std::string& msg);
}
```
4. 声明non-virtual函数的目的是为了令derived classes继承函数的接口及一份强制性实现；

总结：

- 接口继承和实现继承不同，在public继承之下，derived classes总是继承base class的接口；
- pure virtual函数只具体指定接口继承；
- 简朴的（impure virtual）非纯虚函数具体指定接口继承及缺省实现继承；
- non-virtual函数具体指定接口继承以及强制性实现继承；


## 条款35 考虑virtual函数以外的其它选择

non-virtual interface(NVI)：TemplateMethod设计模式的一种特殊形式，令客户通过public non-virtual成员函数间接调用private virtual函数；例：

```c++
class GameCharacter {
public:
    int healthValue() const
    {
        int retVal = doHealthValue();
        return retVal;
    }
private:
    virtual int doHealthValue() const { ... } // derived classes可重新定义它
};
```

将virtual函数替换为“函数指针成员变量”，这是Strategy设计模式的一种分解表现形式；

以`std::function`成员变量替换virtual函数，因而允许使用任何可调用物（callable entity）搭配一个兼容于需求的签名式，这也是Strategy设计模式的某种形式；例：

```c++
class GameCharacter;
int defaultHealthCalc(const GameCharacter& gc);
class GameCharacter {
public:
    typedef std::function<int (const GameCharacter&)> HealthCalcFunc;
    explicit GameCharacter(HealthCalcFunc hcf = defaultHealthCalc) : healthFunc(hcf) {}
    int healthValue() const { return healthFunc(*this); }
private:
    HealthCalcFunc healthFunc;
};
```

将继承体系内的virtual函数替换为另一个继承体系内的virtual函数，这是Strategy设计模式的传统实现手法；

总结：

- virtual函数的替代方案包括NVI手法及Strategy设计模式的多种形式，NVI手法自身是一个特殊形式的Template Method设计模式；
- 将机能从成员函数移到class外部函数，带来的一个缺点是，非成员函数无法访问class的non-public成员；
- `std::function`对象的行为就像一般函数指针，这样的对象可接纳“与给定之目标签名式（target signature）兼容”的所有可调用物（callable entities）;


## 条款36 绝不重新定义继承而来的non-virtual函数

总结：

- 绝对不要重新定义继承而来的non-virtual函数；


## 条款37 绝不重新定义继承而来的缺省参数值

```c++
class Shape {
public:
    enum ShapeColor { Read, Green, Blue };
    void draw(ShapeColor color = Red) const
    {
        doDraw(color);
    }
private:
    virtual void doDraw(ShapeColor color) const = 0;
};
class Rectangle: public Shape {
public:
    ...
private:
    virtual void doDraw(ShapeColor color) const;
};
```

总结：

- 绝对不要重新定义一个继承而来的缺省参数值，因为缺省参数值都是静态绑定，而virtual函数-你唯一应该覆写的东西-却是动态绑定；


## 条款38 通过复合塑模出has-a或“根据某物实现出”

总结：

- 复合（composition）的意义和public继承完全不同；
- 在应用域（application domain），复合意味has-a（有一个）；在实现域（implementation domain），复合意味is-implemented-in-terms-of（根据某物实现出）；


## 条款39 明智而审慎地使用private继承

尽可能使用复合，必要时才使用private继承；

总结：

- Private继承意味is-implemented-in-terms of（根据某物实现出），它通常比复合（composition）的级别低，但是当derived class需要访问protected base class的成员，或需要重新定义继承而来的virtual函数时，这么设计是合理的；
- 和复合（composition）不同，private继承可以造成empty base最优化，这对致力于“对象尺寸最小化”的程序库开发者而言，可能很重要；


## 条款40 明智而审慎地使用多重继承

1. 非必要不使用virtual bases，平常请使用non-virtual继承；
2. 如果必须使用virtual base classes，尽可能避免在其中放置数据；

多重继承的一种用法；例：

```c++
class IPerson {
public:
    virtual ~IPerson();
    virtual std::string name() const = 0;
    virtual std::string birthDate() const = 0;
};
class DatabaseID { ... };
class PersonInfo {
public:
    explicit PersonInfo(DatabaseID pid);
    virtual ~PersonInfo();
    virtual const char* theName() const;
    virtual const char* theBirthDate() const;
    virtual const char* valueDelimOpen() const;
    ...
};
class CPerson: public IPerson, private PersonInfo { // 多重继承
public:
    explicit CPerson(DatabaseID pid): PersonInfo(pid) { }
    virtual std::string name() const { return PersonInfo::theName(); }
    virtual std::string birthDate() const { return PersonInfo::theBirthDate(); }
private:
    const char* valueDelimOpen() const { return ""; } // 重新定义继承而来的virtual“界限函数”
    const char* valueDelimClose() const { return ""; }
};
```

总结：

- 多重继承比单一继承复杂，他可能导致新的歧义性，以及对virtual继承的需要；
- virtual继承会增加大小，速度，初始化（及赋值）复杂度等等成本，如果virtual base classes不带任何数据，将是最具实用价值的情况；
- 多重继承的确有正当用途，其中一个情节涉及“public继承某个Interface class”和“private继承某个协助实现的class”的两相组合；