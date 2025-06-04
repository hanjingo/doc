# Chapter 5 Advanced SQL



A database programmer must have access to a general-purpose programming language for at least two reasons:

1. Not all queries can be expressed in SQL since SQL does not provide the full expressive power of a general-purpose language.
2. Nondeclarative actions--such as printing a report, interacting with a user, or sending the results of a query to a graphical user interface--cannot be done from within SQL.

The `JDBC` standard defines an `application program interface (API)` that Jave programs can use to connect to database servers.

SQL supports constructs that give it almost all the power of a general-purpose programming language. The part of the SQL standard that deals with these constructs is called the `Persistent Storage Module (PSM)`.

A `trigger` is a statement that the system executes automatically as a side effect of a modification to the database. To design a trigger mechanism, we must meet two requirements:

1. Specify when a trigger is to be executed. This is broken up into an `event` that causes the trigger to be checked and a `condition` that must be satisfied for trigger execution to proceed.
2. Specify the `actions` to be taken when the trigger executes.

In particular, recursive queries should not use any of the following constructs, since they would make the query nonmonotonic:

- Aggregation on the recursive view.
- `not exists` on a subquery that uses the recursive view.
- Set difference (`except`) whose right-hand side uses the recursive view.
