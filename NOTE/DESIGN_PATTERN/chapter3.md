# 可复用面向对象软件的基础 结构型模式
## 结构型模式
简介:通过组合类和对象获得更大的结构

### 适配器(ADAPTER)
简介:将某个类的接口转换成客户端期望的另一个接口表示，目的是消除由于接口不匹配所造成的类的兼容性问题

用途:
> 1. 系统需要使用现有的类，而此类的接口不符合系统的需要
> 2. 想要建立一个可以重复使用的类，用于与一些彼此之间没有太大关联的一些类，包括一些可能在将来引进的类一起工作，这些源类不一定有一致的接口
> 3. 通过接口转换，将一个类插入另一个类系中

示例:
```c++
//使用复合，对象模式
class Deque  //双端队列，被适配类
{
public:
    void push_back(int x)
    {
        cout << "Deque push_back:" << x << endl;
    }
    void push_front(int x)
    {
        cout << "Deque push_front:" << x << endl;
    }
    void pop_back()
    {
        cout << "Deque pop_back" << endl;
    }
    void pop_front()
    {
        cout << "Deque pop_front" << endl;
    }
};

class Sequence  //顺序类，目标类
{
public:
    virtual void push(int x) = 0;
    virtual void pop() = 0;
};

class Stack:public Sequence   //栈, 适配类
{
public:
    void push(int x)
    {
        m_deque.push_back(x);
    }
    void pop()
    {
        m_deque.pop_back();
    }

private:
    Deque m_deque;
};

class Queue:public Sequence  //队列，适配类
{
public:
    void push(int x)
    {
        m_deque.push_back(x);
    }
    void pop()
    {
        m_deque.pop_front();
    }

private:
    Deque m_deque;
};
//END
```

- - -
### 桥接(BRIDGE)
简介:将抽象部分与实现部分分离，使它们都可以独立变换

用途:
> 1. 解决需求较多且易变的情况下,类爆炸的问题

示例:
```c++
//将各种App、各种手机全部独立分开，使其自由组合桥接
class App
{
public:
    virtual ~App(){ cout << "~App()" << endl; }
    virtual void run() = 0;
};

class GameApp:public App
{
public:
    void run()
    {
        cout << "GameApp Running" << endl;
    }
};

class TranslateApp:public App
{
public:
    void run()
    {
        cout << "TranslateApp Running" << endl;
    }
};

class MobilePhone
{
public:
    virtual ~MobilePhone(){ cout << "~MobilePhone()" << endl;}
    virtual void appRun(App* app) = 0;  //实现App与手机的桥接
};

class XiaoMi:public MobilePhone
{
public:
    void appRun(App* app)
    {
        cout << "XiaoMi: ";
        app->run();
    }
};

class HuaWei:public MobilePhone
{
public:
    void appRun(App* app)
    {
        cout << "HuaWei: ";
        app->run();
    }
};

int main()
{
    App* gameApp = new GameApp;
    App* translateApp = new TranslateApp;
    MobilePhone* mi = new XiaoMi;
    MobilePhone* hua = new HuaWei;
    mi->appRun(gameApp);
    mi->appRun(translateApp);
    hua->appRun(gameApp);
    hua->appRun(translateApp);
    delete hua;
    delete mi;
    delete gameApp;
    delete translateApp;
    return 0;
}
```

- - -
### 组合(COMPOSITE)
简介:将对象组合成树形结构以表示“部分-整体”的层次结构，组合模式使得用户对单个对象和组合对象的使用具有一致性

用途:
> 1. 解耦

