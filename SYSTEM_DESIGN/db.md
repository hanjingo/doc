[中文版](db_zh.md) | English

# Database Design

[TOC]



## ACID

![acid](res/acid.png)



## CAP Theorem In Database Designing

![cap_theorem](res/cap_theorem.png)

According to the CAP theorem, only two of the three desirable characteristics consistency, availability, and partition tolerance can be shared or present in a networked shared-data system or distributed system.

### CP Database

A CP database prioritizes Consistency and Partition Tolerance from the CAP theorem, it sacrifices Availability, meaning the system might not respond during network issues to maintain data accuracy.

### AP Database

An AP database is a type of database that prioritizes Availability and Partition Tolerance from the CAP theorem, it sacrifices Consistency, meaning different nodes might have slightly different data from a short time.

### CA Database

A CA database is a type of database that prioritizes Consistency and Availability from the CAP theorem, it sacrifices Partition Tolerance meaning that if there is a network issue, the database might stop functioning rather than returning inconsistent or unavailable data.

---



## Types

![types_of_db](res/types_of_db.png)

Types of Databases in System Design:

- Relational Databases
- NoSQL Databases
- NewSQL Databases
- Time-Series Databases
- Object-Oriented Databases

### Relational vs Non-Relational Databases

Here are a few key factors to consider when choosing the right database:

| Factor                          | Relational Databases                                         | Non-Relational Databases                                     |
| ------------------------------- | ------------------------------------------------------------ | ------------------------------------------------------------ |
| Data Structure                  | If your data is structured, and you need to handle complex relationships. | If your data is unstructured or semi-structured.             |
| Scalability Needs               | Typically scale vertically(adding more power to a single server). | Of ten scale horizontally(adding more servers to distribute the load). |
| Consistency vs Availability     | If your application requires strong consistency.             | If your application needs to be highly available and can tolerate some inconsistency for a short time. |
| Transaction Support             | If you need ACID properties(Atomicity, Consistency, Isolation, Durability) for transaction. | If your system can work without strict transaction guarantees. |
| Development Speed & Flexibility | If you need a stable, structured design.                     | If your project evolve rapidly or need to handle changing types of data. |

---



## Data Sharding And Partitioning

![db_data_sharding](res/db_data_sharding.png)

### Data Sharding

![data_sharding](res/data_sharding.png)

Database Sharding is especially useful when a database becomes too large to fit on a single machine or when the traffic load is too high for one server to handle. It helps distribute the load across multiple server.

#### Key Based Sharding

![key_based_sharding](res/key_based_sharding.png)

Key-Based Sharding uses a hash function on a shard key. The generated hash value decides which shard will store the data.

Advantages:

- Key-based sharding assigns each key to a specific shard, ensuring uniform and consistent data distribution.
- It can be optimized to efficiently handle queries over consecutive key ranges.

Disadvantages:

- Uneven data distribution can occur if the sharding key isn't well-distributed.
- Scalability may be limited when certain keys receive heavy traffic or data is skewed.
- Choosing the right sharding key is crucial for effective sharding.

#### Horizontal or Range Based Sharding

![range_based_sharding](res/range_based_sharding.png)

In Horizontal or Range Based Sharding, we divide the data by separating it into different parts based on the range of a specific value within each record.

Advantages:

- Scalability: Horizontal or range-based sharding allows for seamless scalability by distributing data across multiple shards, accommodating growing datasets.
- Improved Performance: Data distribution among shards enhances query performance through parallelization, ensuring faster operations with smaller subsets of data handled by each shard.

Disadvantages:

- Complex Querying Across Shards: Coordinating queries involving multiple shards can be challenging.
- Uneven Data Distribution: Poorly managed data distribution may lead to uneven workloads among shards.

#### Vertical Sharding

![vertical_sharding](res/vertical_sharding.png)

In Vertical Sharding, we split the entire column from the table and we put those columns into new distinct tables. Data is totally independent of one partition to the other ones. Also, each partition holds both distinct rows and columns. We can split different features of an entity in different shards on different machines.

Advantages:

- Query Performance: Vertical sharding can improve query performance by allowing each shard to focus on a specific subset of columns. This specialization enhances the efficiency of queries that involve only a subset of the available columns.
- Simplified Queries: Queries that require a specific set of columns can be simplified, as they only need to interact with the shard containing the relevant columns.

Disadvantages:

- Potential for Hotspots: Certain shards may become hotspots if they contain highly accessed columns, leading to uneven distribution of workloads.
- Challenges in Schema Changes: Making changes to the schema, such as adding or removing columns, may be more challenging in a vertically sharded system. Changes can impact multiple shards and require careful coordination.

#### Directory-Based Sharding

![directory_based_sharding](res/directory_based_sharding.png)

