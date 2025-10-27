# Relational Model

[TOC]

This note summarizes the relational data model and practical concepts you need when designing relational schemas and queries. It covers relations, schemas and tuples, keys and constraints, a brief overview of relational algebra and SQL mapping, integrity constraints, and normalization. The presentation follows the practical emphasis in standard database texts (see `NOTE/DATABASE_SYSTEM_CONCEPTS`).

## Relations, schemas, and tuples

- Relation: a relation is a set of tuples (rows). Conceptually it corresponds to a table in SQL.
- Schema: a relation schema R(A1, A2, ..., An) lists the attributes (columns) and their domains (types).
- Tuple: an ordered mapping from attribute names to values. In practice, SQL tables do not enforce tuple ordering; rows are an unordered multiset unless an ORDER BY is applied.

Example: a relation `Employee(EmpID, Name, DeptID, Salary)`.

## Keys and integrity constraints

- Candidate key: a minimal set of attributes that functionally determines all other attributes in the relation.
- Primary key: a chosen candidate key used to uniquely identify tuples.
- Foreign key: an attribute (or set) in one relation that references a primary key in another relation, enforcing referential integrity.

Integrity constraints:

- Domain constraints: attribute values must come from the declared domain (type, ranges).
- Not-null constraints: disallow NULL values for attributes.
- Unique constraints: ensure attribute values are unique across tuples.
- Referential integrity: foreign keys must reference existing tuples in the parent relation (or be NULL if allowed).

## Relational algebra (brief)

Relational algebra is a set of operations on relations that form the theoretical foundation for SQL. Key operators:

- Selection σ_{condition}(R): filter rows satisfying the condition.
- Projection π_{attrs}(R): select a subset of attributes (columns), removing duplicates.
- Cartesian product R × S: pairs each tuple of R with each tuple of S.
- Join (natural join ⋈ or θ-join): combine related tuples from two relations based on a predicate.
- Union, Intersection, Difference: set operations on relations with compatible schemas.
- Aggregation and grouping (in practical systems) compute summaries (SUM, AVG, COUNT) over groups.

These operators compose to express complex queries; SQL implements a rich dialect that maps to relational-algebraic plans in the query optimizer.

## Normalization and functional dependencies

Normalization uses functional dependencies (FDs) to reduce redundancy and update anomalies. Important points:

- A functional dependency X → Y means that for any two tuples, if they agree on X they must agree on Y.
- From FDs you can derive candidate keys and test normal forms (1NF, 2NF, 3NF, BCNF).

Normalization workflow:

1. List FDs for each relation (from requirements and domain knowledge).
2. Compute candidate keys and examine dependencies.
3. Decompose relations that violate desired normal forms into smaller relations that preserve dependencies and lossless join properties.

Trade-offs: normalization reduces redundancy and update anomalies but may increase the number of joins required at query time. Denormalize selectively for performance in read-heavy schemas.

## NULLs, three-valued logic and practical considerations

NULL represents missing or unknown values in SQL and introduces three-valued logic (true/false/unknown). Practical tips:

- Be explicit about whether attributes allow NULL; use NOT NULL for required attributes.
- Be careful with predicates and NULLs: comparisons with NULL yield UNKNOWN; use IS NULL / IS NOT NULL when testing.

## Mapping to SQL and implementation notes

- SQL tables implement the relational model with extensions (NULLs, duplicates, ordering, procedural features).
- The DBMS query optimizer rewrites SQL into relational-algebraic plans and chooses execution strategies (indexes, join algorithms, scans) based on statistics and available access paths.

## Design checklist (quick)

1. Define relations and attributes from the conceptual model.
2. Identify primary keys and foreign keys.
3. List functional dependencies and normalize to the chosen normal form.
4. Add indexes for common query predicates and joins.
5. Consider denormalization and partitioning for performance when necessary.

## References

- `NOTE/DATABASE_SYSTEM_CONCEPTS` (selected chapters on relational model and normalization)
- Abraham Silberschatz, Henry F. Korth, and S. Sudarshan. Database System Concepts.

<!-- End of relational model note -->
