# SQL语法手册

[TOC]



## 术语

- 数据库(database)
- 表(table)
- 列(column)
- 行(row)
- 主键(primary key)
- 结构化查询语言(Structured Query Language, SQL)
- 关键字(keyword)
- 子句(clause)
- 通配符(wildcard)
- 搜索模式(search pattern)
- 谓词(predicate)
- 字段(field)
- 拼接(concatenate)
- 别名(alias)
- 导出列(derived column)
- 聚集函数(aggregate function)
- 查询(query)
- 子查询(subquery)
- 可伸缩(scale)
- 笛卡尔积(cartesian product)
- 叉联结(cross join)
- 等值联结(equi join)
- 内联结(inner join)
- 自联结(self join)
- 自然链接(natural join)
- 外联结(outer join)
- 并(union)
- 复合查询(compound query)
- 事务(transaction)
- 回退(roll back)
- 提交(commit)
- 保留点(savepoint)
- 临时占位符(placeholder)
- 隐式提交(implicit commit)
- 游标(cursor)
- 约束(constraint)



## 数据类型

| 数据类型           | 说明                                               |
| ------------------ | -------------------------------------------------- |
| BIT                | 单个二进制位值，或者为0或者为1，主要用于开/关标志  |
| DECIMAL            | 定点或精度可变的浮点值                             |
| FLOAT              | 浮点值                                             |
| INT                | 4字节整数值，[-2147483648, 2147483647]             |
| REAL               | 4字节浮点值                                        |
| SMALLINT           | 2字节整数值，[-32768, 32768]                       |
| TINYINT            | 1字节整数值，[0~255]                               |
| CHAR               | 1～255个字符的定长字符串，它的长度必须在创建时规定 |
| NCHAR              | CHAR的特殊形式，用来支持多字节或Unicode字符        |
| NVARCHAR           | TEXT的特殊形式，用来支持多字节或Unicode字符        |
| TEXT               | 变长文本                                           |
| DATE               | 日期值                                             |
| DATETIME/TIMESTAMP | 日期时间值                                         |
| SMALLDATETIME      | 日期时间值，精确到分                               |
| TIME               | 时间值                                             |
| BINARY             | 定长二进制数据，[255B, 8000B]                      |
| LONG RAW           | 变长二进制数据，<=2GB                              |
| RAW                | 定长二进制数据，<=255B                             |
| VARBINARY          | 变长二进制数据，[255B, 8000B]                      |



## 检索

SELECT子句及其顺序：

| 子句       | 说明               | 是否必须使用           |
| ---------- | ------------------ | ---------------------- |
| `SELECT`   | 要返回的列或表达式 | 是                     |
| `FROM`     | 从中检索数据的表   | 仅在从表选择数据时使用 |
| `WHERE`    | 行级过滤           | 否                     |
| `GROUP BY` | 分组说明           | 仅在按组计算聚集时使用 |
| `HAVING`   | 组级过滤           | 否                     |
| `ORDER BY` | 输出排序顺序       | 否                     |

- 检索单个列

  ```sql
  SELECT prod_name FROM Products;
  ```

- 检索多个列

  ```sql
  SELECT prod_id, prod_name, prod_price FROM Products;
  ```

- 检索所有列

  ```sql
  SELECT * FROM Products;
  ```

  **注意：检索不需要的列通常会降低检索和应用程序的性能；**

- 检索具有唯一性的值

  ```sql
  SELECT DISTINCT vend_id FROM Products;
  ```

- 限制检索结果

  ```sql
  -- Mysql, MariaDB, PostgreSQL, SQLite适用
  SELECT prod_name FROM Products LIMIT 5;
  SELECT prod_name FROM Products LIMIT 5 OFFSET 2; -- 从第2行开始
  -- SQL Server和Access适用
  SELECT TOP 5 prod_name FROM Products;
  -- DB2适用
  SELECT prod_name FROM Products FETCH FIRST 5 ROWS ONLY;
  -- Oracle适用
  SELECT prod_name FROM Products WHERE ROWNUM <= 5;
  ```

### 排序

- 对检索结果排序

  ```sql
  SELECT prod_name FROM Products ORDER BY prod_name;
  ```

- 对检索结果按多个列排序

  ```sql
  SELECT prod_id, prod_price, prod_name FROM Products ORDER BY prod_price, prod_name;
  ```

- 对检索结果按列位置排序

  ```sql
  SELECT prod_id, prod_price, prod_name FROM Products ORDER BY 2, 3; -- 先按prod_price排序，在按prod_name排序
  ```

- 指定检索结果的排序方向

  ```sql
  SELECT prod_id, prod_price, prod_name FROM Products ORDER BY prod_price DESC; -- 降序排序
  SELECT prod_id, prod_price, prod_name FROM Products ORDER BY prod_price DESC, prod_name; -- 对其它列降序排序，对prod_name默认（升序）排序
  ```

### 过滤

WHERE子句操作符：

| 操作符 | 说明     | 操作符    | 说明               |
| ------ | -------- | --------- | ------------------ |
| `=`    | 等于     | `>`       | 大于               |
| `<>`   | 不等于   | `>=`      | 大于等于           |
| `!=`   | 不等于   | `!>`      | 不大于             |
| `<`    | 小于     | `BETWEEN` | 在指定的两个值之间 |
| `<=`   | 小于等于 | `IS NULL` | 为NULL值           |
| `!<`   | 不小于   |           |                    |

