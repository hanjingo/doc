# CHAPTER 28 Oracle



Oracle has extensive support for object-relational constructs, including:

- Object types. A single-inheritance model is supported for type hierarchies.
- Collection types. Oracle supports `varrays`, which are variable-length arrays, and nested tables.
- Object tables. These are used to store objects while providing a relational view of the attributes of the objects.
- Table functions. These are functions that produce sets of rows as output, and can be used in the from clause of a query. Table functions in Oracle can be nested. If a table function is used to express some form of data transformation, nesting multiple functions allows multiple transformations to be expressed in a single statement.
- object views. These provide a virtual object table view of data stored in a regular relational table. They allow data to be accessed or viewed in an object-oriented style, even if the data is really stored in a traditional relational format.
- Methods. These can be written in PL/SQL, Java, or C.
- User-defined aggregate functions. These can be used in SQL statements in the same way as built-in functions such as sum and count.

Oracle provides storage containers for multidimensional data known as `analytic workspaces`.

Usually, an Oracle database has the following table spaces:

- The `system` and the auxiliary `sysaux` table spaces, which are always created.
- Table spaces are created to store user data.
- The `undo` table space, which is used solely for storing undo information for transaction management and recovery.
- `Temporary` table spaces.

The space in a table space is divided into units, called `segments`, each of which contains data for a specific data structure. There are four types of segments:

- `Data segments`. Each table in a table space has its own data segment where the table data are stored unless the table is partitioned; if so, there is one data segment per partition.
- `Index segments`. Each index in a table space has its own index segment, except for partitioned indices, which have one index segment per partition.
- `Temporary segments`. These are segments used when a sort operation needs to write data to disk or when data is inserted into a temporary table.
- `Undo segments`. These segments contain undo information so that an uncommitted transaction can be rolled back.

Below the level of the segment, space is allocated at a level of granularity called an `extent`.

Oracle provides storage parameters that allow for detailed control of how space is allocated and managed, parameters such as:

- The size of a new extent that is to be allocated to provide room for rows that are inserted into a table.
- The percentage of space utilization at which a database block is considered full and at which no more rows will be inserted into that block.

Oracle supports several features to protect the data from unauthorized access, including:

- Encryption.
- Database Vault.
- Virtual Private Database.

The ability to partition a table or index has advantages in many areas:

- Backup and recovery are easier and faster, since they can be done on individual partitions rather than on the table as a whole.
- Loading operations in a data warehousing environment are less intrusive: data can be added to a newly created partition, and then the partition added to a table, which is an instantaneous operation. Likewise, dropping a partition with obsolete data from a table is very easy in a data warehouse that maintains a rolling window of historical data.
- Query performance benefits substantially, since the optimizer can recognize that only a subset of the partitions of a table need to be accessed in order to resolve a query (partition pruning). Also, the optimizer can recognize that in a join, it is not necessary to try to match all rows in one table with all rows in the other, but that the joins need to be done only between matching pairs of partitions (partitionwise join).

An index on a partitioned table can be either a `global index` or a `local index`.

Data can be accessed through a variety of access methods:

- Full table scan. 
- Index scan.
- Index fast full scan.
- Index join.
- Cluster and hash cluster access.

Some of the major types of transformations and rewrites supported by Oracle are as follows:

- View merging.
- Complex view merging.
- Subquery flattening.
- Materialized view rewrite.
- Star transformation.

The SQL Tuning Advisor can be used to improve the performance of these statements by making making various kinds of recommendations that fall into the following different categories:

- Statistics Analysis.
- SQL Profiling.
- Access Path Analysis.
- SQL Structure Analysis.

Oracle's SQL Plan Management feature addresses the risk associated with execution plan changes by maintaining a set of trusted execution plans for a workload and phasing in plans changed by the query optimizer only after they have been verified not to cause any performance degradations. The feature has three major components:

- SQL plan baseline capture.
- SQL plan baseline selection.
- SQL plan baseline evolution.

The SGA is a memory area for structures that are shared among users. It is made up of several major structures, including the following:

- Buffer cache.
- Redo log buffer.
- Shared pool.

Oracle can generate about two dozen different types of background processes. Some of the most important ones are:

- Database writer.
- Log writer.
- Checkpoint.
- System monitor.
- Process monitor.
- Recoverer.
- Archiver.

The shared-server configuration increases the number of users that a given number of server processes can support by sharing server processes among statements. It differs from the dedicated server architecture in these major aspects:

- A background dispatch process routes user requests to the next available server process.
- Since a server process is shared among multiple SQL statements, Oracle does not keep private data in the PGA. Instead, it stores the session-specific data in the SGA.

They are major advantages to offloading certain types of processing to storage CPUs:

- It allows a large, but relatively inexpensive, expansion of the amount of processing power that is available.
- The amount of data that needs to be transferred from a storage cell to the database server can be dramatically reduced, which can be very important since the bandwidth between the storage cell and database server is usually expensive and often a bottleneck.

When executing a query against Exadata storage, the reduction of the amount of data that needs to be retrieved comes from several techniques that can be pushed to the storage cells and executed there locally:

- Projection.
- Table filtering.
- Join filtering.

