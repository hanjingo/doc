# Chapter3 Introduction to SQL

The SQL language has several parts:

- Data-definition language(DDL).
- Data manipulation language(DML).
- Integrity.
- View definition.
- Transaction control.
- Embedded SQL and dynamic SQL.
- Authorization.

The SQL DDL allows specification of not only a set of relations, but also information about each realation, including:

- The schema for each relation.
- The types of values associated with each attribute.
- The integrity constraints.
- The set of indices to be maintained for each relation.
- The security and authorization information for each relation.
- The physical storage structure of each relation on disk.

The SQL standard supports a variety of built-in types, including:

- char(n).
- varchar(n).
- int.
- smallint.
- numeric(p, d).
- real, double, precision.
- float(n)

A `null` value indicates an absent value that may exist but be unknown or that may not exist at all.

The `char` data type stores fixed length strings.

We define a SQL relation by using the `creat table` command. The general form of the `create table` command is:

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

We can use the `delete` command to delete tuples from a relation:

```sql
delete from student;
```

To remove a relation from an SQL database, we use the `drop table` command. The `drop table` command deletes all information about the dropped relation from the database. The command:

```sql
drop table r;
```

is a more drastic action than:

```sql
delete from r;
```

the latter retains relation $r$, but deletes all tuples in $r$.

We use the `alter table` command to add attributes to an existing relation. The form of the `alter table` command is:

```sql
alter table r add A D;
```

where $r$ is the name of an existing relation, $A$ is the name of the attribute to be added, and $D$ is the type of the added attribute. We can drop attributes from a relation by the command:

```sql
alter table r drop A;
```

where $r$ is the name of an existing relation, and $A$ is the name of an attribute of the relation.

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

SQL allows the use of the logical connectives `and`, `or`, and `not` in the `where` clause. The operands of the logical connectives can be expressions involving the comparison operators `<`, `<=`, `>`, `>=`, `=`, and `<>`. SQL allows us to use the comparison operators to compare strings and arithmetic expressions, as well as special types, such as data types.

An SQL query can contain three types of clauses, the `select` clause, the `from` clause, and the `where` clause. The role of each clause is as follows:

- The `select` clause is used to list the attributes desired in the result of a query.
- The `from` clause is a list of the relations to be accessed in the evaluation of the query.
- The `where` clause is a predicate involving attributes of the relation in the `from` clause.

a typical SQL query has the form:

```sql
select A1, A2, ..., An from r1, r2, ..., rm where P;
```

each $A_i$ represents an attribute, and each $r_i$ a relation. $P$ is a predicate. If the `where` clause is omitted, the predicate $P$ is true.

The `natural join` operation operates on two relations and produces a relation as the result.

A `from` clause in an SQL query can have multiple relations combined using natural join, as shown here:

```sql
select A1, A2, ..., An from r1 natural join r2 natural join ... natural join rm where P;
```

more generally, a `from` clause can be of the form:

```sql
from E1, E2, ..., En
```

where each $E_i$ can be a single relation or an expression involving natural joins.

The operation `join ... using` requires a list of attribute names to be specified. Both inputs must have attributes with the specified names. Consider the operation `r1 join r2 using(A1, A2)`. The operation is similar to `r1 natural join r2`, except that a pair of tuples $t_1$ from $r_1$ and $t_2$ from $r_2$ match f $t_1 \cdot A_1 = t_2 \cdot A_1$ and $t_1 \cdot A_2 = t_2 \cdot A_2$; the if $r_1$ and $r_2$ both have an attribute named $A_3$, it is not required that $t_1 \cdot A_3 = t_2 \cdot A_3$.

The names of the attributes in the result are derived from the names of the attributes in the relations in the `from` clause.

SQL provides a way of renaming the attributes fo a result relation. It uses the `as` clause, taking the form:

```sql
old-name as new-name
```

the `as` clause can appear in both the select and `from` clauses.

SQL specifies strings by enclosing them in single quotes.

Pattern matching can be performed on strings, using the operator `like`. we describe patterns by using two special characters:

- `Percent(%)`: The `%` character matches any substring.
- `Underscore(_)`: The `_` character matches any character.

patterns are case sensitive; that is, uppercase characters do not match lowercase characters, or vice versa.

SQL expresses patterns by using the `like` comparison operator.

