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