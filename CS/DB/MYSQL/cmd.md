# Mysql命令

[TOC]



## 常用命令

### 执行sql脚本

- 方法一

  ```sh
  mysql –ux –pxx –Dxxx< xxxx # x:用户名, xx:密码, xxx:数据库, xxxx:sql脚本文件路径
  ```

- 方法二

  ```sh
  # 登陆先
  mysql –ux –pxx # x:用户名, xx:密码
  
  # 用source命令
  source x # x:sql脚本文件路径
  ```



## 安全相关

### 修改密码

- 方法1：用SET PASSWORD命令

  ```sh
  # 登陆先
  mysql -u xx
  
  # 用SET PASSWORD命令
  SET PASSWORD FOR 'xx'@'localhost' = PASSWORD('xxx'); # xx:用户名, xxx:密码
  ```

- 方法2：用mysqladmin

  ```sh
  mysqladmin -u root password xx "xxx" # xx:旧密码，xxx:新密码
  ```

- 方法3：用UPDATE直接编辑user表

  ```sh
  # 登陆先
  mysql -u xx
  
  # 切换到mysql
  use mysql;
  
  # 修改user表
  UPDATE user SET Password = PASSWORD('xx') WHERE user = 'xxx'; # xx:新密码，xxx:用户名
  ```

- 方法四：在丢失root密码时，可以使用一些暴力的手段

  ```sh
  # 安全模式登录先
  mysqld_safe --skip-grant-tables&
  mysql -u root mysql
  
  # 修改user表
  UPDATE user SET Password = PASSWORD('xx') WHERE user = 'xxx'; # xx:新密码，xxx:用户名
  
  # 刷入修改命令
  F
  ```

### 查看当前安全等级

```sh
SHOW VARIABLES LIKE 'validate_password%';
```

- `validate_password_check_user_name`
- `validate_password_dictionary_file`
- `validate_password_length` 密码长度最小值
- `validate_password_mixed_case_count` 大小写的最小个数
- `validate_password_number_count` 数字的最小个数
- `validate_password_policy` 安全级别
- `validate_password_special_char_count` 特殊字符的最小个数

设置安全变量：

```sh
set global x = xx; # x:安全变量, xx:安全变量值
```



## 参考

- [MySQL修改root密码的各种方法整理](https://www.linuxidc.com/Linux/2008-02/11137.htm)

