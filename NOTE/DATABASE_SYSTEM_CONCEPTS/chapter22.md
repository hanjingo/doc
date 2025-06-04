# CHAPTER 22 Object-Based Databases



`Object-relational database systems`, that is, database systems based on the object-relation model, provide a convenient migration path for users of relational databases who wish to use object-oriented features.

We address the issue of supporting persistence for data that is in the native type system of an object-oriented programming language. Two approaches are used in practice:

1. Build an `object-oriented database system`, that is, a database system that natively supports an object-oriented type system, and allows direct access to data from an object-oriented programming language using the native type system fo the language.
2. Automatically convert data from the native type system of the programming language to a relational representation, and vice versa. Data conversion is specified using an `object-relational mapping`.

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

The consistency requirements for subtables are:

1. Each tuple of the supertable can correspond to at most one tuple in each of its immediate subtables.
2. SQL has an additional constraint that all the tuples corresponding to each other must be derived from one tuple (inserted into one table).

The following example illustrates how this array and multiset-valued attributes can be defined in SQL:

```sql
create type Publisher as (
	name varchar(20),
	branch varchar(20));
	
create type Book as (
	title varchar(20),
	author_array varchar(20) array [10],
	pub_date date,
	publisher Publisher,
	keyword_set varchar(20) multiset);
	
create table books of Book;
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

Subtables can be stored in an efficient manner, without replication of all inherited fields, in one of two ways:

- Each table stores the primary key (which may be inherited from a parent table) and the attributes that are defined locally. Inherited attributes (other than the primary key) do not need to be stored, and can be derived by means of a join with the supertable, based on the primary key.
- Each table stores all inherited and locally defined attributes. When a tuple is inserted, it is stored only in the table in which it is inserted, and its presence is inferred in each of the supertables. Access to all attributes of a tuple is faster since a join is not required.

A `persistent programming language` is a programming language extended with constructs to handle persistent data. Persistent programming languages can be distinguished from languages with embedded SQL in at least two ways:

1. With an embedded language, the type system of the host language usually differs from the type system of the data manipulation language. The programmer is responsible for any type of conversions between the host language and SQL. Having the programmer carry out this task has several drawbacks:
   - The code to convert between objects and tuples operates outside the object-oriented type system and hence has a higher chance of having undetected errors.
   - Conversion between the object-oriented format and the relational format of tuples in the database takes a substantial amount of code. The format translation code, along with the code for loading and unloading data from a database, can form a significant percentage of the total code required for an application.
2. The programmer using an embedded query language is responsible for writing explicit code to fetch data from the database into memory. If any updates are performed, the programmer must write code explicitly to store the updated data back in the database.

Persistence of Objects:

- `Persistence by class`.
- `Persistence by creation`.
- `Persistence by marking`.
- `Persistence by reachability`.

There are several degrees of permanence of identity:

- `Intraprocedure`.
- `Intraprogram`.
- `Interprogram`.
- `Persistent`.

Persistent C++ Systems:

- `Persistent pointers`.
- `Creation of persistent objects`.
- `Class extents`.
- `Relationships`.
- `Iterator interface`.
- `Transactions`.
- `Updates`.
- `Query language`.

Persistent Java Systems:

- `Persistence by reachability`.
- `Byte code enhancement`.
- `Database mapping`.
- `Class extents`.
- `Single reference type`.

We can summarize the strengths of the various kinds of database systems in this way:

- `Relational systems`: Simple data types, powerful query languages, and high protection.
- `Persistent programming language-based OODBs`: Complex data types, integration with programming language, high performance.
- `Object-relational systems`: Complex data types, powerful query languages, high protection.
- `Object-relational mapping systems`: Complex data types integrated with programming languages, designed as a layer on top of relational database systems.
