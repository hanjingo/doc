# Qt对象

[TOC]



## Q_OBJECT

### 定义

```c++
/* qmake ignore Q_OBJECT */
#define Q_OBJECT \
public: \
    QT_WARNING_PUSH \
    Q_OBJECT_NO_OVERRIDE_WARNING \
    static const QMetaObject staticMetaObject; \
    virtual const QMetaObject *metaObject() const; \
    virtual void *qt_metacast(const char *); \
    virtual int qt_metacall(QMetaObject::Call, int, void **); \
    QT_TR_FUNCTIONS \
private: \
    Q_OBJECT_NO_ATTRIBUTES_WARNING \
    Q_DECL_HIDDEN_STATIC_METACALL static void qt_static_metacall(QObject *, QMetaObject::Call, int, void **); \
    QT_WARNING_POP \
    struct QPrivateSignal {}; \
    QT_ANNOTATE_CLASS(qt_qobject, "")
```

### 作用

宏`Q_OBJECT`主要与元对象系统有关，Qt元对象系统处理流程如下：当编译工程时，遍历所有C++文件，当发现某个类的私有部分声明`Q_OBJECT`宏的时候，自动生成一个`moc_*.cpp`文件，这个文件会生成信号的实现函数，`Q_OBJECT`宏里面定义的函数也会在这个文件中实现，并生成与类相关的元对象。



## 参考

### 外链

- [Qt---之Q_OBJECT详解](https://blog.csdn.net/weixin_39609623/article/details/82966753)
- [Q_OBJECT宏的作用](https://www.cnblogs.com/huanian/p/12877321.html)