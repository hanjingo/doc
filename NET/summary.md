English | [中文版](summary_zh.md)

# Network Summary

[TOC]



## Network Topology

### Mesh Topology

![mesh_topology](res/mesh_topology.png)

### Star Topology

![star_topology](res/star_topology.png)

### Bus Topology

![bus_topology](res/bus_topology.png)

### Ring Topology

![ring_topology](res/ring_topology.png)

### Tree Topology

![tree_topology](res/tree_topology.png)

### Hybrid Topology

![hybrid_topology](res/hybrid_topology.png)

### Point to Point Topology

![p2p_topology](res/p2p_topology.png)

### Daisy Chain Topology

![daisy_chain_topology](res/daisy_chain_topology.png)

---



## OSI Reference Model

![layer7_and_5_osi_model](res/layer7_and_5_osi_model.png)

7-layer OSI reference model:

| Number | Name         | Desc |
| ------ | ------------ | ---- |
| 7      | Application  |      |
| 6      | Presentation |      |
| 5      | Session      |      |
| 4      | Transport    |      |
| 3      | Network      |      |
| 2      | Link         |      |
| 1      | Physical     |      |

5-layer Internet protocol stack:

| Number | Name        | Desc |
| ------ | ----------- | ---- |
| 5      | Application |      |
| 4      | Transport   |      |
| 3      | Network     |      |
| 2      | Link        |      |
| 1      | Physical    |      |

![osi_example](res/osi_example.png)

### Application Layer

The application architecture, on the other hand, is designed by the application developer and dictates how the application is structured over the various end systems.

### Transport Layer

A transport-layer protocol provides for `logical communication` between application processes running on different hosts.

![src_dst_port_num_field](res/src_dst_port_num_field.png)

*Source and destination port-number fields in a transport-layer segment*

![tcp_segment](res/tcp_segment.png)

*TCP segment structure*

### Network Layer

![network_layer](res/network_layer.png)

*The network layer*

### Link Layer

The link layer is implemented in a `network adapter`, also sometimes known as a `network interface card (NIC)`.

![link_layer](res/link_layer.png)

*Network adapter: its relationship to other host components and to protocol stack functionality*

---



## Socket Programming

### TCP

![tcp_programming](res/tcp_programming.png)

### UDP

![udp_programming](res/udp_programming.png)

---



## Protocol

A protocol defines the format and the order of messages exchanged between two or more communicating entities, as well as the actions taken on the transmission and/or receipt of a message or other event.



## Reference

[1] James F. Kurose, Keith W. Ross . COMPUTER NETWORKING: A Top-Down Approach . 6ED
