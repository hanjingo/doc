English | [中文版](paxos_zh.md)

# Paxos

[TOC]



Paxos is a family of protocols developed by Leslie Lamport for achieving consensus in distributed systems despite network delays, node failures, and message looses. Paxos ensures that all nodes agree on a single value even if some nodes fail.

The Paxos algorithm runs in an asynchronous system that allows crash failures. It uses a majority mechanism to guarantee `2F+1` fault tolerance, meaning a system with `2F+1` nodes can tolerate up to `F` node failures, enabling distributed locking.

## Roles

- **Proposer**

  The proposer receives client requests and coordinates consensus; after receiving a request, it initiates a two-phase commit to reach agreement.

- **Acceptor**

  The acceptor votes on proposals and stores data; it votes on proposed values and accepts the agreed value, storing it.

- **Learner**

  The learner stores data; it does not participate in consensus but learns and stores the agreed value.

**Note: A node may serve multiple roles simultaneously.**



## Actions

- **Accept**

- **Promise**

- **Choose**




## Preconditions

1. Each proposal has a unique id; larger ids have higher priority.
2. id structure: `sequence number + service id`.



## Process

The Paxos process is as follows:
1. The `Proposer` sends a prepare request with `id=n` to the `Acceptor`.
2. When an `Acceptor` receives the request, if it has already seen an id greater than `n`, it replies with that higher proposal; otherwise it makes a promise (`Promise`) to not accept requests with `id<=n`.
3. If the `Proposer` does not receive any response with a higher proposal id, it sends an accept request (`Accept`) to the `Acceptor`.
4. The `Proposer` sends the decision result to all `Learner` nodes.

```sequence

```



## Multi-Paxos (an evolution of Paxos)

Because Paxos is relatively inefficient and multiple `Proposers` can cause conflicts and livelock, in practice:

- A `Leader Proposer` is elected, and only the leader can make proposals to prevent deadlock between multiple `Proposers`.
- The `Prepare` phase is often omitted; with a single proposer there is no deadlock, and `Prepare` is used to maintain a global maximum proposal id.



## References

[1] [Wikipedia - Paxos algorithm](https://zh.wikipedia.org/wiki/Paxos%E7%AE%97%E6%B3%95)

[2] [Paxos algorithm detailed explanation (Part 1)](https://blog.csdn.net/lin819747263/article/details/106313936)

[3] [Consensus Algorithms in Distributed System](https://www.geeksforgeeks.org/operating-systems/consensus-algorithms-in-distributed-system/)
