# 可复用面向对象软件的基础 创建型模式
特别说明:本文件中部分代码来自:
1. https://www.cnblogs.com/chengjundu/p/8473564.html
2. <设计模式：可复用面向对象软件的基础>

## 创建型模式
简介:在创建对象时使用方法or类而不使用new运算符的方式

### 生成器(BUILDER)
简介:将一个复杂对象的构建与他的表示分离,使得同样的构建过程可以创建不同的表示

用途:
> 1. 当创建复杂对象的算法应该独立于该对象的组成部分以及他们的装配方式时
> 2. 当构造过程必须允许被构造的对象有不同的表示时

- - -
### 工厂方法(FACTORY METHOD)
简介:定义一个创建对象的接口，让子类决定实例化哪一个类，Factory Method使一个类的实例化延迟到其子类。

用途:
> 1. 我们明确地计划不同条件下创建不同实例的时候
> 2. 当一个类希望由它的子类来制定它所创建的对象的时候

示例:
```c++
class Tank
{
public:
    virtual void message() = 0;
};

class Tank80:public Tank
{
public:
    void message()
    {
        cout << "Tank80" << endl;
    }
};

class Tank99:public Tank
{
public:
    void message()
    {
        cout << "Tank99" << endl;
    }
};

class TankFactory
{
public:
    virtual Tank* createTank() = 0;
};

class Tank80Factory:public TankFactory
{
public:
    Tank* createTank()
    {
        return new Tank80();
    }
};

class Tank99Factory:public TankFactory
{
public:
    Tank* createTank()
    {
        return new Tank99();
    }
};
```

- - -
### 抽象工厂(ABSTACT FACTORY)
简介:提供一个创建一系列相关或相互依赖的对象接口，无需指定他们的具体类.

用途:
> 在一个产品族里面，定义多个产品,而系统只消费其中某一族的产品

示例:
```c++
class Tank
{
public:
    virtual void message() = 0;
};

class Tank80:public Tank
{
public:
    void message()
    {
        cout << "Tank80" << endl;
    }
};

class Tank99:public Tank
{
public:
    void message()
    {
        cout << "Tank99" << endl;
    }
};

class Plain
{
public:
    virtual void message() = 0;
};

class Plain80: public Plain
{
public:
    void message()
    {
        cout << "Plain80" << endl;
    }
};

class Plain99: public Plain
{
public:
    void message()
    {
        cout << "Plain99" << endl;
    }
};

class Factory
{
public:
    virtual Tank* createTank() = 0;
    virtual Plain* createPlain() = 0;
};

class Factory80:public Factory
{
public:
    Tank* createTank()
    {
        return new Tank80();
    }

    Plain* createPlain()
    {
        return new Plain80();
    }
};

class Factory99:public Factory
{
public:
    Tank* createTank()
    {
        return new Tank99();
    }

    Plain* createPlain()
    {
        return new Plain99();
    }
};
```

- - -
###　原型(PROTOTYPE)
简介:用原型实例指定创建对象的种类,并且通过拷贝这些原型创建新的对象

用途:一般用在一开始不确定对象的类型,需要在程序运行期间创建新的对象

示例:
```c++
class Clone
{
public:
    Clone()
    {
    }
    virtual ~Clone()
    {
    }
    virtual Clone* clone() = 0;
    virtual void show() = 0;
};

class Sheep:public Clone
{
public:
    Sheep(int id, string name):Clone(),m_id(id),m_name(name)
    {
        cout << "Sheep() id add:" << &m_id << endl;
        cout << "Sheep() name add:" << &m_name << endl;
    }

    ~Sheep()
    {
    }

    Sheep(const Sheep& obj)
    {
        this->m_id = obj.m_id;
        this->m_name = obj.m_name;
        cout << "Sheep(const Sheep& obj) id add:" << &m_id << endl;
        cout << "Sheep(const Sheep& obj) name add:" << &m_name << endl;
    }

    Clone* clone()
    {
        return new Sheep(*this);
    }

    void show()
    {
        cout << "id  :" << m_id << endl;
        cout << "name:" << m_name.data() << endl;
    }

private:
    int m_id;
    string m_name;
};

int main()
{
    Clone* s1 = new Sheep(1, "abs");
    s1->show();
    Clone* s2 = s1->clone();
    s2->show();
    delete s1;
    delete s2;
    return 0;
}
```

- - -
###　单例(SINGLETON)
简介:保证一个类只有一个实例,并提供一个访问他的全局访问点

单例大约有两种实现方法：懒汉与饿汉。
>　懒汉：在第一次用到类实例的时候才会去实例化
>　饿汉：在单例类定义的时候就进行实例化

特点与选择：
- 由于要进行线程同步，所以在访问量比较大，或者可能访问的线程比较多时，采用饿汉实现，可以实现更好的性能。这是以空间换时间
- 在访问量较小时，采用懒汉实现。这是以时间换空间

示例:
```c++
//懒汉式：加lock，线程安全
std::mutex mt;
class Singleton
{
public:
    static Singleton* getInstance();

private:
    Singleton(){}
    Singleton(const Singleton&) = delete;  //明确拒绝
    Singleton& operator=(const Singleton&) = delete; //明确拒绝
    static Singleton* m_pSingleton;
};

Singleton* Singleton::m_pSingleton = NULL;
Singleton* Singleton::getInstance()
{
    if(m_pSingleton == NULL)
    {
        mt.lock();
        m_pSingleton = new Singleton();
        mt.unlock();
    }
    return m_pSingleton;
}
//END

//饿汉式：线程安全，注意delete
class Singleton
{
public:
    static Singleton* getInstance();
private:
    Singleton(){}
    Singleton(const Singleton&) = delete;  //明确拒绝
    Singleton& operator=(const Singleton&) = delete; //明确拒绝
    static Singleton* m_pSingleton;
};

Singleton* Singleton::m_pSingleton = new Singleton();
Singleton* Singleton::getInstance()
{
    return m_pSingleton;
}
//END
```