- 指定搜索条件进行过滤

  ```sql
  SELECT prod_name, prod_price FROM Products WHERE prod_price = 3.49;
  ```

  **注意：同时使用ORDER BY和WHERE时，应该让ORDER BY位于WHERE之后，否则会产生错误；**

- 检查单个条件

  ```sql
  SELECT prod_name, prod_price FROM Products WHERE prod_price < 10;
  ```

- 不匹配检查

  ```sql
  SELECT vend_id, prod_name FROM Products WHERE vend_id <> 'DLL01';
  SELECT vend_id, prod_name FROM Products WHERE vend_id != 'DLL01';
  ```

  **注意：!=和<>通常可以互换**

- 范围值检查

  ```sql
  SELECT prod_name, prod_price FROM Products WHERE prod_price BETWEEN 5 AND 10;
  ```

- 空值检查

  ```sql
  SELECT prod_name FROM Products WHERE prod_price IS NULL;
  ```

- 检查多个条件

  ```sql
  SELECT prod_id, prod_price, prod_name FROM Products WHERE vend_id = 'DLL01' AND prod_price <= 4;
  ```

- 匹配任意条件

  ```sql
  SELECT prod_name, prod_price FROM Products WHERE vend_id = 'DLL01' OR vend_id = 'BRS01';
  ```

- 指定顺序

  ```sql
  SELECT prod_name, prod_price FROM Products WHERE (vend_id = 'DLL01' OR vend_id = 'BRS01') AND prod_price >= 10; -- 圆括号的优先级大于OR和AND
  ```

- 指定条件范围

  ```sql
  SELECT prod_name, prod_price FROM Products WHERE vend_id IN ('DLL01', 'BRS01') ORDER BY prod_name;
  SELECT prod_name, prod_price FROM Products WHERE vend_id = 'DLL01' OR vend_id = 'BRS01' ORDER BY prod_name; -- 等同于上面
  ```

  IN操作符的优点：

  1. 在有很多合法选项时，IN操作符的语法更清楚，更直观；
  2. 在与其它AND和OR操作符组合使用IN时，求值顺序更容易管理；
  3. IN操作符一般比一组OR操作符执行的更快；
  4. IN的最大优点是可以包含其他SELECT语句，更构更动态地建立WHERE子句；

- 否定条件

  ```sql
  SELECT prod_name FROM Products WHERE NOT vend_id = 'DLL01' ORDER BY prod_name;
  SELECT prod_name FROm Products WHERE vend_id <> 'DLL01' ORDER BY prod_name; -- 等同于上面
  ```

### 通配符

通配符使用技巧：

1. 不要过度使用通配符，如果其他操作符能达到相同的目的，应该使用其他操作符；
2. 在确实需要使用通配符时，也尽量不要把它们用在搜索模式的开始处（这样搜索起来是最慢的）；
3. 仔细注意通配符的位置，如果放错地方，可能不会返回想要的数据；

- `%`

  ```sql
  SELECT prod_id, prod_name FROM Products WHERE prod_name LIKE 'Fish%'; -- 匹配以Fish开头的词
  SELECT prod_id, prod_name FROM Products WHERE prod_name LIKE '%bean bag%'; -- 匹配包含bean bag的值
  SELECT prod_name FROM Products WHERE prod_name LIKE 'F%y'; -- 匹配以F开头y结尾的词
  ```

  **注意：`'%'`不会匹配产品名称为NULL的行；**

- `_`

  ```sql
  SELECT prod_id, prod_name FROM Products WHERE prod_name LIKE '__ inch teddy bear'; -- 匹配一个2位数的值
  ```

  **注意1：DB2不支持`_`；**

  **注意2：Microsoft Access使用`?`代替`_`；**

- `[]`

  ```sql
  SELECT cust_contact FROM Customers WHERE cust_contact LIKE '[JM]%' ORDER BY cust_contact; -- 匹配包含任意'J'和'M'的值
  
  SELECT cust_contact FROM Customers WHERE cust_contact LIKE '[^JM]%' ORDER BY cust_contact; -- 匹配不包含任意'J'和'M'的值
  SELECT cust_contact FROM NOT cust_contact LIKE '[JM]%' ORDER BY cust_contact; -- 等同于'[^JM]%'
  ```



## 计算字段

### 拼接字段

```sql
-- MySQL, MariaDB适用
SELECT Concat(vend_name, '(', vend_country, ')') FROM Vendors ORDER BY vend_name; -- 拼接(+vend_name列+vend_country列+)
SELECT RTRIM(vend_name) + '(' + RTRIM(vend_country) + ')' FROM Vendors ORDER BY vend_name; -- 拼接(+vend_name列+vend_country列+)并去掉右侧空格
SELECT RTRIM(vend_name) + '(' + RTRIM(vend_country) + ')' AS vend_title FROM Vendors ORDER BY vend_name; -- 拼接(+vend_name列+vend_country列+)，使用别名并去掉右侧空格

-- Access, SQL Server适用
SELECT vend_name + '(' + vend_country + ')' FROM Vendors ORDER BY vend_name; -- 同上
SELECT RTRIM(vend_name) + '(' + RTRIM(vend_country) + ')' FROM Vendors ORDER BY vend_name; -- 同上
SELECT RTRIM(vend_name) + '(' + RTRIM(vend_country) + ')' AS vend_title FROM Vendors ORDER BY vend_name; -- 同上

-- DB2, Oracle, PostgreSQL, SQLite, Open Office Base适用
SELECT vend_name || '(' || vend_country || ')' FROM Vendors ORDER BY vend_name; -- 同上
SELECT RTRIM(vend_name) || '(' || RTRIM(vend_country) || ')' FROM Vendors ORDER BY vend_name; -- 同上
SELECT RTRIM(vend_name) || '(' || RTRIM(vend_country) || ')' AS vend_title FROM Vendors ORDER BY vend_name; -- 同上
```

