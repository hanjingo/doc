# QT5信号槽的5种重载形式：
```c++
QMetaObject::Connection connect(const QObject *, const char *, const QObject *, const char *, Qt::ConnectionType);
QMetaObject::Connection connect(const QObject *, const QMetaMethod &,const QObject *, const QMetaMethod &, Qt::ConnectionType);
QMetaObject::Connection connect(const QObject *, const char *, const char *, Qt::ConnectionType) const;
QMetaObject::Connection connect(const QObject *, PointerToMemberFunction, const QObject *, PointerToMemberFunction, Qt::ConnectionType)
QMetaObject::Connection connect(const QObject *, PointerToMemberFunction, Functor);
```

# QT4信号槽的3种重载形式：
```c++
bool connect(const QObject *, const char *, const QObject *,const char *, Qt::ConnectionType );
bool connect(const QObject *, const QMetaMethod &, const QObject *, const QMetaMethod &, Qt::ConnectionType);
bool connect(const QObject *, const char *, const char *, Qt::ConnectionType) const
```