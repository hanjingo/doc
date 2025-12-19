# 1 CHARACTERIZATION OF DISTRIBUTED SYSTEMS

[TOC]



## Introduction

We define a distributed system as one in which hardware or software components located at networked computers communicate and coordinate their actions only by passing messages.

Our definition of distributed systems has the following significant consequences:

- Concurrency.
- No global clock.
- Independent failures.



## Challenges

### Heterogeneity

**Middleware**. The term *middleware* applies to a software layer that provides a programming abstraction as well as masking the heterogeneity of the underlying networks, hardware, operating systems, and programming languages.

**Heterogeneity and mobile code**. The term *mobile code* is used to refer to program code that can be transferred from one computer to another and run at the destination.

The *virtual machine* approach provides a way of making code executable on a variety of host computers: the compiler for a particular language generates code for a virtual machine instead of a particular hardware order code.

### Openness

The openness of a computer system is the characteristic that determines whether the system can be extended and reimplemented in various ways. The openness of distributed systems is determined primarily by the degree to which new resource-sharing services can be added and made available for use by a variety of client programs. To summarize:

- Open systems are characterized by the fact that their key interfaces are published.
- Open distributed systems are based on the provision of a uniform communication mechanism and published interfaces for access to shared resources.
- Open distributed systems can be constructed from heterogeneous hardware and software, possibly from different vendors. But the conformance of each component to the published standard must be carefully tested and verified if the system is to work correctly.

### Security

Security for information resources has three components:

- confidentiality
- integrity
- availability

The following two security challenges have not yet been fully met:

- *Denial of service attacks*: This can be achieved by bombarding the service with such a large number of pointless requests that the serious users are unable to use it.
- *Security of mobile code*.

### Scalability

A system is described as *scalable* if it will remain effective when there is a significant increase in the number of resources and the number of users.

The design of scalable distributed systems presents the following challenges:

- *Controlling the cost of physical resources*: As the demand for a resource grows, it should be possible to extend the system, at reasonable cost, to meet it.
- *Controlling the performance loss*.
- *Preventing software resources running out*.

### Transparency

The ANSA Reference Manual and the International Organization for Standardization's Reference Model for Open Distributed Processing (RM-ODP) identify eight forms of transparency:

- *Access transparency* enables local and remote resources to be accessed using identical operations.
- *Location transparency* enables resources to be accessed without knowledge of their physical or network location.
- *Concurrency transparency* enables several processes to operate concurrently using shared resources without interference between them.
- *Replication transparency* enables multiple instances of resources to be used to increase reliability and performance without knowledge of the replicas by users or application programmers.
- *Failure transparency* enables the concealment of faults, allowing users and application programs to complete their tasks despite the failure of hardware or software components.
- *Mobility transparency* allows the movement of resources and clients within a system without affecting the operation of users or programs.
- *Performance transparency* allows the system to be reconfigured to improve performances as loads vary.
- *Scaling transparency* allows the system and applications to expand in scale without a change to the system structure or the application algorithms.

### Quality of service

The main non-functional properties of systems that affect the quality of the service experienced by clients and users are:

- *reliability*
- *security*
- *performance*
- *adaptability* (to meet changing system configurations and resource availability has been recognized as a further important aspect of service quality.)

