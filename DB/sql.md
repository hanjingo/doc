[中文版](sql_zh.md) | English

# SQL Language

[TOC]



## Data Type

The SQL standard supports a variety of built-in types, including:

- char(n).
- varchar(n).
- int.
- smallint.
- numeric(p, d).
- real, double, precision.
- float(n)



## Table Operation

- `create table`

  We define a SQL relation by using the `create table` command. The general form of the `create table` command is:

  ```sql
  create table r
  	(A1 D1,
     A2 D2,
     ...,
     An Dn,
     <integrity-constraint1>,
     ...
     <integrity-constraintk>);
  ```

  where $r$ is the name of the relation, each $A_i$ is the name of an attribute in the schema of relation $r$, and $D_i$ is the domain of attribute $A_i$; that is, $D_i$ specifies the type of attribute $A_i$ along with optional constraints that restrict the set of allowed values for $A_i$.

- `drop table`

  The `drop table` command deletes all information about the dropped relation from the database. The command:

  ```sql
  drop table r;
  ```

  is a more drastic action than:

  ```sql
  delete from r;
  ```

  the latter retains relation $r$, but deletes all tuples in $r$.

- `alter table`

  We use the `alter table` command to add attributes to an existing relation. The form of the `alter table` command is:
  
  ```sql
  alter table r add A D;
  ```
  
  where $r$ is the name of an existing relation, $A$ is the name of the attribute to be added, and $D$ is the type of the added attribute. We can drop attributes from a relation by the command:
  
  ```sql
  alter table r drop A;
  ```
  
  where $r$ is the name of an existing relation, and $A$ is the name of an attribute of the relation.
  



## Select

We want to force the elimination of duplicates, we insert the keyword `distinct` after `select`. we can rewrite the preceding query as:

```sql
select distinct A from r;
```

if we want duplicates removed. The result of the above query would contain each department name at most once.

SQL allows us to use the keyword `all` to specify explicitly that duplicates are not removed:

```sql
select all A from r;
```

The `select` clause may also contain arithmetic expressions involving the operators `+`, `-`, `*`, and `/` operating on constants or attributes fo tuples. for example:

```sql
select A, B*1.1 from r;
```

The `where` clause allows us to select only those rows in the result relation of the `from` clause that satisfy a specified predicate.

A `from` clause in an SQL query can have multiple relations combined using natural join, as shown here:

```sql
select A1, A2, ..., An from r1 natural join r2 natural join ... natural join rm where P;
```

more generally, a `from` clause can be of the form:

```sql
from E1, E2, ..., En
```

where each $E_i$ can be a single relation or an expression involving natural joins.

*NOTICE*:

An SQL query can contain three types of clauses, the `select` clause, the `from` clause, and the `where` clause. The role of each clause is as follows:

- The `select` clause is used to list the attributes desired in the result of a query.
- The `from` clause is a list of the relations to be accessed in the evaluation of the query.
- The `where` clause is a predicate involving attributes of the relation in the `from` clause.

### Sorting

The `order by` clause causes the tuples in the result of a query to appear in sorted order. To specify the sort order, we may specify `desc` for descending order or `asc` for ascending order:

```sql
select * from instructor order by salary desc, name asc;
```

SQL includes a `between` comparison operator to simplify `where` clauses that specify that a value be less than or equal to some value and greater than or equal to some other value. we can use the `between` comparison to write:

```sql
select name from instructor where salary between 1 and 10;
```

instead of:

```sql
select name from instructor where salary <= 1 and salary >= 10;
```

similarly, we can use the `not between` comparison operator.

### Pattern Matching

Pattern matching can be performed on strings, using the operator `like`. we describe patterns by using two special characters:

- `Percent(%)`: The `%` character matches any substring.
- `Underscore(_)`: The `_` character matches any character.

patterns are case sensitive; that is, uppercase characters do not match lowercase characters, or vice versa.

SQL expresses patterns by using the `like` comparison operator.

