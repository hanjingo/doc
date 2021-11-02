# Mysql环境搭建



## 安装

### ubuntu

- 命令安装

  ```sh
  sudo apt-get update 
  sudo apt-get install mysql-server mysql-client
  # 确认下
  ps -ef | grep mysql*
  ```

- 源码安装

  ```sh
  TODO
  ```



## 配置

### 设置安装选项

```sh
sudo mysql_secure_installation
```

### 重置用户名和密码

```sh
# 切到mysql数据库
use mysql;
# 设置用户名密码
update mysql.user set authentication_string=password('Ya123456') where user='root' and Host='localhost';
# 开启mysql_native_password插件
update user set plugin="mysql_native_password";
flush privileges;
```

如果报错“密码不合法”

```sh
ERROR 1819 (HY000): Your password does not satisfy the current policy requirements;
```

是因为MySQL8.0引入了密码安全度检测机制，解决方法如下：

1. 查看当前安全变量值：

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
   
2. 修改安全密码等级

    ```sh
    set global validate_password_policy = LOW;
    ...
    ```



## 启动

```sh
service mysql start
```



  

