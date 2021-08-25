[TOC]

# MySQL问题



### 修改密码时提示不合法

修改账号和密码时，报错“密码不合法”

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

2. 按照安全变量值要求来修改密码

