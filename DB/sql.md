
English | [中文版](sql_zh.md)

# SQL Language

[TOC]



## Data Types

| Data Type           | Description                                           |
| ------------------- | ----------------------------------------------------- |
| BIT                 | Single binary bit value (0 or 1), used for flags      |
| DECIMAL             | Fixed-point or precision-variable numeric value      |
| FLOAT               | Floating-point value                                  |
| INT                 | 4-byte integer, [-2147483648, 2147483647]             |
| REAL                | 4-byte floating-point value                           |
| SMALLINT            | 2-byte integer, [-32768, 32768]                      |
| TINYINT             | 1-byte integer, [0~255]                               |
| CHAR                | Fixed-length string (1–255 chars) defined at creation |
| NCHAR               | CHAR variant for multibyte or Unicode characters      |
| NVARCHAR            | TEXT variant for multibyte or Unicode characters      |
| TEXT                | Variable-length text                                  |
| DATE                | Date value                                            |
| DATETIME/TIMESTAMP  | Date and time value                                   |
| SMALLDATETIME       | Date and time value with minute precision             |
| TIME                | Time value                                            |
| BINARY              | Fixed-length binary data [255B, 8000B]                |
| LONG RAW            | Variable-length binary data, <= 2GB                   |
| RAW                 | Fixed-length binary data, <= 255B                     |
| VARBINARY           | Variable-length binary data [255B, 8000B]             |



## Retrieval

SELECT clause order and usage:

| Clause      | Description                        | Required?                         |
| ----------- | ---------------------------------- | --------------------------------- |
| `SELECT`    | Columns or expressions to return   | Yes                               |
| `FROM`      | Tables to retrieve data from       | Used only when selecting from tables |
| `WHERE`     | Row-level filtering                | No                                |
| `GROUP BY`  | Grouping specification             | Used only with grouped aggregates |
| `HAVING`    | Group-level filtering              | No                                |
| `ORDER BY`  | Output sort order                  | No                                |

- Retrieve a single column

  ```sql
  SELECT prod_name FROM Products;
  ```

- Retrieve multiple columns

  ```sql
  SELECT prod_id, prod_name, prod_price FROM Products;
  ```

- Retrieve all columns

  ```sql
  SELECT * FROM Products;
  ```

  **Note: selecting unused columns can reduce query and application performance.**

- Retrieve distinct values

  ```sql
  SELECT DISTINCT vend_id FROM Products;
  ```

- Limit results

  ```sql
  -- MySQL, MariaDB, PostgreSQL, SQLite
  SELECT prod_name FROM Products LIMIT 5;
  SELECT prod_name FROM Products LIMIT 5 OFFSET 2; -- start from row 2
  -- SQL Server, Access
  SELECT TOP 5 prod_name FROM Products;
  -- DB2
  SELECT prod_name FROM Products FETCH FIRST 5 ROWS ONLY;
  -- Oracle
  SELECT prod_name FROM Products WHERE ROWNUM <= 5;
  ```

### Ordering

- Sort results

  ```sql
  SELECT prod_name FROM Products ORDER BY prod_name;
  ```

- Sort by multiple columns

  ```sql
  SELECT prod_id, prod_price, prod_name FROM Products ORDER BY prod_price, prod_name;
  ```

- Sort by column position

  ```sql
  SELECT prod_id, prod_price, prod_name FROM Products ORDER BY 2, 3; -- first by prod_price, then by prod_name
  ```

- Specify sort direction

  ```sql
  SELECT prod_id, prod_price, prod_name FROM Products ORDER BY prod_price DESC; -- descending
  SELECT prod_id, prod_price, prod_name FROM Products ORDER BY prod_price DESC, prod_name; -- prod_name defaults to ascending
  ```

### Filtering

WHERE operators:

| Operator | Meaning       | Operator  | Meaning                      |
| -------- | ------------- | --------- | ---------------------------- |
| `=`      | Equal         | `>`       | Greater than                 |
| `<>`     | Not equal     | `>=`      | Greater than or equal        |
| `!=`     | Not equal     | `!>`      | Not greater than             |
| `<`      | Less than     | `BETWEEN` | Between two specified values |
| `<=`     | Less or equal | `IS NULL` | Is NULL                      |
| `!<`     | Not less than |           |                              |

