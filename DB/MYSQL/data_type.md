# Mysql数据类型

[TOC]



## Decimal

`DECIMAL`数据类型主要用于在数据库中存储精确的数值，常用于对精确度要求较高的场景（如：金融系统/会计系统中的货币数据）。

### 定义

```sql
DECIMAL(P, D); # 定义D位小数的P位数
```

- `P` 有效数字字数的精度，范围[1, 65]；
- `D` 小数点后的位数，范围[0, 30]，要求`D <= P`；

### 属性

`DECIMAL`有以下属性：

- `UNSIGNED` 不接受负值；
- `ZEROFILL` 把显示值填充到0以显示由列定义指定的宽度，如果使用`ZEROFILL`属性，mysql自动将`UNSIGNED`添加到列；

mysql分别为整数和小数部分分配存储空间，使用二进制格式存储`DECIMAL`值；

例：`DECIMAL(19, 9)`：对于小数部分(9位数字)需要4个字节，对于整数部分(10位数字)需要5个字节，总共需要9个字节；

### 精度

使用`DECIMAL`表示货币时需要遵守(GAAP)规则(货币栏至少包含4位小数，以确保舍入值不超过`$0.01`)；

定义如下：

```sql
DECIMAL(19, 4);
```

`DECIMAL`为128bit的数据，不存在精度损失；

### 示例

```sql
CREATE TABLE materials (
	id INT AUTO_INCREMENT PRIMARY KEY,
    description VARCHAR(255),
    cost DECIMAL(19, 4) NOT NULL
);

INSERT INTO materials(description, cost) VALUES('bicycle', 500.34);
SELECT * FROM materials;
ALTER TABLE materials MODIFY cost DECIMAL(19, 4) zerofill;
SELECT * FROM materials;
```



## 参考

- [MySQL decimal类型](https://www.yiibai.com/mysql/decimal.html)
- [float、double(浮点数)区别还有和decimal(定点数)的比较](https://www.cnblogs.com/itcomputer/articles/4716024.html)

