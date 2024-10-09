# Chapter4 Intermediate SQL



SQL provides other forms of the join operation, including the ability to specify an explicit `join predicate`, and the ability to include in the result tuples that are excluded by `natural join`.

The `on` condition allows a general predicate over the relations being joined. This predicate is written like a `where` clause predicate except for the use of the keyword `on` rather than `where`. Like the `using` condition, the `on` condition appears at the end of the join expression. For example:

```sql
select * from student join takes on student.ID=takes.ID;
```

The `outer join` operation works in a manner similar to the join operations.

There are in fact three forms of outer join:

- The `left outer join` preserves tuples only in the relation named before (to the left of) the `left outer join` operation.
- The `right outer join` preserves tuples only in the relation named after (to the right of) the `right outer join` operation.
- The `full outer join` preserves tuples in both relations.

The `right outer join` is symmetric to the `left outer join`.

The `full outer join` is a combination of the left and right outer-join types.

Any such relation that is not part of the logical model, but is made visible to a user as a virtual relation, is called a `view`.

We define a view in SQL by using the `create view` command, for example:

```sql
create view v as <query expression>;
```

Certain database systems allow view relations to be stored, but they make sure that, if the actual relations used in the view definition change, the view is kept up-to-date. Such views are called `materialized views`.

The process of keeping the materialized view up-to-date is called `materialized view maintenance` (or often, just `view maintenance`).

In general, an SQL view is said to be `updatable` (this is, inserts, updates or deletes can be applied on the view) if the following conditions are all satisfied by the query defining the view:

- The `from` clause has only one database relation.
- The `select` clause contains only attribute names of the relation and does not have any expressions, aggregates, or `distinct` specifications.
- Any attribute not listed in the `select` clause can be set to `null`; that is, it does not have a `not null` constraint and is not part of a primary key.
- The query does not have a `group by` or `having` clause.

, For example:

```sql
create view history_instructors as select * from instructor where dept_name='History';
```

Views can be defined with a `with check option` clause at the end of the view definition; then, if a tuple inserted into the view does not satisfy the view's `where` clause condition, the insertion is rejected by the database system. Updates are similarly rejected if the new value does not satisfy the `where` clause conditions.

A `transaction` consists of a sequence of query and/or update statements. One of the following SQL statements must end the transaction:

- `Commit work`: commits the current transaction; that is, it makes the updates performed by the transaction become permanent in the database. After the transaction is committed, a new transaction is automatically started.
- `Rollback work`: causes the current transaction to be rolled back; that is, it undoes all the updates performed by the SQL statements in the transaction. Thus, the database state is restored to what it was before the first statement of the transaction was executed.

, The keyword `work` is optional in both the statements.

Once a transaction has executed `commit work`, its effects can no longer be undone by `rollback work`.

The `create table` command may also include integrity-constraint statements. The allowed integrity constraints include:

- not null
- unique
- check(<predicate>)

The `not null` specification prohibits the insertion of a null value for the attribute. Any database modification that would cause a null to be inserted in an attribute declared to be `not null` generates an error diagnostic.

SQL also supports an integrity constraint:

```sql
unique(A1, A2, ..., Am)
```

The `unique` specification says that attributes `A1, A2, ..., Am` form a candidate key.

When applied to a relation declaration, the clause `check(P)` specifies a predicate `P` that must be satisfied by every tuple in a relation. For example:

```sql
create table section
	(course_id    varchar(8),
   sect_id      varchar(8),
   semester     varchar(6),
   year         numeric(4, 0),
   building     varchar(15),
   room_number  varchar(7),
   time_slot_id varchar(4),
   primary key(course_id, sec_id, semester, year),
   check(semester in('Fall', 'Winter', 'Spring', 'summer'))
   );
```

Often, we wish to ensure that a value that appears in one relation for a given set of attributes also appears for a certain set of attributes in another relation. This condition is called `referential integrity`.

More generally, let $r_1$ and $r_2$ be relations whose set of attributes are $R_1$ and $R_2$, respectively, with primary keys $K_1$ and $K_2$. We say that a subset $\alpha$ of $R_2$ is a `foreign key` referencing $K_1$ in relation $r_1$ if it is required that, for every tuple $t_2$ in $r_2$, there must be a tuple $t_1$ in $r_1$ such that $t_1 \cdot K_1 = t_2 \cdot \alpha$ .

Requirements of this form are called `referential-integrity constraints`, or `subset dependencies`.

The SQL standard supports several data types relating to dates and times:

- `date`: A calendar date containing a (four-digit) year, month, and day of the month.
- `time`: The time of day, in hours, minutes, and seconds.
- `timestamp`: A combination of `date` and `time`.

SQL allows a default value to be specified for an attribute.

An `index` on an attribute of a relation is a data structure that allows the database system to find those tuples in the relation that have a specified value for that attribute efficiently, without scanning through all the tuples of the relation.

SQL provides large-object data types for character data(`clob`) and binary data(`blob`). For example:

```sql
book_review clob(10KB)
image blob(10MB)
movie blob(2GB)
```

SQL supports two forms of user-defined data types:

- `distinct types`.
- `structured data types`.

A good type of system should be able to detect such assignments or comparisons. To support such checks, SQL provides the notion of `distinct types`.

SQL had a similar but subtly different notion of `domain`, which can add integrity constraints to an underlying type. For example:

```sql
create domain DDollars as numeric(12, 2) not null;
```

There are two significant differences between types and domains:

1. Domains can have constraints, such as `not null`, specified on them, and can have default values defined for variables of the domain type, whereas userdefined types cannot have constraints or default values specified on them. User-defined types are designed to be used not just for specifying attribute types, but also in procedural extensions to SQL where it may not be possible to enforce constraints.
2. Domains are not strongly typed. As a result, values of one domain type can be assigned to values of another domain type as long as the underlying types are compatible.

Applications often require creation of tables that have the same schema as an existing table. SQL provides a `create table like` extension to support this task:

```sql
create table temp_instructor like instructor;
```

We can create and drop schemas by means of `create schema` and `drop schema` statements.

We may assign a user several forms of authorizations on parts of the database. Authorizations on data include:

- Authorization to read data.
- Authorization to insert new data.
- Authorization to update data.
- Authorization to delete data.

, each of these types of authorizations is called a `privilege`.



## Summary

TODO