- Filter by a condition

  ```sql
  SELECT prod_name, prod_price FROM Products WHERE prod_price = 3.49;
  ```

  **Note: `ORDER BY` must appear after `WHERE` when both are used.**

- Check a single condition

  ```sql
  SELECT prod_name, prod_price FROM Products WHERE prod_price < 10;
  ```

- Not equal checks

  ```sql
  SELECT vend_id, prod_name FROM Products WHERE vend_id <> 'DLL01';
  SELECT vend_id, prod_name FROM Products WHERE vend_id != 'DLL01';
  ```

  **Note: `!=` and `<>` are generally interchangeable.**

- Range check

  ```sql
  SELECT prod_name, prod_price FROM Products WHERE prod_price BETWEEN 5 AND 10;
  ```

- NULL check

  ```sql
  SELECT prod_name FROM Products WHERE prod_price IS NULL;
  ```

- Multiple conditions

  ```sql
  SELECT prod_id, prod_price, prod_name FROM Products WHERE vend_id = 'DLL01' AND prod_price <= 4;
  ```

- Match any condition

  ```sql
  SELECT prod_name, prod_price FROM Products WHERE vend_id = 'DLL01' OR vend_id = 'BRS01';
  ```

- Specify order of evaluation

  ```sql
  SELECT prod_name, prod_price FROM Products WHERE (vend_id = 'DLL01' OR vend_id = 'BRS01') AND prod_price >= 10; -- parentheses precedence
  ```

- Specify a set

  ```sql
  SELECT prod_name, prod_price FROM Products WHERE vend_id IN ('DLL01', 'BRS01') ORDER BY prod_name;
  SELECT prod_name, prod_price FROM Products WHERE vend_id = 'DLL01' OR vend_id = 'BRS01' ORDER BY prod_name; -- equivalent
  ```

  Advantages of `IN`:

  1. Clearer syntax when many valid options exist;
  2. Easier precedence management when combined with `AND`/`OR`;
  3. Often faster than multiple `OR` conditions;
  4. `IN` can include another `SELECT`, making WHERE more dynamic.

- Negation

  ```sql
  SELECT prod_name FROM Products WHERE NOT vend_id = 'DLL01' ORDER BY prod_name;
  SELECT prod_name FROM Products WHERE vend_id <> 'DLL01' ORDER BY prod_name; -- equivalent
  ```

### Wildcards

Wildcard usage tips:
1. Avoid overusing wildcards; use other operators when possible;
2. Avoid leading wildcards when possible (slow search);
3. Pay attention to wildcard placement to get intended matches;

- `%`

  ```sql
  SELECT prod_id, prod_name FROM Products WHERE prod_name LIKE 'Fish%'; -- starts with 'Fish'
  SELECT prod_id, prod_name FROM Products WHERE prod_name LIKE '%bean bag%'; -- contains 'bean bag'
  SELECT prod_name FROM Products WHERE prod_name LIKE 'F%y'; -- starts with F and ends with y
  ```

  Note: `%` does not match NULL values.

- `_`

  ```sql
  SELECT prod_id, prod_name FROM Products WHERE prod_name LIKE '__ inch teddy bear'; -- matches a two-digit number
  ```

  Note 1: DB2 may not support `_`.
  Note 2: Microsoft Access uses `?` instead of `_`.

- `[]`

  ```sql
  SELECT cust_contact FROM Customers WHERE cust_contact LIKE '[JM]%' ORDER BY cust_contact; -- matches values starting with 'J' or 'M'
  
  SELECT cust_contact FROM Customers WHERE cust_contact LIKE '[^JM]%' ORDER BY cust_contact; -- matches values not starting with 'J' or 'M'
  SELECT cust_contact FROM NOT cust_contact LIKE '[JM]%' ORDER BY cust_contact; -- equivalent to '[^JM]%'
  ```



