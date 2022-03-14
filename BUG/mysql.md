[TOC]

# MySQL问题



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