We define the escape character for a `like` comparison using the `escape` keyword. To illustrate, consider the following patterns, which use a backslash(`\`) as the escape character:

- `like 'ab\%cd%' escape '\'` matches all strings beginning with `"ab%cd"`.
- `like 'ab\\cd%' escape '\'` matches all strings beginning with "ab\cd".

sql allows us to search for mismatches instead of matches by using the `not like` comparison operator. Some databases provide variants of the `like` operation which do not distinguish lower and upper case.

The asterisk symbol `*` can be used in the `select` clause to denote "all attributes". Thus, the use of `instructor.*` in the `select` clause of the query:

```sql 
select instruct.* from instructor, teaches where instructor.ID=teaches.ID;
```

indicates that all attributes of `instructor` are to be selected.

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

Since the predicate in a `where` clause can involve Boolean operations such as `and`, `or`, and `not` on the results of comparisons, the definitions of the Boolean operations are extended to deal with the value `unknown`.

SQL uses the special keyword `null` in a predicate to test from a null value. for example:

```sql
select name from instructor where salary is null;
```

The predicate `is not null` succeeds if the value on which it is applied is not null.

`Aggregae functions` are functions that take a collection (a set or multiset) of values as input and return a single value. SQL offers five built-in aggregate functions:

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

The attribute or attributes given in the `group by` clause are used to form groups. Tuples with the same value on all attributes in the `group by` clause are placed in one group:

```sql
select dept_name, avg(salary) as avg_salary from instructor group by dept_name;
```

We use the `having` clause of SQL. SQL applies predicates in the `having` clause after groups have been formed, so aggregate functions may be used. We express this query in SQL as follows:

```sql
select dept_name, avg(salary) as avg_salary from instructor group by dept_name having avg(salary) > 42000;
```

The `count` of an empty collection is defined to be 0, and all other aggregate operations return a value of null when applied on an empty collection.

A `Boolean` data type that can take values `true`, `false`, and `unknown`. The aggregate functions `some` and `every`, which mean exactly what you would intuitively expect, can be applied on a collection of Boolean values.

A subquery is a `select-from-where` expression that is nested within another query.

The `in` connective tests for set membership, where the set is a collection of values produced by a `select` clause. The `not in` connective tests for the absence of set membership:

```sql
select distinct course_id from section where semester='Fall' and year=2009 and course_id not in (select course_id from section where semester='Spring' and year=2010);
```

SQL also allows `<some`, `<=some`, `>=some`, `=some`, and `<>some` comparisons. As an exercise, verify that `=some` is identical to `in`, whereas `<>some` is not the same as `not in`:

```sql
select name from instructor where salary>all(select salary from instructor where dept_name='Biology');
```

as it does from `some`, SQL also allows `<all`, `<=all`, `>=all`, `=all`, and `<>all` comparisons. As an exercise, verify that `<>all` is identical to `not in`, whereas `=all` is not the same as `in`.

A subquery that uses a correlation name from an outer query is called a `correlated subquery`.

We can test for the nonexistence of tuples in a subquery by using the `not exists` construct.

The `unique` construct returns the value `true` if the argument subquery contains no duplicate tuples:

```sql
select T.course_id from course as T where unique(select R.course_id from section as R where T.course_id=R.course_id and R.year = 2009);
```

SQL allows a subquery expression to be used in the `from` clause. The key concept applied here is that any `select-from-where` expression returns a relation as a result and, therefore, can be inserted into another `select-from-where` anywhere that a relation can appear.

The `with` clause provides a way of defining a temporary relation whose definition is available only to the query in which the `with` clause occurs:

```sql
with max_budget(value) as (select max(budget) from department) select budget from department, max_budget where department.budget=max_budget.value.
```

SQL allows subqueries to occur wherever an expression returning a value is permitted, provided the subquery returns only one tuple containing a single attribute; such subqueries are called `scalar subqueries`:

```sql
select dept_name, (select count(*) from instructor where department.dept_name=instructor.dept_name) as num_instructors from department;
```

A delete request is expressed in much the same way as a query. We can delete only whole tuples; we cannot delete values on only particular attributes. SQL expresses a deletion by:

```sql
delete from r where P;
```

where $P$ represents a predicate and $r$ represents a relation.

The simplest `insert` statement is a request to insert one tuple:

```sql
insert into course values('CS-437', 'DB', 'Comp.Sci', 4);
```

for the benefit of users who may not remember the order of the attributes, SQL allows the attributes to be specified as part of the `insert` statement:

```sql
insert into course(id, title, name, credits) values('CS-437', 'DB', 'Comp.Sci', 4);
```

if we carry out some insertions even as the `select` statement is being evaluated, a request such as:

```sql
insert into student select * from student;
```

In certain situations, we may wish to change a value in a tuple without changing `all` values in the tuple. For this purpose, the `update` statement can be used:

```sql
update instructor set salary=salary*1.05;
```

In general, the `where` clause of the `update` statement may contain any construct legal in the `where` clause of the `select` statement (including nested selects).

SQL provides a `case` construct that we can use to perform both the updates with a single `update` statement, avoiding the problem with the order of updates:

```sql
update instructor set salary= case
	when salary <= 1 than salary*1.05
	else salary*1.03
end
```

Scalar subqueries are also useful in SQL update statements, where they can be used in the `set` clause:

```sql
update student S set tot_cred=(
	select sum(credits) from takes natural join course 
  	where S.ID=takes.ID and takes.grade <> 'F' and take.grade is not null
);
```



## Summary

TODO
