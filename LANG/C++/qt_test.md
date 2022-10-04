# QT单元测试


<!-- vim-markdown-toc GFM -->

* [QTestlib](#qtestlib)
    - [使用示例](#使用示例)
* [参考](#参考)

<!-- vim-markdown-toc -->



## QTestlib

### 使用示例

1. 新建一个待测试工程hello：

   ```c++
   #ifndef HELLO_HPP
   #define HELLO_HPP
   
   #include <string>
   
   class Hello
   {
   public:
       Hello(bool b, std::string str, double db, int i)
           : b_{b}, s_{str}, db_{db}, i_{i}
       {}
       ~Hello() {}
   
       void Void()
       {
           return;
       }
       bool Bool()
       {
           return b_;
       }
       std::string String()
       {
           return s_;
       }
       double Double()
       {
           return db_;
       }
       int Int()
       {
           return i_;
       }
   
   private:
       bool        b_;
       std::string s_;
       double      db_;
       int         i_;
   };
   
   #endif // HELLO_HPP
   
   ```

2. 新建一个空的工程hello_test，并在`.pro`文件中将testlib加入QT参数中

   ```txt
   QT += testlib
   QT -= gui
   
   CONFIG += qt console warn_on depend_includepath testcase
   CONFIG -= app_bundle
   
   TEMPLATE = app
   
   SOURCES += \
       hello_test.cpp
   
   HEADERS += \
       ../hello/hello.hpp
   ```

3. 新建测试代码hello_test.cpp：

   ```c++
   #include <QtTest>
   #include "../hello/hello.hpp"
   
   // add necessary includes here
   
   class HelloTest : public QObject
   {
       Q_OBJECT
   
   public:
       HelloTest();
       ~HelloTest();
   
   private slots:
       void Void();
       void Bool();
       void String();
       void Double();
       void Int();
   
   };
   
   HelloTest::HelloTest()
   {
   
   }
   
   HelloTest::~HelloTest()
   {
   
   }
   
   void HelloTest::Void()
   {
       Hello h{true, "hello", 1.23, 1};
   }
   
   void HelloTest::Bool()
   {
       Hello h{true, "hello", 1.23, 1};
       QVERIFY(h.Bool() == true);
   }
   
   void HelloTest::String()
   {
       Hello h{true, "hello", 1.23, 1};
       QVERIFY(h.String() == "world");
   }
   
   void HelloTest::Double()
   {
       Hello h{true, "hello", 1.23, 1};
       QVERIFY(h.Double() == 1.23);
   }
   
   void HelloTest::Int()
   {
       Hello h{true, "hello", 1.23, 1};
       QVERIFY(h.Int() == 1);
   }
   
   QTEST_APPLESS_MAIN(HelloTest) // 类似于main函数
   
   #include "hellotest.moc"
   ```

   

## 参考

- [QTest单元测试框架，简单，好用，高效](https://zhuanlan.zhihu.com/p/39376945)
- [Qt 5单元测试框架](https://blog.csdn.net/hebbely/article/details/78948694)
- [Qt单元测试框架快速上手](http://www.qtbig.com/2019/06/25/qt/qt_quick_study_qtest/)
