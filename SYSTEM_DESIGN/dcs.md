# Distributed System Design

[TOC]



The advantages of using a distributed approach to system development:

1. Resource sharing.
2. Openness.
3. Concurrency.
4. Scalability.
5. Fault tolerance.

## Distributed systems issues

Some of the most important design issues that have to be considered in distributed system engineering are:

1. Transparency.
2. Openness.
3. Scalability.
4. Security.
5. Quality of service.
6. Failure management.

The scalability of a system reflects its ability to deliver a high quality of service as demands on the system increase. Neuman (1994) identifies three dimensions of scalability:

1. Size.
2. Distribution.
3. Manageability.

The types of attacks that a distributed system must defend itself against are the following:

1. Interception.
2. Interruption.
3. Modification.
4. Fabrication.

The quality of service (QoS) offered by a distributed system reflects the system's ability to deliver its services dependably and with a response time and throughput that is acceptable to its users.

### Models of interaction

There are two fundamental types of interaction that may take place between the computers in a distributed computing system:

- procedural interaction.
- message-based interaction.

### Middleware

![dcs_middleware](res/dcs_middleware.png)

*Middleware in a distributed system*

In a distributed system, middleware normally provides two distinct types of support:

1. Interaction support, where the middleware coordinates interactions between different components in the system.
2. The provision of common services, where the middleware provides reusable implementations of services that may be required by several components in the distributed system.



## Architectural patterns for distributed systems

Five architectural styles:

1. Master-slave architecture, which is used in real-time systems in which guaranteed interaction response times are required.
2. Two-tier client-server architecture, which is used for simple client-server systems, and in situations where it is important to centralize the system for security reasons. In such cases, communication between the client and server is normally encrypted.
3. Multitier client-server, which is used when there is a high volume of transactions to be processed by the server.
4. Distributed component architecture, which is used when resources from different systems and databases need to be combined, or as an implementation model for multi-tier client-server systems.
5. Peer-to-peer architecture, which is used when clients exchange locally stored information, and the role of the server is to introduce clients to each other. It may also be used when a large number of independent computations may have to be made.

### Master-slave architectures

![master_slave_arch](res/master_slave_arch.png)

*A traffic management system with a master-slave architecture*

### Two-tier client-server architectures

![thin_fat_client_arch](res/thin_fat_client_arch.png)

*Thin-and fat-client architectural models*

### multi-tier client-server architectures

![multi_tier_cs_arch](res/multi_tier_cs_arch.png)

*Three-tier architecture for an Internet banking system*

### Distributed component architectures

![distributed_component_arch](res/distributed_component_arch.png)

*A distributed component architecture*

The benefits of using a distributed component model for implementing distributed systems are the following:

1. It allows the system designer to delay decisions on where and how services should be provided.
2. It is a very open system architecture that allows new resources to be added as required.
3. The system is flexible and scalable.
4. It is possible to reconfigure the system dynamically with components migrating across the network as required.

Distributed component architectures suffer from two major disadvantages:

1. They are more complex to design than client-server systems.
2. Standardized middleware for distributed component systems has never been accepted by the community.

### Peer-to-peer architectures

![p2p_arch])(res/p2p_arch.png)

*A decentralized p2p architecture*

![semi_cent_p2p_arch](res/semi_cent_p2p_arch.png)

*A semi-centralized p2p architecture*

It is appropriate to use a peer-to-peer architectural model for a system in two circumstances:

1. Where the system is computationally intensive and it is possible to separate the processing required into a large number of independent computations.
2. Where the system primarily involves the exchange of information between individual computers on a network and there is no need for this information to be centrally stored or managed.



## Consensus Algorithms

- Crash Fault Tolerant(CFT) Algorithms:
  - Paxos (for more detail, see:[doc/DCS/CONSENSUS/paxos.md](https://github.com/hanjingo/doc/blob/master/DCS/CONSENSUS/paxos.md))
  - Raft (for more detail, see:[doc/DCS/CONSENSUS/raft.md](https://github.com/hanjingo/doc/blob/master/DCS/CONSENSUS/raft.md))
- Byzantine Fault Tolerant(BFT) Algorithms:
  - Practical Byzantine Fault Tolerance(PBFT) (for more detail, see:[doc/DCS/CONSENSUS/pbft.md](https://github.com/hanjingo/doc/blob/master/DCS/CONSENSUS/pbft.md))
  - Tendermint
- Proof-Based Algorithms:
  - Proof of Work(PoW) (for more detail, see:[doc/DCS/CONSENSUS/pow.md](https://github.com/hanjingo/doc/blob/master/DCS/CONSENSUS/pow.md))
  - Proof of Stake(PoS) (for more detail, see:[doc/DCS/CONSENSUS/pos.md](https://github.com/hanjingo/doc/blob/master/DCS/CONSENSUS/pos.md))
  - Delegate Proof of Stake(DPoS) (for more detail, see:[doc/DCS/CONSENSUS/dpos.md](https://github.com/hanjingo/doc/blob/master/DCS/CONSENSUS/dpos.md))
- Leader-Based Algorithms:
  - Viewstamped Replication(VR)
  - Multi-Paxos
- Voting-Based Algorithm
  - Quorum-Based Algorithms
  - Federated Byzantine Agreement(FBA)



## Secure

Authentication and authorization mechanisms are essential for securing structures and facts. Authentication verifies person identities, while authorization controls their get entry to sources.

### Authentication Mechanisms

1. Passwords and PINs

   - Pros: Simple, widely used.
   - Cons: Vulnerable to assaults(brute pressure, phishing).

2. Biometrics

   - Pros: Hard to forge.
   - Cons: Privacy concerns, false positives/negatives.

3. Multi-Factor Authentication(MFA)

   - Pros: Stronger security.
   - Cons: More complex for users.

4. Token-Based Authentication

   - Pros: Enhances protection.
   - Cons: Tokens can be misplaced or stolen.

5. Certificate-Based Authentication

   - Pros: Strong safety, broadly used in corporations.
   - Cons: Requires infrastructure for dealing with certificates(PKI).

6. Single Sign-On(SSO)

   - Pros: Convenient, improves user experience.
   - Cons: Single factor of failure.

### Authorization mechanisms

1. Role-Based Access Control(RBAC)

   - Pros: Simplifies control, enforces least privilege.
   - Cons: Can be rigid in dynamic environments.

2. Attribute-Based Access Control(ABAC)

   - Pros: Flexible, quality-grained manage.
   - Cons: Complex to put into effect and manage.

3. Discretionary Access Control(DAC)

   - Pros: Flexible, simple
   - Cons: Less secure, liable to insider threats.

4. Mandatory Access Control(MAC)

   - Pros: High safety.
   - Cons: Rigid, hard to control in large businesses.

5. Policy-Based Access Control

   - Pros: Flexible, adaptable to complicated environments.
   - Cons: Can be tough to outline and control regulations.



## Advantage And Disadvantage

Advantages:

- Resource Sharing
- Multiple Independent Nodes
- Transparency
- Scalability
- Reliability and Fault Tolerance
- Performance

Disadvantages:

- Complexity
- Security Challenges
- Network Dependency
- Data Consistency Issues
- Higher Cost
- Troubleshooting Difficulties



## Reference

[1] George Coulouris; Jean Dolimore; Tim Kindberg; Gordon Blair . DISTRIBUTED SYSTEMS: Concepts and Design . 5ED

[2] [Introduction to Distributed System](https://www.geeksforgeeks.org/computer-networks/what-is-a-distributed-system/)