### 算术计算

SQL算数操作符：

| 操作符 | 说明 |
| ------ | ---- |
| `+`    | 加   |
| `-`    | 减   |
| `*`    | 乘   |
| `/`    | 除   |

```sql
SELECT prod_id, quantity, item_price FROM OrderItems WHERE order_num = 20008; -- 检索订单号20008的所有物品
SELECT prod_id, quantity, item_price, quantity*item_price AS expanded_price FROM OrderItems WHERE order_num = 20008; -- 检索prod_id, quantity, item_price, expanded_price(值=quantity*item_price)
```



## 函数

### 文本处理

常用的文本处理函数：

| 函数        | 说明                  |
| ----------- | --------------------- |
| `LEFT()`    | 返回字符串左边的字符  |
| `LENGTH()`  | 返回字符串的长度      |
| `LOWER()`   | 将字符串转换为小写    |
| `LTRIM()`   | 去掉字符串左边的空格  |
| `RIGHT()`   | 返回字符串右边的字符  |
| `RTRIM()`   | 去掉字符串右边的空格  |
| `SOUNDEX()` | 返回字符串的SOUNDEX值 |
| `UPPER()`   | 将字符串转换为大写    |

- 搜索SOUNDEX值

  ```sql
  SELECT cust_name, cust_contact FROM Customers WHERE SOUNDEX(cust_contact) = SOUNDEX('Michael Green'); -- 搜索发音与Michael Green近似的值如：MIchelle Green
  ```

### 日期和时间处理函数

各版本的DBMS获取系统日期的函数：

| DBMS       | 函数/变量        |
| ---------- | ---------------- |
| Access     | `NOW()`          |
| DB2        | `CURRENT_DATE`   |
| MySQL      | `CURRENT_DATE()` |
| Oracle     | `SYSDATE`        |
| PostgreSQL | `CURRENT_DATE`   |
| SQL Server | `GETDATE()`      |
| SQLite     | `date('now')`    |

```sql
-- MySQL, MariaDB
SELECT order_num FROM Orders WHERE YEAR(order_date) = 2012;

-- SQL Server
SELECT order_num FROM Orders WHERE DATEPART(yy, order_date) = 2012; -- 返回2012年的数据

-- Access
SELECT order_num FROM Orders WHERE DATEPART('yyyy', order_date) = 2012; -- 同上

-- Oracle
SELECT order_num FROM Orders WHERE to_number(to_char(order_date, 'YYYY')) = 2012; -- 同上
SELECT order_num FROM Orders WHERE order_date BETWEEN to_date('01-01-2012') AND to_date('12-31-2012'); -- 同上

-- SQLite
SELECT order_num FROM Orders WHERE strftime('%Y', order_date) = '2012'; -- 同上
```

### 数值处理函数

| 函数     | 说明               |
| -------- | ------------------ |
| `ABS()`  | 返回一个数的绝对值 |
| `COS()`  | 返回一个角度的余旋 |
| `EXP()`  | 返回一个数的指数值 |
| `PI()`   | 返回圆周率         |
| `SIN()`  | 返回一个角度的正旋 |
| `SQRT()` | 返回一个数的平方根 |
| `TAN()`  | 返回一个角度的正切 |



## 汇总

SQL聚集函数：

| 函数      | 说明             |
| --------- | ---------------- |
| `AVG()`   | 返回某列的平均值 |
| `COUNT()` | 返回某列的行数   |
| `MAX()`   | 返回某列的最大值 |
| `MIN()`   | 返回某列的最小值 |
| `SUM()`   | 返回某列值之和   |

- 求平均值

  ```sql
  SELECT AVG(prod_price) AS avg_price FROM Products; -- 计算所有产品的平均价格
  SELECT AVG(prod_price) AS avg_price FROM Products WHERE vend_id = 'DLL01'; -- 计算产品'DLL01'的平均价格
  ```

- 统计数目

  ```sql
  SELECT COUNT(*) AS num_cust FROM Customers; -- 统计顾客总数
  SELECT COUNT(cust_email) AS num_cust FROM Customers; -- 统计电子邮件地址的客户计数
  ```

- 返回最大值

  ```sql
  SELECT MAX(prod_price) AS max_price FROM Products; -- 返回最贵的物品价格
  ```

- 返回最小值

  ```sql
  SELECT MIN(prod_price) AS min_price FROM Products; -- 返回最便宜的物品价格
  ```

- 求和

  ```sql
  SELECT SUM(quantity) AS items_ordered FROM OrderItems WHERE order_num = 20005; -- 计算订单20005中物品数量总和
  SELECT SUM(item_price*quantity) AS total_price FROM OrderItems WHERE order_num = 20005; -- 计算订单总金额
  ```

