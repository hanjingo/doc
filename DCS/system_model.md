# Distributed System Model

[TOC]



## Overview

Understanding distributed systems requires different levels of abstraction to capture their complexity and behavior. System models provide structured frameworks for describing, analyzing, and designing distributed systems from multiple perspectives. This document explores three complementary approaches to modeling distributed systems:

- **Physical models** describe the hardware infrastructure and network topology
- **Architectural models** define the organization of computational elements and their interactions
- **Fundamental models** examine core aspects like process interaction and failure handling

Each model offers unique insights into distributed system design and helps address specific challenges in building reliable, scalable distributed applications.



## Physical Models

Physical models provide an explicit description of a system's hardware composition, including computers, mobile devices, and their interconnecting networks. Understanding the evolution of physical models helps contextualize current design decisions.

### Evolution of Distributed Systems

The development of distributed systems can be characterized through three distinct generations:

| Aspect               | Early Generation                                          | Internet-Scale Generation                                    | Contemporary Generation                                      |
| -------------------- | --------------------------------------------------------- | ------------------------------------------------------------ | ------------------------------------------------------------ |
| **Scale**            | Small                                                     | Large                                                        | Ultra-large                                                  |
| **Heterogeneity**    | Limited (typically homogeneous configurations)            | Significant in terms of platforms, languages, and middleware | Added dimensions including radically different architectural styles |
| **Openness**         | Not a priority                                            | Significant priority with a range of standards introduced    | Major research challenge; existing standards cannot yet embrace complex systems |
| **Quality of Service** | In its infancy                                          | Significant priority with a range of services introduced     | Major research challenge; existing services cannot yet embrace complex systems |

**Early generation** systems focused on connecting a limited number of relatively similar machines within local networks. **Internet-scale** systems introduced significant heterogeneity and openness, leading to the development of numerous standards and middleware solutions. **Contemporary** systems face unprecedented challenges in scale and complexity, pushing the boundaries of existing standards and requiring new approaches to system design.



## Architectural Models

Architectural models describe systems in terms of computational and communication tasks performed by computational elements—individual computers or aggregates supported by appropriate network interconnections. These models focus on the logical organization rather than physical implementation.

### Architectural Elements

#### Communication Paradigms

The choice of communication paradigm significantly impacts system design and performance:

**1. Interprocess Communication**

Provides relatively low-level support for communication between processes, including:
- Message-passing primitives
- Direct access to Internet protocol APIs (socket programming)
- Support for multicast communication

**2. Remote Invocation**

Builds on interprocess communication to support client-server computing:
- **Request-reply protocols**: Patterns imposed on underlying message-passing services to support client-server computing
- **Remote procedure calls (RPC)**: Allow programs to call procedures on remote machines as if they were local
- **Remote method invocation (RMI)**: Object-oriented extension of RPC that allows invoking methods on remote objects

**3. Indirect Communication**

Enables loose coupling between communicating entities:
- **Group communication**: One-to-many communication pattern
- **Publish-subscribe systems**: Publishers send messages to topics; subscribers receive messages from topics they subscribe to
- **Message queues**: Asynchronous point-to-point communication through persistent queues
- **Tuple spaces**: Coordination through shared data spaces
- **Distributed shared memory**: Provides the illusion of shared memory across distributed nodes

### Architectural Patterns

#### Layering

Layering partitions complex systems into hierarchical levels, where each layer uses services from the layer below and provides services to the layer above. This approach offers several benefits:
- **Abstraction**: Higher layers remain unaware of implementation details of lower layers
- **Modularity**: Changes to one layer minimally impact other layers
- **Reusability**: Well-defined interfaces enable component reuse

The layered approach applies to both software and hardware organization, creating clear separation of concerns and enabling independent evolution of system components.

#### Tiered Architecture

Tiered architectures are complementary to layering. While layering deals with vertical organization of services into abstraction levels, tiering organizes the functionality of a given layer:
- **Horizontal organization**: Distributes functionality across appropriate servers
- **Physical deployment**: Places components onto physical nodes for optimal performance
- **Scalability**: Enables independent scaling of different tiers

Common patterns include two-tier (client-server), three-tier (presentation, application, data), and n-tier architectures.

### Middleware Solutions

Middleware provides a software layer between applications and underlying operating systems/networks, abstracting heterogeneity and providing common programming abstractions.

Middleware solutions span various categories:
- **Communication middleware**: Message-oriented middleware, remote procedure call systems
- **Application middleware**: Transaction processing monitors, application servers
- **Integration middleware**: Enterprise service buses, message brokers
- **Data middleware**: Distributed databases, distributed file systems



## Fundamental Models

Fundamental models take an abstract perspective to examine individual aspects of distributed systems, helping us understand core challenges and design appropriate solutions.

### Interaction Model