示例:
```c++
class Company
{
public:
    Company(string name):m_name(name){}
    virtual ~Company(){}
    virtual void add(Company* company) = 0;
    virtual void remove(string name) = 0;
    virtual void display(int depth) = 0;

    string getName()
    {
        return m_name;
    }

protected:
    string m_name;
};

//具体的公司
class ConcreteCompany:public Company   //树枝
{
public:
    ConcreteCompany(string name):Company(name){}

    ~ConcreteCompany()
    {
        cout << "~ConcreteCompany()" << endl;
    }
    void add(Company* company) override;
    void remove(string name) override;
    void display(int depth) override;

private:
    list<shared_ptr<Company>> m_listCompany;
};

void ConcreteCompany::add(Company* company)
{
    shared_ptr<Company> temp(company);
    m_listCompany.push_back(temp);
}

void ConcreteCompany::remove(string name)
{
    list<shared_ptr<Company>>::iterator iter = m_listCompany.begin();
    for(; iter != m_listCompany.end(); iter++)
    {
        shared_ptr<Company> temp(*iter);
        string strName = temp.get()->getName();
        if(name == strName)
        {
            m_listCompany.erase(iter);
        }
    }
}

void ConcreteCompany::display(int depth)
{
    for(int i = 0; i < depth; i++)
    {
        cout << "-";
    }
    cout << m_name.data() << endl;
    list<shared_ptr<Company>>::iterator iter = m_listCompany.begin();
    for(; iter != m_listCompany.end(); iter++)
    {
        shared_ptr<Company> temp(*iter);
        temp.get()->display(depth + 2);
    }
}

//公司下的部门
class FinanceDept:public Company    //树叶
{
public:
    FinanceDept(string name):Company(name){}
    ~FinanceDept()
    {
        cout << "~FinanceDept()" << endl;
    }
    void add(Company* company) override;
    void remove(string name) override;
    void display(int depth) override;
};

void FinanceDept::add(Company* company)
{
    cout << "FinanceDept add failed" << endl;
}

void FinanceDept::remove(string name)
{
    cout << "FinanceDept remove failed" << endl;
}

void FinanceDept::display(int depth)
{
    for(int i = 0; i < depth; i++)
    {
        cout << "-";
    }
    cout << m_name.data() << endl;
}

//公司下的部门
class HRDept:public Company  //树叶
{
public:
    HRDept(string name):Company(name){}
    ~HRDept()
    {
        cout << "~HRDept()" << endl;
    }
    void add(Company* company) override;
    void remove(string name) override;
    void display(int depth) override;
};

void HRDept::add(Company* company)
{
    cout << "HRDept add failed" << endl;
}

void HRDept::remove(string name)
{
    cout << "HRDept remove failed" << endl;
}

void HRDept::display(int depth)
{
    for(int i = 0; i < depth; i++)
    {
        cout << "-";
    }
    cout << m_name.data() << endl;
}

int main(int argc, char *argv[])
{
    Company* root = new ConcreteCompany("zong");
    Company* f1 = new FinanceDept("F1");
    Company* h1 = new HRDept("H1");
    root->add(f1);
    root->add(h1);
    Company* c1 = new ConcreteCompany("fen1");
    Company* f2 = new FinanceDept("F2");
    Company* h2 = new HRDept("H2");
    c1->add(f2);
    c1->add(h2);
    root->add(c1);
    root->display(0);
    delete root;
    return 0;
}
```

- - -
###　装饰(DECORATOR)
简介:动态地给一个**对象**而不是**整个类**添加一些额外的功能

用途:
>　1. 避免类爆炸问题

示例:
```c++
class Dumplings    //抽象类   饺子
{
public:
    virtual ~Dumplings(){}
    virtual void showDressing() = 0;
};

class MeatDumplings:public Dumplings    //现实类  肉馅饺子
{
public:
    ~MeatDumplings(){ cout << "~MeatDumplings()" << endl; }
    void showDressing()
    {
        cout << "Add Meat" << endl;
    }
};

class DecoratorDumpling:public Dumplings    //装饰类
{
public:
    DecoratorDumpling(Dumplings* d):m_dumpling(d){}
    virtual ~DecoratorDumpling(){ cout << "~DecoratorDumpling()" << endl; }
    void showDressing()
    {
        m_dumpling->showDressing();
    }

private:
    Dumplings* m_dumpling;
};

class SaltDecorator:public DecoratorDumpling   // 装饰类  加盐
{
public:
    SaltDecorator(Dumplings* d):DecoratorDumpling(d){}
    ~SaltDecorator(){ cout << "~SaltDecorator()" << endl; }
    void showDressing()
    {
        DecoratorDumpling::showDressing();   //注意点
        addDressing();
    }

private:
    void addDressing()
    {
        cout << "Add Salt" << endl;
    }
};

class OilDecorator:public DecoratorDumpling   //装饰类  加油
{
public:
    OilDecorator(Dumplings* d):DecoratorDumpling(d){}
    ~OilDecorator(){ cout << "~OilDecorator()" << endl; }
    void showDressing()
    {
        DecoratorDumpling::showDressing(); //注意点
        addDressing();
    }

private:
    void addDressing()
    {
        cout << "Add Oil" << endl;
    }
};

class CabbageDecorator:public DecoratorDumpling  //装饰类   加蔬菜
{
public:
    CabbageDecorator(Dumplings* d):DecoratorDumpling(d){}
    ~CabbageDecorator(){ cout << "~CabbageDecorator()" << endl; }
    void showDressing()
    {
        DecoratorDumpling::showDressing(); //注意点
        addDressing();
    }

private:
    void addDressing()
    {
        cout << "Add Cabbage" << endl;
    }
};

int main()
{
    Dumplings* d = new MeatDumplings;           //原始的肉饺子
    Dumplings* d1 = new SaltDecorator(d);       //加盐后的饺子
    Dumplings* d2 = new OilDecorator(d1);       //加油后的饺子
    Dumplings* d3 = new CabbageDecorator(d2);   //加蔬菜后的饺子
    d3->showDressing();
    delete d;
    delete d1;
    delete d2;
    delete d3;
    return 0;
}
```

- - -
### 外观(FACADE)
简介:为子系统中的一组接口定义一个一致的界面，外观模式提供了一个高层接口，这个接口使得这一子系统更加容易被使用；对于复杂的系统，系统为客户提供一个简单的接口，把复杂的实现过程封装起来，客户不需要了解系统内部的细节