- 聚焦

  ```sql
  SELECT AVG(DISTINCT prod_price) AS avg_price FROM Products WHERE vend_id = 'DLL01'; -- 计算供应商DLL01提供的产品的平均价格（相同的值算一个）
  ```

  **注意：DISTINCT不能用于`COUNT(*)`**

- 组合多个函数

  ```sql
  SELECT COUNT(*) AS num_items, MIN(prod_price) AS price_min, MAX(prod_price) AS price_max, AVG(prod_price) AS price_avg FROM Products; -- 返回物品数目，最低值，最高值和平均值
  ```



## 分组

使用`GROUP BY`的一些规定：

1. `GROUP BY`子句可以包含任意数目的列，因而可以对分组进行嵌套，更细致的进行数据分组；
2. 如果在`GROUP BY`子句中嵌套了分组，数据将在最后指定的分组上进行汇总（即，建立分组时，不能从个别的列取回数据）；
3. `GROUP BY`子句中列出的每一列都必须是检索列或有效的表达式（但不能是聚集函数）；如果在`SELECT`中使用表达式，则必须在`GROUP BY`子句中指定相同的表达式，不能使用别名；
4. 大多数SQL实现不允许`GROUP BY`列带有长度可变的数据类型（如文本/备注型字段）；
5. 除聚集计算语句外，`SELECT`语句中的每一列都必须在`GROUP BY`子句中给出；
6. 如果分组列中包含具有NULL值的行，则NULL将作为一个分组返回；如果列中有多行NULL值，它们将分为一组；
7. `GROUP BY`子句必须出现在`WHERE`子句之后，`ORDER BY`子句之前；

`ORDER BY`与`GROUP BY`的区别：

| ORDER BY                                     | GROUP BY                                                   |
| -------------------------------------------- | ---------------------------------------------------------- |
| 对产生的输出排序                             | 对行分组，但输出可能不是分组的顺序                         |
| 任意列都可以使用（甚至非选择的列也可以使用） | 只可能使用选择列表或表达式列，而且必须使用每个选择列表达式 |
| 不一定需要                                   | 如果与聚集函数一起使用列（或表达式），则必须使用           |

- GROUP BY分组

  ```sql
  SELECT vend_id, COUNT(*) AS num_prods FROM Products GROUP BY vend_id; -- 计算供应商的产品数量并分组
  ```

- HAVING过滤分组

  ```sql
  SELECT cust_id, COUNT(*) AS orders FROM Orders GROUP BY cust_id HAVING COUNT(*) >= 2; -- 列出顾客购买的产品数量>=2的记录并分组
  
  SELECT vend_id, COUNT(*) AS num_prods FROM Products WHERE prod_price >= 4 GROUP BY vend_id HAVING COUNT(*) >= 2; -- 列出具有2个以上产品且价格>=4的供应商
  
  SELECT vend_id, COUNT(*) AS num_prods FROM Products GROUP BY vend_id HAVING COUNT(*) >= 2; -- 列出产品数量>=2的供应商
  ```

- 分组排序

  ```sql
  SELECT order_num, COUNT(*) AS items FROM OrderItems GROUP BY order_num HAVING COUNT(*) >= 3 ORDER BY items, order_num; -- 按订单号分组数据并根据产品数量和订单号排序
  ```
  
  

## 子查询

- 子查询

  ```sql
  SELECT cust_id FROM Orders WHERE order_num IN (SELECT order_num FROM OrderItems WHERE prod_id = 'RGAN01'); -- 根据产品id查询顾客id
  
  SELECT cust_name, cust_contact FROM Customers WHERE cust_id IN (SELECT cust_id FROM Orders WHERE order_num IN (SELECT order_num FROM OrderItems WHERE prod_id = 'RGAN01')); -- 根据产品id查询顾客名，合约
  ```

  **注意1：作为子查询的SELECT值鞥查询单个列；**

  **注意2：子查询的性能不够高效，谨慎使用；**

- 创建计算字段

  ```sql
  SELECT cust_name, cust_state, (SELECT COUNT(*) FROM Orders WHERE Orders.cust_id = Customers.cust_id) AS orders FROM Customers ORDER BY cust_name; -- 根据顾客ID列出顾客名，顾客状态和订单数量，并根据顾客名排序
  ```

  **注意：这不是最有效率的检索方法；**

  

## 联结表

联结及其使用要点：

1. 注意所使用的联结类型，一般我们使用内联结，但使用外联结也有效；
2. 关于确切的联结语法，应该查看具体的文档看看是否支持；
3. 保证使用正确的联结条件，否则会返回不正确的数据；
4. 应该总是提供联结条件，否则会得出笛卡尔积；
5. 在一个联结中可以包含多个表，甚至可以对每个联结采用不同的联结类型；

- 联结查询

  ```sql
  SELECT vend_name, prod_name, prod_price FROM Vendors, Products WHERE Vendors.vend_id = Products.vend_id;
  ```

- 内联结查询

  ```sql
  SELECT vend_name, prod_name, prod_price FROM Vendors INNER JOIN Products ON Vendors.vend_id = Products.vend_id; -- 根据供应商id使用内联结查找供应商名，产品名，产品价格
  ```

