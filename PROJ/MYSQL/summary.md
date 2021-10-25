# mysql知识点总结

## 常用命令
### 登陆:
|参数|描述|
|:--|:--|
|-D|打开制定数据库|
|-h|服务器名称|
|-p(小写)|密码|
|-P(大写)|端口号|
|—prompt|设置提示符|
|-u|用户名|
|-v|输出版本信息并退出|

### 退出：
- exit;
- quit;
- \q;

### 提示符:
- --prompt \D     完整的日期
- --prompt \d     当前数据库
- --prompt \h     服务器名称
- --prompt \u     当前用户

### 查看信息：
- SELECT  VERSION(); 显示当前服务器版本
- SELECT  NOW();     显示当前日期时间
- SELECT  USER();    显示当前用户
- SELECT  DATABASE(); 显示当前数据库

### 数据库操作：
- CREATE DATABASE test; 创建数据库test
- CREATE DATABASE IF NOT EXISTS t2 CHARACTER SET gbk; 如果不存在t2，则以gbk编码方式创建
- SHOW DATABASES; 显示所有数据库
- SHOW WARNINGS;  显示警告信息
- SHOW CREATE DATABASE test;  显示数据库test编码方式
- ALTER DATABASE t2 CHARACTER SET = utf8; 修改t2的编码为utf8
- DROP DATABASE t1; 删除数据库t1
例子：DROP DATABASE IF EXISTS t1; 如果t1存在，则删除之

总结：创建 CREATE; 显示 SHOW; 修改 ALTER; 删除 DROP;

### 数据类型：
- 整型:TINYINT SMALLINT MEDIUMINT INT BIGINT
- 浮点型:FLOAT DOUBLE
- 日期时间型:YEAR TIME DATE DATETIME TIMESTAMP
- 字符型:CHAR VARCHAR TINYTEXT TEXT MEDIUMTEXT LONGTEXT
- 其他:ENUM SET

### 数据表：
```sql
USE test 使用test数据库

mysql> CREATE TABLE  tb1( //创建数据表tb1
    -> username VARCHAR(20), //用户名：20位VARCHAR型
    -> age TINYINT UNSIGNED, //年龄：无符号短整型
    -> salary FLOAT(8, 2) UNSIGNED //薪水：8位浮点型，6位整数+2位小数
-> );

SHOW TABLES; 查看当前数据库中的数据表

SHOW TABLES FROM mysql; 查看mysql数据库中的数据表

SHOW COLUMNS FROM tb1; 查看数据表tb1的数据结构

INSERT tb1 VALUES('Tom', 25, 7863.25); 将一条信息插入数据库tb1

INSERT tb1(username, salary) VALUES('John', 4500.69); 以省略的方式将一条信息插入数据库tb1

SELECT * FROM tb1; 将数据库tb1中的信息显示出来

CREATE TABLE tb2(
    -> username VARCHAR(20) NOT NULL, //设置usernam禁止为空
    -> age TINYINT UNSIGNED NULL
-> );

CREATE TABLE tb3(
-> id SMALLINT UNSIGNED AUTO_INCREMENT PRIMARY KEY, //AUTO_INCREMENT：自动增长，
//默认步长为1，使用自动增长必须将变量设置为//PRIMARY KEY；PRIMARY KEY默认禁止为空；
-> username VARCHAR(30) NOT NULL
-> );

CREATE TABLE tb5(
    -> id SMALLINT UNSIGNED AUTO_INCREMENT PRIMARY KEY,
    -> username VARCHAR(20) NOT NULL UNIQUE KEY, //UNIQUE KEY：唯一约束
    -> age TINYINT UNSIGNED
-> );

# PRIMARY KEY与UNIQUE KEY的区别：一张表只有一个PRIMARY KEY，但是可以有多个UNIQUE KEY

CREATE TABLE tb6(
    -> id SMALLINT UNSIGNED AUTO_INCREMENT PRIMARY KEY,
    -> username VARCHAR(20) NOT NULL UNIQUE KEY,
    -> sex ENUM('1', '2', '3') DEFAULT '3' //创建联合体，并将sex置为默认类型3
-> );
```
总结：
- 使用: USE;
- 创建数据表: CREATE TABLE;
- 查看数据表: SHOW TABLES; 
- 查看数据表内部结构: SHOW COLUMNS FROM XXX;
- 将信息插入数据表: INSERT XXX VALUES(XXX, XXX,);
- 显示数据表信息: SELECT * FROM XXX;
- 设置禁止为空: NOT NULL;
- 自动增长: AUTO_INCREMKENT;

约束:
- 主键约束: PRIMARY_KEY;
- 唯一约束: UNIQUE KEY;
- 默认约束: DEFAULT;
- 非空约束: NOT NULL;

### 约束：
约束类型：
- NOT NULL      非空约束
- PRIMARY KEY   主键约束
- UNIQUE KEY   唯一约束
- DEFAULT   默认约束
- FOREIGN   外键约束

```sql
CREATE  TABLE  province( //父表

    -> id SMALLINT UNSIGNED PRIMARY KEY AUTO_INCREMENT,

    -> pname VARCHAR(20) NOT NULL

-> );

CREATE  TABLE  users( //子表

    -> id SMALLINT UNSIGNED PRIMARY KEY AUTO_INCREMENT,

    -> username VARCHAR(10) NOT NULL,

    -> pid SMALLINT UNSIGNED,

    -> FOREIGN KEY (pid) REFERENCES province (id) //创建外键链接

    -> );

SHOW INDEXES FROM province\G 显示province表的索引
```

外键约束的参照操作：
1. CASCADE：从父表删除或更新时自动删除或更新子表中匹配的行。
2. SET NULL：从父表删除或更新行，并设置子表中的外键列为NULL。使用该选项必须保证子表列没有指定NOT NULL。
3. RESTRICT：拒绝对父表的删除或更新操作。
4. NO ACTION：标准SQL关键字，在MySQL中与RESTRICT相同。
```sql
CREATE  TABLE  users1(

   -> id SMALLINT UNSIGNED PRIMARY KEY AUTO_INCREMENT,

    -> username VARCHAR(10) NOT NULL,

    -> pid SMALLINT UNSIGNED,

    -> FOREIGN KEY (pid) REFERENCES province (id) ON DELETE CASCADE  //province表中的数据删除时，

//同时删除users1对应的数据

-> );
```

表级约束与列级约束的区别：
- 对一个数据列建立的约束，称为列级约束；
- 对多个数据列建立的约束，称为表级约束；
- 列级约束既可以在列定义时声明，也可以在列定义之后声明；表级约束必须在列定义时声明；

修改数据表:
- 添加列：ALTER TABLE users1 ADD age TINYINT UNSIGNED NOT NULL DEFAULT 10;
- 删除列：ALTER TABLE users1 DROP truename;

- - - 