## Computed Columns

### Concatenate fields

```sql
-- MySQL, MariaDB
SELECT Concat(vend_name, '(', vend_country, ')') FROM Vendors ORDER BY vend_name; -- concatenate vend_name and vend_country
SELECT RTRIM(vend_name) + '(' + RTRIM(vend_country) + ')' FROM Vendors ORDER BY vend_name; -- concatenate and trim right spaces
SELECT RTRIM(vend_name) + '(' + RTRIM(vend_country) + ')' AS vend_title FROM Vendors ORDER BY vend_name; -- use alias and trim

-- Access, SQL Server
SELECT vend_name + '(' + vend_country + ')' FROM Vendors ORDER BY vend_name;
SELECT RTRIM(vend_name) + '(' + RTRIM(vend_country) + ')' FROM Vendors ORDER BY vend_name;
SELECT RTRIM(vend_name) + '(' + RTRIM(vend_country) + ')' AS vend_title FROM Vendors ORDER BY vend_name;

-- DB2, Oracle, PostgreSQL, SQLite, Open Office Base
SELECT vend_name || '(' || vend_country || ')' FROM Vendors ORDER BY vend_name;
SELECT RTRIM(vend_name) || '(' || RTRIM(vend_country) || ')' FROM Vendors ORDER BY vend_name;
SELECT RTRIM(vend_name) || '(' || RTRIM(vend_country) || ')' AS vend_title FROM Vendors ORDER BY vend_name;
```

### Arithmetic

SQL arithmetic operators:

| Operator | Meaning |
| -------- | ------- |
| `+`      | Addition |
| `-`      | Subtraction |
| `*`      | Multiplication |
| `/`      | Division |

```sql
SELECT prod_id, quantity, item_price FROM OrderItems WHERE order_num = 20008; -- all items for order 20008
SELECT prod_id, quantity, item_price, quantity*item_price AS expanded_price FROM OrderItems WHERE order_num = 20008; -- include computed expanded_price
```



## Functions

### Text functions

Common text functions:

| Function   | Description                 |
| ---------- | --------------------------- |
| `LEFT()`   | Return left-most characters |
| `LENGTH()` | Return string length        |
| `LOWER()`  | Convert to lowercase        |
| `LTRIM()`  | Trim left spaces            |
| `RIGHT()`  | Return right-most chars     |
| `RTRIM()`  | Trim right spaces           |
| `SOUNDEX()`| Return SOUNDEX value        |
| `UPPER()`  | Convert to uppercase        |

- Search by SOUNDEX

  ```sql
  SELECT cust_name, cust_contact FROM Customers WHERE SOUNDEX(cust_contact) = SOUNDEX('Michael Green'); -- find similar-sounding values
  ```

### Date and time functions

Functions that return system date by DBMS:

| DBMS       | Function/Variable      |
| ---------- | ---------------------- |
| Access     | `NOW()`                |
| DB2        | `CURRENT_DATE`         |
| MySQL      | `CURRENT_DATE()`       |
| Oracle     | `SYSDATE`              |
| PostgreSQL | `CURRENT_DATE`         |
| SQL Server | `GETDATE()`            |
| SQLite     | `date('now')`          |

```sql
-- MySQL, MariaDB
SELECT order_num FROM Orders WHERE YEAR(order_date) = 2012;

-- SQL Server
SELECT order_num FROM Orders WHERE DATEPART(yy, order_date) = 2012;

-- Access
SELECT order_num FROM Orders WHERE DATEPART('yyyy', order_date) = 2012;

-- Oracle
SELECT order_num FROM Orders WHERE to_number(to_char(order_date, 'YYYY')) = 2012;
SELECT order_num FROM Orders WHERE order_date BETWEEN to_date('01-01-2012') AND to_date('12-31-2012');

-- SQLite
SELECT order_num FROM Orders WHERE strftime('%Y', order_date) = '2012';
```

### Numeric functions

