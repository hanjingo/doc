# DB Summary

[TOC]



## DBMS Intro

### DBMS Types

- Relational Database Management System (RDBMS)
- NoSQL DBMS
- Object-Oriented DBMS (OODBMS)
- Hierarchical Database
- Network Database
- Cloud-Based Database

### DBMS vs RDBMS

|                             DBMS                             |                            RDBMS                             |
| :----------------------------------------------------------: | :----------------------------------------------------------: |
|                 DBMS stores data as a file.                  |              RDBMS stores data in tabular form.              |
|       Data elements need to be accessed individually.        |   Multiple data elements can be accessed at the same time.   |
|                No relationship between data.                 | Data is stored in the form of tables, which are related to each other. |
|                Normalization is not present.                 |                  Normalization is present.                   |
|        DBMS does not support a distributed database.         |            RDBMS supports a distributed database.            |
| It stores data in either a navigational or hierarchical form. | It uses a tabular structure where the headers are the column names, and the rows contain corresponding values. |
|           It deals with a small quantity of data.            |            It deals with a large amount of data.             |
|           Data redundancy is common in this model.           |        Keys and indexes do not allow Data redundancy.        |
| It is used for small organizations and deals with small amounts of data. |         It is used to handle a large amount of data.         |
|              Not all Codd rules are satisfied.               |               All 12 Codd rules are satisfied.               |
|                       Security is less                       |             More security measures are provided.             |
|                  It supports a single user.                  |                 It supports multiple users.                  |
|     Data fetching is slower for a large amount of data.      |  Data fetching is fast because of the relational approach.   |
| The data in a DBMS is subject to low security levels with regard to data manipulation. |  There exist multiple levels of data security in an RDBMS.   |
|            Low software and hardware necessities.            |          Higher software and hardware necessities.           |



## DBMS Architecture

### 1-Tier Architecture

![1_tier_arch](res/1_tier_arch.png)

### 2-Tier Architecture

![2_tier_arch](res/2_tier_arch.png)

### 3-Tier Architecture

![3_tier_arch](res/3_tier_arch.png)



### Relational Algebra

![relational_algebra](res/relational_algebra.png)



## Relational Model

### E-R Notation

![symb_used_in_er_notation](res/symb_used_in_er_notation.png)

![alter_er_notation](res/alter_er_notation.png)

### ER Model

![er_model](res/er_model.png)

### Enhanced ER Model

![enhanced_er_model](res/enhanced_er_model.png)

### Generalization in ER Model

![generalization_in_er_model](res/generalization_in_er_model.png)

### Specialization in ER Model

![specialization_in_er_model](res/specialization_in_er_model.png)

### Inheritance in ER Model

![inheritance_in_er_model](res/inheritance_in_er_model.png)

### Aggregation in ER Model

![aggregation_in_er_model](res/aggregation_in_er_model.png)



## Normalization

![db_normal_forms_hierarchy](res/db_normal_forms_hierarchy.png)

- `First Normal Form (1NF)`: Eliminating Duplicate Records
- `Second Normal Form (2NF)`: Eliminating Partial Dependency
- `Third Normal Form (3NF)`: Eliminating Transitive Dependency
- `Boyce-Codd Normal Form (BCNF)`: The Strongest Form of 3NF
- `Fourth Normal Form (4NF)`: Removing Multi-Valued Dependencies
- `Fifth Normal Form (5NF)`: Eliminating Join Dependency

### Denormalization

![denormalization](res/denormalization.png)

### Data Replication

![data_replication](res/data_replication.png)



## Transactions and Concurrency Control

### ACID Properties

![acid](res/acid.png)

### Concurrency Control Protocols

![concurrency_ctl_protocol](res/concurrency_ctl_protocol.png)

### Recoverable

![log_based_recovery](res/log_based_recovery.png)



## Storage

### Hierarchy

![storage_device_hierarchy](res/storage_device_hierarchy.png)

![disk_mechanism](res/disk_mechanism.png)

![raid_lvl](res/raid_lvl.png)

### Data Abstraction

![data_abstraction](res/data_abstraction.png)

- `Physical level`. The lowest level of abstraction describes `how` the data are actually stored. 
- `Logical level`. The next-higher level of abstraction describes `what` data are stored in the database, and what relationships exist among those data. 
- `View level`. The highest level of abstraction describes only part of the entire database.

### System structure

![system_structure](res/system_structure.png)

### Indexing

![dense_index](res/dense_index.png)

![sparse_index](res/sparse_index.png)



## Reference

[1] Abraham Silberschatz; Henry F. Korth; S. Sudarshan. Database System Concepts. 6th Edition

[2] [DBMS Tutorial](https://www.geeksforgeeks.org/dbms/dbms/)

[3] [Introduction of DBMS](https://www.geeksforgeeks.org/dbms/introduction-of-dbms-database-management-system-set-1/)

[4] [Types of DBMS Architecture](https://www.geeksforgeeks.org/dbms/dbms-architecture-2-level-3-level/)

[5] [Introduction of ER Model](https://www.geeksforgeeks.org/dbms/introduction-of-er-model/)

[6] [Enhanced ER Model](https://www.geeksforgeeks.org/dbms/enhanced-er-model/)

[7] [Introduction to Database Normalization](https://www.geeksforgeeks.org/dbms/introduction-of-database-normalization/)

[8] [Denormalization in Databases](https://www.geeksforgeeks.org/dbms/denormalization-in-databases/)

[9] [ACID Properties in DBMS](https://www.geeksforgeeks.org/dbms/acid-properties-in-dbms/)

[10] [Lock Based Concurrency Control Protocol in DBMS](https://www.geeksforgeeks.org/dbms/lock-based-concurrency-control-protocol-in-dbms/)

[11] [Indexing in Databases](https://www.geeksforgeeks.org/dbms/indexing-in-databases-set-1/)

[12] [Difference Between RDBMS and DBMS](https://www.geeksforgeeks.org/dbms/difference-between-rdbms-and-dbms/)
