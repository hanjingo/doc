# QOS

## Quality of Service (QoS) — concise reference

[TOC]

This note collects the most important QoS concepts from a network perspective: performance metrics, delay components and their intuition, basic queuing behaviour, QoS architectures (IntServ vs DiffServ), common queuing disciplines, policing and shaping, and practical measurement/troubleshooting tips. The treatment follows the style of Kurose & Ross while keeping the presentation compact.

### Key metrics

- Latency (one-way delay): time for a packet to travel from sender to receiver.
- RTT (round-trip time): time for a small packet to travel to the peer and for its response to return.
- Jitter: variation in packet delay (important for real-time media).
- Throughput: achieved application-level transfer rate.
- Loss rate: fraction of packets lost in transit.

Together these metrics determine application experience: e.g., high loss + retransmission increases effective latency and reduces throughput.

### Delay components

As a packet traverses a path, it experiences delays at each node. Common components:

- Processing delay (d_proc): time to examine packet header and perform routing/forwarding.
- Queuing delay (d_queue): time a packet waits in an output queue before transmission; depends strongly on instantaneous load.
- Transmission delay (d_trans): time to push the packet's bits onto the link, L/R, where L is packet size (bits) and R is link bandwidth (bits/sec).
- Propagation delay (d_prop): time for signal to travel across the medium (distance / propagation speed).

The per‑node (n·odal) delay is

$$
d_{nodal} = d_{proc} + d_{queue} + d_{trans} + d_{prop}.
$$

End-to-end (approximate) delay across N links is the sum of per-node delays. For uniform link rates R and packet size L and ignoring queueing and processing, a simple bound is

$$
d_{end-to-end} \approx N\frac{L}{R}.
$$

But queueing dominates under load: queuing delay grows nonlinearly as utilization ρ→1. For an M/M/1 queue with arrival rate λ and service rate μ (service rate μ = 1/average service time), define ρ = λ/μ. The mean time in system (service + waiting) is

$$
W = \frac{1}{\mu - \lambda} = \frac{1/\mu}{1-\rho},
$$

and the mean waiting (queueing) time is

$$
W_q = \frac{\rho}{\mu - \lambda} = \rho\frac{1/\mu}{1-\rho}.
$$

These formulas illustrate that small increases in utilization near 1 produce large increases in queuing delay.

### RTT

RTT = one-way delay (forward) + one-way delay (back). RTT includes propagation, queuing, and processing delays in the forward and reverse directions. RTT matters for transport protocols (e.g., TCP congestion control and timeout estimation).

![rtt_example](res/rtt_example.png)

### Reliability and transport primitives (summary)

Reliable transport typically uses a small set of mechanisms; common items and purpose:

| Mechanism | Purpose / comments |
|---|---|
| Checksum | Detect bit errors in a packet. |
| Timers | Trigger retransmission when ACKs are not received in time; timeout tuning affects both performance and spurious retransmits. |
| Sequence numbers | Detect losses and duplicates; enable reordering and in-order delivery semantics. |
| Acknowledgments (ACKs) | Inform sender of successful receipt; can be cumulative to reduce ACK overhead. |
| Negative ACKs (NAKs) | Explicitly inform sender about missing or corrupted packets (less common). |
| Windowing / pipelining | Allow multiple outstanding packets to keep the pipe full; window size interacts with RTT and receiver buffer capacity. |


### QoS architectures and mechanisms

- Best-effort: the default Internet model — no guaranteed service; scalability and simplicity.

- Integrated Services (IntServ): per‑flow resource reservation (RSVP) and strict guarantees. Precise but does not scale well to many flows.

- Differentiated Services (DiffServ): scalable, class-based treatment using DSCP codepoints; edge devices classify/mark packets and core routers provide per‑class queuing and forwarding behaviours.

Admission control, policing, and shaping are often combined with these architectures to protect guarantees and control overload.

### Queuing disciplines (common)

- FIFO (drop-tail): simple, can produce global synchronization and unfairness under congestion.
- Priority queuing: strict priority for high‑priority flows; can starve low priority traffic.
- Fair queuing (FQ) and Weighted Fair Queuing (WFQ): approximate fair bandwidth sharing among active flows.
- Class-Based Queuing (CBQ): groups traffic into classes with allocated bandwidth.
- Active Queue Management (AQM) (e.g., RED, CoDel): drop/mark packets before buffers fill to avoid long queues and reduce latency.

Choice of discipline affects delay, jitter, and loss patterns seen by applications.

### Policing vs shaping

- Traffic policing: enforces rate limits by dropping or remarking packets that exceed a configured profile (often using token-bucket meters). Policing is an enforcement action.
- Traffic shaping: buffers and smooths bursts to conform to a profile; reduces instant bursts at the cost of added delay.

Token bucket: a common mechanism to allow controlled bursts while enforcing an average rate.

### Measurement and practical tips

- Measure RTT and one-way delay where possible; clock sync is required for accurate one-way measurements.
- Monitor queue occupancy and packet-drop rates to detect congestion and bufferbloat.
- Use AQM (e.g., CoDel) to mitigate excessive queuing delay (bufferbloat) in access networks.
- When designing QoS policies, identify traffic classes (real‑time, interactive, bulk) and match treatment (low latency for voice, high throughput for bulk).
- Test under realistic churn and traffic mixes (synthetic low-latency flows can be overwhelmed by bulk flows if not isolated).

### Quick troubleshooting checklist

1. Is latency the issue (high RTT) or loss/throughput? Measure both.
2. Check link utilization and queue lengths; if utilization is high, consider AQM, shaping, or capacity upgrade.
3. Verify DSCP markings at network edges are preserved through the path.
4. For voice/video: ensure jitter buffers are appropriately sized and that packets aren’t being re-ordered excessively.

## References

- James F. Kurose, Keith W. Ross. Computer Networking: A Top-Down Approach.
- RFCs: DiffServ (RFC 2475), RSVP and IntServ (RFC 2205), AQM (CoDel papers), relevant token-bucket RFCs.
