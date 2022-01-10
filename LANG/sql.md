# SQL

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



## 检索

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








## 参考

### 参考文献

[1] Forta,B.sql必知必会.2013