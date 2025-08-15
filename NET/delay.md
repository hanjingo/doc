# Delay

[TOC]



Sending one packet from the source to the destination over a path consisting of $N$ links each of the rates $R$(thus, there are $N - 1$ routers between the source and destination). Applying the same logic as above, we see that the end-to-end delay is:
$$
d_{end-to-end} = N \frac{L}{R} \qquad (1.1)
$$

## Queuing Delays

`queuing delays`. These delays are variable and depend on the level of congestion in the network. Since the amount of buffer space is finite, an arriving packet may find that the buffer is completely full with other packets waiting for transmission. In this case, `packet loss` will occur--either the arriving packet or one of the already-queued packets will be dropped.

As a packet travels from one node (host or router) to the subsequent node (host or router) along this path, the packet suffers from several types of delays at each node along the path. The most important of these delays are:

- `Processing Delay`.
- `Queuing Delay`.
- `Transmission Delay`.
- `Propagation Delay`.

![average_queuing_delay](res/average_queuing_delay.png)

*Dependence of average queuing delay on traffic intensity*



## RTT

`round-trip time (RTT)`, which is the time it takes for a small packet to travel from client to server and then back to the client. The `RTT` includes packet-propagation delays, packet-queuing delays in intermediate routers and switches, and packet-processing delays.



## Total Delay

If we let $d_{proc}$, $d_{queue}$, $d_{trans}$, and $d_{prop}$ denote the processing, queuing, transmission, and propagation delays, then the total nodal delay is given by:
$$
d_{nodal} = d_{proc} + d_{queue} + d_{trans} + d_{prop}
$$
The contribution of these delay components can vary significantly.



## Reference

[1] James F. Kurose, Keith W. Ross . Computer Networking: A Top-Down Approach . 6ED
