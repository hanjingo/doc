# 5 Implementations

[TOC]

## 条款26 尽可能延后变量定义式的出现时间

```c++
std::string encryptPassword(const std::string& password)
{
    using namespace std;
    string encrypted; // 过早的定义了变量，并且定义时没有及时赋值
    if (password.length() < MinimumPasswordLength) {
        throw logic_error("Password is to short");
    }
    encrypted = password
    encrypt(encrypted);
    return encrypted;
}
```

优化为：

```c++
std::string encryptPassword(const std::string& password)
{
    using namespace std;
    if (password.length() < MinimumPasswordLength) {
        throw logic_error("Password is to short");
    }
    string encrypted{password};
    return encrypted;
}
```

总结：

- 尽可能延后变量定义式的出现，这样做可增加爱程序的清晰度并改善程序效率；



## 条款27 尽量少做转型动作

旧式转型：

- `(T)expression`
- `T(expression)`

例：

```c++
class Widget {
public:
    explicit Widget(int size);
};
void doSomeWork(const Widget& w);
doSomeWork(Widget(15)); // T(expression)
```

新式转型：

- `const_cast` 通常被用来将对象的常量性转除（cast away the constness），它也是唯一有此能力的C++ style转型操作符；

- `dynamic_cast` 主要用来执行“安全向下转型”（safe downcastring），也就是用来决定某对象是否归属继承体系中的某个类型；它是唯一无法由旧式语法执行的动作，也是唯一可耗费重大运行成本的转型动作；

  降低`dynamic_cast`执行成本的方法：

  1. 使用容器并在其中存储直接指向`derived class`对象的指针；例：

     错误的做法：

     ```c++
     class Window { ... };
     class SpecialWindow : public Window {
     public:
         void blink();
         ...
     };
     typedef std::vector<std::shared_ptr<Window> > VPW;
     VPW winPtrs;
     for (VPW::iterator itr = winPtrs.begin(); iter != winPtrs.end(); ++iter) {
         if (SpecialWindow *psw = dynamic_cast<SpecialWindow*>(iter->get()))
             psw->blink();
     }
     ```

     修改为：

     ```c++
     typedef std::vector<std::shared_ptr<SpecialWindow> > VPSW;
     VPSW winPtrs;
     for (VPSW::iterator iter = winPtrs.begin(); iter != winPtrs.end(); ++iter)
         (*iter)->blink();
     ```

  2. 在`base class`内提供virtual函数来处理任务；

     ```c++
     class Window {
     public:
         ...
     };
     class SpecialWindow : public Window {
     public:
         ...
     };
     typedef std::vector<std::shared_ptr<Window> > VPW;
     VPW winPtrs;
     for (VPW::iterator iter = winPtrs.begin(); iter != winPtrs.end(); ++iter)
         (*iter)->blink();
     ```

  3. 避免连续的`dynamic_casts`；

     ```c++
     class Window {...};
     ...
     typedef std::vector<std::shared_ptr<Window> > VPW;
     VPW winPtrs;
     ...
     for (VPW::iterator iter = winPtrs.begin(); iter != winPtrs.end(); ++iter)
     {
         if (SpecialWindow1 *psw1 = dynamic_cast<SpecialWindow1*>(iter->get())) {...}
         else if (SpecialWindow1 *psw2 = dynamic_cast<SpecialWindow1*>(iter->get())) {...} // 及其糟糕的做法
         else if (SpecialWindow1 *psw3 = dynamic_cast<SpecialWindow1*>(iter->get())) {...}
         ...
     }
     ```

- `reinterpret_cast` 意图执行低级转型，实际动作（及结果）可能取决于编译器，这也就表示它不可移植；

- `static_cast` 用来强迫隐式转换（implicit conversions）；

  例：

  ```c++
  class Widow {
  public:
      virtual void onResize() { ... }
  };
  class SpecialWindow : public Window {
  public:
      virtual void onResize() {
          static_cast<Window>(*this).onResize(); // 不要这样做！！！
      }
  }
  ```

  修改为：

  ```c++
  class Widow {
  public:
      virtual void onResize() { ... }
  };
  class SpecialWindow : public Window {
  public:
      virtual void onResize() {
          Window::onResize(); // 调用Window::onResize作用于*this身上
      }
  }
  ```

