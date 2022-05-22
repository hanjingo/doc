# Qt元对象系统

[TOC]



## 元对象系统

`元对象系统（MOC）`

### Q_OBJECT宏

```c++
/* Q_OBJECT 宏定义 */
#define Q_OBJECT \
public: \
    QT_WARNING_PUSH \                                           // 
    Q_OBJECT_NO_OVERRIDE_WARNING \                              // 
    static const QMetaObject staticMetaObject; \                // 定义静态的元对象
    virtual const QMetaObject *metaObject() const; \            // 返回元对象指针
    virtual void *qt_metacast(const char *); \                  // 设置元对象
    virtual int qt_metacall(QMetaObject::Call, int, void **); \ // 对元对象的调用
    QT_TR_FUNCTIONS \                                           // 是否支持i18N
private: \
    Q_OBJECT_NO_ATTRIBUTES_WARNING \
    Q_DECL_HIDDEN_STATIC_METACALL static void qt_static_metacall(QObject *, QMetaObject::Call, int, void **); \
    QT_WARNING_POP \
    struct QPrivateSignal {}; \
    QT_ANNOTATE_CLASS(qt_qobject, "")
```

当编译工程时，遍历所有C++文件，当发现某个类的私有部分声明`Q_OBJECT`宏的时候，自动生成一个`moc_*.cpp`文件，这个文件会生成信号的实现函数，宏里面定义的函数也会在这个文件里面实现，并生成与类相关的元对象。

### QMetaObject