| Function | Description                |
| -------- | -------------------------- |
| `ABS()`  | Absolute value             |
| `COS()`  | Cosine of an angle         |
| `EXP()`  | Exponential value          |
| `PI()`   | Pi constant                |
| `SIN()`  | Sine of an angle           |
| `SQRT()` | Square root                |
| `TAN()`  | Tangent of an angle        |



## Aggregation

SQL aggregate functions:

| Function   | Description              |
| ---------- | ------------------------ |
| `AVG()`    | Average of a column      |
| `COUNT()`  | Count rows/values        |
| `MAX()`    | Maximum value            |
| `MIN()`    | Minimum value            |
| `SUM()`    | Sum of values            |

- Average

  ```sql
  SELECT AVG(prod_price) AS avg_price FROM Products;
  SELECT AVG(prod_price) AS avg_price FROM Products WHERE vend_id = 'DLL01';
  ```

- Count

  ```sql
  SELECT COUNT(*) AS num_cust FROM Customers;
  SELECT COUNT(cust_email) AS num_cust FROM Customers; -- count non-null emails
  ```

- Max

  ```sql
  SELECT MAX(prod_price) AS max_price FROM Products;
  ```

- Min

  ```sql
  SELECT MIN(prod_price) AS min_price FROM Products;
  ```

- Sum

  ```sql
  SELECT SUM(quantity) AS items_ordered FROM OrderItems WHERE order_num = 20005;
  SELECT SUM(item_price*quantity) AS total_price FROM OrderItems WHERE order_num = 20005;
  ```

- Distinct averages

  ```sql
  SELECT AVG(DISTINCT prod_price) AS avg_price FROM Products WHERE vend_id = 'DLL01';
  ```

  **Note: `DISTINCT` cannot be used with `COUNT(*)`.**

- Combine multiple aggregates

  ```sql
  SELECT COUNT(*) AS num_items, MIN(prod_price) AS price_min, MAX(prod_price) AS price_max, AVG(prod_price) AS price_avg FROM Products;
  ```

  


## Grouping

Rules for `GROUP BY`:
1. `GROUP BY` may include any number of columns to nest grouping;
2. Nested grouping will aggregate on the last specified grouping;
3. Every non-aggregate expression in `SELECT` must appear in `GROUP BY` (use same expression, not alias);
4. Many SQL implementations disallow grouping on variable-length types (e.g., TEXT);
5. Aside from aggregate expressions, every `SELECT` column must be listed in `GROUP BY`;
6. NULLs in grouping columns form a single group;
7. `GROUP BY` appears after `WHERE` and before `ORDER BY`.

Difference between `ORDER BY` and `GROUP BY`:

| ORDER BY                                | GROUP BY                                                    |
| --------------------------------------- | ----------------------------------------------------------- |
| Sorts the produced output                | Groups rows; output order may not be grouping order         |
| Can use any column (even non-selected)   | Only use select-list columns or expressions used in SELECT  |
| Not always required                      | Required when using aggregates on columns or expressions    |

- Grouping example

  ```sql
  SELECT vend_id, COUNT(*) AS num_prods FROM Products GROUP BY vend_id;
  ```

- `HAVING` to filter groups

  ```sql
  SELECT cust_id, COUNT(*) AS orders FROM Orders GROUP BY cust_id HAVING COUNT(*) >= 2;
  
  SELECT vend_id, COUNT(*) AS num_prods FROM Products WHERE prod_price >= 4 GROUP BY vend_id HAVING COUNT(*) >= 2;
  
  SELECT vend_id, COUNT(*) AS num_prods FROM Products GROUP BY vend_id HAVING COUNT(*) >= 2;
  ```

- Grouped sorting

  ```sql
  SELECT order_num, COUNT(*) AS items FROM OrderItems GROUP BY order_num HAVING COUNT(*) >= 3 ORDER BY items, order_num;
  ```

  


## Subqueries