- 多表联结查询

  ```sql
  SELECT prod_name, vend_name, prod_price, quantity FROM OrderItems, Products, Vendors WHERE Products.vend_id = Vendors.vend_id AND OrderItems.prod_id = Products.prod_id AND order_num = 20007; -- 根据订单号多表联查产品名，供应商名，产品价格和产品数量
  ```

  **注意1：联结的表越多，性能下降越厉害；**

  **注意2：SQL不限制联结表的数目，但是每种数据库的实现有限制；**

- 使用表别名

  ```sql
  SELECT RTRIM(vend_name) + '(' + RTRIM(vend_country) + ')' AS vend_title FROM Vendors ORDER BY vend_name; -- 查询供应商名(供应商国籍)
  
  SELECT cust_name, cust_contact FROM Customers AS C, Orders AS O, OrderItems AS OI WHERE C.cust_id = O.cust_id AND OI.order_num = O.order_num AND prod_id = 'RGAN01'; -- 查询顾客名，顾客合约
  
  SELECT c1.cust_id, c1.cust_name, c1.cust_contact FROM Customers AS c1, Customers AS c2 WHERE c1.cust_name = c2.cust_name AND c2.cust_contact = 'Jim Jones'; -- 查询顾客id，顾客名，顾客合约
  ```

  **注意：一般来说自联结比子查询快；**

- 自然联结

  ```sql
  SELECT C.*, O.order_num, O.order_date, OI.prod_id, OI.quantity, OI.item_price FROM Customers AS C, Orders AS O, OrderItems AS OI WHERE C.cust_id = O.cust_id AND OI.order_num = O.order_num AND prod_id = 'RGAN01';
  ```

- 外联结

  ```sql
  SELECT Customers.cust_id, Orders.order_num FROM Customers LEFT OUTER JOIN Orders ON Customers.cust_id = Orders.cust_id; -- （左外联结）查询用户id，订单号
  
  -- SQLite不支持
  SELECT Customers.cust_id, Orders.order_num FROM Customers RIGHT OUTER JOIN Orders ON Orders.cust_id = Customers.cust_id; -- （右外联结）查询用户id，订单号
  
  -- Access, MariaDB, MySQL, Open Office Base, SQLite不支持
  SELECT Customers.cust_id, Orders.order_num FROM Orders FULL OUTER JOIN Customers ON Orders.cust_id = Customers.cust_id; -- （全外联结）查询用户id，订单号
  ```

- 带聚集函数的联结

  ```sql
  SELECT Customers.cust_id, COUNT(Orders.order_num) AS num_ord FROM Customers INNER JOIN Orders ON Customers.cust_id = Orders.cust_id GROUP BY Customers.cust_id; -- （内联结）查询顾客id和订单数量
  
  SELECT Customers.cust_id, COUNT(Orders.order_num) AS num_ord FROM Customers LEFT JOIN Orders ON Customers.cust_id = Orders.cust_id GROUP BY Customers.cust_id; -- （左联结）查询顾客id和订单数量
  ```



## 组合查询

`UNION`规则：

1. `UNION`必须由2条或2条以上的SELECT语句组成，语句之间用关键字`UNION`分割；
2. `UNION`中的每个查询必须包含相同的列，表达式或聚集函数；
3. 列数据类型必须兼容：类型不必完全相同，但必须是DBMS可以隐含转换的类型；

- `UNION`组合查询

  ```sql
  SELECT cust_name, cust_contact, cust_email FROM Customers WHERE cust_state IN ('IL', 'IN', 'MI') UNION SELECT cust_name, cust_contact, cust_email FROM Customers WHERE cust_name = 'Fun4All'; -- 组合查询顾客名，合约，邮件
  
  SELECT cust_name, cust_contact, cust_email FROM Customers WHERE cust_state IN ('IL', 'IN', 'MI') OR cust_name = 'Fun4All'; -- 范围查询顾客名，合约，邮件
  ```

- 包含或取消重复的行

  ```sql
  SELECT cust_name, cust_contact, cust_email FROM Customers WHERE cust_state IN ('IL', 'IN', 'MI') UNION ALL SELECT cust_name, cust_contact, cust_email FROM Customers WHERE cust_name = 'Fun4All'; -- 查询顾客名，合约，邮件（允许包含重复行）
  ```

- 对组合查询结果排序

  ```sql
  SELECT cust_name, cust_contact, cust_email FROM Customers WHERE cust_state IN ('IL', 'IN', 'MI') UNION SELECT cust_name, cust_contact, cust_email FROM Customers WHERE cust_name = 'Fun4All' ORDER BY cust_name, cust_contact; -- 查询顾客名，合约，邮件并根据顾客名，合约排序
  ```



## 插入

- 插入完整行

  ```sql
  INSERT INTO Customers(cust_id, 
                        cust_name,
                        cust_address,
                        cust_city,
                        cust_state,
                        cust_zip,
                        cust_country,
                        cust_contact,
                        cust_email) 
                 VALUES('10000006', 
                        'Toy Land', 
                        '123', 
                        'New York',
                        'NY', 
                        '1',
                        'USA',
                        NULL, 
                        NULL); -- 插入一条顾客数据
  ```

- 插入部分行

  ```sql
  INSERT INTO Customers(cust_id,
                        cust_name,
                        cust_address,
                        cust_city,
                        cust_state,
                        cust_zip,
                        cust_country)
                 VALUES('10000006', 
                        'Toy Land', 
                        '123', 
                        'New York',
                        'NY', 
                        '1',
                        'USA');
  ```

