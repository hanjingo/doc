# CHAPTER 13 Query Optimization



`Query optimization` is the process of selecting the most efficient query-evaluation plan from among the many strategies usually possible for processing a given query, especially if the query is complex.

Two relational algebra expressions are said to be `equivalent` if, on every legal database instance, the two expressions generate the same set of tuples.

An `equivalence rule` says that expressions of two forms are equivalent.

A set of equivalence rules is said to be `minimal` if no rule can be derived from any combination of the others.

in a `histogram,` the values for the attribute are divided into a number of ranges, and with each range, the histogram associates the number of tuples whose attribute value lies in that range.

an `equi-width histogram` divides the range of values into equal-sized ranges, whereas an `equi-depth` histogram adjusts the boundaries of the ranges such that each range has the same number of values.

We outline below how to estimate the sizes of the results of other relational-algebra operations:

- Projection.
- Aggregation.
- Set operations.
- Outer join.

A `cost-based optimizer` explores the space of all query-evaluation plans that are equivalent to the given quey, and chooses the one with the least estimated cost.

A particular sort order of the tuples is said to be an `interesting sort order` if it could be useful for a later operation.

Optimizers use `heuristics` to reduce the cost of optimization.

The System $R$ optimizer considers only those join orders where the right operand of each join is one of the initial relations $r_1, ..., r_n$. Such join orders are called `left-deep join orders`.

Most optimizers allow a cost budget to be specified for query optimization. The search for the optimal plan is terminated when the `optimization cost budget` is exceeded, and the best plan found up to that point is returned.

The caching and reuse of query plans is referred to as `plan caching`.

The process of replacing a nested query with a query with join (possibly with a temporary relation) is called `decorrelation`.

The task of keeping a materialized view up-to-date with the underlying data is known as `view maintenance`.

A better option is to modify only the affected parts of the materialized view, which is known as `incremental view maintenance`.

Most database systems perform `immediate view maintenance`; that is, incremental view maintenance is performed as soon as an update occurs, as part of the updating transaction.

Some database systems also support `deferred view maintenance`, where view maintenance is deferred to a later time.

Aggregation operations proceed somewhat like projections. The aggregate operations in SQL are:

- count
- sum
- avg
- min, max

Complex queries may in fact have subexpressions repeated in different parts of the query, which can be similarly exploited, to reduce query evaluation costs. Such optimization is known as `multi-query optimization`.

`Common subexpression elimination` optimizes subexpressions shared by different expressions in a program, by computing and storing the result, and reusing it wherever the subexpression occurs.

The `shared-scan` optimization works as follows: Instead of reading the relation repeatedly from disk, once for each query that needs to scan a relation, data are read once from disk, and pipelined to each of the queries.

In `parametric query optimization`, a query is optimized without being provided specific values for its parameters.



## Summary

TODO