- Subquery examples

  ```sql
  SELECT cust_id FROM Orders WHERE order_num IN (SELECT order_num FROM OrderItems WHERE prod_id = 'RGAN01');
  
  SELECT cust_name, cust_contact FROM Customers WHERE cust_id IN (SELECT cust_id FROM Orders WHERE order_num IN (SELECT order_num FROM OrderItems WHERE prod_id = 'RGAN01'));
  ```

  **Note 1: a subquery used as a value must return a single column.**
  **Note 2: subqueries can be less efficient; use with care.**

- Create computed column with subquery

  ```sql
  SELECT cust_name, cust_state, (SELECT COUNT(*) FROM Orders WHERE Orders.cust_id = Customers.cust_id) AS orders FROM Customers ORDER BY cust_name;
  ```

  **Note: this is not the most efficient retrieval method.**

  


## Joins

Join usage notes:
1. Choose the correct join type (inner joins are common);
2. Check DBMS-specific join syntax;
3. Provide correct join conditions to avoid incorrect results;
4. Always provide join conditions to avoid Cartesian products;
5. Multiple tables and different join types can be combined in one query.

- Simple join

  ```sql
  SELECT vend_name, prod_name, prod_price FROM Vendors, Products WHERE Vendors.vend_id = Products.vend_id;
  ```

- Inner join

  ```sql
  SELECT vend_name, prod_name, prod_price FROM Vendors INNER JOIN Products ON Vendors.vend_id = Products.vend_id;
  ```

- Multi-table join

  ```sql
  SELECT prod_name, vend_name, prod_price, quantity FROM OrderItems, Products, Vendors WHERE Products.vend_id = Vendors.vend_id AND OrderItems.prod_id = Products.prod_id AND order_num = 20007;
  ```

  **Note 1: more tables in a join generally reduce performance.**
  **Note 2: SQL does not limit join count, but DBMS implementations may.**

- Use table aliases

  ```sql
  SELECT RTRIM(vend_name) + '(' + RTRIM(vend_country) + ')' AS vend_title FROM Vendors ORDER BY vend_name;

  SELECT cust_name, cust_contact FROM Customers AS C, Orders AS O, OrderItems AS OI WHERE C.cust_id = O.cust_id AND OI.order_num = O.order_num AND prod_id = 'RGAN01';

  SELECT c1.cust_id, c1.cust_name, c1.cust_contact FROM Customers AS c1, Customers AS c2 WHERE c1.cust_name = c2.cust_name AND c2.cust_contact = 'Jim Jones';
  ```

  **Note: self-joins are generally faster than equivalent subqueries.**

- Natural join example

  ```sql
  SELECT C.*, O.order_num, O.order_date, OI.prod_id, OI.quantity, OI.item_price FROM Customers AS C, Orders AS O, OrderItems AS OI WHERE C.cust_id = O.cust_id AND OI.order_num = O.order_num AND prod_id = 'RGAN01';
  ```

- Outer joins

  ```sql
  SELECT Customers.cust_id, Orders.order_num FROM Customers LEFT OUTER JOIN Orders ON Customers.cust_id = Orders.cust_id;

  -- SQLite does not support RIGHT OUTER JOIN
  SELECT Customers.cust_id, Orders.order_num FROM Customers RIGHT OUTER JOIN Orders ON Orders.cust_id = Customers.cust_id;

  -- Access, MariaDB, MySQL, Open Office Base, SQLite do not support FULL OUTER JOIN
  SELECT Customers.cust_id, Orders.order_num FROM Orders FULL OUTER JOIN Customers ON Orders.cust_id = Customers.cust_id;
  ```

- Joins with aggregates

  ```sql
  SELECT Customers.cust_id, COUNT(Orders.order_num) AS num_ord FROM Customers INNER JOIN Orders ON Customers.cust_id = Orders.cust_id GROUP BY Customers.cust_id;
  
  SELECT Customers.cust_id, COUNT(Orders.order_num) AS num_ord FROM Customers LEFT JOIN Orders ON Customers.cust_id = Orders.cust_id GROUP BY Customers.cust_id;
  ```



## Compound Queries