总结：

- 如果可以，尽量避免转型，特别是在注重效率的代码中避免`dynamic_casts`，如果有个设计需要转型动作，试着发展无需转型的替代设计；
- 如果转型是必要的，试着将它隐藏于某个函数背后，客户随后可以调用该函数，而不需要将转型放进他们自己的代码内；
- 宁可使用C++ style（新式）转型，不要使用旧式转型，前者很容易辨识出来，而且也比较有着分门别类的作用。


## 条款28 避免返回handles指向对象内部成分

References，指针和迭代器统称为handles，返回一个“代表对象内部数据”的handle，带来的是“降低对象封装性”的风险；如果一定要这么做（最好不要这么做，可能会导致指针空悬问题），加上const；例：

```c++
struct RectData {
    Point ulhc;
    Point lrhc;
};

class Rectangle {
private:
    std::shared_ptr<RectData> pData;
public:
    ...
    const Point& upperLeft() const { return pData->ulhc; }
    const Point& lowerRight() const { return pData->lrhc; }
    ...
};
```

总结：

- 避免返回handles（包括references，指针，迭代器）指向对象内部，遵守这个条款可增加封装性，帮助const成员函数的行为像个const，并将发生“空悬”(dangling handles)的可能性降至最低；


## 条款29 为“异常安全”而努力是值得的

```c++
// 非异常安全版本
void PrettyMenu::changeBackground(std::istream& imgSrc)
{
    lock(&mutex);
    delete bgImage;
    ++imageChanges;
    bgImage = new Image(imgSrc);
    unlock(&mutex);
}
```

```c++
// 异常安全版本
void PrettyMenu::changeBackground(std::istream& imgSrc)
{
    Lock m1(&mutex);
    delete bgImage;
    ++imageChanges;
    bgImage = new Image(imgSrc);
}
```

带有异常安全性的函数在异常被抛出时：

1. 不泄漏任何资源；
2. 不允许数据败坏；

异常安全函数（Exception-safe functions）提供**以下三个保证之一**：

1. 基本承诺
    如果异常被抛出，程序内的任何事物仍然保持在有效状态下，没有任何对象或数据结构会因此而败坏，所有对象都处于一种内部前后一致的状态；
2. 强烈保证
    如果异常被抛出，程序状态不改变；如果函数调用失败，程序会回复到“调用函数之前”的状态；
3. 不抛掷（nothrow）保证
    承诺绝不抛出异常，因为它们总是能够完成它们原先承诺的功能；作用于内置类型（例如ints，指针等）身上的所有操作都提供nothrow保证；

`pimpl idiom`：将所有“隶属对象的数据”从原对象放进另一个对象内，然后赋予原对象一个指针，指向哪个所谓的实现对象（implementation object, 副本）；例：

```c++
struct PMImpl {
    std::shared_ptr<Image> bgImage;
    int imageChanges;
};
class PrettyMenu {
    ...
private:
    Mutex mutex;
    std::shared_ptr<PMImpl> pImpl;
};
void PrettyMenu::changeBackground(std::istream& imgSrc)
{
    using std::swap;
    Lock m1(&mutex); // 获得mutex的副本数据
    std::shared_ptr<PMImpl> pNew(new PMImpl(*pImpl));
    pNew->bgImage.reset(new Image(imgSrc)); // 修改副本
    ++pNew->imageChanges;
    swap(pImpl, pNew); // swap数据，释放mutex
}
```

`copy-and-swap`：修改对象数据的副本，然后在一个不抛出异常的函数中将修改后的数据和原件置换；有以下缺点：

1. 并不保证整个函数有强烈的异常安全性；
2. 效率较低；

总结：

- 异常安全函数（Exception-safe functions）即使发生异常也不会泄漏资源或允许任何数据结构损坏；这样的函数区分为三种可能的保证：基本型，强烈型，不抛异常型；
- "强烈保证"往往能够以copy-and-swap实现出来，但“强烈保证”并非对所有函数都可实现或具备现实意义；
- 函数提供的“异常安全保证”通常最高只等于其所调用之各个函数的“异常安全保证”中的最弱者；


## 条款30 透彻了解inlining的里里外外

TODO