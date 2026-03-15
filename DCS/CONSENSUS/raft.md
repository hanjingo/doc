English | [中文版](raft_zh.md)

# Raft

[TOC]



`raft (Reliable Replicated Redundant And Fault-Tolerant)` is a consensus algorithm designed to be easier to understand and implement than Paxos. It works by electing a leader among the nodes to manage log replication and ensure consistency. Raft breaks down consensus into three main subproblems: leader election, log replication, and safety.

## Process

1. Raft first elects a `leader`, who is fully responsible for managing the `replicated log`.
2. The `leader` receives all client update requests, then replicates them to `follower` nodes, and executes these requests when it is "safe" to do so.
3. If the `leader` fails, the `followers` will re-elect a new `leader`.



## Three Node States

* **Leader**
* **Follower**
* **Candidate**
`Maximum number of tolerated faulty nodes = (n-1)/2`

Note: Only one state can be held at a time.



## Leader Election

`Leader Election`: When the system starts, all nodes are in the `follower` state, or if a node does not receive a heartbeat from the leader for a period, it becomes a `candidate` and initiates an election as follows:

1. Increment the node's local `current term` and switch to `candidate` state
2. Vote for itself
3. Send `RequestVote RPCs` to other nodes in parallel to solicit votes
4. Wait for responses:
	- If it receives a majority of votes (including its own), it wins the election and becomes leader
	- If told another node has been elected, it switches back to `follower`
	- If no result is received within a period, it remains `candidate` and starts a new election

**Notes**

1. Each node can only vote once per term
2. The number of voters should be odd to avoid ties
3. The `leader` can only append records, not overwrite or delete them



## Log Replication

`Log Replication`: The whole cluster has a `state machine` (replicated state machine) that can execute external commands. The leader is responsible for log replication, as follows:

1. The `leader` accepts a command, writes it to its own log, and forwards the command to `followers`; if a follower does not respond, it retries.
2. When the `leader` receives confirmation from a majority of `followers`, the command is considered `committed`.
3. When a `follower` sees a command is `committed`, it executes the command.
4. If the `leader` crashes, the cluster's logs may be inconsistent; the new `leader` will compare logs with each `follower`, delete inconsistent entries from the follower, and copy its own log to them.



## Safety

`Safety`: Raft guarantees the following safety properties:

- Election Safety: At most one leader can be elected in a given term
- Leader Append-Only: A leader never overwrites or deletes entries; it only appends new ones
- Log Matching: If two logs contain an entry with the same term and index, then all preceding entries are identical
- Leader Completeness: If an entry is committed in a given term, it will be present in the logs of the leaders for all higher-numbered terms
- State Machine Safety: If a server has applied a log entry at a given index to its state machine, no other server will ever apply a different log entry for the same index



## Application Examples

1. Redis master node election and Sentinel election.



## References

[1] [Wikipedia - Raft](https://zh.wikipedia.org/wiki/Raft)

[2] [Raft algorithm explained](raft.md)

[3] [Consensus Algorithms in Distributed System](https://www.geeksforgeeks.org/operating-systems/consensus-algorithms-in-distributed-system/)