`UNION` rules:
1. `UNION` is composed of two or more `SELECT` statements separated by `UNION`;
2. Each query in a `UNION` must return the same columns, expressions or aggregates;
3. Column data types must be compatible (not necessarily identical) and implicitly convertible by the DBMS.

- `UNION` example

  ```sql
  SELECT cust_name, cust_contact, cust_email FROM Customers WHERE cust_state IN ('IL', 'IN', 'MI') UNION SELECT cust_name, cust_contact, cust_email FROM Customers WHERE cust_name = 'Fun4All';

  SELECT cust_name, cust_contact, cust_email FROM Customers WHERE cust_state IN ('IL', 'IN', 'MI') OR cust_name = 'Fun4All';
  ```

- Include or allow duplicates

  ```sql
  SELECT cust_name, cust_contact, cust_email FROM Customers WHERE cust_state IN ('IL', 'IN', 'MI') UNION ALL SELECT cust_name, cust_contact, cust_email FROM Customers WHERE cust_name = 'Fun4All';
  ```

- Sort union results

  ```sql
  SELECT cust_name, cust_contact, cust_email FROM Customers WHERE cust_state IN ('IL', 'IN', 'MI') UNION SELECT cust_name, cust_contact, cust_email FROM Customers WHERE cust_name = 'Fun4All' ORDER BY cust_name, cust_contact;
  ```



## Insert

- Insert full row

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
              NULL);
  ```

- Insert partial row

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

- Insert from a query

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
  FROM CustNew;
  ```

- Copy table

  ```sql
  SELECT * INTO CustCopy FROM Customers; -- copy Customers into CustCopy
  CREATE TABLE CustCopy AS SELECT * FROM Customers; -- create CustCopy and copy data
  ```



## Update and Delete

Principles when using `UPDATE` or `DELETE`:
1. Never run `UPDATE` or `DELETE` without `WHERE` unless you intend to change all rows;
2. Ensure each table has a primary key and use it in `WHERE` when possible;
3. Test `WHERE` with a `SELECT` before `UPDATE`/`DELETE` to avoid mistakes;
4. Use referential integrity to prevent deleting rows referenced by other tables;
5. Some DBMS allow preventing `UPDATE`/`DELETE` without `WHERE` — use such features if available.

- Update data

  ```sql
  UPDATE Customers SET cust_email = 'abc@qq.com' WHERE cust_id = '100';

  UPDATE Customers SET cust_contact = 'abc', cust_email = 'abc@qq.com' WHERE cust_id = '100';

  UPDATE Customers SET cust_email = NULL WHERE cust_id = '100';
  ```

- Delete data

  ```sql
  DELETE FROM Customers WHERE cust_id = '100';
  ```



## Table operations

Table modification notes:
1. Ideally avoid altering tables that already contain data; design ahead to reduce structural changes;
2. Most DBMS allow adding columns with limitations on type, NULL and DEFAULT usage;
3. Many DBMS do not allow deleting or changing columns easily;
4. Most DBMS allow renaming columns;
5. DBMS often restrict changing columns that contain data; less restriction on empty columns.

- Create table

  ```sql
  CREATE TABLE Products
  (
    prod_id    CHAR(10)      NOT NULL,
    vend_id    CHAR(10)      NOT NULL DEFAULT "a",
    prod_name  CHAR(254)     NULL,
    prod_price DECIMAL(8, 2) ,
    prod_desc  VARCHAR(1000)
  );
  ```

  **Note: primary keys uniquely identify rows and cannot be NULL.**

- Alter table

  ```sql
  ALTER TABLE Vendors ADD vend_phone CHAR(20);

  ALTER TABLE Vendors DROP COLUMN vend_phone;
  ```

- Drop table

  ```sql
  DROP TABLE CustCopy;
  ```



## Views

View rules and limitations:
1. Views must have unique names like tables;
2. No general limit on number of views;
3. Creating views requires sufficient privileges;
4. Views may be nested, but nested views can hurt performance;
5. Many DBMS prohibit `ORDER BY` in view definitions;
6. Some DBMS require explicit column names for returned columns; computed columns need aliases;
7. Views cannot be indexed or have associated triggers/defaults in many DBMS;
8. Some views are read-only; you can select but not write back to base tables;
9. Some DBMS allow only updatable views where inserted/updated rows still belong to the view.