用途:
> 1. 客户不需要了解系统内部复杂的细节，只需要一个接口；系统入口

示例:
```c++
class Cpu
{
public:
    void productCpu()
    {
        cout << "Product Cpu" << endl;
    }
};

class Ram
{
public:
    void productRam()
    {
        cout << "Product Ram" << endl;
    }
};

class Graphics
{
public:
    void productGraphics()
    {
        cout << "Product Graphics" << endl;
    }
};

class Computer
{
public:
    void productComputer()
    {
        Cpu cpu;
        cpu.productCpu();
        Ram ram;
        ram.productRam();
        Graphics graphics;
        graphics.productGraphics();
    }
};

int main()
{
    //客户直接调用computer生产函数，无需关心具体部件的生产过程。也可直接单独生产部件
    Computer computer;   
    computer.productComputer();
    Cpu cpu;
    cpu.productCpu();
    return 0;
}
```

- - -
### 享元(FLYWEIGHT)
简介:运用共享技术有效地支持大量细粒度的对象,也就是对象共享

用途:
> 1. 有大量对象时,对于相同的部分,抽取出来作为共享内存

示例:
```c++
//以Money的类别作为内部标识，面值作为外部状态。
enum MoneyCategory   //类别，内在标识，作为标识码
{
    Coin,
    bankNote
};

enum FaceValue      //面值，外部标识，需要存储的对象
{
    ValueOne = 1,
    ValueTwo
};

class Money      //抽象父类
{
public:
    Money(MoneyCategory cate):m_mCate(cate){}
    virtual ~Money(){ cout << "~Money() " << endl; }
    virtual void save() = 0;

private:
    MoneyCategory m_mCate;
};

class MoneyCoin:public Money    //具体子类1
{
public:
    MoneyCoin(MoneyCategory cate):Money(cate){}
    ~MoneyCoin(){ cout << "~MoneyCoin()" << endl; }
    void save()
    {
        cout << "Save Coin" << endl;
    }
};

class MoneyNote:public Money   //具体子类2
{
public:
    MoneyNote(MoneyCategory cate):Money(cate){}
    ~MoneyNote(){ cout << "~MoneyNote()" << endl; }
    void save()
    {
        cout << "Save BankNote" << endl;
    }
};

class Bank
{
public:
    Bank():m_coin(nullptr),m_note(nullptr),m_count(0){}
    ~Bank()
    {
        if(m_coin != nullptr)
        {
            delete m_coin;
            m_coin = nullptr;
        }
        if(m_note != nullptr)
        {
            delete m_note;
            m_note = nullptr;
        }
    }

    void saveMoney(MoneyCategory cate, FaceValue value)
    {
        switch(cate)    //以类别作为标识码
        {
        case Coin:
        {
            if(m_coin == nullptr)  //内存中存在标识码所标识的对象，则直接调用，不再创建
            {
                m_coin = new MoneyCoin(Coin);
            }
            m_coin->save();
            m_vector.push_back(value);
            break;
        }
        case bankNote:
        {
            if(m_note == nullptr)
            {
                m_note = new MoneyNote(bankNote);
            }
            m_note->save();
            m_vector.push_back(value);
            break;
        }

        default:
            break;
        }
    }

    int sumSave()
    {
        auto iter = m_vector.begin();
        for(; iter != m_vector.end(); iter++)
        {
            m_count += *iter;
        }
        return m_count;
    }

private:
    vector<FaceValue> m_vector;
    Money* m_coin;
    Money* m_note;
    int m_count;
};

int main()
{
    Bank b1;
    b1.saveMoney(Coin, ValueOne);
    b1.saveMoney(Coin, ValueTwo);
    b1.saveMoney(Coin, ValueTwo);
    b1.saveMoney(bankNote, ValueOne);
    b1.saveMoney(bankNote, ValueTwo);
    cout << b1.sumSave() << endl;
    return 0;
}
```

- - -
### 代理(PROXY)
简介:为其它对象提供一种代理以控制对这个对象的访问

用途:
> 1. 防止用户直接访问对象

示例:
```c++
class Gril
{
public:
    Gril(string name = "gril"):m_string(name){}
    string getName()
    {
        return m_string;
    }

private:
    string m_string;
};

class Profession
{
public:
    virtual ~Profession(){}
    virtual void profess() = 0;
};

class YoungMan:public Profession
{
public:
    YoungMan(Gril gril):m_gril(gril){}
    void profess()
    {
        cout << "Young man love " << m_gril.getName().data() << endl;
    }

private:
    Gril m_gril;
};

class ManProxy:public Profession
{
public:
    ManProxy(Gril gril):m_man(new YoungMan(gril)){}
    void profess()
    {
        cout << "I am Proxy" << endl;
        m_man->profess();
    }

private:
    YoungMan* m_man;
};

int main(int argc, char *argv[])
{
    Gril gril("hei");
    Profession* proxy = new ManProxy(gril);
    proxy->profess();
    delete proxy;
    return 0;
}
```