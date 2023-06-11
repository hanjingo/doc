# MySQL问题

<!-- vim-markdown-toc GFM -->

- [修改密码时提示不合法](#修改密码时提示不合法)
- [Windows下QT5连接MYSQL报错](#windows下qt5连接mysql报错)

<!-- vim-markdown-toc -->


### 修改密码时提示不合法

修改账号和密码时，报错“密码不合法”

```sh
ERROR 1819 (HY000): Your password does not satisfy the current policy requirements;
```

是因为MySQL8.0引入了密码安全度检测机制，解决方法如下：

1. 修改当前安全等级

   ```sh
   # 查看安全变量
   SHOW VARIABLES LIKE 'validate_password%';
   # 设置安全等级
   set global validate_password_policy = LOW;
   ```

2. 按照安全变量值要求来修改密码

   略...



### Windows下QT5连接MYSQL报错

**问题**

在windows环境下，使用qt连接mysql时报以下错误：

```sh
QSqlDatabase: QMYSQL driver not loaded
```

**原因**

安装qt时没有安装`Mysql Connector C`或者qt目录缺少`libmysql.dll`和`libmysql.lib`这两个文件。

**解决**

复制`Mysql Connector C安装目录/lib`目录下的`libmysql.dll`和`libmysql.lib`到`qt安装目录下/qt版本/编译平台目录`中。

