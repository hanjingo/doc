# CHAPTER 19 Distributed Databases

In a `homogeneous distributed database` system, all sites have identical database management system software, are aware of one another, and agree to cooperate in processing users’ requests. In such a system, local sites surrender a portion of their autonomy in terms of their right to change schemas or database-management system software. That software must also cooperate with other sites in exchanging information about transactions, to make transaction processing possible across multiple sites.

In contrast, in a `heterogeneous distributed database`, different sites may use different schemas, and different database-management system software. The sites may not be aware of one another, and they may provide only limited facilities for cooperation in transaction processing. The differences in schemas are often a major problem for query processing, while the divergence in software becomes a hindrance for processing transactions that access multiple sites.

Consider a relation $r$ that is to be stored in the database. There are two approaches to storing this relation in the distributed database:

- Replication. The system maintains several identical replicas (copies) of the relation, and stores each replica at a different site. The alternative to replication is to store only one copy of relation $r$.
- Fragmentation. The system partitions the relation into several fragments, and stores each fragment at a different site.

There are a number of advantages and disadvantages to replication:

- Availability. If one of the sites containing relation $r$ fails, then the relation $r$ can be found in another site. Thus, the system can continue to process queries involving $r$, despite the failure of one site.
- Increased parallelism. In the case where the majority of accesses to the relation $r$ result in only the reading of the relation, then several sites can process queries involving $r$ in parallel. The more replicas of r there are, the greater the chance that the needed data will be found in the site where the transaction is executing. Hence, data replication minimizes movement of data between sites.
- Increased overhead on update. The system must ensure that all replicas of a relation $r$ are consistent; otherwise, erroneous computations may result. Thus, whenever $r$ is updated, the update must be propagated to all sites containing replicas. The result is increased overhead. 

If relation $r$ is fragmented, $r$ is divided into a number of $fragments\ r_1, r_2,...,r_n$. These fragments contain sufficient information to allow reconstruction of the original relation $r$. There are two different schemes for fragmenting a relation:

- `Horizontal fragmentation` splits the relation by assigning each tuple of $r$ to one or more fragments.

  In horizontal fragmentation, a relation $r$ is partitioned into a number of subsets, $r_1, r_2,...,r_n$. Each tuple of relation $r$ must belong to at least one of the fragments, so that the original relation can be reconstructed, if needed.

- `Vertical fragmentation` splits the relation by decomposing the scheme $R$ of relation $r$.

  Vertical fragmentation of $r(R)$ involves the definition of several subsets of attributes $R_1, R_2,..., R_n$ of the schema $R$ so that:
  $$
  R = R_1 \cup R_2 \cup \cdots \cup R_n
  $$
  Each fragment $r_i$ of $r$ is defined by:
  $$
  r_i = \prod R_i (r)
  $$
  The fragmentation should be done in such a way that we can reconstruct relation $r$ from the fragments by taking the natural join:
  $$
  r = r_1 \bowtie r_2 \bowtie r_3 \bowtie ··· \bowtie r_n
  $$
  

The user of a distributed database system should not be required to know where
the data are physically located nor how the data can be accessed at the specific
local site. This characteristic, called data transparency, can take several forms:

- `Fragmentation transparency`. Users are not required to know how a relation has been fragmented.

- `Replication transparency`. Users view each data object as logically unique. The distributed system may replicate an object to increase either system performance or data availability. Users do not have to be concerned with what data objects have been replicated, or where replicas have been placed.

- `Location transparency`. Users are not required to know the physical location of the data. The distributed database system should be able to find any data as long as the data identifier is supplied by the user transaction

The `local transactions` are those that access and update data in only one local database; the `global transactions` are those that access and update data in several local databases.

Each site has its own local transaction manager, whose function is to ensure the ACID properties of those transactions that execute at that site. The various transaction managers cooperate to execute global transactions. To understand how such a manager can be implemented, consider an abstract model of a transaction system, in which each site contains two subsystems:

![19_2](res/19_2.png)

- The `transaction manager` manages the execution of those transactions (or subtransactions) that access data stored in a local site. Note that each such transaction may be either a local transaction (that is, a transaction that executes at only that site) or part of a global transaction (that is, a transaction that executes at several sites).
- The `transaction coordinator` coordinates the execution of the various transactions (both local and global) initiated at that site.

The structure of a transaction manager is similar in many respects to the structure of a centralized system. Each transaction manager is responsible for:

- Maintaining a log for recovery purposes.
- Participating in an appropriate concurrency-control scheme to coordinate the concurrent execution of the transactions executing at that site.

The transaction coordinator subsystem is not needed in the centralized environment, since a transaction accesses data at only a single site. A transaction coordinator, as its name implies, is responsible for coordinating the execution of all the transactions initiated at that site. For each such transaction, the coordinator is responsible for:

- Starting the execution of the transaction.
- Breaking the transaction into a number of subtransactions and distributing these subtransactions to the appropriate sites for execution.
- Coordinating the termination of the transaction, which may result in the transaction being committed at all sites or aborted at all sites.

A distributed system may suffer from the same types of failure that a centralized system does (for example, software errors, hardware errors, or disk crashes). There are, however, additional types of failure with which we need to deal in a distributed environment. The basic failure types are:

- Failure of a site.
- Loss of messages.
- Failure of a communication link.
- Network partition.

If we are to ensure atomicity, all the sites in which a transaction $T$ executed must agree on the final outcome of the execution. $T$ must either commit at all sites, or it must abort at all sites. To ensure this property, the transaction coordinator of $T$ must execute a commit protocol:

- `two-phase commit protocol (2PC)`

  Consider a transaction $T$ initiated at site $S_i$ , where the transaction coordinator is $C_i$ .

  When $T$ completes its execution— that is, when all the sites at which $T$ has executed inform $C_i$ that $T$ has completed—$C_i$ starts the 2PC protocol.

  1. Phase 1. $C_i$ adds the record $<prepare\ T>$ to the log, and forces the log onto stable storage. It then sends a prepare $T$ message to all sites at which $T$ executed. On receiving such a message, the transaction manager at that site determines whether it is willing to commit its portion of $T$. If the answer is no, it adds a record $<no\ T>$ to the log, and then responds by sending an abort $T$ message to $C_i$ . If the answer is yes, it adds a record $<ready\ T>$ to the log, and forces the log (with all the log records corresponding to $T$) onto stable storage. The transaction manager then replies with a ready $T$ message to $C_i$ .
  2. Phase 2. When $C_i$ receives responses to the prepare $T$ message from all the sites, or when a prespecified interval of time has elapsed since the prepare $T$ message was sent out, $C_i$ can determine whether the transaction $T$ can be committed or aborted. Transaction $T$ can be committed if $C_i$ received a ready $T$ message from all the participating sites. Otherwise, transaction $T$ must be aborted. Depending on the verdict, either a record $<commit\ T>$ or a record $<abort\ T>$ is added to the log and the log is forced onto stable storage. At this point, the fate of the transaction has been sealed. Following this point, the coordinator sends either a commit $T$ or an abort $T$ message to all participating sites. When a site receives that message, it records the message in the log.

  The 2PC protocol responds in different ways to various types of failures:

  - Failure of a participating site.
  - Failure of the coordinator.
  - Network partition.

- `three-phase commit protocol (3PC)`

  The three-phase commit (3PC) protocol is an extension of the two-phase commit protocol that avoids the blocking problem under certain assumptions. In particular, it is assumed that no network partition occurs, and not more than $k$ sites fail, where $k$ is some predetermined number. Under these assumptions, the protocol avoids blocking by introducing an extra third phase where multiple sites are involved in the decision to commit. Instead of directly noting the commit decision in its persistent storage, the coordinator first ensures that at least $k$ other sites know that it intended to commit the transaction. If the coordinator fails, the remaining sites first select a new coordinator. This new coordinator checks the status of the protocol from the remaining sites; if the coordinator had decided to commit, at least one of the other $k$ sites that it informed will be up and will ensure that the commit decision is respected. The new coordinator restarts the third phase of the protocol if some site knew that the old coordinator intended to commit the transaction. Otherwise the new coordinator aborts the transaction.

`Persistent messages` are messages that are guaranteed to be delivered to the recipient exactly once (neither less nor more), regardless of failures, if the transaction sending the message commits, and are guaranteed to not be delivered if the transaction aborts.

We now consider the `implementation` of persistent messaging. Persistent messaging can be implemented on top of an unreliable messaging infrastructure, which may lose messages or deliver them multiple times, by these protocols:

- Sending site protocol.
- Receiving site protocol.

In the `single lock-manager` approach, the system maintains a single lock manager that resides in a single chosen site—say $S_i$. All lock and unlock requests are made at site $S_i$. When a transaction needs to lock a data item, it sends a lock request to $S_i$. The lock manager determines whether the lock can be granted immediately. If the lock can be granted, the lock manager sends a message to that effect to the site at which the lock request was initiated. Otherwise, the request is delayed until it can be granted, at which time a message is sent to the site at which the lock request was initiated. The transaction can read the data item from any one of the sites at which a replica of the data item resides. In the case of a write, all the sites where a replica of the data item resides must be involved in the writing.

The scheme has these advantages:

- Simple implementation. This scheme requires two messages for handling lock requests and one message for handling unlock requests.
- Simple deadlock handling. Since all lock and unlock requests are made at one site, the deadlock-handling algorithms discussed in Chapter 15 can be applied directly.

The disadvantages of the scheme are:

- Bottleneck. The site $S_i$ becomes a bottleneck, since all requests must be processed there.
- Vulnerability. If the site $S_i$ fails, the concurrency controller is lost. Either processing must stop, or a recovery scheme must be used so that a backup site can take over lock management from $S_i$.

A compromise between the advantages and disadvantages can be achieved through the `distributed-lock-manager` approach, in which the lock-manager function is distributed over several sites. 

Each site maintains a local lock manager whose function is to administer the lock and unlock requests for those data items that are stored in that site. When a transaction wishes to lock a data item $Q$ that is not replicated and resides at site $S_i$ , a message is sent to the lock manager at site $S_i$ requesting a lock (in a particular lock mode). If data item $Q$ is locked in an incompatible mode, then the request is delayed until it can be granted. Once it has determined that the lock request can be granted, the lock manager sends a message back to the initiator indicating that it has granted the lock request.

TODO