- Create view

  ```sql
  CREATE VIEW ProductCustomers AS 
    SELECT cust_name, cust_contact, prod_id 
    FROM Customers, Orders, OrderItems 
    WHERE Customers.cust_id = Orders.cust_id AND OrderItems.order_num = Orders.order_num;
  ```

- Use view

  ```sql
  SELECT cust_name, cust_contact FROM ProductCustomers WHERE prod_id = 'RGAN01';
  ```

- Use views to format output

  ```sql
  SELECT RTRIM(vend_name) + '(' + RTRIM(vend_country) + ')' AS vend_title FROM Vendors ORDER BY vend_name;

  SELECT RTRIM(vend_name) || '(' || RTRIM(vend_country) || ')' AS vend_title FROM Vendors ORDER BY vend_name;

  CREATE VIEW VendorLocations AS SELECT RTRIM(vend_name) + '(' + RTRIM(vend_country) + ')' AS vend_title FROM Vendors;
  SELECT * FROM VendorLocations;

  CREATE VIEW VendorLocations AS SELECT RTRIM(vend_name) || '(' || RTRIM(vend_country) || ')' AS vend_title FROM Vendors; 
  SELECT * FROM VendorLocations;
  ```

- Use view to filter

  ```sql
  CREATE VIEW CustomerEMailList AS SELECT cust_id, cust_name, cust_email FROM Customers WHERE cust_email IS NOT NULL;
  SELECT * FROM CustomerEMailList;
  ```

- Use view to simplify computed columns

  ```sql
  CREATE VIEW OrderItemsExpanded AS SELECT prod_num, prod_id, quantity, item_price, quantity*item_price AS expanded_price FROM OrderItems;
  SELECT * FROM OrderItemsExpanded WHERE order_num = 20008;
  ```



## Stored Procedures

| Parameter Type | Purpose                                |
| -------------- | -------------------------------------- |
| OUT            | Return values from the procedure       |
| IN             | Pass values into the procedure         |
| INOUT          | Pass values in and return modified     |

- Create a stored procedure

  ```sql
  CREATE PROCEDURE MailingListCount (
    ListCount OUT INTEGER
  )
  BEGIN
    SELECT COUNT(*) INTO v_rows 
    FROM Customers 
    WHERE NOT cust_email IS NULL;
    ListCount := v_rows;
  END;
  
  -- Oracle example
  var ReturnValue NUMBER EXEC MailingListCount(:ReturnValue);
  SELECT ReturnValue;
  
  -- SQL Server example
  CREATE PROCEDURE MailingListCount AS DECLARE @cnt INTEGER SELECT @cnt = COUNT(*) FROM Customers WHERE NOT cust_email IS NULL;
  RETURN @cnt;
  
  -- SQL Server usage
  DECLARE @ReturnValue INT
  EXECUTE @ReturnValue=MailingListCount;
  SELECT @ReturnValue;
  ```



## Transactions

- Transaction block

  ```sql
  -- SQL Server
  BEGIN TRANSACTION
  ...
  COMMIT TRANSACTION

  -- MariaDB, MySQL
  START TRANSACTION
  ...

  -- Oracle
  SET TRANSACTION
  ...

  -- PostgreSQL
  BEGIN
  ...
  ```

- Rollback

  ```sql
  DELETE FROM Orders;
  ROLLBACK;
  ```

- Explicit commit

  ```sql
  -- SQL Server
  BEGIN TRANSACTION 
  DELETE OrderItems WHERE order_num = 12345 
  DELETE Orders WHERE order_num = 12345 
  COMMIT TRANSACTION

  -- Oracle
  SET TRANSACTION 
  DELETE OrderItems WHERE order_num = 12345; 
  DELETE Orders WHERE order_num = 12345; 
  COMMIT;
  ```