The interaction model addresses how processes in a distributed system communicate and coordinate. Two significant factors affect interacting processes:

#### Performance of Communication Channels

Communication over computer networks exhibits these performance characteristics:

- **Latency**: The delay between sending and receiving a message, affected by:
  - Processing time at operating system levels
  - Network transmission time
  - Queuing delays at network switches and routers

- **Bandwidth**: The amount of data that can be transmitted per unit time, determining throughput capacity

- **Jitter**: Variation in message delivery times, critical for real-time applications like video streaming

#### Computer Clocks and Timing Events

Each computer has its own internal clock for timestamping events. However, clock synchronization presents challenges:
- Clocks **drift** from perfect time at different rates
- Even if read simultaneously, different computers may report different times
- This affects ordering of events and coordination between processes

#### Synchronous vs. Asynchronous Systems

**Synchronous Distributed Systems**

A synchronous distributed system has defined bounds on:
- Process execution speeds (known lower and upper bounds for each step)
- Message transmission delays (known bounded time for message delivery)
- Clock drift rates (known bound on drift from real time)

While simplifying reasoning about system behavior, true synchronous systems are rare in practice.

**Asynchronous Distributed Systems**

An asynchronous distributed system has no bounds on:
- Process execution speeds
- Message transmission delays  
- Clock drift rates

Most real-world distributed systems are asynchronous, making reasoning about their behavior more challenging but reflecting practical realities.

#### Event Ordering

Consider processes $X$, $Y$, and $Z$ exchanging messages. If their clocks could be perfectly synchronized, messages $m_1$, $m_2$, and $m_3$ would carry timestamps $t_1$, $t_2$, and $t_3$ where $t_1 < t_2 < t_3$, enabling correct ordering.

With roughly synchronized clocks, timestamps often reflect correct ordering, though perfect synchronization remains elusive in practice.

### Failure Model

The failure model characterizes ways in which distributed system components can fail, essential for designing fault-tolerant systems.

#### Omission Failures

Omission failures occur when a process or communication channel fails to perform expected actions:

**Process Omission Failures**
- The primary example is **crash failure**: a process halts and does not execute further steps
- Crashes may be detectable (fail-stop) or undetectable

**Communication Omission Failures**

Communication can fail at different points:
- **Send omission**: Outgoing message buffer fails to transmit
- **Receive omission**: Incoming message buffer fails to receive
- **Channel omission**: Message is lost in the network

#### Severity of Failures

Failures range from benign to severe:

**Benign Failures**

Most distributed system failures are benign, including:
- **Omission failures**: Failures to send or receive messages
- **Timing failures**: Violations of time bounds in synchronous systems
- **Performance failures**: Degraded but functional service

**Timing Failures**

Applicable in synchronous distributed systems with time limits:

- **Process timing failure**: Process response outside time interval
- **Message timing failure**: Message delivery outside specified bounds
- **Clock timing failure**: Clock drift exceeds specified bounds

**Arbitrary (Byzantine) Failures**

The most severe failure semantics, where any type of error may occur:
- Processes may produce incorrect outputs
- Messages may be corrupted or fabricated
- Components may exhibit malicious behavior

Byzantine failures are rare but catastrophic, requiring sophisticated protocols like Byzantine fault tolerance (BFT) for mitigation.

#### Masking Failures

Failure masking techniques hide failures from higher layers:
- Retransmission masks message loss
- Replication masks process failures
- Error-correcting codes mask data corruption

### Reliable Communication

Reliable communication is defined in terms of two key properties:

**Validity**: Any message in the outgoing message buffer is eventually delivered to the incoming message buffer.

**Integrity**: The message received is identical to one sent, and no messages are delivered twice.

#### Threats to Integrity

Two independent sources threaten message integrity:

1. **Protocol-level threats**
   - Protocols that retransmit messages without detecting duplicates
   - Solution: Attach sequence numbers to messages for duplicate detection

2. **Security-level threats**
   - Malicious users may inject spurious messages
   - Attackers may replay old messages
   - Messages may be tampered with in transit
   - Solution: Implement security measures including authentication, encryption, and integrity checks



## Conclusion

System models provide complementary perspectives for understanding distributed systems:

- **Physical models** ground our understanding in hardware realities and network topologies
- **Architectural models** provide structural frameworks for organizing computational elements and their interactions
- **Fundamental models** help us reason about core challenges like process interaction, timing, and failures

Together, these models enable designers to make informed decisions, anticipate challenges, and build robust distributed systems. As distributed systems continue to evolve toward greater scale and complexity, these modeling approaches remain essential tools for managing complexity and ensuring system reliability.



## Reference

[1] George Coulouris, Jean Dolimore, Tim Kindberg, Gordon Blair. DISTRIBUTED SYSTEMS: Concepts and Design. 5ED
