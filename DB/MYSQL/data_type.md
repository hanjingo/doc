# MySQL Data Types

[TOC]



## Decimal

The `DECIMAL` data type is mainly used to store exact numeric values in databases, and is commonly used in scenarios that require high precision (for example, currency data in financial or accounting systems).

### Definition

```sql
DECIMAL(P, D); -- Defines a P-digit number with D decimal places
```

- `P`: precision (number of significant digits), range `[1, 65]`;
- `D`: number of digits after the decimal point, range `[0, 30]`, and `D <= P`;

### Attributes

`DECIMAL` has the following attributes:

- `UNSIGNED`: does not accept negative values;
- `ZEROFILL`: pads the displayed value with zeros to the width specified by the column definition. If `ZEROFILL` is used, MySQL automatically adds `UNSIGNED` to the column;

MySQL allocates storage separately for the integer and fractional parts, and stores `DECIMAL` values in binary format.

Example: `DECIMAL(19, 9)` requires 4 bytes for the fractional part (9 digits) and 5 bytes for the integer part (10 digits), for a total of 9 bytes.

### Precision

When using `DECIMAL` to represent currency, GAAP rules should be followed (currency fields should contain at least 4 decimal places to ensure rounded values do not exceed `$0.01`).

Definition:

```sql
DECIMAL(19, 4);
```

`DECIMAL` is a 128-bit data type and does not suffer from precision loss.

### Example

```sql
CREATE TABLE materials (
	id INT AUTO_INCREMENT PRIMARY KEY,
	description VARCHAR(255),
	cost DECIMAL(19, 4) NOT NULL
);

INSERT INTO materials(description, cost) VALUES('bicycle', 500.34);
SELECT * FROM materials;
ALTER TABLE materials MODIFY cost DECIMAL(19, 4) ZEROFILL;
SELECT * FROM materials;
```



## References

[1] [MySQL decimal type](https://www.yiibai.com/mysql/decimal.html)

[2] [Difference between float and double, and comparison with decimal](https://www.cnblogs.com/itcomputer/articles/4716024.html)