```c++
struct Q_CORE_EXPORT QMetaObject
{
    class Connection;
    const char *className() const;         // 返回类名
    const QMetaObject *superClass() const; // 父类的元对象

    bool inherits(const QMetaObject *metaObject) const Q_DECL_NOEXCEPT;
    QObject *cast(QObject *obj) const;
    const QObject *cast(const QObject *obj) const;

#ifndef QT_NO_TRANSLATION
    QString tr(const char *s, const char *c, int n = -1) const; // 翻译函数
#endif // QT_NO_TRANSLATION

    int methodOffset() const;     // 方法偏移量
    int enumeratorOffset() const; // 枚举偏移量
    int propertyOffset() const;   // 属性偏移量
    int classInfoOffset() const;  // 类信息数目

    int constructorCount() const; // 构造函数数目
    int methodCount() const;      // 方法数目
    int enumeratorCount() const;  // 枚举数据
    int propertyCount() const;    // 属性数目
    int classInfoCount() const;   // 类信息数目

    int indexOfConstructor(const char *constructor) const; // 构造函数索引
    int indexOfMethod(const char *method) const;           // 方法索引
    int indexOfSignal(const char *signal) const;           // 信号量索引
    int indexOfSlot(const char *slot) const;               // 槽索引
    int indexOfEnumerator(const char *name) const;         // 枚举索引
    int indexOfProperty(const char *name) const;           // 属性索引
    int indexOfClassInfo(const char *name) const;          // 类信息索引

    QMetaMethod constructor(int index) const;  // 构造方法
    QMetaMethod method(int index) const;       // 方法
    QMetaEnum enumerator(int index) const;     // 枚举
    QMetaProperty property(int index) const;   // 属性
    QMetaClassInfo classInfo(int index) const; // 类属性信息
    QMetaProperty userProperty() const;        // 用户属性

    static bool checkConnectArgs(const char *signal, const char *method);
    static bool checkConnectArgs(const QMetaMethod &signal,
                                 const QMetaMethod &method);
    static QByteArray normalizedSignature(const char *method);
    static QByteArray normalizedType(const char *type);

    // internal index-based connect
    static Connection connect(const QObject *sender, int signal_index,
                        const QObject *receiver, int method_index,
                        int type = 0, int *types = Q_NULLPTR);
    // internal index-based disconnect
    static bool disconnect(const QObject *sender, int signal_index,
                           const QObject *receiver, int method_index);
    static bool disconnectOne(const QObject *sender, int signal_index,
                              const QObject *receiver, int method_index);
    // internal slot-name based connect
    static void connectSlotsByName(QObject *o);

    // internal index-based signal activation
    static void activate(QObject *sender, int signal_index, void **argv);
    static void activate(QObject *sender, const QMetaObject *, int local_signal_index, void **argv);
    static void activate(QObject *sender, int signal_offset, int local_signal_index, void **argv);

    static bool invokeMethod(QObject *obj, const char *member,
                             Qt::ConnectionType,
                             QGenericReturnArgument ret,
                             QGenericArgument val0 = QGenericArgument(Q_NULLPTR),
                             QGenericArgument val1 = QGenericArgument(),
                             QGenericArgument val2 = QGenericArgument(),
                             QGenericArgument val3 = QGenericArgument(),
                             QGenericArgument val4 = QGenericArgument(),
                             QGenericArgument val5 = QGenericArgument(),
                             QGenericArgument val6 = QGenericArgument(),
                             QGenericArgument val7 = QGenericArgument(),
                             QGenericArgument val8 = QGenericArgument(),
                             QGenericArgument val9 = QGenericArgument());

    static inline bool invokeMethod(QObject *obj, const char *member,
                             QGenericReturnArgument ret,
                             QGenericArgument val0 = QGenericArgument(Q_NULLPTR),
                             QGenericArgument val1 = QGenericArgument(),
                             QGenericArgument val2 = QGenericArgument(),
                             QGenericArgument val3 = QGenericArgument(),
                             QGenericArgument val4 = QGenericArgument(),
                             QGenericArgument val5 = QGenericArgument(),
                             QGenericArgument val6 = QGenericArgument(),
                             QGenericArgument val7 = QGenericArgument(),
                             QGenericArgument val8 = QGenericArgument(),
                             QGenericArgument val9 = QGenericArgument())
    {
        return invokeMethod(obj, member, Qt::AutoConnection, ret, val0, val1, val2, val3,
                val4, val5, val6, val7, val8, val9);
    }

    static inline bool invokeMethod(QObject *obj, const char *member,
                             Qt::ConnectionType type,
                             QGenericArgument val0 = QGenericArgument(Q_NULLPTR),
                             QGenericArgument val1 = QGenericArgument(),
                             QGenericArgument val2 = QGenericArgument(),
                             QGenericArgument val3 = QGenericArgument(),
                             QGenericArgument val4 = QGenericArgument(),
                             QGenericArgument val5 = QGenericArgument(),
                             QGenericArgument val6 = QGenericArgument(),
                             QGenericArgument val7 = QGenericArgument(),
                             QGenericArgument val8 = QGenericArgument(),
                             QGenericArgument val9 = QGenericArgument())
    {
        return invokeMethod(obj, member, type, QGenericReturnArgument(), val0, val1, val2,
                                 val3, val4, val5, val6, val7, val8, val9);
    }

    static inline bool invokeMethod(QObject *obj, const char *member,
                             QGenericArgument val0 = QGenericArgument(Q_NULLPTR),
                             QGenericArgument val1 = QGenericArgument(),
                             QGenericArgument val2 = QGenericArgument(),
                             QGenericArgument val3 = QGenericArgument(),
                             QGenericArgument val4 = QGenericArgument(),
                             QGenericArgument val5 = QGenericArgument(),
                             QGenericArgument val6 = QGenericArgument(),
                             QGenericArgument val7 = QGenericArgument(),
                             QGenericArgument val8 = QGenericArgument(),
                             QGenericArgument val9 = QGenericArgument())
    {
        return invokeMethod(obj, member, Qt::AutoConnection, QGenericReturnArgument(), val0,
                val1, val2, val3, val4, val5, val6, val7, val8, val9);
    }

    QObject *newInstance(QGenericArgument val0 = QGenericArgument(Q_NULLPTR),
                         QGenericArgument val1 = QGenericArgument(),
                         QGenericArgument val2 = QGenericArgument(),
                         QGenericArgument val3 = QGenericArgument(),
                         QGenericArgument val4 = QGenericArgument(),
                         QGenericArgument val5 = QGenericArgument(),
                         QGenericArgument val6 = QGenericArgument(),
                         QGenericArgument val7 = QGenericArgument(),
                         QGenericArgument val8 = QGenericArgument(),
                         QGenericArgument val9 = QGenericArgument()) const;

    enum Call {
        InvokeMetaMethod,
        ReadProperty,
        WriteProperty,
        ResetProperty,
        QueryPropertyDesignable,
        QueryPropertyScriptable,
        QueryPropertyStored,
        QueryPropertyEditable,
        QueryPropertyUser,
        CreateInstance,
        IndexOfMethod,
        RegisterPropertyMetaType,
        RegisterMethodArgumentMetaType
    };

    int static_metacall(Call, int, void **) const;
    static int metacall(QObject *, Call, int, void **);

    struct { // private data
        const QMetaObject *superdata;     // 父类
        const QByteArrayData *stringdata; // 类名
        const uint *data;                 // 指向QMetaObjectPrivate对象的指针
        typedef void (*StaticMetacallFunction)(QObject *, QMetaObject::Call, int, void **);
        StaticMetacallFunction static_metacall;
        const QMetaObject * const *relatedMetaObjects;
        void *extradata; // 扩展数据
    } d;
};
```

元对象的定义。



## 参考

- [Qt---之Q_OBJECT详解](https://blog.csdn.net/weixin_39609623/article/details/82966753)
- [Q_OBJECT宏的作用](https://www.cnblogs.com/huanian/p/12877321.html)