- Savepoints

  ```sql
  -- MariaDB, MySQL, Oracle
  SAVEPOINT delete1;
  ROLLBACK TO delete1;
  
  -- SQL Server
  SAVE TRANSACTION delete1;
  ROLLBACK TRANSACTION delete1;
  ```

```sql
-- SQL Server full example
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



## Cursors

- Declare cursor

  ```sql
  -- DB2, MariaDB, MySQL, SQL Server
  DECLARE CustCursor CURSOR 
  FOR 
  SELECT * FROM Customers WHERE cust_email IS NULL

  -- Oracle, PostgreSQL
  DECLARE CURSOR CustCursor 
  IS 
  SELECT * FROM Customers WHERE cust_email IS NULL
  ```

- Use cursors (Oracle example)

  ```sql
  -- Fetch single row
  DECLARE TYPE CustCursor IS REF CURSOR
    RETURN Customers%ROWTYPE;
  DECLARE CustRecord Customers%ROWTYPE
  BEGIN
    OPEN CustCursor;
    FETCH CustCursor INTO CustRecord;
    CLOSE CustCursor;
  END;
  
  -- Loop through rows
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

-- Microsoft SQL Server example

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

- Close cursor

  ```sql
  -- DB2, Oracle, PostgreSQL
  CLOSE CustCursor
  
  -- SQL Server
  CLOSE CustCursor 
  DEALLOCATE CURSOR CustCursor 
  ```



## Advanced Features

### Constraints

- Primary key

  ```sql
  CREATE TABLE Vendors
  (
    vend_id       CHAR(10) NOT NULL PRIMARY KEY,
    vend_name     CHAR(10) NOT NULL,
    vend_address  CHAR(10) NULL,
    vend_city     CHAR(10) NULL,
    vend_state    CHAR(10) NULL,
    vend_zip      CHAR(10) NULL,
    vend_country  CHAR(10) NULL
  );
  ```

  ```sql
  ALTER TABLE Vendors ADD CONSTRAINT PRIMARY KEY (vend_id);
  ```

- Foreign key

  ```sql
  CREATE TABLE Orders
  (
    order_num  INTEGER  NOT NULL PRIMARY KEY,
    order_date DATETIME NOT NULL,
    cust_id    CHAR(10) NOT NULL REFERENCES Customers(cust_id)
  );
  ```

  ```sql
  ALTER TABLE Orders ADD CONSTRAINT FOREIGN KEY (cust_id) REFERENCES Customers (cust_id)
  ```

- Unique constraint

  ```sql
  CREATE TABLE Employees (
    emp_id INT PRIMARY KEY,
    emp_email VARCHAR(255) UNIQUE,
    emp_name VARCHAR(100)
  );

  -- Or using ALTER TABLE
  ALTER TABLE Employees ADD CONSTRAINT unique_email UNIQUE (emp_email);
  ```

- Check constraint

  ```sql
  CREATE TABLE OrderItems
  (
    order_num  INTEGER  NOT NULL,
    order_item INTEGER  NOT NULL,
    prod_id    CHAR(10) NOT NULL,
    quantity   INTEGER  NOT NULL CHECK(quantity > 0),
    item_price MONEY    NOT NULL
  );
  ADD CONSTRAINT CHECK (gender LIKE '[MF]')
  ```

### Indexes

Indexing notes:
1. Indexes improve retrieval performance but slow inserts/updates/deletes;

2. Indexes can consume significant storage;

3. Index columns should have many distinct values;

4. Indexes help filtering and sorting;

5. Multi-column indexes are supported.

Create index

```sql
CREATE INDEX prod_name_ind ON Products(prod_name);
```

### Triggers

Trigger access to data:
1. For INSERT, access to all new data;
2. For UPDATE, access to old and new data;
3. For DELETE, access to deleted data;

Uses:
1. Enforce data consistency;
2. Perform actions on other tables when a table changes;
3. Perform extra validation and rollback if needed;
4. Compute derived columns or update timestamps;

- Create a trigger

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



## References

[1] Forta B. SQL in 10 Minutes, 2013

