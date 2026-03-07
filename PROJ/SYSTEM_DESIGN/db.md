[中文版](db_zh.md) | English

# Database Design

[TOC]

This note summarizes practical principles for designing and operating relational and analytical databases. It covers schema design and normalization, common system architectures, data partitioning strategies for scale-out systems, distributed database types and trade-offs, and an introduction to data warehousing and OLAP design. Diagrams under `res/` illustrate the architectures.

## Relational schema design

Good schema design starts with modeling entities and relationships, identifying keys and functional dependencies (FDs), and normalizing to reduce redundancy and anomalies.

Important rules for reasoning about functional dependencies:

- Reflexivity: if β ⊆ α then α → β.
- Augmentation: if α → β then αγ → βγ for any attribute set γ.
- Transitivity: if α → β and β → γ then α → γ.

From FDs you can derive candidate keys and reason about normalization. Normal forms reduce update anomalies:

- 1NF (atomicity)
- 2NF (no partial dependency on a composite key)
- 3NF (no transitive dependency on a key)
- BCNF (every nontrivial FD has a superkey on the left)

Normalization trades redundancy for more joins; in practice OLTP schemas are usually normalized while OLAP schemas are denormalized for read performance.

Schema design steps (recommended):

1. Elicit requirements and draw an ER model.
2. List attributes and candidate keys; infer functional dependencies.
3. Normalize to the desired normal form, then consider denormalization where justified by performance.
4. Add indexes, constraints, and physical design choices (partitioning, clustering) to match workload characteristics.

## System architectures

Architectural choices affect scalability, fault tolerance, and operational complexity:

- Client–server: single DB server or cluster accessed by clients; simple but may become a bottleneck.
- Shared-disk: multiple server instances access the same storage (SAN); requires coordination to keep caches coherent.
- Shared-nothing: each node owns its storage and processes a partition of the data; this model scales well horizontally and is common in parallel DBMS and distributed stores.

Refer to `res/center_computer_system.png`, `res/cs_system.png`, and `res/paral_db_arch.png` for illustrations.

## Data partitioning strategies

Partitioning (sharding) is a primary technique for scaling databases. Common strategies include:

- Round-robin: scatter tuples cyclically across nodes/disks. It balances raw storage and sequential I/O but destroys locality (poor for range queries and colocated joins).
- Hash partitioning: hash on one or more attributes to determine the home partition. Hashing balances load and is ideal for equality joins on the partition key because matching tuples appear on the same node.
- Range partitioning: assign contiguous key ranges to partitions. Range partitioning preserves ordering and supports efficient range scans but requires careful split-point selection to avoid hotspots.

Other considerations:

- Replication: copy data to multiple nodes for read scaling and fault tolerance. Synchronous replication preserves strong consistency but adds latency; asynchronous replication favors availability.
- Composite/hybrid partitioning: combine hash and range partitioning (subpartitioning) to exploit multiple access patterns.
- Skew mitigation: monitor and rebalance partitions, use adaptive hashing or hotspot offloading to handle skewed workloads.

## Distributed database models and consistency

Distributed databases span multiple sites and must trade off consistency, availability, and partition tolerance (CAP theorem). Two common setups:

- Homogeneous distributed DB: all sites run the same DBMS and share a global schema and coordination protocol. Easier coordination and uniform tooling.
- Heterogeneous/federated DB: sites may run different systems and schemas; middleware performs schema translation and query federation.

Transaction and consistency approaches:

- Two-phase commit (2PC): provides atomic commit for distributed transactions but can block during coordinator failures.
- Consensus-based replication (Paxos/Raft): builds highly-available replicated state machines and supports leader-based replication.
- Eventual consistency / BASE: relax strong consistency for higher availability and lower latency (common in many NoSQL systems).

Choose the appropriate consistency and replication strategy based on application semantics (financial transactions need serializability; user-facing caches may tolerate weaker guarantees).

## Data warehouse and OLAP design

Data warehouses centralize historical data for analytics. Typical characteristics:

- ETL: Extract, Transform, Load pipelines ingest and clean data from transactional sources.
- Schema patterns: star schema (fact table + dimension tables) and snowflake schema (normalized dimensions). Star schemas are common for reporting because they simplify queries.
- Columnar storage, compression, and vectorized execution: common optimizations for scan-heavy analytic workloads.
- Materialized views and pre-aggregations: speed up frequent queries at the cost of maintenance overhead.

See `res/data_warehouse_arch.png` for an architecture diagram.

## Physical design and operational considerations

- Index selection: choose B-tree, hash, bitmap, or inverted indexes depending on query patterns and cardinality.
- Partitioning and locality: align partitions with typical query predicates and geographic requirements.
- Isolation levels: choose between read committed, repeatable read, and serializable based on correctness and performance needs.
- Backups and recovery: design backup frequency, retention, and point-in-time recovery capability.

## Practical checklist for database design

1. Model entities and relationships (ER).
2. Identify candidate keys and functional dependencies.
3. Normalize to the desired normal form; consider selective denormalization for performance.
4. Select partitioning/sharding and replication strategies aligned with workload and availability goals.
5. Design indexes and access paths for critical queries.
6. Plan monitoring, backup, and operational procedures.

## References

- Abraham Silberschatz, Henry F. Korth, and S. Sudarshan. Database System Concepts, 6th Edition.