# Qt操作数据库


<!-- vim-markdown-toc GFM -->

* [Sqlite](#sqlite)
    - [示例](#示例)
        + [QT5操作sqlite](#qt5操作sqlite)
* [参考](#参考)

<!-- vim-markdown-toc -->



## Sqlite

### 示例

#### QT5操作sqlite

1. 引入sql模块

   ```txt
   QT +=sql
   ```

2. 编写逻辑

   ```c++
   #include <QCoreApplication>
   
   #include <QSql>
   #include <QSqlDatabase>
   #include <QSqlError>
   #include <QSqlQuery>
   
   #include <QDebug>
   #include <QString>
   
   int main(int argc, char* argv[])
   {
       QCoreApplication a(argc, argv);
   
       QSqlDatabase db;
       if (QSqlDatabase::contains("QSQLITE")) {
           db = QSqlDatabase::database("QSQLITE");
       } else {
           db = QSqlDatabase::addDatabase("QSQLITE");
       }
   
       // 设置主机名
       db.setHostName("host1");
   
       // 设置数据库名
       db.setDatabaseName("env");
   
       // 设置用户名
       db.setUserName("he");
   
       // 设置密码
       db.setPassword("123456");
   
       // 打开链接
       db.open();
   
       // 创建表
       QSqlQuery query;
       QString sql = QString("create table tb1("
                             "pk int primary key,"
                             "tchar varchar,"
                             "tint int"
                             ");");
       query.clear();
       if (query.exec(sql)) {
           qDebug() << "create table success";
       } else {
           qDebug() << "create table fail";
       }
   
       // 增
       sql = QString("insert into %1 values(?,?,?)").arg("tb1");
       query.clear();
       query.prepare(sql);
       query.bindValue(0, 0);
       query.bindValue(1, "abc");
       query.bindValue(2, 123);
       if (query.exec()) { // 处理插入
           qDebug() << "insert success";
       } else {
           qDebug() << "insert fail";
       }
   
       query.bindValue(0, 1);
       query.bindValue(1, "def");
       query.bindValue(2, 456);
       if (query.exec()) { // 处理插入
           qDebug() << "insert success";
       } else {
           qDebug() << "insert fail";
       }
   
       // 删
       sql = QString("delete from %1 where pk = %2").arg("tb1").arg(0);
       query.clear();
       if (query.exec()) {
           qDebug() << "delete success";
       } else {
           qDebug() << "delete fail";
       }
   
       // 改
       sql = QString("update %1 set tchar=?, tint=? where pk=%2").arg("tb1").arg(1);
       query.clear();
       query.prepare(sql);
       query.bindValue(0, "xxx");
       query.bindValue(1, 789);
       query.exec();
   
       // 查
       sql = QString("select * from tb1");
       query.clear();
       if (!query.exec(sql)) {
           qDebug() << "select fail with:" << query.lastError();
       } else {
           qDebug() << "---------------------------------------";
           while (query.next()) {
               qDebug() << "pk:" << query.value(0).toInt();
               qDebug() << "tchar:" << query.value(1).toString();
               qDebug() << "tint:" << query.value(2).toInt() << "\n";
           }
           qDebug() << "---------------------------------------" << "\n";
       }
   
       return a.exec();
   }
   ```

   



## 参考

[1] [Qt 操作SQLite数据库](https://www.cnblogs.com/linuxAndMcu/p/11364071.html)