- 插入检索出的数据

  ```sql
  INSERT INTO Customers(cust_id,
                        cust_contact,
                        cust_email,
                        cust_name,
                        cust_address,
                        cust_city,
                        cust_state,
                        cust_zip,
                        cust_country)
  SELECT cust_id,
         cust_contact,
         cust_email,
         cust_name,
         cust_address,
         cust_city,
         cust_state,
         cust_zip,
         cust_country
  FROM CustNew; -- 从CustNew读出数据并插入到Customers
  ```

- 复制表

  ```sql
  SELECT * INTO CustCopy FROM Customers; -- 将Customers复制到CustCopy
  CREATE TABLE CustCopy AS SELECT * FROM Customers; -- 创建CustCopy并将Customers的内容复制过来
  ```



## 更新和删除

使用`UPDATE`或`DELETE`时所遵守的原则：

1. 除非确实打算更新和删除每一行，否则绝对不要使用不带`WHERE`子句的`UPDATE`或`DELETE`语句；
2. 保证每个表都有主键，尽可能像`WHERE`子句那样使用它（指定各主键，多个值或值的范围）；
3. 在`UPDATE`或`DELETE`语句使用`WHERE`子句前，应该先用`SELECT`进行测试，保证它过滤的是正确的记录，以防编写的`WHERE`子句不正确；
4. 使用强制实施引用完整性的数据库，这样DBMS将不允许删除其数据与其他表相关联的行；
5. 有的DBMS允许数据库管理员施加约束，防止执行不带`WHERE`子句的`UPDATE`或`DELETE`语句，如果所采用的DBMS支持这个特性，应该使用它；

- 更新数据

  ```sql
  UPDATE Customers SET cust_email = 'abc@qq.com' WHERE cust_id = '100'; -- 更新邮箱
  
  UPDATE Customers SET cust_contact = 'abc', cust_email = 'abc@qq.com' WHERE cust_id = '100'; -- 更新多个列
  
  UPDATE Customers SET cust_email = NULL WHERE cust_id = '100'; -- 置空cust_email列中的值
  ```

- 删除数据

  ```sql
  DELETE FROM Customers WHERE cust_id = '100'; -- 删除顾客id为100的一条数据
  ```



## 表操作

更新表注意事项：

1. 理想情况下，不要在表中包含数据时对其进行更新；应该在表的设计过程中充分考虑未来可能的需求，避免今后对表的结构做大改动；
2. 所有的DBMS都允许给现有的表增加列，不过对所增加列的数据类型（以及NULL和DEFAULT的使用）有所限制；
3. 许多DBMS不允许删除或更改表中的列；
4. 多数DBMS允许重新命名表中的列；
5. 许多DBMS限制对已经填有数据的列进行更改，对未填有数据的列几乎没有限制；

- 创建表

  ```sql
  CREATE TABLE Products
  (
  	prod_id    CHAR(10)      NOT NULL,             -- 非空
    vend_id    CHAR(10)      NOT NULL DEFAULT "a", -- 非空
    prod_name  CHAR(254)     NULL,                 -- 可空
    prod_price DECIMAL(8, 2) ,                     -- 可空
    prod_desc  VARCHAR(1000)                       -- 可空
  );
  ```

  **注意：主键用于唯一标识表中每一行的列，不允许NULL值的列作为主键；**

- 更新表

  ```sql
  ALTER TABLE Vendors ADD vend_phone CHAR(20); -- 添加供应商列
  
  ALTER TABLE Vendors DROP COLUMN vend_phone; -- 删除供应商列
  ```
  
- 删除表
  
  ```sql
  DROP TABLE CustCopy; -- 删除表CustCOpy
  ```
  



## 视图

视图的规则和限制：

1. 与表一样，视图必须唯一命名；
2. 对于可以创建的视图数目没有限制；
3. 创建视图，必须具有足够的访问权限，这些权限通常由数据库管理人员授予；
4. 视图可以嵌套，即可以利用从其它视图中检索数据的查询来构造视图（嵌套视图可能会严重降低查询的性能）；
5. 许多DBMS禁止在视图查询中使用`ORDER BY`子句；
6. 有些DBMS要求对返回的所有列进行命名，如果列是计算字段，则需要使用别名；
7. 视图不能索引，也不能有关联的触发器或默认值；
8. 有些DBMS把视图作为只读的查询，这表示可以从视图检索数据，但不能将数据写回底层表；
9. 有些DBMS允许创建这样的视图，它不能进行导致行不再属于视图的插入或更新；

- 创建视图

  ```sql
  CREATE VIEW ProductCustomers AS 
  	SELECT cust_name, cust_contact, prod_id 
  	FROM Customers, Orders, OrderItems 
  	WHERE Customers.cust_id = Orders.cust_id AND OrderItems.order_num = Orders.order_num; -- 创建一个联结3个表的视图
  ```

- 使用视图

  ```sql
  SELECT cust_name, cust_contact FROM ProductCustomers WHERE prod_id = 'RGAN01'; -- 检索购买了产品RGAN01的顾客
  ```