We define the escape character for a `like` comparison using the `escape` keyword. To illustrate, consider the following patterns, which use a backslash(`\`) as the escape character:

- `like 'ab\%cd%' escape '\'` matches all strings beginning with `"ab%cd"`.
- `like 'ab\\cd%' escape '\'` matches all strings beginning with "ab\cd".

SQL allows us to search for mismatches instead of matches by using the `not-like` comparison operator. Some databases provide variants of the `like` operation which do not distinguish lower and upper case.

The asterisk symbol `*` can be used in the `select` clause to denote "all attributes". Thus, the use of `instructor.*` in the `select` clause of the query:

```sql 
select instruct.* from instructor, teaches where instructor.ID=teaches.ID;
```

indicates that all attributes of `instructor` are to be selected.

### Union And Filt

SQL permits us to use the $notation(v_1, v_2, ..., v_n)$ to denote a tuple of arity $n$ containing values $v_1, v_2, ..., v_n$. The comparison operators can be used on tuples, and the ordering is defined lexicographically. Thus, the preceding SQL query can be rewritten as follows:

```sql
select name, course_id from instructor, teaches where (instructor.ID, dept_name)=(teaches.ID, 'Biology');
```

The SQL operations `union`, `intersect`,  and `except` operate on relations and correspond to the mathematical set-theory operations $\cup$, $\cap$, and $-$.

The `union` operation automatically eliminates duplicates, unlike the `select` clause. If we want to retain all duplicates, we must write `union all` in place of `union`:

```sql
(select course_id from section where semester='Fall' and year=2009) union all (select course_id from section where semester='Spring' and year=2010);
```

If we want to retain all duplicates, we must write `intersect all` in place of `intersect`:

```sql
(select course_id from section where semester='Fall' and year=2009) intersect all (select course_id from section where semester='spring' and year=2010);
```

The `except` operation outputs all tuples from its first input that do not occur in the second input; that is, it performs set differences. The operation automatically eliminates duplicates in the inputs before performing set difference:

```sql
(select course_id from section where semester='Fall' and year=2009) except (select course_id from section where semester='Spring' and year =2010);
```

If we want to retain duplicates, we must write `except all` in place of `except`:

```sql
(select course_id from section where semester='Fall' and year=2009) except all (select course_id from section where semester='spring' and year = 2010);
```

Null values present special problems in relational operations, including arithmetic operations, comparison operations, and set operations.



## Function

`Aggregate functions` are functions that take a collection (a set or multiset) of values as input and return a single value. SQL offers five built-in aggregate functions:

- Average: avg
- Minimum: min
- Maximum: max
- Total: sum
- Count: count

We can give a meaningful name to the attribute by using the `as` clause as follows:

```sql
select avg(salary) as avg_slary from instructor where dept_name='Comp.Sci.';
```

If we do want to eliminate duplicates, we use the keyword `distinct` in the aggregate expression:

```sql
select count(distinct ID) from teches where semester='Spring' and year=2010;
```

The attributes or attributes given in the `group by` clause are used to form groups. Tuples with the same value on all attributes in the `group by` clause are placed in one group:

```sql
select dept_name, avg(salary) as avg_salary from instructor group by dept_name;
```

We use the `having` clause of SQL. SQL applies predicates in the `having` clause after groups have been formed, so aggregate functions may be used. We express this query in SQL as follows:

```sql
select dept_name, avg(salary) as avg_salary from instructor group by dept_name having avg(salary) > 42000;
```

The `count` of an empty collection is defined to be 0, and all other aggregate operations return a value of null when applied on an empty collection.



## Join Operation

The `outer join` operation works in a manner similar to the join operations.

There are, in fact three forms of outer join:

- The `left outer join` preserves tuples only in the relation named before (to the left of) the `left outer join` operation.
- The `right outer join` preserves tuples only in the relation named after (to the right of) the `right outer join` operation.
- The `full outer join` preserves tuples in both relations.



## User-Defined Type

The above types are called `user-defined` types in SQL:

```sql
create type Address as (
	street varchar(20),
	city varchar(20),
	zipcode varchar(9))
	not final;
```

Subtables defined example:

```sql
create table students of Student under people;
create table teachers of Teacher under people;
```

If we want to insert the preceding tuple into the relations, For example:

```sql
insert into books
	values('Compilers', 
         array['Smith', 'Jones'], 
         new Publisher('McGraw-Hill', 'New York'),
         multiset['parsing', 'analysis']);
```

The `unnest with ordinality` clause can be used to get this information, as illustrated by the following query:

```sql
select title, A.author, A.position from books as B, unnest(B.author_array) with ordinality as A(author, position);
```