In Directory-Based Sharding, we create and maintain a lookup service or lookup table for the original database. Basically we use a shard key for lookup table and we do mapping for each entity that exists in the database. This way we keep track of which database shards hold which data.

Advantages:

- Flexible Data Distribution: Directory-based sharding allows for flexible data distribution, where the central directory can dynamically manage and update the mapping of data to shard locations.
- Efficient Query Routing: Queries can be efficiently routed to the appropriate shard using the information stored in the directory. This results in improved query performance.
- Dynamic Scalability: The system can dynamically scale by adding or removing shards without requiring changes to the application logic.

Disadvantages:

- Centralized Point of Failure: The central directory represents a single point of failure. If the directory becomes unavailable or experiences issues, it can disrupt the entire system, impacting data access and query routing.
- Increased Latency: Query routing through a central directory introduces an additional layer, potentially leading to increased latency compared to other sharding strategies.

### Data Partitioning

Partitioning helps improve query performance by limiting the amount of data the system has to process for specific queries. It also makes it easier to manage large datasets.

---



## Database Replication

Database replication in system design means creating and maintaining multiple copies of the same database on different servers. If one database server fails, another replica can continue serving requests, ensuring the system stays online.

Database replication is important for several reasons:

- High Availability
- Disaster Recovery
- Load Balancer/Load Balancing
- Fault Tolerance
- Scalability
- Data Locality

### Working of Database Replication

Here are the steps explaining how database replication works:

![working_of_database_replication](res/working_of_database_replication.png)

1. Identify the Primary Database(Source);
2. Set up Replica Databases(Targets);
3. Data changes captured;
4. Transmit changes to replicas;
5. Apply changes on replicas;
6. Monitor and maintain synchronization;
7. Read or write operations.

### Types of Database Replication

![types_of_database_replication](res/types_of_database_replication.png)

- Master-Slave Replication
- Master-Master Replication/Multi-Master Replication
- Snapshot Replication
- Transactional Replication
- Merge Replication

### Strategies for Database Replication

Some common database replication strategies include the following:

- Full Replication
- Partial Replication
- Selective Replication
- Sharding
- Hybrid Replication

### Configurations of Database Replication

To accomplish particular objectives related to data consistency, availability, and performance, database replication can be set up and run in a variety of ways:

- Synchronous Replication Configuration
- Asynchronous Replication Configuration
- Semi-synchronous Replication Configuration

---



## Database Persists

### Redis

![redis_persists](res/redis_persists.png)



## Database Normalization And Denormalization

TODO

---



## Summary

### Horizontal Partitioning vs Vertical Partitioning

![horizontal_partitioning_vs_vertical_partitioning](res/horizontal_partitioning_vs_vertical_partitioning.png)

| Feature                  | Vertical Partitioning                                        | Horizontal Partitioning                                      |
| ------------------------ | ------------------------------------------------------------ | ------------------------------------------------------------ |
| Definition               | Dividing a table into smaller tables based on columns.       | Dividing a table into smaller tables based on rows(usually ranges of rows). |
| Purpose                  | Reduce the number of columns in a table to improve query performance and reduce I/O. | Divide a table into smaller tables to manage large volumes of data efficiently. |
| Data distribution        | Columns with related data are placed together in the same table. | Rows with related data(typically based on a range or a condition) are placed together in the same table. |
| Query performance        | Improves query performance when queries only involve specific columns that are part of a partition. | Improves query performance when queries primarily access a subset of rows in a large table. |
| Maintenance and indexing | Easier to manage and index specific columns based on their characteristics and access patterns. | Each partition can be indexed independently, making indexing more efficient. |
| Joins                    | May require joins to combine data from multiple partitions when querying. | Joins between partitions are typically not needed, as they contain disjoint sets of data. |
| Data integrity           | Ensuring data consistency across partitions can be challenging. | Easier to maintain data integrity, as each partition contains a self-contained subset of data. |
| Use cases                | Commonly used for tables with a wide range of columns, where not all columns are frequently accessed together. | Commonly used for tables with a large number of rows, where data can be grouped based on some criteria(e.g., data ranges). |



---



## References

[1] [Database Replication in System Design](https://www.geeksforgeeks.org/system-design/database-replication-and-their-types-in-system-design/)

[2] [Introduction to Database Normalization](https://www.geeksforgeeks.org/dbms/introduction-of-database-normalization/)

[3] [Denormalization in Databases](https://www.geeksforgeeks.org/dbms/denormalization-in-databases/)

[4] [Top 50 System Design Interview Questions for 2026](https://dev.to/somadevtoo/top-50-system-design-interview-questions-for-2024-5dbk)

[5] [System Design CheatSheet for Interview](https://medium.com/javarevisited/system-design-cheatsheet-4607e716db5a)