- 使用视图格式化检索数据

  ```sql
  SELECT RTRIM(vend_name) + '(' + RTRIM(vend_country) + ')' AS vend_title FROM Vendors ORDER BY vend_name; -- （使用+）格式化检索出的供应商和国籍数据
  
  SELECT RTRIM(vend_name) || '(' || RTRIM(vend_country) || ')' AS vend_title FROM Vendors ORDER BY vend_name; -- （使用||）格式化检索出的供应商和国籍数据
  
  CREATE VIEW VendorLocations AS SELECT RTRIM(vend_name) + '(' + RTRIM(vend_country) + ')' AS vend_title FROM Vendors;
  SELECT * FROM VendorLocations;
  
  CREATE VIEW VendorLocations AS SELECT RTRIM(vend_name) || '(' || RTRIM(vend_country) || ')' AS vend_title FROM Vendors; 
  SELECT * FROM VendorLocations;
  ```

- 使用视图过滤数据

  ```sql
  CREATE VIEW CustomerEMailList AS SELECT cust_id, cust_name, cust_email FROM Customers WHERE cust_email IS NOT NULL;
  SELECT * FROM CustomerEMailList; -- 检索顾客id，顾客名，顾客邮箱，并过滤没有邮件的顾客
  ```

- 使用视图简化计算字段

  ```sql
  CREATE VIEW OrderItemsExpanded AS SELECT prod_num, prod_id, quantity, item_price, quantity*item_price AS expanded_price FROM OrderItems;
  SELECT * FROM OrderItemsExpanded WHERE order_num = 20008;
  ```



## 存储过程

| 存储过程参数类型 | 用途                                 |
| ---------------- | ------------------------------------ |
| OUT              | 从存储过程返回值                     |
| IN               | 传递值给存储过程                     |
| INOUT            | 既传递值给存储过程也从存储过程传回值 |

- 创建存储过程

  ```sql
  CREATE PROCEDURE MailingListCount (
  	ListCount OUT INTEGER -- 用于从存储过程返回结果的参数ListCount
  )
  BEGIN
  	SELECT COUNT(*) INTO v_rows 
  	FROM Customers 
  	WHERE NOT cust_email IS NULL;
  	ListCount := v_rows;
  END;
  
  -- Oracle适用
  var ReturnValue NUMBER EXEC MailingListCount(:ReturnValue);
  SELECT ReturnValue;
  
  -- SQL Server适用
  CREATE PROCEDURE MailingListCount AS DECLARE @cnt INTEGER SELECT @cnt = COUNT(*) FROM Customers WHERE NOT cust_email IS NULL;
  RETURN @cnt;
  
  -- SQL Server适用
  DECLARE @ReturnValue INT
  EXECUTE @ReturnValue=MailingListCount;
  SELECT @ReturnValue;
  ```



## 事务

- 事务处理块

  ```sql
  -- SQL Server适用
  BEGIN TRANSACTION
  ...
  COMMIT TRANSACTION
  
  -- MariaDB, MySQL适用
  START TRANSACTION
  ...
  
  -- Oracle适用
  SET TRANSACTION
  ...
  
  -- PostgreSQL适用
  BEGIN
  ...
  ```

- 使用`ROLLBACK`撤销SQL语句

  ```sql
  DELETE FROM Orders;
  ROLLBACK; -- 撤销DELETE语句
  ```

- 使用`COMMIT`显式提交

  ```sql
  -- SQL Server适用
  BEGIN TRANSACTION 
  DELETE OrderItems WHERE order_num = 12345 
  DELETE Orders WHERE order_num = 12345 
  COMMIT TRANSACTION -- 显式提交
  
  -- Oracle适用
  SET TRANSACTION 
  DELETE OrderItems WHERE order_num = 12345; 
  DELETE Orders WHERE order_num = 12345; 
  COMMIT; -- 显式提交
  ```

- 使用保留点（占位符）

  ```sql
  -- MariaDB, MySQL, Oracle适用
  SAVEPOINT delete1;
  ROLLBACK TO delete1;
  
  -- SQL Server适用
  SAVE TRANSACTION delete1;
  ROLLBACK TRANSACTION delete1;
  ```

  ```sql
  -- SQL Server完整示例
  BEGIN TRANSACTION 
  INSERT INTO Customers(cust_id, cust_name) VALUES('100', 'abc');
  SAVE TRANSACTION StartOrder;
  INSERT INTO Orders(order_num, order_date, cust_id) VALUES(20100, '2001/12/1', '100');
  IF @@ERROR <> 0 ROLLBACK TRANSACTION StartOrder;
    INSERT INTO OrderItems(order_num, order_item, prod_id, quantity, item_price) VALUES(20100, 1, 'abc', 100, 5.49);
  IF @@ERROR <> 0 ROLLBACK TRANSACTION StartOrder;
    INSERT INTO OrderItems(order_num, order_item, prod_id, quantity, item_price) VALUES(20100, 2, 'BR03', 100, 10.99);
  IF @@ERROR <> 0 ROLLBACK TRANSACTION StartOrder;
  COMMIT TRANSACTION
  ```



## 游标

- 创建游标

  ```sql
  -- DB2, MariaDB, MySQL, SQL Server适用
  DECLARE CustCursor CURSOR 
  FOR 
  SELECT * FROM Customers WHERE cust_email IS NULL
  
  -- Oracle和PostgreSQL适用
  DECLARE CURSOR CustCursor 
  IS 
  SELECT * FROM Customers WHERE cust_email IS NULL
  ```

- 使用游标

  Oracle语法：

  ```sql
  -- 检索数据
  DECLARE TYPE CustCursor IS REF CURSOR
  	RETURN Customers%ROWTYPE;
  DECLARE CustRecord Customers%ROWTYPE
  BEGIN
  	OPEN CustCursor;
  	FETCH CustCursor INTO CustRecord; -- 检索当前行并放入CustRecord
  	CLOSE CustCursor;
  END;
  
  -- 检索数据并循环
  DECLARE TYPE CustCursor IS REF CURSOR
  	RETURN Customers%ROWTYPE;
  DECLARE CustRecord Customers%ROWTYPE
  BEGIN 
  	OPEN CustCursor;
  	LOOP 
  	FETCH CustCursor INTO CustRecord;
  	EXIT WHEN CustCursor%NOTFOUND;
  	...
  	END LOOP;
  	CLOSE CustCursor;
  END;
  ```

  Microsoft SQL Server语法：

  ```sql
  DECLARE @cust_id CHAR(10),
          @cust_name CHAR(50),
          @cust_address CHAR(50),
          @cust_city CHAR(50),
          @cust_state CHAR(5),
          @cust_zip CHAR(10),
          @cust_country CHAR(50),
          @cust_contact CHAR(50),
          @cust_email CHAR(255)
  OPEN CustCursor 
  FETCH NEXT FROM CustCursor 
  	INTO @cust_id, @cust_name, @cust_address,
  	     @cust_city, @cust_state, @cust_zip,
  	     @cust_country, @cust_contact, @cust_email 
  WHILE @@FETCH_STATUS = 0
  BEGIN
  
  FETCH NEXT FROM CustCursor 
  	INTO @cust_id, @cust_name, @cust_address,
  	     @cust_city, @cust_state, @cust_zip,
  	     @cust_country, @cust_contact, @cust_email 
  END
  CLOSE CustCursor
  ```

- 关闭游标

  ```sql
  -- DB2, Oracle, PostgreSQL适用
  CLOSE CustCursor
  
  -- Microsoft SQL Server适用
  CLOSE CustCursor 
  DEALLOCATE CURSOR CustCursor 
  ```



## 高级特性

### 约束

- 主键

  ```sql
  CREATE TABLE Vendors
  (
  	vend_id       CHAR(10) NOT NULL PRIMARY KEY, -- 定义主键
    vend_name     CHAR(10) NOT NULL,
    vend_address  CHAR(10) NULL,
    vend_city     CHAR(10) NULL,
    vend_state    CHAR(10) NULL,
    vend_zip      CHAR(10) NULL,
    vend_country  CHAR(10) NULL
  );
  ```

  ```sql
  ALTER TABLE Vendors ADD CONSTRAINT PRIMARY KEY (vend_id); -- 定义主键
  ```

- 外键

  ```sql
  CREATE TABLE Orders
  (
  	order_num  INTEGER  NOT NULL PRIMARY KEY,
    order_date DATETIME NOT NULL,
    cust_id    CHAR(10) NOT NULL REFERENCES Customers(cust_id) -- 定义外键
  );
  ```

  ```sql
  ALTER TABLE Orders ADD CONSTRAINT FOREIGN KEY (cust_id) REFERENCES Customers (cust_id) -- 定义外键
  ```

- 唯一约束

  TODO

- 检查约束

  ```sql
  CREATE TABLE OrderItems
  (
  	order_num  INTEGER  NOT NULL,
    order_item INTEGER  NOT NULL,
    prod_id    CHAR(10) NOT NULL,
    quantity   INTEGER  NOT NULL CHECK(quantity > 0), -- 添加约束
    item_price MONEY    NOT NULL
  );
  ADD CONSTRAINT CHECK (gender LIKE '[MF]') -- 检查名为gender的列是否只包含M或F
  ```
  
### 索引

适用索引注意事项：

1. 索引改善检索操作的性能，但降低了数据插入，修改和删除的性能；
2. 索引数据可能要占用大量的存储空间；
3. 并非所有数据都适合做索引，索引适用于取值具有更多可能值的数据；
4. 索引用于数据过滤和数据排序；
5. 可以在索引中定义多个列；

- 创建索引

  ```sql
  CREATE INDEX prod_name_ind ON Products(prod_name); -- 对Products的列prod_name建立索引prod_name_ind
  ```

### 触发器

触发器内的代码居于以下数据的访问权限：

1. INSERT操作中的所有新数据；
2. UPDATE操作中的所有新数据和旧数据；
3. DELETE操作中删除的数据；

用途：

1. 保证数据一致；
2. 基于某个表的变动在其它表上执行活动；
3. 进行额外的验证并根据需要回退数据；
4. 计算计算列的值或更新时间戳；

- 创建触发器

  ```sql
  -- SQL Server
  CREATE TRIGGER customer_state 
  ON Customers 
  FOR INSERT, UPDATE 
  AS 
  UPDATE Customers 
  SET cust_state = Upper(cust_state) 
  WHERE Customers.cust_id = inserted.cust_id;
  
  -- Oracle, PostgreSQL
  CREATE TRIGGER customer_state 
  AFTER INSERT OR UPDATE 
  FOR EACH ROW 
  BEGIN 
  UPDATE Customers 
  SET cust_state = Upper(cust_state) 
  WHERE Customers.cust_id = :OLD.cust_id 
  END;
  ```

  




## 参考

[1] Forta B.sql必知必会.2013